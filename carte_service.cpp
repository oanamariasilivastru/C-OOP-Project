#include "carte_service.h"
#include "Undo.h"
#include <functional>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <map>

using std::ostream;
using std::stringstream;
using std::sort;


void CarteService::filtreazaCount(std::map<std::string, std::vector<Carte>>& dict) const noexcept {
	vector<Carte> carte = repo.getAll();
	for (Carte c : carte) {
		std::string gen = c.getGen();
		auto it = dict.find(gen);
		if (it == dict.end()) {
			std::vector<Carte> carti;
			carti.push_back(c);
			dict.insert({ gen, carti });
		}
		else
			dict[gen].push_back(c);
	}
	
}

void CarteService::exportcos(string fisier) {
	ofstream fout(fisier);
	vector<Carte>carte = currentList.getAllInchirieri();
	for (auto& el : carte) {
		fout << el.getTitlu() << " | " << el.getAutor() << " | " << el.getGen() << " | " << el.getAn() << "\n";
	}
	fout.close();

}
void CarteService::addCarte(const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ titlu, autor, gen, an };
	val.validate(c);
	repo.store(c);
	actiuniUndo.push_back(new UndoAdauga(repo, c));
}
bool CarteService::deleteCarte(const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ titlu, autor, gen, an };
	val.validate(c);
	const bool rezultat = repo.deleteCarte(c);
	if (rezultat == true) {
		actiuniUndo.push_back(new UndoSterge(repo, c));
	}
	return rezultat;
}

bool CarteService::modificaCarte(const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ titlu, autor, gen, an };
	val.validate(c);
	Carte aux = repo.find(titlu, autor);
	const bool rezultat = repo.modificaCarte(c);
	if (rezultat == true) {
		actiuniUndo.push_back(new UndoModifica(repo, aux, c));
	}
	return rezultat;
}

/*vector <Carte> CarteService::filter(function<bool(const Carte&)> fct) {
	vector<Carte> filteredCarti;
	for (const auto& carte : repo.getAll()) {
		if (fct(carte)) {
			filteredCarti.push_back(carte);
		}
	}
	return filteredCarti;
}*/
vector <Carte> CarteService::filtrareAn(int an) {
	const vector <Carte>& carti = repo.getAll();
	vector <Carte> filteredCarti;
	std::copy_if(carti.begin(), carti.end(), back_inserter(filteredCarti),
		[an](const Carte& c) {
			return c.getAn() == an;
		});
	return filteredCarti;
}
vector<Carte> CarteService::filtrareTitlu(string titlu) {
	const vector <Carte>& carti = repo.getAll();
	vector <Carte> filteredCarti;
	std::copy_if(carti.begin(), carti.end(), back_inserter(filteredCarti),
		[titlu](const Carte& c) {
			return c.getTitlu() == titlu;
		});
	return filteredCarti;
}

vector<Carte> CarteService::sortTitlu() {
	vector<Carte> SortedCopy = repo.getAll();
	sort(SortedCopy.begin(), SortedCopy.end(), cmpTitlu);
	return SortedCopy;
}

vector<Carte> CarteService::sortAutor() {
	auto SortedCopy = repo.getAll();
	sort(SortedCopy.begin(), SortedCopy.end(), cmpAutor);
	return SortedCopy;
}

vector<Carte> CarteService::sortAnGen() {
	auto SortedCopy = repo.getAll();
	sort(SortedCopy.begin(), SortedCopy.end(), cmpAnGen);
	return SortedCopy;
}

void CarteService::addToInchiriere(string titlu, string autor) {
	const auto& carte = repo.find(titlu, autor);currentList.addCartetoInchiriere(carte);
}

const vector<Carte>& CarteService::getInchiriereList() {
	return currentList.getAllInchirieri();
}

int CarteService::addRandomToCarti(int howMany) {
	currentList.addRandomCarti(this->getAll(), howMany);
	return (int)currentList.getAllInchirieri().size();
}

void CarteService::emptyInchiriere() {
	currentList.emptyList();
}

void CarteService::undo() {
	if (actiuniUndo.size() == 0)
		throw(exception("Nu se poate face undo!"));

	actiuniUndo.back()->doUndo();
	delete actiuniUndo.back();
	actiuniUndo.pop_back();
}


void testaddCarte() {
	CarteRepo repo;
	CarteValidator val;
	CarteService srv{ repo, val };
	srv.addCarte("titlu1", "autor1", "gen1", 2010);
	assert(srv.getAll().size() == 1);
	srv.undo();
	assert(true);
	try {
		srv.undo();
	}
	catch (exception) {
		assert(true);
	}
	srv.addCarte("titlu1", "autor1", "gen1", 2010);


	try {
		srv.addCarte("titlu1", "autor1", "gen1", -1900);assert(false);
	}
	catch (const ValidateException&) { assert(true); }
	try {
		srv.addCarte("titlu1", "autor1", "gen1", 2010);assert(false);
	}
	catch (const CarteRepoException&) { assert(true); }
}


void testdeleteCarte() {
	CarteRepo repo;
	CarteValidator val;
	CarteService srv{ repo, val };
	srv.addCarte("titlu1", "autor1", "gen1", 2010);
	assert(srv.getAll().size() == 1);
	bool rez = srv.deleteCarte("titlu1", "autor1", "gen1", 2010);
	srv.undo();
	assert(srv.getAll().size() == 1);
	assert(rez == true);
	rez = srv.deleteCarte("titlu10", "autor1", "gen1", 2010);

	//assert(rez == false);
}

