#ifndef LEIC_RNM_MENU_H
#define LEIC_RNM_MENU_H

/**
 * @brief Represents the railway network management system's menu
 */
class Menu {
public:
    Menu();

    /**
     * @brief If the option chosen in the main menu is invalid, clears the buffer
     */
    void invalidInput();

    /**
     * @brief Displays the main menu, indicating the meaning of each option
     */
    void printMainMenu();

    /**
     * @brief Displays the "Basic Services" menu, indicating the meaning of each option
     */
    void printSubMenu1();

    /**
     * @brief Displays the "Cost Optimization" menu, indicating the meaning of each option
     */
    void printSubMenu2();

    /**
     * @brief Displays the "Reliability and Sensitivity to Line Failures" menu, indicating the meaning of each option
     */
    void printSubMenu3();

    /**
     * @brief According to the chosen option, applies the procedures needed to accomplish what was asked in the "Basic Services" menu
     * @param option Option chosen by the user
     */
    void switchSubMenu1(char option);

    /**
     * @brief According to the chosen option, applies the procedures needed to accomplish what was asked in the "Cost Optimization" menu
     * @param option Option chosen by the user
     */
    void switchSubMenu2(char option);

    /**
     * @brief According to the chosen option, applies the procedures needed to accomplish what was asked in the "Reliability and Sensitivity to Line Failures" menu
     * @param option Option chosen by the user
     */
    void switchSubMenu3(char option);

    /**
     * @brief Builds a graph containing the railway's train stations and its connections
     * @param r File containing the train stations' information
     * @param n File containing the railway network's information
     */
    void dataBuilder(const string &r, const string &n);

    /**
     * @brief According to the chosen option, presents and deals with the options to choose: submenus, create a railway network or exit the program.
     */
    void mainMenu();


private:
    /**
     * @brief A manager that handles the interface between the graph and the menu
     */
    Manager manager;
};


#endif //LEIC_RNM_MENU_H
