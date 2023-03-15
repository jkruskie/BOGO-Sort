#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int SIZE = 10;

// Helper function to check if the array is sorted
bool isSorted(int arr[]) {
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// Helper function to shuffle the array randomly
void shuffle(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        int j = rand() % SIZE;
        swap(arr[i], arr[j]);
    }
}

// Bogo sort function
void bogoSort(int arr[]) {
    int iterations = 0;
    while (!isSorted(arr)) {
        shuffle(arr);
        iterations++;
        cout << "Iteration " << iterations << ": ";
        for (int i = 0; i < SIZE; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << "Sorted array: ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Total iterations: " << iterations << endl;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    int arr[SIZE] = { 1, 4, 2, 3, 9, 6, 8, 7, 5, 0 };
    auto start = high_resolution_clock::now(); // Start the timer
    bogoSort(arr); // Sort the array using bogo sort
    auto end = high_resolution_clock::now(); // Stop the timer
    auto duration = duration_cast<milliseconds>(end - start); // Calculate the duration in milliseconds
    cout << "Total execution time: " << duration.count() << " ms" << endl;
    return 0;
}
