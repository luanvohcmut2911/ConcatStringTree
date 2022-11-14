#include "ConcatStringTree.h"
// ConcatStringTree
BTNode* ConcatStringTree::getRoot()const{
    return pRoot;
}
ConcatStringTree::ConcatStringTree(const char *s){
    string data = string(s);
    this->pRoot = new BTNode (data);
}
ConcatStringTree::ConcatStringTree(const ConcatStringTree *pLeftString,const ConcatStringTree *pRightString){
    this->pRoot = new BTNode ("", pLeftString->getRoot(), pRightString->getRoot());
}
int ConcatStringTree::length() const{
    return pRoot->length;
}
char ConcatStringTree::get_(int index, BTNode *pRoot)const{
    // assume full binary tree
    char result;
    if(!pRoot->pLeft && !pRoot->pRight) result = pRoot->data[index];
    else{
        if(!pRoot->pLeft){
            result = get_(index, pRoot->pRight);
        }
        else if(index>=pRoot->pLeft->length){
            result = get_(index-pRoot->pLeft->length, pRoot->pRight);
        }
        else{

            result = get_(index, pRoot->pLeft);
        }
    }
    return result;
}

char ConcatStringTree::get(int index) const{
    if(index < 0|| index >= pRoot->length){
        throw out_of_range("Index of string is invalid!");
    }
    else{
        return get_(index, pRoot);
    }
}
int ConcatStringTree::indexOf_(char c, BTNode *pRoot, int count)const{

    if(pRoot->data==""){
        int findLeft = indexOf_(c, pRoot->pLeft, count);
        int findRight = indexOf_(c, pRoot->pRight,count + pRoot->pLeft->length);
        return (findLeft != -1 ? findLeft : findRight);
    }
    else{
        string data = pRoot->data;
        for(int i=0;i<data.length();i++){
            if(data[i]==c){
                return count + i;
            }
        }
        return -1;
    }
}
int ConcatStringTree::indexOf(char c) const{
    return indexOf_(c, pRoot, 0);
}
string ConcatStringTree::toStringPreOrder_(BTNode* pRoot)const{
    // (LL=5,L=8,<NULL>)
    string LL = to_string(pRoot->key);
    string L = to_string(pRoot->length);
    string result;
    if(pRoot->data==""){
        result = "(LL="+ LL + ",L="+ L +",<NULL>)" ;
    }
    else{
        result = "(LL="+ LL + ",L="+ L +",\""+ pRoot->data +"\")" ;
    }
    if(!pRoot->pLeft && !pRoot->pRight) return result;
    result += ";" + toStringPreOrder_(pRoot->pLeft) + ";" + toStringPreOrder_(pRoot->pRight);
    return result;
}
string ConcatStringTree::toStringPreOrder()const{
    string result = "ConcatStringTree["+toStringPreOrder_(pRoot) + "]";
    return result;
}

void ConcatStringTree::toString_(BTNode *pRoot, string &current)const{
    if(pRoot->data==""){
        toString_(pRoot->pLeft, current);
        toString_(pRoot->pRight, current);
    }
    else{
        current += pRoot->data;
    }
    // return current;
}
string ConcatStringTree::toString()const{
    // "ConcatStringTree["Hello,_t"]"
    string getResult = "";
    toString_(pRoot, getResult);
    string result = "ConcatStringTree[\"" + getResult + "\"]";
    return result;
}
ConcatStringTree ConcatStringTree::concat(const ConcatStringTree & others)const{
    ConcatStringTree newNode = ConcatStringTree(this, &others);
    return newNode;
}
ConcatStringTree ConcatStringTree::subString(int from, int to)const{
    //include from, not to
    if(from < 0||to>= pRoot -> length){
        throw out_of_range("Index of string is invalid");
    }
    else if(from >= to){
        throw logic_error("Invalid range");
    }
    return NULL;
}
ConcatStringTree ConcatStringTree::reverse()const{
    return NULL;
}
//ReducedConcatStringTree
ReducedConcatStringTree::ReducedConcatStringTree(const char *s, LitStringHash *litStringHash){

}

//HashConfig

//LitStringHash
LitStringHash::LitStringHash(const HashConfig & hashConfig){
    
}
int LitStringHash::getLastInsertedIndex() const{
    return 1;
}
string LitStringHash::toString() const{
    return "";
}