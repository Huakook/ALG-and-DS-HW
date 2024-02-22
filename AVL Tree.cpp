#include<iostream>
using namespace std ;
const string N = "NULL" ;

template<class T>
class Node
{
//friend class LinkedList ;
public:
    Node() : data( "" ) , prev( NULL ) , next( NULL ){}
    Node( T data ) : data( data ) , prev( NULL ) , next( NULL ){}
    T getData()
    {
        return data ;
    }
    void setData( T data )
    {
        this -> data = data ;
    }
    Node<T> *getPrev()
    {
        return prev ;
    }
    Node<T> *getNext()
    {
        return next ;
    }
    void setPrev( Node<T> *p )
    {
        prev = p ;
    }
    void setNext( Node<T> *n )
    {
        next = n ;
    }
private:
    T data ;
    Node<T> *prev , *next ;
};

template<class T>
class LinkedList
{
public:
    LinkedList()
    {
        head = NULL ;
        tail = NULL ;
    }
    void addToHead( T data )
    {
        Node<T> *newNode = new Node<T>( data ) ;
        if( head == NULL )
        {
            head = newNode ;
            tail = newNode ;
        }else{
            head -> setPrev( newNode ) ;
            newNode -> setNext( head ) ;
            head = newNode ;
        }
    }

    void addToTail( T data )
    {
        Node<T> *newNode = new Node<T>( data ) ;
        if( head == NULL )
        {
            head = newNode ;
            tail = newNode ;
        }else{
            tail -> setNext( newNode ) ;
            newNode -> setPrev( tail ) ;
            tail = newNode ;
        }
    }
    T *deleteFromHead()
    {
        if( head == NULL )
        {
            return NULL ;
        }
        T *tmp =  new T( head -> getData() ) ;
        if( head == tail )
        {
            delete head ;
            head = NULL ;
            tail = NULL ;
        }else{
            head = head -> getNext() ;
            delete head -> getPrev() ;
            head -> setPrev( NULL ) ;
        }
        return tmp ;
    }
    T *deleteFromTail()
    {
        if( head == NULL )
        {
            return NULL ;
        }
        T *tmp = new T( tail -> getData() ) ;
        if( head == tail )
        {
            delete head ;
            head = NULL ;
            tail = NULL ;
        }else{
            tail = tail -> getPrev() ;
            delete tail -> getNext() ;
            tail -> setNext( NULL ) ;
        }
        return tmp ;
    }
    Node<T> *getTail()
    {
        return tail ;
    }
    Node<T> *getHead()
    {
        return head ;
    }
    bool empty()
    {
        if( head == NULL )
        {
            return true ;
        }
        return false ;
    }
    int size()
    {
        int s = 0 ;
        for( Node<T> *ptr = head ; ptr ; ptr = ptr -> getNext() )
        {
            s++ ;
        }
        return s ;
    }
    ~LinkedList()
    {
        while( head )
        {
            delete deleteFromHead() ;
        }
    }
private:
    Node<T> *head , *tail ;
};

template<class T>
class Queue
{
public:
    Queue()
    {
        list = new LinkedList<T> ;
    }
    void enqueue( T data )
    {
        list -> addToTail( data ) ;
    }
    T *dequeue()
    {
        return list -> deleteFromHead() ;
    }
    int size()
    {
        return list -> size() ;
    }
    bool empty()
    {
        return list -> empty() ;
    }
    ~Queue()
    {
        delete list ;
    }
private:
    LinkedList<T> *list ;
};

template<class T>
class Stack
{
public:
    Stack()
    {
        list = new LinkedList<T> ;
    }
    void push( T data )
    {
        list -> addToTail( data ) ;
    }
    T *pop()
    {
        return list -> deleteFromTail() ;
    }
    int size()
    {
        return list -> size() ;
    }
    bool empty()
    {
        return list -> empty() ;
    }
    ~Stack()
    {
        delete list ;
    }
private:
    LinkedList<T> *list ;
};

