#include <Windows.h>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include "resource.h"
#include "Defi.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {		//создаём тело приложения

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

	CreateWindow(L"MainWndClass", L"Сlick program", 
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		200, 200, 2500, 1250, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
}

WNDCLASS NewWindowClass(																	//я не знаю
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

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {			//функция обработки команд
	switch (msg) {																			//при нажатии кнопки открывается
	case WM_COMMAND:																		//соответствующее диалоговое окно 
		switch (wp) {																		//и его функция
		case OnButtonClicked1:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OptionsProc1);			//внопка выбора фильма		
			//MessageBoxA(hWnd, "Thank you, sempai!!!!!", "1 OAOAOAOAOAOAOA", MB_OK);
			break;
		case OnButtonClicked2:
			//MessageBoxA(hWnd, "Thank you, sempai!!!!!", "2 OAOAOAOAOAOAOA", MB_OK);
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, OptionsProc2);			//кнопка изменения статуса просмотра
			break;
		case OnButtonClicked3:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, OptionsProc3);			//кнопка внесения фильма
			break;
		case OnExitSoftware:
			PostQuitMessage(0);																//функция закрытия программы
			break;
		default: break;
		}
		break;
	case WM_CREATE:																			//функция создания виджетов и прочего
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd) {															//создаём кнопки
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

LRESULT CALLBACK OptionsProc1(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {		//функция выбора фильмов
	HWND Static_name, Static_ganre;
	Static_name = GetDlgItem(hDlg, IDC_STATIC_NAME);
	Static_ganre = GetDlgItem(hDlg, IDC_STATIC_GANRE);
	switch (uiMsg) {
	case WM_INITDIALOG:																		//настраиваем интерфейс на основе шаблона
		
		if (!get_num()) {																	//если файла-счётчика нет, закрываем диалог
			EndDialog(hDlg, 0);
			return TRUE;
		}
		if (choose(0) == "f") {																//если функция выбора вернула f выдаём ошибку и закрываем диалог
			MessageBoxA(hDlg, 
				"К сожалению, нам нечего вам предложить", 
				"2 OAOAOAOAOAOAOA", MB_OK);
			num_film_1 = 1;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		SetWindowTextA(Static_name, choose(0));												//показываем первый предлагаемый фильм
		SetWindowTextA(Static_ganre, " ");
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDNEXT:																		//выдаём следующий фильм
			if (choose(1) == "f") {															//если слудующий заход вернёт f выдаём ошибку и закрываем диалог
				MessageBoxA(hDlg, 
					"К сожалению, нам больше нечего вам предложить", 
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
		case IDYES:																			//желаем приятного просмотра и закрываем диалог
			MessageBoxA(hDlg, 
				"Приятного просмотра!", 
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

LRESULT CALLBACK OptionsProc2(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {		//функция изменения статуса просмотра
	char name[n], * p_name;
	int w_unw = 0;
	HWND Combo;
	p_name = name;
	switch (uiMsg) {
	case WM_INITDIALOG:																		//настраиваем интерфейс на основе шаблона
		Combo = GetDlgItem(hDlg, IDC_COMBO1);
		if (!get_num()) {
			EndDialog(hDlg, 0);
			return TRUE;
		}
		for (int i = 1; i <= get_num(); i++) {
			SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)get_name(i));						//задаём выпадающий список
		}
		return TRUE;
	case WM_COMMAND:																		//обрабатываем команды
		switch (LOWORD(wParam)) {
		case IDOK:																			//команда внесения изменений
			GetDlgItemTextA(hDlg, IDC_COMBO1, name, n);
			if (name[0] == 0) {																//проверяем, заполнены ли поля и выдаём ошибку, если нет
				MessageBoxA(hDlg, 
					"Пожалуйста, введите название", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W)) w_unw = 1;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_UNW)) w_unw = 0;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W) == 0 && 
				IsDlgButtonChecked(hDlg, IDC_RADIO_UNW) == 0) {
				MessageBoxA(hDlg, 
					"Пожалуйста, выберите новый статус просмотра", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			change_w_unw(p_name, w_unw);													//если все поля заполнены отправляем данные в функция для изменения
			MessageBoxA(hDlg, 
				"Статус просмотра фильма изменён", 
				"2 OAOAOAOAOAOAOA", MB_OK);													//выдаём сообщение об успехе и закрываем диплог
			EndDialog(hDlg, 0);
			return TRUE;
		case IDCANCEL:																		//кнопка закрытия
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	default:
		return FALSE;
		break;
	}
}

LRESULT CALLBACK OptionsProc3(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {		//функция внесения фильма
	char name[n], ganre[g], * p_name = 0, * p_ganre = 0;									//создаём строки и указатели для хранения и передачи названий и жанров
	int w_unw = 0, a;
	name[0] = 0;
	ganre[0] = 0;
	p_name = name;																			//присваиваем строкам указатели
	p_ganre = ganre;
	HWND Combo;
	switch (uiMsg) {
	case WM_INITDIALOG:																		//настраиваем интерфейс на основе шаблона
		create();
		Combo = GetDlgItem(hDlg, IDC_COMBO1);												//вводим жанры для выпадающего меню
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Thriller");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Action");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Biography");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Western");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Detective");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Documentary");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Catastrophe");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Horror");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Сomedy");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Fiction");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Melodrama");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Musical");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Noir");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Post-apocalypse");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Drama");
		SendMessageA(Combo, CB_ADDSTRING, 0, (LPARAM)"Romcom");
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {															//отрабатываем команды
		case IDOK:																			//комманда внесения
			GetDlgItemTextA(hDlg, IDC_EDIT1, name, n);										//проверяем заполнение всех полей
			if (name[0] == 0) {
				MessageBoxA(hDlg, 
					"Пожалуйста, введите название", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			GetDlgItemTextA(hDlg, IDC_COMBO1, ganre, g);
			if (ganre[0] == 0) {
				MessageBoxA(hDlg, 
					"Пожалуйста, введите/выберите жанр", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W)) w_unw = 1;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_UNW)) w_unw = 0;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_W) == 0 && 
				IsDlgButtonChecked(hDlg, IDC_RADIO_UNW) == 0) {
				MessageBoxA(hDlg, 
					"Пожалуйста, выберите статус просмотра", 
					"2 OAOAOAOAOAOAOA", MB_OK);
				break;
			}
			a = insert(p_name, p_ganre, w_unw);												//если заполнены, то отправляем в функция посредника и сохраняем ответ
			name[0] = 0;
			ganre[0] = 0;
			if (a != 2) MessageBoxA(hDlg, 
				"Фильм внесён", 
				"2 OAOAOAOAOAOAOA", MB_OK);													//если функция вернула НЕ 2, то выводим сообщение об успехе и закрываем диалог
			else break;																		//если вернула 2, то такой фильм уже есть и нужно изменить название
			EndDialog(hDlg, 0);
			return TRUE;
		case IDCANCEL:																		//кнопка закрытия
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	default:
		return FALSE;
		break;
	}
}