#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "create_file_with_prob.h"
#include "get_text_from_file.h"
#include "alias.h"
#include "compress.h"
#include "decompress.h"

#include <QMainWindow>
#include <QDir>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_about_btn_clicked();

    void on_archive_btn_clicked();

    void on_extact_btn_clicked();

private:
    Ui::MainWindow *ui;
    QDir log_dir;
    QFile log_file;
};

#endif // MAINWINDOW_H
