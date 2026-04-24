#pragma once
#include "LiblaryHeader.h"

class DoiTuongQuanLy {
public:
    virtual void nhap() = 0;
    virtual void save() = 0;  
    virtual void hienThi() = 0;

    virtual ~DoiTuongQuanLy() {}
};