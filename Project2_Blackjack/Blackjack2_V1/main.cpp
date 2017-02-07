/* 
 * File:   main.cpp
 * Author: Caeleb Moeller
 * Created on 7 February, 2017, 11:25 AM
 * Purpose: BlackJack v2
 * 
 */

//System Libraries Here
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

//User Libraries Here


//Function Prototypes Here
void Rules();

//Program Execution Begins Here
int main() {
    //Declare and process variables
    float          cash=0,
                   bet=0,
                   minBet,
                   winings=0,
                   lStks=0;
    long           hStks=0;
    short          nStks=0,
                   deck=52,     //number of cards in deck
                   drawV,       //value of card drawn
                   hand,        //number of cards in hand
                   dHand,       //dealer's hand
                   score,       //user's blackjack score
                   dScore,      //dealer's blackjack score
                   wins=0,      //total wins
                   losses=0,    //total losses
                   turn;        //determines whose turn it is
    char           pckGame,     //user picks game mode
                   rstrt,       //used to set restart value with y/n
                   ans,         //used to set draw value with y/n
                   mnuRtrn;     //used to return to the menu
    bool           draw,        //used to execute draw function
                   viewHnd,     //view hand
                   stand,       //user stops drawing
                   dStand,      //dealer stops drawing
                   restart,     //restarts the game
                   menu;        //continues the menu loop
    string         crdType,     //converts drawV to card type string
                   faceD;       //dealer's facedown card

    //Process/Calculations Here
    cout<<"Welcome to Caeleb Moeller's Blackjack Parlor!\n"
          "We have an exciting variety of games, such as \n"
          "Blackjack, High-Stakes Blackjack, and \n"
          "Low-Stakes Blackjack!"<<endl;
    
    do{
    cout<<  "1 - Blackjack\n"
            "2 - High-Stakes Blackjack\n"
            "3 - Low-Stakes Blackjack\n"
            "4 - Rules\n"
            "Pick a game mode."<<endl;
    cin>>pckGame;
    while(pckGame<49||pckGame>52){
        cout<<"Invalid Input. Please enter a command from the list."<<endl;
        cin>>pckGame;
    }
    while(pckGame=='4'){
        Rules();
        cout<<"1 - Blackjack\n"
              "2 - High-Stakes Blackjack\n"
              "3 - Low-Stakes Blackjack\n"
              "Pick a game mode."<<endl;
        cin>>pckGame;
    }
    switch(pckGame){
        case '1':nStks=500;break;
        case '2':hStks=15000000;break;
        case '3':lStks=1.50;break;
    }
    
        short dAce=0,d2=0,d3=0,d4=0,d5=0,d6=0,d7=0,d8=0,d9=0,d10=0, 
                dJ=0,dQ=0,dK=0;    //tracks cards taken from the deck
        
        cash=nStks+hStks+lStks;
        cout<<fixed<<setprecision(2);
    do {
        
        turn=2;
        srand(time(0));       
        short hAce=0,h2=0,h3=0,h4=0,h5=0,h6=0,h7=0,h8=0,h9=0,h10=0,
              hJ=0,hQ=0,hK=0,     //cards in hand
              dhAce=0,dh2=0,dh3=0,dh4=0,dh5=0,dh6=0,dh7=0,dh8=0,dh9=0,dh10=0,
              dhJ=0,dhQ=0,dhK=0;  //cards in dealer's hand
        hand=0;
        dHand=0;
        faceD="nothing";
        draw=true;
        stand=false;
        dStand=false;
        
        minBet=pckGame=='1'?20:
               pckGame=='2'?500000:
               pckGame=='3'?0.10:0;
        
        cout<<"Your money: $"<<cash<<endl;
        cout<<"Place a bet."<<endl;
        cout<<"Minimum Bet: $"<<minBet<<endl;
        cin>>bet;
        while (bet<minBet){cout<<"Your bet is too low.\nPlace a bet."<<endl;
                           cin>>bet;}
        while (bet>cash){cout<<"You can't afford that.\n"
                "Place a bet."<<endl;
                cin>>bet;}
        cash-=bet;
        
      do {
          if (turn>0){hand++;}else{dHand++;}
          if((dStand==false&&turn<0)||(stand==false&&turn>0)){
          deck--;
          viewHnd=false;
          do{
              crdType="Redraw";
              drawV=rand()%13+1;
                  switch (drawV){
                      case 1:if(dAce!=4){crdType="an Ace";
                      if(turn>0){hAce++;}else{dhAce++;}dAce++;}break;    //Checks number of card taken from deck - if it's 4, defaults and 
                      case 2:if(d2!=4){crdType="a Two";
                      if(turn>0){h2++;}else{dh2++;}d2++;}break;           //rerolls drawV. If it's less than 4, add the card to your hand,
                      case 3:if(d3!=4){crdType="a Three";
                      if(turn>0){h3++;}else{dh3++;}d3++;}break;         //output the card type, and add to the number taken from the deck
                      case 4:if(d4!=4){crdType="a Four";
                      if(turn>0){h4++;}else{dh4++;}d4++;}break;
                      case 5:if(d5!=4){crdType="a Five";
                      if(turn>0){h5++;}else{dh5++;}d5++;}break;
                      case 6:if(d6!=4){crdType="a Six";
                      if(turn>0){h6++;}else{dh6++;}d6++;}break;
                      case 7:if(d7!=4){crdType="a Seven";
                      if(turn>0){h7++;}else{dh7++;}d7++;}break;
                      case 8:if(d8!=4){crdType="an Eight";
                      if(turn>0){h8++;}else{dh8++;}d8++;}break;
                      case 9:if(d9!=4){crdType="a Nine";
                      if(turn>0){h9++;}else{dh9++;}d9++;}break;
                      case 10:if(d10!=4){crdType="a Ten";
                      if(turn>0){h10++;}else{dh10++;}d10++;}break;
                      case 11:if(dJ!=4){crdType="a Jack";
                      if(turn>0){hJ++;}else{dhJ++;}dJ++;}break;
                      case 12:if(dQ!=4){crdType="a Queen";
                      if(turn>0){hQ++;}else{dhQ++;}dQ++;}break;
                      case 13:if(dK!=4){crdType="a King";
                      if(turn>0){hK++;}else{dhK++;}dK++;}break;
                   }    //card Table
          }while (crdType=="Redraw");   //card type table
          }
          dScore=2*dh2+3*dh3+4*dh4+5*dh5+6*dh6+7*dh7+8*dh8+9*dh9+10*dh10+10*dhJ+
                  10*dhQ+10*dhK;    //calculate dealer's score
          for(short dAces=dhAce;dAces>0;dAces--){   //determines values of aces in dealer's hand
              if(dScore<=10){dScore+=11;}
              else{dScore+=1;}
          }
          score=2*h2+3*h3+4*h4+5*h5+6*h6+7*h7+8*h8+9*h9+10*h10+10*hJ+10*hQ+10*hK;   //calculate score by multiplying hand quantities by card values
          for(short aces=hAce;aces>0;aces--){   //determines values of aces in hand
              if(score<=10){score+=11;}
              else{score+=1;}
          }
          
          if(turn>0&&stand==false){
          cout<<"The dealer hands you "<<crdType<<".        Deck: "<<deck<<endl;   //tell the user what they drew
          cout<<"Score: "<<score<<endl;}
          if(turn==1&&faceD!="nothing"&&score<21){
              cout<<"The dealer flips his card. It's "<<faceD<<"."<<endl;
              cout<<"Dealer's Score: "<<dScore<<endl;
              if(dScore>=17&&dScore<22){
                  cout<<"The dealer stands."<<endl;
                  dStand=true;
              }else if(dScore>21){
                  cout<<"The dealer busts. You win!"<<endl;
                  wins++;
                  cash+=2*bet;
                  winings+=2*bet;
                  cout<<"Winnings: $"<<2*bet<<endl;
                  draw=false;
              }
          }else if(turn==-2){
          cout<<"The dealer draws "<<crdType<<".        Deck: "<<deck<<endl;
          cout<<"Dealer's Score: "<<dScore<<endl;
          }else if(turn==-1&&score<21&&dStand==false){
              faceD=crdType;
              cout<<"The dealer draws a card and places it face-down."<<endl;
          }
          
          if(turn==-1&&stand==false){
          if(score==21){cout<<"Blackjack!"<<endl;
              cout<<"Winnings: $"<<2*bet<<endl;
              wins++;
              cash+=2*bet;
              winings+=2*bet;
              draw=false;}
          if(score>21){cout<<"Busted!"<<endl;losses++;winings-=bet;draw=false;}
          if(score<21&&turn!=-2){
              cout<<"h - Hit  s - Stand  v - View Hand"<<endl;
              cin>>ans;
              while(ans!='H'&&ans!='h'&&ans!='S'&&ans!='s'&&ans!='v'&&ans!='V'){
                  cout<<"Invalid input. Please enter one of the listed commands."
                          <<endl;
                  cin>>ans;
              }
              switch(ans){
                  case 'H':draw=true;break;
                  case 'h':draw=true;break;
                  case 'S':stand=true;break;
                  case 's':;stand=true;break;
                  case 'v':viewHnd=true;break;
                  case 'V':viewHnd=true;break;
                    }
          }
          if(viewHnd==true){
              cout<<"You have "<<hand<<" cards in your hand"<<endl;
                if (hAce>0){cout<<"Aces: "<<hAce<<endl;} //displays how many of each type of card is in the user's hand
                if (h2>0){cout<<"Twos: "<<h2<<endl;}
                if (h3>0){cout<<"Threes: "<<h3<<endl;}
                if (h4>0){cout<<"Fours: "<<h4<<endl;}
                if (h5>0){cout<<"Fives: "<<h5<<endl;}
                if (h6>0){cout<<"Sixes: "<<h6<<endl;}
                if (h7>0){cout<<"Sevens: "<<h7<<endl;}
                if (h8>0){cout<<"Eights: "<<h8<<endl;}
                if (h9>0){cout<<"Nines: "<<h9<<endl;}
                if (h10>0){cout<<"Tens: "<<h10<<endl;}
                if (hJ>0){cout<<"Jacks: "<<hJ<<endl;}
                if (hQ>0){cout<<"Queens: "<<hQ<<endl;}
                if (hK>0){cout<<"Kings: "<<hK<<endl;}
                cout<<"Score: "<<score<<endl;
                cout<<endl;
                cout<<"h - Hit  s - Stand"<<endl;
                cin>>ans;
                while(ans!='h'&&ans!='H'&&ans!='s'&&ans!='S'){
                    cout<<"Invalid input. Please enter one of the listed"
                            " commands"<<endl;
                    cin>>ans;
                }
                switch(ans){
                    case 'h':draw=true;break;
                    case 'H':draw=true;break;
                    case 's':stand=true;break;
                    case 'S':stand=true;break;
                }//view hand
          }}
          if(turn==-2){turn+=1;}
          turn*=-1;
          
          if(stand==true&&dStand==true&&score<21){
              draw=false;
              cout<<"Your score: "<<score<<endl;
              cout<<"Dealer's score: "<<dScore<<endl;
              if(score>dScore){cout<<"You win!"<<endl;
                    wins++;
                    cash+=2*bet;
                    cout<<"Winnings: $"<<2*bet<<endl;
                    winings+=2*bet;}
              if(score<dScore){cout<<"The house wins!"<<endl;winings-=bet;
                    losses++;}
              if(score==dScore){
                  cout<<"Tie! You and the dealer split the pot."<<endl;
                  cash+=bet;
              }
          }
      }while(draw);
      
      cout<<"Wins: "<<wins<<"   Losses: "<<losses<<endl;
      cout<<"Total Winnings: $"<<winings<<endl;
      
        cout << endl;
        cout << "Play again? y/n" << endl;
        cin>>rstrt;
        while (rstrt != 'y' && rstrt != 'n' && rstrt != 'Y' && rstrt != 'N') {
            cout << "Please enter y/n" << endl;
            cin>>rstrt;
        }
        if (rstrt == 'y' || rstrt == 'Y'){
            restart = true;
            if(deck<13&&cash!=0){
                cout<<"The dealer shuffles the deck"<<endl;
                deck=52;
                dAce=0,d2=0,d3=0,d4=0,d5=0,d6=0,d7=0,d8=0,d9=0,d10=0, 
                dJ=0,dQ=0,dK=0;
            }
            if(cash==0){
                cout<<"You're broke! Better luck next time."<<endl;
                restart=false;
      }
        }else{restart=false;}
        
        } while (restart);
        cout<<"Would you like to return to the menu?"<<endl;
        cin>>mnuRtrn;
        while(mnuRtrn!='y'&&mnuRtrn!='n'){
            cout<<"Invalid input. Please enter y/n."<<endl;
            cin>>mnuRtrn;
        }
        if(mnuRtrn=='y'){
            menu=true;
        }else{
            menu=false;
        }
    }while(menu);
    //Output Located Here

    //Exit
    return 0;
}

