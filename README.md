# Single Threaded One Billion Rows Challenge 

## Reason to Not User Multi-threading
This is only a 12 Gb file, and the calculation is extremely simple (two comparisons and one addition each iteration). 
Thus, the bottleneck is going to be the IO operation of reading the file. In fact, 
using multi-threading will make it slower due to the added overhead of context switching.

## Methods
- From my experience, reading binary files (both signle and multi-threaded) using memory mapped files is the best, especially when the file is large.
  - I used my encryption memory mapping class to read the file.
- The most of a IO heavy operation like reading a file is from actually accessing the memory mapped pointer to the file. Thus, it is best to minimize 
    the number of times the pointer is accessed. In this case, each character only need to be accessed once from the memory mapped pointer.
- The map that keeps track of the statistics of each city can just use `std::string` since it didn't give me much of a performance improvement when 
I used custom comparator and equality checker with `char*`. 
- The map or specifically `std::unordered_map` should be used since the challenge said there will be at most 10,000 cities. 
Using `std::unordered_map` allows us to call `std::unordered_map::reserve(int)` to make inserts O(1) instead of O(log n).

## Results
| Hardware | Time (seconds) |
|----------|----------------|
| Apple M2 | 0.55           |
