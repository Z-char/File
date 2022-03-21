#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdio>
#include <windows.h>
#define MX 19
#define S 0
#define B 1
#define W 2
#define U 3
#define MDEP 5
#define SRANGE 6
#define oo 1000000000
#define mov(x) (1LL<<(x))

using namespace std;

typedef long long ll;

struct position
{
    int x,y,v;
    bool operator < (const position& t)const{return v>t.v;}
};

ll game_x[4][MX+2];
ll game_y[4][MX+2];
ll game_u[4][MX*2+2];       //x-y+MX
ll game_d[4][MX*2+2];       //x+y
int cur_x,cur_y,cur_p,rob_p;

int line_value_count=31;
int line_value_base[40][6]={    //每一种棋型的估价函数
{+oo,B,B,B,B,B},
{1000,B,B,B,B,S},
{1000,S,B,B,B,B},
{1000,B,S,B,B,B},
{1000,B,B,S,B,B},
{1000,B,B,B,S,B},
{200,B,B,B,S,S},
{200,B,B,S,B,S},
{200,B,B,S,S,B},
{200,B,S,B,B,S},
{200,B,S,B,S,B},
{200,B,S,S,B,B},
{200,S,B,B,B,S},
{200,S,B,B,S,B},
{200,S,B,S,B,B},
{200,S,S,B,B,B},
{20,S,S,S,B,B},
{20,S,S,B,S,B},
{20,S,S,B,B,S},
{20,S,B,S,S,B},
{20,S,B,S,B,S},
{20,S,B,B,S,S},
{20,B,S,S,S,B},
{20,B,S,S,B,S},
{20,B,S,B,S,S},
{20,B,B,S,S,S},
{1,B,S,S,S,S},
{1,S,B,S,S,S},
{1,S,S,B,S,S},
{1,S,S,S,B,S},
{1,S,S,S,S,B}
};
int line_value[32];

int pos_value[MX+2][MX+2];