void testmodificaCarte() {
	CarteRepo repo;
	CarteValidator val;
	CarteService srv{ repo, val };
	srv.addCarte("titlu1", "autor1", "gen1", 2010);
	assert(srv.getAll().size() == 1);
	bool rez = srv.modificaCarte("titlu1", "autor1", "gen10", 2022);
	srv.undo();
	assert(rez == true);
}
void testFilterService() {
	CarteRepo testRepo;
	CarteValidator testVal;
	CarteService srv{ testRepo, testVal };

	srv.addCarte("Un basm", "Stephen King", "SF", 2016);
	srv.addCarte("26 Kisses", "Anna Michels", "Dragoste", 2016);
	srv.addCarte("Theodoros", "Mircea Cartarescu", "Comic", 2022);
	srv.addCarte("Viata lui Pi", "Yann Martel", "SF", 2020);
	srv.addCarte("Circul Noptii", "Stephen King", "Fantasy", 2019);
	srv.addCarte("Dune", "Frank Herbert", "SF", 2010);
	srv.addCarte("Casa fulgerului", "Frank Herbert", "SF", 2022);
	srv.addCarte("Secera", "Neal Shusterman", "Distopie", 2008);
	srv.addCarte("1984", "George Orwell", "Distopie", 2013);
	srv.addCarte("Coraline", "Neil Gaiman", "SF", 2020);

	vector<Carte> cartiFiltrate = srv.filtrareAn(2013);
	cartiFiltrate = srv.filtrareTitlu("Dune");
	srv.emptyInchiriere();
	try {
		srv.addToInchiriere("Titlu", "Autor");assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}

}

void testSortService() {
	CarteRepo testRepo;
	CarteValidator testVal;
	CarteService srv{ testRepo, testVal };

	srv.addCarte("Un basm", "Stephen King", "SF", 2016);
	srv.addCarte("26 Kisses", "Anna Michels", "Dragoste", 2016);
	srv.addCarte("Theodoros", "Mircea Cartarescu", "Comic", 2022);
	srv.addCarte("Viata lui Pi", "Yann Martel", "SF", 2020);
	srv.addCarte("Circul Noptii", "Stephen King", "Fantasy", 2019);
	srv.addCarte("Dune", "Frank Herbert", "SF", 2010);
	srv.addCarte("Casa fulgerului", "Frank Herbert", "SF", 2022);
	srv.addCarte("Secera", "Neal Shusterman", "Distopie", 2008);
	srv.addCarte("1984", "George Orwell", "Distopie", 2013);
	srv.addCarte("Coraline", "Neil Gaiman", "SF", 2020);

	vector<Carte> cartiSortate = srv.sortTitlu();
	cartiSortate = srv.sortAnGen();
	cartiSortate = srv.sortAutor();

}

void test_inchiriere() {
	CarteRepo testRepo;
	CarteValidator testVal;
	CarteService srv{ testRepo, testVal };

	srv.addCarte("Un basm", "Stephen King", "SF", 2016);
	srv.addCarte("26 Kisses", "Anna Michels", "Dragoste", 2016);
	srv.addCarte("Theodoros", "Mircea Cartarescu", "Comic", 2022);
	srv.addCarte("Viata lui Pi", "Yann Martel", "SF", 2020);
	srv.addCarte("Circul Noptii", "Stephen King", "Fantasy", 2019);
	srv.addCarte("Dune", "Frank Herbert", "SF", 2010);
	srv.addCarte("Casa fulgerului", "Frank Herbert", "SF", 2022);
	srv.addCarte("Secera", "Neal Shusterman", "Distopie", 2008);
	srv.addCarte("1984", "George Orwell", "Distopie", 2013);
	srv.addCarte("Coraline", "Neil Gaiman", "SF", 2020);

	srv.addRandomToCarti(4);
	assert(srv.getInchiriereList().size() == 4);
	srv.addToInchiriere("Un basm", "Stephen King");



}

void test_export() {
	CarteRepo testRepo;
	CarteValidator testVal;
	CarteService srv{ testRepo, testVal };

	srv.addCarte("Un basm", "Stephen King", "SF", 2016);
	srv.addCarte("26 Kisses", "Anna Michels", "Dragoste", 2016);
	srv.addCarte("Theodoros", "Mircea Cartarescu", "Comic", 2022);
	srv.addCarte("Viata lui Pi", "Yann Martel", "SF", 2020);
	srv.addCarte("Circul Noptii", "Stephen King", "Fantasy", 2019);
	srv.addCarte("Dune", "Frank Herbert", "SF", 2010);
	srv.addCarte("Casa fulgerului", "Frank Herbert", "SF", 2022);
	srv.addCarte("Secera", "Neal Shusterman", "Distopie", 2008);
	srv.addCarte("1984", "George Orwell", "Distopie", 2013);
	srv.addCarte("Coraline", "Neil Gaiman", "SF", 2020);

	srv.addRandomToCarti(10);
	assert(srv.getInchiriereList().size() == 10);
	srv.exportcos("test.html");
}
void teste_service() {
	testaddCarte();
	testdeleteCarte();
	testmodificaCarte();
	testFilterService();
	testSortService();
	test_inchiriere();
	test_export();
}