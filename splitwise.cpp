#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<string>

using namespace std;

 int idCount=0;

class User{
    int id;
    string firstName;
    string lastName;
    string email;
    int mobileNumber;
    unordered_map<int, double> expenseMap;
    protected:
    static int cnt;
    public:
    User(){

    }

    User(string firstName, string lastName, string email, int mobileNumber){
        this->id = ++(cnt);
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
        this->mobileNumber = mobileNumber;
    }
    int getId(){
        return this->id;
    }
    void addExpense(int id, int amount){
        if(this->expenseMap.find(id)==this->expenseMap.end()){
            this->expenseMap[id] = amount;
        }
        else{
            this->expenseMap[id] += amount;
        }
        
    }
    unordered_map<int,double> getExpenseMap(){
        return this->expenseMap;
    }

    string getFirstName(){
        return this->firstName;
    }
    void setFirstName(string firstName){
        this->firstName = firstName;
    }

    string getLastName(){
        return this->lastName;
    }
    void setLastName(string lastName){
        this->lastName = lastName;
    }

    string getEmail(){
        return this->email;
    }
    void setEmail(string email){
        this->email = email;
    }

    int getMobileNumber(){
        return this->mobileNumber;
    }
    void setMobileNumber(int number){
        this->mobileNumber = number;
    }

};


class SplitWise{
    public:
    unordered_map<int, User> userMap;
    enum splitType {EQUAL, EXACT, PRECENT};

    SplitWise(){

    }

    int addUser(string firstName, string lastName, string email, int number){
        User u(firstName, lastName, email, number);
        userMap[u.getId()] = u;
        return u.getId();
    }

    void splitEqual(int userId, double amount, vector<int> splitUsers){
        int numberOfUser = splitUsers.size();
        double splittedAmount = amount/numberOfUser;
        for(int u : splitUsers){
            userMap[u].addExpense(userId, splittedAmount);
        }
    }

    void splitExact(int userId, double amount, vector<int> splitUsers, vector<int> additionalInfo){
        int numberOfUser = splitUsers.size();
        if(numberOfUser!=additionalInfo.size()){
            cout<<"Please enter proper split amount"<<endl;
            return;
        }
        double temp=0;
        for(int i=0;i<numberOfUser;++i){
            temp+=additionalInfo[i];
        }
        if(temp!=amount){
            cout<<"splitted amount doesn't add up to total amount"<<endl;
            return;
        }
        int i=0;
        for(int u : splitUsers){
            userMap[u].addExpense(userId, additionalInfo[i++]);
        }
    }

    void splitPercent(int userId, double amount, vector<int> splitUsers, vector<int> additionalInfo){
        int numberOfUser = splitUsers.size();
        if(numberOfUser!=additionalInfo.size()){
            cout<<"Please enter proper split amount"<<endl;
            return;
        }
        double temp=0;
        for(int i=0;i<numberOfUser;++i){
            temp+=additionalInfo[i];
        }
        if(temp!=amount){
            cout<<"splitted percent doesn't add up to total amount"<<endl;
            return;
        }
        int i=0;
        for(int u : splitUsers){
            userMap[u].addExpense(userId, (additionalInfo[i++] * amount)/100 );
        }
    }

    void createExpense(int userId, double amount, vector<int> splitUsers, int splitType, vector<int> additionalInfo){

        if(splitType==0){
            splitEqual(userId, amount,  splitUsers);
        }
        else if(splitType==1){
            splitExact(userId, amount, splitUsers, additionalInfo);
        }
        else{
            splitPercent(userId, amount, splitUsers, additionalInfo);
        }
    }

    void displayExpense(){
        unordered_map<int, User>::iterator it1 = userMap.begin();
        //unordered_map<int, double>::iterator it2 = userExpense.begin();
        for(auto u : userMap){
            if(u.second.getExpenseMap().size()==0){
                cout<<"User "<<u.first<<" No expenses"<<endl;
                continue;
            }
            for(auto e : u.second.getExpenseMap()){
                cout<<"User "<<u.first<<" owes user "<< e.first<<": "<<e.second<<endl;
            }
        }
    }

    void displayExpense(int id){
        if(userMap[id].getExpenseMap().size()==0){
            cout<<"User "<<id<<" No expenses"<<endl;
        }
        for(auto it : userMap[id].getExpenseMap()){
            cout<<"User "<<id<<" owes user "<< it.first<<": "<<it.second<<endl;
        }
    }

};

int User::cnt;


int main(){

    SplitWise sp;

    int id1 = sp.addUser("basant", "meena", "bkm@gmail.com", 1234567890);
    int id2 = sp.addUser("aditya", "meena", "bkm2@gmail.com", 1234567890);
    int id3 = sp.addUser("bkm", "meena", "bkm1@gmail.com", 1234567890);
    vector<int> users;
    vector<int> info;
    users.push_back(id2);
    users.push_back(id3);
    info.push_back(60);
    info.push_back(40);
    sp.createExpense(id1, 100, users, 0, info);
    sp.displayExpense(); 
    sp.createExpense(id1, 100, users, 1, info);
    sp.displayExpense(); 
    sp.createExpense(id1, 100, users, 2, info);
    sp.displayExpense(); 
    sp.displayExpense(id2); 
    users[0]=id1;
    sp.createExpense(id2, 1000, users, 0, info);
    sp.displayExpense(); 
    sp.displayExpense(id1);   

    return 0;
}