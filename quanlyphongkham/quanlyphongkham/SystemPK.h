#pragma once
#include "LiblaryHeader.h"
#include "UI.h"
#include "SystemMethod.h"
#include "BenhNhan.h"
#include "PhongKham.h"
#include "CanLamSang.h"

// *================ = SYSTEM PK ================ = */

class SystemPK {

public:

	void menuBenhNhan() {

		int c;

		do {

			UI::clear();
			UI::center("=====BENH NHAN=====", 10);

			cout << "\n1 Nhap benh nhan kham benh\n";
			cout << "2 Xem danh sach benh nhan da kham\n";
			cout << "3 Tim benh nhan\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = SystemMethod::kiemTraKyTu();

			switch (c) {

			case 1: {

				BenhNhan b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				BenhNhan::showBenhNhan();
				break;

			case 3:

				BenhNhan::searchBenhNhan();
				break;

			case 4:

				BenhNhan::exportExcelBenhNhan();
				break;
			}

		} while (c != 5);
	}

	void menuPhongKham() {

		int c;

		do {

			UI::clear();
			UI::center("=====PHONG KHAM=====", 10);

			cout << "\n1 Khai bao phong kham\n";
			cout << "2 Xem danh sach cac phong kham\n";
			cout << "3 Tim phong kham\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = SystemMethod::kiemTraKyTu();

			switch (c) {

			case 1: {

				PhongKham b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				PhongKham::showPhongKham();
				break;

			case 3:

				PhongKham::searchPhongkham();
				break;

			case 4:

				PhongKham::exportExcePhongKham();
				break;
			}

		} while (c != 5);
	}

	void menuBacSi() {

		int c;

		do {

			UI::clear();
			UI::center("=====BAC SI - NHAN VIEN=====", 10);

			cout << "\n1 Khai bao bac si - nhan vien\n";
			cout << "2 Xem danh sach\n";
			cout << "3 Tim kiem\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = SystemMethod::kiemTraKyTu();

			switch (c) {

			case 1: {

				BacSi b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				BacSi::showBacSi();
				break;

			case 3:

				BacSi::searchBacSi();
				break;

			case 4:

				BacSi::exportExceBacSi();
				break;
			}

		} while (c != 5);
	}

	void menuCanLamSang() {

		int c;

		do {

			UI::clear();
			UI::center("=====CAN LAM SANG=====", 10);

			cout << "\n1 Khai bao can lam sang\n";
			cout << "2 Xem danh sach can lam sang\n";
			cout << "3 Tim dich vu CLS\n";
			cout << "4 Xuat excel\n";
			UI::printColor("5 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = SystemMethod::kiemTraKyTu();

			switch (c) {

			case 1: {

				CanLamSang b;
				b.nhap();
				b.save();

				break;
			}

			case 2:

				CanLamSang::showCLS();
				break;

			case 3:

				CanLamSang::searchCLS();
				break;

			case 4:

				CanLamSang::exportExceCLS();
				break;
			}

		} while (c != 5);
	}

	void menuThuoc() {

		int c;

		do {

			UI::clear();
			UI::center("=====KHO THUOC=====", 10);

			cout << "\n1 Nhap thuoc\n";
			cout << "2 Ban thuoc\n";
			cout << "3 Xem ton kho\n";
			cout << "4 Tim thuoc\n";
			cout << "5 Xuat excel\n";
			UI::printColor("6 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = SystemMethod::kiemTraKyTu();

			switch (c) {

			case 1: {

				nhapThuoc b;
				b.nhap();
				b.save();

				break;
			}

			case 2: {

				banThuoc b;
				b.ban();
				b.save();
				break;
			}

			case 3:

				banThuoc::showTonKho();
				break;

			case 4:

				banThuoc::seachThuoc();
				break;
			case 5:

				banThuoc::exportExcelThuoc();
				break;
			}


		} while (c != 6);
	}

	bool kiemTraNgay(string ngay) {

		if (ngay.length() != 10)
			return false;

		if (ngay[2] != '/' || ngay[5] != '/')
			return false;

		int dd = stoi(ngay.substr(0, 2));
		int mm = stoi(ngay.substr(3, 2));
		int yyyy = stoi(ngay.substr(6, 4));

		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);

		int namHienTai = t.tm_year + 1900;

		if (dd < 1 || dd > 31)
			return false;

		if (mm < 1 || mm > 12)
			return false;

		if (yyyy < 1000 || yyyy > namHienTai)
			return false;

		return true;
	}

	string nhapNgayDung() {

		string ngay;

		while (true) {

			cout << "Nhap ngay (dd/mm/yyyy): ";
			getline(cin, ngay);

			if (kiemTraNgay(ngay))
				return ngay;

			cout << "Ngay khong hop le! Vui long nhap lai.\n";
		}
	}

	void thongKeTheoNgay() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		cin.ignore();

		string ngay = nhapNgayDung();

		ifstream f("benhnhan.xml");

		string line;
		int dem = 0;

		while (getline(f, line)) {

			if (line.find("<Ngay>") != string::npos) {

				string ngayFile = line.substr(6, line.find("</") - 6);

				if (ngayFile == ngay)
					dem++;
			}
		}

		f.close();

		cout << "\nNgay " << ngay << " co " << dem << " ca kham\n";

		UI::pause();
	}

	void soSanhHomNayHomQua() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		time_t now = time(0);

		tm today_tm;
		localtime_s(&today_tm, &now);

		tm yesterday_tm = today_tm;
		yesterday_tm.tm_mday -= 1;

		mktime(&yesterday_tm);

		char todayStr[20];
		char yesterdayStr[20];

		sprintf_s(todayStr, "%02d/%02d/%04d",
			today_tm.tm_mday,
			today_tm.tm_mon + 1,
			today_tm.tm_year + 1900);

		sprintf_s(yesterdayStr, "%02d/%02d/%04d",
			yesterday_tm.tm_mday,
			yesterday_tm.tm_mon + 1,
			yesterday_tm.tm_year + 1900);

		ifstream f("benhnhan.xml");

		string line;
		int homnay = 0;
		int homqua = 0;

		while (getline(f, line)) {

			if (line.find("<Ngay>") != string::npos) {

				string ngayFile = line.substr(6, line.find("</") - 6);

				if (ngayFile == todayStr)
					homnay++;

				if (ngayFile == yesterdayStr)
					homqua++;
			}
		}

		f.close();

		cout << "\nHom nay (" << todayStr << ") : " << homnay << " ca\n";
		cout << "Hom qua (" << yesterdayStr << ") : " << homqua << " ca\n";

		if (homnay > homqua)
			cout << "Tang " << homnay - homqua << " ca\n";
		else if (homnay < homqua)
			cout << "Giam " << homqua - homnay << " ca\n";
		else
			cout << "Khong thay doi\n";

		UI::pause();
	}

	void thongKeTienThuocTheoNgay() {

		if (!SystemMethod::fileExist("banthuoc.xml")) {
			cout << "Khong co du lieu ban thuoc\n";
			UI::pause();
			return;
		}

		cin.ignore();

		string ngay = nhapNgayDung();

		ifstream f("banthuoc.xml");

		string line;
		banThuoc b;

		long long tongTien = 0;

		while (getline(f, line)) {

			if (line.find("<ThanhTien>") != string::npos)
				b.thanhtien = line.substr(11, line.find("</") - 11);

			if (line.find("<Ngay>") != string::npos) {

				b.date = line.substr(6, line.find("</") - 6);

				if (b.date == ngay)
					tongTien += stoll(b.thanhtien);
			}
		}

		f.close();

		cout << "\nTong tien thuoc ban ngay " << ngay << " = " << tongTien << " VND\n";

		UI::pause();
	}

	void menuThongKe() {

		int c;

		do {

			UI::clear();
			UI::center("===== THONG KE =====", 10);

			cout << "\n1 Thong ke so ca kham theo ngay";
			cout << "\n2 So sanh hom nay voi hom qua";
			cout << "\n3 Tong tien ban thuoc";
			UI::printColor("\n4 Quay lai\n", 12);

			cout << "\nChon: ";
			c = SystemMethod::kiemTraKyTu();

			switch (c) {

			case 1:
				thongKeTheoNgay();
				break;

			case 2:
				soSanhHomNayHomQua();
				break;

			case 3:
				thongKeTienThuocTheoNgay();
				break;
			}

		} while (c != 4);
	}

	void menuChinh() {

		int c;

		do {

			UI::clear();
			UI::center("=====HE THONG QUAN LY PHONG KHAM=====", 10);

			cout << "\n1 Quan ly Benh nhan";
			cout << "\n2 Quan ly phong kham";
			cout << "\n3 Quan ly bac si - nhan vien";
			cout << "\n4 Quan ly can lam sang";
			cout << "\n5 Quan ly thuoc";
			cout << "\n6 Thong Ke";
			UI::printColor("\n7 Thoat\n", 12);

			cout << "\nChon: ";
			cin >> c;

			switch (c) {

			case 1:
				menuBenhNhan();
				break;

			case 2: {

				menuPhongKham();
				break;
			}

			case 3: {

				menuBacSi();
				break;
			}

			case 4: {

				menuCanLamSang();
				break;
			}

			case 5: {

				menuThuoc();
				break;
			}
			case 6: {

				menuThongKe();
				break;
			}

			}

		} while (c != 7);
	}
};