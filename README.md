# Cache Simulator

# 1. Description

The goal of this project is to write a program that simulates the direct-mapped caches. The simulator should be configured to have different cache sizes and block sizes. Thus, your simulator needs to support the following command-line arguments.

    -s <cache size>
    -b <block size>
    -f <trace file name>

The cache size and block size are a power of 2. The cache size will be 32 ~ 1MB (1KB = 1024 bytes,
1MB=1048576 bytes). The block size will be 4B ~ 256B (2^(m+2) Byte).

The simulator will read in a memory trace file that contains multiple read and write memory requests, which have the following form: <address> <R/W> <data>

Where indicates a read request, and  indicates a write request, and  indicates the memory address being referenced. The memory address is 32 bits which is expressed as a hexadecimal number.  indicates a data that will be stored in the memory for a write request. In case of a read request, there should be no  field.

For each memory request, the cache simulator will determine whether the memory request hits or misses on the cache. If the memory request type is a write, you need to write data (a word) in the cache. Assume that the write policy is the write-back and write-allocate.

At the end of a simulation, your simulator will show the contents (blocks) stored in the cache. It also reports the simulation results: the number of hits, the number of misses, the miss rate, the number of dirty cache blocks, and the average memory access time. Assume that the cache hit time is 1 cycle and the miss penalty is 200 cycles when calculating the average memory access time (in cycles).

![Cache%20Simulator/Untitled.png](Cache%20Simulator/Untitled.png)

---

# 2. How to run the simulator

Simulate 32B direct-mapped cache with a block size of 4B

    $ cache_sim -s 32 -b 4 -f test.trc

Simulate 32B direct-mapped cache with a block size of 32B

    $ cache_sim -s 32 -b 32 -f test.trc