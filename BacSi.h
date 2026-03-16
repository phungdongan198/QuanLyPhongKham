#include "HeaderLiblary.h"
class BacSi
{
private:
	string maBs;
	string tenBs;
	string chuyenKhoa;
	string sdt;
	string diaChi;
	string email;
	string gioiTinh;
	string ngaySinh;

	//getter setter
public:
	void setMaBs(
		string maBs) {
		this->maBs = maBs;
	}

	string getMaBs() {
		return this->maBs;
	}

	void setTenBs(string tenBs) {
		this->tenBs = tenBs;
	}

	string setTenBs() {
		return this->tenBs;
	}

	void setChuyenKhoa(string chuyenKhoa) {
		this->chuyenKhoa = chuyenKhoa;
	}

	string getChuyenKhoa() {
		return this->chuyenKhoa;
	}

	void setSdt(string sdt) {
		this->sdt = sdt;
	}

	string getSdt() {
		return this->sdt;
	}	

	void setDiaChi(string diaChi) {
		this->diaChi = diaChi;
	}

	string getDiaChi() {
		return this->diaChi;
	}

	void setEmail(string email) {
		this->email = email;
	}

	string getEmail() {
		return this->email;
	}

	void setGioiTinh(string gioiTinh) {
		this->gioiTinh = gioiTinh;
	}

	string getGioiTinh() {
		return this->gioiTinh;
	}

	void setNgaySinh(string ngaySinh) {
		this->ngaySinh = ngaySinh;
	}

	string getNgaySinh() {
		return this->ngaySinh;
	}



	//constructor
public:
	BacSi(string maBs, string tenBs, string chuyenKhoa, string sdt, string diaChi, string email, string gioiTinh, string ngaySinh)
	{
		this->maBs = maBs;
		this->tenBs = tenBs;
		this->chuyenKhoa = chuyenKhoa;
		this->sdt = sdt;
		this->diaChi = diaChi;
		this->email = email;
		this->gioiTinh = gioiTinh;
		this->ngaySinh = ngaySinh;
	}

	BacSi() {
		this->maBs = "";
		this->tenBs = "";
		this->chuyenKhoa = "";
		this->sdt = "";
		this->diaChi = "";
		this->email = "";
		this->gioiTinh = "";
		this->ngaySinh = "";
	}

	//method
public:

	BacSi NhapVaLayThongTinBacSi()
	{
		cout << "Nhap ma bac si: ";
		getline(cin, maBs);
		cout << "Nhap ten bac si: ";
		getline(cin, tenBs);
		cout << "Nhap chuyen khoa: ";
		getline(cin, chuyenKhoa);
		cout << "Nhap so dien thoai: ";
		getline(cin, sdt);
		cout << "Nhap dia chi: ";
		getline(cin, diaChi);
		cout << "Nhap email: ";
		getline(cin, email);
		cout << "Nhap gioi tinh: ";
		getline(cin, gioiTinh);
		cout << "Nhap ngay sinh: ";
		getline(cin, ngaySinh);
		return BacSi(maBs, tenBs, chuyenKhoa, sdt, diaChi, email, gioiTinh, ngaySinh);
	}

	void NhapThongTinBacSi()
	{
		cout << "Nhap ma bac si: ";
		getline(cin, maBs);
		cout << "Nhap ten bac si: ";
		getline(cin, tenBs);
		cout << "Nhap chuyen khoa: ";
		getline(cin, chuyenKhoa);
		cout << "Nhap so dien thoai: ";
		getline(cin, sdt);
		cout << "Nhap dia chi: ";
		getline(cin, diaChi);
		cout << "Nhap email: ";
		getline(cin, email);
		cout << "Nhap gioi tinh: ";
		getline(cin, gioiTinh);
		cout << "Nhap ngay sinh: ";
		getline(cin, ngaySinh);
	}

	void LayDanhSachBacSiTuFile()
	{
		ifstream file("bacsi.txt");
		if (!file) {
			cout << "Chua co du lieu!\n";
			UI::pause();
			return;
		}
		
		//file.close();
	}

	void ghiDanhSachBacSi(vector<BacSi> ds)
	{
		ofstream file("bacsi.xml");

		file << "<?xml version=\"1.0\"?>\n";
		file << "<DanhSachBacSi>\n";

		for (BacSi bs : ds)
		{
			file << "  <BacSi>\n";
			file << "    <MaBS>" << bs.maBs << "</MaBS>\n";
			file << "    <TenBS>" << bs.tenBs << "</TenBS>\n";
			file << "    <ChuyenKhoa>" << bs.chuyenKhoa << "</ChuyenKhoa>\n";
			file << "    <SDT>" << bs.sdt << "</SDT>\n";
			file << "    <DiaChi>" << bs.diaChi << "</DiaChi>\n";
			file << "    <Email>" << bs.email << "</Email>\n";
			file << "    <GioiTinh>" << bs.gioiTinh << "</GioiTinh>\n";
			file << "    <NgaySinh>" << bs.ngaySinh << "</NgaySinh>\n";
			file << "  </BacSi>\n";
		}

		file << "</DanhSachBacSi>";

		file.close();
	}
	void ghiBacSi(BacSi bs)
	{
		ofstream file("bacsi.xml");

		file << "<?xml version=\"1.0\"?>\n";
		file << "<DanhSachBacSi>\n";

		
			file << "  <BacSi>\n";
			file << "    <MaBS>" << bs.maBs << "</MaBS>\n";
			file << "    <TenBS>" << bs.tenBs << "</TenBS>\n";
			file << "    <ChuyenKhoa>" << bs.chuyenKhoa << "</ChuyenKhoa>\n";
			file << "    <SDT>" << bs.sdt << "</SDT>\n";
			file << "    <DiaChi>" << bs.diaChi << "</DiaChi>\n";
			file << "    <Email>" << bs.email << "</Email>\n";
			file << "    <GioiTinh>" << bs.gioiTinh << "</GioiTinh>\n";
			file << "    <NgaySinh>" << bs.ngaySinh << "</NgaySinh>\n";
			file << "  </BacSi>\n";
		

		file << "</DanhSachBacSi>";

		file.close();
	}

	string layGiaTri(string line)
	{
		int start = line.find(">") + 1;
		int end = line.find("</");
		return line.substr(start, end - start);
	}

	vector<BacSi> docDanhSachBacSi()
	{
		vector<BacSi> ds;
		ifstream file("bacsi.xml");

		string line;
		BacSi bs;

		while (getline(file, line))
		{
			if (line.find("<MaBS>") != string::npos)
				bs.maBs = layGiaTri(line);

			else if (line.find("<TenBS>") != string::npos)
				bs.tenBs = layGiaTri(line);

			else if (line.find("<ChuyenKhoa>") != string::npos)
				bs.chuyenKhoa = layGiaTri(line);

			else if (line.find("<SDT>") != string::npos)
				bs.sdt = layGiaTri(line);

			else if (line.find("<DiaChi>") != string::npos)
				bs.diaChi = layGiaTri(line);

			else if (line.find("<Email>") != string::npos)
				bs.email = layGiaTri(line);

			else if (line.find("<GioiTinh>") != string::npos)
				bs.gioiTinh = layGiaTri(line);

			else if (line.find("<NgaySinh>") != string::npos)
			{
				bs.ngaySinh = layGiaTri(line);
				ds.push_back(bs); // kết thúc 1 bác sĩ
			}
		}

		file.close();
		return ds;
	}



};
