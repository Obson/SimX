#include <iostream>

#include "expression.h"
#include "globals.h"

#include "sector.h"

// Define statics
vector<string> Expression::names;
vector<string> Expression::freeVars;
unordered_map<int,Expression::Attribs> Expression::dict;
unordered_map<string, Expression*> Expression::definitions;
unordered_map<string, Expression*> Expression::probes;
unordered_map<string, Expression*> Expression::specials;
Expression::OpDesc *Expression::operators = 0;
bool Expression::initialised = false;

void crash(int line)
{
    cout << "*** Program fault in file " << __FILE__ << " at " << line << "***" << endl;
    exit(999);
}

/// @class Expression
/// Parses and resolves equations consisting of a dependent variable (LHS or
/// lvalue) and an rvalue that can consist of a sequence of terms and operators;
/// the name of a sector whose balance is required; or a special built-in
/// quantity such as the periodic time.

/// @brief Defines an expression identifying a sectoral balance with a dependent
/// variable (LHS or lvalue).

Expression::Expression(string &lhs, Sector *sect, double init)
{
    this->lhs = lhs;        // useful for diagnostics

    error = Error::none;
    if (!initialised) {
        initialise();
    }
    defined = -1;
    prev = init;
    sector = sect;
    is_sector_bal = true;   // see note in header
    is_special = false;
    is_parametric = false;
    orig = "Sector " + lhs;
    res = init;
    definitions[lhs] = this;

    return;
}

/// @brief Defines an expression consisting of a dependent variable (LHS or
/// lvalue) and a predicate (RHS or rvalue) containing a number of terms connected
/// by infix operators.

Expression::Expression(string &lhs, string &expr, ExpressionType t, double init)
{
    cout << "Expression::Expression(" << lhs << "," << expr << ")" << endl;
    this->lhs = lhs;        // useful for diagnostics

    error = Error::none;

    is_sector_bal = false;
    is_special = false;

    // Initialise on first instantiation only
    if (!initialised) {
        initialise();
    }

    orig = expr;
    defined = -1;
    prev = init;
    res = init;

    // Tokenise RHS
    int num_tokens = tokenise(expr);

    // Check OK
    if (num_tokens < 0) {
        error = Error::invalid_operator;
        return;
    } else if (num_tokens == 0) {
        error = Error::no_tokens;
        return;
    } else if (num_tokens == 1) {
        // Check if the sole token is a number and if so flag the expression as
        // a parameter (i.e. it can be changed dynamically)
        Attribs a = dict[tokens[0]];
        if (a.category == number) {
            is_parametric = true;
            dflt = a.value.d;
            res = dflt;
            prev = dflt;
        }
    }

    // Convert to RPN
    error = Error::none;
    reversePolish();
    if (error != Error::none) {
        return;
    }

    // Record as definition or probe
    if (t == exp_normal) {
        definitions[lhs] = this;
    } else {
        probes[lhs] = this;
    }
}

/// @brief Defines an expression connecting a dependent variable with a special
/// 'built-in' value.
///
/// @see SpecialType

Expression::Expression(string &lhs, SpecialType t)
{
    cout << "Expression::Expression(" << lhs << "," << t << ")" << endl;
    this->lhs = lhs;        // useful for diagnostics
    error = Error::none;

    orig = "[Time]";        /// @todo add other variations later
    defined = -1;
    prev = -1;
    res = -1;

    special_type = t;
    is_special = true;
    is_sector_bal = false;

    specials[lhs] = this;
}

Expression::~Expression()
{
}

bool Expression::isParameter()
{
    return is_parametric;
}

double Expression::getDefault()
{
    return dflt;
}

void Expression::revert(double init)
{
    defined = -1;
    if (!is_parametric) {
        prev = -1;
        res = init;
    }

    cout << "Expression::revert(" << init << "): prev = " << prev
        << ", res = " << res << ", defined = " << defined << endl;
}

void Expression::initialise()
{
    operators = new OpDesc[Optype::__count];
    operators[nullop] = {string(""), 0};
    operators[plus] = {string("+"), 1};
    operators[minus] = {string("-"), 1};
    operators[mult] = {string("*"), 2};
    operators[divide] = {string("/"), 2};
    operators[lparen] = {string("("), 0};
    operators[rparen] = {string(")"), 0};

    initialised = true;
}

