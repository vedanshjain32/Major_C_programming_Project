#include <stdio.h>
#include "library.h"
#include "utils.h"

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
int main() {
load_data();
printf("PROJECT_NAME - Library Book Tracking System\n");
printf("TEAM - Vedansh Jain, Adarsh Chaudhary\n");
printf("SAP ID - 590023901, 590025023\n");
printf("DATE - 08 Dec
