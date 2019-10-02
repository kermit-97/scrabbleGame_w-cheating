#include "dict.h"

Dict::Dict(const char *filename)
{
    ifstream ifs (filename);    // prendo il file
    string word;
    while(ifs >> word)          // leggo ogni parola
        dict.insert(word);      // e la inserisco nella struttura
}

bool Dict::contains(const string &word) const
{
    return dict.find(word) == Trie::WORD;   // la parola è contenuta se la funzione find ritorna il valore Trie::WORD
}

Trie Dict::getDict() const
{
    return dict;
}

void Dict::setDict(const Trie &value)
{
    dict = value;
}

bool Dict::noSuccessor(const string &word)
{
    return dict.noSuccessor(word);      // richiama la funzione per verificare che la parola non abbia successori
}
