#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <stdlib.h>


using namespace std;

vector<vector<char> >y;
vector<struct NPC>NPCs;

struct Player{
    char pChar;
    int x,ypos;
    int checkCollide(int tx, int ty){
        if (y[ty][tx] == '-' || y[ty][tx] == '|' || tx == y[0].capacity() || abs(ty - y.capacity()) == 1 || tx < 1 || ty < 1){
            return 1;
        }
        return 0;
    }

    void mv(string direction){
            if(direction == "down"){
                if(checkCollide(x, ypos + 1) == 0){
                    ypos = ypos + 1;
                }
            } else if(direction == "up"){
                if(checkCollide(x, ypos - 1) == 0){
                    ypos = ypos - 1;
                }
            } else if(direction == "left"){
                if(checkCollide(x - 1, ypos) == 0){
                    x -= 1;
                }
            } else if(direction == "right"){
                if(checkCollide(x + 1, ypos) == 0){
                    x += 1;
                }
            } else if(direction == "upright"){
                if(checkCollide(x + 1, ypos - 1) == 0){
                    x += 1;
                    ypos -= 1;
                }
            } else if(direction == "upleft"){
                if(checkCollide(x - 1, ypos - 1) == 0){
                    x -= 1;
                    ypos -= 1;
                }
            } else if(direction == "downright"){
                if(checkCollide(x + 1, ypos + 1) == 0){
                    x += 1;
                    ypos += 1;
                }
            } else if(direction == "downleft"){
                if(checkCollide(x - 1, ypos + 1) == 0){
                    x -= 1;
                    ypos += 1;
                }
            }
    }

};

struct NPC{
    string name,message;
    int x;
    int ypos;
    char mychar;
    void printName(void){
        for(int thisChar = 0; thisChar < name.size(); thisChar++){
            y[ypos - 1][x - static_cast<int>(name.size() / 2) + thisChar] = static_cast<char>(name[thisChar]);
        }
    }
    void say(string message){
        cout << name << " says: " << message << endl;
    }

    int checkCollide(int tx, int ty){
        if (y[ty][tx] == '-' || y[ty][tx] == '|' || tx == y[0].capacity() || abs(ty - y.capacity()) == 1 || tx < 1 || ty < 1){
            return 1;
        }
        return 0;
    }

    void mv(string direction){
            if(direction == "down"){
                if(checkCollide(x, ypos + 1) == 0){
                    ypos = ypos + 1;
                }
            } else if(direction == "up"){
                if(checkCollide(x, ypos - 1) == 0){
                    ypos = ypos - 1;
                }
            } else if(direction == "left"){
                if(checkCollide(x - 1, ypos) == 0){
                    x -= 1;
                }
            } else if(direction == "right"){
                if(checkCollide(x + 1, ypos) == 0){
                    x += 1;
                }
            } else if(direction == "upright"){
                if(checkCollide(x + 1, ypos - 1) == 0){
                    x += 1;
                    ypos -= 1;
                }
            } else if(direction == "upleft"){
                if(checkCollide(x - 1, ypos - 1) == 0){
                    x -= 1;
                    ypos -= 1;
                }
            } else if(direction == "downright"){
                if(checkCollide(x + 1, ypos + 1) == 0){
                    x += 1;
                    ypos += 1;
                }
            } else if(direction == "downleft"){
                if(checkCollide(x - 1, ypos + 1) == 0){
                    x -= 1;
                    ypos += 1;
                }
            }
    }

    void findPath(int tx, int ty){
        int distanceX = tx - x;
        int distanceY = ty - ypos;
        if(abs(distanceX) <= 2 && abs(distanceY) <= 2){
        } else if(distanceX > 0 && distanceY > 0){
            mv("downright");
        } else if(distanceX < 0 && distanceY > 0){
            mv("downleft");
        } else if(distanceX > 0 && distanceY < 0){
            mv("upright");
        } else if(distanceX < 0 && distanceY < 0){
            mv("upleft");
        } else if(distanceX < 1 && distanceY == 0){
            mv("left");
        } else if(distanceX > 1 && distanceY == 0){
            mv("right");
        } else if(distanceX == 0 && distanceY > 1){
            mv("down");
        } else if(distanceX == 0 && distanceY < 1){
            mv("up");
        }
    }
};

class BufferToggle {
    private:
        struct termios t;
    public:
        void off(void){
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag &= ~ICANON & ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        }
        void on(void){
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag |= ICANON & ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        }
};

void makeMap(int size){
    y.reserve(size);
    int height = size;
    int width = height;
    for(int i=0; i < height; i++){
        vector<char>x;
        width = height * 2;
        x.reserve(width);
        for(int k = 0; k < x.capacity(); k++){
            x.push_back(' ');
        }
        y.push_back(x);
    }
}

void makeWall(int xpos, int ypos, int width, int height){
    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
            char wallsym;
            if(height > width){
                wallsym = '|';
            } else {
                wallsym = '-';
            }
            y[ypos + i][xpos + k] = wallsym;
        }
    }
}


void printMap(){
    for(int i=0; i < y.size(); i++){
        for(int k=0; k < y[i].size(); k++){
            cout << y[i][k];
        }
        cout << endl;
    }
}

int abs(int x){
    if(x > 0){
        return x;
    }
    return -x;
}

void makeNPC(string name, int x, int ypos, char sym, string message=" "){
    struct NPC npc;
    npc.name=name;
    npc.x = x;
    npc.ypos = ypos;
    npc.mychar = sym;
    npc.message=message;
    NPCs.push_back(npc);
}

void displayNPCs(void){
    for(int i=0; i < NPCs.size(); i++){
        y[NPCs[i].ypos][NPCs[i].x] = NPCs[i].mychar;
    }
}

int main()
{
    struct Player player;
    player.pChar='@';
    makeMap(25);
    player.ypos = y.size() / 2;
    player.x = y[player.ypos].size() / 2;
    NPCs.reserve(10);
    BufferToggle bt;
    bt.off();
    string u_input;
    makeNPC("King Mexis", 16, 2, '&', "Ravioli Ravioli what's in the pocketoli???");
    makeNPC("Andrei the Romanian", 20, 4, '$', "Ey mang you wan sum computer science???");
    makeNPC("Ol'Dally", 13, 12, '%' , "Uhh, weiners.");
    while(true){
        y[player.ypos][player.x] = player.pChar;
        for(int i = 0; i < NPCs.size(); i++){
             y[NPCs[i].ypos][NPCs[i].x] = ' ';
            NPCs[i].findPath(player.x,player.ypos);
        }
        displayNPCs();
        makeWall(0,0,1,4);
        makeWall(1,3,3,1);
        makeWall(6,3,3,1);
        makeWall(9,0,1,4);
        makeWall(1,0,8,1);
        makeWall(7,7,5,1);
        makeWall(14,7,5,1);
        makeWall(7,8,1,8);
        makeWall(18,8,1,8);
        makeWall(7,16,12,1);
        printMap();
        for(int i=0; i < NPCs.size(); i++){
            if(abs(player.x - NPCs[i].x) <= 1 && abs(player.ypos - NPCs[i].ypos) <= 1){
                NPCs[i].say(NPCs[i].message);
            }
        }
        y[player.ypos][player.x] = ' ';
        cout << endl << endl << endl;
        if(getchar() == '\033'){
            getchar();
            switch(getchar()){
                case 'A':
                    player.mv("up");
                    break;
                case 'B':
                    player.mv("down");
                    break;
                case 'C':
                    player.mv("right");
                    break;
                case 'D':
                    player.mv("left");
                    break;
            }
        }
        system("clear");
    }
    bt.off();
    return 0;
}
