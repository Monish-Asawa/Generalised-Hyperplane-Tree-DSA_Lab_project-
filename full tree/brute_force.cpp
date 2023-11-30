#include<iostream>
#include<cmath>
#include<bits/stdc++.h>
#include<vector>
using namespace std ;

#define dataset_size 200 
#define n 10 

struct data {
    float values[n] ; 
} ;



// calculating distance between two vectors 
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


// additional comparison function for sorting the distances vector 
bool sort_basis( pair<float , float > &a , pair<float , float > &b )
{
    return a.second < b.second ; 
}

struct data neighbour( struct data query , vector<struct data> &dataset )
{
    vector<pair< float , float >> distances_data ;  
    // cout << dataset.size() << endl ; 
    for (int i = 0; i < dataset.size() ; i++)
    {
        distances_data.push_back( make_pair( i , distance( query , dataset[i] ) ) ) ; 
    }

    sort( distances_data.begin() , distances_data.end() , sort_basis) ; 

    // for (int i = 0; i < dataset_size ; i++)
    // {
    //     cout << distances_data[i].second << "     " ; 
    // }
    // cout << endl ; 

    return dataset[distances_data[0].first] ; 
}

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

int main () {

    vector<struct data> dataset ;
    read_file( dataset ) ;

    struct data n0 , query ; 

    int A[10] = { 3 , 1 ,-5 , 7 ,2 , 9 , 7 } ; 
    for (int i = 0; i < 10 ; i++)
    {
        query.values[i] = 1; 
    }
    

    n0 = neighbour( query , dataset ) ; 


    cout << "Neighbour: " ; 
    for (int i = 0; i < 10 ; i++)
    {
        cout << n0.values[i] << " " ; 
    }
    cout<<" Distance: "<<distance(query,n0); 
    cout << endl ;

    return 0 ; 
}