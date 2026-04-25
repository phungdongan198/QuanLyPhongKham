#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"
#include "SystemMethod.h"

class nhapThuoc {
private:
	string ma, ten, gia, lo, date, soLuong, ghiChu;

public:

#pragma region getter_&_setter

	string getMa() const { return ma; }
	void setMa(const string& val) { ma = val; }

	string getTen() const { return ten; }
	void setTen(const string& val) { ten = val; }

	string getGia() const { return gia; }
	void setGia(const string& val) { gia = val; }

	string getLo() const { return lo; }
	void setLo(const string& val) { lo = val; }

	string getDate() const { return date; }
	void setDate(const string& val) { date = val; }

	string getSoLuong() const { return soLuong; }
	void setSoLuong(const string& val) { soLuong = val; }

	string getGhiChu() const { return ghiChu; }
	void setGhiChu(const string& val) { ghiChu = val; }

#pragma endregion


	void nhap() {

		cin.ignore();

		ma = Helper::nhapMaKhongTrung(
			"Nhập mã thuốc: ",
			"nhapthuoc.xml",
			"Thuoc",
			"Ma"
		);

		cout << "Tên thuốc: ";
		getline(cin, ten);

		//cout << "Đơn giá: ";
		while (true)
		{
			int donGia = nhapSo<int>("Nhập đơn giá: ");
			if (donGia > 100)
			{
				gia = Helper::formatTien(std::to_string(donGia));
				break;
			}
			else
			{
				cout << "Giá tiền phải từ 100 trở lên! Vui lòng nhập lại.\n";
			}
		}

		cout << "Lô: ";
		getline(cin, lo);

		//Date
		date = NhapVaKiemTraDateThuocNhap();

		//So Luong
		soLuong = std::to_string(nhapSo<int>("Nhập số lượng: "));


		cout << "Ghi chú: ";
		getline(cin, ghiChu);
	}

	void save() {
		bool fileMoi = !SystemMethod::fileExist("nhapthuoc.xml");

		ofstream f("nhapthuoc.xml", ios::app);
		if (fileMoi) {
			f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		}

		f << "<Thuoc>\n";
		f << "<Ma>" << ma << "</Ma>\n";
		f << "<Ten>" << ten << "</Ten>\n";
		f << "<Gia>" << Helper::formatTien(gia) << "</Gia>\n";
		f << "<Lo>" << lo << "</Lo>\n";
		f << "<Date>" << date << "</Date>\n";
		f << "<SoLuong>" << soLuong << "</SoLuong>\n";
		f << "<GhiChu>" << ghiChu << "</GhiChu>\n";
		f << "</Thuoc>\n\n";

		f.close();
	}

	//=========================== CÁC HÀM KIỂM TRA CHO NHẬP THUỐC ===========================

	string NhapVaKiemTraDateThuocNhap() {
		int dd, mm, yyyy;
		char slash1, slash2;

		// 1. Lấy thời gian hiện tại từ hệ thống
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t); // Sử dụng localtime_s cho an toàn trong C++

		int curr_dd = now.tm_mday;
		int curr_mm = now.tm_mon + 1;      // tm_mon tính từ 0-11
		int curr_yyyy = now.tm_year + 1900; // tm_year tính từ 1900

		while (true) {
			cout << "Nhập Date(Định dạng dd/mm/yyyy - Phải sau ngày "
				<< curr_dd << "/" << curr_mm << "/" << curr_yyyy << "): ";

			// 2. Đọc dữ liệu
			if (cin >> dd >> slash1 >> mm >> slash2 >> yyyy && slash1 == '/' && slash2 == '/') {

				// 3. Kiểm tra tính hợp lệ cơ bản của ngày tháng
				bool hopLe = (mm >= 1 && mm <= 12 && dd >= 1 && dd <= 31 && yyyy >= 1900);

				if (hopLe) {
					// 4. KIỂM TRA PHẢI LỚN HƠN NGÀY HIỆN TẠI
					bool sauHienTai = false;
					if (yyyy > curr_yyyy) {
						sauHienTai = true;
					}
					else if (yyyy == curr_yyyy) {
						if (mm > curr_mm) {
							sauHienTai = true;
						}
						else if (mm == curr_mm) {
							if (dd > curr_dd) {
								sauHienTai = true;
							}
						}
					}

					if (sauHienTai) {
						char buffer[11];
						sprintf_s(buffer, "%02d/%02d/%04d", dd, mm, yyyy);
						return string(buffer);
					}
				}
			}

			// Nếu sai định dạng hoặc không sau ngày hiện tại
			cout << "Ngày nhập vào phải LỚN HƠN ngày hiện tại! Vui lòng nhập lại.\n";
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
	}

	string nhapGiaTien(string thongBao) {
		string input;
		while (true) {
			// 1. Kiểm tra định dạng số
			if (SystemMethod::NhapVaKiemTraDuLieuSo<string>(input, thongBao)) {
				// 2. Chuyển sang số để kiểm tra giá trị >= 1000
				long long gia = stoll(input);

				if (gia >= 1000) {
					return input; // Trả về chuỗi để bạn lưu vào XML
				}
				else {
					cout << "Lỗi: Giá tiền phải từ 1000 trở lên!\n";
				}
			}
			else {
				cout << "Lỗi: Vui lòng chỉ nhập ký tự số (không chứa chữ cái hay ký tự đặc biệt).\n";
			}

			// Xóa bộ đệm nếu có lỗi
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
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
				cout << "Lỗi: Vui lòng nhập số.\n";
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
		}
	}

};