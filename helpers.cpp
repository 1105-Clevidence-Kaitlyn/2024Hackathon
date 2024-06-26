#include "hand.h"
#include <random>
#include <ctime>
#include <iomanip>
string mewo[10000];
int mewwo=0;
bool unoCalled=false;
bool Skip=false;
//randomizing functions
extern string* RANDOIMIZE(string value[],const int a);
extern int* RANDOIMIZE(int value[],const int a);
void RANDOIMIZE(Card* start){
    Card* temp = start;
    int num=0;
    string values[200];
    while(temp!=nullptr){
        values[num]=temp->getValue();
        num++;
        temp=temp->getNextCard();
    }
    RANDOIMIZE(values,num);
    num=0;
    
    while(temp!=nullptr){
        temp->setValue(values[num]);
        num++;
        temp=temp->getNextCard();
    }
    
}
void modifyColor(Card&,int);
void RANDOIMIZE(Hand& target){
    RANDOIMIZE(target.getFirstCard());
};

void drawCard(Hand& current, Hand& available){
    current.addCardToHand(*available.getFirstCard());
    available.deleteCardFromHand(0);
}

void displayPlayerHand(Hand& hand){
    //loop through player cards and display each of them side by side 
    Card* currentCard = hand.getFirstCard();
    int location=0;
    while(currentCard != nullptr){
        currentCard->displayACard(6,location*5+3);
        currentCard = currentCard->getNextCard();
        location++;
    }
    cout<<"\e[m\e[10;1H";
    for(int i = 0; i< hand.getNumCardsInHand(); i++){
        cout<<setw(5);
        cout<<i+1;
    }
    cout<<endl;
}


int wild(Card& datcard){
    //prompt for color 
    char choice;
    do{
        cout<<"What color would you like to pick? (R/B/G/Y) ";
        cin>>choice;
    }while(choice != 'r' && choice != 'R' && choice!= 'b' &&choice != 'B' && choice != 'g' && choice!= 'G' &&choice != 'Y' && choice != 'y');
    if(choice == 'r' || choice == 'R'){
        modifyColor(datcard,0);
        datcard.displayACard(2, 3);
        //blank red card value 
    }
    if(choice == 'b' || choice == 'B'){
        modifyColor(datcard,1);
        datcard.displayACard(2, 3);
        //blank blue card value 
    }
    if(choice == 'g' || choice == 'G'){
        modifyColor(datcard,2);
        datcard.displayACard(2, 3);
        //blank green card value 
    }
    if(choice == 'y' || choice == 'Y'){
        modifyColor(datcard,3);
        datcard.displayACard(2, 3);
        //blank yellow card value 
    }
    //change validation 
    return stoi(datcard.getValue());
}
int skip(int turn){
    Skip=true;
}        
void plus2(Hand& h, Hand& a){
    drawCard(h, a );
    drawCard(h, a);
}
int wildPlusX(Hand& other, Hand& a,Card& datcard,int i){
    for(int j=0;j<i;j++){
    drawCard(other, a);}
    return wild(datcard);
}
void wildComputer(Card& datcard){
    random_device rd;
    mt19937 gen(rd());
    // Define the distribution
    uniform_int_distribution<> dis(1, 4);
    // Generate a random number
    int randomNumber = dis(gen);
            
    if(randomNumber == '1'){
        modifyColor(datcard,0);
        datcard.displayACard(2, 3);
        //blank red card value 
    }
    if(randomNumber == '2'){
        modifyColor(datcard,1);
        datcard.displayACard(2, 3);
        //blank blue card value 
    }
    if(randomNumber == '3'){
        modifyColor(datcard,2);
        datcard.displayACard(2, 3);
        //blank green card value 
    }
    if(randomNumber == '4'){
        modifyColor(datcard,3);
        datcard.displayACard(2, 3);
        //blank yellow card value 
    }
}
void wildPlus4Computer(Hand& opposite, Hand& available,Card& val){
    drawCard(opposite, available);
    drawCard(opposite, available);
    drawCard(opposite, available);
    drawCard(opposite, available);
    wildComputer(val);
}

void shuffleCards(Hand& target){
    RANDOIMIZE(target);
}


int getSecond(int a){
    return a/4;
}
int getSecond(string a){
    return stoi(a)/4;
}

