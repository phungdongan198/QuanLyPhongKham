#pragma once
#include "LiblaryHeader.h"
#include "UI.h"
#include "SystemMethod.h"
#include "BenhNhan.h"
#include "PhongKham.h"
#include "CanLamSang.h"
#include "login.h"
#include <vector>
#include <thread>
#include <mutex>
#include <conio.h>



class SystemPK {

public:

	struct KetQuaFile {
		string tenHienThi;
		bool coDuLieu;
	};

#pragma region menu Chức Năng

	void menuBenhNhan() {

		int c;

		do {

			UI::clear();
			UI::center("=====BỆNH NHÂN=====", 10);

			cout << "\n1 Đăng ký khám\n";
			cout << "2 Khám bệnh\n";
			cout << "3 Xóa bệnh nhân\n";
			cout << "4 Xem danh sách bệnh nhân\n";
			cout << "5 Tìm bệnh nhân\n";
			cout << "6 Xuất excel\n";
			UI::printColor("7 Quay lại\n", 12);

			cout << "Chọn: "; ;
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
			UI::center("=====PHÒNG KHÁM=====", 10);

			cout << "\n1 Khai báo phòng khám\n";
			cout << "2 Xem danh sách các phòng khám\n";
			cout << "3 Tìm phòng khám\n";
			cout << "4 Xuất excel\n";
			UI::printColor("5 Quay lại\n", 12);

			cout << "Chọn: "; ;
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
			UI::center("=====BÁC SĨ - NHÂN VIÊN=====", 10);

			cout << "\n1 Khai báo bác sĩ - nhân viên\n";
			cout << "2 Xem danh sách\n";
			cout << "3 Tìm kiếm\n";
			cout << "4 Xuất excel\n";
			UI::printColor("5 Quay lại\n", 12);

			cout << "Chọn: "; ;
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
			UI::center("=====CẬN LÂM SÀNG=====", 10);

			cout << "\n1 Khai báo cận lâm sàng\n";
			cout << "2 Xem danh sách cận lâm sàng\n";
			cout << "3 Tìm dịch vụ CLS\n";
			cout << "4 Xuất excel\n";
			UI::printColor("5 Quay lại\n", 12);

			cout << "Chọn: "; ;
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
			UI::center("=====KHO THUỐC=====", 10);

			cout << "\n1 Nhập thuốc\n";
			cout << "2 Xuất thuốc\n";
			cout << "3 Xem nhập xuất\n";
			cout << "4 Tìm thuốc\n";
			cout << "5 Xuất excel\n";
			UI::printColor("6 Quay lại\n", 12);

			cout << "Chọn: "; ;
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
				if (b.ban()) {
					b.save();
				}
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

	void menuThongKe() {

		int c;

		do {

			UI::clear();
			UI::center("===== THỐNG KÊ - BÁO CÁO=====", 10);

			cout << "\n1 Thống kê số ca khám theo ngày";
			cout << "\n2 So sánh hôm nay với hôm qua";
			cout << "\n3 Tổng tiền bán thuốc";
			UI::printColor("\n4 Quay lại\n", 12);

			cout << "\nChọn: ";
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
			UI::center("===== THANH TOÁN =====", 10);
			cout << "1. Thu tiền\n";
			cout << "2. Hoàn trả\n";
			cout << "3. Xem danh sách\n";
			cout << "4. Tìm kiếm\n";
			cout << "5. Xuất Excel\n";
			UI::printColor("6 Quay lại\n", 12);
			cout << "Chọn: ";
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

	void menuDangNhap()
	{
		Login::CheckListAndAdd();
		int chon = 0;
		string username, password;

		UI::clear();
		UI::center("=====ĐĂNG NHẬP=====", 10);
		cout << "Tài Khoản Khám Bệnh: khambenh/khambenh123\n";
		cout << "Tài Khoản Admin: admin/admin123\n";
		cout << "Nhập UserName:";
		getline(cin, username);
		cout << "Nhập Password:";
		password = nhapPasswordAn();
		if (Login::CheckLogin(username, password) == "admin")
		{
			cout << "Đăng nhập thành công với vai trò Admin!\n";
			/*UI::pause();*/
			menuChinh("admin", username);
		}
		else if (Login::CheckLogin(username, password) == "employee")
		{
			cout << "Đăng nhập thành công với vai trò Employee!\n";
			/*UI::pause();*/
			menuChinh("employee", username);
		}
		else
		{
			cout << "Đăng nhập thất bại! Vui lòng thử lại.\n";
			UI::pause();
			menuDangNhap();
		}
	}

	void menuChinh(string role, string user_dangnhap, bool lanDau = true) {

		int c;

		UI::printColor("Đang kiểm tra hệ thống...\n", 10);
		vector<pair<string, string>> dsFile = {
			{"phongkham.xml", "danh sách phòng khám"},
			{"bacsi.xml", "danh sách bác sĩ"},
			{"canlamsang.xml", "danh sách cận lâm sàng"},
			{ "nhapthuoc.xml", "danh sách thuốc" }
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
				UI::printColor("" + kq.tenHienThi + " Không có dữ liệu. Vui lòng khai báo trước khi làm việc.\n", 12);
			}
		}
		cout << endl;
		UI::printColor("Hệ thống kiểm tra tạo xong", 10);
		cout << endl << endl;


		do {

			if (!lanDau) {
				UI::clear();
			}

			UI::center("=====HỆ THỐNG QUẢN LÝ PHÒNG KHÁM PAP SOFT - " + user_dangnhap + " - NGÀY LÀM VIỆC  " + layNgayHienTai() + " - V 1.0.0 =====", 10);
			UI::printColor("==MENU CHÍNH==", 10);
			UI::printColor("\n--Khám bệnh", 1);
			cout << "\n1 Quản lý bệnh nhân";
			if (role == "admin")
			{
				cout << "\n2 Quản lý thuốc";
				cout << "\n3 Quản lý thanh toán";
				UI::printColor("\n--Danh mục", 1);
				cout << "\n4 Danh mục phòng khám";
				cout << "\n5 Danh mục bác sĩ - nhân viên";
				cout << "\n6 Danh mục cận lâm sàng";
				UI::printColor("\n--Thống kê", 1);
				cout << "\n7 Thống kê - báo cáo";
			}
			UI::printColor("\n--Tiên ích", 1);
			cout << "\n8 Đăng nhập lại";
			UI::printColor("\n9 Kết thúc\n", 12);
			c = SystemMethod::nhapSo<int>("Mời bạn chọn:");
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
				canhBaoThuoc();
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

#pragma endregion

#pragma region các chức năng phụ

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

			cout << "Nhập ngày (dd/mm/yyyy): ";
			getline(cin, ngay);

			if (kiemTraNgay(ngay))
				return ngay;

			cout << "Ngày không hợp lệ! Vui lòng nhập lại.\n";
		}
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

	void thongKeTheoNgay() {

		if (!SystemMethod::fileExist("khambenh.xml")) {
			cout << "Không có dữ liệu\n";
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

		cout << "\nNgày " << ngay << " có " << dem << " ca khám\n";

		UI::pause();
	}

	void soSanhHomNayHomQua() {

		if (!SystemMethod::fileExist("khambenh.xml")) {
			cout << "Không có dữ liệu\n";
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

		cout << "\nHôm nay (" << todayStr << ") : " << homnay << " ca\n";
		cout << "Hôm qua (" << yesterdayStr << ") : " << homqua << " ca\n";

		if (homnay > homqua)
			cout << "Tăng " << homnay - homqua << " ca\n";
		else if (homnay < homqua)
			cout << "Giảm " << homqua - homnay << " ca\n";
		else
			cout << "Không thay đổi\n";
		UI::pause();
	}

	void thongKeTienThuocTheoNgay() {

		if (!SystemMethod::fileExist("banthuoc.xml")) {
			cout << "Không có dữ liệu bán thuốc\n";
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
				b.setThanhTien(line.substr(11, line.find("</") - 11));

			if (line.find("<Ngay>") != string::npos) {

				b.setDate(line.substr(6, line.find("</") - 6));

				if (b.getDate() == ngay)
					tongTien += stoll(Helper::boDauChamTien(b.getThanhTien()));
			}
		}

		f.close();

		cout << "\nTổng tiền thuốc bán ngày " << ngay << " = " << Helper::formatTien(to_string(tongTien)) << " VND\n";
		cout << "Bằng chữ: " << Helper::docTienBangChu(tongTien) << endl;

		UI::pause();
	}

	long long laySoLuongDaBanTheoMa(string maCanTim) {
		long long tongBan = 0;

		// Không có file bán thuốc thì coi như chưa bán gì
		if (!SystemMethod::fileExist("banthuoc.xml")) {
			return 0;
		}

		ifstream f("banthuoc.xml");

		string line;
		string ma = "";
		string soluong = "";

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				ma = line.substr(4, line.find("</") - 4);

			if (line.find("<SoLuong>") != string::npos) {
				soluong = line.substr(9, line.find("</") - 9);

				if (ma == maCanTim && !soluong.empty()) {
					tongBan += stoll(Helper::boDauChamTien(soluong));
				}
			}
		}

		f.close();
		return tongBan;
	}

	void canhBaoThuoc() {

		// Không có file nhập thuốc thì bỏ qua luôn
		if (!SystemMethod::fileExist("nhapthuoc.xml")) {
			return;
		}

		ifstream f("nhapthuoc.xml");

		if (!f.is_open()) {
			return;
		}

		string line;

		string ma = "";
		string ten = "";
		string gia = "";
		string soluong = "";
		string lo = "";
		string date = "";
		string ghichu = "";

		bool coDuLieuThuoc = false;

		vector<vector<string>> dsDate;
		vector<vector<string>> dsTon;

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Gia>") != string::npos)
				gia = line.substr(5, line.find("</") - 5);

			if (line.find("<SoLuong>") != string::npos)
				soluong = line.substr(9, line.find("</") - 9);

			if (line.find("<Lo>") != string::npos)
				lo = line.substr(4, line.find("</") - 4);

			if (line.find("<Date>") != string::npos)
				date = line.substr(6, line.find("</") - 6);

			if (line.find("<GhiChu>") != string::npos) {
				ghichu = line.substr(8, line.find("</") - 8);

				// Nếu bản ghi thiếu dữ liệu quan trọng thì bỏ qua
				if (ma.empty() || ten.empty() || soluong.empty() || date.empty()) {
					continue;
				}

				coDuLieuThuoc = true;

				long long ngayConLai = Helper::soNgayConLai(date);

				long long slNhap = stoll(Helper::boDauChamTien(soluong));
				long long slDaBan = laySoLuongDaBanTheoMa(ma);
				long long slConLai = slNhap - slDaBan;
				// trong vòng 30 ngày
				if (ngayConLai >= 0 && ngayConLai <= 30) {
					dsDate.push_back({
						ma,
						ten,
						lo,
						date,
						to_string(ngayConLai) + " ngày",
						"Gần hết date"
						});
				}
				// đã sạch trơn
				if (ngayConLai < 0) {
					dsDate.push_back({
						ma,
						ten,
						lo,
						date,
						"Quá " + to_string(-ngayConLai) + " ngày",
						"Đã hết hạn"
						});
				}
				// so <= 10
				if (slConLai <= 10) {
					dsTon.push_back({
						ma,
						ten,
						Helper::formatTien(to_string(slNhap)),
						Helper::formatTien(to_string(slDaBan)),
						Helper::formatTien(to_string(slConLai)),
						"Gần hết tồn"
						});
				}

				// Reset để tránh dính dữ liệu bản ghi trước
				ma = "";
				ten = "";
				gia = "";
				soluong = "";
				lo = "";
				date = "";
				ghichu = "";
			}
		}

		f.close();

		// Có file nhưng không có thuốc hợp lệ thì bỏ qua
		if (!coDuLieuThuoc) {
			return;
		}

		// Không có cảnh báo gì thì bỏ qua
		if (dsDate.empty() && dsTon.empty()) {
			return;
		}

		UI::clear();
		UI::center("CẢNH BÁO THUỐC", 12);

		if (!dsDate.empty()) {
			UI::printColor("\n===== THUỐC GẦN HẾT DATE / ĐÃ HẾT HẠN =====\n", 14);

			cout << string(115, '-') << endl;

			Helper::inCot(cout, "Mã", 10);
			Helper::inCot(cout, "Tên thuốc", 35);
			Helper::inCot(cout, "Lô", 15);
			Helper::inCot(cout, "Date", 15);
			Helper::inCot(cout, "Còn/Quá", 15);
			Helper::inCot(cout, "Trạng thái", 25);
			cout << endl;

			cout << string(115, '-') << endl;

			for (auto& x : dsDate) {
				Helper::inCot(cout, x[0], 10);
				Helper::inCot(cout, x[1], 35);
				Helper::inCot(cout, x[2], 15);
				Helper::inCot(cout, x[3], 15);
				Helper::inCot(cout, x[4], 15);
				Helper::inCot(cout, x[5], 25);
				cout << endl;
			}

			cout << string(115, '-') << endl;
		}

		if (!dsTon.empty()) {
			UI::printColor("\n===== THUỐC GẦN HẾT TỒN KHO =====\n", 14);

			cout << string(115, '-') << endl;

			Helper::inCot(cout, "Mã", 10);
			Helper::inCot(cout, "Tên thuốc", 35);
			Helper::inCot(cout, "SL nhập", 15);
			Helper::inCot(cout, "Đã bán", 15);
			Helper::inCot(cout, "Còn lại", 15);
			Helper::inCot(cout, "Trạng thái", 25);
			cout << endl;

			cout << string(115, '-') << endl;

			for (auto& x : dsTon) {
				Helper::inCot(cout, x[0], 10);
				Helper::inCot(cout, x[1], 35);
				Helper::inCot(cout, x[2], 15);
				Helper::inCot(cout, x[3], 15);
				Helper::inCot(cout, x[4], 15);
				Helper::inCot(cout, x[5], 25);
				cout << endl;
			}

			cout << string(115, '-') << endl;
		}

		UI::pause();
	}

#pragma endregion
};