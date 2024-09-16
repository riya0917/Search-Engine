#include "search.h"
using namespace std;

//checks if the string is being cleaned properly
bool testCleanToken() {
  string ans = "hello";
  int pass = 0, fail = 0;

  ans == cleanToken(".hello") ? ++pass : ++fail;
  ans == cleanToken("...hello") ? ++pass : ++fail;
  ans == cleanToken("...hello...") ? ++pass : ++fail;
  ans == cleanToken("...hello123   ") ? ++pass : ++fail;
  ans == cleanToken("123") ? ++pass : ++fail;
  

  return 0 == fail;
}

//test gather token function which seperates each word in the sentence into it's own token
bool testGatherToken(){
    int pass = 0, fail = 0;
    set<string> answer1;
    answer1.insert("hey");
    answer1.insert("there");
    answer1.insert("insert");
    answer1.insert("this");
    answer1.insert("token");

    answer1 == gatherTokens("hey hey there there THere INSERT this this ThiS Token") ? ++pass : ++fail;
    answer1 == gatherTokens("hey there insert this! token!!!!") ? ++pass : ++fail;
    answer1 == gatherTokens("hey!!! hey!!! there...  this   token   ") ? ++pass : ++ fail;

    return 0 == fail;
}

void testBuildIndex(){
    string filename = "tiny.txt";  // Change to the path of your sample text file
    map<string, set<string> > index;

    // Call the buildIndex function to build the index
    int numDocuments = buildIndex(filename, index);
    int count = 0;
    //check if the correct num of documents were added
    if (numDocuments == 4) {
        cout << "buildIndex built successfully!" << endl;
        cout << "Number of documents processed: " << numDocuments << endl;
    
        // Print the index 
        cout << "Index contents:" << endl;
        for (auto& entry : index) {
            count++;
        }
    
        if(count == 20){
            cout << "Success every word was added with its matching url" << endl;
        }else{
            cout << "Failed, every word was not added" << endl;
        }
    }else{
        cout << "Failed, the txt file did not open" << endl;
    }
}



//tests various differenct combinations of words to see if it matches the expected answer
bool testFindQueryMatches(){
    int pass = 0, fail = 0;
    map<string, set<string> > test;

    
    buildIndex("tiny.txt", test);
    set<string> test1, test2, test3, test4, test5;

    //test just a regular word
    test1.insert("www.shoppinglist.com");
    test1.insert("www.dr.seuss.net");
    test1.insert("www.rainbow.org");
    test1 == findQueryMatches(test, "green fish") ? ++pass : ++fail;

    //test set intesection
    test2.insert("www.dr.seuss.net");
    test2 == findQueryMatches(test, "blue +fish") ? ++pass : ++fail;

    //test set differences
    test3.insert("www.ranbow.org");
    test3 == findQueryMatches(test, "green -fish") ? ++pass : ++fail;

    //tests for multiple wordsv
    test4.insert("www.bigbadwolf.com");
    test4.insert("www.dr.seuss.net");
    test4.insert("www.rainbow.org");
    test4.insert("www.shoppinglist.com");
    test4 == findQueryMatches(test, "green blue fish eat") ? ++pass : ++fail;

    //test multiple words with +/-
    test5.insert("www.ranbow.org");
    test5.insert("www.bigbadwolf.com");
    test5 == findQueryMatches(test, "green +blue -fish eat") ? ++pass : ++fail;
    return 0 == fail;
}

int main() {

//    //test clean token function
//     if(testCleanToken){
//         cout << "cleanTokens produces the CORRECT output" << endl;
//     }else{
//         cout << "cleanTokens produces the INCORRECT output" << endl;
//     }

//     //test gather token function
//     if(testGatherToken){
//         cout << "gatherTokens produces the CORRECT output" << endl;
//     }else{
//         cout << "gatherTokens produces the INCORRECT output" << endl;
//     }
//     // test find query funcion
//     if(testFindQueryMatches){
//         cout << "findQueryMatches produces the CORRECT output" << endl;
//     }else{
//         cout << "findQueryMatches produces the INCORRECT output" << endl;
//    }
//    //checks if the txt file was
//     testBuildIndex();

//     cout << endl;

    //run search engine
        string filename;
        getline(cin, filename);
        searchEngine(filename);


    return 0;
}