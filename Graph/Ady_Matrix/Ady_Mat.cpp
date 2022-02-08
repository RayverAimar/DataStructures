#include <iostream>
#include <map>
#include <iomanip>

using namespace std;

#define FORN(i,m,n) for(int i = m; i < (int)n; ++i ) 
#define INF 1e9

int N = 0, **graph;
char *names;
map<char, int> vertexes;

void init_graph(){
    cout<<"Numero de vertices: ";
    cin>>N;
    graph = new int*[N];
    names = new char[N];
    FORN(i,0,N) graph[i] = new int[N];
    FORN(i,0,N) FORN(j,0,N) graph[i][j] = 0;
    cout<<"Etiqueta de los "<<N<<" vertices: ";
    cin>>names;
    FORN(i,0,N) vertexes[names[i]] = i;
}

void InsEdge(int start, int end, int value){
    graph[start][end] = value;// graph[end][start] = value;
}

void printGraph(){
    cout<<"  ";
    FORN(i,0,N) cout<<setw(2)<<names[i]<<" ";
    cout<<"\n";
    FORN(i,0,N){
        cout<<names[i]<<" ";
        FORN(j,0,N) cout<<setw(2)<<graph[i][j]<<" ";
        cout<<"\n";
    }
}

int main(){
    init_graph();
    FORN(i,0,N) FORN(j,0,N) InsEdge(i,j,i-j);
    printGraph();
}