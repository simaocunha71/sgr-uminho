/* ---------------//--------------- [Includes] ---------------//--------------- */
#include "../../includes/controller/interpreter.h"

/* ---------------//--------------- [Defines] ---------------//--------------- */
typedef GHashTable *VARIABLES;

typedef enum op{
  LT = -1,
  EQ = 0,
  GT = 1,
}OPERATOR;

/* ---------------//--------------- [Private Functions] ---------------//--------------- */
//[Free key]
static void free_key (gpointer data) {
  free (data);
}

//[Free table of a hash]
static void destroy_table (gpointer data) {
    TABLE t = (TABLE) data;
    free_table(t);
}

//[Function that says if a string is a operator]
static int is_operator (char *str){
  return ((strcmp(str,"LT") == 0)
       || (strcmp(str,"EQ") == 0)
       || (strcmp(str,"GT") == 0));
}

//[Function that transform a string in a operator]
static int str_to_operator (char *str){
  int r = EQ;
  if(strcmp(str,"LT") == 0) r = LT;
  else if (strcmp(str,"GT") == 0) r = GT;
  return r;
}

//[Function that simplify to operator]
static int simplify_operator (int i){
  int r = EQ;
  if (i < 0) r = LT;
  else if (i > 0) r = GT;
  return r;
}

//[Function that says if it is a number]
static int is_number(char c){
  return (c >= 48 && c <= 57);
}

//[Function that says if it is a int]
static int is_int(char* str){
  int b = 1;
  for (int i = 0; str[i]!='\0' && str[i]!='\n' && b; i++){
    if (!is_number(str[i]))
       b = 0;
  }
  return b;
}

//[Function that says if it is a float]
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

//[Function that transform a parameter in a char]
static char parms_to_char (char* parm){
  char c;
  if(parm[1] == '\\') 
    c = parm[2];
  else c = parm[1];
  return c;
}

//[Function that says if a string finish with the char c]
static int finish_with_char(char* str, char c){
  int i, b = 0;
  for (i = 0; str[i]!='\0'; i++);
  if(str[i-1] == c) b = 1;
  str[i-1] = '\0';
  return b;
}

//[Function that counts the parameters]
static int count_parameters(char* str){
  int count = 0, i;
  for(i = 0; str[i]!='\0'; i++){
    if(i > 0 && str[i] == ',' && (str[i-1] != '\'' || str[i+1] != '\'')) count++;
  }
  count++;
  return count++;
}

//[Function that says if it is a letter or '_']
static int letter_of_var(char c){
    return (isupper(c) || islower(c) || c == '_');
}

//[Function that says if it is a variable]
static int is_var(char* str){
  int N = strlen(str);
  int i, b = 1;
  for(i = 0; i < N; i++){
    if(!(letter_of_var(str[i]))) {
      b = 0;
    }
  }
  return b;
}

//[Function that says if it is a special char]
static int is_special_char (char c){
  return(!(isdigit(c) || isalpha(c) || (c == ' ')));
}

//[Function that says if it is a string]
static int is_string(char* str){
  return ((str[0] == '"') && finish_with_char(str,'"'));
}

//[Function that says if it is a char]
static int is_char(char* str){
  return ((str[0] == '\'') 
      && (((str[2] == '\'') && (str[3] == '\0')) || ((str[3] == '\'') && (str[4] == '\0') && (str[1] == '\\'))));
}

//[Function that says if it is a existent func]
static int valid_func(char* str){
  return ((strcmp(str,"businesses_started_by_letter")   == 0) 
       || (strcmp(str,"business_info")                  == 0)
       || (strcmp(str,"businesses_reviewed")            == 0)
       || (strcmp(str,"businesses_with_stars_and_city") == 0)
       || (strcmp(str,"top_businesses_by_city")         == 0)
       || (strcmp(str,"international_users")            == 0)
       || (strcmp(str,"top_businesses_with_category")   == 0)
       || (strcmp(str,"reviews_with_word")              == 0)
       || (strcmp(str,"fromCSV")                        == 0)
       || (strcmp(str,"proj")                           == 0)
       || (strcmp(str,"filter")                         == 0)
       || (strcmp(str,"friends_of_user")                == 0));
}

//[Function that says if it is a func]
static int is_func (char *line, char**cmds){
  return ((sscanf(line, "%[^(](%[^)]%s", cmds[0],cmds[1],cmds[2]) == 3)
       && (valid_func(cmds[0]))
       && (strcmp(cmds[2],")") == 0));
}

