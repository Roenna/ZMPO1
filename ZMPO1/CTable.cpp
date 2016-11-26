#include "CTable.h"

CTable::CTable() {
	this->i_tableLength = TAB_LENGTH;
	this->s_name = TAB_NAME;
	i_table = new int[i_tableLength];

	for (int i = 0; i < i_tableLength; i++) {
		i_table[i] = 0; //zerowanie tablicy, bo sa smieci
	}

	cout << "bezp: '" << s_name << "'" << endl;
}

CTable::CTable(string sName) {
	this->i_tableLength = TAB_LENGTH;
	this->s_name = sName;
	i_table = new int[i_tableLength];

	for (int i = 0; i < i_tableLength; i++) {
		i_table[i] = 0; //zerowanie tablicy, bo sa smieci
	}

	cout << "parametr: '" << sName << "'" << endl;
}

CTable::CTable(const CTable & pcOther) {
	s_name = pcOther.s_name + "_copy";
	i_tableLength = pcOther.i_tableLength;
	delete i_table;
	i_table = new int[i_tableLength];

	int tmp_val = 0;

	for (int i = 0; i < i_tableLength; i++) {
		pcOther.bGetValue(&tmp_val, i); //pobieranie wartosci z tablicy
		i_table[i] = tmp_val; //i wstawianie do nowej
	}

	cout << "kopiuj: ' " << s_name << "'" << endl;
}
CTable::CTable(string sName, int iTableLength, int* iTable) {
	s_name = sName;
	i_tableLength = iTableLength;
	i_table = new int[iTableLength];
	for (int i = 0; i < iTableLength; i++)
		i_table[i] = iTable[i];
}

string CTable::sGetName() {
	return s_name;
}

void CTable::vSetName(string sName) {
	s_name = sName;
}

string CTable::sGetFull() {
	string sValues = "";
	for (int i = 0; i < i_tableLength; i++) {
		if (i>0) sValues += ", ";
		sValues += to_string(i_table[i]);
	}
	string sInf = s_name + " " + "len: " + to_string(i_tableLength) + " values: " + sValues;
	return sInf;
}

bool CTable::bGetValue(int* ptr_value, int iIndex)const {
	if (iIndex >= i_tableLength)
		return false;
	else {
		*ptr_value = *(i_table + iIndex); //zwracam adres elementu na danej pozycji w tablicy
		return true;
	}
}

bool CTable::bSetValue(int iValue, int iIndex) {
	if (iIndex > i_tableLength)
		return false;
	else {
		i_table[iIndex] = iValue;
		return true;
	}
}

int CTable::iGetTableLength() {
	return i_tableLength;
}

void CTable::vSetTableLength(int iTableLength) {
	int* old_table = i_table; //zapisujemy adres starej tab
	int* new_table = new int[iTableLength]; //tworzymy nowa tab 

	//w ogole to zawczasu wypelnilabym te nowa 0...

	for (int i = 0; i < iTableLength; i++) {
		new_table[i] = 0; //zerowanie tablicy, bo sa smieci
	}

	for (int i = 0; i < i_tableLength; i++) { //dodajemy wartosci idac po indeksach starej tablicy
		if (i < iTableLength) { //index < dl nowej tab, jak wiekszy, to kuniec
			new_table[i] = old_table[i];
		}
		else {
			break;
		}
	}
	delete[] old_table; //usuwamy stara tablice
	i_table = new_table; //przypisujemy nowa 

	i_tableLength = iTableLength; //oraz dlugosc
}

void CTable::vDoNothing(CTable obj) { //rob nic, poniewaz.

}

CTable::~CTable() {
	delete i_table;
	cout << "usuwam: " << s_name << endl;
}

CTable & CTable::operator= (CTable &c) { 
	s_name = c.s_name;
	i_tableLength = c.i_tableLength;
	delete i_table;
	i_table = new int[i_tableLength];

	for (int i = 0; i < i_tableLength; i++) {
		i_table[i] = c.i_table[i];
	}
	return *this; //i zwracam "uaktualniony" obiekt
}

