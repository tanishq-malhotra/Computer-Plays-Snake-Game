Representation of the Snake Game where computer playes the snake game.

I have implemented Breadth First Search to calculate the path from snake head to the food.

After path is calculated, the snake just follows the calculated path.

Pattern of the grid is picked from the pattern.txt file and then stored in 2d char array.

Snake will run till the score is <= 200 but you can change this in the snake.cpp file in the main driver function.

Rest Explanation is given along side with code.

To compile use this command in terminal:-

g++ *.cpp -o main