#pragma once
#include "LiblaryHeader.h"
#include "UI.h"
//#include "NhapThuoc.h"

class banThuoc;

class SystemMethod {
public:
	// ngày thang hiện tại
	static string today() {

		time_t now = time(0);   // tạo biến now

		tm t;
		localtime_s(&t, &now);

		char buf[20];

		sprintf_s(buf, "%02d/%02d/%04d",
			t.tm_mday,
			t.tm_mon + 1,
			t.tm_year + 1900);

		return string(buf);
	}

	// XML HELPER 
	static bool fileExist(string name) {

		ifstream f(name);
		return f.good();
	}

	static int kiemTraKyTu() {

		int x;

		while (true) {

			if (cin >> x)
				return x;

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Nhap sai! Vui long nhap so: ";
		}
	}

	template <typename T>
	static bool NhapVaKiemTraDuLieuSo(T& giaTri, string thongBao) {
		while (true) {
			cout << thongBao;
			if (cin >> giaTri) {
				// Kiểm tra xem sau số đó có còn ký tự thừa nào không (tránh trường hợp nhập "12abc")
				if (cin.peek() == '\n' || cin.peek() == EOF) {
					return true;
				}
			}

			// Nếu vào đến đây nghĩa là nhập sai định dạng
			cout << "Loi: Du lieu nhap vao khong hop le. Vui long nhap lai!\n";
			cin.clear(); // Xóa trạng thái lỗi
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
	}

	template <typename T>
	static string KiemTraDuLieuSo(string thongBao) {
		T giaTri;
		while (true) {
			cout << thongBao;
			if (cin >> giaTri) {
				// Kiểm tra xem sau số đó có còn ký tự thừa nào không (tránh trường hợp nhập "12abc")
				if (cin.peek() == '\n' || cin.peek() == EOF) {
					return (string)giaTri;
				}
			}

			// Nếu vào đến đây nghĩa là nhập sai định dạng
			cout << "Loi: Du lieu nhap vao khong hop le. Vui long nhap lai!\n";
			cin.clear(); // Xóa trạng thái lỗi
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
	}

	//Tạm không dùng
	template <typename T>
	bool laGiaTienHopLe(T gia,string thongBao) {
		// Giá tiền phải lớn hơn 0 và chia hết cho 1000 (ít nhất 3 số 0)
		if (gia <= 0) return false;

		// Ép kiểu về long long để dùng toán tử chia lấy dư %)
		if ((long long)gia % 1000 != 0) return false;

		return true;
	}

	template <typename T>
	static T nhapSo(string thongBao) {
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
