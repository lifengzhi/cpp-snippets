// https://www.pramp.com/tryout

/*
Anonymous Love Letter

L = letter
N = newspaper

L can be written by characters from N, if and only if every character in L is
included in N at least by the same number of occurrences. To determine that, we
should count the number of occurrences for each character in L and determine if
we have all of them, at least at the same quantity in N. A good approach to do
this is using a hash table. The hash key would be the character, and the hash
value would be the number of occurrences counted so far.

Since all characters are ascii we can avoid the hash table and use a simple
array of 256 integers, that we’ll name charMap. Every index in charMap will hold
the number of occurrences of the character represented by its ascii code. Since
N is most likely much longer than L, we start with counting the number of
character occurrences in it first. That way, we’ll be able to stop processing N
once we find all of L's characters in it, and reduce computational costs.

After counting all character occurrences in L, we scan N and for each character,
reduce its count on charMap if it is larger than 0. If all counts in charMap are
zero at some point, we return true. Otherwise, if we are done scanning N and at
least one count is not 0, we return false.
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>

bool is_love_letter_reproducible(const std::string& letter,
                                 const std::string& newspaper) {
  if (newspaper.length() < letter.length()) return false;
  size_t char_count = 0;
  std::array<char, 256> char_map{};
  for (size_t i = 0; i < letter.length(); ++i) {
    char ascii_code = letter[i];
    // https://stackoverflow.com/a/48213308/496459
    assert(static_cast<unsigned char>(ascii_code) <= 127);
    if (char_map[ascii_code] == 0) ++char_count;
    char_map[ascii_code]++;
  }

  for (size_t i = 0; i < newspaper.length(); ++i) {
    char ascii_code = newspaper[i];
    assert(static_cast<unsigned char>(ascii_code) <= 127);
    if (char_map[ascii_code] > 0) {
      char_map[ascii_code]--;
      if (char_map[ascii_code] == 0) char_count--;
    }
    if (char_count == 0) return true;
  }

  return false;
}

void test_reproducibility(const std::string& letter,
                          const std::string& newspaper) {
  std::cout << "reproducible: " << std::boolalpha
            << is_love_letter_reproducible(letter, newspaper) << '\n';
}

int main() {
  const std::string letter = "I'm loving you";

  test_reproducibility(letter, "");
  test_reproducibility(letter, letter);

  std::string reversed_letter{letter};
  std::reverse(std::begin(reversed_letter), std::end(reversed_letter));
  test_reproducibility(letter, reversed_letter);

  test_reproducibility(letter, "Today, I am not working with you.");
  // Testing assert with cedilla:
  // test_reproducibility(letter, "Je suis français.");
}
