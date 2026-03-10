#pragma once
using namespace std;
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
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
};
