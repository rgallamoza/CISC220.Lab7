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
	int hash = getIndex(k);

	if(map[hash]==NULL){
		map[hash] = new hashNode(k,v);
		numKeys++;
	}
	else if(map[hash]->keyword==k){
		map[hash]->addValue(v);
	}
	else{
		int cHash;
		if(c1){
			cHash = collHash1(hash,k);
		}
		else{
			cHash = collHash2(hash,k);
		}

		if(map[cHash]==NULL){
			map[cHash] = new hashNode(k,v);
			numKeys++;
		}
		else{
			map[cHash]->addValue(v);
		}
	}

	if(numKeys>=0.7*mapSize){
		reHash();
	}
}

int hashMap::getIndex(string k){
	if(h1){
		return calcHash(k);
	}
	else{
		return calcHash2(k);
	}
}

int hashMap::calcHash(string k){	//Hash is sum of first 3 characters as base-37 integers
	string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
	int hash = 0;

	for(int i=0;i<3&&i<k.length();i++){
		if(!isalnum(k[i])){
			continue;
		}
		else{
			hash += pow(37,i)*chars.find(k[i]);
		}
	}

	return hash%mapSize;
}

int hashMap::calcHash2(string k){	//Hash based on sum of ASCII values
	int hash = 0;

	for(int i=0;i<k.length();i++){
		hash += int(k[i]);
	}

	return hash%mapSize;
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
	int newHash;

	getClosestPrime();

	hashNode **tmp = map;

	map = new hashNode*[mapSize];
	for(int i=0;i<mapSize;i++){
		map[i] = NULL;
	}

	for(int i=0;i<initSize;i++){
		if(tmp[i]!=NULL){
			newHash = getIndex(tmp[i]->keyword);
			if(map[newHash]==NULL){
				map[newHash] = tmp[i];
			}
			else if(c1){
				int cHash = collHash1(newHash,tmp[i]->keyword);
				map[cHash] = tmp[i];
			}
			else{
				int cHash = collHash2(newHash,tmp[i]->keyword);
				map[cHash] = tmp[i];
			}
		}
	}
}

int hashMap::collHash1(int h,string k){	//Linear probing
	int hash = h;

	while(map[hash]!=NULL){
		if(map[hash]->keyword==k){
			break;
		}

		collisionct1++;
		if(hash==mapSize-1){
			hash = 0;
		}
		else{
			hash++;
		}
	}

	return hash;
}

int hashMap::collHash2(int h,string k){	//Quadratic probing
	int hash = h;
	int i = 0;

	while(map[hash]!=NULL){
		if(map[hash]->keyword==k){
			break;
		}

		collisionct2++;
		hash -= (i*i);
		i++;
		hash += (i*i);
		while(hash>=mapSize){
			hash -= mapSize;
		}
	}

	return hash;
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
	for(int i=0;i<mapSize;i++){
		if(map[i]!=NULL) cout << map[i]->keyword<<endl;
	}
}
