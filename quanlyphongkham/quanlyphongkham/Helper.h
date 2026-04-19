#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Helper {
public:
	static string layGiaTriThe(const string& khoi, const string& tenThe) {
		string theMo = "<" + tenThe + ">";
		string theDong = "</" + tenThe + ">";

		size_t posMo = khoi.find(theMo);
		size_t posDong = khoi.find(theDong);

		if (posMo == string::npos || posDong == string::npos || posDong < posMo)
			return "";

		posMo += theMo.length();
		return khoi.substr(posMo, posDong - posMo);
	}

	static vector<string> docDanhSachTuFile(const string& tenFile, const string& tenKhoi, const string& tenTheCanLay) {
		vector<string> ds;
		ifstream file(tenFile);
		if (!file) return ds;

		string noiDung, dong;
		while (getline(file, dong)) {
			noiDung += dong + "\n";
		}
		file.close();

		string theMoKhoi = "<" + tenKhoi + ">";
		string theDongKhoi = "</" + tenKhoi + ">";

		size_t start = 0;
		while (true) {
			size_t posMo = noiDung.find(theMoKhoi, start);
			if (posMo == string::npos) break;

			size_t posDong = noiDung.find(theDongKhoi, posMo);
			if (posDong == string::npos) break;

			posDong += theDongKhoi.length();

			string khoi = noiDung.substr(posMo, posDong - posMo);
			string giaTri = layGiaTriThe(khoi, tenTheCanLay);

			if (!giaTri.empty()) {
				ds.push_back(giaTri);
			}

			start = posDong;
		}

		return ds;
	}

	static string chonTuDanhSach(const string& tieuDe, const vector<string>& dsLuaChon) {
		if (dsLuaChon.empty()) return "";

		int chon;
		while (true) {
			cout << tieuDe << ":\n";
			for (int i = 0; i < (int)dsLuaChon.size(); i++) {
				cout << i + 1 << ". " << dsLuaChon[i] << endl;
			}

			cout << "Chon: ";
			cin >> chon;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Lua chon khong hop le. Vui long nhap lai!\n";
				continue;
			}

			cin.ignore(1000, '\n');

			if (chon >= 1 && chon <= (int)dsLuaChon.size()) {
				return dsLuaChon[chon - 1];
			}

			cout << "Lua chon khong hop le. Vui long nhap lai!\n";
		}
	}

	static string chonTuFile(const string& tieuDe, const string& tenFile, const string& tenKhoi, const string& tenTheCanLay) {
		vector<string> ds = docDanhSachTuFile(tenFile, tenKhoi, tenTheCanLay);

		if (ds.empty()) {
			string nhapTay;
			cout << "Chua co du lieu tu he thong.\n";
			cout << "Nhap tay " << tieuDe << ": ";
			getline(cin, nhapTay);
			return nhapTay;
		}

		return chonTuDanhSach(tieuDe, ds);
	}

	static string layGiaTriTag(const string& block, const string& tag) {
		string mo = "<" + tag + ">";
		string dong = "</" + tag + ">";

		size_t start = block.find(mo);
		size_t end = block.find(dong);

		if (start == string::npos || end == string::npos) {
			return "";
		}

		start += mo.length();

		return block.substr(start, end - start);
	}

	static string chonTuFile(
		const string& tieuDe,
		const string& tenFile,
		const string& tenKhoi,
		const string& tenTheCanLay,
		const string& tenTheLayKem,
		string& giaTriLayKem
	) {
		ifstream file(tenFile);

		vector<string> dsHienThi;
		vector<string> dsLayKem;

		string line, block;
		bool dangDoc = false;

		while (getline(file, line)) {
			if (line.find("<" + tenKhoi + ">") != string::npos) {
				dangDoc = true;
				block = line + "\n";
			}
			else if (dangDoc) {
				block += line + "\n";

				if (line.find("</" + tenKhoi + ">") != string::npos) {
					string giaTriHienThi = layGiaTriTag(block, tenTheCanLay);
					string giaTriKem = layGiaTriTag(block, tenTheLayKem);

					if (giaTriHienThi != "") {
						dsHienThi.push_back(giaTriHienThi);
						dsLayKem.push_back(giaTriKem);
					}

					dangDoc = false;
					block = "";
				}
			}
		}

		file.close();

		if (dsHienThi.empty()) {
			string nhapTay;

			cout << "Chua co du lieu tu he thong.\n";
			cout << "Nhap tay " << tieuDe << ": ";
			getline(cin, nhapTay);

			giaTriLayKem = "";
			return nhapTay;
		}

		string daChon = chonTuDanhSach(tieuDe, dsHienThi);

		for (int i = 0; i < dsHienThi.size(); i++) {
			if (dsHienThi[i] == daChon) {
				giaTriLayKem = dsLayKem[i];
				break;
			}
		}

		return daChon;
	}

	static bool kiemTraTonTaiXML(
		const string& tenFile,
		const string& tenKhoi,
		const string& tenTheCanKiemTra,
		const string& giaTriCanKiemTra
	) {
		ifstream file(tenFile);

		if (!file.is_open()) {
			return false;
		}

		string line, block;
		bool dangDocKhoi = false;

		while (getline(file, line)) {
			if (line.find("<" + tenKhoi + ">") != string::npos) {
				dangDocKhoi = true;
				block = line + "\n";
			}
			else if (dangDocKhoi) {
				block += line + "\n";

				if (line.find("</" + tenKhoi + ">") != string::npos) {
					string giaTri = layGiaTriTag(block, tenTheCanKiemTra);

					if (giaTri == giaTriCanKiemTra) {
						file.close();
						return true;
					}

					dangDocKhoi = false;
					block = "";
				}
			}
		}

		file.close();
		return false;
	}

	static bool coKhoangTrang(const string& s) {
		for (char c : s) {
			if (isspace((unsigned char)c)) {
				return true;
			}
		}
		return false;
	}

	static string nhapMaKhongTrung(
		const string& thongBao,
		const string& tenFile,
		const string& tenKhoi,
		const string& tenTheMa
	) {
		string ma;

		while (true) {
			cout << thongBao;
			getline(cin, ma);

			if (ma.empty()) {
				cout << "Ma khong duoc de trong. Vui long nhap lai!\n";
				continue;
			}

			if (coKhoangTrang(ma)) {
				cout << "Ma khong duoc chua khoang trang. Vui long nhap lai!\n";
				continue;
			}

			if (kiemTraTonTaiXML(tenFile, tenKhoi, tenTheMa, ma)) {
				cout << "Ma da ton tai. Vui long nhap ma khac!\n";
				continue;
			}

			break;
		}

		return ma;
	}
};