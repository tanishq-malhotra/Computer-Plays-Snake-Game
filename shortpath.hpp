#include<bits/stdc++.h>
using namespace std;

//class used in our bfs algorithm
class sh
{
public:
	//x and y are the initial position's
	//i and j are used to store the position's of the previous cell
	int x,y,i,j;
	sh():x(0),y(0),i(0),j(0){}
	sh(int xx, int yy, int ii, int jj)
	{
		x=xx; y=yy; i=ii; j=jj;
	}
};


bool isValid(int r,int c)
{
	if(r >= 0 && r < 20 && c >= 0 && c < 35)
		return true;
	else 
		return false;
}
//main function
//sx and sy are the snake's head corrdinates, fx and fy are the food coordinates
//queue is passed through reference which stores the coordinates of the calculated path 
//skx and sky are the tail arrays and tailC is the count of the tail in the snake
void shortest_path(int sx,int sy,int fx,int fy,queue<int> &ss,char **grid,int *skx,int *sky,int tailC)
{
	//creating head and food in grid
	grid[sx][sy] = 'O'; 
	grid[fx][fy] = 'F';
	//creating initial object 
	sh s(sx,sy,sx,sy);
	//creating a queue to store objects
	queue<sh> q;
	//pushing the object to queue
	q.push(s);

	//creating a 2d array of objects
	sh g[20][35];

	//visited array to check the unvisited and visited sections
	bool visited[20][35];
	int a,b;

	//loop for storing the object in g and for marking visited
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 35; j++)
		{
			g[i][j] = s;
			if(grid[i][j] == '#')
				visited[i][j] = true;
			else if(grid[i][j] == 'F')
			{
				a = i; b = j; visited[i][j] = false;
			}
			else
				visited[i][j] = false;	
		}
	}

	//marking true where there is snake in the grid so that snake 
	//does not collide with itself
	for(int i = 0; i < tailC; i++)
	{
		visited[skx[i]][sky[i]] = true;
	}
	//marking source as visited
	visited[sx][sy] = true;

	int n=20,m=35;
	//arrays to move left right up and down
	int row[] = {-1,0,0,1};
	int col [] = {0,-1,1,0};
	//main bfs algo loop
	while(!q.empty())
	{
		//creating a class object
		sh p;
		//storing the front object of queue in created object
		p = q.front();
		//poping the object from queue
		q.pop();

		//checking if we reached our destination
		if(grid[p.x][p.y] == 'F')
			{  break; }
		
		//loop to move up down left and right
		for(int i = 0; i < 4; i++)
		{
			//getting new coordinates
			int r = p.x + row[i];
			int c = p.y + col[i];
			//if its true
			if(isValid(r,c) && visited[r][c] == false)
			{
				//pushing new object in queue
				q.push(sh(r,c,0,0));
				//marking visited as true
				visited[r][c] = true;
				//storing the coordinates of previous cell in new cell's i and j to make path
				g[r][c].i = p.x;
				g[r][c].j = p.y;
			}
		}

	}
	//backtracking to create the path
	while(1)
	{
		//storing the corrdinates in the queue
	    ss.push(a);
	    ss.push(b);
	    //changing the values of a and b to the previous posititon 
	    //stored in the i and j of the object
		a = g[a][b].i;
		b = g[a][b].j;

		//if we have reached to our source
		if(grid[a][b] == 'O') break;
	}
	//deleting the head and food from grid 
	grid[sx][sy] = ' '; 
	grid[fx][fy] = ' ';
}