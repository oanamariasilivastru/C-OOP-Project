#include "CarteGUIModel.h"

void CarteGUIModel::initializeGUIComponents() {


	lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editTitlu = new QLineEdit;
	editAutor = new QLineEdit;
	editGen = new QLineEdit;
	editAn = new QLineEdit;

	lyForm->addRow(lblTitlu, editTitlu);
	lyForm->addRow(lblAutor, editAutor);
	lyForm->addRow(lblGen, editGen);
	lyForm->addRow(lblAn, editAn);
	buttonAddCarte = new QPushButton("Adauga carte");
	buttonDeleteCarte = new QPushButton("Sterge carte");
	buttonModifyCarte = new QPushButton("Modifica carte");

	lyForm->addWidget(buttonAddCarte);
	lyForm->addWidget(buttonDeleteCarte);
	lyForm->addWidget(buttonModifyCarte);

	lyLeft->addWidget(form);


	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSortTitlu);
	lyRadioBox->addWidget(radioSortAutor);
	lyRadioBox->addWidget(radioSortGenAn);

	buttonSortCarti = new QPushButton("Sorteaza carti");
	lyRadioBox->addWidget(buttonSortCarti);

	lyLeft->addWidget(groupBox);

	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterTitlu = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterTitlu);
	buttonFilterCarti1 = new QPushButton("Filtreaza carti dupa titlu");
	lyFormFilter->addWidget(buttonFilterCarti1);
	buttonFilterCarti2 = new QPushButton("Filtreaza carti dupa an");
	lyFormFilter->addWidget(buttonFilterCarti2);
	lyLeft->addWidget(formFilter);

	butoane = new QWidget;
	lyButoane = new QVBoxLayout;
	butoane->setLayout(lyButoane);
	lyRight->addWidget(butoane);

	buttonUndo = new QPushButton("Undo");
	buttonReloadData = new QPushButton("Reload data");
	btnCos = new QPushButton("Cos");

	lyLeft->addWidget(buttonUndo);
	lyLeft->addWidget(buttonReloadData);
	lyLeft->addWidget(btnCos);

	//QWidget* right = new QWidget;
	//QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	/*int noLines = 20;
	int noColumns = 4;
	this->tableCarti = new QTableWidget{ noLines, noColumns };

	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Autor" << "Gen" << "An";
	this->tableCarti->setHorizontalHeaderLabels(tblHeaderList);

	this->tableCarti->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	lyRight->addWidget(tableCarti);*/

	//list = new QListWidget;
	//lyRight->addWidget(list);
	model = new MyTableModel{ srv.getAll() };
	this->tableCarti->setModel(model);
	this->tableCarti->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lyRight->addWidget(tableCarti);

	reloadDynamicButtons();

	lyMain->addWidget(left);
	lyMain->addWidget(right);
}

void CarteGUIModel::reloadDynamicButtons() {
	clearLayout(this->lyButoane);
	std::map<std::string, std::vector<Carte>> dict;
	srv.filtreazaCount(dict);
	//QPushButton* buttonGen;

	auto it = dict.begin();
	while (it != dict.end()) {

		auto m = it->second.size();
		a = new QPushButton();
		a->setText(QString::fromStdString(it->first));
		QObject::connect(a, &QPushButton::clicked, [=]() {

			QMessageBox::information(this, "Info", QString::number((int)m));
			});
		lyButoane->addWidget(a);
		//QMessageBox::information(this, "Info", QString::number(it->second.size()));
		it++;

	}
}
void CarteGUIModel::clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}
void CarteGUIModel::reloadCarteList(vector<Carte> carti) {
/*this->tableCarti->clearContents();
	this->tableCarti->setRowCount((int)carti.size());

	int lineNumber = 0;
	for (auto& carte : carti) {
		this->tableCarti->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(carte.getTitlu())));
		this->tableCarti->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(carte.getAutor())));
		this->tableCarti->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(carte.getGen())));
		this->tableCarti->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(carte.getAn())));
		lineNumber++;
	}*/
	this->model->setCarte(carti);
}

void CarteGUIModel::connectSignalsSlots() {

	QObject::connect(buttonAddCarte, &QPushButton::clicked, this, &CarteGUIModel::guiAddCarte);

	QObject::connect(buttonDeleteCarte, &QPushButton::clicked, this, &CarteGUIModel::guiDeleteCarte);

	QObject::connect(buttonModifyCarte, &QPushButton::clicked, this, &CarteGUIModel::guiModifyCarte);

	QObject::connect(buttonUndo, &QPushButton::clicked, this, &CarteGUIModel::guiUndoCarte);

	QObject::connect(buttonSortCarti, &QPushButton::clicked, [&]() {
		if (this->radioSortTitlu->isChecked())
		//this->reloadCarteLab(this->srv.sortTitlu());
		this->reloadCarteList(srv.sortTitlu());
		else
			if (this->radioSortAutor->isChecked())
				//this->reloadCarteLab(this->srv.sortAutor());
				this->reloadCarteList(srv.sortAutor());
			else
				if (this->radioSortGenAn->isChecked())
					//this->reloadCarteLab(this->srv.sortAnGen());
					this->reloadCarteList(srv.sortAnGen());
		});

	QObject::connect(buttonFilterCarti1, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterTitlu->text().toStdString();
	//this->reloadCarteList(srv.filtrareTitlu(filterC));
	this->reloadCarteList(srv.filtrareTitlu(filterC));
		});

	QObject::connect(buttonFilterCarti2, &QPushButton::clicked, [&]() {
		int filterC = this->editFilterTitlu->text().toUInt();
	//this->reloadCarteList(srv.filtrareAn(filterC));
	this->reloadCarteList(srv.filtrareAn(filterC));
		});

	QObject::connect(buttonReloadData, &QPushButton::clicked, [&]() {
		//this->reloadCarteList(srv.getAll());
		this->reloadCarteList(srv.getAll());
		});

	QObject::connect(btnCos, &QPushButton::clicked, this, [&]() {
		cos.show();
		});
}

void CarteGUIModel::guiAddCarte() {

	try {
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toUInt();

		//golim QLineEdit-urle dupa apasarea butonului
		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		this->srv.addCarte(titlu, autor, gen, an);
		//this->reloadCarteList(this->srv.getAll());
		this->reloadCarteList(this->srv.getAll());
		reloadDynamicButtons();
		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes."));

	}
	catch (CarteRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}

}

void CarteGUIModel::guiDeleteCarte()
{
	try {
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toUInt();

		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		this->srv.deleteCarte(titlu, autor, gen, an);
		//this->reloadCarteList(this->srv.getAll());
		this->reloadCarteList(this->srv.getAll());
		reloadDynamicButtons();
		QMessageBox::information(this, "Info", QString::fromStdString("Carte stearsa cu succes!"));

	}
	catch (CarteRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}

void CarteGUIModel::guiModifyCarte()
{
	try {
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toUInt();

		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		this->srv.modificaCarte(titlu, autor, gen, an);
		//this->reloadCarteList(this->srv.getAll());
		this->reloadCarteList(this->srv.getAll());
		reloadDynamicButtons();
		QMessageBox::information(this, "Info", QString::fromStdString("Carte modificata cu succes!"));

	}
	catch (CarteRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}

}

void CarteGUIModel::guiUndoCarte() {
	try {
		this->srv.undo();
		//this->reloadCarteList(this->srv.getAll());
		this->reloadCarteList(this->srv.getAll());
		reloadDynamicButtons();
	}
	catch (exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se mai poate face undo!"));
	}

}

