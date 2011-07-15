#include <iostream>
#include <time.h>
#include "basicFunctions.h"
#include "treeGeneOps.h"

using namespace std;

const int NUM_INIT_TREES = 2;

int main (int argc, char * const argv[]) {
	srand(time(NULL));  //seed the RNG
	//create array to store N trees
	GOftn* initTrees[NUM_INIT_TREES];
	GOftn* cloneTrees[NUM_INIT_TREES];
	int inputs[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int outputs[10] = {1, 6, 15, 28, 45, 66, 91, 120, 153, 190}; //2x^2 + 3x + 1
	
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
	
	/*
	//toss out losers
	//deleteTree(initTrees[0]);
	//copy, mutate and crossover winners
	for (int i=0; i<NUM_INIT_TREES; i++){
		printf("cloning tree %d:\n", i);
		cloneTrees[i] = initTrees[i]->clone();
		mutateTree(&cloneTrees[i]);
	}
	*/
	
	printf("crossover between tree 0 and 1\n");
	GOftn* crossOverTree;
	crossOverTree = initTrees[1]->clone();
	crossOver(crossOverTree, initTrees[0]);
	printTree(crossOverTree);
	
	/*
	for (int i=0; i<NUM_INIT_TREES; i++){
		printf("clone tree %d:\n", i);
		printTree(cloneTrees[i]);
	}
	printf("original tree %d:\n", 0);
	printTree(initTrees[0]);
	*/
	
    return 0;
}