#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


//CNode Implementation

template<class T>
struct CNode{
    T m_v;
    int level;
    CNode<T>* m_children[2];

    //Constructors
    CNode(T _v, int _level);
    CNode(T _v);
};

template<class T>
CNode<T>::CNode(T _v, int _level): m_v(_v), level(_level){
    m_children[0] = m_children[1] = 0;
}

template<class T>
CNode<T>::CNode(T _v): m_v(_v){
    m_children[0] = m_children[1] = 0;
}

//CBinTree Implementation

template<class T>
struct CBinTree{

    //Constructors & Destructors
    CBinTree();
    ~CBinTree();

    //primary functions
    bool find(T x, CNode<T>** &p);
    bool insert(T x);
    bool remove(T x);

    //Secondary functions
    bool findN(T x, CNode<T>** &p, int &n);
    void redN(CNode<T>*p);
    void printN(CNode<T>* p, int n, int& esp, int &temp);
    int update(CNode<T>* p);
    void updt_altura();
    void podar(CNode<T>* p, int n);
    void levels(CNode<T>* p);

    //Traversal
    void pre_order(CNode<T>* n);
    void in_order(CNode<T>* n);
    void post_order(CNode<T>* n);

    //Getters
    CNode<T>* get_root();
    CNode<T>** get_nearest_CNode(CNode<T>** p);

private:
   int height, tab;
   CNode<T>* m_root;
};

template<class T>
CBinTree<T>::CBinTree(): m_root(nullptr) {}

template<class T>
CBinTree<T>::~CBinTree(){}

template<class T>
CNode<T>* CBinTree<T>::get_root(){ return m_root; }

template<class T>
bool CBinTree<T>::find(T x, CNode<T>** &p){
    for(p = &m_root; *p && (*p)->m_v != x; p = &((*p)->m_children[(*p)->m_v < x]));
    return *p;
}

template<class T>
bool CBinTree<T>::insert(T x){
    CNode<T>** p;
    if(find(x, p)) return 0;
    *p = new CNode<T>(x);
    return 1;
}

template<class T>
CNode<T>** CBinTree<T>::get_nearest_CNode(CNode<T>** p){
    srand(unsigned(time(0)));
    int i = rand() % 2;
    for (p = &((*p)->m_children[!i]) ; (*p)->m_children[i]; p = &(*p)->m_children[i]);
    return p;
}

template<class T>
bool CBinTree<T>::remove(T x){
    CNode<T>** p;
    if(!find(x,p)) return 0;
    if((*p)->m_children[0] && (*p)->m_children[1]){
        CNode<T>** q = get_nearest_CNode(&m_root);
        (*p)->m_v = (*q)->m_v;
        p = q;
    }
    CNode<T>* temp = *p;
    *p = (*p)->m_children[ (*p)->m_children[1] != 0 ];
    delete temp;
    return 1;

}

template<class T>
void CBinTree<T>::pre_order(CNode<T>* n){
    if(!n) return;
    cout << n->m_v<<" ";
    pre_order(n->m_children[0]);
    pre_order(n->m_children[1]);
}

template<class T>
void CBinTree<T>::in_order(CNode<T>* n){
    if(!n) return;
    in_order(n->m_children[0]);
    cout << n->m_v<<" ";
    in_order(n->m_children[1]);
}

template<class T>
void CBinTree<T>::post_order(CNode<T>* n){
    if(!n) return;
    post_order(n->m_children[0]);
    post_order(n->m_children[1]);
    cout << n->m_v<<" ";
}


int main(){
    CBinTree<int> myTree;
    myTree.insert(13);
    myTree.insert(27);
    myTree.insert(23);
    myTree.insert(6);
    myTree.insert(1);
    myTree.insert(8);
    myTree.in_order(myTree.get_root());
    cout<<endl;
    myTree.pre_order(myTree.get_root());

}