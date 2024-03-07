#include "Inchirieri.h"
using std::shuffle;

void InchirieriList::addCartetoInchiriere(const Carte& c) {
	this->InchirieriCarte.push_back(c);
	notify();
}

void InchirieriList::emptyList() {
	this->InchirieriCarte.clear();
	notify();
}

void InchirieriList::addRandomCarti(vector<Carte> originalCarte, int howMany) {
	shuffle(originalCarte.begin(), originalCarte.end(), std::default_random_engine(std::random_device{}()));
	while (InchirieriCarte.size() < howMany && originalCarte.size() > 0) {
		InchirieriCarte.push_back(originalCarte.back());
		originalCarte.pop_back();
	}
	notify();
}

const vector<Carte>& InchirieriList::getAllInchirieri() {
	return this->InchirieriCarte;
}