void Rules(){
    cout<<"Blackjack is a fun, fast-paced and simple game that anyone can play.\n"
          "The goal of the game is to get a hand that adds to 21, or at\n"
            "least get closer to 21 than your opponent, the dealer.\n"
            "A hand value of 21 is a blackjack, and a hand value of greater\n"
            "than 21 is a bust.\n"
            "The Game:\n"
            "First turn, you're dealt a card face up, then the dealer\n"
            "takes a card and lays it down face up. Next, the dealer\n"
            "gives you a second card face up and takes a second\n"
            "card for himself and lays it face down. At this point\n"
            "you choose whether to 'hit' (draw another card), or 'stand'\n"
            "(stick with your current hand).  The dealer then turns his \n"
            "card over, and if his score is less than 17 he draws another\n"
            "card until it's over 17, in which case he stands.  If you and\n"
            "the dealer are both standing, your scores are compared, and\n"
            "the player with the score closest to 21 wins\n"
            "Card Values:\n"
            "Number cards' values are equal to their number. Face cards\n"
            "are worth 10 points, and Aces are worth either 1 or 11\n"
            "points, depending on whether adding 11 puts your score over 21.\n"
            "Win/Loss Conditions:\n"
            "Your score is 21 - Win\n"
            "Your score is closer to 21 than the dealer - Win\n"
            "The dealer busts - Win\n"
            "You bust - Lose\n"
            "The dealer's score is closer to 21 than yours - Lose\n"
            "If you and the dealer end with the same score, it's a tie,\n"
            "and you get your bet back.\n"
            "Now go and win some money!"<<endl;
}
