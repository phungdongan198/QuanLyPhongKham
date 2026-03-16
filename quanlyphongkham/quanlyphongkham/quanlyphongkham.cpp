#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

/* ================= UI ================= */
class UI {
public:

	static void setColor(int c) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}
	static void printColor(string text, int color) {

		setColor(color);
		cout << text;
		setColor(7); // trả lại màu mặc định
	}

	static void pause() {
		system("pause");
	}

	static void clear() {
		system("cls");
	}

	static void center(string text, int color = 7) {

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		int padding = (width - text.length()) / 2;

		setColor(color);

		for (int i = 0; i < padding; i++)
			cout << " ";

		cout << text << endl;

		setColor(7);
	}
};

int kiemTraKyTu() {

	int x;

	while (true) {

		if (cin >> x)
			return x;

		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Nhap sai! Vui long nhap so: ";
	}
}

/* ================= DATE ================= */
string today() {

	time_t now = time(0);   // tạo biến now

	tm t;
	localtime_s(&t, &now);

	char buf[20];

	sprintf_s(buf, "%02d/%02d/%04d",
		t.tm_mday,
		t.tm_mon + 1,
		t.tm_year + 1900);

	return string(buf);
}

/* ================= XML HELPER ================= */
bool fileExist(string name) {

	ifstream f(name);
	return f.good();
}

/* ================= BENH NHAN ================= */
class BenhNhan {

public:

	string ma, ten, sinh, gioiTinh;
	string dienThoai, diaChi, doiTuong;
	string phong, ngay;

	void nhap() {

		cin.ignore();

		cout << "Ma BN: ";
		getline(cin, ma);

		cout << "Ten: ";
		getline(cin, ten);

		cout << "Ngay sinh: ";
		getline(cin, sinh);

		cout << "Gioi tinh: ";
		getline(cin, gioiTinh);

		cout << "Dien thoai: ";
		getline(cin, dienThoai);

		cout << "Dia chi: ";
		getline(cin, diaChi);

		cout << "Doi tuong: ";
		getline(cin, doiTuong);

		cout << "Phong kham: ";
		getline(cin, phong);

		ngay = today();
	}

	void save() {

		ofstream file("benhnhan.xml", ios::app);

		file << "<BenhNhan>\n";
		file << "<Ma>" << ma << "</Ma>\n";
		file << "<Ten>" << ten << "</Ten>\n";
		file << "<Sinh>" << sinh << "</Sinh>\n";
		file << "<GioiTinh>" << gioiTinh << "</GioiTinh>\n";
		file << "<DienThoai>" << dienThoai << "</DienThoai>\n";
		file << "<DiaChi>" << diaChi << "</DiaChi>\n";
		file << "<DoiTuong>" << doiTuong << "</DoiTuong>\n";
		file << "<Phong>" << phong << "</Phong>\n";
		file << "<Ngay>" << ngay << "</Ngay>\n";
		file << "</BenhNhan>\n\n";

		file.close();
	}
};

/* ================= PHONG KHAM ================= */
class PhongKham {

public:

	string ma, ten, loai;

	void nhap() {

		cin.ignore();

		cout << "Ma phong: ";
		getline(cin, ma);

		cout << "Ten phong: ";
		getline(cin, ten);

		cout << "Loai phong: ";
		getline(cin, loai);
	}

	void save() {

		ofstream f("phongkham.xml", ios::app);

		f << "<Phong>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<Loai>" << loai << "</Loai>\n";
		f << "</Phong>\n\n";

		f.close();
	}
};

/* ================= BAC SI ================= */
class BacSi {

public:

	string ma, ten, sinh, chungChi, chuyenMon;

	void nhap() {

		cin.ignore();

		cout << "Ma bac si - nhan vien: ";
		getline(cin, ma);

		cout << "Ten: ";
		getline(cin, ten);

		cout << "Ngay sinh: ";
		getline(cin, sinh);

		cout << "Chung chi: ";
		getline(cin, chungChi);

		cout << "Chuyen mon: ";
		getline(cin, chuyenMon);
	}

	void save() {

		ofstream f("bacsi.xml", ios::app);

		f << "<BacSi>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<Sinh>" << sinh << "</Sinh>\n";
		f << "<ChungChi>" << chungChi << "</ChungChi>\n";
		f << "<ChuyenMon>" << chuyenMon << "</ChuyenMon>\n";
		f << "</BacSi>\n\n";

		f.close();
	}
};

/* ================= CAN LAM SANG ================= */
class CanLamSang {

public:

	string ma, ten, gia, ghiChu;

	void nhap() {

		cin.ignore();

		cout << "Ma dich vu: ";
		getline(cin, ma);

		cout << "Ten dich vu: ";
		getline(cin, ten);

		cout << "Don gia: ";
		getline(cin, gia);

		cout << "Ghi chu: ";
		getline(cin, ghiChu);
	}

	void save() {

		ofstream f("canlamsang.xml", ios::app);

		f << "<CLS>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<Gia>" << gia << "</Gia>\n";
		f << "<GhiChu>" << ghiChu << "</GhiChu>\n";
		f << "</CLS>\n\n";

		f.close();
	}
};

/* ================= THUOC ================= */
class nhapThuoc {

public:

	string ma, ten, gia, lo, date, soLuong, ghiChu;

	void nhap() {

		cin.ignore();

		cout << "Ma thuoc: ";
		getline(cin, ma);

		cout << "Ten thuoc: ";
		getline(cin, ten);

		cout << "Don gia: ";
		getline(cin, gia);

		cout << "Lo: ";
		getline(cin, lo);

		cout << "Date: ";
		getline(cin, date);

		cout << "So luong: ";
		getline(cin, soLuong);

		cout << "Ghi chu: ";
		getline(cin, ghiChu);
	}

