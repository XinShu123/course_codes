#include <iostream>
#include <string>
#include <stdio.h>
#include <cctype>
#include <cassert>
using namespace std;
bool isDigit(string str){
    
    for(unsigned i=0;i<str.size();i++){
        int num=(int)str[i];
        if(num>=48&&num<=57)continue;
        else return false;
    }
    return true;
}
void evaPrefx(long long N, string ope[],long long &result,bool & invalid){
    string A[N];
    int top=-1;
    
    for(long long i=N-1;i>=0;i--){
        if(isDigit(ope[i])){
            
           long long num;
           
            num=(stoll(ope[i])%1000000007+1000000007)%1000000007;
            A[++top]=to_string(num);
           
        
            
        }
        
        else {
            if(top==-1) {cout<<"Invalid"<<endl; invalid =false;return; }
            if(!isDigit(A[top]) ){cout<<"Invalid"<<endl; invalid =false;return;}
            long long num1;
            num1=stoll(A[top--]);
            if(top==-1) {cout<<"Invalid"<<endl;invalid = false;return;}
            if(!isDigit(A[top])) {cout<<"Invalid"<<endl; invalid=false;return; }
            long long num2;
            num2=stoll(A[top--]);
            
            if(ope[i].substr(0,1)=="+"){
                
                long long res=((num1+num2)%1000000007+1000000007)%1000000007;
                
                A[++top]=to_string(res);
                
                
               
                
                
            }
            else if(ope[i].substr(0,1)=="-"){
                 
                long long res=((num1-num2)%1000000007+1000000007)%1000000007;
                A[++top]=to_string(res);
            }
            else if(ope[i].substr(0,1)=="*"){
                
                long long res=((num1*num2)%1000000007+1000000007)%1000000007;
                
                
                A[++top]=to_string(res);
                
                
            }
            else{
                cout<<"Invalid"<<endl;
                invalid=false;
                return;
            }

        }
    }
    
    
    if((top+1)!=1){
        cout<<"Invalid"<<endl;
        invalid = false;
        return;
    }
    
    
    else{
    
    result=stoll(A[top--]);}
    
}
int main(){
    long long N;
    cin>>N;
    string A[N];
    for(long long i=0;i<N;i++){
        string str;
        cin>>str;
        A[i]=str;
    }
    bool invalid=true;
    long long result;
    evaPrefx(N,A,result,invalid);
    if(invalid==true){

    cout<<result<<endl;}
    
}
