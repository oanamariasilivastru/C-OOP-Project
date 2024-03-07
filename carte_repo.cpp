#include "carte_repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <stdlib.h>
#include <exception>

using std::ifstream;
using std::ofstream;
using std::ostream;
using std::stringstream;

void CarteRepo::store(const Carte& c)
{
	if (exist(c)) {
		throw CarteRepoException("Exista deja o alta carte: " + c.getTitlu() + " | " + c.getAutor());

	}
	all.push_back(c);
}

bool CarteRepo::exist(const Carte& c) {
	try {
		find(c.getTitlu(), c.getAutor());
		return true;
	}
	catch (CarteRepoException&) {
		return false;
	}
}
bool CarteRepo::deleteCarte(const Carte& c) {
	try {
		all.erase(all.begin() + findPoz(c));
		return true;
	}
	catch (CarteRepoException&) { return false; }
}


int CarteRepo::findPoz(const Carte& c) {
	int i = 0;
	for (const Carte& carte : all) {
		if (carte.getTitlu() == c.getTitlu() && carte.getAutor() == c.getAutor()) {
			return i;
		}
		i++;
	}
	throw CarteRepoException("Nu exista carte cu acest titlu si acest autor. ");
}
/*
* Cauta cartea
* arunca o exceptie daca nu exista cartea
*/
const Carte& CarteRepo::find(string titlu, string autor) {
	vector<Carte>::iterator f = std::find_if(this->all.begin(), this->all.end(),
		[=](const Carte& c) {
			return c.getTitlu() == titlu && c.getAutor() == autor;
		});

	if (f != this->all.end())
		return (*f);
	else
		throw CarteRepoException("Nu exista carte cu acest titlu si acest autor.");
}
bool CarteRepo::modificaCarte(const Carte& c) {
	try {
		const int poz = findPoz(c);
		all[poz] = c;
		return true;
	}
	catch (CarteRepoException&) {
		return false;
	}
}

/*
* returneaza toate cartile salvate
*/
const vector<Carte> CarteRepo::getAll() {
	return all;
}

ostream& operator<<(ostream& out, const CarteRepoException& ex) {
	out << ex.msg;
	return out;
}


/// pt fisiere


void RepositoryFile::loadfromfile() {
	ifstream fin(nume_fisier);
	this->emptyRepo();
	if (!fin.is_open()) {
		throw (CarteRepoException("Eroare la deschiderea fisierukui"));
	}
	while (!fin.eof()) {
		string titlu, autor, gen;
		int an;

		if (fin.eof())break;
		fin >> titlu;
		fin >> autor;
		fin >> gen;
		fin >> an;
		Carte c(titlu, autor, gen, an);
		CarteRepo::store(c);
	}

	fin.close();
}

void RepositoryFile::save() {
	ofstream fout(nume_fisier);
	if (!fout.is_open()) {
		throw CarteRepoException("Eroare la deschiderea fisierului.");

	}

	for (auto& carte : CarteRepo::getAll()) {
		fout << "\n" << carte.getTitlu() << " " << carte.getAutor() << " " << carte.getGen() << " " << carte.getAn();
	}

	fout.close();
}
void testAdd() {
	CarteRepo repo;
	repo.store(Carte{ "titlu", "autor", "gen" , 2010 });
	assert(repo.getAll().size() == 1);
	assert(repo.find("titlu", "autor").getAn() == 2010);
	repo.store(Carte{ "titlu1", "autor1", "gen1" , 2021 });
	assert(repo.getAll().size() == 2);

	try {
		repo.store(Carte{ "titlu", "autor", "gen" , 2010 });assert(false);
	}
	catch (const CarteRepoException&) {
		assert(true);
	}

	try {
		repo.find("titlu10", "autor");assert(false);
	}
	catch (const CarteRepoException& ex) {
		stringstream os;
		os << ex;
		assert(os.str().find("exista") >= 0);

	}
}

void testCauta() {
	CarteRepo repo;
	repo.store(Carte{ "titlu", "autor", "gen" , 2010 });
	Carte c = repo.find("titlu", "autor");
	assert(c.getGen() == "gen");
	assert(c.getAn() == 2010);
	repo.store(Carte{ "titlu1", "autor1", "gen1" , 2021 });

	try {
		repo.find("titlu10", "autor10");assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}

}



///////////PENTRU REPO LAB


void RepoLab::store(const Carte& c)
{
	all = getAll();
	/*if (exist(c)) {
		throw CarteRepoException("Exista deja o alta carte: " + c.getTitlu() + " | " + c.getAutor());

	}
	all.push_back(c);*/
	int rn = rand() % 1;
	if (rn < this->k) {
		throw std::exception("exception");
	}
	else {
		all_map.insert({ this->k, c });
		k++;
		//all.push_back(c);
	}


}

