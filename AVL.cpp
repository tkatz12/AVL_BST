//
// Created by Tyler on 9/14/2024.
//
#include "AVL.h"

//constructor for AVL class with empty root
AVL::AVL() : root(nullptr) {}

//function for destructor
void AVL::destroy(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    //delete children then current node
    destroy(node->left);
    destroy(node->right);
    delete node;
}

//destructor
AVL::~AVL()
{
    destroy(root);
}

//to help with updating height as operations occur
int AVL::getHeight(TreeNode* node)
{
    //to handle when children are null
    if (node == nullptr)
    {
        return 0;
    }

    else
    {
        return node->height;
    }
}

//calculate balance factor for given node
int AVL::getBalanceFactor(TreeNode* node)
{
    //no balance factor if null
    if (node == nullptr)
    {
        return 0;
    }
    //calculate balance factor
    return getHeight(node->left) - getHeight(node->right);
}

//change node's height directly when rotations/insertions/removals occur
void AVL::updateHeight(TreeNode* node)
{
    if (node != nullptr)
    {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

//left heavy imbalance rotation from class
TreeNode* AVL::rightRotate(TreeNode* node)
{
    TreeNode* grandchild = node->left->right;
    TreeNode* new_parent = node->left;
    new_parent->right = node;
    node->left = grandchild;

    //update heights
    updateHeight(node);
    updateHeight(new_parent);
    return new_parent;
}

//right heavy imbalance rotation from class
TreeNode* AVL::leftRotate(TreeNode* node)
{
    TreeNode* grandchild = node->right->left;
    TreeNode* new_parent = node->right;
    new_parent->left = node;
    node->right = grandchild;

    //update heights
    updateHeight(node);
    updateHeight(new_parent);
    return new_parent;
}

//left heavy, but left child subtree is right heavy
TreeNode* AVL::leftRightRotate(TreeNode* node)
{
    //left rotation on left child, then right rotation on node
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

//right heavy, but right child subtree is left heavy
TreeNode* AVL::rightLeftRotate(TreeNode* node)
{
    //right rotation on right child, then left rotation on node
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

//from class slides on trees, but store in string vector for print
void AVL::inOrder(TreeNode* node, vector<string>& res)
{
    if (node == nullptr) return;
    else
    {
        inOrder(node->left, res);
        res.push_back(node->Name);
        inOrder(node->right, res);
    }
}

//from class slides on trees, but store in string vector for print
void AVL::preOrder(TreeNode* node, vector<string>& res)
{
    if (node == nullptr) return;
    else
    {
        res.push_back(node->Name);
        preOrder(node->left, res);
        preOrder(node->right, res);
    }
}

//from class slides on trees, but store in string vector for print
void AVL::postOrder(TreeNode* node, vector<string>& res)
{
    if (node == nullptr) return;
    else
    {
        postOrder(node->left, res);
        postOrder(node->right, res);
        res.push_back(node->Name);
    }
}

//help function for loop to avoid repetition
void AVL::printHelp(const vector<string>& res)
{
    //loop through vector printing all names with comma except last
    for (int i = 0; i < (int)res.size(); i++)
    {
        if (i != (int)res.size() - 1)
        {
            cout << res[i] << ", ";
        }
        else
        {
            cout << res[i];
        }
    }
}

//update root
void AVL::setRoot(TreeNode* new_root)
{
    root = new_root;
}

//to get root outside of class
TreeNode* AVL::getRoot()
{
    return root;
}

//use root internally for print function
void AVL::printInorder()
{
    //store the inorder sequence of names in vector and print
    vector<string> res;
    inOrder(root, res);
    printHelp(res);
}

//use root internally for print function
void AVL::printPreorder()
{
    //store the preorder sequence of names in vector and print
    vector<string> res;
    preOrder(root, res);
    printHelp(res);
}

//use root internally for print function
void AVL::printPostorder()
{
    //store the postorder sequence of names in vector and print
    vector<string> res;
    postOrder(root, res);
    printHelp(res);
}

//use root internally for print function
void AVL::printLevelCount()
{
    if (root == nullptr)
    {
        cout << 0;
    }

    //level is the height of the root since tree is self-balancing
    else
    {
        cout << root->height;
    }
}

//for loop for testing the 3 depth first traversal
string AVL::testHelp(const vector<string>& res)
{
    //result for test comparison
    string result;

    //same thing as printhelp
    //loop through vector returning all names as string with comma except last
    for (int i = 0; i < (int)res.size(); i++)
    {
        if (i != (int)res.size() - 1)
        {
            result += res[i];
            result += ", ";
        }
        else
        {
            result += res[i];
        }
    }
    return result;
}

//test inorder traversal
string AVL::testInorder()
{
    //sort inOrder
    vector<string> res;
    inOrder(root, res);
    return testHelp(res);
}

//test preorder traversal
string AVL::testPreorder()
{
    //sort preOrder
    vector<string> res;
    preOrder(root, res);
    return testHelp(res);
}

//test postorder traversal
string AVL::testPostorder()
{
    //sort postOrder
    vector<string> res;
    postOrder(root, res);
    return testHelp(res);
}

//ensure id is unique and not already used
bool AVL::idUnique(TreeNode* node, int id)
{
    //if we get to a null node in either subtree, it is unique
    if (node == nullptr) return true;

    //if the id matches another id, not unique
    if (node->ID == id) return false;

    if (id < node->ID)
    {
        return idUnique(node->left, id);
    }

    else
    {
        return idUnique(node->right, id);
    }
}

//public recursive insert function
TreeNode* AVL::insert(TreeNode* node, int id, const string& name)
{
    //if node is null, insert as root for first case,
    //then for all other cases insert in respective location
    if (node == nullptr)
    {
        cout << "successful";
        return new TreeNode(id, name);
    }

    //ensure id is not repeated, if it is, return node unchanged
    if (!idUnique(root, id))
    {
        cout << "unsuccessful";
        return node;
    }

    //check the left subtree
    if (id < node->ID)
    {
        node->left = insert(node->left, id, name);
    }

    //check the right subtree
    else
    {
        node->right = insert(node->right, id, name);
    }

    //update the height of the node and ones affected
    //and calculate balance factor in case of rotations
    updateHeight(node);
    int balance_factor = getBalanceFactor(node);

    //check each of the four rotations and perform as necessary
    //left left case -> right rotation
    if (balance_factor == 2 && getBalanceFactor(node->left) == 1)
    {
        return rightRotate(node);
    }

    //right right case -> left rotation
    if (balance_factor == -2 && getBalanceFactor(node->right) == -1)
    {
        return leftRotate(node);
    }

    //left right case -> leftRight rotation
    if (balance_factor == 2 && getBalanceFactor(node->left) == -1)
    {
        return leftRightRotate(node);
    }

    //right left case -> rightLeft rotation
    if (balance_factor == -2 && getBalanceFactor(node->right) == 1)
    {
        return rightLeftRotate(node);
    }
    return node;
}

//search name
void AVL::searchName(TreeNode* node, const string& name)
{
    //follow preorder structure NLR
    static bool match = false;
    static bool first_match = true; //debug the extra newline after successfully printing
    if (node == nullptr) return;

    //link for how to handle id since I only need to use the actual integer for search
    //whereas internally, understanding id as not 8 digits is still ok for the project
    //https://stackoverflow.com/questions/12942348/is-it-possible-to-store-a-leading-zero-in-an-int
    if (node->Name == name)
    {
        if (!first_match)
        {
            cout << endl;
        }
        cout << setw(8) << setfill('0') << node->ID;
        match = true;
        first_match = false; //no new line for unsuccessful or one match
    }

    //recursively search each subtree, left then right
    searchName(node->left, name);
    searchName(node->right, name);

    //check if matches were found
    if (node == root)
    {
        if (!match)
        {
            cout << "unsuccessful";
        }

        //reset for multiple searches
        match = false;
        first_match = true;
    }
}

//search ID
void AVL::searchID(TreeNode* node, int id)
{
    //null node has no name or id
    if (node == nullptr)
    {
        cout << "unsuccessful";
        return;
    }

    //if current node matches, print
    if (node->ID == id)
    {
        cout << node->Name;
        return;
    }

    //recursively search through correct subtree, left then right
    if (id < node->ID)
    {
        searchID(node->left, id);
    }

    else
    {
        searchID(node->right, id);
    }
}

//remove ID
TreeNode* AVL::remove(TreeNode* node, int id)
{
    //ensure id exists
    if (idUnique(root, id))
    {
        cout << "unsuccessful";
        return node;
    }

    //base case
    if (node == nullptr) return nullptr;

    //recursively iterate respective subtree
    else if (id < node->ID)
    {
        node->left = remove(node->left, id);
    }

    else if (id > node->ID)
    {
        node->right = remove(node->right, id);
    }

    //handle the 3 scenarios
    else if (id == node->ID)
    {
        //no children
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            cout << "successful";
            return nullptr;
        }

        //1 child
        if (node->left == nullptr && node->right != nullptr)
        {
            TreeNode* temp = node->right;
            delete node;
            cout << "successful";
            return temp;
        }
        if (node->right == nullptr && node->left != nullptr)
        {
            TreeNode* temp = node->left;
            delete node;
            cout << "successful";
            return temp;
        }

        //2 children
        if (node->left != nullptr && node->right != nullptr)
        {
            //find the inorder successor
            TreeNode* successor = node->right;
            while (successor->left != nullptr)
            {
                successor = successor->left;
            }

            //replace current node with successor node
            //and recurse the right subtree for removal
            node->ID = successor->ID;
            node->Name = successor->Name;
            node->right = remove(node->right, successor->ID);
        }
    }

    //update the height of affected nodes and return the node
    updateHeight(node);
    return node;
}

//inOrder helper for removeInorder
void AVL::inOrderID(TreeNode* node, vector<int>& res)
{
    if (node == nullptr) return;
    else
    {
        inOrderID(node->left, res);
        res.push_back(node->ID);
        inOrderID(node->right, res);
    }
}

//removeInorder
TreeNode* AVL::removeInorder(TreeNode* node, int N)
{
    //use helper to perform inorder traversal
    vector<int> res;
    inOrderID(node, res);

    //make sure N is less than total number of nodes
    if (N > (int)res.size() - 1)
    {
        cout << "unsuccessful";
        return nullptr;
    }

    //perform removal
    node = remove(node, res[N]);

    //return the node
    return node;
}