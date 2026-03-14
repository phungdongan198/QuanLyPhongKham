#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
#include "BenhNhan.h"
#include "UI.h"
#include "ThongKe.h"
#include "PhongKham.h"
using namespace std;

=======
>>>>>>> 3fd49ca4b6f833f1b2da1332004345ec82830fde
#include "UI.h"
#include "BenhNhan.h"
#include "ThongKe.h"
using namespace std;

/* ================= UI ================= */
//class UI {
//public:
//
//	static void setColor(int c) {
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
//	}
//
//	static void pause() {
//		system("pause");
//	}
//
//	static void clear() {
//		system("cls");
//	}
//
//	/* căn giữa chữ */
//	static void center(string text, int color = 7) {
//
//		CONSOLE_SCREEN_BUFFER_INFO csbi;
//		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//
//		int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//		int padding = (width - text.length()) / 2;
//
//		setColor(color);
//
//		for (int i = 0; i < padding; i++)
//			cout << " ";
//
//		cout << text << endl;
//
//		setColor(7);
//	}
//	// chỉ set màu ko căn giữa
//	static void printColor(string text, int color) { setColor(color); cout << text; setColor(7); }
//};

/* ================= BENH NHAN ================= */
//class BenhNhan {
//
//private:
//
//	string maBN, hoTen, ngaySinh, gioiTinh, dienThoai, diaChi, doiTuongKham, phongKham;
//
//public:
//
//	void nhap() {
//
//		cin.ignore();
//
//		cout << "Ma benh nhan: "; getline(cin, maBN);
//		cout << "Ho ten benh nhan: "; getline(cin, hoTen);
//		cout << "Ngay sinh: "; getline(cin, ngaySinh);
//		cout << "Gioi tinh: "; getline(cin, gioiTinh);
//		cout << "Dien thoai: "; getline(cin, dienThoai);
//		cout << "Dia chi: "; getline(cin, diaChi);
//		cout << "Doi tuong kham: "; getline(cin, doiTuongKham);
//		cout << "Phong kham: "; getline(cin, phongKham);
//	}
//
//	void luuXML() {
//
//		ofstream file("benhnhan.xml", ios::app);
//
//		file << "<BenhNhan>\n";
//		file << "<MaBN>" << maBN << "</MaBN>\n";
//		file << "<HoTen>" << hoTen << "</HoTen>\n";
//		file << "<NgaySinh>" << ngaySinh << "</NgaySinh>\n";
//		file << "<GioiTinh>" << gioiTinh << "</GioiTinh>\n";
//		file << "<DienThoai>" << dienThoai << "</DienThoai>\n";
//		file << "<DiaChi>" << diaChi << "</DiaChi>\n";
//		file << "<DoiTuongKham>" << doiTuongKham << "</DoiTuongKham>\n";
//		file << "<PhongKham>" << phongKham << "</PhongKham>\n";
//		file << "</BenhNhan>\n\n";
//
//		file.close();
//	}
//};

/* ================= THONG KE ================= */
//class ThongKe {
//
//public:
//
//	static void benhNhan() {
//
//		UI::clear();
//		UI::center("=== DANH SACH BENH NHAN DA KHAM ===", 10);
//
//		ifstream file("benhnhan.xml");
//
//		if (!file) {
//			cout << "Chua co du lieu!\n";
//			UI::pause();
//			return;
//		}
//
//		string line, ma, ten, sinh, phong;
//		int tong = 0;
//
//		cout << "\nMaBN | HoTen | NamSinh | PhongKham\n";
//		cout << "-------------------------------------\n";
//
//		while (getline(file, line)) {
//
//			if (line.find("<MaBN>") != string::npos)
//				ma = line.substr(6, line.find("</") - 6);
//
//			if (line.find("<HoTen>") != string::npos)
//				ten = line.substr(7, line.find("</") - 7);
//
//			if (line.find("<NgaySinh>") != string::npos)
//				sinh = line.substr(10, line.find("</") - 10);
//
//			if (line.find("<PhongKham>") != string::npos) {
//
//				phong = line.substr(11, line.find("</") - 11);
//
//				cout << ma << " | " << ten << " | " << sinh << " | " << phong << endl;
//				tong++;
//			}
//		}
//
//		cout << "\nTong so benh nhan: " << tong << endl;
//
//		UI::pause();
//	}
//};

/* ================= XOA BENH NHAN ================= */
void xoaBenhNhan() {

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

/* ================= HE THONG ================= */
class PhongKham {

public:

	void menuBenhNhan() {

		int chon;

		do {

			UI::clear();
			UI::center("===== QUAN LY BENH NHAN =====", 10);

			cout << "\n1. Nhap thong tin benh nhan\n";
			cout << "2. Xoa benh nhan\n";
			UI::printColor ( "3. Quay lai menu chinh\n",12);

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
				xoaBenhNhan();
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

<<<<<<< HEAD
=======
>>>>>>> b2625b052f4748af5716357ab6bf8642fc957fa6
>>>>>>> 3fd49ca4b6f833f1b2da1332004345ec82830fde
/* ================= MAIN ================= */
int main() {

	PhongKham pk;
	pk.menuChinh();

	return 0;
}