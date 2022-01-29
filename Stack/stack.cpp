#include <iostream>

using namespace std;

template<class T>
struct CNode{
    T m_v;
    CNode<T>* m_prev;
    CNode(T _v, CNode<T>* n = nullptr);
};

template<class T>
CNode<T>::CNode(T _v, CNode<T>* n): m_v(_v), m_prev(n) {}

template<class T>
struct CStack{

    CStack();

    T top();
    void push(T x);
    void pop();
    void print();   
    int size();
    bool empty();

private:
    CNode<T>* m_top;
    int _size;
};

template<class T>
CStack<T>::CStack(): m_top{nullptr}, _size{0} {}

template<class T>
T CStack<T>::top(){
    return m_top->m_v;
}

template<class T>
void CStack<T>::push(T x){
    CNode<T>* n_top = new CNode<T>(x, m_top);
    m_top = n_top;
    ++_size;
}

template<class T>
void CStack<T>::pop(){
    CNode<T>* to_delete{m_top};
    m_top = m_top->m_prev;
    delete to_delete;
    --_size;
}

template<class T>
void CStack<T>::print(){
    cout<<"TOP->";
    for(CNode<T>* p = m_top; p; p = p->m_prev){
        cout<<p ->m_v<<"->";
    }
    cout<<"BOTTOM";
}

template<class T>
int CStack<T>::size(){
    return _size;
}

template<class T>
bool CStack<T>::empty(){
    return (!m_top) ? true : false;
}

int main(){
    CStack<int> myStack;
    myStack.push(6);
    myStack.push(7);
    myStack.push(8);
    myStack.push(3);
    myStack.pop();
    cout<<"Top of the Stack: "<<myStack.top();
    cout<<endl;
    cout<<"Printing Stack: ";
    myStack.print();
    cout<<endl<<"Stack size: "<<myStack.size();
}