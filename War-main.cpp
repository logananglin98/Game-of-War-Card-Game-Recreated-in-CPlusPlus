/**
  Author: Logan Anglin
 */

#include <iostream> 
#include <algorithm>    // has shuffle
#include <vector> 
#include <stack>
#include <queue>
#include <random>
#include <chrono>

using namespace std;


class GetRandom {
	/** Uses <random> from C++11 to return a random integer in range [1..size] */
public:
	GetRandom(int size) {
		random_device rd; // declares a random_device object that need to generate a random number.
		mt19937 gen(rd()); //mt19937 is an efficient pseudo-random number generator using the Mersenne twister algorithm.
		uniform_int_distribution<int> intdist(1, size); //create a uniform distribution object to turn the pseudorandom result into a random digit between 1 and size.
		self_rand_int_ = intdist(gen); //generates the random number.
	}
	int roll() {
		return self_rand_int_;
	}
private:
	int self_rand_int_;
}; // end of GetRandom

class War {
public:
	War() {
		// This code makes the 5 decks of cards that are in order
		newdecks.reserve(125);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				newdecks.push_back(j);
			}
		}
		// This code gets a time-based seed for randomness
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		//The following code shuffles
		shuffle(newdecks.begin(), newdecks.end(), std::default_random_engine(seed));
	}
	void add_dealingPile() {
		/**Moves cards from newdeck to dealing pile after the newdeck has been sorted.*/
		for (int i = 0; i < newdecks.size(); i++) {
			dealingPile.push(newdecks[i]);
		}
	}
	void deal() {
		/**
		Distributes the cards evenly into both the player's deck and the opponent's deck, alternating
		as the cards are distributed.
		*/
		initialSize = dealingPile.size();
		for (int i = 0; i < initialSize; i++) {
			if (i % 2 == 0) {
				myPlayingPile.push(dealingPile.top());
				dealingPile.pop();
			}
			else {
				otherPlayingPile.push(dealingPile.top());
				dealingPile.pop();
			}
		}
	}

	void declare_war() {
		/**
		This method is called when both the player and the opponent draw a card of equal value. They both
		place those cards in the loot pile, and place an additional card on the loot pile from the top of
		their playing pile stacks. They then both draw another card. If the cards are the same, the process
		is repeated. If the cards are different, the player with the larger card places the entire loot pile
		on their storage pile, and the game continues as normal.
		*/
		check_piles();

		// These two if statements prevent the program from trying to manipulate empty stacks.
		if (!myPlayingPile.empty() && !otherPlayingPile.empty()) {

			// Moving drawn cards of equality and the topmost cards of both playing piles into the loot pile.
			lootPile.push(myCurrent);
			lootPile.push(otherCurrent);
			lootPile.push(myPlayingPile.top());
			myPlayingPile.pop();
			lootPile.push(otherPlayingPile.top());
			otherPlayingPile.pop();
		}

		check_piles();

		// These two if statements prevent the program from trying to manipulate empty stacks.
		if (!myPlayingPile.empty() && !otherPlayingPile.empty()) {

			// Drawing cards in each round of a war.
			draw_cards();

			if (myCurrent > otherCurrent) {
				// placing loot pile in player's storage pile.
				cout << "You won this round! The loot pile goes to you!" << endl;
				myStoragePile.push(myCurrent);
				myStoragePile.push(otherCurrent);
				initialSize = lootPile.size();
				for (int i = 0; i < initialSize; i++) {
					myStoragePile.push(lootPile.front());
					lootPile.pop();
				}
			}
			else if (myCurrent < otherCurrent) {
				// placing loot pile in opponents's storage pile.
				cout << "Your opponent won this round. The loot pile goes to your opponent." << endl;
				otherStoragePile.push(myCurrent);
				otherStoragePile.push(otherCurrent);
				initialSize = lootPile.size();
				for (int i = 0; i < initialSize; i++) {
					otherStoragePile.push(lootPile.front());
					lootPile.pop();
				}
			}
			else {
				// Recurses until the cards are of differing values or a player runs out of cards.
				cout << "The war continues..." << endl;
				declare_war();
			}
		}
	}

	void check_piles() {
		/**
		This method checks if either of the players are out of cards and moves their storage piles to their
		playing piles if their playing pile stack is empty.
		*/
		if (myPlayingPile.empty() && myStoragePile.empty()) {
			continueGame = false;
		}
		else if (myPlayingPile.empty()) {
			initialSize = myStoragePile.size();
			for (int i = 0; i < initialSize; i++) {
				myPlayingPile.push(myStoragePile.front());
				myStoragePile.pop();
			}
		}
		if (otherPlayingPile.empty() && otherStoragePile.empty()) {
			continueGame = false;
		}
		else if (otherPlayingPile.empty()) {
			initialSize = otherStoragePile.size();
			for (int i = 0; i < initialSize; i++) {
				otherPlayingPile.push(otherStoragePile.front());
				otherStoragePile.pop();
			}
		}
	}

	void display_winner() {
		/**Informs the player who won once the game has finished.*/
		if (myCardCount > 1 && otherCardCount > 1) {
			cout << "Round limit reached." << endl;
			cout << endl;
		}
		if (myCardCount > otherCardCount) {
			cout << "You have won! Congratulations!" << endl;
		}
		else {
			cout << "Your opponent has won. Better luck next time!" << endl;
		}
	}

	void check_sizes() {
		/**
		This method calculates displays the combined card count of each player's playing and storage stacks each round. The
		calculations are used to determine a winner in the display_winner method once the game ends.
		*/
		myCardCount = myPlayingPile.size() + myStoragePile.size();
		otherCardCount = otherPlayingPile.size() + otherStoragePile.size();
		cout << "Player card count: " << myCardCount << endl;
		cout << "Opponent card count: " << otherCardCount << endl;
	}

	void game_run_method() {
		/**
		The following code gives the user an option to have the progam run continuously or to press enter to progress to
		each round.
		*/
		cout << "Would you like the program to run in a continuous loop until a winner is declared," << endl;
		cout << "or would you like to have the program pause each turn?" << endl;
		cout << "Type y for continuous playing, n to pause each turn: " << endl;
		cin >> runGameContinuously;
	}

	void draw_cards() {
		/**Used to draw cards from the playing pile each turn.*/
		myCurrent = myPlayingPile.top();
		myPlayingPile.pop();
		otherCurrent = otherPlayingPile.top();
		otherPlayingPile.pop();

		cout << "The card you drew: " << myCurrent << endl;
		cout << "The card your apponent drew: " << otherCurrent << endl;
	}

	void run_game() {
		/**This chunk of code controls the execution of the game. A while loop runs while each player still
		has cards and the gameCounter is less than 100.*/

		game_run_method();

		while (continueGame && (gameCounter < 1000)) {

			// Placed several places throughout the program basically any time a card is drawn or a stack is
			// moved so there are no errors caused from trying to manipulate empty stacks or queues.
			check_piles();

			//Where the cards are drawn each turn.
			draw_cards();

			// Checking which player won, or if a war is necessary.
			if (myCurrent > otherCurrent) {
				cout << "You won this round! Both cards go to you!" << endl;
				myStoragePile.push(myCurrent);
				myStoragePile.push(otherCurrent);
			}
			else if (myCurrent < otherCurrent) {
				cout << "Your opponent won this round. Both cards go to your opponent." << endl;
				otherStoragePile.push(myCurrent);
				otherStoragePile.push(otherCurrent);
			}
			else {
				cout << "A war has been initiated." << endl;
				declare_war();
			}

			cout << endl;
			check_piles();

			// Used only if the player wants to pause the game after each round.
			if (runGameContinuously != 'y') {
				cout << "Press enter to continue..." << endl;
				cin.get();
			}
			gameCounter++;
			check_sizes();
		}
		display_winner();
	}

