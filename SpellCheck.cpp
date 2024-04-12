#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath> // Changed from <math.h> to <cmath>
using namespace std;

int linearP(string table[], int i, int n) {
    while (table[i].length() > 0) {
        i++;
        if (i >= n) { // Changed > to >= for correct condition
            i = i % n;
        }
    }
    return (i % n);
}

int main() {
    int choice = 1;
    cout << "*Linear Probing is taken as choice for Collision resolution Technique*\n\n";
    int tbsize = 100;
    string currWord, wordfile;
    cout << "Enter the name of the word file: ";
    cin >> wordfile;
rehash:
    vector<string> table(tbsize); // Changed from string array to vector
    int s = 0;
    int sz = 0;
    int location = 0;
    int count = 0;
    double fac = 0;
    ifstream words(wordfile);
    while (words >> currWord) {
        s = 0; // Moved inside the loop to reset for each word
        for (int i = 0; i < currWord.length(); i++) {
            s += int(currWord[i]) * (i+1); // Changed (i) to (i+1) for non-zero multiplication
        }
        if (table[s % tbsize].length() > 0) {
            if (choice == 1) {
                location = linearP(&table[0], s % tbsize, tbsize); // Passed vector pointer to linearP
            }
        } else {
            location = s % tbsize;
        }
        table[location] = currWord;
        count++;
        fac = static_cast<double>(count) / tbsize; // Removed unnecessary cast to double
        if (fac > 0.5) {
            cout << "Load Factor has exceeded 0.5. So, Increasing the Table size" << endl;
            cout << "--------------------------------" << endl;
            tbsize = tbsize * 2;
            cout << "New Table Size is: " << tbsize << endl;
            words.close();
            cout << "--------------------------------" << endl;
            cout << "Again Rehashing all words " << endl;
            cout << "--------------------------------" << endl;
            goto rehash;
        }
    }
    cout << "Final tbsize:" << tbsize << endl;
    cout << endl;
    string inputfile, searc;
    int countn = 0;
    cout << "Enter the name of the input file: ";
    cin >> inputfile;
    ifstream fin(inputfile);
    cout << "\nThe contents of the file are: \n";
    while (getline(fin, searc)) {
        cout << searc << endl; // Changed std::cout to cout
    }
    fin.close();
    fin.open(inputfile);
    cout << endl;
    while (fin >> searc) {
        sz = 0;
        for (int i = 0; i < searc.length(); i++) {
            sz += int(searc[i]) * (i+1); // Changed (i) to (i+1) for non-zero multiplication
        }
        if (table[sz % tbsize] != searc) {
            int y = sz;
            if (choice == 1) {
                while (table[y % tbsize].length() > 0 && table[y % tbsize] != searc) { // Added condition for not equal
                    y++;
                }
                if (table[y % tbsize] == searc) {
                    continue;
                }
                cout << searc << " is either not in the table or spelled incorrectly" << endl;
                countn++;
            }
        }
    }
    cout << "\nNo. of wrongly spelled words: " << countn << endl;
    return 0; // Added return statement to indicate successful execution
}
