#include<iostream>
#include<vector>
#include<limits>
#include<math.h>

#define SIZE 200
#define n 10

double INF;

using namespace std;

struct data{
    int values[n];
};

struct Node{
    struct data pivot[2];
    struct Node *child[2];
    bool isleaf = true;
};


typedef struct Node Node;
typedef struct data data;

Node * createnode(void){

    Node *ref= new Node;
    ref->child[0]=NULL;
    ref->child[1]=NULL;
    return ref;
}


// void insert_pivot(Node *ref, vector <data> &list){
//     ref->pivot[0]= list[0];
//     ref->pivot[1]=list[1];
// }


// void create_tree(vector<data> &points, Node **start){

//     *start = createnode();

//     vector<data> piv;

//     int ref1=0, ref2=0;

//     find_pivots(points, piv,&ref1, &ref2);

//     insert_pivot(*start,piv);

//     group datasets;

//     datasets=create_group(piv, points);

//     create_tree(datasets[0], &(*start)->child[0]);
//     create_tree(datasets[1], &(*start)->child[1]);

//     return;

// }

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

float manhattan_dist(data a, data b){
    float dist=0;
    for(int i=0;i<n;i++){
        dist+=abs(a.values[i]-b.values[i]);
    }
    return dist;
}


float chebyshev_dist(data a, data b){
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

bool closer(data x,data a, data b, int (*distance)(data,data)){
    if(distance(x,a)<distance(x,b))
        return false;
    else
        return true;
}

Node* near_n(data x, int (*distance)(data,data),Node *start){

    Node *ref=start, *min_node=start;
    int dist=INF;

    while(ref!=NULL){

        if(closer(x,ref->pivot[0],ref->pivot[1],distance)){
            
            if(dist > distance(x,ref->pivot[0])){
                dist = distance(x,ref->pivot[0]);
                min_node=ref->child[0];
            }

            ref= ref->child[0];
        }
        else{
            if(dist > distance(x,ref->pivot[1])){
                dist = distance(x,ref->pivot[1]);
                min_node=ref->child[1];
            }

            ref= ref->child[1];
        }
    }

    return min_node;
}





int main(){


    INF = numeric_limits<double>::max();
}