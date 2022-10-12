#include <stack>
#include <string>
#include <iostream>
#include <type_traits>
#include <conio.h>

#define ESC_KEY 27

#define ARITHMETIC_TEMPLATE template<typename T, \
	typename = typename std::enable_if<std::is_arithmetic<T>::value,T>::type> 

int GetPriorityOfOperation(const char& op) {
	switch (op)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}

//ARITHMETIC_TEMPLATE
double EvaluateOperation(const double& a, const double& b, const char& op) {
	switch (op) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}

void EvaluateTopOperatrion(std::stack<double>& values, std::stack<char>& operators) {
	auto fristValue = values.top();
	values.pop();
	auto secondValue = values.top();
	values.pop();

	char operation = operators.top();
	operators.pop();

	values.push(EvaluateOperation(secondValue, fristValue, operation));
}

double EvaluateExpression(std::string expression) {
	std::stack <double> values;
	std::stack <char> operators;

	for (int i = 0; i < expression.length(); i++) {
				
		if (expression[i] == ' ')
		{
			continue;
		}
		else if (expression[i] == '(') {
			operators.push(expression[i]);
		}
		else if (isdigit(expression[i])) {			
			std::string num;
			
			while (i < expression.length() &&
				(isdigit(expression[i]) || expression[i] == '.' || expression[i] == ','))
			{
				if (expression[i] == ',') num += '.';
				else num += expression[i];
				i++;
			}

			values.push(std::stod(num));
			i--;
		}
		else if (expression[i] == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				EvaluateTopOperatrion(values, operators);
			}

			if (!operators.empty())
				operators.pop();
		}
		else
		{
			while (!operators.empty() && 
				GetPriorityOfOperation(operators.top())	>= GetPriorityOfOperation(expression[i])) {

				EvaluateTopOperatrion(values, operators);
			}

			operators.push(expression[i]);
		}
	}

	while (!operators.empty()) {
		EvaluateTopOperatrion(values, operators);
	}

	return values.top();
}

int main() {
	while(true)
	{
		std::cout << "Input expression to evaluate: \n";
		std::string exp;
		std::cin >> exp;
		//#TODO: ?????????? ????????? ????????? ????? ??????????? 
		std::cout << "Result: " << EvaluateExpression(exp) << std::endl;
		std::cout << "Press ESC to exit or any key to input new expression\n";
		if (_getch() == ESC_KEY) break;
	}	
	return 0;
}