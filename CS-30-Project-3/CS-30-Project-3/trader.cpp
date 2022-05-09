//
//  main.cpp
//  CS-30-Project-3
//
//  Created by Shawn Davidson on 5/9/22.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>

using namespace std;

// Delimeter for parsing stock price and trading data
const char delimeter        = '|';

// Max profit thresold for triggering an alert
const int  profit_threshold = 500000;

// Max number of days to look back for triggering an alert
const int  days_threshold   = 3;

// Associates days to stock prices
typedef map<int, int> MapStockPrices;

// Associates a day to trades, where each trade associates a trader to # of shares bought or sold.
// The # of shares is indicated by a positive value for a buy and negative for a sell.
typedef unordered_map<int, multimap<string, int>> MapTrades;

// Parse the prices and trades from the stock trading data
void parse(const vector<string>& inputVec, MapStockPrices& prices, MapTrades& trades) {
    vector<string> tokens;
    string token;
    
    // Iterate through each line which represents a stock price change or a trade
    for (const string& input : inputVec) {
        stringstream ss(input);
        
        // Tokenize the input string by the delimeter
        while (getline(ss, token, delimeter)) {
            tokens.push_back(token);
        }
                
        switch (tokens.size()) {
            case 2:
                {
                    // handle stock price change, format: <DAY>|<PRICE>
                    int day     = stoi(tokens[0]);
                    int price   = stoi(tokens[1]);
                    
                    //cout << "Day " << day << ": $" << price << endl;
                    prices[day] = price;
                }
                break;
            case 4:
                {
                    // handle a trade, format: <DAY>|<TRADER>|<TRADE_TYPE>|<AMOUNT>
                    int             tradeDay    = stoi(tokens[0], nullptr);
                    const string&   trader      = tokens[1];
                    const string&   type        = tokens[2];
                    int             amount      = stoi(tokens[3], nullptr);
                    
                    //cout << "Day " << tradeDay << ", " << trader << ", " << tokens[2] << ", " << amount << " shares" << endl;
                    
                    trades[tradeDay].insert({ trader, (type == "BUY") ? amount : -amount });
                }
                break;
            default:
                // TODO: If this were a production app we'd need to handle an invalid line
                break;
        };
        
        // Clear tokens before processing the next line
        tokens.clear();
    }

}

vector<string> findPotentialBadTraders(const vector<string>& inputVec) {
    vector<string> traderAlerts;

    MapStockPrices  prices;
    MapTrades       trades;
    
    parse(inputVec, prices, trades);
    
    int last_price = prices[0];
    
    for (auto pricePair : prices) {
        const int& day    = pricePair.first;
        const int& price  = pricePair.second;
        
        int priceChange = price - last_price;
        
        for (int daysToLookBack = 0; daysToLookBack < days_threshold; daysToLookBack++) {
            int actualDay = day - daysToLookBack;
            
            for (auto tradePair : trades[actualDay]) {
                const string& trader    = tradePair.first;
                const int& amount       = tradePair.second;
                
                if (amount * priceChange > profit_threshold) {
                    stringstream ss;
                    ss << actualDay << delimeter << trader;
                    
                    traderAlerts.push_back(ss.str());
                }
            }
        }
        
        last_price = pricePair.second;
    }
    
    return traderAlerts;
}

int main() {
    
    ifstream in("/Users/sdavidson/XCodeProjects/CS-30-Project-3/CS-30-Project-3/input.txt");
    string str;
    
    if (!in) {
        cerr << "No input file" << endl;
        exit (0);
    }
    
    vector<string> inputVec;
    while (getline(in,str)) {
        inputVec.push_back(str);
    }
    vector<string> resV = findPotentialBadTraders(inputVec);
    for (const string& r : resV) {
        cout << r << endl;;
    }
    return 0;
}
