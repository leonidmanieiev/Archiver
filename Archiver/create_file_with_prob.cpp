#include "create_file_with_prob.h"

void save_as(QWidget* parent, const QString& filename,
             const QString &hash_rep, const quint64& text_length)
{
    QFile out_file(filename);

    if(!out_file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(parent, "Error", "File cannot be open");
        throw std::invalid_argument("save_as()::bad file access");
    }

    QTextStream ts_out(&out_file);
    ts_out.setCodec("Windows-1252");
    ts_out << hash_rep << '\n' << text_length << '\n';

    out_file.flush();
    out_file.close();
}

QString
create_file_with_prob (QWidget* parent, QString& text_to_compress,
                       map_qchar_quint &prob_of_chars)
{
    QString file_to_archive = QFileDialog::getOpenFileName(parent, "Open file",
                                                           "C:\\", "Text files (*.txt)");
    QString archive_name(file_to_archive);
    try
    {
        archive_name = QFileDialog::getSaveFileName(parent, "Save as",
                                                    archive_name.replace(".txt", ""),
                                                    "All archives (*.huff)");
        if(archive_name.isNull())
            throw std::invalid_argument("create_file_with_probability()::invalid file");
    }catch(std::invalid_argument& ia) { throw ia; }

    try
    {
        text_to_compress = get_text_from_file(parent, file_to_archive);
    }catch(const std::invalid_argument& ia)
    {
        std::string err(std::string("create_file_with_probability()::")+ia.what());
        throw std::invalid_argument(err);
    }

    quint64 text_length = text_to_compress.size();
    prob_of_chars = calc_probability_of_chars(text_to_compress);

    QString hash_rep = parse_hash_to_str(prob_of_chars);

    try
    {
        save_as(parent, archive_name, hash_rep, text_length);
    }catch(std::invalid_argument& ia)
    {
        std::string err(std::string("create_file_with_probability()::")+ia.what());
        throw std::invalid_argument(err);
    }

    return archive_name;
}
