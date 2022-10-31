#include "./Node.h"

struct LinkedList
{
    LinkedList();

    bool find(int, Node*& );
    void insert(int, char, Node* = nullptr, Node* = nullptr);
    void erase(int);
    void print();
    void makeTree();
    Node* unbindHead();

    Node* head;

};

LinkedList::LinkedList() : head(nullptr)
{

}

bool LinkedList::find(int value, Node*& p)
{
    p = nullptr;
    for(Node* it = head; it && it->frequency <= value; it = it->next)
    {
        if(it->frequency == value)
        {
            return true;
        }
        p = it;
    }
    return false;
}

void LinkedList::insert(int _frequency, char _name, Node* left, Node* right)
{
    Node* p;
    find(_frequency, p);
    if(!p){
        head = new Node(_frequency, _name, head);
        p = head;
    }
    else 
    {
        p->next = new Node(_frequency, _name, p->next);
        p = p->next;
    }
    if (left) p->children[0] = left;
    if (right) p->children[1] = right;
}

void LinkedList::erase(int value)
{
    Node*pos_ant, *pos_del;
    if(find(value, pos_ant)){
        if(pos_ant){
            pos_del = pos_ant->next;
            pos_ant->next = pos_del->next;
            delete pos_del;
        }
        else{
            pos_del = head;
            head = pos_del->next;
            delete pos_del;
        }
    }
}

void LinkedList::makeTree()
{
    while(head->next->next)
    {
        print();
        int suma = head->frequency + head->next->frequency;
        Node* left = head, *right = head->next;
        Node* temp = head->next->next;
        head->next = head->next->next = nullptr;
        head = temp;
        insert(suma, ' ', left, right);
    }
    print();
    int suma_total = head->frequency + head->next->frequency;
    Node* root = new Node(suma_total, ' ');
    root->children[0] = head;
    root->children[1] = head->next;
    head->next = nullptr;
    head = root;
}

void LinkedList::print()
{
    std::cout << "HEAD-> ";
    for(Node* it = head; it; it = it->next)
    {
        std::cout << "(" << it->name << ", " << it->frequency << ") -> ";
    }
    std::cout << "END\n";
}

Node* LinkedList::unbindHead()
{
    Node* old_head = head;
    head = head->next;
    old_head->next = nullptr;
    return old_head;
}