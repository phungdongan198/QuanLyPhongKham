#pragma once
#include "LiblaryHeader.h"

/* ================= NHAP THUOC ================= */
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