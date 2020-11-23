#include "func.h"
#include "AutoTest.h"

int main()
{
    try {
        string filename = "text.txt";
        AutoTest();
        cout << endl;
        zip(filename);
        unzip(filename);

    }
    catch (int err) { printf("error=%d\n", err); }
}
