#include "floor2.h"

using namespace std;

Floor::Floor(Display& display) {
	for (int i=0; i<VEC_LENGTH; i++) {
		
		if (display.display_vec.at(i) == '.') {
			floor_vec.push_back(new Tile(i));
		} else if (display.display_vec.at(i) == '|') {
			floor_vec.push_back(new Wall_col(i));
		} else if (display.display_vec.at(i) == '-') {
			floor_vec.push_back(new Wall_row(i));
		} else if (display.display_vec.at(i) == '+') {
			floor_vec.push_back(new Door(i));
		} else if (display.display_vec.at(i) == '#') {
			floor_vec.push_back(new Path(i));
		} else if (display.display_vec.at(i) == ' ') {
			floor_vec.push_back(NULL);
		};
	};
	
	int _length = 5;
	for (int i=0; i<_length; ++i) {
		chamber_vec.push_back(display.display_chamber_vec.at(i));
	};
	inventory = Inventory();
	disp = &display;
    deleted_stuff = '.';
    game_over = false;
    join_next_floor = false;
};


//****************************************************************************************








int Floor::find_chamber(int index) {
	std::vector<int>::iterator it;
	for (int i=0; i<5; i++) {
		it = find((chamber_vec.at(i)).begin(), (chamber_vec.at(i)).end(), index);
		if (*it == index) {
			return i; // we find the index in chamber i
		};
	};
	return -1; // if index doesn't belong to any chamber, return -1
};





//****************************************************************************************






void Floor::generate_PC(std::string name,std::string username) {
	int index = find_empty_spot();
	// initialize PC on this spot:
	floor_vec.at(index) = new PC(index, name, username);
	// find out which chamber does this spot belongs to:
	PC_Chamber = find_chamber(index);
	// notify display object:
	notify_display(index, floor_vec.at(index)->get_symbol(), *disp);
	// make this spot unvaiable for other object: delete this spot from chamber_vec 
	delete_spot(index);
	PC_Position = index;
};



//****************************************************************************************










void Floor::generate_NPC(std::string name) {
	int index = find_empty_spot();
	floor_vec.at(index) = new NPC(index, name);
    NPC_pos.push_back(index);
	// field to NPC
	char s;
	if (name == "Vampire") {
		s = 'V';
	} else if (name == "Werewolf") {
		s = 'W';
	} else if (name == "Troll") {
		s = 'T';
	} else if (name == "Goblin") {
		s = 'N';
	} else if (name == "Phoenix") {
		s = 'X';
	} else if (name == "Merchant") {
		s = 'M';
	}; // CHANGE THIS
	notify_display(index, s, *disp);
	delete_spot(index);
};


//****************************************************************************************




void Floor::generate_Dragon(int index) {
	floor_vec.at(index) = new NPC(index, "Dragon");
    NPC_pos.push_back(index);
	notify_display(index, 'D', *disp);
	delete_spot(index);
};


//****************************************************************************************







void Floor::generate_stair() {
	// generate stair at a different spot then PC:
	int index = find_empty_spot();
	int ch = find_chamber(index);
	while (ch == PC_Chamber) {
		index = find_empty_spot();
		ch = find_chamber(index);
	};
	floor_vec.at(index) = new Stair(index);
	notify_display(index, '\\', *disp);
	delete_spot(index);
};

void Floor::generate_potion(int type) {
	int index = find_empty_spot();
	floor_vec.at(index) = new Potion(index, type);
	notify_display(index, 'P', *disp);
	delete_spot(index);
};



//****************************************************************************************





void Floor::generate_gold(int type) {
	int index = find_empty_spot();
	// check if type is a dragon horde:
	if (type == 3) {
		// check surrounding empty spot
		int i = check_surrounding(index);
		if (i == -1) {
			// if no available tile, re-find a spot
			int index = find_empty_spot();
		} else {
			// else, generate Dragon at the available spot
			generate_Dragon(i);
		};
	};
	
	floor_vec.at(index) = new Gold(index, type);
    
	notify_display(index, 'G', *disp);
	delete_spot(index);
};
    
    
    
