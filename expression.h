#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>      // strtol
#include <sstream>      // stringstream
#include <string>

using namespace std;

class SimXFrame;
class Sector;

/// @todo (david#5#) Add other special built-in functions and (possibly) constraints.
class Expression
{
    public:

        enum SpecialType {
            sp_time = 0         ///< only one type at present, may add more later
        };

        enum ExpressionType {
            exp_normal = 0,
            exp_probe = 1       ///< to differentiate from normal Expression
        };

        Expression(string &lhs, string &exp, ExpressionType t = exp_normal, double init = 0);
        Expression(string &lhs, Sector *sect, double init = 0);
        Expression(string &lhs, SpecialType t);

        virtual ~Expression();

        static Expression *find(string);
        static void replace(string, Expression*);
        static void clearAll();
        static void revertAll();
        static bool remove(string);

        void setValue(double);  ///< for parametric values only (otherwise ignored)

        enum Category{
            var,                ///< value -> expr if assigned, -1 if not
            number,             ///< value is integer constant
            opr                 ///< value -> operator
        };

        struct Attribs {
            Category category;
            int id;
            union {
                int i;        ///< use when category is var or opr
                double d;     ///< use when category is number
            } value;
        };

        static unordered_map<string, Expression*>   &getDefinitions();
        static unordered_map<string, Expression*>   &getProbes();
        static unordered_map<string, Expression*>   &getSpecials();
        static unordered_map<int,Attribs>           &getDictionary();
        static vector<string>                       &getFreeVariables();
        static string &getName(int id);;

        static int makeToken(double num);
        static int makeToken(string s);
        static bool haveFreeVariables();

        bool isSectorBalance();
        bool isSpecial();
        bool isParameter();
        bool hasPreviousValue();
        bool evaluate(int serial);          // evaluate this expression (false if unsuccessful)

        Sector *getSector();                // sector balances only

        double value();                     // must check evaluated before calling
        double previousValue(int serial);
        double getDefault();                // parametric expressions only

        string error_string();
        string getRHS();      ///< returns RHS exactly as supplied to constructor

        enum Error {
            none                    = 0,    // last operation succeeded
            no_tokens               = 1,    // should never happen
            invalid_operator        = 2,    // not a recognisable operator string
            too_few_operands        = 3,    //
            unmatched_rparen        = 4,
            unmatched_lparen        = 5,
            undefined_expression    = 6,    // fails to evaluate
            incomplete_expression   = 7,    // referent fails to evaluate
            zero_divisor            = 8     // divide by zero
        } error;

        int term(string s, Category cat);

    protected:

        static void initialise();
        static int makeName(string s);

        bool evaluate_token(int tok, double &res, int serial);
        int tokenise(string s);
        void reversePolish();
        void revert(double init = 0);

    private:

        double res;             // LHS if already evaluated
        double prev;            // LHS on previous cycle
        int defined;            // false until successfully evaluated
        double dflt;            // default value if parametric

        vector<int> tokens;     // original list of tokens for RHS
        vector<int> rpn;        // expression tokens arranged in RPN order
        string error_info;      // e.g. name of undefined expression
        string orig;            // original unparsed expression (RHS onnly)
        string lhs;             // logically redundant, but useful for diagnostics

        void _in(string fn);
        void _out();
        void diags(string);

        /// @warning I tried using sector = nullptr to flag the (usual) case where
        /// the expression doesn't represent a sector balance, but the value was
        /// (sometimes?) returned as 0xff00000000, which would give the value
        /// false when compared against nullptr. There may be a correct procedure
        /// that wouldn't give rise to this apparent anomaly, but life's too
        /// short to waste any more time on it. Instead the bool is_sector_bal
        /// will be used to indicate unambiguously and (I hope) reliably, whether
        /// the expression represents a sector balance or not. When is_sector_bal
        /// is false, the value of sector is undefined and immaterial.

        Sector *sector;         //
        bool is_sector_bal;     //
        SpecialType special_type;
        bool is_special;        // i.e. has built-in function (bif)
        bool is_parametric = false;

        enum State {
            sp      = 0,
            ident   = 1,
            num     = 2,
            op      = 3,
            paren   = 4
        };

        enum Optype {
            nullop = 0,
            plus,
            minus,
            mult,
            divide,
            lparen,
            rparen,
            __count
        };

        struct OpDesc {
            string name;
            int prec;
        };

        static bool initialised;

        static unordered_map<int,Expression::Attribs> dict;
        static unordered_map<string, Expression*> definitions;
        static unordered_map<string, Expression*> probes;
        static unordered_map<string, Expression*> specials;
        static vector<string> names;
        static vector<string> freeVars;
        static OpDesc *operators;

        static int level;
};

#endif // EXPRESSION_H
