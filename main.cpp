#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;

int transfer(int byte,short radix){
  int res=0, k=1;
  for(short i=0;byte!=0; ++i){
      res+=(byte%radix)*k;
      k<<=1;
      byte/=radix;
  }
  return res;
}

void Decompress(vector<string>& dec,short& arg){
    for(short i=dec.size()-1; i>=0; --i){
        arg%=2;
        int cnt=stoi(dec[i]);
        dec[i].clear();
        for(int j=0; j<cnt; ++j)  dec[i].push_back(static_cast<char>(arg+48));
        ++arg;
    }
}

void DeleteNull(string& str){
    short cnt=0;
    for(short i=0; i<str.size() && str[i]!='\0'; ++i){
        if(str[i]=='0'){
            ++cnt;
            str.erase(i--,1);
        }else if(cnt){
            i=i+cnt+1;
            str.insert(i," ");
            cnt=0;
        }else str.insert(++i," ");
    }
}

vector<string> InDEC(const string& str){
    vector<string> res;
    int combo,p;
    for(short i=str.size()-1; i>=0; --i){
        if(str[i]==' '){
            combo=0;
            p=0;
            for(short j=i-1; str[j]!=' ' && j>=0; --j) combo=combo+(static_cast<int>(str[j])-48)*static_cast<int>(1<<p++);
            res.push_back(to_string(combo));
        }
    }
    return res;
}

void Decode_and_Otput(const vector<string>& dec){
    string res,symb;
    for(short i=0; i<dec.size(); ++i) res+=dec[i];
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
            unsigned char symbol=static_cast<unsigned char>(transfer(stoi(symb),10));
            symb.clear();
            cout<<symbol;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    SetConsoleCP(1251);SetConsoleOutputCP(1251);
    short arg=0;
    string str;
    getline(cin,str);

    arg=str[0]%48;
    str.erase(0,1);
    for(short i=0; i<str.size(); ++i) if(str[i]==' ') str.erase(i,1);

    DeleteNull(str);
    vector <string> dec=InDEC(str);

    Decompress(dec,arg);
    Decode_and_Otput(dec);
    cin.get();cin.get();
    return 0;
}
