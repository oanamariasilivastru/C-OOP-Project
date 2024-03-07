#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <qlabel.h>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "carte_service.h"
#include <qpainter.h>
#include "Observer.h"



class CosGUILabel_Draw : public QWidget, public Observer {
public:
	CarteService& srv;
	InchirieriList& list;
	QLabel* lblNrInch;
	QLineEdit* editNrInch;

	void initGUI() {
		auto ly = new QHBoxLayout{};
		this->setLayout(ly);

		lblNrInch = new QLabel{ "Numar carti in cos:" };
		
		editNrInch = new QLineEdit{};

		auto formly = new QFormLayout{};
		formly->addRow(lblNrInch, editNrInch);
		ly->addLayout(formly);

		list.addObserver(this);
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (auto carte: srv.getInchiriereList()) {
			//p.drawRect(x, y, 10, song.getDurata() * 10);
			x = rand() % 200 + 1;
			y = rand() % 200 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("unnamed.png");

			p.drawImage(target, image, source);

			x += 40;

		}
	}

	void update() override {
		this->editNrInch->setText(QString::number(list.getAllInchirieri().size()));
		repaint();
	}
	~CosGUILabel_Draw() {
		list.removeObserver(this);
	}
	CosGUILabel_Draw(InchirieriList& list, CarteService& srv) : list{ list }, srv{ srv } {
		initGUI();
	}

};


class CosGUITable : public QWidget, public Observer {
public:
	InchirieriList& list;
	QHBoxLayout* ly = new QHBoxLayout{};
	QTableWidget* tableCos;
	QPushButton* btnEmpty;

	void initGUI() {
		setLayout(ly);
		tableCos = new QTableWidget(3, 4);
		btnEmpty = new QPushButton{ "Goleste cos" };
		ly->addWidget(tableCos);
		ly->addWidget(btnEmpty);

		list.addObserver(this);
	}

	void reloadGarage(vector<Carte> carti) {
		tableCos->clearContents();
		tableCos->setRowCount(carti.size());

		int line = 0;
		for (auto& car : carti) {
			tableCos->setItem(line, 0, new QTableWidgetItem(QString::fromStdString(car.getTitlu())));
			tableCos->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(car.getAutor())));
			tableCos->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(car.getGen())));
			tableCos->setItem(line, 3, new QTableWidgetItem(QString::number(car.getAn())));
			line++;
		}
	}

	void connectSignalSlots() {
		QObject::connect(btnEmpty, &QPushButton::clicked, this, [&]() {
			list.emptyList();
			});
	}

	void update() override {
		reloadGarage(list.getAllInchirieri());
	}

	~CosGUITable() {
		list.removeObserver(this);
	}

	CosGUITable(InchirieriList& list) : list{ list } {
		initGUI();
		connectSignalSlots();
	}
};

class CosGUICuTabel : public QWidget, public Observer {
public:
	QLineEdit* editTitlu = new QLineEdit;
	QLineEdit* editAutor = new QLineEdit;
	QLineEdit* editNumar = new QLineEdit;
	QLineEdit* editFisier = new QLineEdit;

	CarteService& srv;
	QTableWidget* table;
	QPushButton* buttonAdd;
	QPushButton* buttonRandom;
	QPushButton* buttonClear;
	QPushButton* buttonFile;
	QPushButton* btnCos;
	QPushButton* btnNoCarti;



