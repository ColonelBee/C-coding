/*
Insert a node in a singly linked list with 4 options:
	1. Prepend the 1st node with a new node.
	2. Append the last node with a new node.
	3. Append a specified node with a new node.
	4. Do nothing with the current list.
*/

#include <stdio.h>
#include <stdlib.h>

// Step 0: template of a singly linked list
typedef struct node{
	int data;
	struct node *nxnode;
}node;

// global input data
int in;
// store address of the last node
node *tmp = NULL; 
// Step 1: create nodes (lists) according to the input number of nodes then link them together
node* create(int nnodes){
	// create the 1st node
	node *i = malloc(sizeof(struct node));
	if(i == NULL) return NULL;
	fprintf(stdout, "Input data for node 1: ");
	fscanf(stdin, "%i", &in);
	i->data = in;
	i->nxnode = NULL;
	// from node 2
	int n = 2;
	for(int a = 1; a < nnodes; a++){
		node *j = malloc(sizeof(struct node));
		if(a == 1) i->nxnode = j; // node 1 points to node 2
		else tmp->nxnode = j;
		fprintf(stdout, "Input data for node %i: ", n++);
		fscanf(stdin, "%i", &in); 
		j->data = in;
		j->nxnode = NULL;
		tmp = j;
	}
	return i; // return the first node
}

// Step 3: display nodes
void display(node *start){
	node *k = start;
	int m = 1;
	fprintf(stdout, "\nData entered the list:\n");
	for(; k != NULL; k = k->nxnode)
		fprintf(stdout, "Data of node %i: %i\n", m++, k->data);
}

// Step 4: free nodes after dynamic memory allocation
void nfree(node *start){
	node *h = start;
	node *next = NULL;
	for(; h != NULL; h = next){
		next = h->nxnode;
		free(h);
	}
}

// Additional step: prepend the first node
node *prp_1stnode(node *start){
	node *t = start;
	fprintf(stdout, "Input data for prepended node: ");
	fscanf(stdin, "%i", &in);
	node *x = malloc(sizeof(struct node));
	x->data = in;
	x->nxnode = t;
	return x; // return the new first node
}

// Additional step: append the last node
void appd_lstnode(node *start){
	node *r = start;
	for(; r != NULL; r = r->nxnode){
		if(r == tmp){
			node *w = malloc(sizeof(struct node));
			fprintf(stdout, "Input data for the last appended node: ");
			fscanf(stdin, "%i", &in);
			w->data = in;
			tmp->nxnode = w;
			w->nxnode = NULL;
		}
	}
}

// Additional Step: Insert a node after a specified node
node *apd_rand_node(node *start, int node_to_apd){
	node *f = start;
	int cnt = 1;
	for(; f != NULL; f = f->nxnode){
		if(cnt == node_to_apd){
			node *g = f->nxnode; // store the address of the next node first 
			node *nw = malloc(sizeof(struct node));
			fprintf(stdout, "Input data for node %i: ", node_to_apd + 1);
			fscanf(stdin, "%i", &in);
			nw->data = in;
			f->nxnode = nw;
			nw->nxnode = g;
			break;
		}
		cnt++;
	}
	return start;
}
int main(){	
	fprintf(stdout, "Input the number of nodes: ");
	int nnodes;
	fscanf(stdin, "%i", &nnodes);
	node *p = create(nnodes);
	fprintf(stdout, "============================================\n");
	fprintf(stdout, "Choose one of the options. Do you want to:\n");
	fprintf(stdout, "1. Prepend the 1st node with a new node?\n");
	fprintf(stdout, "2. Append the last node with a new node?\n");
	fprintf(stdout, "3. Append a specified node with a new node?\n");
	fprintf(stdout, "4. Do nothing with the current list.\n");
	fprintf(stdout, "\nEnter your option: ");
	int options;
	fscanf(stdin, "%i", &options);
	if(options == 1){
		node *prp = prp_1stnode(p);
		display(prp);
		nfree(prp);
	}
	else if(options == 2){
		appd_lstnode(p);
		display(p);
		nfree(p);
	}
	else if(options == 3){
		int node_to_apd;
		fprintf(stdout, "\nInput the node you want to append: ");
		fscanf(stdin, "%i", &node_to_apd);
		node *app_rand = apd_rand_node(p, node_to_apd);
		display(p);
		nfree(p);
	}
	else if(options == 4){ 
		display(p);
		nfree(p);
	}
	else fprintf(stdout, "Invalid options. Please try again!\n");
	fprintf(stdout, "============================================\n");
	return 0;
}
