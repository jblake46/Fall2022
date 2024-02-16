/*
 * Name: Blake Moore
 * Date Submitted: 10.7.2022
 * Lab Section: 
 * Assignment Name: Spell Checker Using a Hash Table
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
 /*
 int main()
 {
    vector<string> tmp;
    Stringset words;

    loadStringset(words, "wordlist.txt");
    tmp = spellcheck(words, "lake");

    for(int i=0; i < tmp.size(); i++)
    {
        std::cout << tmp.at(i) << endl;
    }
    cout << tmp.size() << endl;



    testStringset(words);
    return 0;
 }
 */
 
 
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 void loadStringset(Stringset& words, string filename)
 {

    string word;
    ifstream inputFile;
    inputFile.open(filename);
    //reading in every word from the file
    while(getline(inputFile, word))
    {
        //edge case for the very first word adding to the file
        if(words.getNumElems() == 0)
        {
            words.insert(word);
        }
        //determines if the word is already in the words hash
        if(!words.find(word))
        {
            //if its not in the hashset, it should insert
            words.insert(word);
        }
    }
 }
 
 vector<string> spellcheck(const Stringset& words, string word)
 {
    //int value for the other 25 values of the alphabet
    int numLettersInAbc = 26;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    //length of word
    int length = word.length();
    //tmp variable to be able to compare the word 
    //and still have access to the original word
    vector<string> alternatives;
    string tmpWord = word;
  
    //iterates through each letter of the word
    for(int i = 0; i < length; i ++)
    {
        //iterates throught the alphabet
        for(int j = 0; j < numLettersInAbc; j++)
        {
            //changes the letter in the word
            tmpWord[i] = alphabet[j];
            //if tmpWord is a valid word and it is not
            //the original word
            if(words.find(tmpWord) && tmpWord != word)
            {
                //adds tmpWord to the alternatives vector
                alternatives.push_back(tmpWord);
                                        
            }
            //resetting tmpWord to the original word
            tmpWord = word;
        }
    }

    return alternatives;
 }