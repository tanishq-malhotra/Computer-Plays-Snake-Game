#include<bits/stdc++.h>
#include<fstream>
#include<conio.h>
#include<windows.h>

using namespace std;
//handle declared, extern is used because it is a global variable
extern HANDLE hOut;
class Snake
{
public:
//defining row, column, headx and heady
int r, c, x, y;
//food x and y coordinates
int fx,fy;
//used to quit the game
bool gameover = true;
//main game grid
char **grid;
//for storing snake's x and y coordinates
int *sx,*sy;
//counter to check the tail's length
int tailC;
//Score
int sc;
//stack for calculating path
queue<int> q;
//default constructor
Snake();
//parameterised constructor to set value's
Snake(int ,int );
//checks if path is available or not
bool pathExist;
//generating food at random position
void food_random();
//printing the main game
void Print();
//display score
void display_score();
//function to update the values of the tail's position
void moveTail();
//to check the collision of snake with the wall
void checkWallCollision();
//to check the collision of food and snake
void eatFood();
//to check if snake snake hits itself or not
void checkHitItself();
//function to get the grid
char** pat2grid(int r,int c);
//driver function
void driver();
//function which will call the shortest_path function to calculate the shortest path
void path();
//this function is used to reverse the queue to reverse the coordinates stored in the queue
void reverse_queue();
};