#pragma once
#include "LiblaryHeader.h"
#include "SystemMethod.h"
#include "UI.h"
#include "BenhNhan.h"
#include "PhongKham.h"
#include "BacSi.h"
#include "CanLamSang.h"
#include "NhapThuoc.h"
#include "banThuoc.h"
#include "ThanhToan.h"
#include "SystemPK.h"
#include "TiengViet.h"



int main() {
	setupVietnamese();
	SystemPK sys;
	sys.menuDangNhap();

	return 0;
}