int Floor::check_surrounding(int index) {
        // check surrounding spots for index, return the first empty tile
        for (int dir=0; dir<8; ++dir) {
            int i = convert_direction_to_index(dir, index);
            if (floor_vec.at(i)->get_symbol() == '.') {
                return i;
            }
        };
        // if cannot find any empty spot, return -1
        return -1;
        
};



//****************************************************************************************



    
    
void Floor::delete_spot(int index) {
	int ch = find_chamber(index);
//cout << "we will delete element in chamber: " << ch << endl;
	if (ch > -1) {
//cout << "delete" << endl;
//cout << chamber_vec.at(ch).size() << endl;

		for(vector<int>::iterator iter = chamber_vec.at(ch).begin(); iter != chamber_vec.at(ch).end(); ++iter ) {
    			if(*iter == index) {
       			chamber_vec.at(ch).erase(iter);
       			break;
    			};
		};
	};
	
//cout << chamber_vec.at(ch).size() << endl;
};



//****************************************************************************************




//
int Floor::find_empty_spot() {
	// randomly select a chamber with equal probability: 
	int select_chamber = rand() % 5; // generate random integer of 0-4
	int chamber_size = int(chamber_vec.at(select_chamber).size());
	// randomly select a tile with equal probability:
	int select_tile = rand() % chamber_size; 
	int index = (chamber_vec.at(select_chamber)).at(select_tile);
	return index;
};

void Floor::notify_display(int index, char symbol, Display& display) {
	display.notified(index, symbol);
	
};


//****************************************************************************************







//PC_move : surface function to call PC to move, get direction from command line and then do check work,(call checkspot2),and will get money from target place if there is.
void Floor::PC_move(int dir) {
    if (dir<0 || dir>8) {
        return;
    }
    else{
        string name = this->floor_vec.at(PC_Position)->get_username();
        string race = this->floor_vec.at(PC_Position)->get_attribute().name;
    int fut_index = convert_direction_to_index(dir, PC_Position);
    int check_result = check_spot2(PC_Position, dir);
    if(check_result > 0){
        if(this->floor_vec.at(check_result)->get_symbol() == '\\'){
            cout << "IM STUPID"<< endl;
            *this->get_jnf() = true;
        }else{
        move_to_that_place(PC_Position, fut_index);
            this->PC_item_detect();}
    }else
    if(check_result == -1) {
        this->message_to_print << "Trying to move to invalid place.";
    }
    else{
        int money_change = this->floor_vec.at(fut_index)->getmoney();
        this->floor_vec.at(PC_Position)->attribute_change('g', money_change);
        if (race == "Orc") {
        message_to_print << name << " obtains " << float(money_change)/2 << " Gold";
        }else if(race == "Dwarf"){
        message_to_print << name << " obtains " << int(money_change * 2) << " Gold";
        }else{
        message_to_print << name << " obtains " << money_change << " Gold";}
        move_to_that_place(PC_Position, fut_index);
        this->PC_item_detect();
        }
    }
};

//******************************************************************************************







// let PC have ability to pick up potion and put it into inventory instead of using it
void Floor::PC_Pickup_inventory(int dir){
    int check_result = check_spot1(PC_Position, dir);
    if (check_result < 0) {
        message_to_print << "target spot is not valid item to pick up" << endl;
    }else{
        int type =this->floor_vec.at(check_result)->get_type();
        int symbol = this->floor_vec.at(check_result)->get_symbol();
        Object* item;
        if (symbol == 'P') {
            item = new Potion(check_result, type);
            this->inventory.inventory_push_back(item);
            message_to_print << "U have picked up" << item->get_item_name() << endl;
            delete this->floor_vec.at(check_result);
            this->floor_vec.at(check_result) = new Tile(check_result);
            notify_display(check_result, '.', *disp);
        }else{
            return;
        }
    }
}
//******************************************************************************************








