#include <iostream>
using namespace std;
#define inf 2147483647
#include <cassert>
typedef struct node{
    
    int32_t Order;
    int32_t dist;
    node* next;
    node(int32_t order,int32_t Dist){
        
        dist=Dist;
        next=nullptr;
        Order=order;
    }
    
}node;
typedef struct tou_node{
    
    node* tou;
    node* wei;
    tou_node(){
        tou=wei=nullptr;
    }

}tou_node;




 int32_t parent(int32_t i){
    return i/2;
}
int32_t left(int32_t i){
    return 2*i;
}
int32_t right(int32_t i){
    return 2*i+1;
}
void min_heapify(int32_t pq[],int32_t& size,int32_t i,int32_t min_dist[],int position_in_pq[]){
    int32_t l=left(i);/*min_heapify(pq,0,1,min_dist)*//*l=2*/
    int32_t r=right(i);/*r=3*/
    int32_t smallest=0;
    if(l<=size&&min_dist[pq[l]]<min_dist[pq[i]]){
         
         smallest=l;
    }
    else smallest=i;/*smallest=1*/
    
    if(r<=size&&min_dist[pq[r]]<min_dist[pq[smallest]]){
        smallest=r;
        
        
    }
    
    if(smallest!=i){
        int temp=pq[i];
        pq[i]=pq[smallest];
        position_in_pq[pq[smallest]]=i;
        pq[smallest]=temp;
        position_in_pq[temp]=smallest;
        min_heapify(pq,size,smallest,min_dist,position_in_pq);
    }
}
void extract_min(int32_t pq[],int32_t& size,int32_t min_dist[],int position_in_pq[]){
    /*int min=pq[1];extract_min(pq,1,min_dist)*/
    position_in_pq[pq[1]]=0;
    /*for(int i=1;i<size+1;i++){
        cout<<pq[i]<<endl;
    }*/
    pq[1]=pq[size];/*pq[1]=pq[1]*/
    position_in_pq[pq[size]]=1;
    
    size--;/*size=0*/
    
    min_heapify(pq,size,1,min_dist,position_in_pq);/*min_heapify(pq,0,1,min_dist)*/
    

}
int top(int32_t pq[]){
    return pq[1];
    

}

void heap_decrease_key(int32_t pq[],int32_t i,int32_t key,int32_t min_dist[],int32_t position_in_pq[]){
    /*heap_decrease_key(pq,1,5,min_dist)*/
    pq[i]=key;/*pq[1]=5*/
    
    while(i>1&&min_dist[pq[parent(i)]]>min_dist[pq[i]]){
        /*cout<<min_dist[pq[parent(i)]]<<"_"<<min_dist[pq[i]]<<endl;*/
        int32_t temp=pq[i];
        pq[i]=pq[parent(i)];
        position_in_pq[pq[parent(i)]]=i;
        pq[parent(i)]=temp;
        
        i=parent(i);
        

    }
    
    position_in_pq[pq[i]]=i;
}

void min_heap_insert(int32_t pq[],int32_t& size,int32_t put_in_order,int32_t min_dist[],int32_t position_in_pq[]){
      if(position_in_pq[put_in_order]==0){
      size++;/*insert 5, size=1,put_in_order=5*/
      pq[size]=inf;/*pq[1]=-inf*/
      
      heap_decrease_key(pq,size,put_in_order,min_dist,position_in_pq);}
      else{
          heap_decrease_key(pq,position_in_pq[put_in_order],put_in_order,min_dist,position_in_pq);
      }

}


int32_t min_dist[1000001];
    
    
int32_t pq[1000001];

int32_t position_in_pq[1000001];
    
int main(){
    
    
    int32_t a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    /*cout<<endl;*/
    tou_node Adj[a+1];
    for(int32_t i=1;i<a+1;i++){
        min_dist[i]=inf;
    }
    min_dist[c]=0;
    for(int32_t i=1;i<a+1;i++){
        position_in_pq[i]=0;
    }
    
    int32_t size=0;
    
    
    for(int32_t j=0;j<b;j++){
        int32_t d,e,f;
        scanf("%d%d%d",&d,&e,&f);
        if(d==e){
            continue;
        }
        node* Edge=new node(e,f);
        if(Adj[d].tou==nullptr){
            Adj[d].tou=Edge;
            Adj[d].wei=Edge;
        }
        else{
            //tou!=NULL
            Adj[d].wei->next=Edge;
            Adj[d].wei=Adj[d].wei->next;


        }

    }
    
    
    
    min_heap_insert(pq,size,c,min_dist,position_in_pq);
    
    while(size>0){
        

        int32_t current_source=top(pq);
        
        
        while(Adj[current_source].tou!=nullptr){
            
            node * n1=Adj[current_source].tou;
            
            bool update=false;
            if(min_dist[n1->Order]>(min_dist[current_source]+n1->dist)){
                min_dist[n1->Order]=min_dist[current_source]+n1->dist;
                /*cout<<min_dist[n1->Order]<<endl;*/
                update=true;
                /*update=true;*/
            }
            
            
            if(update){
            min_heap_insert(pq,size,n1->Order,min_dist,position_in_pq);}
            
            Adj[current_source].tou=Adj[current_source].tou->next;
            
            
            delete n1;
            n1=nullptr;
            
        }
        Adj[current_source].wei=nullptr;
        extract_min(pq,size,min_dist,position_in_pq);
        
        
    }
    for(int32_t i=1;i<a+1;i++){
        
        if(min_dist[i]==inf){
            printf("%d\n",-1);
        }
        else{
            printf("%d\n",min_dist[i]);
        }
    }
    
    
}
