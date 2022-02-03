#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <queue>

using namespace std;

#define INF 1e9

template<class G>
struct CEdge{
    typedef typename G::Node Node;
    typedef typename G::E E;
    E m_v;
    Node* m_nodes[2];
    bool m_bidir; //0 node[0] -> node[1] / 1 node[0] <-> node[1]

    //Constructor
    CEdge(E e,Node* a, Node* b, bool dir){
        m_v = e;
        m_nodes[0] = a;
        m_nodes[1] = b;
        m_bidir = dir;
    }
};

template<class G>
struct CNode{
    typedef typename G::Edge Edge;
    typedef typename G::N N;

    N m_v;
    list<Edge*> edges;
    int component;
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
    bool InsEdge(E value, Node* start, Node* end, bool bidir);
    bool InsEdge(E value, N start_value, N end_value, bool bidir);
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
bool CGraph<_N, _E>::InsEdge(E value, Node* start, Node* end, bool bidir){
    Node* a = nullptr, *b = nullptr;
    if(FindNode(start->m_v, a)&& FindNode(end->m_v, b)){
        Edge* temp = new Edge(value, a, b, bidir);
        a->edges.push_back(temp);
        if(bidir){
            Edge* temp1 = new Edge(value, b, a, bidir);
            b->edges.push_back(temp1);
        }
        return 1;
    }
    return 0;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(E value, N start_value, N end_value, bool bidir){
    Node* a = new Node(start_value);
    Node* b = new Node(end_value);
    return InsEdge(value, a, b, bidir);
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
            if((*it)->m_bidir) cout<<"<-> ";
            else cout<<"-> ";
            cout <<(*it)->m_nodes[1]->m_v<< left <<setw(2)<< (*it)->m_v << " | ";
        }
        cout<<"\n";
    }
}

struct CGraphCharNum : public CGraph<char,int>
{
    //Shortest path algorithm
    void Dijkstra(N start, N end);

    //Minimum Spanning Tree Algorithms
    void Prim(N node_value);
    void Kruskal();

    //Searchs
    void DFS();
    void BFS();

};

void CGraphCharNum::Dijkstra(N start, N end){

}

void CGraphCharNum::Prim(N value){
    Node* p = nullptr;
    if(!FindNode(value, p)) return;
    for(int i = 0; i < nodes.size(); i++) nodes[i]->component = 0;
    vector<Node*> visited_nodes;
    vector<Edge*> prim_path;
    p->component = 1;
    visited_nodes.push_back(p);
    while(visited_nodes.size() != nodes.size()){
        Edge* temp = nullptr;
        int min = INF;
        //Find the minimum value Edge between all nodes already visited
        for(int i = 0; i < visited_nodes.size(); i++){
            for(auto it = visited_nodes[i]->edges.begin(); it != visited_nodes[i]->edges.end(); ++it){
                if(min > (*it)->m_v && (*it)->m_nodes[1]->component == 0){
                min = (*it)->m_v;
                temp = *it;
                }
            }
        }
        temp->m_nodes[1]->component = 1;
        visited_nodes.push_back(temp->m_nodes[1]);
        prim_path.push_back(temp);
    }
    for(int i = 0; i < prim_path.size(); i++){
        cout << prim_path[i]->m_nodes[0]->m_v<<"-"<<prim_path[i]->m_v<<"-"<<prim_path[i]->m_nodes[1]->m_v<<"\n";
    }
}

void CGraphCharNum::Kruskal(){
    for(int i = 0; i < nodes.size(); i++) nodes[i]->component = i;
    vector<Edge*> kruskal_path;
    while(kruskal_path.size() < nodes.size() - 1){ 
        Edge* temp = nullptr;
        int min = INF;
        for(int i = 0; i < nodes.size(); i++){ //Find minimum value Edge
            for(auto it = nodes[i]->edges.begin(); it != nodes[i]->edges.end(); ++it){
                if(min > (*it)->m_v && (*it)->m_nodes[0]->component != (*it)->m_nodes[1]->component){
                    min = (*it)->m_v;
                    temp = *it;
                }
            }
        }
        kruskal_path.push_back(temp);
        int t = temp->m_nodes[1]->component;
        for(int i = 0; i < nodes.size(); i++){ //Node[0] conquers Node[1] components
            if(nodes[i]->component == t) nodes[i]->component = temp->m_nodes[0]->component;
        }
    }
    for(int i = 0; i < kruskal_path.size(); i++){
        cout << kruskal_path[i]->m_nodes[0]->m_v<<"-"<<kruskal_path[i]->m_v<<"-"<<kruskal_path[i]->m_nodes[1]->m_v<<"\n";
    }
}

void CGraphCharNum::DFS(){
    
}

void CGraphCharNum::BFS(){
    
}


int main(){

    CGraphCharNum myGraph;
    std::string names = "abcdefghi"; 
    
    for(int i = 0; i < 9; i++) myGraph.InsNode(names[i]);

    myGraph.InsEdge(4, 'a', 'b', 1);
    myGraph.InsEdge(8, 'a', 'h', 1);
    myGraph.InsEdge(8, 'b', 'c', 1);
    myGraph.InsEdge(11, 'b', 'h', 1);
    myGraph.InsEdge(7, 'c', 'd', 1);
    myGraph.InsEdge(4, 'c', 'f', 1);
    myGraph.InsEdge(2, 'c', 'i', 1);
    myGraph.InsEdge(9, 'd', 'e', 1);
    myGraph.InsEdge(14, 'd', 'f', 1);
    myGraph.InsEdge(10, 'e', 'f', 1);
    myGraph.InsEdge(2, 'f', 'g', 1);
    myGraph.InsEdge(6, 'g', 'i', 1);
    myGraph.InsEdge(1, 'g', 'h', 1);
    myGraph.InsEdge(7, 'h', 'i', 1);
    
    myGraph.printGraph();

    cout<<endl;
    myGraph.Prim('a');
}