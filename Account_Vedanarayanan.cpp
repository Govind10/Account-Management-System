//
//  Account_Vedanarayanan.cpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 21/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#include "BankAccount_Vedanarayanan.hpp"
#include "Account_Vedanarayanan.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

void Account::put_graph_values()
{
    // read the latest values of total portfolio value and cash balnce from portfolioValue_cashBalance.txt
    ifstream get("portfolioValue_cashBalance.txt", ios::in);
    double totalAmount, amount;
    get >> totalAmount >> amount;
    
    // get the current time and convert time to local time
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime); // get the current time
    localTime = localtime(&currentTime); // convert the current time to the local time
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;
    int hour = localTime->tm_hour;
    int min = localTime->tm_min;
    int sec = localTime->tm_sec;
    
    // store the total portfolio value, cash balance, date and time in portfolio_history.txt
    ofstream put("portfolio_history.txt", ios::app);
    put << totalAmount << "\t\t" << amount << "\t\t" <<  month << "/" << day << "/" << year << "\t\t" << hour << min << endl;
    put.close();

	// thank you note while exiting
	cout << "\nThank you for using your Accounts!\n";
	Time *timeone;
	int amPM;
	if (hour > 12 && hour < 23) amPM = 1;
	else amPM = 0;
	timeone = new CivilianTime(hour, min, amPM);
	timeone->tell();
	cout << endl;
}

void Account::write_bank_transaction_history(string withOrDep, double amount)
{
    // get the current time and convert time to local time
    time_t currentTime;
    struct tm *localTime;
    time( &currentTime ); // get the current time
    localTime = localtime( &currentTime ); // convert the current time to the local time
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;
    
    // store the event, amount withdrawn/deposited, date and cash balance in bank_transaction_history.txt
    ofstream put("bank_transaction_history.txt", ios::app);
    put << withOrDep << "\t" << amount << "\t" <<  month << "/" << day << "/" << year << "\t" << CASH_BALANCE << endl;
    put.close();
}

void Account::write_cash_balance()
{
    // write the values of total portfolio value and cash balance in portfolioValue_cashBalance.txt
    ofstream put("portfolioValue_cashBalance.txt", ios::trunc);
    put << TOTAL_PORTFOLIO_VALUE << "\t\t" << CASH_BALANCE;
    put.close();
}

void Account::read_cash_balance()
{
    // read the values of total portfolio value and cash balance from portfolioValue_cashBalance.txt
    double totalAmount, amount;
    ifstream get("portfolioValue_cashBalance.txt", ios::in);
    get >> totalAmount >> amount;
    TOTAL_PORTFOLIO_VALUE = totalAmount;
    CASH_BALANCE = amount;
    get.close();
}

void Account::openfiles()
{
    ofstream put1("current_portfolio.txt", ios::app);
    put1.close();
    ofstream put2("stock_transaction_history.txt", ios::app);
    put2.close();
    ofstream put3("bank_transaction_history.txt", ios::app);
    put3.close();
    ofstream put4("portfolioValue_cashBalance.txt", ios::app);
    put4.close();
    ofstream put5("portfolio_history.txt", ios::app);
	put5.close();
    
    string event1, symbol, time;
    int numOfShares;
    double price, totalPrice;
    ifstream get1("stock_transaction_history.txt", ios::in);
    get1 >> event1 >> symbol >> numOfShares >> price >> totalPrice >> time;
    
    string event2, date;
    double amount, balance;
    ifstream get2("bank_transaction_history.txt", ios::in);
    get2 >> event2 >> amount >> date >> balance;
    if (get1.eof() && get2.eof())
    {
        TOTAL_PORTFOLIO_VALUE = 10000;
        CASH_BALANCE = 10000;
        write_cash_balance();
    }
}