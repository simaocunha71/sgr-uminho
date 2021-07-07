#include "../../includes/view/table.h"

/* ---------------//--------------- [Structs] ---------------//--------------- */

//[struct table]
struct table{
	string *info;         //Information of table      -> Array of strings
	string *titles;       //Table titles              -> Array of strings
	string title_lines;   //Title lines of table      -> String
	int lines;            //Table lines               -> Int
	int columns;          //Table columns             -> Int
	int size;             //Table size                -> Int
	int number_of_pages;  //Number of table pages     -> Int
	int lines_for_page;   //Lines per page            -> Int
	int *biggest_length;  //Biggest Length of columns -> Int
	int buffer_size;      //Buffer size of table      -> Int
};

/* ---------------//--------------- [Private Functions] ---------------//--------------- */

//[Initialization function of string*]
static string *init_strings(int size){
	string *ss = (string *)malloc(sizeof(string) * size);
	if (ss == NULL){
		abort();
	}
	int i;
	for (i = 0; i < size; i++)
		ss[i] = NULL;
	return ss;
}

//[Destruction function of string*]
static void destroy_strings(string *ss, int size){
	int i;
	for (i = 0; i < size; i++)
		free(ss[i]);
	free(ss);
}

//[Realloc function of string*]
static string *reinit_strings(string *ss, int old_size, int new_size){
	ss = (string *)realloc(ss, sizeof(string) * new_size);
	if (ss == NULL){
		abort();
	}
	int i;
	for (i = old_size; i < new_size; i++)
		ss[i] = NULL;
	return ss;
}

//[Realloc function of int array (int* biggest_length of table)]
static int *reinit_biggest_length(int *bl, int old_size, int new_size){
	bl = (int *)realloc(bl, sizeof(int) * new_size);
	if (bl == NULL){
		abort();
	}
	int i;
	for (i = old_size; i < new_size; i++)
		bl[i] = 0;
	return bl;
}

//[Initialization function of int array (int* biggest_length of table)]
static int *init_biggest_length(int size){
	int *bl = (int *)malloc(sizeof(int) * size);
	if (bl == NULL){
		abort();
	}
	int i;
	for (i = 0; i < size; i++)
		bl[i] = 0;
	return bl;
}

//[Get biggest length of column of a struct table]
static int get_table_biggest_length_of_column(TABLE t, int c){
	return t->biggest_length[c];
}

//[Set biggest length of column of a struct table]
static void set_table_biggest_length_of_column(TABLE t, int c, int length){
	t->biggest_length[c] = length;
}

//[Increment a size of a struct table]
static void inc_table_size(TABLE t){
	t->size += 1;
	if(t->size == t->buffer_size){
		t->info = reinit_strings(t->info,t->buffer_size,t->buffer_size*2);
		t->buffer_size*=2;
	}

}

//[Print a line of repetitions of c]
static void print_line(int size, char c){
	int i;
	for (i = 0; i < size; i++)
		putchar(c);
}

//[Print a string]
static void print_string(string s, int size){
	int size_string;
	size_string = strlen(s);

	int white_spaces;
	white_spaces = (size - size_string) / 2;

	print_line(white_spaces, ' ');
	printf("%s", s);

	int leftover;
	leftover = size - white_spaces - size_string;
	print_line(leftover, ' ');
}

//[Printf titles of a struct table]
static void print_titles(TABLE t){
	putchar('|');

	int c;
	c = get_table_columns(t);

	int i;
	for (i = 0; i < c; i++){
		print_string(t->titles[i], get_table_biggest_length_of_column(t, i) + 2);
		putchar('|');
	}
	putchar('\n');
}

//[Printf line info of a struct table]
static void print_line_info(TABLE t, int l){
	putchar('|');

	int c;
	c = get_table_columns(t);

	int i;
	for (i = 0; i < c; i++){
		print_string(t->info[c * l + i], get_table_biggest_length_of_column(t, i) + 2);
		putchar('|');
	}
	putchar('\n');
}

/* ---------------//--------------- [Public Functions] ---------------//--------------- */

/* [Initialization and destruction functions] */

//[Initialization function of struct table]
TABLE init_table(int buffer_size){
	TABLE t = malloc(sizeof(struct table));
	if (t == NULL){
		abort();
	}
	set_table_columns(t, 0);
	set_table_lines(t, 0);
	set_table_lines_for_page(t, 0);
	set_table_number_of_pages(t, 0);
	set_table_size(t, 0);
	if (buffer_size == 0) 
		t->buffer_size = 50000;
	else 
		t->buffer_size = buffer_size;
	t->info = init_strings(t->buffer_size);
	t->titles = NULL;
	t->biggest_length = NULL;
	t->title_lines = NULL;
	return t;
}

//[Destruction function of struct table]
void free_table(TABLE t){
	if (t != NULL){
		if (t->titles != NULL)
			destroy_strings(t->titles, t->columns);

		if (t->info != NULL)
			destroy_strings(t->info, t->size);

		if (t->biggest_length != NULL)
			free(t->biggest_length);

		if (t->title_lines != NULL)
			free(t->title_lines);

		free(t);
	}
}

/* [getters and setters functions] */

//[Get size of a struct table]
int get_table_size(TABLE t){
	return t->size;
}

//[Get lines of a struct table]
int get_table_lines(TABLE t){
	return t->lines;
}

