#include "token.hpp"

// system includes
#include <cctype>
#include <iostream>

// define constants for special characters
const char OPENCHAR = '(';
const char CLOSECHAR = ')';
const char COMMENTCHAR = ';';
const char OPENSTRINGCHAR = '"';
const char CLOSESTRINGCHAR = '"';

Token::Token(TokenType t): m_type(t){}

Token::Token(const std::string & str): m_type(STRING), value(str) {}

Token::TokenType Token::type() const{
  return m_type;
}

std::string Token::asString() const{
  switch(m_type){
  case OPEN:
    return "(";
  case CLOSE:
    return ")";
  case STRING:
    return value;
  }
  return "";
}


// add token to sequence unless it is empty, clears token
void store_ifnot_empty(std::string & token, TokenSequenceType & seq){
  if(!token.empty()){
    seq.emplace_back(token);
    token.clear();
  }
}

TokenSequenceType tokenize(std::istream & seq){
  TokenSequenceType tokens;
  std::string token;
  //bool isString = false;
  
  while(true){
    char c = seq.get();
    if(seq.eof()) break;
    
    if(c == COMMENTCHAR){
      // chomp until the end of the line
      while((!seq.eof()) && (c != '\n')){
	c = seq.get();
      }
      if(seq.eof()) break;
    }
    else if(c == OPENCHAR){
      store_ifnot_empty(token, tokens);
      tokens.push_back(Token::TokenType::OPEN);
    }
    else if(c == CLOSECHAR){
      store_ifnot_empty(token, tokens);
      tokens.push_back(Token::TokenType::CLOSE);
    }
	/*else if (c == OPENSTRINGCHAR && !isString)
	{
		store_ifnot_empty(token, tokens);
		token.push_back(c);
		isString = true;
	}*/
	else if (c == OPENSTRINGCHAR)
	{
		//store_ifnot_empty(token, tokens);
		token.push_back(c);
		bool stringIsOver = false;
		while (!stringIsOver)
		{
			char c = seq.get();

			if (c != CLOSESTRINGCHAR) 
			{
				token.push_back(c);
			}
			else
			{
				token.push_back(c);
				stringIsOver = true;
			}
		}
	}
	/*else if (c == CLOSESTRINGCHAR && isString)
	{
		store_ifnot_empty(token, tokens);
		token.push_back(c);
		isString = false;
	}*/
    else if(isspace(c)){
      store_ifnot_empty(token, tokens);
    }
    else{
      token.push_back(c);
    }
  }
  store_ifnot_empty(token, tokens);

  return tokens;
}
