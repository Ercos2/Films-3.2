#pragma once

#define OnExitSoftware		4
#define OnButtonClicked1	5
#define OnButtonClicked2	6
#define OnButtonClicked3	7
#define OnReadField			8

#define TextBufferSize		256

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
LRESULT CALLBACK OptionsProc1(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OptionsProc2(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OptionsProc3(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInstance;

using namespace std;
const int n = 50, g = 20;														//������ ���������� ��� ����� ����� � �����
int num = 0, num_film_1 = 1;													//������ ��������
string way = "C:\\Users\\dimak\\Desktop\\Films",
ganre_way = way + "\\Ganre.txt",												//���������� ��� �������� ����� � ������ ����������
name_way = way + "\\Name.txt",
w_unw_way = way + "\\W_Unw.txt",
number_way = way + "\\Number.txt";

void MainWndAddWidgets(HWND hWnd);
char* choose(int a);															//������� ������ ������
int insert(char* p_name, char* p_ganre, int w_unw);								//������� �������� ������ 
void set_name(char* p_name);													//������� ��� ��������� �������� � ����
void set_ganre(char* p_ganre);													//������� ��������� ����� � ����
void set_w_unw(int w_unw);														//������� ��������� ������� ��������� � ����
char* get_name(int num_2);														//������� ������ �������� � ����������� ����������� ������ ����� ������ 
char* get_ganre(int num_2);														//������� ������ ����� � ����������� ����������� ������ ����� ������
int get_w_unw(int num_2);														//������� ������ ������� ��������� � ����������� ����������� ������ ����� ������
void change_w_unw(char* name, bool p_w_unw);									//������� ��������� ������� ��������� � ����������� ��������� �� ������-�������� � ������ ������� 
void num_plus();																//������� ��������� ����������, ���������� ���������� �������
int get_num();																	//������� ������ ����� ��������� �������
bool copy_check(char* p_name);													//��������� ������� ������ ������������� �������
bool num_check();																//������� �������� ������������� ����� �������� �������
int ErrorSaveMessage();
int ErrorFileMessage();
void create();

class name_class {
	static char name[n];
public:
	friend bool copy_check(char* p_name);

	friend void set_name(char* p_name) {										//������� ��� ��������� ����� ������ � ����
		ofstream outside_name(name_way, ios::out | ios::app | ios::binary);		//�������������� ����� �� ����� � ����������� � ���������� ������
		outside_name.write((char*)p_name, strlen(p_name));						//���������� ����� � ��������� ������
		outside_name.write("\n", 1);
		num_plus();																//����������� ������� ������� �� 1
		outside_name.close();													//��������� �����
	}

	friend char* get_name(int num_2) {											//������� ������ ����� ������ � ����������� ����������� ������ ����� ������ 
		char* p_name = name_class::name;
		ifstream inside_name(name_way, ios::in | ios::binary);					//�������������� ����� �� ���� 
		if (!inside_name) {														//���� ����� �� ����������, ����� ������
			inside_name.close();
			ErrorFileMessage();
			return 0;
		}
		while (inside_name.getline(p_name, n)) {								//����������� ������, ���� �� ����� �� ������
			num++;																//num ���������� ����� ���������� ������
			if (num == num_2) {													//���������, ��������� �� ����� ������ � ���������
				num = 0;														//���� ���������, �� ������� ����������
				inside_name.close();											//����� �����������
				return p_name;													//������������ ��������� � ������ ������
			}
		}
		num = 0;
		inside_name.close();													//�� ������ ������ ����� ��������� �����
		return 0;
	}
};
char name_class::name[];

class ganre_class {
	static char ganre[g];
public:
	friend void set_ganre(char* p_ganre) {										//������� ��������� ����� ������ � ����
		ofstream outside_ganre(ganre_way, ios::out | ios::app | ios::binary);	//���������� set_name
		outside_ganre.write((char*)p_ganre, strlen(p_ganre));
		outside_ganre.write("\n", 1);
		outside_ganre.close();
	}

	friend char* get_ganre(int num_2) {											//������� ������ ����� ������ � ����������� ����������� ������ ����� ������
		char* p_ganre = ganre_class::ganre;										//���������� get_name
		ifstream inside_ganre(ganre_way, ios::in | ios::binary);
		if (!inside_ganre) {
			inside_ganre.close();
			ErrorFileMessage();
			return 0;
		}
		while (inside_ganre.getline(p_ganre, n)) {
			num++;
			if (num == num_2) {
				num = 0;
				inside_ganre.close();
				return p_ganre;
			}
		}
		num = 0;
		inside_ganre.close();
		return 0;
	}
};
char ganre_class::ganre[];

class w_unw_class {
public:
	friend void set_w_unw(int w_unw) {											//������� ��������� ������� ��������� � ����
		ofstream outside_w_unw(w_unw_way, ios::out | ios::app | ios::binary);	//���������� set_name
		outside_w_unw << w_unw << "\n";
		outside_w_unw.close();
	}

	friend int get_w_unw(int num_2) {											//������� ������ ������� ��������� ������ � ����������� ����������� ������ ����� ������
		int j;
		ifstream inside_w_unw(w_unw_way, ios::in | ios::binary);				//���������� get_name 
		if (!inside_w_unw) {
			inside_w_unw.close();
			ErrorFileMessage();
			return 0;
		}
		while (inside_w_unw >> j) {
			num++;
			if (num == num_2) {
				num = 0;
				inside_w_unw.close();
				return j;
				break;
			}
		}
		num = 0;
		inside_w_unw.close();
		return 2;
	}

	friend void change_w_unw(char* name, bool p_w_unw) {						//������� ��� ��������� ������� ���������
		bool mass_w_unw[100], j;												//������ ��� �������� ������� ��������� ���� ������� ��� ����������� �������� � ����� ����
		copy_check(name);														//���� ���������� ����� ������
		ifstream inside_w_unw(w_unw_way, ios::in | ios::binary);				//�������������� ����� �� ����
		if (!inside_w_unw) {
			inside_w_unw.close();
			ErrorFileMessage();
			ifstream inside_w_unw(w_unw_way, ios::in | ios::binary);
		}
		for (int a = 0; (inside_w_unw >> j && a < get_num()); a++) {			//���������� w_unw �� ����� � ���������� 
			if (a == (num - 1))													//���� ����� ������������� ���������� ��� ���������, �� ������ � ������ ����� ������
				mass_w_unw[a] = p_w_unw;
			else
				mass_w_unw[a] = j;												//���� �� �������������, �� ������ ������ �� ����������
		}
		inside_w_unw.close();													//��������� ����� �� ����
		ofstream clean_file(w_unw_way, ios::out);								//������������� ������ �� ����� ��� ��������� �����
		clean_file.close();														//�������� ������ ��� ��������� �����
		ofstream outside_w_unw(w_unw_way, ios::out | ios::app | ios::binary);	//������������� ������ �� ����� � ����������� � ��������� ������
		for (int a = 0; a < get_num(); a++)										//�� ��������� ������� ������ ��������, ��� �������
			outside_w_unw << mass_w_unw[a] << "\n";								//������ ������� �� �������
		outside_w_unw.close();													//��������� ����� �� �����
		num = 0;
	}
};

class num_class {
public:
	friend void num_plus() {													//������� ��������� ����������, ���������� ���������� �������
		int num_film;
		ifstream inside_num_plus(number_way, ios::in | ios::binary);			//�������������� ����� �� ���� 
		if (!inside_num_plus) {													//���� ����� ���, �� ��� ����������
			inside_num_plus.close();
			num_film = 1;														//������ ���������� ������� 1 �� ���������
		}
		else {
			inside_num_plus >> num_film;										//���������� ���������� ������� �� ����� � ���������� ����������
			num_film++;															//���������� 1, ������ ��� ������� ���������� ������ ��� ���������� ������ ������
		}
		inside_num_plus.close();												//��������� �����
		ofstream outside_num_plus(number_way, ios::out | ios::binary);			//�������������� ����� �� �����
		outside_num_plus << num_film;											//������� ������ ���������� ������� � ����
		outside_num_plus.close();												//��������� �����
	}

	friend int get_num() {														//������� ��� ������ ���������� ��������� �������
		ifstream inside_num_plus(number_way, ios::in | ios::binary);			//��������� ����� �� ����
		int num_film;
		if (!inside_num_plus) {													//���� ����� ���, ����� ������
			inside_num_plus.close();
			ErrorFileMessage();
			return 0;
		}
		inside_num_plus >> num_film;											//������ ����� �� ����� � ���������� ����������
		inside_num_plus.close();												//��������� �����
		return num_film;														//���������� �����
	}

	friend bool num_check() {													//�������� ������� ����� ���������� �������
		ifstream inside_num_plus(number_way, ios::in | ios::binary);			//��������� �����
		if (!inside_num_plus) {													//���� �� ��������, �������� � ���������� 0
			inside_num_plus.close();
			return 0;
		}
		else {																	//���� ��������, ��������� � ���������� 1
			inside_num_plus.close();
			return 1;
		}
	}
};

char* choose(int a) {															//������� ������ ������
	num_film_1 += a;
	for (num_film_1; num_film_1 <= get_num(); num_film_1++) {					//���� num_film_1 ����� ���������� �������, ���� �������������
		if (get_w_unw(num_film_1) == 1) continue;								//���� ����� ������� �������������, �� ��������� � ����������
		else if (get_w_unw(num_film_1) == 2) break;								//���� ������� 2, �� ��������� ����� ������ � ���� ������������
		else if (get_w_unw(num_film_1) == 0)									//���� ����� ������� ���������������, �� ���������� ��������
			return get_name(num_film_1);
	}
	return (char*)"f";															//���� ��������� ����� ������, ���������� f
}

int insert(char* p_name, char* p_ganre, int w_unw) {							//������� �������� �������
	if (num_check() == 1)														//���� ���� ����-�������, ��������� �����
		if (copy_check(p_name)) {												//���������, ��� �� ��� ������ ������
			num = 0;															//copy_check �������� ��� ����������, ��� ������������ � ������ ��������, �� �� �����
			ErrorSaveMessage();													//������� ��������� � �������
			return 2;															//���������� ���� �������
		}
	set_name(p_name);															//������ ���, ���� � ������ ��������� ��������������� ���������
	set_ganre(p_ganre);
	set_w_unw(w_unw);
	return 1;																	//���������� ����, ��� �����
}

bool copy_check(char* p_name) {													//������� ������ ������������� �������
	ifstream inside_name(name_way, ios::in | ios::binary);						//����� �� ����
	bool i;																		//���������� ��� �������� ������� ����������
	num = 0;
	while (inside_name.getline(name_class::name, n)) {							//������ ������ � ����� � ������ �� � ����������
		num++;																	//������� ��� ���������� ������ ������
		for (int q = 0; q < strlen(p_name); q++) {								//���������� ��� �� ����� � ������ � ������ �� ���������� ����������
			if (name_class::name[q] == p_name[q]) i = 1;						//���� ����� ���������, �� i �������� �� 1
			else if (name_class::name[q] != p_name[q]) {						//���� ���, ������� � ��������� ������\�����
				i = 0;
				break;
			}
		}
		if ((strlen(name_class::name) == strlen(p_name))+1 && i == 1) {			//���� ������ ������ ����� i ����� 1 � ����� ���� ����������, �� ����� ��������� � ����� ��� �����������, ������ 1
			inside_name.close();												//��������� �����
			return 1;
		}
	}
	inside_name.close();														//�� ������ ������, ����� ��������� �����
	return 0;																	//���� ������ �� ���, 1 ��� � �� ���������, �� ����� �� ������� � ���������� 0
}

void create() {																	//���� ��� ����� ��� ����������, ������
	if (!num_check()) {
		boost::filesystem::path dir(way);
		boost::filesystem::create_directories(dir);
	}
}

int ErrorSaveMessage() {														//��������� �� ������
	int msgboxID = MessageBox(
		NULL, 
		L"����� � ����� ������ ��� ����������.", 
		L"Confirm Save As", 
		MB_ICONEXCLAMATION);
	return msgboxID;
}

int ErrorFileMessage() {														//������ ��������� �� ������
	int msgboxID = MessageBoxA(
		NULL, 
		"� ��� �� ������� �� ������ ������.", 
		"Confirm Save As", 
		MB_ICONEXCLAMATION);
	return msgboxID;
}