/// @brief  Whether or not this variable refers to a sector balance
///
/// @return bool True if a sector balance; false otherwise.

bool Expression::isSectorBalance()
{
    return is_sector_bal;
}

/// @brief  Whether or not this variable refers to a built-in function
///
/// @return bool True if built-in function; false otherwise.

bool Expression::isSpecial()
{
    return is_special;
}

/// @brief returns the sector associated with this expression. If the expression
/// does not refer to a sectoral balance the result is undefined and not useful.

Sector *Expression::getSector()
{
    return sector;
}

/// @brief Check whether an expression exists having the specified name.
///
/// @param s string: the name of the required expression
/// @return Expression*: a pointer to the required expression if it exists, or
/// nullptr otherwise.
///
/// @see Expression::evaluated(string)

Expression *Expression::find(string s)
{
    Expression *exp;

    unordered_map<string,Expression*>::const_iterator it_specials = specials.find(s);
    if (it_specials == specials.end()) {
        unordered_map<string,Expression*>::const_iterator it_definitions = definitions.find(s);
        if (it_definitions == definitions.end()) {
            unordered_map<string,Expression*>::const_iterator it_probes = probes.find(s);
            if (it_probes == probes.end()) {
                exp = (Expression*)nullptr;
            } else {
                exp = it_probes->second;
            }
        } else {
            exp = it_definitions->second;
        }
    } else {
        exp = it_specials->second;
    }

    return exp;
}

void Expression::clearAll()
{
    // Clear tokens
    dict.clear();

    // Delete expressions
    for (auto it : definitions) {
        delete it.second;
    }

    // Clear definitions
    definitions.clear();

    // Clear names
    names.clear();

    // We don't clear specials as they are always available
}

void Expression::revertAll()
{
    for (auto it : definitions) {
        it.second->revert();
    }

    for (auto it : specials) {
        it.second->revert();
    }
}


/// @brief  error_string returns a message describing the last error encountered.
///
/// @return string: printable error message.
/// @see error_info

string Expression::error_string()
{
    string s;

    switch (error) {
    case none:
        s = "no error";
        break;
    case invalid_operator:
        s = "invalid operator " + error_info;
        break;
    case too_few_operands:
        s = "too few operands";
        break;
    case unmatched_rparen:
        s = "right parenthesis (\')\') without matching left parenthesis";
        break;
    case unmatched_lparen:
        s = "left parenthesis (\'(\') without matching right parenthesis";
        break;
    case undefined_expression:
        s = "cannot evaluate " + error_info;
        break;
    case incomplete_expression:
        s = "cannot evaluate " + error_info;
        break;
    default:
        s = "unknown error";
        break;
    }
    return s;
}

string Expression::getRHS()
{
    return (is_sector_bal ? sector->getDescription() + " sector balance" : orig);
}

/// @brief Returns the value of the expression if it has been evaluated
///
/// @return int: the value of the expression if it has been evaluated, otherwise
/// undefined.
///
/// @see evaluate(string), evaluated(), evaluate()

double Expression::value()
{
    return res;
}

double Expression::previousValue(int serial)
{
    // If the expression is marked as defined for this serial the previous value
    // will have been stored; otherwise we must use the current value. It's
    // worth checking that it's been defined up to 0, as otherwise there won't
    // be a current value either. In this case we chould really evaluate it,
    // but for now we'll just assume everything starts at zero. This should be
    // fixed later.
    if (defined == serial) {
        return defined > 0 ? prev : 0;
    } else if (serial < defined) {
        return 0;
    } else if (defined == -1) {
        evaluate(serial);
        return prev;
    } else {
        return (is_sector_bal ? sector->getBalance() : res);
    }
}

