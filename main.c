#include <stdio.h>
#include <stdlib.h> //for the use of system and srand and rand
#include "gameObjects.h"
#include "gameFunctions.h"

#define MAX_CHAR_NUMBER 16 //each input should have at most 15 characters

//a helper function that clears the screen, works for both unix and Windows,
//though behaviour might be different.
//reference: https://stackoverflow.com/questions/2347770/
//            how-do-you-clear-the-console-screen-in-c
void clear() {
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("printf '\33[H\33[2J'");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

int main() {
  //set the random seed to 0, it'll generate the same sequence
  //normally it is srand(time(NULL)) so the seed is different in every run
  //using 0 makes it deterministic so it is easier to mark
  //do not change it
  srand(0);

  //variables to store user input
  char userInput1[MAX_CHAR_NUMBER];
  char userInput2[MAX_CHAR_NUMBER];
  int whereInDeck = 0; //handy for indexing which card based on user input

  
  // dummy code so userInput1/userInput2/whereInDeck do not throw warnings on compilation
  // I did this becasue I didn't use any of the above variables
  if (whereInDeck == 0 || userInput1 == userInput2);

  // this is used to keep of track of the players turn
  // more information in step 5 of code.
  bool playerTracker = true;

  // this is used as a var for flushing stdin. 
  // It will be assigned to getchar() in step 3.1/3.2
  char c;
  
  //set up the players
  Player player1, player2;
  initializePlayer(&player1, "Player 1");
  initializePlayer(&player2, "Player 2");
  Player* currentPlayer = &player1; //this pointer remembers who's turn it is

  //set up the deck: initalize & shuffle
  Deck myDeck;
  initializeDeck(&myDeck, "Bicycle");
  shuffleDeck(&myDeck);

  printDeck(&myDeck, true); //print the shuffled deck, face up
  printf("\n");
  clear(); //clear the screen

  /*
  Implement this part for the game to work.
  It is essentially a do-while loop that repeatedly print the deck,
  ask for user inputs, and do some checking. Ends if someone wins.
  */
  do {
    /////////////////////
    // 1 Round
    ////////////////////
    //Step 1: print the shuffled deck, face down
    printDeck(&myDeck, false);

    //Step 2: print who's turn it is by showing the player's name
    printf("%s's turn\n", currentPlayer -> name);
    
    //Step 3.1 get first input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)
    
    // declare variables used for indexing the deck properly
    // Note: rowIdxInt1/colIdxInt1 are just the int versions of rowIdx1/colIdx;
    bool validCard1 = false;
    char rowIdx1, colIdx1;
    int rowIdxInt1, colIdxInt1, cardIdx1;

    // keep scanning stdin until valid card idx is given
    while (validCard1 == false) {

      // scan for the two idxs
      printf("Pick the first card you want to turn (e.g., 0 a) then press enter: ");
      scanf("%c %c", &rowIdx1, &colIdx1);

      // set proper col idx (subtract by 97 so the colIdx is between 0-12)
      // set proper row idxs (subtract by 48 so the rowIdx is betwen 0-3)
      // set cardIdx1, which will be used to properly idx our deck
      rowIdxInt1 = rowIdx1 - 48;
      colIdxInt1 = colIdx1 - 97;
      cardIdx1 = colIdxInt1 + (rowIdxInt1 * 13);

      // check for errors in card selction 
      if (checkPlayerInput(&myDeck, currentPlayer, rowIdx1, colIdx1) == true) {

        // this exist the loop b/c it means the idxs were valid 
        validCard1 = true; 
      }

      // invalid card: card taken ( value is '0')
      else if (myDeck.cards[cardIdx1].value == '0') {
        puts("Error: the card you picked is already taken");
      }

      // invalid card: either invalid row idxs or invalid col idxs (or both)
      else {
        puts("Error: The card you picked has invalid index(es).");
      }

        // flush stdin for garbage values 
        while((c = getchar()) != '\n' && c != EOF);
    } 

    //Step 3.2: get second input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter) 
    
    // declare variables used for indexing the deck properly
    // Note: rowIdxInt2/colIdxInt2 are just the int versions of rowIdx2/colIdx2
    bool validCard2 = false;
    char rowIdx2, colIdx2;
    int rowIdxInt2, colIdxInt2, cardIdx2;

    // keep scanning stdin until valid card idx is given
    while (validCard2 == false) {

      // scan for the two idxs
      printf("Pick the second card you want to turn (e.g., 1 b) then press enter: ");
      scanf("%c %c", &rowIdx2, &colIdx2); 

      // set proper col idx (subtract by 97 so the colIdx is between 0-12)
      // set proper row idxs (subtract by 48 so the rowIdx is betwen 0-3)
      // cardIdx2 is used to properly idx our deck      
      rowIdxInt2 = rowIdx2 - 48;
      colIdxInt2 = colIdx2 - 97;
      cardIdx2 = colIdxInt2 + (rowIdxInt2 * 13);

      // check for errors in card selction 
      if (checkPlayerInput(&myDeck, currentPlayer, rowIdx2, colIdx2) == true) {
   
        // this exist the loop b/c it means the idxs were valid 
        validCard2 = true; 
      }

      // invalid card: card taken ( value is '0')
      else if (myDeck.cards[cardIdx2].value == '0') {
        puts("Error: the card you picked is already taken");
      }

      // invalid card: either invalid row idxs or invalid col idxs (or both)
      else {
        puts("Error: The card you picked has invalid index(es).");
      }

      // flush stdin for garbage values 
      while((c = getchar()) != '\n' && c != EOF);
    } 

    // At this point we have our two valid cards chosen 
    // assign the proper unicode string to suitUniCard1 & suitUniCard2
    char* suitUniCArr[4] = {"\u2660", "\u2661", "\u2663", "\u2662"};
    char* suitCard1, *suitCard2;
    for (int i = 0; i < 4; i++) {
      if (i == myDeck.cards[cardIdx1].suit) {
        suitCard1 = suitUniCArr[i];
      }

      if (i == myDeck.cards[cardIdx2].suit) {
        suitCard2 = suitUniCArr[i];
      }
    }
    
    // print the selected cards
    printf("\nfirst card picked: %c%s\n", myDeck.cards[cardIdx1].value, suitCard1);
    printf("Second card picked: %c%s\n", myDeck.cards[cardIdx2].value, suitCard2);

    //Step 5: call the checkForMatch function to see if the player has picked
    // a matching pair. If so, print the corresponding message and add the cards
    // to the player's winning pile (Player.winPile).
    // Keep the current player as a match leads to an extra round.
    // Otherwise, print the corresponding message and switch player.

    // initialize flag var anotherTurn that turns true on a matching card pair
    bool anotherTurn = false;

    // pass card idxs to checkForMatch and proccess results accordingly
    bool matchResults = checkForMatch(&myDeck, currentPlayer, rowIdx1, colIdx1, rowIdx2, colIdx2);
    if (matchResults == true) {
      printf("\n%s has found a match! Earns an extra turn.\n", currentPlayer -> name);
      anotherTurn = true;
      currentPlayer -> cardsWon += 2;

      // add cards to the player's winPile
      addCardToPlayer(currentPlayer,&myDeck.cards[cardIdx1]);
      addCardToPlayer(currentPlayer,&myDeck.cards[cardIdx2]);

    }
    // no match found. Player does not gain another turn.
    else {
      printf("\n%s has not found a match.\n", currentPlayer -> name);
    }

     
    // Only swap if "anotherTurn" is false
    // aka if the currentPlayer did NOT get a matching pair.
    if (anotherTurn == false) {

      // playerTracker == true means we just finished p1s turn
      // in that case, swap to p2 (aka playerTracker is now false)
      if (playerTracker == true) {
        currentPlayer = &player2;
        playerTracker = false;
      }

      else {

        // otherwise, we just finishd p2s turn. Time to swap to p1.
        currentPlayer = &player1;
        playerTracker = true;
      }
    }
    
  } while (!checkForWinner(&myDeck));

  //Step 6: find out who won the game and announce the winner
  printf("\n%s has won %d cards.\n", player1.name, player1.cardsWon);
  printf("%s has won %d cards.\n", player2.name, player2.cardsWon);
 
  // its a tie! (26 vs 26 cards won)
  if (player1.cardsWon == player2.cardsWon) {
    puts("It's a tie!");
  }

  // player 1 wins! (p1 > p2 in won cards)
  else if (player1.cardsWon > player2.cardsWon) {
    printf("%s has won!\n", player1.name);
  }

  // player 2 wins! (p1 < p2 in won cards)
  else if (player1.cardsWon < player2.cardsWon) {
    printf("%s has won!\n", player2.name);
  }
   
  //Step 7: clean up player's winning piles
  clearPlayer(&player1);
  clearPlayer(&player2);
  
  // game is complete!
  return 0;
}
