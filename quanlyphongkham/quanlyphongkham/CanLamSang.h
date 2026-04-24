#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"
#include "SystemMethod.h"


class CanLamSang {
private:
	string ma, ten, gia, ghiChu;

public:

	#pragma region getter_&_setter

	string getMa() const { return ma; }
	void setMa(const string& val) { ma = val; }

	string getTen() const { return ten; }
	void setTen(const string& val) { ten = val; }

	string getGia() const { return gia; }
	void setGia(const string& val) { gia = val; }

	string getGhiChu() const { return ghiChu; }
	void setGhiChu(const string& val) { ghiChu = val; }

	#pragma endregion

	void nhap() {

		cin.ignore();

		ma = Helper::nhapMaKhongTrung(
			"Mã Dịch Vụ:",
			"canlamsang.xml",
			"CLS",
			"Ma"
		);

		cout << "Tên dịch vụ: ";
		getline(cin, ten);

		//cout << "Đơn giá: ";
		//getline(cin, gia);
		gia = std::to_string(nhapSo<int>("Nhập Đơn giá: "));

		cout << "Ghi chú: ";
		getline(cin, ghiChu);
	}

	void save() {

		bool fileMoi = !SystemMethod::fileExist("canlamsang.xml");
		ofstream f("canlamsang.xml", ios::app);
		if (fileMoi) {
			f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		}

		f << "<CLS>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<Gia>" << gia << "</Gia>\n";
		f << "<GhiChu>" << ghiChu << "</GhiChu>\n";
		f << "</CLS>\n\n";

		f.close();
	}

	static void showCLS() {

		if (!SystemMethod::fileExist("canlamsang.xml")) {
			cout << "Không có dữ liệu\n";
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
			<< setw(15) << "Mã DV"
			<< setw(25) << "Tên Dịch Vụ"
			<< setw(10) << "Đơn Giá"
			<< setw(20) << "Ghi Chú"
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

	static void searchCLS() {

		if (!SystemMethod::fileExist("canlamsang.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		int chon;

		cout << "\n===== TÌM CẬN LÂM SÀNG =====\n";
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
			cout << "Nhập mã dịch vụ: ";
		else
			cout << "Nhập tên dịch vụ: ";

		getline(cin, key);
		string lowerKey = SystemMethod::toLower(key);
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

				if (chon == 1 && SystemMethod::toLower(cls.ma) == key)
					match = true;

				if (chon == 2 && SystemMethod::toLower(cls.ten).find(key) != string::npos)
					match = true;

				if (match)
					ds.push_back(cls);
			}
		}

		f.close();

		if (ds.empty()) {

			cout << "Không tìm thấy\n";
			UI::pause();
			return;
		}

		cout << "\n-------------------------------------------------------------\n";

		cout << left
			<< setw(15) << "Mã DV"
			<< setw(25) << "Tên Dịch Vụ"
			<< setw(10) << "Đơn Giá"
			<< setw(20) << "Ghi Chú"
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

	static void exportExceCLS() {

		if (!SystemMethod::fileExist("canlamsang.xml")) {
			cout << "Không có dữ liệu\n";
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

		cout << "\nXuất Excel thành công: canlamsang.csv\n";

		char ch;

		cout << "Bạn có muốn mở file không? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start canlamsang.csv");

		UI::pause();
	}

	template <typename T>
	static T nhapSo(string thongBao) {
		T value;
		while (true) {
			cout << thongBao;
			if (cin >> value) {
				// Nhập thành công, dọn dẹp bộ đệm đến hết dòng để tránh trôi lệnh sau
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				return value;
			}
			else {
				cout << "Lỗi! Vui lòng nhập số.\n";
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
		}
	}
};