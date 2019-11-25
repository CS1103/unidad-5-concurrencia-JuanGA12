#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

struct node{
    int val;
    node* next;
};


class linkedList{
private:
    node nodo;
    node* head;
    node* tail;
    std::mutex mutex;
public:
    linkedList(){head = nullptr; tail = nullptr;}

    void push_back(int value){
        std::lock_guard<std::mutex> lock(mutex);
        if(head == nullptr){
            node* newNode = new node();
            newNode -> val = value;
            newNode -> next = head;
            head = newNode;
            tail = newNode;
        }
        else{
            node* newNode = new node();
            newNode -> val = value;
            newNode -> next = head;
            head = newNode;
        }
    }

    void pop_back(){
        node* temp = new node();
        temp = head;
        head = temp->next;
        delete temp;
    }

    void print(){
        node* temp = new node();
        temp = head;
        while(temp != nullptr){
            cout << temp->val << ' ';
            temp = temp->next;
        }
    }

};


int main(){
    linkedList l1;
    thread t1([&l1]{
        l1.push_back(5);
    });
    thread t2([&l1]{
        l1.push_back(10);
    });
    thread t3([&l1]{
        l1.push_back(15);
    });
    thread t4([&l1]{
        l1.push_back(20);
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    l1.print();



    return 0;
}
/*thread t1([&l1]{
    l1.push_back(5);
});
thread t2([&l1]{
    l1.push_back(10);
});
thread t3([&l1]{
    l1.push_back(15);
});
thread t4([&l1]{
    l1.push_back(20);
});*/