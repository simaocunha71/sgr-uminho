/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/model/hashes.h"

/* ---------------//--------------- [Structs] ---------------//--------------- */

/* [struct hashdata]
>> Auxiliary struct that helps in handling hashes, especially in foreach */
struct hashdata {
    void* table; 
    void* datas[5];
};

/* ---------------//--------------- [Private Functions] ---------------//--------------- */

//[Destroy key of hash function]
static void free_key (gpointer data) {
  free (data);
}

//[Destroy value of hash (USERS) function]
static void destroy_user (gpointer data) {
    USER u = (USER) data;
    free_user(u);
}

//[Destroy value of hash (REVIEW) function]
static void destroy_review (gpointer data) {
    REVIEW r = (REVIEW) data;
    free_review(r);
}

//[Destroy value of hash (BUSINESS) function]
static void destroy_business (gpointer data) {
    BUSINESS b = (BUSINESS) data;
    free_business(b);
}

//[Destroy value of hash (BUSINESS) function]
static void destroy_hashdata (gpointer data) {
    HASHDATA hd = (HASHDATA) data;
    free_hashdata(hd);
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

//[Initialization function of hash BUSINESSES]
BUSINESSES init_businesses (){
    BUSINESSES bs = g_hash_table_new_full (g_str_hash, g_str_equal, free_key, destroy_business);
    return bs;
}

//[Destruction function of hash BUSINESSES]
void destroy_businesses(BUSINESSES bs){
    g_hash_table_destroy (bs);
}

//[Initialization function of hash REVIEWS]
REVIEWS init_reviews(){
    REVIEWS rs = g_hash_table_new_full (g_str_hash, g_str_equal, free_key, destroy_review);
    return rs;
}

//[Destruction function of hash REVIEWS]
void destroy_reviews(REVIEWS rs){
    g_hash_table_destroy (rs);
}

//[Initialization function of hash USERS]
USERS init_users (){
    USERS us = g_hash_table_new_full (g_str_hash, g_str_equal, free_key, destroy_user);
    return us;
}

//[Destruction function of hash USERS]
void destroy_users(USERS us){
    g_hash_table_destroy (us);
}

//[Initialization function of struct hashdata]
HASHDATA init_hashdata (){
  HASHDATA hd = (HASHDATA) malloc(sizeof(struct hashdata));
  if(hd == NULL)
    abort();
  return hd;
}

//[Destruction function of struct hashdata]
void free_hashdata (HASHDATA hd){
  if (hd != NULL) {
    free(hd);
  }
}

//[Create function of struct hashdata of a BUSINESS]
HASHDATA create_hashdata_business(BUSINESS b){
  int* ptr_total_reviews = malloc(sizeof(int));
  if (ptr_total_reviews == NULL)
    abort();
  else *ptr_total_reviews = 0;
      
  float* ptr_stars = malloc(sizeof(float));
  if (ptr_stars == NULL)
    abort();
  else *ptr_stars = 0.0;
  
  HASHDATA hd_business = init_hashdata(4);
  put_data(hd_business,0,get_business_id(b));
  put_data(hd_business,1,get_business_name(b));
  put_data(hd_business,2,ptr_total_reviews);
  put_data(hd_business,3,ptr_stars);
  return hd_business;
}

//[Create function of hash table of hashdatas]
GHashTable * create_hashtable_of_hd(){
  return g_hash_table_new_full(g_str_hash, g_str_equal,free_key,destroy_hashdata);
}

//[Destruction function of hash table of hashdatas]
void destroy_hashdatas(GHashTable* hash){
  g_hash_table_destroy(hash);
}

/* [Inserts functions] */

//[Insert function of hash BUSINESSES]
int insert_business (BUSINESSES bs, BUSINESS b){
    return (g_hash_table_insert(bs, (gpointer)get_business_id(b), (gpointer)b));
}

//[Insert function of hash REVIEWS]
int insert_review (REVIEWS rs, REVIEW r){
	return (g_hash_table_insert(rs, (gpointer) get_review_id(r), (gpointer)r));
}

//[Insert function of hash USERS]
int insert_user (USERS us, USER u){
	return (g_hash_table_insert(us, (gpointer) get_user_id(u), (gpointer)u));
}

//[Insert hashdtata on a hash table]
void insert_hashdata(GHashTable * hash, gpointer key, gpointer value){
  g_hash_table_insert(hash, key, value);
}

/* [Getters functions] */

//[Get BUSINESS of a hash BUSINESSES]
BUSINESS get_business(BUSINESSES bs, char* business_id){
	BUSINESS b = g_hash_table_lookup(bs, (gconstpointer) business_id);
	return b;
}

//[Get REVIEW of a hash REVIEWS]
REVIEW get_review(REVIEWS rs, char* review_id){
	REVIEW r = g_hash_table_lookup(rs, (gconstpointer) review_id);
	return r;
}

//[Get USER of a hash USERS]
USER get_user(USERS us, char* user_id){
	USER u = g_hash_table_lookup(us, (gconstpointer) user_id);
	return u;
}

//[Get hash size of a hash BUSINESSES]
int get_businesses_size(BUSINESSES bs){
  return g_hash_table_size (bs);
}

//[Get hash size of a hash REVIEWS]
int get_reviews_size(REVIEWS rs){
  return g_hash_table_size (rs);
}

//[Get hash size of a hash USERS]
int get_users_size(USERS us){
  return g_hash_table_size (us);
}

//[Get table of a hashdata]
void* get_hashdata_table (HASHDATA hd){
  return hd->table;
}

//[Get data of a hashdata]
void* get_data (HASHDATA hd, int i){
  return hd->datas[i];
}

//[Get hashdata of a hash table]
gpointer get_hashdata(GHashTable * hash, gconstpointer key){
  return g_hash_table_lookup(hash, key);
}


//[Put table on a hashdata]
void put_hashdata_table (HASHDATA hd, void* t){
  hd->table = t;
}

//[Put data on a hashdata]
void put_data (HASHDATA hd, int i, void* data){
  if(i >= 5)
    printf("Error (put_data), max value is 4");
  hd->datas[i] = data;
}


