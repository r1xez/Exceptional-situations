#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        Clear();
    }

    void AddToFront(const T& value) {
        try {
            Node* newNode = new Node(value);
            if (!head) {
                head = tail = newNode;
            }
            else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            ++size;
        }
        catch (std::bad_alloc&) {
            throw std::runtime_error("Memory allocation failed while adding to the front.");
        }
    }

    void AddToBack(const T& value) {
        try {
            Node* newNode = new Node(value);
            if (!tail) {
                head = tail = newNode;
            }
            else {
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            }
            ++size;
        }
        catch (std::bad_alloc&) {
            throw std::runtime_error("Memory allocation failed while adding to the back.");
        }
    }

    void RemoveFromFront() {
        if (!head) {
            throw std::runtime_error("Cannot remove from an empty list.");
        }
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        --size;
    }

    void RemoveFromBack() {
        if (!tail) {
            throw std::runtime_error("Cannot remove from an empty list.");
        }
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        --size;
    }

    void Clear() {
        while (head) {
            RemoveFromFront();
        }
    }

    void PrintList() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    size_t GetSize() const {
        return size;
    }
};

int main() {
    DoublyLinkedList<int> list;
    int choice, value;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add to front\n";
        std::cout << "2. Add to back\n";
        std::cout << "3. Remove from front\n";
        std::cout << "4. Remove from back\n";
        std::cout << "5. Print list\n";
        std::cout << "6. Clear list\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try {
            switch (choice) {
            case 1:
                std::cout << "Enter value to add to front: ";
                std::cin >> value;
                list.AddToFront(value);
                break;
            case 2:
                std::cout << "Enter value to add to back: ";
                std::cin >> value;
                list.AddToBack(value);
                break;
            case 3:
                list.RemoveFromFront();
                std::cout << "Removed from front.\n";
                break;
            case 4:
                list.RemoveFromBack();
                std::cout << "Removed from back.\n";
                break;
            case 5:
                std::cout << "List: ";
                list.PrintList();
                break;
            case 6:
                list.Clear();
                std::cout << "List cleared.\n";
                break;
            case 7:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice! Try again.\n";
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
