#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"
#include "QuanLy.h"
#include "SystemMethod.h"

// tính kế thừa
class BacSi : public DoiTuongQuanLy {

private:
	string ma, ten, sinh, chungChi, chuyenMon;

public:
#pragma region các getter và setter
	string getMa() const { return ma; }
	void setMa(const string& val) { ma = val; }

	string getTen() const { return ten; }
	void setTen(const string& val) { ten = val; }

	string getSinh() const { return sinh; }
	void setSinh(const string& val) { sinh = val; }

	string getChungChi() const { return chungChi; }
	void setChungChi(const string& val) { chungChi = val; }

	string getChuyenMon() const { return chuyenMon; }
	void setChuyenMon(const string& val) { chuyenMon = val; }
#pragma endregion

	// đa hình
	void nhap() override {

		cin.ignore();

		ma = Helper::nhapMaKhongTrung(
			"Mã BS - NV: ",
			"bacsi.xml",
			"BacSi",
			"Ma"
		);

		cout << "Tên: ";
		getline(cin, ten);

		sinh = NhapVaKiemTraNamSinh();

		cout << "Chứng chỉ: ";
		getline(cin, chungChi);

		cout << "Chuyên môn: ";
		getline(cin, chuyenMon);
	}

	void save() override {
		bool fileMoi = !SystemMethod::fileExist("bacsi.xml");

		ofstream f("bacsi.xml", ios::app);
		if (fileMoi) {
			f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		}

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
		Helper::inCot(out, bs.ma, 10);
		Helper::inCot(out, bs.ten, 40);
		Helper::inCot(out, bs.sinh, 15);
		Helper::inCot(out, bs.chungChi, 25);
		Helper::inCot(out, bs.chuyenMon, 25);

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
			cout << "Không có dữ liệu\n";
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

		cout << string(120, '-') << endl;

		Helper::inCot(cout, "Mã BS", 10);
		Helper::inCot(cout, "Tên BS", 40);
		Helper::inCot(cout, "Ngày Sinh", 15);
		Helper::inCot(cout, "Chứng chỉ", 25);
		Helper::inCot(cout, "Chuyên môn", 25);
		cout << endl;

		cout << string(120, '-') << endl;

		for (auto& b : ds) {

			cout << b << endl;
		}

		cout << string(120, '-') << endl;

		UI::pause();
	}

	void hienThi() override {
		Helper::inCot(cout, ma, 10);
		Helper::inCot(cout, ten, 40);
		Helper::inCot(cout, sinh, 15);
		Helper::inCot(cout, chungChi, 25);
		Helper::inCot(cout, chuyenMon, 15);
		cout << endl;
	}

	static void searchBacSi() {

		if (!SystemMethod::fileExist("bacsi.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		int chon;

		cout << "\n===== TÌM BÁC SĨ =====\n";
		cout << "1 Tìm theo mã\n";
		cout << "2 Tìm theo tên\n";
		UI::printColor("3 Quay lại\n", 12);

		cout << "Chọn: ";
		cin >> chon;

		if (chon == 3)
			return;

		cin.ignore();

		string key;

		if (chon == 1)
			cout << "Nhập mã bác sĩ: ";
		else
			cout << "Nhập tên bác sĩ: ";

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

			cout << "Không tìm thấy\n";
			UI::pause();
			return;
		}

		cout << string(120, '-') << endl;

		Helper::inCot(cout, "Mã BS", 10);
		Helper::inCot(cout, "Tên BS", 40);
		Helper::inCot(cout, "Ngày Sinh", 15);
		Helper::inCot(cout, "Chứng chỉ", 25);
		Helper::inCot(cout, "Chuyên môn", 25);
		cout << endl;

		cout << string(120, '-') << endl;

		for (auto& b : ds) {

			cout << b << endl;
		}

		cout << string(120, '-') << endl;

		UI::pause();
	}

	static void exportExceBacSi() {

		if (!SystemMethod::fileExist("bacsi.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		ifstream f("bacsi.xml");
		ofstream o("bacsi.csv", ios::binary);
		o << "\xEF\xBB\xBF";

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

		cout << "\nXuất Excel thành công: bacsi.csv\n";

		char ch;

		cout << "Bạn có muốn mở file không? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start bacsi.csv");

		UI::pause();
	}

	string NhapVaKiemTraNamSinh() {
		int dd, mm, yyyy;
		char slash1, slash2;

		while (true) {
			cout << "Nhập ngày sinh (Với định dạng dd / mm / yyyy): ";

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
			cout << "Ngày tháng năm sinh bạn nhập không hợp lệ! Vui lòng nhập lại.\n";
			cin.clear(); // Xóa trạng thái lỗi
			cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Xóa sạch bộ đệm cho đến khi gặp dòng mới
		}
	}
};