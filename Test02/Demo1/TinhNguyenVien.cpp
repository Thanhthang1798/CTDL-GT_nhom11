#include "TinhNguyenVien.h"
#include <iostream>
#include <algorithm>
#include <list>

// Định nghĩa constructor và các phương thức của lớp TinhNguyenVien
TinhNguyenVien::TinhNguyenVien(const string& ma, const string& hoLot,
    const string& ten, const string& ngay,
    const string& sdt)
    : maTinhNguyenVien(ma), hoLotTinhNguyenVien(hoLot), tenTinhNguyenVien(ten),
    ngaySinh(ngay), soDienThoai(sdt) {
    tuoi = getTuoi();
}

// Định nghĩa các hàm thao tác với danh sách chiến dịch
void themTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien, const string& ma, const string& hoLot,
    const string& ten, const string& ngay, const string& sdt) {
    TinhNguyenVien moi(ma, hoLot, ten, ngay, sdt); // Tạo đối tượng chiến dịch mới
    dsTinhNguyenVien.addBack(moi); // Thêm chiến dịch vào cuối danh sách
}


void xoaTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien, const std::string& ma) {
    Node<TinhNguyenVien>* current = dsTinhNguyenVien.head; // Bắt đầu từ đầu danh sách
    Node<TinhNguyenVien>* previous = nullptr; // Để lưu trữ nút trước

    while (current) {
        if (current->data.maTinhNguyenVien == ma) { // So sánh mã chiến dịch
            if (previous) {
                previous->next = current->next; // Bỏ qua nút hiện tại
            }
            else {
                dsTinhNguyenVien.head = current->next; // Cập nhật nút đầu danh sách
            }
            delete current; // Giải phóng bộ nhớ
            std::cout << "Da xoa Tinh Nguyen Vien thanh cong!" << std::endl;
            return;
        }
        previous = current; // Cập nhật nút trước
        current = current->next; // Di chuyển đến nút tiếp theo
    }

    std::cout << "Khong tim thay Tinh Nguyen Vien voi ma: " << ma << std::endl;
}



void capNhatTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien, const std::string& ma, const std::string& hoLotMoi, const std::string& tenMoi, const std::string& ngaySinhMoi, const std::string& soDienThoaiMoi) {
    Node<TinhNguyenVien>* current = dsTinhNguyenVien.head; // Bắt đầu từ đầu danh sách

    while (current) {
        if (current->data.maTinhNguyenVien == ma) { // So sánh mã chiến dịch
            current->data.tenTinhNguyenVien = tenMoi; // Cập nhật tên chiến dịch
            current->data.hoLotTinhNguyenVien = hoLotMoi; // Cập nhật tên chiến dịch
            current->data.ngaySinh = ngaySinhMoi; // Cập nhật ngày bắt đầu
            current->data.soDienThoai = soDienThoaiMoi; // Cập nhật ngày kết thúc
            current->data.tuoi = current->data.getTuoi(); // Cập nhật ngày kết thúc
            std::cout << "Da cap nhat Tinh Nguyen Vien thanh cong!" << std::endl;
            return;
        }
        current = current->next; // Di chuyển đến nút tiếp theo
    }

    std::cout << "Khong tim thay Tinh Nguyen Vien voi ma: " << ma << std::endl;
}

void xemDanhSach(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien) {

    cout << left << setw(20) << "Ma TN"
        << setw(20) << "Ho Lot"
        << setw(15) << "Ten"
        << setw(15) << "Ngay Sinh"
        << setw(15) << "So DT"
        << setw(5) << "Tuoi" << endl;
    cout << "----------------------------------------------------------------------------\n";


    Node<TinhNguyenVien>* current = dsTinhNguyenVien.head;
    while (current) {
        cout << left << setw(20) << current->data.maTinhNguyenVien
            << setw(20) << current->data.hoLotTinhNguyenVien
            << setw(15) << current->data.tenTinhNguyenVien
            << setw(15) << current->data.ngaySinh
            << setw(15) << current->data.soDienThoai
            << setw(5) << current->data.tuoi << endl; // Hiển thị tuổi
        current = current->next;
    }
}

void nhapTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien) {
    string ma, hoLot, ten, ngaySinh, soDienThoai;

    cout << "Nhap Ma Tinh Nguyen Vien: ";
    cin >> ma;
    cin.ignore(); // Xoá ký tự newline trong buffer sau khi nhập mã

    cout << "Nhap Ho Lot Tinh Nguyen Vien: ";
    getline(cin, hoLot);

    cout << "Nhap Ten Tinh Nguyen Vien: ";
    getline(cin, ten);

    cout << "Nhap Ngay Sinh (dd/mm/yyyy): ";
    cin >> ngaySinh;

    cout << "Nhap So Dien Thoai: ";
    cin >> soDienThoai;

    // Thêm Tình Nguyện Viên vào danh sách
    dsTinhNguyenVien.addBack(TinhNguyenVien(ma, hoLot, ten, ngaySinh, soDienThoai));

    cout << "Da them Tinh Nguyen Vien thanh cong!\n";
}



