# Auto-detect GCC version
CXX := $(shell ls /opt/homebrew/bin/g++-* 2>/dev/null | sort -V | tail -1)
CXXFLAGS = -fopenmp

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(patsubst %.cpp,%,$(wildcard *.cpp))

.PHONY: clean
