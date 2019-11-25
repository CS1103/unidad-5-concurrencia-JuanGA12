#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>



using namespace std;

mutex mutex1;
condition_variable cv;
int r = 0;
bool listo(){return r!=0;}

template <typename Container>
void mergeSort(Container &left, Container & right, Container & bars){
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) {
        if (left[j] < right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}
template <typename Container>
void sort(Container & bar) {
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    Container left;
    Container right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    thread t1([&left]{
        sort(left);
    });
    thread t2([&right]{
        sort(right);
    });
    t1.join();
    t2.join();

    mergeSort(left, right, bar);
}
template <typename Container>
void imprimir(Container& v){
    unique_lock<std::mutex> lock(mutex1);
    cv.wait(lock,listo);
    for(auto it : v){
        cout << it << ' ';
    }
}

int main() {
    vector<int> vec1 {35,74,1,585,2,68,0,12};

    thread tv([&vec1](){
        sort(vec1);
        r = 1;
        cv.notify_one();
    });

    thread tn([&vec1]{
        imprimir(vec1);
    });

    tv.join();
    tn.join();

    return 0;
}