#include <iostream>
using namespace std;

template <typename T>
class Queue				//Queue using list 
{
public:
	
	class Node
	{
		T  data;
		Node* next;

		Node()
		{
			data = NULL;
			next = nullptr;
		}
		friend class Queue<T>;
	};

	Queue()
	{
		front = rear = NULL;
	}
	bool isEmpty()
	{
		if (front == NULL)
			return true;
		else
			return false;
	}
	bool enqueue(T value)	// insert at tail
	{	
			Node* ptr = new Node;
			ptr->data = value;
			ptr->next = nullptr;

			if (front == NULL)
			{
				front = ptr;
				rear = ptr;
			}
			else
			{
				rear->next = ptr;
				rear = ptr;
			}

		// will always return true 
		return true;
	}
	bool dequeue()			// delete from head
	{
		if (!isEmpty())
		{
			Node* temp = front;
			front = front->next;
			delete temp;

			return true;
		}
		else
			return false;
	}
	bool atFront(T& value)
	{
		if (!isEmpty())
		{
			value = front->data;
			return true;
		}
		else
			return false;
	}
	bool atRear(T& value)
	{
		if (!isEmpty())
		{
			value = rear->data;
			return true;
		}
		else
			return false;
	}
	void display()
	{
		if (isEmpty())
			cout << "\nQueue is Empty";
		else
		{
			Node* temp = front;
			cout << "Queue:\n";
			while (temp != NULL)
			{
				cout << temp->data << "\n";
				temp = temp->next;
			}
			cout << "\n";
		}

	}
	~Queue()
	{
		Node* temp;
		while (front != NULL)
		{
			temp = front;
			front = front->next;
			delete temp;
		}
	}

private:
	Node* front;
	Node* rear;

};
int main()
{
		Queue<int> Queue;
	
		Queue.enqueue(2);
		Queue.enqueue(5);
		Queue.enqueue(10);
		Queue.enqueue(15);
	
		Queue.display();
	
		int value;
		if (Queue.atFront(value))
			cout << "Element at atFront: " << value;
		else
			cout << "\nQueue is Empty";
	
		if (Queue.dequeue())
			cout << "\nPopped " << value;
		else
			cout << "\nCan't Pop as Queue is Empty";
	
		if (Queue.atFront(value))
			cout << "\nElement at atFront: " << value;
		else
			cout << "\nQueue is Empty";
	
		if (Queue.dequeue())
			cout << "\nPopped " << value;
		else
			cout << "\nCan't Pop as Queue is Empty";
	
		if (Queue.atFront(value))
			cout << "\nElement at atFront: " << value;
		else
			cout << "\nQueue is Empty";
	
		if (Queue.dequeue())
			cout << "\nPopped " << value;
		else
			cout << "\nCan't Pop as Queue is Empty";
	
		if (Queue.atFront(value))
			cout << "\nElement at atFront: " << value;
		else
			cout << "\nQueue is Empty";
	
		if (Queue.dequeue())
			cout << "\nPopped " << value;
		else
			cout << "\nCan't Pop as Queue is Empty";
	
		cout << "\n\n";
		system("pause");
		return 0;
}