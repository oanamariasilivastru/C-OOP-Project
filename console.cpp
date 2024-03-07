#include "console.h"

#include "Carte.h"
#include <iostream>
#include <string>
using namespace std;

void ConsoleUI::tipareste(const vector<Carte>& carti) {
	cout << "Carti:\n";
	for (const auto& carte : carti) {
		cout << "Titlu: " << carte.getTitlu() << " | " << "Autor: " << carte.getAutor() << " | " << "Gen: " << carte.getGen() << " | " << "Anul apartiei: " << carte.getAn() << "\n";


	}
}

void ConsoleUI::uiExport() {
	string fisier;
	cout << "Nume fisier: ";
	cin >> fisier;
	if (fisier.size() > 4) {
		string extensie = fisier.substr(fisier.size() - 5, 5);
		if (extensie == ".html") {
			srv.exportcos(fisier);
			cout << "Export efectuat!\n";
			cout << srv.getAll().size() << endl;

		}
		else {
			cout << "Nu ati dat un fisier html!\n";
		}
	}

	else
		cout << "Nu ati dat un fisier valid html!\n";
}
void ConsoleUI::uiUndo() {
	try {
		srv.undo();
		cout << "Undo realizat cu succes!\n";
	}
	catch (exception&) {
		cout << "Nu se mai poate face undo!\n";
	}
}

void ConsoleUI::adaugaUI() {
	std::string titlu, autor, gen;
	int an;

	cout << "Dati titlu: ";
	getline(cin >> ws, titlu);
	cout << "Dati autor: ";
	getline(cin >> ws, autor);
	cout << "Dati gen: ";
	getline(cin >> ws, gen);
	cout << "Dati an:";
	cin >> an;
	srv.addCarte(titlu, autor, gen, an);
	cout << "Carte adaugata cu succes!\n";

}

void ConsoleUI::stergeUI() {
	string titlu, autor, gen;
	int an;
	cout << "Dati titlu: ";
	getline(cin >> ws, titlu);
	cout << "Dati autor: ";
	getline(cin >> ws, autor);
	cout << "Dati gen: ";
	getline(cin >> ws, gen);
	cout << "Dati an:";
	cin >> an;
	const bool rez = srv.deleteCarte(titlu, autor, gen, an);

	if (rez == true) {
		cout << "Carte stearsa cu succes!\n";
	}
	else
		cout << "Nu s-a reusit stergerea!\n";
}

void ConsoleUI::modificaUI() {
	string titlu, autor, gen;
	int an;
	cout << "Dati titlu: ";
	getline(cin >> ws, titlu);
	cout << "Dati autor: ";
	getline(cin >> ws, autor);
	cout << "Dati noul gen: ";
	getline(cin >> ws, gen);
	cout << "Dati noul an:";
	cin >> an;
	const bool rez = srv.modificaCarte(titlu, autor, gen, an);
	if (rez == true) {
		cout << "Carte modificata cu succes!\n";
	}
	else
		cout << "Nu s-a reusit modificarea!\n";

}

void ConsoleUI::uiFilter() {
	string criteriu;
	cout << "Criteriul de filtrare este (titlu/anul aparitiei)";
	cin >> criteriu;

	if (criteriu == "titlu")
	{
		cout << "Titlul pentru care se filtreaza cartile: " << endl;
		string searchedTitlu;
		cin >> searchedTitlu;
		tipareste(srv.filtrareTitlu(searchedTitlu));
	}
	else if (criteriu == "an") {
		cout << "Anul pentru care se filtreaza cartile: " << endl;
		int searchedAn;
		cin >> searchedAn;
		tipareste(srv.filtrareAn(searchedAn));
	}
	else
		cout << "Nu se poate filtra dupa criteriul dat." << endl;



}
void ConsoleUI::uiSort() {
	cout << "Criteriul de sortare este (titlu/autor/anul aparitiei + gen)";
	string criteriu;
	cin >> criteriu;
	if (criteriu == "titlu")
		tipareste(srv.sortTitlu());
	else {
		if (criteriu == "autor")
			tipareste(srv.sortAutor());
		else if (criteriu == "an + gen")
			tipareste(srv.sortAnGen());
		else
			cout << "Nu se poate sorta dupa criteriul dat." << endl;
	}
}

