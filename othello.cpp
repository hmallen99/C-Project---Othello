#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <vector>

using namespace std;

COORD coord={0,0};

HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
WORD wOldColorAttrs;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class Piece{
    private:
        int color;
        int x;
        int y;
    public:
        Piece(){
            x=-1;
            y=-1;
            color=0;
        }
        int getX(){return x;}
        int getY(){return y;}
        int getColor(){return color;}
        void set(int xpos,int ypos,int co){
            x=xpos;
            y=ypos;
            color=co;
        }
        void set(int co){
            color=co;
        }
        void display();
};

class Board{
    private:
        Piece list[64];
        int x1,y1;
        int status;
        int bpieces;
        int wpieces;
        int winner;
        int d;
        vector<int> turns;
        int q;
        int inRange();
        int pieceAtLoc();
        int valid();
        int endGame();
        void flip();
        void display();
    public:
        Board(){
            list[0].set(4,4,1);
            list[1].set(4,5,2);
            list[2].set(5,5,1);
            list[3].set(5,4,2);
        }
        void execute();
};

void Piece::display(){
    if(color==1){
        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN);
        gotoxy(4*x+8,2*y+8);printf("O");
    }
    else if(color==2){
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN);
        gotoxy(4*x+8,2*y+8);printf("X");
    }
    SetConsoleTextAttribute ( h, wOldColorAttrs);
}

int Board::inRange(){
    if((x1>8)||(y1>8)||(x1<1)||(y1<1)){
        return 1;
    }
    else{
        return 0;
    }
}

int Board::pieceAtLoc(){
    int a=0;
    for(int i=0;i<64;i++){
        if((x1==list[i].getX())&&(y1==list[i].getY())){
            a++;
        }
    }
    return a;
}

int Board::valid(){
    int b=0;
    int c=0;
    int e[8]={0,0,0,0,0,0,0,0};
    for(int i=0;i<64;i++){
        if((x1-1==list[i].getX())&&(y1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[0]=1;
                b++;
            }
        }
        else if((x1+1==list[i].getX())&&(y1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[1]=1;
                b++;
            }
        }
        else if((x1==list[i].getX())&&(y1-1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[2]=1;
                b++;
            }
        }
        else if((x1==list[i].getX())&&(y1+1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[3]=1;
                b++;
            }
        }
        else if((x1-1==list[i].getX())&&(y1+1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[4]=1;
                b++;
            }
        }
        else if((x1+1==list[i].getX())&&(y1-1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[5]=1;
                b++;
            }
        }
        else if((x1+1==list[i].getX())&&(y1+1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[6]=1;
                b++;
            }
        }
        else if((x1-1==list[i].getX())&&(y1-1==list[i].getY())){
            if(status!=list[i].getColor()){
                e[7]=1;
                b++;
            }
        }
    }
    if(b>0){
        for(int j=2;j<8;j++){
            for(int i=0;i<64;i++){
                if((x1-j==list[i].getX())&&(y1==list[i].getY())&&(e[0]==1)){
                    if(status==list[i].getColor()){c++;}
                }
                else if((x1+j==list[i].getX())&&(y1==list[i].getY())&&(e[1]==1)){
                    if(status==list[i].getColor()){c++;}
                }
                else if((x1==list[i].getX())&&(y1-j==list[i].getY())&&(e[2]==1)){
                    if(status==list[i].getColor()){c++;}
                }
                else if((x1==list[i].getX())&&(y1+j==list[i].getY())&&(e[3]==1)){
                    if(status==list[i].getColor()){c++;}
                }
                else if((x1-j==list[i].getX())&&(y1+j==list[i].getY())&&(e[4]==1)){
                    if(status==list[i].getColor()){c++;}
                }
                else if((x1+j==list[i].getX())&&(y1-j==list[i].getY())&&(e[5]==1)){
                    if(status==list[i].getColor()){c++;}
                }
                else if((x1+j==list[i].getX())&&(y1+j==list[i].getY())&&(e[6]==1)){
                    if(status==list[i].getColor()){c++;}
                }
                else if((x1-j==list[i].getX())&&(y1-j==list[i].getY())&&(e[7]==1)){
                    if(status==list[i].getColor()){c++;}
                }
            }
        }
    }
    return c;
}

