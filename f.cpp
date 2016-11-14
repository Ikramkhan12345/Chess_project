#include<windows.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include <windows.h>
bool bishopmove=false,bishopsmove=false;
bool rookpmove=false,rooksmove=false;
using namespace std;
enum game {FIRST,SECOND,THIRD};
enum gmenu {NEW,LOAD,REPLAY};
ofstream savegame;
ifstream loadgame;
void checkmate(int Turn,char Board[9][9],bool &checkmusibat,bool &gamewinner,bool &looser);

void gotoRowCol(int rpos, int cpos)
{
 int xpos=cpos, ypos = rpos;
 COORD scrn;
 HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
 scrn.X = xpos; scrn.Y = ypos;
 SetConsoleCursorPosition(hOuput,scrn);
}
void Sleep1(double m)
{
    for(int i=0;i<999999*m;i++)
    {

    }
}
void color(int i){
    HANDLE  hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,i);
}
void loading ()
{
    char c=-37;

    gotoRowCol(19,40);
    color(4);
    cout<<"Loading.......!!!!! "<<endl;
    for(int i=40;i<60;i++)
    {
        gotoRowCol(20,i);
        color(3);
        cout<<c;
        Sleep1(90);
    }
    for(int j=19;j<=20;j++)
    {

    for(int i=40;i<60;i++)
    {
        gotoRowCol(j,i);
        cout<<' ';
        //Sleep1(20);
    }
    }


}

void clearingscrean()
{
    for(int r=0;r<40;r++)
    {
        for(int c=0;c<80;c++)
        {

            gotoRowCol(r,c);
            color(0);
            cout<<' ';
        }
    }

}
void menu(char s)
{
    int rows=15, cols=28;
    //gotoRowCol(rows,cols);

//        for(int i=cols;i<=50;i++)
//        {
//            gotoRowCol(rows,i);
//            cout<<s;
//        }
        color(10);
        gotoRowCol(rows,cols);
        cout<<"New game.....!!!!";
        gotoRowCol(rows+3,cols);
        cout<<"Load game....!!!!";
        gotoRowCol(rows+6,cols);
        cout<<"REPLAY!!!!";



}
///////////

void menu1(char s,game & usermarzi)
{
    int rows=15, cols=28;
    //gotoRowCol(rows,cols);

//        for(int i=cols;i<=50;i++)
//        {
//            gotoRowCol(rows,i);
//            cout<<s;
//        }
        color(10);
        gotoRowCol(rows,cols);
        cout<<"New game.....!!!!";
        gotoRowCol(rows+3,cols);
        cout<<"Load game....!!!!";
        gotoRowCol(rows+6,cols);
        cout<<"REPLAY!!!!";
if(usermarzi==FIRST)
{
    color(192);
        gotoRowCol(rows,cols);
        cout<<"New game.....!!!!";
}
if(usermarzi==SECOND)
{
    color(192);
   gotoRowCol(rows+3,cols);
        cout<<"Load game....!!!!";
}
if(usermarzi==THIRD)
{
    color(192);
   gotoRowCol(rows+6,cols);
        cout<<"REPLAY!!!!";
}



}
////////////
void Turnchange (int &T)
{
    if(T==0)
        T=1;
    else
        T=0;

}
////////
void loadinggame(char Board[9][9],int &Turn,string Players[2],char player1array[20],char player2array[20])
{
    loadgame.open("saved.txt");
    loadgame>>Turn;
     loadgame>>Players[0];
          loadgame>>Players[1];
          loadgame>>bishopmove;
          loadgame>>bishopsmove;
          loadgame>>rookpmove;
          loadgame>>rooksmove;
    for(int r=0;r<=8;r++)
    {
        for(int c=0;c<=8;c++)
        {
            loadgame>>Board[r][c];
        }

    }
    for(int i=0;i<20;i++)
    {
        loadgame>>player1array[i];
    }
    //savegame<<endl;
    for(int i=0;i<20;i++)
    {
        loadgame>>player2array[i];
    }
    loadgame.close();
}
////////
void savingsteps (int &Gamelavel,int &Safety,char Undoredo[100][9][9],int & Turn,char Board[9][9],char player1[50][20],char player2 [50][20],char player1array[20],char player2array[20])
{
    Gamelavel++;
        Safety++;

        for(int j=0;j<9;j++)
        {
        for(int k=0;k<9;k++)
        {
            Undoredo[Gamelavel][j][k]=Board[j][k];
        }
        }
        for(int i=0;i<20;i++)
        {
            player1[Gamelavel][i]=player1array[i];
            player2[Gamelavel][i]=player2array[i];
        }


    ///////



    ////////

}
///////////
void doingundo (int &Gamelavel,char Undoredo[100][9][9],int & Turn,char Board[9][9],char player1[50][20],char player2 [50][20],char player1array[20],char player2array[20])
{

if (Gamelavel!=0)
{
    --Gamelavel;

        for(int j=0;j<9;j++)
        {
        for(int k=0;k<9;k++)
        {
           Board[j][k]= Undoredo[Gamelavel][j][k];
        }
        }
        for(int i=0;i<20;i++)
        {
            player1array[i]=player1[Gamelavel][i];
            player2array[i]=player2[Gamelavel][i];
        }
}


}   ///////

void doingredo (int &Gamelavel,int Safety,char Undoredo[100][9][9],int & Turn,char Board[9][9],char player1[50][20],char player2 [50][20],char player1array[20],char player2array[20])
{
if(Gamelavel<Safety)
{
    ++Gamelavel;

        for(int j=0;j<9;j++)
        {
        for(int k=0;k<9;k++)
        {
           Board[j][k]= Undoredo[Gamelavel][j][k];
        }
        }
         for(int i=0;i<20;i++)
        {
            player1array[i]=player1[Gamelavel][i];
            player2array[i]=player2[Gamelavel][i];
        }
}


    ////////

}
///////////
void savinggame(char Board[9][9],int Turn,string Players[2],char player1array[20],char player2array[20])
{
    savegame.open("saved.txt");
    savegame<<Turn<<endl;
     savegame<<Players[0]<<endl;
          savegame<<Players[1]<<endl;
          savegame<<bishopmove<<endl;
          savegame<<bishopsmove<<endl;
          savegame<<rookpmove<<endl;
          savegame<<rooksmove<<endl;
    for(int r=0;r<=8;r++)
    {
        for(int c=0;c<=8;c++)
        {
            savegame<<Board[r][c]<<" ";
        }
        savegame<<endl;
    }
    for(int i=0;i<20;i++)
    {
        savegame<<player1array[i]<<" ";
    }
    savegame<<endl;
    for(int i=0;i<20;i++)
    {
        savegame<<player2array[i]<<" ";
    }
    savegame.close();
}

//////////////
void savingreplay(char Board[9][9],int Turn,string Players[2],ofstream &savereplay)
{

    savereplay<<Turn<<endl;
     savereplay<<Players[0]<<endl;
          savereplay<<Players[1]<<endl;
    for(int r=0;r<=8;r++)
    {
        for(int c=0;c<=8;c++)
        {
            savereplay<<Board[r][c]<<" ";
        }
        savereplay<<endl;
    }
    savereplay<<endl;
    //savereplay.close();
}

/////////////
void loadingreplay(char Board[9][9],int &Turn,string Players[2],ifstream &loadreplay)
{

    loadreplay>>Turn;
     loadreplay>>Players[0];
      loadreplay>>Players[1];
    for(int r=0;r<=8;r++)
    {
        for(int c=0;c<=8;c++)
        {
            loadreplay>>Board[r][c];
        }

    }
    //loadreplay.close();
}
///////////
void printselectedbox(int r,int c,int rd,int cd,char s,int i)
{
    for(int ri=0; ri<=rd; ri++)
    {
        for(int ci=0; ci<=cd; ci++)
        {
        if(ri==0||ci==0||ri==rd||ci==cd)
        {


                gotoRowCol(r*rd+ri,c*cd+ci);
                color(i);
                cout<<s;
        }
//
//                   if((r+c)%2==0)
//                {
//                    color(255);
//                     cout<<s;
//                }
//                else
//                {
//                    color(160);
//                     cout<<s;
//                }
            //}

        }
    }
}
void printmovementbox(int r,int c,int rd,int cd,char s,int i)
{

    for(int ri=0; ri<=rd; ri++)
    {
        for(int ci=0; ci<=cd; ci++)
        {
            if(ri==0||ci==0||ri==rd||ci==cd)
            {

/////////////
// gotoRowCol(r-1*rd+ri,c-1*cd+ci);
// {
//      if((r+c)%2==0)
//                {
//                    color(255);
//                     cout<<s;
//                }
//                else
//                {
//                    color(160);
//                     cout<<s;
//                }
//
// }

//////////
                gotoRowCol(r*rd+ri,c*cd+ci);
                color(i);
                cout<<s;
            }
//
//                   if((r+c)%2==0)
//                {
//                    color(255);
//                     cout<<s;
//                }
//                else
//                {
//                    color(160);
//                     cout<<s;
//                }
            //}

        }
    }
}
///////////
void printinbox(int r,int c,int rd,int cd,char Board [9][9])
{
    gotoRowCol (r*rd+rd/2,c*cd+cd/2);
     if(Board[r][c]>='A' && Board[r][c]<='Z')
             {
               if((r+c)%2==0)
               {
                   color(252);
               cout<<Board[r][c]<<" ";
               }
               else if((r+c)%2!=0)
               {
                   color(4);
               cout<<Board[r][c]<<" ";
               }
             }
             if(Board[r][c]>='a' && Board[r][c]<='z')
             {
             if((r+c)%2==0)
               {
                   color(251);
               cout<<Board[r][c]<<" ";
               }
               else if((r+c)%2!=0)
               {
                   color(3);
               cout<<Board[r][c]<<" ";
               }



             }
             if(Board[r][c]=='-')
             {
                 if((r+c)%2==0)
               {
                   color(252);
               cout<<" ";
               }
               else if((r+c)%2!=0)
               {
                   color(4);
               cout<<" ";
               }



             }
}
/////
void printbox(int r,int c,int rd,int cd,char s)
{
    for(int ri=0; ri<=rd; ri++)
    {
        for(int ci=0; ci<=cd; ci++)
        {
            //if(ri==0||ci==0||ri==rd||ci==cd)
            //{


                gotoRowCol(r*rd+ri,c*cd+ci);

                   if((r+c)%2==0)
                {
                    color(255);
                     cout<<s;
                }
                else
                {
                    color(160);
                     cout<<s;
                }
            //}

        }
    }
}
//////
bool isnotmypiece(int Turn,char l)
{
    if(Turn==0)
    {
        if('a'<=l &&l<='z' || l=='-')
        {
            return true;
        }
    }
    if(Turn==1)
    {
         if('A'<=l &&l<='Z' || l=='-' )
        {
            return true;
        }
    }
}
bool checkcapital (char piece)
{
    if((piece>='a' && piece<='z') || piece=='-')
    {

return false;

    }
   return true;
}
bool checksmall (char piece)
{
 if((piece>='A' && piece<='Z') || piece=='-')
    {

return false;

    }
   return true;
}

