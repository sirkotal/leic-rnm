#include <iostream>
#include "manager.h"

void invalidInput(){
    int choice = 0;
    while(choice != 1) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Uh-oh invalid option!\n"
                     "Insert 1 to return to the menu.\n >";
        std::cin >> choice;
        if (!std::cin.fail() && choice == 1)
            break;
    }
}

int main() {
    Manager manager = Manager();
    manager.testing();
    cout << manager.maxTrains("Casa Branca", "Portalegre") << endl;
    /*vector<pair<std::string, std::string>> alpha = manager.maxCapacityTrainsPairs();
    for (auto element: alpha) {
        std::cout << element.first << " -> " << element.second << std::endl;
    }*/
    int x = 5;
    manager.topFlowMunicipalities(x);
    int choice;

    do{
        std::cout << """"
                   "----------------------------------------\n"
                   "~ Welcome to the Fast Railway Service! ~\n"
                   "----------------------------------------\n"
                   "How can we help you today?\nInsert the number of the operation.\n"
                   "--------------------\n"
                   "| 1 - Option 1     |\n"
                   "| 2 - Option 2     |\n"
                   "| 0 - Exit Program |\n"
                   "--------------------\n"
                   "> ";
    std::cin >> choice;
    if (!std::cin.fail()){
        switch(choice){
            case 1:
                std::cout << "Implement opt 1\n";
                break;
            case 2:
                std::cout << "Implement opt 2\n";
                break;
            case 0:
                std::cout << "So sorry to see you go! :(\n";
                exit(0);
            default:
                invalidInput();
        }
        std::cin.clear();
    }else{ invalidInput();}
    }while (choice != 0);
    return 0;
}

/*
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠴⢿⣧⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣧⣆⣘⡄⢹⣿⣷⣆⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀ " << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢿⣷⠀⠀⠀⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⣴⣿⣿⠀⠀⠀⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣴⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⢀⣀⡀⣾⡿⠀⠉⠉⠛⠋⠛⠛⠚⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⢠⣍⠹⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⢿⣷⣾⣿⣿⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⢹⣟⢻⣿⣄⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠻⠿⠟⠁⠑⢶⣤⣴⣿⣿⣿⣷⣶⣬⣿⣿⣿⡿⠀⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠛⢛⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀" << std::endl;
std::cout <<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⢿⡿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
*/

