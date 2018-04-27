#include <fcntl.h>
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
	if (temp == L'"')
	{
		temp = fgetwc(file);
	}
	while (temp != L'"')
	{
		if (temp != L',')
		{
			a[i] = temp;
			i++;
			temp = fgetwc(file);
		}
		else break;
	}
	if (temp == L'"')
	{
		temp = fgetwc(file);
	}
	a[i] = L'\0';
}

void laySo(FILE* file, int &a)
{
	wchar_t temp = fgetwc(file);
	if (temp == L'"')
	{
		fwscanf_s(file, L"%d", &a);
		temp = fgetwc(file);
	}
	else
	{
		fseek(file, -1, SEEK_CUR);
		fwscanf_s(file, L"%d", &a);
		temp = fgetwc(file);
	}
	if (temp == L'"')
	{
		temp = fgetwc(file);
	}
}

void getHobby(FILE* file, wchar_t a[10][100], int &soST)
{
	soST = 0;
	int j = 0;
	wchar_t temp = fgetwc(file);
	if (temp == L'"')
	{
		temp = fgetwc(file);
	}
	while (temp != L'"')
	{
		if (temp != L'"'&&temp != L';'&&temp != L'.')
		{
			a[soST][j] = temp;
			j++;
			temp = fgetwc(file);
		}
		else if (temp == L';')
		{
			a[soST][j] = L'\0';
			soST++;
			j = 0;
			temp = fgetwc(file);
		}
		else if (temp == L'.')
		{
			a[soST][j] = L'\0';
			temp = fgetwc(file);
			if (temp == L'"')
			{
				temp = fgetwc(file);
			}
			break;
		}
	}
}

void layDuLieu(FILE* file, SV &a, int &soST, int mail)
{
	getInfo(file, a.MSSV);
	getInfo(file, a.HVT);
	getInfo(file, a.KHOA);
	laySo(file, a.KHOAS);
	if (mail == 1)
	{
		getInfo(file, a.MAIL);
	}
	getInfo(file, a.NS);
	getInfo(file, a.HA);
	getInfo(file, a.MT);
	getHobby(file, a.ST, soST);
}

void optional(int &hvt, int &mssv, int &khoa, int &khoas, int &mail, int &ngaysinh, int &mota, int &sothich, int &mailtemp)
{
	wprintf(L"Lựa chọn các trường nội dung bạn muốn hiển thị (chọn gõ \"1\", không chọn gõ \"0\"):\n");
	wprintf(L"1. Họ và tên: ");
	wscanf(L"%d", &hvt);
	wprintf(L"2. Mã số sinh viên: ");
	wscanf(L"%d", &mssv);
	wprintf(L"3. Khoa: ");
	wscanf(L"%d", &khoa);
	wprintf(L"4. Khóa tuyển: ");
	wscanf(L"%d", &khoas);
	wprintf(L"5. Ngày sinh: ");
	wscanf(L"%d", &ngaysinh);
	wprintf(L"6. Mô tả bản thân: ");
	wscanf(L"%d", &mota);
	wprintf(L"7. Sở thích: ");
	wscanf(L"%d", &sothich);
	if (mail == 1)
	{
		wprintf(L"8. Mail: ");
		wscanf(L"%d", &mailtemp);
	}
}