//NPC_around: helper for NPC_move, mainly check if there is PC around and attack.
bool Floor::NPC_around(int index){
    int i = 0;
    while (i < 8) {
        int target_spot = convert_direction_to_index(i, index);
        if (target_spot == PC_Position) {
            attack(index, target_spot);
            return true;
        }else{
            i++;
        }
    }
    return false;
}

//******************************************************************************************












//NPC_move: surface function to call NPC to move, do iteration inside NPC vector to let every NPC move, npc will move to a random place(no further than one block),and then check if there is PC around, if so NPC will automatically attack PC.
void Floor::NPC_move(){
    int NPC_num = int(NPC_pos.size());
    bool b = 1;
    int select_dir = 0;
    int new_pos = 0;
    for (int i = 0; i < NPC_num; i++) {
        if (NPC_around(NPC_pos.at(i))) {
            continue;
        }
        else{
        do{
            select_dir = rand() % 8;
            new_pos = convert_direction_to_index(select_dir, NPC_pos.at(i));
            b = (check_spot2(NPC_pos.at(i), select_dir) > 0 && floor_vec.at(new_pos)->get_symbol() != '+');
        }
        while (!b);
            if (this->floor_vec.at(NPC_pos.at(i))->get_symbol() == 'D') {
                continue;
            }else{
                move_to_that_place(NPC_pos.at(i), new_pos);}
        }}
}



//****************************************************************************************



// helper for NPC_smart_move
int Floor::search_PC(int index) {
	int sindex, ssindex;
	for (int dir=0; dir<8; ++dir) {
		if (dir == 0) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(0, sindex);
			if (ssindex == PC_Position) {
				return 0;
			};
		} else if (dir == 1) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(0, sindex);
			if (ssindex == PC_Position) {
				return 0;
			};
			ssindex = convert_direction_to_index(1, sindex);
			if (ssindex == PC_Position) {
				return 1;
			};
			ssindex = convert_direction_to_index(2, sindex);
			if (ssindex == PC_Position) {
				return 2;
			};
		} else if (dir == 2) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(2, sindex);
			if (ssindex == PC_Position) {
				return 2;
			};
		} else if (dir == 3) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(2, sindex);
			if (ssindex == PC_Position) {
				return 2;
			};
			ssindex = convert_direction_to_index(3, sindex);
			if (ssindex == PC_Position) {
				return 3;
			}
			ssindex = convert_direction_to_index(4, sindex);
			if (ssindex == PC_Position) {
				return 4;
			};
		} else if (dir == 4) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(4, sindex);
			if (ssindex == PC_Position) {
				return 4;
			};
		} else if (dir == 5) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(4, sindex);
			if (ssindex == PC_Position) {
				return 4;
			};
			ssindex = convert_direction_to_index(5, sindex);
			if (ssindex == PC_Position) {
				return 5;
			};
			ssindex = convert_direction_to_index(6, sindex);
			if (ssindex == PC_Position) {
				return 6;
			};
		} else if (dir == 6) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(6, sindex);
			if (ssindex == PC_Position) {
				return 6;
			};
		} else if (dir == 7) {
			sindex = convert_direction_to_index(dir, index);
			ssindex = convert_direction_to_index(6, sindex);
			if (ssindex == PC_Position) {
				return 6;
			};
			ssindex = convert_direction_to_index(7, sindex);
			if (ssindex == PC_Position) {
				return 7;
			};
			ssindex = convert_direction_to_index(0, sindex);
			if (ssindex == PC_Position) {
				return 0;
			};
		};
	};
	// if we cannot find PC, return -1:
	return -1;
};




//****************************************************************************************




