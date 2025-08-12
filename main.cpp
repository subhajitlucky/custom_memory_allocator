#include <iostream>
using namespace std;

int main(){
    //single int on heap
    int* hp = new int(123);
    cout<<"heap int = "<<*hp<<" at "<<static_cast<const void*>(hp)<<endl;
    delete hp;
    hp = nullptr;

    //array on the heap
    int* arr = new int[5] {5,4,3,2,1};
    for(int i = 0;i<5;++i){
        cout<<"arr["<<i<<"] = "<<*(arr+i)<<endl;
    }

    delete[] arr;
    arr = nullptr;
    return 0;

}