template<class T>
class TreeNode {
  public:
      TreeNode()
      {
          left = NULL ;
          right = NULL ;
          parent = NULL ;
          data = 0 ;
      }
      TreeNode( T d )
      {
          left = NULL ;
          right = NULL ;
          parent = NULL ;
          data = d ;
      }
      TreeNode( T d , TreeNode<T> *l , TreeNode<T> *r )
      {
          data = d ;
          left = l ;
          right = r ;
          parent = NULL ;
      }

      T getData() const
      {
          return data ;
      }
      TreeNode<T> *&getLeft()
      {
          return left ;
      }
      TreeNode<T> *&getRight()
      {
          return right ;
      }
      TreeNode<T> *getParent()
      {
          return parent ;
      }

      void setData( T d )
      {
          data = d ;
      }
      void setLeft( TreeNode<T> *l )
      {
          left = l ;
          if( l )
          {
              l -> setParent( this ) ;
          }
      }
      void setRight( TreeNode<T> *r )
      {
          right = r ;
          if( r )
          {
              r -> setParent( this ) ;
          }
      }
      void setParent( TreeNode<T> *p )
      {
          parent = p ;
      }
  private:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent ;
};


template<class T>
class binarySearchTree {
  public:
    virtual void preorder() = 0;
    virtual void inorder() = 0;
    virtual void postorder() = 0;
    virtual void levelorder() = 0;
    virtual bool insert(T data) = 0;
    virtual void setRoot(T data) = 0;
    virtual TreeNode<T> *search(T target) = 0;
    virtual bool deSerialize(string tree) = 0;
    virtual void serialize() = 0;
    virtual bool isValidSerialization( string tree ) = 0 ;
    virtual bool isValidBinarySearchTree() = 0 ;
  protected:
    TreeNode<T> *root;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T>
{
public:
    BinarySearchTree()
    {
        num = 0 ;
        type = 0 ;
        this -> root = NULL ;
    }

    int _count( TreeNode<T> *root )
    {
        if( root == NULL )
        {
            return 0 ;
        }
        return 1 + _count( root -> getLeft() ) + _count( root -> getRight() ) ;
    }

    int count()
    {
        return _count( this -> root ) ;
    }

    TreeNode<T> *_search( TreeNode<T> *root , T target )
    {
        if( root == NULL )
        {
            return NULL ;
        }
        if( root -> getData() == target )
        {
            return root ;
        }
        if( type )
        {
            if( smaller( root -> getData() , target ) )
            {
                return _search( root -> getRight() , target ) ;
            }else{
                return _search( root -> getLeft() , target ) ;
            }
        }else{
            if( root -> getData() > target )
            {
                return _search( root -> getLeft() , target ) ;
            }else{
                return _search( root -> getRight() , target ) ;
            }
        }
    }

    TreeNode<T> *search( T target )
    {
        return _search( this -> root , target ) ;
    }

    void preorder()
    {
        int flag = 0 ;
        _preorder( this -> root , flag ) ;
        cout << endl ;
    }

    void _preorder( TreeNode<T> *root , int &flag )
    {
        if( root == NULL )
        {
            return ;
        }
        if( flag )
        {
            cout << "," << root -> getData() ;
        }else{
            cout << root -> getData() ;
            flag = 1 ;
        }
        _preorder( root -> getLeft() , flag ) ;
        _preorder( root -> getRight() , flag ) ;
    }

    void inorder()
    {
        int flag = 0 ;
        _inorder( this -> root , flag ) ;
        cout << endl ;
    }

    void _inorder( TreeNode<T> *root , int &flag )
    {
        if( root == NULL )
        {
            return ;
        }
        _inorder( root -> getLeft() , flag ) ;
        if( flag )
        {
            cout << "," << root -> getData() ;
        }else{
            cout << root -> getData() ;
            flag = 1 ;
        }
        _inorder( root -> getRight() , flag ) ;
    }

    void postorder()
    {
        int flag = 0 ;
        _postorder( this -> root , flag ) ;
        cout << endl ;
    }

    void _postorder( TreeNode<T> *root , int &flag )
    {
        if( root == NULL )
        {
            return ;
        }
        _postorder( root -> getLeft() , flag ) ;
        _postorder( root -> getRight() , flag ) ;
        if( flag )
        {
            cout << "," << root -> getData() ;
        }else{
            cout << root -> getData() ;
            flag = 1 ;
        }
    }

    int _height( TreeNode<T> *root )
    {
        if( root == NULL )
        {
            return 0 ;
        }
        int lh = _height( root -> getLeft() ) ;
        int rh = _height( root -> getRight() ) ;
        if( lh > rh )
        {
            return lh + 1 ;
        }else{
            return rh + 1 ;
        }
    }

    int height()
    {
        return _height( this -> root ) ;
    }

    void onLevel( TreeNode<T> *root , int level , int &flag )
    {
        if( root == NULL )
        {
            return ;
        }
        if( level == 0 )//as level = 0, it reaches the level x which is the initial value given when the function is first called
        {
            if( flag )
            {
                cout << "," << root -> getData() ;
            }else{
                cout << root -> getData() ;
                flag = 1 ;
            }
        }
        if( level > 0 )
        {
            onLevel( root -> getLeft() , level - 1 , flag ) ;
            onLevel( root -> getRight() , level - 1 , flag ) ;
        }
    }

    void levelorder()
    {
        int h = height() ;
        int flag = 0 ;
        for( int i = 0 ; i < h ; i++ )
        {
            onLevel( this -> root , i , flag ) ;
        }
        cout << endl ;
    }

    void levelorder2()
    {
        Queue<TreeNode<T>*> q ;
        if( this -> root == NULL )
        {
            return ;
        }
        q.enqueue( this -> root ) ;
        cout << "_____________________\n" ;
        while( !q.empty() )
        {
            int s = q.size() ;
            for( int i = 0 ; i < s ; i++ )//for each level
            {
                TreeNode<T> **tmp = q.dequeue() ;
                TreeNode<T> *cur = *tmp ;
                delete tmp ;
                if( cur -> getLeft() )
                {
                    q.enqueue( cur -> getLeft() ) ;
                }
                if( cur -> getRight() )
                {
                    q.enqueue( cur -> getRight() ) ;
                }
                cout << cur -> getData() << " " ;
            }
            cout << endl ;
        }
        cout << "________________________\n" ;
    }

    T getIdxData( int idx )
    {
        int bit = 1 , pos = idx , dir = pos % 2 ;
        bit  = bit << 30 ;
        while( !( bit & pos ) && bit )
        {
            bit = bit >> 1 ;
        }
        TreeNode<T> *ptr = this -> root ;
        while( bit > 1 )
        {
            bit = bit >> 1 ;
            if( bit & pos )
            {
                ptr = ptr -> getRight() ;
            }else{
                ptr = ptr -> getLeft() ;
            }
        }
        return ptr -> getData() ;
    }

    TreeNode<T> *getIdx( int idx )
    {
        int bit = 1 , pos = idx , dir = pos % 2 ;
        bit  = bit << 30 ;
        while( !( bit & pos ) && bit )
        {
            bit = bit >> 1 ;
        }
        TreeNode<T> *ptr = this -> root ;
        while( bit > 1 )
        {
            bit = bit >> 1 ;
            if( bit & pos )
            {
                ptr = ptr -> getRight() ;
            }else{
                ptr = ptr -> getLeft() ;
            }
        }
        return ptr ;
    }

    int power( int a , int b )
    {
        int res = 1 ;
        for( int i = 0 ; i < b ; i++ )
        {
            res *= a ;
        }
        return res ;
    }

    void setRoot( T d )
    {
        if( this -> root == NULL )
        {
            this -> root = new TreeNode<T>( d , NULL , NULL ) ;
            return ;
        }
        this -> root -> setData( d ) ;
    }

    void _clear( TreeNode<T> *root )
    {
        if( root == NULL )
        {
            return ;
        }
        _clear( root -> getLeft() ) ;
        _clear( root -> getRight() ) ;
        delete root ;
    }

    void clear()//postorder
    {
        _clear( this -> root ) ;
        this -> root = NULL ;
    }

    void _addN( TreeNode<T> *root , int level )
    {
        if( root == NULL )
        {
            return ;
        }
        if( root -> getData() == N )
        {
            return ;
        }
        if( level == 0 )
        {
            if( root -> getRight() == NULL )
            {
                TreeNode<T> *newNode = new TreeNode<T>( N , NULL , NULL ) ;
                root -> setRight( newNode ) ;
            }
            if( root -> getLeft() == NULL )
            {
                TreeNode<T> *newNode = new TreeNode<T>( N , NULL , NULL ) ;
                root -> setLeft( newNode ) ;
            }
        }
        if( level > 0 )
        {
            _addN( root -> getLeft() , level - 1 ) ;
            _addN( root -> getRight() , level - 1 ) ;
        }
    }

    void addN()
    {
        int h = height() ;
        for( int i = 0 ; i < h - 1 ; i++ )
        {
            _addN( this -> root , i ) ;
        }
    }

    bool _insert( TreeNode<T> *&root , T d )//preorder
    {
        if( root == NULL )
        {
            root = new TreeNode<T>( d , NULL , NULL ) ;
            return true ;
        }
        TreeNode<T> *p = root ;
        if( !type )
        {
            if( root -> getData() > d )
            {
                if( _insert( root -> getLeft() , d ) )
                {
                    root -> setLeft( root -> getLeft() ) ;
                }
            }else{
                if( _insert( root -> getRight() , d ) )
                {
                    root -> setRight( root -> getRight() ) ;//root has been changed
                }
            }
        }else{
            if( smaller( root -> getData() , d ) )
            {
                if( _insert( root -> getRight() , d ) )
                {
                    root -> setRight( root -> getRight() ) ;
                }
            }else{
                if( _insert( root -> getLeft() , d ) )
                {
                    root -> setLeft( root -> getLeft() ) ;
                }
            }
        }
        return false ;
    }

    bool insert( T d )
    {
        if( search( d ) )
        {
            return false ;
        }
        if( isdigit( d[ 0 ] ) )
        {
            type = 1 ;
        }
        _insert( this -> root , d ) ;
        return true ;
    }

    void _serialize( TreeNode<T> *root , int level , int &flag , LinkedList<T> *list , int lastLevel )
    {
        if( root == NULL )
        {
            return ;
        }
        if( level == 0 )
        {
            if( lastLevel )
            {
                list -> addToTail( root -> getData() ) ;
            }else{
                if( flag )
                {
                    if( root -> getData() == N )
                    {
                        cout << ",NULL" ;
                    }else{
                        cout << "," << root -> getData() ;
                    }
                }else{
                    if( root -> getData() == N )
                    {
                        cout << "NULL" ;
                    }else{
                        cout << root -> getData() ;
                    }
                    flag = 1 ;
                }
            }
        }
        if( level > 0 )
        {
            _serialize( root -> getLeft() , level - 1 , flag , list , lastLevel ) ;
            _serialize( root -> getRight() , level - 1 , flag , list , lastLevel ) ;
        }
    }

    bool isChar( char c )
    {
        if( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) )
        {
            return true ;
        }
        return false ;
    }

