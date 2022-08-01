// Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>
using namespace std::chrono;

// Simple bubble sort algorithm for a vector of ints (returns sorted vector in ascending order)
std::chrono::nanoseconds bubbleSort(std::vector<int>& arrayInput)
{
    auto start = high_resolution_clock::now();

    bool sorted = false;

    while (!sorted) {
        sorted = true;
        for (int i = 0; i < (int) arrayInput.size() - 1; i++) {
            if (arrayInput[i] > arrayInput[i + 1]) {
                int temp = arrayInput[i];
                arrayInput[i] = arrayInput[i + 1];
                arrayInput[i + 1] = temp;
                sorted = false;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    std::chrono::nanoseconds duration = duration_cast<nanoseconds>(stop - start);

    return duration;
}

int main()
{
    std::vector<int> array1 = { 3, 2, 1 };
    std::vector<int> array2 = { 1, 2 };
    std::vector<int> array3 = { 10, 45, 5, 24, 26, 72, 0, -1, 2 };
    std::vector<int> array4 = { 10, 9, 8, 7, 6, 4, 1, 5, 3, 2 };
    std::vector<int> array5 = { 0 };

    std::vector<std::vector<int>> arrays = { array1, array2, array3, array4, array5 };

    for (int i = 0; i < (int) arrays.size(); i++) {
        std::chrono::nanoseconds seconds = bubbleSort(arrays[i]);
        std::cout << "Array " << i + 1 << " was sorted in " << seconds.count() << " nanoseconds.\n";
    }

    for (int i = 0; i < (int) arrays.size(); i++) {
        std::cout << "Array " << i+1 << ": ";
        for (int j = 0; j < (int) arrays[i].size(); j++) {
            std::cout << arrays[i][j] << " ";
        }
        std::cout << "\n";
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
