#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int SIZE[9] = {4, 3, 3, 2, 2, 2, 1, 1, 1};
const int dx[]={0,1,0,-1,1,1,-1,-1};
const int dy[]={1,0,-1,0,1,-1,1,-1};

int x_0, y_0, order[9];
char map[15][15];

bool range(int x,int y)
{
    return x>=0 && y>=0 && x<10 && y<10;
}

bool put(int x, int y, int s, int dir) {
    for (int i=0;i<s;++i){
        int tx=x+dx[dir]*i,ty=y+dy[dir]*i;
        if (!range(tx,ty) || map[tx][ty]=='#'){
            return false;
        }
        for (int k=0;k<8;++k){
            int xx=tx+dx[k],yy=ty+dy[k];
            if (range(xx,yy) && map[xx][yy]=='#'){
                return false;
            }
        }
    }
    for (int i=0;i<s;++i){
        int tx=x+dx[dir]*i,ty=y+dy[dir]*i;
        map[tx][ty]='#';
    }
    return true;
}

int main() {
    freopen("battleship.in","r",stdin);
    freopen("battleship.out","w",stdout);

    for (int i = 0; i < 10; ++ i) {
        for (int j = 0; j < 10; ++ j) {
            int id;
            scanf("%d", &id);
            if (id == 100) {
                x_0 = i;
                y_0 = j;
            }
        }
    }
    bool found = false;
    for (int i=0;i<9;++i){
        order[i]=i;
    }
    while (!found) {
        found=false;
        bool valid=true;
        memset(map,'.',sizeof(map));
        put(x_0,y_0,1,0);
        for (int i=0;i<9 && valid;++i){
            int u=order[i];
            for (int x=0;x<10;++x){
                for (int y=0;y<10;++y){
                    for (int dir=0;dir<2;++dir){
                        if (put(x,y,SIZE[u],dir)){
                            goto Break;
                        }
                    }
                }
            }
//printf("%d\n",i);
            valid=false;
            Break:;
        }
        if (valid) {
            found = true;
            for (int i = 0; i < 10; ++ i) {
                for (int j = 0; j < 10; ++ j) {
                    putchar(map[i][j]);
                }
                puts("");
            }
            break;
        }
        random_shuffle(order, order + 9);
    }
    return 0;
}
