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
    T &getData()
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
    T last()
    {
        return list -> getTail() -> getData() ;
    }
    void deleteFromTail()
    {
        list -> deleteFromTail() ;
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
class RBTree ;

template<class T>
class RBTreeNode
{
friend class RBTree<T> ;
public:
    RBTreeNode()
    {
        color = 0 ;
        left = right = parent = NULL ;
    }
    RBTreeNode( T d )
    {
        data = d ;
        color = 0 ;
        left = right = parent = NULL ;
    }
    T &getData()/************/
    {
        return data ;
    }
private:

    int getColor()
    {
        return color ;
    }
    RBTreeNode<T> *getLeft()
    {
        return left ;
    }
    RBTreeNode<T> *getRight()
    {
        return right ;
    }
    RBTreeNode<T> *getParent()
    {
        return parent ;
    }
    RBTreeNode<T> *getSibling()
    {
        if( parent == NULL )
        {
            return NULL ;
        }
        if( parent -> getLeft() == this )
        {
            return parent -> getRight() ;
        }
        return parent -> getLeft() ;
    }
    RBTreeNode<T> *getGrandFather()
    {
        if( parent )
        {
            return parent -> getParent() ;
        }
        return NULL ;
    }
    bool isRed()
    {
        if( color == 0 )
        {
            return true ;
        }
        return false ;
    }
    bool isLeft()
    {
        if( parent && parent -> getLeft() == this )
        {
            return true ;
        }
        return false ;
    }
    void setData( T  d )
    {
        data = d ;
    }
    void setRed()
    {
        color = 0 ;
    }
    void setBlack()
    {
        color = 1 ;
    }
    void setColor( int c )
    {
        color = c ;
    }
    void swapColor( RBTreeNode<T> *n )
    {
        int tmp = color ;
        color = n -> getColor() ;
        n -> setColor( tmp ) ;
    }
    void setLeft( RBTreeNode<T> *l )
    {
        left = l ;
        if( l )
        {
            l -> setParent( this ) ;
        }
    }
    void setRight( RBTreeNode<T> *r )
    {
        right = r ;
        if( r )
        {
            r -> setParent( this ) ;
        }
    }
    void setParent( RBTreeNode<T> *p )
    {
        parent = p ;
    }
    T data ;
    int color ;//0 ->> red , 1 ->> black
    RBTreeNode<T> *left , *right , *parent ;
};

bool smaller( string a , string b )
{
    if( stoi( a ) < stoi( b ) )
    {
        return true ;
    }
    return false ;
}

template<class T>
class RBTree
{
public:
    RBTree()
    {
        root = NULL ;
        type = 0 ;
    }
    string serialize()
    {
        string s = "" ;
        if( root == NULL )
        {
            return s ;
        }
        Queue<RBTreeNode<T>*> q ;
        Queue<string> data ;
        q.enqueue( root ) ;
        while( !q.empty() )
        {
            RBTreeNode<T> **tmp = q.dequeue() ;
            RBTreeNode<T> *cur = *tmp ;
            delete tmp ;
            if( cur == NULL )
            {
                data.enqueue( N ) ;
            }else{
                data.enqueue( cur -> getData() ) ;
                q.enqueue( cur -> getLeft() ) ;
                q.enqueue( cur -> getRight() ) ;
            }
        }
        while( !data.empty() && data.last() == N )
        {
            data.deleteFromTail() ;
        }
        while( !data.empty() )
        {
            if( data.size() == 1 )
            {
                s += *data.dequeue() ;
            }else{
                s += *data.dequeue() + ',' ;
            }
        }
        return s ;
    }
    void levelOrder()
    {
        if( root == NULL )
        {
            return ;
        }
        cout << "___________________\n" ;
        Queue<RBTreeNode<T>*> q ;
        int loop = 0 ;
        q.enqueue( root ) ;
        while( !q.empty() )
        {
            loop++ ;
            if( loop > 20 )
            {
                break ;
            }
            int s = q.size() ;
            for( int i = 0 ; i < s ; i++ )//for each level
            {
                RBTreeNode<T> **tmp = q.dequeue() ;
                RBTreeNode<T> *cur = *tmp ;
                delete tmp ;
                if( cur == NULL )
                {
                    cout << "NULL " ;
                    continue ;
                }
                cout << cur -> getData() ;
                if( cur -> isRed() )
                {
                    cout << "(R)" ;
                }else{
                    cout << "(B)" ;
                }
                /*
                if( cur -> getParent() )
                {
                    cout << "[" << cur -> getParent() -> getData() << "]" ;
                }else{
                    cout << "no par" ;
                }*/
                cout << " " ;
                q.enqueue( cur -> getLeft() ) ;
                q.enqueue( cur -> getRight() ) ;
            }
            cout << endl ;
        }
        cout << "______________________\n" ;
    }
    RBTreeNode<T> *insert( T data )
    {
        if( search( data ) )
        {
            return NULL ;
        }
        if( isdigit( data.getFirst()[ 0 ] ) )/*************************************************/
        {
            setTypeNum() ;
        }
        if( root == NULL )
        {
            setRoot( data ) ;
        }else{
            RBTreeNode<T> *ptr = root ;
            if( typeChar() )
            {
                while( ptr )
                {
                    if( data.getFirst() < ptr -> getData().getFirst() )/*************************************/
                    {
                        if( ptr -> getLeft() == NULL )
                        {
                            RBTreeNode<T> *newNode = new RBTreeNode<T>( data ) ;
                            ptr -> setLeft( newNode ) ;
                            insert_fix( ptr -> getLeft() ) ;
                            return newNode ;
                        }
                        ptr = ptr -> getLeft() ;
                    }else{
                        if( ptr -> getRight() == NULL )
                        {
                            RBTreeNode<T> *newNode = new RBTreeNode<T>( data ) ;
                            ptr -> setRight( newNode ) ;
                            insert_fix( ptr -> getRight() ) ;
                            return newNode ;
                        }
                        ptr = ptr -> getRight() ;
                    }
                }
            }else{
                while( ptr )
                {
                    //if( smaller( data.getSecond() , ptr -> getData().getSecond() ) )/***************************************************/
                    if( data.getFirst() < ptr -> getData().getFirst() )/*********************************************/
                    {
                        if( ptr -> getLeft() == NULL )
                        {
                            RBTreeNode<T> *newNode = new RBTreeNode<T>( data ) ;
                            ptr -> setLeft( newNode ) ;
                            insert_fix( ptr -> getLeft() ) ;
                            return newNode ;
                        }
                        ptr = ptr -> getLeft() ;
                    }else{
                        if( ptr -> getRight() == NULL )
                        {
                            RBTreeNode<T> *newNode = new RBTreeNode<T>( data ) ;
                            ptr -> setRight( newNode ) ;
                            insert_fix( ptr -> getRight() ) ;
                            return newNode ;
                        }
                        ptr = ptr -> getRight() ;
                    }
                }
            }
        }
        root -> setBlack() ;
        return root ;
    }
    bool remove( T data )
    {
        RBTreeNode<T> *target = search( data ) ;
        if( !target )
        {
            //cout << data << " is not founded.\n" ;
            return false ;
        }
        _remove( target ) ;
        if( root )
        {
            root -> setBlack() ;
        }
        return true ;
    }
protected:
    RBTreeNode<T> *root ;
    int type ;//0 ->> char , 1 ->> num

    void setRoot( T data )
    {
        root = new RBTreeNode<T>( data ) ;
        root -> setBlack() ;
    }
    RBTreeNode<T> *getRoot()
    {
        return root ;
    }
    bool typeChar()
    {
        if( type == 0 )
        {
            return true ;
        }
        return false ;
    }
    void setTypeNum()
    {
        type = 1 ;
    }
    RBTreeNode<T> *search( T data )
    {
        RBTreeNode<T> *ptr = root ;
        if( typeChar() )
        {
            while( ptr )
            {
                if( ptr -> getData() == data )
                {
                    return ptr ;
                }
                if( data.getFirst() < ptr -> getData().getFirst() )/************************/
                {
                    ptr = ptr -> getLeft() ;
                }else{
                    ptr = ptr -> getRight() ;
                }
            }
        }else{
            while( ptr )
            {
                if( ptr -> getData() == data )
                {
                    return ptr ;
                }
                if( data.getFirst() < ptr -> getData().getFirst() )
                {
                    ptr = ptr -> getLeft() ;
                }else{
                    ptr = ptr -> getRight() ;
                }
            }
        }
        return NULL ;
    }
    void insert_fix( RBTreeNode<T> *cur )
    {
        //getch() ;
        //levelOrder() ;
        while( cur -> isRed() && cur -> getParent() && cur -> getParent() -> isRed() )
        {
            if( cur -> getParent() -> getSibling() && cur -> getParent() -> getSibling() -> isRed() )
            {
                //cout << "case1\n" ;
                cur -> getParent() -> setBlack() ;
                cur -> getParent() -> getSibling() -> setBlack() ;
                cur -> getGrandFather() -> setRed() ;
                cur = cur -> getGrandFather() ;
            }else{
                //cout << "case2\n" ;
                if( cur -> getParent() -> isLeft() && cur -> isLeft() )//LL
                {
                    //cout << "LL\n" ;
                    cur -> getParent() -> setBlack() ;
                    cur -> getGrandFather() -> setRed() ;
                    rightRotation( cur -> getGrandFather() ) ;
                }else if( cur -> getParent() -> isLeft() && !cur -> isLeft() ){//LR
                    //cout << "LR\n" ;
                    RBTreeNode<T> *tmp = cur -> getParent() ;
                    leftRotation( cur -> getParent() ) ;
                    cur = tmp ;
                    //cout << cur -> getData() << endl ;
                    //cout << cur -> isRed() << " " << cur -> getParent() << " " << cur -> getParent() -> isRed() << endl ;
                }else if( !cur -> getParent() -> isLeft() && !cur -> isLeft() ){//RR
                    //cout << "RR\n" ;
                    cur -> getParent() -> setBlack() ;
                    cur -> getGrandFather() -> setRed() ;
                    leftRotation( cur -> getGrandFather() ) ;
                }else{//RL
                    //cout << "RL\n" ;
                    RBTreeNode<T> *tmp = cur -> getParent() ;
                    rightRotation( cur -> getParent() ) ;
                    cur = tmp ;
                }
            }
            //getch() ;
            //levelOrder() ;
        }
        root -> setBlack() ;
    }

    RBTreeNode<T> *predecessor( RBTreeNode<T> *cur )
    {
        if( cur -> getLeft() == NULL )
        {
            return NULL ;
        }
        RBTreeNode<T> *ptr = cur -> getLeft() ;
        while( ptr -> getRight() )
        {
            ptr = ptr -> getRight() ;
        }
        return ptr ;
    }

    void _remove( RBTreeNode<T> *target )
    {
        if( target == NULL )
        {
            return ;
        }
        if( target == root && target -> getLeft() == NULL && target -> getRight() == NULL )
        {
            delete root ;
            root = NULL ;
            return ;
        }
        //cout << "remove node " << target -> getData() << endl ;
        if( !( target -> getLeft() || target -> getRight() ) )//the node to be deleted has no child
        {
            //cout << "delete leaf node " << target -> getData() << endl ;
            if( target -> isRed() )
            {
                if( target -> isLeft() )
                {
                    target -> getParent() -> setLeft( NULL ) ;
                }else{
                    target -> getParent() -> setRight( NULL ) ;
                }
                delete target ;
                target = NULL ;
            }else{
                target -> setData( N ) ;//mark the NULL double black which should be deleted( the others db shouldn't )
                remove_fix( target ) ;
            }
        }else if( target -> getLeft() && !target -> getRight() ){//the node to be deleted has one child( left )
            //cout << "delete node having only left child\n" ;
            target -> setData( target -> getLeft() -> getData() ) ;
            _remove( target -> getLeft() ) ;
        }else if( target -> getRight() && !target -> getLeft() ){//the node to be deleted has one child( right )
            //cout << "delete node having only right child\n" ;
            target -> setData( target -> getRight() -> getData() ) ;
            _remove( target -> getRight() ) ;
        }else{//the node to be deleted has two children
            //cout << "delete node having two children\n" ;
            RBTreeNode<T> *pre = predecessor( target ) ;
            //cout << "pre:" << pre -> getData() ;
            target -> setData( pre -> getData() ) ;
            _remove( pre ) ;
        }
        root -> setBlack() ;
    }

    void remove_fix( RBTreeNode<T> *&db )
    {
        //cout << "remove_fix\n" ;
        if( db == root )
        {
            //cout << "db is root\n" ;
            return ;
        }
        RBTreeNode<T> *sib = db -> getSibling() ;
        RBTreeNode<T> *par = db -> getParent() ;
        if( sib )
        {
            //cout << "sib:" << sib -> getData() << " " << sib -> getColor() << endl ;
        }
        if( sib && sib -> isRed() )
        {
            //cout << "sib is red\n" ;
            par -> setRed() ;
            sib -> setBlack() ;
            if( db -> isLeft() )
            {
                leftRotation( par ) ;
            }else{
                rightRotation( par ) ;
            }
            remove_fix( db ) ;
        }else if( sib ){//sibling is black
            //cout << "sib is black\n" ;
            if( ( !sib -> getLeft() || !sib -> getLeft() -> isRed() ) && ( !sib -> getRight() || !sib -> getRight() -> isRed() ) )//sibling has two black child nodes
            {
                //cout << "sib has two black child nodes\n" ;
                sib -> setRed() ;
                if( par && par -> isRed() )
                {
                    par -> setBlack() ;
                }else{
                    remove_fix( par ) ;
                }
            }else if( ( ( !sib -> getLeft() || !sib -> getLeft() -> isRed() ) && sib -> getRight() -> isRed() ) || ( ( !sib -> getRight() || !sib -> getRight() -> isRed() ) && sib -> getLeft() -> isRed() ) ){
                //cout << "sib has one red child\n" ;
                //getch() ;
                //levelOrder() ;
                if( db -> isLeft() )
                {
                    RBTreeNode<T> *far = sib -> getRight() ;
                    RBTreeNode<T> *near = sib -> getLeft() ;

                    if( near && near -> isRed() )//case 5
                    {
                        //cout << "near is red\n" ;
                        sib -> swapColor( near ) ;
                        rightRotation( sib ) ;
                        remove_fix( db ) ;
                    }else{//case 6
                        //cout << "far is red\n" ;
                        par -> swapColor( sib ) ;
                        leftRotation( par ) ;
                        far -> setBlack() ;
                        /*if( sib )
                        {
                            cout << "sib:" << sib -> getData() << endl ;
                        }
                        if( far )
                        {
                            cout << "far:" << far -> getData() << endl ;
                        }*/
                    }
                }else{//mirrored case
                    RBTreeNode<T> *far = sib -> getLeft() ;
                    RBTreeNode<T> *near = sib -> getRight() ;
                    if( near && near -> isRed() )//case 5
                    {
                        //cout << "near is red\n" ;
                        sib -> swapColor( near ) ;
                        leftRotation( sib ) ;//mirrored
                        remove_fix( db ) ;
                    }else{//case 6
                        //cout << "far is red\n" ;
                        par -> swapColor( sib ) ;
                        rightRotation( par ) ;//mirrored
                        far -> setBlack() ;
                        //cout << "sib:" << sib -> getData() << endl ;
                        //cout << "far:" << far -> getData() << endl ;
                    }
                }
            }else{//sibling has two red child nodes
                /**apply case 6**/
                //cout << "sib has two red child nodes\n" ;
                if( db -> isLeft() )
                {
                    RBTreeNode<T> *far = sib -> getRight() ;
                    RBTreeNode<T> *near = sib -> getLeft() ;
                    par -> swapColor( sib ) ;
                    leftRotation( par ) ;
                    far -> setBlack() ;
                }else{
                    RBTreeNode<T> *far = sib -> getLeft() ;
                    RBTreeNode<T> *near = sib -> getRight() ;
                    par -> swapColor( sib ) ;
                    rightRotation( par ) ;//mirrored
                    far -> setBlack() ;
                }
            }
        }
        if( db && db -> getData() == N )
        {
            //cout << "delete DB\n" ;
            if( db -> isLeft() )
            {
                db -> getParent() -> setLeft( NULL ) ;
            }else{
                db -> getParent() -> setRight( NULL ) ;
            }
            delete db ;
            db = NULL ;
        }
    }

    void leftRotation( RBTreeNode<T> *cur )
    {
        if( cur == NULL )
        {
            return ;
        }
        //cout << "leftRotation " << cur -> getData() << endl ;
        //getch() ;
        //levelOrder() ;
        if( cur == root && cur -> getRight() )
        {
            root = cur -> getRight() ;
        }
        RBTreeNode<T> *tmp_L = cur -> getRight() -> getLeft() ;
        /*if( tmp_L )
        {
            cout << tmp_L -> getData() << endl ;
        }*/

        if( cur -> getParent() )
        {
            if( cur -> isLeft() )
            {
                cur -> getParent() -> setLeft( cur -> getRight() ) ;
            }else{
                cur -> getParent() -> setRight( cur -> getRight() ) ;
            }
        }else{
            cur -> getRight() -> setParent( NULL ) ;
        }
        cur -> getRight() -> setLeft( cur ) ;
        cur -> setRight( tmp_L ) ;

        //getch() ;
        //levelOrder() ;
    }
    void rightRotation( RBTreeNode<T> *cur )
    {
        if( cur == NULL )
        {
            return ;
        }
        if( cur == root && cur -> getLeft() )
        {
            root = cur -> getLeft() ;
        }
        //cout << "rightRotation " << cur -> getData() << endl ;
        RBTreeNode<T> *tmp_R = cur -> getLeft() -> getRight() ;
        if( cur -> getParent() )
        {
            if( cur -> isLeft() )
            {
                cur -> getParent() -> setLeft( cur -> getLeft() ) ;
            }else{
               cur -> getParent() -> setRight( cur -> getLeft() ) ;
            }
        }else{
            cur -> getLeft() -> setParent( NULL ) ;
        }
        cur -> getLeft() -> setRight( cur ) ;
        cur -> setLeft( tmp_R ) ;
    }
    void inorder( LinkedList<RBTreeNode<T>*> *list )
    {
        inorder( this -> root , list ) ;
    }
    void inorder( RBTreeNode<T> *root , LinkedList<RBTreeNode<T>*> *list )
    {
        if( root == NULL )
        {
            return ;
        }
        //cout << "root:" << root << endl ;
        inorder( root -> getLeft() , list ) ;
        list -> addToTail( root ) ;
        inorder( root -> getRight() , list ) ;
    }
};

template<class K,class V>
struct Pair {
    Pair() {}
    Pair(K key, V value)
    {
        first = key ;
        second = value ;
    }
    Pair( K key )
    {
        first = key ;
    }
    Pair(const Pair<K,V>& other)
    {
        first = other.getFirst() ;
        second = other.getSecond() ;
    }
    bool operator ==( Pair<K,V> &p )/*************only check for key value**********/
    {
        if( first == p.getFirst() )
        {
            return true ;
        }
        return false ;
    }
    K getFirst() const
    {
        return first ;
    }
    V getSecond() const
    {
        return second ;
    }
    V &getSecond()
    {
        //cout << "REF\n" ;
        return second ;
    }
    friend ostream& operator<<(ostream& os, const Pair& p) {
      os << p.first << " " << p.second;
      return os;
    }
    K first;
    V second;
};

template <class K, class V>
class Map : public RBTree<Pair<K, V>> {
  public:
    // alias the type
    typedef Pair<K, V> MapType;
    /**
     * @brief Traverse the tree with inorder traversal
     */
    class Iterator{
      public:
        // Implement the function you need.
        Iterator( Map<K,V> *map )
        {
            current = map -> root ;
            while( current -> getLeft() )
            {
                current = current -> getLeft() ;
            }
        }
        Iterator( RBTreeNode<MapType> *n )
        {
            current = n ;
        }
        // Overload the operators
        MapType* operator->() const
        {
            MapType *tmp = new MapType( current -> getData() ) ;
            return tmp ;
        }
        MapType& operator*() const
        {
            MapType *tmp = new MapType( current -> getData() ) ;
            return *tmp ;
        }

        Iterator& operator++(int i)
        {
            if( current -> isLeft() )
            {

            }
            return *this ;
        }
        //Iterator operator++(int){}/*******????????*********/
        RBTreeNode<MapType>* getCur() const
        {
            return current ;
        }
      private:
        RBTreeNode<MapType> *current;
    };

  V& operator[](const K& k)//modified
  {
      //cout << "[]\n" ;
      Iterator iterator = begin() ;
      while( iterator != end() )
      {
          if( iterator.getCur() -> getData().getFirst() == k )
          {//cout << "WW"<< iterator.getCur() -> getData() << " " << &( iterator.getCur() -> getData() -> getData().getSecond() ) << endl ;
              return ( iterator.getCur() -> getData().getSecond() ) ;
              /*****in class RBTreeNode, getData() should return a reference****/
          }
          iterator++ ;
      }

      MapType newData( k ) ;
      this -> insert( newData ) ;
      Iterator iterator2( this ) ;
      while( iterator2 != end() )
      {
          if( iterator2.getCur() -> getData().getFirst() == k )
          {//cout << "WW"<< iterator.getCur() -> getData() << " " << &( iterator.getCur() -> getData() -> getData().getSecond() ) << endl ;
              return ( iterator2.getCur() -> getData().getSecond() ) ;
              /*****in class RBTreeNode, getData() should return a reference****/
          }
          iterator2++ ;
      }
  }

  Iterator begin()
  {
      Iterator iterator( this ) ;
      return iterator ;
  }

  /**
   * @return Iterator pointing to one past the last element in the map
   */
  Iterator end()
  {

  }

  // comparison operators on iterator
  //friend bool operator==(const Iterator& _iter1, const Iterator& _iter2) {}
  friend bool operator!=(const Iterator& _iter1, const Iterator& _iter2)
  {
      if( _iter1.getCur() != _iter2.getCur() )
      {
          return true ;
      }
      return false ;
  }

  // Implement the function you need.
};

int main() {
  Map<string, int> map;
  // Inserting data to Map
  Pair<string, int> p1("earth", 1);
  Pair<string, int> p2("moon", 2);
  Pair<string, int> p3(p2);

  // insert the pair into the map only if key not exist.
  //the order is determined by the key value
  //cout << map.insert(p1) << endl;
  //cout << map.insert(p2)<<endl;
  //cout << map.insert(p3)<<endl;
  map.insert(p1);
  map.insert(p2);
  map.insert(p3);
  // Will replace the value of already added key.
  map["sun"] = 3;
  //cout << map["earth"] << "**" << endl ;
  map["earth"] = 4;
  // Iterate through all elements in Map
  Map<string, int>::Iterator it = map.begin();
  while( it != map.end() ) {/**modified*/
    //cout << it.getCur() << endl ;
    cout<<it->first<<" :: "<<(*it).second<<endl;
    //cout << &( (*it).second) << endl ;
    it++;
  }
  // Check if insertion is successful or not
  if(!map.insert(p1)) {/**modified**/
    cout<<"Element with key 'earth' not inserted because already existed"<<endl;
  }
  return 0;
}

/*
ANS:
earth :: 4
moon :: 2
sun :: 3
Element with key 'earth' not inserted because already existed
*/
