#include <iostream>
#include <string>

using namespace std;

const int MAX_ITEMS = 100;

// Class to represent a menu item
class MenuItem {
public:
    MenuItem() : name(""), isVegan(false), isKosher(false), isHalal(false), isHindu(false) {}

    // Set values for a menu item
    void setValues(const string& itemName, bool vegan, bool kosher, bool halal, bool hindu) {
        name = itemName;
        isVegan = vegan;
        isKosher = kosher;
        isHalal = halal;
        isHindu = hindu;
    }

    // Getter methods
    string getName() const {
        return name;
    }

    bool isVeganOption() const {
        return isVegan;
    }

    bool isKosherOption() const {
        return isKosher;
    }

    bool isHalalOption() const {
        return isHalal;
    }

    bool isHinduOption() const {
        return isHindu;
    }

private:
    string name;
    bool isVegan;
    bool isKosher;
    bool isHalal;
    bool isHindu;
};

// Class to represent a menu
class Menu {
public:
    Menu() : itemCount(0), veganItemCount(0), kosherItemCount(0), halalItemCount(0), hinduItemCount(0) {}

    // Adding items to the specific menus
    void addMenuItem(const string& name, bool isVegan, bool isKosher, bool isHalal, bool isHindu) {
        if (itemCount < MAX_ITEMS) {
            // Set values for the menu item
            menuItems[itemCount].setValues(name, isVegan, isKosher, isHalal, isHindu);
            itemCount++;

            // Add the item to specific menus based on dietary restrictions
            if (isVegan) {
                veganItems[veganItemCount++] = menuItems[itemCount - 1];
            }

            if (isKosher) {
                kosherItems[kosherItemCount++] = menuItems[itemCount - 1];
            }

            if (isHalal) {
                halalItems[halalItemCount++] = menuItems[itemCount - 1];
            }

            if (isHindu) {
                hinduItems[hinduItemCount++] = menuItems[itemCount - 1];
            }
        }
    }

    // Getter methods for all menu items and specific menus
    const MenuItem* getAllMenuItems() const {
        return menuItems;
    }

    int getItemCount() const {
        return itemCount;
    }

    const MenuItem* getVeganMenuItems() const {
        return veganItemCount > 0 ? veganItems : nullptr;
    }

    int getVeganItemCount() const {
        return veganItemCount;
    }

    const MenuItem* getKosherMenuItems() const {
        return kosherItemCount > 0 ? kosherItems : nullptr;
    }

    int getKosherItemCount() const {
        return kosherItemCount;
    }

    const MenuItem* getHalalMenuItems() const {
        return halalItemCount > 0 ? halalItems : nullptr;
    }

    int getHalalItemCount() const {
        return halalItemCount;
    }

    const MenuItem* getHinduMenuItems() const {
        return hinduItemCount > 0 ? hinduItems : nullptr;
    }

    int getHinduItemCount() const {
        return hinduItemCount;
    }

private:
    MenuItem menuItems[MAX_ITEMS];
    int itemCount;

    MenuItem veganItems[MAX_ITEMS];
    int veganItemCount;

    MenuItem kosherItems[MAX_ITEMS];
    int kosherItemCount;

    MenuItem halalItems[MAX_ITEMS];
    int halalItemCount;

    MenuItem hinduItems[MAX_ITEMS];
    int hinduItemCount;
};

// Display menu items based on dietary restrictions
void displayMenu(const MenuItem* items, int itemCount, bool showOnlyVegan) {
    if (items == nullptr) {
        cout << "No items in this menu.\n";
        return;
    }

    for (int i = 0; i < itemCount; ++i) {
        if (!showOnlyVegan || (showOnlyVegan && items[i].isVeganOption())) {
            cout << "Item: " << items[i].getName() << '\n';
        }
    }
}

int main() {
    Menu menu;
    char continueUpdating = 'y';

    // Continuously update the menu based on user input
    do {
        string newMenuItem;
        cout << "Add New Menu Item: ";
        getline(cin, newMenuItem);

        bool isVegan = false;
        bool isKosher = false;
        bool isHalal = false;
        bool isHindu = false;

        // Ask about dietary restrictions
        cout << "Is it a vegan option? (y/n): ";
        char isVeganInput;
        cin >> isVeganInput;
        if (isVeganInput == 'y' || isVeganInput == 'Y') {
            isVegan = true;
        }

        cout << "Is it kosher? (y/n): ";
        char isKosherInput;
        cin >> isKosherInput;
        if (isKosherInput == 'y' || isKosherInput == 'Y') {
            isKosher = true;
        }

        cout << "Is it halal? (y/n): ";
        char isHalalInput;
        cin >> isHalalInput;
        if (isHalalInput == 'y' || isHalalInput == 'Y') {
            isHalal = true;
        }

        cout << "Is it Hindu? (y/n): ";
        char isHinduInput;
        cin >> isHinduInput;
        if (isHinduInput == 'y' || isHinduInput == 'Y') {
            isHindu = true;
        }

        // Add the new menu item to the menu
        menu.addMenuItem(newMenuItem, isVegan, isKosher, isHalal, isHindu);

        // Ask if the user wants to add another item
        cout << "Do you want to add another item? (y/n): ";
        cin >> continueUpdating;
        cin.ignore(); //Puts a line break so you can still answer

    } while (continueUpdating == 'y' || continueUpdating == 'Y');

    // After updating, display all menu items
    cout << "\nMenu:\n";
    displayMenu(menu.getAllMenuItems(), menu.getItemCount(), false);

    // Display specific menus with items
    if (menu.getVeganItemCount() > 0) {
        cout << "Vegan Menu:\n";
        displayMenu(menu.getVeganMenuItems(), menu.getVeganItemCount(), true);
    }

    if (menu.getKosherItemCount() > 0) {
        cout << "\nKosher Menu:\n";
        displayMenu(menu.getKosherMenuItems(), menu.getKosherItemCount(), false);
    }

    if (menu.getHalalItemCount() > 0) {
        cout << "\nHalal Menu:\n";
        displayMenu(menu.getHalalMenuItems(), menu.getHalalItemCount(), false);
    }

    if (menu.getHinduItemCount() > 0) {
        cout << "\nHindu Menu:\n";
        displayMenu(menu.getHinduMenuItems(), menu.getHinduItemCount(), false);
    }

    return 0;
}
//Sources: CodeHS and W3Schools