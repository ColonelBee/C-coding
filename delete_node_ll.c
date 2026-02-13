/*
Create a linked list and program how to:
1. Delete the 1st node of the list.
2. Delete the last node of the list.
3. Delete a specified node of the list, except the 1st and the last one.
*/

#include <stdio.h>
#include <stdlib.h>

// Step 0: template of each node
typedef struct node{
	int data;
	struct node *nxnode;
}node;

// global input data
int in;

// Step 1: create a singly linked list based on the input number of nodes
node *create(int nnodes){
	// handle the 1st node
	node *i = malloc(sizeof(struct node));
	if(i == NULL) return NULL;
	fprintf(stdout, "Input for node 1: ");
	fscanf(stdin, "%i", &in);
	i->data = in;
	i->nxnode = NULL;
	// handle the 2nd node and the others
	// store the last node
	node *tmp = NULL;
	for(int j = 2; j <= nnodes; j++){
		node *k = malloc(sizeof(struct node));
		if(j == 2) i->nxnode = k;
		else tmp->nxnode = k;
		fprintf(stdout, "Input for node %i: ", j);
		fscanf(stdin, "%i", &in);
		k->data = in;
		k->nxnode = NULL;
		tmp = k; // this can be the address of the last node
	}
	return i; // return the 1st node
}

// Additional step: delete the 1st node
node* dlt_1stnode(node *start){
	node *begin = start;
	node *tp = begin->nxnode;
	free(begin);
	return tp; // return the 2nd node
}

// Additional step: delete the last node
void dlt_lastnode(node *start){
	if(start == NULL) return;
	if(start->nxnode == NULL){
		free(start);
		return;
	}
	node *st = start;
	node *lst = NULL;
	// loop until we find the last node
	while(st->nxnode != NULL){
		lst = st;
		st = st->nxnode;	
	}
	// the node right before the last node
	lst->nxnode = NULL;
	free(st);
}

// Additional step: delete a specified node by an input node number
void dlt_spc_node(node *start, int node_spec){
	node *hold = start;
	node *touch = NULL;
	int count = 1;
	for(; hold != NULL; hold = hold->nxnode){
		if(count == node_spec - 1) touch = hold;
		if(count == node_spec){
			touch->nxnode = hold->nxnode;
			free(hold);
			break;
		}
		count++;
	}
}

// Step 2: display all the nodes
void display(node *start){
	node *k = start;
	int m = 1;
	fprintf(stdout, "\nData entered the list:\n");
	for(; k != NULL; k = k->nxnode)
		fprintf(stdout, "Data of node %i: %i\n", m++, k->data);
}

// Step 3: free nodes after dynamic memory allocation
void nfree(node *start){
	node *h = start;
	node *next = NULL;
	for(; h != NULL; h = next){
		next = h->nxnode;
		free(h);
	}
}

int main(){
	int nnodes;
	fprintf(stdout, "Input the number of nodes: ");
	fscanf(stdin, "%i", &nnodes);
	node *make = create(nnodes);
	fprintf(stdout, "================================================================\n");
	fprintf(stdout, "Please choose one the following options. Do you want to:\n");
	fprintf(stdout, "1. Delete the first node of the list?\n");
	fprintf(stdout, "2. Delete the last node of the list?\n");
	fprintf(stdout, "3. Delete a specified node of the list? (apart from the 1st and the last ones)\n");
	fprintf(stdout, "4. Keep everything unchanged and print out the list\n");
	fprintf(stdout, "\nEnter your option: ");
	int option;
	fscanf(stdin, "%i", &option);
	if(option == 1){
		node *dlt = dlt_1stnode(make); // delete the 1st node
		display(dlt);
		nfree(dlt);
	}
	else if(option == 2){
		dlt_lastnode(make); // delete the last node
		display(make);
		nfree(make);
	}
	else if(option == 3){
		int node_spec;
		fprintf(stdout, "Enter the node to delete: ");
		fscanf(stdin, "%i", &node_spec);
		dlt_spc_node(make, node_spec); // delete the specified node
		display(make);
		nfree(make);
	}
	else if(option == 4){
		display(make);
		nfree(make);
	}
	else fprintf(stdout, "Invalid option. Please try again!\n");
	fprintf(stdout, "================================================================\n");
	return 0;
}
