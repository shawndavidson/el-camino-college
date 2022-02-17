//
//  balance.cpp
//  CS2-Project4
//
//  Created by Shawn Davidson on 10/24/21.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <stack>

using namespace std;


// Matching pairs of symbols used in C++
// Symbol sequence must be paired in the order such that opening
// symbols have even indices and closing symbols have odd indices.
const string    symbolPairs             = "{}()[]";
const char      blockCommentSymbol      = 'c';


// Check if a character is an opening symbol such as {
// If so, return true. Otherwise, return false.
bool isOpeningBrace(int c)
{
    size_t pos = symbolPairs.find(c);
    
    return pos != std::string::npos && pos % 2 == 0;
}

// Check if a character is a closing symbol such as }
// If so, return true. Otherwise, return false.
bool isClosingBrace(int c, char& match)
{
    size_t pos = symbolPairs.find(c);
    
    if (pos != std::string::npos && pos % 2 != 0) {
        match = symbolPairs[pos-1];
        
        return true;
    }
    return false;
}

// Check if there is a an opening comment block "/*" at a specified position in a string
// If so, return true. Otherwise, return false.
bool opensBlockComment(const string& s, int pos) {
    return (pos + 1) < s.length() && s[pos] == '/' && s[pos+1] == '*';
}

// Check if there is a closing comment block "*/" at a specified position in a string
// If so, return true. Otherwise, return false.
bool closesBlockComment(const string& s, int pos) {
    return (pos + 1) < s.length() && s[pos] == '*' && s[pos+1] == '/';
}

// Check if there is an inline comment "//" at a specified position in a string
// If so, return true. Otherwise, return false.
bool opensInlineComment(const string& s, int pos) {
    return (pos + 1) < s.length() && s[pos] == '/' && s[pos+1] == '/';
}

// Check if there is an inline comment "//" at a specified position in a string
// If so, return true. Otherwise, return false.
bool extendsInlineComment(const string& s) {
    const size_t len = s.length();
    return len > 0 && s[len-1] == '\\';
}


// Report an unmatch single-character symbol error such as an unbalanced curly brace
void reportUnbalancedSymbol(char symbol, size_t lineNumber) {
    cout << "unmatched symbol " << symbol << " at line " << lineNumber << endl;
}

// Report an unmatch multi-character symbol error such as an unbalanced block comment
void reportUnbalancedSymbol(string multiCharSymbol, size_t lineNumber) {
    cout << "unmatched symbol " << multiCharSymbol << " at line " << lineNumber << endl;
}

// Report the occurance of a matched single-character symbol
void reportMatchedSymbol(char open, char close) {
    cout << "pair matching " << open << " and " << close << endl;
}

// Report the occurance of a matched multi-character symbol
void reportMatchedSymbol(string open, string close) {
    cout << "pair matching " << open << " and " << close << endl;
}

// Print a file with line numbers
void printFile(istream &dictfile)
{
    string s;
    
    // Read the file line by line
    for (int lineNumber = 1; !dictfile.eof(); lineNumber++) {
        getline(dictfile, s);
        
        cout << left << setw(4) << lineNumber << ": " << s << endl;
    }
    
    cout << endl << endl;
}

