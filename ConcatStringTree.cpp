#include "ConcatStringTree.h"
// ConcatStringTree
string reverseString(string str){
    int len = str.length();
    for(int i=0;i<len/2;i++){
        swap(str[i], str[len-i-1]);
    }
    return str;
}

int BTNode::idCount = 1;
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
        if(pRoot->data==""){
            result += ";(LL="+ LL + ",L="+ L +",<NULL>)" ;
        }
        else{
            result += ";(LL="+ LL + ",L="+ L +",\""+ pRoot->data +"\")" ;
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
    if(result!="")result.erase(result.begin());
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
}
string ConcatStringTree::toString()const{
    // "ConcatStringTree["Hello,_t"]"
    string getResult = "";
    toString_(pRoot, getResult);
    string result = "ConcatStringTree[\"" + getResult + "\"]";
    return result;
}
ConcatStringTree ConcatStringTree::concat(const ConcatStringTree & otherS)const{
    ConcatStringTree newNode = ConcatStringTree(this, &otherS);
    this->getRoot()->insertNode(newNode.getRoot());
    otherS.getRoot()->insertNode(newNode.getRoot());
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
    result.isSubRev = true;
    result.pRoot->isSubRev = true;
    // return ConcatStringTree(subString_(getRoot(), from, to));
    return result;
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
    result.isSubRev = true;
    result.pRoot->isSubRev = true;
    return result;
}

// Method for parentTree in ConcatStringTree
int ConcatStringTree::getParTreeSize(const string &query)const{
    BTNode *run = this->pRoot;
    for(int i=0;i<query.length();i++){
        if(query[i]=='l'){
            if(run->pLeft) run = run->pLeft;
            else throw runtime_error("Invalid query: reaching NULL");
        }
        else if(query[i]=='r'){
            if(run->pRight) run = run->pRight;
            else throw runtime_error("Invalid query: reaching NULL");
        }
    }
    return run->pTree->size();
}
string ConcatStringTree::getParTreeStringPreOrder(const string &query)const{
    BTNode *run = this->pRoot;
    for(int i=0;i<query.length();i++){
        if(query[i]=='l'){
            if(run->pLeft) run = run->pLeft;
            else throw runtime_error("Invalid query: reaching NULL");
        }
        else if(query[i]=='r'){
            if(run->pRight) run = run->pRight;
            else throw runtime_error("Invalid query: reaching NULL");
        }
    }
    return run->pTree->toStringPreOrder();
}
// Parent tree
// Rotate AVL
BTNode::ParentsTree::ParentNode* BTNode::ParentsTree::rotateLeft(ParentNode *newNode){
    ParentNode *x = newNode->pParentRight;
    ParentNode *xLeft = x->pParentLeft;
    x->pParentLeft = newNode;
    newNode->pParentRight = xLeft;
    newNode->height = max(newNode->pParentLeft?newNode->pParentLeft->height:0, newNode->pParentRight? newNode->pParentRight->height:0) + 1;
    x->height = max(x->pParentLeft?x->pParentLeft->height:0, x->pParentRight?x->pParentRight->height:0) + 1;
    return x;
    // return NULL;
}
BTNode::ParentsTree::ParentNode* BTNode::ParentsTree::rotateRight(ParentNode *newNode){
    ParentNode *x = newNode->pParentLeft;
    ParentNode *xRight = x->pParentRight;
    x->pParentRight = newNode;
    newNode->pParentLeft = xRight;
    x->height = max(x->pParentLeft?x->pParentLeft->height:0, x->pParentRight?x->pParentRight->height:0) + 1;
    newNode->height = max(newNode->pParentLeft?newNode->pParentLeft->height:0, newNode->pParentRight? newNode->pParentRight->height:0) + 1;
    return x;
    // return NULL;
}

int BTNode::ParentsTree::balanceFactor(ParentNode *temp){
    if(!temp) return 0;
    int heightLeft = 0, heightRight = 0;
    if (temp->pParentLeft) heightLeft = temp->pParentLeft->height;
    if (temp->pParentRight) heightRight = temp->pParentRight->height;
    return heightLeft - heightRight;
}

