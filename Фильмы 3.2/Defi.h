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
const int n = 50, g = 20;														//вводим постоянные для строк имени и жанра
int num = 0, num_film_1 = 1;													//вводим счётчики
string way = "C:\\Users\\dimak\\Desktop\\Films",
ganre_way = way + "\\Ganre.txt",												//переменные для указания путей к файлам сохранения
name_way = way + "\\Name.txt",
w_unw_way = way + "\\W_Unw.txt",
number_way = way + "\\Number.txt";

void MainWndAddWidgets(HWND hWnd);
char* choose(int a);															//функция выбора фильма
int insert(char* p_name, char* p_ganre, int w_unw);								//функция внесения фильма 
void set_name(char* p_name);													//функция для занесения названия в файл
void set_ganre(char* p_ganre);													//функция занесения жанра в файл
void set_w_unw(int w_unw);														//функция занесения статуса просмотра в файл
char* get_name(int num_2);														//функция выдачи названия с требованием порядкового номера этого фильма 
char* get_ganre(int num_2);														//функция выдачи жанра с требованием порядкового номера этого фильма
int get_w_unw(int num_2);														//функция выдачи статуса просмотра с требованием порядкового номера этого фильма
void change_w_unw(char* name, bool p_w_unw);									//функция изменения статуса просмотра с требованием указателя на строку-название и нового статуса 
void num_plus();																//функция изменения переменной, измеряющей количество фильмов
int get_num();																	//функция выдачи числа занесённых фильмов
bool copy_check(char* p_name);													//объявляем функцию поиска повторяющихся фильмов
bool num_check();																//функция проверки существования файла счётчика фильмов
int ErrorSaveMessage();
int ErrorFileMessage();
void create();

class name_class {
	static char name[n];
public:
	friend bool copy_check(char* p_name);

	friend void set_name(char* p_name) {										//функция для занесения имени фильма в файл
		ofstream outside_name(name_way, ios::out | ios::app | ios::binary);		//инициализируем поток на выход с добавлением к имеющемуся списку
		outside_name.write((char*)p_name, strlen(p_name));						//записываем фильм и переносим строку
		outside_name.write("\n", 1);
		num_plus();																//увеличиваем счётчик фильмов на 1
		outside_name.close();													//закрываем поток
	}

	friend char* get_name(int num_2) {											//функция выдачи имени фильма с требованием порядкового номера этого фильма 
		char* p_name = name_class::name;
		ifstream inside_name(name_way, ios::in | ios::binary);					//инициализируем поток на вход 
		if (!inside_name) {														//если файла не существует, выдаём ошибку
			inside_name.close();
			ErrorFileMessage();
			return 0;
		}
		while (inside_name.getline(p_name, n)) {								//проматываем строки, пока не дойдём до нужной
			num++;																//num отображает номер актуальной строки
			if (num == num_2) {													//проверяем, совпадает ли номер строки с требуемым
				num = 0;														//если совпадает, то счётчик обнуляется
				inside_name.close();											//поток закрывается
				return p_name;													//возвращается указатель с именем фильма
			}
		}
		num = 0;
		inside_name.close();													//на всякий случай снова закрываем поток
		return 0;
	}
};
char name_class::name[];

class ganre_class {
	static char ganre[g];
public:
	friend void set_ganre(char* p_ganre) {										//функция занесения жанра фильма в файл
		ofstream outside_ganre(ganre_way, ios::out | ios::app | ios::binary);	//аналогична set_name
		outside_ganre.write((char*)p_ganre, strlen(p_ganre));
		outside_ganre.write("\n", 1);
		outside_ganre.close();
	}

