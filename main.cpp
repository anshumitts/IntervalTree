#include <bits/stdc++.h>
struct node
{
	int key;
	int col;
	node* left;
	node* right;
	// int end;
	// int max;
}

// void print(root)
// {

// }

int ViolationCorrection(root)
{
	
}

void insertNode(node* root,node* temp)
{
	while(root)
	{
		if(root->key > temp->key)
			root = root->left;
		else if(root->key > temp->key)
			root = root->right;
		else{
			cout<<"Node overlapping cannot insert";
			return;
		}
	}
	root=temp;
}