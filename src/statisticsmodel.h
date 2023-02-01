#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H

#include <QAbstractTableModel>
#include "filedirinfo.h"

/**
 * @brief The StatisticsModel class
 * Модель для таблицы-представления со статистикой.
 */
class StatisticsModel : public QAbstractTableModel {
    Q_OBJECT

public:
    StatisticsModel();
    ~StatisticsModel();
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief set_statistics
     * Метод задает новые данные о статистике групп файлов.
     * @param new_statistics - новые данные о статистике.
     */
    void set_statistics(StatisticsDataT new_statistics);

private:
    StatisticsDataT statistics;
};

#endif  // STATISTICSMODEL_H
