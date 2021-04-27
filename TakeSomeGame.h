/*
 * TakeSomeGame.h
 *
 * @version $Id: TakeSomeGame.h,v 1.2 2006/11/10 21:21:05 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *      $Log: TakeSomeGame.h,v $
 *      Revision 1.2  2006/11/10 21:21:05  jeg3600
 *      Added all exceptions
 *
 *      Revision 1.1  2006/11/09 09:35:19  jeg3600
 *      Initial revision
 *
 *
 */

#include <sstream>
#include "Game.h"

#ifndef TAKESOMEGAME_H
#define TAKESOMEGAME_H

class TakeSomeGame : public Game<unsigned int> {

 public:

  // Position type
  typedef unsigned int Position;

 private:

  // The current number of pennies in the pile
  Position current;

  std::vector<Position> valids;

 public: 

  // Class specific
  
  /*
   * Constructer for take some game
   *
   * @param pennies - the amount of pennies to begin with
   * @param valids - the list of valid moves
   * @exception - in case an invalid amount of pennies or valid moves is sent in
   *
   */
  TakeSomeGame(int pennies, std::vector<Position> valids) throw (FormatException);

  /**
   * Take away a specified amount of pennies
   *
   * @param the amount of pennies
   */
  void takeaway(unsigned int amount) throw (IllegalMoveException);


  /*
   * Make sure that the specified move is one of 
   * the valid moves listed
   *
   * @param the move to test validity on
   * @return whether or not that move is valid
  */
  bool isValidMove(const Position pos) const throw();

  /**
   * Destructor
   * Don't do anything. Didn't allocate anything
   */
  ~TakeSomeGame() throw() { }

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
   *
   */
  virtual void executePosition( const Position pos) throw(IllegalMoveException);

  /**
   * Return a string representation of the specified 
   * position for use in maps
   *
   * @param pos The specified position.
   * @return The string representation of that position
   */
  virtual std::string mapString( const Position pos ) const throw();

  // Invert the board. Don't do anything
  virtual void invertBoard() throw() { }

  // Invert position. Don't do anything
  virtual Position invertPosition(Position pos) const throw() { return pos; }

};

#endif
