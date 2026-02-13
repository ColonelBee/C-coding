/*
 Doubly Linked List, forward and backward access
 Test Data :

Input the number of nodes : 3
Input data for node 1 : 5
Input data for node 2 : 6
Input data for node 3 : 7

Expected Output :

 Data entered in the list are :                                                                               
 Data = 5                                                                                                     
 Data = 6                                                                                                     
 Data = 7                                                                                                     
                                                                                                              
 The list in reverse are :                                                                                    
 Data = 7                                                                                                     
 Data = 6                                                                                                     
 Data = 5 

*/

#include <stdio.h>
#include <stdlib.h>

// doubly linked list --> 2-way access
typedef struct node{
	int num;
	struct node *left_node;
	struct node *right_node;
}node;


// forward and backward linked list
node* create_nodes(int nnodes, const char *ask){
	// input data
	int data;
	// create first node
	node *i = malloc(sizeof(struct node));
	// check if the pointer is available on the heap
	if(i == NULL) return NULL;
	// enter the first data for 1st node
	fprintf(stdout, "Input data for node 1: ");
	fscanf(stdin, "%i", &data);
	i->num = data;
	i->left_node = NULL;
	i->right_node = NULL;
	// for the 2nd node and the others
	node *tmp = NULL;
	int nd = 2;
	for(int j = 1; j < nnodes; j++){
		node *k = malloc(sizeof(struct node));
		// from node 2
		if(j == 1){
			i->right_node = k;
			fprintf(stdout, "Input data for node %i: ", nd++);
			fscanf(stdin, "%i", &data);
			k->num = data;
			k->left_node = i;
			k->right_node = NULL;
			tmp = k;
			continue;
		}
		// from node 3
		if(j >= 2) tmp->right_node = k;
		// enter data for each node
		fprintf(stdout, "Input data for node %i: ", nd++);
		fscanf(stdin, "%i", &data);
		k->num = data;
		k->left_node = tmp;
		k->right_node = NULL;
		// store the address from node 2
		tmp = k; // this is also the address of the last node
	}
	if(ask == "BACKWARD") return tmp;
	return i;
}

// forward node display
void fdisplay_nodes(node *start){
	node *hold = start;
	int l = 1;
	fprintf(stdout, "\nData entered in the list:\n");
	for(; hold != NULL; hold = hold->right_node)
		fprintf(stdout, "Data for node %i: %i\n", l++, hold->num);
}

// backward or reverse node display
void bdisplay_nodes(node *last, int nnodes){
	node *final = last;
	int h = nnodes;
	fprintf(stdout, "\nData entered in the list:\n");
	for(; final != NULL; final = final->left_node)
		fprintf(stdout, "Data for node %i: %i\n", nnodes--, final->num);
}

// forward node free
void ffree_nodes(node *start){
	node *hold = start;
	node *next = NULL;
	for(; hold != NULL; hold = next){
		next = hold->right_node;
		free(hold);
	}
}

// backward or reverse node free
void bfree_nodes(node *last){
	node *final = last;
	node *next = NULL;
	for(; final != NULL; final = next){
		next = final->left_node;
		free(final);
	}
}

int main(){
	fprintf(stdout, "Input the number of nodes: ");
	int nnodes;
	int ask_num;
	fscanf(stdin, "%i", &nnodes); // input number of nodes in a linked list
	char *ask1 = "FORWARD";
	char *ask2 = "BACKWARD";
	// ask the user the direction of display, 1 is forward, 0 is backward
	fprintf(stdout, "Which direction do you want to display?\n");
	fprintf(stdout, "0 is backward, 1 is forward. Please enter here: ");
	fscanf(stdin, "%i", &ask_num);
	if(ask_num == 0){
		node *tmp = create_nodes(nnodes, ask2);
		bdisplay_nodes(tmp, nnodes);
		bfree_nodes(tmp);
	}
	if(ask_num == 1){
		node *tmp = create_nodes(nnodes, ask1);
		fdisplay_nodes(tmp);
		ffree_nodes(tmp);
	}
	return 0;
}
