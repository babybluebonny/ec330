//Extra credit: Complete merge sort via linked list for constant space complexity
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Linked list initialization 
typedef struct Node* node_ptr;
struct Node
{
	int data; 
	node_ptr next; //pointer to next node in linked list
};

node_ptr list_head; //head of linked list

//Prints final result one by one
void printlist(node_ptr head)
{
	node_ptr current = head;
	while (current != NULL)
	{
		printf("%d", current->data);
		current = current->next;
	}
}

//Function that splits values in left half and right half 
void split(node_ptr current_head, node_ptr *left, node_ptr *right)
{
	node_ptr end; //incremented twice as much as index until it hits the end of the list
	node_ptr index; //incremented until it eventually becomes the center index

	//Base case
	if (current_head == NULL || current_head->next == NULL)
	{
		*left = current_head;
		*right = NULL;
	}
	else
	{
		index = current_head; //starts off as first element of linked list
		end = current_head->next; //starts off as first+1 element of linked list
	}

	//Idea is to increment pointers until index points to middle so that there are 2 separate linked lists
	while (end != NULL) //while end is still pointing to a linked list element
	{
		end = end->next; //increment end pointer by 1

		if (end != NULL) //if end pointer has not reached the end yet
		{
			index = index->next; //increment index pointer by one
			end = end->next; //increment end pointer by one
		}
	}

	*left = current_head; //left linked list starts at 0
	*right = index->next; //right linked list starts at node after index
	index->next = NULL;
}

//Function that takes 2 linked lists after sorting and merges them together
node_ptr mergelists(node_ptr left, node_ptr right)
{
	node_ptr merge = NULL;

	//Base case
	if (left == NULL)
	{
		return right;
	}
	else if (right == NULL)
	{
		return left;
	}

	//Compare the elements of each half using recursion
	if (left->data <= right->data) //if left element is smaller, add the left side's 
	{
		merge = left;
		merge->next = mergelists(left->next, right);
	}
	else //if right is smaller, then add the right side's
	{
		merge = right;
		merge->next = mergelists(left, right->next);
	}

	return merge; 
}

//Sorts by comparing values of pointers 
void mergesort(node_ptr *value)
{
	node_ptr head = *value;
	node_ptr left = NULL; 
	node_ptr right = NULL;

	//Base case 
	if (head == NULL || head->next == NULL)
	{
		return;
	}

	split(head, &left, &right);

	//Recursively sort each half until elements are alone 
	mergesort(&left);
	mergesort(&right);

	//Check numbers and then "merge" numbers 
	*value = mergelists(left, right);

}

//Add values to linked list nodes
void add(node_ptr *head, int data)
{
	node_ptr new_node = (node_ptr)malloc(sizeof(struct Node));
	new_node->data = data;
	new_node->next = NULL;

	if ((*head) == NULL)
	{
		*head = new_node;
		list_head = *head;
	}
	else
	{
		(*head)->next = new_node;
		*head = new_node;
	}
}

int main()
{
	int input1, input2, input3, input4, input5; 
	node_ptr prev = NULL; //points to element before 

	cout << "Please enter 5 int values to be sorted: " << endl;
	cin >> input1;
	cin >> input2;
	cin >> input3;
	cin >> input4;
	cin >> input5;

	//Add inputed values to linked list nodes
	add(&prev, input1); 
	add(&prev, input2);
	add(&prev, input3);
	add(&prev, input4);
	add(&prev, input5);

	mergesort(&list_head); //sort
	printlist(list_head); //prints out final result
	cout << endl;

	return 0;
}
