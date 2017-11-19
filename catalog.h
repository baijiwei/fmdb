#ifndef CATALOG_H
#define CATALOG_H

#include "sys.h"
#include<string>
#include<map>

using namespace std;

class fmdbCollection {
public:
	fmdbCollection(string name):collName(name){}
	~fmdbCollection() { kv_map.clear(); }
	void AddOneKVValue(string key, string value) {
		map<string, string>::iterator it=kv_map.find(key);
		if (kv_map.end() != it) {
		}
		kv_map.insert(key, value);
	}

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
			return;
		}
		return it->second;
	}


	getHash() { return kv_map; }
private:
    string collName;
	map<string, string> kv_map;
};
class fmdbDatabase {
public:
	fmdbDatabase(string name):dbName(name){}
	~fmdbDatabase(){ collection_map.clear(); }

	void AddOneCollection(string coll_name) {
         fmdbCollection* collection = new fmdbCollection(coll_name);
		 if (NULL == collection) {
			 printf("Memory has been exhausted.\n")
			 return;
		 }
         collection_map.insert(coll_name, collection);
	}
	void DeleteOneCollection(string coll_name) {
		map<string, string>::iterator it=collection_map.find(key);
		if (collection_map.end() == it) {
			return;
		}
		collection_map.erase(it);
	}

	fmdbCollection* findCollection(string coll_name) {
		map<string, string>::iterator it=collection_map.find(coll_name);
		if (collection_map.end() == it) {
			return;
		}
		return it.second;
	}



	getHash() { return collection_map; }
private:
    string dbName;
    map<string, fmdbCollection*>  collection_map;
};
#endif
