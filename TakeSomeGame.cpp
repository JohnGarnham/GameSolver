/*
 * TakeSomeGame.cpp
 * 
 * @version $Id: TakeSomeGame.cpp,v 1.2 2006/11/10 21:20:59 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *      $Log: TakeSomeGame.cpp,v $
 *      Revision 1.2  2006/11/10 21:20:59  jeg3600
 *      Added all exceptions
 *
 *      Revision 1.1  2006/11/09 09:35:15  jeg3600
 *      Initial revision
 *
 *
 */


#include "TakeSomeGame.h"

TakeSomeGame::TakeSomeGame(int pennies, std::vector<Position> vlds) throw (FormatException) {
  if(pennies < 0) {
    throw FormatException("You cannot have a negative amount of pennies!");
  } else {
    current = pennies;
  }

  for(unsigned int i = 0; i < vlds.size(); ++i) {
    if (vlds[i] <= 0) {
      throw FormatException("Invalid take-away amount!");
    }
  }

  valids = vlds;

}

bool TakeSomeGame::isValidMove(const Position pos) const throw() {
  
  
  for(unsigned int i = 0; i < valids.size(); ++i) {
    if( pos == valids[i]) return true;
  }

  return false;


}

bool TakeSomeGame::isWinner(const Position pos) const throw(){

  Position min = valids[0];
  for(unsigned int i = 1; i < valids.size(); ++i) {
    if(valids[i] < min) min = valids[i];
  }

  return (pos < min);


}

bool TakeSomeGame::isLoser(const Position pos) const throw(){

  
  bool ever_finds = false;

  for(unsigned int i = 0; i < valids.size(); ++i) {
    if (pos == valids[i]) ever_finds = true;
  }

  return ever_finds;

}

bool TakeSomeGame::isFinalPosition(const Position pos) const throw(){
  return isWinner(pos) || isLoser(pos);
}


TakeSomeGame::Position TakeSomeGame::getCurrentPosition() const throw() {
  return current;
}


std::vector< TakeSomeGame::Position > TakeSomeGame::generatePositions() const throw() {
  return generatePositions(getCurrentPosition());
}


std::vector< TakeSomeGame::Position > TakeSomeGame::generatePositions(const Position pos) const throw() {
  
  std::vector< Position > posVector;
  
  // According to the takeaway game, the player may take either
  // one, two, or three piles from the penny pile
  
  for(unsigned int i = 0; i < valids.size(); ++i) {
    
    if (pos >= valids[i]) {
      // cout << "Valid: " << pos - valids[i] << endl;
      posVector.push_back(pos - valids[i]);
    } 
    
  }
  
  return posVector;
  
}

void TakeSomeGame::executePosition(const Position pos) throw(IllegalMoveException) {

  std::vector<Position> possibles = generatePositions();

  std::vector<Position>::iterator iter;

  for(iter = possibles.begin(); iter != possibles.end(); ++iter) {
    if(pos == *iter) {
      current = pos;
      return;
    }
  }

  throw IllegalMoveException();

}

// Convert the position into a string for storing in maps
std::string TakeSomeGame::mapString(const Position pos) const throw() {

  std::stringstream out;

  out << pos;
  
  return out.str();
  
}

// Take away num amount of pennies
void TakeSomeGame::takeaway(unsigned int amount) throw (IllegalMoveException) {
  
  for(unsigned int i = 0; i < valids.size(); ++i) {
    if(amount == valids[i]) {
      if(current - amount < 0) {
	throw IllegalMoveException("You cannot take away that many pennies!");
      } else {
	current -= amount;
      }
    }
  }

  throw IllegalMoveException("You cannot take away that many pennies!");

}


