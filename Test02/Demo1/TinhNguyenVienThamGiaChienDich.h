#ifndef TINHNGUYENVIENTHAMGIACHIENDICH_H
#define TINHNGUYENVIENTHAMGIACHIENDICH_H

#include <string>
#include <ctime> // Thư viện để làm việc với thời gian
#include <iostream>
#include <iomanip>
#include <sstream> // Để sử dụng std::stringstream
#include <algorithm>
#include <list>


#include "ChienDich.h"
#include "TinhNguyenVien.h"
#include "SinglyLinkedList.h" 

using namespace std;

class TinhNguyenVienThamGiaChienDich {
public:
	string maTinhNguyenVien;      // Mã tình nguyện viên
	string hoLotTinhNguyenVien;   // Họ lót của tình nguyện viên
	string tenTinhNguyenVien;     // Tên tình nguyện viên
	string ngaySinh;              // Ngày tháng năm sinh (định dạng: dd/mm/yyyy)
	string soDienThoai;           // Số điện thoại liên hệ
	string maChienDich;           // Mã chiến dịch
	string tenChienDich;          // Tên chiến dịch
	string ngayBatDau;            // Ngày bắt đầu chiến dịch (định dạng: dd/mm/yyyy)
	string ngayKetThuc;           // Ngày kết thúc chiến dịch (định dạng: dd/mm/yyyy)
	int tuoiTNV;                  // Tuổi của tình nguyện viên
	int soNgayChienDich;          // Số ngày chiến dịch

	// Constructor
	TinhNguyenVienThamGiaChienDich(
		const string& maTNV,
		const string& hoLot,
		const string& ten,
		const string& ngaySinhTNV,
		const string& sdt,
		const string& maCD,
		const string& tenCD,
		const string& ngayBD,
		const string& ngayKT
	);

	// Phương thức tính tuổi của tình nguyện viên
	int tinhTuoi(const string& ngaySinh) const;

	// Phương thức tính số ngày chiến dịch
	int tinhSoNgayChienDich(const string& ngayBD, const string& ngayKT) const;

	// Phương thức hiển thị thông tin tình nguyện viên
	void hienThiThongTin() const;

};
void hienThiDanhSachThamGia(SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia);

void menuDanhSachThamGia(
	SinglyLinkedList<ChienDich>& danhSachChienDich,
	SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien,
	SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia
);

void danhSachTNVThamGiaChienDichNhieuNgayNhat(SinglyLinkedList<ChienDich>& dsChienDich, SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia);


void themTinhNguyenVienThamGiaChienDich(
	SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien,
	SinglyLinkedList<ChienDich>& danhSachChienDich,
	SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia,
	string maChienDich, string maTinhNguyenVien
);



#endif // TINHNGUYENVIENTHAMGIACHIENDICH_H
