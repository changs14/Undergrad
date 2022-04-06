/* Name: Stephaney Chang, 2001508290, CS 202 Assignment 6
 * Description: Header file for player.cpp containing data
 * related to individual player's deck of cards
 */

#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif

#ifndef IO_H
#define IO_H
#include <iostream>
#endif

#ifndef RAND_H
#define RAND_H
#include <stdlib.h> 
#include <time.h>
#endif

using namespace std;

class Player{
private:
    Deck Hand, Foot;
public:
    Player();
    Player(const Deck &DealtHand);
    Card TurnCardOver();
    void ClaimCard(Card card);
    void ShowSortedCards() const;
    void CombineCards();
    bool HasHand() const;
    bool HasFoot() const;
    void SwapHandAndFoot();
    int GetHandSize() const;
};