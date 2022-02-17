//
//  BankAccount.hpp
//  Midterm-Prep
//
//  Created by Shawn Davidson on 10/13/21.
//

#ifndef BankAccount_hpp
#define BankAccount_hpp

class BankAccount {
public:
    BankAccount(float balance, int password);
    
    bool    deposit(float amount, int password);
    bool    withdraw(float amount, int password);
    
    bool    setPassword(int oldPassword, int newPassword);
    float   balance(int password) const;
    
private:
    bool isPassword(int password) const;
    
private:
    float   m_balance;
    int     m_password;
};

BankAccount* getNewAccount(int password);

#endif /* BankAccount_hpp */
