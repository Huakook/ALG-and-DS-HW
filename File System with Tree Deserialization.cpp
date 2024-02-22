#include<iostream>
#include<string>
using namespace std ;

template<class T>
class Node {
  public:
  Node(): prev( NULL ) , next( NULL ) , data( 0 )
  {
      Node<T>::nodeCount++ ;
  }
  Node(T data): prev( NULL ) , next( NULL ) , data( data )
  {
      Node<T>::nodeCount++ ;
  }
  Node(T data, Node<T> *prev, Node<T> *next):data( data ) , prev( prev ) , next( next )
  {
      Node<T>::nodeCount++ ;
  }
  T getData()
  {
      return data ;
  }
  Node<T>* getPrev()
  {
      return prev ;
  }
  Node<T>* getNext()
  {
      return next ;
  }
  void setData( T data )
  {
      this -> data = data ;
  }
  void setPrev( Node<T> *p )
  {
      prev = p ;
  }
  void setNext( Node<T> *n )
  {
      next = n ;
  }
  ~Node()
  {
      Node<T>::nodeCount-- ;
  }
  static int nodeCount ;
  private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template<class T>
int Node<T>::nodeCount = 0 ;

template<class T>
class LinkedList {
  public:
  LinkedList():head( NULL ) , tail( NULL )
  {}
  Node<T> *getHead()
  {
      return head ;
  }
  Node<T> *getTail()
  {
      return tail ;
  }
  T addToTail(T data)
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
      return data ;
  }
  T addToHead(T data)
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
      return data ;
  }
  T *deleteFromHead()
  {
      if( head == NULL )
      {
          return NULL ;
      }
      T *tmp = new T( head -> getData() ) ;
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
      if( tail == NULL )
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

  T add( T data )
  {
      if( head == NULL || data -> getPath() < head -> getData() -> getPath() )
      {
          if( head )
          {
              cout << data -> getPath() << " < " << head -> getData() -> getPath() << endl ;
          }
          addToHead( data ) ;
          return data ;
      }
      if( data -> getPath() > tail -> getData() -> getPath() )
      {
          addToTail( data ) ;
          return data ;
      }
      Node<T> *newNode = new Node<T>( data ) ;
      for( Node<T> *ptr = head ; ptr ; ptr = ptr -> getNext() )
      {
          if( ptr -> getData() -> getPath() > data -> getPath() )
          {
              ptr -> getPrev() -> setNext( newNode ) ;
              newNode -> setPrev( ptr -> getPrev() ) ;
              ptr -> setPrev( newNode ) ;
              newNode -> setNext( ptr ) ;
              break ;
          }
      }
      return data ;
  }

  void deleteData(T data)
  {
      for( Node<T> *ptr = head ; ptr != NULL ; ptr = ptr -> getNext() )
      {
          if( ptr -> getData() == data )
          {
              if( ptr == head )
              {
                  deleteFromHead() ;
              }else if( ptr == tail ){
                  deleteFromTail() ;
              }else{
                  ptr -> getPrev() -> setNext( ptr -> getNext() ) ;
                  ptr -> getNext() -> setPrev( ptr -> getPrev() ) ;
                  delete ptr ;
              }
              break ;
          }
      }
  }

  void deleteData(T data, int n)
  {
      for( int i = 0 ; i < n ; i++ )
      {
          deleteData( data ) ;
      }
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

  int searchIdx( T target )
  {
      int idx = 0 ;
      for( Node<T> *ptr = head ; ptr ; ptr = ptr -> getNext() )
      {
          if( ptr -> getData() == target )
          {
              return idx ;
          }
          idx++ ;
      }
      return -1 ;
  }
  void searchIdx( T target , int num , LinkedList<int> &idx_list )
  {
      int idx = 0 ;
      LinkedList<T> s ;
      for( Node<T> *ptr = head ; ptr ; ptr = ptr -> getNext() )
      {
          if( ptr -> getData() == target )
          {
              s.addToTail( target ) ;
          }else if( ptr -> getData() == ']' ){
              s.deleteFromTail() ;
          }
          if( s.size() == num && ptr -> getData() == target )
          {
              //cout << ptr -> getData() << endl ;
              idx_list.addToTail( idx ) ;
          }
          if( s.size() == num - 1 && ptr -> getPrev() && ptr -> getPrev() -> getData() == '"' && ptr -> getData()  == 'f' && ptr -> getNext() && ptr -> getNext() -> getData() == 'i' && ptr -> getNext() -> getNext() && ptr -> getNext() -> getNext() -> getData() == 'l' && ptr -> getNext() -> getNext() -> getNext() && ptr -> getNext() -> getNext() -> getNext() -> getData() == 'e' )
          {
              idx_list.addToTail( 0 ) ;
          }
          idx++ ;
      }
  }

  void allAdd( T data )
  {
      for( Node<T> *ptr = head ; ptr ; ptr = ptr -> getNext() )
      {
          ptr -> setData( ptr -> getData() + data ) ;
      }
  }

  void insertIdx( int idx , string &data )
  {
      Node<T> *ptr = head ;
      if( head == NULL )
      {
          return ;
      }
      for( int i = 0 ; i < idx ; i++ )
      {
          ptr = ptr -> getNext() ;
      }
      if( ptr && ptr -> getData() == '}' )
      {
          data = ',' + data ;
      }

      //cout << "insert " << data << " to " << this << endl ;
      int data_len = data.size() ;
      for( int i = 0 ; i < data_len ; i++ )
      {
          Node<char> *newNode = new Node<char>( data[ i ] ) ;
          ptr -> getNext() -> setPrev( newNode ) ;
          newNode -> setNext( ptr -> getNext() ) ;
          ptr -> setNext( newNode ) ;
          newNode -> setPrev( ptr ) ;
          ptr = newNode ;
      }
  }

  friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
  {
      //out << "(" ;
      if( n != NULL )
      {
          int flag = 0 ;
          for( Node<T> *ptr = n -> head ; ptr ; ptr = ptr -> getNext() )
          {
              if( flag )
              {
                  out << ", " << ptr -> getData() ;
              }else{
                  out << ptr -> getData() ;
                  //flag = 1 ;
              }
          }
      }
      //out << ")" << endl ;
      //delete n ;
      return out ;
  }

  ~LinkedList()
  {
      while( head != NULL )
      {
          deleteFromHead() ;
      }
  }

  private:
    Node<T> *head;
    Node<T> *tail;
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
    Node<T> *getFirst()
    {
        return list -> getHead() ;
    }
    Node<T> *getSecond()
    {
        if( list -> getHead() )
        {
            return list -> getHead() -> getNext() ;
        }
        return NULL ;
    }
    LinkedList<T> *getList()
    {
        return list ;
    }
    bool empty()
    {
        return list -> empty() ;
    }
    int size()
    {
        return list -> size() ;
    }
    void display()
    {
        cout << "queue:" << list ;
    }

    ~Queue()
    {
        delete list ;
    }
private:
    LinkedList<T> *list ;
};

template<class T>
class TreeNode {
  public:
      TreeNode():children( new LinkedList<TreeNode<T>*> ) , parent( NULL ) , data("") , path("") , type("") , cur( NULL )
      {}
      TreeNode( T data , T path , T type )
      {
          //data is "" when type == "dir"
          this -> data = data ;
          this -> path = path ;
          this -> type = type ;
          children = new LinkedList<TreeNode<T>*> ;
          parent = NULL ;
          cur = NULL ;
      }
    virtual TreeNode<T>* getParent() = 0 ;
    virtual void setParent(TreeNode<T>* parent) = 0 ;
    virtual LinkedList<TreeNode<T>*>* getChildren() = 0 ;
    virtual void setChildren(LinkedList<TreeNode<T>*>* children) = 0 ;
    virtual TreeNode<T> *addChildren( T , T , T ) = 0;
    virtual TreeNode<T> *addChildren() = 0 ;
    virtual TreeNode<T> *addChildren( TreeNode<T> *child ) = 0 ;
    virtual T getData() = 0 ;
    virtual void setData( T , T , T ) = 0 ;
    virtual void setData( T ) = 0 ;
    virtual bool end() = 0 ;
    virtual void deleteChild( TreeNode<T> *child ) = 0 ;
    virtual Node<TreeNode<T>*> *getCur() = 0 ;
    virtual void setCur( Node<TreeNode<T>*> *c ) = 0 ;
    virtual T getPath() = 0 ;
    virtual T getType() = 0 ;
    virtual void setPath( T ) =  0 ;
    virtual void setType( T ) = 0 ;
    /*virtual ~TreeNode()
    {
        delete children ;
    }*/
  protected:
    T data , path , type ;
    LinkedList<TreeNode<T>*>* children;
    TreeNode<T> *parent ;
    Node<TreeNode<T>*> *cur ;
    /************for postorder traversal*********/
};

template<class T, class D>
class Tree {
  public:
      Tree()
      {
          root = NULL ;
      }
    //virtual void levelorder() = 0 ;
    //virtual void inorder() = 0 ;
    //virtual void preorder() = 0 ;
    //virtual void postorder() = 0 ;
    //virtual bool insert(D data) = 0;
    virtual TreeNode<T> *remove(string data) = 0 ;
    virtual bool move( string , string ) = 0 ;
    virtual TreeNode<T>* search(D data) = 0 ;
    virtual void setRoot(TreeNode<T>* root) = 0  ;
    virtual void deSerialize2(string tree) = 0 ;
    virtual void deSerialize2( LinkedList<char> *list ) = 0 ;
    virtual LinkedList<char> *serialize() = 0 ;
    virtual bool empty() = 0 ;
    virtual TreeNode<T> *touch( string , string ) = 0 ;
    virtual TreeNode<T> *getRoot() = 0 ;
    //virtual TreeNode<T> *mkdir2( string ) = 0 ;
  protected:
    TreeNode<T>* root;
};

template<class T>//if any children is '\0' ->> "end":"true"
class GeneralTreeNode : public TreeNode<T> {
public:
    GeneralTreeNode() : TreeNode<T>()
    {}
    GeneralTreeNode( T data , T path , T type ) : TreeNode<T>( data , path , type )
    {}
    TreeNode<T>* getParent()
    {
        return this -> parent ;
    }
    void setParent(TreeNode<T>* parent)
    {
        this -> parent = parent ;
    }
    LinkedList<TreeNode<T>*>* getChildren()
    {
        return this -> children ;
    }
    void setChildren(LinkedList<TreeNode<T>*>* children)
    {
        this -> children = children ;
    }
    TreeNode<T> *addChildren( T data , T path , T type )
    {
        TreeNode<T> *newNode = new GeneralTreeNode<T>( data , path , type ) ;
        this -> children -> add( newNode ) ;
        newNode -> setParent( this ) ;
        return newNode ;
    }
    TreeNode<T> *addChildren()
    {
        this -> children -> addToTail( new GeneralTreeNode<T> ) ;
        this -> children -> getTail() -> getData() -> setParent( this ) ;
        return this -> children -> getTail() -> getData() ;
    }
    TreeNode<T> *addChildren( TreeNode<T> *child )
    {
        this -> children -> add( child ) ;
        child -> setParent( this ) ;
        return child ;
    }
    Node<TreeNode<T>*> *getCur()
    {
        return this -> cur ;
    }
    void setCur( Node<TreeNode<T>*> *c )
    {
        this -> cur = c ;
    }
    T getData()
    {
        return this -> data ;
    }
    void setData( T data , T path , T type )
    {
        this -> data = data ;
        this -> path = path ;
        this -> type = type ;
    }
    void setData( T data )
    {
        this -> data = data ;
    }
    T getPath()
    {
        return this -> path ;
    }
    void setPath( T path )
    {
        this -> path = path ;
    }
    T getType()
    {
        return this -> type ;
    }
    void setType( T type )
    {
        this -> type = type ;
    }
    bool end()
    {
        for( Node<TreeNode<T>*> *ptr = this -> children -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            if( ptr -> getData() && ptr -> getData() -> getData() == "\n" )
            {
                return true ;
            }
        }
        return false ;
    }
    void deleteChild( TreeNode<T>* child )
    {
        this -> children -> deleteData( child ) ;
    }
    virtual ~GeneralTreeNode()
    {
        //delete this -> children ;
    }
};

class Basis
{
public:
    Basis()
    {
        dir = "{\"children\":[],\"path\":,\"type\":}" ;
        file = "{\"data\":,\"path\":,\"type\":}" ;
    }
    string setData( string data , string path , string type )
    {
        string tmp = "" ;
        if( type == "dir" )
        {
            tmp = "{\"children\":[],\"path\":\"" + path + "\",\"type\":\"dir\"}" ;
        }else{
            tmp = "{\"data\":\"" + data + "\",\"path\":\"" + path + "\",\"type\":\"file\"}" ;
        }
        return tmp ;
    }
private:
    string dir ;
    string file ;
};

template<class T, class D>
class GeneralTree : public Tree<T, D> {
  public:
    GeneralTree(){
        this -> root = NULL ;
       //this -> root = new GeneralTreeNode<T>;
    }

    TreeNode<T> *getRoot()
    {
        return this -> root ;
    }

    int _height( TreeNode<T> *root )
    {
        if( root == NULL )
        {
            return 0 ;
        }
        int max = 0 ;
        for( Node<TreeNode<T>*> *ptr = root -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            int tmp = _height( ptr -> getData() ) ;
            if( max < tmp )
            {
                max = tmp ;
            }
        }
        return max + 1 ;
    }

    int height()
    {
        return _height( this -> root ) ;
    }

	int count()//levelorder
	{
	    if( this -> root == NULL )
        {
            return 0 ;
        }
        int num = 0 ;
        Queue<TreeNode<T>*> q ;
        q.enqueue( this -> root ) ;
	    while( !q.empty() )
        {
            TreeNode<T> **tmp = q.dequeue() ;
            TreeNode<T> *cur = *tmp ;
            delete tmp ;
            num++ ;
            for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
            {
                q.enqueue( ptr -> getData() ) ;
            }
        }
        return num ;
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

    TreeNode<T> *search( D target )// /usr/bin
    {
        if( this -> root == NULL )
        {
            return NULL ;
        }
        if( target == "/" )
        {
            return this -> root ;
        }
        Queue<string> q ;
        for( int i = 0 ; i < target.size() ; i++ )
        {
            if( target[ i ] == '/' )
            {
                string s = "" ;
                for( i = i + 1 ; i < target.size() ; i++ )
                {
                    if( target[ i ] == '/' )
                    {
                        i-- ;
                        break ;
                    }
                    s += target[ i ] ;
                }
                q.enqueue( s ) ;
                //cout << s << " enqueued\n" ;
            }
        }
        TreeNode<T> *cur = this -> root ;
        while( !q.empty() )
        {
            int flag = 0 ;
            string tmp = *q.dequeue() ;
            //cout << "tmp:" << tmp << endl ;
            for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
            {
                //cout << "ptr -> data:" << ptr -> getData() -> getPath() << endl ;
                if( ptr -> getData() -> getPath() == tmp )
                {
                    cur = ptr -> getData() ;
                    flag = 1 ;
                    break ;
                }
            }
            if( !flag )
            {
                return NULL ;
            }
        }
        return cur ;
    }
    /*Cancel operation if <source> does not exist.*/
    /*If the destination file doesn¡¦t exist, it will be created. */
    TreeNode<T> *copy( string source , string destination )/**no matter the destination exists?**/
    {
        TreeNode<T> *s = search( source ) ;
        if( !s )
        {
            return NULL ;
        }
        /**make a copy**/
        GeneralTree<T , D> tmp ;
        tmp.setRoot( s ) ;
        //tmp.levelorder2() ;
        GeneralTree<T , D> tmp2 ;
        tmp2.deSerialize2( tmp.serialize() ) ;
        //tmp2.levelorder2() ;
        TreeNode<T> *d = search( destination ) ;
        if( !d )/**if destination not exist, just create one*//**no matter what is on the path->>X**/
        {
            TreeNode<T> *des = mkdir( destination ) ;
            if( des == NULL )//there's a file with the name on the path
            {
                return NULL ;
            }
            des -> addChildren( tmp2.getRoot() ) ;
            return tmp2.getRoot() ;
        }else if( d -> getType() == "file" ){
            return NULL ;
        }
        //replace the files if it exists in the destination
        for( Node<TreeNode<T>*> *ptr = d -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            if( ptr -> getData() -> getPath() == s -> getPath() )
            {
                //if the types of source and the destination are not the same, cancel the operation
                if( ptr -> getData() -> getType() != s -> getType() )
                {
                    return NULL ;
                }
                //replace
                d -> deleteChild( ptr -> getData() ) ;
                d -> addChildren( tmp2.getRoot() ) ;
                return tmp.getRoot() ;
            }
        }
        //destination has no child that have the same path with the source
        d -> addChildren( tmp2.getRoot() ) ;
        return tmp2.getRoot() ;
    }

    void levelorder2()
    {
        if( this -> root == NULL )
        {
            cout << "Empty.\n" ;
            return ;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
        char ch ;
        int h = height() ;
        cout << "h:" << h << endl ;
        int curH = 0 ;
        Queue<TreeNode<T>*> q ;
        q.enqueue( this -> root ) ;
        TreeNode<T> *SEP = new GeneralTreeNode<T> ;
        while( !q.empty() )
        {
            if( curH == h )
            {
               break ;
            }
            curH++ ;
            int s = q.size() ;
            cout << endl << endl ;
            for( int i = 0 ; i < ( power( 2 , h ) - power( 2 , curH ) ) / 2 + 1 ; i++ )
            {
                cout << "" ;
            }
            for( int i = 0 ; i < s ; i++ )/**for each level*/
            {
                TreeNode<T> **tmp = q.dequeue() ;
                TreeNode<T> *cur = *tmp ;
                delete tmp ;
                if( cur == SEP )
                {
                    cout << " || " ;
                    continue ;
                }
                if( cur == NULL )
                {
                    if( curH == h )
                    {
                       //continue ;
                    }
                    q.enqueue( NULL ) ;
                    q.enqueue( NULL ) ;
                    //cout << 'N' << " " ;
                    continue ;
                }
                cout << cur -> getData() << " " << cur -> getPath() << " " << cur -> getType() << " ";
                for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
                {
                    if( ptr -> getData() )
                    {
                        q.enqueue( ptr -> getData() ) ;
                    }
                }
                q.enqueue( SEP ) ;
            }
        }
        delete SEP ;
        cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl ;
    }

    bool move( string source , string destination )
    //Cancel operation if <source> does not exist
    //move the source file or directory ( if exists ) to under destination ( replace it if it exists )
    /**do the operation even the destination not exist**/
    /**what if there's a file with the same name on the path ->> cancel**/
    /**If the destination file not exist, it will be created.*/
    {
        //cout << "move\n" ;
        TreeNode<T> *s = search( source ) ;
        if( !s )
        {
            return false ;
        }
        //create a new directory if the destination not exist
        /**what if there's a file with the same name on the path?**/
        TreeNode<T> *d = search( destination ) ;
        if( !d )
        {
            TreeNode<T> *des = mkdir( destination ) ;
            if( des == NULL )
            {
                return NULL ;
            }
            des -> addChildren( remove( s ) ) ;
            return true ;
        }else if( d -> getType() == "file" ){
            return NULL ;
        }
        for( Node<TreeNode<T>*> *ptr = d -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            if( ptr -> getData() -> getPath() == s -> getPath() )
            {
                if( ptr -> getData() -> getType() != s -> getType() )
                {
                    return NULL ;
                }
                d -> addChildren( remove( s ) ) ;
                if( s != ptr -> getData() )
                {
                    d -> deleteChild( ptr -> getData() ) ;
                }
                //replace the file or directory in the destination
                return true ;
            }
        }
        //destination has no child that has the same name with the source
        d -> addChildren( remove( s ) ) ;
        return true ;
    }

    TreeNode<T> *remove( string data )//remove a file or a directory if it exists
    {
        TreeNode<T> *tmp = search( data ) ;
        if( !tmp )
        {
            return NULL ;
        }
        if( tmp -> getParent() )
        {
            tmp -> getParent() -> deleteChild( tmp ) ;
        }
        return tmp ;
    }

    TreeNode<T> *remove( TreeNode<T> *target )
    {
        if( target && target -> getParent() )
        {
            target -> getParent() -> deleteChild( target ) ;
        }
        return target ;
    }

    TreeNode<T> *touch( string destination , string data )//add a file
    /****if there's already a file with the same name, replace it***/
    /**even the destination not exists, replace it**/
    {
        //cout << "touch\n";
        TreeNode<T> *d = search( destination ) ;
        if( d )
        {
            if( d -> getType() == "dir" )
            {
                return NULL ;
                /*TreeNode<T> *newNode = new GeneralTreeNode<T>( data , d -> getPath() , "file" ) ;
                d -> getParent() -> addChildren( newNode ) ;
                d -> getParent() -> deleteChild( d ) ;*/
            }else{
                d -> setData( data ) ;
            }
            return d ;
        }else{
            TreeNode<T> *des = mkdir( destination ) ;
            if( des == NULL )
            {
                return NULL ;
            }
            des -> setData( data ) ;
            des -> setType( "file" ) ;
            return des ;
        }
    }

    TreeNode<T> *mkdir( string destination )
    {
        /**what if on the path is a file with the same name**/
        /**no matter what the type of the same path is, cancel this operation??*/
        /**no matter what is on the path, just replace it???**/
        TreeNode<T> *d = search( destination ) ;
        if( d )
        {
            return d ;
        }else{
            /**create a new directory if it's not exist*/
            //return mkdir2( destination ) ;
        }

        //record all the path names needed
        Queue<string> q ;
        for( int i = 0 ; i < destination.size() ; i++ )
        {
            if( destination[ i ] == '/' )
            {
                string s = "" ;
                for( i = i + 1 ; i < destination.size() ; i++ )
                {
                    if( destination[ i ] == '/' )
                    {
                        i-- ;
                        break ;
                    }
                    s += destination[ i ] ;
                }
                q.enqueue( s ) ;
                //cout << s << " enqueued\n" ;
            }
        }

        //if there's a file on the path, cancel the operation
        //else create all the directories needed
        int first = 0 ;//useless
        TreeNode<T> *cur = this -> root ;
        TreeNode<T> *init = NULL ;//the first created new directory
        while( !q.empty() )
        {
            int flag = 0 ;
            string tmp = *q.dequeue() ;
            //cout << "tmp:" << tmp << endl ;
            for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
            {
                //cout << "ptr -> data:" << ptr -> getData() -> getPath() << endl ;
                if( ptr -> getData() -> getPath() == tmp )
                {
                    if( ptr -> getData() -> getType() == "file" )
                    {
                        remove( init ) ;
                        return NULL ;
                    }
                    cur = ptr -> getData() ;
                    flag = 1 ;//the directory with the same name is founded
                    break ;
                }
            }
            if( !flag )
            {
                cur = cur -> addChildren( "" , tmp , "dir" ) ;
                if( !first )
                {
                    init = cur ;
                    first = 1 ;//the first new created directory is created
                }
            }
        }
        return cur ;
    }

    void setRoot(TreeNode<T>* root)
    {
        this -> root = root ;
    }

    void deSerialize2( LinkedList<char> *list )
    {
        string s = "" ;
        for( Node<char> *ptr = list -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            s += ptr -> getData() ;
        }
        deSerialize2( s ) ;
        delete list ;
    }

    /**Post-order traversal**/
    void deSerialize2(string tree)
    {
        if( tree == "{\"root\":}" || tree == "" )
        {
            return ;
        }
        //cout << "DESEIR\n" ;
        this -> root = new GeneralTreeNode<T> ;
        Queue<T> queue ;
        this -> root = new GeneralTreeNode<T> ;
        TreeNode<T> *ptr = this -> root ;
        int tree_len = tree.size() ;
        int i = 0 ;
        for( i = 0 ; i < tree_len ; i++ )
        {
            if( tree[ i ] == '[' )
            {
                break ;
            }
        }
        for( ; i < tree_len ; i++ )
        {
            /**for File***/
            //1.data
            if( i + 3 < tree_len && tree[ i ] == 'd' && tree[ i + 1 ] == 'a' && tree[ i + 2 ] == 't' && tree[ i + 3 ] == 'a' )
            {
                //cout << "data\n" ;
                if( tree[ i + 6 ] == '"' )
                {
                    if( tree[ i + 7 ] == '"' )
                    {
                        queue.enqueue( "" ) ;
                    }else{
                        string s = "" ;
                        int j = 0 ;
                        for( j = i + 7 ; j < tree_len ; j++ )
                        {
                            if( tree[ j ] == '"' )
                            {
                                break ;
                            }
                            s += tree[ j ] ;
                            //cout << "::" << tree[ j ] << endl ;
                        }
                        //cout << "j:" <<  j << " tree_len:" << tree_len << endl ;
                        //cout << s << " enqueued\n" ;
                        queue.enqueue( s ) ;
                    }
                }
            tree[ i + 6 ] = '[' ;/******************************!!!!!!!!!!!!****************************/
            tree[ i + 7 ] = ']' ;
            //2.path
            }else if( i + 3 < tree_len && tree[ i ] == 'p' && tree[ i + 1 ] == 'a' && tree[ i + 2 ] == 't' && tree[ i + 3 ] == 'h' ){
                //cout << "path\n" ;
                string s = "" ;
                for( int j = i + 7 ; j < tree_len ; j++ )
                {
                    if( tree[ j ] == '"' )
                    {
                        break ;
                    }
                    s += tree[ j ] ;
                }
                //cout << s << " enqueued\n" ;
                queue.enqueue( s ) ;
            //3.path
            }else if( i + 3 < tree_len && tree[ i ] == 't' && tree[ i + 1 ] == 'y' && tree[ i + 2 ] == 'p' && tree[ i + 3 ] == 'e' ){
                //cout << "type\n" ;
                string s = "" ;
                for( int j = i + 7 ; j < tree_len ; j++ )
                {
                    if( tree[ j ] == '"' )
                    {
                        break ;
                    }
                    s += tree[ j ] ;
                }
                //cout << s << " enqueued.\n" ;
                queue.enqueue( s ) ;
            }
        }

        //insert node one by one
        for( int i = 0 ; i < tree_len ; i++ )
        {
            if( tree[ i ] == '[' )//discard the first '['
            {
                for( i = i + 1 ; i < tree_len ; i++ )
                {
                    if( tree[ i ] == '[' )//point to the child
                    {
                        TreeNode<T> *par = ptr ;
                        ptr = ptr -> addChildren() ;
                        ptr -> setParent( par ) ;
                    }else if( tree[ i ] == ']' && !queue.empty() ){
                        T *data = queue.dequeue() ;
                        T *data2 = queue.dequeue() ;
                        //cout << *data << "&&&" << *data2 << endl ;
                        if( *data2 == "dir" )
                        {
                            ptr -> setData( "" , *data , *data2 ) ;
                            //cout << "data:" << " path:" << *data << " type:" << *data2 << endl ;
                        }else{
                            T *data3 = queue.dequeue() ;
                            ptr -> setData( *data , *data2 , *data3 ) ;
                            //cout << "data:" << *data << " path:" << *data2 << " type:" << *data3 << endl ;
                            delete data3 ;
                        }
                        delete data ;
                        delete data2 ;
                        ptr = ptr -> getParent() ;
                    }
                }
                break ;
            }
        }
    }

    LinkedList<char> *serialize()
    {
        if( this -> root == NULL )
        {
            return new LinkedList<char> ;
        }
        string init = "{\"root\":}" ;
        int init_len = init.size() ;
        LinkedList<char> *list = new LinkedList<char> ;
        for( int i = 0 ; i < init_len ; i++ )
        {
            list -> addToTail( init[ i ] ) ;
        }
        //level order traversal
        Basis basis ;
        Queue<TreeNode<T>*> q ;
        TreeNode<T> *cur = this -> root ;
        TreeNode<T> *SEP = new GeneralTreeNode<T> ;
        int num = 0 ;//number of '[' //NULL
        int sep = 0 ;//separation of children of different parents //this -> root //the sep th times of the condition that '[' * num
        /**for root*/
        int idx = list -> searchIdx( ':' ) ;
        string bas = basis.setData( cur -> getData() , cur -> getPath() , cur -> getType() ) ;
        list -> insertIdx( idx , bas ) ;

        for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            if( ptr -> getData() )
            {
                q.enqueue( ptr -> getData() ) ;
            }
        }
        /**for possible children*/
        while( !q.empty() )
        {
            num++ ;
            //sep = 0 ;
            int n = q.size() ;//number of nodes on this level
            //int arr_len = 0 ;
            LinkedList<int> idx_list ;
            list -> searchIdx( '[' , num , idx_list ) ;
            int idx_len = idx_list.size() ;
            Node<int> *it = idx_list.getHead() ;
            for( int i = 0 ; i < n ; i++ )/**for one level*/
            {
                cur = *q.dequeue() ;
                if( cur == SEP || it -> getData() == 0 )
                {
                    it = it -> getNext() ;
                    //sep++ ;
                    continue ;
                }
                string bas = basis.setData( cur -> getData() , cur -> getPath() , cur -> getType() ) ;
                list -> insertIdx( it -> getData() , bas ) ;
                idx_list.allAdd( bas.size() ) ;

                for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
                {
                    if( ptr -> getData() && ptr -> getData() -> getData() != "\n" )
                    {
                        q.enqueue( ptr -> getData() ) ;
                    }
                }
                q.enqueue( SEP ) ;
                if( cur && cur -> getChildren() -> size() == 0 /*|| ( cur -> getChildren() -> size() == 1 && cur -> end() )*/ )
                {
                    //q.enqueue( SEP ) ;
                }
                if( q.getList() -> getTail() && q.getList() -> getTail() -> getData() != SEP )
                {
                    //q.enqueue( SEP ) ;//mark the end of children of one parent
                }
            }
        }
        return list ;
    }
    bool empty()
    {
        if( this -> root == NULL )
        {
            return true ;
        }
        return false ;
    }
};

int main()
{
        GeneralTree<string , string> gt ;
        string s ;
        string s1 ;
        getline( cin , s ) ;
        gt.deSerialize2( s ) ;
        //gt.levelorder2() ;
        //cout << gt.serialize() ;
        while( cin >> s )
        {
            if( s == "mv" )
            {
                string source , destination ;
                cin >> source >> destination ;
                gt.move( source , destination ) ;
                //gt.levelorder2() ;
            }else if( s == "cp" ){
                string source , destination ;
                cin >> source >> destination ;
                gt.copy( source , destination ) ;
                //gt.levelorder2() ;
            }else if( s == "rm" ){
                string destination ;
                cin >> destination ;
                gt.remove( destination ) ;
                //gt.levelorder2() ;
            }else if( s == "touch" ){
                int flag = 0 ;//1 is there's a space, i,e,. data is not empty
                string command , data = "" ;
                //char tmp ;
                //cin >> tmp ;
                getline( cin , command ) ;
                for( int i = 1 ; i < command.size() ; i++ )
                {
                    if( command[ i ] == ' ' )
                    {
                        flag = 1 ;
                        for( int j = i + 1 ; j < command.size() ; j++ )
                        {
                            data += command[ j ] ;
                        }
                        break ;
                    }
                }
                string destination = "" ;
                //cout << destination << endl ;
                if( flag )
                {
                    for( int i = 1 ; i < command.size() ; i++ )
                    {
                        if( command[ i ] == ' ' )
                        {
                            //cout << i << endl ;
                            break ;
                        }
                        destination += command[ i ] ;
                    }
                }else{
                    destination = command ;
                }
                //cout << destination << endl ;
                //cout << "touch " << destination << " " << data << endl ;
                gt.touch( destination , data ) ;
                //gt.levelorder2() ;
            }else if( s == "mkdir" ){
                string destination ;
                cin >> destination ;
                gt.mkdir( destination ) ;
                //gt.levelorder2() ;
            }
        }
        cout << gt.serialize() << endl ;
        //gt.levelorder2() ;

        //cin >> s ;
        //cout << "XXX" << gt.search( s ) -> getPath() << endl ;

        //cin >> s ;
        //cout << gt.remove( s ) -> getPath() << endl ;
        //gt.levelorder2() ;

        //cin >> s >> s1 ;
        //gt.move( s , s1 ) ;
        //gt.levelorder2() ;

        //cin >> s >> s1 ;
        //gt.touch( s , s1 ) ;
        //gt.levelorder2() ;

        //cin >> s ;
        //gt.mkdir( s ) ;
        //gt.levelorder2() ;
}

/***
{"root":{"children":[{"data":"","path":"tmp","type":"file"}],"path":"/","type":"dir"}}
{"root":{"children":[],"path":"/","type":"dir"}}
{"root":}
{"children":[],"path":,"type":}
{"data":,"path":,"type":}
**/

/*
{"root":{"children":[{"children":[{"data":"this is script","path":"script","type":"file"}],"path":"bin","type":"dir"},{"children":[],"path":"tmp","type":"dir"},{"children":[],"path":"usr","type":"dir"}],"path":"/","type":"dir"}}
mkdir /usr/bin/systemctl
touch /tmp/tmp this is tmp tmp
rm /user
rm /bin/script
cp /usr /tmp
mv /tmp/usr/bin/systemctl /bin

ANS:
{"root":{"children":[{"children":[{"children":[],"path":"systemctl","type":"dir"}],"path":"bin","type":"dir"},{"children":[{"data":"this is tmp tmp","path":"tmp","type":"file"},{"children":[{"children":[],"path":"bin","type":"dir"}],"path":"usr","type":"dir"}],"path":"tmp","type":"dir"},{"children":[{"children":[{"children":[],"path":"systemctl","type":"dir"}],"path":"bin","type":"dir"}],"path":"usr","type":"dir"}],"path":"/","type":"dir"}}
*/


/*
1. mv <source> <destination>
- move the file or the entire directory from <source> to under <destination>
- Replace the files of <destination> if it exists
- Cancel operation if <source> does not exist.
2. cp <source> <destination>
-copy the file or the entire directory from <source> to under <destination>
- Replace the files of <destination> if it exists
- Cancel operation if <source> does not exist.
3. rm <destination>
- remove the file or directory from <destination>
- Cancel operation if <destination> does not exist.
4. touch <destination> <data>
- add a file to <destination> that contains <data>
- Create directories which in the path if it does not exist.
- Replace the files of <destination> if it exists.
5. mkdir <destination>
- add a directory to <destination>
- Create directories which in the path if it does not exist.
- Cancel operation if <destination> already exist.

<source> and <destination> are both absolute pathnames.
<data> is a string, could be empty.
There should not have the same name dir and file in the same path.
Serialized property of node for File:
{
"data":"<data for the file>",
"path":"<relative pathnames for this node>",
"type":"file"
}
Serialized property of node for Directory:
{
"children":[<children of this node>],
"path":"<relative pathnames for this node>",
"type":"dir"
}
*/

/****Geeksforgeeks

cp command
If the destination file doesn¡¦t exist, it will be created.
In the above command mv simply replaces the source
filename in the directory with the destination filename(new name).
If the destination file exist, then it will be overwrite and the source
file will be deleted. By default, mv doesn¡¦t prompt for overwriting the existing file, So be careful !!
**/

/**
{"root":{"children":[{"children":[{"children":[],"path":"systemctl","type":"dir"}],"path":"bin","type":"dir"},{"children":[{"data":"this is tmp tmp","path":"tmp","type":"file"},{"children":[{"children":[],"path":"bin","type":"dir"}],"path":"usr","type":"dir"}],"path":"tmp","type":"dir"},{"children":[{"children":[{"children":[],"path":"systemctl","type":"dir"}],"path":"bin","type":"dir"}],"path":"usr","type":"dir"}],"path":"/","type":"dir"}}
mkdir /dir/tmp/tmp/tmp
mkdir /tmp/tmp/tmp
mkdir /
mkdir /tmp
mkdir /bin/systemctl/sys
rm /usr
mv /tmp/tmp /dir/tmp
mv /tmp /dir/tmp
**/

/**
{"root":{"children":[{"children":[{"children":[],"path":"systemctl","type":"dir"}],"path":"bin","type":"dir"},{"children":[{"data":"this is tmp tmp","path":"tmp","type":"file"},{"children":[{"children":[],"path":"bin","type":"dir"}],"path":"usr","type":"dir"}],"path":"tmp","type":"dir"},{"children":[{"children":[{"children":[],"path":"systemctl","type":"dir"}],"path":"bin","type":"dir"}],"path":"usr","type":"dir"}],"path":"/","type":"dir"}}
mkdir /bin/systemctl/tmp
cp /bin/systemctl/tmp /tmp/tmp
cp /bin/systemctl/tmp /bin/systemctl/tmp
rm /bin
mv /tmp/usr /usr/bin
touch /tmp/tmp hi
touch /usr/bin a
touch /usr/bin/bin hello
mv /usr/bin /
**/

/**
{"root":{"children":[{"children":[{"data":"this is script","path":"script","type":"file"}],"path":"bin","type":"dir"},{"children":[],"path":"tmp","type":"dir"},{"children":[],"path":"usr","type":"dir"}],"path":"/","type":"dir"}}
mv /tmp /
**/
/*
{"root":{"children":[{"children":[{"data":"data of CP","path":"cp","type":"file"},{"data":"password is not here","path":"pwd","type":"file"},{"data":"Thisssss is not password.","path":"pwdd","type":"file"}],"path":"bin","type":"dir"},{"children":[],"path":"dev","type":"dir"},{"children":[{"data":"This is not a password either.","path":"passwd","type":"file"}],"path":"etc","type":"dir"},{"children":[{"children":[{"data":"barbar barbar batbat","path":"bar","type":"file"},{"data":"foofoo","path":"foo","type":"file"}],"path":"mthomass","type":"dir"},{"children":[{"children":[{"data":"this is home in /home/stuff/home/home","path":"home","type":"file"}],"path":"home","type":"dir"}],"path":"stuff","type":"dir"}],"path":"home","type":"dir"},{"children":[{"children":[{"children":[{"data":"this is environment in /lib/environment.d/environment/environment","path":"environment","type":"file"}],"path":"environment","type":"dir"}],"path":"environment.d","type":"dir"},{"children":[],"path":"jvm","type":"dir"},{"children":[],"path":"kernel","type":"dir"},{"children":[],"path":"openssh","type":"dir"},{"children":[{"data":"print('hello python3')","path":"python.py","type":"file"}],"path":"python3","type":"dir"},{"children":[{"children":[],"path":"python","type":"dir"}],"path":"python3.8","type":"dir"},{"children":[],"path":"python3.9","type":"dir"},{"children":[],"path":"x86_64-linux-gnu","type":"dir"}],"path":"lib","type":"dir"},{"children":[],"path":"mnt","type":"dir"},{"children":[],"path":"proc","type":"dir"},{"children":[],"path":"root","type":"dir"},{"children":[{"children":[{"children":[{"children":[],"path":"bar","type":"dir"},{"children":[],"path":"foo","type":"dir"}],"path":"mthomas","type":"dir"},{"children":[{"data":"barbar barbar batbat","path":"bar","type":"file"},{"data":"foofoo","path":"foo","type":"file"}],"path":"mthomass","type":"dir"},{"children":[],"path":"stuff","type":"dir"}],"path":"home","type":"dir"}],"path":"tmp","type":"dir"},{"children":[{"children":[],"path":"bin","type":"dir"},{"children":[{"children":[{"data":"","path":"home","type":"file"}],"path":"home","type":"dir"}],"path":"home","type":"dir"},{"children":[],"path":"src","type":"dir"}],"path":"usr","type":"dir"}],"path":"/","type":"dir"}}
*/
