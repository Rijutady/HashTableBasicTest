#pragma once
#include<iostream>

using namespace std;

template <class KeyType, class ItemType>
struct TreeNode
{
    // Your implementation...
    KeyType key;
    ItemType item;
    TreeNode<KeyType, ItemType>* left;
    TreeNode<KeyType, ItemType>* right;
};

template <class KeyType, class ItemType>
class DictTree
{
private:
    TreeNode<KeyType, ItemType>* root;
    TreeNode<KeyType, ItemType>* removeFromSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key, bool& success);
    TreeNode<KeyType, ItemType>* removeNode(TreeNode<KeyType, ItemType>* node);
    TreeNode<KeyType, ItemType>* removeLeftmostNode(TreeNode<KeyType, ItemType>* node, TreeNode<KeyType, ItemType>* successor);
    TreeNode<KeyType, ItemType>* containedInSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key);
    void RemoveHelper(TreeNode<KeyType, ItemType>* subTree, KeyType key);
    void preorder(void visit(ItemType&), TreeNode<KeyType, ItemType>* treePtr) const;
    int numNodes;
public:
    DictTree();
    void add(KeyType newKey, ItemType newItem);
    void remove(KeyType newKeys);
    bool contains(KeyType key);
    ItemType getItem(KeyType key);
    int size();
    void traverse(void visit(ItemType&)) const;
    bool isNull();
};


template <class KeyType, class ItemType>
DictTree<KeyType, ItemType>::DictTree()
{
    // Set up the root and the initial number of nodes to 0
    root = nullptr;
    numNodes = 0;
}

template <class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::add(KeyType newKey, ItemType newItem)
{
    
    
    TreeNode<KeyType, ItemType>* currNode = root;


    // If the root hasn't been set up, make a new node with newKey, newItem
    // and set equal to this new node and return.
    
    if (root==nullptr) {
       
        TreeNode<KeyType, ItemType>* newNode = new TreeNode<KeyType, ItemType>;
        newNode->key= newKey;
        newNode->item = newItem;
        newNode->left = newNode->right = nullptr;

        root = newNode;
        numNodes = 1;
        return;
    }
    //Use containedInSubtree to determine if a node with newKey exists
    // If it does, use setValue to set the value to newKey and newItem and return.
    TreeNode<KeyType, ItemType>* n = containedInSubtree(currNode, newKey);
    if (n != nullptr){
        n->item = newItem;
        return;
    }
    else{
        TreeNode<KeyType, ItemType>* newNode = new TreeNode<KeyType, ItemType>;
        newNode->key= newKey;
        newNode->item = newItem;
        newNode->left = newNode->right = nullptr;

        while (currNode) {
            if (newKey < currNode->key) {            // left
                if (currNode->left == nullptr) {
                    currNode->left = newNode;
                    break;
                }
                currNode = currNode->left;
            }
            else{    // right
                if (currNode->right == nullptr) {
                    currNode->right = newNode;
                    break;
                }
                currNode = currNode->right;
            }
        }
    }
    
    numNodes++;
    
}

template <class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::remove(KeyType key)
{
     RemoveHelper(root, key);
    
   
}

template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::RemoveHelper(TreeNode<KeyType, ItemType>* subTree, KeyType key)
{
    // Refer to previous implementation nodes
    TreeNode<KeyType, ItemType>*par=nullptr;
    TreeNode<KeyType, ItemType>*cur=subTree;
    while (cur) {
        if (key==cur->key) {
            //Case 1) Node is a leaf - it is deleted
            if (!cur->left && !cur->right) {
                if (!par) {
                    subTree = removeNode(subTree);
                }
                else if (par->left==cur){
                    par->left=removeNode(subTree);
                }
                else
                    par->right=removeNode(subTree);
                numNodes--;
            }
            //Case 2) Node has one child (left/right) - parent adopts child
            else if(!cur->left && cur->right)
            {
                if (!par) {
                    subTree=cur->right;
                }
                else if (par->left==cur)
                    par->left=cur->right;
                else
                    par->right=cur->right;
                numNodes--;
            }
            else if (cur->left && !cur->right)
            {
                if(!par)
                    subTree=cur->left;
                else if(par->left==cur)
                    par->left=cur->left;
                else
                    par->right=cur->left;
                numNodes--;
            }
            else
            {
            TreeNode<KeyType,ItemType>*successor=cur->right;// On the right branch...
                while (successor->left)// travel as left as possible
                {
                    successor = successor->left;
                }
                KeyType sucKey = successor->key;
                ItemType sucItem = successor->item;// Remember the value of the successor
                RemoveHelper(subTree,sucKey);    // Remove the successor node
                cur->key = sucKey;
                cur->item= sucItem;// Copy the value of the successor node back// Refer to previous implementation nodes
            }
            return;
        }
        else if (key<cur->key)
        {
            par=cur;
            cur=cur->left;
        }
        else{
            par=cur;
            cur=cur->right;
        }
    }
}

/*
* Case 1) Node is a leaf - it is deleted
* Case 2) Node has one child (left/right) - parent adopts child
* Case 3) Node has two children - find successor node.
*/
template<class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::removeNode(TreeNode<KeyType, ItemType>* node)
{
    // Refer to previous implementation nodes
    
    return nullptr;
}

template<class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::removeLeftmostNode(TreeNode<KeyType, ItemType>* node, TreeNode<KeyType, ItemType>* successor)
{
    
    
    return nullptr;
}

template<class KeyType, class ItemType>
ItemType DictTree<KeyType, ItemType>::getItem(KeyType key)
{
    // Use containedInSubtree to find the "item" of the node with the "key"
    // This should be a single line of code.
    TreeNode<KeyType, ItemType>*n=containedInSubtree(root,key);
    return ItemType (n->item);
    //return nullptr;
}
template<class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>:: isNull()
{
    if(root==nullptr)
        return true;
    else
        return false;
}
template <class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>::contains(KeyType key)
{
    
    // Use containedInSubtree to see if a node with the "key" is null.
    if(root==nullptr)
    {
        return false;
    }
    
    return containedInSubtree(root,key);
    
     }
template <class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::containedInSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key)
{
    //cout<<"RooOT";
    // If the subtree is nullptr, then return nullptr
    while(subTree)
    {
    
    // If the subtree key is equal to key, then return the subtree
    //while (subTree)
        //{
        if (key==subTree->key)
    {
        return subTree;
    }
            // If the key is less than the subTree key
            //   see if the key is contained in the left subtree
        else if (key < subTree->key)
    {
        return containedInSubtree(subTree->left,key);
                //subTree = subTree->left;
    }
            // else
                //   see if the key is contained in the right subtree
        else
    {
        return containedInSubtree(subTree->right,key);
    }
    }
    return nullptr;
}

template <class KeyType, class ItemType>
int DictTree<KeyType, ItemType>::size()
{
    // This method is completed.
    return numNodes;
}

template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::traverse(void visit(ItemType&)) const
{
    // This method is completed.
    preorder(visit, root);
}

template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::preorder(void visit(ItemType&), TreeNode<KeyType, ItemType>* treePtr) const
{
    // Your implementation here...
    if (treePtr == nullptr)
        return;

    visit(treePtr->item);
    preorder( visit, treePtr->left);
    preorder(visit, treePtr->right);
    
}

