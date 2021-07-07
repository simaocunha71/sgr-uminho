/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/model/review.h"

/* ---------------//--------------- [Structs] ---------------//--------------- */

//[struct review]
struct review {
    char *review_id;    //Review id                                    -> Array of char
    char *user_id;      //User id                                      -> Array of char
    char *business_id;  //Business id                                  -> Array of char
    float stars;        //Stars of review                              -> Float
    int useful;         //Number of people who found the review useful -> Int
    int funny;          //Number of people who found the review funny  -> Int
    int cool;           //Number of people who found the review cool   -> Int
    char *date;         //Date of review                               -> Array of char
    char *text;         //Text of review                               -> Array of char
};

/* ---------------//--------------- [Private Functions] ---------------//--------------- */

//[Boolean function that says if a char is a number]
static int is_number(char c){
  return (c >= 48 && c <= 57);
}

//[Boolean function that says if a year is a leap year]
static int is_leap_year(int year){
  return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

//[Boolean function that says if a string is a float]
static int is_float(char* str){
    int comma = 0, i, b = 1;
    
    for (i = 0; str[i] != '\0' && b; i++){
      if (str[i] == '.' && (is_number(str[i + 1])) && comma == 0)
        comma++;
      else if (!(is_number(str[i])))
        b = 0;
    }
    return b;
}

//[Boolean function that says if a string is a int]
static int is_int(char* str){
  int b = 1;
  for (int i = 0; str[i]!='\0' && b; i++){
    if (!isdigit(str[i]))
       b = 0;
  }
  return b;
}

//[Boolean function that validates a day]
static int valid_day (int year, int month, int day){
  int b = 0;
  if (day >= 1){
    if (day <= 27)
        b = 1;
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
      if (day <= 31)
        b = 1;
    }
    
    else if (month == 4 || month == 6 || month == 9 || month == 11){
      if (day <= 30)
        b = 1;
    }
    
    else{
      if (is_leap_year(year)){
        if (day <= 29)
          b = 1;
      }
      else
          if (day <= 28)
            b = 1;
    }

  }
  return b;
}

//[Boolean function that validates a month]
static int valid_month (int month){
  return month>=1 && month<=12;
}

//[Boolean function that validates an hour]
static int valid_hour (int hour){
  return hour>=0 && hour<=23;
}

//[Boolean function that validates a minutes/seconds]
static int valid_minutes_or_seconds (int value){
  return value>=0 && value<=59;
}

//[Boolean function that validates a date]
static int valid_date (char* date){
  char year[5], month[3], day[3], hour[3], minute[3], second[3];
  int i, e, y,m,d,h,min,s,t,dp;
  y = m = d = h = min = s = t = dp = e = 0;
  int b = 1;

  for (i = 0; date[i] != '\0' && b; i++){
    switch (date[i]){
      case '-': 
        t++;
        break; 

      case ':':
        if (t == 2) dp++;
        else b = 0;
        break;

      case ' ':
        if (t == 2 && e < 1) e++;
        else b = 0;
        break;

      default:
        switch (t){
          case 0: 
            if (y < 4){
              year[y] = date[i];
              y++;
            }
            else b = 0;
            break;
          case 1: 
            if (m < 2){
              month[m] = date[i];
              m++;
            }
            else b = 0;
            break;
          case 2: 
            if (!e){
              if (d < 2){
                day[d] = date[i];
                d++;
              }
              else
                b = 0;
            }
            else{
              switch(dp){
                case 0:
                  if (h < 2){
                    hour[h] = date[i];
                    h++;
                  }
                  else
                    b = 0;
                  break;
                case 1: 
                  if (min < 2){
                    minute[min] = date[i];
                    min++;
                  }
                  else
                    b = 0;
                  break;
                case 2: 
                  if (s < 2){
                    second[s] = date[i];
                    s++;
                  }
                  else
                    b = 0;
                break;
              } 

            }
            break;
        }
        break;
    }
  }

  year[y] = month[m] = day[d] = hour[h] = minute[min] = second[s] = '\0';

  return (b && dp == 2 && is_int(year) && is_int (month) && is_int(day) && is_int (hour) && is_int (minute) && is_int(second) 
           && atoi(year)>=1983 && valid_month(atoi(month)) && valid_day(atoi(year),atoi(month),atoi(day)) 
           && valid_hour(atoi(hour)) && valid_minutes_or_seconds(atoi(minute)) && valid_minutes_or_seconds(atoi(second))); 
}

