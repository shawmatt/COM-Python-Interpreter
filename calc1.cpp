#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <cctype>

// Token types
//
// eof (end-of-file) token is used to indicate that
// there is no more input left for lexical analysis
enum token_t { integer, plus, eof };

struct Token
{
	Token()
	{
		type = eof;
		charValue = '\0';
	}

	Token(token_t p_type, const char p_charValue) // handles plus and eof
		: type(p_type), charValue(p_charValue) {}

	Token(token_t p_type, const int p_intValue)
		: type(p_type), intValue(p_intValue) {}

	// token type: integer, plus, or eof
	// token value: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', or '\0' for "None"
	// Examples:
    //  Token(integer, 3)
	//  Token(plus '+')

	token_t type;
	char charValue;
	int intValue;
};

class Interpreter
{
public:
	Interpreter(const string& p_text) // client string input, e.g. "3+5"
		: m_text(p_text)
	{
		m_pos = 0;
		// m_pos is an index into m_text
		// current token instance is (eof, '\0')
	}

	void error()
	{
		cerr << "Error parsing input" << endl;
	}

    Token getNextToken()
	{
		/*Lexical analyzer (also known as scanner or tokenizer)

		This method is responsible for breaking a sentence
		apart into tokens.One token at a time.
		*/
		string text(m_text);

		// is m_pos index past the end of the m_text ?
		// if so, then return eof token because there is no more
		// input left to convert into tokens
		if (m_pos > text.length() - 1)
			return Token(eof, '\0');

		// get a character at the position m_pos and decide
		// what token to create based on the single character
		char currentChar = text[m_pos];

		// if the character is a digit then convert it to
		// integer, create an integer token, increment m_pos
		// index to point to the next character after the digit,
		// and return the integer token

		if (isdigit(currentChar))
		{
			++m_pos;
			return Token(integer, int(currentChar - '0'));
		}
		else if (currentChar == '+')
		{
			++m_pos;
			return Token(plus, currentChar);
		}
		else
			error();
	}

	void eat(token_t p_tokenType)
	{
		// compare the current token type with the passed token
		// type and if they match then "eat" the current token
		// and assign the next token to the m_currentToken,
		// otherwise raise an exception.
		if (m_currentToken.type == p_tokenType)
			m_currentToken = getNextToken();
		else
			error();
	}

	int expr()
	{
		/*expr -> integer plus integer*/
		// set current token to the first token taken from the input
		m_currentToken = getNextToken();

		// we expect the current token to be a single-digit integer
		Token left = m_currentToken;
		eat(integer);

		// we expect the current token to be a '+' token
		Token op = m_currentToken;
		eat(plus);

		// we expect the current token to be a single-digit integer
		Token right = m_currentToken;
		eat(integer);
		// after the above call the m_currentToken is set to
		// eof token

		// at this point integer plus integer sequence of tokens
		// has been successfully found and the method can just
		// return the result of adding two integers, thus
		// effectively interpreting client input
		return left.intValue + right.intValue;
	}

private:
	string m_text;
	unsigned m_pos;
	Token m_currentToken;
};

int main()
{
	string inputLine;
	while (true)
	{
		cout << "calc> ";
		getline(cin, inputLine);
		if (cin.eof())
			break;
		if (inputLine == "")
			continue;
		Interpreter interpreter(inputLine);
		cout << interpreter.expr() << endl;
	}

	return 0;
}
