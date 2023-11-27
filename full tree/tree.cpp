#include<iostream>
#include<cmath>
#include<vector>
// #include "tree.h"

using namespace std ;

# define n 10

struct data {
    float values[n] ; 
} ; 

using list = vector<struct data> ;    

struct node {

    struct data pivot1 ;
    struct data pivot2 ;
    struct node* lchild ;
    struct node* rchild ; 
    struct node* parent ; 

} ; 

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

struct node* new_node( list pivots , node* y )
{
    node* z = new node() ; 
    z->lchild = NULL ; 
    z->rchild = NULL ; 
    z->pivot1 = pivots[0] ; 
    z->pivot2 = pivots[1] ; 
    z->parent = y ; 

    return z ; 
}

void insert_node( node** root , list pivots )
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
    else if ( distance(x->pivot1 , pivots[0] ) > distance( x->pivot2, pivots[0] ) )
    {
        x->parent->rchild = z ; 
    }
    else
    {
        x->parent->lchild = z ; 
    }


}


// int main ()
// {
//     node* root = NULL ;

//     list pivots ; 
//     // int a[n] = { 1 , 2 } , b[n] = { 3 , 4 } ;
//     struct data a , b ; 
//     a.values[0] = 1 ;
//     a.values[1] = 2 ;
//     b.values[0] = 3 ;
//     b.values[1] = 4 ;


//     pivots.push_back( a ) ;   
//     pivots.push_back( b ) ;   

//     insert_node( &root , pivots ) ; 

//     cout << (root->pivot2).values[1] << endl ; 
     
// }


