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
    int dfs[2];
    //Constructor
    CNode(N v) : m_v(v) {
        dfs[0] = dfs[1] = -1;
    }
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
    void DFS(N node_value);
    void BFS(N node_value);

    //Auxiliar functions
    void dfs_visit(Node* n, int& n_visit);

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

void CGraphCharNum::dfs_visit(Node* p, int& n_visit){
    p->component = 1;
    p->dfs[0] = n_visit++;
    for(auto it = p->edges.begin(); it != p->edges.end(); ++it){ //Looking for next node
        if((*it)->m_nodes[1] && !(*it)->m_nodes[1]->component){   
            dfs_visit((*it)->m_nodes[1], n_visit);
        }
    }
    p->dfs[1] = n_visit++;
}

void CGraphCharNum::DFS(N node_value){
    Node* p = nullptr;
    if(!FindNode(node_value, p)) return;
    for(int i = 0; i < nodes.size(); i++) nodes[i]->component = 0;
    int n_visit{1};
    dfs_visit(p, n_visit);
    for(int i = 0; i < nodes.size(); i++)
        cout<<nodes[i]->m_v<<" -> "<<nodes[i]->dfs[0]<<"/"<<nodes[i]->dfs[1]<<"\n";
}

void CGraphCharNum::BFS(N node_value){
    for(int i = 0; i < nodes.size(); i++) nodes[i]->component = -1;
    Node* p = nullptr;
    if(!FindNode(node_value, p)) return;
    p->component = 0;
    queue<Node*> Q;
    Q.push(p);
    while(!Q.empty()){
        Node* cur = Q.front();
        Q.pop();
        cout<< cur->m_v <<"-"<<cur->component<<"\n";
        for(auto it = cur->edges.begin(); it != cur->edges.end(); ++it){
            if((*it)->m_nodes[1]->component < 0 ){
                Q.push((*it)->m_nodes[1]);
                (*it)->m_nodes[1]->component = cur->component + 1;
            }
        }
    }
}


int main(){

    CGraphCharNum myGraph;

    std::string names = "stuvwxyz"; 
    
    for(int i = 0; i < names.size(); i++) myGraph.InsNode(names[i]);

    myGraph.InsEdge(1, 's', 'z', 0);
    myGraph.InsEdge(1, 's', 'w', 0);
    myGraph.InsEdge(1, 't', 'u', 1);
    myGraph.InsEdge(1, 't', 'v', 0);
    myGraph.InsEdge(1, 'u', 'v', 0);
    myGraph.InsEdge(1, 'v', 's', 0);
    myGraph.InsEdge(1, 'v', 'w', 0);
    myGraph.InsEdge(1, 'w', 'x', 0);
    myGraph.InsEdge(1, 'x', 'z', 0);
    myGraph.InsEdge(1, 'z', 'y', 0);
    myGraph.InsEdge(1, 'z', 'w', 0);
    myGraph.InsEdge(1, 'y', 'x', 0);

    myGraph.printGraph();

    cout<<"\n";
    myGraph.DFS('s');

}