// improved version of NPC smart move, gives NPC 2 blocks vision to detect PC and chase PC
void Floor::NPC_smart_move(){
    int NPC_num = int(NPC_pos.size());
    bool b = true;
    int select_dir = 0;
    int new_pos = 0;
    for (int i = 0; i < NPC_num; i++) {
        if (NPC_around(NPC_pos.at(i))) {
            continue;
        }
        else{
            select_dir = search_PC(NPC_pos.at(i));
       		do{
           		new_pos = convert_direction_to_index(select_dir, NPC_pos.at(i));
                b = (check_spot2(NPC_pos.at(i), select_dir) > 0 && floor_vec.at(new_pos)->get_symbol() != '+');
                select_dir++;
            }
            while (!b);
            if (this->floor_vec.at(NPC_pos.at(i))->get_symbol() == 'D') {
                continue;
            }else{
                move_to_that_place(NPC_pos.at(i), new_pos);}
		}
	}
}
//****************************************************************************************




//this function is to give npc special skills, will be called everytime npc attacks
void Floor::NPC_skill(int index, int &raw_damage){
    char n = this->floor_vec.at(index)->get_symbol();
    int HP = this->floor_vec.at(index)->get_health();
    int ATK = this->floor_vec.at(index)->get_attack();
    int DEF = this->floor_vec.at(index)->get_defense();
    Attribute attr = this->floor_vec.at(index)->get_attribute();
    if (n == 'V') {
        int health_re = raw_damage / 8;
        if (HP >= VAMPIRE.HP) {
            return;
        }else{
        this->floor_vec.at(index)->attribute_change('h', health_re);
            message_to_print << "Vampire steals " << health_re << " health through attack. ";}
    }else if (n == 'W'){
        int chance = rand() % 5;
        if (chance == 0) {
            raw_damage *=2;
            message_to_print << "Werewolf heavily strikes Player, damage doubled. ";
        }else{
            return;}
    }else if(n == 'T'){
        if (HP < TROLL.HP){
            this->floor_vec.at(index)->attribute_change('h', (attr.HP - HP)/5);
            message_to_print << "Troll regenerates 20% of missing health. ";
        }else{
            return;
        }
    }else if(n == 'N'){
        if(this->floor_vec.at(PC_Position)->getmoney() > 0){
        this->floor_vec.at(PC_Position)->attribute_change('g', -1);
            message_to_print << "Greedy Goblin stole your gold,it's only 1 gold though. ";
        if (this->floor_vec.at(PC_Position)->get_attribute().name == "Orc") {
        this->floor_vec.at(PC_Position)->attribute_change('g', -1);
        }}
        else{return;}
    }else if(n == 'X'){
        raw_damage += 5;
        message_to_print << "U r burned by Phoenix's fire,deals 5 true damage as extra damage";
    }else if(n == 'D'){
        raw_damage = 20;
        this->floor_vec.at(index)->attribute_change('a', ATK * 0.15);
        message_to_print << "Ur defense is like cloth in front of Dragon's craw, and Dragon's attack power is stronger than before(15%). ";
    }
}

//*************************************************************************************



//STUPID_COPY : a function to help copy characters to target spot to help move, called by move_to_that_place   *******************************************************************

void Floor::stupid_copy(int copy_index, int target_index){
    int health = this->floor_vec.at(copy_index)->get_health();
    int attack = this->floor_vec.at(copy_index)->get_attack();
    int defense = this->floor_vec.at(copy_index)->get_defense();
    float money = this->floor_vec.at(copy_index)->get_print_money();
    string name = this->floor_vec.at(copy_index)->get_attribute().name;
    Attribute attr2 = {0,0,0,0,"",0};
    delete this->floor_vec.at(target_index);
    if (this->floor_vec.at(copy_index)->get_username() == "") {
        this->floor_vec.at(target_index) = new NPC(target_index,name);
        attr2 = this->floor_vec.at(target_index)->get_attribute();
    }else{
        this->floor_vec.at(target_index) = new PC(target_index,name,this->floor_vec.at(copy_index)->get_username());
        attr2 = this->floor_vec.at(target_index)->get_attribute();}
    this->floor_vec.at(target_index)->attribute_change('h', health - attr2.HP);
    this->floor_vec.at(target_index)->attribute_change('a', attack - attr2.ATK);
    this->floor_vec.at(target_index)->attribute_change('d', defense - attr2.DEF);
    if (copy_index == PC_Position) {
    this->floor_vec.at(target_index)->money_copy(money - attr2.money);
    }
}