/// @brief Evaluates the operand represented by the token
///
/// @param tok int      : the token
/// @param val double&  : the result will be stored here iff successful
/// @param serial int   : interval counter (clock ticks)
///
/// @return bool        : true iff successful
///
/// This function adds a bit of housekeeping to the evaluation process so it can
/// be used when processing the RPN. It checks the token type and returns in good
/// order when things don't work out. It doesn't update *define* as it is only
/// producing an intermediate result.
///
/// @see evaluate()
///
/// @todo Improve error reporting; at present failure to evaluate a sub-expression
/// is only recorded as a failure in the calling expression. Needs investigating.

bool Expression::evaluate_token(int tok, double &val, int serial)
{
    Attribs a;
    Expression *expr;
    bool ok = false;

    assert(!is_sector_bal);

    a = dict[tok];

    if (a.category == var)
    {
        // Diagnostics only (remove later)
        string var_name = "";
        if (a.category == var) {
            var_name = names[a.id];
            if (var_name == "fs") {
                int x = 1234;
                x += 12;
            }
        }

        expr = Expression::find(names[a.id]);
        if (expr == nullptr)
        {
            error = undefined_expression;
            error_info = names[a.id];
            return false;
        }
        else
        {
            if (a.value.i < 0)
            {
                cout << "Expression::evaluate_token(): getting previous value" << endl;

                // Refers to previous value of the expression. No evaluation needed
                // as previous value is always available. However, we do not set
                // defined as is relates to the current value, which may not have
                // been evaluated or defined.

                val = expr->previousValue(serial);  // evaluates if necessary
                return true;
            }
            else if (expr->evaluate(serial))
            {
                val = expr->value();
                ok = true;
            }
            else
            {
                error = incomplete_expression;
                error_info = names[a.id];
            }
        }
    }
    else
    {
        assert(a.category == number);
        val = a.value.d;
        ok = true;
    }
    return ok;
}

void Expression::setValue(double d)
{
    if (is_parametric) {
        res = d;
        prev = d;
    }
}

/// @brief Evaluates the expression
///
/// @param serial int: interval counter. Incremented once for each clock tick
///
/// @return bool: *true* if a result was obtained or is available, otherwise *false*
///
/// @todo Tidy up distinction between undefined and incomplete expressions
///
/// @see evaluate(string), value(), evaluate_token(int, int&), error
///
/// If the expression has already been evaluated (check using the evaluated()
/// function) the function simply returns *true*. Otherwise it tries to evaluate
/// itself by interpreting its RPN representation. If successful the result is
/// stored, the function is marked as evaluated, and *true* is returned. If not,
/// *false* is returned, *error* is set to indicate the type of error,and if
/// appropriate additional information is stored in *error_info*. For example
/// if an expression was encountered that has not been defined, its name is
/// stored as *error_info*.

