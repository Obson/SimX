#include <iostream>
#include <vector>

#include <thread>
#include <cstdlib>  // strtol
#include <sstream>  // stringstream
#include <string>

#include <iostream>
#include <fstream>


//#include <stdio.h>  // cwd
//#include <unistd.h>

#include "version.h"
#include "sector.h"
#include "transfer.h"

using namespace std;

void showVersion()
{
    cout << "SIM version " << AutoVersion::FULLVERSION_STRING << endl;
}

vector<Sector*> sectors;
vector<Transfer*> transfers;

bool sectorExists(string name)
{
    if (sectors.empty()) {
        return false;
    }
    for (auto it : sectors) {
        if (it->getName() == name) {
            return true;
        }
    }
    return false;
}

Sector *getSector(string name)
{
    for (auto it : sectors) {
        if (it->getName() == name) {
            return it;
        }
    }
    return nullptr;
}

void showSectorBalances()
{
    bool first = true;
    for (auto it : sectors) {
        if (first) {
            first = false;
        } else {
            cout << ", ";
        }
        cout << it->getName() << " = " << it->getMoneyStock();
    }
    cout << endl;
}

void showInfo()
{
    cout << endl << "Enter ':help' for more information" << endl << endl;
}

int interpret(istream &inf, bool prompt = true)
{
    string line;

    do {
        if (prompt) {
            cout << "SIM > ";
        }
        line.clear();
        getline(inf, line);
        stringstream ss(line);
        string tok1;
        ss >> tok1;

        if (inf.eof()) {
            return true;
        }

        if (tok1 == ":q" || tok1 == ":quit") {
            return 0;
        } else if (tok1.empty() || tok1 == "::") {
            continue;
        } else if (tok1 == ":v" || tok1 == ":ver") {
            showVersion();
        } else if (tok1 == ":l" || tok1 == ":load") {

            string fname;
            ss >> fname;
            ifstream infile;
            infile.open(fname);
            if (infile.is_open()) {
                interpret(infile, false);
            } else {
                cout << "Cannot open "  << fname << endl;
            }

        } else if (tok1 == ":h" || tok1 == ":help") {
            cout
                << endl << "Usage Summary" << endl << endl
                << ":h[elp]                          display this information" << endl
                << ":q[uit]                          terminate program" << endl
                << ":v[er]                           show program version" << endl
                << ":l[oad] <filename>               load model from file" << endl
                << ":s[ave]                          save model" << endl
                << ":s[ave] <filename>               save model as file" << endl
                << ":a[dd] sector <sector-name>      add sector" << endl
                << ":show sectors                    list existing sectors" << endl
                << ":show dictionary                 display list of defined dictionary entries" << endl
                << ":r[un] <num-cycles>              run the model for n-cycles cycles" << endl
                << ":clear                           clear existing expressions, sectors and transfers" << endl
                << ":show variables                  display list of variable names" << endl
                << "? <var-name>                     evaluate and display named value" << endl
                << "<var-name> = <exprn>             add equation" << endl
                << "<var-name> : <dest> <- <src>     define inter-sector transfer" << endl
                << "<var-name> : <dest> <+ <src>     define inter-sector transfer" << endl
                << endl;

        } else if (tok1 == ":clear") {

            for (auto it : sectors) {
                delete it;
            }
            sectors.clear();
            for (auto it : transfers) {
                delete it;
            }
            transfers.clear();
            Expression::clearAll();

        } else if (tok1 == ":add") {
            string tok2;
            ss >> tok2;
            if (tok2 == "sector") {
                string tok3;
                ss >> tok3;
                if (sectorExists(tok3)) {
                    cout << "A sector with that name already exists" << endl;
                    continue;
                }
                sectors.push_back(new Sector(tok3));
            } else {
                cout << "'" << tok2 << "' is not a valid entity" << endl;
            }
        } else if (tok1 == ":show") {
            string tok2;
            ss >> tok2;
            if (tok2 == "sectors") {
                if (sectors.empty()) {
                    cout << "No sectors have yet been defined" << endl;
                } else for (auto it : sectors) {
                    cout << it->getName() << endl;
                }
            } else if (tok2 == "dictionary") {
                Expression::showDictionary();
            /*
            } else if (tok2 == "variables") {
                unordered_map<int,Expression::Expression::Attribs> &dict = Expression::getDictionary();
                for (auto it : dict) {
                    if (it.second.category == Expression::Category::var) {
                        cout
                            << it.first
                            << ": "
                            << it.second.id
                            << it.second.value
                            << it.second.category
                            << endl;
                    }
                }
            */
            } else {
                cout << "'" << tok2 << "' is not a valid entity" << endl;
            }

        } else if (tok1 == "?") {

            string tok2;
            ss >> tok2;
            Expression::evaluate(tok2);

        } else if (tok1 == ":r" || tok1 == ":run" || tok1 == ":step") {

            if (ss.eof()) {
                cout << "Number of cycles is missing" << endl;
            } else {
                string num;
                ss >> num;

                bool ok = true;
                long int num_cycles;
                if (num.empty() || (!isdigit(num[0]))) {
                    ok = false;
                } else {
                    char * p;
                    num_cycles = strtol(num.c_str(), &p, 10);
                    ok = (*p == 0);
                }
                if (!ok) {
                    cout << num << " is not a valid integer" << endl;
                } else {
                    int n;
                    for (n = 0; n < num_cycles; n++) {
                        for (unsigned int i = 0; i < transfers.size(); i++) {
                            transfers[i]->exec();
                            if (tok1 == ":step") {
                                showSectorBalances();
                            }
                        }
                        if (tok1 == ":step" && (n < num_cycles)) {
                            cout << endl;
                        } else {
                            showSectorBalances();
                        }
                        Expression::resetAll();
                    }
                }
            }

        } else {

            // Could be an equation or a transfer-specification
            stringstream ss_out;
            bool eqn = false;

            for (unsigned int i = 0; i < line.length(); i++)
            {
                //cout << "i = " << i << ", line[i] = " << line[i] << endl;
                if (line[i] == '=') {
                    // Process as equation
                    eqn = true;
                    string var = ss_out.str();
                    if (var.length() == 0) {
                        cout << "Variable name is missing" << endl;
                    } else if (isdigit(var[0])) {
                        cout << "Variable names may not begin with a digit" << endl;
                    } else {
                        Expression *exp = new Expression(var, line.substr(i+1));
                        // Check for errors
                        if (exp->error != Expression::Error::none) {
                            switch(exp->error) {
                            case Expression::Error::no_tokens:
                                cout << "Right hand side of equation is missing" << endl;
                                break;
                            default:
                                break;
                            }
                            delete exp;
                            break;
                        }
                        // No errors if we got here
                        // ...
                    }
                } else if (line[i] == ':') {
                    // Process as transfer-spec
                    eqn = true;
                    string var = ss_out.str();
                    if (var.length() == 0) {
                        cout << "Variable name is missing" << endl;
                    } else if (isdigit(var[0])) {
                        cout << "Variable names may not begin with a digit" << endl;
                    } else {
                        string s1, opr, s2;
                        if (ss.eof()) {
                            cout << "RHS is missing" << endl;
                        } else {
                            string ignore;
                            ss >> ignore;   // skip ':'
                            if (!ss.eof()) {
                                ss >> s1;
                                if (!sectorExists(s1)) {
                                    cout << "Creating sector " << s1 << endl;
                                    sectors.push_back(new Sector(s1));
                                }
                                if (ss.eof()) {
                                    cout << "Incomplete transfer specification" << endl;
                                } else {
                                    ss >> opr;
                                    if (opr == "<-" || opr == "<+") {
                                        if (ss.eof()) {
                                            cout << "Source sector missing" << endl;
                                        } else {
                                            ss >> s2;
                                            if (!sectorExists(s2)) {
                                                cout << "Creating sector " << s2 << endl;
                                                sectors.push_back(new Sector(s2));
                                            }
                                            transfers.push_back(
                                                new Transfer(
                                                    getSector(s1),
                                                    getSector(s2),
                                                    var,
                                                    (opr == "<-")
                                                    )
                                            );
                                        }
                                    } else {
                                        cout << "Invalid operator (" << opr << ")" << endl;
                                    }
                                }
                            }
                        }
                    }
                } else if (isalnum(line[i]) || line[i] == '\'' || line[i] == '~') {
                    ss_out << line[i];
                } else if (line[i] == ' ') {
                    // This allows spaces in LHS identifiers, but as it ignores
                    // them we still get valid identifiers. This should be fixed
                    // some time.
                    continue;   // ignore spaces
                } else {
                    break;      // Invalid character
                }
            }

            if (!eqn) {
                cout << "Unrecognised command!" << endl;
            }

        }

    } while(true);

    return 0;
}

int main()
{
    cout << "SIM" << endl << "---" << endl;
    showVersion();
    showInfo();
    return interpret(cin, true);
}
