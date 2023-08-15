#include <iostream>
using namespace std;

struct AVLNode
{
	int data;
	AVLNode* left;
	AVLNode* right;
	int hl; // left height
	int hr; // right height
	int height;
	AVLNode()
	{
		data = 0;
		left = right = nullptr;
		hl = hr = height = 0;
	}
	AVLNode(int key)
	{
		data = key;
		left = right = nullptr;
		hl = hr = height = 0;
	}
	int getHL()
	{
		return hl;
	}
	int getHR()
	{
		return hr;
	}
	void incHL()
	{
		hl++;
	}
	void incHR()
	{
		hr++;
	}
};
class AVL
{
	AVLNode* root;
public:
	AVL()
	{
		root = NULL;
	}
	void insert(int key)
	{
		AVLNode* n = new AVLNode(key);
		if (root == NULL)
		{
			root = n;
			return;
		}
		root = insertR(root, key, n);
	}
	AVLNode* rightRotate(AVLNode* y)
	{
		AVLNode* x = y->left;

		y->left = x->right;
		x->right = y;

		// Update heights
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		// Return new root
		return x;
	}

	AVLNode* leftRotate(AVLNode* x)
	{
		AVLNode* y = x->right;

		x->right = y->left;
		y->left = x;
		
		// Update heights
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		// Return new root
		return y;
	}

	// Get Balance factor of AVLNode N
	int balanceCheck(AVLNode* curr)
	{
		curr->height = max(height(curr->left), height(curr->right)) + 1;

		if (curr == NULL)
			return 0;
		else
			return height(curr->left) - height(curr->right);
	}

	AVLNode* insertR(AVLNode* curr, int key, AVLNode* n)
	{
		if (curr == NULL)
			return n;

		if (key < curr->data)
		{
			curr->left = insertR(curr->left, key, n);
		}
		else if (key > curr->data)
		{
			curr->right = insertR(curr->right, key, n);
		}

		// checking if ancestor node is balanced
		int balance = balanceCheck(curr);

		// LL Case
		if (balance > 1 && key < curr->left->data)
			return rightRotate(curr);

		// RR Case
		if (balance < -1 && key > curr->right->data)
			return leftRotate(curr);

		// LR Case
		if (balance > 1 && key > curr->left->data)
		{
			curr->left = leftRotate(curr->left);
			return rightRotate(curr);
		}

		// RL Case
		if (balance < -1 && key < curr->right->data)
		{
			curr->right = rightRotate(curr->right);
			return leftRotate(curr);
		}

		return curr;
	}

	int height(AVLNode* curr)
	{
		if (curr == NULL)
			return 0;
		return curr->height;
	}
	int max(int a, int b)
	{
		if (a > b)
			return a;
		else
			return b;
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
	void printInorder(AVLNode* curr) 	// LVR traversal
	{
		if (curr == NULL)
		{
			return;
		}
		else
		{
			printInorder(curr->left);
			cout << curr->data << endl;
			printInorder(curr->right);
		}
	}
	void clearTree(AVLNode*& curr)
	{
		if (curr)
		{
			clearTree(curr->left);
			clearTree(curr->right);
			delete curr;
			curr = NULL;
		}
	}
	~AVL()
	{
		clearTree(root);
	}
};
int main()
{
	AVL tree;
	tree.insert(10);
	tree.insert(20);
	tree.insert(30);
	tree.insert(40);
	tree.insert(50);
	tree.insert(25);
	tree.inorderPrintR();
	
	system("pause");
	return 0;
}