#include <iostream>
using namespace std;

bool isMatching(char, char);
bool parenthesisCheck(string);
int precedence(char);
string InfixToPostfix(string);
int EvaluatePostfix(string);
int calculate(int, int, char);

template <typename T>
class Stack
{
	T* ptr;
	int top;
	int size;

public:
	Stack()
	{
		ptr = new T[10];
		size = 10;		
		top = -1;
	}
	Stack(int size)
	{
		ptr = new T[size];
		top = -1;
		this->size = size;
	}
	bool push(T val)	// adds an element in stack
	{
		if (!isFull())
		{
			ptr[++top] = val;
			return true;
		}
		else
			return false;
	}
	bool pop()	// removes top element from stack
	{
		if (!isEmpty())
		{
			top--;
			return true;
		}
		else
			return false;
	}
	bool Top(T& value) // returns the top element but does not remove it from the stack
	{
		if (!isEmpty())
		{
			value = ptr[top];
			return true;
		}
		else
			return false;
	}
	bool isEmpty()
	{
		if (top == -1)
			return true;
		else
			return false;
	}
	bool isFull()
	{
		if (top == size - 1)
			return true;
		else
			return false;
	}
	~Stack()
	{
		delete[] ptr;
	}
};

int main()
{
	string expression;
	cout << "Enter the expression: ";
	cin >> expression;

	Menu:
	int op;
	cout << "\nChoose opertion: ";
	cout << "\n1. Paranthesis Check\n2. Infix to Postfix Conversion\n3. Postfix Evaluation\n4.End\n";
	cin >> op;

	if (op == 1)
	{
		bool flag = parenthesisCheck(expression);
		cout << "\nParenthesis Check:";
		if (flag)
			cout << "\nBalanced\n";
		else
			cout << "\nNot balanced\n";
		goto Menu;
	}
	else if (op == 2)
	{
		string postfix = InfixToPostfix(expression);
		goto Menu;
	}
	else if (op == 3)
	{
		int result = EvaluatePostfix(expression);
		cout << "\nResult is: \n";
		cout << result << endl;
		goto Menu;
	}

	else if (op == 4)
		goto end;
	else
	{
		cout << "\nInvalid Input";
		goto end;
	}
	end:
	cout << "\n";
	system("pause");
	return 0;
}

bool parenthesisCheck(string str)
{
	Stack<char> stack(str.length());	// creating an array stack 
	// a list stack wouldve been better

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{') 
		{
			stack.push(str[i]); // if a left bracket is encountered push it to the stack
		}						// operands and operators are ignored 

		else if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			char value;
			stack.Top(value);
			// if
			// a right bracket is encountered in the expression, it should match 
			// with the top element of the stack to be balanced; and then it is popped
			// else
			// either it doesnt match 
			// or the stack is empty; so we return false
			if (stack.isEmpty() || !isMatching(value, str[i]))
			{
				return false;
			}
			else
			{
				stack.pop();
			}
		}
	}
	// If *stack* is not empty after traversal then its not balanced
	// that is there were extra left brackets that were not popped
	if (!stack.isEmpty())
		return false;
	else
		return true;

}
bool isMatching(char ch1, char ch2)
{
	if (ch1 == '(' && ch2 == ')')
		return true;
	else if (ch1 == '{' && ch2 == '}')
		return true;
	else if (ch1 == '[' && ch2 == ']')
		return true;
	else
		return false;
}

int precedence(char chr) 
{
	if (chr == '+' || chr == '-')
		return 1;

	else if (chr == '*' || chr == '/')
		return 2;

	else if (chr == '^')
		return 3;

	else
		return 0;
}
string InfixToPostfix(string infix)
{
	string postfix ;

	Stack<char> stack;

	//cout << infix.length();

	for(int i=0; i<infix.length(); i++) //while not end of expression, get next symbol
	{
		// if operand encountered then keep adding in the expression
		if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= '0' && infix[i] <= '9'))
		{
			postfix += infix[i];
		}
		// if opening bracket encountered then push in the stack
		else if (infix[i] == '(')
		{
			stack.push(infix[i]);
		}
		// if closing bracket encountered then keep popping from stack until opening bracket is not encountered
		else if (infix[i] == ')')
		{
			char value;
			stack.Top(value);
			while (value != '(') 
			{
				postfix += value;
				stack.pop();
				stack.Top(value);
			}
			stack.pop();	// pop opening bracket from stack as well
		}
		// if operator encountered
		else
		{
			char value;
			stack.Top(value);
			while (!stack.isEmpty() && precedence(infix[i]) <= precedence(value))
			{
				postfix += value;
				stack.pop();
				stack.Top(value);
			}
			stack.push(infix[i]);
			// if stack is empty or priority of incoming operator is higher that that of top,
			// push on stack
			// else pop operators from stack and push on postfix
		}
	}
	// pop all the remaining elements from the stack
	while (!stack.isEmpty()) 
	{
		char val;
		stack.Top(val);
		postfix += val;
		stack.pop();
	}

	cout << "\nPostfix is : " << postfix << endl; //it will print postfix conversion  
	return postfix;
}

int EvaluatePostfix(string expression)
{
	int result = 0;
	string postfix = InfixToPostfix(expression);
//	string postfix = expression;

	Stack<int> stack(postfix.length());

	// in the postfix expression we have operators and operands only

	for (int i = 0; i < postfix.length(); i++)
	{
		// if operand, push on stack
		if ( postfix[i] >= '0' && postfix[i] <= '9' )
		{
			stack.push((int(postfix[i]) - '0'));
			// first convert char into int using this formula ^
		}
		//if operator, pop operands(two since we are only considering binary ops rn) from stack and perform the operation
		else
		{
			// assuming all operations are binary + - * / ^
			int val1;
			int val2;
			stack.Top(val1);
			stack.pop();
			stack.Top(val2);
			stack.pop();

			result= calculate(val1, val2, postfix[i]);

			stack.push(result);

		}
	}

	return result;
}
int calculate(int a, int b, char op)
{
	if (op == '+')
	{
		return a + b;
	}
	else if (op == '-')
	{
		return a - b;
	}
	else if (op == '/')
	{
		return a / b;
	}
	else if (op == '*')
	{
		return a * b;
	}
//	else if(op == '^')
//        {
//		return pow(b, a);
//	}

}
