#include <iostream>
#include <vector>
#include "lexer.h"

int main() {
  Lexer l("");
  while(true){
    std::cout << "Math> ";
    string test;
    std::cin >> test;
    l.setText(test);
    std::vector<Token> testv = l.returnToken();
    for(int i=0; i<testv.size(); i++){
      std::cout << testv[i];
    }
  }
  return 0;
}
