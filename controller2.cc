#include "display2.h"
#include "floor2.h"
#include "object2.h"

using namespace std;

const float PB_VAMPIRE = float(3)/18;
const float PB_WEREWOLF = float(2)/9;
const float PB_TROLL = float(1)/9;
const float PB_GOBLIN = float(5)/18;
const float PB_PHOENIX = float(1)/9;
const float PB_MERCHANT = float(1)/9;

const int NUM_NPC = 20;
const int NUM_POTION = 10;
const int NUM_GOLD = 10;

// const float PB_DRAGON:  decided by Dragon treasure 




void game_init(Floor& _floor, char race, string username) {
	if (race == 'h') {
        _floor.generate_PC("Human",username);
	} else if (race == 'e') {
 		_floor.generate_PC("Elf", username);
 	} else if (race == 'd') {
 		_floor.generate_PC("Dwarf", username);
 	} else if (race == 'o') {
 		_floor.generate_PC("Orc", username);
	};
	
	// initialize stair:
	_floor.generate_stair();
	
	// initialize potions: 
	for (int i=0; i<NUM_POTION; ++i) {
		int x = rand() % 6;
		_floor.generate_potion(x);
	};
	
	// initialize gold:
	for (int i=0; i<NUM_GOLD; ++i) {
		int x = rand() % 4;
		_floor.generate_gold(x);
	};
	
	// initialize NPC:
	for (int i=0; i<NUM_NPC; ++i) {
		int x = rand() % 18;
		if (x < 3) {
 			_floor.generate_NPC("Vampire");
		} else if (x>2 && x<7) {
 			_floor.generate_NPC("Werewolf");
		} else if (x>6 && x<9) {
 			_floor.generate_NPC("Troll");
		} else if (x>8 && x<14) {
			_floor.generate_NPC("Goblin");
		} else if (x>13 && x<16) {
			_floor.generate_NPC("Phoenix"); 
		} else if (x>15 && x<18) {
			_floor.generate_NPC("Merchant"); 
		};
	};
};	
	
	
int main(int argc, char *argv[]) { 
	Floor* _floor = NULL;
	bool done = false;
	char race;
    string username;
	
	/* initialize random seed: */
	srand (time(NULL));
  
	Display* _disp = new Display(); // initialize Display with default map
	
	while(!done) {
		string cmd1;
        string cmd;
        bool DLC;
        char ui_cmd;
        string DLC_cmd = "NULL";
        string m_cmd = "NULL";
        string u_cmd = "NULL";
        string a_cmd = "NULL";
        string p_cmd = "NULL";
        int cmd_dir = -1;
		 
		if (_floor == NULL) {
			// if the Floor doesn't exist, create one, and prompt
		 	// player to select his rece
		 	_floor = new Floor(*_disp);
            
            cout << "turn on DLC? type in 'y' or 'n' to make selection" << endl;
            cin >> DLC_cmd;
            
            if (DLC_cmd == "y") {
                DLC = true;
            }else{DLC = false;}
		 	cout << "Type in one of 'h, e, d, o' to select your race:" << endl;
		 	cin >> race;
            cout << "Type in character's name:" << endl;
            cin >> username;
		 	if (cin.eof()) break;
		 	// initialize the game environment:
		 	game_init(*_floor, race, username);
		};
		 	

        _disp->prettyprint();
        
        cout << "PC current health: " << _floor->floor_vec.at(_floor->PC_Position)->get_health() << endl;
        cout << "PC current attack: " << _floor->floor_vec.at(_floor->PC_Position)->get_attack() << endl;
        cout << "PC current defense: " << _floor->floor_vec.at(_floor->PC_Position)->get_defense() << endl;
        cout << "Gold: " << _floor->floor_vec.at(_floor->PC_Position)->get_print_money() << endl;
        cout << "PC race: " << _floor->floor_vec.at(_floor->PC_Position)->get_attribute().name << endl;
        cout << "username: " << username << endl;

        cout << _floor->message_to_print.str() << endl;
        _floor->message_to_print.str("");
        
        
        while (cmd_dir == -1) {
            cout << "command? : " << endl;

        cin >> cmd1;
        if (cmd1 == "i" && DLC) {
            _floor->show_inventory();
            cmd_dir = 10000000;
        }else if(cmd1 == "ui"){
            cin >> ui_cmd;
            _floor->use_inventory(int(ui_cmd));
        }else if (cmd1 == "a") {
            cin >> a_cmd;
            cmd = a_cmd;
        }else if(cmd1 == "u"){
            cin >> u_cmd;
            cmd = u_cmd;
        }else if (cmd1 == "p"){
            cin >> p_cmd;
            cmd = p_cmd;
        }else{
            m_cmd = cmd1;
            cmd = m_cmd;
        }
        
        
        if (cmd == "no") {
            cmd_dir = 0;
        }else
        if (cmd == "nw") {
            cmd_dir = 1;
        }else
        if (cmd == "we") {
            cmd_dir = 2;
        }else
        if (cmd == "sw") {
            cmd_dir = 3;
        }else
        if (cmd == "so") {
            cmd_dir = 4;
        }else
        if (cmd == "se") {
            cmd_dir = 5;
        }else
        if (cmd == "ea") {
            cmd_dir = 6;
        }else
        if (cmd == "ne") {
            cmd_dir = 7;
        }
        }

        if (a_cmd != "NULL") {
            _floor->PC_Attack(cmd_dir);
        }else if (u_cmd != "NULL"){
            _floor->PC_Pickup_Potion(cmd_dir);
        }else if (p_cmd != "NULL"){
            _floor->PC_Pickup_inventory(cmd_dir);
        }else{
            _floor->PC_move(cmd_dir);
        }

        
        if(DLC){
            _floor->NPC_smart_move();
        }else{
            _floor->NPC_move();
        }
        
        
        if (_floor->game_over) {
            while (true) {
            char cmd_e;
            cout << endl << "Game Over. Press (r) to restart the game or (q) to quit." << endl;
            cin >> cmd_e;
            if (cmd_e == 'r') {
                _floor->~Floor();
                _disp->~Display();
                _floor = NULL;
                break;
            }else if(cmd_e == 'q'){
                delete _disp;
                _floor->~Floor();
                exit(EXIT_FAILURE);
            
            }
        }
    }
        
        if(_floor == NULL){
            continue;
        }else
        {
        if (_floor->join_next_floor) {
            cout << "slfjadslf;adslk;ajg;s/gjkgajdkg" << endl;
            PC* copy_man = _floor->join_nextfloor();
            char race;
            int health = copy_man->get_health() - copy_man->get_attribute().HP;
            int attack = copy_man->get_attack() - copy_man->get_attribute().ATK;
            int defense = copy_man->get_defense() - copy_man->get_attribute().DEF;
            int gold = copy_man->getmoney() - copy_man->get_attribute().money;
            string name = copy_man->get_attribute().name;
            if (name == "Orc") {
                race = 'o';
            }else if (name == "Elf"){
                race = 'e';
            }else if (name == "Dwarf"){
                race = 'd';
            }else if (name == "Human"){
                race = 'h';
            }
            string username = copy_man->get_username();
            _floor->~Floor();
            _disp->~Display();
            _disp = new Display();
            _floor = new Floor(*_disp);
            game_init(*_floor, race, username);
            _floor->floor_vec.at(_floor->PC_Position)->attribute_change('h', health);
            _floor->floor_vec.at(_floor->PC_Position)->attribute_change('a', attack);
            _floor->floor_vec.at(_floor->PC_Position)->attribute_change('d', defense);
            _floor->floor_vec.at(_floor->PC_Position)->attribute_change('g', gold);
            delete copy_man;
        }}


		
		/* cout << "Command?" << endl;
		cin >> cmd; // Read in the following command:
		 	// no,so,ea,we,ne,nw,se,sw: direction
			// u <direction>: use item
			// a <direction>: attack NPC
			// h, e, d, o: select race at beginning
			// r: restart the game
			// q: admit defeat and quit the game
		if (cin.eof()) break;
		// TO BE CONT
		*/
	
	};
	
	
};




