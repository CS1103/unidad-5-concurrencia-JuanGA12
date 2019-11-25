#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

using namespace std;

mutex mutex1;

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

int main(){
    int arr[] = { 2, 3, 4, 10, 40 };
    int n = sizeof(arr) / sizeof(arr[0]);
    vector<thread> workers;
    for(int i = 0; i <thread::hardware_concurrency();	i++){
        workers.emplace_back(thread([&](){
            mutex1.lock();
            int result = binarySearch(arr,0,n-1,i);
            (result == -1) ? cout << "Element is not present in array"<<endl
                           : cout << "Element is present at index: "<< result<<endl;
            mutex1.unlock();
        }));
    }
    for_each(workers.begin(),workers.end(),[](thread & th){
        th.join();
    });
    return 0;
}