#include<iostream>
#include<math.h>


#define left 0 
#define right 1
#define n 10

using namespace std;

struct point{
    int coord[n];
};

struct Node{
    struct point** pivot;
    struct Node** child;
    bool isleaf;
};

typedef struct point point;
typedef struct Node Node;

void print_point(point x){
    for(int i=0;i<n;i++){
        cout<<x.coord[i]<<" ";
    }
    return;
}

float euclid_dist( struct point a , struct point b )
{

    float dist_sqr = 0 ; 

    for (int i = 0; i < n ; i++)
    {
        float temp = a.coord[i] - b.coord[i] ; 
        temp *= temp ; 
        dist_sqr += temp ; 
    }

    float dist = sqrt( dist_sqr ) ; 
    return dist ; 

}


bool closer(point x,point a, point b, float (*distance)(point,point)){
    if(distance(x,a)<distance(x,b))
        return false;
    else
        return true;
}

bool equal(point a, point b){
    for(int i=0;i<n;i++){
        if(a.coord[i]!=b.coord[i])
            return false;
    }
    return true;
}


Node *createnode(void){
    Node *ref=new Node;
    ref->pivot = new point*[2];
    ref->child = new Node*[2];

    for(int i=0;i<2;i++){
        ref->pivot[i]=NULL;
        ref->child[i]=NULL;
    }
    ref->isleaf= true;

    return ref;
}


// Insert function for single coords

void insert(point x, Node **start){

        if((*start)==NULL){
            *start = createnode();
            point *ref= new point;
            *ref = x;
            (*start)->pivot[0]=ref;
        }
        else if((*start)->pivot[1]==NULL){
            point *ref= new point;
            *ref = x;
            (*start)->pivot[1]=ref;
        }
        else if((*start)->pivot[0]==NULL){
            point *ref= new point;
            *ref = x;
            (*start)->pivot[0]=ref;
        }
        else{

            (*start)->isleaf=false;

            if(closer(x,*((*start)->pivot[0]),*((*start)->pivot[1]),euclid_dist)){
                insert(x,&((*start)->child[0]));
            }
            else{
                insert(x,&((*start)->child[1]));
            }
        }

        return;
}


// A basic delete function which finds the node and replaces it with NULL

void delete_point(point x,Node **start){
    
    if((*start)==NULL){
        cout<<"No such point in the tree: ";
        print_point(x);
        cout<<"\n";
        return;
    }
    else if(equal(*((*start)->pivot[1]),x)){
        (*start)->pivot[1]=NULL;                                                
    }
    else if(equal(*((*start)->pivot[0]),x)){
        (*start)->pivot[0]=NULL;
    }
    else{
        if(closer(x,*((*start)->pivot[0]),*((*start)->pivot[1]),euclid_dist)){
            delete_point(x,&((*start)->child[0]));
        }
        else{
            delete_point(x,&((*start)->child[1]));
        }
    }
    return;
}



int main(){
    return 0;
}