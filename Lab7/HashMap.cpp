/*
 * HashMap.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: ryan
 */

#include <iostream>
#include <stdlib.h>
#include "HashMap.hpp"
using namespace std;

hashMap::hashMap(bool hash1,bool coll1){
	map = NULL;
	first = NULL;
	numKeys = 0;
	mapSize = 0;
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;
}

void hashMap::addKeyValue(string k,string v){

}

int hashMap::getIndex(string k){

}

int hashMap::calcHash(string k){

}

int hashMap::calcHash2(string k){

}

void hashMap::getClosestPrime(){

}

void hashMap::reHash(){

}

int hashMap::collHash1(int h,int i,string k){

}

int hashMap::collHash2(int h,int i,string k){

}

int hashMap::findKey(string k){

}

void hashMap::printMap(){

}
