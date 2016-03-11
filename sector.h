#ifndef SECTOR_H
#define SECTOR_H

#include <vector>
#include <cstdlib>  // strtol
#include <string>

#include "expression.h"

using namespace std;

class Sector
{
    public:

        static vector<Sector*> &getSectors();

        static Sector *create(string &name, string &descr);
        static bool exists(string &name);
        static Sector *find(string);
        static void clearBalances();

        static void clear();    // delete all sectors

        void setDescription(string &description);

        string getName();
        string getDescription();
        string getLongName();

        double getBalance();

        void debit(double amount);
        void credit(double amount);

    protected:

        Sector(string &name);
        virtual ~Sector();

    private:

        string m_name;
        string m_description;

        double balance;

        static vector<Sector*> sectors;
};

#endif // SECTOR_H
