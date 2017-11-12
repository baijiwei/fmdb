#ifndef __BTREE_H__
#define __BTREE_H__

#define M 4 
#define KEY_NUM (2 * M - 1)

typedef int type_t;

typedef struct btree_t
{
	 int num;                        /* number of keys */
	 char leaf;                      /* if or not is a leaf */
	 type_t key[KEY_NUM];
	 struct btree_t* child[KEY_NUM + 1];
}btree_t, btnode_t;

btree_t*    btree_create();
btree_t*    btree_insert(btree_t *btree, type_t key);
btree_t*    btree_delete(btree_t *btree, type_t key);

/*
 *  * search the key in the btree, save the key index of the btree node in the index
 *   */
btree_t*    btree_search(btree_t *btree, type_t key, int *index);

#endif /* __BTREE_H__ */

