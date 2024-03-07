#pragma once
#include "Carte.h"

#include <vector>
#include <string>
#include <ostream>
#include<map>
using std::map;


using std::vector;
using std::string;
using std::ostream;

class RepoAbstract {
public:
	//RepoAbstract() = default;
	virtual ~RepoAbstract() = default;

	virtual void store(const Carte& c) = 0;

	virtual const Carte& find(string titlu, string autor) = 0;

	virtual const vector<Carte> getAll() = 0;

	virtual bool deleteCarte(const Carte& c) = 0;

	virtual int findPoz(const Carte& c) = 0;

	virtual bool modificaCarte(const Carte& c) = 0;

	virtual bool exist(const Carte& c) = 0;
};

class RepoLab : public RepoAbstract {
public:
	map<int, Carte> all_map;
	float prob = 0.5;
	int k = 0;


	RepoLab(float prob) : prob{ prob } {
		k = 0;
	}
	//nu permitem copierea de obiecte
	/*
	* Salvare carte
	*
	* @param carte: obiect de tip Carte
	* arunca exceptie daca mai exista o carte cu acelasi titlu si autor
	*/
	void store(const Carte& c);

	/*
	* Cauta o carte
	*
	* @param titlu: string
	* @param autor: string
	* arunca exceptie daca nu exista carte
	*/
	const Carte& find(string titlu, string autor);

	/*
	* returneaza toate cartile salvate
	*/
	virtual const vector <Carte> getAll();
	/*
	* Sterge o carte
	*
	* @param titlu: string
	* @param autor: string
	* arunca exceptie daca nu exista carte
	*/
	virtual bool deleteCarte(const Carte& c);
	/*
	* Gaseste pozitia unei carti in lista de carti
	*
	* @param c : obiect de tip Carte
	*
	* @return: pozitia cartii
	*/
	int findPoz(const Carte& c);
	/*
	* Modifica carte
	*
	* @param carte: obiect de tip Carte
	* arunca exceptie daca nu exista o carte cu acelasi titlu si autor
	*/
	virtual bool modificaCarte(const Carte& c);
	vector<Carte> all;
	bool exist(const Carte& c);
	//ostream& operator<<(ostream& out, const exception& ex);


};

class CarteRepo : public RepoAbstract {
	vector <Carte> all;
	//Metoda privata veridica daca exista cartea deja in repository
	bool exist(const Carte& c);
public:
	CarteRepo() = default;
	//nu permitem copierea de obiecte
	CarteRepo(const CarteRepo& ot) = delete;
	/*
	* Salvare carte
	*
	* @param carte: obiect de tip Carte
	* arunca exceptie daca mai exista o carte cu acelasi titlu si autor
	*/
	virtual void store(const Carte& c);

	/*
	* Cauta o carte
	*
	* @param titlu: string
	* @param autor: string
	* arunca exceptie daca nu exista carte
	*/
	const Carte& find(string titlu, string autor);

	/*
	* returneaza toate cartile salvate
	*/
	virtual const vector <Carte> getAll();
	/*
	* Sterge o carte
	*
	* @param titlu: string
	* @param autor: string
	* arunca exceptie daca nu exista carte
	*/
	virtual bool deleteCarte(const Carte& c);
	/*
	* Gaseste pozitia unei carti in lista de carti
	*
	* @param c : obiect de tip Carte
	*
	* @return: pozitia cartii
	*/
	int findPoz(const Carte& c);
	/*
	* Modifica carte
	*
	* @param carte: obiect de tip Carte
	* arunca exceptie daca nu exista o carte cu acelasi titlu si autor
	*/
	virtual bool modificaCarte(const Carte& c);

	void emptyRepo() {
		this->all.clear();
	}
};
/*
* Clasa folosita pentru a semnala situatii exceptionale ce pot aparea in repo
*/
class CarteRepoException {
	string msg;
public:
	CarteRepoException(string m) : msg{ m } {}
	//functie friend
	string getErrorMessage() {
		return this->msg;
	}
	friend ostream& operator<<(ostream& out, const CarteRepoException& ex);
};

ostream& operator<<(ostream& out, const CarteRepoException& ex);

void teste_repo();

class RepositoryFile : public CarteRepo {
private:
	string nume_fisier;
	void loadfromfile();
	void save();
public:
	RepositoryFile(string fisier) : CarteRepo(), nume_fisier{ fisier } { loadfromfile(); };


	void store(const Carte& c) override {
		CarteRepo::store(c);
		save();
	}

	bool deleteCarte(const Carte& c) override {
		CarteRepo::deleteCarte(c);
		save();
		return true;
	}

	bool modificaCarte(const Carte& c) override {
		CarteRepo::modificaCarte(c);
		save();
		return true;
	}
	const vector<Carte> getAll() override {
		loadfromfile();
		return CarteRepo::getAll();

	}
};

