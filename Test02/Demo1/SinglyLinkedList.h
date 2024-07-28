#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include <stdexcept> // For std::out_of_range

// Khai báo cấu trúc Node
template <typename T>
struct Node {
    T data;        // Dữ liệu của nút
    Node* next;    // Con trỏ đến nút tiếp theo

    // Khởi tạo nút với giá trị cho trước
    Node(T value) : data(value), next(nullptr) {}
};

// Khai báo lớp SinglyLinkedList
template <typename T>
class SinglyLinkedList {
public:
    Node<T>* head; // Con trỏ đầu danh sách
    int size;   // Số lượng phần tử trong danh sách

    // Constructor
    SinglyLinkedList() : head(nullptr) {}

    // Destructor
    ~SinglyLinkedList() {
        clear();
    }

    // Thêm phần tử vào đầu danh sách
    void addFront(T value);

    // Thêm phần tử vào cuối danh sách
    void addBack(T value);

    // Định nghĩa toán tử [] để truy cập phần tử theo chỉ số
    T& operator[](int index);

    // Xóa phần tử theo giá trị
    void remove(T value);

    // Sửa giá trị của phần tử trong danh sách
    void update(T oldValue, T newValue);

    // Hiển thị danh sách
    void display() const;

    // Xóa toàn bộ danh sách
    void clear();

    // Lấy số lượng phần tử trong danh sách
    int getSize() const { return size; }

    // Hàm để in nội dung của danh sách
    void printList() const;
};

// Triển khai phương thức của lớp SinglyLinkedList

// Thêm phần tử vào đầu danh sách
template <typename T>
void SinglyLinkedList<T>::addFront(T value) {
    Node<T>* newNode = new Node<T>(value); // Tạo nút mới
    newNode->next = head;                  // Liên kết nút mới với nút đầu
    head = newNode;                        // Đặt nút mới làm nút đầu
}

// Thêm phần tử vào cuối danh sách
template <typename T>
void SinglyLinkedList<T>::addBack(T value) {
    Node<T>* newNode = new Node<T>(value); // Tạo nút mới
    if (!head) {                           // Nếu danh sách rỗng
        head = newNode;                    // Đặt nút mới làm nút đầu
    }
    else {
        Node<T>* current = head;           // Bắt đầu từ đầu danh sách
        while (current->next) {            // Tìm nút cuối cùng
            current = current->next;
        }
        current->next = newNode;           // Thêm nút mới vào cuối
    }
}

// Định nghĩa toán tử [] để truy cập phần tử theo chỉ số
template <typename T>
T& SinglyLinkedList<T>::operator[](int index) {
    Node<T>* current = head;
    int currentIndex = 0;

    while (current != nullptr) {
        if (currentIndex == index) {
            return current->data; // Trả về dữ liệu của nút tại chỉ số index
        }
        current = current->next;
        currentIndex++;
    }

    // Nếu chỉ số ngoài phạm vi
    throw std::out_of_range("Chi so ngoai pham vi danh sach!");
}

// Xóa phần tử theo giá trị
template <typename T>
void SinglyLinkedList<T>::remove(T value) {
    if (!head) return; // Danh sách rỗng

    // Xóa phần tử ở đầu danh sách
    if (head->data == value) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Tìm phần tử cần xóa
    Node<T>* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    // Xóa phần tử nếu tìm thấy
    if (current->next) {
        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// Sửa giá trị của phần tử trong danh sách
template <typename T>
void SinglyLinkedList<T>::update(T oldValue, T newValue) {
    Node<T>* current = head;
    while (current) {
        if (current->data == oldValue) {
            current->data = newValue;
            return;
        }
        current = current->next;
    }
}

// Hiển thị danh sách
template <typename T>
void SinglyLinkedList<T>::display() const {
    Node<T>* current = head;
    while (current) {
        std::cout << current->data << " \n";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Hàm để in nội dung của danh sách
template <typename T>
void SinglyLinkedList<T>::printList() const {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << std::endl; // Sử dụng toán tử << của T
        current = current->next;
    }
}


// Xóa toàn bộ danh sách
template <typename T>
void SinglyLinkedList<T>::clear() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

#endif // SINGLYLINKEDLIST_H
