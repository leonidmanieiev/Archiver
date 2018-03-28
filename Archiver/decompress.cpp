#include "decompress.h"

void adapt_char(std::ifstream& in_file, int& byte)
{
    bool get_flag = false;

    switch(byte)
    {
        case -1: byte = 26; get_flag = false; break;
        case 13:
        {
            if(in_file.peek() == 10)
            {
                byte = in_file.get();
                get_flag = true;
            }
            break;
        }
    }

    if(!get_flag)
        return;
    adapt_char(in_file, byte);
}

void decompress(QWidget *parent)
{
    QString archive_name =
            QFileDialog::getOpenFileName(parent, "Open file", "C:\\", "Archive (*.huff)");
    std::ifstream in_file(archive_name.toStdString(), std::ios::binary);

    QString extract_name = archive_name.replace(".huff", "_extr.txt");
    QFile out_file(extract_name);

    if(!in_file.is_open())
    {
        QMessageBox::warning(parent, "Error", "File cannot be open");
        throw std::invalid_argument("decompress()::prepare_files::invalid in_file");
    }

    if(in_file.eof())
    {
        QMessageBox::warning(parent, "Error", "Compressed file if empty");
        throw std::length_error("decompress()::prepare_files::empty compressed file");
    }

    if(!out_file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(parent, "Error", "File cannot be open");
        throw std::invalid_argument("decompress()::prepare_files::invalid out_file");
    }

    QTextStream ts_out(&out_file);
    std::string str_hash_rep, str_text_length;

    std::getline(in_file, str_hash_rep);
    std::getline(in_file, str_text_length);

    str_hash_rep.pop_back(); // erase '/r' at the end of line
    str_text_length.pop_back();

    QString hash_rep(str_hash_rep.c_str());
    quint64 text_length = stoull(str_text_length);

    map_qchar_quint prob_of_chars = parse_str_to_hash(hash_rep);
    Node* root = create_huffman_tree(prob_of_chars);
    Node* root_ptr = root;

    quint64 write = 0;
    int shifts_cnt = 0, byte = in_file.get();
    adapt_char(in_file, byte);

    while(write < text_length)
    {
        bool bit = byte & (1 << (7 - shifts_cnt));
        root_ptr = bit ? root_ptr->right : root_ptr->left;

        if(root_ptr->data != '$')
        {
            ts_out << root_ptr->data;
            root_ptr = root;
            write++;
        }

        shifts_cnt++;

        if(shifts_cnt == 8)
        {
            shifts_cnt = 0;

            if(!in_file.eof())
            {
                byte = in_file.get();
                adapt_char(in_file, byte);
            }
        }
    }

    in_file.close();
    out_file.flush();
    out_file.close();
}