//***************************************************************************************





//move_to_that_place: another helper funciton to assist moving, directly called by NPC_move or PC_move, will do every detail step to move object in current place to target place:


void Floor::move_to_that_place(int &cur_index, int fut_index){
    notify_display(fut_index, floor_vec.at(cur_index)->get_symbol(), *disp);

    if (cur_index == PC_Position) {
        char cur_deleted_stuff = this->floor_vec.at(fut_index)->get_symbol();
        stupid_copy(cur_index, fut_index);
        delete this->floor_vec.at(cur_index);
        if (this->deleted_stuff == '+') {
            this->floor_vec.at(cur_index) = new Door(cur_index);
        }else
            if (this->deleted_stuff == '#'){
                this->floor_vec.at(cur_index) = new Path(cur_index);
            }else{
                this->floor_vec.at(cur_index) = new Tile(cur_index);
            }
        this->deleted_stuff = cur_deleted_stuff;
    }
    else{
        stupid_copy(cur_index, fut_index);
        delete this->floor_vec.at(cur_index);
        this->floor_vec.at(cur_index) = new Tile(cur_index);}
    notify_display(cur_index, this->floor_vec.at(cur_index)->get_symbol(), *disp);
    cur_index = fut_index;
}

//****************************************************************************************




//PC_Attack: get the direction from cmd and let player attack target place(NPC)
void Floor::PC_Attack(int dir){
    int target_spot = convert_direction_to_index(dir, PC_Position);
    if (this->floor_vec.at(target_spot)->get_npc()) {
        attack(PC_Position, target_spot);
    }else{
        this->message_to_print << "Not valid place to attack" << endl;
    }
};

//****************************************************************************************



//check_spot1: check method NO.1, to check if the target place is valid potion,return index of target place if there is potion, return negative 1 otherwise.
int Floor::check_spot1(int index, int dir) {
	int fut_index = convert_direction_to_index(dir, index);
	// CONT HERE *********:
    char spot2 = this->floor_vec.at(fut_index)->get_symbol();
	if (spot2 == 'P' || spot2 == '&'){
        return fut_index;
    }
    else return -1;
    
};

//****************************************************************************************



//check_spot2: similar to check_spot1, but this one is supposed to check if target place is able to move, including a special case: gold, (will return negative index in this case).
int Floor::check_spot2(int index, int dir) {
	int fut_index = convert_direction_to_index(dir, index);
	// CONT HERE *********:
    char spot2 = this->floor_vec.at(fut_index)->get_symbol();
	if (spot2 == '.'  || spot2 == '+' || spot2 == '#' || spot2 == '\\'){
        return fut_index;
    }
    if ( spot2 == 'G' ) {
        return -1 * index;
    }
    else return -1;

};

//****************************************************************************************



void Floor::PC_item_detect(){
    if (deleted_stuff != '.') {
        return;
    }else{
    for (int i = 0; i < 8; i++) {
        int check_result = check_spot1(PC_Position, i);
        if (check_result > 0) {
            Object* item = this->floor_vec.at(check_result);
            message_to_print << "There is a " << item->get_item_name() << " around you. " << endl;
        }
    }
        return;}
}


//****************************************************************************************




//convert_direction_to_index: to generate target index given current index and direction
int Floor::convert_direction_to_index(int dir, int index) {
	Coordinate coord = convert_index_to_coordinate(index, NUM_COL);
	// modify coordinate according to direction:
	if (dir == 0) {
		--coord.ns; 
	} else if (dir == 1) {
		--coord.ns; --coord.ew;
	} else if (dir == 2) {
		--coord.ew;
	} else if (dir == 3) {
		++coord.ns; --coord.ew;
	} else if (dir == 4) {
		++coord.ns;
	} else if (dir == 5) {
		++coord.ns; ++coord.ew;
	} else if (dir == 6) {
		++coord.ew;
	} else if (dir == 7) {
		++coord.ew; --coord.ns;
	};
	int index0 = convert_coordinate_to_index(coord, NUM_COL);
	return index0;
};

