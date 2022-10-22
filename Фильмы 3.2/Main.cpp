#include <Windows.h>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include "resource.h"
#include "Defi.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {		//������ ���� ����������

	WNDCLASS SoftwareMainClass = NewWindowClass(
		(HBRUSH)COLOR_WINDOW, 
		LoadCursor(NULL, IDC_ARROW), 
		hInst, 
		LoadIcon(NULL, IDI_QUESTION), 
		L"MainWndClass", 
		SoftwareMainProcedure);
	if (!RegisterClassW(&SoftwareMainClass))
		return -1;
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"�lick program", 
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		200, 200, 2500, 1250, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
}

WNDCLASS NewWindowClass(																	//� �� ����
	HBRUSH BGColor, 
	HCURSOR Cursor, 
	HINSTANCE hInst, 
	HICON Icon, 
	LPCWSTR Name, 
	WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };

	NWC.hbrBackground = BGColor;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.hIcon = Icon;
	NWC.lpszClassName = Name;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {			//������� ��������� ������
	switch (msg) {																			//��� ������� ������ �����������
	case WM_COMMAND:																		//��������������� ���������� ���� 
		switch (wp) {																		//� ��� �������
		case OnButtonClicked1:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OptionsProc1);			//������ ������ ������		
			//MessageBoxA(hWnd, "Thank you, sempai!!!!!", "1 OAOAOAOAOAOAOA", MB_OK);
			break;
		case OnButtonClicked2:
			//MessageBoxA(hWnd, "Thank you, sempai!!!!!", "2 OAOAOAOAOAOAOA", MB_OK);
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, OptionsProc2);			//������ ��������� ������� ���������
			break;
		case OnButtonClicked3:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, OptionsProc3);			//������ �������� ������
			break;
		case OnExitSoftware:
			PostQuitMessage(0);																//������� �������� ���������
			break;
		default: break;
		}
		break;
	case WM_CREATE:																			//������� �������� �������� � �������
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd) {															//������ ������
	CreateWindowA("button", "Select movie", 
		WS_VISIBLE | WS_CHILD | ES_CENTER, 
		5, 5, 800, 1100, hWnd, 
		(HMENU)OnButtonClicked1, NULL, NULL);
	CreateWindowA("button", "Change view status", 
		WS_VISIBLE | WS_CHILD | ES_CENTER, 
		810, 5, 800, 1100, hWnd, 
		(HMENU)OnButtonClicked2, NULL, NULL);
	CreateWindowA("button", "Add movie", 
		WS_VISIBLE | WS_CHILD | ES_CENTER, 
		1615, 5, 800, 1100, hWnd, 
		(HMENU)OnButtonClicked3, NULL, NULL);
}

