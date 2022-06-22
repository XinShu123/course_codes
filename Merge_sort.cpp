#include <iostream>
using namespace std;
void merge(unsigned long long A[],int h,int m,int t);
void mergeSort(unsigned long long A[],int h,int t)
{
    if(h>=t)return;
    int m=h+(t-h)/2;
    mergeSort(A,h,m);
    mergeSort(A,m+1,t);
    merge(A,h,m,t);


    

}
void merge(unsigned long long A[],int h,int m,int t){
    int ln=m-h+1;
    int rn=t-m;
    int Left[ln];
    int Right[rn];
    int x=0;
    int y=0;
    for(int i=0;i<ln;i++){
        Left[i]=A[h+i];
    }
    for(int j=0;j<rn;j++){
        Right[j]=A[m+1+j];
    }
    int index=h;
    while(x<ln&&y<rn){
        if(Left[x]<=Right[y]){
            A[index]=Left[x];
            x++;


        }
        else{
            A[index]=Right[y];
            y++;
        }
        index++;
    }
    while(x<ln){
        A[index]=Left[x];
        x++;
        index++;
    }
    while(y<rn){
        A[index]=Right[y];
        y++;
        index++;
    }
    
    






}
int main(){
    
    int N;
    cin>>N;
    unsigned long long A[N];
    for(int i=0;i<N;i++){
        unsigned long long num;
        cin>>num;
        A[i]=num;

    }
    
    
    mergeSort(A,0,N-1);
    for(int i=0;i<N;i++)cout<<A[i]<<endl;
    cout<<endl;


}