//**************************************************************************************



//conver_coordinate to index:
int Floor::convert_coordinate_to_index(Coordinate coord, int num_col) {
	int index = coord.ns * num_col + coord.ew; 
	return index;
};

//**************************************************************************************


//helper
Coordinate Floor::convert_index_to_coordinate(int index, int num_col) {
	Coordinate coord;
	int r = (int) index/num_col;
	int c = index % num_col;
	coord.ew = c;
	coord.ns = r;
	return coord;
};

//*************************************************************************************




//attack: core code for attack, will consume two index which represents attacker and vicitim,this function will check which one is NPC and which one is PC and do attack automatically.
void Floor::attack(int attacker, int victim){
    

    //definition of constant waiting to be used for real attack part
    //note that some constants are float instead of int to calculate damage
    
    float atk1 = float(this->floor_vec.at(attacker)->get_attack());
    int atk2 = this->floor_vec.at(victim)->get_attack();
    int def1 = this->floor_vec.at(attacker)->get_defense();
    float def2 = float(this->floor_vec.at(victim)->get_defense());
    int hp1 = this->floor_vec.at(attacker)->get_health();
    int hp2 = this->floor_vec.at(victim)->get_health();
    int money1 = this->floor_vec.at(attacker)->getmoney();
    int money2 = this->floor_vec.at(victim)->getmoney();
    if (attacker == PC_Position) {    }
    int hp_change = int((atk1 * (100 / (100 + def2))));
    string name1;
    string name2;
    string pcname = this->floor_vec.at(PC_Position)->get_attribute().name;
    
    //to decide name
    if (attacker == PC_Position){
        name1 = this->floor_vec.at(attacker)->get_username();
        name2 = this->floor_vec.at(victim)->get_attribute().name;
    }else
        if (victim == PC_Position){
            name1 = this->floor_vec.at(attacker)->get_attribute().name;
            name2 = this->floor_vec.at(victim)->get_username();
        }
    
    // the real attack part, to calculate damage or gold obtained according to situation
    if (hp_change > hp2) {
    //case1 : one of these two guys is killed, if pc is killed, call gave_over()
    //if npc is killed, clear npc and give reward to pc
    
        if (victim == PC_Position) {
            this->message_to_print << name1 << " deals " << hp_change << " damage to " << name2 << '(' <<  0 << ") ";
            this->gameover();
        }
        else{
            this->floor_vec.at(attacker)->attribute_change('g', money2);
            if (pcname == "Orc") {
                this->message_to_print << name1 << " slains " << name2 << ", obtains " <<
                0.5 * float(money2) << " Gold. ";
            }else if(pcname == "Dwarf"){
                this->message_to_print << name1 << " slains " << name2 << ", obtains " <<
                 2 * money2 << " Gold. ";
            }else{
                this->message_to_print << name1 << " slains " << name2 << ", obtains " << money2  << " Gold. ";}
            this->corpse_clear(victim);}
    }
    else{
    //case2: no one dies but victim is damaged by attacker, calculate damage
    
        int miss = rand() % 2;
        if(victim == PC_Position && miss == 1){
            message_to_print << name1 << " missed the attack.";
        }
        else{
            if(victim == PC_Position){
                NPC_skill(attacker, hp_change);
            }
            this->floor_vec.at(victim)->attribute_change('h', -1 * hp_change);
                    hp2 = this->floor_vec.at(victim)->get_health();
                    this->message_to_print << name1 << " deals " << hp_change << " damage to " << name2 << '(' <<  hp2 << ") " << endl;}
    }
};


//********************************************************************************************