void promotion (char Board[9][9],int Turn,int er)
{
    char optionforprmtn;
    if(Turn==0)
    {

        for(int r=6;r<9;r++)
        {
            for(int c=0;c<9;c++)
            {
                char SS=Board[r][c];
                switch(SS)
                {
                    case 'L':
                    case 'P':
                    case 'N':
                    case 'S':
                    if(er==6 || er==7 || er==8)
                    {
                        gotoRowCol(32,3);
                    color(4);
                    cout<<"Y/N"<<endl;
                    cin>>optionforprmtn;
                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
                    Board[r][c]='G';
                      gotoRowCol(32,3);
                     cout<<"   "<<endl;
                       break;
                    }
                    case 'B':
                    if(er==6 || er==7 || er==8)
                    {
                    cout<<"Y/N"<<endl;
                    cin>>optionforprmtn;
                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
                    bishopmove=true;
                    gotoRowCol(32,3);
                     cout<<"   "<<endl;
                    break;
                    }
                    case 'R':
                    if(er==6 || er==7 || er==8)
                    {

                    cout<<"Y/N"<<endl;
                    cin>>optionforprmtn;
                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
                    rookpmove=true;
                     gotoRowCol(32,3);
                     cout<<"   "<<endl;
                    break;
                    }
                }
            }
        }
    }
    if(Turn==1)
    {
        for(int r=0;r<2;r++)
        {
            for(int c=0;c<9;c++)
            {
                char SS=Board[r][c];
                switch(SS)
                {
                    case 'l':
                    case 'p':
                    case 'n':
                    case 's':
                    if(er==0 || er==1 || er==2)
                    {

                        gotoRowCol(32,3);
                    color(3);
                    cout<<"Y/N"<<endl;
                    cin>>optionforprmtn;
                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
                    Board[r][c]='g';
                      gotoRowCol(32,3);
                     cout<<"   "<<endl;
                       break;
                    }
                    case 'b':
                    if(er==0 || er==1 || er==2)
                    {
                        color(3);
                    cout<<"Y/N"<<endl;
                    cin>>optionforprmtn;
                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
                     bishopsmove=true;
                    //bishopmove=true;
                    gotoRowCol(32,3);
                     cout<<"   "<<endl;
                    break;
                    }
                    case 'r':
                    if(er==0 || er==1 || er==2)
                    {
                        color(3);

                    cout<<"Y/N"<<endl;
                    cin>>optionforprmtn;
                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
                    rooksmove=true;
                    //rookpmove=true;
                     gotoRowCol(32,3);
                     cout<<"   "<<endl;
                    break;
                    }
                }
            }
        }
    }




//                    gotoRowCol(32,3);
//                    color(4);
//                    cout<<"Y/N"<<endl;
//                    cin>>optionforprmtn;
//                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
//                    Board[r][c]='G';
//                    gotoRowCol(32,3);
//                     cout<<"   "<<endl;
//                    break;
//                    case 'B':
//                    cout<<"Y/N"<<endl;
//                    cin>>optionforprmtn;
//                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
//                    bishopmove=true;
//                    gotoRowCol(32,3);
//                     cout<<"   "<<endl;
//                    break;
//                    case 'R':
//                    cout<<"Y/N"<<endl;
//                    cin>>optionforprmtn;
//                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
//                    rookpmove=true;
//                     gotoRowCol(32,3);
//                     cout<<"   "<<endl;
//                    break;
//
//                }
////                if(Board[r][c]=='L')
////                Board[r][c]='G';
//            }
//        }
   // }
//    if(Turn==1)
//    {
//         for(int r=0;r<3;r++)
//        {
//            for(int c=0;c<9;c++)
//           {
//               switch(Board[r][c])
//                {
//                    case 'l':
//                    case 'p':
//                    case 'n':
//                    case 's':
//                    cout<<"Y/N"<<endl;
//                    cin>>optionforprmtn;
//                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
//                    Board[r][c]='g';
//                    gotoRowCol(32,3);
//                     cout<<"   "<<endl;
//                    break;
//                    case 'b':
//                    cout<<"Y/N"<<endl;
//                    cin>>optionforprmtn;
//                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
//                    bishopsmove=true;
//                    gotoRowCol(32,3);
//                     cout<<"   "<<endl;
//                    break;
//                    case 'r':
//                    cout<<"Y/N"<<endl;
//                    cin>>optionforprmtn;
//                    if(optionforprmtn=='Y' ||optionforprmtn=='y')
//                    rooksmove=true;
//                    gotoRowCol(32,3);
//                     cout<<"   "<<endl;
//                    break;
//
//                }
////                if(Board[r][c]=='l')
////                Board[r][c]='g';
//            }
//        }
  //}
}
bool ispawnmove(char Board[9][9],int Startco[2],int Endco[2],int &Turn,int &r,int &c,int &er,int &ec)
{
    int t;

    if (Turn==0)
    { t=(er-r);
        ////if(r==1)
        //{
            if((t==1) && (c==ec))
            return true;
        //}
//        else if(r!=1)
//        {
//
//            if(t==1 &&  c==ec)
//            {
//                return true;
//            }
//        }
        else
                return false;

    }
    if (Turn==1)
    {
    t=(r-er);
        //if(r==6)
        //{//
            //t=(Endco[0]-Startco[0]);
            //if((t==2) || (t==1) && (c==ec))
            //{
                //return true;
            //}
        //}
        //else if(r!=6)
        //{
            //t=(Endco[0]-Startco[0]);
            if(t==1 &&  c==ec)
            {
                return true;
            }
        //}
        else
        return false;
    }

}
//////
bool isdiagonal(int &sr,int &sc,int &er,int &ec)
{
    if((ec-sc)==(er-sr) || (sr+sc)==(er+ec))
    {
        return true;
    }
    return false;
}
///////////
bool isdiagonal1(int &sr,int &sc,int &er,int &ec,char B[9][9])
{
    int t=abs(ec-sc)-1;
    for(int i=1;i<=t;i++)
    {
        if(B[sr+i][sc-i]!='-')
        {
            return false;
        }
    }
    return true;
}
//////////
bool isdiagonal2(int &sr,int &sc,int &er,int &ec,char B[9][9])
{
    int t=abs(sc-ec)-1;
    for(int i=1;i<=t;i++)
    {
        if(B[sr-i][sc+i]!='-')
        {
            return false;
        }
    }
    return true;
}
//////////validater_Sc
bool isdiagonal3(int &sr,int &sc,int &er,int &ec,char B[9][9])
{
    int t=abs(sc-ec)-1;
    for(int i=1;i<=t;i++)
    {
        if(B[sr+i][sc+i]!='-')
        {
            return false;
        }
    }
    return true;
}
///////////
bool isdiagonal4(int &sr,int &sc,int &er,int &ec,char B[9][9])
{
    int t=abs(sc-ec)-1;
    for(int i=1;i<=t;i++)
    {
        if(B[sr-i][sc-i]!='-')
        {
            return false;
        }
    }
    return true;
}
//////
bool isXaxismove(int &sr,int &sc,int &er,int &ec)
{
    if(sr==er)
    {
        return true;
    }
    return false;
}
bool isYaxismove(int &sr,int &sc,int &er,int &ec)
{
    if(sc==ec)
    {
        return true;
    }
    return false;
}
bool isXpathclear(char Board[9][9],int &sr,int &sc,int &er,int &ec)
{
    int min,max,t;
    if(ec>sc)
    {
        min=sc;
        max=ec;
    }
    else
    {
    min=ec;
    max=sc;
    }
    t=(max-min)-1;
    for(int i=1;i<=t;i++)
    {
        if((Board[sr][min+i])!='-')
        {
            return false;
        }
    }
    return true;

}
///////////
bool isYpathclear(char Board[9][9],int &sr,int &sc,int &er,int &ec)
{
    int min,max,t;
    if(er>sr)
    {
        min=sr;
        max=er;
    }
    else
    {
    min=er;
    max=sr;
    }
    t=(max-min)-1;
    for(int i=1;i<=t;i++)
    {
        if((Board[min+i][sc])!='-')
        {
            return false;
        }
    }
    return true;

}
void intializegame(char Board[9][9],int & Turn,string Players[2])
{
    gotoRowCol(0,25);
    color (252);
    cout<<"Enter Players Names"<<endl;
    cin>>Players[0];
    cin>>Players[1];
    system("cls");
    Turn=1;
    for(int r=0;r<9;r++)
    {
        for(int c=0;c<9;c++)
        {
        Board[r][c]='-';
        }
    }
    for(int r=0;r<9;r++)
    {
        Board[2][r]='P';
    }
    for(int r=0;r<9;r++)
    {
        Board[6][r]='p';
    }
    Board[0][0]=Board[0][8]='L';
    Board[8][0]=Board[8][8]='l';
    Board[0][1]=Board[0][7]='N';
    Board[8][1]=Board[8][7]='n';
    Board[0][2]=Board[0][6]='S';
    Board[8][2]=Board[8][6]='s';
    Board[0][3]=Board[0][5]='G';
    Board[8][3]=Board[8][5]='g';
    Board[0][4]='K';
    Board[8][4]='k';
    Board[1][1]='B';
    Board[1][7]='R';
    Board[7][1]='b';
    Board[7][7]='r';


}
void Movepiece(int Startco[2],int Endco[2],char Board[9][9],int Turn,int &r,int &c,string players[2],char Undoredo[50][9][9],int &Gamelavel)
{

    bool check;
    getch();
    int rows,cols,answer;
do
{
gotoRowCol(20,25);
color(251);
cout<<"Where You wanna move Piece"<<endl;
if(Turn==0)
{
   rows=0,cols=0;
  if(kbhit())
  {
do
{
    if((rows+cols)%2==0)
{
    printmovementbox(rows,cols,40/16,80/16,-37,255);
}
else
{
    printmovementbox(rows,cols,40/16,80/16,-37,160);
}
gotoRowCol(22,25);
color(251);
cout<<"Rows "<<rows<<" "<<"Cols "<<cols<<" ";

      answer=getch();

      //////

      ///////


      if(answer==224)
      {
          answer=getch();
          if(answer==72)
          {
              rows--;
          }
          if(answer==80)
          {
             rows++;
          }
          if(answer==75)
          {
              cols--;
          }
          if(answer==77)
          {
              cols++;
          }
      }
      if(rows>8)
      {
          rows=0;
      }
      if(cols>8)
      {
          cols=0;
      }
      /////
      if(rows<0)
      {
         rows=8;
      }
      if(cols<0)
      {
          cols=8;
      }


  printmovementbox(rows,cols,40/16,80/16,-37,254);
}
  while(answer!=13);
  }

}

if(Turn==1)
{
   rows=8,cols=0;
  if(kbhit())
  {
do
{
if((rows+cols)%2==0)
{
    printmovementbox(rows,cols,40/16,80/16,-37,255);
}
else
{
    printmovementbox(rows,cols,40/16,80/16,-37,160);
}

gotoRowCol(22,25);
color(251);
cout<<"Rows "<<rows<<" "<<"Cols "<<cols<<" ";

      answer=getch();


      if(answer==224)
      {
          answer=getch();
          if(answer==72)
          {
              rows--;
          }
          if(answer==80)
          {
             rows++;
          }
          if(answer==75)
          {
              cols--;
          }
          if(answer==77)
          {
              cols++;
          }
      }
      if(rows>8)
      {
          rows=0;
      }
      if(cols>8)
      {
          cols=0;
      }
      /////
      if(rows<0)
      {
         rows=8;
      }
      if(cols<0)
      {
          cols=8;
      }

  printmovementbox(rows,cols,40/16,80/16,-37,254);
}
  while(answer!=13);
  }

}
Endco[0]=rows;
Endco[1]=cols;
 r=Endco[0];
c=Endco[1];
if(Turn==0)
{
if(Board[r][c]=='-' || (Board[r][c]>='a' && Board[r][c]<='z'  ))
{
    check=true;
}
else
check=false;
}
////////
if(Turn==1)
{
if(Board[r][c]=='-' || (Board[r][c]>='A' && Board[r][c]<='Z'))
{
    check=true;
}
else
check=false;
}
////////
}
while(check==false);
gotoRowCol(35,2);
color(0);
cout<<"      ";
}
bool validater_Sc(int Startco[2],char Board[9][9],int Turn,char &hold,int & r,int &c,bool &checkmusibat)
{
    r=Startco[0];
        c=Startco[1];
        hold=Board[r][c];
    if (Turn==0)
    {
//        if(checkmusibat==true)
//        {
//            if(Board[r][c]== 'K')
//            {
//                checkmusibat=false;
//                gotoRowCol(35,2);
//                        cout<<"       ";
//                return true;
//
//            }
//            return false;
//        }

        if(Board[r][c]<'A' ||Board[r][c]>'Z' )
        {
            return false;
        }
        return true;
    }
    if (Turn==1)
    {
//        if(checkmusibat==true)
//        {
//            if(Board[r][c]== 'k')
//            {
//                checkmusibat=false;
//                gotoRowCol(35,2);
//                        cout<<"       ";
//                return true;
//
//            }
//            return false;
//        }
        if(Board[r][c]<'a' ||Board[r][c]>'z' )
        {
            return false;
        }
        return true;
    }
}
//////////////////

