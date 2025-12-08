#include <stdio.h>
if (!found) printf("Matches:\n");
printf("%d\t%d/%d\t%s - %s\n",
books[i].id,
books[i].available,
books[i].total,
books[i].title,
books[i].author);
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
printf("All copies already present.\n");
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
for (int i = idx; i < book_count - 1; i++) {
books[i] = books[i + 1];
}
book_count--;
save_data();
printf("Book removed.\n");
}
