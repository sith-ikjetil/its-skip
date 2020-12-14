//: Title        : its-skip.cpp
//: Date         : 2018-11-24
//: Author       : "Kjetil Kristoffer Solberg" <post@ikjetil.no>
//: Version      : 1.0
//: Descriptions : Filters away n lines of input

//
// #include
//
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

//
// using
//
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;

//
// struct
//
// (i) Contains command line arguments spported by this application
//
struct ItsSkipArguments
{
    long Count = 0;
    bool IsHelp = false;
    string FileIn;
    string FileOut;

    bool IsEmpty()
    {
        return (Count <= 0 && !IsHelp );
    }
};


//
// Function Prototypes
//
void PrintHelp();
void PrintHelp(string msg);
int ExecuteSkip(ItsSkipArguments& args);
int ParseArguments(int argc, char** argv, ItsSkipArguments& args);
bool CheckForSkipStatus(int c, ItsSkipArguments& args);

//
// Function: main
//
// (i) Main
//
int main(int argc, char** argv)
{
    ItsSkipArguments args;

    if ( ParseArguments(argc, argv, args) == EXIT_FAILURE )
    {
        stringstream ss;
        ss << "ParseArguments failed with code:" << errno;

        string msg = ss.str();
        PrintHelp(msg);
    
        return EXIT_FAILURE;
    }

    if ( (args.IsHelp || args.IsEmpty()) )
    {
        PrintHelp();
        return EXIT_SUCCESS;
    }
    
    if ( ExecuteSkip(args) == EXIT_FAILURE )
    {
        stringstream ss;
        ss << "ExecuteSkip failed with code: " << errno;

        string msg = ss.str();
        PrintHelp(msg);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

//
// Function: PrintHelp
//
// (i) Prints Help and Usage and Message
//
void PrintHelp(string msg)
{
    PrintHelp();
    cout << endl;
    cout << "Message: " << msg << endl;
}

//
// Function: PrintHelp
//
// (iI Prints Help and Usage
//
void PrintHelp()
{
    cout << "its-skip v.1.0 (amd64)" << endl;
    cout << "Usage: its-skip [OPTION]..." << endl;
    cout << "   or: its-skip [OPTION]... [FILE IN] [FILE OUT]" << endl;
    cout << endl;
    cout << "With no FILE, read standard input" << endl;
    cout << endl;
    cout << "    options                explanations                         " << endl;
    cout << " --------------       ------------------------------------------" << endl;
    cout << "  -?, --help            Shows this help screen" << endl;
    cout << endl;
    cout << "  -n, --count           Strip first n lines." << endl;
    cout << "                        ::Example: its-skip -n 10" << endl;
    cout << endl;
}

//
// Function: ParseArguments
//
// (i) Parses the command line arguments and populates the ItsStripArguments structure.
//
int ParseArguments(int argc, char** argv, ItsSkipArguments& args)
{
    bool bIsN = false;
    bool bFileIn = true;
    bool bFileOut = false;

    args.IsHelp = false;
    args.Count = 0;

    for ( int i = 1; i < argc; i++)
    {
        string str(argv[i]);
        if ( str == "-?" || str == "--help" )
        {
            args.IsHelp = true;
            return EXIT_SUCCESS;
        }

        if ( str == "-n" || str == "--count" )
        {
            bIsN = true;
            continue;
        }

        if ( bIsN )
        {
            bIsN = false;
            args.Count = std::stol(argv[i]);
            continue;
        }

        if ( bFileIn )
        {
            bFileIn = false;
            bFileOut = true;
            args.FileIn = argv[i];
            continue;
        }

        if ( bFileOut )
        {
            bFileIn = false;
            bFileOut = false;
            args.FileOut = argv[i];
            break;
        }
    }

    return EXIT_SUCCESS;
}

//
// Function: ExecuteStrip
//
// (i) Execute Strip Function
//
int ExecuteSkip(ItsSkipArguments& args)
{
    //
    // Setup Read Stream
    //
    FILE* readStream = stdin;
    if ( args.FileIn.size() > 0 )
    {
        readStream = fopen(args.FileIn.c_str(), "r");
        if ( readStream == nullptr )
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        readStream = stdin;
        if ( readStream == nullptr)
        {
            return EXIT_FAILURE;
        }
    }

    //
    // Setup Write Stream
    //
    FILE* writeStream = stdout;
    if ( args.FileOut.size() > 0 )
    {
        writeStream = fopen(args.FileOut.c_str(),"w");
        if ( writeStream == nullptr )
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        writeStream = stdout;
        if ( writeStream == nullptr)
        {
            return EXIT_FAILURE;
        }
    }

    int c;
    while ((c = fgetc (readStream)) != EOF)
    {
        if ( !CheckForSkipStatus(c, args) )
        {
            fputc(c,writeStream);
        }
    }

    fclose(readStream);
    fclose(writeStream);

    return EXIT_SUCCESS;
}

//
// Function: CheckForStripStatus
//
// (i) Checks given character if it should be stripped or not.
//
bool CheckForSkipStatus(int c, ItsSkipArguments& args)
{
    static long lCount = 1;
    static bool bHit = true;

    if ( c == '\n' ) {
        lCount++;
    }

    if ( lCount <= args.Count )
    {
        return true;
    }

    if ( bHit )
    {
        bHit = false;
        return true;
    }

    return false;
}
