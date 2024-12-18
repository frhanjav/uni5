#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
    
    public:
        Node(int data1, Node* next1) {
            data = data1;
            next = next1;
        }
        
    public:
        Node(int data1) {
            data = data1;
            next = nullptr;
        }
};

void print(Node* head) {
  while(head!= NULL) {
    cout << head->data << " ";
    head = head->next;
  }
  cout << endl;
}

Node* convertArr2LL(vector <int> &arr) {
    Node* head = new Node(arr[0]);
    Node* mover = head;
    for(int i = 1; i<arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        mover->next = temp;
        mover = temp;
    }
    return head;
}

Node* insertHead(Node* head, int val) {
  return new Node(val, head);
}

Node* insertPosition(Node* head, int el, int k) {
    if (head == NULL) {
        if (k == 1) {
            Node* head = new Node(el);
        }
        else {
            return head;
        }
    }
    if (k==1) {
        return new Node(el, head);
    }
    int cnt = 0;
    Node* temp = head;
    
    while (temp != NULL) {
        cnt++;
        if (cnt == (k - 1)) {
            Node* x = new Node(el, temp->next);
            temp->next = x;
            break;
        }
        temp = temp->next;
    }
    
    return head;
    
}

Node* insertBeforeValue(Node* head, int el, int val) {
    if (head == NULL) {
        return head;
    }
    if (head->data == val) {
        return new Node(el, head);
    }
    int cnt = 0;
    Node* temp = head;
    
    while (temp->next != NULL) {
        if (temp->next->data == val) {
            Node* x = new Node(el, temp->next);
            temp->next = x;
            break;
        }
        temp = temp->next;
    }
    
    return head;
    
}

int main() {
    vector <int> arr = {7, 5, 24, 9};
    Node* head = convertArr2LL(arr);
    head = insertBeforeValue(head, 100, 8);
    print(head);
}