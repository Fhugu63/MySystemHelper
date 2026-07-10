#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <chrono>
#include <map>
#include <algorithm>

using namespace std;

using fcwp = string(*)(string);
vector<fcwp> funcsWithP;

using fcwtp = string(*)();
vector<fcwtp> funcsWithoutP;

vector<string> split(string line, char symbol) {
    vector<string> splited_text;
    string part_text;
    int index = 0;
    
    for (char symb : line) {
        
        if (symb == symbol) {
            splited_text.push_back(part_text);
            index++;
            part_text = "";
        } else {
            part_text += symb;
        }
    }
    if (splited_text.empty()) {
        splited_text.push_back(line);
    } else {
        splited_text.push_back(part_text);
    }
    
    return splited_text;
}

string doNothing(string line) {
    return "";
}

//vector<string> commands;
vector<fcwp> numOfCommandFunc;

string getTime(string line) {
    return "idk time";
}

string calculate(string line) {
    vector<string> splited_line = split(line, ' ');
    string parsed_line;
    
    for (string word : splited_line) {
        int symbolNum = 0;
        string parsed_word = "";
        for (auto symbol : word) {
            bool isMatch = false;
            for (int num = 0; num <= 9; num++) {
                if (symbol == '+' || symbol == '-' || symbol == '*'
               || symbol == '/' || symbol == '(' || symbol == ')' 
               || symbol == '^' || symbol - '0' == num) {
                   isMatch = true;
                   break;
               }
            }
            if (isMatch) {
                parsed_word += symbol;
            }
        }
        word = parsed_word;
        for (char symbol : word) {
            
            if (true)  {
                parsed_line += symbol;
                //cout << "next symbol " << splited_line[0][symbolNum+1] << endl;
                if (symbolNum+1 < word.size()) {
                    char next_symbol = word[symbolNum+1];
                    for (int num = 0; num <= 9; num++) {
                        //cout << "symbol " << symbol << " num " << num << endl;
                        if (symbol - '0' == num) {
                            //cout << "yes" << endl;
                            if (next_symbol == '+' || next_symbol == '-' || next_symbol == '*'
                            || next_symbol == '/' || next_symbol == '(' || next_symbol == ')' || next_symbol == '^') {
                                parsed_line += " ";
                                cout << parsed_line << endl;
                            }
                        } else if (symbol == '+' || symbol == '-' || symbol == '*'
                        || symbol == '/' || symbol == '(' || symbol == ')' || symbol == '^') {
                            if (next_symbol - '0' == num) {
                                parsed_line += " ";
                                cout << parsed_line << endl;
                            }
                        }
                    }
                }
            }
            symbolNum++;
        }
        parsed_line+=" ";
    }
    cout << parsed_line << endl;
    
    vector<string> operations;
    
    
    
    //line.replace("calculate ", "");
    string xz;
    for (auto x : splited_line) {xz+=x;}
    return parsed_line;
}

struct Command {
    string command;
    fcwp commandFunc;
    Command(string command, fcwp commandFunc) {
        this->command = command;
        this->commandFunc = commandFunc;
    }
};

vector<Command> commands;

class Commands {
    public:
        static void addCommand(string command, fcwp commandFunc) {
            Command commandBlock = Command(command, commandFunc);
            commands.push_back(commandBlock);
        }
        static vector<Command> getCommands() {
            return commands;
        }
        
        static void onGetInput(string input) {
            vector<string> splited_input = split(input, ' ');
            if (!splited_input.empty()) {
                string command = splited_input[0];
                fcwp commandFunc = doNothing;
                int command_index = 0;
                for (auto it = begin(commands); it != end(commands); it++) {
                    if ((*it).command == command) {
                        commandFunc = (*it).commandFunc;
                        break;
                    }
                }
                
                if (splited_input.size() > 1) {
                    input = input.replace(0, splited_input[0].size()+1, "");
                }
                
                string commandReturn = commandFunc(input);
                
                cout << commandReturn << " g" << endl;
                
            }
            
            
        }
        
        

};

bool initChatSystem() {
    Commands::addCommand("", doNothing); // for reserve index 0 for unexpected command
    Commands::addCommand("calculate", calculate);
    Commands::addCommand("time", getTime);
    
    //cout << getNumOfCommand("calculator") << endl;
    //cout << getNumOfCommand("zxkcvuatot") << endl;
    
    /*while (true) {
        string test;
        cin >> test;
    
        cout << getNumOfCommand(test) << endl;
    }*/
    
    return true;
}

int main() {
    bool work = true;
    cout << "Initializing system..." << endl;
    
    if (initChatSystem()) {
        cout << "Chat system successfully initialized" << endl;
    } else {
        cout << "Error with initialization chat system!" << endl;
    }
    
    while (work) {
        string line;
        getline(cin, line);
        
        Commands::onGetInput(line);
    }
    
    //auto now = std::chrono::system_clock::now();
    //cout << now;
}