#ifndef TINHNGUYENVIEN_H
#define TINHNGUYENVIEN_H

#include <string>
#include <iomanip> // Để sử dụng std::setw
#include "SinglyLinkedList.h"

#include <sstream>
using namespace std;

// Định nghĩa lớp TinhNguyenVien
class TinhNguyenVien {
public:
	string maTinhNguyenVien;      // Mã tình nguyện viên
	string hoLotTinhNguyenVien;   // Họ lót của tình nguyện viên
	string tenTinhNguyenVien;     // Tên tình nguyện viên
	string ngaySinh;              // Ngày tháng năm sinh (định dạng: dd/mm/yyyy)
	string soDienThoai;           // Số điện thoại liên hệ
	int tuoi;

	// Constructor và các phương thức của lớp
	TinhNguyenVien(const string& ma, const string& hoLot,
		const string& ten, const string& ngay,
		const string& sdt); 

	// Dinh nghia toan tu << de in thong tin cua doi tuong TinhNguyenVien
	friend std::ostream& operator<<(std::ostream& os, const TinhNguyenVien& cd) {
		os << "Ma Chien Dich: " << cd.maTinhNguyenVien
			<< ", Ten Chien Dich: " << cd.tenTinhNguyenVien
			/*<< ", Ngay Bat Dau: " << cd.ngayBatDau
			<< ", Ngay Ket Thuc: " << cd.ngayKetThuc*/
			;
		return os;
	}

	// Dinh nghia toan tu so sanh ==
	bool operator==(const TinhNguyenVien& other) const {
		return maTinhNguyenVien == other.maTinhNguyenVien &&
			tenTinhNguyenVien == other.tenTinhNguyenVien // &&
			/*ngayBatDau == other.ngayBatDau &&
			ngayKetThuc == other.ngayKetThuc;*/ ;
	}

	// Dinh nghia toan tu so sanh !=
	bool operator!=(const TinhNguyenVien& other) const {
		return !(*this == other); // Su dung lai toan tu ==
	}
	 
	int getTuoi() const {
		// Giả sử định dạng ngày sinh là "dd/mm/yyyy"
		int ngay, thang, nam;
		char delimiter;

		stringstream ss(ngaySinh);
		ss >> ngay >> delimiter >> thang >> delimiter >> nam;

		if (ss.fail()) {
			throw invalid_argument("Ngay sinh khong dung dinh dang");
		}

		// Lấy năm hiện tại
		time_t t = time(nullptr);
		struct tm now;

		// Sử dụng localtime_s để đảm bảo an toàn
		if (localtime_s(&now, &t) != 0) {
			throw runtime_error("Khong the lay thoi gian he thong");
		}

		int namHienTai = now.tm_year + 1900;
		int thangHienTai = now.tm_mon + 1;
		int ngayHienTai = now.tm_mday;

		// Tính tuổi
		int tuoi = namHienTai - nam;

		// Kiểm tra nếu tháng hiện tại trước tháng sinh hoặc cùng tháng nhưng ngày hiện tại trước ngày sinh
		if (thangHienTai < thang || (thangHienTai == thang && ngayHienTai < ngay)) {
			tuoi--; // Giảm 1 tuổi nếu chưa tới sinh nhật năm nay
		}

		return tuoi;
	}
	
};

// Các hàm thao tác với danh sách chiến dịch
void themTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien, const string& ma, const string& hoLot, const string& ten, const string& ngay, const string& sdt);
void xoaTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien, const string& ma);
void capNhatTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien, const std::string& ma, const std::string& hoLotMoi, const std::string& tenMoi, const std::string& ngaySinhMoi, const std::string& soDienThoaiMoi);
void xemDanhSach(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien);
void timTinhNguyenVienTuoiNhoNhat(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien);
void menuTinhNguyenVien(SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien);

#endif // TINHNGUYENVIEN_H
