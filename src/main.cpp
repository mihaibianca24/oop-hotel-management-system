#include "Menu.h"
using namespace std;
int main() {
    try {
        Menu menu;
        menu.run();
    } catch (exception& e) {
        cout << "Fatal error: " << e.what() << endl;
        return 1;
    }
    return 0;
}