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
#include <set>
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
// Using an unordered_map for fast lookups O(1) by trading day
// Using a multimap because a trader may make multiple trades on a single day
typedef unordered_map<int, multimap<string, int>> MapTrades;

// Associates a day to a set of traders who made suspicious trades (exceeded thresholds)
// Using a map to keep the keys (day) sorted
// Using a set to ensure uniqueness (traders), i.e. a trader has at most one alert on a given day
typedef map<int, set<string>> MapAlerts;

// Parse the stock prices and trades from the raw stock trading data
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

// Format alert data into strings suitable for displaying to the user
void formatAlerts(const MapAlerts& alerts, vector<string>& results) {
    // Convert alerts to strings
    for (auto alertPair : alerts) {
        const int& day = alertPair.first;
        const set<string>& traders = alertPair.second;
        
        for (string trader : traders) {
            stringstream ss;
            ss << day << delimeter << trader;
            
            results.push_back(ss.str());
        }
    }
}

// Analyze stock price changes and trades for excessive profits/avoided losses. Return alerts to the caller.
void analyzeTrades(const MapStockPrices &prices, const MapTrades &trades, MapAlerts &alerts) {
    // Is there anything to check?
    if (prices.size() == 0 || trades.size() == 0)
        return;
    
    int last_price = prices.at(0);
    
    alerts.clear();
    
    // Iterate through the changes in stock price
    for (auto pricePair : prices) {
        const int& day    = pricePair.first;
        const int& price  = pricePair.second;
        
        // Calculate the difference from the last price
        int priceChange = price - last_price;
        
        // Look back over the past N days (days_threshold) for a trade whose profit or
        // avoided loss exceeds our threshold
        for (int daysToLookBack = 0; daysToLookBack < days_threshold; daysToLookBack++) {
            int actualDay = day - daysToLookBack;
            
            try {
                // Iterate through the trades for this day
                for (auto tradePair : trades.at(actualDay)) {
                    const string& trader    = tradePair.first;
                    const int& amount       = tradePair.second;
                    
                    // If a profit or an avoided loss, i.e. a buy before a price increase or a sell before a price decrease
                    // that exceeds our threshold
                    if (amount * priceChange > profit_threshold) {
                        alerts[actualDay].insert(trader);
                    }
                }
            }
            catch(out_of_range ex) {
                // trades.at(actualDay) will throw if there are no trades on this day.
                // It's okay, just keep going...
            }
        }
        
        last_price = pricePair.second;
    }
}

vector<string> findPotentialBadTraders(const vector<string>& inputVec) {
    MapStockPrices  prices;
    MapTrades       trades;

    parse(inputVec, prices, trades);
    
    MapAlerts       alerts;

    analyzeTrades(prices, trades, alerts);
    
    vector<string> results;

    formatAlerts(alerts, results);
    
    return results;
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