// Check if a C++ file is balanced. It is balanced if special symbols
// such as: {, (, [ are closed properly with matching symbols }, ), ].
// This also checks block and inline comments while ignoring the content
// that has been commented out.
bool balanceFile(istream &dictfile)
{
    struct Entry {
        char    symbol;
        size_t  lineNumber;
    };
    
    // Tracks the special symbols we encounter to check for balance
    stack<Entry> balanceStack;
        
    // Roll the file stream back to the beginning
    dictfile.clear();
    dictfile.seekg(0, dictfile.beg);

    bool blockComment   = false;
    bool quote          = false;
    bool charLiteral    = false;
    
    string s;

    // Read the file line by line
    for (int lineNumber = 1; !dictfile.eof(); lineNumber++) {
        getline(dictfile, s);
        
        // Parse a line character by character
        for (int i = 0; i < s.length(); i++) {
            char match;
            
            if (!blockComment && !charLiteral && !quote && isOpeningBrace(s[i])) {
                // Push our symbol on the stack to track it
                Entry entry;
                
                entry.symbol        = s[i];
                entry.lineNumber    = lineNumber;
                
                balanceStack.push(entry);
            }else if (!blockComment && !charLiteral && !quote && isClosingBrace(s[i], match)) {
                // Check the stack. If it's empty or the symbol on the top doesn't match
                // we're unbalanced.
                if (balanceStack.empty() || balanceStack.top().symbol != match) {
                    reportUnbalancedSymbol(s[i], lineNumber);
                    return false;
                }
                
                // Handle a matching symbol
                balanceStack.pop();
                reportMatchedSymbol(match, s[i]);
            }else if (!blockComment && !charLiteral && !quote && opensBlockComment(s, i)) {
                // Track that we're in a blockComment so we can ignore its content
                blockComment = true;
                // Move past the next character for this multi-character symbol
                i++;
                
                // Push a single-character symbol on the stack for
                // the sake of simplicity to track block comments
                // since /* is more than one character
                Entry entry;
                
                entry.symbol        = blockCommentSymbol;
                entry.lineNumber    = lineNumber;
                
                balanceStack.push(entry);
            }else if (blockComment && !charLiteral && !quote && closesBlockComment(s, i)) {
                // Track that we're out of our blockComment
                blockComment = false;
                // Move past the next character for this multi-character symbol
                i++;
                
                // Check the stack. If it's empty or the symbol on the top doesn't match
                // we're unbalanced.
                if (balanceStack.empty() || balanceStack.top().symbol != blockCommentSymbol) {
                    reportUnbalancedSymbol("*/", lineNumber);
                    return false;
                }
                
                balanceStack.pop();
                reportMatchedSymbol("/*", "*/");
            }else if (!blockComment && !charLiteral && !quote && opensInlineComment(s, i)) {
                // ignore the rest of the line
                break;
            }else if (!blockComment && !charLiteral && !quote && s[i]=='\"') {
                quote = true;
                                // Push our symbol on the stack to track it
                Entry entry;
                
                entry.symbol        = s[i];
                entry.lineNumber    = lineNumber;
                
                balanceStack.push(entry);
            }else if (!blockComment && !charLiteral && quote && s[i]=='\"') {
                // Track that we're out of our quote
                quote = false;
                
                // Check the stack. If it's empty or the symbol on the top doesn't match
                // we're unbalanced.
                if (balanceStack.empty() || balanceStack.top().symbol != '\"') {
                    reportUnbalancedSymbol("\"", lineNumber);
                    return false;
                }
                
                balanceStack.pop();
                reportMatchedSymbol("\"", "\"");
            }else if (!blockComment && !charLiteral && !quote && s[i] == '\'') {
                charLiteral = true;
                
                // Push our symbol on the stack to track it
                Entry entry;
                
                entry.symbol        = s[i];
                entry.lineNumber    = lineNumber;
                
                balanceStack.push(entry);
            }else if (!blockComment && charLiteral && !quote && s[i] == '\'') {
                // Track that we're out of our quote
                charLiteral = false;
                
                // Check the stack. If it's empty or the symbol on the top doesn't match
                // we're unbalanced.
                if (balanceStack.empty() || balanceStack.top().symbol != '\'') {
                    reportUnbalancedSymbol("'", lineNumber);
                    return false;
                }
                
                balanceStack.pop();
                reportMatchedSymbol("'", "'");
            }
        }
    }
            
    // Check if there are any unmatched symbols left on the stack
    // that would indicate an unbalanced state
    if (!balanceStack.empty()) {
        // Report any symbols left on the stack as errors
        while (!balanceStack.empty()) {
                // Report the first unbalanced symbol
                const Entry& entry = balanceStack.top();
                
                if (entry.symbol != blockCommentSymbol)
                    reportUnbalancedSymbol(entry.symbol, entry.lineNumber);
                else
                    reportUnbalancedSymbol("/*", entry.lineNumber);
        
                balanceStack.pop();
        }

        return false;
    }
    
    return true;
}



