#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class KhachHang {
protected:
    string ten;
    string soDienThoai;
    int soPhongDat;
public:
    KhachHang(string ten, string soDienThoai, int soPhongDat) : ten(ten), soDienThoai(soDienThoai), soPhongDat(soPhongDat) {}
    virtual ~KhachHang() {}
    string getTen() const {
        return ten;
    }
    string getSoDienThoai() const {
        return soDienThoai;
    }
    int getSoPhongDat() const {
        return soPhongDat;
    }
    virtual void hienThiThongTin() const {
        cout << "Ten: " << ten << endl;
        cout << "So dien thoai: " << soDienThoai << endl;
        cout << "So phong dat: " << soPhongDat << endl;
    }
};

class KhachHangVip : public KhachHang {
private:
    string uuDai;
public:
    KhachHangVip(string ten, string soDienThoai, int soPhongDat, string uuDai)
        : KhachHang(ten, soDienThoai, soPhongDat), uuDai(uuDai) {}
    string getUuDai() const {
        return uuDai;
    }
    void hienThiThongTin() {
        KhachHang::hienThiThongTin();
        cout << "Uu dai: " << uuDai << endl;
    }
};

class KhachSan {
private:
    string tenKhachSan;
    int soPhong;
    vector<int> giaPhong;
    vector<KhachHang*> danhSachKhachHang;
public:
    KhachSan(string ten, int soPhong);
    ~KhachSan();
    void themKhachSan();
    void hienThiThongTin();
    void suaKhachSan();
    void xoaKhachSan();
    void luuDuLieu();
    void docDuLieu();
    void tinhTongDoanhThu();
    void themKhachHang();
    void hienThiDanhSachKhachHang();
    void hienThiDanhSachKhachHangVip();
    void xoaKhachHang();
};

bool dangNhap(string tenDangNhap, string matKhau) {
    if (tenDangNhap == "Toan" && matKhau == "290105") {
        return true;
    }
    else {
        return false;
    }
}

KhachSan::KhachSan(string ten, int soPhong) {
    tenKhachSan = ten;
    this->soPhong = soPhong;
    giaPhong.resize(soPhong);
}

KhachSan::~KhachSan() {
    for (KhachHang* kh : danhSachKhachHang) {
        delete kh;
    }
}

void KhachSan::themKhachSan() {
    cout << "Nhap gia phong cho tung loai phong" << endl;
    for (int i = 0; i < soPhong; i++) {
        cout << "Gia phong loai " << i + 1 << ": ";
        cin >> giaPhong[i];
    }
    luuDuLieu();
}

void KhachSan::hienThiThongTin() {
    cout << "Ten khach san: " << tenKhachSan << endl;
    cout << "So luong phong: " << soPhong << endl;
    cout << "Gia phong tung loai:" << endl;
    for (int i = 0; i < soPhong; i++) {
        cout << "Loai " << i + 1 << ": " << giaPhong[i] << endl;
    }
}

void KhachSan::suaKhachSan() {
    cout << "Nhap gia phong moi cho tung loai phong" << endl;
    for (int i = 0; i < soPhong; ++i) {
        cout << "Gia phong loai " << i + 1 << ": ";
        cin >> giaPhong[i];
    }
    luuDuLieu();
}

void KhachSan::xoaKhachSan() {

}

void KhachSan::luuDuLieu() {
    ofstream file("khachsan.txt");
    if (!file) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file << tenKhachSan << endl;
    file << soPhong << endl;
    for (int i = 0; i < soPhong; i++) {
        file << giaPhong[i] << " ";
    }
    file << endl;
    file.close();
}

void KhachSan::docDuLieu() {
    ifstream file("khachsan.txt");
    if (!file) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file >> tenKhachSan >> soPhong;
    giaPhong.resize(soPhong);
    for (int i = 0; i < soPhong; ++i) {
        file >> giaPhong[i];
    }

    file.close();
}

void KhachSan::tinhTongDoanhThu() {
    int tongDoanhThu = 0;
    for (const auto& kh : danhSachKhachHang) {
        tongDoanhThu += giaPhong[kh->getSoPhongDat() - 1];
    }
    cout << "Tong doanh thu cua khach san: " << tongDoanhThu << endl;
}

