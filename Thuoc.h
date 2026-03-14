#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include "UI.h"

class Thuoc {

private:

    string maThuoc;
    string tenThuoc;
    string donGia;
    string lo;
    string date;
    string soLuong;
    string ghiChu;

public:

    void nhap() {

        cin.ignore();

        cout << "Ma thuoc: "; getline(cin, maThuoc);
        cout << "Ten thuoc: "; getline(cin, tenThuoc);
        cout << "Don gia: "; getline(cin, donGia);
        cout << "Lo: "; getline(cin, lo);
        cout << "Date: "; getline(cin, date);
        cout << "So luong ton kho: "; getline(cin, soLuong);
        cout << "Ghi chu: "; getline(cin, ghiChu);
    }

    void luuXML() {

        ofstream file("thuoc.xml", ios::app);

        file << "<Thuoc>\n";
        file << "<MaThuoc>" << maThuoc << "</MaThuoc>\n";
        file << "<TenThuoc>" << tenThuoc << "</TenThuoc>\n";
        file << "<DonGia>" << donGia << "</DonGia>\n";
        file << "<Lo>" << lo << "</Lo>\n";
        file << "<Date>" << date << "</Date>\n";
        file << "<SoLuong>" << soLuong << "</SoLuong>\n";
        file << "<GhiChu>" << ghiChu << "</GhiChu>\n";
        file << "</Thuoc>\n\n";

        file.close();
    }

    static void xoaThuoc() 
    {

    UI::clear();
    UI::center("=== XOA THUOC ===", 10);

    string maXoa;
    cin.ignore();

    cout << "Nhap ID thuoc can xoa: ";
    getline(cin, maXoa);

    ifstream file("thuoc.xml");
    ofstream temp("temp.xml");

    string line, block;
    bool inBlock = false;
    bool removeBlock = false;

    int dem = 0;

    while (getline(file, line)) {

        if (line.find("<Thuoc>") != string::npos) {
            block = line + "\n";
            inBlock = true;
            continue;
        }

        if (inBlock) {

            block += line + "\n";

            if (line.find("<MaThuoc>") != string::npos) {

                string ma = line.substr(9, line.find("</") - 9);

                if (ma == maXoa) {
                    removeBlock = true;
                }
            }

            if (line.find("</Thuoc>") != string::npos) {

                inBlock = false;

                if (removeBlock) {
                    dem++;
                }
                else {
                    temp << block;
                }

                block = "";
                removeBlock = false;
            }
        }
    }

    file.close();
    temp.close();

    remove("thuoc.xml");
    rename("temp.xml", "thuoc.xml");

    if (dem > 0)
        cout << "Da xoa " << dem << " thuoc co ID = " << maXoa << endl;
    else
        cout << "Khong tim thay thuoc co ID = " << maXoa << endl;

    UI::pause();
}
};