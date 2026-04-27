#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"


class PhongKham {
private:
	string ma, ten, loai;

public:
	#pragma	region getter_&_setter

	string getMa() const { return ma; }
	void setMa(const string& val) { ma = val; }

	string getTen() const { return ten; }
	void setTen(const string& val) { ten = val; }

	string getLoai() const { return loai; }
	void setLoai(const string& val) { loai = val; }

	#pragma endregion

	#pragma region các hàm xử lý menu

	void nhap() {

		cin.ignore();

		ma = Helper::nhapMaKhongTrung(
			"Mã phòng khám:",
			"phongkham.xml",
			"Phong",
			"Ma"
		);

		cout << "Tên phòng: ";
		getline(cin, ten);

		cout << "Loại phòng: ";
		getline(cin, loai);
	}

	void save() {
		bool fileMoi = !SystemMethod::fileExist("phongkham.xml");

		ofstream f("phongkham.xml", ios::app);
		if (fileMoi) {
			f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		}

		f << "<Phong>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<Loai>" << loai << "</Loai>\n";
		f << "</Phong>\n\n";

		f.close();
	}

	static void showPhongKham() {

		if (!SystemMethod::fileExist("phongkham.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		ifstream f("phongkham.xml");

		string line;
		PhongKham pk;

		vector<PhongKham> ds;

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				pk.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				pk.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Loai>") != string::npos) {

				pk.loai = line.substr(6, line.find("</") - 6);

				ds.push_back(pk);
			}
		}

		f.close();

		cout << string(120, '-') << endl;
		Helper::inCot(cout, "Mã Phòng", 10);
		Helper::inCot(cout, "Tên Phòng", 30);
		Helper::inCot(cout, "Loại Phòng", 20);
		cout << endl;
		cout << string(120, '-') << endl;

		for (auto& p : ds) {
			Helper::inCot(cout, p.ma, 10);
			Helper::inCot(cout, p.ten, 30);
			Helper::inCot(cout, p.loai, 20);
			cout << endl;

		}

		cout << string(120, '-') << endl;

		UI::pause();
	}

	static void searchPhongkham() {
		int c;
		if (!SystemMethod::fileExist("phongkham.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}


		cout << "\n===== TÌM PHÒNG KHÁM =====\n";
		cout << "1 Tìm theo mã\n";
		cout << "2 Tìm theo tên\n";
		UI::printColor("3 Quay lại\n", 12);

		cout << "Chọn: ";
		c = SystemMethod::kiemTraKyTu();


		if (c == 3)
			return;

		cin.ignore();

		string key;

		if (c == 1)
			cout << "Nhập mã phòng: ";
		else
			cout << "Nhập tên phòng: ";

		getline(cin, key);
		string lowerKey = SystemMethod::toLower(key);
		ifstream f("phongkham.xml");

		string line;
		vector<PhongKham> ds;
		PhongKham pk;

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				pk.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				pk.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Loai>") != string::npos) {

				pk.loai = line.substr(6, line.find("</") - 6);

				bool match = false;

				if (c == 1 && SystemMethod::toLower(pk.ma) == key)
					match = true;

				if (c == 2 && SystemMethod::toLower(pk.ten).find(key) != string::npos)
					match = true;

				if (match)
					ds.push_back(pk);
			}
		}

		f.close();

		if (ds.empty()) {

			cout << "\nKhông tìm thấy!\n";
			UI::pause();
			return;
		}

		cout << string(120, '-') << endl;

		Helper::inCot(cout, "Mã Phòng", 10);
		Helper::inCot(cout, "Tên Phòng", 30);
		Helper::inCot(cout, "Loại Phòng", 20);
		cout << endl;

		cout << string(120, '-') << endl;

		for (auto& p : ds) {

			Helper::inCot(cout, p.ma, 10);
			Helper::inCot(cout, p.ten, 30);
			Helper::inCot(cout, p.loai, 20);
			cout << endl;
		}

		cout << string(120, '-') << endl;

		UI::pause();
	}

	static void exportExcePhongKham() {

		if (!SystemMethod::fileExist("phongkham.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		ifstream f("phongkham.xml");
		ofstream o("phongkham.csv", ios::binary);
		o << "\xEF\xBB\xBF";

		string line;
		PhongKham pk;

		/* header excel */
		o << "MaPhong,TenPhong,LoaiPhong\n";

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				pk.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				pk.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Loai>") != string::npos) {

				pk.loai = line.substr(6, line.find("</") - 6);

				o << pk.ma << ","
					<< pk.ten << ","
					<< pk.loai << "\n";
			}
		}

		f.close();
		o.close();

		cout << "\nXuất Excel thành công: phongkham.csv\n";

		char ch;

		cout << "Bạn có muốn mở file không? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start phongkham.csv");

		UI::pause();
	}

	#pragma endregion
};