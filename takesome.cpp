/*
 * takesome.cpp
 *
 * @version : $Id: takesome.cpp,v 1.3 2006/11/10 23:29:23 jeg3600 Exp $
 * @author:  John Garnham
 *
 * Revisions:
 *      $Log: takesome.cpp,v $
 *      Revision 1.3  2006/11/10 23:29:23  jeg3600
 *      Corrected wins and losers
 *
 *      Revision 1.2  2006/11/10 23:10:34  jeg3600
 *      Added error checking
 *
 *      Revision 1.1  2006/11/09 09:34:58  jeg3600
 *      Initial revision
 *
 *
 */

#include <iostream>
#include "TakeSomeGame.h"
#include "Strategy.h"

using namespace std;

int main(int argc, char* argv[]) {

  int num = -1;
  bool play_mode = false;
  std::vector<TakeSomeGame::Position> valids;
  int start = 0;
  string valid_string;

  // Grab and validate command line arguments
  if (argc < 3) {

    cerr << "Usage: takesome [play] numberOfPennies <list of valid moves>" 
	 << endl;
    return -1;

  } else {

    if (strcmp(argv[1],"play") == 0) {

      if (argc < 4) {
	cerr << "Usage: takesome [play] numberOfPennies <list of valid moves>"
	     << endl;
	return -1;
      }
      play_mode = true;
      stringstream ss;
      ss << argv[2];
      ss >> num;
      start = 3;

    } else {

      stringstream ss;
      ss << argv[1];
      ss >> num;
      start = 2;
    }

    // Check for a valid amount of pennies in the pile
    if (num < 0) {
      cerr << "Invalid amount of pennies." << endl;
      return -1;
    }

    for(int i = start; i < argc; ++i) {
      stringstream ss;
      int move;
      ss << argv[i];
      ss >> move;
      if (move <= 0) {
	cerr << "Invalid valid move listed." << endl;
	return -1;
      }
      valid_string += argv[i];
      valid_string += " ";
      valids.push_back(move);
    }

  }

  // Remove duplicate elements to improve efficiency
  

  try {

    // Create game and strategy for the game
    TakeSomeGame game(num, valids);
    Strategy<TakeSomeGame::Position, TakeSomeGame> strategy(game);
    
    if (play_mode) {
      
      cout << game.getCurrentPosition() << " pennies left." << endl;
      
      while( !game.isFinalPosition(game.getCurrentPosition()) ) {
	
	// *******************
	// Player's turn
	// *******************
	
	int num = -1;
	string input = "";
	stringstream ss;
	cout << "How many pennies would you like to take away "
	     << valid_string << "? ";
	cin >> input;
	ss << input;
	ss >> num;
      
	while (num < 0 || ! game.isValidMove(num) || (unsigned) num > game.getCurrentPosition() ) {
	  num = -1;
	  input = "";
	  stringstream ss;
	  cout << "Invalid amount." << endl;
	  cout << "How many pennies would you like to take away "
	       << valid_string << "? ";
	  cin >> input;
	  ss << input;
	  ss >> num;
	} 
      
	// The player executes his turn
	game.executePosition(game.getCurrentPosition() - num);
	cout << "Player takes " << num << " pennies away." << endl;
	cout << game.getCurrentPosition() << " pennies left." << endl;
	
	// Check if the player has taken the last piece. 
	// If so, the computer wins.
	if (game.isWinner(game.getCurrentPosition())) {
	  cout << "The player wins!" << endl;
	  return 0;
	}
	
	// ***********************
	// Computer's turn
	// ***********************
	
	// The computer executes his turn
	
	// Use the strategy class to choose the best move
	TakeSomeGame::Position bestOutcome = strategy.getBestMove();
	
	// Execute the move
	
	cout << "Computer takes " << game.getCurrentPosition() - bestOutcome 
	     << " pennies away." << endl;
	
	game.executePosition(bestOutcome);
	
	cout << game.getCurrentPosition() << " pennies left." << endl;
	
	// Check if the computer has taken the last piece
	// If so, the player wins
	if (game.isWinner(game.getCurrentPosition())) {
	  cout << "The computer wins!" << endl;
	return 0;
	}
	
      }
      
      cout << "The computer wins!" << endl;
      
    } else {

      if(game.generatePositions().size() != 0) {
	
	TakeSomeGame::Position bestMove  = strategy.getBestMove();
	
	cout << "Take away " << game.getCurrentPosition() - bestMove 
	    << " pennies. " << endl;
	
      } else {
	cout << "No moves possible." << endl;
      }
      
      return 0;

    }

  } catch (GameException ex) {
    cerr << ex.message() << endl;
    return -1;
  } catch (...) {
    cerr << "Unexpected error has occured." << endl;
    return -1;
  }


}
