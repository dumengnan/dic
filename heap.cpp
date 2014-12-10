#include<iostream>
using namespace std;

void sift(int d[], int ind, int len)
{
		int i = ind;
		 
		int c = i *2 +1;

		while(c < len)
		{
				if(c + 1 < len && d[c] < d[c+1])
						c++;

				if(d[i] > d[c]) break;
				else
				{
						int t = d[c];
						d[c] = d[i];
						d[i] = t;

						i = c;
						c = 2*i + 1;
						}
				}
				return ;
		}

void heap_sort(int d[], int n)
{
		for(int i = (n -2)/2; i >= 0; i--)
				sift(d, i, n);

		for(int j = 0; j < n; j++)
		{
				int t = d[0];
				d[0] = d[n -j -1];
				d[n - j -1] = t;

				sift(d, 0, n-j-1);
				}
		}

int main()
{
		int a[] = {3, 4, 6,3,2,7,5,1};
		heap_sort(a, sizeof(a)/sizeof(*a));

		for(int i = 0; i< sizeof(a)/sizeof(*a); i++)
		{
				cout<<a[i]<<' ';
				}
				cout<<endl;
		return 0;
		}
