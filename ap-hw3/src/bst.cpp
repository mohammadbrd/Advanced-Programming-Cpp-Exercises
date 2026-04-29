#include "bst.h"
///////////////////////////////////////////////////////////////////////////////////////////////////
BST :: Node :: Node(int _value, Node* _left, Node* _right)
{
    value =  _value;
    left = _left;
    right = _right;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST :: Node :: Node()
{
    value = 0;
    right = nullptr;
    left = nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST :: Node :: Node(const Node& node)
{
    value = node.value;
    right = node.right;
    left = node.left;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os,BST::Node &node)
{
    os << "adress of node: " << &node << std::endl;
    os << "adress of left: " << node.left << std::endl;
    os << "adress of right: " << node.right << std::endl;
    os << "value: " << node.value;
    return os;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator<(int _value,BST::Node node)
{
    if(_value < node.value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator<(BST::Node node,int _value)
{
    if(node.value < _value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator>(int _value,BST::Node node)
{
    if(_value > node.value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator>(BST::Node node,int _value)
{
    if(node.value > _value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator<=(int _value,BST::Node node)
{
    if(_value <= node.value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator<=(BST::Node node,int _value)
{
    if(node.value <= _value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator>=(int _value,BST::Node node)
{
    if(_value >= node.value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator>=(BST::Node node,int _value)
{
    if(node.value >= _value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator==(int _value,BST::Node node)
{
    if(_value == node.value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool operator==(BST::Node node,int _value)
{
    if(node.value == _value)
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST::Node*& BST :: get_root()
{
    return root;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool BST :: add_node(int value)
{
    Node* root_1 {root};
    if(root == nullptr)
    {
        root = new Node{value, nullptr, nullptr};
    }
    else
    {
        while(1)
        {
            if(root_1->value > value)
            {
                if(root_1->left == nullptr)
                {
                    root_1->left = new Node{value, nullptr, nullptr};
                    break;
                }
                else
                    root_1 = root_1->left; 
            }
            else if(root_1->value < value)
            {
                if(root_1->right == nullptr)
                {
                    root_1->right = new Node{value, nullptr, nullptr};
                    break;
                }
                else
                    root_1 = root_1->right; 
            }
            else
                return false;
        }
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void BST :: bfs(std::function<void(BST::Node*& node)> func) const
{
    std::list<Node*> queue;
    queue.push_back(root);
    while(!queue.empty())
    {
        auto node =  queue.front();
        queue.pop_front();
        if(node !=  nullptr)
        {
            func(node);
            if(node->left)
                queue.push_back(node->left);
            if(node->right)
                queue.push_back(node->right);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
size_t bst_length(BST::Node *node)
{
    if (node == nullptr)
        return 0;
    else
        return(bst_length(node->left) + 1 + bst_length(node->right));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
size_t BST :: length()
{
    if (root->left == nullptr and root->right == nullptr)
        return 1;
    else
        return(1 + bst_length(root->left) + bst_length(root->right));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<(std::ostream& os,BST::Node *node)
{
    os << node;
    os << "       => value:" << node->value;
    if(node->value < 10)
        os<< " ";
    os << "        left:" << node->left;
    if(node->left == nullptr)
        os<< "        ";
    os << "        right:" << node->right<<std::endl; 
    if(node->left)
        std::cout < node->left;
    if(node->right)
        std::cout < node->right;  
    return os;    
}
///////////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os,BST bst)
{
    os << "********************************************************************************" << std::endl;
    os << bst.get_root();
    os << "       => value:" << bst.get_root()->value;
    os << "        left:" << bst.get_root()->left;
    os << "        right:" << bst.get_root()->right<<std::endl;
    if(bst.get_root()->left)
        std::cout < bst.get_root()->left;
    if(bst.get_root()->right)
        std::cout < bst.get_root()->right;
    os << "binary search tree size: " << bst.length() << std::endl;
    os << "********************************************************************************" << std::endl;
    return os;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST :: Node** BST :: find_node(int value)
{
    Node** root_1 {&root};
    while(1)
    {
        if((*root_1)->value > value)
        {
            if((*root_1)->left)
                root_1 = &(*root_1)->left; 
            else
                return nullptr;  
        }
        else if((*root_1)->value < value)
        {
            if((*root_1)->right)
                root_1 = &(*root_1)->right; 
            else
                return nullptr;
        }
        else
            return root_1;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST :: Node** BST :: find_parrent(int value)
{
    Node** root_1 {&root};
    while(1)
    {
        if((*root_1)->value > value)
        {
            if((*root_1)->left)
                if((*root_1)->left->value == value)
                    return root_1; 
                else
                    root_1 = &(*root_1)->left;   
        }
        else if((*root_1)->value < value)
        {
            if((*root_1)->right)
                if((*root_1)->right->value == value)
                    return root_1; 
                else
                    root_1 = &(*root_1)->right; 
        }
        else
            return nullptr;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST :: Node** BST :: find_successor(int value)
{
    BST::Node** node{find_node(value)};
    if((*node)->left)
    {
        if((*node)->left->right)
        {
            node = &(*node)->left;
            while((*node)->right)
                node = &(*node)->right;
            return node; 
        }
        else
            return &(*node)->left;
    }
    else
        return node;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool BST :: delete_node(int value)
{
    BST::Node** node{find_node(value)};
    if(node != nullptr)
    {
        if((*node)->left == nullptr and (*node)->right == nullptr)
        {
            BST::Node** node_par{find_parrent(value)};
            if(&(*node_par)->left == node)
                (*node_par) = new Node{(*node_par)->value, nullptr, (*node_par)->right};  
            else
                (*node_par) = new Node{(*node_par)->value, (*node_par)->left, nullptr};
        }
        else if((*node)->right == nullptr)
        {
            BST::Node** node_par{find_parrent(value)};
            if(&(*node_par)->left == node)
                (*node_par) = new Node{(*node_par)->value, (*node)->left, (*node_par)->right};  
            else
                (*node_par) = new Node{(*node_par)->value, (*node_par)->left, (*node)->left};
        }
        else if((*node)->left == nullptr)
        {
            BST::Node** node_par{find_parrent(value)};
            if(&(*node_par)->left == node)
                (*node_par) = new Node{(*node_par)->value, (*node)->right, (*node_par)->right};  
            else
                (*node_par) = new Node{(*node_par)->value, (*node_par)->left, (*node)->right};
        }
        else
        {
            BST::Node** node_par{find_parrent(value)};
            BST::Node** node_succ{find_successor(value)};
            BST::Node** node_par_succ{find_parrent((*node_succ)->value)};
            if(&(*node_par_succ)->left == node_succ)
                (*node_par_succ) = new Node{(*node_par_succ)->value, nullptr, (*node_par_succ)->right};  
            else
                (*node_par_succ) = new Node{(*node_par_succ)->value, (*node_par_succ)->left, nullptr};            
            if(node_par != nullptr)
            {
                (*node_succ) = new Node{(*node_succ)->value, (*node)->left, (*node)->right};
                if(&(*node_par)->left == node)
                    (*node_par) = new Node{(*node_par)->value, (*node_succ), (*node_par)->right};  
                else
                    (*node_par) = new Node{(*node_par)->value, (*node_par)->left, (*node_succ)};
            }
            else
                root = new Node{(*node_succ)->value, (*node)->left, (*node)->right};
        }
        return true;
    }
    else
        return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST::~BST()
{
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for(auto& node: nodes)
 	    delete node;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST::BST() : root{nullptr}
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST::BST(BST &inpt_bst) : root{nullptr}
{
    inpt_bst.bfs([this](BST::Node *&node){this->add_node(node->value);});
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST::BST(BST &&inpt_bst)
{
    root = inpt_bst.root;
    inpt_bst.root = nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST BST::operator=(BST &inpt_bst)
{
    inpt_bst.bfs([this](BST::Node *&node){this->add_node(node->value);});
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST BST::operator=(BST &&inpt_bst)
{
    root = inpt_bst.root;
    inpt_bst.root = nullptr;
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST::BST(std::initializer_list<int> inpt) : root{nullptr}
{
    for(int i : inpt)
        add_node(i);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST BST::operator++(int inpt)
{
    auto bfs {*this};
    this->bfs([this](BST::Node *&node){(node->value++);});
    return bfs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BST BST::operator++()
{
    this->bfs([this](BST::Node *&node){(node->value++);});
    return *this;
}