#include <iostream>
#include <fstream>
#include "Drawing.h"

using namespace std;

int main(int argc, char* argv[]) {
    const char* fName = "out.bmp";
    ofstream f;
    f.open(fName, ios::out | ios::binary);

    unsigned int blockSize = 100;
    Drawing d;
    for (int i = 0; i < 100; i++) {
        d.create(blockSize);
    }

    f.write((const char*) d.getBuffer(), d.getBufferSize());

    f.close();

    cout << "Done!" << endl;
    return 0;
}
