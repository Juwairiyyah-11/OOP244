/* Citation and Sources
-----------------------------------------------------------
Workshop #4
Module: Member Operators and Helper Functions
Filename: Account.h
-----------------------------------------------------------
Author: Juwairiyyah Ahmed
Student number: 173801234
Email: jahmed64@myseneca.ca
Subject: OOP244NEE
-----------------------------------------------------------
Revision History
------- --------- ------------------------------------------
Version Date      Reason
V1    2025/6/13  Completing code
V2    2025/6/13  Debugged
V3    2025/6/13  Ready for submission
-----------------------------------------------------------
Summary of Changes / Additions:

File Name	          What Was Added / Modified	                                                            Source
Account.cpp	          Type fixes for C4267 warnings: replaced int len = strlen(accountHolderName);
                      with size_t len = strlen(accountHolderName);                                          From ChatGPT clarification
                      in both overloaded operator[] methods.	                                            + compiler C4267 warning.m

Account.cpp	          Added type casting for assignment operators and safe comparisons as per C2440 errors  From ChatGPT clarification
                      (adjusting variable names and logic where type mismatch occurred)

main.cpp              Fixed C2440 error: replaced cout << "Account B Holder: " << const_cast<const          From ChatGPT suggestion after
                      char*>(accountB) << endl; with cout << "Account B Holder: " << (const char*)accountB  error appeared
                      << endl; to properly use type conversion operator.

main.cpp              Fixed C2593 ambiguous operator issue by making sure no direct cout << accountB was    From compiler C2593 error and
                      attempted without calling display() or proper type cast.                              ChatGPT clarification

reflect.txt           Personally written.
-----------------------------------------------------------
*/
#ifndef SDDS_ACCOUNT_H
#define SDDS_ACCOUNT_H
#include <iostream>

namespace sdds {
    const int MAX_NAME_LEN= 30;
    class Account {
        char accountHolderName[MAX_NAME_LEN + 1];
        int accountNumber;
        double accountBalance;
        void setToInvalid();
    public:

    //Constructors
        Account();
        Account(const char* holderName);
        Account(const char* holderName, int number, double balance);

    //Type conversion operators
        operator bool() const;
        operator int() const;
        operator double() const;
        operator const char* () const;

    //Subscriptor operators
        char& operator[](int index);
        char operator[](int index) const;

    //Assignment operators
        Account& operator=(int accountNumber);
        Account& operator=(double balance);

    //Balance modifer operators
        Account& operator+=(double amount);
        Account& operator-=(double amount);
        //Fund transfering operators
        Account& operator<<(Account& other);
        Account& operator>>(Account& other);

    //Unary operators
        bool operator~() const;
        Account& operator++();   //prefix
        Account operator++(int); //postfix
        Account& operator--();   //prefix
        Account operator--(int); //postfix

    //Display function
        std::ostream& display() const;
    };
}
#endif