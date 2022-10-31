struct Node
{   
    char name;
    int frequency;
    Node *next, *children[2];
    Node();
    Node(int, char, Node* = nullptr);

    bool is_leaf();
};

Node::Node(): name('0'), frequency(0)
{
    next = children[0] = children[1] = nullptr;
}

Node::Node(int _frequency, char _name, Node* _next) : name(_name), frequency(_frequency), next(_next)
{
    children[0] = children[1] = nullptr;
}

bool Node::is_leaf ()
{
    return !children[0] && !children[1];
}