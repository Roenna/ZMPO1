#include "CTable.h"
#include <climits>

enum {
	CREATE_OBJECTS = 1,
	CHANGE_SIZE, REMOVE_OBJECT, REMOVE_ALL_OBJECTS, CHANGE_NAME, CLONE_OBJECT, DISPLAY_ARRAY, DISPLAY_ALL_ARRAYS, CHANGE_VALUE, DO_NOTHING, 
	OP_EQUAL, OP_SUM, OP_SUB, OP_MUL
	};

void cleanupCin() {
	// Czyscimy flagi bledow.
	cin.clear();
	// Czyscimy bufor cin.
	cin.ignore(10000, '\n');
}

void cleanupVector(vector<CTable*>* vec) {
	if (vec != 0) {
		for (int i = 0; i < vec->size(); ++i) {
			delete (*vec)[i];
		}
		delete vec;
	}
}

// Funkcja bedzie prosila o podanie inta do momentu, az
// uzytkownik poda inta.
int getProperInt(string msg, int minimum, int maximum) {
	cout << msg << endl;

	bool dataGood = false;
	int iAmount;

	while (!dataGood) {
		// Zakladamy, ze zostanie podana poprawna wartosc.
		// Jesli nie bedzie poprawna, to ustawimy dataGood na false.
		dataGood = true;

		cin >> iAmount;
		// Jesli podane zostanie cos, co nie jest liczba, to cin.bad() zwroci true.
		if (cin.bad() || iAmount < minimum || iAmount > maximum) {
			cout << "Wpisz liczbe z zakresu [" << minimum << ", " << maximum << "]." << endl;
			dataGood = false;
			cleanupCin();
		}
	}
	return iAmount;
}

