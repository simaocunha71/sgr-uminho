/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/controller/hashcontrol.h"


#define unused(x) (void)(x)
/* ---------------//--------------- [Private Functions] ---------------//--------------- */

//[Put in the table the deals that start with the letter (used on Query 1)]
static void filter_businesses_by_letter(gpointer key, gpointer value, gpointer user_data){
  HASHDATA hd = (HASHDATA) user_data;
  TABLE t = (TABLE) get_hashdata_table(hd);
  BUSINESS b = (BUSINESS) value;
  char* name = get_business_name(b);
  char* letter = (char*) get_data(hd,0);
  if (name[0] == toupper(*letter) || name[0] == tolower(*letter)){
    inc_table_lines(t);
    char* business_id = (char*) key;
    add_info_string(t, business_id);
    add_info_string(t, name);
  }
  free(name);
}

//[Calculates the number of average stars (used on Query 3, 5 e 6)]
static float calculate_average_stars (int total_reviews, float stars){
  float average_stars;
  if(total_reviews > 0)
    average_stars = stars/(float) total_reviews;
  else average_stars = 0.0;
  return average_stars;
}

//[Add stars and increment total reviews (used on Query 3,5 e 6)]
static void add_stars_review (int* ptr_total_reviews, float* ptr_stars,int stars){
  *ptr_total_reviews += 1;
  *ptr_stars += stars;
}

//[Counts the total number of reviews and the total number of stars for a business (used on Query 3)]
static void count_business_stars(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd_business = (HASHDATA) user_data;
  REVIEW r = (REVIEW) value;
  char* review_business_id = get_review_business_id(r);
  char* business_id = (char*) get_data(hd_business,0);
  if (strcmp(review_business_id,business_id) == 0){
    int* ptr_total_reviews = (int*) get_data(hd_business,2);
    float* ptr_stars = (float*) get_data(hd_business,3);
    add_stars_review(ptr_total_reviews,ptr_stars,get_review_stars(r));
  }
  free(review_business_id);
}

//[Put the business reviewed by the user on the table (used on Query 4)]
static void filter_business_reviewed_by_user (gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  TABLE t = (TABLE) get_hashdata_table(hd);
  REVIEW r = (REVIEW) value;
  char* review_user_id = get_review_user_id(r);
  char* user_id = (char*) get_data(hd,1);
  if (strcmp(review_user_id, user_id) == 0) {
    BUSINESSES bs = (BUSINESSES) get_data(hd,0);
    char* business_id = get_review_business_id(r);
    BUSINESS b = (BUSINESS) get_hashdata(bs, (gconstpointer) business_id);
    char* business_name = get_business_name(b);
    inc_table_lines(t);
    add_info_string(t, business_id);
    add_info_string(t, business_name);
    free(business_id);
    free(business_name);
  }
  free(review_user_id);
}

//[Inserts the business of the city in a hash table (used on Query 5)]
static void filter_businesses_by_city(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  BUSINESS b = (BUSINESS) value;
  char* business_city = get_business_city(b);
  char* city = get_data(hd,1);
  if (strcmp(city,business_city) == 0){
    HASHDATA hd_business = create_hashdata_business(b);
    GHashTable* bs_of_city = (GHashTable*) get_data(hd,0);
    insert_hashdata(bs_of_city, (gpointer) get_business_id(b), (gpointer) hd_business);
  }
  free(business_city);
}

//[Counts the total number of reviews and the total number of stars for a business if it exists in the hash table (used on Query 5 e 8)]
static void calculate_stars_of_business(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  REVIEW r = (REVIEW) value;
  char* business_id = get_review_business_id(r);
  GHashTable* hash_bs = (GHashTable*) get_data(hd,0);
  HASHDATA hd_business = (HASHDATA) get_hashdata(hash_bs, (gconstpointer) business_id);
  if (hd_business){
    int* ptr_total_reviews = get_data(hd_business,2);
    float* ptr_stars = get_data(hd_business,3);
    add_stars_review(ptr_total_reviews,ptr_stars,get_review_stars(r));
  }
  free(business_id);
}

//[Put on the table the trades that have more stars than the order (used on Query 5)]
static void filter_business_for_stars(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd = (HASHDATA)user_data;
  TABLE t = (TABLE) get_hashdata_table(hd);
  HASHDATA hd_business = (HASHDATA)value;
  int* ptr_total_reviews = (int*) get_data(hd_business,2);
  float* ptr_stars = (float*) get_data(hd_business,3);
  float average_stars = calculate_average_stars(*ptr_total_reviews,*ptr_stars);
  float *ptr_necessary_stars = (float *) get_data(hd,0);
  if (average_stars >= *ptr_necessary_stars){
    inc_table_lines(t);
    char* business_id = (char *) get_data(hd_business,0);
    char* business_name = (char *) get_data(hd_business,1);
    add_info_string(t, business_id);
    add_info_string(t, business_name);
  }
}

