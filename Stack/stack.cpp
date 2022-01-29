#include <iostream>

using namespace std;

template<class T>
struct CNode{
    T m_v;
    CNode<T>* m_prev;
    CNode(T _v, CNode<T>* n = nullptr);
};

template<class T>
CNode<T>::CNode(T _v, CNode<T>* n){
    m_v = _v;
    m_prev = n;
}

template<class T>
struct CStack{
    CNode<T>* m_top;
    CStack();


    
    T top();
    void push();
    void pop();
    void print();
    
    int size();
    bool empty();

};

template<class T>
CStack<T>::CStack(){
    m_top = nullptr;
}

template<class T>
T CStack<T>::top(){
    return m_top->m_v;
}

template<class T>
void CStack<T>::push(){
    
}

template<class T>
void CStack<T>::pop(){

}

template<class T>
void CStack<T>::print(){
    
}

template<class T>
int CStack<T>::size(){
    return 0;
}

template<class T>
bool CStack<T>::empty(){
    return (!m_top) ? true : false;
}

int main(){
    
}