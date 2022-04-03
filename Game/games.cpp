#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<ctime>
#include<cstdio>
#include<conio.h>
#include<windows.h>
using namespace std;
#define Forij(x) for(int i=1;i<=x;i++)for(int j=1;j<=x;j++)
#define N 25
int fx[4][2]= {{1,1},{1,0},{0,1},{1,-1}};
int Q,GG;
string C[20]= {"●","○","﹢","═","║","╔","╚","╗","╝","·"}; //╋
void color(int a) { //颜色函数
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void gotoxy(int x,int y) {
    COORD pos;
    pos.X=2*x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
struct Gomoku {
    int m[50][50],nx,ny;
    void reset() {
        system("cls");
        memset(m,-1,sizeof(m));
        color(7);
        for (int i=1; i<=N; i++) {
            gotoxy(0,i);
            cout<<C[4];
            gotoxy(N+1,i);
            cout<<C[4];
            gotoxy(i,0);
            cout<<C[3];
            gotoxy(i,N+1);
            cout<<C[3];
        }
        gotoxy(0,0);
        cout<<C[5];
        gotoxy(0,N+1);
        cout<<C[6];
        gotoxy(N+1,0);
        cout<<C[7];
        gotoxy(N+1,N+1);
        cout<<C[8];
        color(3);
        Forij(N) {
            gotoxy(i,j);
            cout<<C[2];
        }
        nx=ny=N/2+1;
        gotoxy(nx,ny);
    }

    void _drop(int x,int i,int j) {
        m[i][j]=x;
        gotoxy(i,j);
        color(15);
        cout<<C[x];
    }

    int check() {
        Forij(N) {
            for (int Fx=0,tmp,lst,xx,yy; Fx<4; Fx++) if(m[i][j]!=-1) {
                    xx=i,yy=j,tmp=0,lst=m[i][j];
                    for (int k=1; k<=5; k++) {
                        if (xx>N || yy>N) break;
                        if (m[xx][yy]==(lst^1)) {
                            break;
                        }
                        if (m[xx][yy]==lst) tmp++;
                        xx+=fx[Fx][0],yy+=fx[Fx][1];
                    }
                    if (tmp==5) {
                        return lst;
                    }
                }
        }
        return -1;
    }
    int arnd(int x,int y) {
        int cnt=0;
        for (int i=x-1; i<=x+1; i++) if (i>0 && i<=N)
                for (int j=y-1; j<=y+1; j++) if (j>0 && j<=N)
                        if (m[i][j]>-1) cnt++;
    }
    void get_val(int x,int y,int &val) {
        val=0;
        Forij(N) {
            for (int Fx=0,tmp,tk,xx,yy; Fx<4; Fx++) {
                xx=i,yy=j,tmp=tk=0;
                for (int k=1; k<=5; k++) {
                    if (xx>N || yy>N) {
                        tmp=0;
                        break;
                    }
                    if (m[xx][yy]==(x^1)) {
                        tmp=0;
                        break;
                    }
                    if (m[xx][yy]==x) tmp++,tk+=(1<<(k-1));
                    xx+=fx[Fx][0],yy+=fx[Fx][1];
                }
                switch(tmp) {
                    case 5:
                        val+=800000000;
                        break;
                    case 4:
                        val+=1000+350*y;
                        break;
                    case 3:
                        val+=(tk==14)?(300+600*y):(300+200*y);
                        break;
                    case 2:
                        val+=3+2*y;
                        break;
                    case 1:
                        val+=1+y;
                        break;
                }
            }
        }
    }

    void AI(int x) {
        int best,brnd,bi,bj,v1,v2,kkk;
        best=-2147483647;
        brnd=-2147483647;
        Forij(N) if (m[i][j]==-1) {
            m[i][j]=x;
            get_val(x,10,v1); //gotoxy(N+5,N/2);printf("%d                ",v1);
            get_val(x^1,80,v2); //gotoxy(N+5,N/2+1);printf("%d             ",v2);
            if (v1-v2>best) bi=i,bj=j,best=v1-v2;
            if (v1-v2==best)
                if ((kkk=arnd(i,j))>brnd)
                    brnd=kkk,bi=i,bj=j;
            m[i][j]=-1;
        }
        _drop(x,bi,bj);
    }

    void HM(int x) {
        char ch=getch();
        for (;; ch=getch()) {
            if (ch=='w') {
                if (ny>1) ny--;
            } else if (ch=='s') {
                if (ny<N) ny++;
            } else if (ch=='a') {
                if (nx>1) nx--;
            } else if (ch=='d') {
                if (nx<N)nx++;
            } else if (m[nx][ny]==-1) {
                _drop(x,nx,ny);
                return;
            }
            gotoxy(nx,ny);
        }
    }
} A;
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string>
using namespace std;
typedef struct Frame {
    COORD position[2];
    int flag;
} Frame;
void SetPos(COORD a) {
    HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out, a);
}
void SetPos(int i, int j) {
    COORD pos= {i, j};
    SetPos(pos);
}
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//把第y行，[x1, x2) 之间的坐标填充为 ch
void drawRow(int y, int x1, int x2, char ch) {
    SetPos(x1,y);
    for(int i = 0; i <= (x2-x1); i++) cout<<ch;
}

//在a, b 纵坐标相同的前提下，把坐标 [a, b] 之间填充为 ch
void drawRow(COORD a, COORD b, char ch) {
    if(a.Y == b.Y) drawRow(a.Y, a.X, b.X, ch);
    else {
        SetPos(0, 25);
        cout<<"error code 01：无法填充行，因为两个坐标的纵坐标(x)不相等";
        system("pause");
    }
}

//把第x列，[y1, y2] 之间的坐标填充为 ch
void drawCol(int x, int y1, int y2, char ch) {
    int y=y1;
    while(y!=y2+1) {
        SetPos(x, y);
        cout<<ch;
        y++;
    }
}

//在a, b 横坐标相同的前提下，把坐标 [a, b] 之间填充为 ch
void drawCol(COORD a, COORD b, char ch) {
    if(a.X == b.X) drawCol(a.X, a.Y, b.Y, ch);
    else {
        SetPos(0, 25);
        cout<<"error code 02：无法填充列，因为两个坐标的横坐标(y)不相等";
        system("pause");
    }
}

//左上角坐标、右下角坐标、用row填充行、用col填充列
void drawFrame(COORD a, COORD  b, char row, char col) {
    drawRow(a.Y, a.X+1, b.X-1, row);
    drawRow(b.Y, a.X+1, b.X-1, row);
    drawCol(a.X, a.Y+1, b.Y-1, col);
    drawCol(b.X, a.Y+1, b.Y-1, col);
}

void drawFrame(int x1, int y1, int x2, int y2, char row, char col) {
    COORD a= {x1, y1};
    COORD b= {x2, y2};
    drawFrame(a, b, row, col);
}

void drawFrame(Frame frame, char row, char col) {
    COORD a = frame.position[0];
    COORD b = frame.position[1];
    drawFrame(a, b, row, col);
}

void drawPlaying() {
    drawFrame(0, 0, 48, 24, '=', '|');//    draw map frame;
    drawFrame(49, 0, 79, 4, '-', '|');//        draw output frame
    drawFrame(49, 4, 79, 9, '-', '|');//        draw score frame
    drawFrame(49, 9, 79, 20, '-', '|');//   draw operate frame
    drawFrame(49, 20, 79, 24, '-', '|');//  draw other message frame
    SetPos(52, 6);
    cout<<"得分：";
    SetPos(52, 7);
    cout<<"称号：";
    SetPos(52,10);
    cout<<"操作方式：";
    SetPos(52,12);
    cout<<"  a,s,d,w 控制战机移动。";
    SetPos(52,14);
    cout<<"  p 暂停游戏。";
    SetPos(52,16);
    cout<<"  e 退出游戏。";
    SetPos(52,18);
    cout<<"  k 发射火箭。";
}

//在[a, b)之间产生一个随机整数
int random(int a, int b) {
    int c=(rand() % (a-b))+ a;
    return c;
}

//在两个坐标包括的矩形框内随机产生一个坐标
COORD random(COORD a, COORD b) {
    int x=random(a.X, b.X);
    int y=random(a.Y, b.Y);
    COORD c= {x, y};
    return c;
}

bool  judgeCoordInFrame(Frame frame, COORD spot) {
    if(spot.X>=frame.position[0].X)
        if(spot.X<=frame.position[1].X)
            if(spot.Y>=frame.position[0].Y)
                if(spot.Y<=frame.position[0].Y)
                    return true;
    return false;
}

void printCoord(COORD a) {
    cout    <<"( "<<a.X<<" , "<<a.Y<<" )";
}

void printFrameCoord(Frame a) {
    printCoord(a.position[0]);
    cout    <<" - ";
    printCoord(a.position[1]);
}

int drawMenu() {
    SetPos(30, 1);
    cout<<"Plane War";
    drawRow(3, 0, 79, '-');
    drawRow(5, 0, 79, '-');
    SetPos(28, 4);
    cout<<"w 和 s 选择， k 确定";
    SetPos(15, 11);
    cout<<"1. 简单的敌人";
    SetPos(15, 13);
    cout<<"2. 冷酷的敌人";
    drawRow(20, 0, 79, '-');
    drawRow(22, 0, 79, '-');
    SetPos(47, 11);
    cout<<"简单的敌人：";
    SetPos(51, 13);
    cout<<"简单敌人有着较慢的移动速度。";
    int j=11;
    cout<<">>";
    while(1) {
        if( _kbhit() ) {
            char x=_getch();
            switch (x) {
                case 'w' : {
                    if( j == 13) {
                        SetPos(12, j);
                        cout<<"　";
                        j = 11;
                        SetPos(12, j);
                        cout<<">>";
                        SetPos(51, 13);
                        cout<<"　　　　　　　　　　　　";
                        SetPos(47, 11);
                        cout<<"简单的敌人：";
                        SetPos(51, 13);
                        cout<<"简单的敌人有着较慢的移动速度。";
                    }
                    break;
                }
                case 's' : {
                    if( j == 11 ) {
                        SetPos(12, j);
                        cout<<"　";
                        j = 13;
                        SetPos(12, j);
                        cout<<">>";
                        SetPos(51, 13);
                        cout<<"　　　　　　　　　　　　　　";
                        SetPos(47, 11);
                        cout<<"冷酷的敌人：";
                        SetPos(51, 13);
                        cout<<"冷酷的敌人有着较快的移动速度。";
                    }
                    break;
                }
                case 'k' : {
                    if (j == 8) return 1;
                    else return 2;
                }
            }
        }
    }
}
/*================== the Game Class ==================*/

class Game {
    public:
        COORD position[10];
        COORD bullet[10];
        Frame enemy[8];
        int score;
        int rank;
        int rankf;
        string title;
        int flag_rank;

        Game ();

        //初始化所有
        void initPlane();
        void initBullet();
        void initEnemy();

        //初始化其中一个
        //void initThisBullet( COORD );
        //void initThisEnemy( Frame );

        void planeMove(char);
        void bulletMove();
        void enemyMove();

        //填充所有
        void drawPlane();
        void drawPlaneToNull();
        void drawBullet();
        void drawBulletToNull();
        void drawEnemy();
        void drawEnemyToNull();

        //填充其中一个
        void drawThisBulletToNull( COORD );
        void drawThisEnemyToNull( Frame );

        void Pause();
        void Playing();
        void judgePlane();
        void judgeEnemy();

        void Shoot();

        void GameOver();
        void printScore();
};

Game::Game() {
    initPlane();
    initBullet();
    initEnemy();
    score = 0;
    rank = 25;
    rankf = 0;
    flag_rank = 0;
}

void Game::initPlane() {
    COORD centren= {39, 22};
    position[0].X=position[5].X=position[7].X=position[9].X=centren.X;
    position[1].X=centren.X-2;
    position[2].X=position[6].X=centren.X-1;
    position[3].X=position[8].X=centren.X+1;
    position[4].X=centren.X+2;
    for(int i=0; i<=4; i++)
        position[i].Y=centren.Y;
    for(int i=6; i<=8; i++)
        position[i].Y=centren.Y+1;
    position[5].Y=centren.Y-1;
    position[9].Y=centren.Y-2;
}

void Game::drawPlane() {
    for(int i=0; i<9; i++) {
        SetPos(position[i]);
        if(i!=5)
            cout<<"O";
        else if(i==5)
            cout<<"|";
    }
}

void Game::drawPlaneToNull() {
    for(int i=0; i<9; i++) {
        SetPos(position[i]);
        cout<<" ";
    }
}

void Game::initBullet() {
    for(int i=0; i<10; i++)
        bullet[i].Y = 30;
}

void Game::drawBullet() {
    for(int i=0; i<10; i++) {
        if( bullet[i].Y != 30) {
            SetPos(bullet[i]);
            cout<<"^";
        }
    }
}

void Game::drawBulletToNull() {
    for(int i=0; i<10; i++)
        if( bullet[i].Y != 30 ) {
            COORD pos= {bullet[i].X, bullet[i].Y+1};
            SetPos(pos);
            cout<<" ";
        }
}

void Game::initEnemy() {
    COORD a= {1, 1};
    COORD b= {45, 15};
    for(int i=0; i<8; i++) {
        enemy[i].position[0] = random(a, b);
        enemy[i].position[1].X = enemy[i].position[0].X + 3;
        enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
    }
}

void Game::drawEnemy() {
    for(int i=0; i<8; i++)
        drawFrame(enemy[i].position[0], enemy[i].position[1], '-', '|');
}

void Game::drawEnemyToNull() {
    for(int i=0; i<8; i++) {
        drawFrame(enemy[i].position[0], enemy[i].position[1], ' ', ' ');
    }
}

void Game::Pause() {
    SetPos(61,2);
    cout<<"               ";
    SetPos(61,2);
    cout<<"暂停中...";
    char c=_getch();
    while(c!='p')
        c=_getch();
    SetPos(61,2);
    cout<<"         ";
}

void Game::planeMove(char x) {
    if(x == 'a')
        if(position[1].X != 1)
            for(int i=0; i<=9; i++)
                position[i].X -= 2;

    if(x == 's')
        if(position[7].Y != 23)
            for(int i=0; i<=9; i++)
                position[i].Y += 1;

    if(x == 'd')
        if(position[4].X != 47)
            for(int i=0; i<=9; i++)
                position[i].X += 2;

    if(x == 'w')
        if(position[5].Y != 3)
            for(int i=0; i<=9; i++)
                position[i].Y -= 1;
}

void Game::bulletMove() {
    for(int i=0; i<10; i++) {
        if( bullet[i].Y != 30) {
            bullet[i].Y -= 1;
            if( bullet[i].Y == 1 ) {
                COORD pos= {bullet[i].X, bullet[i].Y+1};
                drawThisBulletToNull( pos );
                bullet[i].Y=30;
            }

        }
    }
}

void Game::enemyMove() {
    for(int i=0; i<8; i++) {
        for(int j=0; j<2; j++)
            enemy[i].position[j].Y++;

        if(24 == enemy[i].position[1].Y) {
            COORD a= {1, 1};
            COORD b= {45, 3};
            enemy[i].position[0] = random(a, b);
            enemy[i].position[1].X = enemy[i].position[0].X + 3;
            enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
        }
    }
}

void Game::judgePlane() {
    for(int i = 0; i < 8; i++)
        for(int j=0; j<9; j++)
            if(judgeCoordInFrame(enemy[i], position[j])) {
                SetPos(62, 1);
                cout<<"坠毁";
                drawFrame(enemy[i], '+', '+');
                Sleep(1000);
                GameOver();
                break;
            }
}

void Game::drawThisBulletToNull( COORD c) {
    SetPos(c);
    cout<<" ";
}

void Game::drawThisEnemyToNull( Frame f ) {
    drawFrame(f, ' ', ' ');
}

void Game::judgeEnemy() {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 10; j++)
            if( judgeCoordInFrame(enemy[i], bullet[j]) ) {
                score += 5;
                drawThisEnemyToNull( enemy[i] );
                COORD a= {1, 1};
                COORD b= {45, 3};
                enemy[i].position[0] = random(a, b);
                enemy[i].position[1].X = enemy[i].position[0].X + 3;
                enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
                drawThisBulletToNull( bullet[j] );
                bullet[j].Y = 30;
            }
}

