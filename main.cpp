#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;
#define N 1000
#define M 1000

int main() {
    int data;
    RBTree rbTree1, rbTree2;
    int i , j;
    for(i = 0; i < N;i++)
        {
            int k = rand() % 1000 + 1;
            rbTree1.insertValue(k);
        }
    //tree1.disp();
    for(j = 0;j < M  ; j++)
        {
            int l = rand() % 1000 + 1000;
            rbTree2.insertValue(l); 
        }
   /*
    rbTree1.insertValue(10);
    rbTree1.insertValue(20);
    rbTree1.insertValue(30);
    rbTree1.insertValue(40);
    rbTree1.insertValue(50);
    rbTree1.insertValue(60);
*/     

   // rbTree1.preorder();

/*   
    rbTree2.insertValue(100);
    rbTree2.insertValue(200);
    rbTree2.insertValue(300);
    rbTree2.insertValue(400);
    rbTree2.insertValue(500);
    rbTree2.insertValue(600);
    rbTree2.preorder();
*/
    rbTree1.merge(rbTree2);
    rbTree1.inorder();

    return 0;
}