//PC_Pickup_Potion: main function to deal with potion-pick-up part, have a special case(ELF)
void Floor::PC_Pickup_Potion(int dir){
    //preparation for checking
    int check_result = check_spot1(PC_Position, dir);
    string race = this->floor_vec.at(PC_Position)->get_attribute().name;
    if (check_result < 0) {
        message_to_print << "target spot is not valid potion ";
    }else{
        int p_index = check_result;
        int potion_type = this->floor_vec.at(p_index)->get_type();
        string name = this->floor_vec.at(p_index)->get_item_name();
        
        //Elf special case
        if (race == "Elf") {
            if(potion_type % 2){
                potion_type -= 1;
            }
            message_to_print << "Cause of resistance to poison, negative potions turn to be positive for Elf. " << endl;
        }
        
        //determines potiontype and use it on players
        if (potion_type == 0){
            this->floor_vec.at(PC_Position)->attribute_change('h', 10);
            message_to_print << "used "<< name << ", restored 10 health. ";
        }else if (potion_type == 1){
            this->floor_vec.at(PC_Position)->attribute_change('h', -1*10);
                message_to_print << "used "<< name << ", health decreased by 10. ";
        }else if (potion_type == 2){
            this->floor_vec.at(PC_Position)->attribute_change('a', 5);
            message_to_print << "used "<< name << ", attack increased by 5. ";
        }else if (potion_type == 3){
            this->floor_vec.at(PC_Position)->attribute_change('a', -1*5);
            message_to_print << "used "<< name << ", attack decreased by 5. ";
        }else if (potion_type == 4){
            this->floor_vec.at(PC_Position)->attribute_change('d', 5);
            message_to_print << "used "<< name << ", defense increased by 5. ";
        }else if (potion_type == 5){
            this->floor_vec.at(PC_Position)->attribute_change('d', -1*5);
            message_to_print << "used  "<< name << ", defense decreased by 5. ";
        }else{
            message_to_print << "coding error" << endl;
        }
        delete this->floor_vec.at(check_result);
        this->floor_vec.at(check_result) = new Tile(check_result);
        notify_display(check_result, this->floor_vec.at(check_result)->get_symbol(), *disp);
    }
}

//*******************************************************************************************





// this function is used to return the PC information in current floor to be copied to next floor
PC* Floor::join_nextfloor(){
    Attribute attr = this->floor_vec.at(PC_Position)->get_attribute();
    string username = this->floor_vec.at(PC_Position)->get_username();
    PC* pc_copy = new PC(0,"","");
    pc_copy->username = username;
    pc_copy->attr = attr;
    return pc_copy;
}


//******************************************************************************************








//corpse_clear: called when one npc is killed by pc,this function is charge of delete dead pc
void Floor::corpse_clear(int pos){
    delete this->floor_vec.at(pos);
    this->floor_vec.at(pos) = new Tile(pos);
    this->NPC_pos.erase(remove(this->NPC_pos.begin(), this->NPC_pos.end(), pos), this->NPC_pos.end());
    this->notify_display(pos, this->floor_vec.at(pos)->get_symbol(), *disp);
}

//******************************************************************************************








//get if now it's the time to join next floor

bool* Floor::get_jnf(){
    return &join_next_floor;
}


//****************************************************************************************






//gameover: called when pc is killed, let user choose to restart game or quit
void Floor::gameover(){
    delete this->floor_vec.at(PC_Position);
    this->floor_vec.at(PC_Position) = new Tile(PC_Position);
    notify_display(PC_Position, '.', *disp);
    game_over = true;
    
}


void Floor::use_inventory(int pos){
    int i = rand() % 8;
    int h;
    while(check_spot2(PC_Position, i) < 0){
        i = rand() % 8;}
    h = i;
    Object* p = this->inventory.use_inventory(pos);
    new Potion(check_spot2(PC_Position, h), p->index);
    PC_Pickup_Potion(h);
}

//******************************************************************************************






//to print the item stored in inventory
void Floor::show_inventory(){
    string message_print =this->inventory.get_invent_info();
    message_to_print << message_print << endl;
};


//****************************************************************************************




//destructor
Floor::~Floor() {
	for (int i=0; i<floor_vec.size(); i++) {
        if (floor_vec.at(i) != NULL) {
            delete floor_vec.at(i);
        }else{
            continue;
        }
	};
};









