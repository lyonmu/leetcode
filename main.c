#include "utils/utils.h"
#include "0507/time0507.h"

int main() {
    int testArrays[] = {3, 2, 4, 15};
    int test[1];
    int length = arrLength(testArrays);
    int *sum = twoSum(testArrays, length, 7, test);
    traverseArrays(sum, 2);
    traverseArrays(testArrays, length);
    return 0;
}
