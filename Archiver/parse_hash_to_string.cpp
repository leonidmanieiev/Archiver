#include "parse_hash_to_string.h"

QString parse_hash_to_str(const map_qchar_quint& prob_of_chars)
{
    QString hash_rep;
    QTextStream ts(&hash_rep);

    foreach(const auto& key, prob_of_chars.keys())
        ts << key.unicode() << "=" << prob_of_chars[key] << '|';

    return hash_rep;
}
