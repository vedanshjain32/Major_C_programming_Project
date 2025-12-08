#ifndef LIBRARY_H
#define LIBRARY_H


#define MAX_BOOKS 1000
#define TITLE_LEN 100
#define AUTHOR_LEN 100
#define DATAFILE "library.dat"


typedef struct {
int id;
char title[TITLE_LEN];
char author[AUTHOR_LEN];
int total;
int available;
} Book;


extern Book books[MAX_BOOKS];
extern int book_count;


void load_data();
void save_data();
int next_id();
int find_index_by_id(int id);
void add_book();
void list_books();
void search_books();
void issue_book();
void return_book();
void remove_book();


#endif
