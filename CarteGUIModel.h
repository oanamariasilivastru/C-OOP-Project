#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableView>
#include <QGroupBox>
#include <QRadioButton>
#include "Carte_GUI.h"
#include "Cos_GUI.h"
#include "tabelulmeu.h"

using std::vector;
using std::string;

class CarteGUIModel : public QWidget {
private:

	CarteService& srv;

	CosGUICuTabel cos{ srv };

	QHBoxLayout* lyMain;
	QWidget* butoane;
	QVBoxLayout* lyButoane;
	QPushButton* a;
	QLabel* lblTitlu = new QLabel{ "Titlu carte: " };
	QLabel* lblAutor = new QLabel{ "Autor carte: " };
	QLabel* lblGen = new QLabel{ "Gen carte: " };
	QLabel* lblAn = new QLabel{ "An carte: " };

	QLineEdit* editTitlu;
	QLineEdit* editAutor;
	QLineEdit* editGen;
	QLineEdit* editAn;

	QPushButton* buttonAddCarte;
	QPushButton* buttonDeleteCarte;
	QPushButton* buttonModifyCarte;
	QPushButton* buttonUndo;
	QPushButton* btnCos;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSortTitlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radioSortAutor = new QRadioButton(QString::fromStdString("Autor"));
	QRadioButton* radioSortGenAn = new QRadioButton(QString::fromStdString("Gen + An"));

	QPushButton* buttonSortCarti;

	QLabel* lblFilterCriteria = new QLabel{ "Textul dupa care se filtreaza: " };
	QLineEdit* editFilterTitlu;
	QPushButton* buttonFilterCarti1;
	QPushButton* buttonFilterCarti2;
	QPushButton* buttonReloadData;

	MyTableModel* model;
	QTableView* tableCarti = new QTableView;

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;

	void reloadDynamicButtons();

	void clearLayout(QLayout* layout);

	void initializeGUIComponents();

	void connectSignalsSlots();

	void reloadCarteList(vector<Carte> carti);

	void guiAddCarte();

	void guiDeleteCarte();

	void guiModifyCarte();

	void guiUndoCarte();

public:
	CarteGUIModel(CarteService& srv) : srv{ srv } {
		initializeGUIComponents();
		this->model = new MyTableModel{ srv.getAll() };
		this->tableCarti->setModel(model);
		connectSignalsSlots();
		reloadCarteList(srv.getAll());

	}

};