#include <QFont>
#include "statisticsmodel.h"

StatisticsModel::StatisticsModel() : QAbstractTableModel() {

}

StatisticsModel::~StatisticsModel() {

}

int StatisticsModel::columnCount(const QModelIndex & /*parent*/) const {
    return 4;
}

QVariant StatisticsModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole && index.row() < this->statistics.size()) {
        FileDirInfo file_info = this->statistics.at(index.row());
        switch (index.column()) {
        case 0:
            return file_info.name;
        case 1:
            return file_info.get_number();
        case 2:
            return file_info.get_size();
        case 3:
            return file_info.get_mean_size();
        }
    }
    return QVariant();
}

QVariant StatisticsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Наименование");
        case 1:
            return QString("Количество");
        case 2:
            return QString("Общий размер, Б");
        case 3:
            return QString("Средний размер, Б");
        }
    } else if (role == Qt::FontRole) {
        QFont font;
        font.setBold(true);
        return font;
    }
    return QVariant();
}

bool StatisticsModel::insertRows(int position, int rows, const QModelIndex &index) {
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        this->statistics.append(FileDirInfo());
    }
    endInsertRows();
    return true;
}

bool StatisticsModel::removeRows(int position, int rows, const QModelIndex &index) {
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        try {
            this->statistics.removeAt(position);
        }  catch (...) {
            continue;
        }
    }
    endRemoveRows();
    return true;
}

int StatisticsModel::rowCount(const QModelIndex & /*parent*/) const {
   return this->statistics.size();
}

void StatisticsModel::set_statistics(StatisticsDataT new_statistics) {
    if (this->statistics.count() < new_statistics.count()) {
        int rows = new_statistics.count() - this->statistics.count();
        this->insertRows(this->statistics.count(), rows);
    } else if (this->statistics.count() > new_statistics.count()) {
        int rows = this->statistics.count() - new_statistics.count();
        this->removeRows(new_statistics.count() - 1, rows);
    }
    this->statistics = new_statistics;
    emit this->dataChanged(this->index(0, 0), this->index(this->statistics.count(), 3));
}
