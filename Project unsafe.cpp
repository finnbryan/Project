/*********************************************
Finn Bryan, Grace Salazar, Jackson Luff
Project
Date Completed: October 4, 2026
Description: Project.
Version: 1.0
*********************************************/


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

class Move{ 

    public:
    string name;
    string descriptor;
    int damage;
    int hitNumber;

};

class Player{

    public:
    string name;
    int hp;
    int level;
    int room;
    string inventory[20];
    int luck;


};

class Enemy{

    public:
    string name;
    int hp;
    int type;
    string art;


    Enemy()
    {
        name = "";
        hp = 0;
        type = 0;
    }

    Enemy(string n, int h, int t, string a)
    {
        name = n;
        hp = h;
        type = t;
        art = a;

    }

};

class Room{

    public:
    int number;
    bool explored;
    string description;
    Enemy roomEnemy;
    int north;
    int east;
    int south;
    int west;

    Room()
    {
        number = 0;
        explored = false;
        description = "";

        north = -1;
        east = -1;
        south = -1;
        west = -1;
    }

    Room(int num,
         string desc,
         int n,
         int e,
         int s,
         int w,
         Enemy enemy)
    {
        number = num;
        explored = false;
        description = desc;

        north = n;
        east = e;
        south = s;
        west = w;

        roomEnemy = enemy;
    }

};

class chest
{

};



void fight(Player&, Enemy&);
void roomStuff(Player&, Room&);
void movePlayer(Player& , Room[]);
void mapConstructor(Room rooms[]);
bool char_validation();
string playerChoice();
void mapDisplay(Room rooms[], Player& player);
Enemy getEnemy(string name);
void typewrite(const string &text, int delayMs);
int items(Player& player, bool& drank);
void weapondamage(int &sword, int &axe, int &spear, Player& player, Enemy& enemy);
void choice(Enemy& enemy, Player& player, bool& flee);


int main(){

    
    string input;
    Room rooms[25];
    mapConstructor(rooms);
    
    Player player;
    player.hp = 100;
    player.level = 1;
    player.room = 0;


    cout << "Please enter your Characters name: ";
    getline(cin, player.name);
    cout << "You awaken in a damp dungeon, you must escape. There is a door to the south" << endl;

    while(true){

        roomStuff(player, rooms[player.room]);

        input = playerChoice();

        if(input == "E")
            movePlayer(player, rooms);

        else if(input == "L")
            cout << rooms[player.room].description << endl;
        
        else if(input == "M")
            mapDisplay(rooms, player);






    }

}




void fight(Player& player, Enemy& enemy){

    bool flee = false;
    
    

    do
    {
        cout << enemy.art;
        
        choice(enemy, player, flee);
        
        if(flee)
        {
            cout << "your may be cowardly but you know what fights to pick " << endl;
            break;
            
        }

        if(enemy.hp <= 0)
        {
            cout << enemy.name << " was defeated!\n";
            cout << "you gained experience" << endl;
            player.level += 1;
            cout << "your current level " << player.level << endl;
            break;
        }

        cout << enemy.name << " attacks back!\n";
        player.hp -= 5;

        cout << player.name << " HP: "
             << player.hp << endl;

        cout << enemy.name << " HP: "
             << enemy.hp << endl;

    }while(player.hp > 0 && enemy.hp > 0 && !flee);

    if(player.hp <= 0)
    {
        cout << "Game Over!\n";
        exit(0);
    }




}

void chest(Player &player)
{
    cout << "Would you like to open a chest. [Y]es or [N]o" << endl;
    char input;


    if(input == 'Y')
    {
        cout << "You have opened a chest " << endl;

    }

    if(input == 'N')
    {

    }
}

void roomStuff(Player &player, Room &room){

    cout << room.description << endl;


    if(!room.explored)
    {

        if(room.roomEnemy.hp > 0)
        {
            cout << "A " << room.roomEnemy.name
                 << " appears!\n";

            fight(player, room.roomEnemy);

            if(player.hp <= 0)
            {
                cout << "Game over!";
                exit(0);
            }
        }

        room.explored = true;
    }


}

