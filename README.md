<p align="center">
  <img src="https://github.com/zongqiooi/laser-tank/assets/95561298/e0d83e60-406d-49d5-a04b-10d4f088ca66" alt="animated" />
</p>

# LaserTank
LaserTank is a 2D game that allows the player to control the movement of the laser tank and shoot a laser. The laser will be reflected when it hits the mirrors. After the game ends, all the game history will be saved into a log file by using a linked list. 

# Fun Facts 
This is an assignment for the <strong>COMP1000: Unix and C Programming</strong> course that I have taken and probably the assignment that I enjoyed the most and had the most fun completing it. 

<strong>Fun fact</strong>: I completed this entire 2 months assignment within 6 days and received a score of 100/100 😗

# Tech Stack Used
- C
- Makefile 

# Features  
1) Player
    * **Movement**: Move by using the WASD keys 
    * **Shooting**: Shoot by using the F key 
2) Enemy
    * **Shooting**: Shoot by the enemy automatically when the player moves into the direction where the enemy is facing
3) Laser
    * **Color changing**: Switch in RGB colour when the laser travels each step
4) Mirrors
    * **Laser Reflection**: Reflect and change the direction of the laser into 4 different directions depending on the incoming laser direction (North, East, South, West) and mirror-facing directions (/ or \ mirrors)
5) Map
    * **Boundary**: Restrict the player and laser to move beyond the boundary
    * **Map size**: Configurable map size by changing the first line in the "map.txt" text file
6) Log file
    * **Saving**: Save the log of game history using the L key or automatically saved when a winning or losing condition happens
7) Game conditions
    * **Winning**: The enemy is hit by the laser shot by the player
    * **Losing**: The player is hit by its own laser due to mirror reflection OR the player is hit by the enemy laser when it moves into the direction where the enemy is facing
8) Zero memory leaks
    * **Zero memory leaks**: Achieved zero memory leaks with malloc and free functions for the map created with dynamic array and the game log history stored with linked list
   
# Pre-requisites 
Ubuntu environment is required to run the project. The Ubuntu on WSL2 in Windows can be installed and run with VS code in the following link: https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10

# How to Run the Project 
Make sure you have downloaded Ubuntu as mentioned in the pre-requisites section and changed the environment to Ubuntu in VS Code     

1. Clone the project into the local machine   
`git clone https://github.com/zongqiooi/laser-tank.git`
2. Change the directory into the project folder    
`cd laser-tank`
3. Open the current directory in VS Code       
`code .` 
4. Install "make"        
`sudo apt install make`
5. Install "gcc"         
`sudo apt install gcc`
6. Compile the makefile        
`make`
7. Run the laser tank application file with "map.txt" and "log.txt" as command line arguments         
`./laserTank map.txt log.txt`

