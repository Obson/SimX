#include "transfer.h"

vector<Transfer*> Transfer::transfers;

vector<Transfer*> &Transfer::getTransfers()
{
    return transfers;
}

Transfer::Transfer(Sector *dest, Sector *src, string var, string descr, bool negate)
{
    m_dest = dest;
    m_src = src;
    m_var = var;
    m_descr = descr;
    m_negate = negate;

    expr = (Expression*)nullptr;
}

Transfer::~Transfer()
{
}

void Transfer::initAll()
{
    for (auto it: transfers) {
        it->init();
    }
}

void Transfer::init()
{
    m_src->clearBalances();
    m_dest->clearBalances();
}

void Transfer::clear()
{
    for (auto it : transfers) {
        delete it;
    }
    transfers.clear();
}

bool Transfer::execAll(int serial)
{
    for (auto it : transfers) {
        if (!it->exec(serial)) {
            return false;
        }
    }
    return true;
}

Transfer *Transfer::find(string s)
{
    for (auto it : transfers) {
        if (it->getVarName() == s) {
            return it;
        }
    }
    return nullptr;
}

Transfer *Transfer::create(string &dest, string &src, string &name, string &descr)
{
    Sector *to = Sector::find(dest);
    Sector *from = Sector::find(src);

    Transfer *tx = new Transfer(to, from, name, descr);
    transfers.push_back(tx);

    Expression::makeToken(name);

    return tx;
}

string Transfer::getSourceName()
{
    return m_src->getLongName();
}

string Transfer::getDestName()
{
    return m_dest->getLongName();
}

string Transfer::getSourceShortName()
{
    return m_src->getName();
}

string Transfer::getDestShortName()
{
    return m_dest->getName();
}

string Transfer::getSourceNameAlt()
{
    return (m_src->getDescription() + " (" + m_src->getName() + ")");
}

string Transfer::getDestNameAlt()
{
    return (m_dest->getDescription() + " (" + m_dest->getName() + ")");
}

Sector *Transfer::getSource()
{
    return m_src;
}

Sector *Transfer::getDest()
{
    return m_dest;
}

string Transfer::getVarName()
{
    return m_var;
}

string Transfer::getDescription()
{
    return m_descr;
}

bool Transfer::exec(int serial)
{
    if (expr == nullptr) {
        if ((expr = Expression::find(m_var)) == (Expression*)nullptr) {
            error = no_such_expr;
            return false;
        }
    }
    if (expr->evaluate(serial)) {
        // Diagnostics
        double amount = expr->value();
        if (m_negate) {
            amount = -amount;
        }
        m_src->debit(amount);
        m_dest->credit(amount);
        error = no_error;
        return true;
    } else {
        error = cannot_evaluate;
        return false;
    }
}
