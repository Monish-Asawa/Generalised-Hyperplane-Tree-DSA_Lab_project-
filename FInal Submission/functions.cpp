#include<iostream>
#include<cmath>
#include<vector>

using namespace std ;

# define n 10

struct data {
    float values[n]; 
} ; 

struct node {

    struct data pivot1 ;
    struct data pivot2 ;
    struct node* lchild ;
    struct node* rchild ; 
    struct node* parent ; 

} ; 

using point = struct data;
using data_list = vector<struct data> ;    
using Node = struct node;


// creates a new node for tree  
Node *createnode(point nill){
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


// prints whole n-d point 
void print_point( point x ){

    for( int i = 0 ; i < n ; i++ )
    {
        cout << x.values[i] << " " ;
    }
    //cout << endl ; 

}


// checks if two vectors are equal
bool equal( struct data v1 , struct data v2 )
{
    for (int i = 0; i < n ; i++)
    {
        if ( v1.values[i] != v2.values[i] )
        return false ; 
    }
    return true ; 
}



// calculates euclidean distance 
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


// calculates manhattan distance 
float manhattan_dist( point a, point b ){
    float dist = 0 ;
    for( int i = 0 ; i < n ; i++ )
    {
        dist += abs( a.values[i]-b.values[i] ) ;
    }
    return dist;
}


// calculates chebyshev distance 
float chebyshev_dist( point a , point b ){
    float dist ;
    for( int i = 0 ; i < n ; i++ )
    {
        if( !i )
        {
            dist = abs( a.values[i]-b.values[i] ) ;
        }
        else
        {
            if( dist < abs( a.values[i]-b.values[i] ) )
                dist = abs( a.values[i]-b.values[i] ) ;
        }
    }

    return dist;
}


// to check if point x is closer to pivot1 or pivot2  
bool closer_to_pivot1 ( point x , Node* node , float (*distance)(point,point)){

    point pivot1 = node->pivot1 ;
    point pivot2 = node->pivot2; 

    if( distance( x, pivot1 ) < distance( x, pivot2 ) )
        return true ;
    else
        return false ;

}


// inserts a new point in the tree 
void insert(point x, Node **start, point nill, float( *distance )( point , point)){

        if(( *start ) == NULL )
        {
            *start = createnode(nill);
            (*start)->pivot1 = x ;
        }
        else if( equal((*start)->pivot2 , nill ) )
        {                                    
            (*start)->pivot2 = x ;
        }
        else if( equal((*start)->pivot1 , nill ) )
        {
            (*start)->pivot1 = x ;
        }
        else{

            if( closer_to_pivot1( x , *start , distance ) )
            {
                insert( x , &((*start)->lchild) , nill, distance ) ;
            }
            else
            {
                insert( x , &((*start)->rchild) , nill, distance ) ;
            }
        }

        return;
}

 
// deletes a point from the tree 
void delete_point(point x,Node **start, point nill, float( *distance )( point , point)){
    
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
        if( closer_to_pivot1( x, *start , distance) ){
            delete_point(x,&((*start)->lchild),nill, distance);
        }
        else{
            delete_point(x,&((*start)->rchild),nill, distance);
        }
    }
    return;
}