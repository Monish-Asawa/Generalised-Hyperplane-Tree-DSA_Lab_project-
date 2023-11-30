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

void read_query( vector<struct data> &queryset )
{
    ifstream file( "query.txt" ) ; 
    float value ; 

    for (int i = 0; i < 100 ; i++)
    {
        struct data temp ; 
        for (int x = 0; x < n ; x++)
        {
            file >> value ;
            temp.values[x] = value ;  
        }

        queryset.push_back( temp ) ;    
    }

    file.close() ; 
}

void sort_index(int *arr, float* dist, int size){
    for(int i=0;i<2;i++){
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



struct data neighb( struct data query , vector<struct data> &dataset, float( *distance )( struct data , struct data) )
{
    vector<pair< float , float >> distances_data ;  
    // cout << dataset.size() << endl ; 
    for (int i = 0; i < dataset.size() ; i++)
    {
        distances_data.push_back( make_pair( i , distance( query , dataset[i] ) ) ) ; 
    }

    sort( distances_data.begin() , distances_data.end() , sort_basis) ; 

    return dataset[distances_data[0].first] ; 
}

int main (){

    float( *distance )( point , point);

    int j;
    cin>>j;

    if(j==1){
        distance= &euclid_dist;
    }
    else if(j==2){
        distance= &manhattan_dist;
    }
    else{
        distance= &chebyshev_dist;
    }

    

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

    // point query;

    // int A[10] = {  6,-1,-3,6,8,-3,1,10,7,0  } ; 
    // for (int i = 0; i < 10 ; i++)
    // {
    //     query.values[i] = A[i]; 
    // }

    // point neigh = neighb( query , root , distance );
    
    // cout<<"Neighbour: ";
    // print_point(neigh);

    // cout<<" Distance: "<<distance(query,neigh)<<"\n";

    vector <struct data> queryset;
    read_query(queryset);

    int counter=0;

    for(int i=0;i<100;i++){
        point a= neighbour(queryset[i], root, distance);

        point b= neighb(queryset[i], dataset, distance);

        if(equal(a,b))
            counter++;
    }
    cout<<counter<<"\n";

    return 0 ; 
}