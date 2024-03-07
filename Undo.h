#pragma once
#include "Carte.h"
#include "carte_repo.h"
#include<iostream>

using namespace std;

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	RepoAbstract& repo;
	Carte c_adaugata; //cartea adaugata
public:
	UndoAdauga(RepoAbstract& r, Carte c) : repo{ r }, c_adaugata{ c } {} //constructorul
	void doUndo() {
		repo.deleteCarte(c_adaugata);
	}
};

class UndoSterge : public ActiuneUndo {
private:
	RepoAbstract& repo; //repository carti
	Carte c_stearsa; //Cartea stearsa
public:
	UndoSterge(RepoAbstract& r, Carte c) : repo{ r }, c_stearsa{ c } {}

	void doUndo() {
		repo.store(c_stearsa);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	RepoAbstract& repo; //Repository cartilor
	Carte c_inainte; //Cartea de dinainte de modificare
	Carte c_dupa;    // Cartea de dupa stergere
public:
	//Constructorul

	UndoModifica(RepoAbstract& r, Carte c1, Carte c2) : repo{ r }, c_inainte{ c1 }, c_dupa{ c2 } {}

	void doUndo() {
		repo.deleteCarte(c_dupa);
		repo.store(c_inainte);
	}
};