//[Function that says if it is the index command]
static int is_index (char *line, char**cmds, int* a, int* b){
  return ((sscanf(line, "%[^[][%d][%d%s", cmds[0],a,b,cmds[1]) == 4)
       && (is_var(cmds[0]))
       && (strcmp(cmds[1],"]") == 0));
}

//[Function that says if it is an assign command]
static int is_assign(char *line, char**cmds){
  return ((sscanf(line, "%[^ ] = %[^\n]", cmds[0],cmds[1]) == 2)
       && (is_var(cmds[0])));
}

//[Function that says if it is the show command]
static int is_show(char *line, char**cmds){
  return ((sscanf(line, "%[^(](%[^)]%s", cmds[0],cmds[1],cmds[2]) == 3)
       && (strcmp(cmds[0],"show") == 0)
       && (is_var(cmds[1])
       && (strcmp(cmds[2],")") == 0)));
}

//[Function that says if it is the toCSV command]
static int is_toCSV(char *line, char**cmds){
  return ((sscanf(line, "%[^(](%[^)]%s", cmds[0],cmds[1],cmds[2]) == 3)
       && (strcmp(cmds[0],"toCSV") == 0)
       && (strcmp(cmds[2],")") == 0));
}

//[Function that says if it is the proj command]
static int is_proj(char *line, char**cmds){
  return ((sscanf(line, "%[^(](%[^)]%s", cmds[0],cmds[1],cmds[2]) == 3)
       && (strcmp(cmds[0],"proj") == 0)
       && (strcmp(cmds[2],")") == 0));
}

//[Function that says if it is the filter command]
static int is_filter(char *line, char**cmds){
  return ((sscanf(line, "%[^(](%[^)]%s", cmds[0],cmds[1],cmds[2]) == 3)
       && (strcmp(cmds[0],"filter") == 0)
       && (strcmp(cmds[2],")") == 0));
}

//[Function that says if it is the help command]
static int is_help(char *line){
  return (strcmp(line,"help") == 0);
}

//[Function that says if it is the clear command]
static int is_clear(char *line){
  return (strcmp(line,"clear") == 0);
}

//[Function that says if it is the quit command]
static int is_quit(char *line){
  return (strcmp(line,"quit") == 0);
}

//[Function that says if it is the back command]
static int is_back(char *line){
  return (strcmp(line,"back") == 0);
}

//[Function that separates the parameters]
static void split_parameters(char *line, char**parms, int np){
  int i = 0, p, k;
  for(p = 0; p < np; p++){
    while(line[i] == ' '){
      i++;
    }
    strcpy(parms[p],&line[i]);
    if(parms[p][0] == '"'){
      i++;
      for(k = 1; parms[p][k] != '"';k++, i++);
      while((parms[p][k]) != ',' && parms[p][k] != '\0') {
        k++;
        i++;
      }
    }
    else if(parms[p][0] == '\'') {
      i++;
      for(k = 1; parms[p][k] != '\''; k++, i++);
      while((parms[p][k]) != ',' && parms[p][k] != '\0') {
        k++;
        i++;
      }
    }
    else {
      for(k = 0; parms[p][k] != ',' && parms[p][k] != '\0'; k++, i++);
    }
    parms[p][k] = '\0';
    i++;
  }
}

//[function that scan command of terminal (stdin)]
static char* scan_command(ssize_t *ptr_buffer_size){
    char *buffer = NULL;
    size_t len = 0;
    if((*ptr_buffer_size = getline(&buffer,&len,stdin)) == -1)
      perror("getline");
    return buffer;
}

//[add variable TABLE in hash table]
static int add_variable(VARIABLES variables, TABLE t, char* var_name){
  return (g_hash_table_insert(variables, (gpointer)var_name, (gpointer) t));
}

//[index function]
static TABLE index_table(TABLE t, int l, int c){
  TABLE t_index;
  int cs, ls;
  cs = get_table_columns(t);
  ls = get_table_lines(t);
  if (c+1 > cs || l+1 > ls || c < 0 || l < 0){
    printf("This index is not valid.\n");
    t_index = NULL;
  }
  else {
    t_index = init_table(1);
    char* info = get_table_info(t,l*cs+c);
    char* title = get_table_titles(t,c);
    set_table_lines(t_index,1);
    set_table_columns(t_index,1);
    add_title_of_column(t_index,title,0);
    add_info_string(t_index,info);
    set_default_pages(t_index);
  }
  return t_index;
}

