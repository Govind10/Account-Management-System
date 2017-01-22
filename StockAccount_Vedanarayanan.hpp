//
//  StockAccount_Vedanarayanan.hpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 21/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#ifndef StockAccount_Vedanarayanan_hpp
#define StockAccount_Vedanarayanan_hpp

#include "Account_Vedanarayanan.hpp"
#include "Results_Vedanarayanan.hpp"
#include "Node_Vedanarayanan.h"
#include <string>
#include <stdio.h>

class StockAccount: public Account
{
    //head and tail of each node
    Node *head;
    Node *tail;
public:
    // class member function prototypes
    StockAccount();
    void stock_menu(Results, Results, Results, Results, Results);
    Results random_file_selector(Results, Results, Results, Results, Results);
    void display_price(Results);
    void add_node_to_DLL(Node *);
    int search_DLL(Node *);
    void write_transaction_history(string, string, int, double, double);
    void read_transaction_history();
    void from_portfolio_to_DLL();
    void write_current_portfolio(Results);
    void read_current_portfolio();
    void bSort(Results);
    void buy_stock(Results);
    void sell_stock(Results);
	void plot_graph();
};

#endif /* StockAccount_Vedanarayanan_hpp */
