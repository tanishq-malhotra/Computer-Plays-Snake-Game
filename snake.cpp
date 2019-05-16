#include "snake.hpp"
#include "shortpath.hpp"
//handle created, used to clear the screen
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
Snake::Snake() {}
//parameterised constructor to set value's
Snake::Snake(int n, int m):r(n),c(m),tailC(0),sc(0),x(10),y(3)
{
	//creating grid and storing stage in grid
    grid = pat2grid(r, c);
    //setting path to available
    pathExist = true;
    sx = new int[50];
    sy = new int[50];
  	//used to generate food
  	food_random();
}

//generating food at random position
void Snake::food_random()
{
//if the coordinates are zero then we will generate coordinates again
  re:
    fx = rand() % (r);
    fy = rand() % (c);
    //if fx = 0 and fy = 0 or is with border then goto re
    if (fx == 0 || fy == 0 || fx == r - 1 || fy == c - 1 || fx > r || fy > c)
      goto re;
     //if fx and fy matches with the coordinates of the tail
      for(int i = 0; i < tailC; i++)
        if(fx == sx[i] || fy == sy[i])
          {
            fx = rand() % (r);
            fy = rand() % (c);
          }
    
//if food coordinates matches with the coordinates of the pattern in grid
   for(int i = 0; i < r; i++)
    {
     for(int j = 0; j < c; j++)
      {
       if(grid[i][j] == '#' && i == fx && j == fy)
        {
          fx = rand() % (r); fy = rand() % (c);
        }
      }
    }
    path();
    reverse_queue();
}

//printing the main game
void Snake::Print()
{
//clear screen by setting the cursor back to 0,0 coordinates
 SetConsoleCursorPosition(hOut, {0,0});
//main loop
 for (int i = 0; i < r ; i++)
  {
   for (int j = 0; j < c; j++)
    {
     //printing grid
	 cout<<grid[i][j];
	 //printing food
	 if(i == fx && j == fy) cout<<"F";
     //printing head of snake
	 else if(i == x && j == y) cout<<'O';
	 else
	  {
	 //flag used for printing space if there is no tail
	   int f = 0;
     //loop for iterating the snake array
	   for(int k = 0; k < tailC; k++)
	    {
	   //if coordinates matches then print the tail and set flag to 1
	      if(sx[k] == i && sy[k] == j)
	       {
	        f = 1; cout<<"*";
	       }
	    }
	   //if flag is zero, we print space
	    if(f == 0) cout<<' ';
	   }
    }
//printing new line
  cout<<endl;
    }
}

//display score
void Snake::display_score()
{
cout<<endl<<endl<<"Score: "<<sc;
}

//function to update the values of the tail's position
void Snake::moveTail()
{
//storing the initial coordinates of the tail
int tempx = sx[0], tempy = sy[0], tx, ty;
//assigning new coordinates to the tail
sx[0] = x; sy[0] = y;
//loop used to shift the coordinates to the previous tail's
for(int i = 1; i < tailC; i++)
 {
//storing the coodintes of the next tail
   tx = sx[i]; ty = sy[i];
 //assigning new coordinates to the tail
   sx[i] = tempx; sy[i] = tempy;
//updating the value of the temp variables
    tempx = tx; tempy = ty;
  }
}

//to check the collision of snake with the wall
void Snake::checkWallCollision()
{
  for(int i = 0; i < r; i++)
   {
    for(int j = 0; j < c; j++)
     {
       if(grid[i][j] == '#' && i == x && j == y && (i != 0 && i != r - 1 && j != 0 && j != c - 1))
            gameover = false;
     }
   } 
}

//to check the collision of food and snake
void Snake::eatFood()
{
//if the coordinates of the head matches with the coordinates of the food
if(x == fx && y == fy)
{
//if collision then increment the score
  sc += 10;
//to generate new food at a new random position
food_random();
//incrementing the counter means adding new tail
tailC += 1;
}
}

//to check if snake snake hits itself or not
void Snake::checkHitItself()
{
//iterate through the snake array
  for(int i = 1; i < tailC; i++)
  //if array coordinates matches the position of head
  	if(sx[i] == x && sy[i] == y)
     gameover = false;
}

char** Snake::pat2grid(int r,int c)
{
char **grid = new char*[r];
for(int i = 0; i < r; i++) grid[i] = new char [c];
fstream file;
file.open("pattern.txt");
string line;
int i = 0, j = 0;
while(getline(file,line))
{
 for(j = 0; j < line.length(); j++)
	grid[i][j] = (char)line[j];
	i++;
}
file.close();
return grid;
}

//main driver function
void Snake::driver()
{
    while(q.size() && gameover == true && pathExist == true)
    {
      //getting the coodinates of the path from the queue and storing in the head of snake
      y = q.front(); q.pop();
      x = q.front(); q.pop();
      //other functions called
      Print();
      moveTail();
      checkWallCollision();
      display_score();
      eatFood();
      checkHitItself();
    }
  
}

//function which will call the shortest_path function to calculate the shortest path
void Snake::path()
{
  shortest_path(x,y,fx,fy,q,grid,sx,sy,tailC);
}

//this function is used to reverse the queue to reverse the coordinates stored in the queue
void Snake::reverse_queue()
{
  if(q.size() > 1)
  {
    stack<int> s;
    while(q.size())
    {
    s.push(q.front());
    q.pop();
    }
    while(s.size())
    {
      q.push(s.top());
      s.pop();
    }
  }
  else pathExist = false;
}