//[Interperter of show command]
static void interpreter_show(TABLE t, char mode){
  int number_of_pages = get_table_number_of_pages(t);
  int back = 0;
  int page = 1;
  int spage = 1, size = 2;
  while(!back){
    if(size == 2){
      clear_screen();
      if(mode == 'b') business_catalogue_logo();
      else if(mode == 'r') review_catalogue_logo();
      else if(mode == 'u') user_catalogue_logo();
      print_page_of_table(t,page);
    }
    else clear_line();
    show_ask_page('Q');
    char* buffer = NULL;
    size_t len = 0;
    if((size = getline(&buffer, &len, stdin)) == -1)
      perror("getline");
    if(size == 2){
      switch (buffer[0]){
        case 'N':
          if(page < number_of_pages) page++;
          else page = 1 ;
          break;
        case 'P':
          if (page > 1) page--;
          else page = number_of_pages;
          break;
        case 'S':
          show_ask_page('P');
          while(getline(&buffer, &len, stdin) != -1 && (!is_int(buffer) || (spage = atoi(buffer)) < 1 || spage > number_of_pages)){
            clear_line();
            show_ask_page('P');
          }
          page = spage;
          break;
        case 'B':
          back = 1;
          break;
      }
    }
  }
  clear_screen();
  interpreter_logo();
}

//[Function that valids title]
static int valid_title(TABLE t, char* title){
  int found = -1, i;
  int cs = get_table_columns(t);
  for(i = 0; i < cs && found == -1; i++){
    char *title_t = get_table_titles(t, i);
    if(strcmp(title_t,title) == 0) {
      found = i;
    }
    free(title_t);
  }
  return found;
}

//[proj function]
static TABLE proj(TABLE x, char* cols){
  TABLE t;
  int nt, i;
  nt = count_parameters(cols);
  printf("%d\n",nt);
  char **titles = malloc(sizeof(char*) * nt);
  for(i = 0; i < nt; i++){
    titles[i] = (char *) malloc (100 * sizeof (char));
    titles[i][0] = '\0';
  }
  int i_titles[nt];
  split_parameters(cols,titles,nt);
  int valid_titles = 1;
  for(i = 0; i < nt && valid_titles; i++){
    int f;
    if((f = valid_title(x, titles[i])) == -1) valid_titles = 0;
    else i_titles[i] = f;
  }
  if(valid_titles){
    int size = get_table_size(x);
    t = init_table(size);
    set_table_columns(t,nt);
    for(i = 0; i < nt; i++){
      add_title_of_column(t,titles[i],i);
    }
    int ls = get_table_lines(x);
    int cs = get_table_columns(x);
    for(i = 0; i < ls; i++){
      inc_table_lines(t);
      int c;
      for(c = 0; c < nt; c++){
        char* info = get_table_info(x, i_titles[c]+i*cs);
        add_info_string(t,info);
        free(info);
      }
      set_default_pages(t);
    }
  }
  else
    t = NULL;
  for(i = 0; i < nt; i++){
    free(titles[i]);
  }
  free(titles);
  return t;
}

//[filter function]
static TABLE filter (TABLE x, char* title, char* value, OPERATOR op){
  TABLE t;
  int ind_title = valid_title(x, title);
  if (ind_title != -1){
    int l, c;
    int size = get_table_size(x);
    t = init_table(size);
    int ls = get_table_lines(x);
    int cs = get_table_columns(x);
    set_table_columns(t,cs);
    for(c = 0; c < cs; c++){
      char* title_copy = get_table_titles(x,c);
      add_title_of_column(t,title_copy,c);
      free(title_copy);
    }
    for(l = 0; l < ls; l++){
      char* info = get_table_info(x, ind_title+l*cs);
      int cmp = strcasecmp(info,value);
      if(simplify_operator(cmp) == op) { //se calhar ver o case sensetive
        inc_table_lines(t);
        for(c = 0; c < cs; c++){
          char* info_copy = get_table_info(x, c+l*cs);
          add_info_string(t,info_copy);
          free(info_copy);
        }
      }
      free(info);
      char *title_lines = get_table_title_line(x);
      set_title_lines(t,title_lines);
      set_default_pages(t);
    }    
  }
  else
    t = NULL;
  return t;
}