int BTNode::ParentsTree::size() const{
    return this->sizeTree;
}

void BTNode::ParentsTree::toStringPreOrder_(ParentNode *pRoot, string &current)const {
    if(pRoot){
        //(id=1);(id=3)
        current += ";(id="+to_string(pRoot->id)+")";
        toStringPreOrder_(pRoot->pParentLeft, current);
        toStringPreOrder_(pRoot->pParentRight, current);
    }
}

string BTNode::ParentsTree::toStringPreOrder() const{
    string result = "";
    toStringPreOrder_(this->pRoot, result);
    if(result!="") result.erase(result.begin());
    return "ParentsTree["+ result +"]";
}
BTNode::ParentsTree::ParentNode* BTNode::ParentsTree::insert_(ParentNode *pRoot, ParentNode *newNode){
    if(pRoot==NULL){
        return newNode;
    }
    else{
        if(newNode->id < pRoot->id){
            pRoot->pParentLeft = insert_(pRoot->pParentLeft, newNode);
        }
        else if( newNode->id > pRoot->id){
            pRoot->pParentRight = insert_(pRoot->pParentRight, newNode);
        }
        else return pRoot;
    }
    pRoot->height = 1 + max(pRoot->pParentLeft? pRoot->pParentLeft->height:0, pRoot->pParentRight? pRoot->pParentRight->height:0);
    int bF = balanceFactor(pRoot);
    //Left left case
    if(bF > 1 && newNode->id < pRoot->pParentLeft->id){
        pRoot = rotateRight(pRoot);
    }
    //right right case
    if(bF < -1 && newNode->id>pRoot->pParentRight->id){
        pRoot = rotateLeft(pRoot);
    }
    //right left case
    if(bF < -1 && newNode->id < pRoot->pParentRight->id){
        pRoot->pParentRight = rotateRight(pRoot->pParentRight);
        pRoot = rotateLeft (pRoot);
    }
    // left right case
    if(bF >1 && newNode->id > pRoot->pParentLeft->id){
        pRoot->pParentLeft = rotateLeft(pRoot->pParentLeft);
        pRoot = rotateRight(pRoot);
    }
    return pRoot;
}

void BTNode::ParentsTree::insert(BTNode *temp){
    ParentNode *newNode = new ParentNode(temp);
    this->pRoot = insert_(this->pRoot, newNode);
    this->sizeTree++;
}
BTNode::ParentsTree::ParentNode* BTNode::ParentsTree::maxNodeLeft_(ParentNode *pRoot){
    if(!pRoot) return 0;
    if(!pRoot->pParentLeft&&!pRoot->pParentRight) return pRoot;
    ParentNode *maxLeft = maxNodeLeft_(pRoot->pParentLeft);
    ParentNode *maxRight = maxNodeLeft_(pRoot->pParentRight);
    int left = maxLeft ? maxLeft->id: 0;
    int right = maxRight ? maxRight->id:0;
    if(left>right) return maxLeft;
    else return maxRight;
}

