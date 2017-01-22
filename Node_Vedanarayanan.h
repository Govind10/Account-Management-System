//
//  Node_Vedanarayanan.h
//  final_project
//
//  Created by Govindan Vedanarayanan on 22/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#ifndef Node_Vedanarayanan_h
#define Node_Vedanarayanan_h

#include <iostream>
using namespace std;
#include <string>
class Node
{
    friend class StockAccount;
public:
    // constructor to initialize any new node to point to NULL
    Node()
    {
        this->next = NULL;
    }
private:
    // each node will contain the stock symbol and the number of shares
    string symbol;
    int numOfShares;
    Node *next; // to point to the previous node
    Node *prev; // to point to the next node
};


#endif /* Node_Vedanarayanan_h */