void Board::flip(){
    for(int i=0;i<64;i++){
            if((list[d].getX()-1==list[i].getX())&&(list[d].getY()==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()-m==list[j].getX())&&(list[d].getY()==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){
                                l++;
                            }
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()-k==list[n].getX())&&(list[d].getY()==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){
                                list[n].set(status);
                            }
                            list[i].set(status);
                        }
                    }
                }
            }
            if((list[d].getX()+1==list[i].getX())&&(list[d].getY()==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()+m==list[j].getX())&&(list[d].getY()==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){l++;}
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()+k==list[n].getX())&&(list[d].getY()==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){
                                list[n].set(status);
                            }
                            list[i].set(status);
                        }
                    }
                }
                }
            if((list[d].getX()-1==list[i].getX())&&(list[d].getY()-1==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()-m==list[j].getX())&&(list[d].getY()-m==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){l++;}
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()-k==list[n].getX())&&(list[d].getY()-k==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){
                                list[n].set(status);
                            }
                            list[i].set(status);
                        }
                    }
                }
                }
            if((list[d].getX()+1==list[i].getX())&&(list[d].getY()+1==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()+m==list[j].getX())&&(list[d].getY()+m==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){l++;}
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()+k==list[n].getX())&&(list[d].getY()+k==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){
                                list[n].set(status);
                            }
                            list[i].set(status);
                        }
                    }
                }
            }
            if((list[d].getX()==list[i].getX())&&(list[d].getY()-1==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()==list[j].getX())&&(list[d].getY()-m==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){l++;}
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()==list[n].getX())&&(list[d].getY()-k==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){list[n].set(status);}
                            list[i].set(status);
                        }
                    }
                }
            }
            if((list[d].getX()==list[i].getX())&&(list[d].getY()+1==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()==list[j].getX())&&(list[d].getY()+m==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){l++;}
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()==list[n].getX())&&(list[d].getY()+k==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){list[n].set(status);}
                            list[i].set(status);
                        }
                    }
                }
            }
            if((list[d].getX()-1==list[i].getX())&&(list[d].getY()+1==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()-m==list[j].getX())&&(list[d].getY()+m==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){l++;}
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()-k==list[n].getX())&&(list[d].getY()+k==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){list[n].set(status);}
                            list[i].set(status);
                        }
                    }
                }
            }
            if((list[d].getX()+1==list[i].getX())&&(list[d].getY()-1==list[i].getY())){
                int l=2;
                int q=0;
                for(int m=2;m<8;m++){
                    for(int j=0;j<64;j++){
                        if((list[d].getX()+m==list[j].getX())&&(list[d].getY()-m==list[j].getY())){
                            if((status!=list[j].getColor())&&(q==0)){l++;}
                            else if(status==list[j].getColor()){q++;}
                        }
                    }
                }
                for(int n=0;n<64;n++){
                    for(int k=2;k<l+1;k++){
                        if((list[d].getX()+k==list[n].getX())&&(list[d].getY()-k==list[n].getY())&&(q>0)){
                            if(status!=list[n].getColor()){list[n].set(status);}
                            list[i].set(status);
                        }
                    }
                }
            }
    }
}

int Board::endGame(){
    int g=0;
    int p=0;
    int q=0;
    for(int i=0;i<64;i++){
        if(list[i].getColor()>0){
            g++;
        }
    }
    if(g==64){
        p++;
    }
    if((q>1)&&(turns[q]==turns[q-2])){
        p++;
    }
    return p;
}

