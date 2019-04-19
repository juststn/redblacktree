#include <iostream>
#include <string.h>
#include <stack>
#include "TreeNode.h"
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <Vector>
#include <math.h>
#include <iomanip>
#include <fstream>

using namespace std;


/*
Justin He 
Period 2
Red-Black Tree: binary search tree with red-black color to balance the tree
*/

void rotateTree(TreeNode* &current);
void addToTree(int number, TreeNode* &root);
void printTree(TreeNode* root);
void getPrintList(TreeNode* root, int k, int array[1000], int colorArray[1000]);
void printRow(int array[1000], int height, int depth, int cnt);
int  getHeight(TreeNode* root);
void printBinary(TreeNode* root, int numberOfSpace);
void printRow1(int array[1000], int colorArray[1000], int cnt);
void rotateLeft(TreeNode* &current);
void rotateRight(TreeNode* &current);
void printList(TreeNode* root);

int main(){
  char array[5000] = "";
  char token[100] = "";
  int arrayLength = 0;
  int layer = 0;
  TreeNode* root = NULL;
  char filename[200] ="";
  char in[200] =""; 
  ifstream infile;
  int  hasFile =0;
  
  // get file name, and read the first line from the file
  cout<< "Read in a file (yes, no)?"<<endl;
  cin.getline(in, 200);
  if (!strcmp(in, (char*)"yes")) {
    cout << "Please enter the file name: ";
    cin.getline(filename, 200);
    infile.open(filename);
    if (infile.is_open()) {
      infile.getline(array, 5000);
      infile.close();

      hasFile =1;
    }
  else
    {
      cout << "can not open the input file. " << endl;
    }
  }
  
  if (hasFile ==1) {
  // parse the line with list of numbers
  arrayLength = strlen(array);
  for (int i = 0; i <= arrayLength; i++){
    if (array[i] != ' ' && array[i] != ',' && array[i] != '\0'){
      strncat(token, &array[i], 1);
    }
    else{
      if(token[0] != ' ' && token[0] != ',' && token[0] != '\0'){
      int temp = atoi(token);
      token[0] = '\0';
      addToTree(temp, root);
      }
    }
  }
  
  //  cout << "HELLO: " << array << endl;
  cout << "Print of the red-black binary search tree (R for red, B for black): " << endl;
  printTree(root);

  }
  
  char input[100]="";
  int  value;
  int loop=1;
  while (loop ==1) {
    cout << endl << "Enter command (add, print, listprint, exit):" << endl << "(\"listprint\" is for value/color/parent details, \"print\" is treelike)" << endl;
    cin >> input;

    if (!strcmp(input, (char*)"print")) {
      //printBinary(root, 0);
      printTree(root);
    }

    if (!strcmp(input, (char*)"listprint")){
      printList(root);
    }
    if (!strcmp(input, (char*)"add")) {
      cout << "Enter a number to add to tree:" << endl;
      cin >> value;
      addToTree(value, root);
    }
    
    if (!strcmp(input, (char*)"exit")) {
      loop = 0;
    }
    cin.clear();
  }
}

//Shifts and recolors the tree so that the conditions for a red black tree are met
void rotateTree(TreeNode* &current){

  if (current->getParent() == NULL)
    return;

  if (current->getParent()->getColor() == 1)
    return;
  
  //Get color of uncle
  TreeNode* temp = current->getParent()->getParent();
  
  //No grandparent, set parent to black
  if(temp == NULL){
    current->getParent()->setColor(1);
    return;
  }

  //Uncle is the left child of grandparent
  if(temp->getRight() == current->getParent() && temp->getLeft() != NULL){
    int uncleColor = temp->getLeft()->getColor();

    //Uncle is red, recolor parent and uncle to black
    if(uncleColor == 0){
      current->getParent()->setColor(1);
      temp->getLeft()->setColor(1);
      if(temp->getParent() != NULL){
        temp->setColor(0);
        rotateTree(temp);
      }
    }
    else{
      //rotateLeft
      rotateLeft(current);
    }
    return;
  }
  // if has no uncle as left child of grandparent (current is on right side of grandparent)
  if (temp->getRight() == current->getParent() && temp->getLeft() == NULL) {
    rotateLeft(current);
    return;
  }
    
  
  //Uncle is the right child of grandparent
  if(temp->getLeft() == current->getParent() && temp->getRight() != NULL){
    int uncleColor = temp->getRight()->getColor();

    //Uncle red, recolor parent and uncle to black
    if(uncleColor == 0){
      current->getParent()->setColor(1);
      temp->getRight()->setColor(1);
      if(temp->getParent() != NULL){
	temp->setColor(0);
	rotateTree(temp);
      }
    }
    else{
      //rotate Right
      rotateRight(current);
    }
    return;
  }
  
  // if has no uncle as right child of grandparent
  if (temp->getLeft() == current->getParent() && temp->getRight() == NULL) {
    rotateRight(current);
    return; 
  }
    
}

