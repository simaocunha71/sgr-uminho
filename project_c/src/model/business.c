/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/model/business.h"

/* ---------------//--------------- [Structs] ---------------//--------------- */

//[struct business]
struct business {
    char *business_id;  //Business id -> Array of char  
    char *name;         //Name        -> Array of char
    char *city;         //City        -> Array of char
    char *state;        //State       -> Array of char
    char *categories;   //Categories  -> Array of char
};

/* ---------------//--------------- [Private Functions] ---------------//--------------- */

//[Function that passes an entire string to lowercase]
static void str_to_lower (char* str){
    int i;
    for (i = 0; str[i] != '\0'; i++)
        str[i] = tolower((int) str[i]);
}

//[Valid business function]
static int valid_business (char* s){
    int i,c = 0,r = 0;
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == ';' && s[i+1] != ';')
          r++;
        else if (s[i]!= ';' && r == 0)
          c++;
    return (c == 22 && r == 4);
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

//[Initialization function of struct business]
BUSINESS create_business(char *str){
  BUSINESS b;
  if(valid_business(str)){
    b = malloc(sizeof(struct business));
    b->business_id = strdup(strsep(&str, ";"));
    b->name        = strdup(strsep(&str, ";"));
    b->name[0] = toupper(b->name[0]);
    b->city        = strdup(strsep(&str, ";"));
    str_to_lower(b->city);
    b->city[0] = toupper(b->city[0]);
    b->state       = strdup(strsep(&str, ";"));
    b->categories  = strdup(strsep(&str, "\n"));
  }
  else b = NULL;
  return b;
}

//[Destruction function of struct business]
void free_business(BUSINESS b){
  if(b != NULL){
    free(b->business_id);
    free(b->name);
    free(b->city);
    free(b->state);
    free(b->categories);
    free(b);
  }
}

/* [Getters functions] */

//[Get business id of a struct business]
char* get_business_id (BUSINESS b){
  char *id = strdup(b->business_id);
  return id;
}

//[Get name of a struct business]
char* get_business_name (BUSINESS b){
  char *name = strdup(b->name);
  return name;
}

//[Get city of a struct business]
char* get_business_city (BUSINESS b){
  char *city = strdup(b->city);
  return city;
}

//[Get state of a struct business]
char* get_business_state (BUSINESS b){
  char *state = strdup(b->state);
  return state;
}

//[Get categories of a struct business]
char* get_business_categories (BUSINESS b){
  char *categories = strdup(b->categories);
  return categories;
}