void ConsoleUI::uiAddToList() {
	string titlu, autor;
	cout << "Tiltul cartii este: ";
	getline(cin >> ws, titlu);

	cout << "Autorul cartii este; ";
	getline(cin >> ws, autor);
	try {
		srv.addToInchiriere(titlu, autor);
		cout << "Carte adaugata cu succes" << endl;
	}
	catch (CarteRepoException& ex) {
		cout << ex;
	}
	catch (ValidateException& ex) {
		cout << ex;
	}
}

void ConsoleUI::uiRandomToList() {
	int howManyToAdd;
	cout << "Cate carti sa se adauge? ";
	cin >> howManyToAdd;
	try {
		int howManyAdded = srv.addRandomToCarti(howManyToAdd);
		cout << "S-au adaugat " << howManyAdded << " carti la inchiriere" << endl;
	}
	catch (CarteRepoException& ex) {
		cout << ex;

	}
}

void ConsoleUI::uiEmptyList() {
	srv.emptyInchiriere();
	cout << "S-au sters toate cartile din inchirierea curenta" << endl;
}



void ConsoleUI::addDefaultCarti() {
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

}
void ConsoleUI::uiInchirieriList() {
	int cmd;
	int runningList = 1;
	while (runningList) {
		printInchirieriMenu();
		cout << "Introduceti optiunea: " << endl;
		cin >> cmd;
		switch (cmd) {
		case 1:
			uiAddToList();
			break;

		case 2:
			uiRandomToList();
			break;
		case 3:
			uiEmptyList();
			break;
		case 4:
			tipareste(srv.getInchiriereList());
			break;
		case 0:
			runningList = 0;
			break;
		default:
			break;
		}
	}
}
void ConsoleUI::printInchirieriMenu() {
	cout << endl;
	cout << "MENIU INCHIRIERI" << endl;
	cout << "1 - Adauga carti in cos " << endl;
	cout << "2 - Adauga carti random in cos" << endl;
	cout << "3 - Goleste cosul" << endl;
	cout << "4 - Tipareste cosul" << endl;
	cout << "0 - Inapoi la meniul principal" << endl;
	cout << endl;
}
void ConsoleUI::start() {
	/*try {
		addDefaultCarti();
	}
	catch (const CarteRepoException& ex) {
		cout << ex << "\n";
	}
	catch (const ValidateException& ex) {
		cout << ex << "\n";
	}*/

	while (true) {
		cout << "Meniu:\n";
		cout << "1 - Adauga carte\n2 - Tipareste\n3 - Sterge carte\n4 - Modifica carte\n";
		cout << "5 - Filtrare carti\n6 - Sortare carti\n";
		cout << "7 - Cos Inchirieri\n";
		cout << "8 - Undo\n";
		cout << "9- Export cos inchirieri\n";
		cout << "0 - Iesire\n";
		cout << "Dati comanda: ";
		int cmd;
		cin >> cmd;
		try {
			switch (cmd)
			{
			case 1:
				adaugaUI();
				break;
			case 2:
				tipareste(srv.getAll());
				break;
			case 3:
				stergeUI();
				break;
			case 4:
				modificaUI();
				break;
			case 5:
				uiFilter();
				break;
			case 6:
				uiSort();
				break;
			case 7:
				uiInchirieriList();
				break;
			case 8:
				uiUndo();
				break;
			case 9:
				uiExport();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida\n";
				break;
			}
		}
		catch (const CarteRepoException& ex) {
			cout << ex << "\n";
		}
		catch (const ValidateException& ex) {
			cout << ex << "\n";
		}
		catch (const exception) {
			cout << "Eroare!\n";
		}
	}
}

