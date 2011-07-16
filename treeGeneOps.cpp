/*
 *  treeGeneOps.cpp
 *  GeneticProg
 *
 *  Created by Peter Harrington on 7/15/11.
 *  Copyright 2011 Clean Micro, LLC. All rights reserved.
 *
 *	[X] TO DO: crossover
 *
 */
#include <iostream>
#include "treeGeneOps.h"
#include "tools.h"

using namespace std;

const int NUM_INPUTS = 1;
const int MAX_TREE_DEPTH = 4; 
const double MUTATION_THRESH = 0.1;
void crossOver(GOftn* treeToAlter, GOftn* donatingTree){
	if ((treeToAlter->numChildren > 0) && (donatingTree->numChildren > 0)) {
		int childToAlter = rand() % treeToAlter->numChildren;//randomly select side of treeToAlter and donatingTree
		int childToDonate = rand() % donatingTree->numChildren;
		deleteTree(treeToAlter->children[childToAlter]);//delete side of treeToAlter
		treeToAlter->children[childToAlter] = (donatingTree->children[childToDonate])->clone();//clone side of donatingTree
	}
	else PRINTD("not enough child nodes to do crossover\n");
}

void mutateTree(GOftn** inTree, int depth){
	double randNum0t1 = rand()/(double)RAND_MAX;
	if (randNum0t1 < MUTATION_THRESH) {
		PRINTD("SHOULD MUTATE\n");
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
bool treeSortPredIncre(GOftn* t1, GOftn* t2){
	return t1->perfScore > t2->perfScore;
}