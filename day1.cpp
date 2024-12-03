
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int part1(vector<int> list1, vector<int> list2) {
  sort(list1.begin(), list1.end());
  sort(list2.begin(), list2.end());
  int res = 0;
  for (size_t i = 0; i < list1.size(); i++) {
    res += abs(list1[i] - list2[i]);
  }
  return res;
}

int part2(vector<int> list1, vector<int> list2) {
  map<int, int> count2;
  for(int i = 0; i < list2.size(); i++) {
    count2[list2[i]]++;
  }

  int res = 0;
  for (size_t i = 0; i < list1.size(); i++) {
    res += list1[i] * count2[list1[i]];
  } 

  return res;
}

int main() {
  const char *filename = "inputs/day1.txt";
  FILE *file = fopen(filename, "r");

  vector<int> list1;
  vector<int> list2;

  // Read the file
  while (!feof(file)) {
    int val1, val2;
    if (fscanf(file, "%d %d", &val1, &val2) == 2) {
      list1.push_back(val1);
      list2.push_back(val2);
    }
  }
  fclose(file);

  cout << "Solution Part 1: " << part1(list1, list2) << endl;
  cout << "Solution Part 2: " << part2(list1, list2) << endl << "" << endl;
  return 0;
}
