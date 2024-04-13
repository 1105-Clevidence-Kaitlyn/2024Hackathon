#include <iostream>
using namespace std; 

class Card{
    string value;
    Card* nextCard;

    public:
        Card();
        Card(string);
        Card(const Card&);
        
        void setNextCard(Card*);
        Card* getNextCard();

        void setValue(string);
        string getValue();

        void displayCard(); // calls Oren's graphics 
};