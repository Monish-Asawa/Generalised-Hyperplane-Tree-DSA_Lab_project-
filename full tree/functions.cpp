#include<iostream>
#include<cmath>
#include<vector>
// #include "tree.h"

using namespace std ;

# define n 10

struct data {
    float values[n] ; 
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

Node *createnode(void){
    Node *ref=new Node;
    
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


// void insert(s_data x, Node **start){

//         if((*start)==NULL){
//             *start = createnode();
//             (*start)->pivot1=x;
//         }
//         else if((*start)->pivot2==NULL){
                                                               // Need a way to compare the pivots to determine which one is empty
//             (*start)->pivot2=x;
//         }
//         else if((*start)->pivot1==NULL){
            
//             (*start)->pivot1=x;
//         }
//         else{

//             if(closer(x,(*start)->pivot1,(*start)->pivot2,euclid_dist)){
//                 insert(x,&((*start)->lchild));
//             }
//             else{
//                 insert(x,&((*start)->rchild));
//             }
//         }

//         return;
// }


// void delete_point(s_data x,Node **start){
    
//     if((*start)==NULL){
//         cout<<"No such point in the tree: ";
//         print_point(x);
//         cout<<"\n";
//         return;
//     }
//     else if(equal((*start)->pivot2,x)){
//         (*start)->pivot2=NULL;                                                
//     }
//     else if(equal((*start)->pivot1,x)){
//         (*start)->pivot1=NULL;
//     }
//     else{
//         if(closer(x,(*start)->pivot1,(*start)->pivot2,euclid_dist)){
//             delete_point(x,&((*start)->lchild));
//         }
//         else{
//             delete_point(x,&((*start)->rchild2));
//         }
//     }
//     return;
// }


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