bool validateCard(Card* lastCard, Card* chosenCard){
    //make sure the card is either the number (in value), color (in value), or wild card (is a set of values)
    if(stoi(lastCard->getValue())%4 == stoi(chosenCard->getValue())%4){
        return true;
    }
    else if(stoi(lastCard->getValue())-stoi(lastCard->getValue())%4 == stoi(chosenCard->getValue())-stoi(chosenCard->getValue())%4){
        return true;
    }
    else if(getSecond(stoi(chosenCard->getValue()))==12){
        return true;
    }else if(getSecond(stoi(chosenCard->getValue()) == 14)){
        return true;
    }
    else{
        return false;
    }
}

//specialty cards 
int Overreturn;
int checkSpecialtyCardsPlayer(Card& c, Hand& opposite, Hand& available, int turn){
    Overreturn=stoi(c.getValue());
    if(getSecond(c.getValue()) == 14){
        Overreturn=wildPlusX(opposite, available,c,0);
        return true;
    }
    if(getSecond(c.getValue()) == 13 || getSecond(c.getValue()) == 10){
        skip(turn);
        return true;
    }
    if(getSecond(c.getValue()) == 11){
        plus2(opposite, available);
        skip(turn);
        return true;
    }
    if(getSecond(c.getValue()) == 12){
        Overreturn=wildPlusX(opposite, available,c,4);
        skip(turn);
        return true;
    }
    return false;
}

bool checkSpecialtyCardsComputer(Card& c, Hand& opposite, Hand& available, int turn ){
    if(getSecond(c.getValue()) == 14){
        wildComputer(c);
        return true;
    }
    if(getSecond(c.getValue()) == 13 || getSecond(c.getValue()) == 10){
        skip(turn);
        return true;
    }
    if(getSecond(c.getValue()) == 11){
        plus2(opposite, available);
        skip(turn);
        return true;
    }
    if(getSecond(c.getValue()) == 12){
        wildPlus4Computer(opposite, available,c);
        skip(turn);
        return true;
    }
    return false;
}

void displayChat(){
    for(int i=mewwo-1;i>mewwo-10&&i>-1;i--){
        printf("\e[%d;%ldH",i-mewwo+15,115-mewo[i].length());
        cout<<mewo[i]<<"\e[m";
    }
};
void modifyColor(Card& wild,int newColor){
    wild.setValue(to_string(getSecond(stoi(wild.getValue()))*4+newColor));
}
void playCard(Hand& hand, Hand& discard, int choice, string text){
    int tempValue= stoi(hand.getCardAtIndex(choice - 1).getValue());
    string color;
    if(tempValue%4==0){color="Red";}
    else if((tempValue%4)==1){color="Blue";}
    else if((tempValue%4)==2){color="Green";}
    else if((tempValue%4)==3){color="Yellow";}
    string value;
    
    switch(getSecond(tempValue)){
        case 0:value="0";break;
        case 1:value="1";break;
        case 2:value="2";break;
        case 3:value="3";break;
        case 4:value="4";break;
        case 5:value="5";break;
        case 6:value="6";break;
        case 7:value="7";break;
        case 8:value="8";break;
        case 9:value="9";break;
        case 10:value="Reverse";break;
        case 11:value="+2";break;
        case 12:value="Wild +4";break;
        case 13:value="Skip";break;
        case 14:value="Wild";break;
    }
    mewo[mewwo]=text+color+" "+value;
    mewwo++;
    discard.addCardToHand(hand.getCardAtIndex(choice - 1));
    hand.deleteCardFromHand(choice - 1);
}
void playCard(Hand& hand, Hand& discard, int choice, string text,int OVERRIDE){
    hand.getCardAtIndex(choice-1).setValue(to_string(OVERRIDE));
    int tempValue= stoi(hand.getCardAtIndex(choice - 1).getValue());
    string color;
    if(tempValue%4==0){color="Red";}
    else if((tempValue%4)==1){color="Blue";}
    else if((tempValue%4)==2){color="Green";}
    else if((tempValue%4)==3){color="Yellow";}
    string value;
    
    switch(getSecond(tempValue)){
        case 0:value="0";break;
        case 1:value="1";break;
        case 2:value="2";break;
        case 3:value="3";break;
        case 4:value="4";break;
        case 5:value="5";break;
        case 6:value="6";break;
        case 7:value="7";break;
        case 8:value="8";break;
        case 9:value="9";break;
        case 10:value="Reverse";break;
        case 11:value="+2";break;
        case 12:value="Wild +4";break;
        case 13:value="Skip";break;
        case 14:value="Wild";break;
    }
    mewo[mewwo]=text+color+" "+value;
    mewwo++;
    discard.addCardToHand(hand.getCardAtIndex(choice - 1));
    hand.deleteCardFromHand(choice - 1);
}


