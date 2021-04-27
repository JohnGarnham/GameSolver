/*
 * Strategy.h
 * 
 * @version: $Id: Strategy.h,v 1.8 2006/10/30 01:00:29 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: Strategy.h,v $
 *     Revision 1.8  2006/10/30 01:00:29  jeg3600
 *     Updated
 *
 *     Revision 1.7  2006/10/29 14:15:59  jeg3600
 *     Made more efficient
 *
 *     Revision 1.6  2006/10/13 21:26:04  jeg3600
 *     Now works for both Kayles and Takeaway!
 *
 *     Revision 1.5  2006/10/13 10:40:13  jeg3600
 *     Works!
 *
 *     Revision 1.4  2006/10/13 06:43:45  jeg3600
 *     Redefined position
 *
 *     Revision 1.3  2006/10/12 19:52:27  jeg3600
 *     Milestone 1 Submission
 *
 *     Revision 1.2  2006/10/02 01:44:00  jeg3600
 *     Combined Strategy.h and Strategy.cpp due to linking issues
 *
 *     Revision 1.1  2006/26/09 07:58:08  jeg3600
 *     Made more generic with WIN and LOOSE variables
 *
 */

#include<vector>
#include<map>
#include<iostream>
#include "Game.h"

#ifndef STRATEGY_H
#define STRATEGY_H

template<class Position, class Game>
class Strategy {
  
  // A pointer to the game to form the strategy for
  Game* game;

  // Type for the memory map
  typedef std::map<std::string, float> memoryMap;

  // For memorizing the scores of previous positions
  memoryMap memorizer;

 public:

  /**
   * Constructor for Strategy class
   * 
   * @param A copy of the game involved
   * 
   */
  Strategy(Game &newGame) { game = &newGame; }

  /**
   * Returns what the best next position would be given 
   * the current condition.
   *
   * @return The best move
   *
   */
  Position getBestMove() throw();
  
  /**
   * Returns what the best next position would be given
   * a list of possible positions.
   *
   * @param A vector of the possible positions
   * @return The best move
   *
   */
  Position getBestMove(std::vector<Position>) throw();
  
  /**
   * Returns a numeric representation of how good
   * a particular position is. The lower that
   * the number returned is, the better that
   * position is. 0 is an automic win, 1 is an 
   * automatic loss.
   * 
   * @param A given position
   * @return The score of that given position
   *
   */
  float scorePosition(Position pos) throw();
  
};


template<class Position, class Game>
Position Strategy<Position, Game>::getBestMove() throw() {
  return getBestMove(Strategy::game->generatePositions());
}

template<class Position, class Game>
Position Strategy<Position, Game>::getBestMove(std::vector< Position > positions) throw() {

    // Loop through each possibility
    // and if the posibilty results in an automatic
    // loss for the player (is a winner for you), 
    // then choose that move
    
    typename std::vector< Position >::iterator current;
    
    Position bestPosition = positions[0];
    float bestScore = 1;

    bool found_winner = false;
    
    for (current = positions.begin(); current != positions.end(); ++current) {
      
      float score = scorePosition(*current);
	
      // Nothing is better than a complete win
      if (score == 0) return *current;
      
      // Otherwise, get the best from the remaining choices
      if (score < bestScore) {
	bestPosition = *current;
      }
      
    }
    
    return bestPosition;
    
}

template<class Position, class Game>
float Strategy<Position, Game>::scorePosition(Position pos) throw() {
  
  // Check if the score has been memorized

  std::string mapString = Strategy::game->mapString(pos); 

  memoryMap::iterator iter = memorizer.find(mapString);

  if ( iter != memorizer.end() ) return iter->second;

  if (game->isFinalPosition(pos)) {
    if (game->isWinner(pos)) {
      memorizer[mapString] = 0;
      return 0;
    } else {
      memorizer[mapString] = 1;
      return 1;
    }

  } else {
    
    // If it results in all loses, the position is a winner
    // Calculate the position as the average of the children outcomes
    
    // Cycle through each child
      std::vector< Position > children = 
	game->generatePositions(pos);

      bool alwaysLooses = true;
      
      typename std::vector< Position >::iterator currentChild;
      
      for (currentChild = children.begin(); currentChild != children.end();
	   ++currentChild) {
	
	if (scorePosition(*currentChild) == 0) {
	  alwaysLooses = false;
	}
	
      }
      
      if (alwaysLooses) {
	memorizer[mapString] = 0;
	return 0;
      } else {
	memorizer[mapString] = 1;
	return 1;
      }

  }

}

#endif

