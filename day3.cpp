
#include <bits/stdc++.h>

using namespace std;

int part1(string input) {
  int res = 0;
  regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
  smatch matches;
  string::const_iterator search_start(input.cbegin());
  while (regex_search(search_start, input.cend(), matches, pattern)) {
    int a = stoi(matches[1]);
    int b = stoi(matches[2]);
    res += a * b;
    search_start = matches.suffix().first;
  }
  return res;
}

int part2(string input) {
  // Patterns for `do()`, `dont()` and `mul(*, *)`
  regex do_pattern(R"(do\(\))");
  regex dont_pattern(R"(\bdon't\(\))");
  regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

  vector<pair<int, int>> mul_info;
  map<int, int> do_info;
  vector<int> dos_indices;

  smatch matches;
  string::const_iterator search_start(input.cbegin());
  while (regex_search(search_start, input.cend(), matches, mul_pattern)) {
    size_t pos = matches.position() + distance(input.cbegin(), search_start);
    
    int a = stoi(matches[1]);
    int b = stoi(matches[2]);
    int prod = a * b;
    mul_info.push_back({pos, prod});

    search_start = matches.suffix().first;
  }

  search_start = input.cbegin();
  while (regex_search(search_start, input.cend(), matches, do_pattern)) {
    int pos = matches.position() + distance(input.cbegin(), search_start); 
    dos_indices.push_back(pos);
    do_info[pos] = 1;
    search_start = matches.suffix().first;
  }

  search_start = input.cbegin();
  while (regex_search(search_start, input.cend(), matches, dont_pattern)) {
    int pos = matches.position() + distance(input.cbegin(), search_start); 
    dos_indices.push_back(pos);
    do_info[pos] = 0;
    search_start = matches.suffix().first;
  }
  dos_indices.push_back(0);
  do_info[0] = 1;
  sort(dos_indices.begin(), dos_indices.end());

  int res = 0;
  for (auto info : mul_info) {
    int pos  = info.first;
    int prod = info.second;
    
    int idx = lower_bound(dos_indices.begin(), dos_indices.end(), pos) - dos_indices.begin();
    if(do_info[dos_indices[idx-1]] == 1) {
      res += prod; 
    }
  }
  
  return res;
}

int main() {
  const char *filename = "inputs/day3.txt";
  FILE *file = fopen(filename, "r");

  string input;
  while (!feof(file)) {
    char c = fgetc(file);
    input += c;
  }
  fclose(file);

  cout << "Solution Part 1: " << part1(input) << endl;
  cout << "Solution Part 2: " << part2(input) << endl;
}
