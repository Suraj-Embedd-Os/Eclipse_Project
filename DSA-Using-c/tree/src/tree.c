/*
 ============================================================================
 Name        : tree.c
 Author      : EmbeddedOs
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct tree_node tree_ptr;

typedef int element_type;

struct tree_node {
	element_type element;
	tree_ptr *lchild;
	tree_ptr *rchild;

};

tree_ptr *insert_data(element_type element,tree_ptr *root);
void preorderTraversal(tree_ptr *root);
void ineorderTraversal(tree_ptr *root);
void posteorderTraversal(tree_ptr *root);
tree_ptr *create_node(element_type data);
tree_ptr *findSmallestElement(tree_ptr *);
tree_ptr *findLargestElement(tree_ptr*);
tree_ptr *deleteElement(tree_ptr*, int);
tree_ptr*mirrorImage(tree_ptr *);
int totalNodes(tree_ptr *);
int totalExternalNodes(tree_ptr*);
int totalInternalNodes(tree_ptr*);
int Height(tree_ptr *);
tree_ptr *deleteTree(tree_ptr *);

int main(void) {

	tree_ptr *root = NULL;

	element_type data_arr[]={20,21,19,22,18,23,16,24,15,25,14,26};

	for(int i = 0 ;i<sizeof(data_arr)/sizeof(data_arr[0]);i++)
	root=insert_data(data_arr[i],root);

	preorderTraversal(root);
	printf("\n");
	//ineorderTraversal(root);
	//printf("\n");
	//posteorderTraversal(root);
	//printf("\n");

	tree_ptr * ptr = findLargestElement(root);
	printf("%d ",ptr->element);

	return EXIT_SUCCESS;
}

tree_ptr *create_node(element_type data)
{
	tree_ptr *new_node = malloc(sizeof(struct tree_node));
	if(new_node == NULL)
		return NULL;
	new_node->element = data;
	new_node->lchild=NULL;
	new_node->rchild=NULL;

	return new_node;
}

tree_ptr *insert_data(element_type element,tree_ptr *root)
{
	tree_ptr *new_node = create_node(element);
	if(new_node == NULL)
		return root;

	if(root == NULL){
		root=new_node;
		return root;
	}

	tree_ptr *temp = root;
	tree_ptr *prev = root;

	while(temp)
	{
		if(temp->element > element)
		{

			prev=temp;
			temp=temp->lchild;
		}
		else
		{
			prev=temp;
			temp=temp->rchild;
		}
	}

	if(prev->element >element )
		prev->lchild = new_node;
	else
		prev->rchild = new_node;

	return root;

}

void preorderTraversal(tree_ptr *root)
{
	if(root != NULL)
	{
		printf("%d->",root->element);
		preorderTraversal(root->lchild);
		preorderTraversal(root->rchild);
	}


}

void ineorderTraversal(tree_ptr *root)
{
	if(root != NULL)
	{

		preorderTraversal(root->lchild);
		printf("%d->",root->element);
		preorderTraversal(root->rchild);
	}


}

void posteorderTraversal(tree_ptr *root)
{
	if(root != NULL)
	{

		preorderTraversal(root->lchild);
		preorderTraversal(root->rchild);
		printf("%d->",root->element);
	}
}

tree_ptr *findSmallestElement(tree_ptr *root)
{
	if(root == NULL || root->lchild == NULL)
		return root;
	else
		return findSmallestElement(root->lchild);

}

tree_ptr *findLargestElement(tree_ptr *root)
{
	//{20,21,19,22,18,23,16,24,15,25,14,26};
	if(root == NULL || root->rchild == NULL)
		return root;
	else
		return findLargestElement(root->rchild);

}

tree_ptr *deleteElement(tree_ptr *root, element_type element)
{
	return root;
}

tree_ptr *mirrorImage(tree_ptr *root)
{

	return root;
}

int totalNodes(tree_ptr *root)
{
	if(root==NULL)
		return 0;
	else
		return totalNodes(root->lchild)+totalNodes(root->rchild)+1;

}

element_type totalExternalNodes(tree_ptr *root)
{
	if(root == NULL)
		return 0;
	else if(root->rchild == NULL && root->lchild == NULL)
		return 1;
	else
		return totalExternalNodes(root->lchild) + totalExternalNodes(root->rchild);
}

element_type totalInternalNodes(tree_ptr *root)
{
	if(root == NULL)
		return 0;
	else if(root->rchild == NULL || root->lchild == NULL)
		return 0;
	else
		return totalInternalNodes(root->lchild) + totalInternalNodes(root->rchild)+1;
}

element_type Height(tree_ptr *root)
{
	int leftHeight;
	int rightHeight;

	if(root==NULL)
		return 0;
	else
	{
		leftHeight=Height(root->lchild);
		rightHeight=Height(root->rchild);

		if(leftHeight>rightHeight)
			return leftHeight+1;
		else
			return rightHeight+1;
	}
}

tree_ptr *deleteTree(tree_ptr *root)
{
	if(root !=NULL)
	{
		deleteTree(root->lchild);
		deleteTree(root->rchild);
		free(root);
	}
}


