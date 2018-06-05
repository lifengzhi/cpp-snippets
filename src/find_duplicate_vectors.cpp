// http://thispointer.com/c-how-to-find-duplicates-in-a-vector/
// https://stackoverflow.com/q/32590764/496459

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Print the contents of vector
template <typename T>
void print(T& vecOfElements, std::string delimeter = " , ") {
  for (auto const& elem : vecOfElements) std::cout << elem << delimeter;
  std::cout << std::endl;
}

/*
 * Generic function to find duplicates elements in vector.
 * It adds the duplicate elements and their duplication count in given map
 * countMap
 */
template <typename T>
void findDuplicates(std::vector<T>& vecOfElements, std::map<T, int>& countMap) {
  // Iterate over the vector and store the frequency of each element in map
  for (auto& elem : vecOfElements) {
    auto result = countMap.insert(std::pair<std::string, int>(elem, 1));
    if (result.second == false) result.first->second++;
  }

  // Remove the elements from Map which has 1 frequency count
  for (auto it = std::begin(countMap); it != std::end(countMap);) {
    if (it->second == 1)
      it = countMap.erase(it);
    else
      it++;
  }
}

int main() {
  // Vector of strings
  std::vector<std::string> vecOfStings{"at",  "hello", "hi",   "there", "where",
                                       "now", "is",    "that", "hi",    "where",
                                       "at",  "no",    "yes",  "at"};

  print(vecOfStings);

  /*
   * Finding duplicates in vector using generic function
   */

  std::map<std::string, int> duplicateElements;

  // Get the duplicate elements in vector
  findDuplicates(vecOfStings, duplicateElements);

  std::cout << "Duplicate elements and their duplication count " << std::endl;
  for (auto const& elem : duplicateElements)
    std::cout << elem.first << " :: " << elem.second << std::endl;

  return 0;
}
