#ifndef CHIENDICH_H
#define CHIENDICH_H

#include <string>
#include <iomanip> // Để sử dụng std::setw
#include "SinglyLinkedList.h"

using namespace std;

// Định nghĩa lớp ChienDich
class ChienDich {
public:

	string maChienDich;
	string tenChienDich;
	string ngayBatDau;
	string ngayKetThuc;
	int soNgayChienDich;          // Số ngày chiến dịch


	// Constructor và các phương thức của lớp
	ChienDich(const string& ma, const string& ten, const string& ngayBD, const string& ngayKT);

	// Getter và Setter cho các thuộc tính (nếu cần)
	int tinhSoNgayChienDich(const string& ngayBD, const string& ngayKT) const;


	// Dinh nghia toan tu << de in thong tin cua doi tuong ChienDich
	friend std::ostream& operator<<(std::ostream& os, const ChienDich& cd) {
		os << "Ma Chien Dich: " << cd.maChienDich
			<< ", Ten Chien Dich: " << cd.tenChienDich
			<< ", Ngay Bat Dau: " << cd.ngayBatDau
			<< ", Ngay Ket Thuc: " << cd.ngayKetThuc;
		return os;
	}

	// Dinh nghia toan tu so sanh ==
	bool operator==(const ChienDich& other) const {
		return maChienDich == other.maChienDich &&
			tenChienDich == other.tenChienDich &&
			ngayBatDau == other.ngayBatDau &&
			ngayKetThuc == other.ngayKetThuc;
	}

	// Dinh nghia toan tu so sanh !=
	bool operator!=(const ChienDich& other) const {
		return !(*this == other); // Su dung lai toan tu ==
	}
	 
};

// Các hàm thao tác với danh sách chiến dịch
void themChienDich(SinglyLinkedList<ChienDich>& dsChienDich, const string& ma, const string& ten, const string& ngayBD, const string& ngayKT);
void xoaChienDich(SinglyLinkedList<ChienDich>& dsChienDich, const string& ma);
void capNhatChienDich(SinglyLinkedList<ChienDich>& dsChienDich, const string& ma, const string& tenMoi, const string& ngayBDMoi, const string& ngayKTMoi);
void xemDanhSach(SinglyLinkedList<ChienDich>& dsChienDich);
void danhSachChienDichNhieuNgayNhat(SinglyLinkedList<ChienDich>& dsChienDich);
void menuChienDich(SinglyLinkedList<ChienDich>& dsChienDich);


#endif // CHIENDICH_H
