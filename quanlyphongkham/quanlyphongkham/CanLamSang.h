#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"
#include "SystemMethod.h"


class CanLamSang {

public:

	string ma, ten, gia, ghiChu;

	void nhap() {

		cin.ignore();

		ma = Helper::nhapMaKhongTrung(
			"Ma DV",
			"canlamsang.xml",
			"CLS",
			"Ma"
		);

		cout << "Ten dich vu: ";
		getline(cin, ten);

		//cout << "Don gia: ";
		//getline(cin, gia);
		gia = std::to_string(nhapSo<int>("Nhap Don gia: "));

		cout << "Ghi chu: ";
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

	static void searchCLS() {

		if (!SystemMethod::fileExist("canlamsang.xml")) {
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

	static void exportExceCLS() {

		if (!SystemMethod::fileExist("canlamsang.xml")) {
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
				cout << "Loi vui long nhap so.\n";
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
		}
	}
};