//[Get columns of a struct table]
int get_table_columns(TABLE t){
	return t->columns;
}

//[Get number of pages of a struct table]
int get_table_number_of_pages(TABLE t){
	return t->number_of_pages;
}

//[Get lines for page of a struct table]
int get_table_lines_for_page(TABLE t){
	return t->lines_for_page;
}

//[Get column title of a struct table]
char *get_table_titles(TABLE t, int col){
	char *s = strdup(t->titles[col]);
	return s;
}

//[Get info of a struct table]
char *get_table_info(TABLE t, int i){
	char *s = strdup(t->info[i]);
	return s;
}

//[Get info of a struct table]
char *get_table_title_line(TABLE t){
	char *s = strdup(t->title_lines);
	return s;
}

//[Set size of a struct table]
void set_table_size(TABLE t, int size){
	t->size = size;
}

//[Set lines of a struct table]
void set_table_lines(TABLE t, int lines){
	t->lines = lines;
}

//[Set columns of a struct table]
void set_table_columns(TABLE t, int columns){
	if (columns > 0){
		if (t->columns > 0){
			t->titles = reinit_strings(t->titles, t->columns, columns);
			t->biggest_length = reinit_biggest_length(t->biggest_length, t->columns, columns);
		}
		else{
			t->titles = init_strings(columns);
			t->biggest_length = init_biggest_length(columns);
		}
		t->columns = columns;
	}
	else
		t->columns = 0;
}

//[Set number of pages of a struct table]
void set_table_number_of_pages(TABLE t, int number_of_pages){
	t->number_of_pages = number_of_pages;
}

//[Set lines for page of a struct table]
void set_table_lines_for_page(TABLE t, int lines_for_page){
	t->lines_for_page = lines_for_page;
}

//[Set title lines of a struct table]
void set_title_lines(TABLE t, char* title){
	t->title_lines = strdup(title);
}

//[Set default pages [10 lines for page] of a struct table]
void set_default_pages(TABLE t){
	int lines, number_of_pages;
	set_table_lines_for_page(t, 10);

	lines = get_table_lines(t);
	if (lines != 0){
		number_of_pages = lines / 10;
		if (lines%10 != 0) number_of_pages++;
	}
	else
		number_of_pages = 1;

	set_table_number_of_pages(t, number_of_pages);
}

/* [Increment and add functions] */

//[Increment lines of a struct table]
void inc_table_lines(TABLE t){
	t->lines += 1;
}

//[Add a title to the column of a struct table]
void add_title_of_column(TABLE t, string s, int c){
	if (c >= 0){
		int title_size;
		t->titles[c] = strdup(s);
		title_size = strlen(t->titles[c]);
		if (c >= get_table_columns(t))
			set_table_columns(t, c + 1);

		if (title_size > get_table_biggest_length_of_column(t, c))
			set_table_biggest_length_of_column(t, c, title_size);
	}
}

//[Add information to a struct table]
void add_info_string(TABLE t, string s){
	int table_size, info_size, c;

	table_size = get_table_size(t);
	t->info[table_size] = strdup(s);
	info_size = strlen(t->info[table_size]);
	c = table_size % get_table_columns(t);

	if (info_size > get_table_biggest_length_of_column(t, c))
		set_table_biggest_length_of_column(t, c, info_size);

	inc_table_size(t);
}

/* [Print functions] */

//[Print a struct table]
void print_page_of_table(TABLE t, int page){
	int number_of_pages;
	number_of_pages = t->number_of_pages;
	if (page <= number_of_pages && page > 0){
		int lines_for_page, c, cs, ls, length_table;

		lines_for_page = t->lines_for_page;
		cs = get_table_columns(t);
		ls = get_table_lines(t);

		for (length_table = 0, c = 0; c < cs; c++)
			length_table += t->biggest_length[c] + 2;
		
		length_table += cs + 1;

		print_line(length_table, '-');
		putchar('\n');
		print_titles(t);
		print_line(length_table, '-');
		putchar('\n');

		if (get_table_size(t) > 0){
			int i;
			for (i = (page - 1) * lines_for_page; (i < page * lines_for_page && i < ls); i++){
				print_line_info(t, i);
				print_line(length_table, '-');
				putchar('\n');
			}
			if (t->title_lines != NULL)
				printf("[%s]: %d\n", t->title_lines, ls);
			if (number_of_pages > 1)
				printf("Page %d of %d\n", page, number_of_pages);
		}
	}
	else
		printf("Não existe essa página\n");
}

/*
void show_review_text (TABLE t){
	print_line(200,'-');
	printf("\n");
	print_string_coloured(get_table_titles(t, 0), "green");
	print_string_coloured(get_table_info(t,0),"yellow");
	printf("\n");
	print_line(200, '-');
	printf("\n");

	print_string_coloured("On ","blue");
	print_string_coloured(get_table_info(t,2),"yellow");
	print_string_coloured(", the user ","blue");
	print_string_coloured(get_table_info(t,1),"yellow");
	print_string_coloured(" said about the business ","blue");
	print_string_coloured(get_table_info(t,3),"yellow");
	print_string_coloured(" :","blue");
	printf("\n");
	print_string_coloured(get_table_info(t,4),"green");
	printf("\n");
	print_line(200, '-');
	printf("\n");
}
*/