void chat(string c){
    mewo[mewwo]=c;
    mewwo++;
}

bool playerTurn(Hand& p, Hand& np, Hand& discard, Hand& available, int turn){
    
if(!Skip){
    Card* temp = p.getFirstCard();
    Card* test = discard.getLastCard();
    unoCalled=false;
    bool playedCard = false, specialty;
    for(int i = 0; i < p.getNumCardsInHand(); i++){
        //update temp as you go 
        if(validateCard(test, temp)){//test if any cards in the hand are valid 
            int choice=-1;
            string dathing;
            displayPlayerHand(p);
            do{
                cout<<endl<<"Which card would you like to play? \e[s";
                displayChat();cout<<"\e[u";
                cin>>dathing;
                if(dathing[0]>=48&&dathing[0]<=57){
                    choice=stoi(dathing);
                }
                if(choice==0){unoCalled=true;chat("Player 1: UNO!!!");}
            }while((choice<1 || choice>p.getNumCardsInHand())||!validateCard(test, p.getCardptrAtIndex(choice-1)));
            Card merp = p.getCardAtIndex(choice-1);
            Card* merpTwo = &merp;
            if(validateCard(test, merpTwo)){
                if(p.getNumCardsInHand()==1){
                    if(unoCalled){
                        
                        checkSpecialtyCardsPlayer(*merpTwo, np, available, turn);
                        playCard(p, discard, choice, "Player 1 played a ",Overreturn);
                    }else{
                        chat("Player 1 failed to say UNO.");
                        drawCard(p,available);
                        drawCard(p,available);
                        drawCard(p,available);
                        drawCard(p,available);
                    }
                }else{
                    if(!unoCalled){
                        checkSpecialtyCardsPlayer(*merpTwo, np, available, turn);
                        playCard(p, discard, choice, "Player 1 played a ",Overreturn);
                    }else{
                        chat("Player 1 said UNO while they had multiple cards.");
                        drawCard(p,available);
                        drawCard(p,available);
                        drawCard(p,available);
                        drawCard(p,available);
                    }
                }
                //playCard(p, discard, choice, "Player 1 played a ");
                //
                playedCard = true;
            }
            if(p.getNumCardsInHand() == 0){
                return true;
            }
            return false;
            break;
        }
        temp = temp->getNextCard();
    }
    
    if(!playedCard){
        drawCard(p, available);
    }
    return false;
}else{
    Skip=false;
}
}

bool computerTurn(Hand& c, Hand& nc, Hand& discard, Hand& available, int turn){
    if(!Skip){
    Card* temp = c.getFirstCard();
    Card* test = discard.getLastCard();
    for(int i = 0; i < c.getNumCardsInHand(); i++){
        if(validateCard(test, temp)){//test if any cards in the hand are valid 
            //random from 1-getnumcardsinhand 
            // Seed for random number generation
            random_device rd;
            mt19937 gen(rd());
            // Define the distribution
            uniform_int_distribution<> dis(1, c.getNumCardsInHand());
            // Generate a random number
            int randomNumber = dis(gen);
            
            Card merp = c.getCardAtIndex(randomNumber-1);
            Card* merpTwo = &merp;
            if(validateCard(test, merpTwo)){
                if(!checkSpecialtyCardsComputer(*merpTwo, nc, available, turn)){
                    playCard(c, discard, randomNumber,"COMPUTER [PLAY]: ");
                }
            }
            if(c.getNumCardsInHand() == 0){
                return true;
            }
            if(c.getNumCardsInHand() == 1){
                chat("COMPUTER [COMMENT]: HANDSIZE: 1");
            }
            return false;
            break;
        }
        temp = temp->getNextCard();
    }
    drawCard(c, available);
    return false;
    }else{Skip=false;}
}  

bool checkDeck(Hand& available, Hand& discard){
    // check if cards are left in available hand
    // if empty shuffle display hand
    // display hand becomes available hand
    if(available.getNumCardsInHand() == 0){
        shuffleCards(discard);
        available = discard;
        return false;
    }
    return true;
}
