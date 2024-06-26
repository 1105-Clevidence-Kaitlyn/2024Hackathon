#include "hand.h"

Hand::Hand(){
    firstCard = nullptr;
    lastCard = nullptr;
    numCardsInHand = 0; 
}

Hand::Hand(Card* f, Card* l, int n){
    numCardsInHand = n;
    if(f == nullptr){
        firstCard = lastCard = nullptr;
        return;
    }
    Card* temp = f;
    firstCard = lastCard = new Card(*temp);
    firstCard->setValue(temp->getValue());
    firstCard->setNextCard(nullptr);

    temp = temp->getNextCard();
    while(temp != nullptr){
        lastCard->setNextCard(new Card(*temp));
        lastCard = lastCard->getNextCard();
        lastCard->setValue(temp->getValue());
        lastCard->setNextCard(nullptr);
        temp = temp->getNextCard();
    }
}
Hand::Hand(const Hand& rhs){
    numCardsInHand = rhs.numCardsInHand;
    if(rhs.firstCard == nullptr){
        firstCard = lastCard = nullptr;
        return;
    }else{
        Card* temp = rhs.firstCard;
        firstCard = lastCard = new Card(*temp);
        firstCard->setValue(temp->getValue());
        firstCard->setNextCard(nullptr);

        temp = temp->getNextCard();
        while(temp != nullptr){
            lastCard->setNextCard(new Card(*temp));
            lastCard = lastCard->getNextCard();
            lastCard->setValue(temp->getValue());
            lastCard->setNextCard(nullptr);
            temp = temp->getNextCard();
        }
    }
}

Card* Hand::getFirstCard() const{
    return firstCard;
}
Card* Hand::getLastCard() const{
    return lastCard;
}
int Hand::getNumCardsInHand() const{
    return numCardsInHand;
}

void Hand::setFirstCard(Card* f){
    firstCard = f;
}
void Hand::setLastCard(Card* l){
    lastCard = l; 
}

void Hand::addCardToHand(Card c){
    Card* temp = new Card(c);
    if(firstCard == nullptr){
        firstCard = lastCard = temp;
    }
    else{
        lastCard->setNextCard(temp);
        lastCard = temp;
    }
    lastCard->setNextCard(nullptr);
    numCardsInHand++;
}

Card* Hand::getCardptrAtIndex(int i){
    Card* temp = firstCard;
    int count = 0;
    while(temp!= nullptr && count <i){
        temp = temp->getNextCard();
        count++;
    }
    if(temp == nullptr){
        cout<<":("<<endl; 
    }
    return temp;
}
Card& Hand::getCardAtIndex(int i){
    Card* temp = firstCard;
    int count = 0;
    while(temp!= nullptr && count <i){
        temp = temp->getNextCard();
        count++;
    }
    if(temp == nullptr){
        cout<<":("<<endl; 
    }
    return *temp;
}

void Hand::deleteCardFromHand(int i){ 
    if(i < 0 || i>= numCardsInHand){
        cout<<"Index out of bounds"<<endl;
    }
    if(i == 0){
        if(firstCard->getNextCard() == nullptr){
            delete firstCard;
            firstCard = lastCard = nullptr;
        }
        else{
            Card* temp = firstCard;
            firstCard = firstCard->getNextCard();
            delete temp;
        }
    }
    else{
        Card& oneBefore = getCardAtIndex(i-1);
        Card* remove = oneBefore.getNextCard();
        oneBefore.setNextCard(remove->getNextCard());
        delete remove;
        if(i == numCardsInHand -1){
            lastCard = &oneBefore;
        }
    }
    numCardsInHand--;
}

Hand::~Hand(){
    Card * temp = firstCard;
    while(temp!=nullptr){
        Card* remove = temp;
        temp = temp->getNextCard();
        delete remove;
    }
    firstCard = lastCard = nullptr;
}

Hand Hand::operator=(const Hand& rhs){
    numCardsInHand =rhs.numCardsInHand;
    if(rhs.firstCard == nullptr){
        firstCard = lastCard = nullptr;
    }else{
    Card* temp = rhs.firstCard;
    firstCard = lastCard = new Card(*temp);
    firstCard->setValue(temp->getValue());
    firstCard->setNextCard(nullptr);

    temp = temp->getNextCard();
    while(temp != nullptr){
        lastCard->setNextCard(new Card(*temp));
        lastCard = lastCard->getNextCard();
        lastCard->setValue(temp->getValue());
        lastCard->setNextCard(nullptr);
        temp = temp->getNextCard();
    }
    }
    return *this; 
}