//[Valid review function]
static int valid_review (char* s){
    int i,rid = 0,bid = 0, uid = 0, r = 0, st = 0,u = 0,f=0,c=0,d=0, b = 1;
    char stars[5], useful[11], funny[11], cool[11], date[20];  
    for (i = 0; s[i] != '\0' && b; i++)
        if (s[i] == ';' && s[i+1] != ';')
          r++;
        else if (s[i]!= ';' && r == 0){
          if (rid < 22) rid++;
          else b = 0;
        }

        else if (s[i]!= ';' && r == 1){
          if (uid < 22) uid++;
          else b = 0;
        }

        else if (s[i]!= ';' && r == 2){
          if (bid < 22) bid++;
          else b = 0;
        }

        else if (s[i]!= ';' && r == 3){
          if (st < 4){
            stars[st] = s[i];
            st++;
          } 
          else if (!isdigit (s[i]))
            b = 0;
        }

        else if (s[i]!= ';' && r == 4){
          if (u < 10){
            useful[u] = s[i];
            u++;
          } 
          else b = 0;
        }

        else if (s[i]!= ';' && r == 5){
          if (f < 10){
            funny[f] = s[i];
            f++;
          } 
          else b = 0;
        }

        else if (s[i]!= ';' && r == 6){
          if (c < 10){
            cool[c] = s[i];
            c++;
          }
          else b = 0;
        }

        else if (s[i]!= ';' && r == 7){
          if (d < 19){
            date[d] = s[i];
            d++;
          } 
          else b = 0;
        }

      stars[st] = useful[u] = funny[f] = cool[c] = date[d] = '\0';

    return (b && r >= 8 && d == 19 && is_float(stars) && (atoi(stars) <= 5 && atoi(stars) >= 0) 
            && is_int(useful) && is_int(funny) && is_int(cool)
            && valid_date(date));
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

//[Initialization function of struct review]
REVIEW create_review(char *str){
  REVIEW r;
  if(valid_review(str)){
    r = malloc(sizeof(struct review));
    r->review_id   = strdup(strsep(&str, ";"));
    r->user_id     = strdup(strsep(&str, ";"));
    r->business_id = strdup(strsep(&str, ";"));
    r->stars       = atoi(strsep(&str, ";"));
    r->useful      = atoi(strsep(&str, ";"));
    r->funny       = atoi(strsep(&str, ";"));
    r->cool        = atoi(strsep(&str, ";"));
    r->date        = strdup(strsep(&str, ";"));
    r->text        = strdup(strsep(&str, "\n"));
  }
  else r = NULL;
  return r;
}

//[Destruction function of struct review]
void free_review(REVIEW r){
    if(r != NULL){
        free(r->review_id);
        free(r->user_id);
        free(r->business_id);
        free(r->date);
        free(r->text);
        free(r);
    }
}

/* [Getters functions] */

//[Get review id of a struct review]
char* get_review_id (REVIEW r) {
    char *review_id = strdup(r->review_id);
    return review_id;
}

//[Get user id of a struct review]
char* get_review_user_id (REVIEW r) {
    char *user_id = strdup(r->user_id);
    return user_id;
}

//[Get business id of a struct review]
char* get_review_business_id (REVIEW r) {
    char *business_id = strdup(r->business_id);
    return business_id;
}

//[Get stars of a struct review]
float get_review_stars (REVIEW r) {
    return r->stars;
}

//[Get Number of people who found the review funny of a struct review]
int get_review_funny (REVIEW r){
    return r->funny;
}

//[Get Number of people who found the review cool of a struct review]
int get_review_cool (REVIEW r){
    return r->cool;
}

//[Get Number of people who found the review useful of a struct review]
int get_review_useful (REVIEW r){
    return r->useful;
}

//[Get date of a struct review]
char* get_review_date (REVIEW r){
    char *date = strdup(r->date);
    return date;
}

//[Get text of a struct review]
char* get_review_text (REVIEW r){
    char *text = strdup(r->text);
    return text;
}
