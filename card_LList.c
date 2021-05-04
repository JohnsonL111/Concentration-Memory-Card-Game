#include "card_LList.h"

/*
 A function that creates a new Card_LList, which is an empty linked list.
 input: N/A
 output: empty linked list (empty LL)
 Special situation: N/A
*/
Card_LList* createCard_LList() {

	// allocate on heap for LL (linked list) & exit(0) on failure
	Card_LList* cardList = malloc(sizeof(Card_LList));
	if (cardList == NULL) {
		exit(0);
	}

	// initialize both had/tail to NULL
	cardList -> head = NULL;
	cardList -> tail = NULL;

	// return the LL 
	return cardList;
}

/*
 A function that removes all the nodes from the list one by one. Result is an empty LL
 input: pointer to the LL
 output: empty linked list (empty LL)
 Special situation: N/A
*/
void clearCard_LList(Card_LList* theList) {
    
    // traverse and free each node in the LL until it is empty
    while (!isEmptyCard_LList(theList)) { 
    	removeEndCard_LList(theList); 
    } 

	return;
}

/*
 A function that checks if the list is empty. If it is empty, return true; 
 otherwise return false.
 input: pointer to a LL
 output: boolean result
 Special situation: N/A
*/
bool isEmptyCard_LList(Card_LList* theList) {

	// if head is null then the LL is empty; return true
	if (theList -> head == NULL) {
		return true;
	}

	// else the LL is non-empty; return false
	return false;
}

/*
 A function that inserts the card to the front of the LL as a part of a node (the node itself 
 doesn't store the card, but the address of the card). This method encapsulates the inner 
 workings of the linked list and there is no need to duplicate the card.
 input: pointer to the LL
 		pointer to the Card to insert
 output: N/A
 Special situation: N/A
*/
void insertFrontCard_LList(Card_LList* theList, Card* theCard) {
	
	// create node, check for malloc failure, and initialize node's fields
	Card_Node* currentNode = malloc(sizeof(Card_Node));
	if (currentNode == NULL) {
		exit(0);
	}

	currentNode -> card = theCard;

	// Insert node into LL: Empty LL case
	if (theList -> head == NULL) {
		currentNode -> next = NULL;
		theList -> head = currentNode;
		theList -> tail = currentNode;
	}

	// Insert node into LL: Non-empty LL case
	// (1) update the next of currentNode to old head pointee (2) update head pointee 
	else {
		currentNode -> next = theList -> head;
		theList -> head = currentNode;
	}
	
	return;
}


/*
 A function that inserts the card to the end of the LL as a part of a node (the node itself 
 doesn't store the card, but the address of the card). This method encapsulates the inner 
 workings of the linked list and there is no need to duplicate the card.
 input: pointer to the LL
 		pointer to the Card to insert
 output: N/A
 Special situation: N/A
*/
void insertEndCard_LList(Card_LList* theList, Card* theCard) {

	// create node and check for malloc failure 
	Card_Node* currentNode = malloc(sizeof(Card_Node));
	if (currentNode == NULL) {
		exit(0);
	}

	//initialize node's fields
	currentNode -> card = theCard;
	currentNode -> next = NULL;	

	// Insert node into LL: Empty Card_LList case
	if (theList -> head == NULL) {
		theList -> head = currentNode;
		theList -> tail = currentNode;

	}
	// Insert node into LL: Non-empty Card_LList case
	// (1) update next of old tail pointee to currentNode (2) update tail pointee to currentNode
	else {
		theList -> tail -> next = currentNode;
		theList -> tail = currentNode;
	}

	return;
}


/*
 A function that returns the address of the card of the first node.
 This method encapsulates the inner workings of the linked list and there
 is no need to duplicate the card. Freeing of the node memory is done here. 
 input: pointer to the LL
 output: Card to be returned
 Special situation: N/A
*/
Card* removeFrontCard_LList(Card_LList* theList) {

	// empty LL case
	if (theList -> head == NULL) {
		return NULL;
	}

	// LL with one node case
	else if (theList -> head == theList -> tail) {

		// set pointer to the card to return
		Card* tempCard = theList -> head -> card;

		//free the head node and set head/tail to NULL
		free(theList -> head);
		theList -> head = NULL;
		theList -> tail = NULL;
		
		// return the Front card
		return tempCard;
	}

	// LL with more than one node case
	else {

		// set a pointer to the card to return and to the node containing said card
		Card* tempHeadCard = theList -> head -> card;
		Card_Node* tempHeadNode = theList -> head;

		// update head
		theList -> head = theList -> head -> next;

		// disconnect the link with node to remove, free it, and set to NULL
		tempHeadNode -> next = NULL;
		free(tempHeadNode);
		tempHeadNode = NULL;

		// return the Front card
		return tempHeadCard;
	}

	
}

/*
 A function that returns the address of the card of the last node.
 This method encapsulates the inner workings of the linked list and there
 is no need to duplicate the card. Freeing of the node memory is done here. 
 input: pointer to the LL
 output: Card to be returned
 Special situation: N/A
*/
Card* removeEndCard_LList(Card_LList* theList) {
	
	// empty LL case
	if (theList -> head == NULL) {
		return NULL;
	}

	// LL with one node case
	else if (theList -> head == theList -> tail) {

		// set pointer to the card to return
		Card* tempCard = theList -> head -> card;

		//free the head node and set head/tail to NULL
		free(theList -> head);
		theList -> head = NULL;
		theList -> tail = NULL;

		// return the End card 
		return tempCard;
	}

	// LL with more than one node
	else {

		// set a pointer to the card to return, the node containing it, and to the head node
		Card* tempTailCard= theList -> tail -> card;
		Card_Node* tempTailNode = theList -> tail;
		Card_Node* tempHeadNode = theList -> head;

		// traverse LL and update tempHeadNode until it points to the last node in the LL
		while(tempHeadNode -> next != tempTailNode) {
			tempHeadNode = tempHeadNode -> next;
		}

		// make tempheadNode the new last node
		tempHeadNode -> next = NULL;
		theList -> tail = tempHeadNode;

		// free the old tail node 
		free(tempTailNode);
		tempTailNode = NULL;

		// return the End card
		return tempTailCard;
	}
	
} 