//
//  BankAccount.cpp
//  Midterm-Prep
//
//  Created by Shawn Davidson on 10/13/21.
//

#include "BankAccount.hpp"

BankAccount* getNewAccount(int password) {
    return new BankAccount(10.0, password);
}

BankAccount::BankAccount(float balance, int password) {
    this->m_balance     = balance >= 0.0 ? balance : 0.0;
    this->m_password    = password;
}

bool BankAccount::deposit(float amount, int password) {
    if (!isPassword(password) || amount < 0.0)
        return false;
    
    this->m_balance += amount;
    
    return true;
}

bool BankAccount::withdraw(float amount, int password) {
    if (!isPassword(password) || amount < 0.0)
        return false;
    
    if (amount > this->m_balance)
        return false;
    
    this->m_balance -= amount;
    
    return true;
}

bool BankAccount::setPassword(int oldPassword, int newPassword) {
    if (!isPassword(oldPassword))
        return false;
    
    this->m_password = newPassword;
    return true;
}

float BankAccount::balance(int password) const {
    if (!isPassword(password))
        return -1.0;
    
    return this->m_balance;
}

bool BankAccount::isPassword(int password) const {
    return this->m_password == password;
}

