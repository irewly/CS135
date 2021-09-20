/*
 * Name: Irene Wang, 5005298618, Assignment 10
 * Description: The user will run the program with the second commandline
 * argument being the input filename. The program will read in a CSV 
 * formatted twitter file containing all of the tweets and relevant info 
 * of a twitter account through file stream. It will then cout the total 
 * number of tweets read and prompt the user to cin a keyword to search 
 * for. It will then cout the number of tweets that contain the keyword. 
 * The user will then cin another keyword and the program will cout the 
 * number of retweets for tweets that contain the keyword. The user will 
 * then cin yet another keyword and the program will cout all the tweets 
 * that contains the keyword to the terminal in a preset format. The user 
 * can then cin a output filename. The output file will be created 
 * containing all the tweets in the input file in a new format. The 
 * program will then cout the top 10 favorited and the least favorited 
 * tweet to the terminal,restate the total number of tweets read, and end 
 * the program.
 * Input: Input file name via commandline argument, three keywords, 
 * output file name.  
 * Output: Cout total number of tweets read, number of tweets and retweets
 * for corresponding keywords, all tweets containing third keyword. Create
 * output file containing all tweets in new format. Cout top 10 favorited
 * and least favorited tweets. 
 */
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

/* ***********************************************************************
 * class_identifier: This struct contains all the variables that
 * constitute parts of a single tweet. 
 * constructors: N/A
 * public members: string source, string text, string create_at,
 * string retweet_count, string favorite_count, string is_retweet,
 * string id_str (all are strings since getline can only read in strings,
 * converted to other datatypes as per need basis)
 * static members: N/A
* ************************************************************************/
struct Tweet{
    string Source;
    string text;
    string create_at;
    string retweet_count;
    string favorite_count;
    string is_retweet;
    string id_str;
};


//Function Prototypes:
string getSource(string source);
void setSource(Tweet& tweet, string source);
void printTweet(ostream& out, const Tweet& tweet);
void readTweets(char** argv, vector<Tweet>& tweets);
bool strFind(const string phrase, const string tweet);
int countTweets(const vector<Tweet>& tweets, const string phrase);
int countRetweets(const vector<Tweet>& tweets, const string phrase);
void phrasePrinter(const vector<Tweet>& tweets, const string phrase);
void fprintAllTweets(const string oName, const vector<Tweet>& tweets);
void swap(Tweet& L, Tweet& R);
void sortNprintByFavorite(ostream& cout, vector<Tweet>& tweets);

//Main Function:
int main(int argc, char * argv[]){
    string iName, oName;
    string phrase1, phrase2, phrase3;
    Tweet tweet;
    vector<Tweet> tweets;
    
    //program only runs if user puts two commandline arguments 
    //(first ./a.out, second input file name)
    if(argc == 2){
        //read in the CRV input file (file name accessed through argv[1])
        readTweets(argv, tweets);
        
        //for loop for converting all source weblinks to source types via setSource
        for(int j = 0; j < tweets.size(); j++){
            setSource(tweets[j],getSource(tweets[j].Source));
        }
        
        //prompt user to input first keyword search phrase
        cout << "Enter a Phrase to Count how many Tweets contain it: ";
        getline(cin,phrase1);
        cout << endl;
        cout << phrase1 << " Found in " << countTweets(tweets, phrase1) 
             << " Tweets! :o" << endl;
        
        //prompt user to input second keyword search phrase
        cout << "Enter Phrase to add all retweets of a tweet that"
             << " contains the given phrase: ";
        getline(cin,phrase2);
        cout << endl;
        cout << "There were " << countRetweets(tweets, phrase2)
             << " retweets of tweets containing the term '" << phrase2
             << "'!" << endl;

        //prompt user to input third keyword search phrase
        cout << "Enter a phrase to search for and print all tweets that"
             << " contain it: ";
        getline(cin,phrase3);
        cout << endl;
        cout << "Tweets with term '" << phrase3 << "':" << endl << endl;
        phrasePrinter(tweets,phrase3);
        cout << endl;

        //prompt user to input output file name
        cout << "Enter Name of File to Save all Tweets to: ";
        cin >> oName;
        fprintAllTweets(oName,tweets);
        cout << endl;

        //cout top 10 most favorited and least favorited tweet
        sortNprintByFavorite(cout, tweets);

        //restate number of tweets read and cout ending message
        cout << endl << endl;
        cout << "Total Tweets Read: " << tweets.size() << endl << endl;
        cout << "Thanks for Playing!" << endl;

    }

    //If user fails to put exactly two commandline arguments, cout error message
    else{
        cout << "Invalid Input File" << endl;
    }

    return 0;
}

