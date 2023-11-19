#include<iostream> 
#include<bits/stdc++.h>
#include<vector> 

using namespace std ;

# define n 10           // dimension 
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

// function to calculate mean of all vectors 
struct data calc_mean( vector<struct data> &list )
{
    struct data mean ; 
    
    for (int i = 0; i < n ; i++)
    {
        mean.values[i] = 0 ; 
    }

    for (int i = 0; i < list_size ; i++)
    {
        for (int x = 0; x < n ; x++)
        {
            mean.values[x] += list[i].values[x] ; 
        }        
    }

    for (int i = 0; i < n ; i++)
    {
        mean.values[i] /= list_size ; 
    }
    
    cout << "Mean: " ; 
    for (int i = 0; i < n ; i++)
    {
        cout << mean.values[i] << " " ; 
    }
    cout << endl ; 

    return mean ; 
}

// reading file and extracting data
void read_file( vector<struct data> &list )
{
    ifstream file( "n-D_data.txt" ) ; 
    // vector<struct data> list ;  
    float value ; 

    for (int i = 0; i < list_size ; i++)
    {
        struct data temp ; 
        for (int x = 0; x < n ; x++)
        {
            file >> value ;
            temp.values[x] = value ;  
        }
        list.push_back( temp ) ;    
    }

    file.close() ; 
}



int main (){

// reading file train.txt 
    vector<struct data> list ;
    read_file( list ) ;  

// calculating mean vector 
    struct data mean = calc_mean( list ) ; 

// calculating and storing distances of all vectors from the mean vector
    vector<pair< float , float >> distances_data ;  
    for (int i = 0; i < list_size ; i++)
    {
        distances_data.push_back( make_pair( i , distance( mean , list[i] ) ) ) ; 
    }


// indices and distances of potential pivots 
    sort( distances_data.begin() , distances_data.end() , sort_basis) ; 
    cout << distances_data[0].first << " " << distances_data[0].second << endl ;  
    cout << distances_data[1].first << " " << distances_data[1].second << endl ;  

    int p1 = 0 , p2 = 0 , i1 = distances_data[0].first , i2 = distances_data[1].first ; 

    cout << "\nPivot 1: " << "( " << list[i1].values[0] << " " << list[i1].values[1] << " )" << endl ; 
    cout << "Pivot 2: " << "( " << list[i2].values[0] << " " << list[i2].values[1] << " )\n" << endl ; 

    for (int i = 0; i < list_size ; i++)
    {
        if ( distance( list[i] , list[i1]) >= distance( list[i] , list[i2] ))
        p2++ ; 
        else 
        p1++ ; 
    }
    
    cout << "Group_1 : " << p1 << "  Group_2 : " << p2 << endl ; 

    return 0 ; 
}