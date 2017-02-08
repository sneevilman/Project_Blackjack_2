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
short drwChck(short c[],short s);
bool viewHnd(short,short[],short,string[],short,short);
bool Restart();
bool Menu();
float WinLoss(short,float,float,char,float[][4],short,short,short);
//Program Execution Begins Here
int main() {
    //Declare and process variables
    const short    SIZE(13),
                   DATSIZE(50);
    float          cash=0,
                   strtCsh,     //used for game data
                   bet=0,
                   minBet,
                   winings=0,
                   gameDat[DATSIZE][4]={{0,0}},    //stores game#,win/loss,winnings
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
                   nGames,      //number of games
                   turn;        //determines whose turn it is
    char           pckGame,     //user picks game mode
                   win,         //passes win/loss to win/loss function
                   rstrt,       //used to set restart value with y/n
                   ans;         //used to set stand value with y/n
    bool           fourCrd,     //checks for valid # of cards
                   draw,        //used to execute draw function
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
    cash=0;
    nGames=0;     //initialize number of games
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
        strtCsh=cash;
        cout<<fixed<<setprecision(2);
        srand(time(0));       
        
    do {
        nGames++;
        win=-1;                   //initialize as value that doesn't end game
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
        
      do {
          score=0;
          dScore=0;
          if (turn>0){hand++;}else{dHand++;}
          if((dStand==false&&turn<0)||(stand==false&&turn>0)){
          deck--;
          sub=drwChck(cDeck,SIZE);      //sets a card draw value, checks and returns it
          if(turn>0){cHand[sub]++;}
          else{cDealer[sub]++;}
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
          if(turn==1&&faceD!="nothing"&&score<21&&dStand==false){
              cout<<"The dealer flips his card. It's a(n) "<<faceD<<"."<<endl;
              cout<<"Dealer's Score: "<<dScore<<endl<<endl;
              if(dScore>=17&&dScore<21){
                  cout<<"The dealer stands."<<endl;
                  dStand=true;
              }else if(dScore>21){
                  cout<<"The dealer busts. You win!"<<endl;
                  win=1;
                  draw=false;
              }else if(dScore==21){
                  cout<<"Blackjack! The house wins!"<<endl;
                  win=0;
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
              win=1;
              draw=false;}
          if(score>21){cout<<"Busted!"<<endl;
              win=0;
              draw=false;}
          if(score<21&&turn!=-2){
              cout<<"h - Hit  s - Stand  v - View Hand"<<endl;
              cin>>ans;
              if(ans<87){ans+=32;}      //converts input to lower case
              while(ans!='h'&&ans!='s'&&ans!='v'){
                  cout<<"Invalid input. Please enter one of the listed commands."
                          <<endl;
                  cin>>ans;
                  if(ans<87){ans+=32;}
              }
              switch(ans){
                  case 's':;stand=true;break;
                  case 'v':stand=viewHnd(hand,cHand,SIZE,crdType,SIZE,score);
                    }
          }}
          if(turn==-2){turn+=1;}    //if it's the first turn, make it not the first turn
          turn*=-1;                 //switch from player to dealer
          
          if(stand==true&&dStand==true&&score<21){
              cout<<"Your score: "<<score<<endl;
              cout<<"Dealer's score: "<<dScore<<endl;
              if(score>dScore){cout<<"You win!"<<endl;
              win=1;}
              if(score<dScore){cout<<"The house wins!"<<endl;
              win=0;}
              if(score==dScore){cout<<"Tie! You and the dealer split the pot."
                      <<endl;
                  win=2;
              }
          }
          if(win>-1)draw=false;
      }while(draw);
      cash=WinLoss(nGames,bet,cash,win,gameDat,DATSIZE,score,dScore);
      
            restart=Restart();
            if (restart==true){
            if(deck<13&&cash!=0){
                cout<<"The dealer shuffles the deck."<<endl;
                deck=52;
                for(short l=0;l<SIZE;l++){
                    cDeck[l]=0;
                    }
               }
            if(cash==0){
                cout<<"You're broke! Better luck next time."<<endl;
                restart=false;
               }
        }
        
        } while (restart);
        
        cout<<"Would you like to view your game data?"<<endl;
        cin>>ans;
        if(ans<79){ans+=32;}
        while(ans!='n'&&ans!='y'){
            cout<<"Invalid input. Please enter y/n."<<endl;
            cin>>ans;
        }
            float lostCsh=0,    //declaring and initializing values for earned
                  earnedC=0;    //and lost outside the if(ans) brackets
            
        if(ans=='y'){
            short wins=0,
                  losses=0,
                  ties=0;
                  winings=0;
                  cout<<"Game #    Status    Player Score    Dealer Score    Winnings"
                          <<endl;
                  cout<<"------    ------    ------------    ------------    --------"
                          <<endl;
            for(short l=0;l<nGames;l++){
                if(gameDat[l][1]<0){lostCsh+=gameDat[l][1];
                }else{earnedC+=gameDat[l][1];}
                winings+=gameDat[l][1];
                cout<<left<<setw(10)<<l+1;
                if(gameDat[l][0]==0){
                    cout<<setw(6)<<"Loss";
                    losses++;}
                else if(gameDat[l][0]==1){
                    cout<<setw(6)<<"Win";
                    wins++;}
                else if(gameDat[l][0]==2){
                    cout<<setw(6)<<"Tie";
                    ties++;}
                cout<<"    "<<left<<setw(14)<<static_cast<short>(gameDat[l][2])
                    <<"  "<<setw(14)<<left<<static_cast<short>(gameDat[l][3]);
                cout<<"  $"<<gameDat[l][1];
                cout<<endl;
            }
            cout<<"Wins: "<<wins<<endl;
            cout<<"Losses: "<<losses<<endl;
            cout<<"Ties: "<<ties<<endl;
            cout<<"Starting Money: $"<<strtCsh<<endl;
            cout<<"Money Gained: $"<<earnedC<<endl;
            cout<<"Money lost: $"<<-lostCsh<<endl;
            cout<<"Current Money: $"<<cash<<endl;
            cout<<"Total Winnings: $"<<winings<<endl;
        }
        menu=Menu();
    }while(menu);
    //Output Located Here

    //Exit
    return 0;
}
short drwChck(short c[],short s){
       short sub; 
       bool fourCrd;
    do{
        fourCrd=true;
        sub=rand()%13;
        if(c[sub]!=4){
            fourCrd=false;
        }
    }while(fourCrd);
    c[sub]++;
    return sub;
}
bool viewHnd(short h,short cH[],short sizeH,string t[],short sizeT,short score){
 bool stand;
 char ans;
 cout<<"You have "<<h<<" cards in your hand"<<endl;
              for(short l=0;l<sizeH;l++){
                  if(cH[l]>0){
                      cout<<"You have "<<cH[l]<<" "<<t[l];
                      if(cH[l]!=1){
                          cout<<"s";
                      }
                      cout<<endl;
                  }
              }
                cout<<"Score: "<<score<<endl;
                cout<<endl;
                cout<<"h - Hit  s - Stand"<<endl;
                cin>>ans;
                if(ans<84)ans+=32;
                while(ans!='h'&&ans!='s'){
                    cout<<"Invalid input. Please enter one of the listed"
                            " commands"<<endl;
                    cin>>ans;
                    if(ans<84)ans+=32;
                }
                switch(ans){
                    case 'h':stand=false;break;
                    case 's':stand=true;break;
                }//view hand
        return stand;
          }
