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
                   "How can we help you today?\nInsert the number of the operation (1-7).\n"
                   "-------------------------------------------------------------------------------------------------------\n"
                   "|    BASIC SERVICES                                                                                   |\n"
                   "| 1 - (2.1) Calculate max no of trains that can simultaneously travel between two specific stations.  |\n"
                   "| 2 - (2.2) Compute pairs of stations that need more trains between them.                             |\n"
                   "| 3 - (2.3) Estimate which stations need more budget and maintenance.                                 |\n"
                   "| 4 - (2.4) Determine no of trains that can arrive together at a specific station.                    |\n"
                   "|                                                                                                     |\n"
                   "|    COST OPTIMIZATION                                                                                |\n"
                   "| 5 - (3.1) Calculate the max no of trains that can simultaneously travel between                     |\n"
                   "|           two specific stations with minimum cost for the company                                   |\n"
                   "|                                                                                                     |\n"
                   "|    RELIABILITY AND SENSITIVITY TO LINE FAILURES                                                     |\n"
                   "| 6 - (4.1) Calculate the max no of trains that can simultaneously travel between                     |\n"
                   "|           two specific stations in a network of reduced connectivity.                               |\n"
                   "| 7 - (4.2) Compute the stations more affected due to a segment failure.                              |\n"
                   "|                                                                                                     |\n"
                   "| 0 - Exit Program                                                                                    |\n"
                   "-------------------------------------------------------------------------------------------------------\n"
                   "> ";
    std::cin >> choice;

    string src, dst;
    int k;

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
                break;
            case '3':
                break;
            case '4':
                std::cin.ignore(); //clear the buffer
                std::cout << "  Choose destination station.\n       >";
                std::getline(std::cin, dst);
                std::cout << "The maximum number of trains that can arrive at " << dst << " simultaneously is: ";
                std::cout << manager.maxArrivalTrainsAtCertain(dst) << "\n";
                break;
            case '5':
                std::cin.ignore(); //clear the buffer
                std::cout << "  Choose source station.\n        >";
                std::getline(std::cin, src);
                std::cout << "  Choose destination station.\n       >";
                std::getline(std::cin, dst);
                std::cout << "The maximum number of trains that can travel between " << src << " and " << dst << " with minimum cost to the company is: ";
                std::cout << manager.maxTrainsMinCost(src, dst) << "\n";
                break;
                break;
            case '6':
                break;
            case '7':
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