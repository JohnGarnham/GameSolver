/*
 * GameException.h
 *
 * Exception for when illegal moves are attempted
 *
 * @version:  $Id: GameException.h,v 1.1 2006/10/29 23:46:33 jeg3600 Exp jeg3600 $
 * @author:  John Garnham
 *
 * Revisions:
 *     $Log: GameException.h,v $
 *
 *     Revision 1.1  2006/10/27 23:42:59  jeg3600
 *     Initial revision
 *
 */

#include<iostream>

#ifndef ILL_MOVE_EX
#define ILL_MOVE_EX

using namespace std;

class GameException {
 private:

  // The exception message
  string mesg;

 public:
  
  /**
   * Constructor for game exception
   *
   * @param msg - the error message
   *
   */
  GameException(const string msg = "") : mesg(msg) { }

  /**
   * Return the error message
   *
   * @return - the error message
   */
  string message() { return mesg; }

  /**
   * Destructor for game exception
   */
  ~GameException() { }


};

#endif
