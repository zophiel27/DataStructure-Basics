#include <iostream>
using namespace std;

template <typename T>
class Queue
{
public:

	class Stack
	{
		friend class Queue<T>;

		class Node
		{
			T  data;
			Node* next;

			Node()
			{
				data = NULL;
				next = nullptr;
			}
			friend class Stack;
		};

		Stack()
		{
			top = NULL;
		}
		bool Empty()
		{
			if (top == NULL)
				return true;
			else
				return false;
		}
		bool push(T value)//insert at head
		{
			Node* ptr = new Node;
			ptr->data = value;
			ptr->next = top;

			top = ptr;

			return true;
		}
		bool pop()//delete at head
		{
			if (!Empty())
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
			if (!Empty())
			{
				value = top->data;
				return true;
			}
			else
				return false;

		}
		void display()
		{
			Node* temp = top;
			cout << "Queue:\n";
			while (temp != NULL)
			{
				cout << temp->data << "\n";
				temp = temp->next;
			}
			cout << "\n";

		}
		Node* top;

	};

	Queue()
	{
		stack = new Stack();
	}
	bool enqueue(T value)	// insert at tail
	{
		stack->push(value);

		return true;
	}
	bool dequeue()			// delete is interesting
	{
		if (!stack->Empty())
		{
			// first you make a dummy stack and transfer all the values from main stack to it
			Stack* dummyS = new Stack();

			while (!stack->Empty())
			{
				T value;
				stack->Top(value);
				dummyS->push(value);
				stack->pop();
			}
			// so the last value in main stack comes on top
			// then we can just pop that value
			dummyS->pop();

			// transfer all the elements back to the main stack
			while (!dummyS->Empty())
			{
				T value;
				dummyS->Top(value);
				stack->push(value);
				dummyS->pop();
			}
			return true;
		}
		return false;
	}
	void display()
	{
		if (stack->Empty())
			cout << "Queue is Empty\n";
		else
		{
			stack->display();
		}
	}
private:
	Stack* stack;

};
int main()
{
	Queue<int> Queue;

	Queue.enqueue(2);
	Queue.enqueue(5);
	Queue.enqueue(10);
	Queue.enqueue(15);

	Queue.display();

	if (Queue.dequeue())
		cout << "Popped " << endl;
	else
		cout << "Can't Pop as Queue is Empty\n";

	Queue.enqueue(3);
	Queue.enqueue(6);
	Queue.display();
	if (Queue.dequeue())
		cout << "Popped " << endl;
	else
		cout << "Can't Pop as Queue is Empty\n";
	if (Queue.dequeue())
		cout << "Popped " << endl;
	else
		cout << "Can't Pop as Queue is Empty\n";
	Queue.display();

	cout << "\n\n";
	system("pause");
	return 0;
}