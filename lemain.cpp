#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/game.h"
using namespace std;




//grep -v "#" 5-ill-chess-1.txt | ./bin/chessboard_exe > result

//--------------------------------------------------------------
int main() {
// penser à check une piece vide à la base sinn segfault
  Game mygame;
  bool stop(false);
  do {
      mygame.print();
      stop = mygame.hit();
  } while (!stop);
  cout << "end of the game" << endl;

}