//[toCSV function]
static void toCSV(TABLE t, char delim, char *filename){
	char *nameUpdated = malloc((strlen(filename) + 5) * sizeof(char));
	strcpy(nameUpdated, filename);
	strcat(nameUpdated, ".csv");;

	FILE *f;
	f = fopen(nameUpdated, "wb+");

	if (f == NULL)
		perror("Ficheiro vazio\n");

	int colunas = get_table_columns(t);
	int linhas = get_table_lines(t);
  char* title, *info;

	int k = 0;
	for (; k < colunas - 1; k++){
    title = get_table_titles(t, k);
		fprintf(f, "%s%c", title, delim);
    free(title);
  }
  title = get_table_titles(t,k);
	fprintf(f, "%s\n", title);
  free(title);

	int i, j;
	for (i = 0; i < linhas; i++)
	{
		for (j = 0; j < colunas - 1; j++){
      info = get_table_info(t, colunas * i + j);
			fprintf(f, "%s%c", info, delim);
      free(info);
    }
    info = get_table_info(t, colunas * i + j);
		fprintf(f, "%s\n", info);
    free(info);
	}
	fclose(f);
	printf("File %s was saved\n",nameUpdated);
	free(nameUpdated);
}

//[Delimits titles by delim]
static void split_titles(TABLE t, char *str, int col, char delim){
	char *aux;
	int j;
	char aux_delim[1];
	aux_delim[0] = delim;
	for (j = 0; j < col - 1; j++){
		aux = strdup(strsep(&str, aux_delim));
		add_title_of_column(t, aux, j);
		free(aux);
	}
	aux = strdup(strsep(&str, "\n"));
	add_title_of_column(t, aux, j);
  free(aux);
}

//[Delimits info by delim]
static void split_info(TABLE t, char *str, int col, char delim){
	int k;
	char *aux;
	char aux_delim[2];
	aux_delim[0] = delim;
  aux_delim[1] = '\0';
	for (k = 0; k < col - 1; k++){
		aux = strdup(strsep(&str, aux_delim));
		add_info_string(t, aux);
		free(aux);
	}
	aux = strdup(strsep(&str, "\n"));
	add_info_string(t, aux);
	free(aux);
}

//[fromCSV function]
static TABLE fromCSV(char *filename, char delim){
	FILE *f;
  TABLE t;
  f = fopen(filename, "rb+");
	if (f != NULL){
    t = init_table(0);

    int number_of_columns = 0;
    char *buffer = NULL;
    size_t len = 0;
    if (getline(&buffer, &len, f) != -1){
      for (int i = 0; buffer[i] != '\n'; i++){
        if (buffer[i] == delim)
          number_of_columns++;
      }
      number_of_columns++;
      set_table_columns(t, number_of_columns);
    }

    split_titles(t, buffer, number_of_columns, delim);

    while (getline(&buffer, &len, f) != -1){
      inc_table_lines(t);
      split_info(t, buffer, number_of_columns, delim);
    }
    set_default_pages(t);
    free(buffer);
    fclose(f);
  }
  else{
    t = NULL;
    perror("Ficheiro .csv vazio\n");
  }
	return t;
}

