#include "ConcatStringTree.h"
// ConcatStringTree
string reverseString(string str){
    int len = str.length();
    for(int i=0;i<len/2;i++){
        swap(str[i], str[len-i-1]);
    }
    return str;
}


BTNode* ConcatStringTree::getRoot()const{
    return pRoot;
}
ConcatStringTree::ConcatStringTree(BTNode *pRoot){
    this->pRoot = pRoot;
}
ConcatStringTree::ConcatStringTree(const char *s){
    string data = string(s);
    this->pRoot = new BTNode (data);
}
ConcatStringTree::ConcatStringTree(const ConcatStringTree *pLeftString,const ConcatStringTree *pRightString){
    this->pRoot = new BTNode ("", (pLeftString? pLeftString->getRoot(): NULL), (pRightString? pRightString->getRoot(): NULL));
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
void ConcatStringTree::toStringPreOrder_(BTNode* pRoot, string &result)const{
    // (LL=5,L=8,<NULL>)
    if(pRoot){
        string LL = to_string(pRoot->key);
        string L = to_string(pRoot->length);
        // string result;
        if(pRoot->data==""){
            result += "(LL="+ LL + ",L="+ L +",<NULL>);" ;
        }
        else{
            result += "(LL="+ LL + ",L="+ L +",\""+ pRoot->data +"\");" ;
        }
        if(pRoot->pLeft || pRoot->pRight){
            toStringPreOrder_(pRoot->pLeft, result);
            toStringPreOrder_(pRoot->pRight, result);
        }
        
    }
}
string ConcatStringTree::toStringPreOrder()const{
    string result = "";
    toStringPreOrder_(pRoot, result);
    string resultFull = "ConcatStringTree["+ result + "]";
    return resultFull;
}

void ConcatStringTree::toString_(BTNode *pRoot, string &current)const{
    if(pRoot!=NULL){
        if(pRoot->data==""){
            toString_(pRoot->pLeft, current);
            toString_(pRoot->pRight, current);
        }
        else{
            current += pRoot->data;
        }
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

BTNode* ConcatStringTree::subString_(BTNode *pRoot, int from, int to) const{
    if(pRoot->length<from||to<=0){
        return NULL;
    }
    else if(!pRoot->pLeft&&!pRoot->pRight){
        return new BTNode(pRoot->data.substr(from, to-from).c_str());
    }
    BTNode* pLeftNode =  subString_(pRoot->pLeft, from, min(to, pRoot->pLeft->length));
    BTNode* pRightNode = subString_(pRoot->pRight, 0, to - pRoot->pLeft->length);
    BTNode *newNode = new BTNode("",pLeftNode, pRightNode);
    return newNode;
}//leak
ConcatStringTree ConcatStringTree::subString(int from, int to)const{
    if(from < 0||to>= pRoot -> length){
        throw out_of_range("Index of string is invalid");
    }
    else if(from >= to){
        throw logic_error("Invalid range");
    }
    ConcatStringTree result = ConcatStringTree(subString_(getRoot(), from, to));
    return ConcatStringTree(subString_(getRoot(), from, to));
}

BTNode* ConcatStringTree::reverse_(BTNode *pRoot)const{
    if(pRoot==NULL) return NULL;
    if(!pRoot->pLeft&&!pRoot->pRight){
        return new BTNode(reverseString(pRoot->data).c_str());
    }
    BTNode *pNodeLeft = reverse_(pRoot->pRight);
    BTNode *pNodeRight = reverse_(pRoot->pLeft);
    BTNode *newNode = new BTNode("", pNodeLeft, pNodeRight);
    return newNode;
}//leak
ConcatStringTree ConcatStringTree::reverse()const{
    ConcatStringTree result = ConcatStringTree(reverse_(getRoot()));
    return result;
}

// Method for parentTree in ConcatStringTree
int ConcatStringTree::getParTreeSize(const string &query)const{
    return 1;
}
string ConcatStringTree::getParTreeStringPreOrder(const string &query)const{
    return "";
}
// Parent tree
int ConcatStringTree::ParentTree::size() const{
    return 1;
}
string ConcatStringTree::ParentTree::toStringPreOrder() const{
    return "";
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