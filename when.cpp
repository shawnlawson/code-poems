// c++ when.cpp -o when
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
  int wildGuess, distanceTraveled = 0, aBit = 1;

  cout << "How far does it feel to get there? >> ";
    
  while( !(cin >> wildGuess) ){
    cout << "try a number >> ";
    cin.clear();
    cin.ignore();
  }

  int forever = rand() % wildGuess;

  while( distanceTraveled < forever ){
    cout << "... are we there yet?\n";
    distanceTraveled += aBit;
    sleep(1);
  }

  cout << "Yes, finally.\n";
}