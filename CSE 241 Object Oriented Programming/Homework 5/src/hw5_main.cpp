#include <iostream>
#include <string>
#include <vector>
#include "BoardGame2D.h"
#include "PegSolitaire.h"
#include "EightPuzzle.h"
#include "Klotski.h"

using namespace std;
using namespace Base;
using namespace derived_peg;
using namespace derived_puzzle;
using namespace derived_klotski;

int main(){
  vector<BoardGame2D*> all_games;

  PegSolitaire pegBoard1;

  PegSolitaire pegBoard2;

  EightPuzzle puzzleBoard1;

  EightPuzzle puzzleBoard2;

  Klotski klotksiBoard1;

  Klotski klotksiBoard2;

  all_games.push_back(&pegBoard1);

  all_games.push_back(&pegBoard2);

  all_games.push_back(&puzzleBoard1);

  all_games.push_back(&puzzleBoard2);

  all_games.push_back(&klotksiBoard1);

  all_games.push_back(&klotksiBoard2);

  playVector(all_games);

}