void Game::Shoot() {
    for(int i=0; i<10; i++)
        if(bullet[i].Y == 30) {
            bullet[i].X = position[5].X;
            bullet[i].Y = position[5].Y-1;
            break;
        }
}

void Game::printScore() {
    if(score == 120 && flag_rank == 0) {
        rank -= 3;
        flag_rank = 1;
    }

    else if( score == 360 && flag_rank == 1) {
        rank -= 5;
        flag_rank = 2;
    } else if( score == 480 && flag_rank == 2) {
        rank -= 5;
        flag_rank = 3;
    }
    int x=rank/5;
    SetPos(60, 6);
    cout<<score;
    if( rank!=rankf ) {
        SetPos(60, 7);
        if( x == 4)
            title="初级飞行员";
        else if( x == 3)
            title="中级飞行员";
        else if( x == 2)
            title="高级飞行员";
        else if( x == 1 )
            title="王牌飞行员";
        cout<<title;
    }
    rankf = rank;
}

void Game::Playing() {
    //HANDLE MFUN;
    //MFUN= CreateThread(NULL, 0, MusicFun, NULL, 0, NULL);

    drawEnemy();
    drawPlane();

    int flag_bullet = 0;
    int flag_enemy = 0;

    while(1) {
        Sleep(8);
        if(_kbhit()) {
            char x = _getch();
            if ('a' == x || 's' == x || 'd' == x || 'w' == x) {
                drawPlaneToNull();
                planeMove(x);
                drawPlane();
                judgePlane();
            } else if ('p' == x)
                Pause();
            else if( 'k' == x)
                Shoot();
            else if( 'e' == x) {
                //CloseHandle(MFUN);
                GameOver();
                break;
            }

        }
        /* 处理子弹 */
        if( 0 == flag_bullet ) {
            bulletMove();
            drawBulletToNull();
            drawBullet();
            judgeEnemy();
        }
        flag_bullet++;
        if( 5 == flag_bullet )
            flag_bullet = 0;

        /* 处理敌人 */
        if( 0 == flag_enemy ) {
            drawEnemyToNull();
            enemyMove();
            drawEnemy();
            judgePlane();
        }
        flag_enemy++;
        if( flag_enemy >= rank )
            flag_enemy = 0;

        /* 输出得分 */
        printScore();
    }
}

