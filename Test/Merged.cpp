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

// Function to spell check a paragraph from a file
void spellCheckFromFile(const string &wordsFile, const string &paraFile, const string &misspelledFile)
{
    ifstream wordsFileStream(wordsFile);
    ifstream paraFileStream(paraFile);
    ofstream misspelledFileStream(misspelledFile);

    if (!wordsFileStream || !paraFileStream)
    {
        cerr << "Error: Unable to open file\n";
        return;
    }

    unordered_set<string> dictionary;
    string word;
    while (wordsFileStream >> word)
    {
        dictionary.insert(word);
    }

    HashTable<string> hashTable(53); // Initial table size is 53

    while (wordsFileStream >> word)
    {
        hashTable.insert(word);
    }

    string paragraph((istreambuf_iterator<char>(paraFileStream)), istreambuf_iterator<char>());

    vector<string> misspelledWords;
    spellCheckParagraph(paragraph, hashTable, misspelledWords);

    for (const string &misspelledWord : misspelledWords)
    {
        misspelledFileStream << misspelledWord << endl;
    }

    misspelledFileStream.close();
    paraFileStream.close();
    wordsFileStream.close();

    cout << "Misspelled words count: " << misspelledWords.size() << endl;
}

// Function to spell check a paragraph entered by the user
void spellCheckByUserInput()
{
    // Your existing code for user-input spell checking here
    // Include the necessary functions and logic from the second code snippet
    // Adjust file handling or output as needed for user input
}

int main()
{
    int choice;
    cout << "Select spell-checking method:\n1. Spell check from file\n2. Spell check by user input\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        spellCheckFromFile("words.txt", "para.txt", "misspelled_words.txt");
        break;
    case 2:
        spellCheckByUserInput();
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }

    return 0;
}
