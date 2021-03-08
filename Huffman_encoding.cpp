#include <iostream>
#include <string>

using namespace std;
struct Node{
    char data;
    int freq;
    Node* left;
    Node* right;
    Node(char data_,int freq_){
        data=data_;
        freq=freq_;
        left=NULL;
        right=NULL;
    }
    
    
};


void swap(Node* A[],int i,int j){
    Node* temp=A[i];
    A[i]=A[j];
    A[j]=temp;
    


}
int partition(Node* A[],int p,int r){
    
    int i=p-1;
    for(int j=p;j<r;j++){
        if((A[j]->freq<A[r]->freq)||(A[j]->freq==A[r]->freq&&A[j]->data<A[r]->data)){
            i=i+1;
            swap(A,i,j);
        }
    }
    swap(A,i+1,r);
    return i+1;

}
void quickSort_data(Node* A[],int p,int r){
    if(p<r){
        int q=partition(A,p,r);
        quickSort_data(A,p,q-1);
        quickSort_data(A,q+1,r);
    }
}

Node* Huffman(string s,Node* nodes[],int &n){
    int Freq[128];
    for(int i=0;i<128;i++){
        Freq[i]=0;
    }
    int base=s.size();
    for(int i=0;i<base;i++){
        Freq[int(s[i])]++;
    }
    //cout<<int(' ')<<endl;
     n=0;
    for(int i=0;i<128;i++){
        if(Freq[i]!=0){
            
            Node* node=new Node(char(i),Freq[i]);
            
            nodes[n]=node;
            n++;

        }

    }
    quickSort_data(nodes,0,n-1);
    /*for(int i=0;i<n;i++){
        cout<<nodes[i]->data<<nodes[i]->freq<<endl;}*/
    while(n>1){
        Node* left_=nodes[0];//nodes.top()
        for(int i=0;i<n-1;i++){
            nodes[i]=nodes[i+1];
        }
        n--;//nodes.pop()
        Node* right_=nodes[0];
        for(int i=0;i<n-1;i++){
            nodes[i]=nodes[i+1];
        }
        n--;
        Node* node=new Node(left_->data,left_->freq+right_->freq);
        node->left=left_;
        node->right=right_;
        nodes[n]=node;
        n++;//node.push()
        quickSort_data(nodes,0,n-1);
        

    }
    
    return nodes[0];
    

}

void printCodes(Node* root, int arr[],int i,string code[128]){
    if(root->left!=NULL){
        arr[i]=0;
        printCodes(root->left,arr,i+1,code);
    }
    if(root->right!=NULL){
        arr[i]=1;
        printCodes(root->right,arr,i+1,code);
    }
    if(root->left==NULL&&root->right==NULL){
        
        string s="";
        for(int j=0;j<i;j++){
            s+=to_string(arr[j]);
        }
        code[int(root->data)]=s;
        
    }
}
int main(){
    
    string s;
    getline(cin,s);
    int base=s.size();
   
    Node* nodes[100000];
    int n;
    Node* root=Huffman(s,nodes,n);
    int array[100000];
    int i=0;
    string code[196];
    
    printCodes(root,array,i,code);
    string res="";
    for(int i=0;i<base;i++){
        
        res+=code[int(s[i])];


    }
    cout<<res<<endl;
    
    return 0;
}
