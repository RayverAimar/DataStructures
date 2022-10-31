
#include <vector>
#include "../include/HuffmanTree.h"

using namespace std;


int main()
{

    LinkedList myLinkedList;
    std::vector<char> characters = { 'a', 'b', 'c', 'd', 'e', 'f' };
    std::vector<int> frequencies = { 45, 13, 12, 16, 9, 5 };
    for(int i = 0; i < characters.size(); i++ ) myLinkedList.insert(frequencies[i], characters[i]);
    myLinkedList.print();

    HuffmanTree huffmanTree(myLinkedList);

    huffmanTree.inorder(huffmanTree.root);

    std::string first_str = "100011001101";

    std::cout << std::endl;

    huffmanTree.decode(first_str);

}