//[Insert business into your city hash table (used on Query 6)]
static void insert_cities(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  BUSINESS b = (BUSINESS) value;
  char* city = get_business_city(b);
  GHashTable* bs_cities = (GHashTable*) get_data(hd,0);
  HASHDATA hd_of_city = (HASHDATA) get_hashdata(bs_cities, (gconstpointer) city);
  if (hd_of_city){
    GHashTable* bs_of_city = (GHashTable*) get_data(hd_of_city,0);
    HASHDATA hd_business = create_hashdata_business(b);
    insert_hashdata(bs_of_city, (gpointer) get_business_id(b), (gpointer) hd_business);
  }
  else{
      GHashTable* bs_of_city = create_hashtable_of_hd();
      HASHDATA hd_of_city = init_hashdata();
      put_data(hd_of_city,0,bs_of_city);
      int* ptr_top = (int*) get_data(hd,1);
      int top = *ptr_top;
      char** ord_business = malloc(sizeof(char *) * top);
      if(ord_business == NULL)
        abort();
      else
        for (int i = 0; i < top; i++)
          ord_business[i] = NULL;
      put_data(hd_of_city,1,(void*) ord_business);
      HASHDATA hd_business = create_hashdata_business(b);
      insert_hashdata(bs_of_city, (gpointer)get_business_id(b), (gpointer)hd_business);
      insert_hashdata(bs_cities, (gpointer)get_business_city(b), (gpointer)hd_of_city);
  }
  free(city);
}

//[Counts the number of stars and the total number of reviews for businesses in all cities (used on Query 6)]
static void calculate_stars_reviews_for_all_cities(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  REVIEW r = (REVIEW) value;
  BUSINESSES bs = (BUSINESSES) get_data(hd,1);
  char* business_id = get_review_business_id(r);
  BUSINESS b = (BUSINESS) get_hashdata(bs, (gconstpointer) business_id);
  if (b != NULL){
    char* city = get_business_city(b);
    HASHDATA hd_of_city = (HASHDATA) get_hashdata(get_data(hd,0), (gconstpointer) city);
    if (hd_of_city != NULL){
      GHashTable* bs_of_city = (GHashTable*) get_data(hd_of_city,0);
      HASHDATA hd_business = (HASHDATA) get_hashdata(bs_of_city, (gconstpointer) business_id);
      if (hd_business != NULL){
          int* ptr_total_reviews = (int*) get_data(hd_business,2);
          float* ptr_stars = (float*) get_data(hd_business,3);
          add_stars_review(ptr_total_reviews,ptr_stars,get_review_stars(r));
      }
    }
    free(city);
  }
  free(business_id);
}

//[Sorts trades by average order of number of stars in a given top (used on Query 6 e 8)]
static void ordering_average_stars(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  int i, j;
  HASHDATA hd_top = (HASHDATA) user_data;
  HASHDATA hd_business = (HASHDATA) value;
  float average_stars;
  int *ptr_total_reviews = (int*) get_data(hd_business,2);
  float *ptr_stars = (float*) get_data(hd_business,3);
  average_stars = calculate_average_stars(*ptr_total_reviews,*ptr_stars);
  if (average_stars > 0.0){
    int* ptr_top = (int*) get_data(hd_top,1);
    int top = *ptr_top;
    float* ord_average_stars = (float*) get_data(hd_top,0);
    for (i = 0; i < top && ord_average_stars[i] >= average_stars; i++);
    if (i < top){
      char **ord_business = get_data(hd_top,2);
      for (j = top - 2; j >= i; j--){
          ord_business[j + 1] = ord_business[j];
          ord_average_stars[j + 1] = ord_average_stars[j];
      }
      ord_average_stars[i] = average_stars;
      ord_business[i] = get_data(hd_business,0);
    }
  }
}