// rotate tree to right, uncle is on right side of grandparent
void rotateRight(TreeNode* &current) {

  // first, if the current is a right child, rotate it to be left child
  if (current == current->getParent()->getRight()) {
    TreeNode* p =current->getParent();
    TreeNode* t2 =current->getLeft();
    TreeNode* g = current->getParent()->getParent();

    g->setLeft(current);
    current->setLeft(p);
    p->setRight(t2);
    current->setParent(g);
    p->setParent(current);
    
    if(t2 != NULL){
      
    t2->setParent(p);
    
    }
    
    current = p;
  }
  
  // when current is left child
  if (current == current->getParent()->getLeft()) {
    TreeNode* p = current->getParent();
    TreeNode* g = current->getParent()->getParent();
    TreeNode* u = g->getRight();
    TreeNode* t3 = p->getRight();
    
    int pValue = current->getParent()->getValue();
    int gValue = current->getParent()->getParent()->getValue();

    g->setLeft(current);
    g->setValue(pValue);
    current->setParent(g);

    p->setLeft(t3);
    p->setRight(u);
    p->setParent(g);
    p->setValue(gValue);
    g->setRight(p);
    if (t3 != NULL) {t3->setParent(p); }
    if (u != NULL) { u->setParent(p); }

  }
  
}

//rotate right, uncle is on the right side of grandparent
void rotateLeft(TreeNode* &current) {
   if (current == current->getParent()->getLeft()) {
    TreeNode* p =current->getParent();
    TreeNode* t2 =current->getRight();
    TreeNode* g = current->getParent()->getParent();

    g->setRight(current);
    current->setRight(p);
    p->setLeft(t2);
    current->setParent(g);
    p->setParent(current);

    if(t2 != NULL){

    t2->setParent(p);

    }

    current = p;
  }

    // when current is right child
  if (current == current->getParent()->getRight()) {
    TreeNode* p = current->getParent();
    TreeNode* g = current->getParent()->getParent();
    TreeNode* u = g->getLeft();
    TreeNode* t3 = p->getLeft();

    int pValue = current->getParent()->getValue();
    int gValue = current->getParent()->getParent()->getValue();

    g->setRight(current);
    g->setValue(pValue);
    current->setParent(g);

    p->setRight(t3);
    p->setLeft(u);
    p->setParent(g);
    p->setValue(gValue);
    g->setLeft(p);
    if (t3 != NULL) {t3->setParent(p); }
    if (u != NULL) { u->setParent(p); }

  }

   

}

//Add
void addToTree(int number, TreeNode* &root){

  //Add new node with value of number to the tree
  if (root == NULL){
    TreeNode* newNode = new TreeNode;
    newNode->setValue(number);
    newNode->setColor(1);
    root = newNode;
    return;
  }
  else{
    if(number > root->getValue()){
      //Root has no right child
      if(root->getRight() == NULL){
	
	TreeNode* newNode = new TreeNode;
	newNode->setValue(number);
	newNode->setParent(root);
	root->setRight(newNode);
	if(root->getColor() == 0){
	  //Recolor tree
          rotateTree(newNode);
	}
	return;
	}
      //Recursive call to add to right subtree using temporary variable
      else{
	TreeNode* temp = root->getRight();
	addToTree(number, temp);
      }
      return;
    }
    if(number <= root->getValue()){
      //Root has no left child
      if(root->getLeft() == NULL){
	  TreeNode* newNode = new TreeNode;
	  newNode->setValue(number);
	  newNode->setParent(root);
	  root->setLeft(newNode);
	  if(root->getColor() == 0){
	    //Recolor
	    rotateTree(newNode);
	  }
	  return;
      }
      //Recursive call to add to left subtree using temporary variable
      else{
	TreeNode* temp = root->getLeft();
	addToTree(number, temp);
      }

      return;
    } 
  }
}



