#include "stdafx.h"
#include "Lab4.h"
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK   WriteProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK   ReadProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

static char fileName[MAX_LOADSTRING] = "";
static char fileName2[MAX_LOADSTRING] = "";



BYTE byte = 123;
UINT uint = 321;
INT32 int32 = 4567;
INT64 int64 = 7654321;
WORD word = 12;
DWORD dword = 123; 
BOOL bol = TRUE;
LONG lng = 1234567L;
FLOAT floaT = 1.23;
double doublE = 32.1;
CHAR chr = L'I';
char str1[] = "Varabei Ivan";
char str2[] = "Varabei Ivan";
char str3[] = "Makar";


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_SAVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, WriteProc);
				break;
			case ID_READ:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, ReadProc);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

OPENFILENAME ofn, FileBin, FileTxt;
CHAR temp[20];
char szFile[400];
HANDLE hFileBin, hFileText;
int lenght;
WCHAR ch[2];
DWORD  dwRes;
CHAR new_line[] = "\x0D\x0A";
int arrEdit[14] = {IDC_EDIT1, IDC_EDIT2, IDC_EDIT3, IDC_EDIT4, IDC_EDIT5,
IDC_EDIT6, IDC_EDIT7, IDC_EDIT8, IDC_EDIT9, IDC_EDIT10, IDC_EDIT11, IDC_EDIT12,
IDC_EDIT13, IDC_EDIT14 };

BOOL CALLBACK   WriteProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		FileTxt.lStructSize = sizeof(OPENFILENAME); 
		FileTxt.hwndOwner = hDlg;                  
		FileTxt.lpstrFile = (LPWSTR)fileName;            
		FileTxt.lpstrFilter = L"TextFiles\0*.txt";
		FileTxt.nMaxFile = sizeof(fileName);
		FileTxt.lpstrDefExt = L"txt";
		
		SetDlgItemInt(hDlg, IDC_EDIT1, byte, 0);
		SetDlgItemInt(hDlg, IDC_EDIT2, uint, 0);
		SetDlgItemInt(hDlg, IDC_EDIT3, int32, 0);
		SetDlgItemInt(hDlg, IDC_EDIT4, int64, 0);
		SetDlgItemInt(hDlg, IDC_EDIT5, word, 0);
		SetDlgItemInt(hDlg, IDC_EDIT6, dword, 0);
		SetDlgItemInt(hDlg, IDC_EDIT7, lng, 0);
		SetDlgItemInt(hDlg, IDC_EDIT8, bol, 0);
		ch[0] = chr;
		ch[1] = '\0';
		SetDlgItemTextW(hDlg, IDC_EDIT11, ch);
		_gcvt_s(temp, floaT, 5);
		SetDlgItemTextA(hDlg, IDC_EDIT9, (LPCSTR)temp);
		_gcvt_s(temp, doublE, 5);
		SetDlgItemTextA(hDlg, IDC_EDIT10, (LPCSTR)temp);
		SetDlgItemTextA(hDlg, IDC_EDIT12, (LPCSTR)str1);
		SetDlgItemTextA(hDlg, IDC_EDIT13, (LPCSTR)str2);
		SetDlgItemTextA(hDlg, IDC_EDIT14, (LPCSTR)str3);
		return TRUE;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_OK)
		{

			byte = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, NULL);
			uint = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, NULL);
			int32 = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, NULL);
			int64 = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, NULL);
			word = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, NULL);
			dword = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, NULL);
			lng = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, NULL);
			bol = GetDlgItemInt(hDlg, IDC_EDIT8, NULL, NULL);
			floaT = GetDlgItemInt(hDlg, IDC_EDIT9, NULL, NULL);
			doublE = GetDlgItemInt(hDlg, IDC_EDIT10, NULL, NULL);
			chr = GetDlgItemInt(hDlg, IDC_EDIT11, NULL, NULL);

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		if (LOWORD(wParam) == ID_CANSEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON1) {
			
			
			if (GetSaveFileName(&FileTxt))
			{
				hFileText = CreateFile(FileTxt.lpstrFile, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				for (int i = 0; i < 14; i++)
				{
					lenght = GetWindowTextLengthA(GetDlgItem(hDlg, arrEdit[i]));
					GetWindowTextA(GetDlgItem(hDlg, arrEdit[i]), (LPSTR)temp, lenght + 1);
					WriteFile(hFileText, temp, lenght, &dwRes, NULL);
					WriteFile(hFileText, &new_line, strlen(new_line), &dwRes, NULL);

				}
				CloseHandle(hFileText);
			}
			break;
		}
		if (LOWORD(wParam) == IDC_BUTTON2) {
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFile = (LPWSTR)fileName;
			ofn.nMaxFile = sizeof(fileName);
			ofn.lpstrFilter = L"Все\0*.bin*\0";
			ofn.Flags = OFN_OVERWRITEPROMPT;
			if (GetSaveFileName(&ofn))
			{
				hFileBin = CreateFile((LPWSTR)fileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				
				byte = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, NULL);
				uint = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, NULL);
				int32 = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, NULL);
				int64 = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, NULL);
				word = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, NULL);
				dword = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, NULL);
				lng = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, NULL);
				bol = GetDlgItemInt(hDlg, IDC_EDIT8, NULL, NULL);

				WriteFile(hFileBin, &byte, sizeof(byte), &dwRes, NULL);
				WriteFile(hFileBin, &uint, sizeof(UINT), &dwRes, NULL);
				WriteFile(hFileBin, &int32, sizeof(INT32), &dwRes, NULL);		
				WriteFile(hFileBin, &int64, sizeof(INT64), &dwRes, NULL);		
				WriteFile(hFileBin, &word, sizeof(WORD), &dwRes, NULL);			
				WriteFile(hFileBin, &dword, sizeof(DWORD), &dwRes, NULL);		
				WriteFile(hFileBin, &lng, sizeof(LONG), &dwRes, NULL);
				WriteFile(hFileBin, &bol, sizeof(BOOL), &dwRes, NULL);

				////FLOAT
				TCHAR str[256];
				GetWindowText(GetDlgItem(hDlg, IDC_EDIT9), str, 256);
				float fl = (float)_wtof(str);
				WriteFile(hFileBin, &fl, sizeof(float), &dwRes, nullptr);

				WriteFile(hFileBin, &chr, sizeof(CHAR), &dwRes, NULL);
				WriteFile(hFileBin, str1, strlen(str1), &dwRes, NULL);
				WriteFile(hFileBin, str2, strlen(str2), &dwRes, NULL);
				WriteFile(hFileBin, str3, strlen(str3), &dwRes, NULL);
				CloseHandle(hFileBin);
			}
			break;
		}
	}
	return FALSE;
}

