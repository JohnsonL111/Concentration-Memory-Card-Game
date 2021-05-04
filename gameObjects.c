#include "gameObjects.h"
/*
 A function that initializes all the fields in theDeck struct.
 input: address of Deck var
        a cString
 output: N/A
 Special situation: N/A
*/
void initializeDeck(Deck *theDeck, char* brandName) {
    // initialize brand field
    theDeck -> brand = brandName;

    /* host of vars used to initialize deck. In order of appearence they:
    (1) positionIdx: used to properly index the deck 
    (2) initFlag: 0: still initializing, 1: when done initializing deck
    (3) suitInit: int used to initialize the suits correctly (range from 0 to 4)
    (4) valueArr: array of possible values for the cards */
    int positionIdx = 0;
    int initFlag =  0;
    int suitInit = 0;
    char valueArr[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};

    // loop through deck until we've initialized each card properly
    while (initFlag == 0) {
        
        // initialize 1/4 of cards (i.e. values/suits) at a time 
        for (int i = 0; i < NUM_OF_CARDS_IN_DECK/4; i++) {
            
            /* initialize value of cards. Use var i in loop to index
            valueArr for the correct value */
            theDeck -> cards[positionIdx].value = valueArr[i];

            /* initialize suits of cards. suitInit corresponds to the enum
            field. e.g. suitInit = 0 is same as first field in enum aka spades*/
            if (suitInit == 0)
                theDeck -> cards[positionIdx].suit = Spades;

            else if (suitInit == 1)
                theDeck -> cards[positionIdx].suit = Hearts;

            else if (suitInit == 2)
                theDeck -> cards[positionIdx].suit = Clubs;
            
            else
                theDeck -> cards[positionIdx].suit = Diamonds;
            
            // always accumuluate positionIdx after setting value/suit of a card.
            positionIdx += 1;       
        }

        /* after initializing 1/4 of deck than increment suitInit so your suits are
        initialized correctly */
        suitInit += 1;

        // condition check for full deck initialized
        if (positionIdx == NUM_OF_CARDS_IN_DECK)
            initFlag = 1;      
    }   
}  


/*
 A function that shuffles the decks contents.
 input: address of deckVar
 output: N/A
 Special situation: N/A
 Note: Used https://stackoverflow.com/questions/6127503/shuffle-array-in-c
 (aka Victors link in the assignment pdf) for assisstance in the implementation.
*/
void shuffleDeck(Deck* theDeck) {
   
    if (NUM_OF_CARDS_IN_DECK > 1) {

        // loop through deck, select a random idx and swap with fields at current idx
        for (size_t i = 0; i < NUM_OF_CARDS_IN_DECK-1; i++) {
            
            // select random index
            size_t randIdx = i + rand() / (RAND_MAX / (NUM_OF_CARDS_IN_DECK - i) + 1);

            // swap values between the value at randIdx and the one at idx i.
            char tempValue = theDeck -> cards[randIdx].value;
            theDeck -> cards[randIdx].value = theDeck -> cards[i].value;
            theDeck -> cards[i].value = tempValue; 

            // swap suits between the suit at randIdx and the one at idx i.
            int tempSuit = theDeck -> cards[randIdx].suit;
            theDeck -> cards[randIdx].suit = theDeck -> cards[i].suit;
            theDeck -> cards[i].suit = tempSuit;      
        }
    }
}      
        
        
/*
 A function that prints the deck contents and the row/column indexes.
 input: pointer to Deck var (constant)
 output: N/A
 Special situation: N/A
*/
void printDeck(const Deck* theDeck, bool faceUp) {
    
    // prints the column idxs
    for (int i = 97; i < 110; i++) {
        if (i == 97) {
            printf("  ");
        }
        printf(" %c ", i);
        if (i == 109) {
            puts("");
        }
    }
    
   
    /* Purpose of the four variables defined below:
       (1) suitUniCArr used to hold unicode for each suit
       (2) Proper unicode (taken from suitUniCArr) will be assigned to suitUniC
       (3) rowIdx is an array to hold row indexes
       (4) int to be used for indexing said array */
    char* suitUniCArr[4] = {"\u2660", "\u2661", "\u2663", "\u2662"};
    char* suitUniC; 
    int rowIdx[] = {1, 2, 3};
    int idxForRowIdx = 0;

    // hard code the first row idx
    printf("0 ");

    //loops through deck and prints content of one card at a time
    for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i++) {
        
        // skip to printing next card if current card is already won (value = '0')
        if (theDeck -> cards[i].value == '0') {
            printf("   ");
        } 

        // print cards faceup
        else if (faceUp == true) {

            // assigns proper unicode to suitUniC
            for (int j = 0; j < 4; j++) {
                if (theDeck -> cards[i].suit == j) {
                    suitUniC = suitUniCArr[j];
                }
            }

            // print contents of card 0 to card 12 (row 1)
            if (i >= 0 && i <= 12) {
                printf("%c%s ", theDeck -> cards[i].value, suitUniC);
            }
            
            // print contents of card 13 to card 25 (row 2)
            if (i >= 13 && i <= 25) {
                printf("%c%s ", theDeck -> cards[i].value, suitUniC);
            }

            // print contents of card 26 to card 38 (row 3)
            if (i >= 26 && i <= 38) {
                printf("%c%s ", theDeck -> cards[i].value, suitUniC);
            }

            // print contents of card 39 to card 51 (row 4)
            if (i >= 39 && i <= 51) {
                printf("%c%s ", theDeck -> cards[i].value, suitUniC);
            }
        }

        // else print each card facedown
        else if (faceUp == false) {
            printf("%c\u218C ", '?');
        }

        // if at end of row then go to next row and print apt row idx
        if ((i+1) % 13 == 0 && i != 51) {
            printf("\n%d ", rowIdx[idxForRowIdx]);
            idxForRowIdx += 1;
        }     
    }
    puts("\n"); 
}


/*
 A function that initializes all the fields of a Player.
 input: pointer to player struct
        name of player as a string
 output: N/A
 Special situation: N/A
*/
void initializePlayer(Player* thePlayer, char* theName) {

    // initializes all fields of a player
    thePlayer -> name = theName;
    thePlayer -> cardsWon = 0;
    thePlayer -> winPile.head = NULL;
    thePlayer -> winPile.tail = NULL;
    return;

} 

/*
 A function clears the winning pile of the player by calling the necessary
 function on a Card_LList.
 input: pointer to player struct
 output: N/A
 Special situation: N/A
*/
void clearPlayer(Player* thePlayer) {

    //goes to the players winPile linked list and frees all its contents
    Card_LList winningPile = thePlayer -> winPile;
    clearCard_LList(&winningPile);
}