#include "probability_of_chars.h"

map_qchar_quint
calc_probability_of_chars(const QString& text)
{
    map_qchar_quint prob_of_chars;

    for(const QChar& letter : text)
        prob_of_chars[letter]++;

    return prob_of_chars;
}
