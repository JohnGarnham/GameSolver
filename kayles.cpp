/*
 * Main program for playing Kayles game
 *
 * @version     $Id: kayles.cpp,v 1.6 2006/11/10 22:29:34 jeg3600 Exp jeg3600 $
 * @author      John Garnham
 * Revisions:
 *     $Log: kayles.cpp,v $
 *     Revision 1.6  2006/11/10 22:29:34  jeg3600
 *     Fixed
 *
 *     Revision 1.5  2006/11/10 22:24:33  jeg3600
 *     Fixed input errors
 *
 *     Revision 1.4  2006/10/30 01:09:01  jeg3600
 *     Updated
 *
 *     Revision 1.3  2006/10/29 14:16:33  jeg3600
 *     Fixed
 *
 *     Revision 1.2  2006/10/15 21:25:21  jeg3600
 *     Works on non-play mode!
 *
 *     Revision 1.1  2006/10/9 22:59:40  jeg3600
 *     Initial revision
 *
 */

#include <iostream>
#include <vector>
#include "KaylesGame.h"
#include "Strategy.h"

using namespace std;

int main(int argc, char* argv[]) {

  if (argc < 2 ) {
    cerr << "Usage: kayles [play] lineData" << endl;
    return -1;
  }  

  bool play_mode = false;

  // Where to start collecting position data
  int start = 1;

  KaylesGame::Position pegs;

  if (strcmp(argv[1], "play") == 0) {
      play_mode = true;
      start = 2;
      if (argc == 2) {
	cerr << "Usage: kayles [play] lineData" << endl;
	return -1;
      }
  }
  
  for(int i = start; i < argc; ++i) {
    int pile = -1;
    stringstream ss;
    ss << argv[i];
    ss >> pile;

    if (pile < 0) {
      cerr << "Invalid line data!" << endl;
      return -1;
    }

    for(int j = 0; j < pile; ++j) {
      pegs.push_back(true);
    }

    if (i != argc - 1) {
      pegs.push_back(false);
    }
  }

  try {

    KaylesGame game(pegs);
    Strategy< KaylesGame::Position, KaylesGame > strategy(game);
    
    if (play_mode) {
      
      // Print out the kayles piles
      KaylesGame::Position current = game.getCurrentPosition();
      
      // Print out the peg pile sizes
      for(unsigned int i = 0; i < current.size(); ++i) {
	if (current[i]) {
	  cout << 'X';
	} else {
	  cout << '_';
	}
      }
      cout << endl;
      
      // Print out the peg pile positions
      for(unsigned int i = 0; i < current.size(); ++i) {
	cout << i;
      }
      cout << endl;
      
      while(! game.isWinner(game.getCurrentPosition()) ) {
	
	
	// *******************
	// Player's turn
	// *******************
	
	int pos1 = -1, pos2 = -1, size = 0;
	string input = "";
	
	cout << "From what position(s) do you want to remove a peg? ";
	cin >> input;

	unsigned int comma = input.find(",");
	string left = "";
	
	// C++ is annoying
	stringstream ss;
	if (comma != string::npos) {
	  // Two positions specified
	  
	  ss << input.substr(0, comma);
	  ss >> pos1;
	  
	  ss.clear(); 
	  ss << input.substr(comma + 1);
	  ss >> pos2;
	  
	  left = input.substr(comma +1);
	  
	  size = 2;
	  
	} else {
	  
	  ss << input;
	  ss >> pos1;
	  
	  size = 1;
	
	}

	while(pos1 < 0 || (unsigned) pos1 >= current.size() 
	      || current[pos1] == false
	      || left.find(",") != string::npos ||
	      (size == 2 && (pos2 < 0 || (unsigned) pos2 >= current.size() ||
			     current[pos2] == false || abs(pos2 - pos1) != 1))) 
	  {
	    
	    pos1 = -1, pos2 = -1, size = 0;
	    
	    cout << "Invalid data!\n" 
		 << "From what position(s) do you want to remove a peg? ";
	    cin >> input;
	    
	    comma = input.find(",");
	    
	    left = "";
	    
	    stringstream ss;
	    if (comma != string::npos) {
	      // Two positions specified
	      
	      ss << input.substr(0, comma);
	      ss >> pos1;
	      
	      ss.clear();
	      ss << input.substr(comma + 1);
	      ss >> pos2;
	      
	      left = input.substr(comma +1);
	      
	      size = 2;
	      
	    } else {
	      
	      ss << input;
	      ss >> pos1;

	      size = 1;
	      
	    }
	    
	  }
	
	
	if (pos2 == -1) 
	  game.knockdown(pos1);
	else 
	  game.knockdown(pos1, pos2);
	
	current = game.getCurrentPosition();
	
	// Print out the peg pile sizes
	for(unsigned int i = 0; i < current.size(); ++i) {
	  if (current[i]) {
	    cout << 'X';
	  } else {
	    cout << '_';
	  }
	}
	cout << endl;
	
	// Print out the peg pile positions
	for(unsigned int i = 0; i < current.size(); ++i) {
	  cout << i;
	}
	cout << endl;
	
	if (game.isWinner(current)) {
	  cout << "You win!" << endl;
	  return 0;
	}
      
	
	// ***********************
	// Computer's turn
	// ***********************
	

	KaylesGame::Position bestOutcome = strategy.getBestMove();
	
	game.executePosition(bestOutcome);
	cout << "Computer moves" << endl;
	
	// Print out the kayles piles
	current = game.getCurrentPosition();
	
	// Print out the peg pile sizes
	for(unsigned int i = 0; i < current.size(); ++i) {
	  if (current[i]) {
	    cout << 'X';
	  } else {
	    cout << '_';
	  }
	}
	cout << endl;
      
	// Print out the peg pile positions
	for(unsigned int i = 0; i < current.size(); ++i) {
	  cout << i;
	}
	cout << endl;
	
	if (game.isWinner(game.getCurrentPosition())) {
	  cout << "The computer wins!" << endl;
	  return 0;
	}
	
      }
      
      cout << "Draw!" << endl;
      
    } else {
      
      if(game.generatePositions().size() != 0) {
	cout << "Best possible move: " 
	     << game.mapString(strategy.getBestMove()) << endl;
      } else {
	cout << "No moves possible." << endl;
      }
    }

  } catch (GameException ex) {
    cerr << ex.message() << endl;
    return -1;
  } catch (...) {
    cerr << "Unexpected error has occured." << endl;
    return -1;
  }
  
}
