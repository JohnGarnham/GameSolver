/*
 * Main program for connect 3 game
 *
 * @version:  $Id: connect3.cpp,v 1.1 2006/10/29 22:44:22 jeg3600 Exp jeg3600 $
 * @author:  John Garnham
 * Revisions:
 *      $Log: connect3.cpp,v $
 *      Revision 1.1  2006/10/29 22:44:22  jeg3600
 *      Initial revision
 *
 *
 */

#include <iostream>
#include <fstream>
#include "Connect3Game.h"
#include "Strategy.h"

using namespace std;

int main(int argc, char* argv[]) {
  
  typedef vector< int > Row;

  bool play_mode = false;

  string filename = "";
  istream* input_ptr = 0;
  ifstream file;

  if (argc == 2) {

    if(strcmp(argv[1], "-") == 0) {
      input_ptr = &cin;
    } else {
      try {
	file.open(argv[1]);
	if(! file.is_open()) throw "Error opening file!"; 
	input_ptr = &file;
      } catch(...) {
	cerr << "Error opening file!" << endl;
	return -1;
      }
    }

  } else if (argc == 3) {

    if(strcmp(argv[1], "play") == 0) {
      play_mode = true;
    } else {
      cerr << "Usage: connect3 [play] [filename or -]" << endl;
      return -1;
    }

    if (strcmp(argv[2], "-") == 0) {
      input_ptr = &cin;
    } else {
      try {
	file.open(argv[2]);
	if(! file.is_open()) throw "Error opening file!"; 
	input_ptr = &file;
      } catch(...) {
	cerr << "Error opening file!" << endl;
	return -1;
      }
    }

  } else {
    cerr << "Usage: connect3 [play] [filename or -]" << endl;
    return -1;
  }

  if(input_ptr == 0) {
    cerr << "Error: could not open input stream!" << endl;
    return -1;
  }

  // Gather the board information
  istream &input = *input_ptr;
  
  int width = -1, height = -1;
  input >> width >> height;

  Connect3Game::Position initial;

  for(int y = 0; y < height; ++y) {
    Row temp;
    for(int x = 0; x < width; ++x) {
      char next;
      input >> next;
      if(next == '.') {
	temp.push_back(Connect3Game::B);
      } else if (next == 'X') {
	temp.push_back(Connect3Game::X);
      } else if (next == 'O') {
	temp.push_back(Connect3Game::O);
      }
    }
    initial.push_back(temp);
  }

  try {

    Connect3Game game(initial, width, height);
    
    Strategy< Connect3Game::Position, Connect3Game > strategy(game);
    
    if (play_mode) {

      Connect3Game::Position current = game.getCurrentPosition();
      
      // Print current board
      for(int y = 0; y < game.getHeight(); ++y) {
	for(int x = 0; x < game.getWidth(); ++x) {
	  int next = current[y][x];
	  if (next == Connect3Game::B) {
	    cout << ".";
	  } else if (next == Connect3Game::X) {
	    cout << "X";
	  } else if (next == Connect3Game::O) {
	    cout << "O";
	  }
	}
	cout << endl;
      }
      
      for(int i = 0; i < game.getWidth(); ++i) {
	cout << i;
      }
      
      cout << endl;
      
      while(! game.isFinalPosition(game.getCurrentPosition())) {
	
	int column = -1;
	string input = "";
	
	stringstream ss;

	cout << "Where do you want to drop your piece? ";
	cin >> input;
	ss << input;
	ss >> column;
	


	while ( column < 0 || column >= game.getWidth() ||
		current[0][column] != Connect3Game::B) {
	  cout << "Column: " << column << endl;
	  column = -1;
	  input = "";
	  stringstream ss;
	  cout << "Invalid column specified!" << endl;
	  cout << "Where do you want to drop your piece? ";
	  cin >> input;
	  ss << input;
	  ss >> column;
	}

	game.drop(column);

	// Print current board
	current = game.getCurrentPosition();
	for(int y = 0; y < game.getHeight(); ++y) {
	  for(int x = 0; x < game.getWidth(); ++x) {
	    int next = current[y][x];
	    if (next == Connect3Game::B) {
	      cout << ".";
	    } else if (next == Connect3Game::X) {
	      cout << "X";
	    } else if (next == Connect3Game::O) {
	      cout << "O";
	    }
	  }
	  cout << endl;
	}
	
	for(int i = 0; i < game.getWidth(); ++i) {
	  cout << i;
	}
	cout << endl;

	if(game.isFinalPosition(current)) {
	  if(game.isWinner(current)) {
	    cout << "You win!" << endl;
	    return 0;
	  } else {
	    cout << "Draw!" << endl;
	    return 0;
	  }
	}

	game.invertBoard();

	cout << "The computer moves." << endl;
	Connect3Game::Position computer = strategy.getBestMove();
	game.executePosition(computer);

	game.invertBoard();

	// Print current board
	current = game.getCurrentPosition();
	for(int y = 0; y < game.getHeight(); ++y) {
	  for(int x = 0; x < game.getWidth(); ++x) {
	    int next = current[y][x];
	    if (next == Connect3Game::B) {
	      cout << ".";
	    } else if (next == Connect3Game::X) {
	      cout << "X";
	    } else if (next == Connect3Game::O) {
	      cout << "O";
	    }
	  }
	  cout << endl;
	}
	
	for(int i = 0; i < game.getWidth(); ++i) {
	  cout << i;
	}
	cout << endl;

	game.invertBoard();

	if (game.isFinalPosition(game.getCurrentPosition())) {
	  if(game.isWinner(game.getCurrentPosition())) {
	    cout << "The computer wins!" << endl;
	  } else {
	    cout << "Draw!" << endl;
	  }
	}

	game.invertBoard();

      }

    } else {

      // Non-play mode
      
      if(game.isFinalPosition(game.getCurrentPosition())) {

	cout << "Game already decided. No moves possible." << endl;

      } else {

	Connect3Game::Position bestOutcome = strategy.getBestMove();
	
	cout << "Best possible move: " << endl;
	for(int y = 0; y < game.getHeight(); ++y) {
	  for(int x = 0; x < game.getWidth(); ++x) {
	    int next = bestOutcome[y][x];
	    if (next == Connect3Game::B) {
	      cout << ".";
	    } else if (next == Connect3Game::X) {
	      cout << "X";
	    } else if (next == Connect3Game::O) {
	      cout << "O";
	    }
	  }
	  cout << endl;
	}				
	
	cout << endl;
	
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
