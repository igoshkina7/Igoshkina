#pragma once
#include <iostream>
#include<string>
#include <fstream>

using namespace std;

class CKS
{
	friend istream& operator >> (istream& in, CKS& new_ks);
	friend ostream& operator << (ostream& out, const CKS& k);
	friend ofstream& operator << (ofstream& out, const CKS& k);
	friend fstream& operator >> (fstream& in, CKS& k);

	int id;
public:
	string name;
	int kolvo_workshops;
	int kolvo_workshops_in_work;
	double efficiency;
	static int IDC;
	CKS();
	CKS(fstream& fin);
	int get_id() const;
};

