#ifndef TRANSFER_H
#define TRANSFER_H

#include <string>

#include "sector.h"
#include "expression.h"

class Transfer
{
    public:
        Transfer(Sector *dest, Sector *src, string var, string descr, bool negate = false);
        virtual ~Transfer();

        string getSourceName();
        string getDestName();
        string getSourceShortName();
        string getDestShortName();
        string getSourceNameAlt();
        string getDestNameAlt();

        string getVarName();
        string getDescription();

        Sector *getSource();
        Sector *getDest();

        static vector<Transfer*> &getTransfers();
        static Transfer *find(string);
        static void clear();
        static bool execAll(int serial);
        static void initAll();              // clear all balances
        void init();                        // clear balance


        static Transfer *create(string &dest, string &src, string &name, string &descr);

        bool exec(int serial);

        enum Error {
            no_error = 0,
            no_such_expr = 1,
            cannot_evaluate = 2
        };

        Error error;

    protected:

    private:

        string m_var, m_descr;
        Expression *expr;   // nullptr if not yet defined - retrieve using m_var
        Sector *m_dest;
        Sector *m_src;
        bool m_negate;

        static vector<Transfer*> transfers;


};

#endif // TRANSFER_H
