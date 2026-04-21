#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"


class PhongKham {

public:

	string ma, ten, loai;

	void nhap() {

		cin.ignore();
	
		ma = Helper::nhapMaKhongTrung(
			"Ma pk:",
			"phongkham.xml",
			"Phong",
			"Ma"
		);

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

	static void showPhongKham() {

		if (!SystemMethod::fileExist("phongkham.xml")) {
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

	static void searchPhongkham() {
		int c;
		if (!SystemMethod::fileExist("phongkham.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}


		cout << "\n===== TIM PHONG KHAM =====\n";
		cout << "1 Tim theo ma\n";
		cout << "2 Tim theo ten\n";
		UI::printColor("3 Quay lai\n", 12);

		cout << "Chon: ";
		c = SystemMethod::kiemTraKyTu();


		if (c == 3)
			return;

		cin.ignore();

		string key;

		if (c == 1)
			cout << "Nhap ma phong: ";
		else
			cout << "Nhap ten phong: ";

		getline(cin, key);
		string lowerKey = SystemMethod::toLower(key);
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

				if (c == 1 && SystemMethod::toLower(pk.ma) == key)
					match = true;

				if (c == 2 && SystemMethod::toLower(pk.ten).find(key) != string::npos)
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

	static void exportExcePhongKham() {

		if (!SystemMethod::fileExist("phongkham.xml")) {
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
};