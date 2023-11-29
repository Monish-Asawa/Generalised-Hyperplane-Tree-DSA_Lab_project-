#include<iostream> 
#include<bits/stdc++.h>
#include<vector> 
// #include"tree.h"
#include"functions.cpp"
//#include"additional_func.cpp"


using namespace std ;

double INF;

// # define n 10           // dimension 
# define dataset_size 200  // number of points 

// struct data {
//     float values[n] ; 
// } ; 

// To check if two vectors are same or different 
bool compare( struct data a , struct data b )
{

    for (int i = 0; i < n ; i++)
    {
        if ( a.values[i] != b.values[i] )
        {
            return true ; 
        }
    }
    return false ; 

}

bool equal(struct data d1, struct data d2){
    for(int i=0;i<n;i++){
        if(d1.values[i]!=d2.values[i])
            return false;
    }
    return true;
}

// calculating distance between two vectors 
// float distance( struct data a , struct data b )
// {

//     float dist_sqr = 0 ; 

//     for (int i = 0; i < n ; i++)
//     {
//         float temp = a.values[i] - b.values[i] ; 
//         temp *= temp ; 
//         dist_sqr += temp ; 
//     }

//     float dist = sqrt( dist_sqr ) ; 
//     return dist ; 

// }

// additional comparison function for sorting the distances vector 
bool sort_basis( pair<float , float > &a , pair<float , float > &b )
{
    return a.second < b.second ; 
}

// function to calculate mean of all vectors 
struct data calc_mean( vector<struct data> &dataset )
{
    struct data mean ; 
    
    for (int i = 0; i < n ; i++)
    {
        mean.values[i] = 0 ; 
    }

    for (int i = 0; i < dataset.size() ; i++)
    {
        for (int x = 0; x < n ; x++)
        {
            mean.values[x] += dataset[i].values[x] ; 
        }        
    }

    for (int i = 0; i < n ; i++)
    {
        mean.values[i] /= dataset.size() ; 
    }
    
    // cout << "Mean: " ; 
    // for (int i = 0; i < n ; i++)
    // {
    //     cout << mean.values[i] << " " ; 
    // }
    // cout << endl ; 

    return mean ; 
}

// reading file and extracting data
void read_file( vector<struct data> &dataset )
{
    ifstream file( "n-D_data.txt" ) ; 
    // vector<struct data> dataset ;  
    float value ; 

    for (int i = 0; i < dataset_size ; i++)
    {
        struct data temp ; 


        for (int x = 0; x < n ; x++)
        {
            file >> value ;
            temp.values[x] = value ;  
        }
        dataset.push_back( temp ) ;    
    }

    file.close() ; 
}

// find pivots from dataset 
void find_pivots( vector<struct data> &dataset , vector<struct data> &pivots ) 
{
    struct data mean = calc_mean( dataset ) ; 

    vector<pair< float , float >> distances_data ;  
    for (int i = 0; i < dataset.size() ; i++)
    {
        distances_data.push_back( make_pair( i , distance( mean , dataset[i] ) ) ) ; 
    }

    sort( distances_data.begin() , distances_data.end() , sort_basis) ; 
    // cout << distances_data[0].first << " " << distances_data[0].second << endl ;  
    // cout << distances_data[1].first << " " << distances_data[1].second << endl ;  

    int p1 = 0 , p2 = 0 , i1 = distances_data[0].first , i2 = distances_data[1].first ; 

    // cout << "\nPivot 1: " << "( " << dataset[i1].values[0] << " " << dataset[i1].values[1] << " )" << endl ; 
    // cout << "Pivot 2: " << "( " << dataset[i2].values[0] << " " << dataset[i2].values[1] << " )\n" << endl ; 



    pivots.push_back( dataset[i1] ) ;
    pivots.push_back( dataset[i2] ) ;


}

using groups = vector< vector<struct data> > ; 

//create subgroups using pivots of a dataset 
groups create_groups( vector<struct data> pivots , vector<struct data> &dataset ){

    vector<struct data> dataset0 , dataset1 ;  


    for (int i = 0; i < dataset.size() ; i++)
    {
        if ( distance( dataset[i] , pivots[0] ) >= distance( dataset[i] , pivots[1] ))
        {
            if(!equal(dataset[i] , pivots[1]))
                dataset1.push_back( dataset[i] ) ; 
        }
        else 
        {
            if(!equal(dataset[i] , pivots[1]))
                dataset0.push_back( dataset[i] ) ; 
        }
    }
    
    groups group_union ;
    group_union.push_back( dataset0 ) ; 
    group_union.push_back( dataset1 ) ;  
    //cout << "Group_1 : " << group_union[0].size() << "  Group_2 : " << group_union[1].size() << endl ; 

    return group_union ; 
}   

void recursive_partition( vector<struct data> &dataset , node** root )
{
    if ( (dataset).size() > 2 )
    {
        vector<struct data> pivots ; 
        find_pivots( dataset , pivots );
        insert_node( root , pivots ) ; 

        groups group1 = create_groups( pivots , dataset ) ;

        recursive_partition( group1[0] , root ) ; 
        recursive_partition( group1[1] , root ) ;  
    }
}


s_data near_n(s_data x, float (*distance)(s_data,s_data), Node *start){

    Node *ref=start;
    s_data min_node;

    for(int i=0;i<n;i++){
        min_node.values[i]=100;
    }

    float dist=INF;

    while(ref!=NULL){

        if(closer(x,ref->pivot1,ref->pivot2,distance)){
            
            if(dist > distance(x,ref->pivot1)){
                dist = distance(x,ref->pivot1);
                min_node=ref->pivot1;
            }

            ref= ref->lchild;
        }
        else{
            if(dist > distance(x,ref->pivot2)){
                dist = distance(x,ref->pivot2);
                min_node=ref->pivot2;
            }

            ref= ref->rchild;
        }
    }

    return min_node;
}



int main (){

    INF = numeric_limits<double>::max();

    vector<struct data> dataset ;
    read_file( dataset ) ;  

    node* root = NULL ; 
    recursive_partition( dataset , &root ) ; 

    s_data query;

    for(int i=0;i<n;i++){
        query.values[i]=1;
    }

    s_data neighbour = near_n(query, euclid_dist,root );

    // for(int i=0;i<n;i++){
    //     cout<<neighbour.values[i]<<" ";
    // }
    print_point(neighbour);

    cout<<"\n";

    

    return 0 ; 
}
