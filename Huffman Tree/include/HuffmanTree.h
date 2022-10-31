#include <iostream>
#include <string>
#include "./LinkedList.h"

struct HuffmanTree{
    HuffmanTree();
    HuffmanTree(LinkedList);
    void inorder(Node*);
    void decode(std::string);
    Node* root;
};

HuffmanTree::HuffmanTree()
{

}

HuffmanTree::HuffmanTree(LinkedList myLinkedList)
{
    while(myLinkedList.head->next)
    {
        Node* left = myLinkedList.unbindHead();
        Node* right = myLinkedList.unbindHead();
        int result = left->frequency + right->frequency;
        myLinkedList.insert(result, ' ', left, right);
        myLinkedList.print();
    }
    root = myLinkedList.head;
}

void HuffmanTree::decode(std::string str)
{
    Node* it = root->children[(int) str[0] - '0'];

    for(int i = 0; i < str.size() ; i++)
    {
        if(it->is_leaf())
        {
            std::cout << it->name;
            it = root->children[(int) str[i + 1] - '0'];
        }
        else{
            it = it->children[(int)str[i + 1] - '0'];
        }
    }
}

void HuffmanTree::inorder(Node* m_root){
    if(!m_root) return;
    else
    {
        inorder(m_root->children[0]);
        std::cout << "(" << m_root->name << ", " << m_root->frequency << ") ";
        inorder(m_root->children[1]);
    }

}