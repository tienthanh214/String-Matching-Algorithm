
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "StringMatching.h"

using namespace std;

struct MatchedPosition {
    // (x, y) is coordinate of the matched position
    // dir is the direction of the matched string: LR (left to right), TD (up to down), NF (not found)
    int x, y;
    string dir;

    MatchedPosition(int _x, int _y, string _dir) : x(_x), y(_y), dir(_dir) {}

    MatchedPosition() : x(-1), y(-1), dir("NF") {}

    MatchedPosition(const MatchedPosition &other) {
        x = other.x;
        y = other.y;
        dir = other.dir;
    }

    MatchedPosition &operator=(const MatchedPosition &other) {
        x = other.x;
        y = other.y;
        dir = other.dir;
        return *this;
    }
};

void ReadData(int &w, int &h, vector<string> &s, vector<string> &p) {
    ifstream f("input.txt");
    f >> w >> h;
    s.resize(h);
    for (int i = 0; i < h; ++i) {
        s[i].resize(w);
        for (int j = 0; j < w; ++j) {
            f >> s[i][j];
            f.get();
        }
    }
    p.clear();
    string temp;
    while (f >> temp) {
        if (temp[0] == '#') 
            break;
        p.push_back(temp);
    }
    f.close();
    // for (int i = 0; i < h; ++i) cout << s[i] << endl;
    // for (int i = 0; i < p.size(); ++i) cout << p[i] << endl;
}

int CrossGame(int w, int h, vector<string> &s, vector<string> &p, vector<MatchedPosition> &pos) {
    int res = 0;
    pos.clear();
    for (int i = 0; i < p.size(); ++i) {
        for (int j = 0; j < h; ++j) {
            int temp = KMP(s[j], p[i]);
            if (temp != -1) { // found match 
                pos.push_back(MatchedPosition(j, temp, "LR"));
                ++res;
                break;
            }
        }

        if (pos.size() == i + 1) // found matched LR before
            continue;
        for (int j = 0; j < w; ++j) {
            string verticalS;
            for (int k = 0; k < h; ++k) 
                verticalS += s[k][j];
            int temp = KMP(verticalS, p[i]);
            if (temp != -1) { // found match 
                pos.push_back(MatchedPosition(temp, j, "TD"));
                ++res;
                break;
            }
        }
        if (pos.size() == i + 1) // found matched TD before
            continue;
        pos.push_back(MatchedPosition()); // not found
    }
    return res;
}

int main() {
    int w, h;
    vector<string> s, p;
    vector<MatchedPosition> pos;
    ReadData(w, h, s, p);
    cout << CrossGame(w, h, s, p, pos) << '\n';
    for (int i = 0; i < pos.size(); ++i) {
        cout << p[i] << " (" << pos[i].x + 1 << ", " << pos[i].y + 1 << ") " << pos[i].dir << '\n';
    }
    return 0;
}
