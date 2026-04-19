#pragma once
#include "LiblaryHeader.h"
#include "UI.h"
#include "NhapThuoc.h"

class banThuoc;

class SystemMethod {
public:
	// ngày thang shiện tại
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

	
};
