#pragma once
#include "Carte.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;
class InchirieriList : public Observable{
private:
	vector<Carte> InchirieriCarte;
public:
	InchirieriList() = default;

	/*
	Adauga o carte la retela
	@param c:cartea care se adauga

	post:cartea va si afaugat la inchiriere
	*/
	void addCartetoInchiriere(const Carte& c);

	/*
	* Elimina toate cartile din inchiriere
	*
	*/

	void emptyList();

	/*
	Adauga un numar random de carti la inchiriere

	@param originalCarte: cartile din care se alege
	@param howMany: cate carti se adauga

	post: cartile sunt adaugate la inchiriere
	*/
	void addRandomCarti(vector<Carte> originalCarte, int howMany);

	/*
	Returneaza un vector care contine toate cartile din inchiriere
	*/
	const vector<Carte>& getAllInchirieri();
};