    bool deSerialize( string tree )
    {
        string tmp = "" ;
        for( int i = 0 ; i < tree.size() ; i++ )
        {
            if( tree[ i ] == ',' || i == tree.size() - 1 )
            {
                if( i == tree.size() - 1 )
                {
                    tmp += tree[ i ] ;
                }
                //cout << "tmp:" << tmp << endl ;

                if( type && tmp != N && !isdigit( tmp[ 0 ] ) && tmp[ 0 ] != '-' )
                {
                    return false ;
                }
                if( !insert( tmp ) )
                {
                    return false ;
                }
                tmp = "" ;
            }else{
                tmp += tree[ i ] ;
            }
        }
        return true ;
    }

    void serialize()//
    {
        if( this -> root == NULL )
        {
            return ;
        }
        addN() ;
        int h = height() ;
        int flag = 0 ;
        LinkedList<T> *list = new LinkedList<T> ;
        for( int i = 0 ; i < h ; i++ )
        {
            if( i == h - 1 )
            {
                _serialize( this -> root , i , flag , list , 1 ) ;
            }else{
                _serialize( this -> root , i , flag , list , 0 ) ;
            }
        }
        while( list -> getTail() -> getData() == N )
        {
            list -> deleteFromTail() ;
        }
        for( Node<T> *ptr = list -> getHead() ; ptr != NULL ; ptr = ptr -> getNext() )
        {
            if( flag )
            {
                if( ptr -> getData() == N )
                {
                    cout << ",NULL" ;
                }else{
                    cout << "," << ptr -> getData() ;
                }
            }else{
                if( ptr -> getData() == N )
                {
                    cout << "NULL" ;
                }else{
                    cout << ptr -> getData() ;
                }
                flag = 1 ;
            }
        }
        cout << endl ;
    }