	void save() {

		ofstream f("nhapthuoc.xml", ios::app);

		f << "<Thuoc>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<Gia>" << gia << "</Gia>\n";
		f << "<Lo>" << lo << "</Lo>\n";
		f << "<Date>" << date << "</Date>\n";
		f << "<SoLuong>" << soLuong << "</SoLuong>\n";
		f << "<GhiChu>" << ghiChu << "</GhiChu>\n";
		f << "</Thuoc>\n\n";

		f.close();
	}
};


class banThuoc {

public:

	string ma, ten, nguoimua, diachi, dienthoai, benh, soluong, dongia, thanhtien, lo, date, ghichu,ngay;

	void ban() {

		cin.ignore();

		cout << "Ma thuoc: ";
		getline(cin, ma);

		cout << "Ten thuoc: ";
		getline(cin, ten);

		cout << "Nguoi mua: ";
		getline(cin, nguoimua);

		cout << "Dai chi: ";
		getline(cin, diachi);

		cout << "Dien thoai: ";
		getline(cin, dienthoai);

		cout << "Ten benh: ";
		getline(cin, benh);

		cout << "So luong: ";
		getline(cin, soluong);

		cout << "Don gia: ";
		getline(cin, dongia);

		cout << "Thanh tien: ";
		getline(cin, thanhtien);

		cout << "Losx: ";
		getline(cin, lo);

		cout << "Date: ";
		getline(cin, date);


		cout << "Ghi chu: ";
		getline(cin, ghichu);

		ngay = today();
	}

	void save() {

		ofstream f("banthuoc.xml", ios::app);

		f << "<BanThuoc>\n";

		f << "<Ma>" << ma << "</Ma>\n";
		f << "<TenThuoc>" << ten << "</TenThuoc>\n";
		f << "<NguoiMua>" << nguoimua << "</NguoiMua>\n";
		f << "<DiaChi>" << diachi << "</DiaChi>\n";
		f << "<DienThoai>" << dienthoai << "</DienThoai>\n";
		f << "<Benh>" << benh << "</Benh>\n";

		f << "<SoLuong>" << soluong << "</SoLuong>\n";
		f << "<DonGia>" << dongia << "</DonGia>\n";
		f << "<ThanhTien>" << thanhtien << "</ThanhTien>\n";

		f << "<Lo>" << lo << "</Lo>\n";
		f << "<Date>" << date << "</Date>\n";
		f << "<GhiChu>" << ghichu << "</GhiChu>\n";
		f << "<Ngay>" << ngay << "</Ngay>\n";

		f << "</BanThuoc>\n\n";

		f.close();
	}
};

/* ================= XEM FILE ================= */

void showTonKho() {

	UI::clear();
	UI::center("TON KHO THUOC", 10);

	/* ================= DANH SACH THUOC DA NHAP ================= */

	cout << "\n===== DANH SACH THUOC DA NHAP =====\n";

	if (!fileExist("nhapthuoc.xml")) {

		cout << "Khong co du lieu thuoc\n";
	}
	else {

		ifstream f("nhapthuoc.xml");

		string line;
		nhapThuoc t;

		cout << "\n--------------------------------------------------------------------------\n";

		cout << left
			<< setw(10) << "Ma"
			<< setw(20) << "TenThuoc"
			<< setw(10) << "Gia"
			<< setw(10) << "SoLuong"
			<< setw(10) << "Lo"
			<< setw(12) << "Date"
			<< setw(20) << "GhiChu"
			<< endl;

		cout << "--------------------------------------------------------------------------\n";

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				t.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				t.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Gia>") != string::npos)
				t.gia = line.substr(5, line.find("</") - 5);

			if (line.find("<Lo>") != string::npos)
				t.lo = line.substr(4, line.find("</") - 4);

			if (line.find("<Date>") != string::npos)
				t.date = line.substr(6, line.find("</") - 6);

			if (line.find("<SoLuong>") != string::npos)
				t.soLuong = line.substr(9, line.find("</") - 9);

			if (line.find("<GhiChu>") != string::npos) {

				t.ghiChu = line.substr(8, line.find("</") - 8);

				cout << left
					<< setw(10) << t.ma
					<< setw(20) << t.ten
					<< setw(10) << t.gia
					<< setw(10) << t.soLuong
					<< setw(10) << t.lo
					<< setw(12) << t.date
					<< setw(20) << t.ghiChu
					<< endl;
			}
		}

		f.close();

		cout << "--------------------------------------------------------------------------\n";
	}

	/* ================= DANH SACH THUOC DA XUAT ================= */

	cout << "\n===== DANH SACH THUOC DA XUAT =====\n";

	if (!fileExist("banthuoc.xml")) {

		cout << "Khong co du lieu ban thuoc\n";
	}
	else {

		ifstream f("banthuoc.xml");

		string line;
		banThuoc b;

		cout << "\n--------------------------------------------------------------------------\n";

		cout << left
			<< setw(10) << "Ma"
			<< setw(20) << "TenThuoc"
			<< setw(20) << "NguoiMua"
			<< setw(10) << "SoLuongBan"
			<< setw(10) << "DonGia"
			<< setw(10) << "ThanhTien"
			<< endl;

		cout << "--------------------------------------------------------------------------\n";

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				b.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<TenThuoc>") != string::npos)
				b.ten = line.substr(10, line.find("</") - 10);

			if (line.find("<NguoiMua>") != string::npos)
				b.nguoimua = line.substr(10, line.find("</") - 10);

			if (line.find("<SoLuong>") != string::npos)
				b.soluong = line.substr(9, line.find("</") - 9);

			if (line.find("<DonGia>") != string::npos)
				b.dongia = line.substr(8, line.find("</") - 8);

			if (line.find("<ThanhTien>") != string::npos) {

				b.thanhtien = line.substr(11, line.find("</") - 11);

				cout << left
					<< setw(10) << b.ma
					<< setw(20) << b.ten
					<< setw(20) << b.nguoimua
					<< setw(10) << b.soluong
					<< setw(10) << b.dongia
					<< setw(10) << b.thanhtien
					<< endl;
			}
		}

		f.close();

		cout << "--------------------------------------------------------------------------\n";
	}

	UI::pause();
}

