#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
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

			cout << "Chọn: ";
			cin >> chon;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại!\n";
				continue;
			}

			cin.ignore(1000, '\n');

			if (chon >= 1 && chon <= (int)dsLuaChon.size()) {
				return dsLuaChon[chon - 1];
			}

			cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại!\n";
		}
	}

	static string chonTuFile(const string& tieuDe, const string& tenFile, const string& tenKhoi, const string& tenTheCanLay) {
		vector<string> ds = docDanhSachTuFile(tenFile, tenKhoi, tenTheCanLay);

		if (ds.empty()) {
			string nhapTay;
			cout << "Chưa có dữ liệu từ hệ thống.\n";
			cout << "Nhập tay " << tieuDe << ": ";
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

			cout << "Chưa có dữ liệu từ hệ thống.\n";
			cout << "Nhập tay " << tieuDe << ": ";
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
				cout << "Mã không được để trống. Vui lòng nhập lại!\n";
				continue;
			}

			if (coKhoangTrang(ma)) {
				cout << "Mã không được chứa khoảng trắng. Vui lòng nhập lại!\n";
				continue;
			}

			if (kiemTraTonTaiXML(tenFile, tenKhoi, tenTheMa, ma)) {
				cout << "Mã đã tồn tại. Vui lòng nhập mã khác!\n";
				continue;
			}

			break;
		}
		return ma;
	}

	static string chonTuFile(
		const string& tieuDe,
		const string& tenFile,
		const string& tenKhoi,
		const string& tenTheCanLay,
		const vector<string>& dsTheLayKem,
		vector<string>& dsGiaTriLayKem
	)
	{
		ifstream file(tenFile);

		vector<string> dsHienThi;
		vector<vector<string>> dsKemTheo;

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

					if (giaTriHienThi != "") {
						dsHienThi.push_back(giaTriHienThi);

						vector<string> tam;

						for (string tag : dsTheLayKem) {
							tam.push_back(layGiaTriTag(block, tag));
						}

						dsKemTheo.push_back(tam);
					}

					dangDoc = false;
					block = "";
				}
			}
		}

		file.close();

		if (dsHienThi.empty()) {
			string nhapTay;

			cout << "Chưa có dữ liệu từ hệ thống.\n";
			cout << "Nhập tay " << tieuDe << ": ";
			getline(cin, nhapTay);

			dsGiaTriLayKem.clear();
			return nhapTay;
		}

		string daChon = chonTuDanhSach(tieuDe, dsHienThi);

		for (int i = 0; i < dsHienThi.size(); i++) {
			if (dsHienThi[i] == daChon) {
				dsGiaTriLayKem = dsKemTheo[i];
				break;
			}
		}
		return daChon;
	}

	// xử lý in côt cho đẹp hơn
	static int doDaiUTF8(const string& s) {
		int count = 0;

		for (unsigned char c : s) {
			if ((c & 0xC0) != 0x80) {
				count++;
			}
		}

		return count;
	}

	static void inCot(ostream& out, const string& s, int width) {
		out << s;

		int space = width - doDaiUTF8(s);
		if (space > 0) {
			out << string(space, ' ');
		}
	}

	static string formatTien(string s) {
		// Xóa dấu chấm cũ nếu có
		string so = "";
		for (char c : s) {
			if (isdigit((unsigned char)c)) {
				so += c;
			}
		}

		if (so.empty()) return "0";

		string kq = "";
		int dem = 0;

		for (int i = so.length() - 1; i >= 0; i--) {
			kq = so[i] + kq;
			dem++;

			if (dem % 3 == 0 && i != 0) {
				kq = "." + kq;
			}
		}

		return kq;
	}

	static string boDauChamTien(string s) {
		string kq = "";

		for (char c : s) {
			if (isdigit((unsigned char)c)) {
				kq += c;
			}
		}

		return kq;
	}

	static string docSo(int n) {
		string chuSo[] = {
			"không", "một", "hai", "ba", "bốn",
			"năm", "sáu", "bảy", "tám", "chín"
		};

		int tram = n / 100;
		int chuc = (n % 100) / 10;
		int donvi = n % 10;

		string kq = "";

		if (tram > 0) {
			kq += chuSo[tram] + string(" trăm");

			if (chuc == 0 && donvi > 0) {
				kq += " lẻ";
			}
		}

		if (chuc > 1) {
			kq += " " + chuSo[chuc] + string(" mươi");

			if (donvi == 1) {
				kq += " mốt";
			}
			else if (donvi == 5) {
				kq += " lăm";
			}
			else if (donvi > 0) {
				kq += " " + chuSo[donvi];
			}
		}
		else if (chuc == 1) {
			kq += " mười";

			if (donvi == 5) {
				kq += " lăm";
			}
			else if (donvi > 0) {
				kq += " " + chuSo[donvi];
			}
		}
		else if (donvi > 0) {
			kq += " " + chuSo[donvi];
		}

		return kq;
	}

	static string docTienBangChu(long long soTien) {
		if (soTien == 0) return "Không đồng";

		string donVi[] = { "", " nghìn", " triệu", " tỷ" };

		vector<int> nhom;
		while (soTien > 0) {
			nhom.push_back(soTien % 1000);
			soTien /= 1000;
		}

		string kq = "";

		for (int i = nhom.size() - 1; i >= 0; i--) {
			if (nhom[i] != 0) {
				string phan = docSo(nhom[i]);

				if (!kq.empty()) {
					kq += " ";
				}

				kq += phan + donVi[i];
			}
		}

		// Viết hoa chữ cái đầu
		if (!kq.empty()) {
			kq[0] = toupper((unsigned char)kq[0]);
		}

		kq += " đồng";

		return kq;
	}

	static string csvText(const string& s) {
		string kq = s;

		// Nếu có dấu " thì nhân đôi dấu " để CSV không lỗi
		size_t pos = 0;
		while ((pos = kq.find("\"", pos)) != string::npos) {
			kq.replace(pos, 1, "\"\"");
			pos += 2;
		}

		return "\"" + kq + "\"";
	}

	// Ép Excel hiểu là text, không tự đổi số / ngày / tiền
	static string csvTextExcel(const string& s) {
		string kq = s;

		size_t pos = 0;
		while ((pos = kq.find("\"", pos)) != string::npos) {
			kq.replace(pos, 1, "\"\"");
			pos += 2;
		}

		return "=\"" + kq + "\"";
	}

	static time_t chuyenNgaySangTime(string ngay) {
		// định dạng dd/mm/yyyy
		tm t = {};
		t.tm_mday = stoi(ngay.substr(0, 2));
		t.tm_mon = stoi(ngay.substr(3, 2)) - 1;
		t.tm_year = stoi(ngay.substr(6, 4)) - 1900;
		t.tm_hour = 0;
		t.tm_min = 0;
		t.tm_sec = 0;

		return mktime(&t);
	}

	static long long soNgayConLai(string ngayHetHan) {
		time_t hienTai = time(0);
		time_t hetHan = chuyenNgaySangTime(ngayHetHan);

		double giay = difftime(hetHan, hienTai);
		return (long long)(giay / (60 * 60 * 24));
	}
};