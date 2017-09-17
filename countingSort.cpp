//
//  countingSort.cpp
//  counting sort an array
//
//  @Zhiyuan Ding
//

#include <iostream>
#include <vector>
using namespace std;
#define MAX 100

//print the array
//@param a The pointer to the array
//@param len The length of the array
void prt(vector<int> &a, int len)
{
	for(int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

//use counting sort to sort the array. The sorted array will be in b[]
//@param a The array to be sorted
//@param b The array to save the sorted array
//@param len The length of the array
//@param k The data of the element are between 1 and k
void countingSort(vector<int> &a, vector<int> &b, int len, int k)
{
	vector<int> c(k, 0);

	for(int i = 0; i < len; i++)  //count the amount of element of every number
	{
		c[a[i]]++;
	}
	for(int i = 1; i < k; i++)    //count the amount of element less than i
	{
		c[i] = c[i] + c[i - 1];
	}
	for(int i = len - 1; i >= 0; i--)   //save elements to b with sorted order
	{
		b[c[a[i]] - 1] = a[i];
		c[a[i]]--;
	}
}

//main function
int main()
{
	int value;
	vector<int> a;
	cout << "Input the elements to be sorted. The max is " << MAX << endl;
	cout << "Input other character except integers to end input." << endl;
	while(cin >> value)                   //input the array
	{
		a.push_back(value);
	}
	int len = a.size();
	vector<int> b(len, 0);
	cout << "before counting sort:" << endl;
	prt(a, len);                               //print the array before sort
	countingSort(a, b, len, MAX);              //use function to counting sort
	cout << "after counting sort:" << endl;
	prt(b, len);                               //print the array after sort
	return 0;
}
