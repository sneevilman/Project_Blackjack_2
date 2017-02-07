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
    const short    SIZE(13);
    float          cash=0,
                   bet=0,
                   minBet,
                   winings=0,
                   lStks=0;
    long           hStks=0;
    short          nStks=0,
                   deck=52,     //number of cards in deck
                   drawV,       //value of card drawn
                   sub,         //subscript used for parallel arrays
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
    bool           fourCrd,     //checks for valid # of cards
                   draw,        //used to execute draw function
                   viewHnd,     //view hand
                   stand,       //user stops drawing
                   dStand,      //dealer stops drawing
                   restart,     //restarts the game
                   menu;        //continues the menu loop
    string         crdType[SIZE]={"Ace","Two","Three","Four","Five","Six",
                                  "Seven","Eight","Nine","Ten","Jack",
                                  "Queen","King"},
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
    
        short cDeck[SIZE]={0};    //tracks cards taken from the deck
        
        cash=nStks+hStks+lStks;
        cout<<fixed<<setprecision(2);
        srand(time(0));       
        
    do {
        turn=2;
        short cHand[SIZE]={0},    //cards in hand
              cDealer[SIZE]={0};  //cards in dealer's hand
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
          score=0;
          dScore=0;
          if (turn>0){hand++;}else{dHand++;}
          if((dStand==false&&turn<0)||(stand==false&&turn>0)){
          deck--;
          viewHnd=false;
          do{
              fourCrd=true;
              sub=rand()%13;
              if(cDeck[sub]!=4){
                  fourCrd=false;
                  cDeck[sub]++;
                  if(turn>0){
                      cHand[sub]++;
                  }else{
                      cDealer[sub]++;
                  }
              }
            }while (fourCrd==true);   //card draw randomizer
          }
          for (short dh=1;dh<SIZE;dh++){
              if(dh<10){dScore+=cDealer[dh]*(dh+1);}
              else{dScore+=cDealer[dh]*10;}
          }
          for(short dAces=cDealer[0];dAces>0;dAces--){   //determines values of aces in dealer's hand
              if(dScore<=10){dScore+=11;}
              else{dScore+=1;}
          }
          for (short h=1;h<SIZE;h++){
              if(h<10){score+=cHand[h]*(h+1);}
              else{score+=cHand[h]*10;}
          }
          for(short aces=cHand[0];aces>0;aces--){   //determines values of aces in dealer's hand
              if(score<=10){score+=11;}
              else{score+=1;}
          }
          
          if(turn>0&&stand==false){
          cout<<"The dealer hands you a(n)"<<crdType[sub]<<".        Deck: "<<deck<<endl;   //tell the user what they drew
          cout<<"Score: "<<score<<endl;}
          if(turn==1&&faceD!="nothing"&&score<21){
              cout<<"The dealer flips his card. It's a(n) "<<faceD<<"."<<endl;
              cout<<"Dealer's Score: "<<dScore<<endl<<endl;
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
          cout<<"The dealer draws a(n) "<<crdType[sub]<<".        Deck: "<<deck<<endl;
          cout<<"Dealer's Score: "<<dScore<<endl<<endl;
          }else if(turn==-1&&score<21&&dStand==false){
              faceD=crdType[sub];
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
              for(short l=0;l<SIZE;l++){
                  if(cHand[l]>0){
                      cout<<"You have "<<cHand[l]<<" "<<crdType[l];
                      if(cHand[l]!=1){
                          cout<<"s";
                      }
                      cout<<endl;
                  }
              }
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
          if(turn==-2){turn+=1;}    //if it's the first turn, make it not the first turn
          turn*=-1;                 //switch from player to dealer
          
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
      for(short l=0;l<SIZE;l++){
          cout<<l+1<<": "<<cDeck[l]<<endl;
      }
      
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
                for(short l=0;l<SIZE;l++){
                    cDeck[l]=0;
                }
            }
            if(cash==0){
                cout<<"You're broke! Better luck next time."<<endl;
                restart=false;
      }
        }else{restart=false;}
        
        } while (restart);
        cout<<"Would you like to return to the menu? y/n"<<endl;
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
