#include "validator.h"
#include <assert.h>
#include <sstream>

void CarteValidator::validate(const Carte& c) {
	vector<string> msgs;
	if (c.getTitlu().size() < 2) msgs.push_back("Titlu vid!");
	if (c.getAutor().size() < 2) msgs.push_back("Autor vid!");
	if (c.getGen().size() < 2) msgs.push_back("Gen vid!");
	if (c.getAn() < 1900) msgs.push_back("Anul trebuie sa fie mai mare de 1900!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	CarteValidator v;
	Carte c{ "", "", "", -1 };
	try {
		v.validate(c);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);

	}
}