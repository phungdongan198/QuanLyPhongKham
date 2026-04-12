#pragma once
#include "LiblaryHeader.h"
#include "SystemMethod.h"
#include "LuaChon.h"
#include <fstream>
#include <vector>
#include <string>

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

		cout << "Ho ten: ";
		getline(cin, ten);

		cout << "Ngay sinh: ";
		getline(cin, sinh);

		cout << "Gioi tinh: ";
		gioiTinh = LuaChon::chonTuDanhSach("Chon gioi tinh", { "Nam", "Nu","Khac" });

		cout << "Dien thoai: ";
		getline(cin, dienThoai);

		cout << "Dia chi: ";
		getline(cin, diaChi);

		cout << "Doi tuong: ";
		doiTuong = LuaChon::chonTuDanhSach("Chon doi tuong", { "BHYT", "Thu phi","Khac" });

		cout << "Phong kham: ";
		phong = LuaChon::chonTuFile("Chon phong kham", "phongkham.xml", "Phong", "Ten");

		ngay = SystemMethod::today();
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

	static void deleteBenhNhan() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		ifstream in("benhnhan.xml");

		vector<string> lines;
		string line;

		while (getline(in, line)) {
			lines.push_back(line);
		}
		in.close();


		if (lines.empty()) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		string maXoa;
		cout << "Nhap ma benh nhan can xoa: ";
		cin >> maXoa;

		vector<string> newLines;
		bool found = false;
		int count = 0;

		for (int i = 0; i < lines.size(); i++) {
			if (lines[i].find("<BenhNhan>") != string::npos) {
				vector<string> temp;
				bool match = false;

				while (i < lines.size()) {
					temp.push_back(lines[i]);


					if (lines[i].find("<Ma>") != string::npos) {
						size_t start = lines[i].find("<Ma>") + 4;
						size_t end = lines[i].find("</Ma>");

						if (start != string::npos && end != string::npos) {
							string ma = lines[i].substr(start, end - start);

							if (ma == maXoa) {
								match = true;
							}
						}
					}

					if (lines[i].find("</BenhNhan>") != string::npos)
						break;

					i++;
				}

				if (match) {
					found = true;
					count++;
				}
				else {
					for (auto& l : temp)
						newLines.push_back(l);
				}
			}
			else {
				newLines.push_back(lines[i]);
			}
		}


		if (!found) {
			cout << "Khong co thong tin benh nhan!\n";
			UI::pause();
			return;
		}


		ofstream out("benhnhan.xml");
		for (auto& l : newLines) {
			out << l << endl;
		}
		out.close();

		cout << "Da xoa " << count << " benh nhan!\n";
		UI::pause();
	}

	static void showBenhNhan() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
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

	static void searchBenhNhan() {
		int c;
		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}


		cout << "\n===== TIM KIEM BENH NHAN =====\n";
		cout << "1. Tim theo ma (tuyet doi)\n";
		cout << "2. Tim theo ten (tuong doi)\n";
		UI::printColor("3 Quay lai\n", 12);

		cout << "Chon: "; ;
		c = SystemMethod::kiemTraKyTu();

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

	static void exportExcelBenhNhan() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
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
};