#pragma once
using namespace std;
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "BenhNhan.h"
#include "UI.h"
class PhongKham {

public:

	void menuBenhNhan() {

		int chon;

		do {

			UI::clear();
			UI::center("===== QUAN LY BENH NHAN =====", 10);

			cout << "\n1. Nhap thong tin benh nhan\n";
			cout << "2. Xoa benh nhan\n";
			UI::printColor("3. Quay lai menu chinh\n", 12);

			cout << "\nChon: ";
			cin >> chon;

			switch (chon) {

			case 1: {
				UI::clear();
				UI::center("=== NHAP THONG TIN BENH NHAN ===", 10);

				BenhNhan bn;
				bn.nhap();
				bn.luuXML();

				cout << "\nNhap thanh cong!\n";
				UI::pause();
				break;
			}

			case 2:
				BenhNhan::xoaBenhNhan();
				break;
			}

		} while (chon != 3);
	}

	void menuThongKe() {

		int chon;

		do {

			UI::clear();
			UI::center("===== MENU THONG KE =====", 10);

			cout << "\n1. Thong ke danh sach benh nhan\n";
			cout << "2. Danh sach phong kham\n";
			cout << "3. Danh sach bac si\n";
			cout << "4. Danh sach can lam sang\n";
			cout << "5. Danh sach thuoc\n";
			cout << "6. Quay lai menu chinh\n";

			cout << "\nChon: ";
			cin >> chon;

			if (chon == 1)
				ThongKe::benhNhan();
			else if (chon >= 2 && chon <= 5) {
				cout << "Chuc nang dang phat trien...\n";
				UI::pause();
			}

		} while (chon != 6);
	}

	void menuChinh() {

		int chon;

		do {

			UI::clear();
			UI::center("===== QUAN LY PHONG KHAM =====", 10);

			cout << "\n1. Nhap thong tin benh nhan kham benh\n";
			cout << "2. Khai bao phong kham\n";
			cout << "3. Khai bao bac si\n";
			cout << "4. Khai bao thuoc\n";
			cout << "5. Can lam sang\n";
			cout << "6. Quan ly ho so da kham\n";
			cout << "7. Thong ke\n";
			UI::printColor("8. Thoat\n", 12);

			cout << "\nChon chuc nang: ";
			cin >> chon;

			switch (chon) {

			case 1: menuBenhNhan(); break;
			case 7: menuThongKe(); break;

			case 8:
				UI::clear();
				UI::center("Thoat chuong trinh");
				break;

			default:
				cout << "Chuc nang dang phat trien...\n";
				UI::pause();
			}

		} while (chon != 8);
	}
};