//Prints a list with parent color and value
void printList(TreeNode* root){
  if(root == NULL){
    cout << "NULL;" << endl;
  }
  else{
    //VALUE  
    cout << "Value: " << root->getValue() << "; ";

    //COLOR
    if(root->getColor() == 0){
      cout << "Color: " << "R; ";
    }
    else{
      cout << "Color: " << "B; ";
    }

    //PARENT
    if(root->getParent() != NULL){
      cout << "Parent: " << root->getParent()->getValue() << "; ";
    }
    else{
      cout << "Parent: " << "NULL; " << "IS " << "ROOT; ";
    }

    //LEFT OR RIGHT CHILD
    if(root->getParent() != NULL && root->getParent()->getLeft() == root){
      cout << "Is Left/Right Child: " << "Left;";
    }
    if(root->getParent() != NULL && root->getParent()->getRight() == root){
      cout << "Is Left/Right Child: " << "Right;";
    }

    //CHILDREN
    if(root->getLeft() != NULL){
      cout << " Left Child: " << root->getLeft()->getValue() << ";";
    }
    else{
      cout << " Left Child: " << "NULL; ";
    }

    if(root->getRight() != NULL){
      cout << " Right Child: " << root->getRight()->getValue() << endl << endl;
    }
    else{
      cout << " Right Child: " << "NULL" << endl << endl;
    }

    //RECURSIVE
    if(root->getLeft() != NULL){
      printList(root->getLeft());
    }
    if(root->getRight() != NULL){
      printList(root->getRight());
    }
  }
}

// print a binary search tree, row by row
void printTree(TreeNode* root)
 {
      int array[1000];
      int colorArray[1000];
      // initialize the array
      for (int i = 0; i < 1000; i++){
      array[i] = -999;  // -999 represent null tree node
      colorArray[i] = -999;
      }
      // put the tree node value into the array
      getPrintList(root, 0, array, colorArray);
      
      int height = getHeight(root);
      //      cout << "Tree height: " << height << endl;
      
      int cnt=1;
      for (int i = 0 ; i < height; i ++) {
	// printRow(array, height, i, cnt);
	printRow1(array, colorArray, cnt);
	cnt = cnt * 2; 
      }
  }

// get height of tree
int getHeight(TreeNode* root)
{
  if (root == NULL) {
    return 0;
  }

  int righth, lefth;
  righth = getHeight(root->getRight());
  lefth = getHeight(root->getLeft());

  if (righth > lefth) {
    return righth +1;
  }
  else
    {
      return lefth+1;
    }
}

// get the tree into an array for printing
void getPrintList(TreeNode* root, int k, int array[1000], int colorArray[1000])
{
  if (root == NULL)
    return;

  array[k] = root->getValue();
  colorArray[k] = root->getColor();
  getPrintList(root->getLeft(), k*2+1, array, colorArray);
  getPrintList(root->getRight(), k*2+2, array, colorArray);
}

// print a row
void printRow1(int array[1000], int colorArray[1000], int cnt)
{
  int startIndex = cnt-1;
  int endIndex = startIndex + cnt;

  for (int i = startIndex; i < endIndex; i++) {
    if (array[i] != -999){
      printf("%3d", array[i]);
      if (colorArray[i] == 0) {
	printf("R ");
      }
      else{
	printf("B ");
      }   
    }
   else{
      if (cnt <= 63)
         printf(" ___ ");
      else
         printf(" _ ");
    }
  }

  printf("\n");
}
