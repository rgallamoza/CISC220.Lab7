/*
 * HashMap.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: ryan
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include "HashMap.hpp"
using namespace std;

bool isPrime(int x);

hashMap::hashMap(bool hash1,bool coll1){
	first = "";
	numKeys = 0;
	mapSize = 27;
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;

	map = new hashNode*[mapSize];
	for(int i=0;i<mapSize;i++){
		map[i] = NULL;
	}
}

void hashMap::addKeyValue(string k,string v){
	int index = getIndex(k);

	if(map[index]==NULL){
		map[index] = new hashNode(k,v);
		numKeys++;
	}
	else{
		map[index]->addValue(v);
	}

	if(numKeys>=0.7*mapSize){
		reHash();
	}
}

int hashMap::getIndex(string k){
	int index;

	if(h1){
		index = calcHash(k);
	}
	else{
		index = calcHash2(k);
	}

	if(map[index]==NULL||map[index]->keyword==k){
		return index;
	}
	else{
		collisionct1++;
		if(c1){
			return collHash1(index,k);
		}
		else{
			return collHash2(index,k);
		}
	}
}

int hashMap::calcHash(string k){	//Hash function treats first 3 characters as base-256 integers (based on ASCII values)
	int index = 0;

	for(int i=0;i<3&&i<k.length();i++){
		index += pow(256,i)*int(k[i]);
	}

	return index%mapSize;
}

int hashMap::calcHash2(string k){	//Hash function finds sum of ASCII values
	int index = 0;

	for(int i=0;i<k.length();i++){
		index += int(k[i]);
	}

	return index%mapSize;
}

void hashMap::getClosestPrime(){
	int dblSize = 2*mapSize;
	int less = 0;
	int greater = 0;

	for(int i=dblSize-1;less==0;i--){
		if(isPrime(i)){
			less = i;
		}
	}

	for(int i=dblSize+1;greater==0;i++){
		if(isPrime(i)){
			greater = i;
		}
	}

	if(dblSize-less<greater-dblSize){
		mapSize = less;
	}
	else{
		mapSize = greater;
	}
}

bool isPrime(int x){	//Helper function for finding closest prime
	bool a = true;
	int divisor = 2;
	if(x>1){
		while((divisor < x) && a){
				if (x % divisor == 0){
					a = false;
				}
				divisor++;
			}
	}
	else{
		a = false;
	}

	return a;
}

void hashMap::reHash(){
	int initSize = mapSize;
	int newIndex;

	getClosestPrime();

	hashNode **tmp = map;

	map = new hashNode*[mapSize];
	for(int i=0;i<mapSize;i++){
		map[i] = NULL;
	}

	for(int i=0;i<initSize;i++){
		if(tmp[i]!=NULL){
			newIndex = getIndex(tmp[i]->keyword);
			map[newIndex] = tmp[i];
		}
	}
}

int hashMap::collHash1(int h,string k){	//Linear probing
	int index = h;

	while(map[index]!=NULL){
		if(map[index]->keyword==k){
			break;
		}

		collisionct2++;
		if(index==mapSize-1){
			index = 0;
		}
		else{
			index++;
		}
	}

	return index;
}

int hashMap::collHash2(int h,string k){	//Quadratic probing
	int index = h;
	int i = 0;

	while(map[index]!=NULL){
		if(map[index]->keyword==k){
			break;
		}

		collisionct2++;
		i++;
		index = (h+(i*i))%mapSize;
	}

	return index;
}

int hashMap::findKey(string k){
	for(int i=0;i<mapSize;i++){
		if(map[i]->keyword==k){
			return i;
		}
	}
	return -1;
}

void hashMap::printMap(){
	cout << "Map:" << endl;
	for(int i=0;i<mapSize;i++){
		if(map[i]!=NULL) map[i]->printHNode();
	}
	cout << endl;
	cout << "First keyword: " << first << endl;
	cout << "numKeys: " << numKeys << endl;
	cout << "mapSize: " << mapSize << endl;
	cout << "h1: " << h1 << endl;
	cout << "c1: " << c1 << endl;
	cout << "collisionct1: " << collisionct1 << endl;
	cout << "collisionct2: " << collisionct2 << endl;
}
