#define TEST
#include "main.cpp"

#include <dirent.h>

void Tab(int n) {
  for (int i = 0; i < n; i++) {
    cout << "\t";
  }
}

string Blue(string s) {
  return "\033[34m" + s + "\033[m";
}

string Green(string s) {
  return "\033[32m" + s + "\033[m";
}

string Magenta(string s) {
  return "\033[35m" + s + "\033[m";
}

string Red(string s) {
  return "\033[31m" + s + "\033[m";
}

string BGRed(string s) {
  return "\033[41m" + s + "\033[m";
}

string Under(string s) {
  return "\033[4m" + s + "\033[m";
}

string Yellow(string s) {
  return "\033[33m" + s + "\033[m";
}

int sample_num(string path) {
  int n = 0;
  struct dirent *de;

  DIR *d = opendir(path.c_str());
  while ((de = readdir(d))) {
    string file = de->d_name;
    if (file.find("input") != string::npos) {
      n++;
    }
  }
  closedir(d);
  return n;
}

int main() {
  OPTIMIZE_STDIO;

  int tn;

  string path = __FILE__;
  path = path.substr(0, path.find_last_of('/'));

  tn = sample_num(path);

  for (int i = 1; i <= tn; i++) {
    if (i > 1) {
      cout << endl;
    }
    vector<string> po, ao;

    string s;
    stringstream oss;

    string input = path + "/" + to_string(i) + "_input.txt";

    ifstream pifs(input);
    ifstream aifs(path + "/" + to_string(i) + "_output.txt");

    auto start = chrono::system_clock::now();
    solve(pifs, oss);
    auto end = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    pifs.clear();
    pifs.seekg(0, ios_base::beg);

    while (getline(oss, s)) {
      po.push_back(s + "\n");
    }

    while (getline(aifs, s)) {
      ao.push_back(s + "\n");
    }

    ostringstream ss;
    ss << i;
    cout << Green("Testing " + ss.str()) << " ...  ";
    if (po.size() == ao.size() && equal(po.cbegin(), po.cend(), ao.cbegin())) {
      cout << Blue("OK") << "    " << time << " [ms]" << endl;
    } else {
      cout << Red("NG") << "    " << time << " [ms]" << endl;
      Tab(1);
      cout << Magenta("Input") << endl;
      while (getline(pifs, s)) {
        Tab(2);
        cout << s << endl;
      }

      Tab(1);
      cout << Magenta("Your Answer") << endl;
      for (int i = 0; i < po.size(); i++) {
        Tab(2);
        if (i < ao.size() && po[i] == ao[i]) {
          cout << po[i];
        } else {
          cout << Red(po[i]);
        }
      }
      if (po.size() < ao.size()) {
        cout << " ";
        cout << BGRed(" ");
      }
      cout << endl;

      Tab(1);
      cout << Magenta("Right Answer") << endl;
      for (int i = 0; i < ao.size(); i++) {
        Tab(2);
        cout << ao[i];
      }
      cout << endl;
    }
  }
}
