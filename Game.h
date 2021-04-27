/*
 * Game.h
 * 
 *
 * Abstract class for general games
 *
 * @version: $Id: Game.h,v 1.4 2006/10/30 03:04:32 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *      $Log: Game.h,v $
 *      Revision 1.4  2006/10/30 03:04:32  jeg3600
 *      Milestone 3
 *
 *      Revision 1.3  2006/10/13 23:29:58  jeg3600
 *      Modified to conform to RIT C++ coding standards
 *
 *      Revision 1.2  2006/10/13 23:20:38  jeg3600
 *      *** empty log message ***
 *
 *
 */

#include<vector>
#include<iostream>
#include "GameException.h"

#ifndef GAME_H
#define GAME_H

template<typename Position>
class Game {

 public:
  
  // Work the same way. No special features needed
  // Differentiate by name only to aid reading
  typedef GameException IllegalMoveException;
  typedef GameException FormatException;
  
  /**
   * Virtual destructor for the game class
   */
  virtual ~Game() { }

  /**
   * Return what the current position is.
   * 
   * @return The current position
   *
   */
  virtual Position getCurrentPosition() const = 0;

  /**
   * Returns whether or not the position pos is a 
   * winning position.
   * 
   * @param The position to test
   * @return Whether or not it is a winner
   * 
   */
  virtual bool isWinner(const Position pos) const = 0;

  /**
   * Return whether or not the position pos is a 
   * losing position.
   * 
   * @param The position to test
   * @return Whether or not it is a losing position
   *
   */
  virtual bool isLoser(const Position pos) const = 0;
  
  /**
   * Return whether or not the position pos is a 
   * final position.
   *
   * @param The position to test
   * @return Whether or not it is a final position
   *
   */
  virtual bool isFinalPosition(const Position pos) const = 0;

  /**
   * Return a vector of all possible positions given a particular 
   * position.
   *
   * @param The given position.
   * @return A vector of all possible positions.
   *
   */
  virtual std::vector< Position > generatePositions(const Position pos) const = 0;

  /**
   * Execute the move to get the specified position
   *
   * @param The specified position
   *
   */
  virtual void executePosition(const Position pos) throw(IllegalMoveException) = 0;
  
  /**
   * Return a string representation of the specified 
   * position for use in maps
   *
   * @param pos The specified position.
   * @return The string representation of that position
   */
  virtual std::string mapString(const Position pos) const = 0;

  /*
   * Invert the board
   */
  virtual void invertBoard() = 0;

  /*
   * Invert the given position
   *
   * @param pos The position to invert
   * @return the inverted position
   *
   */
  virtual Position invertPosition(Position pos) const = 0;

};

#endif
