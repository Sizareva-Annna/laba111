#include <iostream>
#include <string>

using namespace std;

int main() {
    int counter = 0;
    string message = "Hello";

    cout << "Start program" << endl;

    for (int i = 1; i < 4; i++) {
        cout << "Iteration: " << i << endl;
        cout << "Counter before: " << counter << endl;
        cout << "Message before: " << message << endl;

        counter++;
        message += "!";

        cout << "Counter after: " << counter << endl;
        cout << "Message after: " << message << endl;
    }

    cout << "End program" << endl;

    return 0;
}