HWND readEdit; 
const int readl = 200;
char read[256], out[3], k;
int iLenght, i;

char buff[15];
wchar_t buff1[15];

BOOL CALLBACK ReadProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG: 
		FileBin.lStructSize = sizeof(OPENFILENAME);
		FileBin.hwndOwner = hDlg;
		FileBin.lpstrFile = (LPWSTR)fileName2;
		FileBin.lpstrFilter = L"BinFiles\0*.bin";
		FileBin.nMaxFile = sizeof(fileName2);
		FileBin.lpstrDefExt = L"bin";

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hDlg;
		ofn.lpstrFile = (LPWSTR)fileName;
		ofn.nMaxFile = sizeof(fileName);
		ofn.lpstrFilter = L"Все\0*.txt*\0";
		ofn.Flags = OFN_OVERWRITEPROMPT;

		readEdit = GetDlgItem(hDlg, IDC_EDIT2);
		return TRUE;
	break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON1) 
		{
			SendMessage(readEdit, WM_CLEAR, 0, 0);

			hFileText = CreateFile(ofn.lpstrFile, GENERIC_READ, FILE_SHARE_READ,
				NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (GetOpenFileName(&ofn))
			{
				char str[1000];
				memset(str, NULL, sizeof(str));
				int length = GetFileSize(hFileText, NULL);
				ReadFile(hFileText, &str, length, &dwRes, NULL);
				SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), str);
			}

			BYTE bytes[1000];
			char temp[10], dump[10000] = " ";
			DWORD dwBytes;

			SetFilePointer(hFileText, 0, NULL, FILE_BEGIN);
			ReadFile(hFileText, bytes, 1000, &dwBytes, NULL);
			int i = 0;
			for (; i < dwBytes; i++)
			{
				_itoa_s(bytes[i], temp, 16);
				if (temp[0] == 'a')
				{
					i++;
					continue;
				}
				strcat_s(dump, temp);
				strcat_s(dump, " ");
			}
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), dump);
			CloseHandle(hFileText);

		}

		if (LOWORD(wParam) == IDC_BUTTON3)
		{
			SendMessage(readEdit, WM_CLEAR, 0, 0);
			if (GetOpenFileName(&FileBin))
			{
				DWORD nRead;

				HANDLE hFile = CreateFile(FileBin.lpstrFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
					nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);

				TCHAR buf[256]=L"";
				TCHAR var[256];

				BYTE byte = 0;
				ReadFile(hFile, &byte, sizeof(BYTE), &nRead, nullptr);
				_itow_s(byte, buf, sizeof(buf) / 2, 10);
				lstrcat(buf, L" ");

				UINT uint = 0;
				ReadFile(hFile, &uint, sizeof(UINT), &nRead, nullptr);
				_itow_s(uint, var, sizeof(var) / 2, 10);
				lstrcat(buf, var);
				lstrcat(buf, L" ");

				INT32 in32 = 0;
				ReadFile(hFile, &in32, sizeof(INT32), &nRead, nullptr);
				_itow_s(in32, var, sizeof(var) / 2, 10);
				lstrcat(buf, var);
				lstrcat(buf, L" ");

				INT64 in64 = 0;
				ReadFile(hFile, &in64, sizeof(INT64), &nRead, nullptr);
				_itow_s(in64, var, sizeof(var) / 2, 10);
				lstrcat(buf, var);
				lstrcat(buf, L" ");

				WORD word = 0;
				ReadFile(hFile, &word, sizeof(WORD), &nRead, nullptr);
				_itow_s(word, var, sizeof(var) / 2, 10);
				lstrcat(buf, var);
				lstrcat(buf, L" ");

				DWORD dword = 0;
				ReadFile(hFile, &dword, sizeof(DWORD), &nRead, nullptr);
				_itow_s(dword, var, sizeof(var) / 2, 10);
				lstrcat(buf, var);
				lstrcat(buf, L" ");
				
				LONG lon = 0;
				ReadFile(hFile, &lon, sizeof(LONG), &nRead, nullptr);
				_itow_s(lon, var, sizeof(var) / 2, 10);
				lstrcat(buf, var);
				lstrcat(buf, L" ");

				BOOL bol = 0;
				ReadFile(hFile, &bol, sizeof(BOOL), &nRead, nullptr);
				_itow_s(bol, var, sizeof(var) / 2, 10);
				lstrcat(buf, var);
				lstrcat(buf, L" ");

				float fl = 0;
				ReadFile(hFile, &fl, sizeof(float), &nRead, nullptr);
				StringCbPrintf(var + lstrlen(var), 255, L"%.2f ", fl);
				lstrcat(buf, var);

				lstrcat(buf, L"Varabei Ivan ");
				lstrcat(buf, L"Varabei Ivan ");
				lstrcat(buf, L"Makar ");

				SetWindowText(GetDlgItem(hDlg, IDC_EDIT3), (LPCWSTR)&buf);

				BYTE bytes[1000];
				char temp[10], dump[10000] = " ";
				DWORD dwBytes;

				SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
				ReadFile(hFile, bytes, GetFileSize(hFile, NULL), &dwBytes, NULL);
				int i = 0;
				for (; i < dwBytes; i++)
				{
					_itoa_s(bytes[i], temp, 16);
					if (temp[0] == 'a')
					{
						i++;
						continue;
					}
					strcat_s(dump, temp);
					strcat_s(dump, " ");
				}
				SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), dump);
				BYTE x = bytes[1];
				bytes[1] = bytes[4]; 
				bytes[4] = x;
				dwBytes = 0; 
				BYTE y = 2;
				SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
				WriteFile(hFile, bytes, GetFileSize(hFile, NULL), &dwBytes, NULL);

				BYTE bytes1[1000];
				char temp1[10], dump1[10000] = " ";
				DWORD dwBytes1;

				SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
				ReadFile(hFile, bytes1, GetFileSize(hFile, NULL), &dwBytes1, NULL);
				i = 0;
				for (; i < dwBytes1; i++)
				{
					_itoa_s(bytes1[i], temp1, 16);
					if (temp1[0] == 'a')
					{
						i++;
						continue;
					}
					strcat_s(dump1, temp1);
					strcat_s(dump1, " ");
				}
				SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), dump1);
				
				UINT i1 = 0;
				BYTE k = 0;
				char q[512];
				char buf2[512];
				SetFilePointer(hFile, 0, 0, FILE_BEGIN);
				ReadFile(hFile, &buf2, GetFileSize(hFile, NULL), &nRead, NULL);
				while (i1 < GetFileSize(hFile, NULL))
				{
					k += sprintf_s(q + k, GetFileSize(hFile, nullptr), "%02X ", (unsigned char)buf2[i]);
					i1++;
				}
				SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), q);
				CloseHandle(hFile);
			}
		}
		break;
	}
	return FALSE;
}