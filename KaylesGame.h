/*
 * KaylesGame.h
 *
 * Class for Kayles game 
 *
 * @version: $Id: KaylesGame.h,v 1.8 2006/11/10 21:25:56 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Reivisions:
 *      $Log: KaylesGame.h,v $
 *      Revision 1.8  2006/11/10 21:25:56  jeg3600
 *      Added all exceptions
 *
 *      Revision 1.7  2006/10/30 03:04:22  jeg3600
 *      Milestone 3
 *
 *      Revision 1.6  2006/10/30 00:19:02  jeg3600
 *      Updated
 *
 *      Revision 1.5  2006/10/29 23:59:48  jeg3600
 *      Added exceptions
 *
 *      Revision 1.4  2006/10/29 14:16:11  jeg3600
 *      Fixed
 *
 *      Revision 1.3  2006/10/14 21:26:29  jeg3600
 *      Works!
 *
 *      Revision 1.2  2006/10/13 19:38:29  jeg3600
 *      Fixed generateMoves()
 *
 *      Revision 1.1  2006/10/13 22:57:35  jeg3600
 *      Initial revision
 *
 */

#include <iostream>
#include <sstream>
#include "Game.h"

#ifndef KAYLES_H
#define KAYLES_H

class KaylesGame : public Game< std::vector<bool> >{

 public: 

  // Position type
  typedef std::vector<bool> Position;

 private:

  // The current position
  Position current;


 public:

  // Class specific

  /**
   * Constructor for KaylesGame
   *
   * @param What to start with
   */ 
  KaylesGame(Position newPegs) throw() : current(newPegs) { }

  /**
   * Destructor for KaylesGame
   * Nothing to do
   */
  ~KaylesGame() throw() { };

  void knockdown(int pos) throw(IllegalMoveException);
  void knockdown(int pos1, int pos2) throw(IllegalMoveException);

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
   * current position
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
  virtual void executePosition(const Position pos) throw (IllegalMoveException);

  /**
   * Return a string representation of the specified 
   * position for use in maps
   *
   * @param pos The specified position.
   * @return The string representation of that position
   */
  virtual std::string mapString(const Position pos) const throw();

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
