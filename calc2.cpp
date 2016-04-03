// Filename: calc2.cpp
// Date: 2016-04-02  --  2016-04-02
// Programmer: Matt Shaw
// Additional files: Interpreter_H.h, Interpreter.cpp

/*
		DESCRIPTION:
		
		A very simple calculator.
		Uses the Interpreter class.

*/

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "Interpreter_H.h"

int main()
{
	string inputLine;
	bool again = true;

	while (again)
	{
		cout << "calc> ";
		getline(cin, inputLine);
		if (cin.eof())
		{
			again = false;
			continue;
		}
		if (inputLine == "")
			continue;
		Interpreter interpreter(inputLine);
		int result = interpreter.expr();
		if (interpreter.errorState())
			cout << "Input discarded.\n";
		else
		{
			cout << result << endl;
		}
	}

	return 0;
}
