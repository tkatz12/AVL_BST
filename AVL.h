//
// Created by Tyler on 9/14/2024.
//
#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

//used this setup from Trees slides in class
struct TreeNode
{
    //node components, including height
    int ID;
    string Name;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int id, const string& name) : ID(id), Name(name),
    height(1), left(nullptr), right(nullptr) {}
};

class AVL
{
private:
    TreeNode* root;
    void destroy(TreeNode* node);
    int getHeight(TreeNode* node);
    int getBalanceFactor(TreeNode* node);
    void updateHeight(TreeNode* node);
    TreeNode* rightRotate(TreeNode* node);
    TreeNode* leftRotate(TreeNode* node);
    TreeNode* leftRightRotate(TreeNode* node);
    TreeNode* rightLeftRotate(TreeNode* node);
    void inOrder(TreeNode* node, vector<string>& res);
    void preOrder(TreeNode* node, vector<string>& res);
    void postOrder(TreeNode* node, vector<string>& res);
    void printHelp(const vector<string>& res);
    bool idUnique(TreeNode* node, int id);
    void inOrderID(TreeNode* node, vector<int>& res);
public:
    AVL();
    ~AVL();
    void setRoot(TreeNode* new_root);
    TreeNode* getRoot();
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    string testHelp(const vector<string>& res);
    string testInorder();
    string testPreorder();
    string testPostorder();
    TreeNode* insert(TreeNode* node, int id, const string& name);
    void searchName(TreeNode* node, const string& name);
    void searchID(TreeNode* node, int id);
    TreeNode* remove(TreeNode* node, int id);
    TreeNode* removeInorder(TreeNode* node, int N);
};

#endif //PROJECT1_AVL_H