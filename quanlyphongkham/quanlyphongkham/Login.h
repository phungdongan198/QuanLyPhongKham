#pragma once
#include "LiblaryHeader.h"
#include "SystemMethod.h"

class Login
{
private:
	string username;
	string password;
	string role; 

public:
	#pragma region getter_&_setter
	string getUsername() {
		return username;
	}
	
	string getPassword() {
		return password;
	}

	string getRole() {
		return role;
	}

	void SetUsername(string u) {
		username = u;
	}

	void SetPassword(string p) {
		password = p;
	}

	void SetRole(string r) {
		role = r;
	}
	#pragma endregion

	#pragma region các hàm xử lý menu

	Login() {
		username = "Unknow User";
		password = "123456";
		role = "patient";
	}

	//cách khai báo chỉ gán giá trị
	Login(string u, string p, string r) :username(u), password(p), role(r) {}
	/*	username = u;
		password = p;
		role = r;
	}*/

	static string CheckLogin(string userName, string password) // trả về "NULL", "employee" hoặc "admin"
	{
		string checkContaint = "NULL";
		if (!SystemMethod::fileExist("accounts.xml"))
		{
			cout << "Khong co du lieu\n";
			UI::pause();
			return "NULL";
		}
		ifstream f("accounts.xml");

		string line;
		Login account;

		vector<Login> accountList;

		while (getline(f, line)) {
			// 1. Tìm Username
			if (line.find("<Username>") != string::npos) {
				size_t start = line.find("<Username>") + 10; // 10 là độ dài của "<Username>"
				size_t end = line.find("</Username>");
				account.SetUsername(line.substr(start, end - start));
			}

			// 2. Tìm Password
			if (line.find("<Password>") != string::npos) {
				size_t start = line.find("<Password>") + 10;
				size_t end = line.find("</Password>");
				account.SetPassword(line.substr(start, end - start));
			}

			// 3. Tìm Role
			if (line.find("<Role>") != string::npos) {
				size_t start = line.find("<Role>") + 6; // 6 là độ dài của "<Role>"
				size_t end = line.find("</Role>");
				account.SetRole(line.substr(start, end - start));
			}

			// 4. CHỈ PUSH VÀO LIST KHI ĐÃ ĐỌC XONG MỘT TÀI KHOẢN
			if (line.find("</Account>") != string::npos) {
				accountList.push_back(account);

				// Reset lại account về mặc định để chuẩn bị hứng dữ liệu của account tiếp theo
				account = Login("Unknow User", "123456", "employee");
			}
		}
		f.close();
		if (accountList.empty()) 
		{
			return checkContaint;
		}

		for (auto& a : accountList) {
			if (a.username == userName && a.password == password)
			{
				checkContaint=a.role;
			}
		}
		return checkContaint;
	}

	void AddHardAccount()
	{
		// 1. Kiểm tra xem file đã tồn tại chưa bằng cách thử đọc nó
		ifstream checkFile("accounts.xml");
		if (checkFile.good()) {
			// File đã tồn tại rồi, đóng lại và thoát hàm, không ghi đè dữ liệu cũ
			checkFile.close();
			return;
		}
		checkFile.close();

		// 2. Nếu file chưa tồn tại, tiến hành tạo mới file với 2 tài khoản mặc định
		ofstream f("accounts.xml"); // Không dùng ios::app để tạo mới hoàn toàn file chuẩn

		if (f.is_open()) {
			// Tạo thẻ gốc bao ngoài cho chuẩn XML
			/*f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			f << "<Accounts>\n";*/

			// Tài khoản 1: Employee
			f << "<Account>\n";
			f << "  <Username>khambenh</Username>\n";
			f << "  <Password>khambenh123</Password>\n";
			f << "  <Role>employee</Role>\n";
			f << "</Account>\n\n";

			// Tài khoản 2: Admin
			f << "<Account>\n";
			f << "  <Username>admin</Username>\n";
			f << "  <Password>admin123</Password>\n";
			f << "  <Role>admin</Role>\n";
			f << "</Account>\n\n";

			//f << "</Accounts>\n"; // Đóng thẻ gốc

			f.close();
			cout << "Da khoi tao file accounts.xml voi 2 tai khoan mac dinh!" << endl;
		}
		else {
			cout << "Khong the tao file accounts.xml!" << endl;
		}
	}

	void AddAccount(string userName, string password, string role)
	{
		ofstream f("accounts.xml", ios::app);
		f << "<Account>\n";
		f << "<Username>" << userName << "</Username>\n";
		f << "<Password>" << password << "</Password>\n";
		f << "<Role>" << role << "</Role>\n";
		f << "</Account>\n\n";
		f.close();
	}

	static void CheckListAndAdd()
	{
		/*if (!SystemMethod::fileExist("accounts.xml"))
		{
			cout << "Khong co du lieu\n";
			UI::pause();
		}*/
		ifstream f("accounts.xml");

		string line;
		Login account;

		vector<Login> accountList;

		while (getline(f, line)) {

			if (line.find("<Username>") != string::npos)
				account.username = line.substr(4, line.find("</") - 4);

			if (line.find("<Password>") != string::npos)
				account.password = line.substr(5, line.find("</") - 5);

			if (line.find("<Role>") != string::npos)
				account.role = line.substr(6, line.find("</") - 6);

			accountList.push_back(account);
		}
		f.close();
		if (accountList.empty())
		{
			Login login;
			login.AddHardAccount();
		}
	}

	#pragma endregion
};