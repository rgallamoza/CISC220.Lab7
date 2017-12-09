/*
 * Lab7main.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: ryan
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "MakeSeuss.hpp"
using namespace std;

int main(){
	srand(time(NULL));

	makeSeuss ms1 = makeSeuss("DrSeuss.txt","Output1.txt",false,true);

	return 0;
}


