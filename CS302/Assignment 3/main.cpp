/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 3
   Description: This program will perform parallel matrix multiplication
                algorithm. It will first get input from a file that has the
                matrix size and the A and B matrices. Using the A and B
                matrices, it will use linear algebra to compute the C matrix
                using threads.
*/

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::mutex t_lock; //Locks the theads ig

void calculate(int); // Parallel matrix multiplication

// Declare matrix as global variables
std::vector<std::vector<int>> matrixA; // A matrix
std::vector<std::vector<int>> matrixB; // B matrix
std::vector<std::vector<int>> matrixC; // C matrix

int main() 
{
  // Matrix variables
  int lines = 0; // Gets the size of the matrix
  int num = 0;   // Gets the number from the input file

  // Thread variables
  std::vector<std::thread> threadPool;                  // List of threads
  int maxThreads = std::thread::hardware_concurrency(); // Max amt of threads

  // File variables
  std::string line;     // Gets input from the file as a string
  std::string filename; // Gets name of input file
  std::ifstream inFile; // ifstream variable

  // Get user input file
  do 
  {
    std::cout << "Enter file name: ";
    std::cin >> filename;

    inFile.open(filename.c_str()); // Opens file

    // Error messages if file fails to open
    if (!inFile.is_open()) 
    {
      std::cout << "Invalid file.\n";
    }
  } while (inFile.fail());

  inFile >> lines;           // get the matrix size
  inFile.ignore(1000, '\n'); // Ignore next line

  // Get the A matrix and store in 2d vector
  for (int i = 0; i < lines; i++) 
  {
    std::vector<int> tmpVec;

    for (int j = 0; j < lines; j++) 
    {
      inFile >> line;        // Get number from input file
      num = std::stoi(line); // Convert string to int
      tmpVec.push_back(num); // Store in temp vector
    }

    matrixA.push_back(tmpVec); // Add to the 2d vector
  }

  inFile.ignore(1000, '\n'); // Ignore next line

  // Get the B matrix and store in the 2d vector
  for (int i = 0; i < lines; i++)
  {
    std::vector<int> tmpVec2; // Create a temp vector to store numbers

    for (int j = 0; j < lines; j++) 
    {
      inFile >> line;         // Get number from file
      num = std::stoi(line);  // Convert string to int
      tmpVec2.push_back(num); // Store int to the temp list
    }

    matrixB.push_back(tmpVec2); // Store list in B Matrix
  }

  inFile.close(); // Close the file

  std::cout << "C Matrix\n"; // Display title of the matrix

  // THREADING
  if (threadPool.size() < maxThreads) 
  {
    threadPool.push_back(std::thread(calculate, lines));
  } 
  else 
  {
    for (auto &t : threadPool) {
      t.join();
    }

    threadPool.clear();
  }

  // Synchronize threads
  for (auto &t : threadPool) 
  {
    t.join();
  }

  return 0;
}

// Function to calculate the C matrix values
void calculate(int count) 
{
  int sum = 0; // Holds the sum of the products

  // First loop for A matrix row
  for (int i = 0; i < count; i++) 
  {
    std::vector<int> tempVector; // Temporary vector to hold list of sums

    // Second loop for B matrix column
    for (int j = 0; j < count; j++) 
    {
      sum = 0; // Reset sum

      // Third loop for A matrix column and B matrix row
      for (int k = 0; k < count; k++) 
      {
        sum += matrixA[i][k] * matrixB[k][j]; // Get sum of the products
      }

      tempVector.push_back(sum); // Store sum in temp list
    }

    matrixC.push_back(tempVector); // Store list into C matrix
  }

  // Display C matrix
  for (int i = 0; i < count; i++) 
  {
    for (int j = 0; j < count; j++) 
    {
      t_lock.lock();
      std::cout << matrixC[i][j] << " ";
      t_lock.unlock();
    }
    std::cout << "\n";
  }
}