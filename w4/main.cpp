/* Citation and Sources
-----------------------------------------------------------
Workshop #4
Module: Member Operators and Helper Functions
Filename: main.cpp
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
#include <iostream>
#include "Account.h"
using namespace std;
using namespace sdds;

int main() {
    cout << "---Account Creation Tests---" << endl;

    //New account (only the holder name)
    Account accountA("Alice");
    accountA.display() << endl;

    //Invalid account (the bad number and the negative balance)
    Account invalidAccount("Eve", 555, -100);
    invalidAccount.display() << endl;

    //Valid account
    Account accountB("Bob", 12345, 500.0);
    accountB.display() << endl;
    cout << "---Type Conversion Tests---" << endl;
    cout << "Account B Number: " << int(accountB) << endl;
    cout << "Account B Balance: " << double(accountB) << endl;
    cout << "Account B Holder: " << (const char*)accountB << endl;
    cout << "Is Account B Valid? " << (accountB ? "Yes" : "No") << endl;
    cout << "---Subscript Operator Tests---" << endl;
    cout << "First character of Account B's holder name: " << accountB[0] << endl;
    accountB[0] = 'R';
    accountB.display() << endl;

    cout << "---Assignment Operator Tests---" << endl;
    Account newAccount("Charlie");
    newAccount = 67890;                                   //Valid number assignment
    newAccount.display() << endl;

    newAccount = 123;                                     //Invalid number, it should become invalid
    newAccount.display() << endl;

    cout << "---Balance Modification Tests---" << endl;
    accountB += 250.0;
    accountB.display() << endl;

    accountB -= 800.0;                                  //Not enough funds present
    accountB.display() << endl;

    accountB -= 200.0;
    accountB.display() << endl;

    cout << "---Fund Transfer Tests---" << endl;
    Account accountC("Clara", 54321, 300.0);
    accountC.display() << endl;

    accountC << accountB;
    cout << "After account C << account B:" << endl;
    accountC.display() << endl;
    accountB.display() << endl;

    Account accountD("David", 67890, 700.0);
    accountD.display() << endl;

    accountD >> accountC;
    cout << "After accountD >> accountC:" << endl;
    accountC.display() << endl;
    accountD.display() << endl;

    cout << "---Unary Operator Tests---" << endl;
    cout << "Is Account A new?" << (~accountA ? "Yes" : "No") << endl;
    ++accountC;
    accountC.display() << endl;
    accountC++;
    accountC.display() << endl;
    --accountC;
    accountC.display() << endl;
    accountC--;
    accountC.display() << endl;
    cout << "---Subscript with Loopback Test---" << endl;
    cout << "accountC[50](should loop to valid char):" << accountC[50] << endl;
    return 0;
}