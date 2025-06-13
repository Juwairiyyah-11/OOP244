/* Citation and Sources
-----------------------------------------------------------
Workshop #4
Module: Member Operators and Helper Functions
Filename: Account.cpp
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
                      in both overloaded operator[] methods.	                                            + compiler C4267 warning.

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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Account.h"
using namespace std;

namespace sdds {
    void Account::setToInvalid() {
        accountNumber= -1;
        accountBalance= 0.0;
        accountHolderName[0] = '\0';
    }

    //Constructors
    Account::Account() {
        setToInvalid();
    }
    Account::Account(const char* holderName) {
        if (holderName && holderName[0] != '\0') {
            strncpy(accountHolderName, holderName,MAX_NAME_LEN);
            accountHolderName[MAX_NAME_LEN] = '\0';
            accountNumber= 0;
            accountBalance= 0.0;
        } 
        else {
            setToInvalid();
        }
    }
    Account::Account(const char* holderName, int number, double balance) {
        if (holderName && holderName[0] != '\0' && number >= 10000 && number <= 99999 && balance >= 0) {
            strncpy(accountHolderName, holderName,MAX_NAME_LEN);
            accountHolderName[MAX_NAME_LEN]= '\0';
            accountNumber= number;
            accountBalance= balance;
        }
        else {
            setToInvalid();
        }
    }

    //Type conversion operators
    Account::operator bool() const {
        return accountNumber >= 10000 && accountNumber <= 99999 && accountBalance >= 0 && accountHolderName[0] != '\0';
    }
    Account::operator int() const {
        return accountNumber;
    }
    Account::operator double() const {
        return accountBalance;
    }
    Account::operator const char* () const {
        return accountHolderName;
    }

    //Subscriptor operators
    char& Account::operator[](int index) {
        size_t len= strlen(accountHolderName);
        if (len== 0) return accountHolderName[0];
        index %= static_cast<int>(len);
        if (index < 0) index += static_cast<int>(len);
        return accountHolderName[index];
    }
    char Account::operator[](int index) const {
        size_t len = strlen(accountHolderName);
        if (len== 0) return '\0';
        index %= static_cast<int>(len);
        if (index < 0) index += static_cast<int>(len);
        return accountHolderName[index];
    }

    //Assignment operators
    Account& Account::operator=(int newAccountNumber) {
        if (*this && newAccountNumber >= 10000 && newAccountNumber <= 99999) {
            accountNumber= newAccountNumber;
        } 
        else {
            setToInvalid();
        }
        return *this;
    }
    Account& Account::operator=(double balance) {
        if (*this && balance >= 0) {
            accountBalance= balance;
        } 
        else {
            setToInvalid();
        }
        return *this;
    }

    //Balance modifier
    Account& Account::operator+=(double amount) {
        if (*this && amount >= 0) accountBalance += amount;
        return *this;
    }
    Account& Account::operator-=(double amount) {
        if (*this && amount >= 0 && accountBalance >= amount) accountBalance -= amount;
        return *this;
    }

    //Fund transfer
    Account& Account::operator<<(Account& other) {
        if (this != &other && *this && other) {
            accountBalance += other.accountBalance;
            other.accountBalance= 0;
        }
        return *this;
    }
    Account& Account::operator>>(Account& other) {
        if (this != &other && *this && other) {
            other.accountBalance += accountBalance;
            accountBalance = 0;
        }
        return *this;
    }

    //Unary operators
    bool Account::operator~() const {
        return accountNumber== 0 && accountHolderName[0] != '\0';
    }
    Account& Account::operator++() {
        accountBalance++;
        return *this;
    }
    Account Account::operator++(int) {
        Account temp= *this;
        ++*this;
        return temp;
    }
    Account& Account::operator--() {
        accountBalance--;
        return *this;
    }
    Account Account::operator--(int) {
        Account temp= *this;
        --*this;
        return temp;
    }

    //Display function
    ostream& Account::display() const {
        if (!*this) {
            cout << "Bad Account" << endl;
        } 
        else if (accountNumber== 0) {
            cout << "New: " << accountHolderName << endl;
        } 
        else {
            cout << "Account Holder:" << accountHolderName << ", Number:" << accountNumber << ", Balance:" << accountBalance << endl;
        }
        return cout;
    }
}