    bool isValidSerialization( string tree )
    {
        if( tree[ 0 ] == ',' || tree[ tree.size() - 1 ] == ',' )
        {
            return false ;
        }
        if( isdigit( tree[ 0 ] ) || tree[ 0 ] == '-' )
        {
            type = 1 ;
        }
        for( int i = 0 ; i < tree.size() ; i++ )
        {
            if( !isChar( tree[ i ] ) && !isdigit( tree[ i ] ) && tree[ i ] != ',' && tree[ i ] != '-' )
            {
                return false ;
            }
            if( tree[ i ] == ' ' )
            {
                return false ;
            }
            if( i + 1 < tree.size() && tree[ i ] == ',' && tree[ i + 1 ] == ',' )
            {
                return false ;
            }
        }
        if( !deSerialize( tree ) )
        {
            return false ;
        }
        return true ;
    }

    bool smaller( T a , T b )
    {
        int tmp_a = stoi( a ) ;
        int tmp_b = stoi( b ) ;
        if( tmp_a < tmp_b )
        {
            //cout << tmp_a << " < " << tmp_b << endl ;
            return true ;
        }
        return false ;
    }

    bool inorder( TreeNode<T> *root , T &pre )
    {
        if( root == NULL || root -> getData() == N )
        {
            return true ;
        }
        if( type == 0 )//string
        {
            if( inorder( root -> getLeft() , pre ) && pre < root -> getData() )
            {
                pre = root -> getData() ;
            }else{
                return false ;
            }
        }else{
            //number
            if( inorder( root -> getLeft() , pre ) && ( pre == "" || smaller( pre , root -> getData() ) ) )
            {
                pre = root -> getData() ;
            }else{
                return false ;
            }
        }
        if( inorder( root -> getRight() , pre ) )
        {
            return true ;
        }
        return false ;
    }

