#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
using namespace std;

const int soChotoiDa = 50;            // Số chỗ tối đa trong bãi xe
const int DonGiaMoiGio = 10000;       // Đơn giá mỗi giờ gửi xe

// Enum định nghĩa loại vé
enum LoaiVe { VE_LUOT, VE_NGAY, VE_THANG };
// Enum định nghĩa hạng vé
enum HangVe { VE_THUONG, VE_UUTIEN, VE_VIP };

class ChuXe {
private:
    string Hoten;
    string Sodienthoai;

public:
    // Hàm nhập thông tin chủ xe từ bàn phím
    void nhap() {
        cout << "Nhập họ tên chủ xe: ";
        cin.ignore(); 
        getline(cin, Hoten);

        cout << "Nhập số điện thoại chủ xe: ";
        getline(cin, Sodienthoai);
    }

    // Trả về họ tên
    string getHoten() const { return Hoten; }

    // Trả về số điện thoại
    string getSodienthoai() const { return Sodienthoai; }
};
class Ve {
private:
    LoaiVe loaive;
    HangVe hangve;

public:
    // Hàm nhập loại vé và hạng vé từ bàn phím
    void nhap() {
        int loai, hang;

        // Nhập loại vé và kiểm tra hợp lệ
        cout << "Chọn loại vé (0: lượt, 1: ngày, 2: tháng): ";
        while (!(cin >> loai) || loai < 0 || loai > 2) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Vui lòng nhập lại (0-2): ";
        }
        loaive = static_cast<LoaiVe>(loai);

        // Nhập hạng vé và kiểm tra hợp lệ
        cout << "Chọn hạng vé (0: thường, 1: ưu tiên, 2: VIP): ";
        while (!(cin >> hang) || hang < 0 || hang > 2) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Vui lòng nhập lại (0-2): ";
        }
        hangve = static_cast<HangVe>(hang);
    }

    // Trả về loại vé
    LoaiVe getLoaiVe() const { return loaive; }

    // Trả về hạng vé
    HangVe getHangVe() const { return hangve; }
};
class Xe {
private:
    string Bienso;
    time_t tgianvao;
    ChuXe chuxe;
    Ve vexe;

public:
    // Nhập đầy đủ thông tin xe, chủ xe, vé
    void nhap() {
        cout << "Nhập biển số xe: ";
        cin >> Bienso;
        tgianvao = time(0); // Ghi nhận thời gian vào bãi

        chuxe.nhap();
        vexe.nhap();
    }

    // Các phương thức get dữ liệu
    string getBienso() const { return Bienso; }
    time_t getTgianVao() const { return tgianvao; }
    const ChuXe& getChuXe() const { return chuxe; }
    const Ve& getVe() const { return vexe; }
};

// Danh sách các xe đang ở trong bãi
map<string, Xe> danhsachXe;

// Hàm chuyển enum LoaiVe thành chuỗi
string tenLoaiVe(LoaiVe lv) {
    switch (lv) {
        case VE_LUOT: return "Vé lượt";
        case VE_NGAY: return "Vé ngày";
        case VE_THANG: return "Vé tháng";
    }
    return "";
}

// Hàm chuyển enum HangVe thành chuỗi
string tenHangVe(HangVe hv) {
    switch (hv) {
        case VE_THUONG: return "Thường";
        case VE_UUTIEN: return "Ưu tiên";
        case VE_VIP: return "VIP";
    }
    return "";
}

// Hàm xử lý xe vào bãi
void xeVao() {
    if (danhsachXe.size() >= soChotoiDa) {
        cout << "Bãi xe đã đầy, không thể nhận thêm xe mới!\n";
        return;
    }

    string BiensoCheck;
    cout << "Nhập biển số xe: ";
    cin >> BiensoCheck;

    if (danhsachXe.count(BiensoCheck)) {
        cout << "Xe này đã có trong bãi!\n";
        return;
    }

    Xe xeMoi;
    xeMoi.nhap();

    danhsachXe[BiensoCheck] = xeMoi;

   time_t tvao = danhsachXe[BiensoCheck].getTgianVao();
    cout << "Xe đã được thêm vào. Thời gian vào: " << ctime(&tvao);
    cout << "Chủ xe: " << danhsachXe[BiensoCheck].getChuXe().getHoten()
         << ", SĐT: " << danhsachXe[BiensoCheck].getChuXe().getSodienthoai() << endl;
    cout << "Loại vé: " << tenLoaiVe(danhsachXe[BiensoCheck].getVe().getLoaiVe())
         << ", Hạng vé: " << tenHangVe(danhsachXe[BiensoCheck].getVe().getHangVe()) << endl;
}

// Hàm xử lý xe ra khỏi bãi
void xeRa() {
    string Bienso;
    cout << "Nhập biển số xe cần ra: ";
    cin >> Bienso;

    if (!danhsachXe.count(Bienso)) {
        cout << "Không tìm thấy xe trong bãi!\n";
        return;
    }

    time_t tgianHienTai = time(0);
    Xe xe = danhsachXe[Bienso];

    // Tính thời gian gửi xe (đổi giây → giờ)
    double SoGioGuiXe = difftime(tgianHienTai, xe.getTgianVao()) / 3600;
    if (SoGioGuiXe < 1) SoGioGuiXe = 1;

    int PhiGuiXe = 0;
    if (xe.getVe().getLoaiVe() == VE_LUOT) {
        PhiGuiXe = static_cast<int>(SoGioGuiXe) * DonGiaMoiGio;
    } else {
        cout << "Vé ngày/tháng không tính phí theo lượt.\n";
    }

    cout << "Xe ra lúc: " << ctime(&tgianHienTai);
    cout << "Thời gian gửi xe: " << static_cast<int>(SoGioGuiXe) << " giờ\n";
    cout << "Phí gửi xe: " << PhiGuiXe << " VNĐ\n";

    // Xóa xe khỏi danh sách
    danhsachXe.erase(Bienso);
}

// Hàm in danh sách xe đang có trong bãi
void inDanhSachXe() {
    if (danhsachXe.empty()) {
        cout << "Không có xe nào trong bãi!\n";
        return;
    }

    cout << "\nDanh sách xe trong bãi:\n";
    for (const auto& pair : danhsachXe) {
        const Xe& xe = pair.second;

       time_t tg = xe.getTgianVao();
        cout << "Biển số: " << xe.getBienso() << ", Thời gian vào: " << ctime(&tg);
        cout << "Chủ xe: " << xe.getChuXe().getHoten()
             << ", SĐT: " << xe.getChuXe().getSodienthoai() << endl;
        cout << "Loại vé: " << tenLoaiVe(xe.getVe().getLoaiVe())
             << ", Hạng vé: " << tenHangVe(xe.getVe().getHangVe()) << endl;
        cout << "--------------------------------------\n";
    }
}


int main() {
    int luachon;
    do {
        cout << "\n=============== Các chức năng của bãi giữ xe ===============\n";
        cout << "1. Xe vào bãi\n";
        cout << "2. Xe ra khỏi bãi\n";
        cout << "3. Xem danh sách xe trong bãi\n";
        cout << "4. Thoát chương trình\n";
        cout << "- Chọn chức năng (1-4): ";
        cin >> luachon;

        switch(luachon) {
            case 1: xeVao(); break;
            case 2: xeRa(); break;
            case 3: inDanhSachXe(); break;
            case 4: cout << "Đang thoát chương trình... Cảm ơn bạn đã sử dụng!\n"; break;
            default: cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại!\n";
        }
    } while (luachon != 4);

    return 0;
};
