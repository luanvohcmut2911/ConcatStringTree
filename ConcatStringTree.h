#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"
class BTNode {
protected:
    static int idCount; // declare id for every BTNode
protected:
    class ParentsTree{// AVL tree
    private:
        class ParentNode{
        public:
            int id;
            BTNode *pParent;
            ParentNode *pParentLeft;
            ParentNode *pParentRight;
            int height = 0; 
        public:
            ParentNode(BTNode* pParent){
                this->id = pParent->id;
                this->pParent = pParent;
                this->pParentLeft = NULL;
                this->pParentRight = NULL;
                this->height = 1;
            }
            ~ParentNode(){

            }
        };
    private:
        ParentNode *pRoot;
        int sizeTree;
        void toStringPreOrder_(ParentNode *pRoot, string &current) const;
        ParentNode* insert_(ParentNode *pRoot, ParentNode *newNode);
        ParentNode* rotateRight (ParentNode *newNode);
        ParentNode* rotateLeft (ParentNode *newNode);
        int balanceFactor(ParentNode *temp);
        ParentNode* deleteNode_(ParentNode *pRoot, int id);
        ParentNode* maxNodeLeft_(ParentNode *pRoot);
    public:
        ParentsTree(BTNode *pRoot = NULL){
            this->pRoot = new ParentNode(pRoot);//leak
            // if(pRoot) this->sizeTree = 1;
            // else this->sizeTree = 0;
            this->sizeTree = 1;
        }
        void insert(BTNode *temp);//
        void deleteNode(BTNode *temp);
        int size() const;
        string toStringPreOrder() const;
        bool isEmpty()const;
        ~ParentsTree(){
            delete this->pRoot;
        }
    };
protected:
    int id; // use for ParentTree
    string data;
    BTNode *pLeft;
    BTNode *pRight;
    int length;
    int key;
    //
    friend class ConcatStringTree;
public:
    ParentsTree *pTree;
public:
    BTNode(string data = "", BTNode* pLeft = NULL, BTNode* pRight = NULL){
        if(idCount>10000000) throw overflow_error("Id is overflow!");
        this->data = data;
        this->pLeft = pLeft;
        this->pRight = pRight;
        this->key = (pLeft ? pLeft -> length : 0);
        this->length = data.length();
        if(data.length()==0){
            this->length = (pLeft? pLeft->length:0)+(pRight? pRight->length:0);
        }
        this->id = idCount;
        idCount++;
        pTree = new ParentsTree(this);//leak
        // pTree->insert(this);
    }
    void insertNode(BTNode *newNode){
        this->pTree->insert(newNode);
    }
    void deleteNode(BTNode *newNode){
        this->pTree->deleteNode(newNode);
    }
    // int getParentTreeSize()const;
    ~BTNode(){
        if(this->pLeft) {
            this->pLeft->pTree->deleteNode(this); 
        }
        if(this->pRight) {
            this->pRight->pTree->deleteNode(this);
        }
        
    };
};


class ConcatStringTree {
protected:
    BTNode *pRoot;
protected:
    char get_(int index, BTNode *pRoot) const;
    int indexOf_(char c, BTNode *pRoot, int count) const;
    void toStringPreOrder_(BTNode *pRoot, string &result) const;
    void toString_(BTNode *pRoot, string &current)const;
    BTNode* subString_(BTNode *pRoot, int from, int to)const;
    BTNode* reverse_(BTNode *pRoot)const;
public:
    BTNode *getRoot()const;
    ConcatStringTree(){
        this->pRoot=NULL;
    }
    ConcatStringTree(BTNode *pRoot);
    ConcatStringTree(const char * s);
    ConcatStringTree(const ConcatStringTree *pLeftString, const ConcatStringTree *pRightString);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;

    
    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;
    ~ConcatStringTree(){
        if(this->pRoot->pTree->isEmpty()){
            delete pRoot->pTree;
            delete pRoot;
        }
    }
};

class ReducedConcatStringTree; // forward declaration

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
    friend class LitStringHash;
public:
    HashConfig(int p, double c1, double c2, double lambda, int alpha, int initSize);
};

class LitStringHash {
public:
    LitStringHash(const HashConfig & hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;
};

class ReducedConcatStringTree: public ConcatStringTree{
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    LitStringHash * litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__