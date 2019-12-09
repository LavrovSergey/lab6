#include <iostream>
#include <conio.h>
#include "Header.h"


using namespace std;

int menu();
int main()
{
	setlocale(LC_ALL, "Russian");
	int answer = menu();
	switch (answer) {
	case 0: l5(); break;
	case 1: l13(); break;
	case 2: md5(); break;
	case 3: return 0;
	}
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0) cout << "-> 5" << endl;
		else  cout << "   5" << endl;
		if (key == 1) cout << "-> 13" << endl;
		else  cout << "   13" << endl;
		if (key == 2) cout << "-> md5 text1" << endl;
		else  cout << "   md5 text1" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}