//[Execute command function]
static int execute_cmd (char* line, VARIABLES variables, SGR sgr) {
  int i;
  char **cmds = malloc(sizeof(char*) * 5);
  for(i = 0; i < 5; i++){
    cmds[i] = (char *) malloc (100 * sizeof (char));
    cmds[i][0] = '\0';
  }
  char **parms = malloc(sizeof(char*) * 5);
  for(i = 0; i < 5; i++){
    parms[i] = (char *) malloc (100 * sizeof (char));
    parms[i][0] = '\0';
  }
  int quit = 0, np = 0;
  printf("Executing %s\n",line);
  if (is_quit(line))
    quit = 1;
  else if (is_back(line))
    quit = 2;
  else if (is_help(line)){
    clear_line();
    show_help_guide();
  }
  else if (is_clear(line)){
    clear_screen();
    interpreter_logo();
  }
  else if (is_show(line, cmds)) {   
    TABLE t = g_hash_table_lookup(variables, (gconstpointer)cmds[1]);
    if(t != NULL){
      interpreter_show(t,'i');
    }
    else
      printf("Variable not found\n");
  }
  else if (is_toCSV(line,cmds)){
    np = count_parameters(cmds[1]);
    if (np == 3){
      split_parameters(cmds[1], parms, np);
      if(is_var(parms[0]) && is_char(parms[1]) && is_string(parms[2])) {
        TABLE t = g_hash_table_lookup(variables, (gconstpointer)parms[0]);
        if (t != NULL){
          char delim = parms_to_char(parms[1]);
          if (is_special_char(delim)){
            char *filename = malloc(sizeof(char) * strlen(parms[2]));
            strcpy(filename, &parms[2][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
            toCSV(t, delim, filename);
            free(filename);
          }
          else printf("Delimiter isn't valid!\n");
        }
        else
          printf("Variable TABLE not assigned\n");
      }
    }
  }
  else if (is_assign(line, cmds)) {
    int a = 0; int b = 0;
    char* var_name = strdup(cmds[0]);
    line = strdup(cmds[1]);
    if (is_index(line, cmds, &a, &b)) {
      TABLE t = g_hash_table_lookup(variables, (gconstpointer)cmds[0]);
      if(t != NULL){
        TABLE t_index = index_table(t,a,b);
        if(!(add_variable(variables,t_index,var_name)))
          printf("Variable replaced.\n");
      }
      else
        printf("Variable not found\n");
    }
    else if (is_proj(line,cmds)){
      np = count_parameters(cmds[1]);
      if (np == 2){
        split_parameters(cmds[1], parms, np);
        if(is_var(parms[0]) && is_string(parms[1])) {
          TABLE t = g_hash_table_lookup(variables, (gconstpointer)parms[0]);
          if (t != NULL){
            char *titles = malloc(sizeof(char) * strlen(parms[1]));
            strcpy(titles, &parms[1][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
            TABLE x = proj(t,titles);
            if(x != NULL){
              if(!(add_variable(variables,x,var_name)))
                printf("Variable replaced.\n");
              else{
                printf("feito -> %s\n",var_name);
              }
              free(titles);
            }
            else
              printf("Invalid column name\n");
          }
          else
            printf("Variable TABLE not assigned\n");
        }
      }
    }
    else if (is_filter(line,cmds)){
      np = count_parameters(cmds[1]);
      if (np == 4){
        split_parameters(cmds[1], parms, np);
        if(is_var(parms[0]) && is_string(parms[1]) && is_string(parms[2]) && is_operator(parms[3])) {
          TABLE t = g_hash_table_lookup(variables, (gconstpointer)parms[0]);
          if (t != NULL){
            char *title = malloc(sizeof(char) * strlen(parms[1]));
            char *value = malloc(sizeof(char) * strlen(parms[2]));
            int op = str_to_operator(parms[3]);
            strcpy(title, &parms[1][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
            strcpy(value, &parms[2][1]);
            TABLE x = filter(t,title,value,op);
            if(x != NULL){
              if(!(add_variable(variables,x,var_name)))
                printf("Variable replaced.\n");
              else{
                printf("feito -> %s\n",var_name);
              }
              free(title);
              free(value);
            }
            else
              printf("Invalid column name\n");
          }
          else
            printf("Variable TABLE %s not assigned\n",parms[0]);
        }
      }
    }
    else if (is_func(line, cmds)){
      np = count_parameters(cmds[1]);
      split_parameters(cmds[1],parms,np);
      if(strcmp(cmds[0],"businesses_started_by_letter") == 0 && np == 2){
        if(strcmp(parms[0],"sgr") == 0 && is_char(parms[1])) {
          char letter = parms_to_char(parms[1]);
          TABLE t = businesses_started_by_letter(sgr,letter);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");  
        }
      }
      else if(strcmp(cmds[0],"business_info") == 0 && np == 2) {
        if(strcmp(parms[0],"sgr") == 0 && is_string(parms[1])){
          char* id = malloc(sizeof(char)*strlen(parms[1]));
          strcpy(id,&parms[1][1]);
          TABLE t = business_info(sgr,id);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
          free(id);
        }
      }
      else if(strcmp(cmds[0],"businesses_reviewed") == 0 && np == 2){
        if(strcmp(parms[0],"sgr") == 0 && is_string(parms[1])){
          char* id = malloc(sizeof(char)*strlen(parms[1]));
          strcpy(id,&parms[1][1]);
          TABLE t = businesses_reviewed(sgr,id);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
          free(id);
        }        
      }
      else if(strcmp(cmds[0],"businesses_with_stars_and_city") == 0 && np == 3){
        if(strcmp(parms[0],"sgr") == 0 && is_float(parms[1]) && is_string(parms[2])){
          char* city = malloc(sizeof(char)*strlen(parms[2]));
          float stars = atof(parms[1]);
          strcpy(city,&parms[2][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
          TABLE t = businesses_with_stars_and_city(sgr,stars,city);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
          free(city);
        }
      }
      else if(strcmp(cmds[0],"top_businesses_by_city") == 0 && np == 2){
        if(strcmp(parms[0],"sgr") == 0 && is_int(parms[1])) {
          int top = atoi(parms[1]);
          TABLE t = top_businesses_by_city(sgr,top);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
        }
      }
      else if(strcmp(cmds[0],"international_users") == 0 && np == 1){
        if(strcmp(parms[0],"sgr") == 0) {
          TABLE t = international_users(sgr);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
        }
      }
      else if(strcmp(cmds[0],"top_businesses_with_category") == 0 && np == 3){
        if(strcmp(parms[0],"sgr") == 0 && is_int(parms[1]) && is_string(parms[2])){
          char* category = malloc(sizeof(char)*strlen(parms[2]));
          int top = atoi(parms[1]);
          strcpy(category,&parms[2][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
          TABLE t = top_businesses_with_category(sgr,top,category);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
          free(category);
        }
      }
      else if(strcmp(cmds[0],"reviews_with_word") == 0 && np == 2){
        if(strcmp(parms[0],"sgr") == 0 && is_string(parms[1])){
          char* word = malloc(sizeof(char)*strlen(parms[1]));
          strcpy(word,&parms[1][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
          TABLE t = reviews_with_word(sgr,word);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
          free(word);
        }
      }
      else if(strcmp(cmds[0],"fromCSV") == 0 && np == 2){
        if(is_string(parms[0])  && is_char(parms[1])){

          char delim = parms_to_char(parms[1]);
          if (is_special_char(delim)){
            char *filename = malloc(sizeof(char) * strlen(parms[0]));
            strcpy(filename, &parms[0][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
            TABLE t = fromCSV(filename, delim);
            if (!(add_variable(variables, t, var_name)))
              printf("Variable replaced.\n");
            free(filename);
          }
          else
            printf("Delimiter isn't valid!\n");
        }
      }
      else if(strcmp(cmds[0],"friends_of_user") == 0 && np == 2){
        if(strcmp(parms[0],"sgr") == 0 && is_string(parms[1])){
          char* user_id = malloc(sizeof(char) * strlen(parms[1]));
          strcpy(user_id, &parms[1][1]); //retira o " inicial da string||a funcao is_string já retira o " final, caso seja.
          TABLE t = friends_of_user(sgr,user_id);
          if(!(add_variable(variables,t,var_name)))
            printf("Variable replaced.\n");
          free(user_id);
        }
      }
      else {
        printf("Function not found.\n");
      }
      free(line);
    }
    else
      printf("Assign error\n");
  }
  else
    printf("Invalid command\n");
  
  for(i = 0; i < 5; i++){
    free(parms[i]);
  }
  free(parms);
  for(i = 0; i < 5; i++){
    free(cmds[i]);
  }
  free(cmds);
  return quit;
}

//[Interpreter Function]
static int interpreter(SGR sgr, VARIABLES variables){
  int quit = 0;
  ssize_t buf_size = 0;
  interpreter_logo();
  while(quit == 0){
    print_string_coloured("@I: ","grey");
    char *cmds = scan_command(&buf_size);
    char *buffer = malloc(sizeof(char) * (buf_size+1));
    int j, i;
    for(i = 0; cmds[i] != '\0' && quit == 0; i++){
      while(cmds[i] == ' ' || cmds[i] == ';')
        i++;
      strcpy(buffer, &cmds[i]);
      for (j = 1; (buffer[j] != ';' || (buffer[j-1] == '\'' && buffer[j+1] == '\'') ) && buffer[j] != '\0'; j++, i++);
      if(buffer[j] == ';'){
        buffer[j] = '\0';
        quit = execute_cmd(buffer, variables, sgr);
      }
    }
    free(buffer);
    free(cmds);
  }
  return quit;
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

//[Principal Function]
void menu(){
  int x, quit = 0, i;
  char defpath_users[27] = "input_files/users_full.csv";
  char defpath_businesses[30] = "input_files/business_full.csv";
  char defpath_reviews [27] = "input_files/reviews_1M.csv";
  SGR sgr = NULL;
  VARIABLES variables = g_hash_table_new_full(g_str_hash, g_str_equal,free_key,destroy_table);
  clear_screen();
  show_menu();
  ssize_t size;
  TABLE t_b = NULL, t_r = NULL, t_u = NULL;
  while(!quit){
    print_string_coloured("@M: ","red");
    char* buffer = scan_command(&size);
    clear_line();
    if(size == 2){
      switch (buffer[0]){
        case '1':
          x = 0;
          while(!x){
            show_ask_path('Q');
            char* buffer2 = scan_command(&size);
            clear_line();
            clear_line();
            if(size == 2){
              switch (buffer2[0]){
                case 'D':
                  show_ask_path('D');
                  x = 1;
                  if(sgr != NULL){ 
                    free_sgr(sgr);
                    if(t_u != NULL) free_table(t_u);
                    if(t_b != NULL) free_table(t_b);
                    if(t_r != NULL) free_table(t_r);
                  }
                  sgr = load_sgr(defpath_users, defpath_businesses, defpath_reviews);
                  break;
                case 'A':
                  show_ask_path('A');
                  x = 1;
                  print_string_coloured("@Business file path: ","yellow");
                  char *path_businesses = scan_command(&size);
                  print_string_coloured("Setted new businesses file path -> ","grey");
                  print_string_coloured(path_businesses,"yellow");
                  path_businesses[size-1] = '\0'; //retira o \n.
                  print_string_coloured("@Reviews file path: ","yellow");
                  char *path_reviews = scan_command(&size);
                  print_string_coloured("Setted new reviews file path -> ","grey");
                  print_string_coloured(path_reviews,"yellow");
                  path_reviews[size-1] = '\0'; //retira o \n.
                  print_string_coloured("@Users file path: ","yellow");
                  char *path_users = scan_command(&size);
                  print_string_coloured("Setted new users file path -> ","grey");
                  print_string_coloured(path_users,"yellow");
                  printf("\n");
                  path_users[size-1] = '\0'; //retira o \n.
                  if(sgr != NULL){ 
                    free_sgr(sgr);
                    if(t_u != NULL) free_table(t_u);
                    if(t_b != NULL) free_table(t_b);
                    if(t_r != NULL) free_table(t_r);
                  }
                  sgr = load_sgr(path_users, path_businesses, path_reviews);
                  free(path_users);
                  free(path_businesses);
                  free(path_reviews);
                  break;
              }
            }
            free(buffer2);
          }
          break;
        case '2':
          if (sgr != NULL && exist_users(sgr)){
            if(t_u == NULL) t_u = catalogues(sgr, 'u');
            interpreter_show(t_u,'u');
            clear_screen();
            show_menu();
          }
          else
            printf("You can't view user's catalogue without loading the files.\n");
          break;
        case '3':
          if (sgr != NULL && exist_reviews(sgr)){
            if (t_r == NULL) t_r = catalogues(sgr, 'r');
            interpreter_show(t_r,'r');
            clear_screen();
            show_menu();
          }
          else
            printf("You can't view business' catalogue without loading the files.\n");
          break;
        case '4':
          if (sgr != NULL && exist_businesses(sgr)){
            if (t_b == NULL) t_b = catalogues(sgr, 'b');
            interpreter_show(t_b,'b');
            clear_screen();
            show_menu();
          }
          else
            printf("You can't view business' catalogue without loading the files.\n");
          break;
        case '5':
          if(sgr != NULL ){
            clear_screen();
            i = interpreter(sgr,variables);
            if (i == 1) quit = 1;
            else {
              clear_screen();
              show_menu();
            }
          }
          else
            printf("You can't use interpreter without loading the files.\n");
          break;
        case 'Q':
          clear_line();
          quit = 1;
          break;
        case 'C':
          clear_screen();
          show_menu();
          break;
      }
    }
    free(buffer);
  }
  if(sgr)
    free_sgr(sgr);
  g_hash_table_destroy (variables);
  clear_screen();
  show_exit_message();
}