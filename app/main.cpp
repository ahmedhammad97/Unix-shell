#include <iostream>
#include <vector>

using namespace std;

void welcomeScreen(){
    cout<<"*********************************\n";
    cout<<"Welcome to this Simple Unix Shell\n";
    cout<<"\nCoded by: Ahmed Hammad - 4268\n";
    cout<<"*********************************\n";
}

string scanCommands(){
    string input=" ";
    while(getline(cin, input)){
        if(input.empty()) continue;
        else break;
    }
    return input;
}

vector<string> parseInput(string input){
    vector<string> result;
    string temp = "";
    for(int i=0; i<input.size(); i++){
        if(input[i]==' '){
			if(i==0 || input[i-1]==' '){continue;}
            result.push_back(temp);
            temp="";
        }
        else{
            temp.push_back(input[i]);
        }
    }
    if(temp!=""){result.push_back(temp);}
    return result;
}

bool validate(vector<string> commands){
    if(commands[0][0] == '-'){return false;}
    for(int i=1; i<commands.size(); i++){
        if(commands[i]=="&"){continue;}
        if(commands[i].size()==2 && commands[i][0]=='-'){continue;}
        else{return false;}
    }
    return true;
}


int main(){
	welcomeScreen();
	vector<string> commands;
	do{
        commands = parseInput(scanCommands());
        if(commands.empty()){continue;}

        if(validate(commands)){
            cout<<commands[0]<<endl;
        }
        else{
            cout<<"Unknown input .. Try again."<<endl;
        }
	}while(commands[0]!="exit" && commands[0]!="close" && commands[0]!="end");
}
