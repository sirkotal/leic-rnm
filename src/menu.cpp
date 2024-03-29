#include <iostream>
#include <thread>
#include <chrono>
#include "manager.h"
#include "menu.h"
using namespace std;
Menu::Menu(): manager(Manager()) {}

void Menu::invalidInput(){
    cout << '\n';
    cout << "Uh-oh invalid option!\n";
    cin.ignore(10000, '\n');
    cin.clear();
}

void Menu::printMainMenu() {
    std::cout << """"
                 "----------------------------------------------------------\n"
                 "~          Welcome to the Fast Railway Service!          ~\n"
                 "----------------------------------------------------------\n"
                 "How can we help you today?\nInsert the number of the operation (0-3).\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "|                                                                                                     |\n"
                 "| 1 - Basic Services                                                                                  |\n"
                 "| 2 - Cost Optimization                                                                               |\n"
                 "| 3 - Reliability and Sensitivity to Line Failures                                                    |\n"
                 "|                                                                                                     |\n"
                 "| R - Create the Railway Network                                                                      |\n"
                 "|                                                                                                     |\n"
                 "| 0 - Exit Program                                                                                    |\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "> ";
}

void Menu::printSubMenu1(){
    std::cout << """"
                 "How can we help you today?\nInsert the number of the operation (0-5).\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "|                                                                                                     |\n"
                 "| 1 - (2.1) Calculate max no of trains that can simultaneously travel between two specific stations.  |\n"
                 "| 2 - (2.2) Compute pairs of stations that need more trains between them.                             |\n"
                 "| 3 - (2.3) Estimate which stations need more budget and maintenance (DISTRICTS).                     |\n"
                 "| 4 - (2.3) Estimate which stations need more budget and maintenance (MUNICIPALITIES).                |\n"
                 "| 5 - (2.4) Determine no of trains that can arrive together at a specific station.                    |\n"
                 "|                                                                                                     |\n"
                 "| 0 - Exit Program                                                                                    |\n"
                 "| Any other value - Return to Main Menu                                                               |\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "> ";
}

void Menu::printSubMenu2() {
    std::cout << """"
                 "How can we help you today?\nInsert the number of the operation (0-1).\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "|                                                                                                     |\n"
                 "| 1 - (3.1) Calculate the max no of trains that can simultaneously travel between                     |\n"
                 "|           two specific stations with minimum cost for the company                                   |\n"
                 "|                                                                                                     |\n"
                 "| 0 - Exit Program                                                                                    |\n"
                 "| Any other value - Return to Main Menu                                                               |\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "> ";
}

void Menu::printSubMenu3() {
    std::cout << """"
                 "How can we help you today?\nInsert the number of the operation (0-2).\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "|                                                                                                     |\n"
                 "| 1 - (4.1) Calculate the max no of trains that can simultaneously travel between                     |\n"
                 "|           two specific stations in a network of reduced connectivity.                               |\n"
                 "| 2 - (4.2) Compute the stations more affected due to a segment failure.                              |\n"
                 "|                                                                                                     |\n"
                 "| 0 - Exit Program                                                                                    |\n"
                 "| Any other value - Return to Main Menu                                                               |\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "> ";
}

void Menu::switchSubMenu1(char option) {
    string src, dst;
    int k;
    vector<pair<string, string>> pairs;
    switch (option) {
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
            std::cout << "NOTE: This function may take a while... (~1 min)\n";
            pairs = manager.maxCapacityTrainsPairs();
            std::cout << "The pairs of stations that need more trains between them are: \n";
            for (auto &pair: pairs)
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
        case '0':
            std::cout << "So sorry to see you go! :(\n";
            exit(0);
        default:
            std::cout << "Redirecting to main menu...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
    }
}

void Menu::switchSubMenu2(char option) {
    string src, dst;
    switch (option) {
        case '1':
            std::cin.ignore(); //clear the buffer
            std::cout << "  Choose source station.\n        >";
            std::getline(std::cin, src);
            std::cout << "  Choose destination station.\n       >";
            std::getline(std::cin, dst);
            std::cout << "The minimum cost of operating the maximum number of trains possible between " << src << " and " << dst << " is: ";
            std::cout << manager.maxTrainsMinCost(src, dst) << "€" << "\n";
            break;
        case '0':
            std::cout << "So sorry to see you go! :(\n";
            exit(0);
        default:
            std::cout << "Redirecting to main menu...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
    }
}

void Menu::switchSubMenu3(char option) {
    string src, dst;
    double num;
    int k;

    manager.createReducedGraph();
    switch (option) {
        case '1':
            std::cin.ignore(); //clear the buffer
            std::cout << "  Choose source station.\n        >";
            std::getline(std::cin, src);
            std::cout << "  Choose destination station.\n       >";
            std::getline(std::cin, dst);
            num = manager.maxTrainsWithReducedRailway(src, dst);

            if (num == -1) {
                break;
            }
            cout << "The maximum number of trains that can travel between " << src << " and " << dst << " is: " << num << endl;
            break;
        case '2':
            std::cin.ignore(); //clear the buffer
            std::cout << "  Choose source station.\n        >";
            std::getline(std::cin, src);
            std::cout << "  Choose destination station.\n       >";
            std::getline(std::cin, dst);
            manager.maxTrainsWithReducedRailway(src, dst);
            std::cout << """"
                         "NOTE: This function may take a while... (~1 min)\n"
                         "  Insert which top-k you want to be presented.\n        >";
            std::cin >> k;
            manager.mostImpactedStations(k);
            break;
        case '0':
            std::cout << "So sorry to see you go! :(\n";
            exit(0);
        default:
            std::cout << "Redirecting to main menu...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
    }
}

void Menu::dataBuilder(const string &r, const string &n) {
    manager.buildRailway(r);
    manager.buildNetwork(n);
}

void Menu::mainMenu(){
    char choice_menu, choice_submenu;
    string railway, network;
    string path = "../data/";
    Menu menu = Menu();
    do{
        menu.printMainMenu();
        cin >> choice_menu;

        if (!std::cin.fail()){
            switch(choice_menu){
                case '1':
                    menu.printSubMenu1();
                    cin >> choice_submenu;
                    if (!std::cin.fail()){
                        menu.switchSubMenu1(choice_submenu);
                    }
                    break;
                case '2':
                    menu.printSubMenu2();
                    cin >> choice_submenu;
                    if (!std::cin.fail()){
                        menu.switchSubMenu2(choice_submenu);
                    }
                    break;
                case '3':
                    menu.printSubMenu3();
                    cin >> choice_submenu;
                    if (!std::cin.fail()){
                        menu.switchSubMenu3(choice_submenu);
                    }
                    break;
                case 'r':
                case 'R':
                    cout << "Insert your stations' file: ";
                    cin >> railway;
                    railway = path + railway;
                    std::cin.ignore(); //clear the buffer
                    cout << endl;
                    cout << "Insert your network's file: ";
                    cin >> network;
                    network = path + network;
                    std::cin.ignore(); //clear the buffer

                    menu.dataBuilder(railway, network);
                    break;
                case '0':
                    cout << "So sorry to see you go! :(\n";
                    exit(0);
                default:
                    invalidInput();
                    break;
            }
        }
    } while (choice_menu != '0');
}