#include <algorithm>
#include <iostream>
#include <queue>
#include "mergeAvl.h"
using namespace std;
#define TYPE int
#define N 1000
#define M 1000

int main()
{
	AVL<int> tree1, tree2;
	int i,j;
	for(i = 0; i < N;i++)
		{
			int k = rand() % 1000 + 1;
			tree2.ins(k);
		}
	//tree1.disp();
	for(j = 0;j < M  ; j++)
		{
			int l = rand() % 1000 + 1000;
			tree1.inst(l); 
		}
	//tree2.disp();
	cout<<"\n";
	/*tree1.ins(10);
	tree1.ins(20);
	tree1.ins(30);
	tree1.ins(40);
	tree1.ins(50);
	tree1.ins(25);*/
	
	/*tree2.inst(1);
	tree2.inst(2);
	tree2.inst(3);
	tree2.inst(4);
	tree2.inst(5);
	tree2.inst(0); */
	//tree2.disp();
	//cout<<"\n";
	tree1.add(tree2); 

	return 0;
}