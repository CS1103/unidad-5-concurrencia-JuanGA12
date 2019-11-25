#include <iostream>
#include <vector>
#include <random>
#include <thread>

using namespace std;

template <typename Container>
void generar(Container & cnt, int cantidad){
    int numerador = 2;
    int denominador;
    bool primo;

    for(;cantidad > 0;){
        primo = true;
        for (denominador = 2; denominador < numerador; ++denominador) {
            if (numerador % denominador == 0) {
                primo = !primo;
                break;
            }
        }

        if (primo){
            cnt.push_back(numerador);
            cantidad--;
        }
        numerador++;
    }
}
template <typename Container>
void imprimir(Container & cnt){
    for(auto &it:cnt){
        cout << it <<" ";
    }

}
int main() {
    vector<int> vec1;
    int cantidad;
    cin>>cantidad;
    thread t1([&vec1, &cantidad]{
        generar(vec1,cantidad);
    });
    t1.join();
    thread t2([&vec1]{
        imprimir(vec1);
    });
    t2.join();

    return 0;
}