#include "lrucache.h"
#include <cstdlib>
lrucache::lrucache()//constructor
{
	head = NULL;
	back = NULL;
	max_cache_size = 0;
	now_cache_size = 0;
	for(int i = 0 ; i < HASH_SIZE ; i++)hash_table[i] = NULL;
}

lrucache::lrucache(int size)
{
	head = NULL;
	back = NULL;
	max_cache_size = size;
	now_cache_size = 0;
	for(int i = 0 ; i < HASH_SIZE ; i++)hash_table[i] = NULL;
}
lrucache::~lrucache()
{
	listnode *p = head;
	while(p != NULL)
	{
		listnode *q = p->next;
		if(!delete_node(p)){printf("there is some error happen when deleting!\n");exit(1);}
		else p = q;
	}
	max_cache_size = 0;
	now_cache_size = 0;
	head = NULL;
	back = NULL;
	for(int i = 0; i < HASH_SIZE; i++)
	{
		while(hash_table[i] != NULL)
		{
			hashnode *q = hash_table[i]->next;
			delete hash_table[i];
			hash_table[i] = q;
		}
	}
}
void lrucache::set_max_size(int size)
{
	max_cache_size = size;
}

unsigned long lrucache::str_hash(char *str)
{
	unsigned long key = 0 ;
	for(int i = 0; i < FP_SIZE; i++)
	{
		key = key * 5 + *(str + i);
	}
	key %= HASH_SIZE;
	return key;
}

bool lrucache::insert_hash(char *str, listnode *p)
{
	unsigned long pos = str_hash(str);
	hashnode * q = hash_table[pos];
	if(q == NULL)//first inserting
	{
		q = new hashnode;
		q->list_pos = p;
		q->next = NULL;
		q->front = NULL;
		hash_table[pos] = q;
		return 1;
	}else while(q->next != NULL)q = q->next;
	
	if(q != NULL && q -> next == NULL)
	{
		hashnode *t = new hashnode;
		if(t == NULL)return 0;
		t->list_pos = p;
		t->front = q ;
		t->next = NULL;
		q->next = t;
		return 1;
	}else return 0;
}

bool lrucache::find_hash(char *str, listnode * &result)
{
	result = NULL;
	unsigned long pos = str_hash(str);
	hashnode * q = hash_table[pos];
	while(q != NULL)
	{
		if(strncmp( q->list_pos->hash_key, str, FP_SIZE) == 0)
		{
			result = q->list_pos;
			return 1;
		}else q = q->next;
	}
	return 0;
}


bool lrucache::delete_hash(char *str)
{
	unsigned long pos = str_hash(str);
	hashnode *q = hash_table[pos];
	while(q != NULL)
	{
		if(strncmp(q->list_pos->hash_key ,str ,FP_SIZE) == 0)
		{
			hashnode* t = q;
			if(t->front!= NULL)t->front->next = t-> next;
			else hash_table[pos] = t-> next;
			if(t->next != NULL)t->next->front = t-> front;
			delete t;
			return 1;
		}
	}
	return 0;
}

bool lrucache::add_node_to_head(char *str)
{
	listnode *q = new listnode;
	if(q == NULL)return 0;
	for(int i = 0;i < FP_SIZE ;i++)q->hash_key[i] = *(str + i);
	q->next = head;
	q->front = NULL;
	if(head == NULL) back =q;
	head = q;
	insert_hash(str, q);
	if(now_cache_size < max_cache_size)
		now_cache_size ++ ; 
	else
		delete_node(back);
	return 1;
}

bool lrucache::delete_node(listnode *p)
{
	listnode *t =p;
	if(p == NULL)return 0;
	if(t->front != NULL) t->front->next = t->next;
	else head = t->next;
	if(t->next != NULL) t->next->front = t->front;
	else back = t->front;
	delete_hash(t->hash_key);
	delete t;
	return 1;
	
}

bool lrucache::putdata(char *str)
{
	return add_node_to_head(str);
}

bool lrucache::find(char *str)
{
	listnode *t = NULL;
	bool flag = find_hash(str, t);
	if (!flag) return 0;
	else return 1;
}












