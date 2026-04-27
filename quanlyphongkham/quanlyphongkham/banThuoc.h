#pragma once
#include "SystemMethod.h"
#include "LiblaryHeader.h"
#include "banThuoc.h"
#include <map>
#include "Helper.h"

class banThuoc {

private:
	string ma, ten, nguoimua, diachi, dienthoai, benh, soluong, dongia, thanhtien, lo, date, ghichu, ngay;
public:
	vector<string> thongTinThuoc;

	#pragma region các getter và setter
	string getMa() const { return ma; }
	void setMa(const string& val) { ma = val; }

	string getTen() const { return ten; }
	void setTen(const string& val) { ten = val; }

	string getNguoiMua() const { return nguoimua; }
	void setNguoiMua(const string& val) { nguoimua = val; }

	string getDiaChi() const { return diachi; }
	void setDiaChi(const string& val) { diachi = val; }

	string getDienThoai() const { return dienthoai; }
	void setDienThoai(const string& val) { dienthoai = val; }

	string getBenh() const { return benh; }
	void setBenh(const string& val) { benh = val; }

	string getSoLuong() const { return soluong; }
	void setSoLuong(const string& val) { soluong = val; }

	string getDonGia() const { return dongia; }
	void setDonGia(const string& val) { dongia = val; }

	string getThanhTien() const { return thanhtien; }
	void setThanhTien(const string& val) { thanhtien = val; }

	string getLo() const { return lo; }
	void setLo(const string& val) { lo = val; }

	string getDate() const { return date; }
	void setDate(const string& val) { date = val; }

	string getGhiChu() const { return ghichu; }
	void setGhiChu(const string& val) { ghichu = val; }

	string getNgay() const { return ngay; }
	void setNgay(const string& val) { ngay = val; }
	#pragma endregion

	#pragma region các hàm xử lý menu
	long long laySoLuongConLaiTheoMa(string maCanTim) {
		long long tongNhap = 0;
		long long tongXuat = 0;

		// ================= ĐỌC FILE NHẬP THUỐC =================
		if (SystemMethod::fileExist("nhapthuoc.xml")) {

			ifstream f("nhapthuoc.xml");

			string line;
			string ma = "";
			string soluong = "";

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					ma = line.substr(4, line.find("</") - 4);

				if (line.find("<SoLuong>") != string::npos) {
					soluong = line.substr(9, line.find("</") - 9);

					if (ma == maCanTim) {
						tongNhap += stoll(Helper::boDauChamTien(soluong));
					}
				}
			}

			f.close();
		}

		// ================= ĐỌC FILE XUẤT / BÁN THUỐC =================
		if (SystemMethod::fileExist("banthuoc.xml")) {

			ifstream f("banthuoc.xml");

			string line;
			string ma = "";
			string soluong = "";

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					ma = line.substr(4, line.find("</") - 4);

				if (line.find("<SoLuong>") != string::npos) {
					soluong = line.substr(9, line.find("</") - 9);

					if (ma == maCanTim) {
						tongXuat += stoll(Helper::boDauChamTien(soluong));
					}
				}
			}

