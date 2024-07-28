#include "ChienDich.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <sstream>

// Định nghĩa constructor và các phương thức của lớp ChienDich
ChienDich::ChienDich(const string& ma, const string& ten, const string& ngayBD, const string& ngayKT)
	: maChienDich(ma), tenChienDich(ten), ngayBatDau(ngayBD), ngayKetThuc(ngayKT) {
    soNgayChienDich = tinhSoNgayChienDich(ngayBD, ngayKT);
}


// Phương thức tính số ngày chiến dịch
int ChienDich::tinhSoNgayChienDich(const string& ngayBD, const string& ngayKT) const {
    int ngayBDay, thangBD, namBD;
    int ngayKDay, thangKT, namKT;
    char delimiter;

    // Tách ngày bắt đầu
    stringstream ssBD(ngayBD);
    ssBD >> ngayBDay >> delimiter >> thangBD >> delimiter >> namBD;

    // Tách ngày kết thúc
    stringstream ssKT(ngayKT);
    ssKT >> ngayKDay >> delimiter >> thangKT >> delimiter >> namKT;

    // Tạo cấu trúc tm cho ngày bắt đầu
    tm startDate = {};
    startDate.tm_mday = ngayBDay;
    startDate.tm_mon = thangBD - 1; // Tháng bắt đầu từ 0
    startDate.tm_year = namBD - 1900;

    // Tạo cấu trúc tm cho ngày kết thúc
    tm endDate = {};
    endDate.tm_mday = ngayKDay;
    endDate.tm_mon = thangKT - 1;
    endDate.tm_year = namKT - 1900;

    // Tính số giây từ 1970 đến ngày bắt đầu và ngày kết thúc
    time_t start = mktime(&startDate);
    time_t end = mktime(&endDate);

    // Tính số ngày chiến dịch
    int soNgay = static_cast<int>(difftime(end, start) / (60 * 60 * 24));

    return soNgay;
}

// Định nghĩa các hàm thao tác với danh sách chiến dịch
void themChienDich(SinglyLinkedList<ChienDich>& dsChienDich, const std::string& ma, const std::string& ten, const std::string& ngayBD, const std::string& ngayKT) {
    ChienDich moi(ma, ten, ngayBD, ngayKT); // Tạo đối tượng chiến dịch mới
    dsChienDich.addBack(moi); // Thêm chiến dịch vào cuối danh sách
}


void xoaChienDich(SinglyLinkedList<ChienDich>& dsChienDich, const std::string& ma) {
    Node<ChienDich>* current = dsChienDich.head; // Bắt đầu từ đầu danh sách
    Node<ChienDich>* previous = nullptr; // Để lưu trữ nút trước

    while (current) {
        if (current->data.maChienDich == ma) { // So sánh mã chiến dịch
            if (previous) {
                previous->next = current->next; // Bỏ qua nút hiện tại
            }
            else {
                dsChienDich.head = current->next; // Cập nhật nút đầu danh sách
            }
            delete current; // Giải phóng bộ nhớ
            std::cout << "Da xoa chien dich thanh cong!" << std::endl;
            return;
        }
        previous = current; // Cập nhật nút trước
        current = current->next; // Di chuyển đến nút tiếp theo
    }

    std::cout << "Khong tim thay chien dich voi ma: " << ma << std::endl;
}



void capNhatChienDich(SinglyLinkedList<ChienDich>& dsChienDich, const std::string& ma, const std::string& tenMoi, const std::string& ngayBDMoi, const std::string& ngayKTMoi) {
    Node<ChienDich>* current = dsChienDich.head; // Bắt đầu từ đầu danh sách

    while (current) {
        if (current->data.maChienDich == ma) { // So sánh mã chiến dịch
            current->data.tenChienDich = tenMoi; // Cập nhật tên chiến dịch
            current->data.ngayBatDau = ngayBDMoi; // Cập nhật ngày bắt đầu
            current->data.ngayKetThuc = ngayKTMoi; // Cập nhật ngày kết thúc
            current->data.soNgayChienDich = current->data.tinhSoNgayChienDich(ngayBDMoi, ngayKTMoi); // Cập nhật ngày kết thúc
            std::cout << "Da cap nhat chien dich thanh cong!" << std::endl;
            return;
        }
        current = current->next; // Di chuyển đến nút tiếp theo
    }

    std::cout << "Khong tim thay chien dich voi ma: " << ma << std::endl;
}

void xemDanhSach(SinglyLinkedList<ChienDich>& dsChienDich){

    std::cout << std::left; // Căn chỉnh văn bản bên trái
    std::cout << std::setw(20) << "Ma Chien Dich"
        << std::setw(30) << "Ten Chien Dich"
        << std::setw(20) << "Ngay Bat Dau"
        << std::setw(20) << "Ngay Ket Thuc"
        << std::setw(20) << "So ngay chien dich"
        << std::endl;

    Node<ChienDich>* current = dsChienDich.head;
    while (current) {
        std::cout << std::setw(20) << current->data.maChienDich
            << std::setw(30) << current->data.tenChienDich
            << std::setw(20) << current->data.ngayBatDau
            << std::setw(20) << current->data.ngayKetThuc
            << std::setw(20) << current->data.soNgayChienDich
            << std::endl;
        current = current->next;
    }
}

