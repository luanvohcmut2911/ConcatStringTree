#include "ConcatStringTree.h"

void tc0(){
    ConcatStringTree s1("Hello");
    cout << s1.get(1)<<endl;
    ConcatStringTree s2(",_this");
    ConcatStringTree s3 = s1.concat(s2);
    cout << s3.length()<<endl;
    cout << s3.indexOf('t')<<endl;
    ConcatStringTree s4("_is_zero");
    ConcatStringTree s5 = s3.concat(s4);
    cout<< s5.indexOf('m')<<endl;
    cout<<s5.toStringPreOrder()<<endl;
    cout<<s5.toString()<<endl;
}

void tc3(){
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_this");
    ConcatStringTree s3 = s1.concat(s2);
    ConcatStringTree s4("_is_zero");
    ConcatStringTree s5 = s3.concat(s4);
    cout<<s5.subString(5,10).toStringPreOrder()<<endl;
    cout<<s5.subString(5,10).toString()<<endl;
    cout<<s5.subString(5,10).reverse().toStringPreOrder()<<endl;
}
// test case BKEL
void tc21(){	
    ConcatStringTree s1("acbbcab");
    cout << s1.length() << endl;
    cout << s1.get(1) << endl;
    try {
        cout << "char at index 10: " << s1.get(10) << endl;
    }
    catch (const out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    cout << s1.indexOf('b') << endl;
}
void tc22(){
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_t");
    ConcatStringTree s3 = s1.concat(s2);
    cout << s3.toStringPreOrder() << endl;
    cout << s3.toString() << endl;
    cout << s3.subString(5, 6).toString() << endl;
    cout << s3.reverse().toString() << endl;
}
void tc23(){
	
    ConcatStringTree * s1 = new ConcatStringTree("a");
    ConcatStringTree * s2 = new ConcatStringTree("b");
    ConcatStringTree * s3 = new ConcatStringTree("c");
    ConcatStringTree * s4 = new ConcatStringTree(s1->concat(*s2));
    ConcatStringTree * s5 = new ConcatStringTree(s1->concat(*s3));
    ConcatStringTree * s6 = new ConcatStringTree("1234");
    ConcatStringTree * s7 = new ConcatStringTree("5678");
    ConcatStringTree * s8 = new ConcatStringTree(s6->concat(*s7));

    cout << s8->getParTreeSize("l") << endl;
    cout << s8->getParTreeStringPreOrder("l") << endl;
    cout << s4->getParTreeSize("l") << endl;
    cout << s4->getParTreeStringPreOrder("l") << endl;

    delete s2;
    delete s4;
    delete s3;
    delete s1;
    delete s5;
    delete s6;
    delete s7;
    delete s8;
}
/*
Expected output:
    2
    ParentsTree[(id=1);(id=3)]
*/
void tc24(){
    HashConfig hashConfig(
        2, //p
        0.5, //c1
        0.5, //c2
        0.75, //lambda
        2, //alpha
        4 //initSize
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);
    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    ReducedConcatStringTree * s3 = new ReducedConcatStringTree("bb", litStringHash);

    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;

    delete litStringHash;
    delete s2;
    delete s1;
    delete s3;
}
/*
Expected output:
    ConcatStringTree["a"]
    ConcatStringTree["bb"]
    2
    LitStringHash[();(litS="a");(litS="bb");()]
*/
void tc25(){
    ConcatStringTree s1("Hello");
    cout << "Please focus to id: " << s1.getParTreeStringPreOrder("") << endl;
    ConcatStringTree s2("an-nyeong-ha-se-yo");
    cout << "Please focus to id: " << s2.getParTreeStringPreOrder("") << endl;
    ConcatStringTree s3("nee how");
    cout << "Please focus to id: " << s3.getParTreeStringPreOrder("") << endl;
}//pass
/*
Expected output:
    Please focus to id: ParentsTree[(id=1)]
    Please focus to id: ParentsTree[(id=2)]
    Please focus to id: ParentsTree[(id=3)]
*/
// end test
int main() {
    // tc0();
    // tc1();
    // tc2();
    // tc21();
    // tc22();
    // tc23();
    tc24();
    // tc25();
    return 0;
}