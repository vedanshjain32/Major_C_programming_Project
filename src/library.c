#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "utils.h"

Book books[MAX_BOOKS];
int book_count = 0;

// ----------------- FILE HANDLING --------------------

void load_data() {
    FILE *f = fopen(DATAFILE, "rb");
    if (!f) return;

    fread(&book_count, sizeof(int), 1, f);
    
    if (book_count > 0 && book_count <= MAX_BOOKS)
        fread(books, sizeof(Book), book_count, f);

    fclose(f);
}

void save_data() {
    FILE *f = fopen(DATAFILE, "wb");
    if (!f) {
        printf("Error writing data.\n");
        return;
    }

    fwrite(&book_count, sizeof(int), 1, f);
    fwrite(books, sizeof(Book), book_count, f);
    fclose(f);
}

// ----------------- HELPER FUNCTIONS --------------------

int find_index_by_id(int id) {
    for (int i = 0; i < book_count; i++)
        if (books[i].id == id)
            return i;
    return -1;
}

int next_id() {
    int max = 0;
    for (int i = 0; i < book_count; i++)
        if (books[i].id > max)
            max = books[i].id;
    return max + 1;
}

// ----------------- MAIN LIBRARY OPERATIONS --------------------

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library full.\n");
        return;
    }

    Book b;
    char buf[32];

    b.id = next_id();

    printf("Enter title: ");
    fgets(b.title, TITLE_LEN, stdin);
    strip_newline(b.title);

    printf("Enter author: ");
    fgets(b.author, AUTHOR_LEN, stdin);
    strip_newline(b.author);

    printf("Enter number of copies: ");
    fgets(buf, sizeof(buf), stdin);
    b.total = atoi(buf);
    if (b.total < 1) b.total = 1;

    b.available = b.total;

    books[book_count++] = b;
    save_data();

    printf("Book added. ID = %d\n", b.id);
}

void list_books() {
    if (book_count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("ID\tAvail/Total\tTitle - Author\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < book_count; i++) {
        printf("%d\t%d/%d\t\t%s - %s\n",
            books[i].id,
            books[i].available,
            books[i].total,
            books[i].title,
            books[i].author
        );
    }
}

void search_books() {
    char choice[8];
    printf("Search by (1) ID or (2) Title substring: ");
    fgets(choice, sizeof(choice), stdin);

    if (choice[0] == '1') {
        char buf[32];
        printf("Enter ID: ");
        fgets(buf, sizeof(buf), stdin);

        int id = atoi(buf);
        int idx = find_index_by_id(id);

        if (idx == -1) {
            printf("No book with ID %d\n", id);
            return;
        }

        Book *b = &books[idx];
        printf("ID: %d\nTitle: %s\nAuthor: %s\nTotal: %d\nAvailable: %d\n",
            b->id, b->title, b->author, b->total, b->available);
    } else {
        char q[TITLE_LEN];
        printf("Enter search text: ");
        fgets(q, sizeof(q), stdin);
        strip_newline(q);

        int found = 0;
        for (int i = 0; i < book_count; i++) {
            if (my_strcasestr(books[i].title, q) ||
                my_strcasestr(books[i].author, q)) {

                if (!found)
                    printf("Matches:\n");

                printf("%d\t%d/%d\t%s - %s\n",
                    books[i].id,
                    books[i].available,
                    books[i].total,
                    books[i].title,
                    books[i].author
                );

                found = 1;
            }
        }
        if (!found) printf("No matches.\n");
    }
}

void issue_book() {
    char buf[32];
    printf("Enter ID to issue: ");
    fgets(buf, sizeof(buf), stdin);

    int id = atoi(buf);
    int idx = find_index_by_id(id);

    if (idx == -1) {
        printf("Invalid ID.\n");
        return;
    }
    if (books[idx].available == 0) {
        printf("No copies available.\n");
        return;
    }

    books[idx].available--;
    save_data();
    printf("Book issued.\n");
}

void return_book() {
    char buf[32];
    printf("Enter ID to return: ");
    fgets(buf, sizeof(buf), stdin);

    int id = atoi(buf);
    int idx = find_index_by_id(id);

    if (idx == -1) {
        printf("Invalid ID.\n");
        return;
    }
    if (books[idx].available == books[idx].total) {
        printf("All copies already in library.\n");
        return;
    }

    books[idx].available++;
    save_data();
    printf("Book returned.\n");
}

void remove_book() {
    char buf[32];
    printf("Enter ID to remove: ");
    fgets(buf, sizeof(buf), stdin);

    int id = atoi(buf);
    int idx = find_index_by_id(id);

    if (idx == -1) {
        printf("Invalid ID.\n");
        return;
    }

    for (int i = idx; i < book_count - 1; i++)
        books[i] = books[i + 1];

    book_count--;
    save_data();
    printf("Book removed.\n");
}

void menu() {
    char c[8];

    while (1) {
        printf("\n--- Library Menu ---\n");
        printf("1. Add Book\n");
        printf("2. List Books\n");
        printf("3. Search\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Remove Book\n");
        printf("0. Exit\n");
        printf("Choice: ");

        fgets(c, sizeof(c), stdin);

        switch (c[0]) {
            case '1': add_book(); break;
            case '2': list_books(); break;
            case '3': search_books(); break;
            case '4': issue_book(); break;
            case '5': return_book(); break;
            case '6': remove_book(); break;
            case '0': save_data(); return;
            default: printf("Invalid choice.\n");
        }
    }
}
