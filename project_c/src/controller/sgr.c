/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/controller/sgr.h"

/* ---------------//--------------- [Structs] ---------------//--------------- */
//[struct sgr]
struct sgr {
    USERS users;            //All users -> USERS
    BUSINESSES businesses;  //All businesses -> BUSINESSES
    REVIEWS reviews;        //All reviews -> REVIEWS
};

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

//[Initialization function of struct sgr]
SGR init_sgr(){
  SGR sgr = (SGR) malloc(sizeof(struct sgr));
  sgr->businesses = init_businesses();
  sgr->reviews = init_reviews();
  sgr->users = init_users();
  return sgr;
}

//[Destruction function of struct sgr]
void free_sgr(SGR sgr){
  destroy_businesses(sgr->businesses);
  destroy_reviews(sgr->reviews);
  destroy_users(sgr->users);
  free(sgr);
}

/* [Boolean Functions] */

//[Exist boolean function of users]
int exist_users(SGR sgr){
    return (sgr->users != NULL);
}

//[Exist boolean function of reviews]
int exist_reviews(SGR sgr){
    return (sgr->reviews != NULL);
}

//[Exist boolean function of businesses]
int exist_businesses(SGR sgr){
    return (sgr->businesses != NULL);
}

/* [Queries] */

//[Query 1]
SGR load_sgr(char* users, char* businesses, char* reviews){
  SGR sgr = init_sgr();
  load_business(businesses,sgr->businesses);
  int bsize = get_businesses_size(sgr->businesses);
  load_user(users,sgr->users);
  int usize = get_users_size(sgr->users);
  if(bsize && usize)
    load_reviews(reviews,sgr->reviews,sgr->businesses,sgr->users);
  else
    printf("Need load users file and businesses file to load the reviews file\n");
  return sgr;
}

//[Query 2]
TABLE businesses_started_by_letter(SGR sgr, char letter){
  TABLE t = init_table(0);
  set_table_columns(t, 2);
  add_title_of_column(t, "business_id", 0);
  add_title_of_column(t, "name", 1);
  set_title_lines(t,"Number of businesses");
  BUSINESSES bs = sgr->businesses;  
  puts_businesses_started_by_letter_on_table(bs,t,letter);
  set_default_pages(t);
  return t;
}

//[Query 3]
TABLE business_info(SGR sgr, char* business_id) {
  TABLE t;
  char *name, *city, *state, str_total_reviews[12], str_avg_stars[50];
  int count_reviews = 0;
  float avg_stars;
  BUSINESSES bs = sgr->businesses;
  BUSINESSES rs = sgr->reviews;
  BUSINESS b = get_business(bs,business_id);
  if(b != NULL){
    name = get_business_name(b);
    city = get_business_city(b);
    state = get_business_state(b);
    avg_stars = average_stars_of_business(b,rs,&count_reviews);
    sprintf(str_avg_stars, "%.2f", avg_stars);
    sprintf(str_total_reviews, "%d", count_reviews);  
    t = init_table(6);
    set_table_columns(t, 6);
    set_table_lines(t, 1);
    add_title_of_column(t, "business_id", 0);
    add_title_of_column(t, "name", 1);
    add_title_of_column(t, "city", 2);
    add_title_of_column(t, "state", 3);
    add_title_of_column(t, "average_stars", 4);
    add_title_of_column(t, "total_reviews", 5);
    add_info_string(t, business_id);
    add_info_string(t, name);
    add_info_string(t, city);
    add_info_string(t, state);
    add_info_string(t, str_avg_stars);
    add_info_string(t, str_total_reviews);
    set_table_lines_for_page(t, 1);
    set_table_number_of_pages(t, 1);  
    free(name);
    free(city);
    free(state);
  }
  else
    t = NULL;
  return t;
}

//[Query 4]
TABLE businesses_reviewed(SGR sgr, char* user_id){
  TABLE t = init_table(100);
  set_table_columns(t, 2);
  add_title_of_column(t, "business_id", 0);
  add_title_of_column(t, "name", 1);
  set_title_lines(t,"Number of businesses");
  REVIEWS rs = sgr->reviews;
  BUSINESSES bs = sgr->businesses;
  puts_businesses_reviewd_on_table(rs,bs,t,user_id);
  set_default_pages(t);
  return t;
}

//[Query 5]
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char* city){
  TABLE t = init_table(0);
  set_table_columns(t, 2);
  add_title_of_column(t, "business_id", 0);
  add_title_of_column(t, "name", 1);
  set_title_lines(t,"Number of businesses");
  REVIEWS rs = sgr->reviews;
  BUSINESSES bs = sgr->businesses;
  puts_businesses_with_stars_of_city_on_table(rs,bs,t,stars,city);
  set_default_pages(t);
  return t;
}

