#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"
class BTNode {
private:
    string data;
    BTNode *pLeft;
    BTNode *pRight;
    int length;
    int key;
    friend class ConcatStringTree;
public:
    BTNode(string data = "", BTNode* pLeft = NULL, BTNode* pRight = NULL){
        this->data = data;
        this->pLeft = pLeft;
        this->pRight = pRight;
        this->key = (pLeft ? pLeft -> length : 0);
        this->length = data.length();
        if(data.length()==0){
            this->length = pLeft->length+pRight->length;
        }
    }
    ~BTNode(){};
};


class ConcatStringTree {
private:
    BTNode *pRoot;
    char get_(int index, BTNode *pRoot) const;
    int indexOf_(char c, BTNode *pRoot, int count) const;
    string toStringPreOrder_(BTNode *pRoot) const;
    void toString_(BTNode *pRoot, string &current)const;
public:
    BTNode *getRoot()const;
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
        cout<< pRoot->key<<" is deleted"<<endl;
        delete pRoot; //?
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
};

class LitStringHash {
public:
    LitStringHash(const HashConfig & hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;
};

class ReducedConcatStringTree /* */ {
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    LitStringHash * litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__