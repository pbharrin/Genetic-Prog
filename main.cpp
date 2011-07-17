//			
#include <iostream>
#include <cmath>
#include <time.h>
#include "basicFunctions.h"
#include "treeGeneOps.h"
#include "tools.h"

using namespace std;

const int NUM_INIT_TREES = 300;
const int NUM_GENERATIONS = 15;
const int NUM_DIE_PER_GEN = 90; //how much of the pop we loose per generation

int getRandSurvior();

int main (int argc, char * const argv[]) {
	srand(time(NULL));  //seed the RNG
	double sumAbsErr, err = 0.0;
	//create array to store N trees
	GOftn* initTrees[NUM_INIT_TREES];

	const int NUM_INPUTS = 9;
	double inputs[NUM_INPUTS] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	double outputs[NUM_INPUTS] = {6, 15, 28, 45, 66, 91, 120, 153, 190}; //2x^2 + 3x + 1
	
	// create the inital tree population 
	for (int i=0; i<NUM_INIT_TREES; i++){
		initTrees[i] = createRandomTree();
	}
	
	for (int gen=0; gen<NUM_GENERATIONS; gen++) {
		// test the performance of each one
		// this should be problem-dependent, and implemented in another file
		for (int i=0; i<NUM_INIT_TREES; i++){
			sumAbsErr = 0.0;
			for (int j=0; j<NUM_INPUTS; j++) {
				err = outputs[j] - (initTrees[i]->eval(inputs[j]));
				sumAbsErr += abs(err);
			}
			PRINTD("evaluating tree %d: %f \n", i, sumAbsErr);
			if (sumAbsErr == 0){
				printf("found a solution with 0 error\n");
				printTree(initTrees[i]);
				break;
			}
			if (isnan(sumAbsErr)) sumAbsErr = 1E+37; //max double val
			initTrees[i]->perfScore = sumAbsErr;
		}
		
		//sort by performance (sort in increasing order so we work on first N)
		sort(initTrees, initTrees + NUM_INIT_TREES, treeSortPredIncre);
		
		for (int i=0; i<NUM_DIE_PER_GEN; i++){
			deleteTree(initTrees[i]);			//toss out losers
			//randomly select one of the survivors and clone
			initTrees[i] = initTrees[getRandSurvior()]->clone();
			//do cross over with survivors 
			//crossOver(initTrees[i], initTrees[getRandSurvior()]);
			crossOver(initTrees[i], initTrees[NUM_INIT_TREES - 1]);  //cross over with best
			mutateTree(&initTrees[i]);	//mutate
		}
		printf("Generation %d the best score is: %f\n", gen, initTrees[NUM_INIT_TREES - 1]->perfScore);
	}
	printTree(initTrees[NUM_INIT_TREES - 1]);
    return 0;
}
int getRandSurvior(){
	int randn = rand() % (NUM_INIT_TREES - NUM_DIE_PER_GEN);
	return (NUM_DIE_PER_GEN + randn);
}