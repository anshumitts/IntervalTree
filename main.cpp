#include <bits/stdc++.h>
#define RED 0
#define BLACK 1
using namespace std;
struct node
{
	int key;
	int col;
	int end;
	int max;
	node* left;
	node* right;
	node* parent;
	node(int low, int high)
    {
       this->key = low;
       this->end = high;
       this->col = RED;
       left = right = parent = NULL;
    }
};

void print(node* root)
{
	if(root)
		{
			cout<<root->key<<endl;
			print(root->left);
			print(root->right);
		}
}

int maxVal(node* root)
{
	int lef = -1;
	int righ = -1;
	int itself = root->end;
	if(root->left)
		lef = root->left->max;
	if(root->right)
		righ = root->right->max;
	return max(max(lef,righ),itself);
}

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
	child->max = maxVal(child);
	papa->max = maxVal(papa);
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
	child->max = maxVal(child);
	papa->max = maxVal(papa);
}

void ViolationCorrection(node *&root,node *&newNode)
{
	node *gpap = NULL;
	node* papa = NULL;
	while((newNode!=root)&&(newNode->col==RED)&&((newNode->parent)->col==RED))
	{
		// cout<<newNode->key<<endl;
		papa = newNode->parent;
		gpap = (newNode->parent)->parent;
		if(papa==gpap->left)
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
					rL(root,papa);
					newNode = papa;
					papa = newNode->parent;
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
                gpap->col = RED;
                papa->col = BLACK;
                uncle->col = BLACK;
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
 
                rL(root, gpap);
                int temp = gpap->col;
				gpap->col = papa->col;
				papa->col = temp;
                newNode = papa;
            }
        }
    }
    root->col = BLACK;
    root->max = maxVal(root);
}

node* insertNode(node* root,node* temp)
{
	node *papa = NULL;
	while(root)
	{
		papa = root;
		if(root->key > temp->key)
			{
				if(!(root->left))
					{
						root->left = temp;
						root->left->parent = root;
						root = root->left;
						break;
					}
				root = root->left;
			}
		else if(root->key < temp->key)
			{
				if(!(root->right))
					{
						root->right = temp;
						root->right->parent = root;
						root = root->right;
						break;
					}
				root = root->right;
			}
		else{
			cout<<"Node overlapping cannot insert"<<endl;
			return root;
		}
	}
	root=temp;
	root->parent = papa;
	return root;
}

node* newNodeInsert(node *root, int low, int high)
{
	node *Temp = new node(low,high);
	if(root==NULL)
		{
			root = Temp;
		}
	else{
	Temp = insertNode(root,Temp);
	}
	ViolationCorrection(root, Temp);
	return root;
}

int main()
{
	int n;
	int low,high;
	node *root = NULL;
	cin>>n;
	while(n--)
	{
		cin>>low>>high;
		root = newNodeInsert(root,low,high);
		print(root);
	}
	return 0;
}