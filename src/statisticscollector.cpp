#include <QDebug>
#include <QDir>
#include "statisticscollector.h"

StatisticsCollector::StatisticsCollector() : QThread() {

}

StatisticsCollector::~StatisticsCollector() {

}

int StatisticsCollector::find_group_index(QString group_key) {
    for (int i = 0; i < this->data.count(); i++) {
        if (this->data.at(i).key == group_key) {
            return i;
        }
    }
    return -1;
}

void StatisticsCollector::get_statistics(QString folder_path, bool consider_folders) {
    qDebug() << "Collecting statistics in folder" << folder_path;
    QDir dir(folder_path);
    for (auto file_info : dir.entryInfoList(QDir::AllEntries, QDir::DirsLast)) {
        if (!this->collecting) {
            break;
        }
        if (file_info.fileName() == QString(".") || file_info.fileName() == QString("..")) {
            continue;
        }
        if (file_info.exists() && file_info.isFile()) {
            this->update_data(QString("files"), file_info.size());
            QString key = QString("ext_%1").arg(file_info.suffix());
            this->update_data(key, file_info.size(), file_info.suffix());
        }
        if (consider_folders && file_info.exists() && file_info.isDir()) {
            this->update_data("dirs", file_info.size());
        }
    }
    this->send_statistics();
    for (auto file_info : dir.entryInfoList(QDir::AllEntries, QDir::DirsLast)) {
        if (!this->collecting) {
            break;
        }
        if (file_info.fileName() == QString(".") || file_info.fileName() == QString("..")) {
            continue;
        }
        if (file_info.exists() && file_info.isDir()) {
            this->get_statistics(file_info.absoluteFilePath());
        }
    }
}

void StatisticsCollector::initialize_data() {
    this->mutex.lock();
    this->data.clear();
    this->data.append(FileDirInfo(QString("files"), QString("Все файлы")));
    this->data.append(FileDirInfo(QString("dirs"), QString("Каталоги")));
    this->mutex.unlock();
}

bool StatisticsCollector::is_running() const {
    return this->running;
}

void StatisticsCollector::run() {
    while (this->running) {
        if (!this->tasks.isEmpty()) {
            QString folder_path = this->tasks.dequeue();
            if (folder_path.isEmpty()) {
                continue;
            }
            qDebug() << "Started collecting statistics in the catalog" << folder_path;
            this->collecting = true;
            this->get_statistics(folder_path, true);
            this->collecting = false;
            qDebug() << "Statistics collection completed";
        }
        this->msleep(500);
    }
}

void StatisticsCollector::send_statistics() {
    qDebug() << "Sending updated statistics from statistics collector";
    emit this->statistics_changed(this->data);
}

void StatisticsCollector::set_folder_for_collecting_stat(QString folder_path) {
    this->stop_collectring();
    this->tasks.enqueue(folder_path);
    this->initialize_data();
    emit this->statistics_changed(this->data);
}

void StatisticsCollector::start() {
    this->running = true;
    QThread::start();
}

void StatisticsCollector::stop() {
    this->running = false;
}

void StatisticsCollector::stop_collectring() {
    this->collecting = false;
}

void StatisticsCollector::update_data(QString key, qint64 size, QString ext) {
    this->mutex.lock();
    int index = this->find_group_index(key);
    if (index == -1) {
        QString name;
        if (ext.isEmpty()) {
            name = QString("Файлы без расширения");
        } else {
            name = QString("Файлы с расширением %1").arg(ext);
        }
        this->data.append(FileDirInfo(key, name, 1, size));
        if (this->data.count() > 2) {
            std::sort(this->data.begin() + 2, this->data.end());
        }
    } else {
        StatisticsDataT::iterator it = this->data.begin() + index;
        (*it).number += 1;
        (*it).size += size;
    }
    this->mutex.unlock();
}
