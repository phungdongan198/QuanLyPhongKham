#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include "UI.h"

class CanLamSang {

private:

    string maDV;
    string tenDV;
    string donGia;
    string ghiChu;

public:

    void nhap() {

        cin.ignore();

        cout << "Ma dich vu: "; getline(cin, maDV);
        cout << "Ten dich vu: "; getline(cin, tenDV);
        cout << "Don gia: "; getline(cin, donGia);
        cout << "Ghi chu: "; getline(cin, ghiChu);
    }

    void luuXML() {

        ofstream file("canlamsang.xml", ios::app);

        file << "<DichVu>\n";
        file << "<MaDV>" << maDV << "</MaDV>\n";
        file << "<TenDV>" << tenDV << "</TenDV>\n";
        file << "<DonGia>" << donGia << "</DonGia>\n";
        file << "<GhiChu>" << ghiChu << "</GhiChu>\n";
        file << "</DichVu>\n\n";

        file.close();
    }

    static void xoaDV() {

    UI::clear();
    UI::center("=== XOA DICH VU ===", 10);

    string maXoa;
    cin.ignore();

    cout << "Nhap ID dich vu can xoa: ";
    getline(cin, maXoa);

    ifstream file("canlamsang.xml");
    ofstream temp("temp.xml");

    string line, block;
    bool inBlock = false;
    bool removeBlock = false;

    int dem = 0;

    while (getline(file, line)) {

        if (line.find("<DichVu>") != string::npos) {
            block = line + "\n";
            inBlock = true;
            continue;
        }

        if (inBlock) {

            block += line + "\n";

            if (line.find("<MaDV>") != string::npos) {

                string ma = line.substr(6, line.find("</") - 6);

                if (ma == maXoa) {
                    removeBlock = true;
                }
            }

            if (line.find("</DichVu>") != string::npos) {

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

    remove("canlamsang.xml");
    rename("temp.xml", "canlamsang.xml");

    if (dem > 0)
        cout << "Da xoa " << dem << " dich vu co ID = " << maXoa << endl;
    else
        cout << "Khong tim thay dich vu co ID = " << maXoa << endl;

    UI::pause();
}
};