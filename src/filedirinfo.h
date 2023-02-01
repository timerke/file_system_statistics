#ifndef FILEDIRINFO_H
#define FILEDIRINFO_H

#include <QList>
#include <QString>

/**
 * @brief The FileDirInfo class
 * Класс для хранения информации о группе файлов.
 */
class FileDirInfo {
public:
    /**
     * @brief FileDirInfo
     * Конструктор класса.
     * @param key - ключ, по которому определяется группа файлов;
     * @param name - имя группы файлов;
     * @param number - количество файлов в группе;
     * @param size - полный размер группы файлов в Б.
     */
    FileDirInfo(QString key = QString(""), QString name = QString(""), int number = 0, int size = 0);

    ~FileDirInfo();

    /**
     * @brief get_mean_size
     * @return средний размер файлов в группе в Б.
     */
    QString get_mean_size() const;

    /**
     * @brief get_number
     * @return количество файлов в группе.
     */
    QString get_number() const;

    /**
     * @brief get_size
     * @return общий размер группы файлов в Б.
     */
    QString get_size() const;

    bool operator < (const FileDirInfo &other) const {
        return this->name < other.name;
    }

public:
    QString key;
    QString name;
    int number;
    qint64 size;
};

typedef QList<FileDirInfo> StatisticsDataT;

#endif // FILEDIRINFO_H
