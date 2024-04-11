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
        size_t index = hash<T>{}(item) % size;
        table[index].push_back(item);
    }

    bool search(const T &item)
    {
        size_t index = hash<T>{}(item) % size;
        for (const T &i : table[index])
        {
            if (i == item)
                return true;
        }
        return false;
    }
};

// Function to check if a word is misspelled
bool isMisspelled(const string &word, const unordered_set<string> &dictionary)
{
    return dictionary.find(word) == dictionary.end();
}

// Function to spell check a paragraph
void spellCheckParagraph(const string &paragraph, const unordered_set<string> &dictionary, vector<string> &misspelledWords)
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
                if (isMisspelled(currentWord, dictionary))
                {
                    misspelledWords.push_back(currentWord);
                }
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty())
    {
        if (isMisspelled(currentWord, dictionary))
        {
            misspelledWords.push_back(currentWord);
        }
    }
}

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

    string paragraph((istreambuf_iterator<char>(paraFile)), istreambuf_iterator<char>());

    vector<string> misspelledWords;
    spellCheckParagraph(paragraph, dictionary, misspelledWords);

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