    bool _inorder()
    {
        T pre = "" ;
        return inorder( this -> root , pre ) ;
    }

    bool isValidBinarySearchTree()
    {
        if( this -> root == NULL )
        {
            return true ;
        }
        return _inorder() ;
    }
private:
    int num ;
    int type ;//0 -> string, 1 -> number
};

template<class T>
class AVL_Tree : public BinarySearchTree<T>
{
public:
    AVL_Tree():BinarySearchTree<T>(){}
    int balanceFactor( TreeNode<T> *t1 , TreeNode<T> *t2 )
    {
        //left minus right
        /*
        this -> levelorder2() ;
        cout << "t1:" << t1 << " t2:" << t2 << endl ;
        if( t1 )
        {
            cout << "t1 -> data:" << t1 -> getData() << " " ;
        }
        if( t2 )
        {
            cout << "t2 -> data:" << t2 -> getData() ;
        }
        cout << endl ;
        cout << "h1:" << this -> _height( t1 ) << " h2:" << this -> _height( t2 ) << endl ;*/
        return this -> _height( t1 ) - this -> _height( t2 ) ;
    }
    void _balance( TreeNode<T> *&root )
    {
        //cout << "_balance\n" ;
        //if bf < -1 ->> left rotation , if bf > 1 ->> right rotaion
        //L
        if( root == NULL )
        {
            return ;
        }
        /********balance the subtrees first*********/
        _balance( root -> getLeft() ) ;
        _balance( root -> getRight() ) ;
        if( balanceFactor( root -> getLeft() , root -> getRight() ) > 1 )
        {
            //LR
            /************************<0*********************/
            if( balanceFactor( root -> getLeft() -> getLeft() , root -> getLeft() -> getRight() ) < 0 )
            {
                //cout << "LR\n" ;
                //_balance( root -> getLeft() ) ;
                leftRotation( root -> getLeft() ) ;
                rightRotation( root ) ;
            }else /*if( balanceFactor( root -> getLeft() -> getLeft() , root -> getLeft() -> getRight() ) > 1 )*/{
            //LL
                //cout << "LL\n" ;
                rightRotation( root ) ;
            }
        }else if( balanceFactor( root -> getLeft() , root -> getRight() ) < -1 ){//R
            //RL
            /*********************>0********************/
            if( balanceFactor( root -> getRight() -> getLeft() , root -> getRight() -> getRight() ) > 0 )
            {
                //cout << "RL\n" ;
                //_balance( root -> getRight() ) ;
                rightRotation( root -> getRight() ) ;
                leftRotation( root ) ;
            }else{//RR
                //cout << "RR\n" ;
                leftRotation( root ) ;
            }
        }

    }
    void balance()
    {
        if( this -> root == NULL )
        {
            return ;
        }
        _balance( this -> root ) ;
    }
    void rightRotation( TreeNode<T> *&root )
    {
        //cout << "rR\n" ;
        if( root == NULL )
        {
            return ;
        }
        //this -> levelorder2() ;
        //cout << "::" << root -> getData() << endl ;
        TreeNode<T> *tmp_L = root -> getLeft() ;
        root -> setLeft( tmp_L -> getRight() ) ;
        tmp_L -> setRight( root ) ;
        root = tmp_L ;
        //cout << "after:\n" ;
        //this -> levelorder2() ;
    }
    void leftRotation( TreeNode<T> *&root )
    {
        //cout << "lR\n" ;
        if( root == NULL )
        {
            return ;
        }
        //cout << this -> root << root << endl ;
        //this -> levelorder2() ;
        TreeNode<T> *tmp_R = root -> getRight() ;
        //cout << tmp_R << " " << root << " " << tmp_R -> getLeft() << endl ;
        root -> setRight( tmp_R -> getLeft() ) ;
        tmp_R -> setLeft( root ) ;
        root = tmp_R ;
        //cout << this -> root << root << endl ;
        //cout << "after:\n" ;
        //this -> levelorder2() ;
    }

