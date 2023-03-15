#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::chrono;

const int SIZE = 10;
int numThreads = 4;

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

// Bogo sort function for each thread
void bogoSort(int arr[], int threadNum, mutex& mtx, bool& done) {
    int iterations = 0;
    while (!isSorted(arr)) {
        if (done) {
            return;
        }
        shuffle(arr);
        iterations++;
        {
            lock_guard<mutex> lock(mtx);
            cout << "Thread " << threadNum << " Iteration " << iterations << ": ";
            for (int i = 0; i < SIZE; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
    {
        lock_guard<mutex> lock(mtx);
        cout << "Thread " << threadNum << " Sorted array: ";
        for (int i = 0; i < SIZE; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "Thread " << threadNum << " Total iterations: " << iterations << endl;
    }
}

int main() {
    srand(time(NULL));
    int arr[SIZE] = { 1, 4, 2, 3, 9, 6, 8, 7, 5, 0 };
    mutex mtx;
    bool done = false;
    
    // Create threads
    thread threads[numThreads];
    auto start = high_resolution_clock::now(); // Start the timer
    for (int i = 0; i < numThreads; i++) {
        threads[i] = thread(bogoSort, arr, i+1, ref(mtx), ref(done));
    }
    
    // Wait for threads to finish sorting
    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }
    auto end = high_resolution_clock::now(); // Stop the timer
    auto duration = duration_cast<milliseconds>(end - start); // Calculate the duration in milliseconds
    
    done = true;
    
    cout << "Total execution time: " << duration.count() << " ms" << endl;
    
    return 0;
}