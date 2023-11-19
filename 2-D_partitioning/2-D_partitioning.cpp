#include<iostream> 
#include<bits/stdc++.h>
#include<vector> 

using namespace std ;

# define n 2   // dimension 
# define list_size 200  // number of points 

struct data {
    float values[n] ; 
} ; 

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

int main () {

// reading file train.txt 
    ifstream file( "2-D_data.txt" ) ; 

    srand( time( 0 ) ) ; 
    int count = 1 ; 
    struct data list[list_size] ;
    
    float value ; 
    for (int i = 0; i < list_size ; i++)
    {
        file >> value ; 
        list[i].values[0] = value ; 

        file >> value ; 
        list[i].values[1] = value ; 
    }
    
// calculating mean vector 
    struct data mean ; 
    mean.values[0] = 0 ; 
    mean.values[1] = 0 ; 

    for (int i = 0; i < list_size ; i++)
    {
        mean.values[0] += list[i].values[0] ; 
        mean.values[1] += list[i].values[1] ; 
    }

    mean.values[0] /= list_size ; 
    mean.values[1] /= list_size ; 

    cout << "Mean: " ; 
    cout << mean.values[0] << " " << mean.values[1] << endl ;


// calculating and storing distances of all points from the mean point 
    vector<pair< float , float >> distances_data ;  

    for (int i = 0; i < list_size ; i++)
    {
        distances_data.push_back( make_pair( i , distance( mean , list[i] ) ) ) ; 
    }

    sort( distances_data.begin() , distances_data.end() , sort_basis) ; 

// printing each distance 
    // cout << "distances : "  ;
    // for ( auto& pair : distances_data)
    // {
    //     cout << pair.second << "    " ; 
    // }
    // cout << endl ; 
    

// indices and distances of potential pivots 
    cout << distances_data[0].first << " " << distances_data[0].second << endl ;  
    cout << distances_data[1].first << " " << distances_data[1].second << endl ;  



    int p0 = 0 , p1 = 0 , i0 = distances_data[0].first , i1 = distances_data[1].first ; 

    cout << "vector 1: " << "( " << list[i0].values[0] << " " << list[i0].values[1] << " )" << endl ; 
    cout << "vector 2: " << "( " << list[i1].values[0] << " " << list[i1].values[1] << " )" << endl ; 

    

    for (int i = 0; i < list_size ; i++)
    {
        if ( distance( list[i] , list[i0]) >= distance( list[i] , list[i1] ))
        {
            p1++ ; 
        }
        else 
        {
            p0++ ; 
        }
    }
    
    cout << "Category 1 : " << p0 << "  Category 2 : " << p1 << endl ; 

    return 0 ; 
}