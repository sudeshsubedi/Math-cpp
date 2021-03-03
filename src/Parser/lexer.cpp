#include "lexer.h"

Token::Token(string name_, string value_){
    name = name_;
    value = value_;
}

std::ostream& operator<< (std::ostream& out, const Token& token){
	string str = "Name: " + token.name;
    if(!token.value.empty()){
        str += "\tValue: " + token.value + "\n";
    }else {
        str += "\n";
    }
    out << str;
	return out;
}

Lexer::Lexer(string text_){
    text = text_;
    advance();
}

void Lexer::advance(){
    index++;
    currentChar = (index< (int) text.length()) ? text[index] : '^';
}

std::vector<Token> Lexer::returnToken(){
    std::vector<Token> tokens;
    while(index < (int) text.length()){
        if(currentChar == ' '){
            advance();
        }else if(letters.find(currentChar) != string::npos){
            tokens.push_back(handleString());
        }else if(numbers.find(currentChar) != string::npos){
            tokens.push_back(handleDigit());
        }else if(currentChar == '*'){
            tokens.push_back(handleAstrick());
        }else if(symbols.find(currentChar) != string::npos){
            tokens.push_back(handleSymbol());
        }else if(currentChar == leftParen){
            //Token temp = Token("leftParen");
            tokens.push_back(Token("leftParen"));
            advance();
        }else if(currentChar == rightParen){
            Token temp = Token("rightParen");
            tokens.push_back(temp);
            advance();
        }else {
            throw "Illegal character";
        }
    }
    return tokens;

}

Token Lexer::handleString(){
    string tokenvalue = "";
    while(letters.find(currentChar) != string::npos){
        tokenvalue+=currentChar;
        advance();
    }
    if(currentChar == leftParen){
        return Token("Function", tokenvalue);
    }
    return Token("Variable", tokenvalue);
}

Token Lexer::handleDigit(){
    int dotCounter = 0;
    string tokenvalue = "";
    while(numbers.find(currentChar) != string::npos or currentChar == '.'){
        if(dotCounter > 1){
            throw "More that one decimal point in a digit";
        }
        if(currentChar == '.'){
            dotCounter++;
        }
        tokenvalue+=currentChar;
        advance();
    }
    return Token("Digit", tokenvalue);
}

Token Lexer::handleAstrick(){
    int counter = 0;
    while(currentChar == '*'){
        counter++;
        if(counter>2){
            throw "\nIllegal symbol ***\n";
        }
        advance();
    }
    if(counter == 1){
        return Token("Multiply");
    }
    return Token("Power");
}

Token Lexer::handleSymbol(){
    switch(currentChar){
        case '+':
            advance();
            return Token("Plus");
        case '-':
            advance();
            return Token("Minus");
        case '/':
            advance();
            return Token("Divide");
        case '%':
            advance();
            return Token("Modulo");
        case '!':
            advance();
            return Token("Factorial");
        default:
            throw "Illegal symbol";
            break;
    }
}

void Lexer::setText(string text_){
    text = text_;
}