CTable CTable::operator+ (CTable &c) {
	string name = s_name + " + " + c.s_name; //tworze wszystkie zmienne do obiektu
	int tableLength = i_tableLength + c.i_tableLength;
	int* table = new int[tableLength];
	int i = 0, j = 0;
	while (i < i_tableLength) { //przelatuje przez tablice obiektu
		if (i_table[i] != 0) { //jak wartosc !=0 to ja dodaje
			table[j] = i_table[i];
			i++;
			j++;
		}
		else
			i++;
	}
	i = 0;
	while (i < c.i_tableLength) { //to samo robe z druga tablica
		if (c.i_table[i] != 0) {
			table[j] = c.i_table[i];
			i++;
			j++;
		}
		else
			i++;
	}
	tableLength = j; //zmiana dlugosci na te aktualna, indeks po zsumowaniu el to dl tablicy (bez +1, bo dodawalo sie na biezoco po dodaniu el)
	return CTable(name, tableLength, table); //zwracam nowy obiekt o parametrach tworzonych na biezaco wyzej
}
/*
Gdyz iz poniewaz sposob z tworzeniem nowego obiektu CTable temp, uaktualnianie go i zwracanie skutkowalo utworzeniem nowego
obiektu, zmienianie jego wartosci na "poprawne" wynikowo, lecz przy zwrocie return temp obiekt zostawal usuwany
i zwracana byla jego kopia (tab1 + tab2._copy), czego nie chcieliœmy, trzeba by³o unikn¹æ u¿ycia kontr. kopiujacego.
Druga wersja metody zwraca³a nowy obiekt return CTable(temp.sName, ... ) przyjmujac parametry utworzonego na poczatku obiektu temp.
No i w sumie dzia³a³o. Jednak ostatecznie tworzê zmienne przechowuj¹ce "poprawne" dane obiektu i tworzê obiekt wynikowy
na samym koñcu. Unikam tworzenia niepotrzebnego obiektu tymczasowego (w sumie nie wiem, czy to jakoœ "lepiej", po prostu
dra¿ni³y mnie te napisy w konsoli "Bezp: Tab" "Usuwam: Tab", czy, o zgrozo "Usuwam: tab1 + tab2" wypisywane przy pierwszej wersji)
*/

CTable CTable::operator- (CTable &c) {
	string name = s_name + " - " + c.s_name; //to samo, co wyzej
	int tableLength = i_tableLength + c.i_tableLength;
	int* table = new int[tableLength];
	int i = 0, j = 0;
	while (i < i_tableLength) {
		if (!c.bContains(i_table[i]) && i_table[i]!=0) { //jak jakiegos elementu nie ma w drugiej tablicy, to zostaje w nowej tab
			table[j] = i_table[i];
			i++;
			j++;
		}
		else
			i++;
		
	}
	tableLength = j; //bo po dodaniu ostatniego el i tak doda³o sie 1
	return CTable(name, tableLength, table);
}

CTable CTable::operator* (CTable &c) {
	string name = s_name + " * " + c.s_name;
	int tableLength = i_tableLength + c.i_tableLength;
	int* table = new int[tableLength];
	int i = 0, j = 0;
	while (i < c.i_tableLength) {
		if (bContains(c.i_table[i]) && c.i_table[i] != 0) { //jak el istnieje w obu tablicach, to zostaje dodany do nowej
			table[j] = c.i_table[i];
			i++;
			j++;
		}
		else
			i++;
		
	}
	tableLength = j; //bo po dodaniu ostatniego el i tak doda³o sie 1
	return CTable(name, tableLength, table);
}

bool CTable::bContains(int value) {
	bool contains = false;
	for (int i = 0; i < i_tableLength; i++) {
		if (i_table[i] == value)
			contains = true;
	}
	return contains;
}


