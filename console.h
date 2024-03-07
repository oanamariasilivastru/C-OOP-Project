#pragma once
#include "Carte.h"
#include "carte_service.h"
class ConsoleUI {
	CarteService& srv;
	/*
	* Citeste datele de la tastatura si adauga Carte
	* arunca exceptie daca exista deja o carte cu acelasi titlu si acelasi autor
	* sau daca datele nu sunt valide
	*/
	void adaugaUI();
	/*
	* Tipareste o lista de carti la consola
	*/
	void tipareste(const vector<Carte>& carti);

	void stergeUI();

	void modificaUI();

	void uiFilter();

	void uiSort();

	void uiExport();

public:
	ConsoleUI(CarteService& srv) noexcept : srv{ srv } {};

	//nu permitem copierea obiectelor
	ConsoleUI(const ConsoleUI& ot) = delete;

	void uiInchirieriList();

	void addDefaultCarti();

	void printInchirieriMenu();

	void uiAddToList();

	void uiRandomToList();

	void uiEmptyList();

	void uiUndo();

	void start();
};