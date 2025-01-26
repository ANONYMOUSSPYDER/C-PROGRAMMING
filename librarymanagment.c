#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to represent a book
typedef struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
    struct Book* next;
} Book;

// Structure to represent a borrower
typedef struct Borrower {
    int id;
    char name[50];
    char email[50];
    struct Book* borrowedBooks;
    struct Borrower* next;
} Borrower;

// Function to add a book to the library
void addBook(Book** head, int id, char* title, char* author, int quantity) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->quantity = quantity;
    newBook->next = *head;
    *head = newBook;
}

// Function to add a borrower to the system
void addBorrower(Borrower** head, int id, char* name, char* email) {
    Borrower* newBorrower = (Borrower*)malloc(sizeof(Borrower));
    newBorrower->id = id;
    strcpy(newBorrower->name, name);
    strcpy(newBorrower->email, email);
    newBorrower->borrowedBooks = NULL;
    newBorrower->next = *head;
    *head = newBorrower;
}

// Function to borrow a book
void borrowBook(Book* book, Borrower* borrower) {
    if (book->quantity > 0) {
        book->quantity--;
        Book* borrowedBook = (Book*)malloc(sizeof(Book));
        borrowedBook->id = book->id;
        strcpy(borrowedBook->title, book->title);
        strcpy(borrowedBook->author, book->author);
        borrowedBook->next = borrower->borrowedBooks;
        borrower->borrowedBooks = borrowedBook;
        printf("Book borrowed successfully!\n");
    } else {
        printf("Book is not available.\n");
    }
}

// Function to return a book
void returnBook(Book* book, Borrower* borrower) {
    Book* current = borrower->borrowedBooks;
    Book* previous = NULL;
    while (current != NULL) {
        if (current->id == book->id) {
            if (previous == NULL) {
                borrower->borrowedBooks = current->next;
            } else {
                previous->next = current->next;
            }
            book->quantity++;
            free(current);
            printf("Book returned successfully!\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Book not found in borrower's list.\n");
}

// Function to display all books
void displayBooks(Book* head) {
    while (head != NULL) {
        printf("ID: %d, Title: %s, Author: %s, Quantity: %d\n", head->id, head->title, head->author, head->quantity);
        head = head->next;
    }
}

// Function to display all borrowers
void displayBorrowers(Borrower* head) {
    while (head != NULL) {
        printf("ID: %d, Name: %s, Email: %s\n", head->id, head->name, head->email);
        Book* borrowedBooks = head->borrowedBooks;
        while (borrowedBooks != NULL) {
            printf("  - %s by %s\n", borrowedBooks->title, borrowedBooks->author);
            borrowedBooks = borrowedBooks->next;
        }
        head = head->next;
    }
}

int main() {
    Book* bookHead = NULL;
    Borrower* borrowerHead = NULL;

    int choice;
    while (1) {
        printf("UPES College Library Management System\n");
        printf("1. Add a book\n");
        printf("2. Add a borrower\n");
        printf("3. Borrow a book\n");
        printf("4. Return a book\n");
        printf("5. Display all books\n");
        printf("6. Display all borrowers\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id;
                char title[50], author[50];
                int quantity;
                printf("Enter book ID: ");
                scanf("%d", &id);
                printf("Enter book title: ");
                scanf("%s", title);
                printf("Enter book author: ");
                scanf("%s ", author);
                printf("Enter book quantity: ");
                scanf("%d", &quantity);
                addBook(&bookHead, id, title, author, quantity);
                break;
            }
            case 2: {
                int id;
                char name[50], email[50];
                printf("Enter borrower ID: ");
                scanf("%d", &id);
                printf("Enter borrower name: ");
                scanf("%s", name);
                printf("Enter borrower email: ");
                scanf("%s", email);
                addBorrower(&borrowerHead, id, name, email);
                break;
            }
            case 3: {
                int bookId, borrowerId;
                printf("Enter book ID: ");
                scanf("%d", &bookId);
                printf("Enter borrower ID: ");
                scanf("%d", &borrowerId);
                Book* book = bookHead;
                while (book != NULL) {
                    if (book->id == bookId) {
                        break;
                    }
                    book = book->next;
                }
                if (book == NULL) {
                    printf("Book not found.\n");
                    break;
                }
                Borrower* borrower = borrowerHead;
                while (borrower != NULL) {
                    if (borrower->id == borrowerId) {
                        break;
                    }
                    borrower = borrower->next;
                }
                if (borrower == NULL) {
                    printf("Borrower not found.\n");
                    break;
                }
                borrowBook(book, borrower);
                break;
            }
            case 4: {
                int bookId, borrowerId;
                printf("Enter book ID: ");
                scanf("%d", &bookId);
                printf("Enter borrower ID: ");
                scanf("%d", &borrowerId);
                Book* book = bookHead;
                while (book != NULL) {
                    if (book->id == bookId) {
                        break;
                    }
                    book = book->next;
                }
                if (book == NULL) {
                    printf("Book not found.\n");
                    break;
                }
                Borrower* borrower = borrowerHead;
                while (borrower != NULL) {
                    if (borrower->id == borrowerId) {
                        break;
                    }
                    borrower = borrower->next;
                }
                if (borrower == NULL) {
                    printf("Borrower not found.\n");
                    break;
                }
                returnBook(book, borrower);
                break;
            }
            case 5:
                displayBooks(bookHead);
                break;
            case 6:
                displayBorrowers(borrowerHead);
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}