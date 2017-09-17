//
//  mergeSort.cpp
//  merge sort an array
//
//  @Zhiyuan Ding
//

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

#define MAX 2147483647
 
//merge a[p, ..., q] and a[q+1, ..., r]
//@param a The array to be merged
//@param p,q,r the indices of array
void merge(vector<int> &a, int p, int q, int r)
{
	int n1 = q - p + 1;                   //count the length of two arrays
	int n2 = r - q;
	vector<int> L, R;                     //the left and right sub arrays
	for(int i = 0; i < n1; i++)           //copy the array
	{
		L.push_back(a[p + i]);
	}
	for(int i = 0; i < n2; i++)
	{
		R.push_back(a[q + i + 1]);
	}
	L.push_back(MAX);
	R.push_back(MAX);

	for(int i = 0, j = 0, k = p; k <= r; k++)//merge the left and right arrays
	{
		if(L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
	}
}

//use recursion to merge sort the array from p to r
//@param a The array to be sorted
//@param p,r The indices of the array
void mergeSort(vector<int> &a, int p, int r)
{
	if(p < r)
	{
		int q = floor((p + r) / 2);
		mergeSort(a, p, q);               //sort the left array with recursion
		mergeSort(a, q + 1, r);           //sort the right array
		merge(a, p, q, r);                //merge the left and right array
	}
}

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

	int len = a.size();
	for(int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	mergeSort(a, 0, len - 1);
	for(int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
