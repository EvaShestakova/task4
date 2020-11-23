#include "AutoTest.h"

void AutoTest() {
    string filename = "text1.txt";
    zip(filename);
    unzip(filename);
    if (getsize(filename) == getsize(filename + ".1")) {
        cout << "Autotest passed" << endl;
    }
    else {
        cout << "Autotest failed" << endl;
        throw - 5;
    }
}