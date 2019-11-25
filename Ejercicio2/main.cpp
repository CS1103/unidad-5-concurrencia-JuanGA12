#include <iostream>
#include <thread>
#include <random>
#include <vector>

using namespace std;
random_device rd;

template<typename Container >
void imprimir(Container c){
    cout<<"Container: ";
    for(auto &it : c){
        cout << it << " ";
    }
    cout<<endl;
}

template<typename Container>
void incremento(Container& c, int n){
    for(auto& it : c){
        it += n;
    }
}

int main() {
    vector<int> vec1 = {1, 2, 3, 4, 5, 6};
    int num = rd() % 100;
    imprimir(vec1);

    cout << "Numero: "<<num<<endl;

    thread t1(incremento<vector<int>>, std::ref(vec1), num);
    t1.join();

    imprimir(vec1);
    return 0;
}
