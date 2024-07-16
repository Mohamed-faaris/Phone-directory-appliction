#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a phone number node
typedef struct PhoneNumberNode {
    char number[20];
    struct PhoneNumberNode* next;
} PhoneNumberNode;

// Structure for a contact
typedef struct {
    char name[50];
    PhoneNumberNode* phoneNumbers; // Linked list of phone numbers
} Contact;

// Structure for a node in the BST
typedef struct Node {
    Contact contact;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new phone number node
PhoneNumberNode* createPhoneNumberNode(const char* number) {
    PhoneNumberNode* newNode = (PhoneNumberNode*)malloc(sizeof(PhoneNumberNode));
    strcpy(newNode->number, number);
    newNode->next = NULL;
    return newNode;
}

// Function to add a phone number to the list of phone numbers for a contact
void addPhoneNumber(Contact* contact, const char* number) {
    PhoneNumberNode* newNode = createPhoneNumberNode(number);
    if (contact->phoneNumbers == NULL) {
        contact->phoneNumbers = newNode;
    } else {
        PhoneNumberNode* current = contact->phoneNumbers;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to create a new node
Node* createNode(Contact contact) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a contact into the BST
Node* insert(Node* root, Contact contact) {
    if (root == NULL) {
        return createNode(contact);
    }

    if (strcmp(contact.name, root->contact.name) < 0) {
        root->left = insert(root->left, contact);
    } else {
        root->right = insert(root->right, contact);
    }

    return root;
}

// Function to search for a contact in the BST
Node* search(Node* root, const char* name) {
    if (root == NULL || strcmp(root->contact.name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->contact.name) < 0) {
        return search(root->left, name);
    } else {
        return search(root->right, name);
    }
}

// Function to display contacts in sorted order (inorder traversal)
void display(Node* root) {
    if (root != NULL) {
        display(root->left);
        printf("Name: %s\n", root->contact.name);
        printf("Phone Numbers:\n");
        PhoneNumberNode* current = root->contact.phoneNumbers;
        while (current != NULL) {
            printf("- %s\n", current->number);
            current = current->next;
        }
        printf("\n");
        display(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice;
    Contact newContact;
    char searchName[50];
    char phoneNumber[20];

    do {
        printf("\nPhone Directory Menu:\n");
        printf("1. Add a contact\n");
        printf("2. Search for a contact\n");
        printf("3. Display all contacts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", newContact.name);
                newContact.phoneNumbers = NULL; // Initialize phone numbers list
                printf("Enter phone number: ");
                scanf("%s", phoneNumber);
                addPhoneNumber(&newContact, phoneNumber);
                char addMore;
                do {
                    printf("Add another phone number? (y/n): ");
                    scanf(" %c", &addMore);
                    if (addMore == 'y' || addMore == 'Y') {
                        printf("Enter phone number: ");
                        scanf("%s", phoneNumber);
                        addPhoneNumber(&newContact, phoneNumber);
                    }
                } while (addMore == 'y' || addMore == 'Y');
                root = insert(root, newContact);
                printf("Contact added successfully.\n");
                break;
            case 2:
                printf("Enter name to search: ");
                scanf("%s", searchName);
                Node* result = search(root, searchName);
                if (result != NULL) {
                    printf("Contact found - Name: %s\n", result->contact.name);
                    printf("Phone Numbers:\n");
                    PhoneNumberNode* current = result->contact.phoneNumbers;
                    while (current != NULL) {
                        printf("- %s\n", current->number);
                        current = current->next;
                    }
                } else {
                    printf("Contact not found.\n");
                }
                break;
            case 3:
                printf("Contacts:\n");
                display(root);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
    
    return 0;
}