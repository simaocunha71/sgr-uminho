/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/view/show.h"

/* ---------------//--------------- [Private Functions] ---------------//--------------- */

//[Print a separator]
static void separator (char* colour){
	print_string_coloured("---------------------------------------------------------------------\n",colour);
}

//[Ask a exit message]
static void show_ask_exit_message(){
  separator("red");
	print_string_coloured("Press ","yellow");
	print_string_coloured("Q","grey");
	print_string_coloured(" to quit |","yellow");
}

//[Ask a clean message]
static void show_ask_clean(){
  print_string_coloured(" Press ","yellow");
  print_string_coloured("C","grey");
  print_string_coloured(" to clean\n","yellow");
  separator("red");
}

//[Show university logo]
static void university_logo(){
  printf("\033[91m"); //cor
  printf("████████████████████████████████████████████████████████████████████████████\n");
  printf("██                        ▒██                                            ▒██\n");
  printf("██          ▒██           ▒██  ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀█                        ▒██\n");
  printf("██          ▒██           ▒██  ░▀▀▀▄▄ ▒█░▄▄ ▒█▄▄▀                        ▒██\n");
  printf("██  ▒██▄▄          ▄▄██   ▒██  ▒█▄▄▄█ ▒█▄▄█ ▒█░▒█                        ▒██\n");
  printf("██     ▀▀██▄    ▄██▀▀     ▒██                                            ▒██\n");
  printf("██        ▀██ ▒██▀        ▒██  ▒█░▒█ ▒█▀▄▀█ ▀█▀ ▒█▄░▒█ ▒█░▒█ ▒█▀▀▀█      ▒██\n");
  printf("██                        ▒██  ▒█░▒█ ▒█▒█▒█ ▒█░ ▒█▒█▒█ ▒█▀▀█ ▒█░░▒█      ▒██\n");
  printf("██    ▄███  ▒██  ▒███▄    ▒██  ░▀▄▄▀ ▒█░░▒█ ▄█▄ ▒█░░▀█ ▒█░▒█ ▒█▄▄▄█      ▒██\n");
  printf("██  ▒██▀    ▒██     ▀██   ▒██                                            ▒██\n");
  printf("██          ▒██           ▒██  LI3 Project 2021 - Group 15               ▒██\n");
  printf("██           ▀▀           ▒██  University of Minho MIEI                  ▒██\n");
  printf("██                        ▒██                                            ▒██\n");
  printf("████████████████████████████████████████████████████████████████████████████\n");
  printf("\n");
  printf("\033[0m");
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

//[Clean Screen]
void clear_screen(){
    printf("\e[1;1H\e[2J");
}

//[Clean a line]
void clear_line(){
  printf("\033[A\33[2KT\r");
}

//[Ask about page]
void show_ask_page(char mode){
  if(mode == 'Q')
    printf("[N] Next Page | [P] Previous Page | [S] Set Page | [B] Back | @: ");
  else
    printf("@Page: ");
}

//[Ask about path]
void show_ask_path(char mode){
  if(mode == 'D'){
    print_string_coloured("[D] Default Path ","red");
    print_string_coloured("| [A] Another Path\n","grey"); //talvez tirar o @
    separator("red");
  }
  else if(mode == 'A'){
    print_string_coloured("[D] Default Path | ","grey");
    print_string_coloured("[A] Another Path\n","red");
    separator("red");

  }
  else {
    print_string_coloured("Do you want to assume the default path or customize another one.\n","yellow");
    print_string_coloured("[D] Default Path | [A] Another Path | ","grey");
    print_string_coloured("@: ","red");
  }
}

//[Show help of interperter]
void show_help_guide (){
  printf("\e[1;33m[Query2]\033[0m: \x1b[92mLists the names and the total number of businesses started by a given letter. Don't worry, the search process is not case sensitive.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = businesses_started_by_letter(sgr, %%letter);\n");
  printf("          \033[91mExample:\033[0m x = businesses_started_by_letter(sgr, 'w');\n");
  printf("\e[1;33m[Query3]\033[0m: \x1b[92mGiven a business id, lists his all information: name, city, state, stars and total number of reviews.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = business_info(sgr, %%business_id);\n");
  printf("          \033[91mExample:\033[0m y = business_info(sgr,\"N3_Gs3DnX4k9SgpwJxdEfw\");\n");
  printf("\e[1;33m[Query4]\033[0m: \x1b[92mGiven an user id, lists all the businesses (names and business id's) which he wrote a review for.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = businesses_reviewed(sgr, %%user_id);\n");
  printf("          \033[91mExample:\033[0m z = businesses_reviewed(sgr, \"q_QQ5kBBwlCcbL1s4NVK3g\");\n");
  printf("\e[1;33m[Query5]\033[0m: \x1b[92mGiven a number of stars n and a city, lists all the businesses(names and business id's) with n or greater stars on that city.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = businesses_with_stars_and_city(sgr, %%stars, %%city);\n");
  printf("          \033[91mExample:\033[0m w = businesses_with_stars_and_city(sgr, 3, \"Portland\");\n");
  printf("\e[1;33m[Query6]\033[0m: \x1b[92mGiven an integer n, lists the top n businesses(according to average stars) in each city.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = top_businesses_by_city(sgr, %%top);\n");
  printf("          \033[91mExample:\033[0m k = top_businesses_by_city(sgr, 100);\n");
  printf("\e[1;33m[Query7]\033[0m: \x1b[92mLists all the users id's and total number of users that visited more than one state.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = international_users(sgr);\n");
  printf("          \033[91mExample:\033[0m k = international_users(sgr);\n");
  printf("\e[1;33m[Query8]\033[0m: \x1b[92mGiven an integer n and a category, lists the top n businesses (according to average stars) that belong to that category.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = top_businesses_with_category(sgr, %%stars, %%category);\n");
  printf("          \033[91mExample:\033[0m zz = top_businesses_with_category(sgr, 1, \"Nightlife\");\n");
  printf("\e[1;33m[Query9]\033[0m: \x1b[92mGiven a word, lists all the id's of the reviews in witch that word was used in the field text.\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = reviews_with_word(sgr, %%word);\n");
  printf("          \033[91mExample:\033[0m xyz = reviews_with_word(sgr, \"cook\");\n");
  printf("\e[1;33m[Show]\033[0m: \x1b[92mShows the variable between parenthesis\033[0m\n");
  printf("        \x1b[93mCommand syntax:\033[0m \x1b[90m@I:\033[0m show(%%var);\n");
  printf("        \033[91mExample:\033[0m a = show(x);\n");
  printf("\e[1;33m[toCSV]\033[0m: \x1b[92mConvert a TABLE into a .csv file, delimited with a char %%delim\033[0m\n");
  printf("        \x1b[93m Command syntax:\033[0m \x1b[90m@I:\033[0m toCSV(%%var, %%delim, %%filepath);\n");
  printf("         \033[91mExample:\033[0m toCSV(t,\';\',\"test\");\n");    
  printf("\e[1;33m[fromCSV]\033[0m: \x1b[92mGiven a .csv file, converts into a TABLE \033[0m\n");
  printf("        \x1b[93m   Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = fromCSV(%%filepath,%%delim);\n");
  printf("           \033[91mExample:\033[0m x = fromCSV(\"test\",\';\');\n");  
  printf("\e[1;33m[filter]\033[0m: \x1b[92mGiven a column, a comparison value and a comparison operator {LT (lesser than), EQ (equal) or GT (greater than)}, filters data from a TABLE\033[0m\n");
  printf("        \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = filter(%%var, %%column_name, %%value, %%oper);\n");
  printf("          \033[91mExample:\033[0m tbl = filter(t,\"business_id\",\"hello\",LT);\n"); 
  printf("\e[1;33m[proj]\033[0m: \x1b[92mGiven a TABLE and a title, gets the column that has that word as a title\033[0m\n");
  printf("        \x1b[93mCommand syntax:\033[0m \x1b[90m@I:\033[0m %%var = proj(%%var, %%cols);\n"); 
  printf("        \033[91mExample:\033[0m t = proj(t,\"business_id\");\n"); 
  printf("\e[1;33m[index]\033[0m: \x1b[92mReturn the element of a certain index from a given TABLE\033[0m\n");
  printf("       \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m %%var = %%var[%%d][%%d];\n"); 
  printf("         \033[91mExample:\033[0m t = v[0][1];\n"); 
  printf("\e[1;33m[quit]\033[0m: \x1b[92mTerminates program\033[0m\n");
  printf("      \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m quit;\n");
  printf("        \033[91mExample:\033[0m quit;\n"); 
  printf("\e[1;33m[clean]\033[0m: \x1b[92mClear screen\033[0m\n");
  printf("       \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m clean;\n");
  printf("         \033[91mExample:\033[0m clean;\n");
  printf("\e[1;33m[back]\033[0m: \x1b[92mGoes back to the main manu\033[0m\n");
  printf("      \x1b[93m  Command syntax:\033[0m \x1b[90m@I:\033[0m back;\n");
  printf("        \033[91mExample:\033[0m back;\n");
}

//[Show exit message]
void show_exit_message(){
	separator("grey");
	printf("\x1b[93m");
printf("          ▀▀█▀▀ █░░█ █▀▀█ ▀▀█▀▀ █ █▀▀ 　 █▀▀█ █░░ █░░\n");
printf("          ░▒█░░ █▀▀█ █▄▄█ ░░█░░ ░ ▀▀█ 　 █▄▄█ █░░ █░░\n");
printf("          ░▒█░░ ▀░░▀ ▀░░▀ ░░▀░░ ░ ▀▀▀ 　 ▀░░▀ ▀▀▀ ▀▀▀\n");
printf("                                                     \n");
printf("          　 　 　 ▒█▀▀▀ █▀▀█ █░░ █░█ █▀▀ █           \n");
printf("          　 　 　 ▒█▀▀▀ █░░█ █░░ █▀▄ ▀▀█ ▀           \n");
printf("          　 　 　 ▒█░░░ ▀▀▀▀ ▀▀▀ ▀░▀ ▀▀▀ ▄           \n");
printf("\033[0m");
separator("grey");
}

//[Show interperter logo]
void interpreter_logo(){
    printf("\033[91m"); //cor
    printf("▀█▀ █▀▀▄ ▀▀█▀▀ █▀▀ █▀▀█ █▀▀█ █▀▀█ █▀▀ ▀▀█▀▀ █▀▀ █▀▀█ \n"); 
    printf("▒█░ █░░█ ░░█░░ █▀▀ █▄▄▀ █░░█ █▄▄▀ █▀▀ ░░█░░ █▀▀ █▄▄▀ \n"); 
    printf("▄█▄ ▀░░▀ ░░▀░░ ▀▀▀ ▀░▀▀ █▀▀▀ ▀░▀▀ ▀▀▀ ░░▀░░ ▀▀▀ ▀░▀▀ \n");
    printf("\n"); 
    printf("\033[0m");
}

//[Show business' catalogue logo]
void business_catalogue_logo(){
    printf("\033[91m"); //cor
    printf("▒█▀▀█ █░░█ █▀▀ ░▀░ █▀▀▄ █▀▀ █▀▀ █▀▀ █    █▀▀ █▀▀█ ▀▀█▀▀ █▀▀█ █░░ █▀▀█ █▀▀▀ █░░█ █▀▀\n");
    printf("▒█▀▀▄ █░░█ ▀▀█ ▀█▀ █░░█ █▀▀ ▀▀█ ▀▀█ ░    █░░ █▄▄█ ░░█░░ █▄▄█ █░░ █░░█ █░▀█ █░░█ █▀▀\n");
    printf("▒█▄▄█ ░▀▀▀ ▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀ ░    ▀▀▀ ▀░░▀ ░░▀░░ ▀░░▀ ▀▀▀ ▀▀▀▀ ▀▀▀▀ ░▀▀▀ ▀▀▀\n"); 
    printf("\n"); 
    printf("\033[0m");
}

//[Show review' catalogue logo]
void review_catalogue_logo(){
    printf("\033[91m"); //cor
    printf("▒█▀▀█ █▀▀ ▀█░█▀ ░▀░ █▀▀ █░░░█ █▀▀ █    █▀▀ █▀▀█ ▀▀█▀▀ █▀▀█ █░░ █▀▀█ █▀▀▀ █░░█ █▀▀\n");
    printf("▒█▄▄▀ █▀▀ ░█▄█░ ▀█▀ █▀▀ █▄█▄█ ▀▀█ ░    █░░ █▄▄█ ░░█░░ █▄▄█ █░░ █░░█ █░▀█ █░░█ █▀▀\n");
    printf("▒█░▒█ ▀▀▀ ░░▀░░ ▀▀▀ ▀▀▀ ░▀░▀░ ▀▀▀ ░    ▀▀▀ ▀░░▀ ░░▀░░ ▀░░▀ ▀▀▀ ▀▀▀▀ ▀▀▀▀ ░▀▀▀ ▀▀▀\n");
    printf("\n"); 
    printf("\033[0m");
}

//[Show user's catalogue logo]
void user_catalogue_logo(){
	printf("\033[91m"); //cor
    printf("▒█░▒█ █▀▀ █▀▀ █▀▀█ █ █▀▀    █▀▀ █▀▀█ ▀▀█▀▀ █▀▀█ █░░ █▀▀█ █▀▀▀ █░░█ █▀▀\n"); 
    printf("▒█░▒█ ▀▀█ █▀▀ █▄▄▀ ░ ▀▀█    █░░ █▄▄█ ░░█░░ █▄▄█ █░░ █░░█ █░▀█ █░░█ █▀▀\n"); 
    printf("░▀▄▄▀ ▀▀▀ ▀▀▀ ▀░▀▀ ░ ▀▀▀    ▀▀▀ ▀░░▀ ░░▀░░ ▀░░▀ ▀▀▀ ▀▀▀▀ ▀▀▀▀ ░▀▀▀ ▀▀▀\n");
    printf("\n"); 
	printf("\033[0m");
}

//[Show menu]
void show_menu(){
	university_logo(),
	print_string_coloured("Please select an option to continue\n","yellow");
  separator("red");
  print_string_coloured("[1] ", "yellow");
	print_string_coloured("Loading users, reviews and businesses files\n","white");
  print_string_coloured("[2] ", "yellow");
	print_string_coloured("Showing users catalogue\n","white");
  print_string_coloured("[3] ", "yellow");
	print_string_coloured("Showing reviews catalogue\n", "white");
  print_string_coloured("[4] ", "yellow");
	print_string_coloured("Showing businesses catalogue\n", "white");
  print_string_coloured("[5] ", "yellow");
	print_string_coloured("Going to the command interpreter\n","white");
	show_ask_exit_message();
  show_ask_clean();
}

//[Printf with colour]
void print_string_coloured (char* word_to_print, char* colour){
  if (strcmp(colour,"grey") == 0){
    printf("\x1b[90m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }

  else if (strcmp(colour,"red") == 0){
    printf("\x1b[91m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }

  else if (strcmp(colour,"green") == 0){
    printf("\x1b[92m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }

  else if (strcmp(colour,"yellow") == 0){
    printf("\x1b[93m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }

  else if (strcmp(colour,"blue") == 0){
    printf("\x1b[94m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }

  else if (strcmp(colour,"pink") == 0){
    printf("\x1b[95m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }
  else if (strcmp(colour,"back_red")==0){
    printf("\e[41m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }
    else if (strcmp(colour,"white")==0){
    printf("\e[0;37m");
    printf("%s", word_to_print);
    printf("\033[0m");
  }
  else
    printf("Colour not available\n");
}
