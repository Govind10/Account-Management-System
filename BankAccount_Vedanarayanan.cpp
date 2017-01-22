//
//  BankAccount_Vedanarayanan.cpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 21/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#include "BankAccount_Vedanarayanan.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// stock account main menu
void BankAccount::bank_menu()
{
    /* the total portfolio value and cash balance of both stock account is
     updated with latest values by reading from portfolioValue_cashBalance.txt */
    read_cash_balance();
    int i = 3, option;
    cout << "\nBank Account";
    do
    {
        cout << "\nPlease select an option";
        cout << "\n1. View Account Balance";
        cout << "\n2. Deposit money";
        cout << "\n3. Withdraw money";
        cout << "\n4. Print out history";
        cout << "\n5. Return to previous menu\n";
        cin >> option;
        switch (option)
        {
            case 1:
            {
                // display bank balance if user chooses option 1
                view_balance();
                break;
            }
            case 2:
            {
                // deposit money into bank account if user chooses option 2
                deposit_money();
                break;
            }
            case 3:
            {
                // withdraw money from bank account if user chooses option 3
                withdraw_money();
                break;
            }
            case 4:
            {
                // display bank transaction history if user chooses option 4
                read_Btransaction_history();
                break;
            }
            case 5:
            {
                /* if user wants to return to previous menu, first update total portfolio value and cash balance
                 in portfolioValue_cashBalance.txt and then break from loop */
                write_cash_balance();
                i = 0;
                break;
            }
            default:
            {
                cout << "\nPlease select a valid option!";
            }
        }
    }while(i == 3);
}

// function to display current bank balance
void BankAccount::view_balance()
{
    cout << "\nYou have $" << CASH_BALANCE << " in your bank account.\n";
}

// function to deposit money into bank account
void BankAccount::deposit_money()
{
    double amount;
    cout << "\nPlease enter the amount you want to deposit: $";
    cin >> amount;
    CASH_BALANCE += amount; // add the amount user wants to deposit to the current cash balance
    TOTAL_PORTFOLIO_VALUE += amount; // also add the amount user wants to deposit to the total portfolio value
    cout << "\n$" << amount << " has been deposited to your bank account.\n";
    
    // write the transaction (of depositing amount into bank account) in bank_transacion_history.txt file
    write_bank_transaction_history("Deposit", amount);
}

// function to withdraw money from bank account
void BankAccount::withdraw_money()
{
    double amount;
    cout << "\nPlease enter the amount you want to withdraw: $";
    cin >> amount;
    
    // print error if user is tring to withdraw more money than he/she has
    if (amount > CASH_BALANCE) cout << "\nTransaction failed! You cannot withdraw more than what you have!\n";
    else
    {
        CASH_BALANCE -= amount; // subtract the amount user wants to deposit to the current cash balance
        TOTAL_PORTFOLIO_VALUE -= amount; // also subtract the amount user wants to deposit to the total portfolio value
        cout << "\n$" << amount << " has been withdrawn from your bank account.\n";
        
        // write the transaction (of withdrawing amount from bank account) in bank_transacion_history.txt file
        write_bank_transaction_history("Withdrawal", amount);
    }
}

// function to display bank transaction history
void BankAccount::read_Btransaction_history()
{
    string event, date;
    double amount, balance;
    ifstream get("bank_transaction_history.txt", ios::in);
    get >> event >> amount >> date >> balance;
    if (!get.eof())
    {
        cout << "  Event\t\t\t" << " Amount\t\t\t" << "Date\t\t\t" << "Balance\n";
        while (!get.eof())
        {
            cout << setfill(' ') << setw(4) << event;
            cout << fixed << setprecision(4);
            cout << setfill(' ') << setw(6) << "$" << amount << setfill(' ') << setw(14) << date << setfill(' ') << setw(8) << right << "$" << balance << endl;
            get >> event >> amount >> date >> balance;
        }
        get.close();
    }
    else cout << "\nBank transaction history is empty!\n";
}