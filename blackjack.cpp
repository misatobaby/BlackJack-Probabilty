#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;

int DealCard(bool cardsDealt[]);
void PrintHand(int iaHand[], const int kiCardCount);
void PrintCard(int iCard);
int ScoreHand(int iaHand[], const int kiCardCount);
int WinningCardCountDealer(int playerHand[], int houseHand[], int playerScore, int playerCardCount, int houseCardCount);
int WinningCardCount(int playerHand[], int houseHand[], int playerScore, int playerCardCount);
void PrintScoresAndHands(int houseHand[], const int khouseCardCount, int playerHand[], const int kplayerCardCount);
float WinningProbabilityDealer(int playerHand[], int houseHand[], int playerScore, int playerCardCount, int houseCardCount);
float WinningProbability(int playerHand[],int houseHand[], int playerScore, int playerCardCount, int houseCardCount);

int main () {

time_t qTime;
time(&qTime);
srand(qTime);


bool cardsDealt[52];
int houseCardCount = 2;
int houseHand[12];
int playerCardCount = 2;
int playerHand[12];
int cardsDealtCount = houseCardCount + playerCardCount;

playerHand[0]		= DealCard(cardsDealt);
houseHand[0]		= DealCard(cardsDealt);
playerHand[1]		= DealCard(cardsDealt);
houseHand[1]		= DealCard(cardsDealt);

cout << "--------------------------------------------------------" << endl;
cout << "-----------------------Blackjack------------------------" << endl;
cout << "--------------------------------------------------------" << endl;

int playerScore = ScoreHand(playerHand, playerCardCount);
char cPlayerChoice;
bool bPlayerHits	= true;

do{

		cout << "House's Hand" << endl;
		cout << "** ";
    PrintCard(houseHand[1]);
    cout << endl;
    cout << "Player's Hand";
    cout << endl;
    PrintHand(playerHand, playerCardCount);

    if (playerScore == 21){
        cout << "BACKJACK!!! YOU WIN!!!" << endl;
        PrintScoresAndHands(houseHand,houseCardCount,playerHand,playerCardCount);
        exit(EXIT_SUCCESS);
      }

    cout <<"Player's Hand Sum: " << ScoreHand(playerHand, playerCardCount);
    cout << endl;

    while (playerScore < 10){

      cout << "Your sum is less than 10 so you can't bust on your next hit.";
      cout << endl;
      playerHand[playerCardCount] = DealCard(cardsDealt);
			++playerCardCount;
			playerScore	= ScoreHand(playerHand, playerCardCount);
      cout << "Thus a new card has been dealt to you." << endl;
      cout << "House's Hand" << endl;
      cout << "** ";
      PrintCard(houseHand[1]);
      cout << endl;
      cout << "Player's Hand" << endl;
      PrintHand(playerHand,playerCardCount);
      cout <<"Player's Hand Sum: " << ScoreHand(playerHand, playerCardCount);
      cout << endl;
     }

      int blackJackCard = 21 - playerScore;
     cout << "You want " << blackJackCard << " to get a BlackJack!!!";
     cout << endl;
     cout << "There is currently " << WinningCardCount(playerHand,houseHand,playerScore,playerCardCount) << " " << "'"<< blackJackCard << "'"<< " on the table right now..." << endl;

     cout << "Probabilty of Blackjack on next hit" << endl;
     cout << "Only with cards shown: " << setprecision(3) << WinningProbability(playerHand, houseHand, playerScore,playerCardCount, houseCardCount);
     cout << "%" << endl;
     cout << "If the dealer's face down card is a " << blackJackCard << " : ";
     cout << setprecision(3) <<  WinningProbabilityDealer(playerHand, houseHand, playerScore,playerCardCount,houseCardCount);
     cout << "%" << endl;

      cout << "Hit(h) or stay(s): ";
			cin >> cPlayerChoice;
			cout << endl;
    
        if (cPlayerChoice == 'h'){
          playerHand[playerCardCount] = DealCard(cardsDealt);
				++playerCardCount;
        }
       else if (cPlayerChoice == 's') {
				bPlayerHits = false;
			} else {
				cout << "Error: Try Again!" << endl;
			}

      // Get the Player's current score to update and check for bust.
			playerScore	= ScoreHand(playerHand, playerCardCount);
			cout << endl;
      if (playerScore == 21){
        cout << "BACKJACK!!! YOU WIN!!!" << endl;
        PrintScoresAndHands(houseHand,houseCardCount,playerHand,playerCardCount);
        exit(EXIT_SUCCESS);
      }
    } while (bPlayerHits && playerScore < 22);

    // Once the player is done taking hits, check whether he busted
		if (playerScore> 21) {
			// The Player busted. The House wins.
			cout << "**** The House Wins!!! ****" << endl;
     PrintScoresAndHands(houseHand,houseCardCount,playerHand,playerCardCount);
		
		} else {
			// If the player didn't bust, then the house takes hits below 17
			int iHouseScore		= ScoreHand(houseHand, houseCardCount);
			while (iHouseScore < 17) {
				houseHand[houseCardCount] = DealCard(cardsDealt);
				++houseCardCount;
				iHouseScore		= ScoreHand(houseHand, houseCardCount);
			}
			bool bHouseBusts	= (iHouseScore > 21);
			if (bHouseBusts) {
				// The House busted. Player wins
				cout << "**** The Player Wins!!! ****" << endl;
       PrintScoresAndHands(houseHand,houseCardCount,playerHand,playerCardCount);
			
			} else {
				// Compare scores and determine the winner
				if (playerScore == iHouseScore) {
					// Tie. This is called a "push."
					cout << "**** Tie!!! ****" << endl;
          PrintScoresAndHands(houseHand,houseCardCount,playerHand,playerCardCount);
				
				} else if (playerScore > iHouseScore) {
					// The Player wins
          	cout << "**** The Player Wins!!! ****" << endl;
          PrintScoresAndHands(houseHand,houseCardCount,playerHand,playerCardCount);
				
				} else {
					// The House wins
					cout << "**** The House Wins!!! ****" << endl;
          PrintScoresAndHands(houseHand,houseCardCount,playerHand,playerCardCount);

				}
      }
    }
}

