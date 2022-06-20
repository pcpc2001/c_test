// Question: how to get "Magical!!!!" as output?

#include <iostream>
#include "magic.h"
#include <iomanip>
#include <string>

static const size_t MAGIC_INITIAL_KEY_INDEX = 1;
static const size_t MAGIC_INDEX = 2;
static const size_t MAGIC_VALUES_INDEX = 3;
static const int MAX_TRIAL = 10;

// Prototypes
std::unique_ptr<std::vector<std::string>> parseSequenceData(const std::string& valuesString);

/**
 * @brief Main Program - This program simulates a magical check on the inputs.
 * 
 * @param argc - number of command line arguments received
 * @param argv - actual arguments
 * @return int - System return code
 * 
 * Arugments:
 *   1) Initial Key
 *   2) starting index would be used to initialize the sequence for unlocking
 *   3) Sequence in Comman separated format.  i.e.  3,15,682,1234
 * 
 * MagicData Structure:
 *  struct MagicData
    {
        int a;
        int* b;
        int result;
        int magicData[MAGIC_DATA_MAX];
        int count;
    };

    Description:
        This program uses the initial key argument to generate an known public key set of 8 elements: {a, b, c, d, e, f, g, h}
        User must supply a list of private element to replace some or all public key elements in order to pass the validation check.
            EX:  Starting Index of 3 and with sequence {5,6,7} would produce the finaly key set of {a, b, c, 5, 6, 7, g, h}
 */
int main (int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Not enough arguments!" << std::endl;
        std::exit(-1);
    }

    const int initialKey = std::stoi(argv[MAGIC_INITIAL_KEY_INDEX]);
    const int magicIndex = std::stoi(argv[MAGIC_INDEX]);
    const std::string initlaSequence(argv[MAGIC_VALUES_INDEX]);

    std::unique_ptr<Magic> magic (new Magic());
    Magic::MagicData data;

    magic->initialize(&data);

    //init;
    data.a = 0;
    data.b = 0;
    data.count = 0;
    data.result = 0;

    // replace sequence from cmd args
    std::unique_ptr<std::vector<std::string>> values = parseSequenceData(initlaSequence);
    int index = magicIndex;
    for (int i = 0; i < MAGIC_DATA_MAX; i++)
    {
        if ( i >= values->size())
        {
            // too much data was given
            break;
        }
        
        data.magicData[index++] = std::stoi((*values)[i]);
    }

    int counter = MAX_TRIAL;
    while (0 == data.result)
    {
        if (counter == 0)
        {
            break;
        }

        counter--;

        data.result = magic->magicCheck(&data);
    }

    if (data.result == 0)
    {
        std::cout<<"Magic Failed"<<std::endl;
    }
    else
    {
        std::cout<<"Magical!!!!"<<std::endl;
    }

    return 0;
}

/**
 * @brief Parse CSV data into string vector
 * 
 * @param index 
 * @param valuesString 
 * @return std::unique_ptr<std::vector<std::string>> 
 */
std::unique_ptr<std::vector<std::string>> parseSequenceData(const std::string& valuesString)
{
    if (valuesString.length() <= 0)
    {
        return nullptr;
    }

    std::unique_ptr<std::vector<std::string>> values (new std::vector<std::string>());

    int startIndex = 0;
    for (int i = 0; i < valuesString.length(); i++)
    {
        const char c = valuesString[i];
        if (c == ',')
        {
            values->push_back(valuesString.substr(startIndex, i - startIndex));
            startIndex = i + 1;
        }
        else if (i == valuesString.length() - 1)
        {
            values->push_back(valuesString.substr(startIndex, i - startIndex));
        }
    }
    
    return values;
}