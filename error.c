#include <stdio.h>
#include <string.h>

int main() {
    // Book Data
    int bkid[50], n = 0, i, j, sno;
    char bktitle[50][50], bkauthor[50][50], status[50][50];

    // Borrower Data
    int stid[50], temp_bkid, temp_stid;

    // Other Data4

    int fine = 10;
    int ldays;
    
    printf("\tWelcome to Library Management System!\n");

    while (1) {
        // Choice Portal
        printf("\nWhat do you want to do?\n\t1. Add a Book\n\t2. Borrow a Book\n\t3. Return a Book\n\t4. Display Book List\n\t5. Exit\nEnter your choice: ");
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
        case 1: {
            // Add book to the Library (Admin Access)
            printf("ADD BOOK TO LIBRARY:- \n");
            printf("Access only for Admins\n");

            int admin;
            printf("Enter Admin ID: ");
            scanf("%d", &admin);

            switch (admin) {
            case 0000:
                printf("Access Granted\n");
                printf("Enter Serial Number of book(0-49): ");
                scanf("%d", &sno);
                getchar();  // To consume the newline character after the integer input

                printf("Enter the Book ID: ");
                scanf("%d", &bkid[sno]);
                getchar();  // To consume the newline character after the integer input
                
                printf("Enter the Book Title: ");
                fgets(bktitle[sno], 50, stdin);
                getchar()  // Remove newline character

                printf("Enter the Book Author: ");
                fgets(bkauthor[sno], 50, stdin);
                getchar();  // Remove newline character

                strcpy(status[sno], "available");
                n++;
                printf("Book is now added to the library!\n");
                break;
            default:
                printf("Access Denied. Invalid Credentials.\n");
                break;
            }
            break;
        }
        case 2: {
            // Borrow a book
            printf("Enter Student ID: ");
            scanf("%d", &temp_stid);
            printf("Enter the Book ID: ");
            scanf("%d", &temp_bkid);

            for (i = 0; i < n; i++) {
                if (bkid[i] == temp_bkid && strcmp(status[i], "available") == 0) {
                    strcpy(status[i], "borrowed");
                    stid[i] = temp_stid;
                    printf("Book Borrowed Successfully\n");
                    break;
                }
            }
            if (i == n) {
                printf("Book ID not found or already borrowed.\n");
            }
            break;
        }
        case 3: {
            // Return a book
            printf("Enter Student ID: ");
            scanf("%d", &temp_stid);
            printf("Enter Borrowed Book ID: ");
            scanf("%d", &temp_bkid);

            for (i = 0; i < n; i++) {
                if (bkid[i] == temp_bkid && stid[i] == temp_stid && strcmp(status[i], "borrowed") == 0) {
                    printf("Enter the Late Days (if any, else 0): ");
                    scanf("%d", &ldays);

                    if (ldays > 0) {
                        printf("Fine = Rs. %d\n", fine * ldays);
                    }
                    strcpy(status[i], "available");
                    stid[i] = 0;
                    printf("Book Returned Successfully!\n");
                    break;
                }
            }
            if (i == n) {
                printf("Book or Student ID not found.\n");
            }
            break;
        }
        case 4: {
            // Display book list
            printf("Book ID\tTitle\tAuthor\tStatus\tStudent ID\n");
            for (i = 0; i < n; i++) {
                printf("%d\t%s\t%s\t%s\t%d\n", bkid[i], bktitle[i], bkauthor[i], status[i], stid[i]);
            }
            break;
        }
        case 5:
            // Exit
            printf("Bye Bye!!\n");
            return 0;
        default:
            printf("Invalid Input!!\n");
        }
    }

    return 0;
}
