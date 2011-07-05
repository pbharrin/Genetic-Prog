/*
 *  basicFunctions.cpp
 *  GeneticProg
 *
 *  Created by Peter Harrington on 7/1/11.
 *  Copyright 2011 Clean Micro, LLC. All rights reserved.
 *
 */
#include <iostream>
#include "basicFunctions.h"
using namespace std;

//
//		ConstNode
//
ConstNode::ConstNode(){
	numChildren = 0;
	constVal = rand()/(double)RAND_MAX;
	char str[20] = "";
	sprintf(str, "Const: %f", constVal);
	label = str;
}
ConstNode::ConstNode(double preSetVal){
	numChildren = 0;
	constVal = preSetVal;
	char str[20] = "";
	sprintf(str, "Const: %f", constVal);
	label = str;
}
double ConstNode::eval(double inVal){
	return constVal;
}
ConstNode* ConstNode::clone(){
	ConstNode* retTree = new ConstNode(constVal);
	return retTree; 
}
string ConstNode::getLabel(){
	return label;
}
//
//		InputNode
//
InputNode::InputNode(int numPossibleInputs){
	numChildren = 0;
	inputIndex = rand() % numPossibleInputs;
	setValues(inputIndex);
}
double InputNode::eval(double inVal){
	return inVal;
}
void InputNode::setValues(int inIndex){
	char str[20] = "";
	sprintf(str, "InputVal: %d", inIndex);
	label = str;
}
InputNode* InputNode::clone(){
	InputNode* retTree = new InputNode(1);
	retTree->setValues(inputIndex);
	return retTree; 
}
string InputNode::getLabel(){
	return label;
}
//
//		Add
//
Add::Add(){
	numChildren = 2;
	label = "Add";
}
double Add::eval(double inVal){
	if (children[0] && children[1]){
		return children[0]->eval(inVal) + children[1]->eval(inVal);
	}
	else {
		cerr << "left and right not defined in add"<<endl;
		return -1.0;
	}
}
Add* Add::clone(){
	Add* retNode = new Add();
	for (int i=0; i<numChildren; i++) {
		retNode->children[i] = children[i]->clone();
	}
	return retNode;
}
string Add::getLabel(){
	return label;
}
//
//		Subtract
//
Subtract::Subtract(){
	numChildren = 2;
	label = "Subtract";
}
double Subtract::eval(double inVal){
	if (children[0] && children[1]){
		return children[0]->eval(inVal) - children[1]->eval(inVal);
	}
	else {
		cerr << "left and right not defined in subtract"<<endl;
		return -1.0;
	}
}
Subtract* Subtract::clone(){
	Subtract* retNode = new Subtract();
	for (int i=0; i<numChildren; i++) {
		retNode->children[i] = children[i]->clone();
	}
	return retNode;
}
string Subtract::getLabel(){
	return label;
}
//
//		Multiply
//
Multiply::Multiply(){
	numChildren = 2;
	label = "Multiply";
}
double Multiply::eval(double inVal){
	if (children[0] && children[1]){
		return children[0]->eval(inVal) * children[1]->eval(inVal);
	}
	else {
		cerr << "left and right not defined in multiply"<<endl;
		return -1.0;
	}
}
Multiply* Multiply::clone(){
	Multiply* retNode = new Multiply();
	for (int i=0; i<numChildren; i++) {
		retNode->children[i] = children[i]->clone();
	}
	return retNode;
}
string Multiply::getLabel(){
	return label;
}
//
//		Divide
//
Divide::Divide(){
	numChildren = 2;
	label = "Divide";
}
double Divide::eval(double inVal){
	if (children[0] && children[1]){
		return children[0]->eval(inVal) / children[1]->eval(inVal);
	}
	else {
		cerr << "left and right not defined in multiply"<<endl;
		return -1.0;
	}
}
Divide* Divide::clone(){
	Divide* retNode = new Divide;
	for (int i=0; i<numChildren; i++) {
		retNode->children[i] = children[i]->clone();
	}
	return retNode;
}
string Divide::getLabel(){
	return label;
}