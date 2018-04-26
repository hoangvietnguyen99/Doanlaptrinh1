﻿#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

struct SV
{
	wchar_t MSSV[10];
	wchar_t HVT[30];
	wchar_t KHOA[30];
	int KHOAS;
	wchar_t MAIL[20];
	wchar_t NS[11];
	wchar_t HA[20];
	wchar_t MT[1000];
	wchar_t ST[10][100];
};

void getInfo(FILE *file, wchar_t a[])
{
	wchar_t temp = fgetwc(file);
	int i = 0;
	while (1)
	{
		if (temp != L','&&temp != L'"')
		{
			a[i] = temp;
			i++;
			temp = fgetwc(file);
		}
		else break;
	}
	a[i] = L'\0';
}

void laySo(FILE* file, int &a)
{
	wchar_t temp = fgetwc(file);
	if (temp == L'"')
	{
		fwscanf_s(file, L"%d", &a);
		fseek(file, 2L, SEEK_CUR);
	}
	else
	{
		fseek(file, -1L, SEEK_CUR);
		fwscanf_s(file, L"%d", &a);
		fseek(file, 1L, SEEK_CUR);
	}
}

void getHobby(FILE* file, wchar_t a[10][100])
{
	wchar_t temp = fgetwc(file);
	int i = 0;
	int j = 0;
	while (1)
	{
		if (temp != L'"')
		{
			a[i][j] = temp;
			j++;
			temp = fgetwc(file);
		}
		if (temp == L';' || temp == L'.')
		{
			a[i][j] = L'\0';
			i++;
			j = 0;
		}
		if (temp == L'\n' || temp == WEOF)
		{
			a[i][j] = L'\0';
			break;
		}
	}
}

void layDuLieu(FILE* file, SV &a)
{
	getInfo(file, a.MSSV);
	getInfo(file, a.HVT);
	getInfo(file, a.KHOA);
	laySo(file, a.KHOAS);
	getInfo(file, a.MAIL);
	getInfo(file, a.NS);
	getInfo(file, a.HA);
	getInfo(file, a.MT);
	getHobby(file, a.ST);
}