void seachThuoc() {

	if (!fileExist("nhapthuoc.xml")) {
		cout << "Khong co du lieu thuoc\n";
		UI::pause();
		return;
	}

	int chon;

	cout << "\n===== TIM THUOC =====\n";
	cout << "1 Tim theo ma\n";
	cout << "2 Tim theo ten\n";
	UI::printColor("3 Quay lai\n", 12);

	cout << "Chon: ";
	cin >> chon;

	if (chon == 3)
		return;

	cin.ignore();

	string key;

	if (chon == 1)
		cout << "Nhap ma thuoc: ";
	else
		cout << "Nhap ten thuoc: ";

	getline(cin, key);

	ifstream f("thuoc.xml");

	string line;
	nhapThuoc t;

	vector<nhapThuoc> ds;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			t.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			t.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Gia>") != string::npos)
			t.gia = line.substr(5, line.find("</") - 5);

		if (line.find("<Lo>") != string::npos)
			t.lo = line.substr(4, line.find("</") - 4);

		if (line.find("<Date>") != string::npos)
			t.date = line.substr(6, line.find("</") - 6);

		if (line.find("<SoLuong>") != string::npos)
			t.soLuong = line.substr(9, line.find("</") - 9);

		if (line.find("<GhiChu>") != string::npos) {

			t.ghiChu = line.substr(8, line.find("</") - 8);

			bool match = false;

			if (chon == 1 && t.ma == key)
				match = true;

			if (chon == 2 && t.ten.find(key) != string::npos)
				match = true;

			if (match)
				ds.push_back(t);
		}
	}

	f.close();

	if (ds.empty()) {

		cout << "\nKhong tim thay thuoc!\n";
		UI::pause();
		return;
	}

	cout << "\n--------------------------------------------------------------------------\n";

	cout << left
		<< setw(10) << "Ma"
		<< setw(20) << "TenThuoc"
		<< setw(10) << "Gia"
		<< setw(10) << "SoLuong"
		<< setw(10) << "Lo"
		<< setw(12) << "Date"
		<< setw(20) << "GhiChu"
		<< endl;

	cout << "--------------------------------------------------------------------------\n";

	for (auto& x : ds) {

		cout << left
			<< setw(10) << x.ma
			<< setw(20) << x.ten
			<< setw(10) << x.gia
			<< setw(10) << x.soLuong
			<< setw(10) << x.lo
			<< setw(12) << x.date
			<< setw(20) << x.ghiChu
			<< endl;
	}

	cout << "--------------------------------------------------------------------------\n";

	UI::pause();
}
void exportExcelThuoc() {

	int chon;

	cout << "\n===== XUAT EXCEL =====\n";
	cout << "1 Xuat danh sach thuoc nhap\n";
	cout << "2 Xuat danh sach thuoc ban\n";
	UI::printColor("3 Quay lai\n", 12);

	cout << "Chon: ";
	cin >> chon;

	if (chon == 3)
		return;

	/* ================= XUAT THUOC NHAP ================= */

	if (chon == 1) {

		if (!fileExist("nhapthuoc.xml")) {
			cout << "Khong co du lieu thuoc\n";
			UI::pause();
			return;
		}

		ifstream f("nhapthuoc.xml");
		ofstream o("nhapthuoc.csv");

		string line;
		nhapThuoc t;

		o << "MaThuoc,TenThuoc,DonGia,SoLuong,Lo,Date,GhiChu\n";

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				t.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				t.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Gia>") != string::npos)
				t.gia = line.substr(5, line.find("</") - 5);

			if (line.find("<Lo>") != string::npos)
				t.lo = line.substr(4, line.find("</") - 4);

			if (line.find("<Date>") != string::npos)
				t.date = line.substr(6, line.find("</") - 6);

			if (line.find("<SoLuong>") != string::npos)
				t.soLuong = line.substr(9, line.find("</") - 9);

			if (line.find("<GhiChu>") != string::npos) {

				t.ghiChu = line.substr(8, line.find("</") - 8);

				o << t.ma << ","
					<< t.ten << ","
					<< t.gia << ","
					<< t.soLuong << ","
					<< t.lo << ","
					<< t.date << ","
					<< t.ghiChu << "\n";
			}
		}

		f.close();
		o.close();

		cout << "\nDa xuat file thuocnhap.csv\n";
		char ch;

		cout << "Ban co muon mo file khong? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start thuocnhap.csv");
	}

	/* ================= XUAT THUOC BAN ================= */

	else if (chon == 2) {

		if (!fileExist("banthuoc.xml")) {
			cout << "Khong co du lieu ban thuoc\n";
			UI::pause();
			return;
		}

		ifstream f("banthuoc.xml");
		ofstream o("thuocban.csv");

		string line;
		banThuoc b;

		o << "MaThuoc,TenThuoc,NguoiMua,SoLuong,DonGia,ThanhTien\n";

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				b.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<TenThuoc>") != string::npos)
				b.ten = line.substr(10, line.find("</") - 10);

			if (line.find("<NguoiMua>") != string::npos)
				b.nguoimua = line.substr(10, line.find("</") - 10);

			if (line.find("<SoLuong>") != string::npos)
				b.soluong = line.substr(9, line.find("</") - 9);

			if (line.find("<DonGia>") != string::npos)
				b.dongia = line.substr(8, line.find("</") - 8);

			if (line.find("<ThanhTien>") != string::npos) {

				b.thanhtien = line.substr(11, line.find("</") - 11);

				o << b.ma << ","
					<< b.ten << ","
					<< b.nguoimua << ","
					<< b.soluong << ","
					<< b.dongia << ","
					<< b.thanhtien << "\n";
			}
		}

		f.close();
		o.close();

		cout << "\nDa xuat file thuocban.csv\n";
		char ch;

		cout << "Ban co muon mo file khong? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start thuocban.csv");
	}

	UI::pause();
}



