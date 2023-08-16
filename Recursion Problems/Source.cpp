#include <iostream>
using namespace std;

const int N = 8; // N-Queens Problem
int board[N][N];
int** subsets = new int* [100];

void init(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}
void print(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}
int reverseDigits(int n)
{
	static int ans = 0; // to store reversed 

	if (n == 0)
	{
		return ans;
	}
	else
	{
		ans = (ans * 10) + (n % 10);// taking the last digit in num and accumulating the result in ans
		reverseDigits(n / 10);	// dividing original num by 10
	}
}
void evenOdd(int* arr, int n)
{
	if (n == 0)
	{
		return;
	}
	else
	{
		if (arr[0] % 2 == 0)
		{
			evenOdd(arr + 1, n - 1);
		}
		else if (arr[n - 1] % 2 != 0)
		{
			evenOdd(arr, n - 1);
		}
		else
		{
			int temp = arr[0];
			arr[0] = arr[n - 1];
			arr[n - 1] = temp;

			evenOdd(arr + 1, n - 2);
		}
	}
}
bool checkSum(int* arr, int j, int k, int i)
{
	if (j == i)	// j will move forward and i will move backward
	{
		return false;
	}
	else
	{
		if (j == i - 1) // when j has done checking sum for an i, then i moves backward and j starts checking from 0 again
		{
			checkSum(arr, 0, 1, i - 1);
		}
		else if (k == i) // when k reaches i, move j forward and place k one step forward too
		{
			checkSum(arr, j + 1, j + 1, i);
		}
		else if (arr[j] + arr[k] == arr[i]) // as soon as a sum is found
		{
			return true;
		}
		else
		{
			checkSum(arr, j, k + 1, i);	// iteration for each sum check 
		}
	}
}
int countPaths(int n, int m)
{
	static int count = 1;
	// when any of the cordiantes becomes 0, theres only one possible path from there
	if (n == 0 || m == 0)
	{
		return count;
	}

	countPaths(n - 1, m);
	countPaths(n, m - 1); // only allowed to move in these two directions
	count++;
}
void MergeSort(int* arr, int low, int high)
{
	if (low >= high)
	{
		return;
	}
	else
	{
		int mid = low + (high - low) / 2;

		// here the arrays are divided into two sub arrays
		// divide:
		MergeSort(arr, low, mid);
		MergeSort(arr, mid + 1, high);

		// merge:
		int* temp = new int[high + 1]; // copying both parts in an array
		for (int i = low; i <= high; i++)
		{
			temp[i] = arr[i];
		}

		int i = low;
		int j = mid + 1;
		int k = low;
		// copy the smallest values from either the right or left side of the array to the original array
		while (i <= mid && j <= high)
		{
			if (temp[i] <= temp[j])
			{
				arr[k++] = temp[i++];
			}
			else
			{
				arr[k++] = temp[j++];
			}
		}

		while (i <= mid)
		{
			arr[k++] = temp[i++];
		}
	}
}
bool underAttack(int i, int j)
{
	for (int k = 0; k < N; k++) // checking if theres alrdy a queen in that row/col
	{
		if ((board[i][k] == 1) || (board[k][j] == 1))
			return 1;
	}
	for (int k = 0; k < N; k++) // checking for diagonals
	{
		for (int l = 0; l < N; l++)
		{
			if (((k + l) == (i + j)) || ((k - l) == (i - j)))
			{
				if (board[k][l] == 1)
					return 1;
			}
		}
	}
	return 0;
}
int N_queen(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (!underAttack(i, j) && board[i][j] != 1) // checking if we can place a queen here
				{
					board[i][j] = 1; // we place the queen at a suitable location

					if (N_queen(n - 1) == 1)
					{
						return 1;
					}
					board[i][j] = 0; // if not then that queen is removed and the next place is checked
				}
			}
		return 0; // when no order is found
	}
}
int** ComputeSubsets(int* arr, int n, int k, int index, int* subset, int i)
{
	static int x = 0;

	if (index == k)
	{
		for (int j = 0; j < k; j++)
		{
			subsets[x][j] = subset[j];
		}
		x++;
		return subsets;
	}
	else if (i >= n)
		return subsets;
	else
	{
		subset[index] = arr[i];
		ComputeSubsets(arr, n, k, index + 1, subset, i + 1);
		ComputeSubsets(arr, n, k, index, subset, i + 1);
	}
}
bool isPalindrome(string str, int index)				// starts from first index of string (=0) and checks if it is equal to the last index
{
	if (index >= (str.length() / 2) + 1)					// if the index exceeds midpoint that means it has been matching so it will be a palindrome
		return true;

	else if (str[index] == str[str.length() - index - 1])	// if it matches then checks the next index
		return isPalindrome(str, index + 1);

	return false;										// if there was no match it will immediately return false 
}

