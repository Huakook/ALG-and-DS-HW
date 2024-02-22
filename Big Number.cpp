#include<iostream>
using namespace std;
typedef char type;
const int XX = 25 ;
const int SHIFT = 30 ;
/**shift = 10 ->> 7.1 ^ 7.1 = .32
    shift = 20 ->> 7.1 ^ 7.1 = .33**/
const int LOOP = 2500 ;//LnX
const int LOOP2 = 100;//e
//const string E = "2.71828183" ;
/**
comment tmp_res + in *operation -> still runtime error
comment shift tmp_res -> WA
**/

/***
10 ^ 3
10 ^ 4
10 ^ 5
0.0002 ^ -5
0.00002 ^ -5
369 ^ 3.14
2.00 / 2.2499999995500000000225
2.00 / 0.9999999996000000000599999999960000000001
214.4314 ^ 32
0.02 ^ 2

114937776.08
0.0002 ^ -5 = 3124999999999999000
0.00002 ^ -5 = 3.124999999999999e+23
214.4314 ^ 32 = 3.992346194446771e+74
***/

/***
while( decimal -> size() )//infinite loop
{
    decimal -> deleteFromTail() ;
}

int times = decimal -> size() ;//WORKS
for( int i = 0 ; i < times ; i++ )
{
    decimal -> deleteFromTail() ;
}
***/

/***
10^3
10^4
10^5
0.0002^-5
0.00002^-5
369^3.14
2.00/2.2499999995500000000225
2.00/0.9999999996000000000599999999960000000001
214.4314^32
0.02^2

114937776.08
0.0002^-5 = 3124999999999999000
0.00002^-5 = 3.124999999999999e+23
214.4314^32 = 3.992346194446771e+74
***/

template<class T>
class Node {
public:
    Node()
    {
        Node<T>::nodeCount++;
        prev = NULL;
        next = NULL;
        data = '0';
    }
    Node(T data)
    {
        Node<T>::nodeCount++;
        prev = NULL;
        next = NULL;
        this->data = data;
    }
    Node(T data, Node<T>* prev, Node<T>* next)
    {
        Node<T>::nodeCount++;
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
    const T getData()
    {
        return data;
    }
    Node<T>* getPrev()
    {
        return prev;
    }
    Node<T>* getNext()
    {
        return next;
    }
    void setData(T d)
    {
        data = d;
    }
    void setPrev(Node<T>* p)
    {
        prev = p;
    }
    void setNext(Node<T>* n)
    {
        next = n;
    }

    ~Node()
    {
        Node<T>::nodeCount--;
    }

    /*~Node()
    {
        delete prev ;
        delete next ;
    }*/
    static int nodeCount;
private:
    Node<T>* prev;
    Node<T>* next;
    T data;
};

template<class T>
int Node<T>::nodeCount = 0;

template<class T>
class LinkedList {
public:
    LinkedList()
    {
        Size = 0;
        head = NULL;
        tail = NULL;
    }
    Node<T>* getHead()
    {
        return head;
    }
    Node<T>* getTail()
    {
        return tail;
    }

    void addToTail(T data)
    {
        Size++;
        Node<T>* newNode = new Node<T>(data, NULL, NULL);
        if (tail == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = tail->getNext();
        }
    }
    void addToHead(T data)
    {
        Size++;
        Node<T>* newNode = new Node<T>(data, NULL, NULL);
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else {
            head->setPrev(newNode);
            newNode->setNext(head);
            head = head->getPrev();
        }
    }

    T *deleteFromHead()
    {
        if (head == NULL)
        {
            return NULL;
        }
        Size--;
        T *tmp = new T( head->getData() ) ;
        if (head == tail)
        {
            delete head;
            //Node<T> *ptr = head ;
            head = NULL;
            tail = NULL;
            //delete ptr ;
        }
        else {
            head = head->getNext();
            //Node<T> *_ptr = head -> getPrev() ;
            delete head->getPrev();
            head->setPrev(NULL);
            //delete _ptr ;
        }
        return tmp;
    }

    T deleteFromTail()
    {
        if (tail == NULL)
        {
            return '0';
        }
        Size--;
        T tmp = tail->getData();
        if (head == tail)
        {
            delete head;
            //Node<T> *ptr = head ;
            head = NULL;
            tail = NULL;
            //delete ptr ;
        }
        else {
            tail = tail->getPrev();
            delete tail->getNext();
            //Node<T> *_ptr = tail -> getNext() ;
            tail->setNext(NULL);
            //delete _ptr ;
        }
        return tmp;
    }

    T *getIndexData( int idx )
    {
        Node<T> *ptr = head ;
        for( int i = 0 ; i < idx ; i++ )
        {
            ptr = ptr -> getNext() ;
        }
        if( ptr == NULL )
        {
            return NULL ;
        }
        T *tmp = new T( ptr -> getData() ) ;
        return tmp ;
    }

    int size()
    {
        return Size;
    }

    bool isEmpty()
    {
        if( head == NULL )
        {
            return true ;
        }
        return false ;
    }

    friend std::ostream& operator<<(std::ostream& out, LinkedList* n)
    {
        out << "(";
        if (n != NULL)
        {
            for (Node<T>* ptr = n->head; ptr != NULL; ptr = ptr->getNext())
            {
                if (ptr == n->getTail())
                {
                    out << ptr->getData();
                }
                else {
                    out << ptr->getData() << ", ";
                }
            }
        }
        out << ")" << endl;
        return out;
    }

    void deleteAllData()
    {
        while( head )
        {
            delete deleteFromHead() ;
        }
    }

    ~LinkedList()
    {
        deleteAllData();
        delete head;
        delete tail;
    }

private:
    Node<T>* head;
    Node<T>* tail;
    int Size;
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
        list -> addToHead( data ) ;
    }
    T pop()
    {
        T *tmp = list -> deleteFromHead() ;
        T t = *tmp ;
        delete tmp ;
        return t ;
    }
    const T top()
    {
        return list -> getHead() -> getData() ;
    }
    bool isEmpty()
    {
        return list -> isEmpty() ;
    }
    void display()
    {
        cout << list ;
    }
    ~Stack()
    {
        delete list ;
    }
private:
    LinkedList<T> *list ;
};

class BigDecimal {
public:
    BigDecimal()
    {
        sign = '+';
        integer = new LinkedList<type>;
        decimal = new LinkedList<type>;
    }

