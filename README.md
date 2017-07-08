## Introduction

### This is a lrucache without using STL.

For this cache, the key type is char *

Two consts can be changed in `lrucache.h`

- `FP_SIZE`  means the max length of input key string.
- `HASH_SIZE` means the max length of hash table

you can easily use this cache just like in `lrutester.cpp`

- cache.set_max_cache_size(int): set the max size of cache


- cache.putdata(char*) : Insert key into cache;
- cache.find(char*):return 1 if the key is in the cache;

