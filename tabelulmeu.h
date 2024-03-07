#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include "Carte.h"
#include <vector>
#include <qfont.h>
#include <qdebug.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Carte> carti;
public:
	MyTableModel(const std::vector<Carte>& carti) :carti{ carti } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override  {
		return int(carti.size());
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		//qDebug() << index.data(role);

		if (role == Qt::ForegroundRole) {
			auto carte = this->carti[index.row()];
			if (carte.getGen() == "comedie") {
				return QBrush(Qt::magenta);
			}
		}
		if (role == Qt::FontRole) {
			QFont f;
			f.setItalic(index.row() % 10 == 1);
			f.setBold(index.row() % 10 == 1);
			return f;
		}
		if (role == Qt::BackgroundRole) {

			int row = index.row();
			QModelIndex i = index.sibling(index.row(), 1);
			if (i.data().toString() == "Deep Purple") {
				QBrush bg(Qt::yellow);
				return bg;
			}
		}

		if (role == Qt::DisplayRole) {

			Carte p = carti[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getTitlu());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.getAutor());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getGen());
			}
			else if (index.column() == 3) {
				return QString::number(p.getAn());
			}
		}

		return QVariant{};
	}

	void setCarte(const vector<Carte> carti) {
		this->carti = carti;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return tr("Titlu");
				case 1:
					return tr("Autor");
				case 2:
					return tr("Gen");
				case 3:
					return tr("An");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};
