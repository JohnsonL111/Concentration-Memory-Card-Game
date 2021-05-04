#include "gameFunctions.h"


/*
 A function that adds the card to the player's winning pile by calling
 the appropriate function from card_LList and update the cards won.
 Also marks the card as taken ('0').
 input: pointer to player struct
 		pointer to a card to be added to a player
 output: N/A
 Special situation: N/A
*/
void addCardToPlayer(Player* thePlayer, Card* theCard) {

	// insert card to the end of the players winPile
	insertEndCard_LList(&thePlayer -> winPile, theCard);

	// marks the value of the card taken to '0'
	theCard -> value = '0';
	return;
}

/*
 A function that checks if the user choice is valid:
 if any of the choices are invalid, report that and return false.
 input: pointer to Deck struct 
 		pointer to Playe struct
 		a row idx as a char type
 		a col idx as a col type
 output: a boolean value.
 Special situation: N/A
*/
bool checkPlayerInput(Deck* theDeck, Player* thePlayer, char row, char col) {

	// checks if row was a valid choice to begin wtih
	if (row != '0' && row != '1' && row != '2' && row != '3') {
		return false;
	}

	// checks if col was a valid choice to begin with 
	// initialize  a flag var called "validColIdx" to keep track if a valid col is found
	// loop through valid cols and change flag to true if the cols match
	bool validColIdx = false;
	char colArr[13] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i','j', 'k', 'l', 'm'};
	for (int i = 0; i < 13; i++) {
		if (colArr[i] == col) {
			validColIdx = true;
		}
	}
	if (validColIdx == false) {
		return false;
	}

	// initialize proper rowIdx (subtract by 48 so the rowIx is between 0-4)
	// initialize proper colIdx (subtract by 97 so the colIdx is between 0-12)
	row = row - 48;
	col = col - 97;
	

	// initialize the idx of the card; idx = column idx + (row idx * width)
	// check if the card has been picked already (value == '0')
	int idx = col + (row * 13);
	if (theDeck -> cards[idx]. value == '0') {
		return false;
	}

	// valid card
	return true;
}

/*
 A function that checks if there is a match:
 if the two choices are the same, report it and return false.
 if there is a match, return true; otherwise, return false.
 input: pointer to Deck struct 
 		pointer to Playe struct
 		a row idx as a char type x2 
 		a col idx as a col type x2
 output: a boolean value.
 Special situation: N/A
*/
bool checkForMatch(Deck* theDeck, Player* thePlayer, char r1, char c1, char r2, char c2) {

	// checks if both choices are the same (invalid)
	if (r1 == r2 && c1 == c2) {
		puts("Error: Both cards are the same.");
		return false;
	}
	
	// initialize proper col idxs for both cards (subtract by 97 so the colIdx is between 0-12)
	c1 = c1 - 97;
	c2 = c2 - 97;

	// initialize proper row idxs for both cards (subtract by 48 so the rowIdx is betwen 0-3)
	r1 = r1 - 48;
	r2 = r2 - 48;

	// initialize the idx of each card 
	int idx1 = c1 + (r1 * 13);
	int idx2 = c2 + (r2 * 13);

	// initialize the associated cards 
	Card card1 = theDeck -> cards[idx1];
	Card card2 = theDeck -> cards[idx2];

	// checks if both cards are the same
	if (card1.value == card2.value) {
		return true;
	}

	return false;
}

/*
 A function that checks if the game has a winner (all cards in the deck are taken).
 input: pointer to Deck struct 
 output: a boolean value.
 Special situation: N/A
*/
bool checkForWinner(const Deck* theDeck) {

	// loop through deck. If any card does not have value 0, then the deck is not empty.
	for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i++) {
		if (theDeck -> cards[i].value != '0') {
			return false;
		}
	}
	
	return true;
}
