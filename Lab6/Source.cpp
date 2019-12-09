#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <Wincrypt.h>
#include "Header.h"

#define BUFSIZE 1024
#define MD5LEN  16
using namespace std;

int back() {
	int code;
	cout << "Нажмите SPACE, если хотите обратно";
	code = _getch();
	if (code == 32) { main(); }
	else return 0;
}
int l5()
{
	int n1, n2 = 0, k = 0;
	cout << "Введите минимальную длину палиндромов, которые удалять" << endl;
	cin >> n1;
	ifstream f1("file1.txt");
	ofstream f2("file2.txt");
	while (!f1.eof())
	{
		char str[1000] = { '\0' };
		char s[15] = { '\0' };
		f1.getline(str, 1000);
		bool palindrom = true;
		str[strlen(str)] = '\n';
		for (int i = 0; i < 1000; i++)
		{
			if (isalpha(str[i]))
			{
				s[k] = str[i];
				k++;
			}
			if (str[i] == ' ' || str[i] == '!' || str[i] == '.' || str[i] == ',' || str[i] == '?' || str[i] == ':' || str[i] == ';' || str[i] == '\n')
			{
				bool palindrom = true;
				for (int j = 0; j < k / 2; j++)
				{
					if (s[j] != s[k - j - 1])
					{
						palindrom = false;
						break;
					}
					n2 = j + 1;
				}
				if (palindrom && n2 >= n1)
				{
					for (int a = i - 1 - k; a <= i - 1; a++)
					{
						str[a] = '1';
					}
					for (int i = k - 1; i >= 0; i--)
					{
						s[i] = '\0';
					}
					k = 0;
					n2 = 0;
				}
				else
				{
					for (int i = k - 1; i >= 0; i--)
					{
						s[i] = '\0';
					}
					k = 0;
					n2 = 0;
				}
			}
			if ((str[i] == '\n' && str[i + 1] == '\0') || str[i] == '\0')
			{
				break;
			}
		}
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] != '\0')
			{
				if (str[i] != '1') { f2 << str[i]; }
			}
		}
	}
	f1.close();
	f2.close();
	back();
	return 0;
}
int l13()
{
	setlocale(LC_ALL, "Russian");
	ifstream f1("text1.txt");
	ofstream f2("text2.txt");
	int n;
	cout << "~~~~~~~~~~~~~~~~WARNING~~~~~~~~~~~~~~~~" << endl;
	cout << "Работает, но через раз и не со всеми словами. Если укажите на ошибку-буду признателен" << endl;
	cout << "Введите сколько слов будет в словаре" << endl;
	cin >> n;
	cout << "Заполните словарь" << endl;
	for (int i = 0; i < n; i++)
	{
		char word[25] = { '\0' };
		char line[250] = { '\0' };
		cin >> word;
		while (!f1.eof())
		{
			bool flag = false;
			f1.getline(line, 250);
			if (strstr(line, word))
			{
				int l1 = strlen(word);
				int l2 = 0;
				for (int i = 0; i < strlen(line); i++)
				{
					l2 = 0;
					flag = false;
					int ii = i;
					for (int j = 0; j < 25; j++)
					{
						if (line[ii] == word[j])
						{
							ii++; l2++;
						}
						else if (line[ii] != word[j] && l2 == l1)
						{
							flag = true; break;
						}
						else if (line[ii] != word[j]) { break; }

					}
					if (flag) { f2 << word << ' '; }
				}
			}
		}
		f1.seekg(0, ios::beg);
	}
	f1.close();
	f2.close();
	return 0;
}
unsigned long long md5()
{
	DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HANDLE hFile = NULL;
	BYTE rgbFile[BUFSIZE];
	DWORD cbRead = 0;
	BYTE rgbHash[MD5LEN];
	DWORD cbHash = 0;
	CHAR rgbDigits[] = "0123456789abcdef";
	LPCWSTR filename = L"text1.txt";


	hFile = CreateFile(filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwStatus = GetLastError();
		printf("Error opening file %s\nError: %d\n", filename,
			dwStatus);
		return dwStatus;
	}


	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		dwStatus = GetLastError();
		printf("CryptAcquireContext failed: %d\n", dwStatus);
		CloseHandle(hFile);
		return dwStatus;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		dwStatus = GetLastError();
		printf("CryptAcquireContext failed: %d\n", dwStatus);
		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);
		return dwStatus;
	}

	while (bResult = ReadFile(hFile, rgbFile, BUFSIZE,
		&cbRead, NULL))
	{
		if (0 == cbRead)
		{
			break;
		}

		if (!CryptHashData(hHash, rgbFile, cbRead, 0))
		{
			dwStatus = GetLastError();
			printf("CryptHashData failed: %d\n", dwStatus);
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			CloseHandle(hFile);
			return dwStatus;
		}
	}

	if (!bResult)
	{
		dwStatus = GetLastError();
		printf("ReadFile failed: %d\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return dwStatus;
	}

	cbHash = MD5LEN;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		printf("MD5: ", filename);
		for (DWORD i = 0; i < cbHash; i++)
		{
			printf("%c%c", rgbDigits[rgbHash[i] >> 4],
				rgbDigits[rgbHash[i] & 0xf]);
		}
		printf("\n");
	}
	else
	{
		dwStatus = GetLastError();
		printf("CryptGetHashParam failed: %d\n", dwStatus);
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);
	back();
	return dwStatus;
}