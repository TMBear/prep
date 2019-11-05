// Concatenated Words https://leetcode.com/problems/concatenated-words/
#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_set>


std::ostream& operator<< (std::ostream& out, std::vector<std::string>& words) {
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, ", "));
  return out;
}

class Solution {
public:
  std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string>& words);

private:
  bool tryWord(const std::string& word, int subwords);

  std::unordered_set<std::string> m_words;
};




std::vector<std::string> Solution::findAllConcatenatedWordsInADict(std::vector<std::string>& words) {
  m_words.clear();
  for (const auto& word : words) 
    m_words.insert(word);


  std::vector<std::string> result;
  for (const auto& word : words) {
    if (tryWord(word, 0))
      result.push_back(word);
  }

  return result;
}

bool Solution::tryWord(const std::string& word, int subwords) {
  if (word.empty())
    return subwords > 1;

//  std::cout << std::string(" ", subwords * 2) << word << ":" << subwords << std::endl;

  for (std::size_t i = 1; i < word.length()+1; ++i) {
//    std::cout << std::string(" ", subwords * 2) <<  "? " << word.substr(0, i) << std::endl;
    if (m_words.find(word.substr(0, i)) == m_words.end())
      continue;

//    std::cout << std::string(" ", subwords * 2) <<  "+ " << word.substr(0, i) << std::endl;
    if (tryWord(word.substr(i), subwords+1))
      return true;

  }

  return false;
}




static void test() {
  Solution s;

  {
    std::vector<std::string> words = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    auto res = s.findAllConcatenatedWordsInADict(words);
    std::cout << res << std::endl;
  }
  

}