void mapConstructor(Room rooms[]){
    

    rooms[0] = Room(
    0,
    "A dark cave entrance.",
    -1, 1, -1, -1,
    Enemy()
    );

    rooms[1] = Room(
    1,
    "A narrow tunnel.",
    -1, 2, -1, 0,
    Enemy()
    );

    rooms[2] = Room(
    2,
    "The treasure room.",
    3, -1, -1, 1,
    Enemy()
    );

    rooms[3] = Room(
    3,
    "The stairwell.",
    -1, -1, 2, 1,
    Enemy()
    );

    rooms[0].roomEnemy = getEnemy("Ghost");


}

void movePlayer(Player& player, Room rooms[])
{
    string choice;
    cout << "There are doors to the: ";
    if(rooms[player.room].north > -1)
        cout << "North\t";
    if(rooms[player.room].east > -1)
        cout << "East\t";
    if(rooms[player.room].south > -1)
        cout << "South\t";
    if(rooms[player.room].west > -1)
        cout << "West\t";
    cout << "\nDirection (N/E/S/W): ";
    getline(cin,choice);

    choice = toupper(choice[0]);

    switch(choice[0])
    {
        case 'N':
            if(rooms[player.room].north != -1)
                player.room = rooms[player.room].north;
            break;

        case 'E':
            if(rooms[player.room].east != -1)
                player.room = rooms[player.room].east;
            break;

        case 'S':
            if(rooms[player.room].south != -1)
                player.room = rooms[player.room].south;
            break;

        case 'W':
            if(rooms[player.room].west != -1)
                player.room = rooms[player.room].west;
            break;

        default:
            cout << "Invalid direction!\n";
    }
}

bool char_validation(string c)
{

    bool valid = true;

    if(!(isalpha(c[0])) || !(c.size() == 1)){
        valid = false;
    }
    if(!valid){
        cout << "invalid input" << endl;
        return false;
    }
    return true;

}

string playerChoice(){
    string choice;
    bool valid = false;

    while(!valid){
        cout << "Would you like to: " << endl;
        cout << "[L]ook around \t" << "[E]xplore further\t" << "check [M]ap" << endl;

        getline(cin, choice);
        choice = toupper(choice[0]);

        if(choice =="E" || choice == "L" || choice == "M")
            valid = true;
        
        if(!valid)
            cout << "Invalid Input" << endl;

    }

    return choice;

}

void mapDisplay(Room room[],Player& player){
    
    cout << "Key:\n";
    cout << "P = player\n";
    cout << "X = explored\n";

    cout << " --------------------- " << endl;

    for(int i = 0; i < 25; i++){
        cout << " | ";
        if(player.room == i)
            cout << "P";
        else if(room[i].explored == true)
            cout << "X";
        else
            cout << " ";
        if(((i + 1) % 5) == 0){
            cout << " | " << endl;
            cout << " --------------------- " << endl;
        }

        
    }

}

Enemy getEnemy(string name){
    if(name == "Big Spider"){
        return Enemy(
            "Big Spider",
            20,
            1,
            "       ___________\n"
            "  ____/           \\____\n"
            " /    |           |    \\ \n"
            "/  ___|___________|___  \\\n"
            "  /    |         |    \\ \n"
            " /   __|_________|__   \\ \n"
            "    /    |. . .|    \\ \n"
            "         |_____| \n"


        );
    }

    else if(name == "Ghost"){
        return Enemy(
            "Ghost",
            30,
            5,
            "            ###############\n"
            "         #####################\n"
            "       #########################\n"
            "      ###########################\n"
            "     #############################\n"
            "    ###############################\n"
            "   #################################\n"
            "  #########    #########    #########\n"
            "  #########    #########    #########\n"
            "  #########    #########    #########\n"
            "  ###################################\n"
            "  ###################################\n"
            "  ###############    ################\n"
            "  ##############      ###############\n"
            "  ##############      ###############\n"
            "  ###############    ################\n"
            "  ###################################\n"
            "  ###################################\n"
            "  ###################################\n"
            "  ###################################\n"
            "  ###################################\n"
            "  ###################################\n"
            "  ###################################\n"
            "  ########### ########### ###########\n"
            "   #########   #########   #########\n"
            "    #######     #######     #######\n"
            "     #####       #####       #####\n"
            "      ###         ###         ###\n"


        );
    }
}