////////////////
void printboard(char Board [9][9],int Turn,int Rows,int Cols,string Players[2],int rd,int cd,char s,char player1array[20],char player2array[20],int dprows,int dpcols)
{
    color(0);
    system("cls");
    gotoRowCol(0,0);
        for(int r=0; r<=8; r++)
    {
        //int n=9;
        for(int c=0; c<=8; c++)
        {

                printbox(r,c,rd,cd,s);
                printinbox(r,c,rd,cd,Board);

        }
    }



    if(Turn==0)
    {
    gotoRowCol(30,3);
    color(252);
    cout<<Players[0]<<"  Turn"<<endl;
    }
    else
    {
        gotoRowCol(30,3);
        color(251);
        cout<<Players[1]<<"  Turn"<<endl;
    }
//    ////////////
//     if(Turn==0)
//    {
//        color(4);
//        gotoRowCol(3,55);
//        cout<<"You Droping Pieces";
//
//
//    }
//
//
//    if(Turn==1)
//    {
//        color(3);
//        gotoRowCol(3,55);
//        cout<<"You Droping Pieces";
//
//    }
//    if(Turn==0)
//    {
//        for(int i=0;i<20;i++)
//        {
//            color(4);
//            gotoRowCol(dprows+i+1,dpcols);
//            if(player1array[i]!=' ')
//              cout<<player1array[i]<<endl;;
//        }
//    }
//    if(Turn==1)
//    {
//        for(int i=0;i<20;i++)
//        {
//            color(3);
//            gotoRowCol(dprows+i+1,dpcols);
//            if(player2array[i]!=' ')
//              cout<<player2array[i]<<endl;;
//        }
//    }
    ///////////////
}
void printmove(int Startco[2],int Endco[2],char Board[9][9],char hold,int &r,int &c,int &rr ,int cc)
{
    int sr=Startco[0];
    int sc=Startco[1];
    Board[rr][cc]='-';
    Board[r][c]=hold;

}
bool isrookmove(char Board[9][9],int Startco [2],int Endco[2],int &Turn,int &sr,int &sc,int &er,int &ec)
{
    return(isXaxismove(sr,sc,er,ec) && isXpathclear(Board,sr,sc,er,ec) || isYaxismove(sr,sc,er,ec) && isYpathclear(Board,sr,sc,er,ec));

}
bool isbishopmove(char Board[9][9],int Startco[2],int Endco[2],int &Turn,int &sr,int &sc,int &er,int &ec)
{

if(isdiagonal(sr,sc,er,ec)==true)
    {
        if(sr>er &&sc<ec)//
        {
            return(isdiagonal2(sr,sc,er,ec,Board));
        }
        /////
        if(sc>ec &&sr<er)//
        {
            return(isdiagonal1(sr,sc,er,ec,Board));
        }
        /////
        if(sc<ec && sr<er)//
        {
            return(isdiagonal3(sr,sc,er,ec,Board));
        }
        /////
        if(sc>ec && sr>er)
        {
            return(isdiagonal4(sr,sc,er,ec,Board));
        }

//    return (isdiagonal1(sr,sc,er,ec,Board))||(isdiagonal2(sr,sc,er,ec,Board))||(isdiagonal3(sr,sc,er,ec,Board))||(isdiagonal4(sr,sc,er,ec,Board));

}
}
bool islancemove(int &sr,int& sc,int&er,int &ec,int &Turn)
{
    int t;
    if(Turn==0)
    {
        if(sc==ec && er>sr)
        return true;
        return false;

    }
    if(Turn==1)
    {
   if(sc==ec && er<sr)
        return true;
        return false;
    }
}
bool kingmove(int &sr,int &sc,int &er,int &ec)
{
    int t1=abs(sr-er);
    int t2=abs(ec-sc);
    int t3=abs(sr-er);
    int t4=abs(sc-ec);
   if((t1==1 && sc==ec)|| t2==1 && sr==er ||(t3==1&& t4==1))
   {
       return true;
   }
   return false;
}
///////
bool silvergeneralmove(int &sr,int &sc,int &er,int &ec,int Turn)
{
    int rd,cd;
    if(Turn==0)
    {
        rd=abs(er-sr);
        cd=abs(ec-sc);
        if((rd==1 && cd==1) || (rd==1 && cd==0 && er>sr))
        {
            return true;
        }
        return false;
    }
    if(Turn==1)
    {
        rd=abs(sr-er);
        cd=abs(sc-ec);
        if((rd==1 && cd==1) || (rd==1 && cd==0 &&er<sr))
        {
            return true;
        }
        return false;
    }
}
////////////
//////
bool goldengeneralmove(int &sr,int &sc,int &er,int &ec,int Turn)
{
    int rd,cd;
    if(Turn==0)
    {
        rd=abs(er-sr);
        cd=abs(ec-sc);
        if((rd==1 && cd==0)|| (rd==0 && cd==1) || (rd==1 && cd==1 && er>sr))
        {
            return true;
        }
        return false;
    }
    if(Turn==1)
    {
        rd=abs(sr-er);
        cd=abs(sc-ec);
        if((rd==1 && cd==0)|| (rd==0 && cd==1) || (rd==1 && cd==1 && er<sr))
        {
            return true;
        }
        return false;
    }
}
///////
bool knightmove(int &sr,int &sc,int &er,int &ec,int Turn)
{

  if(Turn==0)
  {
      int rd=(er-sr);
      int cd=abs(ec-sc);
      if(rd==2 && cd==1)
      {
          return true;
      }
      return false;
  }
  if(Turn==1)
  {
     int rd=(sr-er);
      int cd=abs(sc-ec);
      if(rd==2 && cd==1)
      {
          return true;
      }
      return false;
  }
}
//////////
bool validmovement(int &er,int &ec,int &sr,int &sc,int Startco[2],int Endco[2],char Board[9][9],int Turn)
{
//    int r=Startco[0];
//    int c=Startco[1];
    char symbol=Board[sr][sc];
    char esymbol=Board[er][ec];
    switch(symbol)
    {
        case 'P':
        case  'p':
        return (ispawnmove(Board,Startco,Endco,Turn,sr,sc,er,ec));
        case 'R':
        if(rookpmove==true)
        return (isrookmove(Board,Startco,Endco,Turn,sr,sc,er,ec)|| kingmove(sr,sc,er,ec));
        else
        return (isrookmove(Board,Startco,Endco,Turn,sr,sc,er,ec));
        case'r':
        if(rooksmove==true)
        return (isrookmove(Board,Startco,Endco,Turn,sr,sc,er,ec)|| kingmove(sr,sc,er,ec));
        else
        return (isrookmove(Board,Startco,Endco,Turn,sr,sc,er,ec));
       case 'B':
       if(bishopmove==true)
       return (isbishopmove(Board,Startco,Endco,Turn,sr,sc,er,ec)|| kingmove(sr,sc,er,ec));
       else
       return (isbishopmove(Board,Startco,Endco,Turn,sr,sc,er,ec));
        case'b':
        if(bishopsmove==true)
       return (isbishopmove(Board,Startco,Endco,Turn,sr,sc,er,ec)|| kingmove(sr,sc,er,ec));
        else
        return (isbishopmove(Board,Startco,Endco,Turn,sr,sc,er,ec));
        case 'L':
        case'l':
        return(islancemove(sr,sc,er,ec,Turn) && (isYpathclear(Board,sr,sc,er,ec)));
        case 'K':
        case'k':
        return(kingmove(sr,sc,er,ec));
          case 'N':
        case'n':
        return(knightmove(sr,sc,er,ec,Turn));
        case 'S':
        case's':
        return(silvergeneralmove(sr,sc,er,ec,Turn));
        case 'G':
        case'g':
        return(goldengeneralmove(sr,sc,er,ec,Turn));
        case '-':
        return false;

////isYaxismove(sr,sc,er,ec)&& isYpathclear(Board,sr,sc,er,ec)&&
    }
}
//////
void printavailablemove(int Turn,char b[9][9],int sc[2],int &rows,int &cols)
{
//    int str=sc[0];
//    int stc=sc[1];

    int Endco[2];
    for(int r=0;r<9;r++)
    {
        for(int c=0 ;c<9;c++)
        {
            Endco[0]=r;
            Endco[1]=c;
            //////
            if(Turn==0)
            {

           if((validmovement(r,c,rows,cols,sc,Endco,b,Turn)==true) && ((b[r][c]>='a' &&b[r][c]<='z') ||(b[r][c]=='-')))
           {
                printmovementbox(r,c,40/16,80/16,-37,20);
           }
           else
           {
               if((r+c)%2==0)
              {
               printmovementbox(r,c,40/16,80/16,-37,255);
              }
          else
           {
               printmovementbox(r,c,40/16,80/16,-37,160);
           }
           }
        }
        /////////
        if(Turn==1)
            {

           if((validmovement(r,c,rows,cols,sc,Endco,b,Turn)==true) && ((b[r][c]>='A' &&b[r][c]<='Z') ||(b[r][c]=='-')))
           {
                printmovementbox(r,c,40/16,80/16,-37,20);
           }
           else
           {
               if((r+c)%2==0)
              {
               printmovementbox(r,c,40/16,80/16,-37,255);
              }
          else
           {
               printmovementbox(r,c,40/16,80/16,-37,160);
           }
           }
        }
        /////////
        }
    }

}
////////////////
void takeinput (int Startco[2],char Board[9][9],int &Turn,char hold,int &r,int &c,string players[2],int undo[50][2],int &i,char Undoredo[50][9][9],int &Gamelavel,bool checkmusibat )
{
    getch();
    int rows,cols,answer;

do
{
gotoRowCol(20,25);
color(251);
cout<<"Select Your Piece"<<endl;
if(Turn==0)
{
    rows=0,cols=0;
  if(kbhit())
  {

do
{
    if((rows+cols)%2==0)
{
    printselectedbox(rows,cols,40/16,80/16,-37,255);
}
else
{
    printselectedbox(rows,cols,40/16,80/16,-37,160);
}

gotoRowCol(22,25);
color(252);
cout<<"Rows "<<rows<<" "<<"Cols "<<cols<<" ";

      answer=getch();



      if(answer==224)
      {
          answer=getch();
          if(answer==72)
          {
              rows--;
          }
          if(answer==80)
          {
             rows++;
          }
          if(answer==75)
          {
              cols--;
          }
          if(answer==77)
          {
              cols++;
          }
      }
      if(rows>8)
      {
          rows=0;
      }
      if(cols>8)
      {
          cols=0;
      }
      /////
      if(rows<0)
      {
          rows=8;
      }
      if(cols<0)
      {
          cols=8;
      }
      printselectedbox(rows,cols,40/16,80/16,-37,254);
      char checkvalidsymbol= Board[rows][cols];
      if(Turn==0)
      {
          if(checkvalidsymbol>='A' && checkvalidsymbol<='Z')
          printavailablemove(Turn,Board,Startco,rows,cols);
      }
//      else if(Turn==1)
//      {
//          if(checkvalidsymbol>='a' && checkvalidsymbol<='z')
//          printavailablemove(Turn,Board,Startco,rows,cols);
//      }
      //printavailablemove(Turn,Board,Startco,rows,cols);
      ///////
  }
  while(answer!=13);
  }
}
if(Turn==1)
{
     rows=8,cols=0;
  if(kbhit())
  {

do
{
    if((rows+cols)%2==0)
{
    printselectedbox(rows,cols,40/16,80/16,-37,255);
}
else
{
    printselectedbox(rows,cols,40/16,80/16,-37,160);
}
gotoRowCol(22,25);
color(251);
cout<<"Rows "<<rows<<" "<<"Cols "<<cols<<" ";

      answer=getch();


      if(answer==224)
      {
          answer=getch();
          if(answer==72)
          {
              rows--;
          }
          if(answer==80)
          {
             rows++;
          }
          if(answer==75)
          {
              cols--;
          }
          if(answer==77)
          {
              cols++;
          }
      }
      if(rows>8)
      {
          rows=0;
      }
      if(cols>8)
      {
          cols=0;
      }
      /////
      if(rows<0)
      {
          rows=8;
      }
      if(cols<0)
      {
          cols=8;
      }
      printselectedbox(rows,cols,40/16,80/16,-37,254);
      char checkvalidsymbol= Board[rows][cols];
      if(Turn==1)
     {
         if(checkvalidsymbol>='a' && checkvalidsymbol<='z')
        printavailablemove(Turn,Board,Startco,rows,cols);
     }
         //printavailablemove(Turn,Board,Startco,rows,cols);
  }

  while(answer!=13);
  }

/////
}
Startco[0]=rows;
Startco[1]=cols;


}
while(validater_Sc(Startco,Board,Turn,hold,r,c,checkmusibat)!=true);




}
///////
void start (game &usermarzi,gmenu &Start,char s)
{

    do
    {


    int answer1=getch();
//    if(answer1==224)
//    {
        switch(answer1)
        {
            case 72:
            if(usermarzi==FIRST)
            {
                usermarzi=THIRD;
                Start=REPLAY;
            }
           else if(usermarzi==THIRD)
            {
                usermarzi=SECOND;
                Start=LOAD;
            }
           else if(usermarzi==SECOND)
            {
                usermarzi=FIRST;
                Start=NEW;
            }
            //Start=true;
            menu1(s,usermarzi);
            break;
            case 80:
            //Start=false;
            if(usermarzi==FIRST)
            {
                usermarzi=SECOND;
                Start=LOAD;
            }
           else if(usermarzi==SECOND)
            {
                usermarzi=THIRD;
                Start=REPLAY;
            }
            else if(usermarzi==THIRD)
            {
                usermarzi=FIRST;
                Start=NEW;

            }

            menu1(s,usermarzi);
            break;
        }
    //}
    }
    while(getch()!=13);
}
void printmoveforcheck(int Startco[2],int Endco[2],char Board[9][9],char hold,int &r,int &c,int &rr ,int cc,char endhold)
{
    int sr=Startco[0];
    int sc=Startco[1];
    Board[rr][cc]=hold;
    Board[r][c]=endhold;

}
bool checkking(int Turn,char Board[9][9],bool &checkmusibat,bool &gamewinner,bool & looser)
{
checkmusibat=false;
    ////////// intialing new array
//    for(int i=0;i<8;i++)
//    {
//        kingcheckmoves[i][0]=0;
//        kingcheckmoves[i][1]=0;
//
//    }
 int count=0;
 int counter=0;
int Ek[2]={0,0};
int Sk[2]={0,0};
int er,ec,sr,sc;
    if(Turn==0)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(Board[i][j]=='K')
                {
                    Ek[0]=i;
                    Ek[1]=j;
                    er=i;
                    ec=j;
                    count=1;
                    break;
                }

            }
            if(count==1)
            break;
        }
