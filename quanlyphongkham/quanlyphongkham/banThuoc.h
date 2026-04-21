#pragma once
#include "SystemMethod.h"
#include "LiblaryHeader.h"
#include "banThuoc.h"
#include "Helper.h"


class banThuoc {

public:

	string ma, ten, nguoimua, diachi, dienthoai, benh, soluong, dongia, thanhtien, lo, date, ghichu, ngay;
	vector<string> thongTinThuoc;
	void ban() {

		cin.ignore();

		int loaiNguoiMua;
		while (true) {
			cout << "Loai nguoi mua:\n";
			cout << "1. Benh nhan mua le\n";
			cout << "2. Benh nhan kham tu phong kham\n";
			cout << "Chon: ";
			cin >> loaiNguoiMua;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Lua chon khong hop le. Vui long nhap lai!\n";
				continue;
			}

			cin.ignore(1000, '\n');

			if (loaiNguoiMua == 1) {
				cout << "Nguoi mua: ";
				getline(cin, nguoimua);
				break;
			}
			else if (loaiNguoiMua == 2) {
				nguoimua = Helper::chonTuFile("Chon benh nhan", "khambenh.xml", "KhamBenh", "Ten");
				break;
			}
			else {
				cout << "Lua chon khong hop le. Vui long nhap lai!\n";
			}
		}

		ten = Helper::chonTuFile(
			"Ten thuoc",
			"nhapthuoc.xml",
			"Thuoc",
			"Ten",
			{ "Ma", "Gia", "Lo", "Date" },
			thongTinThuoc
		);
		ma = thongTinThuoc[0];
		dongia = thongTinThuoc[1];
		lo = thongTinThuoc[2];
		date = thongTinThuoc[3];
		cout << "Ma thuoc: " << ma << endl;
		cout << "Lo:  " << lo << endl;
		cout << "Date: " << date << endl;
		soluong = std::to_string(nhapSo<int>("Nhap so luong xuat: "));
		cout << "Don gia: " << dongia << endl;
		thanhtien = to_string(stoi(soluong) * stoi(dongia));
		cout << "Thanh tien: " << thanhtien << endl;

		cout << "Dia chi: ";
		getline(cin, diachi);

		while (true)
		{
			cout << "Dien thoai: ";
			getline(cin, dienthoai);
			if (KiemTraSoDienThoai(dienthoai))
				break;
			else
				cout << "So dien thoai khong hop le! Vui long nhap lai.\n";
		}

		cout << "Ten benh: ";
		getline(cin, benh);
	

		cout << "Ghi chu: ";
		getline(cin, ghichu);

