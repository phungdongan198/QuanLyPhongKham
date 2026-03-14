#pragma once
using namespace std;
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "UI.h"
class ThongKe {

public:

	static void benhNhan() {

		UI::clear();
		UI::center("=== DANH SACH BENH NHAN DA KHAM ===", 10);

		ifstream file("benhnhan.xml");

		if (!file) {
			cout << "Chua co du lieu!\n";
			UI::pause();
			return;
		}

		string line, ma, ten, sinh, phong;
		int tong = 0;

		cout << "\nMaBN | HoTen | NamSinh | PhongKham\n";
		cout << "-------------------------------------\n";

		while (getline(file, line)) {

			if (line.find("<MaBN>") != string::npos)
				ma = line.substr(6, line.find("</") - 6);

			if (line.find("<HoTen>") != string::npos)
				ten = line.substr(7, line.find("</") - 7);

			if (line.find("<NgaySinh>") != string::npos)
				sinh = line.substr(10, line.find("</") - 10);

			if (line.find("<PhongKham>") != string::npos) {

				phong = line.substr(11, line.find("</") - 11);

				cout << ma << " | " << ten << " | " << sinh << " | " << phong << endl;
				tong++;
			}
		}

		cout << "\nTong so benh nhan: " << tong << endl;

		UI::pause();
	}
};
