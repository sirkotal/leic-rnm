#include <iostream>
#include "manager.h"

void invalidInput(){
    std::cout << '\n';
    std::cout << "Uh-oh invalid option!\n";
    std::cin.ignore(10000, '\n');
    std::cin.clear();
}

int main() {
    Manager manager = Manager();
    manager.testing();
    cout << manager.maxArrivalTrainsAtCertain("Benquerenças") << endl;
    cout << manager.maxArrivalTrainsAtCertain("Freixo de Numão") << endl;
    cout << manager.maxArrivalTrainsAtCertain("São Romão") << endl;
    cout << manager.maxTrains("Lisboa Oriente", "Porto Campanhã") << endl << endl;
    cout << manager.maxTrainsWithReducedRailway("Lisboa Oriente", "Porto Campanhã") << endl << endl;
    cout << manager.maxTrains("Lisboa Oriente", "Porto Campanhã") << endl << endl;
    int l = 5;
    manager.mostImpactedStations(l);

    /*vector<pair<std::string, std::string>> alpha = manager.maxCapacityTrainsPairs();
    for (auto element: alpha) {
        std::cout << element.first << " -> " << element.second << std::endl;
    }*/

    /*std::cout << manager.maxArrivalTrainsAtCertain("Viana do Castelo") << std::endl;*/

    /*int x = 5;
    manager.topFlowMunicipalities(x);*/

    char choice;

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
            case '1':
                std::cout << "Implement opt 1\n";
                break;
            case '2':
                std::cout << "Implement opt 2\n";
                break;
            case '0':
                std::cout << "So sorry to see you go! :(\n";
                exit(0);
            default:
                invalidInput();
                break;
        }
    }
    } while (choice != '0');
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