float WinLoss(short nGames,float bet,float cash,char win,float g[][4],short size,short score,short dScore){
    if(nGames%size>0){nGames=nGames%size;}  //overwrites game data for numbers/multiples of games over 50
    g[nGames-1][0]=win;
    g[nGames-1][2]=score;
    g[nGames-1][3]=dScore;
    if(win==1){                 //for this array, the 0 subscript indicates wins/losses;
        g[nGames-1][1]=bet;   //the 1 subscript stores values for winnings. 2 subscript stores
    }else if(win==0){           //values for your score, and 3 stores values for dealer score
        g[nGames-1][1]=-bet;
    }else{
        g[nGames-1][1]=0;
    }
    cash+=g[nGames-1][1];
    cout<<"nGames"<<nGames<<endl;
    cout<<"cash: "<<cash<<endl;
    cout<<"g["<<nGames-1<<"][0]"<<g[nGames-1][0]<<endl;
    cout<<"g["<<nGames-1<<"][1]"<<g[nGames-1][1]<<endl;
    return cash;
                            
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
bool Restart() {
    char ans;
    bool restart;
    cout << endl;
    cout << "Would you like to run this program again? y/n" << endl;
    cin>>ans;
    while (ans != 'y' && ans != 'n' && ans != 'Y' && ans != 'N') {
        cout << "Please enter y/n" << endl;
        cin>>ans;
    }
    if (ans == 'y' || ans == 'Y')
        restart = true;
    else
        restart = false;
    return restart;
}
bool Menu() {
    char ans;
    bool menu;
    cout << endl;
    cout << "Would you like to return to the menu? y/n" << endl;
    cin>>ans;
    while (ans != 'y' && ans != 'n' && ans != 'Y' && ans != 'N') {
        cout << "Please enter y/n" << endl;
        cin>>ans;
    }
    if (ans == 'y' || ans == 'Y')
        menu = true;
    else
        menu = false;
    return menu;
}
