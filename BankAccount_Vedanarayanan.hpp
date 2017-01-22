//
//  BankAccount_Vedanarayanan.hpp
//  final_project
//
//  Created by Govindan Vedanarayanan on 21/11/16.
//  Copyright © 2016 Govindan Vedanarayanan. All rights reserved.
//

#ifndef BankAccount_Vedanarayanan_hpp
#define BankAccount_Vedanarayanan_hpp

#include "Account_Vedanarayanan.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class BankAccount: public Account
{
public:
    // class member function prototypes
    void bank_menu();
    void view_balance();
    void deposit_money();
    void withdraw_money();
    void read_Btransaction_history();
};

// structural design pattern: bridge
class TimeImp
{
public:
	TimeImp(int h, int m)
	{
		hour = h;
		min = m;
	}
	virtual void tell()
	{
		cout << "Current time is " << hour << min << endl;
	}
protected:
	int hour, min;
};

class CivilianTimeImp : public TimeImp
{
public:
	CivilianTimeImp(int h, int m, int amPM) : TimeImp(h, m)
	{
		if (amPM) strcpy(thisOrThat, " PM");
		else strcpy(thisOrThat, " AM");
	}
	void tell()
	{
		cout << "You exited at " << hour << ":" << min << thisOrThat << endl;
	}
protected:
	char thisOrThat[4];
};

class Time
{
public:
	Time() {}
	Time(int h, int m)
	{
		imp = new TimeImp(h, m);
	}
	virtual void tell()
	{
		imp->tell();
	}
protected:
	TimeImp *imp;
};

class CivilianTime : public Time
{
public:
	CivilianTime(int h, int m, int amPM)
	{
		imp = new CivilianTimeImp(h, m, amPM);
	}
};

#endif /* BankAccount_Vedanarayanan_hpp */
