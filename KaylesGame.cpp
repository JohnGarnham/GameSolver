/*
 * KaylesGame.cpp
 *
 * Class for the Kayles game
 *
 * @version: $Id: KaylesGame.cpp,v 1.7 2006/11/10 21:25:56 jeg3600 Exp $
 * @author: John Garnham
 * 
 * Revisions:
 *     $Log: KaylesGame.cpp,v $
 *     Revision 1.7  2006/11/10 21:25:56  jeg3600
 *     Added all exceptions
 *
 *     Revision 1.6  2006/10/30 00:18:44  jeg3600
 *     Updated
 *
 *     Revision 1.5  2006/10/29 23:59:55  jeg3600
 *     Added exceptions
 *
 *     Revision 1.4  2006/10/29 14:16:24  jeg3600
 *     Fixed
 *
 *     Revision 1.3  2006/10/14 21:26:40  jeg3600
 *     Works!
 *
 *     Revision 1.2  2006/10/13 19:38:38  jeg3600
 *     Fixed generateMoves()
 *
 *     Revision 1.1  2006/10/13 22:57:41  jeg3600
 *     Initial revision
 *
 *
 */

#include "KaylesGame.h"

void KaylesGame::knockdown(int pos) throw(IllegalMoveException){
  if (current[pos]) {
    current[pos] = false;
  } else {
    throw IllegalMoveException("The peg already is knocked down!");
  }
}

void KaylesGame::knockdown(int pos1, int pos2) throw(IllegalMoveException){
  knockdown(pos1);
  if (pos2 == pos1 - 1 || pos1 == pos2 - 1) {
    knockdown(pos2);
  } else {
    throw IllegalMoveException("The pegs are not next to each other!");
  }
}

bool KaylesGame::isWinner(Position pos) const throw(){

  Position::iterator iter;

  for(iter = pos.begin(); iter != pos.end(); ++iter) 
    if (*iter) return false;
  
  return true;

}


bool KaylesGame::isLoser(Position pos) const throw() {

  int numPiles = 0, previous = 0;

  Position::iterator iter;

  for(iter = pos.begin(); iter != pos.end(); ++iter) {

    if (*iter) {

      // If there are more than 3 pegs in a row, it is a loser
      if (previous >= 2) {
	// std::cout << "More than 2 in row" << std::endl;
	return false;
      } 
      
      if (previous == 0) ++numPiles;

      ++previous;

    } else {
      previous = 0;
    }

  }
  
  // If there are more than one peg pile, it is a loser
  return numPiles == 1;

}

bool KaylesGame::isFinalPosition(Position pos) const throw() {
  return isWinner(pos) || isLoser(pos);
}

KaylesGame::Position KaylesGame::getCurrentPosition() const throw() {  
  return current;
}


std::vector< KaylesGame::Position > KaylesGame::generatePositions() const throw() {
  return generatePositions(getCurrentPosition());
}


std::vector< KaylesGame::Position > KaylesGame::generatePositions(const Position pos) const throw() {

  std::vector< Position > posVector;

  for(int i = 0; i < pos.size(); ++i) {

    // Copy the current position
    Position temp = pos;

    if (pos[i]) {
      // Knock down one pin
      temp[i] = false;
      posVector.push_back(temp);
      if(i + 1 < pos.size() && pos[i]) {
	// Knock down two pins
	temp[i + 1] = false;
	posVector.push_back(temp);
      }
    }

  }
  
  return posVector;

}

void KaylesGame::executePosition(const KaylesGame::Position pos) throw(IllegalMoveException) {

  std::vector<Position> possibles = generatePositions();

  std::vector<Position>::iterator iter;

  for(iter = possibles.begin(); iter != possibles.end(); ++iter) {
    if (pos == *iter) {
      current = pos;
      return;
    }
  }

  throw IllegalMoveException();

}


std::string KaylesGame::mapString(const Position pos) const throw() {
  
  std::stringstream out;

  for(int i = 0; i < pos.size(); ++i) {
    out << pos[i];
  }

  return out.str();

}
