//
//  insertionSort.cpp
//  Insertion sort an array
//
//  @Zhiyuan Ding
//

#include <iostream>
#include <vector>

using namespace std;

//use insertion sort to sort the array
//@param a The pointer to the array
//@param len The length of the array
void insertSort(vector<int> &a, int len)
{
	for(int i = 1; i < len; i++)     //The key will move to next after insertion
	{
		int key = a[i], j = i - 1;           //The elements before key is sorted
		for(; j >= 0 && a[j] > key; j--)     //find the right place to insert
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = key;                      //insert key to the array
	}
}

//main function
int main()
{
	int value;
	vector<int> a;
	cout << "Input the elements to be sorted." << endl;
	cout << "Input other character except integers to end input." << endl;

	while(cin >> value)
	{
		a.push_back(value);
	}
	int len = a.size();
	cout << "before insertion sort:" << endl;
	for(int i = 0; i < len; i++)             //print the array before sort
	{
		cout << a[i] << " ";
	}
	cout << endl;
	insertSort(a, len);                      //insertion sort with function
	cout << "after insertion sort:" << endl;
	for(int i = 0; i < len; i++)             //print array after sort
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
