#include <iostream>
# include<stack>

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
    this->size = 100;
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

    void Pre_order(Node *p);

    void Post_order(Node *p);

    void In_order(Node *p);

    int Height(Node *p);

    int TotalNodes(Node *p);

    void Pre_order_Iterative(Node *p);

    void In_order_Iterative(Node *p);

    void Post_order_Iterative(Node *p);


public:
    Tree() { root = NULL; }

    void CreateTree();

    // overloading ==> non-parameter Pre_order() will call the one with the parameter.
    // just can do it in a recursive way.
    // Also, root can be private now. ==> encapsulation
    void Pre_order() { Pre_order(this->root); }
    void Post_order() { Post_order(this->root); }
    void In_order() { In_order(this->root); }
    void Level_order();
    // -------------------------------------------------------------------
    // 求Height，我减去了1，因为height从0开始算。如果是求level，那么不需要-1.
    int Height() { return Height(this->root) -1; }
    // -------------------------------------------------------------------
    int TotalNodes() { return TotalNodes(this->root); }
    void Pre_order_Iterative() { Pre_order_Iterative(this->root); }
    void In_order_Iterative() { In_order_Iterative(this->root); }
    void Post_order_Iterative() { Post_order_Iterative(this->root); }
};

void Tree::CreateTree() {
    Node *p, *t;
    int x;
    Queue q(100);
    cout << "Enter root value: ";
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
        cout << "Enter left child for this node: " << p->data << ": ";
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
        cout << "Enter right child of this node:" << p->data << ": ";
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

void Tree::Level_order() {
    Node *p = this->root;
    Node *temp;
    Queue q(100);
    cout << p->data << " ";
    q.Join(p);
    while (!q.isEmpty()) {
//        temp = q.Front();
        temp = q.Leave();
        if (temp->lchild) {
            cout << temp->lchild->data << " ";
            q.Join(temp->lchild);
        }

        if (temp->rchild) {
            cout << temp->rchild->data << " ";
            q.Join(temp->rchild);
        }
    }
}

int Tree::Height(Node *p) {
    int x, y;
    if (p) {
        x = Height(p->lchild);
        y = Height(p->rchild);
        if (x > y) return x + 1;
        else return y + 1;
    }
    return 0;
}

// 顺序 print， left， right
void Tree::Pre_order_Iterative(Node *p) {
    stack<Node *> stack;
    Node *temp;
    temp = p;
    while (temp || !stack.empty()) {
        if (temp) {
            cout << temp->data << " ";
            stack.push(temp);
            temp = temp->lchild;
        } else {
            temp = stack.top();
            stack.pop();
            temp = temp->rchild;
        }
    }
}


// left, print, right
void Tree::In_order_Iterative(Node *p) {
    stack<Node *> stack;
    Node *temp = p;
    while (temp || !stack.empty()) {
        if (temp) {
            stack.push(temp);
            temp = temp->lchild;
        } else {
            temp = stack.top();
            stack.pop();
            cout << temp->data << " ";
            temp = temp->rchild;
        }
    }
}


// left, right, print
// 这个要复杂一些，stack类型要是long来存储Node地址，因为这样可以存储负数地址
void Tree::Post_order_Iterative(Node *p) {
    stack<long> stack;
    long tempLongAddress;
    Node *temp = p;
    while (temp || !stack.empty()) {
        if (temp) {
            stack.push((long) temp);
            temp = temp->lchild;
        } else {
            // pop from stack,
            tempLongAddress = stack.top();
            stack.pop();
            //if it is positive, then push it to stack again
            if (tempLongAddress > 0) {
                // 将栈顶元素的负值推入栈中
                stack.push(-tempLongAddress);
                // 根据负值地址找到对应节点的右子节点
                temp = ((Node *) (tempLongAddress))->rchild;
            }
                // if it is negative, print it
            else {
                cout << ((Node *) (-1 * tempLongAddress))->data << " ";
                temp = NULL;
            }


        }
    }


}

int Tree::TotalNodes(Node *p) {
    int x, y;
    if (p) {
        x = TotalNodes(p->lchild);
        y = TotalNodes(p->rchild);
        return x + y + 1;
    }
    return 0;
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

//    cout << "PreOrder: ";
//    t.Pre_order();
//    cout << endl;
//    cout << "InOrder: ";
//    t.In_order();
//    cout << endl;
//    cout << "PostOrder: ";
//    t.Post_order();
//    cout << endl;

//    t.Post_order_Iterative();
//    t.Level_order();
    cout << "count number of total nodes:" << t.TotalNodes() << endl;

    cout << "tree height is: " << t.Height()<< endl;



}