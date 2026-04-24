#pragma once
#include "LiblaryHeader.h"
#include "SystemMethod.h"
#include "Helper.h"
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <limits>
#include <regex>
#include "QuanLy.h"


class BenhNhan : public DoiTuongQuanLy {

private:
	// phần nhập đk
	string ma, ten, sinh, gioiTinh;
	string dienThoai, diaChi, doiTuong;
	string phong, trangthai, ngay, noidungkham, cls;


public:
	#pragma region các getter và setter
	string getMa() const { return ma; }
	void setMa(const string& val) { ma = val; }

	string getTen() const { return ten; }
	void setTen(const string& val) { ten = val; }

	string getSinh() const { return sinh; }
	void setSinh(const string& val) { sinh = val; }

	string getGioiTinh() const { return gioiTinh; }
	void setGioiTinh(const string& val) { gioiTinh = val; }

	string getDienThoai() const { return dienThoai; }
	void setDienThoai(const string& val) { dienThoai = val; }

	string getDiaChi() const { return diaChi; }
	void setDiaChi(const string& val) { diaChi = val; }

	string getDoiTuong() const { return doiTuong; }
	void setDoiTuong(const string& val) { doiTuong = val; }

	string getPhong() const { return phong; }
	void setPhong(const string& val) { phong = val; }

	string getTrangThai() const { return trangthai; }
	void setTrangThai(const string& val) { trangthai = val; }

	string getNgay() const { return ngay; }
	void setNgay(const string& val) { ngay = val; }

	string getNoiDungKham() const { return noidungkham; }
	void setNoiDungKham(const string& val) { noidungkham = val; }

	string getCls() const { return cls; }
	void setCls(const string& val) { cls = val; }
#pragma endregion
	
