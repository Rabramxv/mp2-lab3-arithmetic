// объявление функций и классов для вычисления арифметических выражений
#include <string>
#include "stack.h"
#include "vector"
#include <iostream>
#include <map>
#include <cctype>
using namespace std;


class TArithmeticExpression {
	string infix;
	vector <string> postfix;
	vector <string> lexems;
	map <char, int> priority;
	vector <std::pair <string, double>> operands_value;
	char GetType(char a) {
		if (isalpha(a)) {
			return '0';
		}
		else if ((isdigit(a)) || (a == '.')) {
			return '1';
		}
		else if ((a == '(') || (a == ')') || (a == '*') || (a == '/') || (a == '+') || (a == '-')) {
			return '2';
		}
		else {
			return '3';
		}
	}
	bool Check()  {
		int flag_bracket = 0, flag_operators = 0,
			flag_points = 0;
		if ((GetType(infix[0]) == '2' && infix[0] != '(' && infix[infix.size() - 1] != ')') ||
			(GetType(infix[infix.size() - 1]) == '2' && infix[0] != '(' && infix[infix.size() - 1] != ')') ||
			(infix[0] == '.') || (infix[infix.size() - 1] == '.')) {
			return false;
		}

		for (int i = 0; i < infix.size(); i++) {
			if (GetType(infix[i]) == '3') {
				return false;
			}
			if (flag_bracket < 0) {
				return false;
			}
			if (infix[i] == '(') {
				if (i > 0 && (i < infix.size() - 2)) {
					if (GetType(infix[i - 1]) != '2' || (GetType(infix[i + 1]) == '2' && (infix[i + 1] != ')'))) {
						return false;
					}
				}
				flag_bracket += 1;
			}
			else if (infix[i] == ')') {
				flag_bracket -= 1;
			}
			else if (GetType(infix[i]) == '0') {
				flag_operators = 0;
			}
			else if (GetType(infix[i]) == '2') {
				if (flag_operators > 0) {
					return false;
				}
				if (flag_points > 1) {
					return false;
				}
				flag_points = 0;
				flag_operators = 1;
			}
			else if (infix[i] == '.') {
				if (GetType(infix[i - 1]) != '1') {
					return false;
				}
				flag_points += 1;
			}
			else if (GetType(infix[i]) == '1') {
				if (i != 0) {
					if (GetType(infix[i - 1]) == '0') {
						return false;
					}
				}
				flag_operators = 0;
			}
		}
		if (flag_bracket > 0) {
			return false;
		}
	}
	void Parse() {
		if (!Check()) {
			throw "Incorrect input";
		}
		else {
			string token(1, infix[0]);
			int p = 1, k = 0, prevType = GetType(infix[0]);
			while (p < infix.size()) {
				int x = GetType(infix[p]);
				if ((prevType != x) || (prevType == '2') && (x == '2')) {
					lexems.push_back(token);
					token = string(1, infix[p]);
					k++;
				}
				else {
					token += infix[p];
				}
				prevType = x;
				p++;
			}
			lexems.push_back(token);
		}

	};
	void ToPostfix() {
		Parse();
		TVectorStack<string> st;
		TVectorStack <string> operator_stack;
		for (int i = 0; i < lexems.size(); i++) {
			string item = lexems[i];
			if (GetType(item[0]) == '0' || GetType(item[0]) == '1') {
				postfix.push_back(item);
			}
			else if (GetType(item[0]) == '2') {
				if (item == "(") {
					operator_stack.Push(item);
				}
				else if (item == ")") {
					string last = operator_stack.Pop();
					while (last != "(") {
						postfix.push_back(last);
						last = operator_stack.Pop();
					}
				}
				else {
					if (operator_stack.IsEmpty()) {
						operator_stack.Push(item);
					}
					else {
						if (priority[item[0]] > priority[operator_stack.LastElem()[0]]) {
							operator_stack.Push(item);
						}
						else {
							while (!operator_stack.IsEmpty()) {
								if (priority[item[0]] <= priority[operator_stack.LastElem()[0]] && item != "(" && item != ")") {
									postfix.push_back(operator_stack.Pop());
								}
								else {
									break;
								}
							}
							operator_stack.Push(item);
						}
					}
				}
			}
		}
		if (!operator_stack.IsEmpty()) {
			while (!operator_stack.IsEmpty()) {
				postfix.push_back(operator_stack.Pop());
			}
		}
	}
public:
	TArithmeticExpression(string infix): infix(infix) {
		priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
		ToPostfix();
	}
	string GetInfix() const {
		return infix;
	}
	string GetPostfix() const {
		string res;
		for (int i = 0; i < postfix.size(); i++) {
			res += postfix[i];
		}
		return res;
	}
	double* Get_Elem(string item) {
		for (int i = 0; i < operands_value.size(); i++) {
			if (operands_value[i].first == item) {
				return &(operands_value[i].second);
			}
		}
		return nullptr;
	}
	double Get_Operand(string item) {
		double* a = Get_Elem(item);
		if (a == nullptr) {
			double b;
			cout << "Введите значение " << item << ": ";
			cin >> b;
			operands_value.push_back(std::pair <string, double>(item, b));
			return b;
		}
		return *a;
	}
	double Calculate() {
		TVectorStack <string> operators;
		TVectorStack <double> numbers;
		for (int i = 0; i < postfix.size(); i++) {
			string item = postfix[i];
			char type_elem = GetType(item[0]);
			if (type_elem == '0') {
				double c = Get_Operand(item);
				numbers.Push(c);
			}
			else if (type_elem == '1') {
				numbers.Push(stod(item));
			}
			else if (type_elem == '2') {
				double first_num = numbers.Pop();
				double second_num = numbers.Pop();
				double result;
				if (item == "+") {
					result = first_num + second_num;
				}
				else if (item == "-") {
					result = second_num - first_num;
				}
				else if (item == "*") {
					result = first_num * second_num;
				}
				else {
					if (second_num == 0 || first_num == 0) {
						throw "Division by zero";
					}
					result = second_num / first_num;
				}
				numbers.Push(result);
			}
		}
		return numbers.Pop();
	}
};