void Board::execute(){
    status=list[0].getColor();
    char repeat;
    d=0;
    int r=0;
    do{
        d++;
    }while(list[d].getColor()!=0);
    bpieces=0;
    wpieces=0;
    display();
    for(int i=0;i<64;i++){
        if(list[i].getColor()==1){wpieces++;}
        else if(list[i].getColor()==2){bpieces++;}
    }
    gotoxy(0,28);printf("O Pieces: ");
    cout<<wpieces;
    gotoxy(0,29);printf("X Pieces: ");
    cout<<bpieces;
    for(int i=0;i<64;i++){
            if(list[i].getColor()>0){
                r++;
            }
        }
    turns.push_back(r);
    q++;
    do{
            bpieces=0;
            wpieces=0;
            r=0;
            gotoxy(20,4);
            cout<<"Turn: Player ";
            if(status==1){cout<<"O";}
            else if(status==2){cout<<"X";}
            gotoxy(0,31);printf("Enter an x coord: |");
            cin>>x1;
            gotoxy(0,31);printf("                                ");
            gotoxy(0,31);printf("Enter a y coord:  |");
            cin>>y1;
            gotoxy(0,31);printf("                                ");
            for(int i=0;i<64;i++){
                if(list[i].getColor()>0){
                    r++;
                }
            }
            turns.push_back(r);
            if((x1!=0)&&(y1!=0)){
                if((inRange()==0)&&(pieceAtLoc()==0)&&(valid()>0)){
                    list[d].set(x1,y1,status);
                    flip();
                    for(int i=0;i<64;i++){
                        if(list[i].getColor()==1){wpieces++;}
                        else if(list[i].getColor()==2){bpieces++;}
                    }
                    gotoxy(0,28);printf("                                          ");
                    gotoxy(0,29);printf("                                          ");
                    gotoxy(0,28);printf("O Pieces: ");
                    cout<<wpieces;
                    gotoxy(0,29);printf("X Pieces: ");
                    cout<<bpieces;
                    display();
                    if(endGame()>0){
                            SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            gotoxy(22,6);printf("GAME OVER");
                    }
                    else if((bpieces==0)||(wpieces==0)){
                        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            gotoxy(22,6);printf("GAME OVER");
                            repeat='n';
                    }
                    else{
                        repeat='y';
                        gotoxy(0,31);printf("                                ");
                        d++;
                        if(status==1){status++;}
                        else if(status==2){status--;}
                    }
                }
                else if((inRange()>0)||(pieceAtLoc()>0)||(valid()==0)){
                    gotoxy(0,31);printf("Invalid Location, Try Again");
                    Sleep(1000);
                    gotoxy(0,31);printf("                                ");
                    repeat='y';
                }
            }
            else if((x1==0)&&(y1==0)){
                for(int i=0;i<64;i++){
                    if(list[i].getColor()==1){wpieces++;}
                    else if(list[i].getColor()==2){bpieces++;}
                }
                if(status==1){status++;}
                else if(status==2){status--;}
                if(endGame()==0){
                    repeat='y';
                }
                else if(endGame()>0){
                        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        gotoxy(22,6);printf("GAME OVER");
                        repeat='n';
                }
            }
            q++;
    }while(repeat=='y');
    SetConsoleTextAttribute ( h, FOREGROUND_GREEN| FOREGROUND_INTENSITY);
    if(bpieces>wpieces){
        for(int i=0;i<30;i++){
            gotoxy(12,29);
            cout<<"<------- WINNER!";
            Sleep(300);
            gotoxy(12,29);
            cout<<"                  ";
            Sleep(300);
        }
        gotoxy(12,29);
        cout<<"<------- WINNER!";
    }
    else if(wpieces>bpieces){
        for(int i=0;i<30;i++){
            gotoxy(12,28);
            cout<<"<------- WINNER!";
            Sleep(300);
            gotoxy(12,28);
            cout<<"                  ";
            Sleep(300);
        }
        gotoxy(12,28);
        cout<<"<------- WINNER!";
    }
    else if(bpieces==wpieces){
        for(int i=0;i<30;i++){
            gotoxy(12,29);
            cout<<"TIE!";
            gotoxy(12,28);
            cout<<"TIE!";
            Sleep(300);
            gotoxy(12,29);
            cout<<"        ";
            gotoxy(12,28);
            cout<<"        ";
            Sleep(300);
        }
        gotoxy(12,29);
        cout<<"TIE!";
        gotoxy(12,28);
        cout<<"TIE!";
    }
    gotoxy(0,31);printf("                                        ");
    SetConsoleTextAttribute ( h, wOldColorAttrs);
}

void Board::display(){
    SetConsoleTextAttribute ( h, FOREGROUND_GREEN | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
    gotoxy(8,7);printf("|-----------------------------------|");
    gotoxy(8,8);printf("|   1   2   3   4   5   6   7   8   |");
    cout<<endl;
    for(int i=0;i<8;i++){
        gotoxy(10,2*i+9);printf("---------------------------------");
        gotoxy(8,2*i+9);cout<<"| ";
        gotoxy(8,2*i+10);cout<<"| ";
        gotoxy(43,2*i+9);cout<<" |";
        gotoxy(9,2*i+10);cout<<i+1;
        gotoxy(10,2*i+10);printf("|   |   |   |   |   |   |   |   |");
        cout<<i+1<<"|";
    }
    gotoxy(10,25);printf("---------------------------------");
    gotoxy(8,25);cout<<"| ";
    gotoxy(43,25);cout<<" |";
    gotoxy(8,26);printf("|   1   2   3   4   5   6   7   8   |");
    gotoxy(8,27);printf("|-----------------------------------|");
    for(int i=0;i<64;i++){
        list[i].display();
    }
}

int main(){
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    Board bOut;
    bOut.execute();
    return 0;
}
