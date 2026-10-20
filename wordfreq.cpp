// wordfreq.cpp - count how often each word appears in a text file.
//
// Build:  g++ -std=c++17 -O2 -Wall -Wextra -o wordfreq wordfreq.cpp
// Usage:  ./wordfreq <file> [top_n]
//
// Words are runs of letters (and apostrophes inside a word), lowercased.

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Read the file and tally word counts in a hash map.
static std::unordered_map<std::string, std::size_t>
countWords(std::istream& in) {
    std::unordered_map<std::string, std::size_t> counts;
    std::string word;

    auto flush = [&]() {
        // Strip leading/trailing apostrophes (e.g. quotes like 'hello').
        while (!word.empty() && word.front() == '\'') word.erase(word.begin());
        while (!word.empty() && word.back() == '\'') word.pop_back();
        if (!word.empty()) ++counts[word];
        word.clear();
    };

    char c;
    while (in.get(c)) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (std::isalpha(uc) || c == '\'') {
            word.push_back(static_cast<char>(std::tolower(uc)));
        } else {
            flush();
        }
    }
    flush();  // last word if the file doesn't end in a delimiter
    return counts;
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <file> [top_n]\n";
        return 1;
    }

    std::size_t topN = 0;  // 0 = show all
    if (argc == 3) {
        long n = std::strtol(argv[2], nullptr, 10);
        if (n < 0) {
            std::cerr << "top_n must be non-negative\n";
            return 1;
        }
        topN = static_cast<std::size_t>(n);
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: cannot open '" << argv[1] << "'\n";
        return 1;
    }

    auto counts = countWords(file);

    // Move into a vector so we can sort: highest count first, ties alphabetical.
    std::vector<std::pair<std::string, std::size_t>> sorted(counts.begin(),
                                                            counts.end());
    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    std::size_t total = 0;
    for (const auto& kv : sorted) total += kv.second;

    std::size_t limit = (topN == 0 || topN > sorted.size()) ? sorted.size() : topN;
    for (std::size_t i = 0; i < limit; ++i) {
        std::cout << sorted[i].second << '\t' << sorted[i].first << '\n';
    }

    std::cerr << "\n" << total << " words total, " << sorted.size()
              << " unique\n";
    return 0;
}
