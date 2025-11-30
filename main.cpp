#include <iostream>
#include "Account.h"
using namespace std;


  int main() {
    srand(time(0)); //seed time in main so passwords come out different when provided the same length.
    //initialize all Accounts.
    Account a("Matthew");
    a.Make_Password(9);
    Account b("Isabella");
    b.Make_Password(10);
    Account c("Johnny");
    c.Make_Password(11);
    Account d("Peter");
    d.Make_Password(10);
    Account e("Kevin");
    e.Make_Password(11);
    Account f("Joe");
    f.Make_Password(9);
     Account g("lanier");
    g.Make_Password(9);
    Account h("Grant");
    h.Make_Password(10);
    Account i("Lisa");
    i.Make_Password(11);
    Account j("Tori");
    j.Make_Password(10);
    Account k("Michael");
    k.Make_Password(11);
    Account l("Jaxon");
    l.Make_Password(9);

   //Display all account information
   cout << a.to_string();
   cout << "\n";
   cout << b.to_string();
   cout << "\n";
   cout << c.to_string();
   cout << "\n";
   cout << d.to_string();
   cout << "\n";
   cout << e.to_string();
   cout << "\n";
   cout << f.to_string();
   cout << "\n";

  
    //Make account a follow all users
    a.follow(b.get_username());
    a.follow(c.get_username());
    a.follow(d.get_username());
    a.follow(e.get_username());
    a.follow(f.get_username());
    a.follow(g.get_username());
    a.follow(h.get_username());
    a.follow(i.get_username());
    a.follow(j.get_username());
    a.follow(k.get_username());
    a.follow(l.get_username());

    cout << "User " << a.get_username() << " after following account's " << b.get_username() 
    << ", " << c.get_username() << ", " << d.get_username() << ", " << e.get_username() << ", " << f.get_username() 
    << ", " << g.get_username() << ", " << h.get_username() << ", " << i.get_username() << ", " << j.get_username() 
    << ", " << k.get_username() << ", " << l.get_username()  
    << endl;
    //Display updated user a info
    cout << a.to_string();
    //Display user a following
    cout << a.get_following();
    cout << "\n";
    cout << "\n";
    //Search for "er in users"
    cout << "Search for er" << endl;
    cout << a.get_following("er");
    cout << "\n";
    cout << "\n";
    cout << "Now unfollow "<< d.get_username() << endl;
    a.unfollow(d.get_username());
    //Unfollow accounts and display updated user a
    cout << a.to_string();
    cout << a.get_following();
    cout << "\n";
    cout << "\n";
    //try following an account that is already followed
    cout << "Try following "<< b.get_username() << endl;
    a.follow(b.get_username());
    cout << "\n";
    //try to unfollow an account that is already unfollowed
    cout << "Now try unfollowing " << d.get_username() << endl;
    bool unfollowalpha;
    unfollowalpha = a.unfollow(d.get_username());
    if (unfollowalpha == false)
    {
      cout << "Already unfollowed" << endl;
    }
    


    
    return 0;
  }