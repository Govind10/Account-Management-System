//
//  StockAccount_Vedanarayanan.cpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 21/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#include "StockAccount_Vedanarayanan.hpp"
#include "Results_Vedanarayanan.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <time.h>
#include <iomanip>
#pragma comment(lib, "libmat.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmex.lib")
#pragma comment(lib, "libeng.lib")
#include<engine.h>
#include<yvals.h>
#if(_MSC_VER>=1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
using namespace std;

// constructor that initializes head and tail to NULL
StockAccount::StockAccount():head(NULL), tail(NULL)
{
    
}

// stock account main menu
void StockAccount::stock_menu(Results res1, Results res2, Results res3, Results res4, Results res5)
{
    int i = 5, option;
    
    /* the total portfolio value and cash balance of both stock account is
       updated with latest values by reading from portfolioValue_cashBalance.txt */
    read_cash_balance();
    
    // selecting a random file from the 5 files; object 'res' with point to a randomly chosen file
//--------------------------------->>>>>>>> Results res = random_file_selector(res1, res2, res3, res4, res5);
    
    cout << "\nStock Portfolio Account";
    do
    {
        Results res = random_file_selector(res1, res2, res3, res4, res5);
        cout << "\nPlease select an option:";
        cout << "\n1. Display the prize for a stock symbol";
        cout << "\n2. Display the current portfolio";
        cout << "\n3. Buy shares";
        cout << "\n4. Sell shares";
        cout << "\n5. View a graph for the portfolio value";
        cout << "\n6. View transaction history";
        cout << "\n7. Return to previous menu\n";
        cin >> option;
        switch (option)
        {
            case 1:
            {
                // display the price of a stock if user chose option 1
                display_price(res);
                break;
            }
            case 2:
            {
                // display the current portfolio if user chose option 2
                read_current_portfolio();
                break;
            }
            case 3:
            {
                // buy shares if user chose option 3
                buy_stock(res);
                break;
            }
            case 4:
            {
                // sell shares if user chose option 4
                sell_stock(res);
                break;
            }
            case 5:
            {
                // print graph of portfolio value if user chose option 5
				plot_graph();
				break;
            }
            case 6:
            {
                // print the stock transaction history if user chose option 6
                read_transaction_history();
                break;
            }
            case 7:
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
    }while(i == 5);
}

// function that randomly selects one of the 5 files
Results StockAccount::random_file_selector(Results res1, Results res2, Results res3, Results res4, Results res5)
{
    srand((unsigned int)time(NULL));
    int random = rand() % 5 + 1;
    if (random == 1) return res1;
    else if (random == 2) return res2;
    else if (random == 3) return res3;
    else if (random == 4) return res4;
    else return res5;
}

// function to display price of a stock
void StockAccount::display_price(Results res)
{
    string symbol;
    int flag = 0;
    cout << "\nPlease enter the stock symbol: ";
    cin >> symbol;
    for (int i = 0; i < 49 && flag == 0; i++) // iterate through each of the 49 stock symbols
    {
        if (symbol.compare(res.symbol[i]) == 0) // check if symbol in file equal to symbol entered by user
        {
            cout << "Company Symbol" << setw(17) << "Price per share" << endl;
            cout << setw(9) << res.symbol[i] << setw(13) << "$" << res.price[i] << endl;
            flag = 1;
        }
    }
    if (flag == 0) cout << "\nSymbol cannot be found!\n";
}

// function to add a new node to the doubly linked list
void StockAccount::add_node_to_DLL(Node *cur)
{
    if (head == NULL && tail == NULL) // for first node
    {
        cur->prev = NULL;
        head = cur;
        tail = cur;
    }
    else
    {
        cur->prev = tail;
        tail->next = cur;
        tail = cur;
    }
}

// function to search the doubly linked list to find whether or not a node was previouly added
int StockAccount::search_DLL(Node *cur)
{
    string symbol = cur->symbol;
    if (head != NULL && tail != NULL) // check if there is atleast one node
    {
        Node *temp = head;
        while (temp != NULL) // iterate through all nodes
        {
            if (temp->symbol.compare(symbol) == 0) // if the node is already present, just add number of shares to that
            {
                temp->numOfShares += cur->numOfShares;
                return 1;
            }
            temp = temp->next;
        }
        delete temp;
    }
    return 0;
}

// function to write the stock transaction history into stock_transaction_history.txt
void StockAccount::write_transaction_history(string buyOrSell, string symbol, int numOfShares, double price, double totalPrice)
{
    // get the current time and convert time to local time
    time_t currentTime;
    struct tm *localTime;
    time( &currentTime ); // get the current time
    localTime = localtime( &currentTime ); // convert the current time to the local time
    int hour = localTime->tm_hour;
    int min = localTime->tm_min;
    int sec = localTime->tm_sec;
    
    // store the event, symbol, number of shares, price of each share and the total price in stock_transaction_history.txt
    ofstream put("stock_transaction_history.txt", ios::app);
    put << " " << buyOrSell << "\t\t\t" << symbol << "\t\t\t" << numOfShares << "\t\t " << price << "\t\t " << totalPrice << "\t   " << hour << ":" << min << ":" << sec << endl;
    put.close();
}

// function to read the stock transaction history from stock_transaction_history.txt
void StockAccount::read_transaction_history()
{
    string event, symbol, time;
    int numOfShares;
    double price, totalPrice;
    ifstream get("stock_transaction_history.txt", ios::in);
    get >> event >> symbol >> numOfShares >> price >> totalPrice >> time;
    if (!get.eof())
    {
        cout << "Event\t" << "Company Symbol\t" << " Number\t" << "  Price per share\t" << "Total value\t" << "    Time\n";
        while (!get.eof())
        {
            cout << setfill(' ') << setw(4) << event << setfill(' ') << setw(12) << symbol << setfill(' ') << setw(12) << numOfShares;
            cout << fixed << setprecision(4);
            cout << setfill(' ') << setw(10) << right << "$" << price;
            cout << setfill(' ') << setw(8) << right << "$" << totalPrice << setfill(' ') << setw(12) << time << endl;
            get >> event >> symbol >> numOfShares >> price >> totalPrice >> time;
        }
        get.close();
    }
    else cout << "\nStock transaction history is empty!\n";
}

// function to copy information from current_portfolio.txt to the doubly linked list
void StockAccount::from_portfolio_to_DLL()
{
    string symbol;
    int numOfShares, flag = 0;
    double price, totalPrice;
    ifstream get("current_portfolio.txt", ios::in);
    get >> symbol >> numOfShares >> price >> totalPrice;
    while (!get.eof())
    {
        Node *cur = new Node;
        cur->symbol = symbol;
        cur->numOfShares = numOfShares;
        add_node_to_DLL(cur);
        get >> symbol >> numOfShares >> price >> totalPrice;
    }
    get.close();
}

// function to store the current portfolio in current_portfolio.txt
void StockAccount::write_current_portfolio(Results res)
{
    TOTAL_PORTFOLIO_VALUE = CASH_BALANCE;
    Node *temp = head;
    ofstream put("current_portfolio.txt", ios::trunc);
    while (temp != NULL)
    {
        put << "    " << temp->symbol << "\t\t\t\t" << temp->numOfShares << "\t\t\t\t";
        int flag = 0;
        for (int i = 0; i < 49 && flag == 0; i++) // iterate through each of the 49 stock symbols
        {
            if (temp->symbol.compare(res.symbol[i]) == 0)
            {
                double totalPrice = res.price[i] * temp->numOfShares;
                put << res.price[i] << "\t\t\t\t" << totalPrice << endl;
                TOTAL_PORTFOLIO_VALUE += totalPrice;
                flag = 1;
            }
        }
        temp = temp->next;
    }
    put.close();
}

// function to read the current portfolio from current_portfolio.txt
void StockAccount::read_current_portfolio()
{
    string symbol;
    int numOfShares;
    double price, totalPrice;
   /* cout << "\nCurrent Portfolio:\n";
    cout << "Cash Balance: $" << CASH_BALANCE <<endl; */
    if (head != NULL)
    {
        cout << "\nCurrent Portfolio:\n";
        cout << "Cash Balance: $" << CASH_BALANCE <<endl;
        cout << "Company Symbol\t" << " Number of Shares\t" << " Price per share\t" << " Total value\n";
        ifstream get("current_portfolio.txt", ios::in);
        get >> symbol >> numOfShares >> price >> totalPrice;
        while (!get.eof())
        {
            cout << setfill(' ') << setw(8) << symbol << setfill(' ') << setw(16) << numOfShares;
            cout << fixed << setprecision(4);
            cout << setfill(' ') << setw(18) << right << "$" << price;
            cout << setfill(' ') << setw(9) << right << "$" << totalPrice << endl;
            get >> symbol >> numOfShares >> price >> totalPrice;
        }
        get.close();
        cout << "Total Portfolio Value: $" << TOTAL_PORTFOLIO_VALUE <<endl;
    }
    else cout << "\nPortfolio is empty!\n";
   // cout << "Total Portfolio Value: $" << TOTAL_PORTFOLIO_VALUE <<endl;
}

// function to keep the doubly linked list sorted at all times using bubble sort
void StockAccount::bSort(Results res)
{
    if (head == NULL) return;
    if (head->next == NULL) return;
    Node *temp, *dummy = new Node;
    int swap = 1;
    double tP1, tP2;
    while (swap)
    {
        swap = 0;
        temp = head;
        while (temp->next != NULL)
        {
            int flag = 0;
            for (int i = 0; i < 49 && flag == 0; i++) // iterate through each of the 49 stock symbols
            {
                if (temp->symbol.compare(res.symbol[i]) == 0)
                {
                    tP1 = temp->numOfShares * res.price[i];
                    flag = 1;
                }
            }
            flag = 0;
            for (int i = 0; i < 49 && flag == 0; i++) // iterate through each of the 49 stock symbols
            {
                if (temp->next->symbol.compare(res.symbol[i]) == 0)
                {
                    tP2 = temp->next->numOfShares * res.price[i];
                    flag = 1;
                }
            }
            if (tP1 < tP2) // if total prices of two nodes are in ascending order, swap
            {
                swap = 1;
                dummy->symbol = temp->symbol;
                temp->symbol = temp->next->symbol;
                temp->next->symbol = dummy->symbol;
                dummy->numOfShares = temp->numOfShares;
                temp->numOfShares = temp->next->numOfShares;
                temp->next->numOfShares = dummy->numOfShares;
            }
            temp = temp->next;
        }
    }
}

// function to enable user to buy stock
void StockAccount::buy_stock(Results res)
{
    int flag = 0;
    double max;
    Node *cur = new Node; // create new node
    
    // get input from user
    cout << "\nPlease enter the stock symbol you wish to purchase: ";
    cin >> cur->symbol;
    cout << "\nPlease enter the number of shares you want to buy: ";
    cin >> cur->numOfShares;
    cout << "\nPlease enter the maximum amount you are willing to pay per share: $";
    cin >> max;
    
    // print error if cash balance is lower than what the user is wiling to pay
    if (max > CASH_BALANCE) cout << "\nTransaction failed! You cannot use more money than you have!\n";
    else
    {
        for (int i = 0; i < 49 && flag == 0; i++) // iterate through each of the 49 stock symbols
        {
            if (cur->symbol.compare(res.symbol[i]) == 0) // check if symbol in file is equal to symbol entered by user
            {
                // print error if price of symbol is more than what the user is wiling to pay
                if (res.price[i] > max )
                {
                    cout << "\nTransaction failed! Cost per stock is more than what you are willing to pay!\n";
                    flag = 1;
                }
                
                // print error if user can't afford to buy so many shares
                else if ((CASH_BALANCE - (cur->numOfShares * res.price[i])) < 0)
                {
                    cout << "\nYou don't have sufficient cash balance to buy " << cur->numOfShares << " shares of " << cur->symbol << "!\n";
                    flag = 1;
                }
                
                // let the user buy shares
                else
                {
                    double totalPrice = cur->numOfShares * res.price[i]; // total price = number of shares * price per share
                    cout << "\nYou have purchased " << cur->numOfShares << " share(s) of " << cur->symbol << " at $" << res.price[i] << " each for a total of $" << totalPrice << ".\n";
                    CASH_BALANCE -= totalPrice;
                    
                    // write the transaction (of buying shares) in stock_transaction_history.txt file
                    write_transaction_history("Buy", cur->symbol, cur->numOfShares, res.price[i], totalPrice);
                    
                    // write the transaction (of withdrawing amount from bank account) in bank_transacion_history.txt file
                    write_bank_transaction_history("Withdrawal", totalPrice);
                    
                    int k = search_DLL(cur); // search whether the node is already present in the doubly linked list
                    if (k == 0) add_node_to_DLL(cur); // if not, add it to the doubly linked list
                    else delete cur; // if yes, don't add; just delete the pointer
                    
                    // bubble sort after each buy operation
                    bSort(res);
                    
                    // write the transaction made in current_portfolio.txt file
                    write_current_portfolio(res);
                    
                    flag = 1;
                }
            }
        }
        if (flag == 0) cout << "\nThe stock is not available!\n";
    }
}

// function to enable user to sell stock
void StockAccount::sell_stock(Results res)
{
    string symbol;
    int numOfShares;
    double min;
    
    // get input from user
    cout << "\nPlease enter the ticker symbol of the stock you want to sell: ";
    cin >> symbol;
    cout << "\nPlease enter the number of shares you want to sell: ";
    cin >> numOfShares;
    cout << "\nPlease enter the minimum amount you want to sell each share of the stock for: $";
    cin >> min;
    int flag = 0;
    double price;
    Node *temp = head; // start from head
    while (temp != NULL && flag == 0)
    {
        if (temp->symbol.compare(symbol) == 0) // check if the symbol entered by user is present in the doubly linked list
        {
            int flag1 = 0;
            for (int i = 0; i < 49 && flag1 == 0; i++) // iterate through each of the 49 stock symbols
            {
                if (temp->symbol.compare(res.symbol[i]) == 0)
                {
                    price = res.price[i];
                    flag1 = 1;
                }
            }
            
            // print error if actual price of a share is less than what the user is willing to pay
            if (price < min) cout << "\nTransaction failed! Price per share of the stock is lower than what you are willing to sell for.\n";
            
            // print error if user is trying to sell more number of shares than he has
            else if (temp->numOfShares < numOfShares) cout << "\nTransaction failed! There are insufficient shares of " << symbol << ".\n";
            
            // let the user sell shares
            else
            {
                double totalPrice = (numOfShares * price); // total price = number of shares * price per share
                CASH_BALANCE += totalPrice;
                temp->numOfShares -= numOfShares;
                
                // remove the node from doubly linked list if the number of shares equals zero
                if (temp->numOfShares == 0)
                {
                    if (head == tail) head = tail = NULL;
                    else if (temp == head)
                    {
                        head = head->next;
                        head->prev = NULL;
                    }
                    else if (temp == tail)
                    {
                        tail = tail->prev;
                        tail->next = NULL;
                    }
                    else
                    {
                        Node *temp1 = temp->prev;
                        Node *temp2 = temp->next;
                        temp2->prev = temp1;
                        temp1->next = temp2;
                    }
                }
                
                cout << "\nYou have sold " << numOfShares << " share(s) of " << symbol << " at $" << price << " each for a total of $" << totalPrice << ".\n";
                
                // write the transaction (of selling shares) in stock_transaction_history.txt file
                write_transaction_history("Sell", symbol, numOfShares, price, totalPrice);
                
                // write the transaction (of depositing amount from into account) in bank_transacion_history.txt file
                write_bank_transaction_history("Deposit", totalPrice);
                
                // bubble sort after each sell operation
                bSort(res);
                
                // write the transaction made in current_portfolio.txt file
                write_current_portfolio(res);
            }
            flag = 1;
        }
        temp = temp->next;
    }
    
    // print error if user is trying to sell a stock he/she doesn't have
    if (flag == 0) cout << "\nTransaction failed! You can't sell because you don't have shares of " << symbol << " at all!";
    cout << endl;
}

// function to plot graph
void StockAccount::plot_graph()
{
	double totalAmount, amount;
	int time1, n = 0;
	string date1;
    ifstream g("portfolio_history.txt", ios::in);
    g >> totalAmount >> amount >> date1 >> time1;
    while (!g.eof()
    {
        n++;
        g >> totalAmount >> amount >> date1 >> time1;
    }
	ifstream get("portfolio_history.txt", ios::in);
	get >> totalAmount >> amount >> date1 >> time1;
	if (!get.eof())
	{
		Engine *ep;
		ep = engOpen(NULL);
		if (ep == NULL)
		{
			cout << "\nError";
			exit(0);
		}
		double x[100];
		double y[100];
		int i = 0;
		while (!get.eof())
		{
			x[i] = time1;
			y[i] = totalAmount;
			get >> totalAmount >> amount >> date1 >> time1;
			i++;
		}
		get.close();
		mxArray* m_X;
		mxArray* m_Y;
		m_X = mxCreateDoubleMatrix(1, n, mxREAL);
		m_Y = mxCreateDoubleMatrix(1, n, mxREAL);
		memcpy((void*)mxGetPr(m_X), (void*)x, sizeof(double) * n);
		memcpy((void*)mxGetPr(m_Y), (void*)y, sizeof(double) * n);
		engPutVariable(ep, "x", m_X);
		engPutVariable(ep, "y", m_Y);
		engEvalString(ep, "plot(x,y);");
	}
	else cout << "\nNo portfolio history present to plot a graph!\n";
}