bool Expression::evaluate(int serial)
{
    cout << "Expression[" << lhs << "]::evaluate(" << serial << ")" << ", defined = " << defined << endl;

    /// @note If defined > serial we are reverting to an earlier state. Generally
    /// this would be a restart, in which case we should set prev and res back
    /// to their starting value -- essentially a partial re-initialisation. I
    /// think this should do it, but it should be kept under review. Also, we
    /// will need something much more sophisticated if we want to revert to an
    /// intermediate state.

    if (defined > serial) {
        revert();
    } else if (defined == serial) {
        return true;
    } else /* defined < serial */ {
        cout << "Expression[" << lhs << "]::evaluate(" << serial << "): " << "prev = " << prev << ", res = " << res << endl;
        prev = res;
        cout << "Expression[" << lhs << "]::evaluate(" << serial << "): " << "prev updated to " << prev << endl;
    }

    defined = serial;

    if (is_sector_bal) {
        res = sector->getBalance();
        defined = serial;
        return true;
    } else if (is_special) {
        /// @todo Add special fumction R returning a random number
        // At present there's only one kind of special function -- the time
        // function, which just returns the value of serial.
        defined = serial;
        res = serial;
        prev = serial - 1;
        return true;
    } else if (is_parametric) {
        // Value (res) will have been set from SimXFrame so no need to evaluate
        // anything
        return true;
    }

    stack<int> st;
    int tok, tok1, tok2, n;
    double res0, res1, res2;
    Attribs a;

    // For diagnostics
    if (rpn.size() < 1 || rpn.size() > 100) {
        wxMessageBox(_("Faulty RPN"), _("PROGRAM FAULT"), wxICON_EXCLAMATION);
    }

    if (rpn.size() == 1)
    {
        // The expression consists of a single token. Evaluate it, leaving the
        // result in res. If OK update defined to the current serial.
        double temp;
        if (evaluate_token(rpn[0], temp, serial)) {
            res = temp;
            return true;
        } else {
            /// @todo Should set error here...
            error_info = names[dict[rpn[0]].id];
            return false;
        }
    }
    else for (unsigned int i = 0; i < rpn.size(); i++)
    {
        // The expression consists of a number of terms represented as tokens
        // in the RPN array. We must reduce this to a single value, evaluating
        // individual terms as we go

        // Get next token and process according to token type (category)
        tok = rpn[i];                   // next token
        a = dict[tok];                  // get attributes
        if (a.category == var || a.category == number)
        {
            st.push(tok);               // number or variable -- push onto stack
        }
        else if (a.category == opr)
        {
            cout << "Expression[" << lhs << "]::evaluate(" << serial << "): "
                << "Operator found" << endl;

            // Operators require two operands
            if (st.size() < 2) {
                error = Error::too_few_operands;
                return false;
            }

            // Get second operand (token) from stack
            tok2 = st.top();
            st.pop();

            // Evaluate it
            if (!evaluate_token(tok2, res2, serial)) {
                error = undefined_expression;
                error_info = names[dict[tok2].id];
                return false;
            }

            // Get first operand (token) from stack
            tok1 = st.top();
            st.pop();

            // Evaluate it
            if (!evaluate_token(tok1, res1, serial)) {
                error = undefined_expression;
                error_info = names[dict[tok1].id];
                return false;
            }

            // Combine the operands...
            cout << "Expression[" << lhs << "]::evaluate(" << serial << "): "
                << "Operands: " << res1 << ", " << res2 << endl;

            if (a.value.i == plus) {
                res0 = res1 + res2;
            } else if (a.value.i == minus) {
                res0 = res1 - res2;
            } else if (a.value.i == mult) {
                res0 = res1 * res2;
            } else if (a.value.i == divide) {
                if (res2 == 0) {
                    // Compiler might complain, but it's OK because division
                    // by res2 ~ 0 is not dangerous, and division by res2 == 0
                    // will be rejected...
                    error = Error::zero_divisor;
                    return false;
                } else {
                    res0 = res1 / res2;
                }
            }

            /* Diags only
            cout << "Expression[" << lhs << "]::evaluate(" << serial << "): "
                << "Operator produces temporary result = " << res0
                << " (stacked)" << endl;
            */

            // ... and push the result onto the stack.
            n = makeToken(res0);
            st.push(n);

            /// @note It's pretty inefficient to make a new token for every
            /// number but avoiding duplicates would be an unnecessary
            /// complication at this stage. Consider modifying makeToken(int)
            /// to avoid duplicates later.
        }
    }

    res = res0;

    cout << "Expression[" << lhs << "]::evaluate(" << serial << "): " << "var " << lhs << " = " << res << endl;

    return true;
}

int Expression::makeName(string s)
{
    unsigned int i;
    for (i = 0; i < names.size(); i++) {
        if (names[i] == s) {
            return i;
        }
    }
    names.push_back(s);
    return i;
}

int Expression::makeToken(double num)
{
    /** @todo (David#9#): Avoid putting number tokens in dictionary
     * This puts a new entry in the dictionary every time a number is used,
     * which is messy and inefficient. However, we do need to store the Attribs
     * somewhere, and it doesn't seem to be a very good idea to look for a match
     * every time we want to store a number. On the other hand I don't think
     * we should have to do this for storing the result of an evaluation since
     * that's a final value.
     */
    Attribs a;
    a.category = number;
    a.value.d = num;
    a.id = -1;
    int n = dict.size();
    dict[n] = a;
    return n;
}

