#include <iostream>
#include "magic.h"
#include <iomanip>

// Magic Data Struct
struct MagicData
{
    int a;
    int* b;
    int result;
    int magicData[MAGIC_DATA_MAX];
    int count;
};

int question1(int input, MagicData* magicData);

int main (int argc, char** argv)
{
    MagicData data;

    //init;
    data.a = 0;
    data.b = 0;
    data.count = 0;
    data.result = -1;

    int result = question1(10, &data);

    return 0;
}

// Find errors and find output
int question1(int input, MagicData* magicData)
{
    Magic* magic = new Magic();

    *(magicData->b) = input;
    magicData->a = magic->getMagic(*(magicData->b));

    int* ptr = magicData->magicData;
    for (int i = 0; i <= MAGIC_DATA_MAX; i++)
    {
        magicData->count++;
        magicData->a = magic->getMagic(magicData->a);
        *ptr = magicData->a;

        ptr++;
    }

    std::cout << "count = " << magicData->count << std::endl;

    return magicData->result;
}