BTNode::ParentsTree::ParentNode* BTNode::ParentsTree::deleteNode_(ParentNode *pRoot, int id){
    if(pRoot){
        if(id<pRoot->id){
            pRoot->pParentLeft = deleteNode_(pRoot->pParentLeft, id);
        }
        else if(id>pRoot->id){
            pRoot->pParentRight = deleteNode_(pRoot->pParentRight, id);
        }
        else{
            //1. No child
            if(!pRoot->pParentLeft&&!pRoot->pParentRight){
                delete pRoot;
                pRoot = NULL;
            }
            //2. Only one child
            else if(!pRoot->pParentLeft||!pRoot->pParentRight){
                ParentNode *temp = pRoot->pParentLeft? pRoot->pParentLeft: pRoot->pParentRight;
                delete pRoot;
                pRoot = temp;
            }
            //3. Two child
            else if(pRoot->pParentLeft && pRoot->pParentRight){
                ParentNode *temp = maxNodeLeft_(pRoot->pParentLeft);
                pRoot->id = temp->id;
                // delete pRoot->pParent;
                pRoot->pParent = temp->pParent;
                pRoot->pParentLeft = deleteNode_(pRoot->pParentLeft, temp->id);
            }
        }
    }
    if(pRoot==NULL) return pRoot;
    pRoot->height = 1 + max((pRoot->pParentLeft? pRoot->pParentLeft->height:0), (pRoot->pParentRight? pRoot->pParentRight->height:0));
    int bF = balanceFactor(pRoot);
    //1. LL case
    if(bF>1&&balanceFactor(pRoot->pParentLeft)>=0){
        pRoot = rotateRight(pRoot);
    }
    //2. LR case
    if(bF>1&&balanceFactor(pRoot->pParentLeft)<0){
        pRoot->pParentLeft = rotateLeft(pRoot->pParentLeft);
        pRoot = rotateRight(pRoot);
    }
    //3. RR case
    if(bF< -1 && balanceFactor(pRoot->pParentRight)<=0){
        pRoot = rotateLeft(pRoot);
    }
    //4. RL case
    if(bF< -1 && balanceFactor(pRoot->pParentRight)>0){
        pRoot->pParentRight = rotateRight(pRoot->pParentRight);
        pRoot = rotateLeft(pRoot);
    }
    return pRoot;
}
void BTNode::ParentsTree::deleteNode(BTNode *temp){
    this->pRoot = deleteNode_(this->pRoot, temp->id);
    this->sizeTree--;
}

bool BTNode::ParentsTree::isEmpty()const{
    return this->sizeTree == 0;
}

