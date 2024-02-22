#include<iostream>
#include<climits>
#include<string>
#include<cmath>
#include<fstream>
using namespace std ; 
const int inf = INT_MAX ;
int N , **record , pow_2_N , start , end ;  ;// number of cities
double **coordinate , **dp , **cost  ;
ifstream inFile ; 
/*
Time complexity: O( 2 ^ N * N )
Space complexity: O( 2 ^ N * N )
*/

void init() ; 
void initCoordinate() ; 
void input()
{
    inFile >> N ;
    init() ; 
    int tmp ;
    for( int i = 0 ; i < N ; i++ )
    {
        inFile >> tmp >> coordinate[ i ][ 0 ] >> coordinate[ i ][ 1 ] ; 
    }
    initCoordinate() ; 
}

void printCoordinate()
{
    for( int i = 0 ; i < N ; i++ )
    {
        for( int j = 0 ; j < 2 ; j++ )
        {
            cout << coordinate[ i ][ j ] << " " ; 
        }cout << endl ; 
    }
}

void printCost()
{
    cout << "Cost: \n" ;
    for( int i = 0 ; i < N ; i++ )
    {
        for( int j = 0 ; j < N ; j++ )
        {
            cout << cost[ i ][ j ] << " " ;
        }cout << endl ;
    }cout << endl ;
}

void printDp()
{
    cout << "DP: \n" ;
    for( int i = 0 ; i < pow( 2 , N ) ; i++ )
    {
        for( int j = 0 ; j < N ; j++ )
        {
            if( dp[ i ][ j ] == inf ) cout << "X" ;
            else cout << dp[ i ][ j ] << " " ;
        }cout << endl ;
    }cout << endl ;
}

void init()
{
    pow_2_N = pow( 2 , N ) ; 
    //pow_2_N = 10 ; 
    coordinate = new double*[ N ] ; 
    for( int i = 0 ; i < N ; i++ ) coordinate[ i ] = new double[ 2 ] ; 

    dp = new double*[ pow_2_N ] ;
    for( int i = 0 ; i < pow_2_N ; i++ ) dp[ i ] = new double[ N ] ;
    for( int i = 0 ; i < pow_2_N ; i++ ) for( int j = 0 ; j < N ; j++ ) dp[ i ][ j ] = inf ; 
    cost = new double*[ N ] ;
    for( int i = 0 ; i < N ; i++ ) cost[ i ] = new double[ N ] ;

    record = new int*[ pow_2_N ] ;
    for( int i = 0 ; i < pow_2_N ; i++ ) record[ i ] = new int[ N ] ;  
}

void initCoordinate()
{
    for( int i = 0 ; i < N ; i++ )
    {
        for( int j = 0 ; j < N ; j++ ) 
        {   
            //cout << "i:" << i << " j:" << j << " " << sqrt( pow( coordinate[ i ][ 0 ] - coordinate[ j ][ 0 ] , 2 ) + pow( coordinate[ i ][ 1 ] - coordinate[ j ][ 1 ] , 2 ) ) << endl ; 
            cost[ i ][ j ] = sqrt( pow( coordinate[ i ][ 0 ] - coordinate[ j ][ 0 ] , 2 ) + pow( coordinate[ i ][ 1 ] - coordinate[ j ][ 1 ] , 2 ) ) ; 
        }
    }
}

string traceBack( int , int ) ; 

void solve()
{
    //printCoordinate() ; 
    //printCost() ; 
    for( int i = 0 ; i < pow_2_N ; i++ )
    {
        for( int j = 0 ; j < N ; j++ )
        {
            //if the j-th is NOT included in the set i ->> the j-th item cannot be the end of the set ->> the table[ i ][ j ] is X  
            int p = pow( 2 , j ) ;
            if( p == i )
            {
                dp[ i ][ j ] = 0 ; 
                record[ i ][ j ] = -1 ; 
            }else if( i & p ){
                for( int k = 0 ; k < N ; k++ )
                {
                    int tmp = i - pow( 2 , j ) ;
                    if( tmp < 0 ) continue ; 
                    //cout << dp[ tmp ][ k ] << " " << dp[ tmp ][ k ] << " " << cost[ k ][ j ] << endl ; 
                    if( static_cast<int>( dp[ tmp ][ k ] ) < inf - 100 && dp[ i ][ j ] > dp[ tmp ][ k ] + cost[ k ][ j ] )
                    {
                        //cout << "YES\n" ; 
                        dp[ i ][ j ] = dp[ tmp ][ k ] + cost[ k ][ j ] ;
                        record[ i ][ j ] = k ; 
                    }
                }
            }else{
                dp[ i ][ j ] = inf ; 
                record[ i ][ j ] = -1 ; 
            }
        }
    }

    double min = inf ; 
    ::end = -1 ; 
    for( int i = 0 ; i < N ; i++ )
    {
        traceBack(pow_2_N - 1 , i ) ;
        //cout << dp[ pow_2_N - 1 ][ i ] + cost[ i ][ start ] << "   " ; 
        if( min > dp[ pow_2_N - 1 ][ i ] + cost[ i ][ start ] )
        {
            min = dp[ pow_2_N - 1 ][ i ] + cost[ i ][ start ] ;
            ::end = i ; 
        }
    }
    //cout << min << " " << end ;
    //cout << " !!! " << record[ pow_2_N - 1 ][ static_cast<int>( end ) ] ; 
    //printDp() ;
    cout << "path:" ; 
    cout << traceBack( pow_2_N - 1 , ::end ) ; 
    cout << ::end + 1 << " " << start + 1 ; 
    cout << endl << "minlength:" << min << endl ;
}

string traceBack( int i , int j )
{
    //cout << "i:" << i << " j:" << j << endl ; 
    if( record[ i ][ j ] < 0 )
    {
        start = j ; 
        return "" ; 
    }
    return traceBack( i - static_cast<int>( pow( 2 , j ) ) , record[ i ][ j ] ) + to_string( record[ i ][ j ] + 1 ) + " " ; 
}

int main()
{
    inFile.open("dp test case.txt") ; 
    input() ;
    solve() ;
} 

/*
20
1 37 52
2 49 49
3 52 64
4 20 26
5 40 30
6 21 47
7 17 63
8 31 62
9 52 33
10 51 21
11 42 41
12 31 32
13 5 25
14 12 42
15 36 16
16 52 41
17 27 23
18 17 33
19 13 13
20 57 58
ANS:
path:3 20 2 11 16 9 10 15 5 12 17 4 19 13 18 14 6 7 8 1 3
minlength:243.179
*/


/*
10
1 37 52
2 49 49
3 52 64
4 20 26
5 40 30
6 21 47
7 17 63
8 31 62
9 52 33
10 51 21
ANS:
path:4 5 10 9 2 3 1 8 7 6 4
minlength:160.649
*/