private:
	vector<int> newdecks; //This is the ONLY vector you are allowed to use

	/* For each set of piles (except possibly the dealing pile as described),
	you are required to use stacks, queues, and deques data structures appropriately,
	you may NOT use vectors for these, and you must use each data structures correctly.
	i.e. you MAY NOT iterate through any of the other data structures.
	You may use ONLY 1 vector, and that is for your new cards because the vector class
	has a shuffle feature which you will see in this starter code.
	This single vector may be used for your dealing pile or you can choose to use a stack,
	queue or deque for the dealing pile.*/

	stack<int> dealingPile;
	stack<int> myPlayingPile;
	stack<int> otherPlayingPile;
	queue<int> myStoragePile;
	queue<int> otherStoragePile;
	queue<int> lootPile;

	int myCurrent;
	int otherCurrent;

	// These variables are for declaring a winner at the end of the game in the display_winner method.
	int myCardCount;
	int otherCardCount;

	// Will be set to false when the player or opponent runs out of cards.
	bool continueGame = true;

	// For recording the initial size of each pile so for loops can increment the correct amount of times.
	int initialSize;

	// I had originally created this to make testing easier, but it's also a handy option for an end user. This allows 
	// the user to run the game continuously or to pause the game each round. Controlled with game_run_method.
	char runGameContinuously;

	// Used to create a finite amount of rounds considering how long this program can theoretically run.
	int gameCounter = 0;

}; //a semi colon must end every C++ class declaration.

//---------------------------------------------------------------------
// main begins here

int main() {
	char stopme;

	War game;

	game.add_dealingPile();
	game.deal();
	game.run_game();

	cin >> stopme; //holds open the window in some cases
	return 0;
}



