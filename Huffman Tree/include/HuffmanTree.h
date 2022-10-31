#include <map>
#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <vector>
#include "./LinkedList.h"

struct HuffmanTree{
    
    public:
    
    HuffmanTree();
    HuffmanTree(LinkedList);
    void inorder(Node*);
    void decode(std::string);
    void importHuffmanTree();
    void exportHuffmanTree();
    Node* root;

    private:
    Node* loadHuffmanTree(int&, const std::vector<std::string> &);
    void saveNode(Node*, std::ofstream&);
};

HuffmanTree::HuffmanTree() : root(nullptr)
{
    char option;
    std::cout << "Got a file to import? (y/n): ";
    std::cin >> option;
    if(option == 'y')
    {
        importHuffmanTree();
    }
    else{
        LinkedList temporalLinkedList;
        std::map<char, int> frecuencies; 
        std::string line;
        std::ifstream infile("../tests/test1.txt");
        if (infile.is_open())
        {
            while(std::getline(infile, line))
            {
                for(int i = 0; i < line.size(); i++)
                {
                    frecuencies[line[i]]++;
                }
            }
        }

        for(auto it = frecuencies.begin(); it != frecuencies.end(); ++it)
        {
            temporalLinkedList.insert(it->second, it->first);
        }

        while(temporalLinkedList.head->next)
            {
                Node* left = temporalLinkedList.unbindHead();
                Node* right = temporalLinkedList.unbindHead();
                int result = left->frequency + right->frequency;
                temporalLinkedList.insert(result, ' ', left, right);
                temporalLinkedList.print();
            }
        root = temporalLinkedList.head;
    }

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

Node* HuffmanTree::loadHuffmanTree(int& id, const std::vector<std::string>& nodes )
{
    int children = stoi(nodes[id].substr(0,1));
    int frequency = stoi(nodes[id].substr(2, nodes[id].size()));
    char name = nodes[id][1];

    if(!children){
        Node* leaf = new Node(frequency, name);
        return leaf;
    }
    Node* left = loadHuffmanTree(++id, nodes);
    Node* right = loadHuffmanTree(++id, nodes);
    Node* dad = new Node(frequency, name);
    dad->children[0] = left;
    dad->children[1] = right;
    return dad;
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

void HuffmanTree::importHuffmanTree()
{
    std::vector<std::string> data;
    std::string line;
    std::string path = "../files/";
    std::string file_name;
    std::cout << "Enter file-to-import name: ";
    std::cin >> file_name;
    path.append(file_name);
    std::ifstream infile(path);
    if(infile.is_open())
    {
        while(std::getline(infile, line))
        {
            data.push_back(line);
        }
    }
    else{
        std::cout << "Unable to open file" << std::endl;
    }

    for(auto e : data)
    {
        std::cout << e << std::endl;
    }
    int id = 0;
    root = loadHuffmanTree(id, data);
}

void HuffmanTree::exportHuffmanTree()
{
    std::string file_name;
    std::string exported_file_name = "../files/";
    std::cout << "Enter file-to-export name: ";
    std::cin >> file_name;
    file_name.append(".txt");
    exported_file_name.append(file_name);
    std::ofstream outfile(exported_file_name);

    if(!outfile.is_open())
    {
        std::cout << "Unable to create file" << std::endl;
        return;
    }

    saveNode(root, outfile);

    std::cout << file_name << " saved succesfully! at " << exported_file_name  << std::endl;
}

void HuffmanTree::saveNode(Node* cur_node, std::ofstream& outfile)
{
    if(cur_node->is_leaf())
        outfile << "0"; 
    else
        outfile << "1";
    outfile << cur_node->name << cur_node->frequency << "\n";

    if(!cur_node->is_leaf())
    {
        saveNode(cur_node->children[0], outfile);
        saveNode(cur_node->children[1], outfile);
    }
}