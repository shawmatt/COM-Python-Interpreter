// Filename: Interpreter.cpp
// Date: 2016-04-02  --  2016-04-02
// Programmer: Matt Shaw
// Implements the Interpreter class and the Token struct
// Additional file: Interpreter_H.h

#include "Interpreter_H.h"

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <cctype>

Token::Token(token_t p_type, const char p_charValue)
{
	type = p_type;
	value.charValue = p_charValue;
}

Token::Token(token_t p_type, const int p_intValue)
{
	type = p_type;
	value.intValue = p_intValue;
}

Interpreter::Interpreter(const string& p_text)
// client string input, e.g. "3+5", 12-5", etc.
{
	m_text = p_text;
	// m_pos is an index into m_text
	m_pos = 0;
	// current token instance is (eof, '\0')
	m_currentToken = Token(Eof, '\0');
	m_currentChar = m_text[m_pos];
	errorFlag = false;
}

void Interpreter::error(const string& errorMessage)
{
	cerr << "Error parsing input: " << errorMessage << endl;
	errorFlag = true;
}

void Interpreter::advance()
//Advance the 'm_pos' pointer and set the 'm_currentChar' variable.
{
	++m_pos;
	if (m_pos > (m_text.length() - 1))
		m_currentChar = '\0'; // Indicates end of input;
	else
		m_currentChar = m_text[m_pos];
}

//void Interpreter::skipWhitespace()
//{
//	while ((m_pos < m_text.length()) && isspace(m_currentChar))
//		m_currentChar = m_text[++m_pos]; // skip consecutive whitespaces
//}

void Interpreter::skipWhitespace()
{
	while ((m_currentChar != '\0') && isspace(m_currentChar))
		advance(); // skip consecutive whitespaces
}

int Interpreter::integer()
//Return a (multidigit) integer consumed from the input.
{
	string intString = "";
	while ((m_currentChar != '\0') && isdigit(m_currentChar))
	{
		intString.push_back(m_currentChar);
		advance();
	}
	return stoi(intString);
}

Token Interpreter::getNextToken()
{
	/*Lexical analyzer (also known as scanner or tokenizer)

	This method is responsible for breaking a sentence
	apart into tokens.One token at a time.
	*/

	while (m_currentChar != '\0')
	{
		if (isspace(m_currentChar))
		{
			skipWhitespace();
			continue;
		}

		if (isdigit(m_currentChar))
			return Token(Integer, integer());

		if (m_currentChar == '+')
		{
			advance();
			return Token(Op, '+');
		}

		if (m_currentChar == '-')
		{
			advance();
			return Token(Op, '-');
		}

		error("unexpected character in input");
	}
	return Token(Eof, '\0');
}

void Interpreter::eat(token_t p_tokenType)
{
	// compare the current token type with the passed token
	// type and if they match then "eat" the current token
	// and assign the next token to the m_currentToken,
	// otherwise raise an exception.
	if (m_currentToken.type == p_tokenType)
		m_currentToken = getNextToken();
	else
		error("token type mismatch");
}

int Interpreter::expr()
{
/*
	Parser / Interpreter

	expr->INTEGER PLUS INTEGER
	expr->INTEGER MINUS INTEGER
*/

	// set current token to the first token taken from the input
	m_currentToken = getNextToken();
	if (errorFlag) return INT_MAX;

	// we expect the current token to be an integer
	Token left = m_currentToken;
	eat(Integer);
	if (errorFlag) return INT_MAX;

	// we expect the current token to be a '+' or '-' (type Op) token
	Token op = m_currentToken;
	eat(Op);
	if (errorFlag) return INT_MAX;

	// we expect the current token to be an integer
	Token right = m_currentToken;
	eat(Integer);
	if (errorFlag) return INT_MAX;

	// after the above call the m_currentToken is set to
	// Eof token

	// at this point integer plus integer sequence of tokens
	// has been successfully found and the method can just
	// return the result of adding two integers, thus
	// effectively interpreting client input
	if (op.value.charValue == '+')
			return left.value.intValue + right.value.intValue;
	else
		return left.value.intValue - right.value.intValue;
}

bool Interpreter::errorState() const { return errorFlag; }
