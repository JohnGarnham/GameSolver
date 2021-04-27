/*
 * PennyPile.h
 *
 * @version: $Id: PennyPile.h,v 1.12 2006/11/10 21:12:02 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: PennyPile.h,v $
 *     Revision 1.12  2006/11/10 21:12:02  jeg3600
 *     All exceptions added
 *
 *     Revision 1.11  2006/10/30 03:04:15  jeg3600
 *     Milestone 3
 *
 *     Revision 1.10  2006/10/30 00:19:47  jeg3600
 *     Added exceptions
 *
 *     Revision 1.9  2006/10/30 00:05:36  jeg3600
 *     Added exceptions
 *
 *     Revision 1.8  2006/10/13 06:11:03  jeg3600
 *     Redefined position
 *
 *     Revision 1.7  2006/10/13 20:46:05  jeg3600
 *     Generalized Position
 *
 *     Revision 1.6  2006/10/13 07:31:25  jeg3600
 *     Added inheritance from Game class
 *
 *     Revision 1.5  2006/10/13 01:04:39  jeg3600
 *     Added PennyPilePosition support
 *
 *     Revision 1.4  2006/10/12 19:52:19  jeg3600
 *     Milestone 1 Submission
 *
 *     Revision 1.3  2006/10/01 18:38:52  jeg3600
 *     Added generateMoves() method to return vector of all posibile moves
 *
 *     Revision 1.2  2006/25/09 08:58:12  jeg3600
 *     Added operator overloading for positions
 *
 *     Revision 1.1  2006/22/09 08:01:40  jeg3600
 *     Initial revision
 *
 */

#include <sstream>
#include "Game.h"

#ifndef PENNYPILE_H
#define PENNYPILE_H

class PennyPile : public Game<unsigned int> {

 public: 

  // The position type
  typedef unsigned int Position;

 private:

  // The current number of pennies in the pile
  Position current;

 public:

  // Class specific

  /**
   * Constructor the the penny pile class
   *
   * @param - the amount of pennies
   * @exception - an illegal amount of pennies is passed in
   */
  PennyPile(int pennies) throw (FormatException);

  /**
   * Take away a specified amount of pennies
   *
   * @param - the amount of pennies
   * @exception - an illegal move is attempted 
   */
  void takeaway(unsigned int amount) throw (IllegalMoveException);

  /**
   * Destructor for PennyPile
   * Didn't allocate anything. Don't need to do anything.
   */
  ~PennyPile() throw() { };

 public:

  // Inherited from Game

  /**
   * Returns whether or not the position pos is a 
   * winning position.
   * 
   * @param The position to test
   * @return Whether or not it is a winner
   * 
   */
  virtual bool isWinner(const Position pos) const throw();

  /**
   * Return whether or not the position pos is a 
   * losing position.
   * 
   * @param The position to test
   * @return Whether or not it is a losing position
   *
   */
  virtual bool isLoser(const Position pos) const throw();
  
  /**
   * Return whether or not the position pos is a 
   * final position.
   *
   * @param The position to test
   * @return Whether or not it is a final position
   *
   */
  virtual bool isFinalPosition(const Position pos) const throw();

  /**
   * Return what the current position is.
   * 
   * @return The current position
   *
   */
  virtual Position getCurrentPosition() const throw();
  
  /**
   * Return a vector of all possible positions given the
   * current position. Player is irrelevant in this case.
   *
   * @return A vector of all possible positions.
   *
   */ 
  std::vector< Position > generatePositions() const throw();
  
  /**
   * Return a vector of all possible positions given a particular 
   * position.
   *
   * @param The given position.
   * @return A vector of all possible positions.
   *
   */
  virtual std::vector< Position > generatePositions(const Position pos) const throw();

  /**
   * Execute the move to get the specified position
   *
   * @param The specified position
   * @exception - an illegal move is attempted
   */
  virtual void executePosition( const Position pos) throw(IllegalMoveException);

  /**
   * Return a string representation of the specified 
   * position for use in maps
   *
   * @param pos The specified position.
   * @return The string representation of that position
   */
  virtual std::string mapString( const Position pos ) const throw() ;

  /**
   * Invert the board
   */
  virtual void invertBoard() throw() { }

  /*
   * Invert the position
   *
   * @param - the position to invert
   * @return - the inverted position
   * 
   */
  virtual Position invertPosition(Position pos) const throw() { return pos; }

};

#endif
