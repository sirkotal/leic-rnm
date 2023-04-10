#ifndef LEIC_RNM_MENU_H
#define LEIC_RNM_MENU_H


class Menu {
public:
    Menu();
    void invalidInput();
    void printMainMenu();
    void printSubMenu1();
    void printSubMenu2();
    void printSubMenu3();
    void switchSubMenu1(char option);
    void switchSubMenu2(char option);
    void switchSubMenu3(char option);
    void dataBuilder(const string &r, const string &n);
    void mainMenu();


private:
    Manager manager;
};


#endif //LEIC_RNM_MENU_H
