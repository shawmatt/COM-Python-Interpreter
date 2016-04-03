// Filename: Interpreter_H.h
// Date: 2016-04-02  --  2016-04-02
// Programmer: Matt Shaw
// Defines the Interpreter class.
// Defines and implements the Token structure and token_t type.
// Additional file: Interpreter.cpp

#ifndef MATT_SHAW_COMP_235_INTERPRETER_H
#define MATT_SHAW_COMP_235_INTERPRETER_H

#include <string>
using std::string;

struct Token
{
	enum token_t { Integer, Op, Eof }; // Token types
	// Eof (end-of-file) token is used to indicate that
	// there is no more input left for lexical analysis
	union value_t
	{
		char charValue;
		int intValue;
	};

	token_t type;
	value_t value;

	// token type: Integer, Op, or Eof
	// token value: '0', '1', '2', '3', '4', '5',
	//  '6', '7', '8', '9', '+', '-', or '\0' indicating "None"

	Token(token_t p_type = Eof, const char p_charValue = '\0');
	// handles Op, Eof, and default/none (uses Eof)

	Token(token_t p_type, const int p_intValue);
	// handles Integer

	// Examples:
	//  Token(Integer, 3)
	//  Token(Op, '+')
};

class Interpreter
{
public:
	// No default constructor
	Interpreter(const string&); // String argument must be present

	int expr(); // evaluates the expression, returning the integer result
	// if the expression is invalid, returns INT_MAX and sets the error flag

	bool errorState() const; // Returns status of error flag.

private:
	// Enable clean use of token_t type:

	typedef Token::token_t token_t;

	const token_t Eof = token_t::Eof;
	const token_t Integer = token_t::Integer;
	const token_t Op = token_t::Op;

	// Members:
	string m_text;
	unsigned m_pos;
	Token m_currentToken;
	char m_currentChar;
	bool errorFlag;

	//Helper functions:
	void error(const string&); // displays error message and sets error flag
	Token getNextToken(); // Lexical analyzer (also known as scanner or tokenizer)
	void eat(token_t p_tokenType); // moves to the next token.
	// If the current token doesn't match the argument, raises an error
	void skipWhitespace();
	void advance();
	int integer();
};

#endif