	friend char* get_ganre(int num_2) {											//функция выдачи жанра фильма с требованием порядкового номера этого фильма
		char* p_ganre = ganre_class::ganre;										//аналогична get_name
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
	friend void set_w_unw(int w_unw) {											//функция занесения статуса просмотра в файл
		ofstream outside_w_unw(w_unw_way, ios::out | ios::app | ios::binary);	//аналогична set_name
		outside_w_unw << w_unw << "\n";
		outside_w_unw.close();
	}

	friend int get_w_unw(int num_2) {											//функция выдачи статуса просмотра фильма с требованием порядкового номера этого фильма
		int j;
		ifstream inside_w_unw(w_unw_way, ios::in | ios::binary);				//аналогична get_name 
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

	friend void change_w_unw(char* name, bool p_w_unw) {						//функция для изменения статуса просмотра
		bool mass_w_unw[100], j;												//массив для хранения статуса просмотра всех фильмов для дальнейшего переноса в новый файл
		copy_check(name);														//ищем порядковый номер фильма
		ifstream inside_w_unw(w_unw_way, ios::in | ios::binary);				//инициализируем поток на вход
		if (!inside_w_unw) {
			inside_w_unw.close();
			ErrorFileMessage();
			ifstream inside_w_unw(w_unw_way, ios::in | ios::binary);
		}
		for (int a = 0; (inside_w_unw >> j && a < get_num()); a++) {			//записываем w_unw из файла в переменную 
			if (a == (num - 1))													//если номер соответствует требуемому для изменения, то вносим в массив новый статус
				mass_w_unw[a] = p_w_unw;
			else
				mass_w_unw[a] = j;												//если не соответствует, то вносим статус из переменной
		}
		inside_w_unw.close();													//закрываем поток на вход
		ofstream clean_file(w_unw_way, ios::out);								//инициализация потока на выход для обнуление файла
		clean_file.close();														//закрытие потока для обнуления файла
		ofstream outside_w_unw(w_unw_way, ios::out | ios::app | ios::binary);	//инициализация потока на выход с добавлением к имеющимся данным
		for (int a = 0; a < get_num(); a++)										//не позволяем вносить больше статусов, чем фильмов
			outside_w_unw << mass_w_unw[a] << "\n";								//вносим статусы из массива
		outside_w_unw.close();													//закрываем поток на выход
		num = 0;
	}
};

class num_class {
public:
	friend void num_plus() {													//функция изменения переменной, измеряющей количество фильмов
		int num_film;
		ifstream inside_num_plus(number_way, ios::in | ios::binary);			//инициализируем поток на вход 
		if (!inside_num_plus) {													//если файла нет, то сам создасться
			inside_num_plus.close();
			num_film = 1;														//ставим количество фильмов 1 по умолчанию
		}
		else {
			inside_num_plus >> num_film;										//записываем количество фильмов из файла в глобальную переменную
			num_film++;															//прибавляем 1, потому что функция вызывается только при добавлении нового фильма
		}
		inside_num_plus.close();												//закрываем поток
		ofstream outside_num_plus(number_way, ios::out | ios::binary);			//инициализируем поток на выход
		outside_num_plus << num_film;											//заносим новыое количество фильмов в файл
		outside_num_plus.close();												//закрываем поток
	}

	friend int get_num() {														//функция для выдачи количества занесённых фильмов
		ifstream inside_num_plus(number_way, ios::in | ios::binary);			//открываем поток на вход
		int num_film;
		if (!inside_num_plus) {													//если файла нет, выдаём ошибку
			inside_num_plus.close();
			ErrorFileMessage();
			return 0;
		}
		inside_num_plus >> num_film;											//вносим число из файла в глобальную переменную
		inside_num_plus.close();												//закрываем поток
		return num_film;														//возвращаем число
	}

	friend bool num_check() {													//проверка наличия файла количества фильмов
		ifstream inside_num_plus(number_way, ios::in | ios::binary);			//открываем поток
		if (!inside_num_plus) {													//если НЕ открылся, закрваем и возвращаем 0
			inside_num_plus.close();
			return 0;
		}
		else {																	//если открылся, закрываем и возвращаем 1
			inside_num_plus.close();
			return 1;
		}
	}
};

char* choose(int a) {															//функция выбора фильма
	num_film_1 += a;
	for (num_film_1; num_film_1 <= get_num(); num_film_1++) {					//если num_film_1 равен количеству фильмов, цикл заканчивается
		if (get_w_unw(num_film_1) == 1) continue;								//если фильм отмечен просмотренным, то переходим к следующему
		else if (get_w_unw(num_film_1) == 2) break;								//если выходит 2, то достигнут конец списка и цикл прекращается
		else if (get_w_unw(num_film_1) == 0)									//если фильм отмечен непросмотренным, то возвращаем название
			return get_name(num_film_1);
	}
	return (char*)"f";															//если достигнут конец списка, возвращаем f
}

int insert(char* p_name, char* p_ganre, int w_unw) {							//функция внесения фильмов
	if (num_check() == 1)														//если есть файл-счётчик, проверяем копии
		if (copy_check(p_name)) {												//проверяем, нет ли уже такого фильма
			num = 0;															//copy_check изменяет эту переменную, она используется в других функциях, но не здесь
			ErrorSaveMessage();													//выводит сообщение с ошибкой
			return 2;															//возвращаем кодс ошибкой
		}
	set_name(p_name);															//вносим имя, жанр и статус просмотра индивидуальными функциями
	set_ganre(p_ganre);
	set_w_unw(w_unw);
	return 1;																	//возвращаем один, как успех
}

bool copy_check(char* p_name) {													//функция поиска повторяющихся фильмов
	ifstream inside_name(name_way, ios::in | ios::binary);						//поток на вход
	bool i;																		//переменная для хранения статуса повторения
	num = 0;
	while (inside_name.getline(name_class::name, n)) {							//читаем строки с файла и вносим их в переменную
		num++;																	//счётчик для нахождения номера фильма
		for (int q = 0; q < strlen(p_name); q++) {								//сравниваем имя из файла с именем с именем из переменной побуквенно
			if (name_class::name[q] == p_name[q]) i = 1;						//если буква совпадает, то i меняется на 1
			else if (name_class::name[q] != p_name[q]) {						//если нет, переход к следующей строке\слову
				i = 0;
				break;
			}
		}
		if ((strlen(name_class::name) == strlen(p_name))+1 && i == 1) {			//если спустя целове слово i равно 1 и длина слов одинаковая, то слова совпадают и можно это подтвердить, вернув 1
			inside_name.close();												//закрываем поток
			return 1;
		}
	}
	inside_name.close();														//на всякий случай, снова закрываем поток
	return 0;																	//если спустя всё это, 1 так и не вернулась, то копии не найдено и возвращаем 0
}

void create() {																	//если нет папки для сохранения, создаём
	if (!num_check()) {
		boost::filesystem::path dir(way);
		boost::filesystem::create_directories(dir);
	}
}

int ErrorSaveMessage() {														//сообщение об ошибке
	int msgboxID = MessageBox(
		NULL, 
		L"Фильм с таким именем уже существует.", 
		L"Confirm Save As", 
		MB_ICONEXCLAMATION);
	return msgboxID;
}

int ErrorFileMessage() {														//другое сообщение об ошибке
	int msgboxID = MessageBoxA(
		NULL, 
		"У вас не внесено ни одного фильма.", 
		"Confirm Save As", 
		MB_ICONEXCLAMATION);
	return msgboxID;
}