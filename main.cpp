#include <bits/stdc++.h>
using namespace std;
#define RED 0;
#define BLACK 1;
struct node
{
	int key;
	int col;
	node* left;
	node* right;
	node* parent;
	// int end;
	// int max;
	node(int data)
    {
       this->key = data;
       this->col = RED;
       left = right = parent = NULL;
    }
}

// void print(root)
// {

// }

void rL(node *&root,node *&child)
{
	node* papa = (child->right);
	child->right = papa->left;
	if (child->right !=NULL)
		(child->right)->parent = child;
	papa->parent = child->parent;
	if (papa->parent==NULL)
		root=papa;
	else if(child == child->parent->left)
		(child->parent)->left=papa;
	else
		(child->parent)->right=papa;
	papa->left = child;
	child->parent=papa;
}

void rR(node *&root,node *&child)
{
	node* papa = (child->left);
	child->right = papa->right;
	if (child->left !=NULL)
		(child->left)->parent = child;
	papa->parent = child->parent;
	if (papa->parent==NULL)
		root=papa;
	else if(child == child->parent->left)
		(child->parent)->left=papa;
	else
		(child->parent)->right=papa;
	papa->right = child;
	child->parent=papa;
}

void ViolationCorrection(node *&root,node *&newNode)
{
	node *gpap = NULL;
	node* papa = NULL;
	while((newNode!=root)&&(newNode->col==RED)&&newNode->parent->col==RED)
	{
		papa = newNode->parent;
		gpap = (newNode->parent)->parent;
		if(papa ==gpap->left)
		{
			node *uncle = gpap->right;
			if(uncle!=NULL && uncle->col==RED)
			{
				gpap->col=RED;
				papa->col=BLACK;
				uncle->col=BLACK;
				newNode = gpap;
			}
			else
			{
				if (newNode = papa->right)
				{
					rL(root,papa)
					newNode = parent;
					parent = newNode->papa;
				}
				rR(root,gpap);
				int temp = gpap->col;
				gpap->col = papa->col;
				papa->col = temp;
				newNode = papa;
			}
		}
		else
		{
			node *uncle = gpap->left;
 
            if ((uncle != NULL) && (uncle->col == RED))
            {
                gpap->color = RED;
                papa->color = BLACK;
                uncle->color = BLACK;
                newNode = gpap;
            }
            else
            {
               if (newNode == papa->left)
                {
                    rR(root, papa);
                    newNode = papa;
                    papa = newNode->parent;
                }
 
                /* Case : 3
                   newNode is right child of its parent
                   Left-rotation required */
                rL(root, gpap);
                int temp = gpap->col;
				gpap->col = papa->col;
				papa->col = temp;
                newNode = papa;
            }
        }
    }
 
    root->col = BLACK;
}

node* insertNode(node* root,node* temp)
{
	node *papa = NULL
	while(root)
	{
		papa = root;
		if(root->key > temp->key)
			{
				root = root->left;
			}
		else if(root->key > temp->key)
			{
				root = root->right;
			}
		else{
			cout<<"Node overlapping cannot insert";
			return;
		}
	}
	root=temp;
	root->parent = papa;
	return root;
}

node* newNodeInsert(node *root, int data)
{
	node *Temp = new node(data);
	Temp = insertNode(root,Temp);
	ViolationCorrection(root, Temp);
	return root;
}

int main()
{
	int n;
	int data;
	node *root = NULL
	cin>>n;
	while(n--)
	{
		cin>>data;
		root = newNodeInsert(data);
	}
	return 0;
}