    /*******inorder predecessor OR inorder successor?********/
    TreeNode<T> *_delete( TreeNode<T> *&target )
    {
        if( target == this -> root && !this -> root -> getLeft() && !this -> root -> getRight() )
        {
            this -> root = NULL ;
            return this -> root ;
        }
        if( target -> getLeft() && target -> getRight() )
        {//has two children
          /***must choose only one of the approaches finding the predecessor or successor***/
            //the nodes on the left hand side is more than the right hand side
            //find the largest node smaller than target
            TreeNode<T> *ptr = target -> getLeft() ;
            while( ptr -> getRight() )
            {
                ptr = ptr -> getRight() ;
            }
            target -> setData( _delete( ptr ) -> getData() ) ;

            /*int bf = balanceFactor( target -> getLeft() , target -> getRight() ) ;
            if( bf < 0 )
            {//the nodes on the right hand side is more than the left hand side
            //find the smallest node larger than target
                TreeNode<T> *ptr = target -> getRight() ;
                 while( ptr -> getLeft() )
                 {
                     ptr = ptr -> getLeft() ;
                 }
                 target -> setData( _delete( ptr ) -> getData() ) ;
            }else{
            //the nodes on the left hand side is more than the right hand side
            //find the largest node smaller than target
                TreeNode<T> *ptr = target -> getLeft() ;
                 while( ptr -> getRight() )
                 {
                     ptr = ptr -> getRight() ;
                 }
                 target -> setData( _delete( ptr ) -> getData() ) ;
            }*/
        }else if( target -> getLeft() || target -> getRight() ){//has only one child
            if( target -> getParent() -> getRight() == target )
            {
                if( target -> getLeft() )
                {
                    target -> getParent() -> setRight( target -> getLeft() ) ;
                }else{
                    target -> getParent() -> setRight( target -> getRight() ) ;
                }
            }else{
                if( target -> getLeft() )
                {
                    target -> getParent() -> setLeft( target -> getLeft() ) ;
                }else{
                    target -> getParent() -> setLeft( target -> getRight() ) ;
                }
            }
        }else{
        //has no child
            if( target -> getParent() -> getLeft() == target )
            {
                target -> getParent() -> setLeft( NULL ) ;
            }else{
                target -> getParent() -> setRight( NULL ) ;
            }
        }
        balance() ;
        return target ;
    }

