
#include <bits/stdc++.h>
using namespace std;

size_t split(const std::string &txt, std::vector<std::string> &strs, const char ch) {
  size_t pos = txt.find(ch);
  size_t initialPos = 0;
  strs.clear();

  while (pos != std::string::npos) {
    strs.push_back(txt.substr(initialPos, pos - initialPos));
    initialPos = pos + 1;
    pos = txt.find(ch, initialPos);
  }

  strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
  return strs.size();
}

bool is_safe(vector<int> &nums) {
  bool inc = (nums[1] > nums[0]);
  for (int i = 0; i < nums.size() - 1; i++) {
    int diff = nums[i + 1] - nums[i];
    int abs_diff = abs(diff);
    if (inc && (diff < 0))
      return false;
    if (!inc && (diff > 0))
      return false;
    if (!(abs_diff == 1 || abs_diff == 2 || abs_diff == 3))
      return false;
  }
  return true;
}

bool is_safe_without(vector<int> &nums, int index) {
  vector<int> nums_copy;
  copy(nums.begin(), nums.begin() + index, back_inserter(nums_copy));
  copy(nums.begin() + index + 1, nums.end(), back_inserter(nums_copy));
  return is_safe(nums_copy);
}

//-----------------------------------------------------------------------------------------------

int part1(vector<vector<int>> &input) {
  int safe_count = 0;
  for(vector<int> nums : input) {
    if(is_safe(nums)) {
      safe_count++;
    }
  }
  return safe_count;
}

int part2(vector<vector<int>> input) {
 
  int safe_count = 0;
  for(vector<int> nums : input) {
    bool safe = is_safe(nums);
    if (safe) {
      safe_count++;
      continue;
    }

    for (int i = 0; i < nums.size() - 1; i++) {
      int diff = nums[i + 1] - nums[i];
      int abs_diff = abs(diff);

      if (!(abs_diff == 1 || abs_diff == 2 || abs_diff == 3)) {
        bool s1 = is_safe_without(nums, i);
        bool s2 = is_safe_without(nums, i + 1);
        safe = s1 || s2;
        break;
      }
      if (i < nums.size() - 2) {
        int diff2 = nums[i + 2] - nums[i + 1];
        if ((diff > 0) != (diff2 > 0)) {
          bool s3 = is_safe_without(nums, i);
          bool s4 = is_safe_without(nums, i + 1);
          bool s5 = is_safe_without(nums, i + 2);
          safe = s3 || s4 || s5;
          break;
        }
      }
    }

    if (safe) safe_count++;
  }

  return safe_count;
}

int main() {
  ifstream file("inputs/day2.txt");

  vector<vector<int>> input;
  string line;
  while (getline(file, line)) {
    vector<string> s_nums;
    vector<int> nums;
    const char delim = ' ';
    split(line, s_nums, delim);
    for (string s : s_nums) { nums.push_back(stoi(s)); }
    input.push_back(nums);
  }
  file.close();

  cout << "Solution Part 1: " << part1(input) << endl;
  cout << "Solution Part 2: " << part2(input) << endl;
}
