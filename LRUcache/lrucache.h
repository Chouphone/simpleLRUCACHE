//this a simple LRU cache
//#ifdef LRUCACHE_H
//#define LRUCACHE_H

#include <cstdlib>
#include <stdint.h>
#include <string>
#include <cstdio>
#include <cmath>
#include <string.h>
#define FP_SIZE 6
#define HASH_SIZE 1000000
struct listnode
{
	char hash_key[FP_SIZE];
	listnode *next;
	listnode *front;
};
struct hashnode
{
	listnode *list_pos;
	hashnode *next;
	hashnode *front;
};
class lrucache
{
	public:
		int64_t max_cache_size;
		int64_t now_cache_size;
		lrucache();// Constructor
		lrucache(int size);// Constructor with size
		~lrucache();
		void set_max_size(int size);
		bool putdata(char *str);//put a sting into cache, with a ruturn 1 when inserting success;
		bool find(char *str);//find a strnig in cache, with 1 when find it;
	private:
		//------------this is hash operation ---------------------
		unsigned long str_hash(char *str);
		bool insert_hash(char *str, listnode *p);
		bool find_hash(char *str, listnode * &result);
		bool delete_hash(char *str);
		//------------this is list operation ---------------------
		bool add_node_to_head(char *str);
		bool delete_node(listnode *p);
		//---------------------------------------------------
		hashnode *hash_table[HASH_SIZE];
		listnode *head;
		listnode *back;
};
//#endif