//Function Definitions:

/* ***********************************************************************
 * function_identifier: This function will change the original source
 * string (web link) to a keyword (such as iPhone, Mobile, etc.) in the
 * struct tweet.
 * parameters: The originial string tweet.Source from struct Tweet 
 * (obtained through getline) and the new "source" keyword (through 
 * getSource function).
 * return value: None, void function
* ************************************************************************/
void setSource(Tweet& tweet, string source){
    tweet.Source = source;
};
/* ***********************************************************************
 * function_identifier: This function will match the original tweet.Source
 * (weblink) to a keyword "source" that denotes whether the tweet source 
 * is Mobile, Website, iPhone, Media Studio, or Other. 
 * parameters: The original tweet.Source string.
 * return value: The new "source" keyword string.
* ************************************************************************/
string getSource(string source){
    if(source == "https://mobile.twitter.com"){
        source = "Mobile";
    }
    else if(source == "https://www.twitter.com/"){
        source = "Website";
    }
    else if(source == "http://twitter.com/download/iphone"){
        source = "iPhone";
    }
    else if(source == "https://studio.twitter.com"){
        source = "Media Studio";
    }
    else{
        source = "Other";
    }
    return source;
};
/* ***********************************************************************
 * function_identifier: This function will print out a single tweet in the
 * designated format to a ostream source (cout or fout).
 * parameters: The ostream variable (cout/fout), the struct Tweet.
 * return value: None, void function
* ************************************************************************/
void printTweet(ostream& out, const Tweet& tweet){
    out << "Tweet Source: " << tweet.Source << endl;
    out << "Text: " << tweet.text << endl;
    out << "Created at: " << tweet.create_at << endl;
    out << "Retweet Count: " << tweet.retweet_count << endl;
    out << "Favorite Count: " << tweet.favorite_count << endl;
    //Check to see if the tweet is a retweet
    if(tweet.is_retweet == "false"){
        out << "Not a Retweet" << endl;
    }
    else{
        out << "Is a Retweet" << endl;
    }
    out << "ID STR: " << tweet.id_str << endl;
};
/* ***********************************************************************
 * function_identifier: This function will open the input tweets file
 * though ifstream. The input file name is denoted as the second 
 * commandline argument and passed in through argv. It read in the CSV 
 * formatted input file and store various components into variables in the
 * struct Tweet. getLine is used to read in pieces of the file with "," as 
 * delimiter and store the string into the corresponding variable. After 
 * all the variables of a single Tweet struct have been read in by 
 * getLine, the struct is then push_backed into the struct vector tweets 
 * (except for first one which is not a tweet but a header, thus not 
 * pushed into vector). After all of the structs(or tweets) have been 
 * read in, the last one is popped out of the vector and discarded since 
 * eof.() reads past the end of file (which means the loop runs one extra 
 * time). The vector size of "tweets" is used as initial tweet count and 
 * couted to the terminal.
 * parameters: The commandline array "argv", the Tweet struct vector
 * tweets
 * return value: None, void function
* ************************************************************************/
void readTweets(char** argv, vector<Tweet>& tweets){
    string iName;
    ifstream fin;
    Tweet tweet;
    iName = argv[1];
    fin.open(iName.c_str());
    //lCount (loop count) used to avoid reading in first line used for CSV
    //(which is not a tweet) into the vector
    int lCount = 0;
    
    //If file fails to open, cout error message
    if(fin.fail()){
        cout << "Invalid Input File" << endl;
    }
    //Otherwise, run getline to store tweet info into Tweet structs
    else{
        while(!fin.eof()){
            getline(fin,tweet.Source,',');
            getline(fin,tweet.text,',');
            getline(fin,tweet.create_at,',');
            getline(fin,tweet.retweet_count,',');
            getline(fin,tweet.favorite_count,',');
            getline(fin,tweet.is_retweet,',');
            getline(fin,tweet.id_str);
            if(lCount != 0){
                tweets.push_back(tweet);
            }
            lCount ++;
        }
        //removes last struct since .eof reads past end of file (which means
        //one extra "tweet" struct read in at the end)
        tweets.pop_back();
        cout << tweets.size() << " Tweets read" << endl;
    }
};
/* ***********************************************************************
 * function_identifier: This function will search through the tweet text
 * ("tweet") to see if it contains a keyword ("phrase"). This is done 
 * through nest for loops that compares the phrase and the tweet text
 * character by character. 
 * parameters: The user inputed keyword string "phrase", the tweet text
 * string "tweet".
 * return value: If all characters of "phrase" are found in "tweet", the 
 * function returns true, otherwise, the function returns false.
* ************************************************************************/
bool strFind(const string phrase, const string tweet){
    for(int i = 0; i < tweet.size(); i++){
        for(int j = 0; j < phrase.size(); j++){
            //Check to see if "phrase" is going out of "tweet" bounds, if
            //so, the word is not found and return false.
            if((i + j) > tweet.size()){
                return false;
                break;
            }
            //Otherwise, continue
            if(phrase[j] == tweet[i+j]){
                //signals that the entire array of phrase matches the section in tweet
                //found a match!
                if(j == phrase.size()-1){ 
                    return true;
                }
            }
            //If a character does not match, break out of loop and start looking with
            //the next character in tweet.
            else{
                break;
            }
        }          
    }
    return false;
};
/* ***********************************************************************
 * function_identifier: This function will count the number of tweets 
 * containing a keyword "phrase" through a for loop (which loops through
 * entire vector "tweets"). strFind is called to see if the tweet contains
 * the keyword, if it does, strFind will return true and tCount will
 * increase by 1.
 * parameters: The Tweet struct vector "tweets", the use inputed keyword
 * string "phrase".
 * return value: Returns the integer count value "tCount"
* ************************************************************************/
int countTweets(const vector<Tweet>& tweets, const string phrase){
    int tCount = 0;
    for(int j = 0; j < tweets.size(); j++){
        //tCount only increases when strFind returns true (found keyword phrase)
        if(strFind(phrase,tweets[j].text) == true){
            tCount ++;
        }
    }
    return tCount;
};
/* ***********************************************************************
 * function_identifier: This function will add the total number of 
 * retweets of tweets containing the keyword "phrase" through a for loop 
 * (which loops through entire vector "tweets"). strFind is called to see 
 * if the tweet contains the keyword, if it does, strFind will return true 
 * and the retweet_count of that tweet will be added to rTCount (which is 
 * the sum of retweet_count).
 * parameters: The Tweet struct vector tweets (which contains all tweets
 * (one tweet per struct) in the file ) and the user inputed keyword
 * string "phrase".
 * return value: The retweet count "rTCount"
* ************************************************************************/
int countRetweets(const vector<Tweet>& tweets, const string phrase){
    //rTCount used to store retweet_count sum
    long unsigned int rTCount = 0;
    for(int j = 0; j < tweets.size(); j++){
        //rTCount is updated by adding the retweet_count of each keyword
        //phrase containing tweet to the existing sum
        if(strFind(phrase,tweets[j].text) == true){
            rTCount = rTCount + stoi(tweets[j].retweet_count);
        }
    }
    return rTCount;
};
/* ***********************************************************************
 * function_identifier: This function will print out all tweets 
 * containing the third keyword string "phrase" to the terminal. It runs
 * all the tweets in the vector through a for loop and uses strFind to
 * see if a tweet contains the keyword "phrase". If it does, then the 
 * tweet will be printed out to the terminal in a designated format 
 * through printTweet function. If no tweets are found containing the
 * keyword, then a message will be couted to the terminal informing the
 * user about it.
 * parameters: The Tweet struct vector "tweets" and the user inputed 
 * keyword string "phrase".
 * return value: None, void function
* ************************************************************************/
void phrasePrinter(const vector<Tweet>& tweets, const string phrase){
    int counter = 0;
    for(int i = 0; i < tweets.size(); i++){
        if(strFind(phrase,tweets[i].text) == true){
            printTweet(cout, tweets[i]);
        }
        //If "counter" equals to tweets vector size, this means that every
        //single tweet in the vector have returned false by strFind, thus
        //there are no tweets in the file containing the keyword.
        else{
            counter ++;
            if(counter == tweets.size()){
                cout << "No Tweets found containing: '" << phrase << "'" << endl;
            }
        }
    }
};
/* ***********************************************************************
 * function_identifier: This function will print all the tweets in the 
 * input file to a user specified output file through ofstream. It runs
 * through the entire vector of "tweets" via a for loopand and prints out 
 * each tweet in the designated format to the output file through 
 * printTweet function.
 * parameters: The user specified output file name "oName", and the Tweet
 * struct vector "tweets".
 * return value: None, void function
* ************************************************************************/
void fprintAllTweets(const string oName, const vector<Tweet>& tweets){
    //open ofstream and use oName to create output file
    ofstream fout;
    fout.open(oName.c_str());
    //print all tweets to output file
    for(int i = 0; i < tweets.size(); i++){
        printTweet(fout,tweets[i]);
    }
};
/* ***********************************************************************
 * function_identifier: This function is used by sortNprintByFavorite 
 * function for bubble sort swapping of structs.
 * parameters: The Tweet struct on the left and the Tweet struct on the
 * right when performing sorting comparisons
 * return value: None, void function
* ************************************************************************/
void swap(Tweet& L, Tweet& R){
    Tweet temp = L;
    L = R;
    R = temp;
};
/* ***********************************************************************
 * function_identifier: This function uses bubble sort to sort out the 
 * top 10 Tweet structs with the highest favorite_counts as well as the
 * Tweet struct with the lowest favorite_count. The highest counts are 
 * sorted in a non-descending manner and the loop stops as soon as it have
 * the top 10 sorted to the end of the vector (to save time). The lowest
 * count is sorted in a non-acending manner and the loop stops as soon as
 * it has the lowest one sorted to the end of the vector. In the case that
 * there are multiple lowest favorite_counts, an additional search is
 * performed so that the one with the lowest retweet_count is selected. 
 * Both the top ten and the least favorited are couted to the terminal.
 * parameters: The ostream variable (in this case cout), and the Tweet
 * struct vector "tweets".
 * return value: None, void function
* ************************************************************************/
void sortNprintByFavorite(ostream& cout, vector<Tweet>& tweets){
    //Non-descending bubble sort for top 10 most favorited tweets only
    //(bubbled at the end)
    for(int x = 0; x < 10; x++){
        for(int index = 0; index < tweets.size()-1-x; index++){
            if(stoi(tweets[index + 1].favorite_count) < stoi(tweets[index].favorite_count))
            {
                swap(tweets[index + 1], tweets[index]);
            }
        }
    }
    cout << "Top 10 Favorited Tweets:" << endl << endl;
    for(int i = 0; i < 10; i ++){
        printTweet(cout,tweets[(tweets.size()-1)-i]);
    }
    cout << endl;

    //Non-ascending bubble sort for least favorited tweet only (bubbled at the end)
    for(int x = 0; x < 1; x++){
        for(int index = 0; index < (tweets.size()-1)-x; index++){
            if(stoi(tweets[index + 1].favorite_count) > stoi(tweets[index].favorite_count))
            {
                swap(tweets[index + 1], tweets[index]);
            }
            //additional sorting for tweets with same number of favorite_count
            //non-ascending order for retweet_count
            if(stoi(tweets[index + 1].favorite_count) == stoi(tweets[index].favorite_count))
            {
                if(stoi(tweets[index + 1].retweet_count) > stoi(tweets[index].retweet_count))
                {
                    swap(tweets[index + 1], tweets[index]);
                }
            }
        }
    }
    cout << "Least Favorited Tweet:" << endl << endl;
    printTweet(cout,tweets[tweets.size()-1]);
};

