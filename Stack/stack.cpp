#include <iostream>

using namespace std;

template<class T>
struct CNode{
    T m_v;
    CNode<T>* m_prev;
    CNode(T _v, CNode<T>* n = nullptr);
};
template<class T>
CNode<T>::CNode(T _v, CNode<T>* n = nullptr){
    m_v = _v;
    m_prev = n;
}

template<class T>
struct CStack{
    CNode<T>* m_top;
    CStack();
    
};

template<class T>
CStack<T>::CStack(){
    m_top = nullptr;
}



int main(){

}