//[Query 6]
TABLE top_businesses_by_city(SGR sgr, int top){
  TABLE t = init_table(0);
  set_table_columns(t, 5);
  add_title_of_column(t, "#", 0);
  add_title_of_column(t, "business_id", 1);
  add_title_of_column(t, "name", 2);
  add_title_of_column(t, "average_stars", 3);
  add_title_of_column(t, "city", 4);
  set_title_lines(t,"Number of businesses");
  BUSINESSES bs = sgr->businesses;
  REVIEWS rs = sgr->reviews;
  puts_top_businesses_on_table(rs,bs,t,top);
  set_default_pages(t);
  return t;
}

//[Query 7]
TABLE international_users(SGR sgr){
  TABLE t = init_table(0);
  set_table_columns(t, 2);
  add_title_of_column(t, "#", 0);
  add_title_of_column(t, "user_id", 1);
  set_title_lines(t,"Number of users");
  REVIEWS rs = sgr->reviews;
  BUSINESSES bs = sgr->businesses;
  puts_international_users_on_table(rs,bs,t);
  set_default_pages(t);
  return t;
}

//[Query 8]
TABLE top_businesses_with_category(SGR sgr, int top, char *category){
  TABLE t = init_table(0);
  set_table_columns(t,4);
  add_title_of_column(t,"#",0);
  add_title_of_column(t,"business_id",1);
  add_title_of_column(t,"name",2);
  add_title_of_column(t,"average_stars",3);
  REVIEWS rs = sgr->reviews;
  BUSINESSES bs = sgr->businesses;
  puts_businesses_of_category_on_table(rs,bs,t,top,category);
  set_default_pages(t);
  return t;
}

//[Query 9]
TABLE reviews_with_word(SGR sgr, char* word){
  TABLE t = init_table(0);
  set_table_columns(t, 1);
  add_title_of_column(t, "review_id", 0);
  set_title_lines(t,"Number of reviews");
  REVIEWS rs = sgr->reviews;
  puts_reviews_with_word_on_table(rs,t,word);
  set_default_pages(t);
  return t;
}

//[Query 10 (Optional)]
TABLE friends_of_user (SGR sgr, char* user_id){
  TABLE t = init_table(0);
  set_table_columns(t, 1);
  USERS us = sgr->users;
  USER u = get_user(us, user_id);
  if (u != NULL){
    char *name = get_user_name(u);
    char *friends = get_user_friends(u);
    char *title = (char *)malloc(sizeof(char) * 50);
    strcpy(title, name);
    strcat(title, "'s friends");
    add_title_of_column(t, title, 0);
    set_title_lines(t,"Number of friends");
    char *buffer = (char *)malloc(sizeof(char) * strlen(friends));
    int i, j;
    for (i = 0; friends[i] != '\0'; i++) {
      j = 0;
      strcpy(buffer, &friends[i]);
      for (j = 0; buffer[j] != ',' && buffer[j] != '\0'; j++, i++);
      buffer[j] = '\0';
      inc_table_lines(t);
      add_info_string(t, buffer);
    }
    set_default_pages(t);
    free(friends);
    free(name);
    free(title);
    free(buffer);
  } 
  return t;
}

//[Query 11 (Optional)]
TABLE catalogues (SGR sgr, char mode){
  TABLE t;
  int size;
  if (mode == 'b'){
    size = get_businesses_size(sgr->businesses); 
    t = init_table(size*2);
    set_table_columns(t,2);
    add_title_of_column(t, "business_id",0);
    add_title_of_column(t, "name", 1);;
    set_title_lines(t,"Number of businesses");
    puts_businesses_on_catalogue(sgr->businesses, t);
    set_default_pages(t);
  }
  else if (mode == 'u'){
    size = get_users_size(sgr->users);
    t = init_table(size*2);
    set_table_columns(t,2);
    add_title_of_column(t, "user_id",0);
    add_title_of_column(t, "name", 1);
    set_title_lines(t,"Number of users");
    puts_users_on_catalogue(sgr->users, t);
    set_default_pages(t);
  }
  else if (mode == 'r'){
    size = get_reviews_size(sgr->reviews);
    t = init_table(size);
    set_table_columns(t,1);
    add_title_of_column(t, "reviews_id",0);
    set_title_lines(t,"Number of reviews");
    puts_reviews_on_catalogue(sgr->reviews, t);
    set_default_pages(t);
  }
  else t = NULL;
  return t;
}