bool RepoLab::exist(const Carte& c) {
	all = getAll();
	try {
		find(c.getTitlu(), c.getAutor());
		return true;
	}
	catch (CarteRepoException&) {
		return false;
	}

}
bool RepoLab::deleteCarte(const Carte& c) {
	all = getAll();
	/*try {
		all.erase(all.begin() + findPoz(c));
		return true;
	}
	catch (CarteRepoException&) { return false; }*/

	int rn = rand() % 1;
	if (rn < this->k) {
		throw std::exception("exception");
	}
	else {
		all.erase(all.begin() + findPoz(c));
		return true;

	}
}


int RepoLab::findPoz(const Carte& c) {
	all = getAll();

	int rn = rand() % 1;
	if (rn < this->k) {
		throw std::exception("exception");
	}
	else {
		int i = 0;
		for (const Carte& carte : all) {
			if (carte.getTitlu() == c.getTitlu() && carte.getAutor() == c.getAutor()) {
				return i;
			}
			i++;
		}
		return i;
	}
}
/*for (const Carte& carte : all) {
	if (carte.getTitlu() == c.getTitlu() && carte.getAutor() == c.getAutor()) {
		return i;
	}
	i++;
}
throw CarteRepoException("Nu exista carte cu acest titlu si acest autor. ");*/
/*
* Cauta cartea
* arunca o exceptie daca nu exista cartea
*/
const Carte& RepoLab::find(string titlu, string autor) {

	/*vector<Carte>::iterator f = std::find_if(this->all.begin(), this->all.end(),
		[=](const Carte& c) {
			return c.getTitlu() == titlu && c.getAutor() == autor;
		});

	if (f != this->all.end())
		return (*f);
	else
		throw CarteRepoException("Nu exista carte cu acest titlu si acest autor.");*/
	all = getAll();

	int rn = rand() % 1;
	if (rn < this->k) {
		throw("exception");
	}
	else {
		vector<Carte>::iterator f = std::find_if(this->all.begin(), this->all.end(),
			[=](const Carte& c) {
				return c.getTitlu() == titlu && c.getAutor() == autor;
			});

		return (*f);
	}

}
bool RepoLab::modificaCarte(const Carte& c) {

	all = getAll();
	/*try {
		const int poz = findPoz(c);
		all[poz] = c;
		return true;
	}
	catch (CarteRepoException&) {
		return false;
	}*/

	int rn = rand() % 1;
	if (rn < this->k) {
		throw("exception");
	}
	else {

		const int poz = findPoz(c);
		all[poz] = c;
		return true;
	}
}

/*
* returneaza toate cartile salvate
*/
const vector<Carte> RepoLab::getAll() {
	for (auto i : all_map)
		all.push_back(i.second);
	return all;
}

void testFindPoz() {
	CarteRepo repo;
	repo.store(Carte{ "titlu", "autor", "gen" , 2010 });
	Carte c = Carte{ "titlu", "autor", "gen" , 2010 };
	int poz = repo.findPoz(c);
	assert(poz == 0);
	repo.store(Carte{ "titlu1", "autor1", "gen1" , 2021 });
	Carte c1 = Carte{ "titlu1", "autor1", "gen1" , 2021 };
	poz = repo.findPoz(c1);
	assert(poz == 1);
	try {
		Carte c2 = Carte{ "titlu99", "autor1", "gen1" , 2021 };
		poz = repo.findPoz(c2);assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testDeleteCarte() {
	CarteRepo repo;
	repo.store(Carte{ "titlu", "autor", "gen" , 2010 });
	repo.store(Carte{ "titlu1", "autor1", "gen1" , 2021 });
	assert(repo.getAll().size() == 2);
	bool rez = repo.deleteCarte(Carte{ "titlu", "autor", "gen" , 2010 });
	assert(rez == true);
	assert(repo.getAll().size() == 1);
	try {
		rez = repo.deleteCarte(Carte{ "titlu100", "autor7", "gen" , 2010 });
	}
	catch (CarteRepoException&) { assert(true); }


}

void testModificaCarte() {
	CarteRepo repo;
	repo.store(Carte{ "titlu", "autor", "gen" , 2010 });
	repo.store(Carte{ "titlu1", "autor1", "gen1" , 2021 });
	assert(repo.getAll().size() == 2);
	bool rez = repo.modificaCarte(Carte{ "titlu", "autor", "gen20" , 2022 });
	assert(rez == true);
	rez = repo.modificaCarte(Carte{ "titlu100", "autor7", "gen" , 2010 });
	assert(rez == false);
}

void testFileRepo() {
	RepositoryFile repo("test.txt");
	repo.getAll();
	repo.store(Carte{ "titlu100", "autor100", "gen100", 2019 });
	bool rez = repo.modificaCarte(Carte{ "titlu100", "autor100", "gen20" , 2022 });
	rez = repo.deleteCarte(Carte{ "titlu100", "autor100", "gen20" , 2022 });
}
void teste_repo() {
	testAdd();
	testCauta();
	testDeleteCarte();
	testFindPoz();
	testModificaCarte();
	testFileRepo();
}