#include<iostream> 
#include<bits/stdc++.h>

using namespace std ;

# define n 2
# define list_size 200   

struct data {

    int values[n] ; 

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

    ofstream file( "train.txt" ) ; 

    srand( time( 0 ) ) ; 
    int count = 1 ; 
    struct data list[list_size] ;
 

cout << "hi" << endl ; 

    struct data temp ; 
    for (int x = 0; x < n ; x++)
    {
        temp.values[x] = rand()%21 - 10 ; 
    }
    list[count-1] = temp ; 
    count++ ; 


    for (int i = 1; i < list_size; i++)
    {
        cout << "hi " << i << endl ; 

        struct data temp ; 
        for (int x = 0; x < n ; x++)
        {
            temp.values[x] = rand()%21 - 10 ; 
        }

        for (int x = 0; x < n ; x++)
        {
            cout << temp.values[x] << " " ; 
        }
        cout << endl ; 
        
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
        file << "( " ; 
        for (int x = 0; x < n ; x++)
        {
            file << list[i].values[x] ; 
            if ( x != n-1 )
            file << " , " ; 
            else 
            file << " )" ;
        }
        file << endl ; 
    }
    

    // fclose( file ) ; 

    file.close() ; 

    return 0 ; 
}