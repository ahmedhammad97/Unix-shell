#include <iostream>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <wait.h>

using namespace std;

void initializeLog(){ // TBC
    return;
}

void welcomeScreen(){
    cout<<"*********************************\n";
    cout<<"Welcome to this Simple Unix Shell\n";
    cout<<"\nCoded by: Ahmed Hammad - 4268\n";
    cout<<"*********************************\n";
}

string scanCommands(){
    string input=" ";
    while(getline(cin, input)){ // Ignoring empty lines
        if(input.empty()) continue;
        else break;
    }
    return input;
}

vector<string> parseInput(string input){ // Splits input string into tokens
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

bool isAsync(const vector<string>& commands){ // Checks for & symbol
    for(auto& command : commands){
        if(command == "&"){return true;}
    }
    return false;
}

char** toArray(vector<string> commands){ // Converts C++ vector to C-like char array
    char** result = new char* [commands.size()];
    for(int i=0; i<commands.size(); i++){
        result[i] = new char[commands[i].size() + 1];
        strcpy(result[i], commands[i].c_str());
    }
    return result;
}

void writeToLog(string message){ // TBC
    return;
}

void signalHandler(int sigNum){ // TBC
    return;
}

bool executeCommand(vector<string>& commands){
    int pid = fork(); // Creates a child
    //cout<<"PID : "<<pid<<endl;
    if(pid < 0){
        cout<<"An internal error occured .. My apologies :("<<endl;
        return false;
    }
    else if(pid == 0){ //Process
        char** arr = toArray(commands);
        int result = execvp(arr[0], arr);
        if(result < 0){
            cout<<"Wrong command .. Try again"<<endl;
            return false;
        }

    }
    else{ //Parent
        if(isAsync(commands)){
            signal(SIGCHLD, signalHandler);
        }else{
            wait(NULL);
        }
    }
    return true;
}


int main(){
    initializeLog(); // To be implemented
	welcomeScreen();
	vector<string> commands;
	do{
        cout<<"Shell >> ";
        string input = scanCommands();
        commands = parseInput(input);

        if(executeCommand(commands)){
            writeToLog(input + " executed successfully\n"); // To be implemented
        }


	}while(commands[0]!="exit" && commands[0]!="close" && commands[0]!="end");
}
