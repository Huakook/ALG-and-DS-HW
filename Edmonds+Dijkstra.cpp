#include<iostream>
#include<climits>
using namespace std ;
const int inf = INT_MAX ;
int V , E , s , t , **capacity , **flow , **residual , **weight , bottleneck , *visited , *parent , *shortest ;
//Let the 0-th vertex be s and the ( |V| - 1 )th vertex be t
//DIRECTED GRAPH

void init() ;
void input()
{
    cout << "Enter the number of vertex and edges: \n" ;
    cin >> V >> E ;
    int v1 , v2 , cap , w ;
    init() ;
    cout << "Enter the edges info( v1 v2 capacity weight ): \n" ;
    for( int i = 0 ; i < E ; i++ )
    {
        cin >> v1 >> v2 >> cap >> w ;
        capacity[ v1 ][ v2 ] = cap ;
        weight[ v1 ][ v2 ] = w ;
    }
    cout << "Enter the source and sink vertex: \n" ;
    cin >> s >> t ;
}

void init()
{
    capacity = new int*[ V ] ;
    for( int i = 0 ; i < V ; i++ ) capacity[ i ] = new int[ V ] ;
    flow = new int*[ V ] ;
    for( int i = 0 ; i < V ; i++ ) flow[ i ] = new int[ V ] ;
    residual = new int*[ V ] ;
    for( int i = 0 ; i < V ; i++ ) residual[ i ] = new int[ V ] ;
    weight = new int*[ V ] ;
    for( int i = 0 ; i < V ; i++ ) weight[ i ] = new int[ V ] ;
    for( int i = 0 ; i < V ; i++ ) for( int j = 0 ; j < V ; j++ )
    {
         //capacity[ i ][ j ] = residual[ i ][ j ] = i == j ? 0 : -inf ;
         capacity[ i ][ j ] = -inf ;
         flow[ i ][ j ] = 0 ;
         weight[ i ][ j ] = inf ;
    }

    shortest = new int[ V ] ;
    visited = new int[ V ] ;
    for( int i = 0 ; i < V ; i++ ) visited[ i ] = 0 ;
    parent = new int[ V ] ;
}

void setResidual()
{
    for( int i = 0 ; i < V ; i++ )
    {
        for( int j = 0 ; j < V ; j++ )
        {
            if( capacity[ i ][ j ] != -inf )
            {//the edge exists
                if( capacity[ i ][ j ] - flow[ i ][ j ] > 0 ) residual[ i ][ j ] = capacity[ i ][ j ] - flow[ i ][ j ] ;
            }else if( capacity[ j ][ i ] != -inf ){
                residual[ i ][ j ] = flow[ j ][ i ] ;
            }else{
                residual[ i ][ j ] = 0 ;
            }
        }
    }
}

void initVisited()
{
    for( int i = 0 ; i < V ; i++ ) visited[ i ] = 0 ;
}

void initParent()
{
    for( int i = 0 ; i < V ; i++ ) parent[ i ] = -1 ;
}

void initShortest()
{
    for( int i = 0 ; i < V ; i++ ) shortest[ i ] = weight[ s ][ i ] ;
}

void printParent()
{
    for( int i = 0 ; i < V ; i++ )
    {
        cout << parent[ i ] << " " ; 
    }cout << endl ;
}

bool findPath()//Dijkstra
{
    initShortest() ;
    initVisited() ;
    initParent() ;
    //start from s
    int pre = s ;
    visited[ s ] = 1 ;
    for( int i = 0 ; i < V - 1 ; i++ )
    {//select V - 1 vertex
        //find the minimum cost edge from s
        int minCost = inf , minVertex = -1 ;
        for( int j = 0 ; j < V ; j++ )
        {
            if( !visited[ j ] && minCost > shortest[ j ] )
            {
                minCost = shortest[ j ] ;
                minVertex = j ;
            }
        }
        visited[ minVertex ] = 1 ;
        //check if any path can be updated
        if( minVertex == -1 ) break ;
        if( residual[ pre ][ minVertex ] == -inf || residual[ pre ][ minVertex ] == 0 ) continue ;
        pre = minVertex ;
        for( int j = 0 ; j < V ; j++ )
        {
            /***path from the source vertex to the selected vertex cannot be updated***/
            if( !visited[ j ] && shortest[ minVertex ] != inf && weight[ minVertex ][ j ] != inf && shortest[ j ] > shortest[ minVertex ] + weight[ minVertex ][ j ] )
            {
                shortest[ j ] = weight[ s ][ minVertex ] + weight[ minVertex ][ j ] ;
                parent[ j ] = minVertex ;
            }
        }
    }
    printParent() ;
    //we assume that the vertex |V| - 1 is the sink
    if( parent[ t ] != -1 )//if there's a path from s to t
        return true ;
    else
        return false ; 
}


void printGraph()
{
    for( int i = 0 ; i < V ; i++ )
    {
        for( int j = 0 ; j < V ; j++ )
        {
            cout << flow[ i ][ j ] << "/" ;
            if( capacity[ i ][ j ] != -inf ) cout << capacity[ i ][ j ] ;
            else cout << "X" ;
            cout << " " ;
        }cout << endl ;
    }
}

void printResidualGraph()
{
    for( int i = 0 ; i < V ; i++ )
    {
        for( int j = 0 ; j < V ; j++ )
        {
            cout << residual[ i ][ j ] << " " ;
        }cout << endl ;
    }
}

void solve()
{
    setResidual() ;
    while( findPath() )
    {
        //find the bottleneck
        int cur = t ;
        cout << cur << endl ;
        bottleneck = inf ;
        while( parent[ cur ] != -1 )
        {
            bottleneck = bottleneck < residual[ parent[ cur ] ][ cur ] ? bottleneck : residual[ parent[ cur ] ][ cur ] ;
            cur = parent[ cur ] ;
        }
        //update the flow in graph and the residual graph
        cur = t ;
        while( parent[ cur ] != -1 )
        {
            flow[ parent[ cur ] ][ cur ] += bottleneck ;
            //flow[ cur ][ parent[ cur] ] -= bottleneck ;
            if( capacity[ parent[ cur ] ][ cur ] != -inf )
            {//the edge from parent[ cur ][ cur ] exists
                residual[ parent[ cur ] ][ cur ] = capacity[ parent[ cur ] ][ cur ] - flow[ parent[ cur ] ][ cur ] ;
                residual[ cur ][ parent[ cur ] ] = flow[ parent[ cur ] ][ cur ] ;
            }else if( capacity[ cur ][ parent[ cur ] ] != inf ){
                residual[ cur ][ parent[ cur ] ] = capacity[ cur ][ parent[ cur ] ] - flow[ cur ][ parent[ cur ] ] ;
                residual[ parent[ cur ] ][ cur ] = flow[ cur ][ parent[ cur ] ] ;
            }else{
                residual[ parent[ cur ] ][ cur ] = 0 ;
                residual[ cur ][ parent[ cur ] ] = 0 ;
            }
            cur = parent[ cur ] ;
            //printGraph() ;
        }
        //printResidualGraph() ;
    }
    cout << endl ;
    printGraph() ;
}

int main()
{
    input() ;
    solve() ;   
}

/*
test1:
6 9
0 1 16 1
0 2 13 1
1 3 12 1
2 1 4 1
2 4 14 1
3 2 9 1
4 3 7 1
3 5 20 1
4 5 4 1
0 5
*/

/*
test2:
7 10
0 1 3 
0 2 2 
0 4 5 
1 5 3 
1 6 5 
2 1 3 
2 3 2 
3 5 4 
4 6 3 
5 6 2 
0 6
*/
