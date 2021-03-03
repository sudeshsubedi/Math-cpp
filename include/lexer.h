#pragma once
#include <iostream>
#include <string>
#include <vector>

#define string std::string

// TOKENS
enum TOKENS
{
    NUMBER,
    VARIABLE,
    SYMBOL,
    FUNCTION
};

struct Token
{
    string name;
    string value="";
    Token(string name_, string value_="");
    friend std::ostream& operator<< (std::ostream& out, const Token& token);
};

class Lexer
{
private:
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string numbers = "0123456789";
    const string symbols = "+-/%!";
    const char leftParen = '(';
    const char rightParen = ')';
    char currentChar;
    int index = -1;
    string text = "";
public:
    Lexer(string text);
    void advance();
    std::vector<Token> returnToken();
    Token handleString();
    Token handleDigit();
    Token handleAstrick();
    Token handleSymbol();
    void setText(string text_);
};