void showBacSi() {

	if (!fileExist("bacsi.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("bacsi.xml");

	string line;
	BacSi bs;

	vector<BacSi> ds;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			bs.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			bs.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Sinh>") != string::npos)
			bs.sinh = line.substr(6, line.find("</") - 6);

		if (line.find("<ChungChi>") != string::npos)
			bs.chungChi = line.substr(10, line.find("</") - 10);

		if (line.find("<ChuyenMon>") != string::npos) {

			bs.chuyenMon = line.substr(11, line.find("</") - 11);

			ds.push_back(bs);
		}
	}

	f.close();

	cout << "\n-----------------------------------------------------------------------\n";

	cout << left
		<< setw(10) << "MaBS"
		<< setw(20) << "TenBacSi"
		<< setw(15) << "NgaySinh"
		<< setw(15) << "ChungChi"
		<< setw(20) << "ChuyenMon"
		<< endl;

	cout << "-----------------------------------------------------------------------\n";

	for (auto& b : ds) {

		cout << left
			<< setw(10) << b.ma
			<< setw(20) << b.ten
			<< setw(15) << b.sinh
			<< setw(15) << b.chungChi
			<< setw(20) << b.chuyenMon
			<< endl;
	}

	cout << "-----------------------------------------------------------------------\n";

	UI::pause();
}

void searchBacSi() {

	if (!fileExist("bacsi.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	int chon;

	cout << "\n===== TIM BAC SI =====\n";
	cout << "1 Tim theo ma\n";
	cout << "2 Tim theo ten\n";
	UI::printColor("3 Quay lai\n", 12);

	cout << "Chon: ";
	cin >> chon;

	if (chon == 3)
		return;

	cin.ignore();

	string key;

	if (chon == 1)
		cout << "Nhap ma bac si: ";
	else
		cout << "Nhap ten bac si: ";

	getline(cin, key);

	ifstream f("bacsi.xml");

	string line;
	BacSi bs;

	vector<BacSi> ds;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			bs.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			bs.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Sinh>") != string::npos)
			bs.sinh = line.substr(6, line.find("</") - 6);

		if (line.find("<ChungChi>") != string::npos)
			bs.chungChi = line.substr(10, line.find("</") - 10);

		if (line.find("<ChuyenMon>") != string::npos) {

			bs.chuyenMon = line.substr(11, line.find("</") - 11);

			bool match = false;

			if (chon == 1 && bs.ma == key)
				match = true;

			if (chon == 2 && bs.ten.find(key) != string::npos)
				match = true;

			if (match)
				ds.push_back(bs);
		}
	}

	f.close();

	if (ds.empty()) {

		cout << "Khong tim thay\n";
		UI::pause();
		return;
	}

	cout << "\n-----------------------------------------------------------------------\n";

	cout << left
		<< setw(10) << "MaBS"
		<< setw(20) << "TenBacSi"
		<< setw(15) << "NgaySinh"
		<< setw(15) << "ChungChi"
		<< setw(20) << "ChuyenMon"
		<< endl;

	cout << "-----------------------------------------------------------------------\n";

	for (auto& b : ds) {

		cout << left
			<< setw(10) << b.ma
			<< setw(20) << b.ten
			<< setw(15) << b.sinh
			<< setw(15) << b.chungChi
			<< setw(20) << b.chuyenMon
			<< endl;
	}

	cout << "-----------------------------------------------------------------------\n";

	UI::pause();
}

void exportExceBacSi() {

	if (!fileExist("bacsi.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("bacsi.xml");
	ofstream o("bacsi.csv");

	string line;
	BacSi bs;

	o << "MaBS,TenBacSi,NgaySinh,ChungChi,ChuyenMon\n";

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			bs.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			bs.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Sinh>") != string::npos)
			bs.sinh = line.substr(6, line.find("</") - 6);

		if (line.find("<ChungChi>") != string::npos)
			bs.chungChi = line.substr(10, line.find("</") - 10);

		if (line.find("<ChuyenMon>") != string::npos) {

			bs.chuyenMon = line.substr(11, line.find("</") - 11);

			o << bs.ma << ","
				<< bs.ten << ","
				<< bs.sinh << ","
				<< bs.chungChi << ","
				<< bs.chuyenMon << "\n";
		}
	}

	f.close();
	o.close();

	cout << "\nXuat Excel thanh cong: bacsi.csv\n";

	char ch;

	cout << "Ban co muon mo file khong? (Y/N): ";
	cin >> ch;

	if (ch == 'Y' || ch == 'y')
		system("start bacsi.csv");

	UI::pause();
}


void showCLS() {

	if (!fileExist("canlamsang.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("canlamsang.xml");

	string line;
	CanLamSang cls;

	vector<CanLamSang> ds;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			cls.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			cls.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Gia>") != string::npos)
			cls.gia = line.substr(5, line.find("</") - 5);

		if (line.find("<GhiChu>") != string::npos) {

			cls.ghiChu = line.substr(8, line.find("</") - 8);

			ds.push_back(cls);
		}
	}

	f.close();

	cout << "\n-------------------------------------------------------------\n";

	cout << left
		<< setw(15) << "MaDV"
		<< setw(25) << "TenDichVu"
		<< setw(10) << "DonGia"
		<< setw(20) << "GhiChu"
		<< endl;

	cout << "-------------------------------------------------------------\n";

	for (auto& c : ds) {

		cout << left
			<< setw(15) << c.ma
			<< setw(25) << c.ten
			<< setw(10) << c.gia
			<< setw(20) << c.ghiChu
			<< endl;
	}

	cout << "-------------------------------------------------------------\n";

	UI::pause();
}

void searchCLS() {

	if (!fileExist("canlamsang.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	int chon;

	cout << "\n===== TIM CAN LAM SANG =====\n";
	cout << "1 Tim theo ma\n";
	cout << "2 Tim theo ten\n";
	UI::printColor("3 Quay lai\n", 12);

	cout << "Chon: ";
	cin >> chon;

	if (chon == 3)
		return;

	cin.ignore();

	string key;

	if (chon == 1)
		cout << "Nhap ma dich vu: ";
	else
		cout << "Nhap ten dich vu: ";

	getline(cin, key);

	ifstream f("canlamsang.xml");

	string line;
	vector<CanLamSang> ds;
	CanLamSang cls;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			cls.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			cls.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Gia>") != string::npos)
			cls.gia = line.substr(5, line.find("</") - 5);

		if (line.find("<GhiChu>") != string::npos) {

			cls.ghiChu = line.substr(8, line.find("</") - 8);

			bool match = false;

			if (chon == 1 && cls.ma == key)
				match = true;

			if (chon == 2 && cls.ten.find(key) != string::npos)
				match = true;

			if (match)
				ds.push_back(cls);
		}
	}

	f.close();

	if (ds.empty()) {

		cout << "Khong tim thay\n";
		UI::pause();
		return;
	}

	cout << "\n-------------------------------------------------------------\n";

	cout << left
		<< setw(15) << "MaDV"
		<< setw(25) << "TenDichVu"
		<< setw(10) << "DonGia"
		<< setw(20) << "GhiChu"
		<< endl;

	cout << "-------------------------------------------------------------\n";

	for (auto& c : ds) {

		cout << left
			<< setw(15) << c.ma
			<< setw(25) << c.ten
			<< setw(10) << c.gia
			<< setw(20) << c.ghiChu
			<< endl;
	}

	cout << "-------------------------------------------------------------\n";

	UI::pause();
}

void exportExceCLS() {

	if (!fileExist("canlamsang.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("canlamsang.xml");
	ofstream o("canlamsang.csv");

	string line;
	CanLamSang cls;

	o << "MaDV,TenDichVu,DonGia,GhiChu\n";

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			cls.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			cls.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Gia>") != string::npos)
			cls.gia = line.substr(5, line.find("</") - 5);

		if (line.find("<GhiChu>") != string::npos) {

			cls.ghiChu = line.substr(8, line.find("</") - 8);

			o << cls.ma << ","
				<< cls.ten << ","
				<< cls.gia << ","
				<< cls.ghiChu << "\n";
		}
	}

	f.close();
	o.close();

	cout << "\nXuat Excel thanh cong: canlamsang.csv\n";

	char ch;

	cout << "Ban co muon mo file khong? (Y/N): ";
	cin >> ch;

	if (ch == 'Y' || ch == 'y')
		system("start canlamsang.csv");

	UI::pause();
}


void showPhongKham() {

	if (!fileExist("phongkham.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("phongkham.xml");

	string line;
	PhongKham pk;

	vector<PhongKham> ds;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			pk.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			pk.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Loai>") != string::npos) {

			pk.loai = line.substr(6, line.find("</") - 6);

			ds.push_back(pk);
		}
	}

	f.close();

	cout << "\n--------------------------------------------------\n";

	cout << left
		<< setw(15) << "MaPhong"
		<< setw(25) << "TenPhong"
		<< setw(20) << "LoaiPhong"
		<< endl;

	cout << "--------------------------------------------------\n";

	for (auto& p : ds) {

		cout << left
			<< setw(15) << p.ma
			<< setw(25) << p.ten
			<< setw(20) << p.loai
			<< endl;
	}

	cout << "--------------------------------------------------\n";

	UI::pause();
}
void searchPhongkham() {
	int c;
	if (!fileExist("phongkham.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}


	cout << "\n===== TIM PHONG KHAM =====\n";
	cout << "1 Tim theo ma\n";
	cout << "2 Tim theo ten\n";
	UI::printColor("3 Quay lai\n", 12);

	cout << "Chon: ";
	c = kiemTraKyTu();


	if (c == 3)
		return;

	cin.ignore();

	string key;

	if (c == 1)
		cout << "Nhap ma phong: ";
	else
		cout << "Nhap ten phong: ";

	getline(cin, key);

	ifstream f("phongkham.xml");

	string line;
	vector<PhongKham> ds;
	PhongKham pk;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			pk.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			pk.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Loai>") != string::npos) {

			pk.loai = line.substr(6, line.find("</") - 6);

			bool match = false;

			if (c == 1 && pk.ma == key)
				match = true;

			if (c == 2 && pk.ten.find(key) != string::npos)
				match = true;

			if (match)
				ds.push_back(pk);
		}
	}

	f.close();

	if (ds.empty()) {

		cout << "\nKhong tim thay!\n";
		UI::pause();
		return;
	}

	cout << "\n--------------------------------------------------\n";

	cout << left
		<< setw(15) << "MaPhong"
		<< setw(25) << "TenPhong"
		<< setw(20) << "LoaiPhong"
		<< endl;

	cout << "--------------------------------------------------\n";

	for (auto& p : ds) {

		cout << left
			<< setw(15) << p.ma
			<< setw(25) << p.ten
			<< setw(20) << p.loai
			<< endl;
	}

	cout << "--------------------------------------------------\n";

	UI::pause();
}

void exportExcePhongKham() {

	if (!fileExist("phongkham.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("phongkham.xml");
	ofstream o("phongkham.csv");

	string line;
	PhongKham pk;

	/* header excel */
	o << "MaPhong,TenPhong,LoaiPhong\n";

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			pk.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			pk.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Loai>") != string::npos) {

			pk.loai = line.substr(6, line.find("</") - 6);

			o << pk.ma << ","
				<< pk.ten << ","
				<< pk.loai << "\n";
		}
	}

	f.close();
	o.close();

	cout << "\nXuat Excel thanh cong: phongkham.csv\n";

	char ch;

	cout << "Ban co muon mo file khong? (Y/N): ";
	cin >> ch;

	if (ch == 'Y' || ch == 'y')
		system("start phongkham.csv");

	UI::pause();
}

void showBenhNhan() {

	if (!fileExist("benhnhan.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("benhnhan.xml");

	string line;
	BenhNhan bn;

	vector<BenhNhan> ds;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			bn.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			bn.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Sinh>") != string::npos)
			bn.sinh = line.substr(6, line.find("</") - 6);

		if (line.find("<Phong>") != string::npos)
			bn.phong = line.substr(7, line.find("</") - 7);

		if (line.find("<Ngay>") != string::npos) {

			bn.ngay = line.substr(6, line.find("</") - 6);

			ds.push_back(bn);
		}
	}

	f.close();

	cout << "\n--------------------------------------------------------------------------------\n";

	cout << left
		<< setw(10) << "MaBN"
		<< setw(20) << "Ten"
		<< setw(15) << "NgaySinh"
		<< setw(15) << "Phong"
		<< setw(15) << "NgayKham"
		<< endl;

	cout << "--------------------------------------------------------------------------------\n";

	for (auto& b : ds) {

		cout << left
			<< setw(10) << b.ma
			<< setw(20) << b.ten
			<< setw(15) << b.sinh
			<< setw(15) << b.phong
			<< setw(15) << b.ngay
			<< endl;
	}

	cout << "--------------------------------------------------------------------------------\n";
	UI::pause();
}

/* ================= TIM KIEM ================= */
void searchBenhNhan() {
	int c;
	if (!fileExist("benhnhan.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}


	cout << "\n===== TIM KIEM BENH NHAN =====\n";
	cout << "1. Tim theo ma (tuyet doi)\n";
	cout << "2. Tim theo ten (tuong doi)\n";
	UI::printColor("3 Quay lai\n", 12);

	cout << "Chon: "; ;
	c = kiemTraKyTu();

	if (c == 3) return;

	cin.ignore();

	string key;

	if (c == 1)
		cout << "Nhap ma benh nhan: ";
	else
		cout << "Nhap ten can tim: ";

	getline(cin, key);

	ifstream f("benhnhan.xml");

	string line;
	vector<BenhNhan> ds;
	BenhNhan bn;

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			bn.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			bn.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Sinh>") != string::npos)
			bn.sinh = line.substr(6, line.find("</") - 6);

		if (line.find("<Phong>") != string::npos)
			bn.phong = line.substr(7, line.find("</") - 7);

		if (line.find("<Ngay>") != string::npos) {

			bn.ngay = line.substr(6, line.find("</") - 6);

			bool match = false;

			if (c == 1 && bn.ma == key)
				match = true;

			if (c == 2 && bn.ten.find(key) != string::npos)
				match = true;

			if (match)
				ds.push_back(bn);
		}
	}

	f.close();

	if (ds.empty()) {

		cout << "\nKhong tim thay!\n";
		UI::pause();
		return;
	}

	cout << "\n--------------------------------------------------------------------------------\n";

	cout << left
		<< setw(10) << "MaBN"
		<< setw(20) << "Ten"
		<< setw(15) << "NgaySinh"
		<< setw(15) << "Phong"
		<< setw(15) << "NgayKham"
		<< endl;

	cout << "--------------------------------------------------------------------------------\n";

	for (auto& b : ds) {

		cout << left
			<< setw(10) << b.ma
			<< setw(20) << b.ten
			<< setw(15) << b.sinh
			<< setw(15) << b.phong
			<< setw(15) << b.ngay
			<< endl;
	}

	cout << "--------------------------------------------------------------------------------\n";
	UI::pause();

	UI::pause();
}

/* ================= EXPORT CSV ================= */
void exportExcelBenhNhan() {

	if (!fileExist("benhnhan.xml")) {
		cout << "Khong co du lieu\n";
		UI::pause();
		return;
	}

	ifstream f("benhnhan.xml");
	ofstream o("benhnhan.csv");

	string line;
	BenhNhan bn;

	/* header excel */
	o << "MaBN,Ten,NgaySinh,GioiTinh,DienThoai,DiaChi,DoiTuong,Phong,NgayKham\n";

	while (getline(f, line)) {

		if (line.find("<Ma>") != string::npos)
			bn.ma = line.substr(4, line.find("</") - 4);

		if (line.find("<Ten>") != string::npos)
			bn.ten = line.substr(5, line.find("</") - 5);

		if (line.find("<Sinh>") != string::npos)
			bn.sinh = line.substr(6, line.find("</") - 6);

		if (line.find("<GioiTinh>") != string::npos)
			bn.gioiTinh = line.substr(10, line.find("</") - 10);

		if (line.find("<DienThoai>") != string::npos)
			bn.dienThoai = line.substr(11, line.find("</") - 11);

		if (line.find("<DiaChi>") != string::npos)
			bn.diaChi = line.substr(8, line.find("</") - 8);

		if (line.find("<DoiTuong>") != string::npos)
			bn.doiTuong = line.substr(10, line.find("</") - 10);

		if (line.find("<Phong>") != string::npos)
			bn.phong = line.substr(7, line.find("</") - 7);

		if (line.find("<Ngay>") != string::npos) {

			bn.ngay = line.substr(6, line.find("</") - 6);

			o << bn.ma << ","
				<< bn.ten << ","
				<< bn.sinh << ","
				<< bn.gioiTinh << ","
				<< bn.dienThoai << ","
				<< bn.diaChi << ","
				<< bn.doiTuong << ","
				<< bn.phong << ","
				<< bn.ngay << "\n";
		}
	}

	f.close();
	o.close();

	cout << "\nXuat Excel thanh cong: benhnhan.csv\n";

	char ch;

	cout << "Ban co muon mo file khong? (Y/N): ";
	cin >> ch;

	if (ch == 'Y' || ch == 'y')
		system("start benhnhan.csv");

	UI::pause();
}

/* ================= MENU ================= */
class SystemPK {

public:

	void menuBenhNhan() {

		int c;

		do {

			UI::clear();
			UI::center("=====BENH NHAN=====", 10);

			cout << "\n1 Nhap benh nhan kham benh\n";
			cout << "2 Xem danh sach benh nhan da kham\n";
			cout << "3 Tim benh nhan\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = kiemTraKyTu();

			switch (c) {

			case 1: {

				BenhNhan b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				showBenhNhan();
				break;

			case 3:

				searchBenhNhan();
				break;

			case 4:

				exportExcelBenhNhan();
				break;
			}

		} while (c != 5);
	}

	void menuPhongKham() {

		int c;

		do {

			UI::clear();
			UI::center("=====PHONG KHAM=====", 10);

			cout << "\n1 Khai bao phong kham\n";
			cout << "2 Xem danh sach cac phong kham\n";
			cout << "3 Tim phong kham\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = kiemTraKyTu();

			switch (c) {

			case 1: {

				PhongKham b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				showPhongKham();
				break;

			case 3:

				searchPhongkham();
				break;

			case 4:

				exportExcePhongKham();
				break;
			}

		} while (c != 5);
	}

	void menuBacSi() {

		int c;

		do {

			UI::clear();
			UI::center("=====BAC SI - NHAN VIEN=====", 10);

			cout << "\n1 Khai bao bac si - nhan vien\n";
			cout << "2 Xem danh sach\n";
			cout << "3 Tim kiem\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = kiemTraKyTu();

			switch (c) {

			case 1: {

				BacSi b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				showBacSi();
				break;

			case 3:

				searchBacSi();
				break;

			case 4:

				exportExceBacSi();
				break;
			}

		} while (c != 5);
	}

	void menuCanLamSang() {

		int c;

		do {

			UI::clear();
			UI::center("=====CAN LAM SANG=====", 10);

			cout << "\n1 Khai bao can lam sang\n";
			cout << "2 Xem danh sach can lam sang\n";
			cout << "3 Tim dich vu CLS\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = kiemTraKyTu();

			switch (c) {

			case 1: {

				CanLamSang b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				showCLS();
				break;

			case 3:

				searchCLS();
				break;

			case 4:

				exportExceCLS();
				break;
			}

		} while (c != 5);
	}

	void menuThuoc() {

		int c;

		do {

			UI::clear();
			UI::center("=====KHO THUOC=====", 10);

			cout << "\n1 Nhap thuoc\n";
			cout << "2 Ban thuoc\n";
			cout << "3 Xem ton kho\n";
			cout << "4 Tim thuoc\n";
			cout << "5 Xuat excel\n";
			UI::printColor("6 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = kiemTraKyTu();

			switch (c) {

			case 1: {

				nhapThuoc b;
				b.nhap();
				b.save();

				break;
			}

			case 2: {

				banThuoc b;
				b.ban();
				b.save();
				break;
			}

			case 3:

				showTonKho();
				break;

			case 4:

				seachThuoc();
				break;
			case 5:

				exportExcelThuoc();
				break;
			}


		} while (c != 6);
	}
	bool kiemTraNgay(string ngay) {

		if (ngay.length() != 10)
			return false;

		if (ngay[2] != '/' || ngay[5] != '/')
			return false;

		int dd = stoi(ngay.substr(0, 2));
		int mm = stoi(ngay.substr(3, 2));
		int yyyy = stoi(ngay.substr(6, 4));

		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);

		int namHienTai = t.tm_year + 1900;

		if (dd < 1 || dd > 31)
			return false;

		if (mm < 1 || mm > 12)
			return false;

		if (yyyy < 1000 || yyyy > namHienTai)
			return false;

		return true;
	}


	string nhapNgayDung() {

		string ngay;

		while (true) {

			cout << "Nhap ngay (dd/mm/yyyy): ";
			getline(cin, ngay);

			if (kiemTraNgay(ngay))
				return ngay;

			cout << "Ngay khong hop le! Vui long nhap lai.\n";
		}
	}

	void thongKeTheoNgay() {

		if (!fileExist("benhnhan.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		cin.ignore();

		string ngay = nhapNgayDung();

		ifstream f("benhnhan.xml");

		string line;
		int dem = 0;

		while (getline(f, line)) {

			if (line.find("<Ngay>") != string::npos) {

				string ngayFile = line.substr(6, line.find("</") - 6);

				if (ngayFile == ngay)
					dem++;
			}
		}

		f.close();

		cout << "\nNgay " << ngay << " co " << dem << " ca kham\n";

		UI::pause();
	}

	void soSanhHomNayHomQua() {

		if (!fileExist("benhnhan.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		time_t now = time(0);

		tm today_tm;
		localtime_s(&today_tm, &now);

		tm yesterday_tm = today_tm;
		yesterday_tm.tm_mday -= 1;

		mktime(&yesterday_tm);

		char todayStr[20];
		char yesterdayStr[20];

		sprintf_s(todayStr, "%02d/%02d/%04d",
			today_tm.tm_mday,
			today_tm.tm_mon + 1,
			today_tm.tm_year + 1900);

		sprintf_s(yesterdayStr, "%02d/%02d/%04d",
			yesterday_tm.tm_mday,
			yesterday_tm.tm_mon + 1,
			yesterday_tm.tm_year + 1900);

		ifstream f("benhnhan.xml");

		string line;
		int homnay = 0;
		int homqua = 0;

		while (getline(f, line)) {

			if (line.find("<Ngay>") != string::npos) {

				string ngayFile = line.substr(6, line.find("</") - 6);

				if (ngayFile == todayStr)
					homnay++;

				if (ngayFile == yesterdayStr)
					homqua++;
			}
		}

		f.close();

		cout << "\nHom nay (" << todayStr << ") : " << homnay << " ca\n";
		cout << "Hom qua (" << yesterdayStr << ") : " << homqua << " ca\n";

		if (homnay > homqua)
			cout << "Tang " << homnay - homqua << " ca\n";
		else if (homnay < homqua)
			cout << "Giam " << homqua - homnay << " ca\n";
		else
			cout << "Khong thay doi\n";

		UI::pause();
	}

	void thongKeTienThuocTheoNgay() {

		if (!fileExist("banthuoc.xml")) {
			cout << "Khong co du lieu ban thuoc\n";
			UI::pause();
			return;
		}

		cin.ignore();

		string ngay = nhapNgayDung();

		ifstream f("banthuoc.xml");

		string line;
		banThuoc b;

		long long tongTien = 0;

		while (getline(f, line)) {

			if (line.find("<ThanhTien>") != string::npos)
				b.thanhtien = line.substr(11, line.find("</") - 11);

			if (line.find("<Ngay>") != string::npos) {

				b.date = line.substr(6, line.find("</") - 6);

				if (b.date == ngay)
					tongTien += stoll(b.thanhtien);
			}
		}

		f.close();

		cout << "\nTong tien thuoc ban ngay " << ngay << " = " << tongTien << " VND\n";

		UI::pause();
	}

	void menuThongKe() {

		int c;

		do {

			UI::clear();
			UI::center("===== THONG KE =====", 10);

			cout << "\n1 Thong ke so ca kham theo ngay";
			cout << "\n2 So sanh hom nay voi hom qua";
			cout << "\n3 Tong tien ban thuoc";
			UI::printColor("\n4 Quay lai\n", 12);

			cout << "\nChon: ";
			c = kiemTraKyTu();

			switch (c) {

			case 1:
				thongKeTheoNgay();
				break;

			case 2:
				soSanhHomNayHomQua();
				break;

			case 3:
				thongKeTienThuocTheoNgay();
				break;
			}

		} while (c != 4);
	}

	void menuChinh() {

		int c;

		do {

			UI::clear();
			UI::center("=====HE THONG QUAN LY PHONG KHAM=====", 10);

			cout << "\n1 Quan ly Benh nhan";
			cout << "\n2 Quan ly phong kham";
			cout << "\n3 Quan ly bac si - nhan vien";
			cout << "\n4 Quan ly can lam sang";
			cout << "\n5 Quan ly thuoc";
			cout << "\n6 Thong Ke";
			UI::printColor("\n7 Thoat\n", 12);

			cout << "\nChon: ";
			cin >> c;

			switch (c) {

			case 1:
				menuBenhNhan();
				break;

			case 2: {

				menuPhongKham();
				break;
			}

			case 3: {

				menuBacSi();
				break;
			}

			case 4: {

				menuCanLamSang();
				break;
			}

			case 5: {

				menuThuoc();
				break;
			}
			case 6: {

				menuThongKe();
				break;
			}

			}

		} while (c != 7);
	}
};

/* ================= MAIN ================= */
int main() {

	SystemPK sys;

	sys.menuChinh();

	return 0;
}