//[Put the businesses of each city on the table (used on Query 6)]
static void puts_business_on_table(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  int i;
  HASHDATA hd = (HASHDATA) user_data;
  HASHDATA hd_of_city = (HASHDATA) value;
  TABLE t = (TABLE) get_hashdata_table(hd);
  GHashTable *bs_of_city = (GHashTable*) get_data(hd_of_city,0);
  int* ptr_top = (int*) get_data(hd,1);
  int top = *ptr_top;
  float* ord_average_stars = malloc(sizeof(float) * top);
  if (ord_average_stars == NULL)
    abort();
  else
    for (i = 0; i < top; i++)
      ord_average_stars[i] = 0.0; 
  char** ord_business = (char **) get_data(hd_of_city,1);
  HASHDATA hd_top = init_hashdata();
  put_data(hd_top,0,(void*) ord_average_stars);
  put_data(hd_top,1,(void*) ptr_top);
  put_data(hd_top,2,(void*) ord_business);
  char* city = (char*) key;
  g_hash_table_foreach(bs_of_city, ordering_average_stars, (gpointer) hd_top);  
  char position[12];
  char average_stars[50];
  if (ord_average_stars[0] > 0){
    for (i = 0; i < top && ord_average_stars[i] > 0; i++){
      HASHDATA hd_business = (HASHDATA) get_hashdata(bs_of_city, (gconstpointer)ord_business[i]);
      char* name = (char*) get_data(hd_business,1);
      sprintf(average_stars, "%.2f", ord_average_stars[i]);
      sprintf(position, "%d", i + 1);
      inc_table_lines(t);
      add_info_string(t, position);
      add_info_string(t, ord_business[i]);
      add_info_string(t, name);
      add_info_string(t, average_stars);
      add_info_string(t, city);
    }
  }
  destroy_hashdatas(bs_of_city);
  free(ord_business);
  free(ord_average_stars);
  free_hashdata(hd_top);
}

//[Insert users into the hash table counting whether they visited +1 city (used on Query 7)]
static void insert_users (gpointer key, gpointer value, gpointer user_data) {
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  GHashTable* inter_users = (GHashTable*) get_data(hd,0);
  REVIEW r = (REVIEW) value;
  BUSINESSES bs = (BUSINESSES) get_data(hd,1);
  char* review_user_id = get_review_user_id(r);
  char* review_business_id = get_review_business_id(r);
  HASHDATA hd_users = (HASHDATA) get_hashdata(inter_users, (gconstpointer) review_user_id);
  if (hd_users != NULL){
    int *ptr_visited_states = (int*) get_data(hd_users,0);
    if(*ptr_visited_states < 2){
      BUSINESS b = (BUSINESS) get_hashdata(bs, (gconstpointer) review_business_id);
      if(b != NULL){
        char* state = get_business_state(b);
        char* visited_state = (char*) get_data(hd_users,1);
        if(strcmp(state,visited_state)!=0){
          *ptr_visited_states +=1;
        }           
      }
    }
  }
  else  {
    BUSINESS b = get_hashdata(bs, (gconstpointer) review_business_id);
    if(b != NULL){
      char* state = get_business_state(b);
      int* ptr_visited_states = (int*) malloc(sizeof(int));
      if(ptr_visited_states == NULL){
        abort();
      }
      else 
        *ptr_visited_states = 1;
      HASHDATA hd_users = init_hashdata();
      put_data(hd_users,0,ptr_visited_states);
      put_data(hd_users,1,state);
      insert_hashdata(inter_users, (gpointer)review_user_id, (gpointer) hd_users);
    }
  }
}

//[Puts international users on the table (used on Query 7)]
static void puts_user_in_table (gpointer key, gpointer value, gpointer user_data) {
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  TABLE t = (TABLE) get_hashdata_table(hd);
  HASHDATA hd_users = (HASHDATA) value;
  int* ptr_visited_states = (int*) get_data(hd_users,0);
  if(*ptr_visited_states == 2){
    inc_table_lines(t);
    char number_of_users[12];
    int number = get_table_size(t);
    char* user_id = (char*) key;
    if(!number) number = 1;
    else number = number/2 + 1;
    sprintf(number_of_users, "%d", number);
    add_info_string(t,number_of_users);
    add_info_string(t,user_id);
  }
}

//[Boolean function that says if a char is not a letter (used on Query 8,9)]
static int not_letter(char c){
  return !(isupper(c) || islower(c));
}

//[Boolean function that says if a word is inserted in a text (used on Query 8,9)]
static int word_in_text(char *word, char *text){
  int size_word, size_text, i, j; 
  size_word = strlen(word);
  size_text = strlen(text);
  for (i = 0; i <= size_text - size_word; i++){
    for (j = 0; j < size_word; j++)
      if (tolower(text[i + j]) != tolower(word[j]))
        break;
    if (j == size_word && (i < 1 || not_letter(text[i - 1])) && not_letter(text[i + j]))
      return 1;
  }
  return 0;
}