int Expression::makeToken(string s)
{
    int ix = makeName(s);
    unsigned int i;
    for (i = 0; i < dict.size(); i++) {
        if (dict[i].category == var && dict[i].id == ix) {
            return i;
        }
    }

    Attribs a;
    a.category = var;
    a.value.i = 0;
    a.id = ix;

    dict[i] = a;

    return i;
}

void Expression::reversePolish()
{
    stack<int> st;
    int tok1, tok2;
    Attribs a1, a2;
    Category cat1;
    int prec1, prec2;

    for (unsigned int i = 0; i < tokens.size(); i++) {

        tok1 = tokens[i];
        a1 = dict[tok1];
        //val1 = a1.value;
        cat1 = a1.category;

        if (cat1 == opr) {
            prec1 = operators[a1.value.i].prec;
        }

        if (cat1 == var || cat1 == number)
        {
            rpn.push_back(tok1);
        }
        else if (cat1 == opr)
        {
            if (a1.value.i == lparen)
            {
                st.push(tok1);
            }
            else if (a1.value.i == rparen)
            {
                tok2 = -1;
                while (st.size() > 0)
                {
                    tok2 = st.top();
                    st.pop();
                    if (dict[tok2].value.i == lparen)
                    {
                        break;
                    }
                    else
                    {
                        rpn.push_back(tok2);
                    }
                }
                if (dict[tok2].value.i != lparen)
                {
                    cout << "Expression::reversePolish(): Unmatched rparen" << endl;
                    error = unmatched_rparen;
                    return;
                }
            }
            else
            {
                while (st.size() > 0)
                {
                    tok2 = st.top();
                    a2 = dict[tok2];
                    wxASSERT(a2.category == opr);
                    prec2 = operators[a2.value.i].prec;

                    // We haven't accounted for associativity, so we simply assume
                    // all operators are left-associative
                    if (prec1 > prec2) {
                        break;
                    }

                    st.pop();
                    rpn.push_back(tok2);
                }

                st.push(tok1);
            }
        }
        else
        {
            if (st.size() < 2) {
                cout << "Expression::reversePolish(): Too few operands" << endl;
                error = Error::too_few_operands;
                return;
            }
        }
    }

    while (st.size() > 0)
    {
        tok2 = st.top();
        if (dict[tok2].value.i == lparen)
        {
            cout << "Expression::reversePolish(): Unmatched lparen" << endl;
            error = unmatched_lparen;
            return;
        }
        else
        {
            rpn.push_back(tok2);
            st.pop();
        }
    }
}

unordered_map<string, Expression*> &Expression::getDefinitions()
{
    return definitions;
}

unordered_map<string, Expression*> &Expression::getProbes()
{
    return probes;
}

unordered_map<string, Expression*> &Expression::getSpecials()
{
    return specials;
}

unordered_map<int,Expression::Attribs> &Expression::getDictionary()
{
    return dict;
}

vector<string> &Expression::getFreeVariables()
{
    freeVars.clear();
    for (auto it : dict) {
        Attribs a = it.second;
        if (a.category == Category::var) {
            string name = getName(a.id);
            if (find(name) == nullptr) {
                freeVars.push_back(name);
            }
        }
    }
    return freeVars;
}

bool Expression::haveFreeVariables()
{
    for (auto it : dict) {
        Attribs a = it.second;
        if (a.category == Category::var) {
            string name = getName(a.id);
            if (find(name) == nullptr) {
                return true;
            }
        }
    }
    return false;
}

string &Expression::getName(int id)
{
    return names.at(id);
}

