#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-11;
const double pi = acos(-1.0);

struct Complex {
    double x, y;

    Complex(double x = 0, double y = 0) : x(x), y(y) {}
};

inline Complex operator+(const Complex &a, const Complex &b)
{
    return Complex(a.x + b.x, a.y + b.y);
}

inline Complex operator-(const Complex &a, const Complex &b)
{
    return Complex(a.x - b.x, a.y - b.y);
}

inline Complex operator*(const Complex &a, const Complex &b)
{
    return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

void FFT(Complex P[], int n, int oper)
{
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        double p0 = pi / m * oper;
        sincos(p0, &unit_p0.y, &unit_p0.x);
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; j++) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}

const int MOD = 1000;
const int MAXB = 1 << 18;

struct BigInt
{
    vector<int> digits;

    BigInt(int a = 0) : digits(1, a) {
        normalize();
    }

    BigInt(const char *str) {
        int len = strlen(str);
        int now = 1;
        digits.clear();
        for (int i = len - 1; i >= 0; i--) {
            if (now == 1) {
                digits.push_back(0);
            }
            digits.back() += now * (str[i] - '0');
            if ((now *= 10) == MOD) {
                now = 1;
            }
        }
    }
    
    BigInt &normalize() {
        int carry = 0;
        for (int i = 0; i < digits.size() || carry; i++) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry;
            carry = digits[i] / MOD;
            digits[i] %= MOD;
            while (digits[i] < 0) {
                digits[i] += MOD;
                carry --;
            }
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    BigInt &operator+=(const BigInt &o) {
        if (digits.size() < o.digits.size()) {
            digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            digits[i] += o.digits[i];
        }
        return normalize();
    }

    BigInt &operator-=(const BigInt &o) {
        if (digits.size() < o.digits.size()) {
            digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            digits[i] -= o.digits[i];
        }
        return normalize();
    }

    BigInt &div2() {
        int carry = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            digits[i] += carry * MOD;
            carry = digits[i] & 1;
            digits[i] >>= 1;
        }
        return normalize();
    }

    BigInt operator*(const BigInt &o) {
        BigInt ret;
        ret.digits.resize(digits.size() + o.digits.size() - 1);
        int len = 1;
        while (len < ret.digits.size()) {
            len *= 2;
        }
        static Complex A[MAXB], B[MAXB], C[MAXB];
        for (int i = 0; i < len; i++) {
            A[i] = i < digits.size() ? digits[i] : 0;
            B[i] = i < o.digits.size() ? o.digits[i] : 0;
        }
        FFT(A, len, 1);
        FFT(B, len, 1);
        for (int i = 0; i < len; i++) {
            C[i] = A[i] * B[i];
        }
        FFT(C, len, -1);
        long long carry = 0;
        for (int i = 0; i < ret.digits.size(); i++) {
            long long now = carry + (long long)(C[i].x / len + 0.5);
            ret.digits[i] = now % MOD;
            carry = now / MOD;
        }
        while (carry) {
            ret.digits.push_back(carry % MOD);
            carry /= MOD;
        }
        return ret.normalize();
    }

    BigInt operator+(const BigInt &o) const {
        BigInt ret = *this;
        return ret += o;
    }

    BigInt operator-(const BigInt &o) const {
        BigInt ret = *this;
        return ret -= o;
    }

    void show() {
        printf("%d", digits.back());
        for (int i = (int)digits.size() - 2; i >= 0; i--) {
            printf("%03d", digits[i]);
        }
    }
};


const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};

const int maxn  =   1005;

char s[maxn][maxn];
int f[maxn][maxn][4],n,m;

inline int dfs(int x,int y,int dir)
{
    if (x<0 || x>=n || y<0 || y>=m || s[x][y]=='#') return 0;
    int &res=f[x][y][dir];
    if (res!=-1) return res;
    return res=dfs(x+dx[dir],y+dy[dir],dir)+1;
}

vector< pair<int,int> > q;

inline void flood(int sx,int sy)
{
    q.clear();
    q.push_back(make_pair(sx,sy));
    
    s[sx][sy]='!';
    
    for (int i=0;i<q.size();++i){
        int x=q[i].first,y=q[i].second;
        for (int k=0;k<4;++k){
            int tx=x+dx[k],ty=y+dy[k];
            if (tx>=0 && ty>=0 && tx<n && ty<m && s[tx][ty]=='.'){
                s[tx][ty]='!';
                q.push_back(make_pair(tx,ty));
            }
        }
    }
}

inline int solve(int len)
{
    int res=0;
    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j){
            if (s[i][j]=='.'){
                flood(i,j);

                bool horizon=false,vertical=false;
                sort(q.begin(),q.end());
                for (int k=0;k<q.size();++k){
                    int x=q[k].first,y=q[k].second;
                    int l1=f[x][y][0]+f[x][y][1]-1;
                    int l2=f[x][y][2]+f[x][y][3]-1;
//printf("%d,%d   %d %d\n",x,y,l1,l2);
                    if (l1<len && l2<len) return -1;
                    if (l1!=len && l2==len) horizon=true;
                    if (l1==len && l2!=len) vertical=true;
                }
//printf("%d,%d   size=%d hor:%d  ver:%d\n",i,j,q.size(),horizon,vertical);
                if (horizon && vertical) return -1;
                
                if (!horizon && !vertical){
                    ++res;
                }else{
                    int dir;
                    if (horizon){
                        dir=2;
                    }else{
                        dir=0;
                    }
                    for (int k=0;k<q.size();++k){
                        int x=q[k].first,y=q[k].second;
                        if (s[x][y]=='!'){
                            for (int d=0;d<len;++d){
                                int tx=x+dx[dir]*d,ty=y+dy[dir]*d;
                                if (tx<0 || ty<0 || tx>=n || ty>=m || s[tx][ty]!='!') return -1;
                                s[tx][ty]='#';
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

int main()
{
    freopen("armor.in","r",stdin);
    freopen("armor.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i){
        scanf("%s",s[i]);
    }
    
    memset(f,-1,sizeof(f));
    int len=0;
    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j){
            for (int k=0;k<4;++k){
                dfs(i,j,k);
            }
            len=max(len,f[i][j][0]+f[i][j][1]-1);
            len=max(len,f[i][j][2]+f[i][j][3]-1);
        }
    }

    int pw=solve(len);
    
    if (pw==-1){
        puts("0");
        return 0;
    }
    
    //printf("%d\n",pw);
    BigInt ans(1),mul(2);
    while (pw>0){
        if (pw&1) ans=ans*mul;
        mul=mul*mul;
        pw>>=1;
    }
    ans.show();
    puts("");
    
    
    return 0;
}

