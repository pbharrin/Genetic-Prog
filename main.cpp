#include <iostream>
#include <time.h>
#include "basicFunctions.h"

using namespace std;

GOftn* createRandomNode(int depth);
GOftn* createRandomTree(int depth=0);
void printTree(GOftn* inTree, int depth=0);
void mutateTree(GOftn** inTree, int depth=0);
void deleteTree(GOftn* inTree);

const int NUM_INIT_TREES = 1;
const int NUM_INPUTS = 1;
const int MAX_TREE_DEPTH = 4; 
const double MUTATION_THRESH = 0.1;

int main (int argc, char * const argv[]) {
	srand(time(NULL));  //seed the RNG
	//create array to store N trees
	GOftn* initTrees[NUM_INIT_TREES];
	GOftn* cloneTrees[NUM_INIT_TREES];
	
	// create the inital tree population 
	for (int i=0; i<NUM_INIT_TREES; i++){
		printf("creating tree: %d \n", i);
		initTrees[i] = createRandomTree();
		printTree(initTrees[i]);
	}
	// test the performance of each one
	for (int i=0; i<NUM_INIT_TREES; i++){
		printf("evaluating tree %d: %f \n", i, initTrees[i]->eval(1.0));
	}
	
	//toss out losers
	//deleteTree(initTrees[0]);
	
	//copy and mutate winners
	
	for (int i=0; i<NUM_INIT_TREES; i++){
		printf("cloning tree %d:\n", i);
		cloneTrees[i] = initTrees[i]->clone();
		mutateTree(&cloneTrees[i]);
	}
	for (int i=0; i<NUM_INIT_TREES; i++){
		printf("clone tree %d:\n", i);
		printTree(cloneTrees[i]);
	}
	printf("original tree %d:\n", 0);
	printTree(initTrees[0]);
	
    return 0;
}
void mutateTree(GOftn** inTree, int depth){
	double randNum0t1 = rand()/(double)RAND_MAX;
	if (randNum0t1 < MUTATION_THRESH) {
		printf("SHOULD MUTATE\n");
		//create new node
		GOftn* newNode = createRandomNode(depth + 1);//create a random node to replace current node
		int childrenToMove = min(newNode->numChildren, (*inTree)->numChildren);
		for (int i=0; i<childrenToMove; i++){
			newNode->children[i] = (*inTree)->children[i];
		}
		int numNewChildren = newNode->numChildren - childrenToMove;
		for (int i=childrenToMove; i<(childrenToMove + numNewChildren); i++){
			newNode->children[i] = createRandomTree(depth + 1);
		}
		free(*inTree);		//free memory held by old node
		*inTree = newNode;	//replace old ptr with ptr to new
	}
	for (int i=0; i<(*inTree)->numChildren; i++) {
		mutateTree(&(*inTree)->children[i], depth + 1);
	}
}
void printTree(GOftn* inTree, int depth){
	for (int j=0; j<depth; j++) {
		printf("..");
	}
	//printf("%s\n", inTree->label.c_str());
	cout << inTree->label.c_str() <<endl;
	for (int i=0; i<inTree->numChildren; i++) {
		printTree(inTree->children[i], depth+1);
	}
}
GOftn* createRandomTree(int depth){
	GOftn* retFtn = createRandomNode(depth);

	for (int i=0; i < retFtn->numChildren; i++) {
		retFtn->children[i] = createRandomTree(depth+1);
	}
	return retFtn;
}
GOftn* createRandomNode(int depth){
	int randn = 0;
	int numFtnChoices = 2;
	GOftn* retFtn;
	
	if (depth < MAX_TREE_DEPTH) numFtnChoices = 6;  //if the depth is greater than 3 only allow const or inputs
	randn = rand() % numFtnChoices;		//generate random int
	
	switch (randn) {	//move random 
		case 0:
			retFtn = new ConstNode();
			break;
		case 1:
			retFtn = new InputNode(NUM_INPUTS);
			break;
		case 2:
			retFtn = new Add();
			break;
		case 3:
			retFtn = new Subtract();
			break;
		case 4:
			retFtn = new Multiply();
			break;
		case 5:
			retFtn = new Divide();
			break;
		default:
			cerr<<"invalid random number, bad news\n\n\n";
			break;
	}
	return retFtn;
}
void deleteTree(GOftn* inTree){
	for (int i=0; i<inTree->numChildren; i++) {  //free any children first
		deleteTree(inTree->children[i]);
	}
	free(inTree);
}
