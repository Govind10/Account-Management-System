//
//  Results_Vedanarayanan.cpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 22/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#include "Results_Vedanarayanan.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// function to store information in file to data structure
void Results::get_data(string file)
{
    int i, j, k;
    i = j = k = 0;
    string s1, s2;
    double d;
    ifstream get(file, ios::in);
    while (!get.eof())
    {
        get >> s1 >> d >> s2;
        symbol[i++] = s1;
        price[j++] = d;
        date[k++] = s2;
    }
    get.close();
}