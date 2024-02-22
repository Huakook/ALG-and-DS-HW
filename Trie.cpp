#include<iostream>
#include<fstream>
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
      if( head == NULL || data -> getData() <= head -> getData() -> getData() )
      {
          addToHead( data ) ;
          return data ;
      }
      if( data -> getData() >= tail -> getData() -> getData() )
      {
          addToTail( data ) ;
          return data ;
      }
      Node<T> *newNode = new Node<T>( data ) ;
      for( Node<T> *ptr = head ; ptr ; ptr = ptr -> getNext() )
      {
          if( ptr -> getData() -> getData() >= data -> getData() )
          {
              ptr -> getPrev() -> setNext( newNode ) ;
              newNode -> setPrev( ptr -> getPrev() ) ;
              newNode -> setNext( ptr ) ;
              ptr -> setPrev( newNode ) ;
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
      //cout << "searchIdx" << this << endl ;
      //cout << "target:" << target << " num:" << num << endl ;
      int idx = 0 ;
      //int t = 0 ;// times of meeting the condition that s.size() == num
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
              idx_list.addToTail( idx ) ;
          }
          idx++ ;
      }
      /*cout << "searchIdx end:" ;
      for( int i = 0 ; i < t ; i++ )
      {
          cout << arr[ i ] << " " ;
      }
      cout << endl ;*/
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
      //cout << "insertIdx:" << idx << endl ;
      Node<T> *ptr = head ;
      if( head == NULL )
      {
          return ;
      }
      for( int i = 0 ; i < idx ; i++ )
      {
          ptr = ptr -> getNext() ;
      }
      /*
      cout << "#1" << ptr -> getData() ;
      if( ptr -> getNext() )
      {
          cout << "#2" << ptr -> getNext() -> getData() ;
      }
      if( ptr -> getNext() -> getNext() )
      {
          cout << "#3" << ptr -> getNext() -> getNext() -> getData() ;
      }
      cout << endl ;*/
      if( ptr && ptr -> getData() == '}' )
      {
          data = ',' + data ;
      }
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

      //cout << "insertIdx end:" << data << endl ;
      //cout << this << endl ;
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
      delete n ;
      return out ;
  }

  ~LinkedList()
  {
      while( head != NULL )
      {
          //cout << "X" ;
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
        //cout << data << " enqueue\n" ;
        list -> addToTail( data ) ;
    }
    T *dequeue()
    {
        return list -> deleteFromHead() ;
        //cout << *tmp << " dequeue\n" ;
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
    bool empty()
    {
        return list -> empty() ;
    }
    int size()
    {
        return list -> size() ;
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
      TreeNode():data( 0 ) , children( new LinkedList<TreeNode<T>*> ) , parent( NULL )
      {}
      TreeNode( T data )
      {
          this -> data = data ;
          children = new LinkedList<TreeNode<T>*> ;
          parent = NULL ;
      }
    virtual TreeNode<T>* getParent() = 0;
    virtual void setParent(TreeNode<T>* parent) = 0;
    virtual LinkedList<TreeNode<T>*>* getChildren() = 0;

    virtual void setChildren(LinkedList<TreeNode<T>*>* children) = 0;

    virtual TreeNode<T> *addChildren( T data ) = 0 ;
    virtual TreeNode<T> *addChildren() = 0 ;
    virtual T getData() = 0 ;
    virtual void setData( T data ) = 0 ;
    virtual bool end() = 0 ;
    virtual void deleteChild( TreeNode<T> *child ) = 0 ;
    virtual Node<TreeNode<T>*> *getCur() = 0 ;
    virtual void setCur( Node<TreeNode<T>*> *c ) = 0 ;
  protected:
    T data;
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
    virtual void levelorder() = 0;
    virtual void inorder() = 0;
    virtual void preorder() = 0;
    virtual void postorder() = 0;
    virtual bool insert(D data) = 0;
    virtual bool remove(D data) = 0;
    virtual TreeNode<T>* search(D data) = 0;
    virtual void setRoot(TreeNode<T>* root) = 0;
    virtual void deSerialize(string tree) = 0;
    virtual LinkedList<char> *serialize() = 0;
    virtual bool empty() = 0 ;
  protected:
    TreeNode<T>* root;
};

template<class T>//if any children is '\0' ->> "end":"true"
class GeneralTreeNode : public TreeNode<T> {
public:
    GeneralTreeNode() : TreeNode<T>()
    {}
    GeneralTreeNode( T data )
    {
        this -> data = data ;
        this -> parent = NULL ;
        this -> children = new LinkedList<TreeNode<T>*> ;
    }
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
    TreeNode<T> *addChildren( T data )
    {
        TreeNode<T> *newNode = new GeneralTreeNode<T>( data ) ;
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
    void setData( T data )
    {
        this -> data = data ;
    }
    bool end()
    {
        for( Node<TreeNode<T>*> *ptr = this -> children -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            if( ptr -> getData() && ptr -> getData() -> getData() == '\n' )
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
};

class Basis
{
public:
    Basis()
    {
        object = "{\"children\":[],\"data\":}" ;
    }
    string setData( char data )
    {
        if( data == '\0' )
        {
            return "{\"children\":[],\"data\":\"\"}" ;
        }
        string tmp = "{\"children\":[],\"data\":\"" ;
        tmp += data ;
        tmp += "\"}" ;
        return tmp ;
    }
    string setDataEnd( char data )
    {
        if( data == '\0' )
        {
            return "{\"children\":[],\"data\":\"\"}" ;
        }
        string tmp = "{\"children\":[],\"data\":\"" ;
        tmp += data ;
        tmp += "\",\"end\":\"true\"}";
        return tmp ;
    }
private:
    string object ;
};

template<class T, class D>
class GeneralTree : public Tree<T, D> {
  public:
    GeneralTree(){
        this -> root = NULL ;
       //this -> root = new GeneralTreeNode<T>;
    }

    void levelorder()
    {
        if( this -> root == NULL )
        {
            return ;
        }
        int flag = 0 ;
        Queue<TreeNode<T>*> q ;
        q.enqueue( this -> root ) ;
        while( !q.empty() )
        {
            TreeNode<T> *cur = *q.dequeue() ;
            if( cur && cur -> getData() != '\n' )
            {
                if( flag )
                {
                    cout << "," << cur -> getData() ;
                }else{
                    cout << cur -> getData() ;
                    flag = 1 ;
                }
                for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
                {
                    q.enqueue( ptr -> getData() ) ;
                }
            }
        }
        cout << endl ;
    }

    void inorder()
    {

    }

    void preorder()//Non-recursive
    {
        if( this -> root == NULL )
        {
            return ;
        }
        Stack<TreeNode<T>*> s ;
        s.push( this -> root ) ;
        while( !s.empty() )
        {
            TreeNode<T> **tmp = s.pop() ;
            TreeNode<T> *cur = *tmp ;
            delete tmp ;
            cout << cur -> getData() << "," ;
            for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getTail() ; ptr ; ptr = ptr -> getPrev() )
            {
                if( ptr -> getData() && ptr -> getData() -> getData() != '\n' )
                {
                    s.push( ptr -> getData() ) ;
                }
            }
        }
        cout << endl ;
    }

    void postorder()//Non-recursive
    {
        TreeNode<T> *cur = this -> root ;
        while( cur )
        {
            if( cur -> getCur() )
            {
                cur = cur -> getCur() -> getData() ;
                cur -> getParent() -> setCur( cur -> getParent() -> getCur() -> getNext() ) ;
            }else{
                if( cur -> getData() != '\n' )
                {
                    cout << cur -> getData() << "," ;
                }
                cur -> setCur( cur -> getChildren() -> getHead() ) ;
                cur = cur -> getParent() ;
            }
        }
        cout << endl ;
    }

    bool insert(D data)
    {
        if( search( data ) )
        {
            return false ;
        }
        if( this -> root == NULL )
        {
            this -> root = new GeneralTreeNode<T>( '\0' ) ;
            TreeNode<T> *cur = this -> root ;
            int data_len = data.size() ;
            for( int i = 0 ; i < data_len ; i++ )
            {
                cur = cur -> addChildren( data[ i ] ) ;
            }
            cur -> addChildren( '\n' ) ;
        }else{
            TreeNode<T> *cur = this -> root ;
            int i = 0 ;
            int data_len = data.size() ;
            for( ; i < data_len ; i++ )//find the character one by one in different levels
            {
                int flag = 0 ;
                for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
                {
                    if( ptr -> getData() && ptr -> getData() -> getData() == data[ i ] )
                    {
                        cur = ptr -> getData() ;
                        flag = 1 ;
                        break ;
                    }
                }
                if( !flag )
                {
                    break ;
                }
            }
            for( ; i < data_len ; i++ )
            {
                cur = cur -> addChildren( data[ i ] ) ;
            }
            cur -> addChildren( '\n' ) ;
            if( i == data_len )
            {
                return false ;
            }
        }
        return true ;
    }

    bool remove(D data)
    {
        TreeNode<T> *tmp = search( data ) ;
        if( !tmp )
        {
            return false ;
        }
        while( tmp )
        {
            if( ( tmp -> getParent() && tmp -> getParent() -> getChildren() -> size() != 1 ) || ( tmp -> getParent() && tmp -> getParent() -> end() ) )
            {
                break ;
            }
            tmp = tmp -> getParent() ;
        }
        if( tmp == this -> root )
        {
            this -> root = NULL ;
        }else{
            tmp -> getParent() -> deleteChild( tmp ) ;
        }
        return true ;
    }

    TreeNode<T>* search(D data)
    {
        if( this -> root == NULL )
        {
            return NULL ;
        }
        TreeNode<T> *cur = this -> root ;
        int i = 0 ;
        int data_len = data.size() ;
        for( ; i < data_len ; i++ )//find the character one by one in different levels
        {
            int flag = 0 ;
            for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
            {
                if( ptr -> getData() && ptr -> getData() -> getData() == data[ i ] )
                {
                    cur = ptr -> getData() ;
                    flag = 1 ;
                    if( i == data_len - 1 && ptr -> getData() -> end() )
                    {
                        return ptr -> getData() ;
                    }
                    break ;
                }
            }
            if( !flag )
            {
                return NULL ;
            }
        }
        return NULL ;
    }

    void setRoot(TreeNode<T>* root)
    {
        this -> root = root ;
    }

    /******level order*****/
     void deSerialize( string tree )/**'\n' ->> end ; '\0' ->> ' ' **/
     {
         int h = 0 ; //height of the tree
         Stack<char> s ;
         int tree_len = tree.size() ;
         for( int i = 0 ; i < tree_len ; i++ )//count the depth of '['
         {
             if( tree[ i ] == '[' )
             {
                 s.push( '[' ) ;
             }else if( tree[ i ] == ']' ){
                 s.pop() ;
             }
             if( s.size() > h )
             {
                 h = s.size() ;
             }
         }

         Stack<char> stack ;
         Queue<T> q ;
         Queue<TreeNode<T>*> queue ;
         TreeNode<T> *ptr = NULL ;
         for( int i = 0 ; i < h ; i++ )
         {
             for( int j = 0 ; j < tree_len ; j++ )
             {
                 if( tree[ j ] == '[' )
                 {
                     stack.push( '[' ) ;
                 }else if( tree[ j ] == ']' ){
                     stack.pop() ;
                 }
                 if( stack.size() == i )
                 {
                     if( j + 3 < tree_len && tree[ j ] == 'd' && tree[ j + 1 ] == 'a' && tree[ j + 2 ] == 't' && tree[ j + 3 ] == 'a' )
                     {
                         if( tree[ j + 6 ] == '"' )
                         {
                             if( tree[ j + 7 ] == '"' )
                             {
                                 q.enqueue( '\0' ) ;
                             }else{
                                 q.enqueue( tree[ j + 7 ] ) ;
                             }
                         }else{
                            q.enqueue( tree[ j + 6 ] ) ;
                         }
                     }
                 }else if( stack.size() == i - 1 ){
                     if( j + 1 < tree_len && tree[ j ] == '}' && tree[ j + 1 ] == ',' )
                     {
                         q.enqueue( '\0' ) ;
                     }
                 }
             }
             if( this -> root == NULL )
             {
                 this -> root = new GeneralTreeNode<T>( *q.dequeue() ) ;
                 ptr = this -> root ;
             }else{
                 while( !q.empty() )
                 {
                     T tmp = *q.dequeue() ;
                     if( tmp == '\0' )
                     {
                         ptr = *queue.dequeue() ;
                     }else{
                         ptr -> addChildren( tmp ) ;
                         queue.enqueue( ptr ) ;
                     }
                 }
             }
         }
     }

    /**Post-order traversal**/
    void deSerialize2(string tree)
    {
        this -> root = new GeneralTreeNode<T> ;
        Queue<T> queue ;
        this -> root = new GeneralTreeNode<T> ;
        TreeNode<T> *ptr = this -> root ;
        int tree_len = tree.size() ;
        for( int i = 0 ; i < tree_len ; i++ )
        {
            if( i + 3 < tree_len && tree[ i ] == 'd' && tree[ i + 1 ] == 'a' && tree[ i + 2 ] == 't' && tree[ i + 3 ] == 'a' )
            {
                if( tree[ i + 6 ] == '"' )
                {
                    if( tree[ i + 7 ] == '"' )
                    {
                        queue.enqueue( '\0' ) ;
                        //cout << "R\n" ;
                    }else{
                        queue.enqueue( tree[ i + 7 ] ) ;/****if char***/
                    }
                }else{
                    queue.enqueue( tree[ i + 6 ] ) ;/****if int****/
                }
            }else if( i + 2 < tree_len && tree[ i ] == 'e' && tree[ i + 1 ] == 'n' && tree[ i + 2 ] == 'd' ){
                queue.enqueue( '\n' ) ;
            }
        }

        for( int i = 0 ; i < tree_len ; i++ )
        {
            if( tree[ i ] == '[' )//discard the first '['
            {
                //cout << "i:" << i << endl ;
                for( i = i + 1 ; i < tree_len ; i++ )
                {
                    if( tree[ i ] == '[' )//point to the child
                    {
                        //cout << "i:" << i << endl ;
                        //cout << "O" ;
                        TreeNode<T> *par = ptr ;
                        //cout << ptr -> getChildren() -> size() << endl ;
                        ptr = ptr -> addChildren() ;
                        //cout << "X" ;
                        if( !ptr )
                        {
                            //cout << "NULL\n" ;
                        }
                        ptr -> setParent( par ) ;
                    }else if( tree[ i ] == ']' && !queue.empty() ){
                        //cout << "]\n" ;
                        T *data = queue.dequeue() ;
                        //cout << "Y\n" ;
                        //cout << *data << endl ;
                        ptr -> setData( *data ) ;

                        //cout << "H\n" ;
                        //delete data ;
                        //cout << "queue.size:" << queue.size() << endl ;
                        if( queue.getFirst() && queue.getFirst() -> getData() == '\n' )/*********/
                        {
                            //cout << "hi\n" ;
                            delete queue.dequeue() ;
                            ptr -> addChildren( '\n' ) ;
                        }
                        //cout << "A\n" ;
                        ptr = ptr -> getParent() ;
                    }/*else if( i + 3 < tree.size() && tree[ i ] == 'd' && tree[ i + 1 ] == 'a' && tree[ i + 2 ] == 't' && tree[ i + 3 ] == 'a' ){
                        if( tree[ i + 6 ] == '"' )
                        {
                            if( tree[ i + 7 ] == '"' )
                            {
                                queue.enqueue( ' ' ) ;
                                cout << "R\n" ;
                            }else{
                                queue.enqueue( tree[ i + 7 ] ) ;
                            }
                        }else{
                            queue.enqueue( stoi( &tree[ i + 7 ] ) ) ;
                        }
                    }else if( i + 2 < tree.size() && tree[ i ] == 'e' && tree[ i + 1 ] == 'n' && tree[ i + 2 ] == 'd' ){
                        queue.enqueue( 0 ) ;
                    }*/
                }
                //this -> root -> setData( *queue.dequeue() ) ;
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
        T tmp = cur -> getData() ;
        string bas = basis.setData( tmp ) ;
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
            //int *arr = new int[ 1000 ]{ 0 } ;//index of '[' * num
            list -> searchIdx( '[' , num , idx_list ) ;//cout << "hi" ;
            int idx_len = idx_list.size() ;
            Node<int> *it = idx_list.getHead() ;
            //cout << "n:" << n << endl ;
            for( int i = 0 ; i < n ; i++ )/**for one level*/
            {
                cur = *q.dequeue() ;
                if( cur == SEP )
                {
                    it = it -> getNext() ;
                    //sep++ ;
                    //cout << "sep+++++++++++++++\n" ;
                    continue ;
                }
                T tmp = cur -> getData() ;//cout << "XXX" ;
                if( cur -> end() )
                {
                    string bas = basis.setDataEnd( tmp ) ;
                    //cout << "bas:" << bas << " " << bas.size() << endl ;
                    list -> insertIdx( it -> getData() , bas ) ;
                    //cout << "sep:" << sep << endl ;
                    idx_list.allAdd( bas.size() ) ;
                }else{
                    string bas = basis.setData( tmp ) ;
                    list -> insertIdx( it -> getData() , bas ) ;
                    //cout << "bas:" << bas << " " << bas.size() << endl ;
                    //cout << "sep:" << sep << endl ;
                    idx_list.allAdd( bas.size() ) ;
                }
                for( Node<TreeNode<T>*> *ptr = cur -> getChildren() -> getHead() ; ptr ; ptr = ptr -> getNext() )
                {
                    if( ptr -> getData() && ptr -> getData() -> getData() != '\n' )
                    {
                        q.enqueue( ptr -> getData() ) ;
                    }
                }
                if( cur -> getChildren() -> size() == 0 || ( cur -> getChildren() -> size() == 1 && cur -> end() ) )
                {
                    q.enqueue( SEP ) ;
                }
                if( q.getList() -> getTail() && q.getList() -> getTail() -> getData() != SEP )
                {
                    q.enqueue( SEP ) ;//mark the end of children of one parent
                }
            }

            /*
            if( !q.empty() && q.getFirst() && q.getFirst() -> getData() == SEP )
            {
                q.dequeue() ;
            }*/
            //delete [] arr ;
        }
        /*
        string output = "" ;
        for( Node<char> *ptr = list -> getHead() ; ptr ; ptr = ptr -> getNext() )
        {
            output += ptr -> getData() ;
        }
        output += "\0" ; /****+= '\0' ->> WA****/
        //cout << "list -> size():" << list -> size() << endl ;
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

int main() {
    //string test = "df" ;
    //cout << test << endl ;
    //test += '0' + 3 ;
    //cout << test << endl ;

    /*string input ;
    cin >> input ;
    GeneralTree<char , string> GT ;
    //GT.deSerialize( input ) ;//level-order
    //GT.levelorder() ;
    GT.deSerialize2( input ) ;//post-order
    GT.levelorder() ;
    //cout << "{\"children\":[],\"data\":}" << endl ;
    seri << GT.serialize() ;
    return 0 ;*/

    GeneralTree<char , string> gt ;
    /*gt.insert( "hello" ) ;
    gt.levelorder() ;
    gt.insert( "hells" ) ;
    gt.levelorder() ;
    gt.insert( "hela" ) ;
    gt.levelorder() ;
    cout << gt.search("he") << endl ;
    cout << gt.search("hello") << endl ;
    cout << gt.search("hells") << endl ;
    cout << gt.search("hela") << endl ;
    cout << gt.search("hell") << endl ;
    gt.remove( "hells" ) ;
    gt.levelorder() ;
    cout << gt.serialize() ;
    cout << "start:" << Node<char>::nodeCount << endl ;*/
    int m = 0 , n = 0 ;
    cin >> m >> n ;

    for( int i = 0 ; i < m ; i++ )
    {
        string s ;
        cin >> s ;
        gt.insert( s ) ;
    }
    for( int i = 0 ; i < n ; i++ )
    {
        string s ;
        cin >> s ;
        if( gt.search( s ) )
        {
            cout << 1 << endl ;
            //cout << gt.search( s ) -> getData() << "XX\n" ;
        }else{
            cout << 0 << endl ;
        }
    }
    //gt.levelorder() ;
    //gt.preorder() ;
    //gt.inorder() ;
    //gt.postorder() ;
    /*if( gt.empty() )
    {
        return 0 ;
    }*/
    cout << gt.serialize() << endl ;
    //cout << "end:" << Node<char>::nodeCount << endl ;
    return 0;
}
/**
the type of key in JSON must be string
**/
/*
{"root":{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[],"data":"r","end":"true"}],"data":"e"}],"data":"w"}],"data":"s","end":"true"},{"children":[],"data":"y","end":"true"}],"data":"n"}],"data":"a"},{"children":[{"children":[{"children":[],"data":"e","end":"true"}],"data":"y"}],"data":"b"},{"children":[{"children":[{"children":[{"children":[{"children":[],"data":"r","end":"true"}],"data":"i"},{"children":[{"children":[],"data":"e","end":"true"}],"data":"r"}],"data":"e"}],"data":"h"}],"data":"t"}],"data":""}}
{"root":{"children":[{"children":[{"children":[],"data":"d"},{"children":[],"data":"p"}],"data":"a"},{"children":[],"data":"b"}],"data":""}}
*/
/**SERIALIZE
Basis:{"children":[],"data":}
{"root":}
{"root":{"children":[],"data":""}}
{"root":{"children":[{"children":[],"data":"a"},{"children":[],"data":"b"}],"data":""}}
{"root":{"children":[{"children":[{"children":[],"data":"d"},{"children":[],"data":"p"}],"data":"a"},{"children":[],"data":"b"}],"data":""}}
{"root":{"children":[{"children":[{"children":[],"data":"d"},{"children":[],"data":"p"}],"data":"a"},{"children":[{"children":[],"data":"c"}],'data":"b"}],"data":""}}
*/

/*
6 5
answer
ans
any
bye
their
there
ans
any
the
byb
answ
*/

/*
5 2
aaa
bbb
ccc
aab
ddd
aa
aaa
*/

/*
6
3
aaa
aab
b
c
dda
aa
aa
da
aac
{"root":{"children":[{"children":[{"children":[{"children":[],"data":"a","end":"true"},{"children":[],"data":"b","end":"true"}],"data":"a","end":"true"}],"data":"a"},{"children":[],"data":"b","end":"true"},{"children":[],"data":"c","end":"true"},{"children":[{"children":[{"children":[],"data":"a","end":"true"}],"data":"d"}],"data":"d"}],"data":""}}
*/

/*
3 2
a
a
a
ab
a
*/

/*
3 2
abc
abd
abe
abeee
ab
{"root":{"children":[{"children":[{"children":[{"children":[],"data":"c","end":"true"},{"children":[],"data":"d","end":"true"},{"children":[],"data":"e","end":"true"}],"data":"b"}],"data":"a"}],"data":""}}
*/

/*

*/

/*
the TreeNode in same level have same depth of '['
*/

/*
{"root":{"children":[{"children":[{"children":[{"children":[],"data":"a","end":"true"},{"children":[],"data":"b","end":"true"}],"data":"a","end":"true"}],"data":"a"},{"children":[],"data":"b","end":"true"},{"children":[],"data":"c","end":"true"},{"children":[{"children":[{"children":[],"data":"a","end":"true"}],"data":"d"}],"data":"d"}],"data":""}}*/
