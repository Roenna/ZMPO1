#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>

#define TAB_NAME "Tab"
#define TAB_LENGTH 10

using namespace std;
/*
priv:
z: i_tableLength
f: i_getTableLength // problem z odroznieniem f od zm
pub:
z: iTableLength
f: iGetTableLength
*/

class CTable {

private:
	string s_name;
	int* i_table;
	int i_tableLength;

public:
	CTable();
	CTable(string sName);
	CTable(const CTable & pcOther);
	CTable(string sName, int iTableLength, int* iTable);

	//wydaje mi sie, ze sety i gety nie wymagaja komentarzy.

	string sGetName();
	void vSetName(string sName);

	string sGetFull();

	bool bGetValue(int *ptr_value, int iIndex)const;
	bool bSetValue(int iValue, int iIndex);

	int iGetTableLength();
	void vSetTableLength(int iTableLength);

	void vDoNothing(CTable obj); // jak napisane.. rob nic.

	bool bContains(int value);

	CTable & operator= (CTable &c);
	CTable operator+ (CTable &c);
	CTable operator- (CTable &c);
	CTable operator* (CTable &c);

	~CTable();
};