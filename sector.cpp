#include "sector.h"

vector<Sector*> Sector::sectors;

Sector *Sector::create(string &name, string &descr)
{
    Sector *sector = new Sector(name);
    sector->setDescription(descr);
    sectors.push_back(sector);

    new Expression(name, sector); // (adds itself to definitions)

    return sector;
}

bool Sector::exists(string &name)
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

Sector::Sector(string &name)
{
    balance = 0;
    m_name = name;
    m_description = "";
}

Sector::~Sector()
{
}

vector<Sector*> &Sector::getSectors()
{
    return sectors;
}

void Sector::clearBalances()
{
    for (auto it : sectors) {
        it->balance = 0;
    }
}

void Sector::clear()
{
    for (auto it : sectors) {
        delete it;
    }
    sectors.clear();
}

Sector *Sector::find(string name)
{
    for (auto it : sectors) {
        if (it->getName() == name) {
            return it;
        }
    }

    return nullptr;
}

void Sector::setDescription(string &description)
{
    m_description = description;
}

string Sector::getName()
{
    return m_name;
}

string Sector::getDescription()
{
    return m_description;
}

string Sector::getLongName()
{
    return (m_name + "\t" + m_description);
}

void Sector::debit(double amt)
{
    balance -= amt;
}

void Sector::credit(double amt)
{
    balance += amt;
}

double Sector::getBalance()
{
    return balance;
}
