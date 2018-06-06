// http://thispointer.com/c-how-to-find-duplicates-in-a-vector/
// https://stackoverflow.com/q/32590764/496459

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename T>
void print(T& vecOfElements, std::string delimeter = " , ") {
  for (auto const& elem : vecOfElements) std::cout << elem << delimeter;
  std::cout << std::endl;
}

template <typename T>
std::map<T, int> findDuplicates(std::vector<T>& vecOfElements) {
  std::map<T, int> countMap;

  for (auto& elem : vecOfElements) {
    countMap[elem]++;
  }

  // https://stackoverflow.com/a/8234813/496459
  // See also: Effective STL Item 9 Choose carefully among erasing options

  for (auto it = std::begin(countMap); it != std::end(countMap);) {
    if (it->second == 1)
      it = countMap.erase(it);
    else
      ++it;
  }

  return countMap;
}

int main() {
  std::vector<std::string> words{"at",  "hello", "hi",   "there", "where",
                                       "now", "is",    "that", "hi",    "where",
                                       "at",  "no",    "yes",  "at"};

  print(words);

  auto const duplicateElements = findDuplicates(words);

  std::cout << "Duplicate elements and their duplication count:" << std::endl;
  for (auto const& elem : duplicateElements) {
    std::cout << elem.first << " :: " << elem.second << std::endl;
  }

  return 0;
}
