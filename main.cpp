#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <stdlib.h>


using namespace std;

vector<vector<char> >y;
char pChar = '@';

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

int main()
{
    BufferToggle bt;
    bt.off();
    string u_input;
    makeMap(25);
    int iYp = y.size() / 2;
    int iXp = y[iYp].size() / 2;
    makeWall(0,0,1,4);
    makeWall(1,3,3,1);
    makeWall(6,3,3,1);
    makeWall(9,0,1,4);
    makeWall(1,0,8,1);
    while(true){
        y[iYp][iXp] = pChar;
        printMap();
        y[iYp][iXp] = ' ';
        cout << endl << endl << endl;
        if(getchar() == '\033'){
            getchar();
            switch(getchar()){
                case 'A':
                    if(y[iYp - 1][iXp] == '-' || y[iYp - 1][iXp] == '|'){
                            cout << "That's a fucking wall, retard.\n";
                        } else {
                            if(iYp - 1 > 0){
                                iYp = iYp - 1;
                            }
                        }
                    break;
                case 'B':
                    if(y[iYp + 1][iXp] == '-' || y[iYp + 1][iXp] == '|'){
                        cout << "That's a fucking wall, retard.\n";
                    } else {
                        if(iYp + 1 < y.size() - 1){
                            iYp = iYp + 1;
                        }
                    }
                    break;
                case 'C':
                    if(y[iYp][iXp + 1] == '-' || y[iYp][iXp + 1] == '|'){
                        cout << "That's a fucking wall, retard.\n";
                    } else {
                        if(iXp + 1 < y[0].size()){
                            iXp = iXp + 1;
                        }
                    }
                    break;
                case 'D':
                    if(y[iYp][iXp - 1] == '-' || y[iYp][iXp - 1] == '|'){
                        cout << "That's a fucking wall, retard.\n";
                    } else {
                        if(iXp - 1 > 0){
                        iXp = iXp - 1;
                        }
                    }
                    break;
            }
        }
        system("clear");
    }
    bt.off();
    return 0;
}