//ReducedConcatStringTree
ReducedConcatStringTree::ReducedConcatStringTree(const char *s, LitStringHash *litStringHash){
    this->litStringHash = litStringHash;
    int mapSize = litStringHash->currentSize;
    this->copyMap = litStringHash->litStringHashMap;
    this->mapSize = mapSize;
    int index = this->litStringHash->addLitString(s);
    string getString = this->litStringHash->litStringHashMap[index].litStringData;
    this->pRoot = new BTNode(getString);
}
ReducedConcatStringTree::ReducedConcatStringTree(const ReducedConcatStringTree *pLeftString, const ReducedConcatStringTree *pRightString){
    this->pRoot = new BTNode ("", (pLeftString? pLeftString->getRoot(): NULL), (pRightString? pRightString->getRoot(): NULL));
}
ReducedConcatStringTree ReducedConcatStringTree::concat(const ReducedConcatStringTree &otherS)const {
    ReducedConcatStringTree newNode = ReducedConcatStringTree(this, &otherS);
    this->getRoot()->insertNode(newNode.getRoot());
    otherS.getRoot()->insertNode(newNode.getRoot());
    return newNode;
}
void ReducedConcatStringTree::removeLitString(bool deleteHash){
    int count = 0;
    for(int i=0;i<this->mapSize;i++){
        if(this->copyMap[i].litStringData!=""){
            count++;
        }
        if(this->copyMap[i].litStringData==this->pRoot->data){
            this->copyMap[i].pointedCount--;
            if(this->copyMap[i].pointedCount==0){
                this->copyMap[i].litStringData="";
                count--;
            }
            
        }
    }
    // cout<<deleteHash<<endl;
    if(count == 0&&deleteHash){
        delete[] this->copyMap;
    }
}
//HashConfig
HashConfig::HashConfig(){
    this->p = 0;
    this->c1 = 0;
    this->c2 = 0;
    this->lambda = 0;
    this->alpha = 0;
    this->initSize = 0;
}
HashConfig::HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize){
    this->p = p;
    this->c1 = c1;
    this->c2 = c2;
    this->lambda = lambda;
    this->alpha = alpha;
    this->initSize = initSize;
}
//LitStringHash
LitStringHash::LitStringHash(const HashConfig & hashConfig){
    this->data = hashConfig;
    this->litStringHashMap = new LitString[this->data.initSize];
    this->currentSize = this->data.initSize;
    this->lastElement = -1;
}
int LitStringHash::getLastInsertedIndex() const{ // O(1)
    return this->lastElement;
}
string LitStringHash::toString() const{
    string result = "LitStringHash[";
    for(int i=0;i<this->currentSize;i++){
        result += "(";
        if(this->litStringHashMap[i].litStringData!=""){
            result += "litS=\"";
            result += litStringHashMap[i].litStringData;
            result += "\"";
        }
        result += ");";
        // cout<<this->litStringHashMap[i].pointedCount<<endl;
    }
    if(result[result.length()-1]==';') result.erase(result.end()-1);
    result+="]";
    return result;
}
void LitStringHash::checkReHash(){
    int countElement = 0;
    for(int i=0;i<this->currentSize;i++){
        if(this->litStringHashMap[i].litStringData!=""){
            countElement++;
        }
    }
    double loadFactor = countElement/this->currentSize;
    if(loadFactor>this->data.lambda) {
        reHashing();
    }
}
void LitStringHash::reHashing(){
    // cout<<"rehashing"<<endl;
    int newSize = (int)(this->data.alpha * this->currentSize);
    LitString *litStringRehashMap = new LitString[newSize];
    for(int i=0;i<this->currentSize;i++){
        this->litStringHashMap[i] = litStringRehashMap[i];
    }
    delete[] this->litStringHashMap;
    this->litStringHashMap = litStringRehashMap;
    this->currentSize = newSize;
}
int LitStringHash::addLitString(string litData){
    for(int i=0;i<this->currentSize;i++){
        if(this->litStringHashMap[i].litStringData==litData){
            this->litStringHashMap[i].pointedCount++;
            return i;
        }
    }
    LitString newLitString = LitString(litData);
    int indexNewLitString = newLitString.getHashIndex(this->data, this->litStringHashMap);
    this->litStringHashMap[indexNewLitString] = newLitString;
    if(this->lastElement<indexNewLitString) this->lastElement = indexNewLitString;
    checkReHash();// check to renew hashmap
    return indexNewLitString;
}
void LitStringHash::removeLitString(string litData){
    for(int i=0;i<this->currentSize;i++){
        if(this->litStringHashMap[i].litStringData==litData){
            this->litStringHashMap[i].pointedCount--;
            if(this->litStringHashMap[i].pointedCount==0){
                this->litStringHashMap[i].litStringData="";
            }
            //redefine lastElement
            if(i==this->lastElement){
                this->lastElement = -1;
                for(int i=0;i<this->currentSize;i++){
                    if(this->litStringHashMap[i].litStringData!=""){
                        this->lastElement = i;
                    }
                }
            }
            // if(this->lastElement==-1){
            //     delete []litStringHashMap;
            // }
            break;
        }
    }
}

int pow (int a, int b){
    if(a==0) return 0;
    int res = 1;
    for(int i=1;i<=b;i++){
        res *= a;
    }
    return res;
}

int LitStringHash::LitString::getHashIndex(HashConfig dataConfig, LitString *litStringHashMap){
    string data = this->litStringData;
    int dataLength = data.length();
    int index = 0;
    for(int i=0;i<dataLength;i++){
        index += static_cast<int>(data[i])*pow(dataConfig.p, i);
    }
    index %= dataConfig.initSize;
    // Search function
    // bool foundIndex = true;
    for(int i=0;i<dataConfig.initSize;i++){
        int probingIndex = (index + (int)dataConfig.c1*i % dataConfig.initSize + 
                                    (int) dataConfig.c2*pow(i, 2) %dataConfig.initSize) 
                            %dataConfig.initSize;
        if(litStringHashMap[probingIndex].litStringData == ""){
            return probingIndex;
        }
    }
    throw runtime_error("No possible slot");
}