# chess-cpp

This is C++ console application with witch you can play chess with another player.

## How it works?

When you run an application in command prompt, you will see chess board and you will be invite to make move.

![start_game](https://user-images.githubusercontent.com/55924004/93360424-eebbbe00-f843-11ea-8ea4-0a78432c0f25.PNG)

Moves are making by giving coordinate of field with chessman which we want to move and then giving the coordinates of field where we want to move this chessman.\
Game logic check possible moves and when king is checked:

![check](https://user-images.githubusercontent.com/55924004/93360433-f24f4500-f843-11ea-9c37-342763b459b2.PNG)

or when is checkmate:

![checkmate](https://user-images.githubusercontent.com/55924004/93360443-f4b19f00-f843-11ea-99e1-7976c3534cbc.PNG)

## Installation on Ubuntu

Clone github repository:

```bash
git clone https://github.com/konradkrasno/chess-cpp.git
cd chess-cpp/ChessBoard
```
Install g++ and make:
```bash
apt-get update && apt-get install g++ make
```
Compile and run the program:
```bash
make -f chess.mak
./chess
```
