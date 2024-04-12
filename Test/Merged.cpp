#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

// Hash Function for strings
struct StringHash
{
    size_t operator()(const string &str) const
    {
        size_t hash = 0;
        for (char c : str)
        {
            hash = hash * 31 + c;
        }
        return hash;
    }
};

// Hash Table class
template <typename T>
class HashTable
{
private:
    vector<vector<T>> table;
    size_t size;

public:
    HashTable(size_t size) : size(size)
    {
        table.resize(size);
    }

    void insert(const T &item)
    {
        size_t index = StringHash{}(item) % size;
        table[index].push_back(item);
    }

    bool search(const T &item)
    {
        size_t index = StringHash{}(item) % size;
        for (const T &i : table[index])
        {
            if (i == item)
                return true;
        }
        return false;
    }
};

// Function to check if a word is misspelled
bool isMisspelled(const string &word, const HashTable<string> &hashTable)
{
    return !hashTable.search(word);
}

// Function to spell check a paragraph using the hash table
void spellCheckParagraph(const string &paragraph, const HashTable<string> &hashTable, vector<string> &misspelledWords)
{
    string word;
    string currentWord;
    for (char c : paragraph)
    {
        if (isalpha(c))
        {
            currentWord += tolower(c);
        }
        else
        {
            if (!currentWord.empty())
            {
                if (isMisspelled(currentWord, hashTable))
                {
                    misspelledWords.push_back(currentWord);
                }
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty())
    {
        if (isMisspelled(currentWord, hashTable))
        {
            misspelledWords.push_back(currentWord);
        }
    }
}

// Function to implement Linear Probing
int linearProbe(string table[], int i, int n);

// Function to implement quadratic probing
int quadProbe(string table[], int i, int n);

int main()
{
    ifstream wordsFile("words.txt");
    ifstream paraFile("para.txt");
    ofstream misspelledFile("misspelled_words.txt");

    if (!wordsFile || !paraFile)
    {
        cerr << "Error: Unable to open file\n";
        return 1;
    }

    unordered_set<string> dictionary;
    string word;
    while (wordsFile >> word)
    {
        dictionary.insert(word);
    }

    HashTable<string> hashTable(53); // Initial table size is 53

    while (wordsFile >> word)
    {
        hashTable.insert(word);
    }

    string paragraph((istreambuf_iterator<char>(paraFile)), istreambuf_iterator<char>());

    vector<string> misspelledWords;
    spellCheckParagraph(paragraph, hashTable, misspelledWords);

    for (const string &misspelledWord : misspelledWords)
    {
        misspelledFile << misspelledWord << endl;
    }

    misspelledFile.close();
    paraFile.close();
    wordsFile.close();

    cout << "Misspelled words count: " << misspelledWords.size() << endl;

    return 0;
}