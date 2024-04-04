#include <iostream>

using namespace std;

// This node is for a tree node
class Node {
public:
    Node *lchild, *rchild;
    int data;
};


class Queue {
private:
    int size;
    int front, rear;
    // // This is an array address for integer
    //int *Q;

    // Now for creating a BT, we need to change the value type
    Node **Q; // should store an address of a tree, so

public:
    Queue();

    Queue(int size);

    ~Queue();

    void Join(Node *node);

    Node *Leave();

    Node *Front();

    bool isEmpty();

    void Display();

};

Queue::Queue() {
    this->size = 5;
    front = rear = 0;
    //Q = new int[this->size];
    Q = new Node *[this->size];
}

Queue::Queue(int size) {
    this->size = size;
    front = rear = 0;
//    Q = new int[this->size];
    Q = new Node *[size];
}

Queue::~Queue() {

}

// change int to Node
void Queue::Join(Node *p) {
    // check if the array is full
    // 条件是用%，如果(rear +1) % size == front, 那就是已经满了
    if ((rear + 1) % size == front)
        cout << "The queue is full. can't add more elements" << endl;
    else {
        // 如果没有满，那可以继续添加，添加到(rear + 1) % size 的地方，来达到circular的目的
        rear = (rear + 1) % size;
        // 把data插进queue
//        Q[rear] = data;
        Q[rear] = p;
    }
}

Node *Queue::Leave() {
    // 先检查array是不是已经空了
    // empty的条件是：front == rear 吗
    Node *temp = NULL;
    if (isEmpty()) {
        cout << "The queue is empty, will delete(and return) nothing." << endl;
    } else {
        // 如果不是空的，那么删除这个front元素
        // front也要执行circular，用%计算新的位置
        front = (front + 1) % size;
        temp = Q[front];
    }
    return temp;
}

Node *Queue::Front() {
    Node *p = NULL;
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
    } else {
        p = Q[(front + 1) % size];
    }
    return p;


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


// class Tree
class Tree {
private:
    Node *root;

public:
    Tree() { root = NULL; }

    void CreateTree();

    // overloading ==> non-parameter Pre_order() will call the one with the parameter.
    // just can do it in a recursive way.
    // Also, root can be private now. ==> encapsulation
    void Pre_order() { Pre_order(this->root); }

    void Pre_order(Node *p);

    void Post_order() { Post_order(this->root); }

    void Post_order(Node *p);

    void In_order() { In_order(this->root); }

    void In_order(Node *p);

    void Level_order(Node *p);

    int Height(Node *p);
};

void Tree::CreateTree() {
    Node *p, *t;
    int x;
    Queue q(10);
    cout << "Enter root value " << endl;
    string input;
    getline(cin, input);
    int int_input = stoi(input);// convert String => integer
    // allocate memory to root from heap
    this->root = new Node;
    root->data = int_input;
    root->lchild = root->rchild = NULL;
    // push the root to Queue for the further using
    // this step is an initialise step to create a tree
    q.Join(root);

    // the following steps are repeated steps to finish creating the tree
    while (!q.isEmpty()) // when q is not empty:
    {
        // get a tree node from the queue, ask user to type in its left/ right child
//        p = q.Front();
        p = q.Leave();
        cout << "Enter left child for this node: " << p->data << endl;
        string lc;
        getline(cin, lc);
        int intlc = stoi(lc);

        // check if user input is -1, that means there will be no left child for this node
        // if input is not -1, then create a new node and add it to its parent's lchild.
        if (intlc != -1) {
            t = new Node;
            t->data = intlc;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            // push this lchild to queue
            q.Join(t);
        }

        // Ok, now it's right child's turn
        cout << "Enter right child of this node:" << p->data << endl;
        string rc;
        getline(cin, rc);
        int intrc = stoi(rc);
        if (intrc != -1) {
            t = new Node;
            t->data = intrc;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            q.Join(t);
        }

    }


}

void Tree::Pre_order(Node *p) {
    if (p) {
        cout << p->data << " ";
        Pre_order(p->lchild);
        Pre_order(p->rchild);
    }

}

void Tree::Post_order(Node *p) {
    if (p) {
        Pre_order(p->lchild);
        Pre_order(p->rchild);
        cout << p->data << " ";
    }
}

void Tree::In_order(Node *p) {
    if (p) {
        Pre_order(p->lchild);
        cout << p->data << " ";
        Pre_order(p->rchild);
    }

}

void Tree::Level_order(Node *p) {
    Node *temp;
    Queue q(20);
    cout << p->data << " ";
    q.Join(p);
    while (!q.isEmpty()) {
        temp = q.Front();
        if (temp->lchild) {
            cout << temp->lchild->data << " ";
            q.Join(temp->lchild);
        }

        if (temp->rchild) {
            cout << temp->rchild->data << endl;
            q.Join(temp->rchild);
        }
    }
}

int Tree::Height(Node *p) {
    int x = 0, y = 0;
    if (!root)
        return 0;
    x = Height(p->lchild);
    y = Height(p->rchild);
    if (x > y)
        return x + 1;
    else
        return y + 1;
}


int main() {
//    Queue Q;
//    Q.Join(10);
//    Q.Join(20);
//    Q.Join(30);
//    Q.Join(40); // 只能加到这，因为default是5，但是总有一个空的不能用，就是front指向的那个array
//    Q.Join(50);  // 失败
//    Q.Join(60); // 失败
//    Q.Display(); //10 20 30 40
//
//    Q.Leave();
//    Q.Display(); //20 30 40

// creating a BT
    Tree t;
    t.CreateTree();

    cout << "PreOrder: ";
    t.Pre_order();
    cout << endl;
    cout << "InOrder: ";
    t.In_order();
    cout << endl;
    cout << "PostOrder: ";
    t.Post_order();
    cout << endl;

}