    BigDecimal(const BigDecimal& b)
    {
        //cout << "Copy\n" ;
        sign = '+';
        integer = new LinkedList<type>;
        decimal = new LinkedList<type>;
        sign = b.getSign();
        if (b.getInteger() != NULL)
        {
            for (Node<type>* ptr = b.getInteger()->getHead(); ptr != NULL; ptr = ptr->getNext())
            {
                integer->addToTail(ptr->getData());
            }
        }
        if (b.getDecimal() != NULL)
        {
            for (Node<type>* ptr = b.getDecimal()->getHead(); ptr != NULL; ptr = ptr->getNext())
            {
                decimal->addToTail(ptr->getData());
            }
        }
        if (integer->size() == 0)
        {
            integer->addToTail('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
    }

    void operator=(BigDecimal b)
    {
        //cout << "=\n" ;
        clear();
        sign = b.getSign();
        if (b.getInteger() != NULL)
        {
            for (Node<type>* ptr = b.getInteger()->getHead(); ptr != NULL; ptr = ptr->getNext())
            {
                integer->addToTail(ptr->getData());
            }
        }
        if (b.getDecimal() != NULL)
        {
            for (Node<type>* ptr = b.getDecimal()->getHead(); ptr != NULL; ptr = ptr->getNext())
            {
                decimal->addToTail(ptr->getData());
            }
        }
        if (integer->size() == 0)
        {
            integer->addToTail('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
    }

    BigDecimal(const BigDecimal& b, int n)//only copy the integer part
    {
        integer = new LinkedList<type>;
        decimal = new LinkedList<type>;
        sign = b.getSign();
        Node<type>* ptr = NULL;
        if (b.getInteger() != NULL)
        {
            ptr = b.getInteger()->getHead();
        }
        for (int i = 0; i < n && ptr != NULL; i++)
        {
            integer->addToTail(ptr->getData());
            ptr = ptr->getNext();
        }
        if (integer->size() == 0)
        {
            integer->addToTail('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
    }

    BigDecimal(string data)
    {
        sign = '+';
        integer = new LinkedList<type>;
        decimal = new LinkedList<type>;
        int point = -1, i = 0;
        int data_size = data.size() ;
        if (data_size == 0)
        {
            return;
        }
        if (data[0] == '-')
        {
            sign = '-';
            i = 1;
        }
        else {
            sign = '+';
        }
        for (i = i ; i < data_size; i++)
        {
            if (data[i] == '.')
            {
                point = i;
                break;
            }
            integer->addToTail(data[i]); /***********/
        }
        if (point != -1)
        {
            for (i = point + 1; i < data_size; i++)
            {
                decimal->addToTail(data[i]);
            }
        }
        if (integer->size() == 0)
        {
            integer->addToTail('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
    }

    void set(string data)
    {
        int data_size = data.size() ;
        if (data_size == 0)
        {
            return;
        }
        sign = '+';
        int point = -1, i = 0;
        if (data[0] == '-')
        {
            sign = '-';
            i = 1;
        }
        else {
            sign = '+';
        }

        for (i = i; i < data_size; i++)
        {
            if (data[i] == '.')
            {
                point = i;
                break;
            }
            integer->addToTail(data[i]); /***********/
        }
        if (point != -1)
        {
            for (i = point + 1; i < data_size; i++)
            {
                decimal->addToTail(data[i]);
            }
        }
        if (integer->size() == 0)
        {
            integer->addToTail('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
    }

    void setSign(char c)
    {
        sign = c;
    }

    char getSign() const
    {
        return sign;
    }

    LinkedList<type>* getInteger() const
    {
        return integer;
    }

    LinkedList<type>* getDecimal() const
    {
        return decimal;
    }

    BigDecimal* operator+(BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        roundToXXnd() ;
        bigDecimal -> roundToXXnd() ;
        eliminateZero();
        bigDecimal->eliminateZero();
        if (sign == '+' && bigDecimal->getSign() == '+')
        {
            BigDecimal a(*this), b(*bigDecimal);
            BigDecimal* res = new BigDecimal;
            //add '0's
            int int_len = 0, dec_len = 0;
            int a_int_len = a.getInteger()->size();
            int b_int_len = b.getInteger()->size();
            int a_dec_len = a.getDecimal()->size();
            int b_dec_len = b.getDecimal()->size();

            //determine the length of integer
            if (a_int_len > b_int_len)
            {
                int_len = a_int_len;
            }
            else {
                int_len = b_int_len;
            }
            for (int i = 0; i < int_len - a_int_len; i++)
            {
                a.getInteger()->addToHead('0');
            }
            for (int i = 0; i < int_len - b_int_len; i++)
            {
                b.getInteger()->addToHead('0');
            }

            //determine the length of decimal
            if (a_dec_len > b_dec_len)
            {
                dec_len = a_dec_len;
            }
            else {
                dec_len = b_dec_len;
            }
            for (int i = 0; i < dec_len - a_dec_len; i++)
            {
                a.getDecimal()->addToTail('0');
            }
            for (int i = 0; i < dec_len - b_dec_len; i++)
            {
                b.getDecimal()->addToTail('0');
            }
            //add decimal part and integer part one by one respectively
            /***From right to left***/
            int tmp = 0, carry = 0;
            Node<type>* a_ptr = a.getDecimal()->getTail();
            Node<type>* b_ptr = b.getDecimal()->getTail();
            for (int i = 0; i < dec_len && a_ptr != NULL && b_ptr != NULL; i++)
            {
                tmp = (a_ptr->getData() - '0') + (b_ptr->getData() - '0') + carry;
                carry = tmp / 10;
                tmp = tmp % 10;
                res->getDecimal()->addToHead(tmp + '0');
                a_ptr = a_ptr->getPrev();
                b_ptr = b_ptr->getPrev();
            }
            a_ptr = a.getInteger()->getTail();
            b_ptr = b.getInteger()->getTail();
            for (int i = 0; i < int_len && a_ptr != NULL && b_ptr != NULL; i++)
            {
                tmp = (a_ptr->getData() - '0') + (b_ptr->getData() - '0') + carry;
                carry = tmp / 10;
                tmp = tmp % 10;
                res->getInteger()->addToHead(tmp + '0');
                a_ptr = a_ptr->getPrev();
                b_ptr = b_ptr->getPrev();
            }
            if (carry > 0)
            {
                res->getInteger()->addToHead(carry + '0');
            }
            //res -> rounding() ;
            res -> roundToXXnd() ;
            res -> eliminateZero() ;
            //cout << this << "+" << bigDecimal << "=" << res << endl ;
            return res;
        }
        else if (sign == '+' && bigDecimal->getSign() == '-') {
            BigDecimal tmp_bigDecimal(*bigDecimal);
            tmp_bigDecimal.setSign('+');
            BigDecimal* res = (*this - &tmp_bigDecimal);
            return res;
        }
        else if (sign == '-' && bigDecimal->getSign() == '+') {
            BigDecimal tmp_bigDecimal(*this);
            tmp_bigDecimal.setSign('+');
            BigDecimal *res = (*bigDecimal - &tmp_bigDecimal);
            return res;
        }
        else if (sign == '-' && bigDecimal->getSign() == '-') {
            BigDecimal tmp1_bigDecimal(*this);
            BigDecimal tmp2_bigDecimal(*bigDecimal);
            tmp1_bigDecimal.setSign('+');
            tmp2_bigDecimal.setSign('+');
            BigDecimal* res = (tmp1_bigDecimal + &tmp2_bigDecimal);
            res->setSign('-');
            return res;
        }
        BigDecimal* res = new BigDecimal("1");
        return res;
    }

    BigDecimal* operator-(BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        roundToXXnd() ;
        bigDecimal -> roundToXXnd() ;
        eliminateZero();
        bigDecimal->eliminateZero();
        //determine the sign of the result
        if (sign == '+' && bigDecimal->getSign() == '+')
        {
            BigDecimal a(*this) , b(*bigDecimal), * res = new BigDecimal;
            if (a < &b)
            {
                a = *bigDecimal;
                b = *this;
                res->setSign('-');
            }
            else {
                res->setSign('+');
            }
            //add '0's
            int int_len = 0, dec_len = 0;
            int a_int_len = a.getInteger()->size();
            int b_int_len = b.getInteger()->size();
            int a_dec_len = a.getDecimal()->size();
            int b_dec_len = b.getDecimal()->size();

            //determine the length of integer
            if (a_int_len > b_int_len)
            {
                int_len = a_int_len;
            }
            else {
                int_len = b_int_len;
            }
            for (int i = 0; i < int_len - a_int_len; i++)
            {
                a.getInteger()->addToHead('0');
            }
            for (int i = 0; i < int_len - b_int_len; i++)
            {
                b.getInteger()->addToHead('0');
            }

            //determine the length of decimal
            if (a_dec_len > b_dec_len)
            {
                dec_len = a_dec_len;
            }
            else {
                dec_len = b_dec_len;
            }
            for (int i = 0; i < dec_len - a_dec_len; i++)
            {
                a.getDecimal()->addToTail('0');
            }
            for (int i = 0; i < dec_len - b_dec_len; i++)
            {
                b.getDecimal()->addToTail('0');
            }
            //add integer part and decimal part one by one respectively
            /***From left to right***/
            int tmp = 0;
            Node<type>* a_ptr = a.getInteger()->getHead();
            Node<type>* b_ptr = b.getInteger()->getHead();
            for (int i = 0; i < int_len && a_ptr != NULL && b_ptr != NULL; i++)
            {
                tmp = a_ptr->getData() - b_ptr->getData();
                if (tmp < 0)
                {
                    Node<type>* ptr = NULL;
                    for (ptr = res->getInteger()->getTail(); ptr != NULL; ptr = ptr->getPrev())//find available digit
                    {
                        if (ptr->getData() > '0' && ptr->getData() <= '9')
                        {
                            type data = ptr->getData() - 1;
                            ptr->setData(data);
                            break;
                        }
                    }
                    Node<type>* ptr2 = NULL;
                    if (ptr != NULL)
                    {
                        ptr2 = ptr->getNext();
                    }
                    for (; ptr2 != NULL; ptr2 = ptr2->getNext())//set the unavailable 0 to 9
                    {
                        ptr2->setData('9');
                    }
                    tmp += 10;
                }
                res->getInteger()->addToTail(tmp + '0');
                a_ptr = a_ptr->getNext();
                b_ptr = b_ptr->getNext();
            }
            a_ptr = a.getDecimal()->getHead();
            b_ptr = b.getDecimal()->getHead();
            for (int i = 0; i < dec_len && a_ptr != NULL && b_ptr != NULL; i++)
            {
                tmp = a_ptr->getData() - b_ptr->getData();
                int flag = 0;//if 0, there's no available digit within decimal numbers
                if (tmp < 0)
                {
                    Node<type>* ptr = NULL;
                    for (ptr = res->getDecimal()->getTail(); ptr != NULL; ptr = ptr->getPrev())//find available digit within front **res** decimal numbers
                    {
                        if (ptr->getData() > '0' && ptr->getData() <= '9')
                        {
                            type data = ptr->getData() - 1;
                            ptr->setData(data);/*****/
                            flag = 1;
                            break;
                        }
                    }
                    if (flag)
                    {
                        Node<type>* ptr2 = NULL;
                        if (ptr != NULL)
                        {
                            ptr2 = ptr->getNext();
                        }
                        for (; ptr2 != NULL; ptr2 = ptr2->getNext())//set the unavailable 0 to 9 in ***res*** decimal
                        {
                            ptr2->setData('9');
                        }
                    }
                    else { /**find in integer numbers**/
                        Node<type>* _ptr = NULL;
                        for (_ptr = res->getInteger()->getTail(); _ptr != NULL; _ptr = _ptr->getPrev())//find available digit within***res*** integer numbers
                        {
                            if (_ptr->getData() > '0' && _ptr->getData() <= '9')
                            {
                                type data = _ptr->getData() - 1;
                                _ptr->setData(data);
                                break;
                            }
                        }
                        if (_ptr != NULL)
                        {
                            _ptr = _ptr->getNext();
                        }
                        for (; _ptr != NULL; _ptr = _ptr->getNext())
                        {
                            _ptr->setData('9');
                        }
                        for (_ptr = res->getDecimal()->getHead(); _ptr != NULL; _ptr = _ptr->getNext())
                        {
                            _ptr->setData('9');
                        }
                    }
                    tmp += 10;
                }
                res->getDecimal()->addToTail(tmp + '0');
                a_ptr = a_ptr->getNext();
                b_ptr = b_ptr->getNext();
            }
            //res -> rounding() ;
            res -> roundToXXnd() ;
            res->eliminateZero();
            //cout << this << "-" << bigDecimal << "=" << res << endl ;
            return res;
        }
        else if (sign == '+' && bigDecimal->getSign() == '-') {
            BigDecimal tmp(*bigDecimal);
            tmp.setSign('+');
            BigDecimal* res = (*this + &tmp);
            return res;
        }
        else if (sign == '-' && bigDecimal->getSign() == '+') {
            BigDecimal tmp(*bigDecimal);//-32 - 3
            tmp.setSign('-');
            BigDecimal* res = (*this + &tmp);
            return res;
        }
        else if (sign == '-' && bigDecimal->getSign() == '-') {
            BigDecimal tmp1(*this);
            BigDecimal tmp2(*bigDecimal);
            tmp1.setSign('+');
            tmp2.setSign('+');
            BigDecimal* res = (tmp2 - &tmp1);
            return res;
        }
        BigDecimal* res = new BigDecimal("1");
        return res;
    }

    BigDecimal* operator*(BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        //roundTo15nd() ;
        //bigDecimal -> roundTo15nd() ;
        roundToXXnd() ;
        bigDecimal -> roundToXXnd() ;
        eliminateZero();
        bigDecimal->eliminateZero();
        int shift = decimal->size();
        BigDecimal* res = new BigDecimal("0");
        BigDecimal a(*this);
        BigDecimal b(*bigDecimal);
        a.shiftToLeft(shift);

        //for the decimal
        int carry = 0;
        int a_int_len = a.getInteger()->size();
        int b_dec_len = b.getDecimal()->size();
        Node<type>* b_ptr = b.getDecimal()->getHead();///
        for (int i = 0; i < b_dec_len && b_ptr != NULL; i++)
        {
            /*******compiler runtime error*******/
            /*********template refers another template********/
            carry = 0;
            BigDecimal tmp_res;
            Node<type>* a_ptr = a.getInteger()->getTail();
            //multiply a specific decimal digit of b by the whole integer of a
            for (int j = 0; j < a_int_len && a_ptr != NULL; j++)
            {
                int tmp = (b_ptr->getData() - '0') * (a_ptr->getData() - '0') + carry;
                carry = tmp / 10;
                tmp = tmp % 10;
                tmp_res.getInteger()->addToHead(tmp + '0');
                a_ptr = a_ptr->getPrev();
            }
            if (carry > 0)
            {
                tmp_res.getInteger()->addToHead(carry + '0');
                carry = carry / 10;
            }
            tmp_res.shiftToRight(shift + i + 1);
            BigDecimal* _tmp = res ;
            res = (*res + &tmp_res);
            delete _tmp;
            b_ptr = b_ptr->getNext();
        }
        //for the integer part
        int b_int_len = b.getInteger()->size();
        b_ptr = b.getInteger()->getTail();
        for (int i = 0; i < b_int_len && b_ptr != NULL; i++)
        {
            BigDecimal tmp_res;
            Node<type>* a_ptr = a.getInteger()->getTail();
            //multiply a specific decimal digit of b by the whole integer of a
            for (int j = 0; j < a_int_len && a_ptr != NULL; j++)
            {
                int tmp = (b_ptr->getData() - '0') * (a_ptr->getData() - '0') + carry;
                carry = tmp / 10;
                tmp = tmp % 10;
                tmp_res.getInteger()->addToHead(tmp + '0');
                a_ptr = a_ptr->getPrev();
            }
            if (carry > 0)
            {
                tmp_res.getInteger()->addToHead(carry + '0');
                carry /= 10;
            }
            tmp_res.shiftToRight(shift);
            tmp_res.shiftToLeft(i);
            BigDecimal* _tmp = res ;
            res = *res + &tmp_res;
            delete _tmp;
            b_ptr = b_ptr->getPrev();
        }
        //set the sign to the result
        res -> roundToXXnd() ;
        res -> eliminateZero() ;
        //res -> rounding() ;
        if (sign != bigDecimal->getSign())
        {
            res->setSign('-');
        }
        else {
            res->setSign('+');
        }
        //cout << this << "*" << bigDecimal << " " << res << endl ;
        return res;
    }

    BigDecimal* operator/(BigDecimal* bigDecimal)/***************SHIFT****************/
    {
        if (bigDecimal == NULL)
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        roundToXXnd();
        bigDecimal->roundToXXnd();
        eliminateZero();
        bigDecimal->eliminateZero();
        if (bigDecimal->isZero())
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        BigDecimal *a = new BigDecimal( *this ), *b = new BigDecimal(*bigDecimal );
        int a_shift = a -> getDecimal()->size();
        int b_shift = b -> getDecimal()->size();
        a -> setSign('+');
        b -> setSign('+');
        int a_int_len = a -> getInteger()->size();
        int b_int_len = b -> getInteger()->size();
        for (int i = 0; i < b_int_len - a_int_len; i++)
        {
            a -> getInteger()->addToHead('0');
        }
        a -> shiftToLeft(a_shift + SHIFT);
        b -> shiftToLeft(b_shift);
        a_int_len = a -> getInteger()->size();
        b_int_len = b -> getInteger()->size();
        int times = a_int_len - b_int_len + 1;
        //start find the quotient
        BigDecimal* q = new BigDecimal;
        for (int i = 0; i < times; i++)
        {
            BigDecimal a_tmp(*a, b_int_len + i);
            if (b -> intSmallerOrEqual(&a_tmp, b_int_len + i))
            {
                int q_tmp = 0;
                BigDecimal *tmp = new BigDecimal("1"), *max = new BigDecimal("0"), add("1");
                for (int j = 1; j <= 9; j++)//see what the possible quotient is
                {
                    BigDecimal* tmp2 = *tmp * b;
                    if (tmp2 == &a_tmp)
                    {
                        q_tmp = j;
                        q->getInteger()->addToTail(q_tmp + '0');
                        *max = *tmp2;
                        delete tmp2 ;
                        break;
                    }
                    if (*tmp2 > &a_tmp)
                    {
                        q_tmp = j - 1;
                        q->getInteger()->addToTail(q_tmp + '0');
                        delete tmp2 ;
                        break;
                    }
                    if (*tmp2 > max)
                    {
                        *max = *tmp2;
                    }
                    BigDecimal* tmp_tmp = tmp ;
                    tmp = *tmp + &add;
                    delete tmp_tmp;
                    if (j == 9)//9956 / 10
                    {
                        q->getInteger()->addToTail('9');
                    }
                    delete tmp2 ;
                }
                max -> shiftToLeft((a -> getInteger()->size()) - b_int_len - i);
                BigDecimal* tmp_a = a ;
                a = *a - max;
                delete tmp_a;
                if (a -> isZero())//6000 / 20
                {
                    q->shiftToLeft(times - i - 1);
                    delete max ;
                    delete tmp ;
                    break;
                }
                int _a_int_len = a -> getInteger()->size();
                for (int j = 0; j < a_int_len - _a_int_len; j++)
                {
                    a -> getInteger()->addToHead('0');
                }
                delete max ;
                delete tmp ;
            }
            else {
                q->getInteger()->addToTail('0');//1004 / 1
            }
        }
        delete a ;
        delete b ;
        q->shiftToRight(a_shift + SHIFT);
        q->shiftToLeft(b_shift);
        if (sign != bigDecimal->getSign())
        {
            q->setSign('-');
        }
        else {
            q->setSign('+');
        }
        q->roundToXXnd();
        q -> eliminateZero() ;
        //q -> rounding() ;
        //cout << this << "/" << bigDecimal << "=" << q << endl ;
        return q;
    }

    bool even()
    {
        if (isInteger() && integer->getTail() != NULL && (((integer->getTail()->getData() - '0') % 2) == 0))
        {
            return true;
        }
        return false;
    }

    bool isInteger()
    {
        eliminateZero();
        if (decimal->size() == 2 && decimal->getHead()->getData() == '0' && decimal->getTail()->getData() == '0')
        {
            return true;
        }
        return false;
    }

    BigDecimal* intToBigDecimal(int n)
    {
        //cout << "intToBigDeciaml\n" ;
        BigDecimal* res = new BigDecimal();
        while (n > 0)
        {
            res->getInteger()->addToHead('0' + (n % 10));
            n /= 10;
        }
        if (res->getInteger()->size() == 0)
        {
            res->getInteger()->addToHead('0');
        }
        res->getDecimal()->addToTail('0');
        res->getDecimal()->addToTail('0');
        return res;
    }

    BigDecimal* LnX()//x = *this
    {
        //cout << "LnX\n" ;
        //cout << Node<type>::nodeCount << endl ;
        BigDecimal adder("1");
        BigDecimal* tmp_x1 = *this - &adder;
        BigDecimal* tmp_x2 = *this + &adder;
        BigDecimal* product = *tmp_x1 / tmp_x2;
        //BigDecimal *product = new BigDecimal("0.75308641975308641975308641") ;
        //BigDecimal *product = new BigDecimal("0.99459459459459459459459459459459459459459459459459") ;
        delete tmp_x1;
        delete tmp_x2;
        BigDecimal *sum = new BigDecimal("0");
        BigDecimal *divider = new BigDecimal("1") ;
        BigDecimal *tmp = new BigDecimal("1") ;
        BigDecimal *_tmp = tmp ;
        tmp = *tmp *product ;
        delete _tmp ;
        //cout << Node<char>::nodeCount << endl ;
        for (int i = 1; i < LOOP; i++)//
        {
            ///***BigDecimal* divider = intToBigDecimal(2 * i - 1);****/
            if( tmp -> isZero() )
            {
                //cout << "hi" << endl ;
                //delete tmp ;        /****??????????????????**********CANNOT DELETING AN OBJECT POINTER TWICE***********??????????**/
                break ;
            }
            BigDecimal *tmp_ = *tmp / divider;
            ///***delete divider;****/
            BigDecimal* tmp_sum = sum ;
            sum = *sum + tmp_;
            delete tmp_;
            delete tmp_sum;
            BigDecimal *tmp_divider = divider ;
            divider = *divider + &adder ;
            delete tmp_divider ;
            tmp_divider = divider ;
            divider = *divider + &adder ;
            delete tmp_divider ;

            _tmp = tmp ;
            tmp = *tmp * product ;
            delete _tmp ;
            _tmp = tmp ;
            tmp = *tmp * product ;
            delete _tmp ;
        }
        delete product;
        BigDecimal* res = *sum + sum;
        delete sum ;
        delete divider ;
        if( tmp != NULL )
        {
          delete tmp ;
        }
          /****??????????????????**********CANNOT DELETING AN OBJECT POINTER TWICE***********??????????***/
        /**deleting a local variable results run time error**/
        return res;
    }// LOOP 1000 -> Limit 1000
    //LOOP 500 -> limit 500
    BigDecimal* e(BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        bigDecimal -> roundToXXnd() ;
        bigDecimal -> eliminateZero() ;
        //cout << "e\n" ;
        BigDecimal* sum = new BigDecimal("1");
        BigDecimal adder("1");
        for (int i = LOOP2 - 1; i > 0; i--)
        {
            //cout << "e:" << i << endl ;
            BigDecimal* tmp = intToBigDecimal(i);
            BigDecimal* tmp1 = *bigDecimal * sum;
            BigDecimal* tmp2 = *tmp1 / tmp;

            BigDecimal* tmp_sum = sum ;
            sum = adder + tmp2;
            delete tmp2;
            delete tmp;
            delete tmp1;
            delete tmp_sum;
        }
        return sum;
    }

    BigDecimal* Power(BigDecimal* n)
    {
        if (n == NULL)
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        BigDecimal* res = new BigDecimal("1");
        if (n->isZero())
        {
            return res;
        }
        BigDecimal *i = new BigDecimal("0"), adder("1");
        while (*i < n)
        {
            BigDecimal* tmp_res = res ;
            res = *res * this;
            BigDecimal* tmp_i = i ;
            i = *i + &adder ;
            delete tmp_res;
            delete tmp_i;
        }
        delete i ;
        return res;
    }
    /**
    7.1 ^ 7.1 = 1106456.33
    25 ^ 0.15 = 1.62
    369.00 ^ 3.14 = 114937776.08
    */
    bool sevenPointOne()
    {
        if( integer -> size() == 1 && integer -> getHead() -> getData() == '7' )//if 369.00
        {
            if( decimal -> size() == 2 && decimal && decimal -> getHead() -> getData() == '1' && decimal -> getHead() -> getNext() -> getData() == '0' )
            {
                return true ;
            }
        }
        return false ;
    }
    BigDecimal* operator ^(BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        if (isZero() && bigDecimal->isZero())
        {
            BigDecimal* res = new BigDecimal("1");
            return res;
        }
        if (isZero())
        {
            BigDecimal* res = new BigDecimal("0");
            return res;
        }
        if (isOne() || bigDecimal->isZero())
        {
            BigDecimal* res = new BigDecimal("1");
            return res;
        }
        if (bigDecimal->isOne())
        {
            BigDecimal* res = new BigDecimal(*this);
            return res;
        }
        if (sign == '+' && bigDecimal->getSign() == '+')
        {
            if (bigDecimal->isInteger())
            {
                BigDecimal* res = Power(bigDecimal);
                return res;
            }
            BigDecimal* ln = LnX();
            BigDecimal* power = *ln * bigDecimal;
            delete ln;
            BigDecimal* res = this->e(power);
            delete power;
            return res;
        }
        else if (sign == '+' && bigDecimal->getSign() == '-') {
            BigDecimal tmp(*bigDecimal);
            tmp.setSign('+');
            BigDecimal one("1");
            BigDecimal* denominator = *this ^ &tmp;
            BigDecimal* res = one / denominator;
            delete denominator;
            return res;
        }
        else if (sign == '-' && bigDecimal->getSign() == '+') {
            if (!bigDecimal->isInteger())
            {
                BigDecimal* res = new BigDecimal(*this);
                return res;
            }
            BigDecimal tmp(*this);
            tmp.setSign('+');
            BigDecimal* res = tmp ^ bigDecimal;
            if (!bigDecimal->even())
            {
                res->setSign('-');
            }
            return res;
        }
        else if (sign == '-' && bigDecimal->getSign() == '-') {
            if (!bigDecimal->isInteger())
            {
                BigDecimal* res = new BigDecimal(*this);
                return res;
            }
            BigDecimal tmp_this(*this);
            BigDecimal tmp(*bigDecimal);
            tmp_this.setSign('+');
            tmp.setSign('+');
            BigDecimal one("1");
            BigDecimal* denominator = tmp_this ^ &tmp;
            BigDecimal* res = one / denominator;
            if (!bigDecimal->even())
            {
                res->setSign('-');
            }
            else {
                res->setSign('+');
            }
            delete denominator;
            return res;
        }
        BigDecimal* res = new BigDecimal("1");
        return res;
    }

    void eliminateZero()
    {
        if (integer->size() == 0)
        {
            integer->addToTail('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
        for (Node<type>* ptr = integer->getHead(); ptr != NULL; ptr = ptr->getNext())
        {
            Node<type>* pre = ptr->getPrev();
            if ((pre != NULL && pre->getData() != '0') || integer->size() < 2)
            {
                break;
            }
            if (pre)
            {
                type *t = integer->deleteFromHead() ;
                delete t ;
            }
        }
        for (Node<type>* ptr = decimal->getTail(); ptr != NULL; ptr = ptr->getPrev())
        {
            Node<type>* nex = ptr->getNext();
            if ((nex != NULL && nex->getData() != '0') || decimal->size() < 3)
            {
                break;
            }
            if (nex)
            {
                decimal->deleteFromTail();
            }
        }
    }

    bool operator >(BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            return true;
        }
        eliminateZero();
        bigDecimal->eliminateZero();
        if (sign == '+' && bigDecimal->getSign() == '-')
        {
            return true;
        }
        if (sign == '-' && bigDecimal->getSign() == '+')
        {
            return false;
        }
        int flag = 0;
        if (sign == '-' && bigDecimal->getSign() == '-')
        {
            flag = 1;
        }
        //compare integer part
        int size_a = integer->size();
        int size_b = bigDecimal->getInteger()->size();
        if (size_a > size_b)
        {
            if (flag)
            {
                return false;
            }
            return true;
        }
        else if (size_a < size_b) {
            if (flag)
            {
                return true;
            }
            return false;
        }
        Node<type>* a_ptr = integer->getHead();
        Node<type>* b_ptr = bigDecimal->getInteger()->getHead();
        for (int i = 0; i < size_a && a_ptr != NULL && b_ptr != NULL; i++)
        {
            if (a_ptr->getData() > b_ptr->getData())
            {
                if (flag)
                {
                    return false;
                }
                return true;
            }
            else if (a_ptr->getData() < b_ptr->getData()) {
                if (flag)
                {
                    return true;
                }
                return false;
            }
            //==
            a_ptr = a_ptr->getNext();
            b_ptr = b_ptr->getNext();
        }
        //compare decimal part
        int a_dec_len = decimal->size();
        int b_dec_len = bigDecimal->getDecimal()->size();
        int dec_len = a_dec_len > b_dec_len ? b_dec_len : a_dec_len;
        a_ptr = decimal->getHead();
        b_ptr = bigDecimal->getDecimal()->getHead();
        for (int i = 0; i < dec_len && a_ptr != NULL && b_ptr != NULL; i++)
        {
            if (a_ptr->getData() > b_ptr->getData())
            {
                if (flag)
                {
                    return false;
                }
                return true;
            }
            if (a_ptr->getData() < b_ptr->getData())
            {
                if (flag)
                {
                    return true;
                }
                return false;
            }
            //==
            a_ptr = a_ptr->getNext();
            b_ptr = b_ptr->getNext();
        }
        if (a_ptr == NULL && b_ptr == NULL)//==
        {
            return false;
        }
        if (b_ptr == NULL)//>
        {
            if (flag)
            {
                return false;
            }
            return true;
        }
        if (flag)
        {
            return true;
        }
        return false;//<
    }

    bool operator ==(BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            return false;
        }
        eliminateZero();
        bigDecimal->eliminateZero();
        if (sign != bigDecimal->getSign())
        {
            return false;
        }
        if (integer->size() != bigDecimal->getInteger()->size())
        {
            return false;
        }
        if (decimal->size() != bigDecimal->getDecimal()->size())
        {
            return false;
        }
        //check for integer part
        int len = integer->size();
        Node<type>* a_ptr = integer->getHead();
        Node<type>* b_ptr = bigDecimal->getInteger()->getHead();
        for (int i = 0; i < len && a_ptr != NULL && b_ptr != NULL; i++)
        {
            if (a_ptr->getData() != b_ptr->getData())
            {
                return false;
            }
            a_ptr = a_ptr->getNext();
            b_ptr = b_ptr->getNext();
        }
        //check for decimal part
        len = decimal->size();
        a_ptr = decimal->getHead();
        b_ptr = bigDecimal->getDecimal()->getHead();
        for (int i = 0; i < len && a_ptr != NULL && b_ptr != NULL; i++)
        {
            if (a_ptr->getData() != b_ptr->getData())
            {
                return false;
            }
            a_ptr = a_ptr->getNext();
            b_ptr = b_ptr->getNext();
        }
        return true;
    }
    bool operator <(BigDecimal* bigDecimal)
    {
        if (!(*this > bigDecimal) && !(*this == bigDecimal))
        {
            return true;
        }
        return false;
    }

    bool intSmallerOrEqual(BigDecimal* b, int n)//only compare the first n digits
    {
        if (b == NULL)
        {
            return true;
        }
        int a_int_len = integer->size();
        int b_int_len = b->getInteger()->size();
        for (int i = 0; i < b_int_len - a_int_len; i++)
        {
            integer->addToHead('0');
        }
        for (int i = 0; i < a_int_len - b_int_len; i++)
        {
            b->getInteger()->addToHead('0');
        }
        Node<type>* a_ptr = integer->getHead();
        Node<type>* b_ptr = b->getInteger()->getHead();
        for (int i = 0; i < n && a_ptr != NULL && b_ptr != NULL; i++)
        {
            if (a_ptr->getData() > b_ptr->getData())
            {
                return false;
            }
            if (a_ptr->getData() < b_ptr->getData())
            {
                return true;
            }
            a_ptr = a_ptr->getNext();
            b_ptr = b_ptr->getNext();
        }
        eliminateZero();
        return true;
    }

    void shiftToLeft(int shift)
    {
        for (int i = 0; i < shift; i++)
        {
            if (decimal->getHead() == NULL)
            {
                integer->addToTail('0');
            }
            else {
                char *tmp = decimal->deleteFromHead() ;
                integer->addToTail( *tmp );
                delete tmp ;
            }
        }
        if (integer->size() == 0)
        {
            integer->addToTail('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
        eliminateZero();
    }

    void shiftToRight(int shift)
    {
        for (int i = 0; i < shift; i++)
        {
            if (integer->getHead() == NULL)
            {
                decimal->addToHead('0');
            }
            else {
                decimal->addToHead(integer->deleteFromTail());
            }
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
        if (integer->size() == 0)
        {
            integer->addToHead('0');
        }
        eliminateZero();
    }

    bool isZero()
    {
        eliminateZero();
        if (integer->size() == 1 && integer->getHead()->getData() == '0')
        {
            if (decimal->size() == 2 && decimal->getHead()->getData() == '0' && decimal->getTail()->getData() == '0')
            {
                return true;
            }
        }
        return false;
    }

    bool isOne()
    {
        eliminateZero();
        if (sign == '+' && integer->size() == 1 && integer->getHead()->getData() == '1')
        {
            if (decimal->size() == 2 && decimal->getHead()->getData() == '0' && decimal->getTail()->getData() == '0')
            {
                return true;
            }
        }
        return false;
    }

    void roundng()
    {
        if (integer->size() == 0)
        {
            integer->addToHead('0');
        }
        if (decimal->size() == 0)
        {
            decimal->addToTail('0');
        }
        if (decimal->size() == 1)
        {
            decimal->addToTail('0');
        }
        roundTo5nd() ;
        int places = decimal->size() - 2;
        char pre = '0';
        for (int i = 0; i < places; i++)
        {
            if (decimal->getTail()->getData() > '5' || (decimal->getTail()->getData() == '5' && (((decimal->getTail()->getPrev()->getData() - '0') % 2 == 1) || pre != '0')))/****/
            {
                int len = decimal->size();//if 3
                BigDecimal *adder = new BigDecimal("0.10");
                BigDecimal mulplier("0.10");
                for (int j = 0; j < len - 2; j++)//0.1 * 0.1
                {
                    BigDecimal* tmp_adder = adder ;
                    adder = *adder * &mulplier;
                    delete tmp_adder;
                }
                if (sign == '+')
                {
                    BigDecimal* tmp_this_ = *this + adder;
                    *this = *tmp_this_;
                    delete tmp_this_;
                }
                else {
                    BigDecimal* tmp_this = *this - adder;
                    *this = *tmp_this;
                    delete tmp_this;
                }
                delete adder ;
            }
            pre = decimal->deleteFromTail();
        }
    }

    void roundTo15nd()
    {
        int s = decimal -> size() ;
        for( int i = 15 ; i < s ; i++ )
        {
            decimal -> deleteFromTail() ;
        }
    }
    void roundTo5nd()
    {
        int s = decimal -> size() ;
        for( int i = 5 ; i < s ; i++ )
        {
            decimal -> deleteFromTail() ;
        }
    }

    void roundToXXnd()
    {
        int s = decimal->size();
        for (int i = XX; i < s; i++)
        {
            decimal->deleteFromTail();
        }
    }

    friend std::ostream& operator<<(std::ostream& out, BigDecimal* bigDecimal)
    {
        if (bigDecimal == NULL)
        {
            out << "ERROR" << endl;
            return out;
        }
        bigDecimal->eliminateZero();
        bigDecimal -> roundng() ;
        /*******commenting rounding -> WA********/
        if (bigDecimal->getSign() == '-' && !bigDecimal->isZero())
        {
            out << "-";
        }
        for (Node<type>* ptr = bigDecimal->getInteger()->getHead(); ptr != NULL; ptr = ptr->getNext())
        {
            out << ptr->getData();
        }
        out << ".";

        out << bigDecimal -> decimal -> getHead() -> getData() ;
        out << bigDecimal -> decimal -> getHead() -> getNext() -> getData() ;

        /*
        for (Node<type>* ptr = bigDecimal->getDecimal()->getHead(); ptr != NULL; ptr = ptr->getNext())
        {
            out << ptr->getData();
        }*/
        delete bigDecimal ;
        return out;
    }

    void clear()
    {
        if (integer != NULL)
        {
            integer->deleteAllData();
        }
        if (decimal != NULL)
        {
            decimal->deleteAllData();
        }
    }

    /***deletion calls the destructor first, then free the memory, BUT the default destructor does NOT call the destructor of pointer members***/
    ~BigDecimal()
    {
        delete integer;
        delete decimal;
    }

    friend std::istream& operator>>(std::istream& in, BigDecimal* data)
    {
        string s;
        in >> s;
        data->set(s);
        return in;
    }

private:
    char sign;
    LinkedList<type>* integer;
    LinkedList<type>* decimal;
};

template<class T>
class expresstion
{
public:
    expresstion()
    {}
    expresstion( string o )
    {
        op = o ;
        list = new LinkedList<T> ;
    }
    bool isOperator( char c )
    {
        if( c == '^' || c == '*' || c == '/' || c == '+' || c == '-' )
        {
            return true ;
        }
        return false ;
    }

    bool isOperand( char c )
    {
        if( c >= 'A' && c <= 'Z' )
        {
            return true ;
        }
        return false ;
    }

    bool check1()
    {
        int L = 0 , R = 0 ;
        int len = op.size() ;
        for( int i = 0 ; i < len ; i++ )
        {
            if( op[ i ] == '.' && ( i == 0 || ( i - 1 >= 0 && !isdigit( op[ i - 1 ] ) ) || ( i + 1 < len && !isdigit( op[ i + 1 ] ) ) ) )
            {
                return false ;
            }
            if( op[ i ] == '(' )
            {
                if( i - 1 >= 0 && isdigit( op[ i - 1 ] ) )
                {
                    return false ;
                }
                L++ ;
            }
            if( op[ i ] == ')' )
            {
                if( i + 1 < len && isdigit( op[ i + 1 ] ) )
                {
                    return false ;
                }
                R++ ;
            }
            if( !isdigit( op[ i ] ) && !isOperator( op[ i ] ) && op[ i ] != '(' && op[ i ] != ')' && op[ i ] != '.' )
            {
                return false ;
            }
        }
        if( !isdigit( op[ len - 1 ] ) && op[ len - 1 ] != ')' )
        {
            return false ;
        }
        if( R != L )
        {
            return false ;
        }
        return true ;
    }

    bool check2()
    {
        int len = op.size() ;
        for( int i = 0 ; i < len ; i++ )
        {
            if( i + 1 < len && isOperator( op[ i ] ) && isOperator( op[ i + 1 ] ) )
            {
                return false ;
            }
        }
        return true ;
    }

    bool check3()
    {
        int opr = 0 , ort = 0 ;
        for( int i = 0 ; i < postfix.size() ; i++ )
        {
            if( isOperand( postfix[ i ] ) )
            {
                opr++ ;
            }else if( isOperator( postfix[ i ] ) ){
                ort++ ;
            }
        }
        if( ort >= opr )
        {
            return false ;
        }
        return true ;
    }

    bool setNumberSymbols()
    {
        int len = op.size() ;
        for( int i = 0 ; i < len ; i++ )
        {
            if( isdigit( op[ i ] ) )
            {
                int point = 0 ;
                string s = "" ;
                for( int j = i ; j < len && ( isdigit( op[ j ] ) || op[ j ] == '.' )  ; j++ )
                {
                    if( op[ j ] == '.' )
                    {
                        point++ ;
                    }
                    s += op[ j ] ;
                }
                if( point > 1 )
                {
                    return false ;
                }
                BigDecimal tmp( s ) ;
                if( ( i == 1 && op[ 0 ] == '-' ) || ( i - 2 >= 0 && op[ i - 1 ] == '-' && ( isOperator( op[ i - 2 ] ) || op[ i - 2 ] == '(' ) ) )
                {
                    op[ i - 1 ] = ' ' ;
                    tmp.setSign( '-' ) ;
                }
                op[ i ] = 'A' + list -> size() ;
                list -> addToTail( tmp ) ;
                int j = i + 1 ;
                while( isdigit( op[ j ] ) || op[ j ] == '.' )/**********/
                {
                    op[ j ] = ' ' ;
                    j++ ;
                }
            }
        }
        /*
        printf("list::") ;
        display( *list ) ;*/
        return true ;
    }

    int precedence( char c )
    {
        if( c == '^' )
        {
            return 3 ;
        }
        if( c == '*' || c == '/' )
        {
            return 2 ;
        }
        if( c == '+' || c == '-' )
        {
            return 1 ;
        }
        return 0 ;
    }

    void convertInfixToPostfix()
    {
        int len = op.size() ;
        Stack<char> stack;
        for( int i = 0 ; i < len ; i++ )
        {
            if( isOperand( op[ i ] ) )
            {
                postfix += op[ i ] ;
            }else if( op[ i ] == '(' ){
                stack.push( op[ i ] ) ;
            }else if( op[ i ] == ')' ){
                while(  stack.top() != '(' )
                {
                    postfix += stack.pop() ;
                }
                stack.pop() ;
            }else if( isOperator( op[ i ] ) ) {
                if( stack.isEmpty() )
                {
                    stack.push( op[ i ] ) ;
                }else{
                    if( precedence( op[ i ] ) > precedence( stack.top() ) )
                    {
                        stack.push( op[ i ] ) ;
                    }else if( precedence( op[ i ] ) == precedence( stack.top() ) && op[ i ] == '^' ) {
                        stack.push( op[ i ] ) ;
                    }else{
                        while( !stack.isEmpty() && precedence( op[ i ] ) <= precedence( stack.top() ) )
                        {
                            postfix += stack.pop() ;
                        }
                        stack.push( op[ i ] ) ;
                    }
                }
            }
        }
        while( !stack.isEmpty() )
        {
            postfix += stack.pop() ;
        }
    }

    BigDecimal *arithmetic( BigDecimal *a , BigDecimal *b , char _operator )/***!!!!!!!!!!!!!!***/
    {
        //printf("%lf %lf op:%c\n", a , b , _operator ) ;
        BigDecimal *tmp = NULL ;
        switch( _operator )
        {
        case '^':
            tmp = *a ^ b ;
            break ;
        case '*':
            tmp = *a * b ;
            break ;
        case '/':
            tmp = *a / b ;
            break ;
        case '+':
            tmp = *a + b ;
            break ;
        case '-':
            tmp = *a - b ;
            break ;/**remember to add the break statement*/
        }
        if( tmp == NULL )
        {
            return NULL ;
        }
        tmp -> roundng() ;
        return tmp ;
    }

    BigDecimal *doCalculation()
    {
        int len = postfix.size() ;
        Stack<T> stack ;
        for( int i = 0 ; i < len ; i++ )
        {
            if( isOperand( postfix[ i ] ) )
            {
                T *t = list -> getIndexData( ( int )( postfix[ i ] - 'A' ) ) ;
                stack.push( *t ) ;
                delete t ;
            }
            if( isOperator( postfix[ i ] ) )
            {
                BigDecimal tmp1 = stack.pop() ;
                BigDecimal tmp2 = stack.pop() ;
                BigDecimal *tmp = arithmetic( &tmp2 , &tmp1 , postfix[ i ] ) ;/***?The second argument is executed first??***/
                if( tmp == NULL )
                {
                    return NULL ;
                }
                stack.push( *tmp ) ;
                delete tmp ;
            }
            /*
            cout << "(doCalculation)stack:" ;
            stack.display() ;*/
        }
        BigDecimal *res = new BigDecimal ;
        *res = stack.top() ;
        return res ;
    }

    BigDecimal *calculate()
    {
        if( !check1() )
        {
            //cout << "!check1()" << endl ;
            return NULL ;
        }
        if( !setNumberSymbols() )
        {
            return NULL ;
        }
        //cout << op << endl ;
        //cout << list ;
        //printArr( arr , ( int )strlen( arr ) ) ;
        if( list -> size() == 0 )
        {
                return NULL ;
        }
        if( !check2() )
        {
            //cout << "!check2()" << endl ;
            return NULL ;
        }
        //printf("!@#") ;
        convertInfixToPostfix() ;
        if( !check3() )
        {
            //cout << "!check3()" << endl ;
            return NULL ;
        }
        //cout << postfix << endl ;
        //printArr( postfix , ( int )strlen( postfix ) ) ;
        BigDecimal *tmp = doCalculation() ;
        return tmp ;
    }
    ~expresstion()
    {
        delete list ;
    }
private:
    string op , postfix ;
    LinkedList<BigDecimal> *list ;
};

int main()
{
    //cout << fixed << setprecision( 50 ) << 0.14 << endl ;
    string input ;
    while( getline( cin , input ) )
    {
        expresstion<BigDecimal> exp( input ) ;
        BigDecimal *tmp = exp.calculate() ;
        if( tmp == NULL )
        {
            cout << "ERROR\n" ;
        }else{
            cout << tmp << endl ;
        }
    }
    //cout << Node<char>::nodeCount << " " << Node<BigDecimal>::nodeCount << endl ;
}

/*
13.34+567.8
1+2+3
1.1+2.2+3.3
-1.1+2.2
-123.123+-123.123
123+-123
123+123-123
1+2/3
0.5*2.67
0.5*2.57
0^0
1234^0.1
-1234^0.1
1234^-0.1
-1234^-0.1
10000000^10^0.1
23*(-2000000000000000)
23*(--2000000000000000)
30^-0.00000000001
-3*3-32^10
1/23*5
0.0.0
1/23*5+1/5
(369^(-2))^(-3)
100+3/5*(-2^3.4)+23/5
-12^20
(-12)^20
-(12^20)
1-(12^20)
)-12*(1
7.1^7.1
(2^1025)^30
(10/-10)^(2^1024)+1
*/

/*
123^3.14+100/-23
1/0
369-13^3.14
(369-13)^3.14
*/

/*
123+456/789-2^(20+1)*2
1/2^3
0.1+0.035+8*2
(((-8)/3)*0.5)^10
-100--10*10
(9*8/7)^1.1*1000
369.00^3.14

ANS:
-4194180.42
0.12
16.14
18.67
0.00
12990.00
114937776.08
*/

/*
123++++456/789-2^(20+1)*2
0.1+0.035+8*2*
1//2^3
(((-8)/3)*0.5))^10

ANS:
ERROR
ERROR
ERROR
ERROR
*/

/*
123++++456/789-2^(20+1)*2
0.1+0.035+8*2*
1//2^3
(((-8)/3)*0.5))^10
++++++
(^.^)/
/^0^)/)

ANS:
ERROR
ERROR
ERROR
ERROR
ERROR
ERROR
ERROR
*/

/*
18.5455
18.545
*/

/*
123.312+321.31
check1( for '.' and numbers of parentheses and unknown symbols and '(' and ')' )
setNumberSymbols(including negative numbers) and store the numbers in a double list
check2( for continuous operator )
infix to postfix
calculation from left to right ( operand ->push ; operator -> pop*2 then push the result back )
*/

/*
1+2
-1+-5
111.111+123.123
123.1+11.111
-123.1+-11.111
0.1+0.45
1+0.23
30.2334+-234.111
-0.002+0.01
-23.443+-32.344
0.001+0.014
0+1.123
2.5+-12.3
-12.3+2.5
-0.57+-0.125


1-2
2-1
1.23-1.11
1.23-0.55
1.22-1.111
1-0.99
5.5-4.73
0.11111-0.00009
0.05-0.009
-0.0001-0.03
1.002-0.005
0.01-0.002
0.01-0.005
0.01-0.006

1*2
3*4
1.2*0.2
0*3.5
0*-3.5
0.00*0
23.05*-12
-0.05*23.5
-30000*0.0005
-10000*-0.0001
5*34243
34243*5

1/2
1/4
3/4
1/20
100/10
1.5/0.5
324.432/342.43
342.43/324.432
23.324/0.0000000001
-2/5
-10/-0.0005
-0.0034/343
20/-1
20/-0.45
2.00/2.2499999995500000000225
2.00/0.9999999996000000000599999999960000000001
 integer -> getHead() != NULL

2^2
2^-3
2^-4
-3^3
-3^4
-2^-2
-2^-3

0.25^2
0.13^-0.23
-23^0.3
-23^0.32
-3^1
-23^0
1.00
214.4314^32
0^2
0^0
0.0002^-5 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,
*/

/*
10^3
10^4
10^5
0.0002^-5
0.00002^-5
369^3.14
2.00/2.2499999995500000000225
2.00/0.9999999996000000000599999999960000000001
214.4314^32
*/

/*
10^311
2.56*3.45
8400/3
123400/1234
9956/10
6000/200
*/

/*
123+456/789-2^(20+1)*2
1/2^3
0.1+0.035+8*2
(((-8)/3)*0.5)^10 ?????????
-100--10*10
(9*8/7)^1.1*1000 ????????

Ans:
-4194180.42
0.12
16.14
18.67 ???????
0.00
12990.00 ??????????
*/

/*
123++++456/789-2^(20+1)*2
0.1+0.035+8*2*
1//2^3
(((-8)/3)*0.5))^10

Ans:
ERROR
ERROR
ERROR
ERROR
ERROR
*/

/*
.
4..5
---4 ???
++3 ???
-(+5) ???
+(-5) ???
-+5 ???
+-5 ???
+--5 ???
-+6 ???
36.67^(3+(-3))
2^2^3 ->>> 2^( 2 ^3 )
3/3/3/3/3/3
2*-3 ???
(+5) XXXXX
(-5) OOOOO
-0 OOO
+0??OOOOO
1/0
1/( 3 - 3 )
.324
234.
()
Ans:
ERROR
ERROR
ERROR

-5.00
-5.00
-6.00
-6.00
1.00
*/

/*
set the numbers and then deal with the minus signs( negative numbers)

-+5
+-5
--5
+5
-5 = -5
2--3 ->> 1 ?
3 * -2 = -6 ?


3*-2*-2
3*(-2)*(-2)

4(+5)
3.-3
*/

/*
-+50
+-50
--50
+50
-50
20--30
30*-20
30*-20*-20
30*(-20)*(-20)
40(+50)
30.-30
.
40..50
---40
++30
-(+5)
+(-50)
-+50
+-50
+--50
-+60
36.67^(30+(-30))
10^2^3
30/30/30/30/30/30
20*-30
(+500)
(-500)
-0
+0
-123
+123
12/0
120/( 30 - 30 )
.324
234.
()

*/

/*
(-50)*(-30)/20+50 - 2^3
1+1000/1000*1000*2
2^(3)6
*/

/***4.
123456 / 654321
4.51225 * 20
7.1 ^ 7.1
25.00 ^ 0.15
369.00 ^ 3.14
369.00 * 3.1401
369.00 * -5.13
-12.321 * -32.123
-987654.3210 / -1234.4321

ANS:
0.19
90.24
1106456.33
1.62
114937776.08
1158.70
-1892.97
395.79
800.09
*/

/*
constructor:
  add at least two decimal
printing method:
  meet the first non-zero number and start printing, print a point, print two dec

added functions:
copy constructor
eliminateZero()
operator overloading '>' '<' "=="
add private member char sign for '+' or '-'
setSign( char c )
roundTo2ndDecimal() ;
compareInt()
compareDec()
shiftPoint()
shiftInt()
ln( x )

for addition:
    if +, + -> go on
    if +, - -> subtraction of the first number by the second number with positive sign
    if -, + -> subtraction of the second number by the first number with positive sign
    if -, - ->  add the pure number part then set the res to -
  method!!!
                                                                   if needed, just add the carry to Head
  (1) add '0's for int and dec, remember to reserve one more space for the possible carry in integer part
        compare the lengths of the integer part and the decimal part
  ( 2 ) add integer part and decimal part respectively
        if there's a carry for decimal part, add the integer part by one
  ( 3 )add one by one ***from right*** and remember to record the carry
for subtraction:
    if +, + -> go on
    if +, - -> addition of the first number by the second number with positive sign
    if -, + -> addition of the first number by the first number by the second number with negative sign
    if -, - -> subtraction of the second number with positive sign by the first number with positive sign
  method!!!
  (1) compare the two numbers,
            if a > b, set the res to '+'; else, set to '-'
                if a.dec > b.dec -> go on
                if a.dec < b.dec -> after operation, set the decimal part++ and sub int part by 1
            if a < b, sub b by a then get the result then set the res to '-';
  ( 2 ) add the '0's
  ( 3 ) sub ***from left*** and if the digit is smaller to subtract, borrow 1 from the left side positon
for multiplication:
    set res to "0"
    method!!!
  ( 1 )record the point position of a eg,123.456 -> shift = 3 ; eg, 12.00 -> shift = 2 ( to left )
  ( 2 )shift a to left until there's no decimal
  ( 3 )get the most left digit of b( record the point position eg, 123,23 * 12.564, if 123.23 * 0.06 -> i = 1 )
        and multiply it by a from left to right one by one and shift it to the right position then sum them up
        RULE of SHIFTING:
        eg, 123.456 * 85.34 shift = 3
              ***for decimal part:
                  Node<type> *ptr = b.getDecimal() -> getHead() ;
                  for( i = 0 ; i < b.getDecimal() -> size() ; i++ )
                      i = 0, 123456 * 3 -> then shift it to left by 3 + ( i + 1 ) ( = 0 + 1 )
                      i = 1, 123456 * 4 -> then shift it to left by 3 + ( i + 1 ) ( = 1 + 1 )
                      ptr = ptr -> getNext() ;
                      res = res + tmp
              ***for integer part:
                  Node<type> *ptr = b.getInteger() -> getTail() ;
                  for( i = 0 ;  i < b.getInteger() -> size() ; i++ )
                      i = 0, 123456 * 5 -> then shift it to left by 3 and shift it to right by i = 0
                      i  = 1, 123456 * 8 -> then shift it to left by 3 and shift it to right by i = 1
                      ptr = ptr -> getNext() ;
                      res = res + tmp
        if + + or - -
        set res to '+'
        if + - or - +
        set res to '-'
  ( 4 )

for division:
    if b == 0, ERROR
    method!!!
  ( 1 )record a_shift, b_shift. eg, 123.456 -> 3 ; 34.30 -> 2
        shift a and b to left + 3
        record a_int_len and b_int_len
        int times = a_int_len - b_int_len + 1 ;//times for comparison
        Big_q ;
  ( 2 )for( int i = 0 ; i < times ; i++ )
            if( smaller( a , b_int_len + i ) )
                int q_tmp = 0 ;
                Big_tmp("1") , Big_max("0") , Big_add("1") , Big_a_tmp( a , b_int_len + i ) ;
                for( int j = 0 ; j < 9 ; j++ )//see what the possible quotient is
                    tmp2 = tmp * b
                    if( tmp2 > a_tmp )
                        q_tmp = j ;
                        break ;
                    if( tmp2 > max )
                        max = tmp2 ;
                    tmp = tmp + add ;
                max.shiftToLeft( a.int.size - max.int.size ) ;
                a = a - max ;
                if( a == 0 )
                {
                    q -> shiftToLeft( times - i - 1 ) ;
                    break ;
                }
                while( a.getIntger() -> size() < a_int_len )
                {
                    a.getInteger() -> addToHead('0') ;
                }
                q -> getInteger() -> addToTail( q_tmp + '0' ) ;
      q -> shiftToRight( a_shift + 3 ) ;
      q -> shiftToLeft( b_shift ) ;
for powers:
    a^b = e ^ ( b * ln(a) )
    eg, a ^ ( 3.14 ) ->> a ^( 314 / 100 ) ->> root( a ^ 314 , 100 )
*/

/*
1 + 2
2 ^ 3
1 / 8
123.4567 * 3
0 - 100
-10 + 1
369.00 ^ 3.14

ANS:
3.00
8.00
0.12
370.37
-100.00
-9.00
114937776.08
*/

/*
1 + 2
-1 + -5
111.111 + 123.123
123.1 + 11.111
-123.1 + -11.111
0.1 + 0.45
1 + 0.23
30.2334 + -234.111
-0.002 + 0.01
-23.443 + -32.344
0.001 + 0.014
0 + 1.123
2.5 + -12.3
-12.3 + 2.5
-0.57 + -0.125


1 - 2
2 - 1
1.23 - 1.11
1.23 -  0.55
1.22 - 1.111
1 - 0.99
5.5 - 4.73
0.11111 - 0.00009
0.05 - 0.009
-0.0001 - 0.03
1.002 - 0.005
0.01 - 0.002
0.01 - 0.005
0.01 - 0.006

1 * 2
3 * 4
1.2 * 0.2
0 * 3.5
0 * -3.5
0.00 * 0
23.05 * -12
-0.05 * 23.5
-30000 * 0.0005
-10000 * -0.0001
5 * 34243
34243 * 5

1 / 2
1 / 4
3 / 4
1 / 20
100 / 10
1.5 / 0.5
324.432 / 342.43
342.43 / 324.432
23.324 / 0.0000000001
-2 / 5
-10 /  -0.0005
-0.0034 / 343
20 / -1
20 / -0.45
2.00 / 2.2499999995500000000225
2.00 / 0.9999999996000000000599999999960000000001
 integer -> getHead() != NULL

2 ^ 2
2 ^ -3
2 ^ -4
-3 ^ 3
-3 ^ 4
-2 ^ -2
-2 ^ -3

0.25 ^ 2
0.13 ^ -0.23
-23 ^ 0.3
-23 ^ 0.32
-3 ^ 1
-23 ^ 0
214.4314 ^ 32
0 ^ 2
0 ^ 0
0.0002 ^ -5 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,
*/

/*
10 ^ 3
10 ^ 4
10 ^ 5
0.0002 ^ -5
0.00002 ^ -5
369 ^ 3.14
2.00 / 2.2499999995500000000225
2.00 / 0.9999999996000000000599999999960000000001
214.4314 ^ 32
*/

/*
10 ^ 311
2.56 * 3.45
8400 / 3
123400 / 1234
9956 / 10
6000 / 200
*/

/*#########1
1 + 2
2 ^ 3
1 / 8
123.4567 * 3
0 - 100
-10 + 1

ANS:
3.00
8.00
0.12
370.37
-100.00
-9.00
*/

/*########2
10 ^ 311
-10 ^ 311
-10 ^ 310
*/

/*########4
123456 / 654321
4.51225 * 20
7.1 ^ 7.1
25.00 ^ 0.15
369.00 ^ 3.14
369.00 * 3.1401
369.00 * -5.13
-12.321 * -32.123
-987654.3210 / -1234.4321

ANS:
0.19
90.24
1106456.33
1.62
114937776.08
1158.70
-1892.97
395.79
800.09
*/
