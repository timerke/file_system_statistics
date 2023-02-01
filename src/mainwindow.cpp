#include <QDebug>
#include <QFileInfo>
#include <QFileSystemModel>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("FileSystemStatistics");

    this->file_system_model = new QFileSystemModel();
    this->file_system_model->setRootPath(QDir::currentPath());
    ui->tree_view_file_system->setModel(this->file_system_model);
    ui->tree_view_file_system->header()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->tree_view_file_system, &QTreeView::clicked, this,
            &MainWindow::handle_click_on_file_system);

    this->watcher = new QFileSystemWatcher();
    connect(this->watcher, &QFileSystemWatcher::directoryChanged, this,
            &MainWindow::set_folder_for_collecting_stat);

    this->statistics_model = new StatisticsModel();
    ui->table_statistics->setModel(this->statistics_model);
    ui->table_statistics->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->collector = new StatisticsCollector();
    connect(this->collector, &StatisticsCollector::finished, this, &MainWindow::close);
    connect(this->collector, &StatisticsCollector::statistics_changed, this->statistics_model,
            &StatisticsModel::set_statistics);
    this->collector->start();
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->file_system_model;
    delete this->collector;
    delete this->watcher;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (this->collector->is_running()) {
        this->collector->stop_collectring();
        this->collector->stop();
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::handle_click_on_file_system(const QModelIndex &index) {
    QFileInfo file_info(this->file_system_model->filePath(index));
    if (file_info.exists() && file_info.isDir()) {
        this->set_folder_for_collecting_stat(this->file_system_model->filePath(index));
    } else {
        this->set_folder_for_collecting_stat("");
    }
}

void MainWindow::set_folder_for_collecting_stat(QString new_folder_path) {
    ui->line_edit_folder_path->setText(new_folder_path);
    if (!this->folder_path.isEmpty()) {
        this->watcher->removePath(this->folder_path);
    }
    this->folder_path = new_folder_path;
    if (!this->folder_path.isEmpty()) {
        this->watcher->addPath(this->folder_path);
    }
    this->collector->set_folder_for_collecting_stat(this->folder_path);
}
