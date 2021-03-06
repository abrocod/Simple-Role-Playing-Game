#ifndef __DISP_H__
#define __DISP_H__

#include <iostream>
#include <string>

#include <vector>
 const int NUM_COL = 79;
const int NUM_ROW = 25;
 const int VEC_LENGTH = 1975;

struct Display {
	// the actual display map
	std::vector<char> display_vec; 
	// std::vector<int> display_chamber_vec; // same as chamber_array
	//typedef std::vector<int> vecint;
	std::vector<std::vector<int> >  display_chamber_vec;
	
	int length_ch1;
	int length_ch2;
	int length_ch3;
	int length_ch4;
	int length_ch5;
	
	std::vector<int> chamber1_vec;
	std::vector<int> chamber2_vec;
	std::vector<int> chamber3_vec;
	std::vector<int> chamber4_vec;
	std::vector<int> chamber5_vec;
	

	// ctor:
	Display();
	// use built-in default map
	
	// DO IT LATER:
	// Display(...) // use import map
	
	// NO NEED destructor, since nothing is heap allocated
	
	// method:
	void notified(int index, char symbol);		
	void prettyprint();

};


















#endif
