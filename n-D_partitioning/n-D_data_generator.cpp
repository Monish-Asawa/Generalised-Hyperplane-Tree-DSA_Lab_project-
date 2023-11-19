#include<iostream> 
#include<bits/stdc++.h>

using namespace std ;

# define n 10
# define list_size 200   

struct data {

    float values[n] ; 

} ; 

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

int main () {


    // FILE* file = fopen( "data.txt" , "w") ; 

    ofstream file( "n-D_data.txt" ) ; 

    srand( time( 0 ) ) ; 
    int count = 1 ; 
    struct data list[list_size] ;
 

    struct data temp ; 
    for (int x = 0; x < n ; x++)
    {
        temp.values[x] = rand()%21 - 10 ; 
    }
    list[count-1] = temp ; 
    count++ ; 


    for (int i = 1; i < list_size; i++)
    {
        struct data temp ; 
        for (int x = 0; x < n ; x++)
        {
            temp.values[x] = rand()%21 - 10 ; 
        }
        
        int check = 1 ; 
        for (int x = 0; x < count; x++)
        {
            if ( !compare( temp , list[x] ) )
            {
                i-- ; 
                check = 0 ; 
                break ;
            } 
        }
        if ( check )
        {
            list[count -1 ] = temp ; 
            count ++ ; 
        }
        
    }
    
    for (int i = 0; i < list_size ; i++)
    {
        for (int x = 0; x < n ; x++)
        {
            file << list[i].values[x] ; 
            if ( x != n-1 )
            file << " " ; 
        }
        if ( i != list_size-1 )
        file << endl ; 
    }
    

    file.close() ; 

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


    cout << "Mean: " ; 
    for (int i = 0; i < n ; i++)
    {
        cout << mean.values[i] << " " ; 
    }
    cout << endl ; 

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

    return 0 ; 
}