#include<iostream>
#include<cmath>
#include<vector>
// #include "tree.h"

using namespace std ;

# define n 10

struct data {
    float values[n]; 
} ; 



using s_data = struct data;


using data_list = vector<struct data> ;    

struct node {

    struct data pivot1 ;
    struct data pivot2 ;
    struct node* lchild ;
    struct node* rchild ; 
    struct node* parent ; 

} ; 

using Node = struct node;


float euclid_dist( struct data a , struct data b )
{

    float dist_sqr = 0 ; 

    for (int i = 0; i < n ; i++)
    {
        float temp = a.values[i] - b.values[i] ; 
        temp *= temp ; 
        dist_sqr += temp ; 
    }

    float dist = sqrt( dist_sqr ) ; 
    return dist ; 

}

float manhattan_dist(s_data a, s_data b){
    float dist=0;
    for(int i=0;i<n;i++){
        dist+=abs(a.values[i]-b.values[i]);
    }
    return dist;
}


float chebyshev_dist(s_data a, s_data b){
    float dist;
    for(int i=0;i<n;i++){
        if(!i){
            dist=abs(a.values[i]-b.values[i]);
        }
        else{
            if(dist > abs(a.values[i]-b.values[i]))
                dist= abs(a.values[i]-b.values[i]);
        }
    }

    return dist;
}

float distance( struct data a , struct data b )
{

    float dist_sqr = 0 ; 

    for (int i = 0; i < n ; i++)
    {
        float temp = a.values[i] - b.values[i] ; 
        temp *= temp ; 
        dist_sqr += temp ; 
    }

    float dist = sqrt( dist_sqr ) ; 
    return dist ; 

}

struct node* new_node( data_list pivots , node* y )
{
    node* z = new node() ; 
    z->lchild = NULL ; 
    z->rchild = NULL ; 
    z->pivot1 = pivots[0] ; 
    z->pivot2 = pivots[1] ; 
    z->parent = y ; 

    return z ; 
}

Node *createnode(s_data nill){
    Node *ref=new Node;
    
    ref->pivot1=nill;
    ref->pivot2=nill;

    ref->lchild = new Node;
    ref->rchild = new Node;
    ref->parent = new Node;

    ref->lchild = NULL;
    ref->rchild = NULL;
    ref->parent = NULL;

    return ref;
}

void insert_node( node** root , data_list pivots )
{
    node* y = NULL ; 
    node* x = *root ; 

    while( x != NULL )
    {
        y = x ; 

        if ( distance(x->pivot1 , pivots[0] ) > distance( x->pivot2 , pivots[0] ) )
        {
            x = x->rchild ; 
        }
        else 
        {
            x = x->lchild ; 
        }
    }

    node* z = new_node( pivots , y ) ;
    
    if ( y == NULL )
    {
        *root = z ; 
    } 
    else if ( distance(y->pivot1 , pivots[0] ) > distance( y->pivot2, pivots[0] ) )
    {
        y->rchild = z ; 
    }
    else
    {
        y->lchild = z ; 
    }

    return;

}

void print_point(s_data x){
    for(int i=0;i<n;i++){
        cout<<x.values[i]<<" ";
    }
    return;
}

bool closer(s_data x,s_data a, s_data b, float (*distance)(s_data,s_data)){
    if(distance(x,a)<distance(x,b))
        return false;
    else
        return true;
}


bool equal(struct data d1, struct data d2){
    for(int i=0;i<n;i++){
        if(d1.values[i]!=d2.values[i])
            return false;
    }
    return true;
}

void insert(s_data x, Node **start, s_data nill){

        if((*start)==NULL){
            *start = createnode(nill);
            (*start)->pivot1=x;
        }
        else if(equal((*start)->pivot2,nill)){
                                                               
            (*start)->pivot2=x;
        }
        else if(equal((*start)->pivot1,nill)){
            
            (*start)->pivot1=x;
        }
        else{

            if(closer(x,(*start)->pivot1,(*start)->pivot2,euclid_dist)){
                insert(x,&((*start)->lchild),nill);
            }
            else{
                insert(x,&((*start)->rchild),nill);
            }
        }

        return;
}


void delete_point(s_data x,Node **start, s_data nill){
    
    if((*start)==NULL){
        cout<<"No such point in the tree: ";
        print_point(x);
        cout<<"\n";
        return;
    }
    else if(equal((*start)->pivot2,x)){
        (*start)->pivot2=nill;                                                
    }
    else if(equal((*start)->pivot1,x)){
        (*start)->pivot1=nill;
    }
    else{
        if(closer(x,(*start)->pivot1,(*start)->pivot2,euclid_dist)){
            delete_point(x,&((*start)->lchild),nill);
        }
        else{
            delete_point(x,&((*start)->rchild),nill);
        }
    }
    return;
}






