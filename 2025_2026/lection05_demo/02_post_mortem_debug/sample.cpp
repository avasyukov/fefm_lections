#include <iostream>

using std::cout;
using std::endl;

class Node {
public:
    int data;
    Node *next;
};

Node* create_node(int data);
Node* create_list(int length);
void print_list(Node* list, int length);

Node* create_node(int data) {
    Node* new_node = new Node();
    new_node->data = data;
    new_node->next = nullptr;
    return new_node;
}

Node* create_list(int length) {
    Node* head = nullptr;
    if (length > 0) {
        head = create_node(0);
        int i = 1;
        Node *curr = head;
        while (i < length) {
            curr->next = create_node(i);
            curr = curr->next;
            i++;
        }
    }
    return head;
}

void print_list(Node *list, int length) {
    Node *curr = list;
    int i = 0;
    while (i <= length) {
        cout << curr->data << " -> ";
        curr = curr->next;
        i++;
    }
    cout << "." << endl;
}

int main() {
    int length1 = 7;
    Node* list1 = create_list(length1);
    print_list(list1, length1);

    return 0;
}
