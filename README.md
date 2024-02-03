<p align="center">
  <img src="https://github.com/zongqiooi/laser-tank/assets/95561298/e0d83e60-406d-49d5-a04b-10d4f088ca66" alt="animated" />
  <h1 align="center">Laser Tank</h1>
</p>

<p align="center">
  A 2D shooting game in C.
</p>

<p align="center">
  <a href="#introduction"><strong>Introduction</strong></a> ·
  <a href="#features"><strong>Features</strong></a> ·
  <a href="#tech-stack"><strong>Tech Stack</strong></a> ·
  <a href="#prerequisite"><strong>Prerequisite</strong></a> ·
  <a href="#setting-up-locally"><strong>Setting Up Locally</strong></a>
</p>
<br/>

# Introduction
LaserTank is a 2D game that allows the player to control the movement of the laser tank and shoot a laser. The laser will be reflected when it hits the mirrors. After the game ends, all the 2D maps game history stored in a linked list will be saved into a log text file. 

# Features  
1) Player
    * **Movement**: Move by using the WASD keys 
    * **Shooting**: Shoot by using the F key 
2) Enemy
    * **Shooting**: Shoot by the enemy automatically when the player moves into the direction where the enemy is facing
3) Laser
    * **Color changing**: Switch in RGB colour when the laser travels each step
4) Mirrors
    * **Laser reflection**: Reflect and change the direction of the laser into 4 different directions depending on the incoming laser direction (North, East, South, West) and mirror-facing directions (/ or \ mirrors)
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

# Tech Stack 
- [C](https://www.cprogramming.com/) - programming language
- [Makefile](https://www.gnu.org/software/make/) - utility tool for automation

# Prerequisite 
Ubuntu environment is required to run the project. The Ubuntu on WSL2 in Windows can be installed and run with VS code in the following link: https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10

# Setting Up Locally
Make sure you have downloaded Ubuntu as mentioned in the pre-requisites section and changed the environment to Ubuntu in VS Code     

To run the app locally, you can run the following commands:

```
git clone https://github.com/zongqiooi/laser-tank.git
cd laser-tank
code .
sudo apt install make
sudo apt install gcc
make
./laserTank map.txt log.txt
```
