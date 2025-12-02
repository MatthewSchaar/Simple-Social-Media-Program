#include "Account.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Initialize static member
vector<Account*> Account::allAccounts_;

//constructor for username
Account::Account(const string& username)
{
    this->username_ = username;
    this->nFollowers_ = 0;
    // Add this account to the list of all accounts for trending
    allAccounts_.push_back(this);
}
//constructor for password
string Account::Make_Password(int length)
{
    //see if length is between certain parameters
if (length < 8 || length > 12)
    {
    cout << "Password Length must be within 8 to 12 characters"
    << endl; 
    return "";

    //if length is within parameters initiate password generation
    }   else 
        {
            //initialize password array
            string password[length] = {""};
            
            //start a postion tracker
        int pos = 0;
       
        //begin first loop for password letter generation until position is not less then length
         for (int i = 0; pos < length; i++)
        {
                //initialize a random digit and turn it it aski value into a char then move into password postion then increment password position         
                int Randomdigit = rand() % (38 - 35 + 1) + 35; //[38,35]
                password[pos] = (char)Randomdigit;
                pos++;  
            //check position so generation does spill over
                if (pos < length) 
                {
                    //initialize a random uppercase askivalue and turn into a char then move into the next array element then increment
                    int Randomuppercase = rand() % (90 - 65 + 1) + 65; // [90,65]
                    password[pos] = (char)Randomuppercase;
                    pos++;
                }
            //check again to prevent over generation
                if (pos < length) 
                {
                //initialize a random lowercase askivalue then turn into a char and move into next array element and increment again
                int Randomlowercase = rand() % (122 - 97 + 1) + 97; //[122,97]
                password[pos] = (char)Randomlowercase;
                pos++;
                }
                //restart the loop until first password is generated
        }
        //once first password is generated roll a die of 6 and if die is greater then 3 then initialize a randomizer

          int Randompos1 = rand() % 7;
          if (Randompos1 > 3)
          {
           //begin loop until length of password
            for (int i = 0; i < length; i++)
        {
           //roll another die to determine which decision to make for the first position of i and so on until array is filled.
            int Randompos = rand() % 7;
            if(Randompos <= 2)
            {
                //if second die is less then or equal to 2 then make a random digit into an aski value and replace password element with it
                int Randomdigit = rand() % (38 - 35 + 1) + 35;
                 string aski = string(1 , (char)Randomdigit);
                password[i] = aski;
            }
            //if second die is greater than 2 and less than or equal to 4 then make a random uppercase value into an aski value and replace password element with it
            else if(Randompos > 2 && Randompos <=4)
            {
                int Randomuppercase = rand() % (90 - 65 + 1) + 65;
                 string aski2 = string(1 , (char)Randomuppercase);
                 password[i] = aski2;
            }
            //if second die is greater than 4 and less than or equal to 6 then make a random lower case value into an aski value and replace password element with it
            else if (Randompos > 4 && Randompos <=6)
            {
                int Randomlowercase = rand() % (122 - 97 + 1) + 97;
                 string aski3 = string(1 , (char)Randomlowercase);
                 password[i] = aski3;
            }   
           
            
        }

          }
          //initiate a final password swapper than swaps each element of password with a random value of password
          for (int i = 0; i < length; i++)
          {
            int swapper = rand() % length;
            swap(password[i] , password[swapper]);

          }
          //finally add up password into finalpassword and return it as well as store password into private data
            string finalPassword;
            for (int i = 0; i < length; i++)
            {
                finalPassword += password[i];
            }
            password_ = finalPassword;
            return finalPassword;
        }
}

string Account::get_password() const
{
    return password_;
}

 string Account::get_username() const
 {
    return username_;
 }
//to stream to print account information
string Account::to_string() const
{
ostringstream oss;
oss << "The user " << get_username() << " has " << get_password() << " as their password and is following " << get_nfollowing()  
<< " Accounts." << endl;
return oss.str();
}
//follow function
bool Account::follow(const string& username)
{
    //first check if account already follows username if it does return false
    for (unsigned i = 0; i < following_.size(); i++)
    {   
        if (following_[i] == username)
        {
            cout << "The account is already following " << username << endl;
            return false;
        }

    }
    //if not following then initiate follow by putting username in a vector of following and return true
    following_.push_back(username);
    nFollowing_ = following_.size();
    
    // Increment the follower count of the followed user
    Account* followedAccount = find_account(username);
    if (followedAccount != nullptr) {
        followedAccount->add_follower();
    }
    
    return true;
    
}
//unfollow function
bool Account::unfollow(const string& username)
{
    //first loop to check elements of following to see if username is included then initiate unfollow and return true
    for (unsigned i = 0; i < following_.size(); i++)
    {   
        if (following_[i] == username)
        {
            following_.erase(following_.begin() + i);
            nFollowing_ = following_.size();
            
            // Decrement the follower count of the unfollowed user
            Account* unfollowedAccount = find_account(username);
            if (unfollowedAccount != nullptr) {
                unfollowedAccount->remove_follower();
            }
            
            return true;
        } 
         
    }
    //if not following to begin with simply return false
    
     return false;

}
//gets number of following
unsigned Account::get_nfollowing() const
{
return following_.size();
}
//get each user who is following an account and display
string Account::get_following(const string& key) const
{
    //initialize result outstream bool flag and counter
    cout << "The user is following: \n";
    string result = "";
    ostringstream oss;
    bool match = false;
    int counter = 0;
    //begin to search for key passed in function and check to see if its in the following vector
    for (unsigned i = 0; i < following_.size(); i++ )
    {   
        string users = following_[i]; 
        if (key == "" || users.find(key) != string::npos)
        {
            //if found key in following_ print then set bool flag to true and add to coutner for every username printed
            oss << left << setw(18) << users;
            match = true;
            counter++;
            //if 4 usernames have been printed then end the line to add space for more users in the list.
            if(counter % 4 == 0)
            {
                oss << "\n";
            }
        } 

        // if bool flag has no match then there are no usernames 
    }
        if (!match)
        {
         return "No matching users found.";
        }
        return oss.str();
}

//get number of followers
unsigned Account::get_nfollowers() const
{
    return nFollowers_;
}

//add a follower to this account
void Account::add_follower()
{
    nFollowers_++;
}

//remove a follower from this account
void Account::remove_follower()
{
    if (nFollowers_ > 0) {
        nFollowers_--;
    }
}

//find an account by username
Account* Account::find_account(const string& username)
{
    for (unsigned i = 0; i < allAccounts_.size(); i++) {
        if (allAccounts_[i]->get_username() == username) {
            return allAccounts_[i];
        }
    }
    return nullptr;
}

//show trending accounts sorted by number of followers
string Account::show_trending(int limit)
{
    ostringstream oss;
    oss << "=== TRENDING ACCOUNTS ===" << endl;
    
    if (allAccounts_.empty()) {
        oss << "No accounts found." << endl;
        return oss.str();
    }
    
    // Create a copy of all accounts for sorting
    vector<Account*> sortedAccounts = allAccounts_;
    
    // Sort accounts by number of followers in descending order
    sort(sortedAccounts.begin(), sortedAccounts.end(), 
        [](Account* a, Account* b) {
            return a->get_nfollowers() > b->get_nfollowers();
        });
    
    // Limit to the specified number of trending accounts
    int count = 0;
    for (unsigned i = 0; i < sortedAccounts.size() && count < limit; i++) {
        count++;
        oss << count << ". " << left << setw(15) << sortedAccounts[i]->get_username() 
            << " - " << sortedAccounts[i]->get_nfollowers() << " followers" << endl;
    }
    
    return oss.str();
}