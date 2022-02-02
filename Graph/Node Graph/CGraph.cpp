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
    typedef CEdge<G> Edge;
    typedef CNode<G> Node;

    vector<Node*> nodes;

    //primary functions    
    bool InsNode(N value);
    bool RemNode(N value);
    //Overloading InsEdge
    bool InsEdge(E value, Node* start, Node* end, bool dir);
    bool InsEdge(E value, N start_value, N end_value, bool dir);
    //Overloading RemEdge
    bool RemEdge(E value, Node* start, Node* end);
    bool RemEdge(E value, N start_value, N end_value);
    
    //Secondary functions
    void printGraph(); //Missing

    //Auxiliar functions
    bool FindNode(N value, Node* &p);
    bool FindEdge(E value, Node* p, Edge* &e);
};

template<class _N, class _E>
bool CGraph<_N, _E>::FindNode(N value, Node* &p){
    for(auto it = nodes.begin(); it != nodes.end(); ++it){
        if((*it)->m_v == value){
            p = *it;
            return 1;
        }
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::FindEdge(E value, Node* p, Edge* &e){
    for(auto it = p->edges.begin(); it != p->edges.end(); ++it){
        if((*it)->m_v == value){
            e = *it;
            return 1;
        }
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsNode(N value){
    Node* p = nullptr;
    if(FindNode(value, p)) return 0;
    Node* m = new Node(value);
    nodes.push_back(m);
    return 1;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(E value, Node* start, Node* end, bool dir){ //Error
    Node* a = nullptr, *b = nullptr;
    if(FindNode(start->m_v, a)&& FindNode(end->m_v, b)){
        Edge* temp = new Edge(value, a, b, dir);
        a->edges.push_back(temp);
        b->edges.push_back(temp);
        return 1;
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(E value, N start_value, N end_value, bool dir){
    Node* a = new Node(start_value);
    Node* b = new Node(end_value);
    return InsEdge(value, a, b, dir);
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemEdge(E value, Node* start, Node* end){
    Node* a = nullptr, *b = nullptr;
    if(FindNode(start->m_v, a) && FindNode(end->m_v, b)){
        Edge* e = nullptr;
        if(FindEdge(value, start, e)) start->edges.remove(e);
        else return 0;
        e = nullptr;
        if(FindEdge(value, end, e)) end->edges.remove(e);
        else return 0;
        delete e;
        return 1;
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemEdge(E value, N start_value, N end_value){
    Node* a = new Node(start_value);
    Node* b = new Node(end_value);
    return RemEdge(value, a, b);
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemNode(N value){
    Node* p = nullptr;
    if(!FindNode(value, p)) return 0;
    while (!p->edges.empty()){
        E v = p->edges.front()->m_v;
        RemEdge(v, p,p->edges.front()->m_nodes[1]);
    }

    for (auto it = nodes.begin(); it != nodes.end(); ++it){ if (*it == p) nodes.erase(it);}
    delete p;
    return 1;
}

template<class _N, class _E>
void CGraph<_N, _E>::printGraph(){
    for(int i = 0; i < nodes.size(); i++){
        cout<< nodes[i]->m_v<<": ";
        for(auto it = nodes[i]->edges.begin(); it != nodes[i]->edges.end(); ++it){
            bool temp = (*it)->m_dir;
            if(((*it)->m_nodes[1] != nodes[i]) || !temp){
                if(temp) cout << "->";
                else cout << "<->";
                cout << (*it)->m_nodes[1]->m_v;
                cout << (*it)->m_v << " | ";
            }
        }
        cout<<"\n";
    }

}


int main(){

    CGraph<char, int> myGraph;    
    std::string names = "ABCD"; 
    
    for(int i = 0; i < 4; i++) myGraph.InsNode(names[i]);

    myGraph.InsEdge(2, 'A','B',true);
    myGraph.InsEdge(1, 'A','C',true);
    myGraph.InsEdge(3, 'B','C',true);
    myGraph.InsEdge(4, 'B','D',true);
    myGraph.InsEdge(5, 'C','D',true);

    cout << "Printing \n";
    myGraph.printGraph();
}