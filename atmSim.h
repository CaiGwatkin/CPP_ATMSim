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

void PrintWelcome();    // Displays the information about the author of the program
void Continue();        // Programs waits for user to enter a character
void Finish();          // Programs waits for user to enter a character