	void initGUI() {
		int noLines = 20;
		int noColumnns = 4;
		QHBoxLayout* ly = new QHBoxLayout;
		table = new QTableWidget{ noLines, noColumnns };
		QStringList tblHeaderList;
		tblHeaderList << "Titlu" << "Autor" << "Gen" << "An";
		this->table->setHorizontalHeaderLabels(tblHeaderList);
		this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

		ly->addWidget(table);
		setLayout(ly);

		QWidget* form = new QWidget;
		QFormLayout* lyForm = new QFormLayout;
		form->setLayout(lyForm);

		QLabel* lblTitlu = new QLabel{ "Titlu carte: " };
		QLabel* lblAutor = new QLabel{ "Autor carte: " };

		lyForm->addRow(lblTitlu, editTitlu);
		lyForm->addRow(lblAutor, editAutor);

		buttonAdd = new QPushButton("Adaugare inchiriere in cos");
		lyForm->addWidget(buttonAdd);


		editNumar = new QLineEdit;
		QLabel* lblNumar = new QLabel{ "Numar random: " };
		lyForm->addRow(lblNumar, editNumar);


		buttonRandom = new QPushButton("Genereaza cos");
		lyForm->addWidget(buttonRandom);

		buttonClear = new QPushButton("Goleste cos");
		lyForm->addWidget(buttonClear);


		QLabel* lblFisier = new QLabel{ "Nume fisier: " };
		lyForm->addRow(lblFisier, editFisier);
		buttonFile = new QPushButton("Export in fisier");
		btnCos = new QPushButton("Deschide cos");
		btnCos->setStyleSheet("background-color: green");
		btnNoCarti = new QPushButton("Vizualizeaza nr. carti");
		btnNoCarti->setStyleSheet("background-color: magenta");
		lyForm->addWidget(buttonFile);
		lyForm->addWidget(btnCos);
		lyForm->addWidget(btnNoCarti);
		ly->addWidget(form);
	}

	CosGUICuTabel(CarteService& srvgui) : srv{ srvgui } {
		srv.getInchiriere().addObserver(this);
		initGUI();
		connectSignals();
		loadTable();

	}

	void update() override {
		loadTable();

	}


	void loadTable() {
		vector<Carte> currentList = srv.getInchiriereList();
		this->table->clearContents();
		this->table->setRowCount((int)currentList.size());
		int lineNumber = 0;
		for (auto& carte : currentList) {
			this->table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(carte.getTitlu())));
			this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(carte.getAutor())));
			this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(carte.getGen())));
			this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(carte.getAn())));
			lineNumber++;
		}
	}

	void guiAddInchiriere() {
		try {
			string titlu = editTitlu->text().toStdString();
			string autor = editAutor->text().toStdString();

			//golim QLineEdit-urle dupa apasarea butonului
			editTitlu->clear();
			editAutor->clear();

			this->srv.addToInchiriere(titlu, autor);
			this->loadTable();
			QMessageBox::information(this, "Info", QString::fromStdString("Inchiriere adaugata cu succes! "));
		}
		catch (CarteRepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
		}
		catch (ValidateException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
		}


	}

	void generateCos() {
		try {
			int howMany = editNumar->text().toUInt();

			editNumar->clear();
			this->srv.addRandomToCarti(howMany);
			this->loadTable();

			QMessageBox::information(this, "Info", QString::fromStdString("Generare reusita! "));
		}
		catch (CarteRepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
		}
	}

	void exportCos() {
		string fisier = editFisier->text().toStdString();
		QMessageBox::information(this, "Info", QString::fromStdString("Export reusit! "));
		editFisier->clear();
		this->srv.exportcos(fisier);
		this->loadTable();
	}

	void connectSignals() {
		QObject::connect(buttonAdd, &QPushButton::clicked, [&]() {
			this->guiAddInchiriere();
			});

		QObject::connect(buttonClear, &QPushButton::clicked, [&]() {
			this->srv.emptyInchiriere();
		this->loadTable();
			});

		QObject::connect(buttonRandom, &QPushButton::clicked, [&]() {
			this->generateCos();
			});

		QObject::connect(buttonFile, &QPushButton::clicked, [&]() {
			this->exportCos();
			});
		QObject::connect(btnNoCarti, &QPushButton::clicked, this, [=]() {
			auto cosWindow = new CosGUILabel_Draw{ srv.getInchiriere(), srv };
		cosWindow->resize(300, 300);
		cosWindow->show();
			});
		QObject::connect(btnCos, &QPushButton::clicked, this, [=]() {
			auto cosWindow = new CosGUITable{ srv.getInchiriere() };
		cosWindow->show();
			});
	}

};