	string NhapVaKiemTraNamSinh() {
		int dd, mm, yyyy;
		char slash1, slash2;

		while (true) {
			cout << "Nhập ngày sinh (Với định dạng dd / mm / yyyy): ";

			// Đọc dữ liệu theo định dạng dd / mm / yyyy
			if (cin >> dd >> slash1 >> mm >> slash2 >> yyyy && slash1 == '/' && slash2 == '/') {

				// Kiểm tra tính hợp lệ của ngày tháng (logic cơ bản)
				if (mm >= 1 && mm <= 12 && dd >= 1 && dd <= 31 && yyyy >= 1920 && yyyy <= 2026) {
					char buffer[11];
					sprintf_s(buffer, "%02d/%02d/%04d", dd, mm, yyyy);
					return string(buffer); // Thoát hàm và trả về kết quả
				}
			}

			// Nếu nhập sai định dạng hoặc sai logic ngày tháng
			cout << "Ngày tháng năm sinh bạn nhập không hợp lệ! Vui lòng nhập lại.\n";
			cin.clear(); // Xóa trạng thái lỗi
			cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Xóa sạch bộ đệm cho đến khi gặp dòng mới
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

	string layGiaTriTag(const string& block, const string& tag) {
		string openTag = "<" + tag + ">";
		string closeTag = "</" + tag + ">";

		size_t start = block.find(openTag);
		size_t end = block.find(closeTag);

		if (start == string::npos || end == string::npos) {
			return "";
		}

		start += openTag.length();
		return block.substr(start, end - start);
	}

	void capNhatTinhTrangBenhNhan(const string& maCanTim) {
		ifstream fileIn("benhnhan.xml");

		if (!fileIn.is_open()) {
			cout << "Không mở được file benhnhan.xml!\n";
			return;
		}

		string line;
		string noiDungMoi = "";
		string block = "";
		bool dangDocBenhNhan = false;

		while (getline(fileIn, line)) {
			if (line.find("<BenhNhan>") != string::npos) {
				dangDocBenhNhan = true;
				block = line + "\n";
			}
			else if (dangDocBenhNhan) {
				block += line + "\n";

				if (line.find("</BenhNhan>") != string::npos) {
					string maTrongFile = layGiaTriTag(block, "Ma");

					if (maTrongFile == maCanTim) {
						size_t start = block.find("<TrangThai>");
						size_t end = block.find("</TrangThai>");

						if (start != string::npos && end != string::npos) {
							end += string("</TrangThai>").length();

							block.replace(
								start,
								end - start,
								"<TrangThai>Dakham</TrangThai>"
							);
						}
					}

					noiDungMoi += block;
					block = "";
					dangDocBenhNhan = false;
				}
			}
			else {
				noiDungMoi += line + "\n";
			}
		}

		fileIn.close();

		ofstream fileOut("benhnhan.xml");

		if (!fileOut.is_open()) {
			cout << "Không ghi được file benhnhan.xml!\n";
			return;
		}

		fileOut << noiDungMoi;
		fileOut.close();
	}

	void nhapDangKy() {

		cin.ignore();

		ma = Helper::nhapMaKhongTrung(
			"Nhập mã bệnh nhân: ",
			"benhnhan.xml",
			"BenhNhan",
			"Ma"
		);

		cout << "Họ tên: ";
		getline(cin, ten);

		sinh = NhapVaKiemTraNamSinh();

		cout << "Giới tính: ";
		gioiTinh = Helper::chonTuDanhSach("Chọn giới tính", { "Nam", "Nữ","Khác" });

		//Kiểm tra nhập số điện thoại hợp lệ
		while (true)
		{
			cout << "Điện thoại: ";
			getline(cin, dienThoai);
			if (KiemTraSoDienThoai(dienThoai))
				break;
			else
				cout << "Số điện thoại không hợp lệ! Vui lòng nhập lại.\n";
		}

		cout << "Địa chỉ: ";
		getline(cin, diaChi);

		cout << "Đối tượng: ";
		doiTuong = Helper::chonTuDanhSach("Chọn đối tượng", { "BHYT", "Thu phí","Khác" });

		cout << "Phòng khám: ";
		phong = Helper::chonTuFile("Chọn phòng khám", "phongkham.xml", "Phong", "Ten");

		trangthai = "Mới";

		ngay = SystemMethod::today();
	}

	void saveDangKy() {
		bool fileMoi = !SystemMethod::fileExist("benhnhan.xml");

		ofstream file("benhnhan.xml", ios::app);

		if (fileMoi) {
			file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		}

		file << "<BenhNhan>\n";
		file << "<Ma>" << ma << "</Ma>\n";
		file << "<Ten>" << ten << "</Ten>\n";
		file << "<Sinh>" << sinh << "</Sinh>\n";
		file << "<GioiTinh>" << gioiTinh << "</GioiTinh>\n";
		file << "<DienThoai>" << dienThoai << "</DienThoai>\n";
		file << "<DiaChi>" << diaChi << "</DiaChi>\n";
		file << "<DoiTuong>" << doiTuong << "</DoiTuong>\n";
		file << "<Phong>" << phong << "</Phong>\n";
		file << "<TrangThai>" << trangthai << "</TrangThai>\n";
		file << "<Ngay>" << ngay << "</Ngay>\n";
		file << "</BenhNhan>\n\n";

		file.close();
	}

	void nhap() override {
		nhapDangKy();
	}

	void save() override {
		saveDangKy();
	}

	void nhapKhamBenh() {

		cin.ignore();

		ten = Helper::chonTuFile(
			"Chọn tên",
			"benhnhan.xml",
			"BenhNhan",
			"Ten",
			"Ma",
			ma
		);
		cout << "Mã bệnh nhân: " << ma << endl;

		cout << "Nội dung khám: ";
		getline(cin, noidungkham);

		cls = Helper::chonTuFile(
			"Chọn dịch vụ",
			"canlamsang.xml",
			"CLS",
			"Ten"
		);

		ngay = SystemMethod::today();
	}

	void saveKhamBenh() {

		bool fileMoi = !SystemMethod::fileExist("khambenh.xml");

		ofstream file("khambenh.xml", ios::app);

		if (fileMoi) {
			file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		}

		file << "<KhamBenh>\n";
		file << "<Ma>" << ma << "</Ma>\n";
		file << "<Ten>" << ten << "</Ten>\n";
		file << "<Noidungkham>" << noidungkham << "</Noidungkham>\n";
		file << "<DichVu>" << cls << "</DichVu>\n";
		file << "<Ngay>" << ngay << "</Ngay>\n";
		file << "</KhamBenh>\n\n";
		file.close();
		capNhatTinhTrangBenhNhan(ma);
	}

	static void deleteBenhNhan() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		ifstream in("benhnhan.xml");

		vector<string> lines;
		string line;

		while (getline(in, line)) {
			lines.push_back(line);
		}
		in.close();

		if (lines.empty()) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		string ten;
		string maXoa;

		cout << "Chọn bệnh nhân cần xóa: ";

		ten = Helper::chonTuFile(
			"Chon ten:",
			"benhnhan.xml",
			"BenhNhan",
			"Ten",
			"Ma",
			maXoa
		);


		vector<string> newLines;
		bool found = false;
		bool daKham = false;
		int count = 0;

		for (int i = 0; i < lines.size(); i++) {
			if (lines[i].find("<BenhNhan>") != string::npos) {
				vector<string> temp;
				bool match = false;
				string trangthai = "";

				while (i < lines.size()) {
					temp.push_back(lines[i]);

					if (lines[i].find("<Ma>") != string::npos) {
						size_t start = lines[i].find("<Ma>");
						size_t end = lines[i].find("</Ma>");

						if (start != string::npos && end != string::npos) {
							start += string("<Ma>").length();
							string ma = lines[i].substr(start, end - start);

							if (ma == maXoa) {
								match = true;
							}
						}
					}

					if (lines[i].find("<TrangThai>") != string::npos) {
						size_t start = lines[i].find("<TrangThai>");
						size_t end = lines[i].find("</TrangThai>");

						if (start != string::npos && end != string::npos) {
							start += string("<TrangThai>").length();
							trangthai = lines[i].substr(start, end - start);
						}
					}

					if (lines[i].find("</BenhNhan>") != string::npos)
						break;

					i++;
				}

				if (match) {
					found = true;

					if (trangthai == "Moi") {
						count++;
						// Không đưa temp vào newLines => xóa bệnh nhân
					}
					else {
						daKham = true;

						for (auto& l : temp)
							newLines.push_back(l);
					}
				}
				else {
					for (auto& l : temp)
						newLines.push_back(l);
				}
			}
			else {
				newLines.push_back(lines[i]);
			}
		}

		if (!found) {
			cout << "Không có thông tin bệnh nhân!\n";
			UI::pause();
			return;
		}

		if (daKham && count == 0) {
			cout << "Bệnh nhân đã khám, không thể xóa!\n";
			UI::pause();
			return;
		}

		ofstream out("benhnhan.xml");
		for (auto& l : newLines) {
			out << l << endl;
		}
		out.close();

		cout << "Đã xóa bệnh nhân: " << ten << endl;
		cout << "Mã bệnh nhân: " << maXoa << endl;

		UI::pause();
	}

	// nạp chồng toán tử
	friend ostream& operator<<(ostream& out, const BenhNhan& bn) {
		out << left
			<< setw(10) << bn.ma
			<< setw(20) << bn.ten
			<< setw(15) << bn.sinh
			<< setw(15) << bn.phong
			<< setw(15) << bn.ngay
			<< setw(15) << bn.trangthai;

		return out;
	}

	static void showBenhNhan() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		ifstream f("benhnhan.xml");

		string line;
		BenhNhan bn;

		vector<BenhNhan> ds;

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				bn.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				bn.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Sinh>") != string::npos)
				bn.sinh = line.substr(6, line.find("</") - 6);

			if (line.find("<Phong>") != string::npos)
				bn.phong = line.substr(7, line.find("</") - 7);

			if (line.find("<TrangThai>") != string::npos)
				bn.trangthai = line.substr(11, line.find("</") - 11);

			if (line.find("<Ngay>") != string::npos) {

				bn.ngay = line.substr(6, line.find("</") - 6);

				ds.push_back(bn);
			}
		}

