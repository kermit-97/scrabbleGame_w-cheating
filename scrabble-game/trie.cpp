#include "trie.h"

using namespace std;

Trie::Trie():endOfWord(false), successor{}{}

Trie::~Trie(){
    for(int i = 0; i < Trie::NUM_OF_CHAR; i++)
        delete successor[i];
}

void Trie::insert(const string& word){
    if(word == "") return;      // controllo che non sia un caso anomalo
    return insert(word, 0);     // chiamo la funzione privata
}

void Trie::insert(const string& word, int cur){
    if(cur == word.length()){       // se sono arrivato in fondo, allora ho inserito tutta la parola
        endOfWord = true;           // setto il flag di fine parola
        return;
    }

    int index = tolower(word[cur]) - 'a';   // calcolo il successore della lettera
    if(successor[index] == NULL)            // se non esiste
        successor[index] = new Trie();      // lo creo
    successor[index]->insert(word, cur+1);  // inserisco
}

int Trie::find(const string& word) const{
    if(word == "") return false;    // controllo che non sia un caso anomalo
    return find(word, 0);           // chiamo la funzione privata
}

int Trie::find(const string& word, int cur) const{
    if(cur == word.length())        // se sono arrivato in fondo alla parola da cercare
        return endOfWord ? int(Trie::WORD) : int(Trie::PREFIX);     // se sono effettivamente alla fine di una parola ritorno il valore Trie::WORD, altrimenti il valore Trie::PREFIX

    int index = tolower(word[cur]) - 'a';   // calcolo il successore della lettera
    if(successor[index] == NULL)            // se non esiste
        return int(Trie::NONE);             // ritorno il valore Trie::NONE
    return successor[index]->find(word, cur+1); // altrimenti continuo
}

bool Trie::noSuccessor(const string &word)
{
    if (word == "")     // se sono alla fine della parola, allora ritorno falso
        return false;
    else if (successor[tolower(word[0]) - 'a'] == NULL) // se il successore non esiste
        return true;    // allora ritorno vero

    return successor[tolower(word[0]) - 'a']->noSuccessor(word.substr(1,word.size()-1));    // altrimenti continuo la chiamata ricorsiva, spostandomi sul successore, eliminando la prima lettera della parola
}
