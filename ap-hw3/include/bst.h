#ifndef BST_H
#define BST_H

#include <iostream> 
#include <memory> 
#include <functional>
#include <list>
#include <iomanip>

class BST
{
public:
    class Node
    {
    public:
	    Node(int value, Node* left, Node* right);
	    Node();
	    Node(const Node& node);

        friend std::ostream& operator<<(std::ostream& os,BST::Node &node);
        friend bool operator<(int _value,BST::Node node);
        friend bool operator<(BST::Node node,int _value);
        friend bool operator>(int _value,BST::Node node);
        friend bool operator>(BST::Node node,int _value);
        friend bool operator<=(int _value,BST::Node node);
        friend bool operator<=(BST::Node node,int _value);
        friend bool operator>=(int _value,BST::Node node);
        friend bool operator>=(BST::Node node,int _value);
        friend bool operator==(int _value,BST::Node node);
        friend bool operator==(BST::Node node,int _value);
	    int value;
	    Node* left;
	    Node* right;
    };
    
    BST();
    ~BST();
    BST(BST &bst);
    BST(BST &&bst);   
    BST operator=(BST &bst);
    BST operator=(BST &&bst);
    BST operator++(int inpt);
    BST operator++();
    BST(std::initializer_list<int> inpt);

    Node*& get_root();
    void bfs(std::function<void(BST::Node*& node)> func) const;
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os,BST bst);

    private:
        Node* root;
};
#endif //BST_H