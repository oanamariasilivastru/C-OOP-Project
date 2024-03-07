#pragma once
#include "Carte.h"
#include "Undo.h"
#include "carte_repo.h"
#include "Inchirieri.h"
#include <functional>
#include "validator.h"
#include <map>
#include "Observer.h"
using std::function;

class CarteService {
	RepoAbstract& repo;
	CarteValidator& val;
	InchirieriList currentList;
	vector<ActiuneUndo*>actiuniUndo;

public:
	CarteService(RepoAbstract& repo, CarteValidator& val) noexcept : repo{ repo }, val{ val } {}
	//Nu permitem copierea de obiecte Carte
	CarteService(const CarteService& ot) = delete;
	void filtreazaCount(std::map<std::string, std::vector<Carte>>& dict) const noexcept;
	/*
	* returneaza toate cartile in ordinea in care au fost adaugate
	*/
	const vector<Carte> getAll() noexcept {
		return repo.getAll();
	}
	/*
	* Adauga o noua carte
	*
	* @param titlu: string
	* @param autor: string
	* @param gen: string
	* @param an: int
	*
	* Arunca exceptie daca exista deja o carte cu acelasi titlu si acelasi autor sau
	* daca datele nu sunt valide
	*/
	void addCarte(const string& titlu, const string& autor, const string& gen, int an);
	/* Sterge cartea cu titlu si autorul dat
	*
	* param titlu: string
	* @param autor: string
	* @param gen: string
	* @param an: int
	*
	*/
	bool deleteCarte(const string& titlu, const string& autor, const string& gen, int an);
	/*
	* Modifica cartea data
	*
	* param titlu: string
	* @param autor: string
	* @param gen: string
	* @param an: int
	*/
	bool modificaCarte(const string& titlu, const string& autor, const string& gen, int an);
	/*
	Filtreaza lista de carti pe baza unui criteriu

	@param fct: functia dupa care se filtreaza lista de carti
	@return: lista cu cartile care indeplinesc criteriul dat
	*/
	vector<Carte> filter(function<bool(const Carte&)> fct);

	/*
	* Returneaza o lista de carti cu titlul dat
	*
	* @param titlu: titlu dupa care se filtreaza
	* @return: lista cu cartile care au titlul dat
	* (vector cu elemente de tip Carte)
	*/
	vector<Carte> filtrareTitlu(string titlu);

	/*
	* Returneaza o lista de carti cu anul dat
	*
	* @param an: anul dupa care se filtreaza
	* @return: lista cu cartile care au anul dat
	* (vector cu elemente de tip Carte)
	*/
	vector<Carte> filtrareAn(int an);

	/*
	* Functie de sortare proprie
	*
	* @param maiMicF: functia de comparare folosita pentru sortare
	*
	* @return: lista de carti sortata dupa criteriul dat (vector cu elemente de
	*			tip Carte)
	*/
	vector<Carte> generalSort(bool(*maiMicF)(const Carte&, const Carte&));

	/*
	* Sorteaza cartile dupa titlu
	*
	* @return: lista cu cartile sortate dupa titlu
	*/
	vector<Carte> sortTitlu();

	/*
	* Sorteaza cartile dupa autor
	*
	* @return: lista cu cartile sortate dupa autor
	*/
	vector<Carte> sortAutor();

	/*
	* Sorteaza cartile dupa an si gen
	*
	* @return: lista cu cartile sortate dupa an si gen
	*/
	vector<Carte> sortAnGen();

	/*
	* Adauga o melodie cu titlu titlu si artist artist in playlist
	*
	* @param titlu: titlul melodiei care se adauga (string)
	* @param artist: artistul melodiei care se adauga (string)
	*
	* post: melodia este adaugata la playlist
	* @throws: RepoException daca nu exista melodie cu titlu si artist dat
	*/
	void addToInchiriere(string titlu, string autor);

	/*
	* Adauga un numar random de melodii in playlist
	*
	* @param howMany: cate melodii se adauga (int)
	*
	* @return: numarul de melodii adaugate in playlist
	* post: se adauga un numar random de melodii in playlist
	*/
	int addRandomToCarti(int howMany);

	/*
	* Elimina toate melodiile din playlist
	* post: playlist-ul nu contine nicio melodie
	*/
	void emptyInchiriere();
	void undo();

	void exportcos(string fisier);
	/*
	* Returneaza un vector cu toate melodiile din playlist
	*/
	const vector<Carte>& getInchiriereList();

	void creareMap();

	InchirieriList& getInchiriere() {
		return this->currentList;
	}


};

void teste_service();

