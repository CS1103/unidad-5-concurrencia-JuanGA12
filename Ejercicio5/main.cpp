#include <iostream>
#include <vector>
#include <thread>


using namespace std;

template <typename Container>
void delete_item(Container& cnt, int num){
    cnt.erase(std::remove(cnt.begin(), cnt.end(),num),cnt.end());
}
template <typename Container>
void imprimir(Container& cnt){
    for(auto &i:cnt){
        cout<<i<<" ";
    }
}

int main() {

    vector<int> vec1 = {10,1,10,2,3,4,10,5,6,10,7,8,9,10};
    int n;
    cin>>n;
    thread t1([&vec1,&n]{
        delete_item(vec1,n);
    });
    t1.join();
    imprimir(vec1);
    return 0;
}