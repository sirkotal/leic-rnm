#include <iostream>
#include "manager.h"
#include "menu.h"

void invalidInput(){
    cout << '\n';
    cout << "Uh-oh invalid option!\n";
    cin.ignore(10000, '\n');
    cin.clear();
}

int main() {
    char choice_menu, choice_submenu;
    string railway, network;
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
            case 'R':
                cout << "Insert your stations file's path: ";
                getline(cin, railway);
                cout << endl;
                cout << "Insert your network file's path: ";
                getline(cin, network);

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
    return 0;
}