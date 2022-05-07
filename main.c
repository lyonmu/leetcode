#include "utils.h"

int main() {
    int testArrays[10], length = arrLength(testArrays);
    getRand(testArrays, length);
    traverseArrays(testArrays, length);
    return 0;
}
