#include<iostream>
#include<climits>
using namespace std ;
const int inf = INT_MAX ;
int V , E , s , t , **capacity , **flow , **residual , bottleneck , *queue , q_front , q_rear , *visited , *parent ;
//Let the 0-th vertex be s and the ( |V| - 1 )th vertex be t
//DIRECTED GRAPH

void init() ;
void input()
{
    cout << "Enter the number of vertex and edges: \n" ;
    cin >> V >> E ;
    int v1 , v2 , cap ;
    init() ;
    cout << "Enter the edges info( v1 v2 capacity ): \n" ;
    for( int i = 0 ; i < E ; i++ )
    {
        cin >> v1 >> v2 >> cap ;
        capacity[ v1 ][ v2 ] = cap ;
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
    for( int i = 0 ; i < V ; i++ ) for( int j = 0 ; j < V ; j++ )
    {
         //capacity[ i ][ j ] = residual[ i ][ j ] = i == j ? 0 : -inf ;
         capacity[ i ][ j ] = -inf ;
         flow[ i ][ j ] = 0 ;
    }

    queue = new int[ V ] ;
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

void enqueue( int v )
{
    //cout << "queue[" << q_rear << "] = " << v << endl ;
    queue[ ++q_rear ] = v ;
}

int dequeue()
{
    //cout << "dequeue queue[" << q_front << "] == " << queue[ q_front ] << endl ; 
    return queue[ q_front++ ] ;
}

void initQueue()
{
    q_front = 0 ;//the first accessible element
    q_rear = -1 ;//the last accessible element
    /*if q_front > q_rear, then there's no element accessible in the queue*/    
}

void initVisited()
{
    for( int i = 0 ; i < V ; i++ ) visited[ i ] = 0 ;
}

void initParent()
{
    for( int i = 0 ; i < V ; i++ ) parent[ i ] = -1 ;
}

void printParent()
{
    for( int i = 0 ; i < V ; i++ )
    {
        cout << parent[ i ] << " " ; 
    }cout << endl ;
}

bool findPath()//BFS
{
    initQueue() ;
    initVisited() ;
    initParent() ;
    //add the s into the queue
    enqueue( s ) ;
    visited[ s ] = 1 ;
    
    while( q_front <= q_rear )//there's at least 1 element in the queue
    {
        int cur = dequeue() ;
        visited[ cur ] = 1 ;
        for( int i = 0 ; i < V ; i++ )
        {
            if( !visited[ i ] && residual[ cur ][ i ] != 0 )
            {//if there's an edge from cur to i and vertex i hasn't been visited
                enqueue( i ) ;
                visited[ i ] = 1 ;
                parent[ i ] = cur ;
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
0 1 16
0 2 13
1 3 12
2 1 4
2 4 14
3 2 9
4 3 7
3 5 20
4 5 4
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