//        for(int kr=er-1;kr<=er+1;kr++)
//        {
//            if(kr<0)
//            continue;
//            for(int kc=ec-1;kc<=ec+1;kc++)
//            {
//                if(kc<0)
//            continue;
//            if(kr==er && kc==ec)
//            continue;
//                if(validmovement(kr,kc,er,ec,Sk,Ek,Board,1)==true)
//                    {
//                        if((Board[kr][kc]>='a' && Board[kr][kc]<='z')|| (Board[kr][kc]=='-'))
//                        {
//                        kingcheckmoves[counter][0]=kr;
//                        kingcheckmoves[counter][1]=kc;
//                        counter++;
//                        }
//
//
//                    }
//            }
//        }

        ////////
        for(int k=0;k<9;k++)
        {
            for(int l=0;l<9;l++)
            {
                char c=Board[k][l];
                if(c>='a' &&c<='z')
                {
                    Sk[0]=k;
                    Sk[1]=l;
                    sr=k;
                    sc=l;
                    if(validmovement(er,ec,sr,sc,Sk,Ek,Board,1)==true)
                    {
                       gotoRowCol(35,2);
                       color(252);
                        cout<<"check"<<endl;
                        checkmusibat=true;
                        return true;
                    }
                }
            }
        }
//        if(checkmusibat==true)
//        checkmate(Turn,Board,checkmusibat,counter,gamewinner,looser);
        ///////
    }
    if(Turn==1)
    {

        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(Board[i][j]=='k')
                {
                    Ek[1]=i;
                    Ek[2]=j;
                    er=i;
                    ec=j;
                    count=1;
                    break;
                }

            }
            if(count==1)
            break;
        }
