#include <iostream>
#include <string>
#include "blackjack.cpp"

using namespace std;


int main() {

    int i=0;
    cout << "Enter a key to start playing." << endl;
    cin >> i;

    cout << R"(
.------..------..------..------..------..------..------..------..------.
|S.--. ||N.--. ||A.--. ||C.--. ||K.--. ||J.--. ||A.--. ||C.--. ||K.--. |
| :/\: || :(): || (\/) || :/\: || :/\: || :(): || (\/) || :/\: || :/\: |
| :\/: || ()() || :\/: || :\/: || :\/: || ()() || :\/: || :\/: || :\/: |
| '--'S|| '--'N|| '--'A|| '--'C|| '--'K|| '--'J|| '--'A|| '--'C|| '--'K|
`------'`------'`------'`------'`------'`------'`------'`------'`------')" << endl;
    string choice;
    Blackjack blackjack;


    cout << "Welcome to Blackjack with the snackers!" << endl;

    cout << "Here at SnackJack, we let the player pick their own name and their dealer's name." << endl;
    cout << "Your name: ";
    cin >> blackjack.userName;
    cout << "Your dealer's name: ";
    cin >> blackjack.dealerName;

    string dealerName = blackjack.dealerName;
    string userName = blackjack.userName;

    blackjack.dealFirstTwoCards();
    
    while (true) {
        if (blackjack.userPull==1) {
            string userCard = blackjack.randomCard(userName);
            cout << userName << " pulled " << userCard << endl;
            blackjack.updatePoints(userName, userCard);
            blackjack.verifyOverPoints();
        }

        if (blackjack.dealerPull==1) {
            string dealerCard = blackjack.randomCard(dealerName);
            blackjack.updatePoints(dealerName, dealerCard);
            blackjack.verifyOverPoints();
        }

        if (blackjack.dealerPoints > 17) {
            if(blackjack.dealerPull==1) cout << "The dealer has decided to fold!" << endl;
            blackjack.dealerPull=0;
        }

        if (blackjack.userPull==1 && blackjack.userPoints<21) {
            cout << "Fold or continue?" << endl;
            cin >> choice;
        }

        if (choice == "fold"){
            cout << "You have decided to fold!" << endl;
            blackjack.userPull=0;
        }

        if (blackjack.userPull==0 && blackjack.dealerPull==0) break;
    }

    blackjack.verifyWin();

    return 0;
}