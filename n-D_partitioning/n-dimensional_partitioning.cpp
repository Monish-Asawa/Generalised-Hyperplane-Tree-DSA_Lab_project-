#include<iostream> 
#include<bits/stdc++.h>
#include<vector> 

using namespace std ;

# define n 10           // dimension 
# define list_size 100  // number of points 

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

    for (int i = 0; i < list.size() ; i++)
    {
        for (int x = 0; x < n ; x++)
        {
            mean.values[x] += list[i].values[x] ; 
        }        
    }

    for (int i = 0; i < n ; i++)
    {
        mean.values[i] /= list.size() ; 
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

void find_pivots( vector<struct data> &list , vector<struct data> &pivots ) 
{
    struct data mean = calc_mean( list ) ; 

    vector<pair< float , float >> distances_data ;  
    for (int i = 0; i < list.size() ; i++)
    {
        distances_data.push_back( make_pair( i , distance( mean , list[i] ) ) ) ; 
    }

    sort( distances_data.begin() , distances_data.end() , sort_basis) ; 
    cout << distances_data[0].first << " " << distances_data[0].second << endl ;  
    cout << distances_data[1].first << " " << distances_data[1].second << endl ;  

    int p1 = 0 , p2 = 0 , i1 = distances_data[0].first , i2 = distances_data[1].first ; 

    cout << "\nPivot 1: " << "( " << list[i1].values[0] << " " << list[i1].values[1] << " )" << endl ; 
    cout << "Pivot 2: " << "( " << list[i2].values[0] << " " << list[i2].values[1] << " )\n" << endl ; 



    pivots.push_back( list[i1] ) ;
    pivots.push_back( list[i2] ) ;

}

using groups = vector< vector<struct data> > ; 

groups create_groups( vector<struct data> pivots , vector<struct data> &list ){

    vector<struct data> list0 , list1 ;  


    for (int i = 0; i < list.size() ; i++)
    {
        if ( distance( list[i] , pivots[0] ) >= distance( list[i] , pivots[1] ))
        {
            if ( compare( list[i] , pivots[1] ))
            list1.push_back( list[i] ) ; 
        }
        else 
        {
            if ( compare( list[i] , pivots[0] ))
            list0.push_back( list[i] ) ; 
        }
    }
    
    groups group_union ;
    group_union.push_back( list0 ) ; 
    group_union.push_back( list1 ) ;  
    cout << "Group_1 : " << group_union[0].size() << "  Group_2 : " << group_union[1].size() << endl ; 

    return group_union ; 
}   


// void recursive_partition( vector<struct data> &list )
// {
//     if ( (list).size() > 2 )
//     {
//         vector<struct data> pivots ;
//         find_pivots( list , &pivots );

//         groups group1 = create_groups( pivots , list ) ;

//         recursive_partition( &group1[0] ) ; 
//         recursive_partition( &group1[1] ) ;  
//     }
// }

int main (){

// reading file train.txt 
    vector<struct data> list ;
    read_file( list ) ;  



    vector<struct data> pivots ;
    find_pivots( list , pivots ) ;

    groups groups1 ; 
    groups1 = create_groups( pivots , list ) ; 


    // cout << "values of group1 " << endl ;
    // for (int i = 0; i < groups1[0].size() ; i++)
    // {
    //     for (int x = 0; x < n ; x++)
    //     {
    //         cout << groups1[0][i].values[x] << " " ; 
    //     }
    //     cout << endl ; 
    // }
    

    // vector<struct data> pivots_n0 ;
    // find_pivots( groups1[0] , pivots_n0 ) ; 
    
    // groups groups2 ; 
    // groups2 = create_groups( pivots_n0 , groups1[0] ) ; 

    // vector<struct data> pivots_n1 ;
    // find_pivots( groups1[1] , pivots_n1 ) ; 
    
    // groups groups3 ; 
    // groups3 = create_groups( pivots_n1 , groups1[1] ) ; 


    return 0 ; 
}