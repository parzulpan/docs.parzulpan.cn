// main.cpp

#include "FingerprintModule.h"

int main(int argc, char *argv[])
{
    FingerprintModule *fp = new FingerprintModuleA();
    fp->algorithm();

    printf("\n");

    fp = new FingerprintModuleB();
    fp->algorithm();

    printf("\n");

    fp = new FingerprintModuleC();
    fp->algorithm();

    delete fp;

    return 0;
}