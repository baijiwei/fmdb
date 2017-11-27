#ifndef CATALOG_H
#define CATALOG_H

#include "sys.h"
#include<string>
#include<map>

using namespace std;

class fmdbCollection {
public:
	fmdbCollection(string name):collName(name), curr_str_size(0){}
	~fmdbCollection() { kv_map.clear(); }
	void AddOneKVValue(string key, string value); 

	void DeleteOneKVValue(string key) {
		map<string, string>::iterator it=kv_map.find(key);
		if (kv_map.end() == it) {
			return;
		}
		kv_map.erase(it);
	}
	string FindKVValue(string key) {
		map<string, string>::iterator it=kv_map.find(key);
		if (kv_map.end() == it) {
			return "";
		}
		return it->second;
	}


	map<string, string> getHash() { return kv_map; }
    void FlushKVString();
private:
	const uint_T total_str_size = 32*1024*1024; 

    string collName;
	map<string, string> kv_map;
	uint_T curr_str_size;
};
class fmdbDatabase {
public:
	fmdbDatabase(string name):dbName(name){}
	~fmdbDatabase(){ collection_map.clear(); }

	void AddOneCollection(string name, fmdbCollection* collection) {
         collection_map.insert(std::pair<string, fmdbCollection*>(name, collection));
	}
	void AddOneCollection(string coll_name) {
         fmdbCollection* collection = new fmdbCollection(coll_name);
		 if (NULL == collection) {
			 printf("Memory has been exhausted.\n");
			 return;
		 }
         collection_map.insert(std::pair<string, fmdbCollection*>(coll_name, collection));
	}
	void DeleteOneCollection(string coll_name) {
		map<string, fmdbCollection*>::iterator it=collection_map.find(coll_name);
		if (collection_map.end() == it) {
			return;
		}
		collection_map.erase(it);
	}

	fmdbCollection* findCollection(string coll_name) {
		map<string, fmdbCollection*>::iterator it=collection_map.find(coll_name);
		if (collection_map.end() == it) {
			return NULL;
		}
		return it->second;
	}



	map<string, fmdbCollection*> getCollectionMap() { return collection_map; }
private:
    string dbName;
    map<string, fmdbCollection*>  collection_map;
};
#endif
