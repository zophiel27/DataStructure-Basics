#include <iostream>
using namespace std;

template <typename T>	// class Stack using linked list
class Stack				// it will have one top pointer 
{						// as it is a list, theres no need for size, it can grow and shrink as much as u want
public:
	// linked list node class that will have data and node pointer to store address of next element
	class Node			
	{					
		T  data;
		Node* next;

		Node()
		{
			data = NULL;
			next = nullptr;
		}
		friend class Stack<T>;
	};

	Stack()
	{
		top = NULL;		// when stack is empty top points to null
	}

	// now implementing the functions of stack ~ ~ ~
	// if u want to add an isFull function it will always return false
	bool isEmpty()
	{
		if (top == NULL)
			return true;
		else
			return false;
	}
	bool push(T value) // inserting at the head, so newNode->next = top
	{
		Node* ptr = new Node;
		ptr->data = value;
		ptr->next = top;

		top = ptr;

		// it will always return true 
		return true;
	}
	bool pop()
	{
		if (!isEmpty())
		{
			Node* temp = top;
			top = top->next;
			delete temp;

			return true;
		}
		else
			return false;
	}
	bool Top(T& value)
	{
		if (!isEmpty())
		{
			value = top->data;
			return true;
		}
		else
			return false;
		
	}
	void display()
	{
		if (isEmpty())
				cout << "\nStack is Empty";
		else
		{
			Node* temp = top;
			cout << "Stack:\n";
			while (temp != NULL)
			{
				cout << temp->data << "\n";
				temp = temp->next;
			}
			cout << "\n";
		}
		
	}
	~Stack()
	{
		Node* temp;
		while (top != NULL)
		{
			temp = top;
			top = top->next;
			delete temp;
		}
	}

private:
	Node* top;

};

int main()
{
	Stack<int> stack;

	stack.push(2);
	stack.push(5);
	stack.push(10);

	stack.display();

	int value;
	if (stack.Top(value))
		cout << "Element at top: " << value;
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
//when there is one or two(?) elements in the stack 