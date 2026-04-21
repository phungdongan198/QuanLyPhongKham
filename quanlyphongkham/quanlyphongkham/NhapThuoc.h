#pragma once
#include "LiblaryHeader.h"
#include "Helper.h"
#include "SystemMethod.h"

class nhapThuoc {

public:

	string ma, ten, gia, lo, date, soLuong, ghiChu;


	void nhap() {

		cin.ignore();
		
		ma = Helper::nhapMaKhongTrung(
			"Nhap ma thuoc: ",
			"nhapthuoc.xml",
			"Thuoc",
			"Ma"
		);

		cout << "Ten thuoc: ";
		getline(cin, ten);

		//cout << "Don gia: ";
		while (true)
		{
			int donGia = nhapSo<int>("Nhap Don Gia: ");
			if (donGia > 100)
			{
				gia = std::to_string(donGia);
				break;
			}
			else
			{
				cout << "Gia tien phai tu 100 tro len! Vui long nhap lai.\n";
			}
		}

		cout << "Lo: ";
		getline(cin, lo);
		
		//Date
        date = NhapVaKiemTraDateThuocNhap();

		//So Luong
		soLuong = std::to_string(nhapSo<int>("Nhap so luong: "));
		

		cout << "Ghi chu: ";
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
		f << "<Gia>" << gia << "</Gia>\n";
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
			cout << "Nhap Date(Dinh dang dd/mm/yyyy - Phai sau ngay "
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
			cout << "Ngay nhap vao phai LON HON ngay hien tai! Vui long nhap lai.\n";
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
					cout << "Loi: Gia tien phai tu 1000 tro len!\n";
				}
			}
			else {
				cout << "Loi: Vui long chi nhap ky tu so (khong chua chu cai hay ky tu dac biet).\n";
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
				cout << "Loi vui long nhap so.\n";
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
		}
	}

};