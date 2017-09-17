//
//heapSort.cpp
//heap sort an array
//
//@Zhiyuan Ding
//

#include <iostream>
#include <vector>

using namespace std;

//Summary: exchange two elements
//Parameter:
//  a: the array to be exchanged
//  i & j: the elements to be exchanged
void exchange(vector<int> &a, int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

//Summary: get the left child and right child
//Parameter:
//  i: the index of the parent node
int left(int i)
{
	return(2 * i + 1);
}
int right(int i)
{
	return(2 * i + 2);
}

//Summary: keep the heap with the root i being a max heap
//Parameter:
//  a: The array to be sorted
//  len: The length of the array
//  i: The index of the root in this case
void maxHeapIFY(vector<int> &a, int len, int i)
{
	int largest = i;
	int l = left(i);                   //get the left child
	int r = right(i);                  //get the right child
	if(l < len && a[largest] < a[l])   //compare child with parent
	{
		largest = l;
	}
	if(r < len && a[largest] < a[r])
	{
		largest = r;
	}
	if(largest != i)                   //make parent the largest
	{
		exchange(a, i, largest);
		//make the heap with the new child as root being a max heap
		maxHeapIFY(a, len, largest);
	}
}

//Summary: build max heap from a heap
//Parameter:
//  a: the array to be sorted
//  len: the length of the array
void buildMaxHeap(vector<int> &a, int len)
{
	//make every heap in the array being a max heap
	for(int i = len - 1; i >= 0; i--)
	{
		maxHeapIFY(a, len, i);         //make the heap being a max heap
	}
}

//Summary: heap sort an array with functions
//Parameter: 
//  a: the array to be sorted
//  len: the length of the array
void heapSort(vector<int> &a, int len)
{
	buildMaxHeap(a, len);              //build a max heap at first
	exchange(a, 0, len - 1);           //put the root(max number) on the last
	for(int i = len - 1; i > 0; i--)
	{
		maxHeapIFY(a, i, 0);           //keep max heap after every change
		exchange(a, i - 1, 0);         //put the root on the right position
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
	int len = a.size();
	cout << "before heap sort:" << endl;
	for(int i = 0; i < len; i++)       //print the array before sort
	{
		cout << a[i] << " ";
	}
	cout << endl;

	heapSort(a, len);

	cout << "after heap sort:" << endl;
	for(int i = 0; i < len; i++)       //print the array after sort
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
