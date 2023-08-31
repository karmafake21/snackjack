#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class Blackjack {
public:
    int dealerPoints=0;
    int userPoints=0;

    int dealerPull=1;
    int userPull=1;

    int userDraws=0;
    int dealerDraws=0;

    string userName;
    string dealerName;

    vector<string> cards = {"Two of Diamonds", "Two of Hearts", "Two of Spades", "Two of Clubs", 
        "Three of Diamonds", "Three of Hearts", "Three of Spades", "Three of Clubs", 
        "Four of Diamonds", "Four of Hearts", "Four of Spades", "Four of Clubs", 
        "Five of Diamonds", "Five of Hearts", "Five of Spades", "Five of Clubs", 
        "Six of Diamonds", "Six of Hearts", "Six of Spades", "Six of Clubs", 
        "Seven of Diamonds", "Seven of Hearts", "Seven of Spades", "Seven of Clubs", 
        "Eight of Diamonds", "Eight of Hearts", "Eight of Spades", "Eight of Clubs", 
        "Nine of Diamonds", "Nine of Hearts", "Nine of Spades", "Nine of Clubs", 
        "Ten of Diamonds", "Ten of Hearts", "Ten of Spades", "Ten of Clubs", 
        "Jack of Diamonds", "Jack of Hearts", "Jack of Spades", "Jack of Clubs", 
        "Queen of Diamonds", "Queen of Hearts", "Queen of Spades", "Queen of Clubs", 
        "King of Diamonds", "King of Hearts", "King of Spades", "King of Clubs", 
        "Ace of Diamonds", "Ace of Hearts", "Ace of Spades", "Ace of Clubs"};

    vector<string> userCards;
    vector<string> dealerCards;


    string randomCard(string person) {
        string card;
        srand(time(nullptr));
        int randIndex = rand() % cards.size();
        card = cards[randIndex];
        string randIndexStr = to_string(randIndex);
        auto removed = find(cards.begin(), cards.end(), card);
        cards.erase(removed);

        if (person == userName){
            userDraws++;
            userCards.push_back(card);
        } else {
            dealerDraws++;
            dealerCards.push_back(card);
        }

        return card;
    }

    void updatePoints(string person, string card) {
        srand(time(nullptr));
        int value, choiceForAce;

        if (card.find("Two") != string::npos) value=2;
        else if (card.find("Three") != string::npos) value=3;
        else if (card.find("Four") != string::npos) value=4;
        else if (card.find("Five") != string::npos) value=5;
        else if (card.find("Six") != string::npos) value=6;
        else if (card.find("Seven") != string::npos) value=7;
        else if (card.find("Eight") != string::npos) value=8;
        else if (card.find("Nine") != string::npos) value=9;
        else if (card.find("Ten") != string::npos || card.find("Jack") != string::npos || card.find("Queen") != string::npos || card.find("King") != string::npos) value=10;

        if (person == dealerName) {
            if (card.find("Ace") != string::npos) {
                if (dealerPoints < 11) value=11;
                else value=1;
            }
            dealerPoints += value;
        }

        if (person == userName) {
            if (card.find("Ace") != string::npos) {
                if (userPoints < 11) {
                    cout << "Ace is 1 or 11?" << endl;
                    cin >> choiceForAce;
                    if (choiceForAce == 1) value=1;
                    else value=11;
                } else value=1;
                if (userDraws < 3) value=11;
            }
            userPoints += value;
        }
    }

    void userFirst() {
        cout << userName << "'s cards were: ";
            for (int i=0; i<userCards.size();i++) {
                if (i!=userCards.size()-1) cout << userCards[i] << ", ";
                else cout << userCards[i] << "." << endl;
            }
            cout << dealerName << "'s cards were: ";
            for (int i=0; i<dealerCards.size();i++) {
                if (i!=dealerCards.size()-1) cout << dealerCards[i] << ", ";
                else cout << dealerCards[i] << "." << endl;
            }
    }

    void dealerFirst() {
        cout << dealerName << "'s cards were: ";
            for (int i=0; i<dealerCards.size();i++) {
                if (i!=dealerCards.size()-1) cout << dealerCards[i] << ", ";
                else cout << dealerCards[i] << "." << endl;
            }
        cout << userName << "'s cards were: ";
            for (int i=0; i<userCards.size();i++) {
                if (i!=userCards.size()-1) cout << userCards[i] << ", ";
                else cout << userCards[i] << "." << endl;
            }
    }

    void verifyOverPoints() {
        if (userPoints > 21) {
            cout << userName << " has lost with " << userPoints << " points! " << dealerName << " has " << dealerPoints << " points!" << endl;
            userFirst();
            exit(0);
        }
        if (dealerPoints > 21) {
            cout << dealerName << " has lost with " << dealerPoints << " points! " << userName << " has " << userPoints << " points!" << endl;
            dealerFirst();
            exit(0);
        }
    }

    void verifyWin () {
        if (dealerPoints == 21 && userPoints != 21) {
            cout << dealerName << " has won with " << dealerPoints << " points! " << userName << " has " << userPoints << " points!" << endl;
            dealerFirst();
            exit(0);
        }

        if (userPoints == 21 && userPoints != 21) {
            cout << userName << " has won with " << userPoints << " points! " << dealerName << " has " << dealerPoints << " points!" << endl;
            userFirst();
            exit(0);
        }
        
        if (dealerPoints < 22 && dealerPoints > userPoints){
            cout << dealerName << " has won with " << dealerPoints << " points! " << userName << " has " << userPoints << " points!" << endl;
            dealerFirst();
            exit(0);
        }

        if (userPoints < 22 && userPoints > dealerPoints){
            cout << userName << " has won with " << userPoints << " points! " << dealerName << " has " << dealerPoints << " points!" << endl;
            userFirst();
            exit(0);
        }

        if (dealerPoints == userPoints) {
            cout << "It's a tie! Both users have "<< userPoints << " points!" << endl;
            userFirst();
            exit(0);
        }

    }

    void dealFirstTwoCards() {
        string choice;
        cout << "The first 2 cards have been dealt." << endl;

        string cardUserOne = randomCard(userName);
        updatePoints(userName, cardUserOne);

        string cardUserTwo = randomCard(userName);
        updatePoints(userName, cardUserTwo);

        cout << "You pulled: " << cardUserOne << " and " << cardUserTwo << "." << endl;

        string cardDealerOne = randomCard(dealerName);
        updatePoints(dealerName, cardDealerOne);

        string cardDealerTwo = randomCard(dealerName);
        updatePoints(dealerName, cardDealerTwo);

        if (userPoints == 21) {
            cout << userName << " has won by pulling 21 points!" << endl;
            exit(0);
        }
        if (dealerPoints == 21) {
            cout << dealerName << " has won by pulling 21 points! " << ""  << endl;
            exit(0);
        }

        if (dealerPoints > 17){
            dealerPull=0;
        }

        if (dealerPull==1) cout << dealerName << " decided to pull another card. "<< userName <<", fold or pull another card?" << endl;
        else cout << dealerName << " has decided to fold. " << userName <<", fold or pull another card?" << endl;
        cin >> choice;

        if (choice == "fold") {
            userPull=0;
        }

        if (userPull==0 && dealerPull==0) verifyWin();

    }

};

// everything works
// add betting system and replay option