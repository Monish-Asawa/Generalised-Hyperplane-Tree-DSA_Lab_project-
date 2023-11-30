#include<iostream> 
#include<bits/stdc++.h>
#include<vector> 
#include"functions.cpp"

using namespace std ;
double INF;

// defined n = 10 in function file 
# define dataset_size 200  // number of points 

// comparison function used in sorting 
bool sort_basis( pair<float , float > &a , pair<float , float > &b )
{
    return a.second < b.second ; 
}


// function to calculate mean of all vectors 
struct data calc_mean( vector<struct data> &dataset )
{
    struct data mean ; 
    
    //initialisation 
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

    return mean ; 
}


// reading file and storing data
void read_file( vector<struct data> &dataset )
{
    ifstream file( "n-D_data.txt" ) ; 
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

void sort_index(int *arr, float* dist, int size){
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(dist[i]>dist[j]){
                float k=dist[j];
                dist[j]=dist[i];
                dist[i]=k;

                int l=arr[i];
                arr[i]=arr[j];
                arr[j]=l;
            }
        }
    }

    return;
}

// find pivots from dataset and stores it in pivots data structure 
void find_pivots( vector<struct data> &dataset , vector<struct data> &pivots, float( *distance )( point , point) ) 
{
    struct data mean = calc_mean( dataset ) ; 

    vector<pair< float , float >> distances_data ;  

    int index[dataset.size()];
    float dist_arr[dataset.size()];
    for (int i = 0; i < dataset.size() ; i++)
    {
        index[i]=i;
        dist_arr[i]= distance(mean,dataset[i]);
        distances_data.push_back(  make_pair(i, distance(mean,dataset[i]))  ) ; 
    }

    sort_index(index, dist_arr, dataset.size());
    pivots.push_back( dataset[index[0]] ) ;
    pivots.push_back( dataset[index[1]] ) ;

   

}


using groups = vector< vector<struct data> > ; 

//create subgroups using pivots of a dataset 
groups create_sub_groups( vector<struct data> pivots , vector<struct data> &dataset , float( *distance )( point , point)){

    vector<struct data> dataset1 , dataset2 ;  

    for (int i = 0; i < dataset.size() ; i++)
    {
        if ( distance( dataset[i] , pivots[0] ) >= distance( dataset[i] , pivots[1] ))
        {
            if( !equal(dataset[i] , pivots[1]) )
                dataset2.push_back( dataset[i] ) ; 
        }
        else 
        {
            if( !equal(dataset[i] , pivots[1]) )
                dataset1.push_back( dataset[i] ) ; 
        }
    }
    
    groups sub_groups ;
    sub_groups.push_back( dataset1 ) ; 
    sub_groups.push_back( dataset2 ) ;  

    return sub_groups ; 
}   


// parition of complete dataset and storing all elements on the tree
void recursive_partition( vector<struct data> &dataset , node** root , point nill, float( *distance )( point , point) )
{
    if ( (dataset).size() > 2 )
    {
        vector<struct data> pivots ; 
        find_pivots( dataset , pivots, distance );

        insert(  pivots[0] , root , nill , distance) ; 
        insert(  pivots[1] , root , nill , distance) ; 

        groups sub_groups = create_sub_groups( pivots , dataset , distance) ;

        recursive_partition( sub_groups[0] , root , nill , distance) ; 
        recursive_partition( sub_groups[1] , root , nill, distance ) ;  
    }
}


// finding neighbour using GHT 
point neighbour( point x , Node *start , float (*distance)(point,point) ){

    Node* temp=start;
    point min_node;

    for(int i = 0 ; i < n ; i++ )
    {
        min_node.values[i] = 100 ;
    }

    float dist = INF ;
    while( temp != NULL ){

        if( closer_to_pivot1( x , temp , distance ) )
        {
            if( dist > distance( x , temp->pivot1 ) )
            { 
                dist = distance( x , temp->pivot1 ) ;
                min_node = temp->pivot1 ;
            }
            temp = temp->lchild ;
        }
        else
        {
            if( dist > distance( x , temp->pivot2 ) )
            {
                dist = distance( x , temp->pivot2 ) ;
                min_node = temp->pivot2 ;
            }
            temp = temp->rchild;
        }
    }

    return min_node;
}


int main (){

//     int A[n] = { -6 , -4 , 3 , 2 , 2 , -2 , -1 , -6 , 2 , 5 } ; 
//     int B[n] = { 5 , 4 , -5 , 0 , 2 , 3 , 8 , 2 , 1 , 1 } ; 

//     int C[10] = { 3 , 1 ,-5 , 7 ,2 , 9 , 10 } ; 

//    point query , n1 , no ; 
//     for (int i = 0; i < n ; i++)
//     {
//         query.values[i] = C[i] ; 
//         no.values[i] = B[i] ;
//         n1.values[i] = A[i] ;  
//     }
    
//     float dist = distance( query , no ) ;
//     cout << dist << endl ; 

//     dist = distance( query , n1 ) ;
//     cout << dist << endl ; 


    float( *distance )( point , point) = & euclid_dist;

    INF = numeric_limits<double>::max();

    vector<struct data> dataset ;
    read_file( dataset ) ;  

    node* root = NULL ; 


    point nill ; 
    for (int i = 0; i < n ; i++)
    {
        nill.values[i] = -100 ; 
    }
    
    recursive_partition( dataset , &root , nill, distance) ; 

    point query;

    int A[10] = { 9 , 10 ,-5 , 7 ,2 , 9 , 10 } ; 

    for( int i = 0 ; i < n ; i++ )
    {
        query.values[i] =  7 ;
    }

    point neigh = neighbour( query , root , distance );

    print_point(neigh);

    return 0 ; 
}