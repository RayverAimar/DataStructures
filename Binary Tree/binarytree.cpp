#include <iostream>

using namespace std;


//CNode Implementation

template<class T>
struct CNode{
    T m_v;
    int level;
    CNode<T>* m_children[2];
    CNode(T _v, int _level);
    CNode(T _v);
};

template<class T>
CNode<T>::CNode(T _v, int _level): m_v(_v), level(_level){
    m_children[0] = m_children[1] = nullptr;
}

template<class T>
CNode<T>::CNode(T _v): m_v(_v){
    m_children[0] = m_children[1] = nullptr;
}

//CBinTree Implementation

template<class T>
struct CBinTree{
    int height, tab;
    CBinTree(){};  
    ~CBinTree(){};
    bool find(T x, CNode<T>** &p);
    bool findN(T x, CNode<T>** &p, int &n);
    void redN(CNode<T>*p);
    bool insert(T x);
    bool remove(T x);
    CNode<T>** rep(CNode<T>** p);
    void printN(CNode<T>* p, int n, int& esp, int &temp);
    int update(CNode<T>* p);
    void updt_altura();
    void podar(CNode<T>* p, int n);
    void levels(CNode<T>* p);
};

int main(){

}