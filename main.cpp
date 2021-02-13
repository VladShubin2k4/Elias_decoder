#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <windows.h>
using namespace std;

int transfer(int byte,short radix){
  int res=0, k=1;
  for(short i=0;byte!=0; ++i){
      res+=(byte%radix)*k;
      k*=2;
      byte/=radix;
  }
  return res;
}

void DeleteElem(string& str, short& len, short arg){
    for (short i=arg; i<len-1; ++i) str[i]=str[i+1];
    --len;
    str[len]='\0';
}

void Decompress(vector<string>& dec,short& arg){
    for(short i=dec.size()-1; i>=0; --i){
        arg%=2;
        int cnt=stoi(dec[i]);
        dec[i].clear();
        for(int j=0; j<cnt; ++j)  dec[i].insert(j,to_string(arg));
        ++arg;
    }
}

void DeleteNull(string& str, short& len, bool& first){
    short cnt=0;
    if(!first) --cnt;
    for(short i=0; i<str.size() && str[i]!='\0'; ++i){
        if(str[i]=='0'){
            ++cnt;
            DeleteElem(str, len, i);
            --i;
        }else if(cnt){
            i=i+cnt+1;
            ++len;
            str.insert(i," ");
            cnt=0;
        }else{
            ++len;
            str.insert(i+1," ");
            ++i;
        }
    }
}

vector<string> InDEC(string& str, short& len){
    vector<string> res;
    int combo,p,iterator=0;
    len=0;
    while(str[++len]!='\0'){}
    --len;
    for(short i=len; i>=0; --i){
        if(str[i]==' '){
            combo=0;
            p=0;
            for(short j=i-1; str[j]!=' ' && j>=0; --j){
                combo=combo+(static_cast<int>(str[j])-48)*static_cast<int>(pow(2,p));
                ++p;
            }
            res.push_back(to_string(combo));
            iterator++;
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    freopen("res.txt","w",stdout);
    cout<<"Enter Gamma Code:\n";
    short n, len;bool drop1st=false;
    string str;
    getline(cin,str);
    len=str.size();n=str[0];if(n!=48) drop1st=true;
    for(short i=0; i<str.size(); ++i) if(str[i]==' ') DeleteElem(str,len,i);
    DeleteNull(str,len,drop1st);
    vector <string> dec=InDEC(str,len);
    if(drop1st) dec.pop_back();
    short arg=static_cast<short>(drop1st);
    Decompress(dec,arg);
    string res;
    for(short i=0; i<dec.size(); ++i) res+=dec[i];
    string symb;
    short isfull=(res.size())%8;
    if(isfull){
        short cntnon=isfull;
        for(short j=res.size()-1; --cntnon>=0; --j)  symb+=res[j];
        unsigned char symbol=transfer(stoi(symb),10);
        symb.clear();
        cout<<symbol;
    }
    for(short j=res.size()-isfull-1;j>=0;--j){
        symb+=res[j];
        if(symb.size()==8){
            unsigned char symbol=transfer(stoi(symb),10);
            symb.clear();
            cout<<symbol;
        }
    }
    cout<<endl;
    return 0;
}