void danhSachChienDichNhieuNgayNhat(SinglyLinkedList<ChienDich>& dsChienDich) {
    if (dsChienDich.head == nullptr) {
        cout << "Danh sách trống." << endl;
        return;
    }
    SinglyLinkedList<ChienDich> ketQua;

    int maxSoNgay = 0;
    Node<ChienDich>* current = dsChienDich.head;

    // Tìm số ngày dài nhất của các chiến dịch
    while (current != nullptr) {
        if (current->data.soNgayChienDich > maxSoNgay) {
            maxSoNgay = current->data.soNgayChienDich;
        }
        current = current->next;
    }

    // In ra các chiến dịch có số ngày dài nhất
    current = dsChienDich.head;
    cout << "So ngay dai nhat cua chien dich la: " << maxSoNgay << " ngay" << endl;
    cout << "Danh sach cac chien dich co so ngay dai nhat:" << endl;
    while (current != nullptr) {
        if (current->data.soNgayChienDich == maxSoNgay) {
            ketQua.addBack(current->data);
        }
        current = current->next;
    }

    xemDanhSach(ketQua);
};


// Ham main thuc hien cac chuc nang duoc yeu cau
void menuChienDich(SinglyLinkedList<ChienDich>& list) {
    //SinglyLinkedList<ChienDich> list; // Khoi tao danh sach lien ket don cho cac chien dich
    int choice;                       // Bien lua chon chuc nang cua nguoi dung

    // Thêm phần tử vào danh sách
    list.addFront(ChienDich("CD01", "Chien Dich 1", "01/01/2024", "01/02/2024"));
    list.addFront(ChienDich("CD02", "Chien Dich 2", "01/01/2024", "01/02/2024"));
    list.addBack(ChienDich("CD03", "Chien Dich 3", "01/01/2024", "01/02/2024"));

    do {
        // Hien thi menu
        std::cout << "\nMenu Quan Ly Chien Dich\n";
        std::cout << "1. Xem Tat Ca Chien Dich" << std::endl;
        std::cout << "2. Them Chien Dich" << std::endl;
        std::cout << "3. Sua Chien Dich" << std::endl;
        std::cout << "4. Xoa Chien Dich" << std::endl;
        std::cout << "5. Chiến dịch có thời gian dài nhất" << std::endl;
        std::cout << "0. Thoat" << std::endl;
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
        case 1: { // Xem Tat Ca Chien Dich
            std::cout << "\nDanh Sach Tat Ca Cac Chien Dich:\n";
            //list.display(); // Hien thi tat ca cac chien dich

            xemDanhSach(list);
            break;
        }

        case 2: { // Them Chien Dich
            std::string ma, ten, batDau, ketThuc;

            std::cout << "Nhap Ma Chien Dich: ";
            std::cin >> ma;
            std::cout << "Nhap Ten Chien Dich: ";
            std::cin.ignore(); // Xoa ky tu newline con lai trong buffer
            std::getline(std::cin, ten);
            std::cout << "Nhap Ngay Bat Dau (YYYY-MM-DD): ";
            std::cin >> batDau;
            std::cout << "Nhap Ngay Ket Thuc (YYYY-MM-DD): ";
            std::cin >> ketThuc;

            // Them chien dich moi vao danh sach
            list.addBack(ChienDich(ma, ten, batDau, ketThuc));
            std::cout << "Da them chien dich thanh cong!\n";
            break;
        }

        case 3: { // Sua Chien Dich
            std::string ma, ten, batDau, ketThuc;

            std::cout << "Nhap Ma Chien Dich Can Sua: ";
            std::cin >> ma;
            std::cout << "Nhap Ten Chien Dich Moi: ";
            std::cin.ignore();
            std::getline(std::cin, ten);
            std::cout << "Nhap Ngay Bat Dau Moi (YYYY-MM-DD): ";
            std::cin >> batDau;
            std::cout << "Nhap Ngay Ket Thuc Moi (YYYY-MM-DD): ";
            std::cin >> ketThuc;

            // Tim va sua chien dich
            capNhatChienDich(list, ma, ten, batDau, ketThuc); 
            break;
        }

        case 4: { // Xoa Chien Dich
            std::string ma;

            std::cout << "Nhap Ma Chien Dich Can Xoa: ";
            std::cin >> ma;

            xoaChienDich(list, ma);
            break;
        }

        case 5: { // Thoat
            danhSachChienDichNhieuNgayNhat(list);
            break;
        }
        case 0: { // Thoat
            std::cout << "Quay ve menu chinh." << std::endl;
            break;
        }

        default: {
            std::cout << "Lua chon khong hop le! Vui long chon lai." << std::endl;
            break;
        }
        }
    } while (choice != 0); // Lap lai cho den khi nguoi dung chon thoat

}