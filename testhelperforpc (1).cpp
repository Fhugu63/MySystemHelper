#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

using fc = void(*)(string);

vector<fc> funcs;

struct Commands {
    vector<string> commands;

    size_t getNumOfCommand(string line) {
        if (!commands.empty()) {
            for (auto it = commands.begin(); it != commands.end(); it++) {
                if (*it == line) {
                    return distance(commands.begin(), it);
                }
            }
        }
        
        return 0;
    }
    
    void addCommand(string command) {
        commands.push_back(command);
    }
    
    void init() {
        funcs.push_back(addCommand);
    }
};

struct ChatModule {
    Commands commandsModule;
    bool initModule() {
        commandsModule = Commands();
        commandsModule.addCommand("");
        commandsModule.addCommand("test");
        
        cout << commandsModule.getNumOfCommand("gh") << endl;
        
        commandsModule.init();
        
        return true;
    }
};

struct HelperSystem {
    ChatModule chatModule;
    bool init() {
        chatModule = ChatModule();
        chatModule.initModule();
    
        return true;
    }
};

int main() {
    cout << "Initializing system..." << endl;
    
    HelperSystem helperSystem = HelperSystem();
    
    helperSystem.init();
}