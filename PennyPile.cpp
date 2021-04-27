/*
 * PennyPile.cpp
 *
 * @versions: $Id: PennyPile.cpp,v 1.11 2006/11/10 21:11:50 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: PennyPile.cpp,v $
 *     Revision 1.11  2006/11/10 21:11:50  jeg3600
 *     All exceptions added
 *
 *     Revision 1.10  2006/10/30 00:19:59  jeg3600
 *     Added exceptions
 *
 *     Revision 1.9  2006/10/30 00:05:43  jeg3600
 *     Added exceptions
 *
 *     Revision 1.8  2006/10/13 06:20:00  jeg3600
 *     Redefined Position
 *
 *     Revision 1.7  2006/10/13 20:46:17  jeg3600
 *     Generalized Position
 *
 *     Revision 1.6  2006/10/13 07:31:35  jeg3600
 *     Added inheritance from Game class
 *
 *     Revision 1.5  2006/10/13 01:05:00  jeg3600
 *     Added PennyPilePosition support
 *
 *     Revision 1.4  2006/10/12 19:52:08  jeg3600
 *     Milestone 1 Submission
 *
 *     Revision 1.3  2006/10/01 18:39:06  jeg3600
 *     Added generateMoves() method to return vector of all possible moves
 *
 *     Revision 1.2  2006/25/09 08:58:26  jeg3600
 *     Added operator overloading for positions
 *
 *     Revision 1.1  2006/22/09 08:01:35  jeg3600
 *     Initial revision
 *
 */

#include "PennyPile.h"

PennyPile::PennyPile(int pennies) throw (FormatException) {
  if(pennies < 0) {
    throw FormatException("You cannot have a negative amount of pennies!");
  } else {
    current = pennies;
  }
}

bool PennyPile::isWinner(const Position pos) const throw(){
  return (pos == 1);
}

bool PennyPile::isLoser(const Position pos) const throw() {
  return (pos == 0);
}

bool PennyPile::isFinalPosition(const Position pos) const throw() {
  return isWinner(pos) || isLoser(pos);
}


PennyPile::Position PennyPile::getCurrentPosition() const throw() {
  return current;
}


std::vector< PennyPile::Position > PennyPile::generatePositions() const throw(){
  return generatePositions(getCurrentPosition());
}


std::vector< PennyPile::Position > PennyPile::generatePositions(const Position pos) const throw(){
  
  std::vector< Position > posVector;
  
  // According to the takeaway game, the player may take either
  // one, two, or three piles from the penny pile
  
  if (pos >= 1) {
    posVector.push_back(pos - 1);
  } 
    
  if (pos >= 2) {
    posVector.push_back(pos - 2);
  }
  
  if (pos >= 3) {
      posVector.push_back(pos - 3);
  }
  
  return posVector;
  
}

void PennyPile::executePosition(const Position pos) throw(IllegalMoveException) {

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
std::string PennyPile::mapString(const Position pos) const throw() {

  std::stringstream out;

  out << pos;
  
  return out.str();
  
}

// Take away num amount of pennies
void PennyPile::takeaway(unsigned int amount) throw (IllegalMoveException) {
  if(current - amount < 0) {
    throw IllegalMoveException("You cannot take away that many pennies!");
  } else {
    current -= amount;
  }
}


