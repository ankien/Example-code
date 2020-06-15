#include <iostream>
#include <stdint.h>
template <typename T>
class DoublyLinkedList {
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T data) {this->data = data;}
    };

    public:
        Node *head, *tail;
        DoublyLinkedList() {
            head = tail = NULL;
        }

        void frontInsert(T data) {
            Node *temp = new Node(data);
            if (head == NULL) {
                tail = temp;
                temp->next = temp->prev = NULL;
            } else {
                head->prev = temp;
                temp->next = head;
                temp->prev=NULL;
            } head = temp;
        }

        void rearInsert(T data) {
            Node *temp = new Node(data);
            if (head == NULL) {
                head = temp;
                temp->next = temp->prev = NULL;
            } else {
                tail->next = temp;
                temp->prev = tail;
                temp->next = NULL;
            } tail = temp;
        }

        void insertAfter(Node* address, T data) {
            if (address == NULL) { return; }
            Node *temp = new Node(data);
            if(address->next != NULL) {
                address->next->prev = temp;
            }
            temp->next = address->next;
            address->next = temp;
            temp->prev = address;
        }

        void printList() {
            Node* temp = head;
            std::cout << "[ ";
            while (temp != NULL) {
                std::cout << temp->data << " ";
                temp = temp->next;
            } std::cout << "]\n";
        }

        // Deletes a node given its pointer, call deleteByValue if pointer is unknown.
        T deleteNode(Node* address) {
            if((head == NULL) || (address == NULL)) {return T();}
            if (head == address) {
                head = address->next;
            }
            if (address->next != NULL) {
                address->next->prev = address->prev;
            }
            if (address->prev != NULL) {
                address->prev->next = address->next;
            }

            T temp = address->data;
            delete address;
            return temp;
        }

        // Deletes a node by value, specify path starting from head 'h' or tail 't'.
        T deleteByValue(T value, char mode) {
            if(mode == 'h') {
                if(head == NULL) {return T();}
                Node* temp = head;
                while(temp != NULL) {
                    if(temp->data == value) {
                        return deleteNode(temp);
                    } temp = temp->next;
                }
            } 
            
            else if(mode == 't') {
                if(tail == NULL) {return T();}
                Node* temp = tail;
                while(temp != NULL) {
                    if(temp->data == value) {
                        return deleteNode(temp);
                    } temp = temp->prev;
                }
            } 
            
            return T();
        }
};