#include <iostream>
#include <stdexcept>
#include <string>


class CustomException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "An error occurred.";
    }
};


class MathException : public CustomException {
public:
    const char* what() const noexcept override {
        return "Math error occurred.";
    }
};


class DivisionByZeroException : public MathException {
public:
    const char* what() const noexcept override {
        return "Division by zero error.";
    }
};

class MemoryException : public CustomException {
public:
    const char* what() const noexcept override {
        return "Memory allocation failed.";
    }
};

class FileException : public CustomException {
public:
    const char* what() const noexcept override {
        return "File error occurred.";
    }
};


class FileOpenException : public FileException {
public:
    const char* what() const noexcept override {
        return "Error opening the file.";
    }
};


class FileReadException : public FileException {
public:
    const char* what() const noexcept override {
        return "Error reading from the file.";
    }
};


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
            throw MemoryException();
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
            throw MemoryException();
        }
    }

    void RemoveFromFront() {
        if (!head) {
            throw CustomException();  
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


double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw DivisionByZeroException();
    }
    return numerator / denominator;
}

int main() {
    try {
       
        double result = divide(5.0, 0.0);
        std::cout << "Result: " << result << std::endl;

    }
    catch (const DivisionByZeroException& e) {
        std::cerr << "Math error: " << e.what() << std::endl;
    }

    try {
      
        DoublyLinkedList<int> list;
        list.AddToBack(1);
        list.AddToBack(2);
        list.AddToBack(3);
        std::cout << "List before removal: ";
        list.PrintList();

        list.RemoveFromFront();
        std::cout << "List after removal: ";
        list.PrintList();

        list.RemoveFromFront();
        list.RemoveFromFront();
        list.RemoveFromFront(); 

    }
    catch (const CustomException& e) {
        std::cerr << "Error with linked list: " << e.what() << std::endl;
    }

    try {
     
        throw FileOpenException();  

    }
    catch (const FileException& e) {
        std::cerr << "File error: " << e.what() << std::endl;
    }

    return 0;
}
