/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/model/reading.h"

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

/* [Loading functions] */

//[Load business.csv Function]
int load_business(char *filename, BUSINESSES bs){
  FILE *f;
  f = fopen(filename, "r");
  if (f == NULL) {
    perror("File doesn't exist.\n");
    return -1;
  }
  printf("Loading Businesses...\n");
  
  char *line = NULL;
  size_t len = 0;
  int i = 0;
  
  while (getline(&line, &len, f) != -1) {
    BUSINESS b = create_business(line);
    if (b != NULL){
      if(!(insert_business(bs, b)))
        printf("Line \x1b[91m%d\033[0m have a duplicate business id.\n", i + 1); 
    }
    else if (i > 0)
      printf("Line \x1b[91m%d\033[0m isn't valid as a business.\n", i + 1);
    i++;
  }
  printf("Loaded\n");
  free(line);
  fclose(f);
  return 1;
}

//[Load user.csv Function]
int load_user(char* filename, USERS us){
  FILE* f;
  f = fopen(filename, "r");
  if (f==NULL) {
    perror("File doesn't exist.\n");
    return -1;
  }
  printf("Loading Users...\n");
  
  char *line = NULL;
  size_t len = 0;
  int i = 0;
  
  while(getline(&line, &len, f) != -1) {
    USER u = create_user(line);
    if (u != NULL){
      if(!(insert_user(us, u)))
        printf("Line \x1b[91m%d\033[0m have a duplicate business id.\n", i + 1); 
    }
    else if (i > 0)
      printf("Line \x1b[91m%d\033[0m isn't valid as an user\n", i + 1);
    i++;
  }
  printf("Loaded\n");
  free(line);
  fclose(f);
  return 1;
}

//[Load review.csv Function]
int load_reviews(char *filename, REVIEWS rs, BUSINESSES bs, USERS us){
  FILE *f;
  f = fopen(filename, "r");
  if (f == NULL) {
    perror("File doesn't exist.\n");
    return -1;
  }
  printf("Loading Reviews...\n");
  
  char *line = NULL;
  size_t len = 0;
  int i = 0;
  while (getline(&line, &len, f) != -1) {
    REVIEW r = create_review(line);
    if (r != NULL){
      char* business_id = get_review_business_id(r);
      char* user_id = get_review_user_id(r);
      BUSINESS b = get_business(bs,business_id);
      USER u = get_user(us,user_id);
      if(b != NULL && u != NULL){
        if(!(insert_review(rs, r)))
              printf("Line \x1b[91m%d\033[0m have a duplicate review id.\n", i + 1);
      }
      else{
        printf("Line \x1b[91m%d\033[0m have a unknown business or user id.\n", i + 1);
        free_review(r);
      }
      free(business_id);
      free(user_id);
    }
    else if (i > 0)
      printf("Line \x1b[91m%d\033[0m isn't valid as a review\n", i + 1);
    i++;
  }
  printf("Loaded\n");
  free(line);
  fclose(f);
  return 1;
}