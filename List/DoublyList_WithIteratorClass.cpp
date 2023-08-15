#include <iostream>
using namespace std;

template <typename T>
class list
{

public:
	list()
	{
		head = nullptr; tail = nullptr;
	}
	class node
	{
		T  data;
		node* next;
		node* prev;
		node()
		{
			data = NULL;
			next = prev = nullptr;
		}
		node(T data, node* p, node* q)
		{
			this->data = data;
			next = p;
			prev = q;
		}
		friend class list<T>;
	};

	class listiterator
	{
		private:
			node* current;
			friend class list<T>;
		public:
			//Default Constructor
			listiterator()
			{
				current = nullptr;
			}
			//Parameterized Constructor used in begin and end functions
			listiterator(node* p)
			{
				current = p;
			}
			//Dereference operation to provide access of data to user
			T& operator* () const
			{
				return current->data;
			}
			//Move forward Pre-increment
			listiterator& operator++ ()
			{
				if (current != nullptr)
					this->current = this->current->next;
				return *this;
			}
			//Move forward Post-increment
			listiterator operator++ (int)
			{
				listiterator old = *this;
				++(*this);
				return old;
			}
			//If two iterators point to same node
			bool operator== (const listiterator& rhs) const
			{
				return current == rhs.current;
			}
			//If two iterators point to different nodes
			bool operator!= (const listiterator& rhs) const
			{
				return !(*this == rhs);
			}
	};
	//Iterator returned that points to First Node 
	listiterator begin()
	{
		return head;
	}
	//Iterator returned that points to Last Node  
	listiterator end()
	{
		return nullptr;
	}
	//Functions of Link list
	void  Insert(T value)	// ascending order
	{
		node* curr = head;
		node* pre = nullptr;

		node* n = new node(value, nullptr, nullptr);

		if (head == nullptr)			// if list is empty
		{		
			head = n;
			tail = n;
		}
		else if (curr->data > value)	// if place is before the head
		{
			curr->prev = n;
			n->next = curr;
			head = n;
			n->prev = nullptr;
		}
		else							// if place is in the middle or at the end
		{

			while (curr != nullptr && curr->data < value)
			{
				pre = curr;
				curr = curr->next;
			}
			// for the end
			if (curr == nullptr)	// if a smaller number wasnt found it is placed at the tail
			{
				pre->next = n;		// prev pointre is needed for this
				n->prev = pre;
				n->next = nullptr;
				tail = n;
			}
			//for the middle
			else
			{
				//pre->next = n;
				//n->prev = pre; OR:
				curr->prev->next = n;
				n->prev = curr->prev;
				n->next = curr;
				curr->prev = n;
			}
		}
	}
	// printing ~
	void  printForward()
	{
		node* curr;
		curr = head;
		while (curr != nullptr)
		{
			cout << curr->data << " -> ";
			curr = curr->next;
		}
		cout << "null" << endl;
	}
	void printBackward()
	{
		node* curr;
		curr = tail;
		while (curr != nullptr)
		{
			cout << curr->data << " -> ";
			curr = curr->prev;
		}
		cout << "null" << endl;
	}
	int getSize() const
	{
		int size = 0;
		node* curr = head;
		while (curr != nullptr)
		{
			size++;
			curr = curr->next;
		}
		return size;
	}
	int getMid(int mid) const
	{
		node* curr = head;
		for (int i = 0; i < mid; i++)
		{
			curr = curr->next;
		}
		return curr->data;
	}
	//deleting ~
	void erase(T value)	// deleting a value from list
	{
		node* curr = head;
		node* pre = nullptr;

		while (curr != nullptr && curr->data != value)
		{
			pre = curr;
			curr = curr->next;
		}
		if (curr == head)			// if found at head
		{
			head = head->next;
			head->prev = nullptr;
			delete curr;
		}
		else if (curr != nullptr)	// if it is in the middle
		{
			pre->next = curr->next;
			curr->prev = pre;
			delete curr;
		}
		else						// if its not found
		{
			cout << "Not Found";
		}
	}
	// binary search ~
	bool Search(T value) const
	{
		int low = 0;
		int high = getSize()-1;
		int mid;

		while (low <= high)
		{
			mid = (high + low) / 2;
			
			int midValue = getMid(mid);

			if (midValue == value)
			{
				cout << "\n" << value << " found at index " << mid + 1;
				return true;
			}
			else if (midValue < value)
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
		if (low > high)
		{
			cout << "Not Found";
			return false;
		}
	}
	void insertAtTail(T const element)
	{
		// insert a new node
		node* n = new node;
		n->data = element;
		n->next = nullptr;

		if (tail == NULL)

		{
			tail = n;
			head = n;
		}
		else
		{
			tail->next = n;
			tail = n;
		}
	}
	~list()
	{
		node* temp;
		while (head != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}

	}
private:
	node* head;
	node* tail;
};

// using iterators for the implementation of the following functions
// these functions arent part of any class
template <typename T>
void printList(list<T>& a)
{
	for (list<int>::listiterator i = a.begin(); i != a.end(); i++)	
		cout << (*i) << " -> ";
	cout << "null" << endl;
}
template <typename T>
void unionList(list<T>& a, list<T>& b, list<T>& c)
{
	for (list<int>::listiterator i = a.begin(); i != a.end(); i++)
	{
		c.Insert((*i));
	}
	for (list<int>::listiterator i = b.begin(); i != b.end(); i++)	
	{
		int flag = 0;
		for (list<int>::listiterator j = c.begin(); j != c.end(); j++)
		{
			if ((*i) == (*j))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			c.Insert((*i));
		}
	}

}
template <typename T>
void intersectionList(list<T>& a, list<T>& b, list<T>& c)
{
	for (list<int>::listiterator i = a.begin(); i != a.end(); i++)
	{
		for (list<int>::listiterator j = b.begin(); j != b.end(); j++)
		{
			if ((*i) == (*j))
			{
				c.Insert((*i));
			}
		}
	}
}
template <typename T> 
void bubbleSort(list<T>& a)
{
repeat:
	list<int>::listiterator i = a.begin();
	list<int>::listiterator next = i;
	next++;

	bool flag = 0;
	for (; next != a.end(); next++,i++)
	{
		if (*next < *i)
		{
			T temp = (*i);
			*i = *next;
			*next = temp;
			flag = 1;
		}
		
	}
	if (flag)
		goto repeat;
}

int main()
{
	list <int> a;
	a.Insert(6);
	a.Insert(3);
	a.Insert(-1);
	a.Insert(8);
	a.Insert(10);

	list <int> b;
	b.Insert(5);
	b.Insert(4);
	b.Insert(1);
	b.Insert(-5);
	b.Insert(10);

	cout << "a: ";
	a.printForward();
	cout << "b: ";
	b.printForward();
	cout << endl << "Printing Backwards:\na: ";
	a.printBackward();
	cout << "b: ";
	b.printBackward();
	cout << endl;

	//Print list a using iterator
	cout << "Incrementing list a:\nbefore: ";
	for (list<int>::listiterator i = a.begin(); i != a.end(); i++)	//this is the increment operation
		cout << (*i)++ << " -> ";
	cout << "null" << endl;
	cout << "after: ";
	for (list<int>::listiterator i = a.begin(); i != a.end(); i++)	//displaying
		cout << (*i) << " -> ";
	cout << "null" << endl;

	//Print list b using iterator
	cout << endl << "Decrementing list b: \nbefore: ";
	for (list<int>::listiterator i = b.begin(); i != b.end(); i++)	//decrementing operation
		cout << (*i)-- << " -> ";
	cout << "null" << endl;
	cout << "after: ";
	for (list<int>::listiterator i = b.begin(); i != b.end(); i++)	//displaying
		cout << (*i) << " -> ";
	cout << "null" << endl;

	//restoring a original value since it was incremented
	for (list<int>::listiterator i = a.begin(); i != a.end(); i++)
		(*i)--;
	for (list<int>::listiterator i = b.begin(); i != b.end(); i++)	
		(*i)++;
	cout << "\nDeleting some elements ";
	a.erase(10);
	a.erase(-1);
	cout << endl;
	a.printForward();

	//restoring list a for now
	a.Insert(10);
	a.Insert(-1);
	cout << endl;
	a.printForward();

	//Binary Search
	a.Search(6);
	a.Search(-1);

	cout << endl << endl;
	list <int> c;
	c.insertAtTail(5);
	c.insertAtTail(2);
	c.insertAtTail(4);
	c.insertAtTail(-5);
	c.insertAtTail(10);
	printList(c);
	bubbleSort(c);
	printList(c);

	cout << "\n\nUnion of two lists: \n";
	list <int>x;
	list <int>y;
	list <int>z;

	x.Insert(6);
	x.Insert(3);
	x.Insert(-1);
	x.Insert(0);
	x.Insert(2);

	y.Insert(6);
	y.Insert(2);
	y.Insert(-5);
	y.Insert(-1);
	y.Insert(1);
	
	cout << "x: ";
	printList(x);
	cout << "y: ";
	printList(y);

	cout << "\nUnion: ";
	unionList(x, y, z);
	printList(z);

	cout << "\nIntersection: ";
	list <int>p;
	intersectionList(x, y, p);
	printList(p);

	cout << "\n\n";
	system("pause");
	return 0;
}