#include<cstdlib>
#include<cstdio>
#include "lrucache.h"
using namespace std;

int main()
{
	lrucache cache(6);
	cache.putdata("aaaaaa");
	cache.putdata("bbbbbb");
	cache.putdata("cccccc");
	cache.putdata("dddddd");
	cache.putdata("eeeeee");
	printf("%d\n",cache.find("bbbbbb"));
	printf("%d\n",cache.find("bbbbab"));
	cache.putdata("feeeee");
	cache.putdata("ffeeee");
	printf("%d\n",cache.find("aaaaaa"));
	printf("%d\n",cache.find("cccccc")); 	
	return 0;
}
