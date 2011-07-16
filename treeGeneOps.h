/*
 *  treeGeneOps.h
 *  GeneticProg
 *
 *  Created by Peter Harrington on 7/15/11.
 *  Copyright 2011 Clean Micro, LLC. All rights reserved.
 *
 *	This file includes functions for basic tree genetic operations.
 *	These operations are cross over, mutation, creating a tree, 
 *	deleting a tree and printing a tree.  
 *
 */
#include "basicFunctions.h"

GOftn* createRandomNode(int depth);
GOftn* createRandomTree(int depth=0);
void printTree(GOftn* inTree, int depth=0);
void mutateTree(GOftn** inTree, int depth=0);
void crossOver(GOftn* treeToAlter, GOftn* donatingTree);
void deleteTree(GOftn* inTree);
bool treeSortPredIncre(GOftn* t1, GOftn* t2);