#include <iostream>

using namespace std;

class Queue {
private:
    int size;
    int front, rear;
    int *Q;

public:
    Queue();

    Queue(int size);

    ~Queue();

    void Join(int data);

    int Leave();

    int Front();

    bool isEmpty();

    void Display();

};

Queue::Queue() {
    this->size = 5;
    front = rear = 0;
    Q = new int[this->size];
}

Queue::Queue(int size) {
    this->size = size;
    front = rear = 0;
    Q = new int[this->size];
}

Queue::~Queue() {

}

void Queue::Join(int data) {
    // check if the array is full
    // 条件是用%，如果(rear +1) % size == front, 那就是已经满了
    if ((rear + 1) % size == front)
        cout << "The queue is full. can't add more elements" << endl;
    else {
        // 如果没有满，那可以继续添加，添加到(rear + 1) % size 的地方，来达到circular的目的
        rear = (rear + 1) % size;
        // 把data插进queue
        Q[rear] = data;
    }
}

int Queue::Leave() {
    // 先检查array是不是已经空了
    // empty的条件是：front == rear 吗
    int returnData = -1;
    if (front == rear) {
        cout << "The queue is empty, will delete(and return) nothing." << endl;
    } else {
        // 如果不是空的，那么删除这个front元素
        // front也要执行circular，用%计算新的位置
        front = (front + 1) % size;
        returnData = Q[front];
    }
    return returnData;

}

int Queue::Front() {
    int x = -1;
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
    }
    else
    {
        x = Q[(front+1) %size];
    }
    return x;
    

}

bool Queue::isEmpty() {
    return (front == rear);
}

void Queue::Display() {
    // 是front +1，因为index front指向的array总是空的
    int i = front + 1;
    do {
        cout << Q[i] << " ";
        i = (i + 1) % size;
    }
        // 循环一直执行，直到到最后一个元素。
        // 最后一个元素的判断条件：
    while (i != ((rear + 1) % size));
    cout << endl;
}


int main() {
    Queue Q;
    Q.Join(10);
    Q.Join(20);
    Q.Join(30);
    Q.Join(40); // 只能加到这，因为default是5，但是总有一个空的不能用，就是front指向的那个array
    Q.Join(50);  // 失败
    Q.Join(60); // 失败
    Q.Display(); //10 20 30 40

    Q.Leave();
    Q.Display(); //20 30 40


}