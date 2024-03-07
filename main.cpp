//#define _CRTDBG_MAP_ALLOC
#include "QtWidgetsApplication3.h"
#include "Carte_GUI.h"
#include<QtWidgets/QApplication>
#include "CarteGUIModel.h"
#include "Cos_GUI.h"

#include <stdlib.h>
//#include <crtdbg.h>
#include "console.h"

void testAll() {
	testValidator();
	teste_repo();
	teste_service();
}

/**void ignition() {
	testAll();
	//RepoLab repo{ 0.5 };
	CarteRepo repo;
	//RepositoryFile repo("repository.txt");
	CarteValidator val;
	CarteService srv{ repo, val };
	ConsoleUI ui{ srv };
	ui.start();
}
*
int main() {
	ignition();
	_CrtDumpMemoryLeaks();
	return 0;
}*/

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//CarteRepo repo;
	RepositoryFile repo{ "Repository.txt" };
	CarteValidator val;
	CarteService srv{ repo, val };
	CarteGUI gui{ srv };
	//CarteGUIModel gui{ srv };
//	gui.move(100, 100);

	//CosGUICuTabel cos{ srv };
	//cos.move(900, 100);
	//cos.show();
	gui.show();

	return a.exec();
}