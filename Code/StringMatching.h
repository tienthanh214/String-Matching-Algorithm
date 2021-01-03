#pragma once
#include <string>
#include <vector>
#include <iostream>

std::vector<int> computePrefixFunction(const std::string &p) {
    std::vector<int> pi(p.size());
    pi[0] = 0;
    for (int i = 1; i < (int)p.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && p[j] != p[i])
            j = pi[j - 1];
        if (p[i] == p[j])
            j = j + 1;
        pi[i] = j;
    }    
    return pi;
}

// return the position of the pattern p
// return -1 if not found
int KMP(const std::string &s, const std::string &p) {
    std::vector<int> pi = computePrefixFunction(p);
    for (int i = 0, j = 0; i < s.size(); ++i) {
        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];
        if (s[i] == p[j])
            j = j + 1;
        if (j == (int)p.size()) // found a match
            return i - j + 1;
    }
    return -1; // not found
}
