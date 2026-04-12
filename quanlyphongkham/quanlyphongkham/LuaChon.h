#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class LuaChon {
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
};