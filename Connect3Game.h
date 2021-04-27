e/**
 * Connect3Game.h
 *
 * Class for Connect three game
 *
 * @version: $Id: Connect3Game.h,v 1.5 2006/11/10 21:39:10 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: Connect3Game.h,v $
 *     Revision 1.5  2006/11/10 21:39:10  jeg3600
 *     Added exceptions
 *
 *     Revision 1.4  2006/10/30 03:43:51  jeg3600
 *     Milestone 3
 *
 *     Revision 1.3  2006/10/30 00:19:26  jeg3600
 *     Added exceptions
 *
 *     Revision 1.2  2006/10/27 22:45:00  jeg3600
 *     Initial methods done
 *
 *     Revision 1.1  2006/10/27 09:20:14  jeg3600
 *     Initial revision
 *
 *
 */

#include <iostream>
#include <sstream>
#include "Game.h"


class Connect3Game : public Game< std::vector< std::vector<int> > > {

 public:

  // Position type
  typedef std::vector< std::vector< int > > Position;

 private:

  // Private data members

  int width, height;

  Position current;

 public:

  // Class specific

  enum {B = 0, X = 1, O = 2};

  /**
   * Constructor for Connect3Game
   *
   * @param What to start with
   */
  Connect3Game(Position newGame, int w, int h) throw (FormatException);

  // Return the width
  inline int getWidth() const throw() { return width; } ;
  
  // Return the height
  inline int getHeight() const throw() { return height; } ;

  // Drop a piece
  void drop(int where) throw (IllegalMoveException);

  ~Connect3Game() { };

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
  virtual void executePosition(const Position pos) throw(IllegalMoveException);

  /**
   * Return a string representation of the specified 
   * position for use in maps
   *
   * @param pos The specified position.
   * @return The string representation of that position
   */
  virtual std::string mapString(const Position pos) const throw() ;

  /**
   * Invert the connect3 board
   */
  virtual void invertBoard() throw();

  /**
   * Invert the position
   * 
   * @param - Position to invert
   *
   */
  virtual Position invertPosition(Position pos) const throw();

};