int DealCard(bool cardsDealt[]) {
	bool bCardDealt	= true;
	int iNewCard	= -1;
	do {
		iNewCard = (rand() % 52);
		if (!cardsDealt[iNewCard]) {
			bCardDealt = false;
		}
	} while (bCardDealt);
	return iNewCard;
}

void PrintHand(int iaHand[], const int kiCardCount) {
	using namespace std;
	for (int iCardIndex = 0; iCardIndex < kiCardCount; ++iCardIndex) {
		const int kiNextCard = iaHand[iCardIndex];
		PrintCard(kiNextCard);
		cout << " ";
	}
	cout << endl;
}

void PrintCard(int iCard) {
	using namespace std;
	// Print Rank
	const int kiRank = (iCard % 13);
	if (kiRank == 0) {
		cout << 'A';
	} else if (kiRank < 9) {
		cout << (kiRank + 1);
	} else if (kiRank == 9) {
		cout << 'T';
	} else if (kiRank == 10) {
		cout << 'J';
	} else if (kiRank == 11) {
		cout << 'Q';
	} else {
		cout << 'K';
	}
	// Print Suit
	const int kiSuit = (iCard/13);
	if (kiSuit == 0) {
		cout << 'C';
	} else if (kiSuit == 1) {
		cout << 'D';
	} else if (kiSuit == 2) {
		cout << 'H';
	} else {
		cout << 'S';
	}
}

int ScoreHand(int iaHand[], const int kiCardCount) {
	int iAceCount	= 0;
	int iScore		= 0;
	for (int iCardIndex = 0; iCardIndex < kiCardCount; ++iCardIndex) {
		const int kiNextCard = iaHand[iCardIndex];
		const int kiRank = (kiNextCard % 13);
		if (kiRank == 0) {
			++iAceCount;
			++iScore;
		} else if (kiRank < 9) {
			iScore = iScore + (kiRank + 1);
		} else {
			iScore = iScore + 10;
		}
	}
	while (iAceCount > 0 && iScore < 12) {
		--iAceCount;
		iScore = iScore + 10;
	}
	return iScore;
}

void PrintScoresAndHands(int houseHand[], const int khouseCardCount, int playerHand[], const int kplayerCardCount) {
	using namespace std;
	cout << "House's Hand: Score = " << ScoreHand(houseHand, khouseCardCount) << endl;
	PrintHand(houseHand, khouseCardCount);
	cout << "Player's Hand: Score = " << ScoreHand(playerHand, kplayerCardCount) << endl;
	PrintHand(playerHand, kplayerCardCount);
	cout << endl;
}

int WinningCardCountDealer(int playerHand[],int houseHand[], int playerScore, int playerCount, int houseCount){


  using namespace std;
  int wcc = 0;
  int winningCard = 21 - playerScore;
  for (int i = 0; i < playerCount; i++)
 if(winningCard == 0 && winningCard == (playerHand[i]) % 13){
   wcc++;
   }
  for (int i = 0; i < playerCount; i++){
   if(winningCard ==(playerHand[i] +1 ) % 13){
   wcc++;
   }
  }

 for (int i = 0; i < houseCount; i++)
 if(winningCard == 0 && winningCard == (houseHand[i]) % 13){
   wcc++;
   }
  for (int i = 0; i < houseCount; i++){
   if(winningCard == (houseHand[i] + 1) % 13)
   wcc++;

}
return wcc;
}


int WinningCardCount(int playerHand[], int houseHand[], int playerScore, int playerCount){
int wccd = 0;
  int winningCard = 21 - playerScore;

  for (int i = 0; i < playerCount; i++){
   if(winningCard == (playerHand[i] +1 ) % 13){
   wccd++;
   }
   }
   if (winningCard == (houseHand[1] +1) % 13) { 
    wccd++;
  }
return wccd;
}


float WinningProbability(int playerHand[], int houseHand[],int playerScore, int playerCardCount, int houseCardCount){

  int winningCard = 21 - playerScore;
  if (winningCard == 10){
    return static_cast<float> (12- WinningCardCount(playerHand, houseHand,playerScore,playerCardCount)) * 100  / (52 - (houseCardCount + playerCardCount));
  }

return static_cast<float> (4- WinningCardCount(playerHand, houseHand,playerScore,playerCardCount)) * 100  / (52 - (houseCardCount + playerCardCount));
}

float WinningProbabilityDealer(int playerHand[], int houseHand[], int playerScore, int playerCardCount, int houseCardCount){
  int winningCard = 21 - playerScore;
  if (winningCard == 10){

    return static_cast<float> ((12- WinningCardCount(playerHand,houseHand,playerScore,playerCardCount) - 1)) * 100 / (52 - (houseCardCount + playerCardCount));
    
  }

return static_cast<float> ((4- WinningCardCount(playerHand,houseHand,playerScore,playerCardCount) - 1)) * 100 / (52 - (houseCardCount + playerCardCount));
}
