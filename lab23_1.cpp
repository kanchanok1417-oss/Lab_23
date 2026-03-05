#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    string line;

    while(getline(file, line)){
        char name[100];
        int s1, s2, s3;
        sscanf(line.c_str(), "%[^:]: %d %d %d", name, &s1, &s2, &s3);

        names.push_back(name);
        int total = s1 + s2 + s3;
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    char format[] ="%s %[^\n]";
    string str;
    getline(cin, str);
    char t[100], k[100];
    sscanf(str.c_str(), format, t, k);
    command = toUpperStr(t);
    key = k;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    string upKey = toUpperStr(key);
        bool found = false;
    
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == upKey){
            cout << "---------------------------------\n";   
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            found = true;
        }
    }
    
    if(!found){ 
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";}

}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
        bool found = false;
    cout << "---------------------------------\n"; 
    for(unsigned i = 0; i < grades.size(); i++){
        string currentGrade(1, grades[i]);
        if(toupper(key[0]) == toupper(grades[i])){
            cout << names[i] << " (" << scores[i] << ")" << "\n";
            found = true;
        }
    }
    if(!found)cout << "Cannot found.\n";
    
    cout << "---------------------------------\n";

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
