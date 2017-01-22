//
//  Results_Vedanarayanan.hpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 22/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#ifndef Results_Vedanarayanan_hpp
#define Results_Vedanarayanan_hpp

#include <iostream>
#include <string>
using namespace std;

class Results
{
public:
    // class data members and member function prototype
    string symbol[50];
    double price[50];
    string date[50];
    void get_data(string);
};

#endif /* Results_Vedanarayanan_hpp */
