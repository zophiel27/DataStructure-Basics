#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <typename T>
struct node
{
	T data;
	node<T>* left;
	node<T>* right;
	node()
	{
		data = NULL;
		left = NULL;
		right = NULL;
	}
	node(T val)
	{
		data = val;
		left = NULL;
		right = NULL;
	}
};

template <typename T>
class BST
{
private:
	node<T>* root;
public:
	BST()
	{
		root = NULL;
	}
	bool insert(T key)	// always as leaf node
	{
		//create a node with key value
		node<T>* n = new node<T>(key);

		//assign a current and prev pointer; start from root
		node<T>* curr = root;
		node<T>* prev = NULL;

		if (curr == NULL)	// if tree is empty
		{
			root = n;
		}
		else
		{
			while (curr != NULL)
			{
				if (curr->data == key)	// if key already exists
					return false;

				else if (key < curr->data)	// if key is smaller than data then move to left
				{
					prev = curr;
					curr = curr->left;
				}
				else	// otherwise move to right
				{
					prev = curr;
					curr = curr->right;
				}
			}
			if (key < prev->data)
			{
				prev->left = n;
			}
			else
				prev->right = n;
		}
	}
	node<T>* search(node<T>*& prev, T key)
	{
		node<T>* curr = root;
		if (curr == NULL)
		{
			//cout << "Empty\n";
			return NULL;
		}
		while (curr != NULL)
		{
			if (key == curr->data)
			{
				//cout << "Found\n";
				return curr;
			}
			else if (key < curr->data)
			{
				prev = curr;
				curr = curr->left;
			}
			else
			{
				prev = curr;
				curr = curr->right;
			}
		}
		//cout << "Not Found\n";
		return NULL;
	}
	bool deleteNode(T key)
	{
		node<T>* prev = NULL;
		if (root == NULL || !search(prev, key))				// case1 = empty tree or key not found
		{
			return false;
		}
		else
		{
			node<T>* curr = search(prev, key); //searches for node and updates prev

			if (curr->left == NULL && curr->right == NULL)// case2 = found at leaf node
			{
				if (curr == prev->right)
				{
					prev->right = NULL;
				}
				else
				{
					prev->left = NULL;
				}
				delete curr;
			}
			else if (curr->left != NULL && curr->right == NULL)// case3 = non leaf node with left child
			{
				if (curr == prev->right)
				{
					prev->right = curr->left;
				}
				else
				{
					prev->left = curr->left;
				}
				delete curr;
			}
			else if (curr->right != NULL && curr->left == NULL)// case3 = non leaf node with right child
			{
				if (curr == prev->right)
				{
					prev->right = curr->right;
				}
				else
				{
					prev->left = curr->right;
				}
				delete curr;
			}
			else	// case4 = non leaf node with both left n right children
			{
				//search for the predecessor; it is in the left subtree, the rightmost element
				node<T>* p = curr->left; // so u go left once and then
				while (p->right != NULL) // keep going to the right
				{
					prev = p;
					p = p->right;
				}
				//swap curr with the predecessor data
				int temp = curr->data;
				curr->data = p->data;
				p->data = temp;

				if (curr->left == p) // incase it doesnt have a right most element and predecessor is in left part
				{
					curr->left = p->left;
					delete p;
				}
				else // if right most element found 
				{
					prev->right = p->left;
					delete p;
				}
			}
		}
	}
	void inorderPrintR()	// using this function to call the recursive function of print
	{					// because we cant pass root from main
		if (root != NULL)
		{
			printInorder(root);
			cout << endl;
		}
		else
			cout << "Empty Tree\n";
	}
	void printInorder(node<T>* curr) 	// LVR traversal
	{
		if (curr == NULL)
		{
			return;
		}
		else
		{
			printInorder(curr->left);
			cout << curr->data << " ";
			printInorder(curr->right);
		}
	}
	void preorderPrintR()	// VLR traversal
	{
		printPreorder(root);
		cout << endl;
	}
	void printPreorder(node<T>* ptr) const
	{
		if (ptr == NULL)
			return;
		else
		{
			cout << ptr->data << " ";
			printPreorder(ptr->left);
			printPreorder(ptr->right);
		}
	}
	void postorderPrintR()	// LRV traversal
	{
		printPostorder(root);
		cout << endl;
	}
	void printPostorder(node<T>* curr) const
	{
		if (curr == NULL)
			return;
		else
		{
			printPostorder(curr->left);
			printPostorder(curr->right);
			cout << curr->data << " ";
		}
	}
	void inorderPrint()
	{
		stack<node<T>*> stack;

		// start from the root node
		node<T>* curr = root;

		if (curr == NULL)
		{
			cout << "Tree is Empty\n";
			return;
		}

		while (!stack.empty() || curr != NULL)
		{
			// if the current node exists, push it into the stack and move to its left child
			if (curr != NULL)
			{
				stack.push(curr);
				curr = curr->left;
			}
			else
			{
				// otherwise, if the current node is null, pop an element from the stack,
				// print it, and finally set the current node to its right child
				curr = stack.top();
				stack.pop();
				cout << curr->data << " ";

				curr = curr->right;
			}
		}
		cout << endl;
	}
	void preorderPrint()
	{
		if (root == nullptr)
		{
			cout << "Tree is Empty\n";
			return;
		}

		stack<node<T>*> stack;
		stack.push(root);

		while (!stack.empty())
		{
			// pop a node from the stack and print it
			node<T>* curr = stack.top();
			stack.pop();

			cout << curr->data << " ";

			// push the right child first and then the left child (LIFO) so it will check the left first in the next iteration
			if (curr->right != NULL)
			{
				stack.push(curr->right);
			}
			if (curr->left != NULL)
			{
				stack.push(curr->left);
			}
		}
		cout << endl;
	}
	void postorderPrint()
	{
		if (root == nullptr)
		{
			cout << "Tree is Empty\n";
			return;
		}
		// will be done using two stacks
		stack<node<T>*> s1;
		s1.push(root);

		stack<T> s2;

		while (!s1.empty())
		{
			// pop first stack and push data into the second stack
			node<T>* curr = s1.top();
			s1.pop();

			s2.push(curr->data);

			// push the left and then right child of the popped node into the stack
			if (curr->left != NULL)
			{
				s1.push(curr->left);
			}

			if (curr->right != NULL)
			{
				s1.push(curr->right);
			}
		}

		// print second stack
		while (!s2.empty())
		{
			cout << s2.top() << " ";
			s2.pop();
		}
		cout << endl;
	}
	void levelOrderPrint() const	// Level Order traversal
	{
		if (root != NULL)
		{
			queue<node<T>*> queue;
			node<T>* n = root;
			// push root
			queue.push(n);

			while (!queue.empty())
			{
				// print front node
				n = queue.front();
				cout << n->data << " ";

				// if node has a left or right child (FIFO) so left first then right
				if (n->left != NULL)
				{
					queue.push(n->left);
				}
				if (n->right != NULL)
				{
					queue.push(n->right);
				}
				queue.pop();
			}
			cout << endl;
		}
		else
			cout << "Empty Tree\n";
	}
	bool isBST()
	{
		if (root == NULL)
		{
			cout << "Empty Tree\n";
			return false;
		}
		else
		{
			node<T>* prev = NULL;
			if (is_BST(root, prev))
				return true;
			else
				return false;
		}
	}
	bool is_BST(node<T>* curr, node<T>* prev)
	{
		if (curr == NULL)
			return 1;

		if (!is_BST(curr->left, prev))
			return 0;

		if (prev != NULL && curr->data <= prev->data)
			return 0;

		prev = curr;

		return is_BST(curr->right, prev);

		return 1;
	}
	int levels() // height of BST
	{
		return levelsR(root);
	}
	int levelsR(node<T>* curr)
	{
		if (curr == NULL)
			return 0;
		else
		{
			int hl = levelsR(curr->left);
			int hr = levelsR(curr->right);

			if (hl > hr)
				return hl + 1;
			else
				return hr + 1;
		}
	}
	int countNodes() //iteratively using stack
	{
		int count = 0;
		if (root == nullptr)
		{
			return count;
		}
		stack<node<T>*> s;
		s.push(root);

		while (!s.empty())
		{
			node<T>* curr = s.top();
			s.pop();
			count++;

			if (curr->right != NULL)
			{
				s.push(curr->right);
			}

			if (curr->left != NULL)
			{
				s.push(curr->left);
			}
		}
		return count;
	}
	int countNodesR()	//recursively using LVR traversal
	{
		int Count = 0;
		LVR(Count, root);
		return Count;
	}
	void LVR(int& Count, node<T>* curr) const
	{
		if (curr == NULL)
		{
			return;
		}
		else
		{
			LVR(Count, curr->left);
			LVR(Count, curr->right);
			Count++;
		}
	}
	int pathCount()	//counts leaf nodes using VLR
	{
		int Count = 0;
		VLR(Count, root);
		return Count;
	}
	void VLR(int& Count, node<T>* curr) const
	{
		if (curr == NULL)
		{
			return;
		}
		if (curr->left == NULL && curr->right == NULL)
		{
			Count++;
		}
		else
		{
			VLR(Count, curr->left);
			VLR(Count, curr->right);
		}
	}
	void pathSum(vector<T>& sums)
	{
		int sum = 0;
		path_Sum(sum, sums, root);
	}
	void path_Sum(T sum, vector<T>& sums, node<T>* curr)
	{
		if (curr == NULL)
		{
			return;
		}
		if (curr->left == NULL && curr->right == NULL)
		{
			sums.push_back(sum + curr->data);
			return;
		}
		else
		{
			sum = sum + curr->data;
			path_Sum(sum, sums, curr->left);
			path_Sum(sum, sums, curr->right);

		}
	}
	void mirrorBST() //all right sub trees get exchanged by left sub trees for all the nodes(not just the root node)
	{
		if (root == NULL)
		{
			cout << "Empty Tree\n";
			return;
		}
		else
		{
			mirror_BST(root);
		}
	}
	void mirror_BST(node<T>* curr)
	{
		if (curr == NULL)
			return;
		else
		{
			mirror_BST(curr->left);
			mirror_BST(curr->right);
			node<T>* temp = curr->left;
			curr->left = curr->right;
			curr->right = temp;
		}
	}
	bool updateKey(T key1, T key2)
	{
		if (deleteNode(key1))
		{
			insert(key2);
			return true;
		}
		else
		{
			cout << "Node doesnt exist\n";
			return false;
		}
	}
	int width() // number of nodes in the fullest level of the tree
	{
		int maxWidth = 0;
		for (int i = 0; i < levelsR(root); i++) // checking leaf nodes of all levels 
		{
			int temp = calculateWidth(root, i);
			if (temp > maxWidth)
			{
				maxWidth = temp;
			}
		}
		return maxWidth;
	}
	int calculateWidth(node<T>* curr, int i)
	{
		if (curr == NULL)// for the last level
			return 0;

		else if (i == 1) // when it reaches the level we want
			return 1;

		else if (i > 1)
			return calculateWidth(curr->left, i - 1) + calculateWidth(curr->right, i - 1);

	}
	BST(const BST& obj)	// copy constructor using recursive function
	{
		root = copy(obj.root);
	}
	void operator=(const BST& obj) // assignment operator
	{
		root = copy(obj.root);
	}
	node<T>* copy(node<T>* curr)	// the recursive copy function
	{
		node<T>* newRoot;
		if (curr == NULL)
			return NULL;
		else
		{
			newRoot = new node<T>;
			newRoot->data = curr->data;

			newRoot->left = copy(curr->left);
			newRoot->right = copy(curr->right);
		}
		return newRoot;
	}
	void deleteTree()
	{
		clearTree(root);
	}
	void clearTree(node<T>*& curr)
	{
		if (curr != NULL)
		{
			clearTree(curr->left);
			clearTree(curr->right);
			delete curr;
			curr = NULL;
		}
	}
	~BST()
	{
		deleteTree();
	}
};

