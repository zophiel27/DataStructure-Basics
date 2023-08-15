#include <iostream>
using namespace std;

template <typename T>	//Array Stack
class Stack
{
	T* ptr;
	int top;
	int size;

public:
	Stack()
	{
		ptr = new T[10];//acc to Q default constructor
		size = 10;		//creates stack of maxSize 10
		top = -1;
	}
	Stack(int size)
	{
		ptr = new T[size];
		this->size = size;
		top = -1;
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
	bool pop()			// removes top element from stack
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
	int ssize = 3;
	Stack<char> stack(ssize);

	if (!stack.push('R'))
		cout << "Can't push as stack is full";
	if (!stack.push('O'))
		cout << "\nCan't push as stack is full";
	if (!stack.push('X'))
		cout << "\nCan't push as stack is full";
	if (!stack.push('Z'))
		cout << "\nCan't push as stack is full";
	cout << endl;

	char value;
	if (stack.Top(value))
		cout << "\nElement at top: " << value;
	else
		cout << "\nStack is Empty";

	if (stack.pop())
		cout << "\nPopped " << value;
	else
		cout << "\nCan't Pop as Stack is Empty";

	if (stack.Top(value))
		cout << "\nElement at top: " << value;
	else
		cout << "\nStack is Empty";

	if (stack.pop())
		cout << "\nPopped " << value;
	else
		cout << "\nCan't Pop as Stack is Empty";

	if (stack.Top(value))
		cout << "\nElement at top: " << value;
	else
		cout << "\nStack is Empty";

	if (stack.pop())
		cout << "\nPopped " << value;
	else
		cout << "\nCan't Pop as Stack is Empty";

	if (stack.Top(value))
		cout << "\nElement at top: " << value;
	else
		cout << "\nStack is Empty";

	if (stack.pop())
		cout << "\nPopped " << value;
	else
		cout << "\nCan't Pop as Stack is Empty";

	cout << "\n\n";
	system("pause");
	return 0;
}