# Word Frequency Counter (C++)

A command-line tool that reads a text file and counts how often each word appears, using a hash map (`std::unordered_map`) for O(1) average-time lookups and updates.

## Features

- Case-insensitive counting ("The" and "the" are the same word)
- Handles contractions ("didn't" stays one word) and strips surrounding quotes/punctuation
- Output sorted by frequency (highest first), ties broken alphabetically
- Optional `top_n` argument to show only the most common words
- Prints total and unique word counts

## Build

Requires a C++17 compiler (g++ or clang++).

```bash
make
# or
g++ -std=c++17 -O2 -Wall -Wextra -o wordfreq wordfreq.cpp
```

## Usage

```bash
./wordfreq <file> [top_n]
```

Example:

```bash
$ ./wordfreq examples/sample.txt 5
5	the
2	dog
2	fox
2	quick
1	brown

21 words total, 14 unique
```

The word list goes to stdout and the summary goes to stderr, so output can be piped or redirected cleanly.

## How it works

1. Stream the file character by character, building each word from letters and apostrophes.
2. On a delimiter, normalize the word and increment its count in an `unordered_map<string, size_t>`.
3. Copy the map into a vector and sort it by count (descending), then alphabetically.

Time complexity is O(n) to count plus O(k log k) to sort, where n is the number of characters and k is the number of unique words.

## Possible improvements

- Unicode / accented character support
- Stop-word filtering
- Multi-file input and CSV output
