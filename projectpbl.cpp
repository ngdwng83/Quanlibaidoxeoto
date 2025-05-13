#include <iostream>
#include <string>
#include <map>
#include <ctime>
using namespace std;

    const int soChotoiDa = 50;    //Số chỗ gửi xe tối đa 
    const int DonGiaMoiGio = 10000; //Giá mỗi giờ là 10000vnđ

    struct Xe { // Cấu trúc dữ liệu của xe
        string Bienso;
        time_t tgianvao;
    };

    map<string, Xe> danhsachXe;

    void xeVao(){ //Hàm tạo xe mới khi có xe vàovào
        if(danhsachXe.size() >= soChotoiDa) {
            cout << "Bãi xe đã đầy, không thể nhận thêm xe mới!";
            return;
        }
        string  Bienso;
        cout << "Nhập biển số xe: ";
        cin >> Bienso;

        //Kiểm tra xem xe đã có trong bãi chưa
        if(danhsachXe.count(Bienso)){
            cout << "Xe này đã có trong bãi!";
            return;
        }

        time_t tgianHienTai = time(0);
        
        Xe xeMoi;
        xeMoi.Bienso = Bienso;
        xeMoi.tgianvao = tgianHienTai;
        danhsachXe[Bienso] = xeMoi;

        cout << "Xe đã được thêm vào. Thời gian vào: " << ctime(&tgianHienTai);
    }

    void xeRa(){
        string Bienso;
        cout << "Nhập biển số xe cần ra: ";
        cin >> Bienso;

        //Kiểm tra xem xe có trong bãi không
        if(!danhsachXe.count(Bienso)){
            cout << "Không tìm thấy xe trong bãi!\n";
            return;
        }

        time_t tgianHienTai = time(0);
        Xe xe = danhsachXe[Bienso];

        double SoGioGuiXe = difftime(tgianHienTai, xe.tgianvao) / 3600;
        if(SoGioGuiXe < 1) SoGioGuiXe = 1; //Tính số giờ gửi xe ít nhất bằng 1
        int PhiGuiXe = static_cast <int> (SoGioGuiXe) * DonGiaMoiGio;

        cout << "Xe ra lúc: " << ctime(&tgianHienTai) << endl;
        cout << "Thời gian gửi xe: " << static_cast<int>(SoGioGuiXe) << "g" << endl;
        cout << "Phí gửi xe: " << PhiGuiXe << "VNĐ" << endl;

        danhsachXe.erase(Bienso); //Xóa xe khỏi danh sách xe trong bãi
    }

    int main(){
        int luachon;
        do{
            cout << "===============Các chức năng của bãi giữ xe===============\n";
            cout << "1. Xe vào bãi\n";
            cout << "2. Xe ra khỏi bãi\n";
            cout << "3. .......\n";
            cout << "- Chọn chức năng (1-3): ";
            cin >> luachon;

            switch(luachon) {
                case 1: xeVao(); break;
                case 2: xeRa(); break;
                case 3: ; break;
                default: cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại!\n";
            }
        }while(luachon != 3);

        return 0;
    }