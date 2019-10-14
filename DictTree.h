#pragma once

//using namespace std;

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
    void preorder(void visit(ItemType&), TreeNode<KeyType, ItemType>* treePtr) const;
    int numNodes;
public:
    DictTree();
    void add(KeyType newKey, ItemType newItem);
    bool remove(KeyType newKeys);
    bool contains(KeyType key);
    ItemType getItem(KeyType key);
    int size();
    void traverse(void visit(ItemType&)) const;
};


template <class KeyType, class ItemType>
DictTree<KeyType, ItemType>::DictTree()
{
    // Set up the root and the initial number of nodes to 0
    root = 0;
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
bool DictTree<KeyType, ItemType>::remove(KeyType key)
{
    // This method is done.
    bool isSuccessful = false;

    root = removeFromSubtree(root, key, isSuccessful);

    if (isSuccessful)
        numNodes--;

    return isSuccessful;
}

template<class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::removeFromSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key, bool& success)
{
    // Refer to previous implementation nodes

    return nullptr;
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
    // Refer to previous implementation nodes
    return nullptr;
}

template<class KeyType, class ItemType>
ItemType DictTree<KeyType, ItemType>::getItem(KeyType key)
{
    // Use containedInSubtree to find the "item" of the node with the "key"
    // This should be a single line of code.
    return nullptr;
}

template <class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>::contains(KeyType key)
{
    // Use containedInSubtree to see if a node with the "key" is null.

    return false;
}

template <class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::containedInSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key)
{
    // If the subtree is nullptr, then return nullptr
    if (subTree==nullptr)
    {
        return nullptr;
    }
    // If the subtree key is equal to key, then return the subtree
    while (subTree)
        {
            if (key==subTree->key)
            {
                return subTree;
            }

            // If the key is less than the subTree key
            //   see if the key is contained in the left subtree
            if (key < subTree->key)
            {
                subTree = subTree->left;
            }
            // else
                //   see if the key is contained in the right subtree
            else
            {
                subTree = subTree->right;
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

    preorder( visit, treePtr->left);
    visit(treePtr->item);
    preorder(visit, treePtr->right);
}

