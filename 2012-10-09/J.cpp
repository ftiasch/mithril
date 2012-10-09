#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define debug 0

string ans;
vector<string> candidates;

inline int query(string s)
{
    if (debug){
        if (s==ans) return -1;
        int c=0;
        for (int i=0;i<s.size();++i){
            if (s[i]==ans[i]) ++c;
        }
printf("    %s: %d\n",s.c_str(),c);
        return c;
    }else{
        int c;
        printf("%s\n",s.c_str());
        fflush(stdout);
        scanf("%d",&c);
        return c;
    }
}

string s;
vector<int> known;
vector<string> condition;

inline bool dfs(int step,char last)
{
    if (step==18){
        return true;
    }
    for (char ch='a';ch<='d';++ch){
        if (ch==last) continue;
        bool valid=true;
        for (int i=0;i<(int)known.size();++i){
            if (condition[i][step]==ch){
                --known[i];
            }
            if (known[i]<0 || known[i]>18-step-1){
                valid=false;
            }
        }
        bool ok=false;
        if (valid){
            s[step]=ch;
            if (dfs(step+1,ch)){
                ok=true;
            }
        }
        for (int i=0;i<known.size();++i){
            if (condition[i][step]==ch){
                ++known[i];
            }
        }
        if (ok){
            return true;
        }
    }
    return false;
}

int main()
{
    ans="";
    srand(time(0)^616127617);
    for (int i=0;i<18;++i){
        char ch='a'+rand()%4;
        while (ans.size()!=0 && ans[ans.size()-1]==ch){
            ch='a'+rand()%4;
        }
        ans+=ch;
    }
    
    s="";
    for (int i=0;i<18;++i){
        s+="a";
    }
    
    for (int i=0;i<15;++i){
        dfs(0,'0');
        condition.push_back(s);
        known.push_back(query(s));
        if (known.back()==-1) return 0;
    }
    
    return 0;
}

