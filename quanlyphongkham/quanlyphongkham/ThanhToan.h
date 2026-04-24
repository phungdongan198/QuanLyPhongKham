#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"

class ThuTien {
private:
	string ma, ten, soTien, nguoiThu, lyDo, ngay;

public:
	#pragma region các getter và setter
	// Getter và Setter cho Ma
	string getMa() const { return ma; }
	void setMa(const string& val) { ma = val; }

	// Getter và Setter cho Ten (Tên phiếu hoặc Tên người nộp)
	string getTen() const { return ten; }
	void setTen(const string& val) { ten = val; }

	// Getter và Setter cho SoTien
	string getSoTien() const { return soTien; }
	void setSoTien(const string& val) { soTien = val; }

	// Getter và Setter cho NguoiThu
	string getNguoiThu() const { return nguoiThu; }
	void setNguoiThu(const string& val) { nguoiThu = val; }

	// Getter và Setter cho LyDo
	string getLyDo() const { return lyDo; }
	void setLyDo(const string& val) { lyDo = val; }

	// Getter và Setter cho Ngay
	string getNgay() const { return ngay; }
	void setNgay(const string& val) { ngay = val; }
	#pragma endregion

	void nhapThu() {
		cin.ignore();

		ten = Helper::chonTuFile(
			"tên BN",
			"khambenh.xml",
			"KhamBenh",
			"Ten",
			"Ma",
			ma
		);
		cout << "Mã bệnh nhân: " << ma << endl;
 
		//Nhập số tiền
		while (true)
		{
			int tienThu = nhapSo<int>("Nhập Số tiền: ");
			if (tienThu > 100)
			{
				soTien = std::to_string(tienThu);
				break;
			}
			else
			{
				cout << "Giá tiền phải từ 100 trở lên! Vui lòng nhập lại.\n";
			}
		}

        nguoiThu = Helper::chonTuFile("Chọn người thu", "bacsi.xml", "BacSi", "Ten");
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
			"Tên BN",
			"khambenh.xml",
			"KhamBenh",
			"Ten",
			"Ma",
			ma
		);
		cout << "Mã bệnh nhân: " << ma << endl;
		//Nhập số tiền hoàn
		while (true)
		{
			int tienHoan = nhapSo<int>("Nhập Số tiền hoàn: ");
			if (tienHoan >= 100)
			{
				soTien = std::to_string(tienHoan);
				break;
			}
			else
			{
				cout << "Giá tiền phải từ 100 trở lên! Vui lòng nhập lại.\n";
			}
		}

	    nguoiThu = Helper::chonTuFile("Chọn người thu", "bacsi.xml", "BacSi", "Ten");
		cout << "Lý do: "; getline(cin, lyDo);

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

			cout << "\n================= DANH SÁCH THU =================\n";
			cout << left
				<< setw(10) << "Mã"
				<< setw(20) << "Tên"
				<< setw(12) << "Số Tiền"
				<< setw(20) << "Người Thu"
				<< setw(15) << "Ngày"
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

			cout << "\n================= DANH SÁCH HOÀN =================\n";

			cout << left
				<< setw(10) << "Mã"
				<< setw(20) << "Tên"
				<< setw(12) << "Số Tiền"
				<< setw(20) << "Người Thu"
				<< setw(20) << "Lý Do"
				<< setw(15) << "Ngày"
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

			cout << "Không có dữ liệu\n";
		}

		UI::pause();
	}

	static void search() {

		int c;

		if (!SystemMethod::fileExist("thutien.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		cout << "\n===== TÌM KIẾM THU TIỀN =====\n";
		cout << "1. Tìm theo mã (tuyệt đối)\n";
		cout << "2. Tìm theo tên (tương đối)\n";
		UI::printColor("3 Quay lại\n", 12);

		cout << "Chọn: ";
		c = SystemMethod::kiemTraKyTu();

		if (c == 3) return;

		cin.ignore();

		string key;

		if (c == 1)
			cout << "Nhập mã bệnh nhân: ";
		else
			cout << "Nhập tên cần tìm: ";

		getline(cin, key);
		string lowerKey = SystemMethod::toLower(key);
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

				if (c == 1 && SystemMethod::toLower(t.ma) == key)
					match = true;

				if (c == 2 && SystemMethod::toLower(t.ten).find(key) != string::npos)
					match = true;

				if (match)
					ds.push_back(t);
			}
		}

		f.close();


		if (ds.empty()) {
			cout << "\nKhông tìm thấy!\n";
			UI::pause();
			return;
		}


		cout << "\n--------------------------------------------------------------------------\n";

		cout << left
			<< setw(10) << "Mã"
			<< setw(20) << "Tên"
			<< setw(12) << "Số Tiền"
			<< setw(20) << "Người Thu"
			<< setw(15) << "Ngày"
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

		cout << "Xuất Excel thành công\n";
		char ch;

		cout << "Bạn có muốn mở file không? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start thutien_all.csv");

		UI::pause();
	}

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
				cout << "Lỗi! Vui lòng nhập số.\n";
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
		}
	}
};