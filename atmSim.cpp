//////////////////////////////////////////////
//  15146508 - Gwatkin, Cai                 //
//  Assignment 1, Part 2                    //
//////////////////////////////////////////////
//  This program simulates a simple ATM     //
//  using account and transactional         //
//  data from text files.                   //
//////////////////////////////////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

const std::string ACCTFILE = "acct.txt";            // Account file path
const std::string TRANZFILE = "tranz.txt";          // Transaction file path
const unsigned int MAX_NUMBER_OF_ACCOUNTS = 100;    // Sets size of array of accounts to be created

// Stores linked list of all accounts
class Account
{
private:
    int _id;
    double _balance;
    unsigned int _numberOfTransactions;

public:
    Account();
    ~Account();
    int GetID();                                        // Returns the ID number of the account
    double GetBalance();                                // Returns the balance of the account
    unsigned int GetNumberOfTransactions();             // Returns the number of transactions
    void NewAccountData(int id, double balance);        // Sets values for account ID and balance
    void UpdateAccountData(double changeInBalance);     // Adds the change in balance (positive for deposit, negative for withdrawal) to the current balance and increments the number of transactions
};

// Account constructor
Account::Account()
{
    _id = -1;
    _balance = 0;
    _numberOfTransactions = 0;
}

// Account destructor
Account::~Account() { }

// Returns the ID number of the account
int Account::GetID()
{
    return _id;
}

// Returns the balance of the account
double Account::GetBalance()
{
    return _balance;
}

// Returns the number of transactions
unsigned int Account::GetNumberOfTransactions()
{
    return _numberOfTransactions;
}

// Sets new values for account ID and balance
void Account::NewAccountData(int id, double balance)
{
    _id = id;
    _balance = balance;
    _numberOfTransactions = 0;
}

// Adds the change in balance (positive for deposit, negative for withdrawal) to the current balance and increments the number of transactions
void Account::UpdateAccountData(double changeInBalance)
{
    _balance = _balance + changeInBalance;
    _numberOfTransactions++;
}

// Stores an array of accounts from data in a file and modifies the balance of those accounts from data in another file
class ATM
{
private:
    Account * _accounts;
    unsigned int _numberOfAccounts;

public:
    ATM(int numberOfAccounts);
    ~ATM();
    void PrintState();                                      // Displays the current state of all accounts
    bool IsAccount(int id);                                 // Returns true if there is an account with the inputted id
    void AddAccountsFromFile(std::ifstream &inputFile);     // Gets account information from ACCTFILE file and stores data in array of accounts
    void ProcessTransactions(std::ifstream &inputFile);     // Processes all legitimate transactions in TRANZFILE file and updates data in accounts
};

// ATM constructor
ATM::ATM(int numberOfAccounts)
{
    _accounts = new Account[numberOfAccounts];
}

// ATM destructor
ATM::~ATM() { }

// Displays the current state of all accounts
void ATM::PrintState()
{
    for (unsigned int i = 0; i < _numberOfAccounts; i++)
    {
        std::cout.width(7);  std::cout << std::left << "Acct#";
        std::cout.width(4);  std::cout << std::right << _accounts[i].GetID();
        std::cout.width(10); std::cout << std::right << "Bal:  ";
        std::cout.width(11); std::cout << std::right << std::fixed << std::setprecision(2) << _accounts[i].GetBalance();
        std::cout.width(19); std::cout << std::right << "Trans so far:  ";
        std::cout.width(2);  std::cout << std::right << _accounts[i].GetNumberOfTransactions() << std::endl;
    }
}

// Returns true if there is an account with the inputted ID
bool ATM::IsAccount(int id)
{
    for (unsigned int i = 0; i < _numberOfAccounts; i++)
    {
        if (_accounts[i].GetID() == id) return true;
    }
    return false;
}

// Gets account information from ACCTFILE file and stores data in array of accounts
void ATM::AddAccountsFromFile(std::ifstream &inputFile)
{
    _numberOfAccounts = 0;
    while (!inputFile.eof() && _numberOfAccounts < MAX_NUMBER_OF_ACCOUNTS)
    {
        int id;
        double balance;

        inputFile >> id >> balance;

        if (id > 0 && !IsAccount(id))
        {
            _accounts[_numberOfAccounts].NewAccountData(id, balance);
            _numberOfAccounts++;
        }
    }

    std::cout << "Initial data as in file \"" << ACCTFILE << "\"" << std::endl;
    std::cout << _numberOfAccounts << " correct accounts read from file." << std::endl << std::endl;
}

// Processes all legitimate transactions in TRANZFILE file and updates data in accounts
void ATM::ProcessTransactions(std::ifstream &inputFile)
{
    std::string ignoreFirstLine;
    getline(inputFile, ignoreFirstLine);

    while (!inputFile.eof())
    {
        int id = -1;
        char type = ' ';
        double amount = 0.0;

        inputFile >> id >> type >> amount;

        if (amount > 0.0)   // Transactions must be positive
        {
            for (unsigned int i = 0; i < _numberOfAccounts; i++)
            {
                if (_accounts[i].GetID() == id) // Find correct account ID
                {
                    if (type == 'W')        // Withdrawal
                    {
                        if (amount <= _accounts[i].GetBalance())    // Must have sufficient money in account
                        {
                            _accounts[i].UpdateAccountData(-amount);
                        }
                    }
                    else if (type == 'D')   // Deposit
                    {
                        _accounts[i].UpdateAccountData(amount);
                    }
                    break;
                }
            }
        }
    }

    std::cout << std::endl << "After processing data in file \"" << TRANZFILE << "\"" << std::endl << std::endl;
}

void PrintWelcome();    // Displays the information about the author of the program
void Continue();        // Programs waits for user to enter a character
void Finish();          // Programs waits for user to enter a character

int main()
{
    PrintWelcome();

    ATM *atm = new ATM(MAX_NUMBER_OF_ACCOUNTS);
    std::ifstream inputAccountsFile(ACCTFILE);
    std::ifstream inputTransactionsFile(TRANZFILE);

    if (!inputAccountsFile || !inputTransactionsFile)
    {
        std::cout << "Error: cannot open files" << std::endl;
        return 1;
    }

    atm->AddAccountsFromFile(inputAccountsFile);
    inputAccountsFile.close();

    atm->PrintState();
    Continue();

    atm->ProcessTransactions(inputTransactionsFile);
    inputTransactionsFile.close();

    atm->PrintState();
    Finish();

    return 0;
}

// Displays the information about the author of the program
void PrintWelcome()
{
    std::cout << "***********************" << std::endl;
    std::cout << "* Assignment 1 Part 2 *" << std::endl;
    std::cout << "* Gwatkin C. 15146508 *" << std::endl;
    std::cout << "* 159.234 OOP         *" << std::endl;
    std::cout << "***********************" << std::endl << std::endl;
}

// Programs waits for user to enter a character
void Continue()
{
    std::cout << std::endl << "Enter 'c' to continue..." << std::endl;
    std::cin.get();
    std::cin.ignore();
}

// Programs waits for user to enter a character
void Finish()
{
    std::cout << std::endl << "Enter 'f' to finish..." << std::endl;
    std::cin.get();
    std::cin.ignore();
}