void timTinhNguyenVienTuoiNhoNhat(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien) {
    if (dsTinhNguyenVien.head == nullptr) {
        cout << "Danh sách trống." << endl;
        return;
    }

    int minAge = std::numeric_limits<int>::max(); // Khởi tạo tuổi nhỏ nhất là lớn nhất có thể
    Node<TinhNguyenVien>* current = dsTinhNguyenVien.head;

    // Tìm tuổi nhỏ nhất
    while (current != nullptr) {
        if (current->data.tuoi < minAge) {
            minAge = current->data.tuoi;
        }
        current = current->next;
    }

    // Tìm và in ra các tình nguyện viên có tuổi nhỏ nhất
    current = dsTinhNguyenVien.head;
    cout << "Tinh nguyen vien co tuoi nho nhat la: " << minAge << endl;
    cout << "Danh sach tinh nguyen vien co tuoi nho nhat:" << endl;
    while (current != nullptr) {
        if (current->data.tuoi == minAge) {
            cout << "Ma: " << current->data.maTinhNguyenVien << ", "
                << "Ho lot: " << current->data.hoLotTinhNguyenVien << ", "
                << "Ten: " << current->data.tenTinhNguyenVien << ", "
                << "Ngay sinh: " << current->data.ngaySinh << ", "
                << "So dien thoai: " << current->data.soDienThoai << ", "
                << "Tuoi: " << current->data.tuoi << endl;
        }
        current = current->next;
    }
}

// Hàm cập nhật thông tin tình nguyện viên
void menuCapNhatTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien) {
    string maTinhNguyenVien;

    cout << "Nhap ma tinh nguyen vien can cap nhat: ";
    cin >> maTinhNguyenVien;

    // Duyệt danh sách để tìm tình nguyện viên có mã cần cập nhật
    bool found = false;
    for (int i = 0; i < dsTinhNguyenVien.getSize(); i++) {
        if (dsTinhNguyenVien[i].maTinhNguyenVien == maTinhNguyenVien) {
            // Nếu tìm thấy, cho phép người dùng nhập thông tin mới
            found = true;
            string hoLotMoi, tenMoi, ngaySinhMoi, soDienThoaiMoi;

            cout << "Nhap ho lot moi: ";
            cin.ignore();  // Xóa bỏ ký tự xuống dòng thừa từ cin trước đó
            getline(cin, hoLotMoi);

            cout << "Nhap ten moi: ";
            getline(cin, tenMoi);

            cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
            cin >> ngaySinhMoi;

            cout << "Nhap so dien thoai moi: ";
            cin >> soDienThoaiMoi;

            // Cập nhật thông tin mới cho tình nguyện viên
            capNhatTinhNguyenVien(dsTinhNguyenVien, maTinhNguyenVien, hoLotMoi, tenMoi, ngaySinhMoi, soDienThoaiMoi);

            // Tính toán lại tuổi dựa trên ngày sinh mới
            dsTinhNguyenVien[i].tuoi = dsTinhNguyenVien[i].getTuoi();

            cout << "Da cap nhat thong tin tinh nguyen vien thanh cong!\n";
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay tinh nguyen vien voi ma " << maTinhNguyenVien << ".\n";
    }
}

// Ham main thuc hien cac chuc nang duoc yeu cau
void menuTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien) {
    //SinglyLinkedList<TinhNguyenVien> list; // Khoi tao danh sach lien ket don cho cac Tinh Nguyen Vien
    int choice;                       // Bien lua chon chuc nang cua nguoi dung

    do {
        // Hien thi menu
        std::cout << "\nMenu Quan Ly Tinh Nguyen Vien\n";
        std::cout << "1. Xem Tat Ca Tinh Nguyen Vien" << std::endl;
        std::cout << "2. Them Tinh Nguyen Vien" << std::endl;
        std::cout << "3. Sua Tinh Nguyen Vien" << std::endl;
        std::cout << "4. Xoa Tinh Nguyen Vien" << std::endl;
        std::cout << "5. Các TNV nhỏ tuổi nhất" << std::endl;
        std::cout << "0. Thoat" << std::endl;
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
        case 1: { // Xem Tat Ca Tinh Nguyen Vien
            std::cout << "\nDanh Sach Tat Ca Cac Tinh Nguyen Vien:\n";

            xemDanhSach(dsTinhNguyenVien);
            break;
        }

        case 2: { // Them Tinh Nguyen Vien
            nhapTinhNguyenVien(dsTinhNguyenVien);
            break;
        }

        case 3: { // Sua Tinh Nguyen Vien
            menuCapNhatTinhNguyenVien(dsTinhNguyenVien);
            break;
        }

        case 4: { // Xoa Tinh Nguyen Vien
            std::string ma;

            std::cout << "Nhap Ma Tinh Nguyen Vien Can Xoa: ";
            std::cin >> ma;

            xoaTinhNguyenVien(dsTinhNguyenVien, ma);
            break;
        }
        case 5: { // Xoa Tinh Nguyen Vien
            timTinhNguyenVienTuoiNhoNhat(dsTinhNguyenVien);
            break;
        }

        case 0: { // Thoat
            system("cls");
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