void taoFileHtm(SV a, int soST, int hvt, int mssv, int khoa, int khoas, int mail, int ngaysinh, int mota, int sothich)
{
	wchar_t ten[30];
	int i, j;
	for (i = 0; a.MSSV[i] != L'\0'; i++)
	{
		ten[i] = a.MSSV[i];
	}
	wchar_t temp[] = { L'.', L'h', L't', L'm' };
	for (j = 0; j < 4; j++)
	{
		ten[i + j] = temp[j];
	}
	ten[i + j] = L'\0';
	FILE* f = _wfopen(ten, L"w, ccs=UTF-8");
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
		if (hvt == 1 || mssv == 1 || khoa == 1 || khoas == 1 || ngaysinh == 1 || mail == 1)
		{
			fwprintf(f, L"\t\t\t\t\t\t<div class=\"InfoGroup\">Thông tin cá nhân</div>\n");
			fwprintf(f, L"\t\t\t\t\t\t<div>\n");
			fwprintf(f, L"\t\t\t\t\t\t\t<ul class=\"TextInList\">\n");
			if (hvt == 1)
			{
				fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Họ và tên: %ls</li>\n", a.HVT);
			}
			if (mssv == 1)
			{
				fwprintf(f, L"\t\t\t\t\t\t\t\t<li>MSSV: %ls</li>\n", a.MSSV);
			}
			if (khoa == 1)
			{
				fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Sinh viên khoa %ls</li>\n", a.KHOA);
			}
			if (khoas == 1)
			{
				fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Khóa tuyển: %d</li>\n", a.KHOAS);
			}
			if (ngaysinh == 1)
			{
				fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Ngày sinh: %ls</li>\n", a.NS);
			}
			if (mail == 1)
			{
				fwprintf(f, L"\t\t\t\t\t\t\t\t<li>Email: %ls</li>\n", a.MAIL);
			}
		}
		fwprintf(f, L"\t\t\t\t\t\t\t</ul>\n");
		fwprintf(f, L"\t\t\t\t\t\t</div>\n");
		if (sothich == 1)
		{
			fwprintf(f, L"\t\t\t\t\t\t<div class=\"InfoGroup\">Sở thích</div>\n");
			fwprintf(f, L"\t\t\t\t\t\t<div>\n");
			fwprintf(f, L"\t\t\t\t\t\t\t<ul class=\"TextInList\">\n");
			for (int i = 0; i <= soST; i++)
			{
				fwprintf(f, L"\t\t\t\t\t\t\t\t<li>%ls</li>\n", *(a.ST + i));
			}
			fwprintf(f, L"\t\t\t\t\t\t\t</ul>\n");
			fwprintf(f, L"\t\t\t\t\t\t</div>\n");
		}
		if (mota == 1)
		{
			fwprintf(f, L"\t\t\t\t\t\t<div class=\"InfoGroup\">Mô tả</div>\n");
			fwprintf(f, L"\t\t\t\t\t\t<div class=\"Description\">\n");
			fwprintf(f, L"\t\t\t\t\t\t\t%ls.\n", a.MT);
			fwprintf(f, L"\t\t\t\t\t\t</div>\n");
		}
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
		wprintf(L"Không thể tạo file %ls!\n", ten);
	}
}

void wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	int hvt = 1;
	int mssv = 1;
	int khoa = 1;
	int khoas = 1;
	int mail = 1;
	int mailtemp = 1;
	int ngaysinh = 1;
	int mota = 1;
	int sothich = 1;
	SV a[100];
	int soST;
	int soSV = 0;
	int option = 1;
	wchar_t ten[30];
	wprintf(L"Sao chép tập tin dữ liệu của bạn vào thư mục của project này. \nSau đó nhập tên của tập tin csv (ví dụ: thongtin.csv, là tập tin sẵn của sinh viên làm đồ án): ");
	wscanf(L"%ls", ten);
	wprintf(L"%ls", ten);
	FILE* f = _wfopen(ten, L"r,ccs=UTF-8");
	if (f != NULL)
	{
		while (!feof(f))
		{
			wchar_t temp = fgetwc(f);
			if (temp == L'\n')
			{
				soSV++;
			}
		}
		fseek(f, 3, SEEK_SET);
		wprintf(L"Tập tin thông tin của bạn có trường email không?\nNếu có gõ \"1\", nếu không có gõ \"0\" (Tập tin mặc định của sinh viên nhập \"1\"): ");
		wscanf(L"%d", &mail);
		wprintf(L"Hỗ trợ cấu hình trang: Bạn muốn tùy chỉnh cho tất cả các trang nhập \"1\", tùy chỉnh cho từng trang nhập \"0\":");
		wscanf(L"%d", &option);
		if (option == 1)
		{
			optional(hvt, mssv, khoa, khoas, mail, ngaysinh, mota, sothich, mailtemp);
			for (int i = 0; i < soSV; i++)
			{
				layDuLieu(f, *(a + i), soST, mail);
				taoFileHtm(*(a + i), soST, hvt, mssv, khoa, khoas, mailtemp, ngaysinh, mota, sothich);
			}
		}
		else
		{
			for (int i = 0; i < soSV; i++)
			{
				wprintf(L"Sinh viên %d:\n", i + 1);
				layDuLieu(f, *(a + i), soST, mail);
				optional(hvt, mssv, khoa, khoas, mail, ngaysinh, mota, sothich, mailtemp);
				taoFileHtm(*(a + i), soST, hvt, mssv, khoa, khoas, mailtemp, ngaysinh, mota, sothich);
			}
		}
		wprintf(L"Đã phát sinh tất cả các trang theo yêu cầu!\n");
		fclose(f);
	}
	else
	{
		wprintf(L"Không thể mở file!\n");
	}
}