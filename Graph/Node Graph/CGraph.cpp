#include <iostream>
#include <vector>
#include <list>

using namespace std;


template<class G>
struct CEdge{
    typedef typename G::Node Node;
    typedef typename G::E E;
    E m_v;
    Node* m_nodes[2];
    bool m_dir; //0 node[0] <-> node[1] / 1 node[0] -> node[1]

    //Constructor
    CEdge(E e,Node* a, Node* b, bool dir){
        m_v = e;
        m_nodes[0] = a;
        m_nodes[1] = b;
        m_dir = dir;
    }
};

template<class G>
struct CNode{
    typedef typename G::Edge Edge;
    typedef typename G::N N;

    N m_v;
    list<Edge*> edges;
    //Constructor
    CNode(N v) : m_v(v) {}
};

template<class _N, class _E>
struct CGraph{
    //types
    typedef _N N; 
    typedef _E E;
    typedef CGraph<_N,_E> G;
    typedef CEdge<G> Node;
    typedef CNode<G> Edge;

    vector<Node*> nodes;

    //primary functions    
    bool InsNode(N value);
    bool InsEdge(E value, Node* start, Node* end, bool dir);
    bool RemEdge(Node* start, Node* end, E value);
    bool RemNode(N value);

    //Secondary functions
    void printGraph();

    //Auxiliar functions
    bool FindNode(N value, Node* &p);
};

template<class _N, class _E>
bool CGraph<_N, _E>::FindNode(N value, Node* &p){
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsNode(N value){
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(E value, Node* start, Node* end, bool dir){
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemEdge(Node* start, Node* end, E value){
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemNode(N value){
    return 0;
}

template<class _N, class _E>
void CGraph<_N, _E>::printGraph(){

}


int main(){

}