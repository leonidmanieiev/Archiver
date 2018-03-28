#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(280, 40);

    if(!this->log_dir.exists("Log/"))
        this->log_dir.mkdir("Log/");

    this->log_file.setFileName("Log/log.txt");
    if(!log_file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QMessageBox::warning(this, "Error", "Log file cannot be open");
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_about_btn_clicked()
{
    QTextStream ts_log(&this->log_file);
    QString about_text, about_text_path = ":/My_files/Resources/Text/about.txt";

    try
    {
        about_text = get_text_from_file(this, about_text_path);
    }catch(const std::invalid_argument& ia)
    {
        ts_log << QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")
               << ": on_about_btn_clicked()::"<< ia.what() << '\n';
        return;
    }

    log_file.flush();
    log_file.close();

    QMessageBox about_box(QMessageBox::NoIcon, "About",
                          about_text, QMessageBox::Ok, this);
    about_box.exec();
}

void MainWindow::on_archive_btn_clicked()
{
    QTextStream ts_log(&this->log_file);
    map_qchar_quint prob_of_chars;
    QString archive_name, text_to_compress;

    try
    {
        archive_name = create_file_with_prob(this, text_to_compress, prob_of_chars);
    }catch(const std::invalid_argument& ia)
    {
        ts_log << QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")
               << ": on_archive_btn_clicked()::" << ia.what() << '\n';
        return;
    }

    if(prob_of_chars.size() <= 1)
    {
        QMessageBox about_box(QMessageBox::NoIcon, "About",
                              "There is no reason to archive empty / one symbol file.",
                              QMessageBox::Ok, this);
        about_box.exec();
        return;
    }

    Node* huffman_tree = create_huffman_tree(prob_of_chars);
    hash_qchar_qstr hash_char_code = get_codes(huffman_tree, "");

    try
    {
        compress(this, hash_char_code, archive_name, text_to_compress);
    }catch(const std::invalid_argument& ia)
    {
        ts_log << QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")
               << ": on_archive_btn_clicked()::" << ia.what() << '\n';
        return;
    }

    log_file.flush();
    log_file.close();

    QApplication::beep();
    QMessageBox about_box(QMessageBox::NoIcon, "About",
                          "Compression is done", QMessageBox::Ok, this);
    about_box.exec();
}

void MainWindow::on_extact_btn_clicked()
{
    QTextStream ts_log(&this->log_file);

    try
    {
        decompress(this);
    }catch(const std::invalid_argument& ia)
    {
        ts_log << QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")
               << ": on_extact_btn_clicked()::" << ia.what() << '\n';
        return;
    }catch(const std::length_error& le)
    {
        ts_log << QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")
               << ": on_extact_btn_clicked()::" << le.what() << '\n';
        return;
    }

    log_file.flush();
    log_file.close();

    QApplication::beep();
    QMessageBox about_box(QMessageBox::NoIcon, "About",
                          "Decompression is done", QMessageBox::Ok, this);
    about_box.exec();
}
