// Etas_Calendar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Utility\base.h"

#include "Impl\htmlCalendarImpl.h"

using namespace Etas;

int main()
{
    std::string year;
    std::string filename;
    bool running = true;

    Shared<htmlCalendar> hc = htmlCalendarImpl::Create();

    while (running) {
        std::cout << "Enter the year: ";
        std::cin >> year;

        std::cout << "Enter the Filename: ";
        std::cin >> filename;

        filename += ".html";

        std::ofstream myFile;
        myFile.open(filename);

        hc->htmlHead(myFile);
        hc->adjYears(myFile, year);
        hc->htmlEnd(myFile);

        std::cout << "Enter 'q' to quit or Anything else to generate another file" << std::endl;
        char exit;
        std::cin >> exit;
        if (tolower(exit) == 'q') running  = false;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