void Game::GameOver() {
    system("cls");
    COORD p1= {28,9};
    COORD p2= {53,15};
    drawFrame(p1, p2, '=', '|');
    SetPos(36,12);
    string str="Game Over!";
    for(int i=0; i<str.size(); i++) {
        Sleep(80);
        cout<<str[i];
    }
    Sleep(1000);
    system("cls");
    drawFrame(p1, p2, '=', '|');
    SetPos(31, 11);
    cout<<"击落敌机："<<score/5<<" 架";
    SetPos(31, 12);
    cout<<"得　　分："<<score;
    SetPos(31, 13);
    cout<<"获得称号："<<title;
    SetPos(30, 16);
    Sleep(1000);
    cout<<"继续？ 是（y）| 否（n）";
as:
    char x=_getch();
    if (x == 'n')
        exit(0);
    else if (x == 'y') {
        system("cls");
        Game game;
        int a = drawMenu();
        if(a == 2)
            game.rank = 20;
        system("cls");
        drawPlaying();
        game.Playing();
    } else goto as;
}
#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int s;
class Guess {
    private:
        int n;
    public :
        Guess() {
            srand(time(0));
            n = rand() % 1000 + 1;
        }
        void guess() {
            int m;
            while (true) {
                cout << "请猜:" << endl;
                cin >> m;
                if (m > n) {
                    cout << "大了" << endl;
                    s++;
                } else if (m < n) {
                    cout << "小了" << endl;
                    s++;
                } else {
                    cout << "对了" << endl;
                    s++;
                    cout<<"共猜了"<<s<<"次"<<endl;
                    break;//exit(0);
                }
            }
        }
};

