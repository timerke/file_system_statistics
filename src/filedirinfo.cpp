#include "filedirinfo.h"

FileDirInfo::FileDirInfo(QString key, QString name, int number, int size) {
    this->key = key;
    this->name = name;
    this->number = number;
    this->size = size;
}

FileDirInfo::~FileDirInfo() {

}

QString FileDirInfo::get_mean_size() const {
    if (number == 0) {
        return QString("N/A");
    }
    return QString::number(this->size / this->number);
}

QString FileDirInfo::get_number() const {
    return QString::number(this->number);
}

QString FileDirInfo::get_size() const {
    return QString::number(this->size);
}