		f.close();

		cout << "\n--------------------------------------------------------------------------------\n";

		cout << left
			<< setw(10) << "Mã BN"
			<< setw(20) << "Tên"
			<< setw(15) << "Ngày Sinh"
			<< setw(15) << "Phòng"
			<< setw(15) << "Ngày Khám"
			<< setw(15) << "Trạng Thái"
			<< endl;

		cout << "--------------------------------------------------------------------------------\n";

		for (auto& b : ds) {

			cout << b << endl;
		}

		cout << "--------------------------------------------------------------------------------\n";
		UI::pause();
	}

	void hienThi() override {
		cout << left
			<< setw(10) << ma
			<< setw(20) << ten
			<< setw(15) << sinh
			<< setw(15) << phong
			<< setw(15) << ngay
			<< setw(15) << trangthai
			<< endl;
	}

	static void searchBenhNhan() {
		int c;
		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}


		cout << "\n===== TÌM KIẾM BỆNH NHÂN =====\n";
		cout << "1. Tìm theo mã (tuyệt đối)\n";
		cout << "2. Tìm theo tên (tương đối)\n";
		UI::printColor("3 Quay lại\n", 12);

		cout << "Chọn: "; ;
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
		ifstream f("benhnhan.xml");

		string line;
		vector<BenhNhan> ds;
		BenhNhan bn;

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				bn.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				bn.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Sinh>") != string::npos)
				bn.sinh = line.substr(6, line.find("</") - 6);

			if (line.find("<Phong>") != string::npos)
				bn.phong = line.substr(7, line.find("</") - 7);

			if (line.find("<Ngay>") != string::npos) {

				bn.ngay = line.substr(6, line.find("</") - 6);

				bool match = false;

				if (c == 1 && SystemMethod::toLower(bn.ma) == key)
					match = true;

				if (c == 2 && SystemMethod::toLower(bn.ten).find(key) != string::npos)
					match = true;

				if (match)
					ds.push_back(bn);
			}
		}

		f.close();

		if (ds.empty()) {

			cout << "\nKhông tìm thấy!\n";
			UI::pause();
			return;
		}

		cout << "\n--------------------------------------------------------------------------------\n";

		cout << left
			<< setw(10) << "Mã BN"
			<< setw(20) << "Tên"
			<< setw(15) << "Ngày Sinh"
			<< setw(15) << "Phòng"
			<< setw(15) << "Ngày Khám"
			<< endl;

		cout << "--------------------------------------------------------------------------------\n";

		for (auto& b : ds) {

			cout << left
				<< setw(10) << b.ma
				<< setw(20) << b.ten
				<< setw(15) << b.sinh
				<< setw(15) << b.phong
				<< setw(15) << b.ngay
				<< endl;
		}

		cout << "--------------------------------------------------------------------------------\n";
		UI::pause();

		UI::pause();
	}

	static void exportExcelBenhNhan() {

		if (!SystemMethod::fileExist("benhnhan.xml")) {
			cout << "Không có dữ liệu\n";
			UI::pause();
			return;
		}

		ifstream f("benhnhan.xml");
		ofstream o("benhnhan.csv");

		string line;
		BenhNhan bn;

		/* header excel */
		o << "MaBN,Ten,NgaySinh,GioiTinh,DienThoai,DiaChi,DoiTuong,Phong,NgayKham\n";

		while (getline(f, line)) {

			if (line.find("<Ma>") != string::npos)
				bn.ma = line.substr(4, line.find("</") - 4);

			if (line.find("<Ten>") != string::npos)
				bn.ten = line.substr(5, line.find("</") - 5);

			if (line.find("<Sinh>") != string::npos)
				bn.sinh = line.substr(6, line.find("</") - 6);

			if (line.find("<GioiTinh>") != string::npos)
				bn.gioiTinh = line.substr(10, line.find("</") - 10);

			if (line.find("<DienThoai>") != string::npos)
				bn.dienThoai = line.substr(11, line.find("</") - 11);

			if (line.find("<DiaChi>") != string::npos)
				bn.diaChi = line.substr(8, line.find("</") - 8);

			if (line.find("<DoiTuong>") != string::npos)
				bn.doiTuong = line.substr(10, line.find("</") - 10);

			if (line.find("<Phong>") != string::npos)
				bn.phong = line.substr(7, line.find("</") - 7);

			if (line.find("<Ngay>") != string::npos) {

				bn.ngay = line.substr(6, line.find("</") - 6);

				o << bn.ma << ","
					<< bn.ten << ","
					<< bn.sinh << ","
					<< bn.gioiTinh << ","
					<< bn.dienThoai << ","
					<< bn.diaChi << ","
					<< bn.doiTuong << ","
					<< bn.phong << ","
					<< bn.ngay << "\n";
			}
		}

		f.close();
		o.close();

		cout << "\nXuất Excel thành công: benhnhan.csv\n";

		char ch;

		cout << "Bạn có muốn mở file không? (Y/N): ";
		cin >> ch;

		if (ch == 'Y' || ch == 'y')
			system("start benhnhan.csv");

		UI::pause();
	}
};