#pragma once
#include "LiblaryHeader.h"

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
};