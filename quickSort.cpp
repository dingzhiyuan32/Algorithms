//
//  quickSort.cpp
//  quick sort an array
//
//  @Zhiyuan Ding
//

#include <iostream>
#include <vector>
using namespace std;

//print the array
//@param a The array to be printed
//@param len The length of the array
void prt(vector<int> &a, int len)
{
	for(int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

//exchange two elements
//@param a The array to be exchanged
//@param i The index of element to be exchanged
//@param j The index of element to be exchanged
void exchange(vector<int> &a, int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

//partition the array. every element less than a[r] will be on the left of a[r]
//  every element larger than a[r] will be on the right of a[r].
//@param p & r The array between a[p] and a[r] will be partitioned
//@return The new position of a[r]
int partition(vector<int> &a, int p, int r)
{
	int i = p - 1;
	int x = a[r];
	for(int j = p; j < r; j++)
	{
		if(a[j] < x)
		{
			i++;
			exchange(a, i, j);
		}
	}
	exchange(a, i + 1, r);             //put a[r] on the right position
	return(i + 1);                     //return the new position of a[r]
}

//quick sort the array by recursion
//@param a The array to be sorted
//@param p & r The elements between p and r will be sorted
void quickSort(vector<int> &a, int p, int r)
{
	if(p < r)
	{
		int q = partition(a, p, r);    //patition the array
		quickSort(a, p, q - 1);        //quick sort a[p...q-1]
		quickSort(a, q + 1, r);        //quick sort a[q+1...r]
	}
}

//main function
int main()
{
	int value;
	vector<int> a;
	cout << "Input the elements to be sorted." << endl;
	cout << "Input other character except integers to end input." << endl;
	while(cin >> value)                   //input the array
	{
		a.push_back(value);
	}
	int len = a.size();  //The length of the array
	cout << "before quick sort:" << endl;
	prt(a, len);                       //print the array before sort
	quickSort(a, 0, len - 1);          //use function to quick sort
	cout << "after quick sort:" << endl;
	prt(a, len);                       //print the array after sort
	return 0;
}
