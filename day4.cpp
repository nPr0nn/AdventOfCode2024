
#include <bits/stdc++.h>
using namespace std;

void print_input(vector<vector<char>> input) {
  cout << "  ";
  for (int i = 0; i < input.size(); i++) {
    cout << i;
  }
  cout << endl;
  for (int i = 0; i < input.size(); i++) {
    cout << i << " ";
    for (int j = 0; j < input[i].size(); j++) {
      cout << input[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

int dir_search(vector<vector<char>> &input, vector<vector<int>> &dp, int i,
               int j, int index, string word, int i_dir, int j_dir) {
  if (index == word.size()) {
    return 1;
  }
  int new_i = i + i_dir;
  int new_j = j + j_dir;
  if (new_i < 0 || new_j < 0 || new_i >= input.size() ||
      new_j >= input[0].size())
    return 0;
  if (input[new_i][new_j] != word[index])
    return 0;
  return dir_search(input, dp, new_i, new_j, index + 1, word, i_dir, j_dir);
}

int search(vector<vector<char>> &input, vector<vector<int>> &dp, int i, int j,
           int index, string word) {

  if (index == word.size()) {
    return 1;
  }

  int i_dir[8] = {0, 1, -1, 0, 1, 1, -1, -1};
  int j_dir[8] = {1, 0, 0, -1, 1, -1, -1, 1};

  int finds = 0;
  for (int k = 0; k < 8; k++) {
    int new_i = i + i_dir[k];
    int new_j = j + j_dir[k];

    if (new_i < 0 || new_j < 0 || new_i >= input.size() ||
        new_j >= input[0].size())
      continue;

    if (input[new_i][new_j] == word[index]) {
      int cur_finds = dir_search(input, dp, new_i, new_j, index + 1, word,
                                 i_dir[k], j_dir[k]);
      finds += cur_finds;
    }
  }

  return finds;
}

//-----------------------------------------------------------------------------------------------------------

int part1(vector<vector<char>> input, string word) {
  int counter = 0;
  vector<vector<int>> dp(input.size(), vector<int>(input[0].size(), 0));

  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[i].size(); j++) {
      if (input[i][j] == word[0]) {
        counter += search(input, dp, i, j, 1, word);
      }
    }
  }

  return counter;
}

int part2(vector<vector<char>> input, string word) {
  int counter = 0;
  vector<vector<int>> dp(input.size(), vector<int>(input[0].size(), 0));

  for (int i = 1; i < input.size()-1; i++) {
    for (int j = 1; j < input[i].size()-1; j++) {
      if (input[i][j] == word[1]) {

        bool dia1 = false;
        bool dia2 = false; 

        char top_left  = input[i-1][j-1];
        char bot_right = input[i+1][j+1];
       
        if( (top_left == word[0] && bot_right == word[2]) || (top_left == word[2] && bot_right == word[0]) ) {
          dia1 = true;
        }

        char top_right = input[i-1][j+1];
        char bot_left  = input[i+1][j-1];

        if( (top_right == word[0] && bot_left == word[2]) || (top_right == word[2] && bot_left == word[0]) ) {
          dia2 = true;
        }
        
        if(dia1 && dia2) {
          counter++;
        }

      }
    }
  }

  return counter;
}

  int main() {
    FILE *file = fopen("inputs/day4.txt", "r");

    vector<vector<char>> input;
    vector<char> s;
    while (!feof(file)) {
      char c = fgetc(file);
      if (c == '\n') {
        input.push_back(s);
        s.clear();
      } else
        s.push_back(c);
    }
    fclose(file);

    print_input(input);
    cout << "Solution Part 1: " << part1(input, "XMAS") << endl;
    cout << "Solution Part 2: " << part2(input, "MAS") << endl;
  }
