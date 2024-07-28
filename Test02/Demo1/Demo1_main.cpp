
#include <iostream>
#include <list> 
#include <algorithm>

#include "ChienDich.h"
#include "TinhNguyenVien.h"
#include "TinhNguyenVienThamGiaChienDich.h"

using namespace std;


void pauseScreen() {
	cout << "nhan phim enter de tiep tuc...";
	cin.ignore();  // bo qua ky tu enter co the con sot lai trong bo dem
	cin.get();     // doi nguoi dung nhan enter
}

int main(int argc, char* args[]){
    SinglyLinkedList<ChienDich> danhSachChienDich; // Khoi tao danh sach lien ket don cho cac chien dich
    SinglyLinkedList<TinhNguyenVien> dsTinhNguyenVien;
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich> danhSachThamGia;

    int luaChon;
    do {
        std::cout << "Nhap 1 de nhap chien dich" << std::endl;
        std::cout << "Nhap 2 de nhap tinh nguyen vien" << std::endl;
        std::cout << "Nhap 3 de nhap tinh nguyen vien tham gia chien dich" << std::endl;
        std::cout << "Nhap 9 để clear man hinh console" << std::endl;
        std::cout << "Nhap 0 de thoat" << std::endl;
        std::cout << "Lua chon cua ban: ";
        std::cin >> luaChon;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Xóa ký tự newline còn lại trong bộ đệm

        switch (luaChon) {
        case 1:
            menuChienDich(danhSachChienDich);
            break;
        case 2:
            menuTinhNguyenVien(dsTinhNguyenVien);
            break;
        case 3:
            menuDanhSachThamGia(danhSachChienDich, dsTinhNguyenVien, danhSachThamGia);
            break;
        case 9: 
            system("cls");
            break;
        case 0:
            std::cout << "Thoat chuong trinh." << std::endl;
            break;
        default:
            std::cout << "Lua chon khong hop le. Vui long chon lai." << std::endl;
        }
    } while (luaChon != 0);

    return 0;
}
