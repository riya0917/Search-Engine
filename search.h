//----------------------------------------------------------------------------------------------------------------
// Program 2: Search
// Course: CS 251, Fall 2023, UIC
// Professor: Ethan Ordentlich
// Author: Riya Patel
// The search project is intended to take a data file and process the key words and associating URL
// It is intended to organize the data into a map, and based on user input on what word they are trying to output,
// The program is supposed to print the corresponding URl
//----------------------------------------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
using namespace std;


//This function is intended to clean the string from leading or trailing punctuation
//Parameters include a string that is going to be cleaned
//Returns the cleaned string with no trailing and leading punctuation
string cleanToken(string s) {
    string cleanS = "";
    int start = 0, end = s.length() - 1;
    bool alpha = false;

    //checks for leading punctuation
    while(ispunct(s[start])){
        start++;
    }
    //looks for trailing punctuation
    while(ispunct(s[end])){
        end--;
    }

    //enters the new string with no extra punct to a new string
    for(int i = start; i <= end; i++){
        cleanS += s[i];
    }
    
    //checks if each character is an alphabet, and converts it to lowercase
    for(int i = 0; i < cleanS.length(); i++){
        if(isalpha(cleanS[i])){
            alpha = true;
            cleanS[i] = tolower(cleanS[i]);
        }
    }
    //if the string has been cleaned, return the cleaned string else return an empty string
    if(alpha){
        return cleanS;
    }else{
        cleanS = "";
        return cleanS;
    }
}

//sepetares each word from a string
//Parameters include a string which is then parsed through
//returns the set of strings
set<string> gatherTokens(string text) {
    set<string> tokens;
    string writtenText;
    
    stringstream stream;
    stream << text;

    while(stream >> writtenText){
        //clean each word found in the text
        string tokenCleaned = cleanToken(writtenText);
        //if a token is returned, insert it into a set
        if(!tokenCleaned.empty()){
            tokens.insert(tokenCleaned);
        }
    }
    return tokens;
}

//This function is intended to build an index of terms and associated URLs from a file
//Parameters include a filename to read data from, and a map where the index will be stored.
//Returns the number of documents indexed
int buildIndex(string filename, map<string, set<string> >& index) {

    ifstream file;
    file.open(filename);
    string url, text;

    set<string> eachToken; // A set to hold individual tokens from the text
    int numDoc = 0;
    if(!file.is_open()){
        return 0;
    }
    while(!file.eof()){
        //read the url and text for the data
        getline(file, url);
        getline(file, text);

         // Tokenize the text into individual words
        eachToken = gatherTokens(text);

        // Iterate through each token and associate it with the URL in the index
        for(auto& item : eachToken){
            if(url != ""){
                // Insert the URL into the set associated with the token
                index[item].insert(url);
            }
        }
        if(!url.empty()){
            numDoc++;
        }
    }
    // Return the total number of documents processed
    return numDoc;
}


//Function to find query matches based on index and a query sentence
//Parameters include a map of keywords to sets of URL, and a sentence to find in the query
//Returns a set of matching URL based on the query
set<string> findQueryMatches(map<string, set<string> >& index, const string& sentence) {
    set<string> result;
    
    stringstream str;
    string eachWord;
    str << sentence;
    //for each word in the sentence
    while(str >> eachWord){
        //performs search intersection
        if(eachWord[0] == '+'){
            eachWord = cleanToken(eachWord);
            set<string> intersect;
            set_intersection(result.begin(), result.end(), index.at(eachWord).begin(), index.at(eachWord).end(), inserter(intersect ,intersect.begin()));
            result = intersect;
        //performs set difference
        }else if(eachWord[0] == '-'){
            eachWord = cleanToken(eachWord);
            set<string> difference;
            set_difference(result.begin(), result.end(), index.at(eachWord).begin(), index.at(eachWord).end(), inserter(difference ,difference.begin()));
            result = difference;
        //performs set unionbec
        }else if(isalpha(eachWord[0])){
            eachWord = cleanToken(eachWord);
            set<string> setUnion;
            set_union(result.begin(), result.end(), index.at(eachWord).begin(), index.at(eachWord).end(), inserter(setUnion ,setUnion.begin()));
            result = setUnion;
        }
    }
    return result;
}


//Combine each function to create a working search engine
//Parameters include a file that is going to be searched through
void searchEngine(string filename) {
    cout << "Stand by while building index...\n";
    map<string, set<string> > idx; 
    //Calls the build index function to figure out the number of pages and number of unique terms
    int numPages = buildIndex(filename, idx);
    cout << "Indexed " << numPages  << " pages containing "  <<  idx.size()  << " unique terms" << endl;
    bool run = true;
    string userInput;
    set <string> results;

    //while user wants to continue searching the directory
    while(run){
        cout << endl << "Enter query sentence (press enter to quit): ";
        getline(cin, userInput);
        if(userInput == ""){
            run = false;
        }else{
            //look through the query to find the specific words
            results = findQueryMatches(idx, userInput);
            cout << "Found " << results.size() << " matching pages" << endl;
            //print out the url for each mathcing query word
            for(string item: results){
                cout << item << endl;
            }
        }      
    }
    cout << "Thank you for searching!";
}

