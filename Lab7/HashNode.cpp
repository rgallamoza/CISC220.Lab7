/*
 * HashNode.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: ryan
 */

#include <iostream>
#include <stdlib.h>
#include "HashNode.hpp"
using namespace std;

hashNode::hashNode(){
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;
}

hashNode::hashNode(string s){
	keyword = s;
	valuesSize = 100;
	currSize = 0;
	values = new string[valuesSize];
}

hashNode::hashNode(string s,string v){
	keyword = s;
	valuesSize = 100;
	currSize = 1;
	values = new string[valuesSize];
	values[0] = v;
}

void hashNode::addValue(string v){
	values[currSize] = v;
	currSize++;

	if(currSize==valuesSize){
		dblArray();
	}
}

void hashNode::dblArray(){
	string *tmp = new string[valuesSize*2];

	for(int i=0;i<valuesSize;i++){
		tmp[i] = values[i];
	}

	valuesSize *= 2;
	values = tmp;
}

string hashNode::getRandValue(){
	if (currSize==0){
		return "";
	}
	else{
		return values[rand()%currSize];
	}
}

void hashNode::printHNode(){
	cout << keyword << ":";
	for(int i=0;i<currSize;i++){
		cout << values[i] << ",";
	}
	cout << endl;
}
