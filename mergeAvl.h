#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
#ifndef AVL_H
#define AVL_H
template <class T>
class AVL
{
	struct node
	{
		T data;		   // Search value
		node *left, *right; // Pointers to children
		int height;		 // Height of subtree
		node()
		{
			left = NULL;
			right = NULL;
			height = 0;
		}
	};
	node *root;
	node* rotateRight(node *);    // O(1) right rotate function
	node* rotateLeft(node *);     // O(1) left rotate function
	node* insert(node *, T);      // O(LogN) recursive insertion
	node* delet(node *, T);       // O(LogN) recursive deletion
	node* checkHeights(node *);   // Maintain balance in the force
	node* extractMin(node **);    // Get minimum value in O(LogN)
	node* mergeWithNode(node *, node *, node *); // Merge trees in O(LogN + LogM)
	void breakTree(T, node **, node **);         // Break trees along key in O(LogM + LogN)
	void printTree(node* root)
	{
		if(root == NULL)
			//cout<<"\n the tree is empty\n" << endl;
			return;
		
				printTree(root->left);
				cout << root->data << " ";
				printTree(root->right);
				
			
	}
public:
	AVL()
	{
		root = NULL;
	}
	AVL<T> split(T key);       // Changes calling tree to larger tree, returns smaller tree
	AVL<T> add(AVL<T> tree2);  // O(LogM + LogN) calls extractMin() and mergeWithNode()
	AVL<T> ins(T val);         // O(LogN) calls insert()
	AVL<T> inst(T val);
	AVL<T> del(T val);         // O(LogN) calls delet()
	T find(T val);             // O(LogN)
	void disp();               // O(N) traversal, for debugging
};
template <class T>
typename AVL<T>::node* AVL<T>::rotateRight(node *n)
{
	if(n == NULL || n->left == NULL)
		return n;
	node *t = n->left;
	n->left = t->right;
	t->right = n;

	// Set heights
	if(n->left != NULL && n->right != NULL)
		n->height = max(n->left->height, n->right->height) + 1;
	else if(n->left != NULL)
		n->height = n->left->height + 1;
	else if(n->right != NULL)
		n->height = n->right->height + 1;
	else
		n->height = 1;

	if(t->left != NULL)
		t->height = max(n->height, t->left->height) + 1;
	else
		t->height = n->height + 1;
	return t;
}
template <class T>
typename AVL<T>::node* AVL<T>::rotateLeft(node *n)
{
	if(n == NULL || n->right == NULL)
		return n;
	node *t = n->right;
	n->right = t->left;
	t->left = n;

	// Set heights
	if(n->left != NULL && n->right != NULL)
		n->height = max(n->left->height, n->right->height) + 1;
	else if(n->left != NULL)
		n->height = n->left->height + 1;
	else if(n->right != NULL)
		n->height = n->right->height + 1;
	else
		n->height = 1;

	if(t->right != NULL)
		t->height = max(n->height, t->right->height) + 1;
	else
		t->height = n->height + 1;
	return t;
}
template <class T>
typename AVL<T>::node* AVL<T>::insert(node *n, T val)
{
	// Create and insert node
	if(n == NULL)
	{
		n = new node;
		n->data = val;
		n->height = 1;
		return n;
	}

	// Insert into appropriate subtree
	if(n->data <= val)
		n->right = insert(n->right, val);
	else
		n->left = insert(n->left, val);

	// Recalculate heights and rotate
	return checkHeights(n);
}
template <class T>
typename AVL<T>::node* AVL<T>::delet(node *n, T val)
{
	if(n == NULL)
	{
		cerr<<"Node not found\n";
		return NULL;
	}
	// Find and delete node
	if(val == n->data)
	{
		if(n->left == NULL && n->right == NULL)
		{
			delete n;
			return NULL;
		}
		else if(n->left == NULL)
		{
			node *t = n->right;
			*n = *t;
			delete t;
		}
		else if(n->right == NULL)
		{
			node *t = n->left;
			*n = *t;
			delete t;
		}
		else
		{
			node *t = n->left;
			while(t->right != NULL)
				t = t->right;
			T temp = n->data;
			n->data = t->data;
			t->data = temp;
			n->left = delet(n->left, val);
		}
	}
	else if(val < n->data)
		n->left = delet(n->left, val);
	else
		n->right = delet(n->right, val);
	// Rebalance tree
	return checkHeights(n);
}
template <class T>
typename AVL<T>::node* AVL<T>::checkHeights(node *n)
{
	if(n == NULL)
		return n;
	if(n->left == NULL && n->right == NULL)
	{
		n->height = 1;
		return n;
	}
	else if(n->left == NULL)
	{
		n->height = n->right->height + 1;
		if(n->right->height >= 2)
		{
			if(n->right->left != NULL && (n->right->right == NULL || n->right->left->height > n->right->right->height))
				n->right = rotateRight(n->right);
			return rotateLeft(n);
		}
	}
	else if(n->right == NULL)
	{
		n->height = n->left->height + 1;
		if(n->left->height >= 2)
		{
			if(n->left->right != NULL && (n->left->left == NULL || n->left->right->height > n->left->left->height))
				n->left = rotateLeft(n->left);
			return rotateRight(n);
		}
	}
	else
	{
		n->height = max(n->left->height, n->right->height) + 1;
		if(abs(n->left->height - n->right->height) >= 2)
		{
			if(n->left->height > n->right->height)
			{
				if(n->left->right != NULL && (n->left->left == NULL || n->left->right->height > n->left->left->height))
					n->left = rotateLeft(n->left);
				return rotateRight(n);
			}
			else
			{
				if(n->right->left != NULL && (n->right->right == NULL || n->right->left->height > n->right->right->height))
					n->right = rotateRight(n->right);
				return rotateLeft(n);
			}
		}
	}
	return n;
}
// Assumption: All nodes of tree2 have values
// that are <= the smallest value in tree1
template <class T>
typename AVL<T>::node* AVL<T>::mergeWithNode(node *tree1, node *tree2, node *mergeNode)
{
	if(mergeNode == NULL)
		return tree1;
	if(tree1 == NULL && tree2 == NULL)
		return mergeNode;
	else if(tree1 == NULL)
	{
		T t = mergeNode->data;
		tree2 = insert(tree2, t);
		delete mergeNode;
		return tree2;
	}
	else if(tree2 == NULL)
	{
		T t = mergeNode->data;
		tree1 = insert(tree1, t);
		delete mergeNode;
		return tree1;
	}
	if(tree1->height - tree2->height >= 2)
	{
		tree1->left = mergeWithNode(tree1->left, tree2, mergeNode);
		tree1 = checkHeights(tree1);
		return tree1;
	}
	else if(tree2->height - tree1->height >= 2)
	{
		tree2->right = mergeWithNode(tree1, tree2->right, mergeNode);
		tree2 = checkHeights(tree2);
		return tree2;
	}
	mergeNode->left = tree2;
	mergeNode->right = tree1;
	mergeNode = checkHeights(mergeNode);
	cout<<"successfull";
	cout<<"\n";
	return mergeNode;

}
// Get the minimum value in O(LogN)
template <class T>
typename AVL<T>::node* AVL<T>::extractMin(node **tree)
{
	if(tree == NULL)
		return NULL;
	// Found minimum node
	if((*tree)->left == NULL)
	{
		// Copy details
		node *temp = new node;
		*temp = **tree;
		// Remove node from tree
		*tree = delet(*tree, (*tree)->data);
		// Rebalance
		*tree = checkHeights(*tree);
		return temp;
	}
	// Keep moving
	node *t = extractMin(&((*tree)->left));
	// Rebalance
	(*tree) = checkHeights(*tree);
	return t;
}


// Assumption: Tree2 is tree with smaller keys
template <class T>
AVL<T> AVL<T>::add(AVL<T> tree2)
{
	node *m = extractMin(&root);
	root = mergeWithNode(root, tree2.root, m);
	printTree(root);
	return *this;
}
template <class T>
AVL<T> AVL<T>::ins(T val)
{
	root = insert(root, val);
	return *this;
}
template <class T>
AVL<T> AVL<T>::inst(T val)
{
	root = insert(root, val);
	return *this;
}
template <class T>
AVL<T> AVL<T>::del(T val)
{
	root = delet(root, val);
	return *this;
}
template <class T>
T AVL<T>::find(T val)
{
	// Search tree until required value encountered
	node *t = root;
	while(t != NULL && t->data != val)
	{
		if(val > t->data)
			t = t->right;
		else
			t = t->left;
	}
	// Value not found
	if(t == NULL)
		return -1;
	// Value found
	return t->data;
}
template <class T>
void AVL<T>::disp()
{
	printTree(root);
}
#endif