void KhachSan::themKhachHang() {
    string ten, soDienThoai;
    int soPhongDat;
    cout << "Nhap ten khach hang: ";
    cin.ignore();
    getline(cin, ten);
    cout << "Nhap so dien thoai: ";
    cin >> soDienThoai;
    cout << "Nhap so phong da dat: ";
    cin >> soPhongDat;

    KhachHang* kh;
    if (giaPhong[soPhongDat - 1] >= 500) {
        kh = new KhachHangVip(ten, soDienThoai, soPhongDat, "Uu dai dac biet");
    }
    else {
        kh = new KhachHang(ten, soDienThoai, soPhongDat);
    }
    danhSachKhachHang.push_back(kh);
}

void KhachSan::hienThiDanhSachKhachHang() {
    cout << "Danh sach khach hang da dat phong:" << endl;
    for (const auto& kh : danhSachKhachHang) {
        kh->hienThiThongTin();
        cout << "----------------------------" << endl;
    }
}

void KhachSan::hienThiDanhSachKhachHangVip() {
    cout << "Danh sach khach hang VIP:" << endl;
    for (const auto& kh : danhSachKhachHang) {
        if (KhachHangVip* khVip = dynamic_cast<KhachHangVip*>(kh)) {
            khVip->hienThiThongTin();
            cout << "----------------------------" << endl;
        }
    }
}

void KhachSan::xoaKhachHang() {
    string ten;
    cout << "Nhap ten khach hang can xoa: ";
    cin.ignore();
    getline(cin, ten);

    auto it = remove_if(danhSachKhachHang.begin(), danhSachKhachHang.end(), [ten](KhachHang* kh) {
        return kh->getTen() == ten;
        });

    if (it != danhSachKhachHang.end()) {
        delete* it;
        danhSachKhachHang.erase(it, danhSachKhachHang.end());
        cout << "Xoa khach hang thanh cong!" << endl;
    }
    else {
        cout << "Khach hang khong ton tai!" << endl;
    }
}

int main() {
    string tenDangNhap, matKhau;

    do {
        cout << "Nhap ten dang nhap: ";
        cin >> tenDangNhap;

        cout << "Nhap mat khau: ";
        cin >> matKhau;

        if (!dangNhap(tenDangNhap, matKhau)) {
            cout << "Ten dang nhap hoac mat khau sai. Vui long nhap lai!" << endl;
        }
    } while (!dangNhap(tenDangNhap, matKhau));

    cout << "Dang nhap thanh cong!" << endl;

    int luaChon;
    KhachSan ks("Khach San THIEN AN", 5);
    ks.docDuLieu();

    do {
        cout << "              Moi Ban Lua Chon               " << "\n";
        cout << "=============================================" << "\n";
        cout << "|                   MENU                    |" << "\n";
        cout << "=============================================" << "\n";
        cout << "|1. Them khach san                          |" << "\n";
        cout << "|2. Hien thi thong tin khach san            |" << "\n";
        cout << "|3. Sua thong tin khach san                 |" << "\n";
        cout << "|4. Xoa thong tin khach san                 |" << "\n";
        cout << "|5. Xoa thong tin khach hang                |" << "\n";
        cout << "|6. Tinh tong doanh thu                     |" << "\n";
        cout << "|7. Them khach hang                         |" << "\n";
        cout << "|8. Hien thi danh sach khach hang dat phong |" << "\n";
        cout << "|9. Hien thi danh sach khach hang VIP       |" << "\n";
        cout << "|10. Thoat                                  |" << "\n";
        cout << "=============================================" << "\n";

        cout << "Chon chuc nang: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1: {
            string ten;
            int soPhong;
            cout << "Nhap ten khach san: ";
            cin.ignore();
            getline(cin, ten);
            cout << "Nhap so luong phong: ";
            cin >> soPhong;
            ks = KhachSan(ten, soPhong);
            ks.themKhachSan();
            cin.ignore();
            break;
        }
        case 2: {
            cout << "\n----- DANH SACH KHACH SAN -----" << endl;
            ks.hienThiThongTin();
            break;
        }
        case 3: {
            ks.suaKhachSan();
            break;
        }
        case 4: {
            ks.xoaKhachSan();
            break;
        }
        case 5: {
            ks.xoaKhachHang();
            break;
        }
        case 6: {
            ks.tinhTongDoanhThu();
            break;
        }
        case 7: {
            ks.themKhachHang();
            break;
        }
        case 8: {
            ks.hienThiDanhSachKhachHang();
            break;
        }
        case 9: {
            ks.hienThiDanhSachKhachHangVip();
            break;
        }
        case 10: {
            cout << "Tam biet!" << endl;
            break;
        }
        default: {
            cout << "Chon sai! Vui long chon lai." << endl;
            break;
        }
        }
    } while (luaChon != 10);

    return 0;
}

