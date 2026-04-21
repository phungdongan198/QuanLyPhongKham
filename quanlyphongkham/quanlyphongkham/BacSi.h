#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"
#include "QuanLy.h"
#include "SystemMethod.h"


// tính kế thừa
class BacSi : public DoiTuongQuanLy {

public:

	string ma, ten, sinh, chungChi, chuyenMon;
	// đa hình
	void nhap() override {

		cin.ignore();

		ma = Helper::nhapMaKhongTrung(
			"Ma BS - NV: ",
			"bacsi.xml",
			"BacSi",
			"Ma"
		);

		cout << "Ten: ";
		getline(cin, ten);

		sinh = NhapVaKiemTraNamSinh();

		cout << "Chung chi: ";
		getline(cin, chungChi);

		cout << "Chuyen mon: ";
		getline(cin, chuyenMon);
	}

	void save() override {

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

	// nạp chồng toán tử
	friend ostream& operator<<(ostream& out, const BacSi& bs) {
		out << left
			<< setw(10) << bs.ma
			<< setw(25) << bs.ten
			<< setw(15) << bs.sinh
			<< setw(20) << bs.chungChi
			<< setw(20) << bs.chuyenMon;

		return out;
	}

public:
	BacSi() {
		ma = ten = sinh = chungChi = chuyenMon = "";
	}

	BacSi(string ma, string ten, string sinh, string chungChi, string chuyenMon) {
		this->ma = ma;
		this->ten = ten;
		this->sinh = sinh;
		this->chungChi = chungChi;
		this->chuyenMon = chuyenMon;
	}

	static void showBacSi() {

		if (!SystemMethod::fileExist("bacsi.xml")) {
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
			
			cout << b << endl;
		}

		cout << "-----------------------------------------------------------------------\n";

		UI::pause();
	}

	void hienThi() override {
		cout << left
			<< setw(10) << ma
			<< setw(25) << ten
			<< setw(15) << sinh
			<< setw(20) << chungChi
			<< setw(20) << chuyenMon
			<< endl;
	}

	static void searchBacSi() {

		if (!SystemMethod::fileExist("bacsi.xml")) {
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
		string lowerKey = SystemMethod::toLower(key);

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

				if (chon == 1 && SystemMethod::toLower(bs.ma) == key)
				{
					match = true;
				}
				if (chon == 2 && SystemMethod::toLower(bs.ten).find(key) != string::npos)
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

	static void exportExceBacSi() {

		if (!SystemMethod::fileExist("bacsi.xml")) {
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

	string NhapVaKiemTraNamSinh() {
		int dd, mm, yyyy;
		char slash1, slash2;

		while (true) {
			cout << "Nhap ngay sinh (Voi dinh dang dd / mm / yyyy): ";

			// Đọc dữ liệu theo định dạng dd / mm / yyyy
			if (cin >> dd >> slash1 >> mm >> slash2 >> yyyy && slash1 == '/' && slash2 == '/') {

				// Kiểm tra tính hợp lệ của ngày tháng (logic cơ bản)
				if (mm >= 1 && mm <= 12 && dd >= 1 && dd <= 31 && yyyy >= 1920 && yyyy <= 2026) {
					char buffer[11];
					sprintf_s(buffer, "%02d/%02d/%04d", dd, mm, yyyy);
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max)(), '\n');
					return string(buffer); // Thoát hàm và trả về kết quả
				}
			}

			// Nếu nhập sai định dạng hoặc sai logic ngày tháng
			cout << "Ngay thang nam sinh ban nhap khong hop le! Vui long nhap lai.\n";
			cin.clear(); // Xóa trạng thái lỗi
			cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Xóa sạch bộ đệm cho đến khi gặp dòng mới
		}
	}
};