#pragma once
#include "LiblaryHeader.h"
#include <WinBase.h>
#include "TiengViet.h"


class UI {
public:

	#pragma region các hàm tiện ích
	static void setColor(int c) 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

	static void printColor(string text, int color) {

		setColor(color);
		cout << text;
		setColor(7); // trả lại màu mặc định
	}

	static void pause() {
		system("pause");
	}

	static void clear() {
		system("cls");
	}

	static void center(string text, int color = 7) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		int padding = (width - utf8Length(text)) / 2; 

		setColor(color);

		for (int i = 0; i < padding; i++)
			cout << " ";

		cout << text << endl;

		setColor(7);
	}
	#pragma endregion
};