////////
// Delete below here
///////

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <csignal>
#include <regex>
#include <type_traits>
#include <set>

using namespace std;

class streambuf_switcher
{
public:
    streambuf_switcher(ios& dest, ios& src)
    : dest_stream(dest), saved_streambuf(dest.rdbuf(src.rdbuf()))
    {}
    ~streambuf_switcher()
    {
        dest_stream.rdbuf(saved_streambuf);
    }
private:
    ios& dest_stream;
    streambuf* saved_streambuf;
};

void testone(int n)
{

    ostringstream strCout;
    streambuf_switcher sso(cout, strCout);
    
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            istringstream iss("{}");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\{ *and *\})");
            assert(regex_search(str, e));
        } break; case  2: {
            istringstream iss("[]");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *[ *and *])");
            assert(regex_search(str, e));
        } break; case  3: {
            istringstream iss("()");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\)");
            assert(regex_search(str, e));
        } break; case  4: {
            istringstream iss("/* */");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching */\* *and *\*/)");
            assert(regex_search(str, e));
        } break; case  5: {
            istringstream iss("\" \"");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\" *and *\")");
            assert(regex_search(str, e));
        } break; case  6: {
            istringstream iss("' '");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *' *and *')");
            assert(regex_search(str, e));
        } break; case  7: {
            istringstream iss("{\n}");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\{ *and *\})");
            assert(regex_search(str, e));
        } break; case  8: {
            istringstream iss("{(\n)}");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case  9: {
            istringstream iss("() {}");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case  10: {
            istringstream iss("\" ][ \"");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching *\" *and *\")");
            assert(regex_search(str, e));
        } break; case  11: {
            istringstream iss("/* \n ][ */ { * }");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching */\* *and *\*/.*\npair *matching *\{ *and *\})");
            assert(regex_search(str, e));
        } break; case  12: {
            istringstream iss("/* \n ][ */");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e(R"(pair *matching */\* *and *\*/)");
            assert(regex_search(str, e));
        } break; case  13: {
            istringstream iss("\n{\n(\n//']\n)}");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case  14: {
            istringstream iss("\n{\n(\n//*]\n)}");
        assert(balanceFile(iss));
            string str = strCout.str();
            regex e("pair *matching *\\( *and *\\).*\\npair *matching *\\{ *and *\\}");
            assert(regex_search(str, e));
        } break; case  15: {
            istringstream iss("\n{\n(]\n)}");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced).*(\\(|\\]).*3");
            assert(regex_search(str, e));
        } break; case  16: {
            istringstream iss("\n{(\n)");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced).*\\{.*2");
            assert(regex_search(str, e));
        } break; case  17: {
            istringstream iss("\n\n{(\n')}");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced).*'.*4");
            assert(regex_search(str, e));
        } break; case  18: {
            istringstream iss("{");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case  19: {
            istringstream iss("}");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case  20: {
            istringstream iss("{ /* }");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case  21: {
            istringstream iss("'*");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case  22: {
            istringstream iss("()[]{ * }}");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break; case  23: {
            istringstream iss("()([{}]) /* */");
        assert(balanceFile(iss));
        } break; case  24: {
            istringstream iss("/* ]][()) ' */");
        assert(balanceFile(iss));
        } break; case  25: {
            istringstream iss(" ][ ");
        assert(!balanceFile(iss));
            string str = strCout.str();
            regex e("(unmatched|unbalanced)");
            assert(regex_search(str, e));
        } break;
    
    }
}

int main()
{
    // cout << "Enter test number: ";
    // int n;
    // cin >> n;
    
    for (int n = 1; n < 25+1; n++) {
        cout << "Running test " << n << endl;
        testone(n);
    }
    
    cout << "Passed" << endl;
    
    return 0;
}
