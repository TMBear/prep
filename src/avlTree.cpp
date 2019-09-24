////////////////////////////////////////////////////////////////////////
// https://www.hackerrank.com/challenges/self-balancing-tree/problem
//
#include <iostream>
#include <random>
#include "utils/binTree.h"


typedef struct node
{
  int val;
  struct node* left;
  struct node* right;
  int ht;
} node;


#include <algorithm>

int getHeightShallow(node* root) {
  return root ? root->ht : -1;
}

int balanceFactor(node* root) {
  if (!root)
    return 0;

  int leftHt = getHeightShallow(root->left);
  int rightHt = getHeightShallow(root->right);
  int balanceFactor = leftHt - rightHt;
  return balanceFactor;
}

void updateHeight(node* root) {
  if (!root)
    return;
  auto lh = getHeightShallow(root->left);
  auto rh = getHeightShallow(root->right);

  root->ht = std::max(lh, rh) + 1;
}

void updateDeepHeight(node* root) {
  updateHeight(root->left);
  updateHeight(root->right);
  updateHeight(root);
}

node* rotateLeftLeft(node* root) {
  node* leftChild = root->left;
  root->left = leftChild->right;
  leftChild->right = root;

  updateDeepHeight(leftChild);

  return leftChild;
}


node* rotateRightRight(node* root) {
  node* rightChild = root->right;
  root->right = rightChild->left;
  rightChild->left = root;

  updateDeepHeight(rightChild);
  
  return rightChild;
}


node* rotateLeftRight(node* root) {
  node* leftChild = root->left;
  node* leftRightChild = leftChild->right;
  leftChild->right = leftRightChild->left;
  leftRightChild->left = leftChild;
  root->left = leftRightChild;
  
  return rotateLeftLeft(root);
}


node* rotateRightLeft(node* root) {
  node* rightChild = root->right;
  node* rightLeftChild = rightChild->left;
  rightChild->left = rightLeftChild->right;
  rightLeftChild->right = rightChild;
  root->right = rightLeftChild;
  
  return rotateRightRight(root);
}



node* insert(node* root,int val)
{
	if (root == nullptr)
    return new node{val, nullptr, nullptr, 0};
  
  node* &subtree = val < root->val ? root->left : root->right;
  subtree = insert(subtree, val);

  if (balanceFactor(root) == 2) {
    if (balanceFactor(root->left) == -1)
      root = rotateLeftRight(root);
    else
      root = rotateLeftLeft(root);
  } else if (balanceFactor(root) == -2) {
    if (balanceFactor(root->right) == 1) 
      root = rotateRightLeft(root);
    else
      root = rotateRightRight(root);
  }
  
  int leftHt = getHeightShallow(root->left);
  int rightHt = getHeightShallow(root->right);
  root->ht = std::max(leftHt, rightHt) + 1;
  
  return root;
}



BinTree<std::string>::Node* convertTree(node* root) {
  if (!root)
    return nullptr;

  auto newRoot = new BinTree<std::string>::Node(std::to_string(root->val) + "-" + std::to_string(root->ht));
  newRoot->left = convertTree(root->left);
  newRoot->right = convertTree(root->right);

  return newRoot;
}

void dumpTree(node* root) {
  BinTree<std::string> bt(convertTree(root));
  bt.Dump();
 
  std::cout << std::endl << std::endl;
}



void avlTree() {

  // First create an instance of an engine.
  std::random_device rnd_device;
  // Specify the engine and distribution.
  std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
  std::uniform_int_distribution<int> dist {1, 52};

  auto gen = [&dist, &mersenne_engine](){return dist(mersenne_engine);};

  std::vector<int> data(10);
  generate(data.begin(), data.end(), gen);

//  std::vector<int> data = {13, 47, 46, 27, 34};
  for (const auto i : data)
    std::cout << i << ", ";

  std::cout << std::endl << std::endl;

  node* r = nullptr;
  for (const auto i: data) {
    r = insert(r, i);
    dumpTree(r);
  }
}