//[Insert the trades in the table that have the category given in their categories (used on Query 8)]
static void filter_businesses_by_category(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  HASHDATA hd = (HASHDATA) user_data;
  BUSINESS b = (BUSINESS) value;
  GHashTable *bs_of_category = (GHashTable*) get_data(hd,0);
  char* categories = get_business_categories(b);
  char* category = (char*) get_data(hd,1);
  if(word_in_text(category,categories)){
    char* business_id = get_business_id(b);
    HASHDATA hd_business = create_hashdata_business(b);
    insert_hashdata(bs_of_category, (gpointer)business_id, (gpointer) hd_business);
  }
  free(categories);
}

//[Insert the reviews in the table that have the word given in your text (used on Query 9)]
static void filter_reviews_with_word(gpointer key, gpointer value, gpointer user_data){
  HASHDATA hd = (HASHDATA) user_data;
  TABLE t = (TABLE) get_hashdata_table(hd);
  REVIEW r = (REVIEW) value;
  char* review_text = get_review_text(r);
  char* word = (char*) get_data(hd,0);
  char* review_id = (char*) key;
  if (word_in_text(word,review_text)){
    inc_table_lines(t);
    add_info_string(t,review_id);
  }
  free(review_text);
}

//[Insert the businesses in the catalogue (used on Query 11 mode 'b')]
static void insert_business_on_catalogue(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  TABLE t = (TABLE) user_data;
  BUSINESS b = (BUSINESS) value;
  inc_table_lines(t);
  add_info_string(t, get_business_id(b));
  add_info_string(t, get_business_name(b));
}

//[Insert the users in the catalogue (used on Query 11 mode 'u')]
static void insert_user_on_catalogue(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  TABLE t = (TABLE) user_data;
  USER u = (USER)value;
  inc_table_lines(t);
  add_info_string(t, get_user_id(u));
  add_info_string(t, get_user_name(u));    
}

