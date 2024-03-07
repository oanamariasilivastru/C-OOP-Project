#pragma once
#include <string>
#include <iostream>
#include "Observer.h"
using std::string;
using std::cout;

class Carte : public Observable {
	std::string titlu;
	std::string autor;
	std::string gen;
	int an;
public:
	Carte() = delete;
	Carte(const string t, const string a, const string g, int an) :titlu{ t }, autor{ a }, gen{ g }, an{ an } {};

	string getTitlu() const {
		return titlu;
	}
	string getAutor() const {
		return autor;
	}
	string getGen() const {
		return gen;
	}
	int getAn() const noexcept {
		return an;
	}

	void setAn(int An) {
		this->an = An;
	}

	void setGen(string Gen) {
		this->gen = Gen;
	}
};


/*
* Compara doua carti dupa titlu
*
* @return: true daca titlul cartii c1 este mai mic decat
*		   titlul cartii c2, false altfel
*/
bool cmpTitlu(const Carte& c1, const Carte& c2);

/*
* Compara doua carti dupa autor
*
* @return: true daca autorul cartii c1 este mai mic decat
*		   autor cartii c2, false altfel
*/
bool cmpAutor(const Carte& c1, const Carte& c2);

/*
* Compara doua carti dupa an si gen
*
* @return: true daca autorul cartii c1 este mai mic decat
*		   autor cartii c2, false altfel
*/
bool cmpAnGen(const Carte& c1, const Carte& c2);



