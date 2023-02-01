#ifndef STATISTICSCOLLECTOR_H
#define STATISTICSCOLLECTOR_H

#include <QMutex>
#include <QQueue>
#include <QThread>
#include "filedirinfo.h"

/**
 * @brief The StatisticsCollector class
 * Класс для сбора статистики о количестве и размере файлов.
 */
class StatisticsCollector : public QThread {
    Q_OBJECT

public:
    StatisticsCollector();
    ~StatisticsCollector();

    /**
     * @brief is_running
     * @return true, если сборщик статистики работает.
     */
    bool is_running() const;

    /**
     * @brief run
     * Метод, который выполняется при запуске сборщика статистики.
     */
    void run() override;

    /**
     * @brief set_folder_for_collecting_stat
     * Метод задает каталог, в котором нужно провести сбор статистики.
     * @param folder_path - путь к каталогу.
     */
    void set_folder_for_collecting_stat(QString folder_path);

    /**
     * @brief start
     * Запуск сборщика статистики.
     */
    void start();

    /**
     * @brief stop
     * Метод совсем останавливает сборщик.
     */
    void stop();

    /**
     * @brief stop_collectring
     * Метод прекращает сборку статистики в каталоге. Но сборщик остается работать
     * и можно будет заново собрать статистику.
     */
    void stop_collectring();

private:
    /**
     * @brief find_group_index
     * Метод ищет в списке со статистикой групп индекс группы, которая соответствует
     * заданному ключу.
     * @param group_key - ключ, по которому определяется группа файлов.
     * @return индекс группы. Если группа не найдена, то возвращается -1.
     */
    int find_group_index(QString group_key);

    /**
     * @brief get_statistics
     * Метод набирает статистику по количеству и размеру файлов в заданном каталоге.
     * @param folder_path - путь к каталогу, в котором нужно набрать статистику;
     * @param consider_folders - если true, то в статистику будет добавлено количество и
     * размер подкаталогов.
     */
    void get_statistics(QString folder_path, bool consider_folders = false);

    /**
     * @brief initialize_data
     * Метод переводит список со статистикой групп в исходное состояние.
     */
    void initialize_data();

    /**
     * @brief send_statistics
     * Метод отправляет список со статистикой групп по сигналу.
     */
    void send_statistics();

    /**
     * @brief update_data
     * Метод обновляет список со статистикой групп файлов.
     * @param key - ключ для обозначения группы файлов;
     * @param size - размер файла в байтах;
     * @param ext - расширение файла.
     */
    void update_data(QString key, qint64 size, QString ext = QString(""));

signals:
    void statistics_changed(StatisticsDataT data);

private:
    bool collecting = false;
    StatisticsDataT data;
    QMutex mutex;
    bool running = false;
    QQueue<QString> tasks;
};

#endif  // STATISTICSCOLLECTOR_H