int main() {
	int iChoice = 0;
	bool bIsCreated = false;
	vector<CTable*>* ptr_vec_CTable = 0;

	do {
		cout <<
			"\n0. Koniec " <<
			"\n1. Utworzenie obiektow " <<
			"\n2. Zmiana dl. tablicy " <<
			"\n3. Skasowanie obiektu " <<
			"\n4. Usuniecie wszystkich obiektow " <<
			"\n5. Nowa nazwa obiektu " <<
			"\n6. Klonowanie " <<
			"\n7. Info o obiekcie " <<
			"\n8. Wszystkie obiekty " <<
			"\n9. Zmiana wartosci komorki obiektu " <<
			"\n10. Rob nic " <<
			"\n11. Operator =" <<
			"\n12. Operator +" <<
			"\n13. Operator -" <<
			"\n14. Operator *" << endl;
			
		cin >> iChoice;

		switch (iChoice) {
			case CREATE_OBJECTS: { //utworzenie objektow
				if (bIsCreated == true) {
					cout << "Obiekty sa juz utworzone!" << endl;
				}
				else {
					int iAmount = getProperInt("Jak duzo obiektow chcesz utworzyc: ", 1, INT32_MAX);
					ptr_vec_CTable = new vector<CTable*>(iAmount); //utworzenie obiektow
					for (int i = 0; i < ptr_vec_CTable->size(); ++i)
					{
						(*ptr_vec_CTable)[i] = new CTable();
					}
					cout << "Wygenerowano " << iAmount << " obiektow" << endl;
					bIsCreated = true;
				}
			}break;

			case CHANGE_SIZE: { //zmiana dlugosci tablicy
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("Podaj nr obiektu, ktory chcesz zmodyfikowac: ", 1, ptr_vec_CTable->size());
					int iNewLength = getProperInt("Podaj nowa dlugosc tablicy: ", 1, INT32_MAX);
					(*ptr_vec_CTable)[iWhichOb - 1]->vSetTableLength(iNewLength);
					cout << "Nowa dlugosc tablicy w obiekcie nr " << iWhichOb << " na " << iNewLength << endl;
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case REMOVE_OBJECT: { //usuniecie obiektu
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("Podaj nr obiektu, ktory chcesz usunac: ", 1, ptr_vec_CTable->size());
					(*ptr_vec_CTable).erase((*ptr_vec_CTable).begin() + (iWhichOb - 1));
					cout << "Skasowano obiekt nr " << iWhichOb << endl; 
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
				if ((*ptr_vec_CTable).size() == 0) {
					bIsCreated = false;
				} // jesli wielkosc wektora jest 0, to oznacza, ze nie ma juz zadnych obiektow
			}break;

			case REMOVE_ALL_OBJECTS: { //usuniecie wszystkich obiektow
				if (bIsCreated == true) {
					(*ptr_vec_CTable).clear();
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
				cout << "Skasowano wszystkie obiekty! " << endl;
				bIsCreated = false;
			}break;

			case CHANGE_NAME: { //zmiana nazwy obiektu
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("Podaj nr obiektu, ktorego nazwe chcesz zmienic: ", 1, ptr_vec_CTable->size());
					string sNewName;
					cout << "Podaj nowa nazwe: ";
					cin >> sNewName;
					(*ptr_vec_CTable)[iWhichOb - 1]->vSetName(sNewName);
					cout << "Zmieniono nazwe w obiekcie nr " << iWhichOb << " na " << sNewName << endl;
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case CLONE_OBJECT: { //sklonowanie obiektu
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("Podaj nr obiektu, ktory chcesz sklonowac: ", 1, ptr_vec_CTable->size());
					CTable *cpy = new CTable(*(*ptr_vec_CTable)[iWhichOb - 1]);
					(*ptr_vec_CTable).push_back(cpy);
					cout << "Obiekt nr " << iWhichOb << " zostal sklonowany!" << endl;
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case DISPLAY_ARRAY: { //zawartosc tablicy
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("Podaj nr obiektu, ktorego zawartosc chcesz zobaczyc: ", 1, ptr_vec_CTable->size());
					cout << (*ptr_vec_CTable)[iWhichOb - 1]->sGetFull() << endl;
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case DISPLAY_ALL_ARRAYS: { //wyswietlenie wszystkich obiektow
				if (bIsCreated == true) {
					for(int i = 0; i<ptr_vec_CTable->size(); i++)
						cout << (*ptr_vec_CTable)[i]->sGetFull() << endl;
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case CHANGE_VALUE: { //ustalenie wartosci na polu w tablicy
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("Podaj nr obiektu, ktory chcesz modyfikowac: ", 1, ptr_vec_CTable->size());
					while ((*ptr_vec_CTable)[iWhichOb - 1]->iGetTableLength() == 0) {
						cout << "Rozmiar tablicy = 0, wybierz inny obiekt!" << endl;
						iWhichOb = getProperInt("Podaj nr obiektu, ktory chcesz modyfikowac: ", 1, ptr_vec_CTable->size());
					}
					int iIndex = getProperInt("Podaj numer pola: ", 0, ((*ptr_vec_CTable)[iWhichOb - 1]->iGetTableLength()));
					int iValue = getProperInt("Podaj wartosc: ", INT32_MIN, INT32_MAX);
					//i jak juz poda..
					(*ptr_vec_CTable)[iWhichOb - 1]->bSetValue(iValue, iIndex-1);
					cout << "Zmieniono wartosc obiektu nr " << iWhichOb << " w polu nr " << iIndex << " na " << iValue << endl;
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case DO_NOTHING: { //rob nic
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("Podaj nr obiektu: ", 1, ptr_vec_CTable->size());
					(*ptr_vec_CTable)[iWhichOb - 1]->vDoNothing(*(*ptr_vec_CTable)[iWhichOb - 1]);
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;
			
			case OP_EQUAL: { //operator =
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("", 1, ptr_vec_CTable->size());
					int iWhichOb1 = getProperInt(" = ", 1, ptr_vec_CTable->size());
					(*ptr_vec_CTable)[iWhichOb - 1]->operator=(*(*ptr_vec_CTable)[iWhichOb1 - 1]);
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case OP_SUM: { 
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("", 1, ptr_vec_CTable->size());
					int iWhichOb1 = getProperInt(" = ", 1, ptr_vec_CTable->size());
					int iWhichOb2 = getProperInt(" + ", 1, ptr_vec_CTable->size());
					//(*ptr_vec_CTable)[iWhichOb - 1]->operator=((*ptr_vec_CTable)[iWhichOb1 - 1]->operator+(*(*ptr_vec_CTable)[iWhichOb2 - 1]));



					*(*ptr_vec_CTable)[iWhichOb - 1] = (*((*ptr_vec_CTable)[iWhichOb1 - 1]) + (*(*ptr_vec_CTable)[iWhichOb2 - 1]));
				} 
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case OP_SUB: {
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("", 1, ptr_vec_CTable->size());
					int iWhichOb1 = getProperInt(" = ", 1, ptr_vec_CTable->size());
					int iWhichOb2 = getProperInt(" - ", 1, ptr_vec_CTable->size());
					(*ptr_vec_CTable)[iWhichOb - 1]->operator=((*ptr_vec_CTable)[iWhichOb1 - 1]->operator-(*(*ptr_vec_CTable)[iWhichOb2 - 1])); //dziwnie, ale tak dziala, pomyslec
					}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			case OP_MUL: {
				if (bIsCreated == true) {
					int iWhichOb = getProperInt("", 1, ptr_vec_CTable->size());
					int iWhichOb1 = getProperInt(" = ", 1, ptr_vec_CTable->size());
					int iWhichOb2 = getProperInt(" * ", 1, ptr_vec_CTable->size());
					(*ptr_vec_CTable)[iWhichOb - 1]->operator=((*ptr_vec_CTable)[iWhichOb1 - 1]->operator*(*(*ptr_vec_CTable)[iWhichOb2 - 1]));
				}
				else {
					cout << "Nie utworzono jeszcze obiektow!" << endl;
				}
			}break;

			default: {
				iChoice = 0;
				break;
			}

		}

		system("pause");
		cleanupCin();
		system("cls");
	} while (iChoice != 0);

	cleanupVector(ptr_vec_CTable);

	return 0;
}