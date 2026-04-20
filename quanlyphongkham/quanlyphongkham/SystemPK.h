#pragma once
#include "LiblaryHeader.h"
#include "UI.h"
#include "SystemMethod.h"
#include "BenhNhan.h"
#include "PhongKham.h"
#include "CanLamSang.h"
#include "login.h";
#include <vector>
#include <thread>
#include <mutex>
#include <conio.h>



class SystemPK {

public:


	string layNgayHienTai() {
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);

		string ngay = (ltm.tm_mday < 10 ? "0" : "") + to_string(ltm.tm_mday);
		string thang = (ltm.tm_mon + 1 < 10 ? "0" : "") + to_string(ltm.tm_mon + 1);
		string nam = to_string(1900 + ltm.tm_year);

		return ngay + "/" + thang + "/" + nam;
	}

	string nhapPasswordAn() {
		string password = "";
		char ch;

		while (true) {
			ch = _getch();

			// Enter
			if (ch == 13) {
				break;
			}
			// Backspace
			else if (ch == 8) {
				if (!password.empty()) {
					password.pop_back();
					cout << "\b \b";
				}
			}
			// Ký tự bình thường
			else if (ch >= 32 && ch <= 126) {
				password += ch;
				cout << '*';
			}
		}

		cout << endl;
		return password;
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

	struct KetQuaFile {
		string tenHienThi;
		bool coDuLieu;
	};

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

	void menuBenhNhan() {

		int c;

		do {

			UI::clear();
			UI::center("=====BENH NHAN=====", 10);

			cout << "\n1 Dang ky kham\n";
			cout << "2 Kham benh\n";
			cout << "3 Xoa benh nhan\n";
			cout << "4 Xem danh sach benh nhan\n";
			cout << "5 Tim benh nhan\n";
			cout << "6 Xuat excel\n";
			UI::printColor("7 Quay lai\n", 12);

			cout << "Chon: "; ;
			c = SystemMethod::kiemTraKyTu();

			switch (c) {

			case 1: {

				BenhNhan b;
				b.nhapDangKy();
				b.saveDangKy();

				break;
			}
			case 2: {

				BenhNhan b;
				b.nhapKhamBenh();
				b.saveKhamBenh();
				break;
			}
			case 3:

				BenhNhan::deleteBenhNhan();
				break;

			case 4:

				BenhNhan::showBenhNhan();
				break;

			case 5:

				BenhNhan::searchBenhNhan();
				break;

			case 6:

				BenhNhan::exportExcelBenhNhan();
				break;
			}

		} while (c != 7);
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
			cout << "2 Xuat thuoc\n";
			cout << "3 Xem nhap xuat\n";
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

	void thongKeTheoNgay() {

		if (!SystemMethod::fileExist("khambenh.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		cin.ignore();

		string ngay = nhapNgayDung();

		ifstream f("khambenh.xml");

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

		if (!SystemMethod::fileExist("khambenh.xml")) {
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

		ifstream f("khambenh.xml");

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
			UI::center("===== THONG KE - BAO CAO=====", 10);

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

	void menuThuTien() {
		int c;
		do {
			UI::clear();
			UI::center("===== THANH TOAN =====", 10);
			cout << "1. Thu tien\n";
			cout << "2. Hoan tra\n";
			cout << "3. Xem danh sach\n";
			cout << "4. Tim kiem\n";
			cout << "5. Xuat Excel\n";
			UI::printColor("6 Quay lai\n", 12);

			cout << "Chon: ";
			c = SystemMethod::kiemTraKyTu();

			switch (c) {
			case 1: {
				ThuTien t;
				t.nhapThu();
				t.saveThu();
				break;
			}
			case 2: {
				ThuTien h;
				h.nhapHoan();
				h.saveHoan();
				break;
			}
			case 3:
				ThuTien::showAll();
				break;
			case 4:
				ThuTien::search();
				break;
			case 5:
				ThuTien::exportExcel();
				break;
			}
		} while (c != 6);
	}

	bool fileCoDuLieu(const string& tenFile) {
		ifstream f(tenFile, ios::binary);
		if (!f) return false;

		f.seekg(0, ios::end);
		return f.tellg() > 0;
	}

	void kiemTraFile(const string& tenFile, const string& tenHienThi, KetQuaFile& kq) {
		kq.tenHienThi = tenHienThi;
		kq.coDuLieu = fileCoDuLieu(tenFile);
	}

	void menuDangNhap()
	{
		Login::CheckListAndAdd();
		int chon = 0;
		string username, password;

		UI::clear();
		UI::center("=====DANG NHAP=====", 10);
		cout << "Tai Khoan Kham Benh: khambenh/khambenh123\n";
		cout << "Tai Khoan Admin: admin/admin123\n";
		cout << "Nhap UserName:";
		getline(cin, username);
		cout << "Nhap Password:";
		password = nhapPasswordAn();
		if (Login::CheckLogin(username, password) == "admin")
		{
			cout << "Dang nhap thanh cong voi vai tro Admin!\n";
			/*UI::pause();*/
			menuChinh("admin", username);
		}
		else if (Login::CheckLogin(username, password) == "employee")
		{
			cout << "Dang nhap thanh cong voi vai tro Employee!\n";
			/*UI::pause();*/
			menuChinh("employee", username);
		}
		else
		{
			cout << "Dang nhap that bai! Vui long thu lai.\n";
			UI::pause();
			menuDangNhap();
		}
	}

	void menuChinh(string role, string user_dangnhap, bool lanDau = true) {

		int c;

		UI::printColor("Dang khoi tao he thong\n", 10);
		vector<pair<string, string>> dsFile = {
			{"phongkham.xml", "danh sach phong kham"},
			{"bacsi.xml", "danh sach bac si"},
			{"canlamsang.xml", "danh sach can lam sang"},
			{ "nhapthuoc.xml", "danh sach thuoc" }
		};

		vector<KetQuaFile> dsKetQua(dsFile.size());
		vector<thread> dsLuong;

		for (int i = 0; i < (int)dsFile.size(); i++) {
			dsLuong.emplace_back(&SystemPK::kiemTraFile, this,
				dsFile[i].first, dsFile[i].second, ref(dsKetQua[i]));
		}

		for (auto& luong : dsLuong) {
			luong.join();
		}

		for (const auto& kq : dsKetQua) {
			if (kq.coDuLieu) {
				//UI::printColor("Xong: " + kq.tenHienThi + " da co du lieu.", 10);
			}
			else {
				UI::printColor("" + kq.tenHienThi + " khong co du lieu. Vui long khai bao truoc khi làm viec .\n", 12);
			}
		}
		cout << endl;
		UI::printColor("He thong da khoi tao xong", 10);
		cout << endl << endl;


		do {

			if (!lanDau) {
				UI::clear();
			}

			UI::center("=====HE THONG QUAN LY PHONG KHAM PAP SOFT - " + user_dangnhap + " - NGAY LAM VIEC  " + layNgayHienTai() + " - V 1.0.0 =====", 10);
			cout << "\n1 Quan ly benh nhan";
			if (role == "admin")
			{
				cout << "\n2 Quan ly thuoc";
				cout << "\n3 Quan ly thanh toan";
				cout << "\n4 Danh muc phong kham";
				cout << "\n5 Danh muc bac si - nhan vien";
				cout << "\n6 Danh muc can lam sang";
				cout << "\n7 Thong ke - bao cao";
			}
			cout << "\n8 Dang nhap lai";
			UI::printColor("\n9 Ket thuc\n", 12);
			c = SystemMethod::nhapSo<int>("Moi ban chon:");
			lanDau = false;

			if (role == "employee" && (c >= 2 && c <= 7))
			{
				c = 9;
			}

			switch (c)
			{
			case 1:
				menuBenhNhan();
				break;

			case 2: {
				menuThuoc();
				break;
			}
			case 3: {
				menuThuTien();
				break;
			}

			case 4: {
				menuPhongKham();
				break;
			}

			case 5: {
				menuBacSi();
				break;
			}

			case 6: {
				menuCanLamSang();
				break;
			}

			case 7: {
				menuThongKe();
				break;
			}
			case 8: {
				menuDangNhap();
				break;
			}
			}

		} while (c != 9);
		cout << "\nXin cam on ban da su dung he thong!\n";
		UI::pause();
	}
};