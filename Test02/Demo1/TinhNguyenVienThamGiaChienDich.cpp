#include "TinhNguyenVienThamGiaChienDich.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>


TinhNguyenVienThamGiaChienDich::TinhNguyenVienThamGiaChienDich(
    const string& maTNV,
    const string& hoLot,
    const string& ten,
    const string& ngaySinhTNV,
    const string& sdt,
    const string& maCD,
    const string& tenCD,
    const string& ngayBD,
    const string& ngayKT
) : maTinhNguyenVien(maTNV), hoLotTinhNguyenVien(hoLot), tenTinhNguyenVien(ten),
ngaySinh(ngaySinhTNV), soDienThoai(sdt), maChienDich(maCD), tenChienDich(tenCD),
ngayBatDau(ngayBD), ngayKetThuc(ngayKT) {

    // Tính tuổi của tình nguyện viên
    tuoiTNV = tinhTuoi(ngaySinhTNV);

    // Tính số ngày chiến dịch
    soNgayChienDich = tinhSoNgayChienDich(ngayBD, ngayKT);
}

// Phương thức tính tuổi của tình nguyện viên

using namespace std;

int TinhNguyenVienThamGiaChienDich::tinhTuoi(const string& ngaySinh) const {
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


// Phương thức tính số ngày chiến dịch
int TinhNguyenVienThamGiaChienDich::tinhSoNgayChienDich(const string& ngayBD, const string& ngayKT) const {
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

// Phương thức hiển thị thông tin tình nguyện viên
void TinhNguyenVienThamGiaChienDich::hienThiThongTin() const {
    cout << left << setw(15) << maTinhNguyenVien
        << setw(20) << hoLotTinhNguyenVien
        << setw(15) << tenTinhNguyenVien
        << setw(12) << ngaySinh
        << setw(15) << soDienThoai
        << setw(15) << maChienDich
        << setw(35) << tenChienDich
        << setw(12) << ngayBatDau
        << setw(12) << ngayKetThuc
        << setw(5) << tuoiTNV
        << setw(5) << soNgayChienDich << endl;
}

// Hàm hiển thị danh sách tình nguyện viên tham gia chiến dịch
void hienThiDanhSachThamGia(
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia
) {
    if (danhSachThamGia.size = 0) {
        cout << "Danh sach Tinh Nguyen Vien tham gia chien dich trong!" << endl;
        return;
    }

    cout << left << setw(15) << "Ma TNV"
        << setw(20) << "Ho Lot"
        << setw(15) << "Ten"
        << setw(12) << "Ngay Sinh"
        << setw(15) << "So DT"
        << setw(15) << "Ma CD"
        << setw(35) << "Ten CD"
        << setw(12) << "Ngay BD"
        << setw(12) << "Ngay KT"
        << setw(5) << "Tuoi"
        << setw(5) << "So Ngay" << endl;

    for (Node<TinhNguyenVienThamGiaChienDich>* node = danhSachThamGia.head;
        node != nullptr; node = node->next) {
        node->data.hienThiThongTin();
    }
}


// Hàm thêm tình nguyện viên vào danh sách tham gia chiến dịch
void nhapTinhNguyenVienThamGiaChienDich(
    SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien,
    SinglyLinkedList<ChienDich>& danhSachChienDich,
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia
) {
    string maTinhNguyenVien;
    string maChienDich;

    // Nhập mã tình nguyện viên và mã chiến dịch
    cout << "Nhap Ma Tinh Nguyen Vien: ";
    cin >> maTinhNguyenVien;
    cout << "Nhap Ma Chien Dich: ";
    cin >> maChienDich;

    themTinhNguyenVienThamGiaChienDich(dsTinhNguyenVien, danhSachChienDich, danhSachThamGia, maChienDich, maTinhNguyenVien);
}

void themTinhNguyenVienThamGiaChienDich(
    SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien,
    SinglyLinkedList<ChienDich>& danhSachChienDich,
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia,
    string maChienDich, string maTinhNguyenVien
) {
    
    // Tìm tình nguyện viên trong danh sách tình nguyện viên
    Node<TinhNguyenVien>* tnNode = dsTinhNguyenVien.head;
    TinhNguyenVien* tinhNguyenVien = nullptr;

    while (tnNode != nullptr) {
        if (tnNode->data.maTinhNguyenVien == maTinhNguyenVien) {
            tinhNguyenVien = &tnNode->data;
            break;
        }
        tnNode = tnNode->next;
    }

    if (tinhNguyenVien == nullptr) {
        cout << "Tinh Nguyen Vien khong ton tai!" << endl;
        return;
    }

    // Tìm chiến dịch trong danh sách chiến dịch
    Node<ChienDich>* cdNode = danhSachChienDich.head;
    ChienDich* chienDich = nullptr;

    while (cdNode != nullptr) {
        if (cdNode->data.maChienDich == maChienDich) {
            chienDich = &cdNode->data;
            break;
        }
        cdNode = cdNode->next;
    }

    if (chienDich == nullptr) {
        cout << "Chien Dich khong ton tai!" << endl;
        return;
    }

    // Nếu tồn tại, thêm vào danh sách tham gia
    danhSachThamGia.addBack(TinhNguyenVienThamGiaChienDich(
        tinhNguyenVien->maTinhNguyenVien,
        tinhNguyenVien->hoLotTinhNguyenVien,
        tinhNguyenVien->tenTinhNguyenVien,
        tinhNguyenVien->ngaySinh,
        tinhNguyenVien->soDienThoai,
        chienDich->maChienDich,
        chienDich->tenChienDich,
        chienDich->ngayBatDau,
        chienDich->ngayKetThuc
    ));

    cout << "Da them Tinh Nguyen Vien vao Chien Dich thanh cong!" << endl;
}

/// <summary>
/// thêm chiến dịch tự động
/// </summary>
/// <param name="dsTinhNguyenVien"></param>
/// <param name="danhSachChienDich"></param>
/// <param name="danhSachThamGia"></param>
void nhapTinhNguyenVienThamGiaChienDichTuDong(
    SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien,
    SinglyLinkedList<ChienDich>& danhSachChienDich,
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia
) {
   
    for (int i = 1; i <= 9; ++i) {
        std::string maChienDich = "CD00" + std::to_string(i);
        for (int j = 1; j <= 9; ++j) {
            std::string maTinhNguyenVien = "TNV00" + std::to_string(j);
            themTinhNguyenVienThamGiaChienDich(dsTinhNguyenVien, danhSachChienDich, danhSachThamGia, maChienDich, maTinhNguyenVien);
        }
    }

    themTinhNguyenVienThamGiaChienDich(dsTinhNguyenVien, danhSachChienDich, danhSachThamGia, "", "");
}

void inputData(SinglyLinkedList<ChienDich>& danhSachChienDich,
    SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien) {
    //giả lập dữ liệu chiến dịch
    danhSachChienDich.addBack(ChienDich("CD001", "Chien dich Mua He Xanh", "01/06/2023", "31/08/2023"));
    danhSachChienDich.addBack(ChienDich("CD002", "Chien dich Mua Xuan", "15/01/2023", "15/04/2023"));
    danhSachChienDich.addBack(ChienDich("CD003", "Chien dich Mua Thu Vang", "01/09/2023", "30/11/2023"));
    danhSachChienDich.addBack(ChienDich("CD004", "Chien dich Mua Dong Am Ap", "01/12/2023", "28/02/2024"));
    danhSachChienDich.addBack(ChienDich("CD005", "Chien dich Trai Tim Hong", "05/05/2023", "05/07/2023"));
    danhSachChienDich.addBack(ChienDich("CD006", "Chien dich Tinh Nguyen", "10/03/2023", "10/06/2023"));
    danhSachChienDich.addBack(ChienDich("CD007", "Chien dich Tiep Suc Mua Thi", "20/06/2023", "20/08/2023"));
    danhSachChienDich.addBack(ChienDich("CD008", "Chien dich Xanh Sach Dep", "01/02/2023", "01/05/2023"));
    danhSachChienDich.addBack(ChienDich("CD009", "Chien dich Bao Ve Moi Truong", "10/04/2023", "10/07/2023"));
    danhSachChienDich.addBack(ChienDich("CD010", "Chien dich Tre Em Viet", "15/05/2023", "15/08/2023"));
    danhSachChienDich.addBack(ChienDich("CD011", "Chien dich Phu Nu Viet", "25/02/2023", "25/05/2023"));
    danhSachChienDich.addBack(ChienDich("CD012", "Chien dich Tri Thuc Tre", "05/03/2023", "05/06/2023"));
    danhSachChienDich.addBack(ChienDich("CD013", "Chien dich Nang Luong Xanh", "10/07/2023", "10/10/2023"));
    danhSachChienDich.addBack(ChienDich("CD014", "Chien dich Kien Thuc Moi", "01/04/2023", "01/07/2023"));
    danhSachChienDich.addBack(ChienDich("CD015", "Chien dich Y Te Cong Dong", "10/08/2023", "10/11/2023"));
    //giả lập dữ liệu tình nguyện viên
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV001", "Nguyen Van", "An", "01/01/1990", "0912345678"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV002", "Tran Thi", "Binh", "15/02/1991", "0923456789"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV003", "Le Van", "Cuong", "20/03/1992", "0934567890"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV004", "Pham Thi", "Dung", "25/04/1993", "0945678901"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV005", "Hoang Van", "Em", "30/05/1994", "0956789012"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV006", "Vu Thi", "Phuong", "10/06/1995", "0967890123"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV007", "Do Van", "Ghi", "05/07/1996", "0978901234"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV008", "Nguyen Thi", "Hoa", "10/08/1997", "0989012345"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV009", "Bui Van", "Khuyen", "15/09/1998", "0990123456"));
    dsTinhNguyenVien.addBack(TinhNguyenVien("TNV010", "Trinh Thi", "Ly", "20/10/1999", "0901234567"));

}

#pragma region Tìm kiếm dữ liệu trên danh sách 
// Hàm tìm kiếm tình nguyện viên theo tiêu chí
void timKiemTinhNguyenVien(
    const SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSach,
    const std::string& tenChienDich,
    const std::string& maTinhNguyenVien,
    const std::string& soDienThoai)
{
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich> ketQua; // LinkedList để lưu kết quả tìm kiếm

    // Duyệt qua từng tình nguyện viên trong danh sách
    Node<TinhNguyenVienThamGiaChienDich>* tnNode = danhSach.head;

    while (tnNode != nullptr) {
        bool thoaMan = true;

        // Kiểm tra từng tiêu chí tìm kiếm
        if (!tenChienDich.empty()) { // Nếu có tên chiến dịch để tìm kiếm
            if (tnNode->data.tenChienDich.find(tenChienDich) == std::string::npos) {
                thoaMan = false; // Không chứa tên chiến dịch
            }
        }

        if (!maTinhNguyenVien.empty()) { // Nếu có mã tình nguyện viên để tìm kiếm
            if (tnNode->data.maTinhNguyenVien != maTinhNguyenVien) {
                thoaMan = false; // Không khớp mã
            }
        }

        if (!soDienThoai.empty()) { // Nếu có số điện thoại để tìm kiếm
            if (tnNode->data.soDienThoai.find(soDienThoai) == std::string::npos) {
                thoaMan = false; // Không chứa số điện thoại
            }
        }

        // Nếu tất cả tiêu chí đều thỏa mãn, thêm vào danh sách kết quả
        if (thoaMan) {
            ketQua.addBack(tnNode->data);
        }

        tnNode = tnNode->next; // Duyệt qua nút tiếp theo
    }

    std::cout << "Ket qua tim kiem theo\n";
    std::cout << "Ten chien dich: " << tenChienDich << "\n";
    std::cout << "Ma tinh nguyen vien: " << maTinhNguyenVien << "\n";
    std::cout << "so dien thoai tinh nguyen vien: " << soDienThoai << "\n";
    hienThiDanhSachThamGia(ketQua);

    //return ketQua; // Trả về danh sách kết quả tìm kiếm
}

// Hàm tìm kiếm theo tất cả tiêu chí theo từ khóa 
// Nhập vào từ khóa và tìm tất cả các field có matching với nó không
void timKiemTongHop(
    const SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSach,
    const std::string& keywords)
{
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich> ketQua; // LinkedList để lưu kết quả tìm kiếm

    // Duyệt qua từng tình nguyện viên trong danh sách
    Node<TinhNguyenVienThamGiaChienDich>* tnNode = danhSach.head;

    while (tnNode != nullptr) {
        bool thoaMan = true;

        // Kiểm tra từng tiêu chí tìm kiếm
        // 
        if (tnNode->data.tenChienDich.find(keywords) == std::string::npos || 
            tnNode->data.hoLotTinhNguyenVien.find(keywords) == std::string::npos ||
            tnNode->data.tenTinhNguyenVien.find(keywords) == std::string::npos ||
            tnNode->data.maChienDich.find(keywords) == std::string::npos ||
            tnNode->data.maTinhNguyenVien.find(keywords) == std::string::npos  
            ) {
            ketQua.addBack(tnNode->data);
        } 

        tnNode = tnNode->next; // Duyệt qua nút tiếp theo
    }

    std::cout << "Ket qua tim kiem theo tu khoa:" << keywords << " \n";
    hienThiDanhSachThamGia(ketQua);

    //return ketQua; // Trả về danh sách kết quả tìm kiếm
}

void nhapThongTinTimKiemVaTimKiem(const SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSach) {
    string tenChienDich, maTinhNguyenVien, soDienThoai;

    // Input prompt for search criteria

    // Input prompt for search criteria
    std::cout << "Nhap ten chien dich (hoac nhan Enter de bo qua): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, tenChienDich);  // Đọc cả dòng để bao gồm cả khoảng trắng

    // Đảm bảo xóa bộ đệm trước khi sử dụng std::getline()

    std::cout << "Nhap ma tinh nguyen vien (hoac nhan Enter de bo qua): ";
    std::getline(std::cin, maTinhNguyenVien);  // Đọc cả dòng để bao gồm cả khoảng trắng

    std::cout << "Nhap so dien thoai (hoac nhan Enter de bo qua): ";
    std::getline(std::cin, soDienThoai);  // Đọc cả dòng để bao gồm cả khoảng trắng

    // Xử lý trường hợp người dùng nhấn Enter để bỏ qua
    if (tenChienDich.empty()) {
        tenChienDich = "";  // If Enter is pressed, treat as empty string
    }
    if (maTinhNguyenVien.empty()) {
        maTinhNguyenVien = "";  // If Enter is pressed, treat as empty string
    }
    if (soDienThoai.empty()) {
        soDienThoai = "";  // If Enter is pressed, treat as empty string
    }

    // In thông tin đã nhập
    std::cout << "Ten Chien Dich: " << tenChienDich << std::endl;
    std::cout << "Ma Tinh Nguyen Vien: " << maTinhNguyenVien << std::endl;
    std::cout << "So Dien Thoai: " << soDienThoai << std::endl;


    // Perform the search using the specified criteria
    timKiemTinhNguyenVien(danhSach, tenChienDich, maTinhNguyenVien, soDienThoai);
     
}
#pragma endregion

#pragma region Lọc danh sách
void danhSachTNVThamGiaTheoChienDich(SinglyLinkedList<ChienDich>& dsChienDich, SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia) {
    if (dsChienDich.head == nullptr) {
        cout << "Danh sách trống." << endl;
        return;
    } 
    Node<ChienDich>* current = dsChienDich.head; 

    // In ra các chiến dịch có số ngày dài nhất
    current = dsChienDich.head; 
    while (current != nullptr) {
        Node<TinhNguyenVienThamGiaChienDich>* currentDSTG = danhSachThamGia.head;
        SinglyLinkedList<TinhNguyenVienThamGiaChienDich> thamGiaChienDich;
        cout << "Chiến dịch: " << current->data.tenChienDich << " - " << current->data.maChienDich << endl;
        while (currentDSTG != nullptr) { 
            if (current->data.maChienDich == currentDSTG->data.maChienDich) {
                thamGiaChienDich.addBack(currentDSTG->data);
            }
            currentDSTG = currentDSTG->next;
        }
        hienThiDanhSachThamGia(thamGiaChienDich);
        cout << "--------------------------------------" << endl;
        current = current->next;
    }

    //xemDanhSach(ketQua);
}

/// <summary>
/// Danh sách tình nguyện viên tham gia nhiều ngày nhất
/// </summary>
/// <param name="dsChienDich"></param>
/// <param name="danhSachThamGia"></param>
void danhSachTNVThamGiaChienDichNhieuNgayNhat(SinglyLinkedList<ChienDich>& dsChienDich, SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia) {
    if (dsChienDich.head == nullptr) {
        cout << "Danh sách trống." << endl;
        return;
    }
    SinglyLinkedList<ChienDich> dsChienDichNhieuNgayNhat;

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
    cout << "So ngay dai nhat cua chien dich la: " << maxSoNgay << " ngay" << endl;
    cout << "Danh sach cac chien dich co so ngay dai nhat:" << endl;
    cout << "--------------------------------------" << endl;
    // In ra các chiến dịch có số ngày dài nhất
    current = dsChienDich.head; 
    while (current != nullptr) {
        if (current->data.soNgayChienDich == maxSoNgay) {
            dsChienDichNhieuNgayNhat.addBack(current->data);
        }
        current = current->next;
    }
    danhSachTNVThamGiaTheoChienDich(dsChienDichNhieuNgayNhat, danhSachThamGia);
}
#pragma endregion


void menuDanhSachThamGia(
    SinglyLinkedList<ChienDich>& danhSachChienDich,
    SinglyLinkedList<TinhNguyenVien>& dsTinhNguyenVien,
    SinglyLinkedList<TinhNguyenVienThamGiaChienDich>& danhSachThamGia
) { 

    int luaChon;

    do {
        cout << "===== Menu Chinh =====" << endl;
        cout << "1. Xem danh sach Tinh Nguyen Vien Tham Gia Chien Dich" << endl;
        cout << "2. Them Tinh Nguyen Vien Tham Gia Chien Dich" << endl;
        cout << "5. Xem danh sách Chien Dich" << endl;
        cout << "6. Xem danh sách Tinh Nguyen Vien" << endl;
        cout << "7. Them Tinh Nguyen Vien Tham Gia Chien Dich tu dong" << endl;
        cout << "8. Nap du lieu tu đong" << endl;
        cout << "9. clear man hinh." << endl;
        cout << "Chuc nang tim kiem" << endl;
        cout << "10. Tim kiem tong hop" << endl;
        cout << "11. Tim kiem theo thong tin theo tieu chi" << endl;
        cout << "Chuc nang hien thi theo danh sach" << endl;
        cout << "21. Thong tin TNV tham gia chien dich nhieu ngay nhat" << endl;

        cout << "0. Quay lai menu truoc" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1:
            hienThiDanhSachThamGia(danhSachThamGia);
            break;
        case 2:
            nhapTinhNguyenVienThamGiaChienDich(dsTinhNguyenVien, danhSachChienDich, danhSachThamGia);
            break;
        case 5:
            xemDanhSach(danhSachChienDich);
            break;
        case 6:
            xemDanhSach(dsTinhNguyenVien);
            break;
        case 7:
            nhapTinhNguyenVienThamGiaChienDichTuDong(dsTinhNguyenVien, danhSachChienDich, danhSachThamGia);
            break;
        case 8:
            inputData(danhSachChienDich, dsTinhNguyenVien);
            nhapTinhNguyenVienThamGiaChienDichTuDong(dsTinhNguyenVien, danhSachChienDich, danhSachThamGia);
            break;
        case 9:
            system("cls");
            break;
        case 10: // chức năng khác 
            break;
        case 11: // Tìm kiếm theo tiêu chí 
            nhapThongTinTimKiemVaTimKiem(danhSachThamGia);
            break;
        // danh sách
        case 20: // In ra màn hình danh sách tình nguyện viên theo tên chiến dịch (tất cả các chiến dịch).
            danhSachTNVThamGiaTheoChienDich(danhSachChienDich, danhSachThamGia);
            break;
        case 21: // Tìm kiếm theo tiêu chí 
            danhSachTNVThamGiaChienDichNhieuNgayNhat(danhSachChienDich, danhSachThamGia);
            break;
        case 0:
            cout << "Quay lai menu truoc." << endl;
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (luaChon != 0);
     
}



