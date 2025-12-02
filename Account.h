//This file contains the definition of the Account class. Do not change anything in this file.

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
using namespace std;

class Account {
  private:
    string username_;
    string password_;
    vector<string> following_; //to store the usernames of all accounts followed by the current account owner
    unsigned nFollowing_;  //number of people followed by this account
    unsigned nFollowers_;  //number of followers this account has
    static vector<Account*> allAccounts_; //static vector to track all accounts for trending
  public:

  
    //constructors
    Account(const string& username);
    string Make_Password(int length);

  

    //Accessors
    string get_password() const;
    string get_username() const;
    string get_following(const string& key = "") const; 
    unsigned get_nfollowing() const;
    unsigned get_nfollowers() const;
    string to_string() const;
    
    

    //mutator
    bool follow(const string& username);
    bool unfollow(const string& username);
    void add_follower();
    void remove_follower();
    
    //static function for trending
    static string show_trending(int limit = 5);
    static Account* find_account(const string& username);
};

#endif



