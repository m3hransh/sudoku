#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define N 9

struct cell{
    char x;
    char y;
    char v;
};

//global variables
char table[N][N]; // the main sudoku table
std::vector<cell> emptycells;// list of empty cells

//print the talbe contents
void print_table(){
    //create new table for adding empty cells as well
    char tab[N][N];
    
    for(int i=0; i <N;i++){
        for(int j=0; j<N;j++)
            tab[i][j] = table[i][j];
        }
    //adding emptycells values
    for(int i=0; i<emptycells.size();++i) 
       tab[emptycells[i].x-'0'][emptycells[i].y-'0'] = emptycells[i].v; 
    for(int i=0; i <N;i++){
        for(int j=0; j<N;j++)
            std::cout<< tab[i][j]<<',';
        std::cout<<std::endl;
}
        std::cout<<std::endl;
}
//print vector of cells
void print_cells(std::vector<cell> v){
    for(auto& i:v)
       std::cout<<'('<<i.x<<','<<i.y<<") "; 
}

//check if the all the elements of the row element k is in is compatible
bool check_row(int k){
    //take care of constant valued cells
    for(int j=0; j<N; ++j){
        //to make sure is not the same cell
        if(emptycells[k].y != '0' +j){
            if (table[emptycells[k].x-'0'][j] == emptycells[k].v){
                return false;
            }
        }
    }
    return true;
}
bool check_col(int k){
    //take care of constant valued cells
    for(int i=0; i<N; ++i){
        // check it isn't the same element
        if(emptycells[k].x != '0'+i){
            if (table[i][emptycells[k].y-'0'] == emptycells[k].v){
                return false;
            }
        }
    }
    return true;
}
bool check_sq(int k){
    //finding the top left square in 3*3 square k is in 
    int sq_row = int(emptycells[k].x /3)*3;
    int sq_col = int(emptycells[k].x /3)*3;
    for(int i=sq_row; i <sq_row+3;++i){
        for(int j=sq_col ; j<sq_col+3;++j){
            if(emptycells[k].x -'0' != i || emptycells[k].y -'0' !=j)
            {
                if(emptycells[k].v == table[i][j])
                    return false;
            }
        }
    }
    return true;

}
//checking if the previous choices are compatible
bool check_pre_cells(int k){
    //the squre that element k is in 
    int sq_row = int(emptycells[k].x /3)*3;
    int sq_col = int(emptycells[k].y /3)*3;

    for(int i=0; i<k; ++i){
        //row_check
        if(emptycells[i].x == emptycells[k].x)
            if (emptycells[i].v == emptycells[k].v)
                return false;
        //col_check
        if(emptycells[i].y == emptycells[k].y)
            if (emptycells[i].v == emptycells[k].v)
                return false;
        //square_check
        if(int(emptycells[i].x/3)*3 == sq_row && int(emptycells[i].y/3)*3 == sq_col)
            if (emptycells[i].v == emptycells[k].v)
                return false;
    }
    return true;
}

bool promising( int k){
    if (check_row(k) && check_col(k) && check_sq(k) && check_pre_cells(k))
        return true;
    else
        return false;
}
void sudoku(int k){
   for(int i=1; i<= N;++i){
       emptycells[k].v = '0' + i;
       if (promising(k)){
            if(k== emptycells.size()-1){ 
                print_table();
            }
            else
                sudoku(k+1);
       } 
   } 
}
using namespace std;

int main(int argc, char** argv){
    //getting file name from argv in terminal
    //else default value of game1.txt
    string filename;
    if (argc >1)
        filename = argv[1];
    else
       filename = "game1.txt";
    ifstream myfile;
    myfile.open(filename);
    string line;
    int i=0;
    while (getline(myfile,line)) {
        istringstream iss(line);
        for(int j=0; j<N; ++j){
            iss>>table[i][j];
            if (table[i][j] == '0'){
                cell c{char('0'+i),char('0'+j),'0'};
                emptycells.push_back(c);
            }
        }
        i++;     
       }
    sudoku(0);
    return 0;
}

