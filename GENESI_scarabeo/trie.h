#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <iostream>
#include <cstring>

using std::string;
using std::vector;

class Trie{
public:
    static const int NUM_OF_CHAR = 26;
    static const int PREFIX = 1;
    static const int WORD = 3;
    static const int NONE = 0;

    Trie();
    ~Trie();

    void insert(const string& word);    // inserisce la parola nella struttura

    // ritorna:
    // Trie::WORD se la parola è valida all'interno della struttura
    // Trie::PREFIX se la parola è parte di una o più parole all'interno della struttra
    // Trie::NONE se non è nessuna delle precedenti
    int find(const string& word) const;

    bool noSuccessor(const string& word);       // controlla se, seguendo la struttura TRIE, la parola non ha successori

private:
    bool endOfWord;                 // indica se ci si trova alla fine di una parola all'interno della struttura
    Trie* successor[NUM_OF_CHAR];   // ogni lettera della struttra ha potenzialmente altri 26 successori

    void insert(const string& word, int cur);               // v. sopra
    int find(const string& word, int cur) const;            // v. sopra
};



#endif // TRIE_H