string putCommas(string STR, int index)		// starting from the last index of number 
{
	static string result;

	if (index == 0)										// if all numbers have been traversed through
	{
		result += STR[STR.length() - index - 1];
		return result;
	}
	else if (index % 3 == 0)								// if 3 numbers have passed(including this turn) then add a comma
	{
		result += STR[STR.length() - index - 1];
		result += ',';
	}
	else
		result += STR[STR.length() - index - 1];					// otherwise keep adding characters

	return putCommas(STR, index - 1);
}

// printing the binary combinations
void printStrings(int* arr, int k)
{
	for (int i = 0; i < k; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
void print01(int k, int i)
{
	static int* arr = new int[k];

	if (i == k)
	{
		printStrings(arr, k);
		return;
	}

	arr[i] = 0;		// assign 0 to the ith position and then check for all the other combi
	print01(k, i + 1);

	arr[i] = 1;		// assign 1 to the ith position and then check for all the other combi
	print01(k, i + 1);

}

string removeDuplicates(string str, int i)
{
	static string result;

	if (i > str.length() - 1)
		return result;
	else
	{
		while (str[i] == str[i + 1])
			i++;
	}
	result += str[i];

	return removeDuplicates(str, i + 1);
	//	return result;
}

int main()
{
	cout << "Is Palindrome ~\n";
	string str = "madam";

	if (isPalindrome(str, 0))
		cout << "Is a Palindrome\n";
	else
		cout << "Is not a Palindrome\n";

	cout << "--------------------------------------------------------\nPutting Commas in Numbers ~\n";
	string str2 = "23856235294";
	string result = putCommas(str2, str2.length() - 1);
	for (int i = 0; i < result.length(); i++)
		cout << result[i];
	cout << endl;
	cout << "--------------------------------------------------------\nRemove Duplicates ~\n";
	string str3 = "aaabbbccddeffffwe";
	string result2 = removeDuplicates(str3, 0);
	for (int i = 0; i < result2.length(); i++)
		cout << result2[i];
	cout << endl;

	cout << "--------------------------------------------------------\nPrint N size binary numbers ~\n";
	int K;
	cout << "Enter a number: ";
	cin >> K;

	print01(K, 0);

	int num = 0;
	int Size = 0;
	int x = 0;
	int y = 0;
	int k = 0;

	cout << "--------------------------------------------------------\nReversing Digits ~";
	cout << "\nEnter Number: \n";
	cin >> num;

	cout << "\nResult: \n" << reverseDigits(num) << endl;

	cout << "--------------------------------------------------------\nRearrange Array (Even Odd) ~\n";
	cout << "Enter Size of Array: ";
	cin >> Size;
	cout << "Enter Values:\n";
	int* arr = new int[Size];
	init(arr, Size);

	evenOdd(arr, Size);

	cout << "\nResult: ";
	print(arr, Size);
	cout << endl;
	delete[] arr;


	cout << "--------------------------------------------------------\nCheck Sum ~\n";
	cout << "Enter size of array: ";
	cin >> Size;
	cout << "Enter values:\n";
	arr = new int[Size];
	init(arr, Size);
	cout << endl;

	if (checkSum(arr, 0, 1, Size))
	{
		cout << "Yes\n";
	}
	else
		cout << "No\n";

	delete[] arr;

	cout << "--------------------------------------------------------\nCount Paths ~\n";
	cout << "Enter x: ";
	cin >> x;
	cout << "Enter y: ";
	cin >> y;
	cout << "\nNo. of Possible Paths: " << countPaths(x, y);

	cout << "\n--------------------------------------------------------\nMerge Sort ~\n";
	cout << "Enter Size of Array: ";
	cin >> Size;
	cout << "Enter Values:\n";
	arr = new int[Size];
	init(arr, Size);

	MergeSort(arr, 0, Size - 1); // low = first index and high = last index

	cout << "\nResult: ";
	print(arr, Size);
	cout << endl;
	delete[] arr;

	cout << "--------------------------------------------------------\n8-Queens Problem ~\n";
	//setting all elements to 0
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = 0;
		}
	}

	N_queen(N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << board[i][j] << " ";
		cout << "\n";
	}

	cout << "--------------------------------------------------------\nFind Subsets ~\n";

	cout << "Enter Size of Array: ";
	cin >> Size;
	cout << "Enter Values:\n";
	arr = new int[Size];
	init(arr, Size);
	cout << "Enter k: ";
	cin >> k;
	int* subset = new int[k];
	for (int i = 0; i < 100; i++)
	{
		subsets[i] = new int[k];
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < k; j++)
		{
			subsets[i][j] = 0;
		}
	}
	int** resultt = ComputeSubsets(arr, Size, k, 0, subset, 0);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < k; j++)
		{
			cout << resultt[i][j] << " ";
		}
		cout << endl;
	}
	delete[] arr;

	cout << endl << endl;
	system("pause");
	return 0;
}
