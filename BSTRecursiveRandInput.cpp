#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

struct node{
    int data;
    struct node* left;
    struct node* right;

    struct node* parent;
};

struct node* newNode(int data) 
{  
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  node->data = data; 
  node->left = NULL; 
  node->right = NULL; 

  node->parent = NULL;

  return(node); 
}

struct binarySearchTree{
    struct node *root = newNode(-1);
    binarySearchTree();
    void insertRec(int value, node* root){
        //initial count should always be 0
        if(root->data == -1){
            root->data=value;
            return;
        }
        //if(root->left==NULL){
        else if(value < root->data){
            if (root->left==NULL){
                root->left = newNode(-1);
                root->left->parent = root;
                
            }
            insertRec(value, root->left);
        }
        //insert(value, root->left);
        else if(value > root->data){
            if (root->right==NULL){
                root->right = newNode(-1);
                root->right->parent = root;
            }
            insertRec(value, root->right);
        }
        return;
    }
    void deleteRec(int value, node* root){
        if(root->data == value){
            //3 cases
            //leaf case
            if(root->left == NULL && root->right == NULL){
                //if this is root node
                if(root->parent == NULL){
                    root = newNode(-1);
                }
                //not root node
                else if(root->parent != NULL){
                    if(root->parent->data > root->data){
                        root->parent->left = NULL;
                    }
                    if(root->parent->data < root->data){
                        root->parent->right = NULL;
                    }
                }
            }
            //one child case
            else if(root->left != NULL && root->right == NULL){
                root->left->parent = root->parent;

                if(root->parent!=NULL){
                    if(root->parent->data > root->data){
                        root->parent->left = root->left;
                    }
                    if(root->parent->data < root->data){
                        root->parent->right = root->left;
                    }
                }
                else{
                    this->root=root->left;
                }
            }
            else if(root->left == NULL && root->right != NULL){
                root->right->parent = root->parent;

                if(root->parent != NULL){
                    if(root->parent->data > root->data){
                        root->parent->left = root->right;
                    }
                    if(root->parent->data < root->data){
                        root->parent->right = root->right;
                    }
                }
                else{
                    this->root=root->right;
                }
            }
            //two children case
            else if(root->left != NULL && root->right != NULL){
                int successor = findMinRec(root->right);
                deleteRec(successor, root->right);
                root->data = successor;
            }
            return;
        }
        else if(value < root->data){
            deleteRec(value, root->left);
        }
        else if(value > root->data){
            deleteRec(value, root->right);
        }
        return;
    }

    int findNextRec(node* root){
        int next;
        //ignore edge case where there is no next (no right child and no greater parent)
        //case with right child
        if(root->right != NULL){
            next = findMinRec(root->right);
        }
        //case with no right child, but greater parent exists
        else if(root->right == NULL && (root->parent->data > root->data)){
            next = root->parent->data;
        }
        return next;
    }

    int findPrevRec(node* root){
        int previous;
        //ignore edge case where there is no next (no left child and no lesser parent)
        //case with left child
        if(root->left != NULL){
            previous = findMaxRec(root->left);
        }
        //case with no left child, but lesser parent exists
        else if(root->left == NULL && (root->parent->data < root->data)){
            previous = root->parent->data;
        }
        return previous;
    }

    int findMinRec(node* root){
        int temp;
        //case where this is leaf
        if(root->left==NULL){
            return root->data;
        }
        //case where left/lesser child exists
        else if(root->left != NULL){
            temp = findMinRec(root->left);
        }
        return temp;
    }
    int findMaxRec(node* root){
        int temp;
        //case where this is leaf
        if(root->right==NULL){
            return root->data;
        }
        //case where left/lesser child exists
        else if(root->right != NULL){
            temp = findMaxRec(root->right);
        }
        return temp;
    }

    void sort(int* arr,int size, node* root,int* sortedarray){
        //This implementation of sort is destructive!
        //insert all ints from array
        fromArray(arr, size, root);
        //now make an array out of inorder traversal
        //int* newArray;
        for(int i = 0; i < size; i++){
            sortedarray[i] = findMinRec(this->root);
            deleteRec(findMinRec(this->root), this->root);
        }
        //return sortedarray;
    }

    void fromArray(int* array, int size, node* root){
        for(int i = 0; i < size; i++){
            insertRec(array[i], root);
        }
    }
    
};

binarySearchTree :: binarySearchTree(){
    //root = NULL;
}

int main(){
    binarySearchTree Poopy;
    /*int size = 7;
    int inputArray[size] = {5,3,7,2,4,6,9};
    int sortedArray[size];
    Poopy.sort(inputArray, size, Poopy.root,sortedArray);
    for(int i = 0; i < size; i++){
        cout << sortedArray[i] << endl;
    }*/
    /*
    Poopy.fromArray(inputArray, 7, Poopy.root);
    cout << Poopy.root->data << endl;
    cout << Poopy.root->right->data << endl;
    cout << Poopy.root->left->data << endl;
    cout << Poopy.root->right->right->data << endl;
    cout << "max is: " << Poopy.findMaxRec(Poopy.root) << endl;
    cout << "min is: " << Poopy.findMinRec(Poopy.root) << endl;
    Poopy.deleteRec(5,Poopy.root);
    cout << Poopy.root->data << endl;
    cout << Poopy.root->right->data << endl;
    cout << Poopy.root->left->data << endl;
    cout << Poopy.root->right->right->data << endl;
    cout << Poopy.findPrevRec(Poopy.root) << endl;
    cout << Poopy.findNextRec(Poopy.root) << endl;
    cout << Poopy.findNextRec(Poopy.root->right) << endl;*/

    int inputArray[10000];
    ifstream File;
    File.open("pumpkin.txt");

    int count;
    File >> count;

    for(int a = 0; a < 10000; a++){
        File >> inputArray[a];
    }
    /*for(int a = 0; a < 10; a++){
        cout << inputArray[a] << endl;;
    }*/
    Poopy.fromArray(inputArray, 10000, Poopy.root);
    cout << Poopy.root->data << endl;
    cout << Poopy.root->right->data << endl;
    cout << Poopy.root->left->data << endl;
}
