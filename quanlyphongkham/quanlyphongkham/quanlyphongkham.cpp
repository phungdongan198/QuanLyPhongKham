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



int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	SystemPK sys;
	/*sys.menuChinh();*/
	sys.menuDangNhap();

	return 0;
}