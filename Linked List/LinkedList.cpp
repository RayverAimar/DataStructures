#include <iostream>

using namespace std;

template<class T>
struct CNode{
    T m_v;
    CNode* next;
    CNode(T _v, CNode<T>* n = NULL){
        m_v = _v;
        next = n;
    }
};
template<class T>
struct CLinkedList{
    CNode<T>* m_head;
    CLinkedList(){
        m_head = nullptr;
    }
    bool find(T value, CNode<T>*& pos);
    void insert(T value);
    void erase(T value);
    void print();
    string get_Linked_List();
};

template<class T>
bool CLinkedList<T>::find(T value, CNode<T>*& pos){
    bool found = false;
    pos = nullptr;
    for(CNode<T>* p = m_head; p && p->m_v <= value; p = p->next)
    {
        if(p->m_v == value)
        {
            found = true;
            break;
        }
        pos = p;
    }
    return found;
}

template<class T>
void CLinkedList<T>::insert(T value){
    CNode<T>* p;
    if(!find(value, p)){
        if(!p) //No existe ningun elemento
            m_head = new CNode<T>(value, m_head);
        else p->next = new CNode<T> (value, p->next);
    }
}
template<class T>
void CLinkedList<T>::erase(T value){
    CNode<T>*pos_ant, *pos_del;
    if(find(value, pos_ant)){
        if(pos_ant){
            pos_del = pos_ant->next;
            pos_ant->next = pos_del->next;
            delete pos_del;
        }
        else{
            pos_del = m_head;
            m_head = pos_del->next;
            delete pos_del;
        }
    }
}

template<class T>
void CLinkedList<T>::print(){
    cout<<endl<<"HEAD->";
    for(CNode<T>* p = m_head; p; p = p->next){
        cout<<p->m_v<<"->";
    }
    cout<<"NULL"<<endl;
}

template<class T>
string CLinkedList<T>::get_Linked_List(){
    string _result = "";
    _result+="HEAD->";
    for(CNode<T>* p = m_head; p; p = p->next){
        _result = _result + to_string(p->m_v) + "->";
    }
    _result+="NULL";
    return _result;
}

int main(){
    string obtained_result;
    CLinkedList<int> myLinkedList;
    myLinkedList.insert(6);
    myLinkedList.insert(3);
    myLinkedList.insert(9);
    myLinkedList.insert(12);
    myLinkedList.insert(4);
    obtained_result = myLinkedList.get_Linked_List();
    
    cout<<obtained_result;
}