//        for(int kr=er-1;kr<=er+1;kr++)
//        {
//            for(int kc=ec-1;kc<=ec+1;kc++)
//            {
//                if(validmovement(kr,kc,er,ec,Sk,Ek,Board,0)==true)
//                    {
//                        if((Board[kr][kc]>='A' && Board[kr][kc]<='Z')|| (Board[kr][kc]=='-'))
//                        {
//                        kingcheckmoves[counter][0]=kr;
//                        kingcheckmoves[counter][1]=kc;
//                        counter++;
//                        }
//
//                    }
//            }
//        }


    ////////
        for(int k=0;k<9;k++)
        {
            for(int l=0;l<9;l++)
            {
                char c=Board[k][l];
                if(c>='A' &&c<='Z')
                {
                    Sk[0]=k;
                    Sk[1]=l;
                    sr=k;
                    sc=l;
                    if(validmovement(er,ec,sr,sc,Sk,Ek,Board,0)==true)
                    {
                        gotoRowCol(35,2);
                        color(251);
                        cout<<"Check"<<endl;
                        checkmusibat=true;
                        return true;
                    }

                }
            }
        }
//        if(checkmusibat==true)
       //checkmate(Turn,Board,checkmusibat,counter,gamewinner,looser);
    }
        ///////
}
bool Alllegalmoves11 (int Turn,char Board[9][9],bool &checkmusibat,bool &gamewinner,bool looser)
{
    int sc[2];
    int ec[2];
    int sr,scc,er,ecc;
    for(int r=0;r<9;r++)
    {

        for(int c=0;c<9;c++)
        {
            sc[0]=r;
            sc[1]=c;
            sr=r;
            scc=c;
            if(Board[r][c]!='-')
            {

            for(int k=0;k<9;k++)
            {
                for(int l=0;l<9;l++)
                {
                    ec[0]=k;
                    ec[1]=l;
                    er=k;
                    ecc=l;
//                    checkking(Turn,Board,checkmusibat,gamewinner,looser);
                    if(validmovement(er,ecc,sr,scc,sc,ec,Board,Turn)==true &&  checkking(Turn,Board,checkmusibat,gamewinner,looser)==true )
                    {
                        if(Turn==0)
                        {
                            if((Board[er][ecc]>'a' && Board[er][ecc]<'z')|| Board[er][ecc]=='-')
                            return true;
                        }
                        if(Turn==1)
                        {
                            if((Board[er][ecc]>'A' && Board[er][ecc]<'Z')|| Board[er][ecc]=='-')
                            return true;
                        }

                    }
                }
            }
            }
        }
    }
    return false;
}
bool Alllegalmoves (int Turn,char Board[9][9],bool &checkmusibat,bool &gamewinner,bool looser)
{
    int sc[2];
    int ec[2];
    char hold;
    int sr,scc,er,ecc;
    char endhold;
    if(Turn==0)
    {
    for(int r=0;r<9;r++)
    {

        for(int c=0;c<9;c++)
        {
            sc[0]=r;
            sc[1]=c;
            sr=r;
            scc=c;
            hold=Board[sr][scc];
            if(Board[r][c]>'A' && Board[r][c]<'Z')
            {

            for(int k=0;k<9;k++)
            {
                for(int l=0;l<9;l++)
                {
                    ec[0]=k;
                    ec[1]=l;
                    er=k;
                    ecc=l;
                    endhold=Board[k][l];
//                    checkking(Turn,Board,checkmusibat,gamewinner,looser);
                    if(validmovement(ec[0],ec[1],sr,scc,sc,ec,Board,Turn)==true)
                    {
                         printmove(sc,ec,Board,hold,er,ecc,sr,scc);

                        if(checkking(Turn,Board,checkmusibat,gamewinner,looser)==false)
                        {


//                        if(Turn==0)
//                        {
                            printmoveforcheck(sc,ec,Board,hold,er,ecc,sr,scc,endhold);
                            //printmove(sc,ec,Board,hold,sr,scc,er,ecc);
                            if((Board[er][ecc]>'a' && Board[er][ecc]<'z')|| Board[er][ecc]=='-')
                            return true;
                      //  }
//                        if(Turn==1)
//                        {
//                            printmove(sc,ec,Board,hold,sr,scc,er,ecc);
//
//                            if((Board[er][ecc]>'A' && Board[er][ecc]<'Z')|| Board[er][ecc]=='-')
//                            return true;
//                        }
                       }
                        printmoveforcheck(sc,ec,Board,hold,er,ecc,sr,scc,endhold);
                        //printmove(sc,ec,Board,hold,sr,scc,er,ecc);

                    }
                }
            }
            }
        }
    }

    return false;
    }
    /////////////////////////////
    if(Turn==1)
    {
    for(int r=0;r<9;r++)
    {

        for(int c=0;c<9;c++)
        {
            sc[0]=r;
            sc[1]=c;
            sr=r;
            scc=c;
            hold=Board[sr][scc];
            if(Board[r][c]>'a' && Board[r][c]<'z')
            {

            for(int k=0;k<9;k++)
            {
                for(int l=0;l<9;l++)
                {
                    ec[0]=k;
                    ec[1]=l;
                    er=k;
                    ecc=l;
                    endhold=Board[k][l];
//                    checkking(Turn,Board,checkmusibat,gamewinner,looser);
                    if(validmovement(ec[0],ec[1],sr,scc,sc,ec,Board,Turn)==true)
                    {
                         printmove(sc,ec,Board,hold,er,ecc,sr,scc);

                        if(checkking(Turn,Board,checkmusibat,gamewinner,looser)==false)
                        {

//
//                        if(Turn==0)
//                        {
//                            printmove(sc,ec,Board,hold,sr,scc,er,ecc);
//                            if((Board[er][ecc]>'a' && Board[er][ecc]<'z')|| Board[er][ecc]=='-')
//                            return true;
//                        }
//                        if(Turn==1)
//                        {
                            printmoveforcheck(sc,ec,Board,hold,er,ecc,sr,scc,endhold);
                            //printmove(sc,ec,Board,hold,sr,scc,er,ecc);

                            if((Board[er][ecc]>'A' && Board[er][ecc]<'Z')|| Board[er][ecc]=='-')
                            return true;
                       // }
                        }
                        printmoveforcheck(sc,ec,Board,hold,er,ecc,sr,scc,endhold);
                        //printmove(sc,ec,Board,hold,sr,scc,er,ecc);

                    }
                }
            }
            }
        }
    }

    return false;
    }
    ////////////////////////
}
void checkmate(int Turn,char Board[9][9],bool &checkmusibat,bool &gamewinner,bool &looser)
{
 //checkking(Turn,Board,checkmusibat,gamewinner,looser);
if(Alllegalmoves(Turn,Board,checkmusibat,gamewinner,looser)==false && checkking(Turn,Board,checkmusibat,gamewinner,looser)==true)
{
    gamewinner=true;
    looser=Turn+1%2;
}
else
{
    gamewinner=false;
}

}