			f.close();
		}

		return tongNhap - tongXuat;
	}

	bool ban() {

		cin.ignore();

		int loaiNguoiMua;
		while (true) {
			cout << "Loại người mua:\n";
			cout << "1. Bệnh nhân mua lẻ\n";
			cout << "2. Bệnh nhân khám từ phòng khám\n";
			cout << "Chọn: ";
			cin >> loaiNguoiMua;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại!\n";
				continue;
			}

			cin.ignore(1000, '\n');

			if (loaiNguoiMua == 1) {
				cout << "Người mua: ";
				getline(cin, nguoimua);
				break;
			}
			else if (loaiNguoiMua == 2) {
				nguoimua = Helper::chonTuFile("Chọn bệnh nhân", "khambenh.xml", "KhamBenh", "Ten");
				break;
			}
			else {
				cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại!\n";
			}
		}

		ten = Helper::chonTuFile(
			"Tên thuốc",
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
		cout << "Mã thuốc: " << ma << endl;
		cout << "Lô:  " << lo << endl;
		cout << "Date: " << date << endl;

		long long soLuongConLai = laySoLuongConLaiTheoMa(ma);

		cout << "Số lượng còn lại: "
			<< Helper::formatTien(to_string(soLuongConLai)) << endl;

		if (soLuongConLai <= 0) {
			cout << "Thuốc này đã hết hàng, không thể bán!\n";
			UI::pause();
			return false;
		}

		while (true) {

			long long slXuat = nhapSo<long long>("Nhập số lượng xuất: ");

			if (slXuat <= 0) {
				cout << "Số lượng xuất phải lớn hơn 0. Vui lòng nhập lại!\n";
				continue;
			}

			if (slXuat > soLuongConLai) {
				cout << "Số lượng xuất vượt quá tồn kho!\n";
				cout << "Hiện chỉ còn: "
					<< Helper::formatTien(to_string(soLuongConLai)) << endl;
				continue;
			}

			soluong = to_string(slXuat);
			break;
		}

		cout << "Đơn giá: " << dongia << endl;

		long long sl = stoll(soluong);
		long long dg = stoll(Helper::boDauChamTien(dongia));

		thanhtien = Helper::formatTien(to_string(sl * dg));

		cout << "Thành tiền: " << thanhtien << endl;

		cout << "Địa chỉ: ";
		getline(cin, diachi);

		while (true)
		{
			cout << "Điện thoại: ";
			getline(cin, dienthoai);
			if (KiemTraSoDienThoai(dienthoai))
				break;
			else
				cout << "Số điện thoại không hợp lệ! Vui lòng nhập lại.\n";
		}

		cout << "Tên bệnh: ";
		getline(cin, benh);


		cout << "Ghi chú: ";
		getline(cin, ghichu);

		ngay = SystemMethod::today();
		return true;
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
		f << "<DonGia>" << Helper::formatTien(dongia) << "</DonGia>\n";
		f << "<ThanhTien>" << Helper::formatTien(thanhtien) << "</ThanhTien>\n";

		f << "<Lo>" << lo << "</Lo>\n";
		f << "<Date>" << date << "</Date>\n";
		f << "<GhiChu>" << ghichu << "</GhiChu>\n";
		f << "<Ngay>" << ngay << "</Ngay>\n";

		f << "</BanThuoc>\n\n";

		f.close();
	}

	static void showTonKho() {

		UI::clear();
		UI::center("TỒN KHO THUỐC", 10);

		map<string, long long> soLuongDaBan;

		if (SystemMethod::fileExist("banthuoc.xml")) {

			ifstream fb("banthuoc.xml");

			string line;
			string ma, soluong;

			while (getline(fb, line)) {

				if (line.find("<Ma>") != string::npos)
					ma = line.substr(4, line.find("</") - 4);

				if (line.find("<SoLuong>") != string::npos) {
					soluong = line.substr(9, line.find("</") - 9);

					long long sl = stoll(Helper::boDauChamTien(soluong));
					soLuongDaBan[ma] += sl;
				}
			}

			fb.close();
		}

		/* ================= DANH SACH THUOC DA NHAP ================= */

		cout << "\n===== DANH SÁCH THUỐC ĐÃ NHẬP =====\n";

		if (!SystemMethod::fileExist("nhapthuoc.xml")) {

			cout << "Không có dữ liệu thuốc\n";
		}
		else {

			ifstream f("nhapthuoc.xml");

			string line;
			nhapThuoc t;

			cout << string(120, '-') << endl;

			Helper::inCot(cout, "Mã thuốc", 10);
			Helper::inCot(cout, "Tên thuốc", 35);
			Helper::inCot(cout, "Đơn giá", 15);
			Helper::inCot(cout, "SL nhập", 10);
			Helper::inCot(cout, "Đã bán", 10);
			Helper::inCot(cout, "Còn lại", 10);
			Helper::inCot(cout, "Lô", 15);
			Helper::inCot(cout, "Date", 15);
			Helper::inCot(cout, "Ghi chú", 15);
			cout << endl;
			cout << endl;

			cout << string(120, '-') << endl;

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					t.setMa(line.substr(4, line.find("</") - 4));

				if (line.find("<Ten>") != string::npos)
					t.setTen(line.substr(5, line.find("</") - 5));

				if (line.find("<Gia>") != string::npos)
					t.setGia(line.substr(5, line.find("</") - 5));

				if (line.find("<Lo>") != string::npos)
					t.setLo(line.substr(4, line.find("</") - 4));

				if (line.find("<Date>") != string::npos)
					t.setDate(line.substr(6, line.find("</") - 6));

				if (line.find("<SoLuong>") != string::npos)
					t.setSoLuong(line.substr(9, line.find("</") - 9));

				if (line.find("<GhiChu>") != string::npos) {

					t.setGhiChu(line.substr(8, line.find("</") - 8));

					long long slNhap = stoll(Helper::boDauChamTien(t.getSoLuong()));
					long long slBan = soLuongDaBan[t.getMa()];
					long long slConLai = slNhap - slBan;

					Helper::inCot(cout, t.getMa(), 10);
					Helper::inCot(cout, t.getTen(), 35);
					Helper::inCot(cout, t.getGia(), 15);
					Helper::inCot(cout, Helper::formatTien(to_string(slNhap)), 10);
					Helper::inCot(cout, Helper::formatTien(to_string(slBan)), 10);
					Helper::inCot(cout, Helper::formatTien(to_string(slConLai)), 10);
					Helper::inCot(cout, t.getLo(), 15);
					Helper::inCot(cout, t.getDate(), 15);
					Helper::inCot(cout, t.getGhiChu(), 15);
					cout << endl;
				}
			}

			f.close();

			cout << string(120, '-') << endl;
		}

		/* ================= DANH SACH THUOC DA XUAT ================= */

		cout << "\n===== DANH SÁCH THUỐC ĐÃ XUẤT =====\n";

		if (!SystemMethod::fileExist("banthuoc.xml")) {

			cout << "Không có dữ liệu bán thuốc\n";
		}
		else {

			ifstream f("banthuoc.xml");

			string line;
			banThuoc b;

			cout << string(120, '-') << endl;
			Helper::inCot(cout, "Mã thuốc", 10);
			Helper::inCot(cout, "Tên thuốc", 30);
			Helper::inCot(cout, "Người mua", 20);
			Helper::inCot(cout, "Số lượng", 15);
			Helper::inCot(cout, "Đơn giá", 15);
			Helper::inCot(cout, "Thành tiền", 15);
			cout << endl;

			cout << string(120, '-') << endl;

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

					Helper::inCot(cout, b.ma, 10);
					Helper::inCot(cout, b.ten, 30);
					Helper::inCot(cout, b.nguoimua, 20);
					Helper::inCot(cout, b.soluong, 15);
					Helper::inCot(cout, b.dongia, 15);
					Helper::inCot(cout, b.thanhtien, 15);
					cout << endl;
				}
			}

			f.close();

			cout << string(120, '-') << endl;
		}

		UI::pause();
	}

	static void seachThuoc() {

		if (!SystemMethod::fileExist("nhapthuoc.xml")) {
			cout << "Không có dữ liệu thuốc\n";
			UI::pause();
			return;
		}

		int chon;

		cout << "\n===== TÌM THUỐC =====\n";
		cout << "1 Tìm theo mã (tuyệt đối)\n";
		cout << "2 Tìm theo tên (tương đối)\n";
		UI::printColor("3 Quay lại\n", 12);

		cout << "Chọn: ";
		cin >> chon;

		if (chon == 3)
			return;

		cin.ignore();

		string key;

		if (chon == 1)
			cout << "Nhập mã thuốc: ";
		else
			cout << "Nhập tên thuốc: ";

		getline(cin, key);
		string lowerKey = SystemMethod::toLower(key);
		ifstream f("nhapthuoc.xml");

		string line;
		nhapThuoc t;

		vector<nhapThuoc> ds;

		while (getline(f, line))
		{
			if (line.find("<Ma>") != string::npos)
				t.setMa(line.substr(4, line.find("</") - 4));

			if (line.find("<Ten>") != string::npos)
				t.setTen(line.substr(5, line.find("</") - 5));

			if (line.find("<Gia>") != string::npos)
				t.setGia(line.substr(5, line.find("</") - 5));

			if (line.find("<Lo>") != string::npos)
				t.setLo(line.substr(4, line.find("</") - 4));

			if (line.find("<Date>") != string::npos)
				t.setDate(line.substr(6, line.find("</") - 6));

			if (line.find("<SoLuong>") != string::npos)
				t.setSoLuong(line.substr(9, line.find("</") - 9));

			if (line.find("<GhiChu>") != string::npos)
			{
				t.setGhiChu(line.substr(8, line.find("</") - 8));

				bool match = false;

				if (chon == 1 && SystemMethod::toLower(t.getMa()) == key)
					match = true;

				if (chon == 2 && SystemMethod::toLower(t.getTen()).find(key) != string::npos)
					match = true;

				if (match)
					ds.push_back(t);
			}
		}

		f.close();

		if (ds.empty()) {

			cout << "\nKhông tìm thấy thuốc!\n";
			UI::pause();
			return;
		}

		cout << string(120, '-') << endl;


		Helper::inCot(cout, "Mã thuốc", 10);
		Helper::inCot(cout, "Tên thuốc", 40);
		Helper::inCot(cout, "Đơn giá", 15);
		Helper::inCot(cout, "Số lượng", 10);
		Helper::inCot(cout, "Lô", 15);
		Helper::inCot(cout, "Date", 15);
		Helper::inCot(cout, "Ghi chú", 15);
		cout << endl;


		cout << string(120, '-') << endl;

		for (auto& x : ds) {
			Helper::inCot(cout, x.getMa(), 10);
			Helper::inCot(cout, x.getTen(), 40);
			Helper::inCot(cout, x.getGia(), 15);
			Helper::inCot(cout, x.getSoLuong(), 10);
			Helper::inCot(cout, x.getLo(), 15);
			Helper::inCot(cout, x.getDate(), 15);
			Helper::inCot(cout, x.getGhiChu(), 15);
			cout << endl;

		}

		cout << string(120, '-') << endl;

		UI::pause();
	}

	static void exportExcelThuoc() {

		int chon;

		cout << "\n===== XUẤT EXCEL =====\n";
		cout << "1 Xuất danh sách thuốc nhập\n";
		cout << "2 Xuất danh sách thuốc bán\n";
		UI::printColor("3 Quay lại\n", 12);

		cout << "Chọn: ";
		cin >> chon;

		if (chon == 3)
			return;

		/* ================= XUAT THUOC NHAP ================= */

		if (chon == 1) {

			if (!SystemMethod::fileExist("nhapthuoc.xml")) {
				cout << "Không có dữ liệu thuốc\n";
				UI::pause();
				return;
			}

			ifstream f("nhapthuoc.xml");
			ofstream o("nhapthuoc.csv", ios::binary);
			o << "\xEF\xBB\xBF";

			string line;
			nhapThuoc t;

			o << "MaThuoc,TenThuoc,DonGia,SoLuong,Lo,Date,GhiChu\n";

			while (getline(f, line)) {

				if (line.find("<Ma>") != string::npos)
					t.setMa(line.substr(4, line.find("</") - 4));

				if (line.find("<Ten>") != string::npos)
					t.setTen(line.substr(5, line.find("</") - 5));

				if (line.find("<Gia>") != string::npos)
					t.setGia(line.substr(5, line.find("</") - 5));

				if (line.find("<Lo>") != string::npos)
					t.setLo(line.substr(4, line.find("</") - 4));

				if (line.find("<Date>") != string::npos)
					t.setDate(line.substr(6, line.find("</") - 6));

				if (line.find("<SoLuong>") != string::npos)
					t.setSoLuong(line.substr(9, line.find("</") - 9));

				if (line.find("<GhiChu>") != string::npos) {

					t.setGhiChu(line.substr(8, line.find("</") - 8));

					o << t.getMa() << ","
						<< t.getTen() << ","
						<< Helper::csvTextExcel(t.getGia()) << ","
						<< t.getSoLuong() << ","
						<< t.getLo() << ","
						<< t.getDate() << ","
						<< t.getGhiChu() << "\n";
				}
			}

			f.close();
			o.close();

			cout << "\nĐã xuất file nhapthuoc.csv\n";
			char ch;

			cout << "Bạn có muốn mở file không? (Y/N): ";
			cin >> ch;

			if (ch == 'Y' || ch == 'y')
				system("start nhapthuoc.csv");
		}

		/* ================= XUAT THUOC BAN ================= */

		else if (chon == 2) {

			if (!SystemMethod::fileExist("banthuoc.xml")) {
				cout << "Không có dữ liệu bán thuốc\n";
				UI::pause();
				return;
			}

			ifstream f("banthuoc.xml");
			ofstream o("banthuoc.csv", ios::binary);
			o << "\xEF\xBB\xBF";

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
						<< Helper::csvTextExcel(b.dongia) << ","
						<< Helper::csvTextExcel(b.thanhtien) << ","
						<< b.lo << ","
						<< b.date << ","
						<< b.ghichu << ","
						<< b.ngay << "\n";
				}
			}

			f.close();
			o.close();

			cout << "\nĐã xuất file banthuoc.csv\n";
			char ch;

			cout << "Bạn có muốn mở file không? (Y/N): ";
			cin >> ch;

			if (ch == 'Y' || ch == 'y')
				system("start banthuoc.csv");
		}

		UI::pause();
	}
	#pragma endregion

	#pragma region các hàm tiện ích

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

	bool KiemTraSoDienThoai(const string& sdt) {
		// Regex này kiểm tra:
		// ^0: Bắt đầu bằng số 0
		// [35789]: Chữ số thứ hai thường là 3, 5, 7, 8, 9 (các đầu số nhà mạng VN)
		// [0-9]{8}: 8 chữ số tiếp theo là bất kỳ số nào từ 0-9
		// $: Kết thúc chuỗi
		const regex pattern("^0[35789][0-9]{8}$");

		return regex_match(sdt, pattern);
	}

	#pragma endregion
};
