#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class minHeap
{
public:
	minHeap() // default constructor
	{

	}
	minHeap(T* arr, int N, int build) // parameterized constructor that will take an array of random numbers and its size in parameters and initialize the heap with random values.It will call the buildMinHeap() function to convert the random values into a heap.
	{
		v.push_back(NULL);
		for (int i = 0; i < N; i++)
		{
			v.push_back(arr[i]);
		}
		if (build)
			buildMinHeap();
	}
	void buildMinHeap() // It will generate heap from random values stored in the object
	{
		int N = v.size();
		T* tempArr = new T[N];
		for (int i = 0; i < N; i++)
		{
			tempArr[i] = v[i];
		}
		v.clear();
		for (int i = 0; i < N; i++)
		{
			insert(tempArr[i]);
		}
	}
	void insert(const T& x) // Inserts the key value in the heap array such that, the resultant heap tree is a complete binary tree and it follows min heap order
	{
		v.push_back(x);
		bubble_up(v.size() - 1); //sending the index of the new element added
	}
	bool isEmpty() const // returns true if it is empty
	{
		if (v.size() == 0)
			return true;
		return false;
	}
	const T& getMin() const //returns minimum value this operation should be performed in O(1)
	{
		return v.at(1);
	}
	void deleteMin() //always from root node
	{
		//swap root node with last leaf node
		T temp = v.at(1);
		v.at(1) = v.at(v.size() - 1);
		v.at(v.size() - 1) = temp;

		//delete the leaf node
		v.pop_back();

		//bubble down from root
		bubble_down(1);

	}
	bool deleteAll(T key) //remove all occurrences of key value from the heap and update the heap accordingly
	{
		for (int i = 1; i < v.size(); i++)
		{
			if (key == v.at(i))
			{
				T temp = v.at(i);
				v.at(i) = v.at(v.size() - 1);
				v.at(v.size() - 1) = temp;
				v.pop_back();
				bubble_up(i);
				bubble_down(i);
				return true;
			}
		}
		return false;
	}
	void display()
	{
		for (int i = 0; i < v.size(); i++)
		{
			cout << v.at(i) << " ";
		}
		cout << endl;
	}
private:
	vector<T> v;
	void bubble_up(int i) // A recursive method to heapify a subtree with the root at given index. It maintains heap property during insertion
	{
		if (i == 1)
			return;
		else
		{
			if (v.at(i) < v.at(i / 2))
			{
				T temp = v.at(i);
				v.at(i) = v.at(i / 2);
				v.at(i / 2) = temp;
				bubble_up(i / 2);		// as it goes to the parent after comparing
				// send recursive call only if it swaps 
			}
		}
	}
	void bubble_down(int i) // It maintains heap property during deletion
	{
		if (i * 2 > v.size() || i * 2 + 1 > v.size()) // if they have reached the leaf node
			return;
		else
		{
			if (2 * i < v.size() && 2 * i + 1 < v.size()) // if both children exist
			{
				if (v.at(2 * i) < v.at(2 * i + 1)) // it will CHECK right AND left child based on which one is smaller
				{
					if (v.at(2 * i) < v.at(i))  // THEN it compares that (smaller) child with the current node
					{
						T temp = v.at(i);		// if yes then it swaps
						v.at(i) = v.at(2 * i);
						v.at(2 * i) = temp;
						bubble_down(2 * i);
					}
				}
				else  // otherwise if the other child was smaller then it would have swapped with that if needed
				{
					if (v.at(2 * i + 1) < v.at(i))
					{
						T temp = v.at(i);
						v.at(i) = v.at(2 * i + 1);
						v.at(2 * i + 1) = temp;
						bubble_down(2 * i + 1);
					}
				}
			}
			else
			{
				if (v.at(2 * i) < v.at(i)) // since heap is always a complete tree, if both children dont exist, the only
				{							//other possibility is that it has a left child, so we compare with that
					T temp = v.at(i);
					v.at(i) = v.at(2 * i);
					v.at(2 * i) = temp;
					bubble_down(2 * i);
				}
			}
		}
	}
};
template <typename T>
class maxHeap
{
public:
	maxHeap() // default constructor
	{

	}
	maxHeap(T* arr, int N, int build)
	{
		v.push_back(NULL);
		for (int i = 0; i < N; i++)
		{
			v.push_back(arr[i]);
		}
		if (build)
			buildMaxHeap();
	}
	void buildMaxHeap() // It will generate heap from random values stored in the object
	{
		int N = v.size();
		T* tempArr = new T[N];
		for (int i = 0; i < N; i++)
		{
			tempArr[i] = v[i];
		}
		v.clear();
		for (int i = 0; i < N; i++)
		{
			insert(tempArr[i]);
		}
	}
	void insert(const T& x)
	{
		v.push_back(x);
		bubble_up(v.size() - 1);
	}
	bool isEmpty() const // returns true if it is empty
	{
		if (v.size() == 0)
			return true;
		return false;
	}
	const T& getMax() const
	{
		return v.at(1);
	}
	void deleteMax() //always from root node
	{
		//swap root node with last leaf node
		T temp = v.at(1);
		v.at(1) = v.at(v.size() - 1);
		v.at(v.size() - 1) = temp;

		//delete the leaf node
		v.pop_back();

		//bubble down
		bubble_down(1);

	}
	bool deleteAll(T key) //remove all occurrences of key value from the heap and update the heap accordingly
	{
		for (int i = 1; i < v.size(); i++)
		{
			if (key == v.at(i))
			{
				T temp = v.at(i);
				v.at(i) = v.at(v.size() - 1);
				v.at(v.size() - 1) = temp;
				v.pop_back();
				bubble_up(i);
				bubble_down(i);
				return true;
			}
		}
		return false;
	}
	void display()
	{
		for (int i = 0; i < v.size(); i++)
		{
			cout << v.at(i) << " ";
		}
		cout << endl;
	}
private:
	vector<T> v;
	void bubble_up(int i)
	{
		if (i == 1)
			return;
		else
		{
			if (v.at(i) > v.at(i / 2))
			{
				T temp = v.at(i);
				v.at(i) = v.at(i / 2);
				v.at(i / 2) = temp;
				bubble_up(i / 2);		// it goes to the parent after comparing
				// send recursive call only if it swaps 
			}
		}
	}
	void bubble_down(int i) // maintains heap property during deletion
	{
		if (i * 2 > v.size() || i * 2 + 1 > v.size()) // if they have reached the leaf node
			return;
		else
		{
			if (2 * i < v.size() && 2 * i + 1 < v.size()) // if both children exist
			{
				if (v.at(2 * i) > v.at(2 * i + 1)) // it will CHECK right and left child based on which one is smaller
				{
					if (v.at(2 * i) > v.at(i))  // THEN it compares that (smaller) child with than the current node
					{
						T temp = v.at(i);		// if yes then it swaps
						v.at(i) = v.at(2 * i);
						v.at(2 * i) = temp;
						bubble_down(2 * i);
					}
				}
				else  // otherwise if the other child was smaller then it would have swapped with that if needed
				{
					if (v.at(2 * i + 1) > v.at(i))
					{
						T temp = v.at(i);
						v.at(i) = v.at(2 * i + 1);
						v.at(2 * i + 1) = temp;
						bubble_down(2 * i + 1);
					}
				}
			}
			else
			{
				if (v.at(2 * i) > v.at(i)) // since heap is always a complete tree, if both children dont exist, the only
				{							//other possibility is that it has a left child, so we compare with that
					T temp = v.at(i);
					v.at(i) = v.at(2 * i);
					v.at(2 * i) = temp;
					bubble_down(2 * i);
				}
			}
		}
	}
};
template <typename T>
void heapSort(T* arr, int size, int sorting_order)
{
	if (sorting_order == 1)// descending order
	{
		// heapify min heap
		minHeap<int> heap_2(arr, size, 1);

		for (int i = size - 1; i >= 0; i--)
		{
			// swap root node with last leaf node
			/*int temp = arr[0];
			arr[0] = arr[i];
			arr[i] = temp;*/

			//save the value from the root node
			arr[i] = heap_2.getMin();

			//deleteMin deletes it and also bubbles down
			heap_2.deleteMin();
		}
	}
	else if (sorting_order == 0) //ascending order
	{
		maxHeap<int> heap_3(arr, size, 1);

		for (int i = size - 1; i >= 0; i--)
		{
			// swap root node with last leaf node
			/*int temp = arr[0];
			arr[0] = arr[i];
			arr[i] = temp;*/

			//save the value from the root node
			arr[i] = heap_3.getMax();

			//deleteMax deletes it and also bubbles down
			heap_3.deleteMax();
		}
	}
}
void heapify(int arr[], int n, int i) //recursive heapify function
{
	// Find largest among root, left child and right child
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// left > n and right > n are the base cases
	if (left < n && arr[left] > arr[largest])
		largest = left;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	// Swap and continue heapifying if root is not largest
	if (largest != i)
	{
		int x = arr[i];
		arr[i] = arr[largest];
		arr[largest] = x;
		heapify(arr, n, largest);
	}
}
void heapSort(int arr[], int n)
{
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Heap sort
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);

		// Heapify root element to get highest element at root again
		heapify(arr, i, 0);
	}
}
int main()
{
	int array[] = { 20, 40, 50, 10, 80, 30, 90 };
	const int N = 7;
	int order;
	minHeap<int> heap(array, N, 1);
	cout << "Min Heap: \n";
	heap.display();

	// deleting first, second & third minimum in min heap
	cout << "Deleting ";
	for (int i = 0; i < 3; ++i)
	{
		cout << heap.getMin() << " ";
		heap.deleteMin();
	}
	cout << endl; heap.display();

	cout << "\nHeap Sort:\nWhat order do you want to sort the following array in? (0 for ascending and 1 for descending)\n";
	cin >> order;
	cout << "\nBefore: ";
	for (int i = 0; i < N; i++)cout << array[i] << " "; cout << endl;
	heapSort(array, N, order);
	cout << "After:  ";
	for (int i = 0; i < N; i++)cout << array[i] << " "; cout << endl;

	cout << "\n\n";
	system("pause");
	return 0;
}