#pragma once
#pragma once
using namespace std;
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "UI.h"
class BenhNhan {

private:

	string maBN, hoTen, ngaySinh, gioiTinh, dienThoai, diaChi, doiTuongKham, phongKham;

public:

	void nhap() {

		cin.ignore();

		cout << "Ma benh nhan: "; getline(cin, maBN);
		cout << "Ho ten benh nhan: "; getline(cin, hoTen);
		cout << "Ngay sinh: "; getline(cin, ngaySinh);
		cout << "Gioi tinh: "; getline(cin, gioiTinh);
		cout << "Dien thoai: "; getline(cin, dienThoai);
		cout << "Dia chi: "; getline(cin, diaChi);
		cout << "Doi tuong kham: "; getline(cin, doiTuongKham);
		cout << "Phong kham: "; getline(cin, phongKham);
	}

	void luuXML() {

		ofstream file("benhnhan.xml", ios::app);

		file << "<BenhNhan>\n";
		file << "<MaBN>" << maBN << "</MaBN>\n";
		file << "<HoTen>" << hoTen << "</HoTen>\n";
		file << "<NgaySinh>" << ngaySinh << "</NgaySinh>\n";
		file << "<GioiTinh>" << gioiTinh << "</GioiTinh>\n";
		file << "<DienThoai>" << dienThoai << "</DienThoai>\n";
		file << "<DiaChi>" << diaChi << "</DiaChi>\n";
		file << "<DoiTuongKham>" << doiTuongKham << "</DoiTuongKham>\n";
		file << "<PhongKham>" << phongKham << "</PhongKham>\n";
		file << "</BenhNhan>\n\n";

		file.close();
	}

	static void xoaBenhNhan() {

		UI::clear();
		UI::center("=== XOA BENH NHAN ===", 10);

		string maXoa;
		cin.ignore();

		cout << "Nhap ma benh nhan can xoa: ";
		getline(cin, maXoa);

		ifstream file("benhnhan.xml");
		ofstream temp("temp.xml");

		if (!file) {
			cout << "Khong mo duoc file!\n";
			UI::pause();
			return;
		}

		string line, block;
		bool inBlock = false, removeBlock = false;
		int dem = 0;

		while (getline(file, line)) {

			if (line.find("<BenhNhan>") != string::npos) {
				block = line + "\n";
				inBlock = true;
				continue;
			}

			if (inBlock) {

				block += line + "\n";

				if (line.find("<MaBN>") != string::npos) {

					string ma = line.substr(6, line.find("</") - 6);

					if (ma == maXoa) {
						removeBlock = true;
						dem++;
					}
				}

				if (line.find("</BenhNhan>") != string::npos) {

					inBlock = false;

					if (!removeBlock)
						temp << block;

					block = "";
					removeBlock = false;
				}
			}
		}

		file.close();
		temp.close();

		if (dem == 0) {
			remove("temp.xml");
			cout << "Khong tim thay ma benh nhan!\n";
			UI::pause();
			return;
		}

		if (remove("benhnhan.xml") != 0 || rename("temp.xml", "benhnhan.xml") != 0) {
			cout << "Xoa that bai!\n";
			UI::pause();
			return;
		}

		cout << "Da xoa " << dem << " benh nhan!\n";
		UI::pause();
	}
};