void gotoxy(int x, int y)
{
    COORD pos;
    pos.X=x-1;
    pos.Y=y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

int get_value(int *seq)         //获得一种棋型的估价函数
{
    int sum=0,f;
    for(int i=0;i<line_value_count;i++)
    {
        f=1;
        for(int j=0;j<5;j++)
        {
            if( (line_value_base[i][j+1]==B&&seq[j]==B)||
                (line_value_base[i][j+1]==S&&seq[j]==S));
            else {f=0;break;}
        }
        if(f)sum+=line_value_base[i][0];
    }
    return sum;
}

void init()                     //将每一种棋型预处理为二进制
{
    int now_seq[MX];
    for(int i=1;i<=MX;i++)
        for(int j=1;j<=MX;j++)
            pos_value[i][j]=min(min(i,j),min(MX+1-i,MX+1-j));
    for(int j=0;j<mov(5);j++)
    {
        for(int l=0;l<5;l++)
        {
            if(j&mov(l))now_seq[l]=B;
            else now_seq[l]=S;
        }
        line_value[j]=get_value(now_seq);
    }
    cur_p=B;
    cur_x=10,cur_y=10;
    gotoxy(cur_x*2+1,MX-cur_y+2);
}

bool place_seed(int x,int y,int p)  //在 (x,y) 处放置玩家 p 的棋
{
    int u=x+y;
    int d=x-y+MX;
    if((game_x[B][y]|game_x[W][y])&mov(x))return 0;
    game_x[p][y]|=mov(x);
    game_y[p][x]|=mov(y);
    game_u[p][d]|=mov(u>>1);
    game_d[p][u]|=mov(d>>1);
    return 1;
}

bool unplace_seed(int x,int y,int p)    //删除 (x,y) 处玩家 p 的棋
{
    int u=x+y;
    int d=x-y+MX;
    if(!(game_x[p][y]&mov(x)))return 0;
    game_x[p][y]^=mov(x);
    game_y[p][x]^=mov(y);
    game_u[p][d]^=mov(u>>1);
    game_d[p][u]^=mov(d>>1);
    return 1;
}

int get_x_line(int x,int y,int p)       //获得以 (x,y) 为左端点的水平连续的 5 个格子内的状态
{
    if(x<1||x+4>19||y<1||y>19)return 0;
    ll a,b;
    a=game_x[p][y]>>x;
    b=game_x[3-p][y]>>x;
    if((b&(mov(5)-1)))return 0;
    else return (a&(mov(5)-1));
}

int get_y_line(int x,int y,int p)       //获得以 (x,y) 为下端点的竖直连续的 5 个格子内的状态
{
    if(x<1||x>19||y<1||y+4>19)return 0;
    ll a,b;
    a=game_y[p][x]>>y;
    b=game_y[3-p][x]>>y;
    if((b&(mov(5)-1)))return 0;
    else return (a&(mov(5)-1));
}

int get_u_line(int x,int y,int p)       //获得以 (x,y) 为左端点的斜向上连续 5 个格子内的状态
{
    if(x<1||x+4>19||y<1||y+4>19)return 0;
    int u=x+y;
    int d=x-y+MX;
    ll a,b;
    a=game_u[p][d]>>(u>>1);
    b=game_u[3-p][d]>>(u>>1);
    if((b&(mov(5)-1)))return 0;
    else return (a&(mov(5)-1));
}

int get_d_line(int x,int y,int p)       //获得以 (x,y) 为左端点的斜向下连续 5 个格子内的状态
{
    if(x<1||x+4>19||y-4<1||y>19)return 0;
    int u=x+y;
    int d=x-y+MX;
    ll a,b;
    a=game_d[p][u]>>(d>>1);
    b=game_d[3-p][u]>>(d>>1);
    if((b&(mov(5)-1)))return 0;
    else return (a&(mov(5)-1));
}

int evaluate(int p)                     //估计整个棋盘内玩家 p 的权值
{
    int sum=0;
    for(int i=1;i<=MX;i++)
        for(int j=1;j<=MX;j++)
            sum+=
                line_value[get_x_line(i,j,p)]+
                line_value[get_y_line(i,j,p)]+
                line_value[get_u_line(i,j,p)]+
                line_value[get_d_line(i,j,p)];
    return sum;
}

void display()                          //windwos 控制台下的显示函数
{
    gotoxy(1,1);
    for(int i=0;i<=20;i++)putchar('-'),putchar('-');
    putchar('\n');
    for(int i=19;i>=1;i--)
    {
        putchar('|'),putchar(' ');
        for(int j=1;j<=19;j++)
        {
            if(game_x[B][i]&mov(j))putchar('X');
            else if(game_x[W][i]&mov(j))putchar('O');
            else putchar(' ');
            putchar(' ');
        }
        putchar('|'),putchar('\n');
    }
    for(int i=0;i<=20;i++)putchar('-'),putchar('-');
    gotoxy(cur_x*2+1,MX-cur_y+2);
}

int dfs(int dep,int player,int top)     //博弈搜索
{
    position stk[MX*MX+2];
    int num=0;
    int ret=-oo,e1=evaluate(player),e2=evaluate(3-player);
    if(dep==MDEP||abs(e1-e2)>=+oo/2)return e1-e2;
    else
    {
        for(int i=1;i<=MX;i++)
            for(int j=1;j<=MX;j++)
                if(place_seed(i,j,player))
                {
                    stk[++num]=(position){i,j,evaluate(player)-evaluate(3-player)};
                    unplace_seed(i,j,player);
                }
        sort(stk+1,stk+num+1);
        for(int i=1;i<=SRANGE;i++)
        {
            place_seed(stk[i].x,stk[i].y,player);
            ret=max(ret,-dfs(dep+1,3-player,ret));
            unplace_seed(stk[i].x,stk[i].y,player);
            if(-ret<=top)return ret;
        }
        return ret;
    }
}

void play()
{
    if(cur_p==rob_p)
    {
        int mxval=-oo,nowval,nx=0,ny=0;
        position stk[MX*MX+2];
        int num=0;
        for(int i=1;i<=MX;i++)
            for(int j=1;j<=MX;j++)
                if(place_seed(i,j,cur_p))
                {
                    stk[++num]=(position){i,j,evaluate(cur_p)-evaluate(3-cur_p)+pos_value[i][j]};
                    unplace_seed(i,j,cur_p);
                }
        sort(stk+1,stk+num+1);
        for(int i=1;i<=SRANGE;i++)
        {
            int tx=stk[i].x,ty=stk[i].y;
            place_seed(tx,ty,cur_p);
            nowval=-dfs(1,3-cur_p,mxval-pos_value[nx][ny])+pos_value[tx][ty];
            if(nowval>mxval)nx=tx,ny=ty,mxval=nowval;
            unplace_seed(tx,ty,cur_p);
        }
        system("cls");
        place_seed(cur_x=nx,cur_y=ny,cur_p);
        cur_p=3-cur_p;
        display();
    }
    else
    {
        int ch=getch();         //获得按键 (上下左右与 WASD，空格回车落子)
        if(ch==224)
        {
            ch=getch();
            if(ch==77)cur_x++;
            else if(ch==75)cur_x--;
            else if(ch==72)cur_y++;
            else if(ch==80)cur_y--;
        }
        else if(ch==100)cur_x++;
        else if(ch==97)cur_x--;
        else if(ch==119)cur_y++;
        else if(ch==115)cur_y--;
        else if(ch==13||ch==32)
        {
            system("cls");
            if(place_seed(cur_x,cur_y,cur_p))cur_p=3-cur_p;
            display();
        }
        if(cur_x<1)cur_x=1;
        if(cur_x>19)cur_x=19;
        if(cur_y<1)cur_y=1;
        if(cur_y>19)cur_y=19;
        gotoxy(cur_x*2+1,MX-cur_y+2);
    }
}

bool win(int p)             //判断是否有人获胜
{
    for(int i=1;i<=MX;i++)
        for(int j=1;j<=MX;j++)
            if( line_value[get_x_line(i,j,p)]>=+oo||
                line_value[get_y_line(i,j,p)]>=+oo||
                line_value[get_u_line(i,j,p)]>=+oo||
                line_value[get_d_line(i,j,p)]>=+oo)
                    return 1;
    return 0;
}

int main()
{
    rob_p=B;
    init();
    display();
    while(1)
    {
        play();
        if(win(W))
        {
            gotoxy(6,23);
            printf("White Win!\n");
            break;
        }
        if(win(B))
        {
            gotoxy(6,23);
            printf("Black Win!\n");
            break;
        }
    }
    return 0;
}