		ngay = SystemMethod::today();
	}

	void save() {
		bool fileMoi = !SystemMethod::fileExist("banthuoc.xml");

		ofstream f("banthuoc.xml", ios::app);
		if (fileMoi) {
			f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		}

		f << "<BanThuoc>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<TenThuoc>" << ten << "</TenThuoc>\n";
		f << "<NguoiMua>" << nguoimua << "</NguoiMua>\n";
		f << "<DiaChi>" << diachi << "</DiaChi>\n";
		f << "<DienThoai>" << dienthoai << "</DienThoai>\n";
		f << "<Benh>" << benh << "</Benh>\n";

		f << "<SoLuong>" << soluong << "</SoLuong>\n";
		f << "<DonGia>" << dongia << "</DonGia>\n";
		f << "<ThanhTien>" << thanhtien << "</ThanhTien>\n";

		f << "<Lo>" << lo << "</Lo>\n";
		f << "<Date>" << date << "</Date>\n";
		f << "<GhiChu>" << ghichu << "</GhiChu>\n";
		f << "<Ngay>" << ngay << "</Ngay>\n";

		f << "</BanThuoc>\n\n";

		f.close();
	}

	static void showTonKho() {

		UI::clear();
		UI::center("TON KHO THUOC", 10);

		/* ================= DANH SACH THUOC DA NHAP ================= */

		cout << "\n===== DANH SACH THUOC DA NHAP =====\n";

		if (!SystemMethod::fileExist("nhapthuoc.xml")) {

			cout << "Khong co du lieu thuoc\n";
		}
		else {

			ifstream f("nhapthuoc.xml");

			string line;
			nhapThuoc t;

			cout << "\n--------------------------------------------------------------------------\n";

			cout << left
				<< setw(10) << "Ma"
				<< setw(20) << "TenThuoc"
				<< setw(10) << "Gia"
				<< setw(10) << "SoLuong"
				<< setw(10) << "Lo"
				<< setw(12) << "Date"
				<< setw(20) << "GhiChu"
				<< endl;

			cout << "--------------------------------------------------------------------------\n";

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					t.ma = line.substr(4, line.find("</") - 4);

				if (line.find("<Ten>") != string::npos)
					t.ten = line.substr(5, line.find("</") - 5);

				if (line.find("<Gia>") != string::npos)
					t.gia = line.substr(5, line.find("</") - 5);

				if (line.find("<Lo>") != string::npos)
					t.lo = line.substr(4, line.find("</") - 4);

				if (line.find("<Date>") != string::npos)
					t.date = line.substr(6, line.find("</") - 6);

				if (line.find("<SoLuong>") != string::npos)
					t.soLuong = line.substr(9, line.find("</") - 9);

				if (line.find("<GhiChu>") != string::npos) {

					t.ghiChu = line.substr(8, line.find("</") - 8);

					cout << left
						<< setw(10) << t.ma
						<< setw(20) << t.ten
						<< setw(10) << t.gia
						<< setw(10) << t.soLuong
						<< setw(10) << t.lo
						<< setw(12) << t.date
						<< setw(20) << t.ghiChu
						<< endl;
				}
			}

			f.close();

			cout << "--------------------------------------------------------------------------\n";
		}

		/* ================= DANH SACH THUOC DA XUAT ================= */

		cout << "\n===== DANH SACH THUOC DA XUAT =====\n";

		if (!SystemMethod::fileExist("banthuoc.xml")) {

			cout << "Khong co du lieu ban thuoc\n";
		}
		else {

			ifstream f("banthuoc.xml");

			string line;
			banThuoc b;

			cout << "\n--------------------------------------------------------------------------\n";

			cout << left
				<< setw(10) << "Ma"
				<< setw(20) << "TenThuoc"
				<< setw(20) << "NguoiMua"
				<< setw(10) << "SoLuong"
				<< setw(10) << "DonGia"
				<< setw(10) << "ThanhTien"
				<< endl;

			cout << "--------------------------------------------------------------------------\n";

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					b.ma = line.substr(4, line.find("</") - 4);

				if (line.find("<TenThuoc>") != string::npos)
					b.ten = line.substr(10, line.find("</") - 10);

				if (line.find("<NguoiMua>") != string::npos)
					b.nguoimua = line.substr(10, line.find("</") - 10);

				if (line.find("<SoLuong>") != string::npos)
					b.soluong = line.substr(9, line.find("</") - 9);

				if (line.find("<DonGia>") != string::npos)
					b.dongia = line.substr(8, line.find("</") - 8);

				if (line.find("<ThanhTien>") != string::npos) {

					b.thanhtien = line.substr(11, line.find("</") - 11);

					cout << left
						<< setw(10) << b.ma
						<< setw(20) << b.ten
						<< setw(20) << b.nguoimua
						<< setw(10) << b.soluong
						<< setw(10) << b.dongia
						<< setw(10) << b.thanhtien
						<< endl;
				}
			}

			f.close();

			cout << "--------------------------------------------------------------------------\n";
		}

		UI::pause();
	}

	static void seachThuoc() {

		if (!SystemMethod::fileExist("nhapthuoc.xml")) {
			cout << "Khong co du lieu thuoc\n";
			UI::pause();
			return;
		}

		int chon;

		cout << "\n===== TIM THUOC =====\n";
		cout << "1 Tim theo ma (tuyet doi)\n";
		cout << "2 Tim theo ten (tuong doi)\n";
		UI::printColor("3 Quay lai\n", 12);

		cout << "Chon: ";
		cin >> chon;

		if (chon == 3)
			return;

		cin.ignore();

		string key;

		if (chon == 1)
			cout << "Nhap ma thuoc: ";
		else
			cout << "Nhap ten thuoc: ";

		getline(cin, key);
		string lowerKey = SystemMethod::toLower(key);
		ifstream f("nhapthuoc.xml");

		string line;
		nhapThuoc t;

		vector<nhapThuoc> ds;

		while (getline(f, line)) 
		{
			if (line.find("<Ma>") != string::npos)
				t.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				t.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Gia>") != string::npos)
				t.gia = line.substr(5, line.find("</") - 5);

			if (line.find("<Lo>") != string::npos)
				t.lo = line.substr(4, line.find("</") - 4);

			if (line.find("<Date>") != string::npos)
				t.date = line.substr(6, line.find("</") - 6);

			if (line.find("<SoLuong>") != string::npos)
				t.soLuong = line.substr(9, line.find("</") - 9);

			if (line.find("<GhiChu>") != string::npos) 
			{
				t.ghiChu = line.substr(8, line.find("</") - 8);

				bool match = false;

				if (chon == 1 && SystemMethod::toLower(t.ma) == key)
					match = true;

				if (chon == 2 && SystemMethod::toLower(t.ten).find(key) != string::npos)
					match = true;

				if (match)
					ds.push_back(t);
			}
		}

		f.close();

		if (ds.empty()) {

			cout << "\nKhong tim thay thuoc!\n";
			UI::pause();
			return;
		}

		cout << "\n--------------------------------------------------------------------------\n";

		cout << left
			<< setw(10) << "Ma"
			<< setw(20) << "TenThuoc"
			<< setw(10) << "Gia"
			<< setw(10) << "SoLuong"
			<< setw(10) << "Lo"
			<< setw(12) << "Date"
			<< setw(20) << "GhiChu"
			<< endl;

		cout << "--------------------------------------------------------------------------\n";

		for (auto& x : ds) {

			cout << left
				<< setw(10) << x.ma
				<< setw(20) << x.ten
				<< setw(10) << x.gia
				<< setw(10) << x.soLuong
				<< setw(10) << x.lo
				<< setw(12) << x.date
				<< setw(20) << x.ghiChu
				<< endl;
		}

		cout << "--------------------------------------------------------------------------\n";

		UI::pause();
	}

	static void exportExcelThuoc() {

		int chon;

		cout << "\n===== XUAT EXCEL =====\n";
		cout << "1 Xuat danh sach thuoc nhap\n";
		cout << "2 Xuat danh sach thuoc ban\n";
		UI::printColor("3 Quay lai\n", 12);

		cout << "Chon: ";
		cin >> chon;

		if (chon == 3)
			return;

		/* ================= XUAT THUOC NHAP ================= */

		if (chon == 1) {

			if (!SystemMethod::fileExist("nhapthuoc.xml")) {
				cout << "Khong co du lieu thuoc\n";
				UI::pause();
				return;
			}

			ifstream f("nhapthuoc.xml");
			ofstream o("nhapthuoc.csv");

			string line;
			nhapThuoc t;

			o << "MaThuoc,TenThuoc,DonGia,SoLuong,Lo,Date,GhiChu\n";

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					t.ma = line.substr(4, line.find("</") - 4);

				if (line.find("<Ten>") != string::npos)
					t.ten = line.substr(5, line.find("</") - 5);

				if (line.find("<Gia>") != string::npos)
					t.gia = line.substr(5, line.find("</") - 5);

				if (line.find("<Lo>") != string::npos)
					t.lo = line.substr(4, line.find("</") - 4);

				if (line.find("<Date>") != string::npos)
					t.date = line.substr(6, line.find("</") - 6);

				if (line.find("<SoLuong>") != string::npos)
					t.soLuong = line.substr(9, line.find("</") - 9);

				if (line.find("<GhiChu>") != string::npos) {

					t.ghiChu = line.substr(8, line.find("</") - 8);

					o << t.ma << ","
						<< t.ten << ","
						<< t.gia << ","
						<< t.soLuong << ","
						<< t.lo << ","
						<< t.date << ","
						<< t.ghiChu << "\n";
				}
			}

			f.close();
			o.close();

			cout << "\nDa xuat file nhapthuoc.csv\n";
			char ch;

			cout << "Ban co muon mo file khong? (Y/N): ";
			cin >> ch;

			if (ch == 'Y' || ch == 'y')
				system("start nhapthuoc.csv");
		}

		/* ================= XUAT THUOC BAN ================= */

		else if (chon == 2) {

			if (!SystemMethod::fileExist("banthuoc.xml")) {
				cout << "Khong co du lieu ban thuoc\n";
				UI::pause();
				return;
			}

			ifstream f("banthuoc.xml");
			ofstream o("banthuoc.csv");

			string line;
			banThuoc b;

			o << "Ma,TenThuoc,NguoiMua,DiaChi,DienThoai,Benh,SoLuong,DonGia,ThanhTien,Lo,Date,GhiChu,Ngay\n";

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					b.ma = line.substr(4, line.find("</") - 4);

				if (line.find("<TenThuoc>") != string::npos)
					b.ten = line.substr(10, line.find("</") - 10);

				if (line.find("<NguoiMua>") != string::npos)
					b.nguoimua = line.substr(10, line.find("</") - 10);

				if (line.find("<DiaChi>") != string::npos)
					b.diachi = line.substr(8, line.find("</") - 8);

				if (line.find("<DienThoai>") != string::npos)
					b.dienthoai = line.substr(11, line.find("</") - 11);

				if (line.find("<Benh>") != string::npos)
					b.benh = line.substr(6, line.find("</") - 6);

				if (line.find("<SoLuong>") != string::npos)
					b.soluong = line.substr(9, line.find("</") - 9);

				if (line.find("<DonGia>") != string::npos)
					b.dongia = line.substr(8, line.find("</") - 8);

				if (line.find("<ThanhTien>") != string::npos)
					b.thanhtien = line.substr(11, line.find("</") - 11);

				if (line.find("<Lo>") != string::npos)
					b.lo = line.substr(4, line.find("</") - 4);

				if (line.find("<Date>") != string::npos)
					b.date = line.substr(6, line.find("</") - 6);

				if (line.find("<GhiChu>") != string::npos)
					b.ghichu = line.substr(8, line.find("</") - 8);

				if (line.find("<Ngay>") != string::npos) {
					b.ngay = line.substr(6, line.find("</") - 6);

					o << b.ma << ","
						<< b.ten << ","
						<< b.nguoimua << ","
						<< b.diachi << ","
						<< b.dienthoai << ","
						<< b.benh << ","
						<< b.soluong << ","
						<< b.dongia << ","
						<< b.thanhtien << ","
						<< b.lo << ","
						<< b.date << ","
						<< b.ghichu << ","
						<< b.ngay << "\n";
				}
			}

			f.close();
			o.close();

			cout << "\nDa xuat file banthuoc.csv\n";
			char ch;

			cout << "Ban co muon mo file khong? (Y/N): ";
			cin >> ch;

			if (ch == 'Y' || ch == 'y')
				system("start banthuoc.csv");
		}

		UI::pause();
	}

	//=========================== CÁC HÀM KIỂM TRA CHO Bán THUỐC ===========================
	template <typename T>
	T nhapSo(string thongBao) {
		T value;
		while (true) {
			cout << thongBao;
			if (cin >> value) {
				// Nhập thành công, dọn dẹp bộ đệm đến hết dòng để tránh trôi lệnh sau
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				return value;
			}
			else {
				cout << "Loi vui long nhap so.\n";
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
		}
	}

	bool KiemTraSoDienThoai(const string& sdt) {
		// Regex này kiểm tra:
		// ^0: Bắt đầu bằng số 0
		// [35789]: Chữ số thứ hai thường là 3, 5, 7, 8, 9 (các đầu số nhà mạng VN)
		// [0-9]{8}: 8 chữ số tiếp theo là bất kỳ số nào từ 0-9
		// $: Kết thúc chuỗi
		const regex pattern("^0[35789][0-9]{8}$");

		return regex_match(sdt, pattern);
	}
};
