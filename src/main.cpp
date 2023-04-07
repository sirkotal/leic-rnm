#include <iostream>
#include "manager.h"

void invalidInput(){
    std::cout << '\n';
    std::cout << "Uh-oh invalid option!\n";
    std::cin.ignore(10000, '\n');
    std::cin.clear();
}

int main() {
    char choice;
    Manager manager = Manager();
    do{
        std::cout << """"
                   "----------------------------------------------------------\n"
                   "~          Welcome to the Fast Railway Service!          ~\n"
                   "----------------------------------------------------------\n"
                   "How can we help you today?\nInsert the number of the operation (0-8).\n"
                   "-------------------------------------------------------------------------------------------------------\n"
                   "|    BASIC SERVICES                                                                                   |\n"
                   "| 1 - (2.1) Calculate max no of trains that can simultaneously travel between two specific stations.  |\n"
                   "| 2 - (2.2) Compute pairs of stations that need more trains between them.                             |\n"
                   "| 3 - (2.3) Estimate which stations need more budget and maintenance (DISTRICTS).                     |\n"
                   "| 4 - (2.3) Estimate which stations need more budget and maintenance (MUNICIPALITIES).                |\n"
                   "| 5 - (2.4) Determine no of trains that can arrive together at a specific station.                    |\n"
                   "|                                                                                                     |\n"
                   "|    COST OPTIMIZATION                                                                                |\n"
                   "| 6 - (3.1) Calculate the max no of trains that can simultaneously travel between                     |\n"
                   "|           two specific stations with minimum cost for the company                                   |\n"
                   "|                                                                                                     |\n"
                   "|    RELIABILITY AND SENSITIVITY TO LINE FAILURES                                                     |\n"
                   "| 7 - (4.1) Calculate the max no of trains that can simultaneously travel between                     |\n"
                   "|           two specific stations in a network of reduced connectivity.                               |\n"
                   "| 8 - (4.2) Compute the stations more affected due to a segment failure.                              |\n"
                   "|                                                                                                     |\n"
                   "| 0 - Exit Program                                                                                    |\n"
                   "-------------------------------------------------------------------------------------------------------\n"
                   "> ";
    std::cin >> choice;

    string src, dst;
    int k;
    vector<pair<string,string>> pairs;

    if (!std::cin.fail()){
        switch(choice){
            case '1':
                std::cin.ignore(); //clear the buffer
                std::cout << "  Choose source station.\n        >";
                std::getline(std::cin, src);
                std::cout << "  Choose destination station.\n       >";
                std::getline(std::cin, dst);
                std::cout << "The maximum number of trains that can travel between " << src << " and " << dst << " is: ";
                std::cout << manager.maxTrains(src, dst) << "\n";
                break;
            case '2':
                    pairs = manager.maxCapacityTrainsPairs();
                    std::cout << "The pairs of stations that need more trains between them are: \n";
                    for (auto & pair : pairs)
                        std::cout << pair.first << " and " << pair.second << "\n";
                    break;
            case '3':
                std::cin.ignore(); //clear the buffer
                std::cout << """"
                               "NOTE: This function may take a while... (~1 min)\n"
                               "  Insert which top-k you want to be presented.\n        >";
                std::cin >> k;
                manager.topFlowDistricts(k);
                break;
            case '4':
                std::cin.ignore(); //clear the buffer
                std::cout << """"
                             "NOTE: This function may take a while... (~1 min)\n"
                             "  Insert which top-k you want to be presented.\n        >";
                std::cin >> k;
                manager.topFlowMunicipalities(k);
                break;
            case '5':
                std::cin.ignore(); //clear the buffer
                std::cout << "  Choose destination station.\n       >";
                std::getline(std::cin, dst);
                std::cout << "The maximum number of trains that can arrive at " << dst << " simultaneously is: ";
                std::cout << manager.maxArrivalTrainsAtCertain(dst) << "\n";
                break;
            case '6':
                std::cin.ignore(); //clear the buffer
                std::cout << "  Choose source station.\n        >";
                std::getline(std::cin, src);
                std::cout << "  Choose destination station.\n       >";
                std::getline(std::cin, dst);
                std::cout << "The maximum number of trains that can travel between " << src << " and " << dst << " with minimum cost to the company is: ";
                std::cout << manager.maxTrainsMinCost(src, dst) << "\n";
                break;
            case '7':
                break;
            case '8':
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