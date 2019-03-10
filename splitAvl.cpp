#include <algorithm>
#include <iostream>
#include <queue>
#include "splitAvl.h"
using namespace std;
#define TYPE int
#define N 10
#define M 1000

int main()
{
	AVL<int> tree1, tree2;
	int i,j=0;
	TYPE x= 525;
	for(j = 0; j < M;j++)
	{
		int k = rand() % 1000 + 1;
		tree1.ins(j);
	}
	tree1.ins(x);
	for(j = 0; j < M;j++)
	{
		int k = rand() % 1000 + 500;
		tree1.ins(j);
	}
	/*for(i = 0; i < N;i++)
		{
			int k = rand() % 1000 + 1;
			tree2.ins(k);
		}
	//tree1.disp(); */
	/*while(j<M)
	{
		tree1.ins(j);
		j++;
	}*/
	cout<<"\n";
/*	tree1.ins(10);
	tree1.ins(20);
	tree1.ins(30);
	tree1.ins(40);
	tree1.ins(50);
	tree1.ins(25); */
	//tree1.disp();
	/*tree2.ins(1);
	tree2.ins(2);
	tree2.ins(3);
	tree2.ins(4);
	tree2.ins(5);
	tree2.ins(0);*/
	//tree2.disp(); 
	
	tree1.split(x).disp();
	cout<<"\n";
	tree1.disp();
	return 0;
}