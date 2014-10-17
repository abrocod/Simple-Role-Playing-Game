#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <typeinfo>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <stdlib.h> 
#include <time.h>
#include "object2.h"
#include "display2.h"

struct Coordinate {
	int ew, ns;
};

class Object; // forward declaration
class Display;

class Floor {
	public: // TEMP, ADD GETTER FUNCTION
	int PC_Chamber;  // store in which Chamber the PC is generated
    int PC_Position; // get current position of PC
    
    char deleted_stuff;
    bool game_over;
    bool join_next_floor;
    std::ostringstream message_to_print;
    std::vector<int> NPC_pos; // to store the position of NPC
	std::vector<Object*> floor_vec;
	std::vector<std::vector<int> > chamber_vec;
    //ASFDASDFASFDASFAFASDF
    Inventory inventory;
    //AFADSFDASFDSFASFSAFAF
	Display* disp;
	
	public:
	Floor(Display& display);
    ~Floor(); // NEED TO WRITE IT!
	
	void generate_PC(std::string name, std::string username);
	void generate_NPC(std::string name);
	void generate_stair();
	void generate_potion(int type);
	void generate_gold(int type);
    void generate_Dragon(int index);

    
	void PC_move(int dir);
		// representation of direction: 
		// no,so,ea,we,ne,nw,se,sw
		// 0=no, 1=nw, 2=we, 3=sw,
		// 4=so, 5=se, 6=ea, 7=ne,
		
    bool NPC_around(int index);
    /*NPC_around:
    this method allows NPC to check if there is PC around him when NPC tries
    to move, if so , returns true to make NPC attack and not move until PC leaves
    if there is no PC around, NPC just regularly moves to random spot around it.
     */
	void NPC_move();
    /* NPC_move()
    firstly, NPC_move will check surrounding spots to make sure there is no PC around(
    if there is, attack PC and not move), if there is no PC around, do regular move
    */
    int search_PC(int index);
    void NPC_smart_move();
    
    
    void NPC_skill(int index,int &raw_damage);
    
    
    void PC_Attack(int dir);
    /* PC_Attack:
    called when player gives attack command.This function will check the target spot
    first to make sure there is something to attack, if there is no NPC in target spot,
    print out error message and do nothing. IF there is NPC, call attack method.
     */
	void PC_Pickup_Potion(int dir);
	
    void PC_Pickup_inventory(int dir);
	// Helper method:
    int check_surrounding(int index);
	int find_empty_spot();  
	int find_chamber(int index);
	void notify_display(int index, char symbol, Display& display);
	void delete_spot(int index);
    void stupid_copy(int copy_index, int target_index);//pretty stupid copy method
    void move_to_that_place(int &cur_index, int fut_index);
    /* move_to_that_place
    this method is a helper method to help PC and NPC to move
     
    
    */
    int check_spot1(int index, int dir);
        // this version is called by PC_pickup
        // calculate future index use convert_direction_to_index(int dir, int index)
        // check if future index can be picked up
        // if yes then convert future coord into future index then return it
        // if not, return -1
	int check_spot2(int index, int dir); 
		// this version is called by PC/NPC_move
		// calculate future index use convert_direction_to_index(int dir, int index)
		// check if future index is move-able
		// if yes then convert future coord into future index then return it
		// if it is not place can move to, return -1
		
    
    void PC_item_detect();
	int convert_direction_to_index(int dir, int index);
		// first convert index into coordinate
		// then perform calculate
		// convert back to index
		
	int convert_coordinate_to_index(Coordinate coord, int num_col);
	Coordinate convert_index_to_coordinate(int index, int num_col);
	
    // Print method helper:
    // to report error or information;

    
    //void pick_up_error();
    
    // helper function for attack:
    void attack(int attacker, int victim);
    PC* join_nextfloor();
    void corpse_clear(int pos);
    bool* get_jnf();
    void show_inventory();
    void use_inventory(int pos);
	void gameover();
};





#endif
