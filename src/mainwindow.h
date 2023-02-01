#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QFileSystemModel>
#include <QFileSystemWatcher>
#include <QMainWindow>
#include "statisticscollector.h"
#include "statisticsmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief closeEvent
     * Переопределение метода, который обрабатывает закрытие окна.
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief handle_click_on_file_system
     * @param index
     */
    void handle_click_on_file_system(const QModelIndex &index);

    /**
     * @brief set_folder_for_collecting_stat
     * Метод задает путь до папки, в которой нужно собрать статистику.
     * @param new_folder_parh - путь до папки.
     */
    void set_folder_for_collecting_stat(QString new_folder_parh);

private:
    StatisticsCollector *collector;
    QFileSystemModel *file_system_model;
    QString folder_path;
    StatisticsModel *statistics_model;
    QFileSystemWatcher *watcher;
    Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