// Stores the term in the dictionary and returns the dictionary index or -1 if
// there's an error (currently this just means an invalid operator).
int Expression::term(string s, Category cat)
{
    //assert(sector == nullptr);

    union {
        int i;
        double d;
    } id;
    id.i = -1;
    int dashed = 0;

    // Validate and evaluate

    switch(cat) {

    case opr:
        // See if s is listed as an operator
        for (unsigned int i = 0; i < Optype::__count; i++) {
            if (operators[i].name == s) {
                id.i = i;
                break;
            }
        }
        if (id.i < 0) {
            error = invalid_operator;
            error_info = s;
            //cout << "Unrecognised operator " << s << endl;
            return -1;
        }
        break;

    case number:
        // Convert to number
        id.d = atof(s.c_str());   // (only positive integers handled at present)
        /// @todo Allow unary operator '-'. Currently we have to write '-1' as
        /// (0 - 1)
        break;

    case var:
        // Check whether the last character is '
        if (s.back() == '\'') {
            s.pop_back();
            dashed = -1;

        }
        // See if s is listed as a name
        for (unsigned int i = 0; i < names.size(); i++) {
            if (names[i] == s) {
                id.i = i;
            }
        }
        // If not, add it
        if (id.i == -1) {
            names.push_back(s);
            id.i = names.size() - 1;  // (first element is names[0])
        }
        break;
    }

    // Look up token in dictionary. We only add one instance of each variable
    // name, but numbers and operators are stored anyway as they are effectively
    // anonymous. Operators could be optimised but it hardly seems worth it.
    if (cat == var) {
        for (auto it : dict) {
            // Found, return index
            if (it.second.category == var && it.second.id == id.i && it.second.value.i == dashed) {
                return it.first;
            }
        }
    }
    // Not found, add to dictionary
    Attribs a;
    if (cat == var) {
        a.id = id.i;      // id indexes array of names
        // The value field used to contain -1 to indicate that the expression
        // was undefined, but this info is now held in the target object itself.
        // Instead, we now use it to indicate that a historical value is
        // required, -1 indicating the previous value, -2 the value before
        // that, and so on. Initially we will only go back to the previous
        // version. We will change this is it turns out to be useful.
        a.value.i = dashed;
    } else if (cat == opr) {
        a.id = -1;      // non-vars stand for themselves and do not need a name
        a.value.i = id.i;   // the id is its own value (operator value indexes operators array)
    } else /* cat == number */ {
        a.id = -1;      // non-vars stand for themselves and do not need a name
        a.value.d = id.d;   // the id is its own value (operator value indexes operators array)
    }
    a.category = cat;
    int n = dict.size();
    dict[n] = a;
    return n;
}

/// @todo (david#3#): Improve parsing mechanism e.g. don't treat arbirary
/// combinations of characters as operators, allow expression to start with
/// minus sign). Consider adding unary operators and functions.

int Expression::tokenise(string s)
{
    // assert(sector == nullptr);

    State state = sp;   // notional whitespace at start
    stringstream tok;
    char c;

    for (unsigned int i = 0; i <= s.length(); i++) {

        // Prevent access beyond end of string
        c = (i == s.length() ? char(0) : s[i]);

        // Uncomment if needed for debugging:
        // cout << i << ": c = " << c << " tok = " << tok.str() << " state " << state << endl;

        switch(state) {

        case sp:
            if (isdigit(c)) {
                tok << c;
                state = num;
            } else if (ispunct(c)) {
                tok << c;
                state = op;
            } else if (isalpha(c)) {
                tok << c;
                state = ident;
            }
            break;

        case ident:
            if (isalnum(c) || c == '\'' || c == '~') {
                tok << c;
            } else {
                tokens.push_back(Expression::term(tok.str(),var));
                tok.str("");    // empty tok
                if (ispunct(c)) {
                    tok << c;
                    state = op;
                } else {
                    state = sp;
                }
            }
            break;

        case num:
            if (isdigit(c) || c == '.') {
                tok << c;
            } else {
                tokens.push_back(Expression::term(tok.str(),number));
                tok.str("");    // empty tok
                if (ispunct(c)) {
                    tok << c;
                    state = op;
                } else if (isalpha(c)) {
                    tok << c;
                    state = ident;
                } else {
                    state = sp;
                }
            }
            break;

        case op:
            if (ispunct(c)) {
                tok << c;
            } else {
                // Check opr is valid
                int op_tok = Expression::term(tok.str(),opr);
                if (op_tok < 0) {
                    return -1;
                }
                tokens.push_back(op_tok);
                tok.str("");    // empty tok
                if (isdigit(c)) {
                    tok << c;
                    state = num;
                } else if (isalpha(c)) {
                    tok << c;
                    state = ident;
                } else {
                    state = sp;
                }
            }
            break;
        }
    }
    return tokens.size();
}

