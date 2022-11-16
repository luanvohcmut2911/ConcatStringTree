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

void tc05(){
    ConcatStringTree *s1 = new ConcatStringTree("Hello");
    ConcatStringTree *s2 = new ConcatStringTree(",_this");
    ConcatStringTree *s3 = new ConcatStringTree(s1->concat(*s2));
    ConcatStringTree *s4 = new ConcatStringTree("_is_zero");
    ConcatStringTree *s5 = new ConcatStringTree(s3->concat(*s4));
    // delete s5;
    // delete s3;
    // delete s4;
    // delete s2;
    // delete s1;
    delete s1;
    s1=NULL;
    cout<<s5->toString()<<endl;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
}

void tc1(){
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

void tc2(){
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_t");
    ConcatStringTree s3 = s1.concat(s2);
    cout << s1.toStringPreOrder() << endl;
    cout << s3.toStringPreOrder() << endl;
    cout << s3.toString() << endl;
    cout << s3.subString(1, 7).toStringPreOrder() << endl;
    cout << s3.reverse().toString() << endl;
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

int main() {
    // tc0();
    // tc1();
    // tc2();
    tc3();
    return 0;
}