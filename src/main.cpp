#include <iostream>
#include "manager.h"
#include "station.h"
#include "vertexedge.h"
#include "graph.h"

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
                   "How can we help you today?\nInsert the number of the operation.\n"
                   "------------------------------------------------------------------------------------------------\n"
                   "| 1 - Calculate no of trains that can simultaneously travel between two specific stations.      |\n"
                   "| 2 - Determine no of trains that can arrive together at a specific station.                    |\n"
                   "| 3 - The same as 2, but considering failures on the route.                                     |\n"
                   "| 4 - Compute pairs of stations that need more trains between them.                             |\n"
                   "| 5 - Estimate which stations need more maintenance.                                            |\n"
                   "| 6 - Evaluate which stations are the most affected by failures on a route.     (TODO)          |\n"
                   "| 0 - Exit Program                                                                              |\n"
                   "------------------------------------------------------------------------------------------------\n"
                   "> ";
    std::cin >> choice;
    string src, dst;
    if (!std::cin.fail()){
        switch(choice){
            case '1':
                std::cin.ignore(); //clear the buffer
                std::cout << "  Choose source station.\n        >";
                std::getline(std::cin, src);
                std::cout << "  Choose destination station.\n       >";
                std::getline(std::cin, dst);
                std::cout << "The maximum number of trains that can travel between " << src << " and " << dst << " is: ";
                std::cout << manager.maxTrains(src, dst);

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