#include"Carte.h"
#include<assert.h>
#include<string.h>
bool cmpTitlu(const Carte& c1, const Carte& c2) {
	return c1.getTitlu() < c2.getTitlu();
}

bool cmpAutor(const Carte& c1, const Carte& c2) {
	return c1.getAutor() < c2.getAutor();
}

bool cmpAnGen(const Carte& c1, const Carte& c2) {
	if (c1.getAn() == c2.getAn())
		return c1.getGen() < c2.getGen();
	else
		return c1.getAn() < c2.getAn();
}