int main()
{
	BST<int> tree;
	int value;  int newVal; int n;

	// USER INPUT

	/*cout << "Insert Values in Tree (-1 to stop)\n";
	cin >> value;
	while (value != -1)
	{
		tree.insert(value);
		cin >> value;
	}*/

	// HARD CODED VALUES

	//tree.insert(10);

	tree.insert(60);
	tree.insert(70);
	tree.insert(80);
	tree.insert(90);
	tree.insert(20);
	tree.insert(30);
	tree.insert(40);
	tree.insert(10);
	//	tree.insert(50);
	//tree.insert(100);

		// printing
	cout << "Printing Tree1~\n";
	cout << "Level Order Print:\n";
	tree.levelOrderPrint();
	cout << "InOrder Print(LVR):\n";
	tree.inorderPrint();
	cout << "PreOrder Print(LVR):\n";
	tree.preorderPrintR();
	cout << "PostOrder Print:\n";
	tree.postorderPrint();

	// width, count, path sum
	cout << "\nLevels: " << tree.levels() << endl;
	cout << "Width: " << tree.width() << endl;
	cout << "Count: " << tree.countNodes() << endl;
	vector<int> sums;
	tree.pathSum(sums);
	cout << "Path Count: " << sums.size() << "\nSum of each Path: ";
	for (int i = 0; i < sums.size(); i++)
	{
		cout << sums.at(i) << " ";
	}

	// = overload and copy constructor
	cout << "\n\nCopy Functions~\nTree1: "; tree.levelOrderPrint();
	BST<int> tree2(tree);
	cout << "Tree2 using copy constructor: "; tree2.levelOrderPrint();
	BST<int> tree3;
	tree3 = tree;
	cout << "Tree3 using assignment op:    "; tree3.levelOrderPrint();

	// mirror 
	cout << "\nMirroring Tree2~\nBefore: "; tree2.levelOrderPrint();
	tree2.mirrorBST();
	cout << "After:  "; tree2.levelOrderPrint();

	// isBST
	if (tree3.isBST())
		cout << "\nTree is BST";
	else
		cout << "\nTree is not BST";

	// delete
	cout << "\nDeleting~\nBefore: "; tree.levelOrderPrint();
	cout << "How many nodes do you want to delete: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter value to Delete: ";
		cin >> value;
		if (tree.deleteNode(value))
		{
			cout << "After:  "; tree.levelOrderPrint();
		}
		else
			cout << "Node doesnt exist\n";
	}

	// update key
	cout << "\nUpdate Key~\nBefore: "; tree.levelOrderPrint();
	cout << "Enter node data to Update: ";
	cin >> value;
	cout << "Enter new value: ";
	cin >> newVal;
	if (tree.updateKey(value, newVal))
	{
		cout << "After:  "; tree.levelOrderPrint();
	}

	cout << "\n"; system("pause"); return 0;
}