int main(int argc, char *argv[]) {
    system("title 游戏世界 6.4版本");
    system("color b9");
    int n,m;
    bool c[100005];
    int a,b,d,e,f,g,i; int k;
    system("date /T");
    system("TIME /T");
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    for(i=1; i<=100000000; i++) {

    };
    cout<<"                                  游"; 
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"戏";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"世";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"界";
        for(i=1; i<=100000000; i++) {

    }
    Sleep(1000);
    system("cls");
    system("color b9");
    system("date /T");
    system("TIME /T");
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"欢";
    for(i=1; i<=100000000; i++) {

    }
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    cout<<"迎";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"来";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"到";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"游";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"戏";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"世";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"界";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"~";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"~"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"一，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"五";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"子";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"棋";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"（";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"1";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"二，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"打";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"飞";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"机";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"（";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"2";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
        for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"三，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"猜";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"数";
    for(i=1; i<=10000000; i++) {

    }
    cout<<"(";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"3";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
        for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"四，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"关";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"机";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"程";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"序";
    for(i=1; i<=10000000; i++) {

    }
    cout<<"(";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"4";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    cin>>n;
    if(n==1) {
        {
            for (;;) {
                A.reset();
                for (GG=-1;;) {
                    gotoxy(A.nx,A.ny);
                    A.HM(0);
                    GG=A.check();
                    if (GG>-1) break;
                    A.AI(1);
                    GG=A.check();
                    if (GG>-1) break;
                }
                gotoxy(5,N+3);
                if (GG==0) printf("AI_1 win!");
                if (GG==1) printf("AI_2 wins!");
                while (kbhit()) getch();
                Sleep(500);
                gotoxy(5,N+3);
                printf("Press anything to continue.");
                getch();
            }
        }
    }
    if(n==2) {
        cout << string(13, '\n');
        cout << string(50, ' ') << "Game Loading" << endl << ".";
        Sleep(500);
        cout << "\t.";
        Sleep(500);
        cout << "\t\t.";
        Sleep(500);
        cout << "\t\t\t.";
        Sleep(500);
        cout << "\t\t\t.";
        Sleep(500);
        cout << "\t\t.";
        Sleep(500);
        cout << "\t\t.";
        Sleep(500);
        cout << "\t.";
        Sleep(2000);
        system("cls");
        //游戏准备
        srand((int)time(0));    //随机种子
        HideCursor();   //隐藏光标

        Game game;
        int a = drawMenu();
        if(a == 2)
            game.rank = 20;
        system("cls");
        drawPlaying();
        game.Playing();
    }
    if(n==3) {
        system("color b5");
        cout<<"猜数 3.2\n";
        srand(time(NULL));
        cout<<"==============================================================\n几人猜数（只支持100000人以内）？？";
        cin>>n;
        cout<<"==============================================================\n0~几？？";
        cin>>m;
        for(;;) {
            cout<<"==============================================================\n开始！！！";
            int x=rand()%(m+1),y,h=0,e=m,t=rand()%n;
            bool hh=1,ee=1;
            do {
                cout<<"\n==============================================================\n";
                cout<<h<<"~"<<e<<endl;
                ++t;
                t-=t>n?n:0;
                if(!c[t])
                    cout<<t<<"号猜(电脑帮猜？输-1 设置TA为电脑？输-2)",cin>>y;
                if(y==-2)
                    c[t]=1;
                if(y==-1||c[t]) {
                    y=(h+e)/2;
                    cout<<"帮"<<t<<"号猜猜成"<<y<<endl;
                    if(y==x)
                        break;
                    if(y>x) {
                        cout<<"大了";
                        e=y;
                        continue;
                    }
                    if(y<x) {
                        cout<<"小了";
                        h=y;
                        continue;
                    }
                }
                if(y<=h||y>=e) {
                    cout<<"浪费机会！！！";
                    continue;
                    if(!h&&!y)
                        if(hh)
                            hh=0;
                        else {
                            cout<<"浪费机会！！！";
                            continue;
                        }
                    if(e==m&&y==m)
                        if(ee)
                            ee=0;
                        else {
                            cout<<"浪费机会！！！";
                            continue;
                        }
                }
                if(y>x) {
                    cout<<"大了";
                    e=y;
                }
                if(y<x) {
                    cout<<"小了";
                    h=y;
                }
            } while(x!=y);
            cout<<t<<"号赢了！！！\n==============================================================\n再来一局吗？\ny/n\n";
            char a;
            a=getch();
            if(a=='n'||a=='N')
                break;
        }
        getchar();
        cout<<"==============================================================\nbyebye!\n==============================================================\n双击任意键结束，单机空格关机！";
        char a=getch();
        if(a==' ') {
            cout<<"\n确定吗？？确定点空格一下，否则双击任意键结束。";
            a=getch();
            if(a==' ')
                system("shutdown -s -t 0");
        }
    }
    if(n==4) {
        char cmd[20]="shutdown -s -t ";

        char t[5]="0";

        int c;
        system("cls");
        system("title C语言关机程序");  //设置cmd窗口标题

        system("color f0");  //可以写成 red 调出颜色组

        system("date /T");

        system("TIME /T");

        printf("----------- C语言关机程序 -----------\n");

        printf("1.实现10分钟内的定时关闭计算机\n");

        printf("2.立即关闭计算机\n");

        printf("3.注销计算机\n");

        printf("0.退出系统\n");

        printf("-------------------------------------\n");

        scanf("%d",&c);

        switch(c) {

            case 1:

                printf("您想在多少秒后自动关闭计算机？（0~600）\n");

                scanf("%s",t);

                system(strcat(cmd,t));

                break;

            case 2:

                system("shutdown -p");

                break;

            case 3:

                system("shutdown -l");

                break;

            case 0:

                break;

            default:

                printf("Error!\n");

        }

        system("pause");
    }
    system("cls");
    system("color b9");
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"问";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"您";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"是";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"继";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"续";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"还";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"是";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"退";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"出";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"此";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"游";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"戏？";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"（";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"是";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"继";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"续";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"1";
    Sleep(300);
    cout<<",";
    Sleep(300);
    cout<<"如";
    Sleep(300);
    cout<<"果";
    Sleep(300);
    cout<<"不";
    Sleep(300);
    cout<<"玩";
    Sleep(300);
    cout<<"请";
    Sleep(300);
    cout<<"按";
    Sleep(300);
    cout<<"2";
    Sleep(300);
    cout<<")";
    cin>>k;
    if(k==2)
    {
        cout<<"byebye";
        return 0;
    }
    if(k==1)
    {
        system("cls");
            system("color b9");
    int n,m;
    bool c[100005];
    int a,b,d,e,f,g,i; int k;
    for(i=1; i<=100000000; i++) {

    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;cout<<endl;
    cout<<endl;cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                                  游"; 
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"戏";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"世";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"界";
        for(i=1; i<=100000000; i++) {

    }
    Sleep(1000);
    system("cls");
    system("color b9");
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"欢";
    for(i=1; i<=100000000; i++) {

    }
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    cout<<"迎";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"来";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"到";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"游";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"戏";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"世";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"-";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"界";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"--"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"                                                       作";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"者";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"：";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"邱";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"睿";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"量";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"工"; 
        for(i=1; i<=100000000; i++) {

    }
    cout<<"作";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"室";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"~";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"~"<<endl;
    for(i=1; i<=100000000; i++) {

    }
    cout<<"一，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"五";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"子";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"棋";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"（";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"1";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
    system("color f3");
    for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    system("color f9");
    for(i=1; i<=100000000; i++) {

    }
    cout<<"二，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"打";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"飞";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"机";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"（";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"2";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
system("color f3");
        for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    system("color f9");
    for(i=1; i<=100000000; i++) {

    }
    cout<<"三，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"猜";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"数";
    for(i=1; i<=10000000; i++) {

    }
    cout<<"(";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"3";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
    system("color f3");
        for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    system("color f9");
    for(i=1; i<=100000000; i++) {

    }
    cout<<"四，";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"关";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"机";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"程";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"序";
    for(i=1; i<=10000000; i++) {

    }
    cout<<"(";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"想";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"4";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"）"<<endl;
    system("color f3");
    for(i=1; i<=100000000; i++) {

    }
    cout<<"<><><><<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"<<endl;
    system("color f9");
    cin>>n;
    if(n==1) {
        {
            for (;;) {
                A.reset();
                for (GG=-1;;) {
                    gotoxy(A.nx,A.ny);
                    A.HM(0);
                    GG=A.check();
                    if (GG>-1) break;
                    A.AI(1);
                    GG=A.check();
                    if (GG>-1) break;
                }
                gotoxy(5,N+3);
                if (GG==0) printf("AI_1 win!");
                if (GG==1) printf("AI_2 wins!");
                while (kbhit()) getch();
                Sleep(500);
                gotoxy(5,N+3);
                printf("Press anything to continue.");
                getch();
            }
        }
    }
    if(n==2) {
        cout << string(13, '\n');
        cout << string(50, ' ') << "Game Loading" << endl << ".";
        Sleep(500);
        cout << "\t.";
        Sleep(500);
        cout << "\t\t.";
        Sleep(500);
        cout << "\t\t\t.";
        Sleep(500);
        cout << "\t\t\t.";
        Sleep(500);
        cout << "\t\t.";
        Sleep(500);
        cout << "\t\t.";
        Sleep(500);
        cout << "\t.";
        Sleep(2000);
        system("cls");
        //游戏准备
        srand((int)time(0));    //随机种子
        HideCursor();   //隐藏光标

        Game game;
        int a = drawMenu();
        if(a == 2)
            game.rank = 20;
        system("cls");
        drawPlaying();
        game.Playing();
    }
    if(n==3) {
        system("color b5");
        cout<<"猜数 3.2\n";
        srand(time(NULL));
        cout<<"==============================================================\n几人猜数（只支持100000人以内）？？";
        cin>>n;
        cout<<"==============================================================\n0~几？？";
        cin>>m;
        for(;;) {
            cout<<"==============================================================\n开始！！！";
            int x=rand()%(m+1),y,h=0,e=m,t=rand()%n;
            bool hh=1,ee=1;
            do {
                cout<<"\n==============================================================\n";
                cout<<h<<"~"<<e<<endl;
                ++t;
                t-=t>n?n:0;
                if(!c[t])
                    cout<<t<<"号猜(电脑帮猜？输-1 设置TA为电脑？输-2)",cin>>y;
                if(y==-2)
                    c[t]=1;
                if(y==-1||c[t]) {
                    y=(h+e)/2;
                    cout<<"帮"<<t<<"号猜猜成"<<y<<endl;
                    if(y==x)
                        break;
                    if(y>x) {
                        cout<<"大了";
                        e=y;
                        continue;
                    }
                    if(y<x) {
                        cout<<"小了";
                        h=y;
                        continue;
                    }
                }
                if(y<=h||y>=e) {
                    cout<<"浪费机会！！！";
                    continue;
                    if(!h&&!y)
                        if(hh)
                            hh=0;
                        else {
                            cout<<"浪费机会！！！";
                            continue;
                        }
                    if(e==m&&y==m)
                        if(ee)
                            ee=0;
                        else {
                            cout<<"浪费机会！！！";
                            continue;
                        }
                }
                if(y>x) {
                    cout<<"大了";
                    e=y;
                }
                if(y<x) {
                    cout<<"小了";
                    h=y;
                }
            } while(x!=y);
            cout<<t<<"号赢了！！！\n==============================================================\n再来一局吗？\ny/n\n";
            char a;
            a=getch();
            if(a=='n'||a=='N')
                break;
        }
        getchar();
        cout<<"==============================================================\nbyebye!\n==============================================================\n双击任意键结束，单机空格关机！";
        char a=getch();
        if(a==' ') {
            cout<<"\n确定吗？？确定点空格一下，否则双击任意键结束。";
            a=getch();
            if(a==' ')
                system("shutdown -s -t 0");
        }
    }
    if(n==4) {
        char cmd[20]="shutdown -s -t ";

        char t[5]="0";

        int c;

        system("title C语言关机程序");  //设置cmd窗口标题

        system("mode con cols=48 lines=25");  //窗口宽度高度

        system("color f0");  //可以写成 red 调出颜色组

        system("date /T");

        system("TIME /T");

        printf("----------- C语言关机程序 -----------\n");

        printf("1.实现10分钟内的定时关闭计算机\n");

        printf("2.立即关闭计算机\n");

        printf("3.注销计算机\n");

        printf("0.退出系统\n");

        printf("-------------------------------------\n");

        scanf("%d",&c);

        switch(c) {

            case 1:

                printf("您想在多少秒后自动关闭计算机？（0~600）\n");

                scanf("%s",t);

                system(strcat(cmd,t));

                break;

            case 2:

                system("shutdown -p");

                break;

            case 3:

                system("shutdown -l");

                break;

            case 0:

                break;

            default:

                printf("Error!\n");

        }

        system("pause");
    }
    system("cls");
    system("color b9");
    for(i=1; i<=100000000; i++) {

    }
    cout<<"请";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"问";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"您";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"是";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"继";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"续";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"还";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"是";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"退";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"出";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"此";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"游";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"戏？";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"（";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"如";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"果";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"是";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"继";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"续";
    for(i=1; i<=100000000; i++) {

    }
    cout<<"玩";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"按";
        for(i=1; i<=100000000; i++) {

    }
    cout<<"1";
    Sleep(300);
    cout<<",";
    Sleep(300);
    cout<<"如";
    Sleep(300);
    cout<<"果";
    Sleep(300);
    cout<<"不";
    Sleep(300);
    cout<<"玩";
    Sleep(300);
    cout<<"请";
    Sleep(300);
    cout<<"按";
    Sleep(300);
    cout<<"2";
    Sleep(300);
    cout<<")";
    cin>>k;
    }
}