void taoFileHtm(SV a)
{
	wchar_t* ten = a.MSSV;

	FILE* f = _wfopen(L"WEBSITE\\sinhvien.htm", L"w, ccs=UTF-8");
	if (f != NULL)
	{
		fwprintf(f, L"<!DOCTYPE html PUBLIC \" -//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
		fwprintf(f, L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
		fwprintf(f, L"\t</head>\n");
		fwprintf(f, L"\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
		fwprintf(f, L"\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n");
		fwprintf(f, L"\t\t<title>HCMUS - %ls</title>\n", a.HVT);
		fwprintf(f, L"\t</head>\n");
		fwprintf(f, L"\t<body>\n");
		fwprintf(f, L"\t\t<div class=\"Layout_container\">\n");
		fwprintf(f, L"\t\t\t<!-- Begin Layout Banner Region -->\n");
		fwprintf(f, L"\t\t\t<div class=\"Layout_Banner\" >\n");
		fwprintf(f, L"\t\t\t\t<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n");
		fwprintf(f, L"\t\t\t\t<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\n");
		fwprintf(f, L"\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t<!-- End Layout Banner Region -->\n");
		fwprintf(f, L"\t\t\t<!-- Begin Layout MainContents Region -->\n");
		fwprintf(f, L"\t\t\t<div class=\"Layout_MainContents\">\n");
		fwprintf(f, L"\t\t\t\t<!-- Begin Below Banner Region -->\n");
		fwprintf(f, L"\t\t\t\t<div class=\"Personal_Main_Information\">\n");
		fwprintf(f, L"\t\t\t\t\t<!-- Begin Thông tin cá nhân của thầy cô ------------------------------------------------------------------------------------------->\n");
		fwprintf(f, L"\t\t\t\t\t<div class=\"Personal_Location\">\n");
		fwprintf(f, L"\t\t\t\t\t\t<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n");
		fwprintf(f, L"\t\t\t\t\t\t<span class=\"Personal_FullName\">%ls - %ls</span>\n", a.HVT, a.MSSV);
		fwprintf(f, L"\t\t\t\t\t\t<div class=\"Personal_Department\">KHOA %ls</div>\n", a.KHOA);
		fwprintf(f, L"\t\t\t\t\t\t<br />\n");
		fwprintf(f, L"\t\t\t\t\t\t<div class=\"Personal_Phone\">\n");
		fwprintf(f, L"\t\t\t\t\t\t\tEmail: %ls\n", a.MAIL);
		fwprintf(f, L"\t\t\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t\t\t<br />\n");
		fwprintf(f, L"\t\t\t\t\t\t<br />\n");
		fwprintf(f, L"\t\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t\t<!-- End Thông tin cá nhân của thầy cô ------------------------------------------------------------------------------------------->\n");
		fwprintf(f, L"\t\t\t\t\t<div class=\"Personal_HinhcanhanKhung\">\n");
		fwprintf(f, L"\t\t\t\t\t\t<img src=\"%ls\" class=\"Personal_Hinhcanhan\" />\n", a.HA);
		fwprintf(f, L"\t\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t<!-- End Below Banner Region -->\n");
		fwprintf(f, L"\t\t\t\t<!-- Begin MainContents Region -->\n");
		fwprintf(f, L"\t\t\t\t<div class=\"MainContain\">\n");
		fwprintf(f, L"\t\t\t\t\t<!-- Begin Top Region -->\n");
		fwprintf(f, L"\t\t\t\t\t<div class=\"MainContain_Top\">\n");
		fwprintf(f, L"\t\t\t\t\t\t<div class=\"InfoGroup\">Thông tin cá nhân</div>\n");
		fwprintf(f, L"\t\t\t\t\t\t<div>\n");
		fwprintf(f, L"\t\t\t\t\t\t\t<ul class=\"TextInList\">\n");
		fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Họ và tên: %ls</li>\n", a.HVT);
		fwprintf(f, L"\t\t\t\t\t\t\t\t<li>MSSV: %ls</li>\n", a.MSSV);
		fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Sinh viên khoa %ls</li>\n", a.KHOA);
		fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Ngày sinh: %ls</li>\n", a.NS);
		fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Email: %ls</li>\n", a.MAIL);
		fwprintf(f, L"\t\t\t\t\t\t\t</ul>\n");
		fwprintf(f, L"\t\t\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t\t\t<div class=\"InfoGroup\">Sở thích</div>\n");
		fwprintf(f, L"\t\t\t\t\t\t<div>\n");
		fwprintf(f, L"\t\t\t\t\t\t\t<ul class=\"TextInList\">\n");
		for (int i = 0; i < a.soST; i++)
		{
			fwprintf(f, L"\t\t\t\t\t\t\t\t<li>%ls</li>\n", *(a.ST + i));
		}
		fwprintf(f, L"\t\t\t\t\t\t\t</ul>\n");
		fwprintf(f, L"\t\t\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t\t\t<div class=\"InfoGroup\">Mô tả</div>\n");
		fwprintf(f, L"\t\t\t\t\t\t<div class=\"Description\">\n");
		fwprintf(f, L"\t\t\t\t\t\t\t%ls.\n", a.MT);
		fwprintf(f, L"\t\t\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t<!-- Begin Layout Footer -->\n");
		fwprintf(f, L"\t\t\t<div class=\"Layout_Footer\">\n");
		fwprintf(f, L"\t\t\t\t<div class=\"divCopyright\">\n");
		fwprintf(f, L"\t\t\t\t\t<br />\n");
		fwprintf(f, L"\t\t\t\t\t<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n");
		fwprintf(f, L"\t\t\t\t\t<br />\n");
		fwprintf(f, L"\t\t\t\t\t@2018</br>\n");
		fwprintf(f, L"\t\t\t\t\tĐồ án giữa kỳ</br>\n");
		fwprintf(f, L"\t\t\t\tKỹ thuật lập trình</br>\n");
		fwprintf(f, L"\t\t\t\tTH2018/04</br>\n");
		fwprintf(f, L"\t\t\t\t1712905 - Nguyễn Hoàng Việt</br>\n");
		fwprintf(f, L"\t\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t</div>\n");
		fwprintf(f, L"\t\t\t<!-- End Layout Footer -->\n");
		fwprintf(f, L"\t\t</div>\n");
		fwprintf(f, L"\t</body>\n");
		fwprintf(f, L"</html>");
		fclose(f);
	}
	else
	{
		wprintf(L"Không thể tạo file html!\n");
	}
}

void wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	SV a;
	int dem = 0;
	FILE* f = _wfopen(L"thongtin.csv", L"r,ccs=UTF-8");
	if (f != NULL)
	{
		fseek(f, 3, SEEK_SET);
		layDuLieu(f, a);
		//FILE* file = _wfopen(L"chep.txt", L"w,ccs=UTF-8");
		//fwprintf(file, L"%ls %ls %ls %d", a.MSSV, a.HVT, a.KHOA, a.KHOAS);
		//fclose(file);
		taoFileHtm(a);
	}
	else
	{
		wprintf(L"Không thể mở file!\n");
	}
	fclose(f);
}