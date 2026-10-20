CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra

wordfreq: wordfreq.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: wordfreq
	./wordfreq examples/sample.txt 5

clean:
	rm -f wordfreq

.PHONY: run clean
