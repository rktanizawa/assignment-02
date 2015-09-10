* ----------------------------------------------------------------------------
 * Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
 *                  2015 Randy Tanizawa <rtanizawa@csu.fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * A program to read unsigned integers from a text file and separate them into
 * two files, one for primes, another for composites.
 */


#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

ifstream infilename;
ofstream outfilename;

int total;
int min_num = 65535;
int max_num = 1;

int find_max(const string& infilename);

void sieve(const int size_of, bool primes[]);

int write_primes( const int size_of,
                  bool primes[],
                  const string& infilename,
                  const string& outfilename );



int write_composites( const int size_of,
                      bool primes[],
                      const string& infilename,
                      const string& outfilename );



// ----------------------------------------------------------------------------

int main() {

    infilename.open("input.txt");

    int MAX = find_max(infilename);
    if(MAX == -1)
    {
        cout << "Error in find_max()." << endl;
        return 1;
    }

    bool primes[max_num + 1];
    sieve(max_num + 1, primes);

    int ret_value;
    ret_value = write_primes(total,primes,infilename,outfilename);
    if(ret_value == -1)
    {
        cout << "Error in write_primes()." << endl;
        return 1;
    }

    int ret;
    ret = write_composites(total,primes,infilename,outfilename);
     if(ret_value == -1)
    {
        cout << "Error in write_composites()." << endl;
        return 1;
    }

    cout << "Files successfully created and sorted." << endl;

    return 0;
}

// ----------------------------------------------------------------------------

int find_max(ifstream& infilename)
{
    infilename.clear();
    infilename.seekg(0, infilename.beg);
    if(infilename){
    int number;
    total = 0;

    while(infilename >> number)                      // Read through file from beginning. If the number is larger than
    {                                                // the max_number set at 1, replace it to be the max_number.
        total++;                                     // The min_number is to eliminate any numbers larger than the limit
        if(number > max_num)                         // set at 65535.
            max_num = number;
        if(number < min_num)
            min_num = number;
    }
    return max_num;
    }
    else
        return -1;
}

void sieve(const int size_of, bool primes[])
{
    for(int TRUE = 0; TRUE < max_num + 1; TRUE++)     // Set all elements to true
    {
        primes[TRUE] = 1;
    }

    int x = 2;                                        // Using "x" as the multiplicand.
    for(x; x < ((max_num + 1)/2);)                    // "x" grows by 1 as long as it is less than half the max number.
    {
        for(int i = 2; i * x < (max_num + 1); i++)
        {
            primes[x * i] = 0;                        // Any numbers that go into the brackets are set to 0
        }                                             // and are therefore not prime
        ++x;
    }

}

int write_primes(const int size_of,
                 bool primes[],
                 const string& infilename,
                 const string& outfilename)
{
    infilename.clear();                               // The file has already been read and needs the read
    infilename.seekg(0, infilename.beg);              // position to be set back to the beginning.

    outfilename.open("primes.txt");
    if(outfilename.is_open()){
    int contents;

    while (infilename >> contents)                    // Search through the file again and prints all numbers
    {                                                 // that match with the prime array's true values
        for(int i = 2; i < (max_num + 1); i++)
        {
            if(primes[i] == 1 && contents == i)
            {
                outfilename << contents << endl;
    }   }   }
        return 0;
    }
    else
        return -1;
}

int write_composites( const int size_of,
                      bool primes[],
                      const string& infilename,
                      const string& outfilename )
{
    infilename.clear();                               // The file has already been read and needs the read
    infilename.seekg(0, infilename.beg);              // position to be set back to the beginning.

    outfilename.open("composites.txt");
    if(outfilename.is_open()){
    int contents;

    while (infilename >> contents)                    // Search through the file again and prints all numbers
    {                                                 // that match with the prime array's false values.
        for(int i = 2; i < (max_num + 1); i++)
        {
            if(primes[i] == 0 && contents == i)
            {
                outfilename << contents << endl;
    }   }   }
        return 0;
    }
    else
        return -1;
}
