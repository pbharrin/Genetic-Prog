/*
 *  basicFunctions.h
 *  GeneticProg
 *
 *  Created by Peter Harrington on 7/1/11.
 *  Copyright 2011 Clean Micro, LLC. All rights reserved.
 
 * To Do:
	Transforms to add:
	[ ] Lag
	[ ] input^2
	[ ] sqrt
	[ ] ln
 *
 */

#ifndef BASIC_FTNS_H
#define BASIC_FTNS_H 1

#include <string>
using namespace std;

//Master abstract class: GOftn: Genetic Optimize Function
class GOftn
{	
public:
	string label;
	int numChildren;
	GOftn* children[];
	GOftn() { } // to be used later
	virtual ~GOftn() { } // to be used later
	virtual double eval(double inVal) = 0;  //setting the 0 makes it a PURE
	virtual GOftn* clone() = 0; //make a deep copy of the current tree
	virtual string getLabel() = 0;
};

//class for storing constant values
class ConstNode : public GOftn {
	double constVal;
public:
	ConstNode();
	ConstNode(double preSetVal);
	virtual double eval(double inVal);
	ConstNode* clone();
	virtual string getLabel();
};

//class for using inputs
class InputNode : public GOftn {
	int inputIndex;
public:
	InputNode(int numPossibleInputs);
	virtual double eval(double inVal);
	InputNode* clone();
	void setValues(int inIndex);
	virtual string getLabel();
};

//addition
class Add : public GOftn {
public:
	Add();
	GOftn* children[2];
	virtual double eval(double inVal);
	Add* clone();
	virtual string getLabel();
};

//subtraction
class Subtract : public GOftn {
public:
	Subtract();
	GOftn* children[2];
	virtual double eval(double inVal);
	Subtract* clone();
	virtual string getLabel();
};
//multiplication
class Multiply : public GOftn {
public:
	Multiply();
	GOftn* children[2];
	virtual double eval(double inVal);
	Multiply* clone();
	virtual string getLabel();
};
//division
class Divide : public GOftn {
public:
	Divide();
	GOftn* children[2];
	virtual double eval(double inVal);
	Divide* clone();
	virtual string getLabel();
};

#endif