void typewrite(const string &text, int delayMs)
{
    for (char c : text)
    {
        cout << c;
        this_thread :: sleep_for(chrono::milliseconds(delayMs));
    }
};

void weapondamage(int &sword, int &axe, int &spear, Player& player, Enemy& enemy)
{
    int criticalhit;
    bool critical = false;
    for(int i = 0; i < 1 + player.luck; i++)
    {
        criticalhit = rand() % 30;

        if(criticalhit == 0)
        {
            critical = true;
            cout << "Your feeling lethal today(your gonna hit a critical attack) " << endl;
            break;
            
        }
    }
        
    if(critical == true)
    {
        sword = 30 + player.level;
        axe = 40 + player.level;
        spear = 25 + player.level;
            
            
    }
    else
    {
        sword = 10 + player.level;
        axe = 15 + player.level;
        spear = 5 + player.level;

    }
}

int items(Player& player, bool& drank)
{
    
    if(drank == true)
    {
        player.luck += 15;
        
    }
    return player.luck;
}

void choice(Enemy& enemy, Player& player, bool& flee)
{
    int sword, spear, axe, chance;
    char input;
        
    bool valid = false;
    bool escape = false;

    
    do
    {  
        cout << "Will you [A]ttack/[D]odge/[F]lee/[I]tem/[R]isky Final attack/[G]ameplay logic: " << endl;
        cin >> input;
        cin.ignore(1000, '\n');
        input = toupper(input);

        if(input == 'A' || input == 'D' || input == 'F' ||input == 'I' || input == 
        'R' || input == 'G')
        {


            
            if(input == 'A')
            {
                
                weapondamage(sword,axe,spear, player, enemy);
                cout << "Choose one of your current weapon " << endl;;
                cout << "[E]xcalibur" << endl;
                cout << "[A]xe" << endl;
                cout << "[S]pear" << endl;

                cin >> input;
                cin.ignore(1000, '\n');
                input = toupper(input);

                if(input == 'A')
                {
                    cout << player.name <<  " You swung A mean ATTACK at " << enemy.name << endl;
                    enemy.hp -= axe;
                    valid = true;
                
                }
                else if(input == 'E')
                {
                    cout << player.name << " The legendary sword made a slash at " << enemy.name  << endl;
                    enemy.hp -= sword;
                    valid = true;
                
                
                }
                else if (input == 'S')
                {
                    cout << player.name << " Careful you might poke " << enemy.name << " eye out " << endl;
                    enemy.hp -= spear;
                    valid = true;
                
                }
                else
                {
                    cout << "Invalid weapon choice " << endl;
                
                }
            

            }
            if(input == 'D')
            {
                escape = false;
                for(int i = 0; i < 1 + player.luck; i++)
                {
                    chance = rand() % 5;
                    if(chance == 0)
                    {
                        escape = true;
                        break;
                    }
                    
                }
                if(escape == true)
                {
                    cout << "you dodged and healed up" << endl;
                    player.hp += 10;
                    cout << player.name << "HP: " << endl;
                    valid = false;
                }
                else
                {
                    cout << "you failed to dodge but landed a small counter attack" << endl;
                    enemy.hp -= 5;
                    valid = true;
                }
                
            }

            if (input == 'F')
            {

                flee = true;
                valid = true;
                
                
                

            }

            if (input == 'I')
            {
                do
                {
                    cout << "would you like to [B]uy some potions or [U]se your own potion or [E]xit" << endl;
                    cin >> input;
                    cin.ignore(1000, '\n');
                    input = toupper(input);
                    
                    if(input == 'B')
                    {
                        cout << "[L]uck potion (1 level) or [E]xit" << endl;
                        cin >> input;
                        cin.ignore(1000, '\n');
                        input = toupper(input);
                        if (player.level >= 1)
                        {
                            if(input == 'L')
                            {
                                bool drank = true;
                                items(player, drank);

                                cout << "youll be feeling extra lucky -merchant " << endl;
                                player.level -= 1;
                                cout << "-1 level " << "Your current level " << player.level << endl;
                                cout << "you drank the potion " << endl;

                            
                            }
                            else if (input == 'E')
                            {
                                    
                                
                            }
                            else
                            {
                                cout << "Invalid input " << endl;
                                input = 'B';
                            }
                        }
                        else 
                        {
                            cout << "Your out of levels go out and kill a few beast" << endl;
                            cout << "your current level " << player.level << endl;
                            input = 'E';
                        }

                            
                        
                        
                    }
                    else if (input == 'U')
                    {
                        
                    }
                    else if (input == 'E')
                    {

                    }
                    else
                    {
                        cout << "invalid input" << endl;
                    }

                
                }while(input != 'E');
                cout << "you exited " << endl;
                continue;
            }
        
        
                        
        
                     
        

    

            if (input == 'G')
            {
                cout << "This is an overview of logic if you want to understand the game " << endl;
                cout << endl;

                cout << "Attack" << endl;
                cout << endl;
                cout << "Attack has base damage and can be amplified with your level" << endl;
                cout << "You can roll a critical hit on each weapon " << endl;
                cout << endl;

                cout << "Dodge" << endl;
                cout << endl;
                cout << "Dodge allows you to heal up and avoid taking damage " << endl;
                cout << "if your dodge fails you get a small counter attack " << endl;
                cout << endl;

                cout << "Flee" << endl;
                cout << endl;
                cout << "you value your life over anything" << endl;
                cout << "you can continue exploring without having battled " << endl;
                cout << endl;

                cout << "Items" << endl;
                cout << endl;
                cout << "your allowed to buy items with your levels or use items you have found" << endl;
                cout << endl;



                cout << "Risky Final Attack" << endl;
                cout << endl;
                cout << "This feature is a gamble you can do 200 damage if your lucky.  if you are unlucky you will get hit by an additional attack from the enemy" << endl;
                cout << "You can get lucky if your gamble fails.  For example you can fail the risky attack and then manage to dodge the additional attack " << endl;
                cout << endl;

                cout << "Luck Potion" << endl;
                cout << endl;
                cout << "if you use a luck potion it increase the amount of rolls you get for things involving dodges/critical hits/risky attacks" << endl;
                cout << endl;

                cout << endl;
                cout << "Thanks for checking this out" << endl;
                player.luck += 1; //secret mechanic 
                valid = false;
        
            }
            if (input == 'R')
            {
                
                escape = false;
                
                for(int i = 0; i < 1 + player.luck; i++)
                {
                    

                    chance = rand() % 50;
                    if(chance == 0)
                    {
                        escape = true;
                        break;
                    }
                    
                }

                if(escape == true)
                {
                    cout << "You Used up ALL your energy and vanquished the enemy" << endl;
                    enemy.hp -= 200;
                    valid = true;
                }
                else
                {
                    cout << "You made a risky mistake but I respect the guts " << endl;
                    cout << "due to your risk you left yourself wide open " << endl;
                    for(int i = 0; i < 1 + player.luck; i++)
                    {
                        chance = rand() % 10;
                            
                        if (chance == 4)
                        {
                            escape = true;
                            break;
                        }
                            
                    }

                    if (escape == true)
                    {
                        cout << "consider yourself lucky you managed to narrowly escape that mean additional goblins attack " << endl;
                        cout << player.hp << endl;
                        valid = true;
                        
                            
                    }
                    else
                    {
                        cout << enemy.name << " made an additional attack" << endl;
                        player.hp -= 20;
                        cout << player.name << " HP: " << player.hp << endl;
                        valid = true;
                    }
                }

            }
        }
        else
        {
            cout << "invalid input try again. " << endl;
        }


    }while(!valid);
    

}

    
        
