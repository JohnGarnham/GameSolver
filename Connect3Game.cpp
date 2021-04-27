/**
 * Connect3Game.cpp
 *
 * Implementation for Connect3Game class
 *
 * @version:  $Id: Connect3Game.cpp,v 1.5 2006/11/10 21:39:17 jeg3600 Exp jeg3600 $
 * @author:  John Garnham
 *
 * Revisions:
 *     $Log: Connect3Game.cpp,v $
 *     Revision 1.5  2006/11/10 21:39:17  jeg3600
 *     Added all exceptions
 *
 *     Revision 1.4  2006/10/30 03:43:45  jeg3600
 *     Milestone 3
 *
 *     Revision 1.3  2006/10/30 00:19:33  jeg3600
 *     Added exceptions
 *
 *     Revision 1.2  2006/10/27 22:44:53  jeg3600
 *     Initial methods done
 *
 *     Revision 1.1  2006/10/27 09:20:18  jeg3600
 *     Initial revision
 *
 *
 */

#include "Connect3Game.h"

Connect3Game::Connect3Game(Position newGame, int w, int h) throw (FormatException) {
  
  if (w <= 0) {
    throw FormatException("Illegal width!");
  } else {
    width = w;
  }

  if(h <= 0) {
    throw FormatException("Illegal height!");
  } else {
    height = h;
  }

  // Check if the board is valid
  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {
      // Make sure O and Xs are not "floating"
      if(newGame[y][x] != B) {
	// Y-coordinates upside down
	for(int i = y; i < height; ++i) {
	  if(newGame[i][x] == B) {
	    throw FormatException("Illegal board!");
	  }
	} 
	if(newGame[y][x] != B && newGame[y][x] != X && newGame[y][x] != O) {
	  throw FormatException("Illegal board!");
	}
      } 
    }
  }

  current = newGame;

}

void Connect3Game::invertBoard() throw() {
  current = invertPosition(current);
}

Connect3Game::Position Connect3Game::invertPosition(Connect3Game::Position pos) const throw() {

  Position temp = pos;

  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {
      if (temp[y][x] == X) {
	temp[y][x] = O;
      } else {
	if (temp[y][x] == O) temp[y][x] = X;
      }
    }
  }
  
  return temp;

}
void Connect3Game::drop(int where) throw (IllegalMoveException){
  
  if(where < 0 || where > width) {
    throw IllegalMoveException("Invalid place to drop a piece!");
  }

  if(current[0][where] != B) {
    throw IllegalMoveException("Column already full!");
  }

  // Start from bottom-up
  for(int y = height - 1; y >= 0; --y) {
    
    if(current[y][where] == B) {
      current[y][where] = X;
      return;
    }

  }
   
}


bool Connect3Game::isWinner(const Connect3Game::Position pos) const throw() {

  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {

      // Check if you can win
      
      if (pos[y][x] == X) {
	    
	// Check for XXXs
	
	if(x + 2 < width) {
	  if (pos[y][x+1] == X && pos[y][x+2] == X)  return true;
	}
	  
	if(y - 2 >= 0) {

	  // Check for X
	  //           X
	  //	       Xs
	  if (pos[y-1][x] == X && pos[y-2][x] == X) return true;

	  
	  // Check for X    X
	  //            X  X
	  //             XX    s
	  if(x + 2 < width && pos[y-1][x+1] == X && pos[y-2][x+2] == X) return true;

	  if(x - 2 >= 0 && pos[y-1][x-1] == X && pos[y-2][x-2] == X) return true;

	}
      
      } 

    }
  }

  return false;

}

bool Connect3Game::isLoser(const Connect3Game::Position pos) const throw() {

  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {

      // Prevent other player from winning 

      if(pos[y][x] == O) {

	// OOO
	if (x + 2 < width && pos[y][x+1] == O && pos[y][x+2] == O) return true;

	if(y - 2 >= 0) {
	  
	  // O
	  // O
	  // O
	  if (pos[y-1][x] == O && pos[y-2][x] == O) return true;
	
	  // Check for O    Os
	  //            O  O
	  //             OO
	  if(x+2 < width && pos[y-1][x+1] == O && pos[y-2][x+2] == O) return true;

	  if(x-2 >= 0 && pos[y-1][x-1] == O && pos[y-2][x-2] == O) return true;
	
	}
	
      }
      
    }

  }

  return false;

}

bool Connect3Game::isFinalPosition(const Connect3Game::Position pos) const throw() {

  
  if(isWinner(pos)) {
    return true;
  }

  Position other = invertPosition(pos);
  if(isWinner(other)) {
    return true;
  }

  // Draw
  bool full = true;
  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {
      if (pos[y][x] == B) full = false;
    }
  }

  return full;

}


Connect3Game::Position Connect3Game::getCurrentPosition() const throw() {

  return current;

}

std::vector< Connect3Game::Position > Connect3Game::generatePositions() const throw() {
  return generatePositions(getCurrentPosition());
}

std::vector< Connect3Game::Position > Connect3Game::generatePositions(const Position pos) const throw() {

  std::vector< Connect3Game::Position > posVector;

  bool found[width];
  for(int i = 0; i < width; ++i) { found[i] = false; }

  // Start from bottom-up
  for(int y = height - 1; y >= 0; --y) {
    for(int x = 0; x < width; ++x) {
      
      if ( ! found[x] ) {
	
	// Check for first B
	if (pos[y][x] == B) {
	  	  
	  Position temp = pos;
	  temp[y][x] = X;
	  posVector.push_back(temp);
	  found[x] = true;
	 
	}
	
      }
      

    }
  }
 
  return posVector;

}

void Connect3Game::executePosition(const Connect3Game::Position pos) throw(IllegalMoveException) {
  
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

std::string Connect3Game::mapString(const Connect3Game::Position pos) const throw() {

  std::stringstream out;

  for(unsigned int i = 0; i < pos.size(); ++i) {
    for(unsigned int j = 0; j < pos[i].size(); ++j) {
      out << pos[i][j];
    }
    out << "\n";
  }
      
  return out.str();

}

