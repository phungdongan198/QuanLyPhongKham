#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"



class ThuTien {
public:
	string ma, ten, soTien, nguoiThu, lyDo, ngay;


	void nhapThu() {
		cin.ignore();

		ten = Helper::chonTuFile(
			"Ten BN",
			"khambenh.xml",
			"KhamBenh",
			"Ten",
			"Ma",
			ma
		);
		cout << "Ma benh nhan: " << ma << endl;

		cout << "So tien: "; getline(cin, soTien);
        nguoiThu = Helper::chonTuFile("Chon nguoi thu", "bacsi.xml", "BacSi", "Ten");

		ngay = SystemMethod::today();
	}

	void saveThu() {
		ofstream f("thutien.xml", ios::app);

		f << "<ThuTien>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<SoTien>" << soTien << "</SoTien>\n";
		f << "<NguoiThu>" << nguoiThu << "</NguoiThu>\n";
		f << "<Ngay>" << ngay << "</Ngay>\n";
		f << "</ThuTien>\n\n";

		f.close();
	}


	void nhapHoan() {
		cin.ignore();

		ten = Helper::chonTuFile(
			"Ten BN",
			"khambenh.xml",
			"KhamBenh",
			"Ten",
			"Ma",
			ma
		);
		cout << "Ma benh nhan: " << ma << endl;
		cout << "So tien tra: "; getline(cin, soTien);
	    nguoiThu = Helper::chonTuFile("Chon nguoi thu", "bacsi.xml", "BacSi", "Ten");
		cout << "Ly do: "; getline(cin, lyDo);

		ngay = SystemMethod::today();
	}

	void saveHoan() {
		ofstream f("hoantra.xml", ios::app);

		f << "<HoanTra>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<SoTien>" << soTien << "</SoTien>\n";
		f << "<NguoiThu>" << nguoiThu << "</NguoiThu>\n";
		f << "<LyDo>" << lyDo << "</LyDo>\n";
		f << "<Ngay>" << ngay << "</Ngay>\n";
		f << "</HoanTra>\n\n";

		f.close();
	}


	static void showAll() {

		string line;


		if (SystemMethod::fileExist("thutien.xml")) {

			ifstream f("thutien.xml");

			ThuTien t;
			vector<ThuTien> dsThu;

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					t.ma = line.substr(4, line.find("</") - 4);

				if (line.find("<Ten>") != string::npos)
					t.ten = line.substr(5, line.find("</") - 5);

				if (line.find("<SoTien>") != string::npos)
					t.soTien = line.substr(8, line.find("</") - 8);

				if (line.find("<NguoiThu>") != string::npos)
					t.nguoiThu = line.substr(10, line.find("</") - 10);

				if (line.find("<Ngay>") != string::npos) {

					t.ngay = line.substr(6, line.find("</") - 6);

					dsThu.push_back(t); // 👉 giống benhnhan
				}
			}

			f.close();

			cout << "\n================= DANH SACH THU =================\n";

			cout << left
				<< setw(10) << "Ma"
				<< setw(20) << "Ten"
				<< setw(12) << "SoTien"
				<< setw(20) << "NguoiThu"
				<< setw(15) << "Ngay"
				<< endl;

			cout << "--------------------------------------------------------------------------------------------------\n";

			for (auto& x : dsThu) {
				cout << left
					<< setw(10) << x.ma
					<< setw(20) << x.ten
					<< setw(12) << x.soTien
					<< setw(20) << x.nguoiThu
					<< setw(15) << x.ngay
					<< endl;
			}
		}


		if (SystemMethod::fileExist("hoantra.xml")) {

			ifstream f("hoantra.xml");

			ThuTien h;
			vector<ThuTien> dsHoan;

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					h.ma = line.substr(4, line.find("</") - 4);

				if (line.find("<Ten>") != string::npos)
					h.ten = line.substr(5, line.find("</") - 5);

				if (line.find("<SoTien>") != string::npos)
					h.soTien = line.substr(8, line.find("</") - 8);

				if (line.find("<NguoiThu>") != string::npos)
					h.nguoiThu = line.substr(10, line.find("</") - 10);

				if (line.find("<LyDo>") != string::npos)
					h.lyDo = line.substr(6, line.find("</") - 6);

				if (line.find("<Ngay>") != string::npos) {

					h.ngay = line.substr(6, line.find("</") - 6);

					dsHoan.push_back(h);
				}
			}

			f.close();

			cout << "\n================= DANH SACH HOAN =================\n";

			cout << left
				<< setw(10) << "Ma"
				<< setw(20) << "Ten"
				<< setw(12) << "SoTien"
				<< setw(20) << "NguoiThu"
				<< setw(20) << "LyDo"
				<< setw(15) << "Ngay"
				<< endl;

