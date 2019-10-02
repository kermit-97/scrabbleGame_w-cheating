#ifndef DICT_H
#define DICT_H

#include <unordered_map>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm>
#include <QObject>
#include "trie.h"

using namespace std;

class Dict
{
public:
    Dict(const char* filename);                 // il costruttore carica il dizionario in memoria
    bool contains(const string& word) const;    // controlla se la parola è contenuta nel dizionario

    bool noSuccessor(const string& word);       // controlla se, seguendo la struttura TRIE, la parola non ha successori

    // getter and setters
    Trie getDict() const;
    void setDict(const Trie &value);

private:
    Trie dict;      // struttura TRIE che contiene tutte le parole del dizionario
};

#endif // DICT_H