//void savingboaddrooping (char Board[9][9])
//{
// for(int r=0;r<9;r++)
//    {
//        for(int c=0;c<9;c++)
//        {
//        Board[r][c]='-';
//        }
//    }
//    for(int r=0;r<9;r++)
//    {
//        Board[2][r]='P';
//    }
//    for(int r=0;r<9;r++)
//    {
//        Board[6][r]='p';
//    }
//    Board[0][0]=Board[0][8]='L';
//    Board[8][0]=Board[8][8]='l';
//    Board[0][1]=Board[0][7]='N';
//    Board[8][1]=Board[8][7]='n';
//    Board[0][2]=Board[0][6]='S';
//    Board[8][2]=Board[8][6]='s';
//    Board[0][3]=Board[0][5]='G';
//    Board[8][3]=Board[8][5]='g';
//    Board[0][4]='K';
//    Board[8][4]='k';
//    Board[1][1]='B';
//    Board[1][7]='R';
//    Board[7][1]='b';
//    Board[7][7]='r';
//
//
//
//
//}
//void savingdropingelements(char player1array[20],char player2array[20],int Turn,int &dropingcounter2,int &dropingcoubter1,int Rows,int Cols,char findingdrop)
//{
////    if(Turn==0)
////    {
////        color(252);
////        gotoRowCol(3,55);
////        cout<<"You Droping Pieces";
////
////
////    }
////
////
////    if(Turn==1)
////    {
////        color(3);
////        gotoRowCol(3,55);
////        cout<<"You Droping Pieces";
////
////    }
//    if(Turn==0)
//    {
//        findingdrop=toupper(findingdrop);
//        player1array[dropingcoubter1]=findingdrop;
//
////         color(251);
////            gotoRowCol(Rows+dropingcoubter1,Cols);
////              cout<<player1array[dropingcoubter1]<<endl;;
//    }
//    if(Turn==1)
//    {
//        findingdrop=tolower(findingdrop);
//        player2array[dropingcounter2]=findingdrop;
////        char cc=player2array[dropingcounter2];
////        color(3);
////              gotoRowCol(Rows+dropingcounter2+1,Cols);
////              cout<<player2array[dropingcounter2]<<endl;;
//    }
//}
//void printdropelements(int counter,int &Rows,int &Cols,char findingdrop,int Turn,int &i,char player1array[20],char player2array[20],int &dropingcounter2)
//{
//
//int hold;
//    int loop=0;
//    switch(findingdrop)
//    {
//      case 'P':
//      case 'p':
//      if(counter>9)
//      {
//          hold=counter-9;
//          counter-=hold;
//      }
//      loop=abs(counter-9);
//      break;
//      case 'B':
//      case 'b':
//      case 'R':
//      case 'r':
//      if(counter>1)
//      {
//          hold=counter-1;
//          counter-=hold;
//      }
//      loop=abs(counter-1);
//      break;
//      case 'N':
//      case 'n':
//      case 'G':
//      case 'g':
//      case 's':
//      case 'S':
//      case 'l':
//      case 'L':
//      if(counter>2)
//      {
//          hold=counter-2;
//          counter-=hold;
//      }
//      loop=abs(counter-2);
//      break;
//
//
//    }
//    if(Turn==0)
//    {
//    if(findingdrop>='a' && findingdrop<='z')
//      {
//          for(int z=0;z<loop;z++)
//          {
//                        savingdropingelements(player1array,player2array,Turn,dropingcounter2,i,Rows,Cols,findingdrop);
//                        i++;
//
////              color(251);
////              gotoRowCol(Rows+i,Cols);
////              cout<<findingdrop<<endl;;
//          }
//
//
//      }
//    }
//      ///////////////////
//      if(Turn==1)
//      {
//      if(findingdrop>='A' && findingdrop<='Z')
//      {
//          for(int z=0;z<loop;z++)
//          {
//              savingdropingelements(player1array,player2array,Turn,dropingcounter2,i,Rows,Cols,findingdrop);
//              dropingcounter2++;
//
//              // i++;
////              color(3);
////              gotoRowCol(Rows+i,Cols);
////              cout<<findingdrop<<endl;
//
//          }
//
//
//      }
//      }
//}
//void searchingdrop (char Board[9][9],char hold[9][9],char findingdrop,int &Rows,int &Cols,int Turn,int &i,char player1array[20],char player2array[20],int &dropingcounter2)
//{
////    int i=0;
//   int counter=0;
//    for(int k=0;k<9;k++)
//    {
//         for(int l=0;l<9;l++)
//         {
//             char check=Board[k][l];
//             if(check==findingdrop)
//             counter++;
//         }
//    }
//
//    printdropelements(counter,Rows,Cols,findingdrop,Turn,i,player1array,player2array,dropingcounter2);
//   //i++;
//
//}
//void checkdroping (char Board[9][9],char holdarray [9][9],int Rows,int Cols,int Turn,int i,char player1array[20],char player2array[20],int dropingcounter2)
//{
//    int count=0;
//    int smallp=0,capp=0,smallrk=0,caprook=0,smallbishop=0,capbishop=0;
//    int smalgnrl=0,capgenrl=0,sn=0,cn=0,smalsg=0,capsg=0,smallance=0,caplance=0;
//    for(int fazool=0;fazool<20;fazool++)
//    {
//        player1array[fazool]=' ';
//        player2array[fazool]=' ';
//    }
//    for(int r=0;r<9;r++)
//    {
//        for(int c=0;c<9;c++)
//        {
//        char findingdrop=holdarray[r][c];
//      switch(findingdrop)
//        {    //////////
//      case 'P':
//      capp++;
//      count=capp;
//      break;
//      case 'p':
//      smallp++;
//      count=smallp;
//      break;
//      case 'B':
//      capbishop++;
//      count=capbishop;
//      break;
//      case 'b':
//      smallbishop++;
//      count=smallbishop;
//      break;
//      case 'R':
//      caprook++;
//      count=caprook;
//      break;
//      case 'r':
//      smallrk++;
//      count=smallrk;
//      break;
//      case 'N':
//      cn++;
//      count=cn;
//      break;
//      case 'n':
//      sn++;
//       count=sn;
//       break;
//      case 'G':
//      capgenrl++;
//      count=capgenrl;
//      break;
//      case 'g':
//      smalgnrl++;
//      count=smalgnrl;
//      break;
//      case 's':
//      smalsg++;
//      count=smalsg;
//      break;
//      case 'S':
//      capsg++;
//      count=capsg;
//      break;
//      case 'l':
//      smallance++;
//      count=smallance;
//      break;
//      case 'L':
//      caplance++;
//      count=caplance;
//      break;
//        }
//        if(count==1)
//        {
//            searchingdrop(Board,holdarray,findingdrop,Rows,Cols,Turn,i,player1array,player2array,dropingcounter2);
//        }
//            //////////
//
//
//
//        }
//    }
//}
void printdroping(char player1array[20],char player2array[20],int Turn,int Rows,int Cols)
{
   if(Turn==0)
    {
        color(4);
        gotoRowCol(3,55);
        cout<<"Your Droping Pieces";


    }


    if(Turn==1)
    {
        color(3);
        gotoRowCol(3,55);
        cout<<"Your Droping Pieces";

    }
    if(Turn==0)
    {
        for(int i=0;i<20;i++)
        {
            color(4);
            gotoRowCol(Rows+i+1,Cols);
            //if(player1array[i]!=' ')

              cout<<player1array[i]<<endl;;
        }
    }
    if(Turn==1)
    {
        for(int i=0;i<20;i++)
        {
            color(3);
            gotoRowCol(Rows+i+1,Cols);
            //if(player2array[i]!=' ')
            char z=player2array[i];
              cout<<player2array[i]<<endl;;
        }
    }
}
bool validdropingpiece (char player1array[20],char player2array[20],int Turn,char drop)
{
    if(Turn==0)
    {
        for(int i=0;i<20;i++)
        {
            if(player1array[i]==drop)
            return true;
            //check=true;
        }
    }
    if(Turn==1)
    {
         for(int i=0;i<20;i++)
        {
            if(player2array[i]==drop)
            return true;
            //check=true;
        }
    }

}
void availablemovementsfor_brgs(char Board[9][9])
{
    for(int r=0;r<9;r++)
    {
        for(int c=0;c<9;c++)
        {
            if(Board[r][c]=='-')
            {
                printmovementbox(r,c,40/16,80/16,-37,20);
            }
            else
           {
               if((r+c)%2==0)
              {
               printmovementbox(r,c,40/16,80/16,-37,255);
              }
          else
           {
               printmovementbox(r,c,40/16,80/16,-37,160);
           }
           }
        }
    }
}
bool validdrropingco (int r,int c,int k,int l,char Board[9][9])
{
     if((Board[k][l]=='-') || (Board[k][k]>'a' && Board[r][c]<'z'))
     return true;
     return false;
}
//void makingendco(char Drop, int &rows,int  &cols,int &k,int &l,int Turn)
//{
//    switch(Drop)
//    {
//        case 'P':
//        case 'p':
//        if(Turn==0)
//        {
//            k=rows+1;
//        l=cols;
//        }
//        if(Turn==1)
//        {
//            k=rows-1;
//        l=cols;
//        }
//        break;
//        case 'L':
//        case 'l':
//        if(Turn==0)
//        {
//            k=rows+1;
//        l=cols;
//        }
//        if(Turn==1)
//        {
//            k=rows-1;
//        l=cols;
//        }
//        break;
//        case 'n':
//        case 'N':
//        if(Turn==0)
//        {
//            k=rows+2;
//        l=cols+1;
//        }
//        if(Turn==1)
//        {
//            k=rows-2;
//        l=cols+1;
//        }
//        break;
//    }
//}
void removingdroppiece(int Turn,char player1array[20],char player2array[20],char Drop)
{
   if(Turn==0)
   {
      for(int i=0;i<20;i++)
      {
          if(player1array[i]==Drop)
          {
              player1array[i]=' -';
              return;
          }
      }
   }
   if(Turn==1)
   {
       for(int i=0;i<20;i++)
      {
          if(player2array[i]==Drop)
          {
              player2array[i]='-';
              return;
          }
      }
   }
}
void movingdroppiece(char Board[9][9],char Drop,int Turn,char player1array[20],char player2array[20])
{
bool check;

    int rows,cols,answer,k,l;
//getch();
//gotoRowCol(20,25);
//color(251);
//cout<<"Where You wanna move Piece"<<endl;
///////

do
{
    check=true;
getch();
    rows=0,cols=0;
  if(kbhit())
  {
do
{
    if((rows+cols)%2==0)
{
    printmovementbox(rows,cols,40/16,80/16,-37,255);
}
else
{
    printmovementbox(rows,cols,40/16,80/16,-37,160);
}
gotoRowCol(22,25);
color(251);
cout<<"Rows "<<rows<<" "<<"Cols "<<cols<<" ";

      answer=getch();

      //////

      ///////


      if(answer==224)
      {
          answer=getch();
          if(answer==72)
          {
              rows--;
          }
          if(answer==80)
          {
             rows++;
          }
          if(answer==75)
          {
              cols--;
          }
          if(answer==77)
          {
              cols++;
          }
      }
      if(rows>8)
      {
          rows=0;
      }
      if(cols>8)
      {
          cols=0;
      }
      /////
      if(rows<0)
      {
         rows=8;
      }
      if(cols<0)
      {
          cols=8;
      }


  printmovementbox(rows,cols,40/16,80/16,-37,254);
}
  while(answer!=13);
  }
   //makingendco(Drop,rows,cols,k,l,Turn);
//   if(Turn==0)
//   {
       if((Board[rows][cols]>='A' && Board[rows][cols]<='Z')||(Board[rows][cols]>='a' && Board[rows][cols]<='z'))
       check=false;
  // }
//   if(Turn==1)
//   {
//       if(Board[rows][cols]>='a' && Board[rows][cols]<='z')
//       check=false;
//   }
}
while(check==false);
Board[rows][cols]=Drop;
removingdroppiece(Turn,player1array,player2array,Drop);
/////////
}
void callingfunction(int r,int c,int Turn,char Board[9][9],char Drop)
{
    int k,l;
    int ec[2];
    int sc[2];
    switch(Drop)
    {
        case 'P':
        case 'p':
        if(Turn==0)
        {
            k=r+1;
        l=c;
        }
        if(Turn==1)
        {
            k=r-1;
        l=c;
        }
        if(ispawnmove(Board,sc,ec,Turn,r,c,k,l)==true)
        {
                if(validdrropingco (r,c,k,l,Board)==true)
                printmovementbox(r,c,40/16,80/16,-37,20);
        }
            else
           {
               if((r+c)%2==0)
              {
               printmovementbox(r,c,40/16,80/16,-37,255);
              }
          else
           {
               printmovementbox(r,c,40/16,80/16,-37,160);
           }
           }
           break;

        case 'L':
        case 'l':
        if(Turn==0)
        {
            k=r+1;
        l=c;
        }
        if(Turn==1)
        {
            k=r-1;
        l=c;
        }
        if(islancemove(r,c,k,l,Turn)==true)
        {
            //if((Board[k][l]=='-') || (Board[k][k]>'a' && Board[r][c]<'z'))
              if(validdrropingco (r,c,k,l,Board)==true)
              printmovementbox(r,c,40/16,80/16,-37,20);
        }
            else
           {
               if((r+c)%2==0)
              {
               printmovementbox(r,c,40/16,80/16,-37,255);
              }
          else
           {
               printmovementbox(r,c,40/16,80/16,-37,160);
           }
           }
           break;

        case 'n':
        case 'N':
        if(Turn==0)
        {
            k=r+2;
        l=c+1;
        }
        if(Turn==1)
        {
            k=r-2;
        l=c+1;
        }
         if(knightmove(r,c,k,l,Turn)==true)
         {

                 //if((Board[k][l]=='-') || (Board[k][k]>'a' && Board[r][c]<'z'))
                if(validdrropingco (r,c,k,l,Board)==true)
                printmovementbox(r,c,40/16,80/16,-37,20);
         }
            else
           {
               if((r+c)%2==0)
              {
               printmovementbox(r,c,40/16,80/16,-37,255);
              }
          else
           {
               printmovementbox(r,c,40/16,80/16,-37,160);
           }
           }
           break;

    }

}
void avilablemovemetsfor_pln(char Board[9][9],int Turn,char Drop)
{

       for(int r=0;r<9;r++)
       {
           for(int c=0;c<9;c++)
           {
               if(Board[r][c]=='-')
               {
//               for(int k=0;k<9;k++)
//               {
//                   for(int l=0;l<9;l++)
//                   //{
                       callingfunction(r,c,Turn,Board,Drop);
                   //}
               }
               }
           }



}
void movementofpiece(int Turn,int Drop,char Board[9][9],char player1array[20],char player2array[20])
{
    switch(Drop)
    {
        case 'B':
        case 'r':
        case 'S':
        case 'g':
        case 'b':
        case 'R':
        case 's':
        case 'G':
        availablemovementsfor_brgs(Board);
        movingdroppiece(Board,Drop,Turn,player1array,player2array);
        break;
        case 'l':
        case 'n':
        case 'p':
        case 'L':
        case 'N':
        case 'P':
        avilablemovemetsfor_pln(Board,Turn,Drop);
        movingdroppiece(Board,Drop,Turn,player1array,player2array);
    }
}
void takingdropelements (char player1array[20],char player2array[20],int Turn,char Board[9][9])
{
    //bool check=false;
    char drop;
    if(Turn==0)
    {

        do
        {
            color(4);
        gotoRowCol(33,5);
        cout<<"Enter Droping Elemments"<<endl;
        cin>>drop;
        //validdropingpiece(player1array,player2array,Turn,check,drop);
        }
        while(validdropingpiece(player1array,player2array,Turn,drop)!=true);
movementofpiece(Turn,drop,Board,player1array,player2array);


    }
    if(Turn==1)
    {


        do
        {
             color(3);
        gotoRowCol(33,5);
        cout<<"Enter Droping Elemments"<<endl;
        cin>>drop;
        //validdropingpiece(player1array,player2array,Turn,check,drop);

        }
        while(validdropingpiece(player1array,player2array,Turn,drop)!=true);

movementofpiece(Turn,drop,Board,player1array,player2array);
    }
}
bool legalmovesaftercheck(int Startco[2],int Endco[2],char Board[9][9],char hold,int r,int c,int rr,int cc,int Turn,bool &checkmusibat,bool &gamewinning,bool &looser)
{
    hold=Board[rr][cc];
   int endhold=Board[r][c];
   printmove(Startco,Endco,Board,hold,r,c,rr,cc);
    checkking(Turn,Board,checkmusibat,gamewinning,looser);
    if(checkmusibat==false)
    {
         printmoveforcheck(Startco,Endco,Board,hold,rr,cc,r,c,endhold);
         return true;
    }
     if(checkmusibat==true)
    {
         printmoveforcheck(Startco,Endco,Board,hold,rr,cc,r,c,endhold);
         return false;
    }
}
void optionmenu()
{
    gotoRowCol(33,35);
    color(3);
    cout<<"Press N for New game !! S for SAVE "<<endl;
    gotoRowCol(34,35);
    cout<<"Press Z for UNDO"<<endl;
    gotoRowCol(35,35);
    cout<<"Press X for REDO"<<endl;

}
void startingmenu(char s,int rows,int cols,int &Turn,char Board[9][9],ofstream &savereplay,ifstream &loadreplay,string Players[2],gmenu &Start,game &usermarzi,int rd,int cd,int dropcols,int droprows,char holdarray[9][9],char player1array[20],char player2array[20])
{
    for(int i=0;i<20;i++)
    {
        player1array[i]='-';
        player2array[i]='-';
    }
menu(s);
getch();
if(kbhit())
{
start (usermarzi,Start,s);
}
//cout<<"Enter 1 for New game "<<endl;
//cout<<endl;
//cout<<"Enter 2 for Load game "<<endl;
//cin>>Start;
//savingboaddrooping(holdarray);
if(Start==LOAD)
{
loadinggame(Board,Turn,Players,player1array,player2array);
Turnchange(Turn);
savereplay.open("replay.txt");

}
if(Start==NEW)
{
intializegame(Board,Turn,Players);
savereplay.open("replay.txt");
//savingboaddrooping(holdarray);
}
color(0);
clearingscrean();
loading();
optionmenu();
}
void dropingelements(char Board[9][9],int Turn,int r,int c,char player1array[20],char player2array[20],int &dropingcounter1,int &dropingcounter2,char drop)
{
    //char drop=Board[r][c];
    if(Turn==0)
    {

        if(drop>'a' && drop<'z')
        {
               drop=toupper(drop);
        player1array[dropingcounter1]=drop;
        dropingcounter1++;
        }


    }
    if(Turn==1)
    {
        if(drop>'A' && drop<'Z')
       {
            drop=tolower(drop);
        player2array[dropingcounter2]=drop;
        dropingcounter2++;
       }
    }
}
void stalemate(int Turn,char Board[9][9],bool &checkmusibat,bool &gamewinner,bool &looser,bool &draw)
{
 //checkking(Turn,Board,checkmusibat,gamewinner,looser);
if(Alllegalmoves(Turn,Board,checkmusibat,gamewinner,looser)==false && checkking(Turn,Board,checkmusibat,gamewinner,looser)==false)
{
    draw=true;
//    gamewinner=true;
//    looser=Turn+1%2;
}
else
{
    draw=false;
//    gamewinner=false;
}

}
//////
int main()
{

int Turn=0,Rows=40,Cols=80,r,c,rr,cc;
string Players [2];
char Board[9][9];
char holdarray[9][9];
int Startco[2];
int Endco[2];
int rd=Rows/16;
int cd=Cols/16;
int droprows=3;
int dropcols=57;
char drop;
char s=-37;
char hold;
int i=0;
int dropingcounter1=0,dropingcounter2=0;
int undo[50][2];
char player1[50][20];
char player2[50][20];
char player1array[20]={'-'};
char player2array[20]={'-'};
int redo[50][2];
gmenu Start=NEW;
bool gamedraw=false;
bool gamewinning=false,validaftercheck;
bool looser;
int kingmovecheck[8][2];
char Undoredo[50][9][9];
int Gamelavel=0,Safety=0;
ofstream savereplay;

ifstream loadreplay;

bool valid,checkmusibat=false;
game usermarzi=FIRST;
startingmenu(s,Rows,Cols,Turn,Board,savereplay,loadreplay,Players,Start,usermarzi,rd,cd,dropcols,droprows,holdarray,player1array,player2array);

if(Start==REPLAY)
{
    loadreplay.open("replay.txt");
    while(!loadreplay.eof())
    {




        loadingreplay(Board,Turn,Players,loadreplay);

        printboard(Board,Turn,Rows,Cols,Players,rd,cd,s,player1array,player2array,droprows,dropcols);
        Sleep1(200);
        if(kbhit())
        {
            int c=getch();
            if(c==13)
            //Turnchange(Turn);
            break;
        }
    }



}

savingreplay(Board,Turn,Players,savereplay);
savingsteps (Gamelavel,Safety,Undoredo,Turn,Board,player1,player2,player1array,player2array);


do
{



Turnchange(Turn);

printboard(Board,Turn,Rows,Cols,Players,rd,cd,s,player1array,player2array,droprows,dropcols);
optionmenu();

//checkdroping(Board,holdarray,droprows,dropcols,Turn,dropingcounter1,player1array,player2array,dropingcounter2);
checkking(Turn,Board,checkmusibat,gamewinning,looser);
//if(checkmusibat==true)
printdroping(player1array,player2array,Turn,droprows,dropcols);
if(checkmusibat==true)
checkmate(Turn,Board,checkmusibat,gamewinning,looser);
stalemate(Turn,Board,checkmusibat,gamewinning,looser,gamedraw);
if(gamewinning==true)
break;
if(gamedraw==true)
break;
//getch();
//if(kbhit())
//{
    char ss=getch();
    if(ss==-32)
    getch();

    switch(ss)
    {
        case 'S':
        case 's':
        {
         savinggame(Board,Turn,Players,player1array,player2array);
         break;
        }

        case 'z':
        case 'Z':
         {
             doingundo(Gamelavel,Undoredo,Turn,Board,player1,player2,player1array,player2array);
         continue;
         }

        case 'x':
        case 'X':
        {
            doingredo(Gamelavel,Safety,Undoredo,Turn,Board,player1,player2,player1array,player2array);
         continue;
        }
        case 'n':
        case 'N':
        {
            clearingscrean();
            startingmenu(s,Rows,Cols,Turn,Board,savereplay,loadreplay,Players,Start,usermarzi,rd,cd,dropcols,droprows,holdarray,player1array,player2array);
            printboard(Board,Turn,Rows,Cols,Players,rd,cd,s,player1array,player2array,droprows,dropcols);
          break;
        }
        case 'd':
        case 'D':
        {
       takingdropelements (player1array,player2array,Turn,Board);
   Turnchange(Turn);
  printboard(Board,Turn,Rows,Cols,Players,rd,cd,s,player1array,player2array,droprows,dropcols);
//    //checkdroping(Board,holdarray,droprows,dropcols,Turn,dropingcounter1,player1array,player2array,dropingcounter2);
   printdroping(player1array,player2array,Turn,droprows,dropcols);


    break;
        }

    }
//}
//if(getch()=='S' || getch()=='s')
//      {
//         savinggame(Board,Turn,Players);
//
//      }
// if(getch()=='z' || getch()=='Z')
//      {
//          doingundo(Gamelavel,Undoredo,Turn,Board);
//          continue;
//
//      }
//else if(getch()=='x' || getch()=='X')
//      {
//          doingredo(Gamelavel,Safety,Undoredo,Turn,Board);
//          continue;
//
//      }
// if(getch()=='D'|| getch()=='d')
//{
//    takingdropelements (player1array,player2array,Turn,Board);
//      Turnchange(Turn);
//    printboard(Board,Turn,Rows,Cols,Players,rd,cd,s,player1array,player2array,droprows,dropcols);
//    checkdroping(Board,holdarray,droprows,dropcols,Turn,dropingcounter1,player1array,player2array,dropingcounter2);
//    printdroping(player1array,player2array,Turn,droprows,dropcols);
//
//}



 takeinput(Startco,Board,Turn,hold,rr,cc,Players,undo,i,Undoredo,Gamelavel,checkmusibat);
validater_Sc(Startco,Board,Turn,hold,rr,cc,checkmusibat);
Movepiece(Endco,Startco,Board,Turn,r,c,Players,Undoredo,Gamelavel);
valid=validmovement(r,c,rr,cc,Startco,Endco,Board,Turn);
drop=Board[r][c];
hold=Board[rr][cc];
validaftercheck=legalmovesaftercheck(Startco,Endco,Board,hold,r,c,rr,cc,Turn,checkmusibat,gamewinning,looser);
if(valid==false || validaftercheck==false )
{
    Turnchange(Turn);
    continue;
}

dropingelements(Board,Turn,r,c,player1array,player2array,dropingcounter1,dropingcounter2,drop);
if(valid==true)
{


printmove(Startco,Endco,Board,hold,r,c,rr,cc);
promotion(Board,Turn,r);

}
savingreplay(Board,Turn,Players,savereplay);
savingsteps (Gamelavel,Safety,Undoredo,Turn,Board,player1,player2,player1array,player2array);





}
while(1);
if(gamewinning==true)
{


if(looser==0)
{
    color(251);
    gotoRowCol(36,2);
    cout<<endl;
    cout<<"Checkmate"<<endl;
    cout<<endl;
    cout<<Players[0]<<" "<<"Won The game"<<endl;
    getch();
}
if(looser==1)
{
    color(252);
    gotoRowCol(36,2);
    cout<<endl;
    cout<<"Checkmate"<<endl;
    cout<<endl;
    cout<<Players[1]<<" "<<"Won The game"<<endl;
    getch();
}
}
else
{
    color(252);
    gotoRowCol(36,2);
    cout<<endl;
    cout<<"Game Draw";
}
//if(looser==0)
//{
//    color(251);
//    gotoRowCol(36,2);
//    cout<<Players[0]<<" "<<"Won The game"<<endl;
//    getch();
//}
//else
//if(looser==1)
//{
//    color(252);
//    gotoRowCol(36,2);
//    cout<<Players[1]<<" "<<"Won The game"<<endl;
//    getch();
//}


    return 0;
}
