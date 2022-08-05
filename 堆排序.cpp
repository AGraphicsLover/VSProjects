#include<iostream>
using namespace std;

int a[] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

void swap(int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int getParentIndex(int child)
{
	return ((child - 1) / 2);
}

int getLeftChildIndex(int parent)
{
	return (2 * parent + 1);
}

void adjustHeap(int i, int len)
{
    int left, right, j;
    left = getLeftChildIndex(i);
    while (left <= len)
    {
        right = left + 1;
        j = left;
        if (j < len && a[left] < a[right])
            j++;
        if (a[i] < a[j])
        {
            swap(i, j);
            i = j;
            left = getLeftChildIndex(i);
        }
        else
            break;
    }
}

int main()
{
    int last = 9;
    for (int i = getParentIndex(last); i >= 0; i--)
        adjustHeap(i, last);
    while (last >= 0) 
    {
        swap(0, last--);
        adjustHeap(0, last);
    }
    for (int i = 0; i < 10; i++)
        cout << a[i] << "  ";
    cout << endl;
    return 0;
}