#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector<vector<char> >y;
char pChar = '@';

void squareMap(int size){
    y.reserve(size);
    int height = size;
    int width = height;
    for(int i=0; i < height; i++){
        vector<char>x;
        width = height * 2;
        x.reserve(width);
        for(int k = 0; k < x.capacity(); k++){
            x.push_back('.');
        }
        y.push_back(x);
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
    string u_input;
    squareMap(5);
    int iYp = y.size() / 2;
    int iXp = y[iYp].size() / 2;
    while(true){
        y[iYp][iXp] = pChar;
        printMap();
        y[iYp][iXp] = '.';
        cout << endl << endl << endl;
        getline(cin,u_input);
        if(u_input == "mv up"){
            iYp = iYp - 1;
        }else if(u_input == "mv down"){
            iYp = iYp + 1;
        }else if(u_input == "mv left"){
            iXp = iXp - 1;
        }else if(u_input == "mv right"){
            iXp = iXp + 1;
        }
    }
    return 0;
}
