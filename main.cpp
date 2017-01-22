//
//  main.cpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 21/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Account_Vedanarayanan.hpp"
#include "StockAccount_Vedanarayanan.hpp"
#include "BankAccount_Vedanarayanan.hpp"
#include "Results_Vedanarayanan.hpp"

using namespace std;

int main()
{    
    int option;
    
    // 5 objects; one for each of the Result.txt file
    Results res1, res2, res3, res4, res5;
    
    // storing the 5 Result.txt files with random values in a data structure
    res1.get_data("Result_1.txt");
    res2.get_data("Result_2.txt");
    res3.get_data("Result_3.txt");
    res4.get_data("Result_4.txt");
    res5.get_data("Result_5.txt");
    
    // object of class 'StockAccount'
    StockAccount stockAcc;
    
    // object of class 'BankAccount'
    BankAccount bankAcc;
    
    // create new files or open if already created
    stockAcc.openfiles();
    
    // when program starts, information in current_portfolio.txt is copied to the double linked list
    stockAcc.from_portfolio_to_DLL();
    
    /* when program starts, the total portfolio value and cash balance of both stock account and bank account are 
       updated with latest values by reading from portfolioValue_cashBalance.txt */
    stockAcc.read_cash_balance();
    bankAcc.read_cash_balance();
    
    cout << "Welcome to Account Management System!";
    do
    {
        cout << "\nPlease select an account to access:";
        cout << "\n1. Stock Portfolio Account";
        cout << "\n2. Bank Account";
        cout << "\n3. Exit\n";
        cin >> option;
        switch (option)
        {
            case 1:
            {
                    // print stock account menu if user chose option 1
                    stockAcc.stock_menu(res1, res2, res3, res4, res5);
                    break;
            }
            case 2:
            {
                    // print bank account menu if user chose option 2
                    bankAcc.bank_menu();
                    break;
            }
            case 3:
            {
                    // when program exits, store the total portfolio value, cash balance, date and time in portfolio_history.txt
                    stockAcc.put_graph_values();
                    exit(0);
            }
            default:
            {
                    cout << "\nPlease select a valid option!\n";
            }
        }        
    }while(7);
    return 0;
}
