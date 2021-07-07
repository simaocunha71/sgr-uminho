/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/model/user.h"

/* ---------------//--------------- [Structs] ---------------//--------------- */

//[struct user]
struct user {
    char *user_id;  //User id -> Array of char
    char *name;     //Name    -> Array of char
    char *friends;  //Friends -> Array of char
};

/* ---------------//--------------- [Private Functions] ---------------//--------------- */

//[Valid user function]
static int valid_user (char* str){
  int i, c = 0, r = 0;
  for (i = 0; str[i] != '\0'; i++)
    if (str[i] == ';' && str[i+1] != ';')
      r++;
    else if (str[i]!= ';' && r == 0)
      c++;
  return (c == 22 && r == 2);
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

//[Initialization function of struct user]
USER create_user(char *str) {
  USER u;
  if (valid_user(str)){
    u = malloc(sizeof(struct user));
    u->user_id = strdup(strsep(&str, ";"));
    u->name    = strdup(strsep(&str, ";"));
    u->friends = strdup(strsep(&str, "\n"));
  } 
  else u = NULL;
  return u;
}

//[Destruction function of struct user]
void free_user(USER u){
  if(u != NULL){
    free(u->user_id);
    free(u->name);
    free(u->friends);
    free(u);
  }
}

/* [Getters functions] */

//[Get user id of a struct user]
char* get_user_id (USER u) {
  char *user_id = strdup(u->user_id);
  return user_id;
}

//[Get name of a struct user]
char* get_user_name (USER u) {
  char *name = strdup(u->name);
  return name;
}

//[Get friends of a struct user]
char* get_user_friends (USER u) {
  char *friends = strdup(u->friends);
  return friends;
}

