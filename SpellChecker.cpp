#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Searcher is used to store the word whose spelling is to be checked or which is to be found in the table
string searcher;

// Function to implement Linear Probing
int linearProbe(string table[], int i, int n);

// Function to implement quadratic probing
int quadProbe(string table[], int i, int n);

int main()
{
  // Variable to choose linear or quadratic probing
  int choice = 0;

  cout << "Enter the choice of the probing technique:\t 1: Linear Probing\t 2: Quadratic Probing" << endl;

  cin >> choice;
  // Initially starting with a hashtable of size 53 as required by the problem definition
  int tablesize = 53;

  // The Start label is used to rehash the words again in case the load factor increases beyond 0.5
start:

  // The Hash Table by the name table, with a size of tablesize
  if (tablesize > 0)
  {
    string table[tablesize];
    for (int i = 0; i < tablesize; i++)
    {
      table[i] = "";
    }
    int s = 0;
    int sz = 0;

    // Variable to store the number of collisions
    int collisions = 0;

    // Variable which probes the table incase of a collision
    int location = 0;

    // File operation variable to read from the file
    ifstream f;
    int count = 0;
    // Variable to calculate the load factor
    double fac = 0;
    // Getting the currentWord from the file
    string currWord;

    // Opening the file containing all the 100 words as required
    f.open("loop.txt");

    if (f.is_open())
    {
      // Run the loop until the end of file is not reached
      while (f >> currWord)
      {
        // The Hash Function, calculates the key of each word by multiplying each ASCII value with it's location

        // Eg: in "abc": Hash Function: (Ascii(a) * 0 + Ascii(b) * 1 + Ascii(c) * 2 )
        for (int i = 0; i < currWord.length(); i++)
        {
          // Calculating the value of key for each word
          s += int(currWord[i]) * (i);
        }

        // Checking For collision of the word
        if (table[s % tablesize] != "")
        {
          // Calculating the total number of collisions
          collisions += 1;
          if (choice == 1)
          {
            // Linear Probing for collision resolution
            location = linearProbe(table, s % tablesize, tablesize);
          }
          else if (choice == 2)
          {
            // Quadratic Probing for collision resolution
            location = quadProbe(table, s % tablesize, tablesize);
          }
        }
        else
        {
          // If No collision, Just add the word at the location, Key Modulo TableSize
          location = s % tablesize;
        }

        // Store the word at the location after probing
        table[location] = currWord;

        // Increase the number of words stored in table to calculate load factor
        count++;

        // Calculate Load Factor
        fac = static_cast<double>(count) / static_cast<double>(tablesize);

        if (fac > 0.5)
        {
          cout << "The Load Factor has exceeded 0.5" << endl;
          cout << "-------------------------------------------------------" << endl;

          cout << "Increasing the Table size" << endl;
          cout << "-------------------------------------------------------" << endl;
          tablesize = tablesize * 2;

          cout << "New Table Size is: " << tablesize << endl;
          f.close();
          cout << "-------------------------------------------------------" << endl;
          cout << "Rehashing all words again" << endl;
          cout << "-------------------------------------------------------" << endl;
          goto start;
        }

        s = 0;
      }

      f.close();
    }
    else
    {
      cout << "Error: Unable to open the file." << endl;
      return 1;
    }

    if (choice == 1)
    {
      cout << "Number of Collisions in Linear Probing is:" << collisions << endl;
      cout << endl;
    }
    else
    {
      cout << "Number of Collisions in Quadratic Probing is:" << collisions << endl;
      cout << endl;
    }

    cout << "Final TableSize:" << tablesize << endl;
    cout << endl;

    // Variable to store the number of words you want to search/check
    int n1 = 0;
    cout << "Enter the number of words you want to search in the table" << endl;
    cin >> n1;
    cin.ignore();
    while (n1 > 0)
    {
      sz = 0;
      cout << "Enter a Word to search:" << endl;
      getline(cin, searcher);

      // Calculating the hash key for the word entered
      for (int i = 0; i < searcher.length(); i++)
      {
        sz += int(searcher[i]) * (i);
      }

      // Searching the table
      if (table[sz % tablesize] == searcher)
      {
        cout << "Your Word is in the table" << endl;
        cout << "The Spelling for the word you entered is correct" << endl;
        cout << endl;
      }
      else
      {
        // Else It may have happened that the word would have suffered a collision and would have been probed
        int y = sz;
        int qaz = 1;

        // Doing a quadratic probe for a maximum number of 20 successive collisions
        if (choice == 2)
        {
          int f = 0;

          while (qaz != 20 && table[y % tablesize] != "")
          {
            y = sz + static_cast<int>(pow(qaz, 2));
            if (table[y % tablesize] == searcher)
            {
              cout << "Found the word, it is spelled correctly but suffered a collision" << endl;
              f = 1;
              break;
            }
            else
            {
              qaz++;
            }
          }
          if (f == 0)
          {
            cout << "Your word is either not in the table or spelled incorrectly" << endl;
          }
        }
        else if (choice == 1)
        {
          int y = sz;
          int f = 0;

          // If linearly probed, the word has be within the next blank entry of the table
          while (table[y % tablesize] != "")
          {
            if (table[y % tablesize] == searcher)
            {
              cout << "Found the word, it is spelled correctly but suffered a collision" << endl;
              f = 1;
              break;
            }
            y++;
          }
          if (f == 0)
          {
            cout << "Your word is either not in the table or spelled incorrectly" << endl;
          }
        }
      }
      n1--;
    }
  }
  else
  {
    cout << "Error: Invalid table size." << endl;
    return 1;
  }

  return 0;
}

int linearProbe(string table[], int i, int n)
{
  // Function to implement linear probing
  while (table[i] != "")
  {
    i++;
    if (i >= n)
    {
      i = 0;
    }
  }
  return i;
}

int quadProbe(string table[], int i, int n)
{
  int sq = 1;
  int j = i;
  // Function to implement Quadratic probing
  while (table[j] != "")
  {
    j = (i + static_cast<int>(pow(sq, 2))) % n;
    sq++;
  }
  return j;
}