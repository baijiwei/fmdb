#include "catalog.h"
#include <stdlib.h>
#include <string.h>
#include<vector>

using namespace std;
void fmdbCollection::FlushKVString()
{
	 std::vector<std::string> keys;
	 for (std::map<string,string>::iterator it=kv_map.begin(); it!=kv_map.end(); ++it) {
         keys.push_back(it->first);
	 }

     
     return;    
}

void fmdbCollection::AddOneKVValue(string key, string value)
{
	map<string, string>::iterator it=kv_map.find(key);
	if (kv_map.end() != it) {
		return;
	}
	curr_str_size += (key.size()+value.size()+2);
	if (curr_str_size >= total_str_size) {
		FlushKVString();
	}
	kv_map.insert(std::pair<string, string>(key, value));
}
