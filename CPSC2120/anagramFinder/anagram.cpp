/*
 * Name: Blake Moore
 * Date Submitted: Oct 27
 * Assignment Name: single Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

/*
int main()
{
    vector<string> words;
    vector<string> anagrams;
    string inputWord;
    words=loadWordlist("wordlist.txt");
    cout << "Find single-word anagrams for the following word: ";
    cin >> inputWord;
    anagrams = anagram(inputWord, words);
    for (int i=0; i<anagrams.size(); i++)
    {
        cout << anagrams[i] << endl;
    }
    return 0;
}
*/

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Implement this function
vector<string> anagram(string word, vector<string> wordlist)
{

    //create unordered map for the strings
    unordered_map<string, vector <string>> map;
    //creating needed variables
    string masterKey;
    string currentWord;
    string currentWordKey;
    vector<string> properAnagrams;

    //making a copy of word to be sorted
    string sortedWord = word;
    //sorting to make each word abc sorted, 
    //that way any anagram sorted will fall into the same
    //bucket
    sort(sortedWord.begin(), sortedWord.end());
    masterKey = sortedWord;
    //iterates through the wordlist
    // creates a key for each word 
    // then adds them to the map
    for(int i = 0; i < wordlist.size(); i ++)
    {
        currentWord = wordlist[i];
        //creating variable to store sorted current word
        string currentWordSorted = currentWord;
        sort(currentWordSorted.begin(), currentWordSorted.end());
        currentWordKey = currentWordSorted;
        map[currentWordKey].push_back(currentWord); 
    }
    //returns all anagrams that have been created
    //via a vector of strings
    return properAnagrams = map[masterKey];
}