LRESULT CALLBACK OptionsProc1(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {		//������� ������ �������
	HWND Static_name, Static_ganre;
	Static_name = GetDlgItem(hDlg, IDC_STATIC_NAME);
	Static_ganre = GetDlgItem(hDlg, IDC_STATIC_GANRE);
	switch (uiMsg) {
	case WM_INITDIALOG:																		//����������� ��������� �� ������ �������
		
		if (!get_num()) {																	//���� �����-�������� ���, ��������� ������
			EndDialog(hDlg, 0);
			return TRUE;
		}
		if (choose(0) == "f") {																//���� ������� ������ ������� f ����� ������ � ��������� ������
			MessageBoxA(hDlg, 
				"� ���������, ��� ������ ��� ����������", 
				"2 OAOAOAOAOAOAOA", MB_OK);
			num_film_1 = 1;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		SetWindowTextA(Static_name, choose(0));												//���������� ������ ������������ �����
		SetWindowTextA(Static_ganre, " ");
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDNEXT:																		//����� ��������� �����
			if (choose(1) == "f") {															//���� ��������� ����� ����� f ����� ������ � ��������� ������
				MessageBoxA(hDlg, 
					"� ���������, ��� ������ ������ ��� ����������", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				num_film_1 = 1;
				EndDialog(hDlg, 0);
				return TRUE;
			}
			//Static_name = GetDlgItem(hDlg, IDC_STATIC_NAME);
			SetWindowTextA(Static_name, choose(0));
			SetWindowTextA(Static_ganre, " ");
			return TRUE;
		case IDC_INFO:
			SetWindowTextA(Static_ganre, get_ganre(num_film_1));
			return TRUE;
		case IDYES:																			//������ ��������� ��������� � ��������� ������
			MessageBoxA(hDlg, 
				"��������� ���������!", 
				"2 OAOAOAOAOAOAOA", MB_OK);
			num_film_1 = 1;
			EndDialog(hDlg, 0);
			return TRUE;
		case IDCANCEL:
			num_film_1 = 1;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	default:
		return FALSE;
		break;
	}
}

LRESULT CALLBACK OptionsProc2(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {		//������� ��������� ������� ���������
	char name[n], * p_name;
	int w_unw = 0;
	HWND Combo;
	p_name = name;
	switch (uiMsg) {
	case WM_INITDIALOG:																		//����������� ��������� �� ������ �������
		Combo = GetDlgItem(hDlg, IDC_COMBO1);
		if (!get_num()) {
			EndDialog(hDlg, 0);
			return TRUE;
		}
		for (int i = 1; i <= get_num(); i++) {
			SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)get_name(i));						//����� ���������� ������
		}
		return TRUE;
	case WM_COMMAND:																		//������������ �������
		switch (LOWORD(wParam)) {
		case IDOK:																			//������� �������� ���������
			GetDlgItemTextA(hDlg, IDC_COMBO1, name, n);
			if (name[0] == 0) {																//���������, ��������� �� ���� � ����� ������, ���� ���
				MessageBoxA(hDlg, 
					"����������, ������� ��������", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W)) w_unw = 1;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_UNW)) w_unw = 0;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W) == 0 && 
				IsDlgButtonChecked(hDlg, IDC_RADIO_UNW) == 0) {
				MessageBoxA(hDlg, 
					"����������, �������� ����� ������ ���������", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			change_w_unw(p_name, w_unw);													//���� ��� ���� ��������� ���������� ������ � ������� ��� ���������
			MessageBoxA(hDlg, 
				"������ ��������� ������ ������", 
				"2 OAOAOAOAOAOAOA", MB_OK);													//����� ��������� �� ������ � ��������� ������
			EndDialog(hDlg, 0);
			return TRUE;
		case IDCANCEL:																		//������ ��������
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	default:
		return FALSE;
		break;
	}
}

LRESULT CALLBACK OptionsProc3(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {		//������� �������� ������
	char name[n], ganre[g], * p_name = 0, * p_ganre = 0;									//������ ������ � ��������� ��� �������� � �������� �������� � ������
	int w_unw = 0, a;
	name[0] = 0;
	ganre[0] = 0;
	p_name = name;																			//����������� ������� ���������
	p_ganre = ganre;
	HWND Combo;
	switch (uiMsg) {
	case WM_INITDIALOG:																		//����������� ��������� �� ������ �������
		create();
		Combo = GetDlgItem(hDlg, IDC_COMBO1);												//������ ����� ��� ����������� ����
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Thriller");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Action");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Biography");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Western");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Detective");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Documentary");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Catastrophe");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Horror");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"�omedy");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Fiction");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Melodrama");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Musical");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Noir");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Post-apocalypse");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Drama");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Romcom");
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {															//������������ �������
		case IDOK:																			//�������� ��������
			GetDlgItemTextA(hDlg, IDC_EDIT1, name, n);										//��������� ���������� ���� �����
			if (name[0] == 0) {
				MessageBoxA(hDlg, 
					"����������, ������� ��������", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			GetDlgItemTextA(hDlg, IDC_COMBO1, ganre, g);
			if (ganre[0] == 0) {
				MessageBoxA(hDlg, 
					"����������, �������/�������� ����", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W)) w_unw = 1;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_UNW)) w_unw = 0;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W) == 0 && 
				IsDlgButtonChecked(hDlg, IDC_RADIO_UNW) == 0) {
				MessageBoxA(hDlg, 
					"����������, �������� ������ ���������", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			a = insert(p_name, p_ganre, w_unw);												//���� ���������, �� ���������� � ������� ���������� � ��������� �����
			name[0] = 0;
			ganre[0] = 0;
			if (a != 2) MessageBoxA(hDlg, 
				"����� �����", 
				"2 OAOAOAOAOAOAOA", MB_OK);													//���� ������� ������� �� 2, �� ������� ��������� �� ������ � ��������� ������
			else break;																		//���� ������� 2, �� ����� ����� ��� ���� � ����� �������� ��������
			EndDialog(hDlg, 0);
			return TRUE;
		case IDCANCEL:																		//������ ��������
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	default:
		return FALSE;
		break;
	}
}