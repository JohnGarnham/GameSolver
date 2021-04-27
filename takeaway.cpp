/*
 * takeaway.cpp
 *
 * Main program for takeaway game
 *
 * @version: $Id: takeaway.cpp,v 1.7 2006/11/10 22:49:55 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: takeaway.cpp,v $
 *     Revision 1.7  2006/11/10 22:49:55  jeg3600
 *     *** empty log message ***
 *
 *     Revision 1.6  2006/11/09 05:28:23  jeg3600
 *     Fixed errors
 *
 *     Revision 1.5  2006/10/30 01:04:16  jeg3600
 *     Updated
 *
 *     Revision 1.4  2006/10/13 10:40:21  jeg3600
 *     Works!
 *
 *     Revision 1.3  2006/10/12 19:52:38  jeg3600
 *     Milestone 1 Submission
 *
 *     Revision 1.2  2006/26/09 03:39:07  jeg3600
 *     Added Strategy
 *
 *     Revision 1.1  2006/23/09 08:03:15  jeg3600
 *     Initial revision
 *
 */

#include <iostream>
#include "PennyPile.h"
#include "Strategy.h"

using namespace std;

int main(int argc, char* argv[]) {

  //typedef unsigned int Position;

  int num = -1;
  bool play_mode = false;

  // Grab and validate command line arguments
  if (argc != 2 && argc != 3) {

    cerr << "Usage: takeaway [play] numberOfPennies" << endl;
    return -1;

  } else {

    if (strcmp(argv[1],"play") == 0) {
      play_mode = true;
      if (argc != 3) {
	cerr << "Usage: takeaway [play] numberOfPennies" << endl;
	return -1;
      }
      stringstream ss;
      ss << argv[2];
      ss >> num;
    } else if (argc == 2) {
      stringstream ss;
      ss << argv[1];
      ss >> num;
    } else {
      cerr << "Usage: takeaway [play] numberOfPennies" << endl;
      return -1;
    }

    // Check for a valid amount of pennies in the pile
    if (num < 0) {
      cerr << "Invalid amount of pennies." << endl;
      return -1;
    }

  }
  
  try {

    // Create game and strategy for the game
    PennyPile game(num);
    Strategy<PennyPile::Position, PennyPile> strategy(game);
    
    if (play_mode) {
      
      cout << game.getCurrentPosition() << " pennies left." << endl;
      
      while( !game.isLoser(game.getCurrentPosition()) ) {
	
	// *******************
	// Player's turn
	// *******************
	
	int num = -1;
	string input = "";
	stringstream ss;
	cout << "How many pennies would you like to take away (1-3)? ";
	cin >> input; 
	ss << input;
	ss >> num;
	
	while (num < 1 || (unsigned) num > game.getCurrentPosition() || num > 3) {
	  num = -1;
	  input = "";
	  stringstream ss;
	  cout << "Invalid amount." << endl;
	  cout << "How many pennies would you like to take away (1-3)? ";
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
	if (game.isLoser(game.getCurrentPosition())) {
	  cout << "The computer wins!" << endl;
	  return 0;
	}
	
	// ***********************
	// Computer's turn
	// ***********************
	
	// The computer executes his turn

	// Use the strategy class to choose the best move
	PennyPile::Position bestOutcome = strategy.getBestMove();
	
	// Execute the move

	cout << "Computer takes " << game.getCurrentPosition() - bestOutcome 
	     << " pennies away." << endl;
	
	game.executePosition(bestOutcome);
	
	cout << game.getCurrentPosition() << " pennies left." << endl;

	// Check if the computer has taken the last piece
	// If so, the player wins
	if (game.isLoser(game.getCurrentPosition())) {
	  cout << "The player wins!" << endl;
	  return 0;
	}
	
      }
      
      cout << "Draw!" << endl;
      
    } else {
      
      if(game.generatePositions().size() != 0) {
	cout << "Take away " 
	     << game.getCurrentPosition() - strategy.getBestMove() 
	     << " pennies. " << endl;
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
