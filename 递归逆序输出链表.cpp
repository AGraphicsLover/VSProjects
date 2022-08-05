#include<iostream>
using namespace std;
static int i = 0;
class Node
{
    int num;
    Node* next;
public:
    Node(int n)
    {
        num = n;
        next = NULL;
    }
    void setNext(Node* p)
    {
        next = p;
    }
    int getNum()
    {
        return num;
    }
    Node* getNext()
    {
        return next;
    }
};
class list
{
    Node* head;
public:
    Node* gethead()
    {
        return head;
    }
    list(int n)
    {
        head = new Node(n);
    }
    void addNode(int n);
    void visitAllNode();
    void visitAllNode_reverse(Node* node);
    void visitAllNode_reverse_K(Node* node,int j,int k);
};
void list::addNode(int n)
{
    Node* p = head;
    if (head == NULL)
    {
        head = new Node(n);
    }
    else
    {
        while (p->getNext() != NULL)
        {
            p = p->getNext();
        }
        p->setNext(new Node(n));
        i++;
        cout << "已创建第" << i << "个节点!" << endl;
    }
}
void list::visitAllNode()
{
    Node* p;
    p = head;
    if (p == NULL)
    {
        cout << "空链表!" << endl;
    }
    else
    {
        cout << "顺序输出：表头  ";
        while (p->getNext() != NULL)
        {
            cout << p->getNum() << "   ";
            p = p->getNext();
        }
        cout << p->getNum() << "   表尾" << endl;
    }
}
void list::visitAllNode_reverse(Node* node)
{
    if (node != NULL)
    {
        if (node->getNext() != NULL)
        {
            visitAllNode_reverse(node->getNext());
        }
        cout << node->getNum()<<"   ";
    }
    else
    {
        cout << "空链表!" << endl;
    }
}
void list::visitAllNode_reverse_K(Node* node,int j,int k)
{
    if (node != NULL)
    {
        if (node->getNext() != NULL)
        {
            visitAllNode_reverse_K(node->getNext(), --j, k);
            if (j == i - k - 1)
                cout << node->getNum() << "   ";
        }
        else
        {
            if(j==i-k)
                cout<< node->getNum() << "   ";
        }
    }
    else
    {
        cout << "空链表!" << endl;
    }
}
int main()
{
    list* p1;
    int m,n,k;
    cout << "请输入你想创建的节点数：";
    cin >> m;
    if (m > 0)
    {
        cout << "请输入第一个节点值从而创建第一个节点：";
        cin >> n;
        p1 = new list(n);
        i++;
        cout << "已创建第" << i << "个节点!" << endl;
        while (i < m)
        {
            cout << "请输入节点值：";
            cin >> n;
            p1->addNode(n);
        }
        p1->visitAllNode();
        cout << "反序输出：表尾  ";
        p1->visitAllNode_reverse(p1->gethead());
        cout << "表头" << endl;
        cout << "请输入k的值：";
        cin >> k;
        int j = i;
        if (k >= 0 && k < i)
        {
            cout << "倒数第k个节点为：";
            p1->visitAllNode_reverse_K(p1->gethead(), j, k);
        }
        else
            cout << "不存在这样的节点！" << endl;
        delete p1;
    }
    else
        cout << "无法创建链表！" << endl;
    return 0;
}