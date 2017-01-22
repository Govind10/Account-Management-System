//
//  Account_Vedanarayanan.hpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 21/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#ifndef Account_Vedanarayanan_hpp
#define Account_Vedanarayanan_hpp

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Account
{
public:
    double CASH_BALANCE;
    double TOTAL_PORTFOLIO_VALUE;
    void put_graph_values();
    void write_bank_transaction_history(string, double);
    void write_cash_balance();
    void read_cash_balance();
    void openfiles();
};

#endif /* Account_Vedanarayanan_hpp */
