#pragma once
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <string>

// Gọi 1 lần duy nhất trong main()
inline void setupVietnamese() {
    SetConsoleOutputCP(65001);  // dùng 65001 thay CP_UTF8 — tránh lỗi môi trường
    SetConsoleCP(65001);
    setlocale(LC_ALL, ".UTF-8");
}

// string UTF-8 -> wstring (dùng khi đọc từ XML để hiển thị)
inline std::wstring toWstring(const std::string& str) {
    if (str.empty()) return L"";
    int size = MultiByteToWideChar(65001, 0, str.c_str(), -1, nullptr, 0);
    if (size <= 0) return L"";
    std::wstring result(size - 1, 0);
    MultiByteToWideChar(65001, 0, str.c_str(), -1, &result[0], size);
    return result;
}

// wstring -> string UTF-8 (dùng khi lưu vào XML)
inline std::string toString(const std::wstring& wstr) {
    if (wstr.empty()) return "";
    int size = WideCharToMultiByte(65001, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (size <= 0) return "";
    std::string result(size - 1, 0);
    WideCharToMultiByte(65001, 0, wstr.c_str(), -1, &result[0], size, nullptr, nullptr);
    return result;
}

// Đếm số ký tự hiển thị thực của chuỗi UTF-8 (dùng cho UI::center căn giữa)
inline int utf8Length(const std::string& str) {
    int count = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) count++;
    }
    return count;
}