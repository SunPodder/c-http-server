typedef struct entry_t {
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;


typedef struct {
    entry_t **entries;
} ht_t;


ht_t* ht_create(unsigned int TABLE_SIZE);
char* ht_get(ht_t* hashtable, char* key);
void ht_set(ht_t* hashtable, char* key, char* value);
void ht_dump(ht_t* hashtable);

