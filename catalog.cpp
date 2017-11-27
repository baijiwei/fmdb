#include "catalog.h"

using namespace std;
void fmdbCollection::FlushKVString()
{
     return;    
}

void fmdbCollection::AddOneKVValue(string key, string value)
{
	map<string, string>::iterator it=kv_map.find(key);
	if (kv_map.end() != it) {
		return;
	}
	if (curr_str_size >= total_str_size) {
		FlushKVString();
	}
	kv_map.insert(std::pair<string, string>(key, value));
}