//[Insert the reviews in the catalogue (used on Query 11 mode 'r')]
static void insert_review_on_catalogue(gpointer key, gpointer value, gpointer user_data){
  unused(key);
  TABLE t = (TABLE) user_data;
  REVIEW r = (REVIEW) value;
  inc_table_lines(t);
  add_info_string(t, get_review_id(r));
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

//[Auxiliar that controls hashs of Query 2]
void puts_businesses_started_by_letter_on_table (BUSINESSES bs, TABLE t, char letter){
  HASHDATA hd = init_hashdata();
  put_hashdata_table(hd,(void*) t);
  put_data(hd,0,&letter);
  g_hash_table_foreach(bs, filter_businesses_by_letter, (gpointer) hd);
  free_hashdata(hd);
}

//[Auxiliar that controls hashs of Query 3]
float average_stars_of_business(BUSINESS b, REVIEWS rs, int* count_reviews){
  HASHDATA hd_business = create_hashdata_business(b);
  g_hash_table_foreach(rs, count_business_stars, (gpointer)hd_business);
  int* ptr = (int*) get_data(hd_business,2);
  *count_reviews = *ptr;
  float* stars = (float*) get_data(hd_business,3);
  float avg_stars = calculate_average_stars(*count_reviews, *stars);
  free_hashdata(hd_business);
  return avg_stars;
}

//[Auxiliar that controls hashs of Query 4]
void puts_businesses_reviewd_on_table (REVIEWS rs, BUSINESSES bs, TABLE t, char* user_id){
  HASHDATA hd = init_hashdata();
  put_hashdata_table(hd,(void*) t);
  put_data(hd,0,(void*) bs);
  put_data(hd,1,(void*) user_id);
  g_hash_table_foreach(rs, filter_business_reviewed_by_user, (gpointer) hd);
  free_hashdata(hd);    
}

//[Auxiliar that controls hashs of Query 5]
void puts_businesses_with_stars_of_city_on_table (REVIEWS rs, BUSINESSES bs,TABLE t, float stars, char* city){
  GHashTable *bs_of_city = create_hashtable_of_hd();
  HASHDATA hd = init_hashdata();
  put_data(hd,0,(void*) bs_of_city);
  put_data(hd,1,(void*) city);
  g_hash_table_foreach(bs, filter_businesses_by_city, (gpointer)hd);
  g_hash_table_foreach(rs, calculate_stars_of_business, (gpointer)hd);
  put_hashdata_table(hd,(void*) t);
  put_data(hd,0,(void*) &stars);
  g_hash_table_foreach(bs_of_city, filter_business_for_stars, (gpointer)hd);
  destroy_hashdatas(bs_of_city);
  free_hashdata(hd);
}

//[Auxiliar that controls hashs of Query 6]
void puts_top_businesses_on_table(REVIEWS rs, BUSINESSES bs, TABLE t, int top){
  GHashTable *bs_cities = create_hashtable_of_hd();
  HASHDATA hd = init_hashdata();
  put_data(hd,0,bs_cities);
  put_data(hd,1,(void*)&top);
  g_hash_table_foreach(bs, insert_cities, (gpointer)hd);  
  put_data(hd,1,(void*)bs);
  g_hash_table_foreach(rs, calculate_stars_reviews_for_all_cities, (gpointer)hd);
  put_hashdata_table(hd,(void*) t);
  put_data(hd,1,(void*)&top);
  g_hash_table_foreach(bs_cities, puts_business_on_table, (gpointer)hd);
  destroy_hashdatas(bs_cities);
  set_default_pages(t);
  free_hashdata(hd);
}

//[Auxiliar that controls hashs of Query 7]
void puts_international_users_on_table(REVIEWS rs, BUSINESSES bs, TABLE t){
  GHashTable *inter_users = create_hashtable_of_hd();
  HASHDATA hd = init_hashdata();
  put_data(hd,0,(void*)inter_users);
  put_data(hd,1,(void*)bs);
  g_hash_table_foreach(rs, insert_users, (gpointer) hd);
  put_hashdata_table(hd,(void*) t);
  g_hash_table_foreach(inter_users, puts_user_in_table, (gpointer) hd);
  free_hashdata(hd);
}

//[Auxiliar that controls hashs of Query 8]
void puts_businesses_of_category_on_table(REVIEWS rs, BUSINESSES bs, TABLE t, int top, char* category){
  int i;
  GHashTable *bs_of_category = create_hashtable_of_hd();
  HASHDATA hd_top = init_hashdata();
  put_data(hd_top,0,(void*)bs_of_category);
  put_data(hd_top,1,(void*)category);
  g_hash_table_foreach(bs, filter_businesses_by_category, (gpointer) hd_top);
  g_hash_table_foreach(rs, calculate_stars_of_business, (gpointer)hd_top);
  put_data(hd_top,1,(void*)&top);
  float* ord_average_stars = malloc(sizeof(float) * top);
  if (ord_average_stars == NULL)
    abort();
  else
    for (i = 0; i < top; i++)
      ord_average_stars[i] = 0.0;
  put_data(hd_top,0,(void*)ord_average_stars);
  char** ord_business = (char **) malloc(sizeof(char*) * top);
  if(ord_business == NULL){
    abort();
  }
  else
    for (i = 0; i < top; i++)
      ord_business[i] = NULL;
  put_data(hd_top,2,(void*)ord_business);
  g_hash_table_foreach(bs_of_category, ordering_average_stars, (gpointer) hd_top);
  char position[12];
  char average_stars[50];
  if (ord_average_stars[0] > 0){
    for (i = 0; i < top && ord_average_stars[i] > 0; i++){
      HASHDATA hd_business = (HASHDATA) get_hashdata(bs_of_category, (gconstpointer)ord_business[i]);
      char* name = (char*) get_data(hd_business,1);
      sprintf(average_stars, "%.2f", ord_average_stars[i]);
      sprintf(position, "%d", i + 1);
      inc_table_lines(t);
      add_info_string(t, position);
      add_info_string(t, ord_business[i]);
      add_info_string(t, name);
      add_info_string(t, average_stars);
    }
  }
  destroy_hashdatas(bs_of_category);
  free_hashdata(hd_top);
  free(ord_business);
  free(ord_average_stars);
}

//[Auxiliar that controls hashs of Query 9]
void puts_reviews_with_word_on_table (REVIEWS rs, TABLE t, char* word){
  HASHDATA hd = init_hashdata();
  put_hashdata_table(hd,(void*) t);
  put_data(hd,0,(void*)word);
  g_hash_table_foreach(rs, filter_reviews_with_word, (gpointer)hd);
  free_hashdata(hd);
}

//[Auxiliar that controls hashs of Query 11-mode'b']
void puts_businesses_on_catalogue (BUSINESSES bs, TABLE t){
  g_hash_table_foreach(bs, insert_business_on_catalogue, (gpointer)t);
}

//[Auxiliar that controls hashs of Query 11-mode'u']
void puts_users_on_catalogue (USERS us, TABLE t){
  g_hash_table_foreach(us, insert_user_on_catalogue, (gpointer)t);
}

//[Auxiliar that controls hashs of Query 11-mode'r']
void puts_reviews_on_catalogue (REVIEWS rs, TABLE t){
  g_hash_table_foreach(rs, insert_review_on_catalogue, (gpointer)t);
}