    bool Delete( T data )
    {
        TreeNode<T> *target = this -> search( data ) ;
        if( !target )
        {
            return false ;
        }
        _delete( target ) ;
        return true ;
    }
};


int main()
{
    string s = "" ;
    AVL_Tree<string> avt ;
    while( getline( cin , s ) )
    {
        string tmp = "" ;
        for( int i = 7 ; i < s.size() ; i++ )
        {
            tmp += s[ i ] ;
        }
        if( s[ 0 ] == 'i' )
        {
            avt.insert( tmp ) ;
            //avt.levelorder2() ;
            avt.balance() ;
            //avt.levelorder2() ;
        }else{
            //avt.levelorder2() ;
            avt.Delete( tmp ) ;
            avt.balance() ;
            //avt.levelorder2() ;
        }
    }
    avt.serialize() ;
    //avt.levelorder2() ;
    //cout << avt.height() ;
}

/*
insert 20
insert 40
insert 60
insert 80
insert 50
delete 61
delete 60

ANS:
40,20,50,NULL,NULL,NULL,80
*/

/*
insert Phil
insert Carl
insert Matthew
insert Mandel
insert Julia
insert Harriet
delete Mattheww
delete Matthew

ANS:
Julia,Carl,Mandel,NULL,Harriet,NULL,Phil
*/

/*
insert 10
insert 5
insert 11
insert 4
insert 12
insert 2
insert 13

ANS:
10,4,12,2,5,11,13
*/

/*
insert 40
insert 20
insert 10
insert 25
insert 30
insert 22
insert 50

ANS:
25,20,40,10,22,30,50
*/

/*
insert 20
insert 10
insert 25
insert 3

ANS:
20,10,25,3
*/

/*
insert 20
insert 10
insert 25
insert 3
insert 22

ANS:
20,10,25,3,NULL,22
*/

/*
insert 20
insert 10
insert 25
insert 3
insert 22
insert 30
delete 25
*/

/*
insert 14
insert 11
insert 19
insert 7
insert 12
insert 17
insert 53
insert 4
insert 8
insert 13
insert 16
insert 20
insert 60
delete 8
delete 7
delete 11
delete 14
delete 17

ANS:
13,12,19,4,NULL,16,53,NULL,NULL,NULL,NULL,20,60
*/

/*
insert 20
insert 15
insert 30
insert 25
delete 20

ANS:
25,15,30
*/

/*
insert 30
insert 15
insert 25

ANS:
25,15,30
*/

/*
insert 20
insert 40
insert 60

ANS:
40,20,60
*/
