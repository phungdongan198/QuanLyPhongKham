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

	//void LayDanhSachBacSiTuFile()
	//{
	//	ifstream file("bacsi.txt");
	//	if (!file) {
	//		cout << "Chua co du lieu!\n";
	//		UI::pause();
	//		return;
	//	}
	//	
	//	//file.close();
	//}



};