			cout << "--------------------------------------------------------------------------------------------------\n";

			for (auto& x : dsHoan) {
				cout << left
					<< setw(10) << x.ma
					<< setw(20) << x.ten
					<< setw(12) << x.soTien
					<< setw(20) << x.nguoiThu
					<< setw(20) << x.lyDo
					<< setw(15) << x.ngay
					<< endl;
			}
		}

		// ❌ Không có file nào
		if (!SystemMethod::fileExist("thutien.xml") &&
			!SystemMethod::fileExist("hoantra.xml")) {

			cout << "Khong co du lieu\n";
		}

		UI::pause();
	}


	static void search() {

		int c;

		if (!SystemMethod::fileExist("thutien.xml")) {
			cout << "Khong co du lieu\n";
			UI::pause();
			return;
		}

		cout << "\n===== TIM KIEM THU TIEN =====\n";
		cout << "1. Tim theo ma (tuyet doi)\n";
		cout << "2. Tim theo ten (tuong doi)\n";
		UI::printColor("3 Quay lai\n", 12);

		cout << "Chon: ";
		c = SystemMethod::kiemTraKyTu();

		if (c == 3) return;

		cin.ignore();

		string key;

		if (c == 1)
			cout << "Nhap ma benh nhan: ";
		else
			cout << "Nhap ten can tim: ";

		getline(cin, key);

		ifstream f("thutien.xml");

		string line;
		vector<ThuTien> ds;
		ThuTien t;

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				t.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				t.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<SoTien>") != string::npos)
				t.soTien = line.substr(8, line.find("</") - 8);

			if (line.find("<NguoiThu>") != string::npos)
				t.nguoiThu = line.substr(10, line.find("</") - 10);

			if (line.find("<Ngay>") != string::npos) {

				t.ngay = line.substr(6, line.find("</") - 6);

				bool match = false;

				if (c == 1 && t.ma == key)
					match = true;

				if (c == 2 && t.ten.find(key) != string::npos)
					match = true;

				if (match)
					ds.push_back(t);
			}
		}

		f.close();


		if (ds.empty()) {
			cout << "\nKhong tim thay!\n";
			UI::pause();
			return;
		}


		cout << "\n--------------------------------------------------------------------------\n";

		cout << left
			<< setw(10) << "Ma"
			<< setw(20) << "Ten"
			<< setw(12) << "SoTien"
			<< setw(20) << "NguoiThu"
			<< setw(15) << "Ngay"
			<< endl;

		cout << "--------------------------------------------------------------------------\n";

		for (auto& x : ds) {
			cout << left
				<< setw(10) << x.ma
				<< setw(20) << x.ten
				<< setw(12) << x.soTien
				<< setw(20) << x.nguoiThu
				<< setw(15) << x.ngay
				<< endl;
		}

		cout << "--------------------------------------------------------------------------\n";

		UI::pause();
	}


	static void exportExcel() {

		ofstream o("thutien_all.csv");

		o << "Loai,Ma,Ten,SoTien,NguoiThu,Ngay,LyDo\n";

		string line;


		ifstream f1("thutien.xml");
		ThuTien t;

		while (getline(f1, line)) {

			if (line.find("<Ma>") != string::npos)
				t.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				t.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<SoTien>") != string::npos)
				t.soTien = line.substr(8, line.find("</") - 8);

			if (line.find("<NguoiThu>") != string::npos)
				t.nguoiThu = line.substr(10, line.find("</") - 10);

			if (line.find("<Ngay>") != string::npos) {

				t.ngay = line.substr(6, line.find("</") - 6);

				o << "Thu," << t.ma << "," << t.ten << ","
					<< t.soTien << "," << t.nguoiThu << ","
					<< t.ngay << ",\n";
			}
		}

		f1.close();


		ifstream f2("hoantra.xml");
		ThuTien h;

		while (getline(f2, line)) {

			if (line.find("<Ma>") != string::npos)
				h.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				h.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<SoTien>") != string::npos)
				h.soTien = line.substr(8, line.find("</") - 8);

			if (line.find("<LyDo>") != string::npos)
				h.lyDo = line.substr(6, line.find("</") - 6);

			if (line.find("<Ngay>") != string::npos) {

				h.ngay = line.substr(6, line.find("</") - 6);

				o << "Hoan," << h.ma << "," << h.ten << ","
					<< "-" << h.soTien << ",," << h.ngay << ","
					<< h.lyDo << "\n";
			}
		}

		f2.close();
		o.close();

		cout << "Xuat Excel thanh cong\n";
		char ch;

		cout << "Ban co muon mo file khong? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start thutien_all.csv");

		UI::pause();
	}
};