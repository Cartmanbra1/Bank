// (89110, Spring 2023, Assignment #5, Roie Amsalem, 322535436, roieams)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_CHAR 1
#define DECIMAL_BASE 10

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Account {
    unsigned int accountNumber;
    char *accountHolder;
    int balance;
} Account;

typedef struct Transaction {
    unsigned int fromAccount;
    unsigned int toAccount;
    int amount;
} Transaction;

typedef struct Bank {
    Node *accounts;
    Node *transactions;
} Bank;

void menu();

void cleanBuffer(char cleanBuffer);

void createAccountNumber(Bank *bank, Account *accountNumber, int *counter);

void createAccountHolder(Node *newNode);

void freeMemory(Bank *bank);

void deleteAccount(Bank *bank);

void updateAccount(Bank *bank);

void depositOrWithdraw(Bank *bank);

void fDeposit(Bank *bank, unsigned int insertNum);

void fWithdraw(Bank *bank, unsigned int insertNum);

int findAccount(Node *head, unsigned int insertNum);

int checkAmount(char *numCheck);

void multipleTransactions(Bank *bank);

char *makeString();

char *makeStringTransactions();

int stringToInt(char *turnToNumber);

void viewAccount(Bank *bank);

void freeDummyMemory(Node *dummyList, Node *dummyListTran);

int main() {
    menu();
}

/**
 * @brief Displays a menu of options and performs corresponding actions based on user input.
 *
 * This function displays a menu of options to the user and performs the corresponding actions based on the user's input.
 * The options include creating an account, deleting an account, updating an account, depositing or withdrawing money,
 * transferring money, and viewing account details.
 *
 * @param true An integer value that is always true (non-zero) to keep the menu running until the user exits.
 */
void menu() {
    // Allocate memory for Bank struct
    Bank *accountInfo = (Bank *) malloc(sizeof(Bank));
    // Allocate memory for Account struct
    Account *accountNumber = (Account *) malloc(sizeof(Account));
    if (accountInfo == NULL || accountNumber == NULL) {
        // Exit the program if memory allocation fails
        exit(1);
    }
    // Tracks the number of accounts
    int countAccounts = 0;
    // Stores the user's menu choice
    char option;
    // Loop continues indefinitely
    while (1) {
        if (countAccounts == 0) {
            // Set accounts pointer to NULL
            accountInfo->accounts = NULL;
            // Set transactions pointer to NULL
            accountInfo->transactions = NULL;
        }
        printf("Choose an option:\n"
               "0. Exit\n"
               "1. Create account\n"
               "2. Delete account\n"
               "3. Update account\n"
               "4. Deposit / Withdraw money\n"
               "5. Transferring\n"
               "6. View account\n");
        // Read the user's menu choice
        scanf("%c", &option);
        // Clean the input buffer (implementation not provided
        if (option < '0' || option > '6') {
            if (option != '\n') {
                printf("Invalid option\n");
                cleanBuffer(0);
                // Skip to the next iteration of the loop
                continue;
            } else {
                cleanBuffer(0);
                printf("Invalid option\n");
                continue;
            }
        }

        if (option == '0') {
            // Exit the loop and end the program
            break;
        } else if (option == '1') {
            // Create a new account
            createAccountNumber(accountInfo, accountNumber, &countAccounts);
        } else if (option == '2') {
            // Delete an existing account
            deleteAccount(accountInfo);
            // Clean the input buffer (implementation not provided)
            cleanBuffer(0);
        } else if (option == '3') {
            // Update account information
            updateAccount(accountInfo);
        } else if (option == '4') {
            // Perform deposit or withdrawal
            depositOrWithdraw(accountInfo);
        } else if (option == '5') {
            // Perform multiple transactions
            multipleTransactions(accountInfo);
        } else if (option == '6') {
            // View account details
            viewAccount(accountInfo);
            // Clean the input buffer (implementation not provided)
            cleanBuffer(0);
        }
    }
    // Free dynamically allocated memory
    freeMemory(accountInfo);
    free(accountInfo);
    free(accountNumber);
}

/**
 * @brief Clears the input buffer.
 *
 * @param cleanBuffer A variable to store the cleaned input buffer.
 */
void cleanBuffer(char cleanBuffer) {
    // Parsing the buffer
    scanf("%c", &cleanBuffer);
    // Continuing to parse the buffer until '\n'
    while (cleanBuffer != '\n') {
        scanf("%c", &cleanBuffer);
    }
}

/**
 * @brief Creates an account number for a new account and adds it to the bank's accounts list.
 *
 * @param bank The bank structure.
 * @param accountNumber The account structure to store the account number.
 * @param counter The counter to keep track of the number of accounts.
 */
void createAccountNumber(Bank *bank, Account *accountNumber, int *counter) {
    Node *head, *newNode;
    // Receiving user input for account number
    printf("Enter account number:\n");
    scanf("%u", &accountNumber->accountNumber);
    // Making sure account number isn't 0 (unsigned int can't be negative)
    if (accountNumber->accountNumber == 0) {
        printf("Account number already exists\n");
        cleanBuffer(0);
        // Exit the function if it's 0;
        return;
    }
    head = bank->accounts;
    // A while loop on the linked list
    while (head != NULL) {
        // Check if the account number already exists in the linked list
        if (((Account *) head->data)->accountNumber == accountNumber->accountNumber) {
            printf("Account number already exists\n");
            cleanBuffer(0);
            // Exit the function if the account number already exists
            return;
        }
        // Go to the next element
        head = head->next;
    }
    // Create a new node and assign the account number
    newNode = (Node *) malloc(sizeof(Node));
    // Check if memory was allocated successfully
    if (newNode == NULL) {
        exit(1);
    }
    // Check if memory was allocated successfully
    newNode->data = malloc(sizeof(Account));
    if (newNode->data == NULL) {
        exit(1);
    }
    // Insert the new account number to the new node
    ((Account *) newNode->data)->accountNumber = accountNumber->accountNumber;
    // Set the balance of the new account number to 0 for future uses.
    ((Account *) newNode->data)->balance = 0;
    // If the bank is empty insert the first account.
    if (bank->accounts == NULL) {
        bank->accounts = newNode;
        newNode->next = NULL;
        // If it isn't empty insert it to the beginning of the list.
    } else {
        newNode->next = bank->accounts;
        bank->accounts = newNode;
    }
    // pointer to counter++;
    (*counter)++;
    // Function call to createAccountHolder with the newNode as input.
    createAccountHolder(newNode);
}

/**
 * @brief Creates an account holder name for a new account and adds it to the account structure.
 *
 * @param newNode The new node to add to the accounts list.
 */
void createAccountHolder(Node *newNode) {
    // Declare variables
    char *name = NULL, character = 0, clean = 0, *temp;
    int length = 0, count = 1;
    // Allocate memory for name
    name = (char *) malloc(sizeof(char));
    if (name == NULL) {
        exit(1);
    }
    // Prompt for account holder input
    printf("Enter account holder:\n");
    // Clear input buffer
    cleanBuffer(clean);
    // Read characters until newline is encountered
    scanf("%c", &character);
    while (character != '\n') {
        // Store character in name
        name[length] = character;
        length++;
        // Reallocate memory if needed
        if (length >= SIZE_OF_CHAR * count) {
            count++;
            // Use temp to make sure there is no memory leak in case of realloc failure.
            temp = name;
            name = (char *) realloc(name, count * sizeof(char));
            if (name == NULL) {
                free(temp);
                exit(1);
            }
        }
        // Read the next character
        scanf("%c", &character);
    }
    // Add null terminator to name
    name[length] = '\0';
    // Allocate memory for accountHolder and copy name into it
    ((Account *) newNode->data)->accountHolder = (char *) malloc(length + 1);
    if (((Account *) newNode->data)->accountHolder == NULL) {
        exit(1);
    }
    strcpy(((Account *) newNode->data)->accountHolder, name);
    // Free the memory allocated for name
    free(name);
    // Print success message
    printf("Account created successfully\n");
}


/**
 * @brief Frees the memory allocated for the linked lists and account data.
 *
 * @param bank The bank structure.
 */
void freeMemory(Bank *bank) {
    // Declare and initialize variables
    Node *current = bank->accounts;
    Node *currentTran = bank->transactions;
    Node *next, *nextTran;
    // Free memory for accounts
    while (current != NULL) {
        // Store the next node in a temporary variable
        next = current->next;
        // Free memory for accountHolder and account data
        free(((Account *) current->data)->accountHolder);
        free(current->data);
        // Free memory for the current node
        free(current);
        // Move to the next node
        current = next;
    }
    // Set accounts pointer to NULL
    bank->accounts = NULL;
    // Free memory for transactions
    while (currentTran != NULL) {
        // Store the next node in a temporary variable
        nextTran = currentTran->next;
        // Free memory for transaction data
        free((Transaction *) currentTran->data);
        // Free memory for the current node
        free(currentTran);
        // Move to the next node
        currentTran = nextTran;
    }
    // Set transactions pointer to NULL
    bank->transactions = NULL;
}


/**
 * @brief Deletes an account from the bank's accounts list.
 *
 * @param bank The bank structure.
 */
void deleteAccount(Bank *bank) {
    // Declare variables
    Node *head, *temp;
    unsigned int insertNum = 0;
    // Prompt for account number input
    printf("Enter account number:\n");
    scanf("%u", &insertNum);
    // Set head to the first node in the accounts list
    head = bank->accounts;
    // Check if the accounts list is empty
    if (head == NULL) {
        printf("Account not found\n");
        return;
    }
    // Check if the head node is the account to be deleted
    if (head->next == NULL) {
        if (((Account *) head->data)->accountNumber == insertNum) {
            bank->accounts = NULL;
            free(((Account *) head->data)->accountHolder);
            free(head->data);
            free(head);
            printf("Account deleted successfully\n");
            return;
        }
    } else if (head->next != NULL) {
        // Check if the head node is the account to be deleted
        if (((Account *) head->data)->accountNumber == insertNum) {
            bank->accounts = head->next;
            free(((Account *) head->data)->accountHolder);
            free(head->data);
            free(head);
            printf("Account deleted successfully\n");
            return;
        }
        // Traverse the accounts list to find the account to be deleted
        while (head->next != NULL) {
            if (((Account *) head->next->data)->accountNumber == insertNum) {
                // Store the next node in a temporary variable
                temp = head->next;
                // Update the links to remove the node
                head->next = head->next->next;
                // Free memory for the accountHolder and account data
                free(((Account *) temp->data)->accountHolder);
                free(temp->data);
                // Free memory for the current node
                free(temp);
                printf("Account deleted successfully\n");
                break;
            }
            // Move to the next node
            head = head->next;
        }
    } else {
        printf("Account not found\n");
    }
}


/**
 * @brief Updates the account holder name for a given account.
 *
 * @param bank The bank structure.
 */
void updateAccount(Bank *bank) {
    // Declare variables
    char *newName, character;
    Node *head;
    unsigned int insertNum, length = 0, count = 1;
    // Prompt for account number input
    printf("Enter account number:\n");
    scanf("%d", &insertNum);
    // Set head to the first node in the accounts list
    head = bank->accounts;
    // Traverse the accounts list
    newName = (char *) malloc(sizeof(char) * count + 1);
    while (head != NULL) {
        // Check if the current node's accountNumber matches the input
        if (((Account *) head->data)->accountNumber == insertNum) {
            printf("Enter new account holder:\n");
            // Clear input buffer
            cleanBuffer(0);
            // Read characters until newline is encountered
            scanf("%c", &character);
            while (character != '\n') {
                // Store character in newName
                newName[length] = character;
                length++;
                // Reallocate memory if needed
                if (length >= sizeof(char) * count) {
                    count++;
                    newName = (char *) realloc(newName, 2 * length);
                    if (newName == NULL) {
                        exit(1);
                    }
                }
                // Read the next character
                scanf("%c", &character);
            }
            // Add null terminator to newName
            newName[length] = '\0';
            // Free memory for the current accountHolder
            free(((Account *) head->data)->accountHolder);
            // Update accountHolder with newName
            ((Account *) head->data)->accountHolder = newName;
            return;
        }
        // Move to the next node
        head = head->next;
    }
    // Clear input buffer
    cleanBuffer(0);
    // If code reached here account not found
    printf("Account not found\n");
}


/**
 * @brief Performs deposit or withdraw operation on a given account.
 *
 * @param bank The bank structure.
 */
// Function to deposit or withdraw money from a bank account
void depositOrWithdraw(Bank *bank) {
    // Declare variables 'answer' and 'character'
    char *answer, character = 0;
    // Declare strings 'deposit' and 'withdraw'
    char *deposit = "deposit\0", *withdraw = "withdraw\0";
    // Declare unsigned integers
    unsigned int insertNum, i = 0, count = 1, isAccountReg;
    // Print a prompt for the account number
    printf("Enter account number:\n");
    // Read the account number from the user
    scanf("%u", &insertNum);
    // Check if the account exists
    isAccountReg = findAccount(bank->accounts, insertNum);
    // If the account does not exist, print an error message and return
    if (isAccountReg == 1) {
        printf("Account not found\n");
        cleanBuffer(0);
        return;
    }
    // Prompt the user to choose between depositing or withdrawing money
    printf("Would you like to deposit or withdraw money?\n");
    cleanBuffer(0);
    // Read the user's choice
    scanf("%c", &character);
    // Allocate memory for the 'answer' string
    answer = (char *) malloc(sizeof(char) + 1);
    // Read characters until a newline character is encountered
    while (character != '\n') {
        // If the allocated memory is not sufficient, reallocate more memory
        if (i >= sizeof(char) * count) {
            count++;
            answer = (char *) realloc(answer, 2 * i);
        }
        // Store the character in the 'answer' string
        answer[i] = character;
        // Read the next character
        scanf("%c", &character);
        i++;
    }

    // Add a null-terminating character to the 'answer' string
    answer[i] = '\0';

    // Check if the user chose to deposit money
    if (strcmp(answer, deposit) == 0) {
        // Call the function to deposit money
        fDeposit(bank, insertNum);
        // Free the memory allocated for 'answer' and return
        free(answer);
        return;
    }
        // Check if the user chose to withdraw money
    else if (strcmp(answer, withdraw) == 0) {
        // Call the function to withdraw money
        fWithdraw(bank, insertNum);
        // Free the memory allocated for 'answer' and return
        free(answer);
        return;
    }
        // If the user's choice is neither deposit nor withdraw, print an error message and return
    else {
        printf("Invalid action\n");
        // Free the memory allocated for 'answer' and return
        free(answer);
        return;
    }
}


/**
 * @brief Deposits money into a given account.
 *
 * @param bank The bank structure.
 * @param insertNum The account number.
 */
void fDeposit(Bank *bank, unsigned int insertNum) {
    // Declare variables
    int isValueValid = 0;
    Node *head, *headTran, *newTransaction;
    char *deposit;
    // Initialize variables
    head = bank->accounts;
    headTran = bank->transactions;
    // Prompt the user to enter the deposit amount
    printf("How much money would you like to deposit?\n");
    // Read the deposit amount as a string
    deposit = makeString();
    // Validate the deposit amount
    isValueValid = checkAmount(deposit);
    // Free the memory allocated for the deposit string
    free(deposit);
    // If the deposit amount is invalid, print an error message and return
    if (isValueValid < 0) {
        printf("Invalid amount\n");
        return;
    }
    // Search for the account with the given account number
    while (head != NULL) {
        // If the account is found
        if (((Account *) head->data)->accountNumber == insertNum) {
            // Update the account balance with the deposit amount
            if (((Account *) head->data)->balance == 0) {
                ((Account *) head->data)->balance = isValueValid;
            } else {
                ((Account *) head->data)->balance += isValueValid;
            }
            // Create a new transaction node
            newTransaction = (Node *) malloc(sizeof(Node));
            newTransaction->data = malloc(sizeof(Transaction));
            ((Transaction *) newTransaction->data)->fromAccount = 0;
            ((Transaction *) newTransaction->data)->toAccount = insertNum;
            ((Transaction *) newTransaction->data)->amount = isValueValid;
            newTransaction->next = NULL;
            // Append the new transaction node to the transactions list
            if (headTran == NULL) {
                bank->transactions = newTransaction;
            } else {
                while (headTran->next != NULL) {
                    headTran = headTran->next;
                }
                headTran->next = newTransaction;
                ((Transaction *) headTran->data)->amount += isValueValid;
                headTran->next = NULL;
            }
            // Print a success message with the new account balance
            printf("Money deposited successfully; your new balance is %d\n", ((Account *) head->data)->balance);
            return;
        }
        // Move to the next account
        head = head->next;
    }
    // If the account is not found, print an error message
    printf("Account not found\n");
}


/**
 * @brief Finds an account with the given account number in a linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @param insertNum The account number to search for.
 * @return 0 if the account is found, 1 otherwise.
 */
int findAccount(Node *head, unsigned int insertNum) {
    // Search for the account with the given account number
    while (head != NULL) {
        // If the account is found, return 0
        if (((Account *) head->data)->accountNumber == insertNum) {
            return 0;
        }
        // Move to the next account
        head = head->next;
    }
    // If the account is not found, return 1
    return 1;
}

/**
 * @brief Checks if a given string can be converted to a valid amount (integer).
 *
 * @param numCheck The string to check.
 * @return The converted integer if the string is a valid amount, -1 otherwise.
 */
int checkAmount(char *numCheck) {
    char *endptr;
    long number;
    number = strtol(numCheck, &endptr, DECIMAL_BASE);
    if (*endptr == '\0') {
        return number;
    } else {
        return -1;
    }
}

/**
 * @brief Withdraws money from a given account.
 *
 * @param bank The bank structure.
 * @param insertNum The account number.
 */
void fWithdraw(Bank *bank, unsigned int insertNum) {
    // Declare variables
    char *withdraw;
    int isValueValid = 0;
    Node *head, *headTran, *newTransaction;

    // Set initial values for linked list heads
    head = bank->accounts;
    headTran = bank->transactions;

    // Prompt user for withdrawal amount and validate input
    printf("How much money would you like to withdraw?\n");
    withdraw = makeString();
    isValueValid = checkAmount(withdraw);
    free(withdraw);

    // Check if withdrawal amount is invalid
    if (isValueValid == -1) {
        printf("Invalid amount\n");
        return;
    }

    // Search for the account with the specified account number
    while (head != NULL) {
        if (((Account *) head->data)->accountNumber == insertNum) {
            // Update account balance based on withdrawal amount
            if (((Account *) head->data)->balance == 0) {
                if (isValueValid == 0) {
                    ((Account *) head->data)->balance = isValueValid;
                } else {
                    printf("Not enough money\n");
                    return;
                }
            } else {
                if (((Account *) head->data)->balance > isValueValid) {
                    ((Account *) head->data)->balance -= isValueValid;
                } else {
                    printf("Not enough money\n");
                    return;
                }
            }

            // Create a new transaction and assign its values
            newTransaction = (Node *) malloc(sizeof(Node));
            newTransaction->data = malloc(sizeof(Transaction));
            ((Transaction *) newTransaction->data)->fromAccount = insertNum;
            ((Transaction *) newTransaction->data)->toAccount = 0;
            ((Transaction *) newTransaction->data)->amount = isValueValid;
            newTransaction->next = NULL;

            // Append the new transaction node to the transactions list
            if (headTran == NULL) {
                bank->transactions = newTransaction;
            } else {
                while (headTran->next != NULL) {
                    headTran = headTran->next;
                }
                headTran->next = newTransaction;
            }

            // Print the updated account balance
            printf("Money withdrawn successfully; your new balance is %d\n", ((Account *) head->data)->balance);
            return;
        }
        head = head->next;
    }

    // Account with the specified account number was not found
    printf("Account not found\n");
}


/**
 * @brief Performs multiple transactions based on the given instructions.
 *
 * @param bank The bank structure.
 */
void multipleTransactions(Bank *bank) {
    // Variable Declarations
    char *str, *strCopy = "\0", *senderChar = "-5\0", *receiverChar, *valueChar, *false = "-1\0";
    unsigned int sender, receiver, value, conditionCleared = 0;
    Node *head, *headTran, *newTransaction, *dummyList, *dummyListTran, *newNode;
    Node *dummyListHead, *dummyListHeadTran, *dummyNewTransaction, *newTranNode, *temp;
    // Prompt for instructions
    printf("Enter instructions:\n");
    // Read user input
    str = makeStringTransactions();
    // Dynamically allocate memory for strCopy
    strCopy = (char *) malloc(strlen(str) + 1);
    // Check if memory allocation was successful
    if (strCopy == NULL) {
        free(strCopy);
        exit(1);
    }
    // Copy str to strCopy
    strcpy(strCopy, str);
    // Check for false instruction
    if (strcmp(str, false) == 0) {
        cleanBuffer(0);
        printf("Invalid instructions\n");
        free(strCopy);
        return;
    }
    // Initialize dummyList and dummyListTran
    dummyList = NULL;
    dummyListTran = NULL;
    // Copy account data to dummyList and transaction data to dummyListTran
    head = bank->accounts;
    headTran = bank->transactions;
    while (head != NULL) {
        // Create a new node for account data
        newNode = (Node *) malloc(sizeof(Node));
        newNode->data = malloc(sizeof(Account));
        newNode->next = NULL;
        // Update dummyList and dummyListHead
        if (dummyList == NULL) {
            dummyList = newNode;
            dummyListHead = dummyList;
        } else {
            dummyListHead->next = newNode;
            dummyListHead = dummyListHead->next;
        }
        // Copy account data
        ((Account *) dummyListHead->data)->accountNumber = ((Account *) head->data)->accountNumber;
        ((Account *) dummyListHead->data)->balance = ((Account *) head->data)->balance;
        // Check if there is any transaction data
        if (headTran != NULL) {
            // If there is create a new node for a new transaction and insert it to the list
            newTranNode = (Node *) malloc(sizeof(Node));
            newTranNode->data = malloc(sizeof(Transaction));
            newTranNode->next = NULL;
            // Update dummyListTran and dummyListHeadTran
            if (dummyListTran == NULL) {
                dummyListTran = newTranNode;
                dummyListHeadTran = dummyListTran;
            } else {
                dummyListHeadTran->next = newTranNode;
                dummyListHeadTran = dummyListHeadTran->next;
            }
            // Copy transaction data
            ((Transaction *) dummyListHeadTran->data)->fromAccount = ((Transaction *) headTran->data)->fromAccount;
            ((Transaction *) dummyListHeadTran->data)->toAccount = ((Transaction *) headTran->data)->toAccount;
            ((Transaction *) dummyListHeadTran->data)->amount = ((Transaction *) headTran->data)->amount;
            // Move to the next transaction
            headTran = headTran->next;
        }
        // Move to the next account
        head = head->next;
    }
    // Reset head pointers
    head = bank->accounts;
    headTran = bank->transactions;
    dummyNewTransaction = NULL;
    // Process instructions
    while (conditionCleared <= 1) {
        // Process sender, receiver, and value for each transaction
        while (conditionCleared == 0) {
            // Extract sender account number
            if (strcmp(senderChar, "-5\0") == 0) {
                senderChar = strtok(strCopy, "-");
            } else {
                senderChar = strtok(NULL, "-");
            }
            // Check if all instructions have been processed
            if (senderChar == NULL) {
                conditionCleared++;
                break;
            }
            // Convert sender account number to an integer
            sender = stringToInt(senderChar);
            // Check if the sender account number is valid
            if (sender == 0) {
                free(str);
                free(strCopy);
                freeDummyMemory(dummyList, dummyListTran);
                return;
            }
            // Extract receiver account number
            receiverChar = strtok(NULL, ":");
            // Check if receiver account number is present
            if (receiverChar == NULL) {
                cleanBuffer(0);
                printf("Invalid instructions\n");
                free(str);
                free(strCopy);
                freeDummyMemory(dummyList, dummyListTran);
                return;
            }
            // Convert receiver account number to an integer
            receiver = stringToInt(receiverChar);
            // Check if the receiver account number is valid
            if (receiver == 0) {
                free(str);
                free(strCopy);
                freeDummyMemory(dummyList, dummyListTran);
                return;
            }
            // Extract value
            valueChar = strtok(NULL, ",");
            // Check if value is present
            if (valueChar == NULL) {
                cleanBuffer(0);
                printf("Invalid instructions\n");
                free(str);
                free(strCopy);
                freeDummyMemory(dummyList, dummyListTran);
                return;
            }
            // Convert value to an integer
            value = stringToInt(valueChar);
            // Check if the value is valid
            if (value == 0) {
                free(str);
                free(strCopy);
                freeDummyMemory(dummyList, dummyListTran);
                return;
            }
            // Check if dummyList is empty
            if (dummyList == NULL) {
                printf("Invalid instructions\n");
                free(str);
                free(strCopy);
                free(dummyList);
                free(dummyListTran);
                return;
            }
            // Reset dummyListHead and dummyListHeadTran
            dummyListHead = dummyList;
            dummyListHeadTran = dummyListTran;
            // Find the sender account in dummyList and process the transaction
            while (dummyListHead->next != NULL) {
                if (((Account *) dummyListHead->data)->accountNumber == sender) {
                    (((Account *) dummyListHead->data)->balance -= value);
                    // Check if the sender has sufficient balance
                    if (((Account *) dummyListHead->data)->balance < 0) {
                        printf("Invalid instructions\n");
                        free(str);
                        free(strCopy);
                        freeDummyMemory(dummyList, dummyListTran);
                        return;
                    }
                    // Create a new transaction node
                    if (dummyNewTransaction == NULL) {
                        dummyNewTransaction = (Node *) malloc(sizeof(Node));
                        dummyNewTransaction->data = malloc(sizeof(Transaction));
                        ((Transaction *) dummyNewTransaction->data)->fromAccount = sender;
                        ((Transaction *) dummyNewTransaction->data)->toAccount = receiver;
                        ((Transaction *) dummyNewTransaction->data)->amount = value;
                        dummyNewTransaction->next = NULL;
                    } else {
                        // Else create a list of dummy transactions to check on them if they are all valid
                        temp = dummyNewTransaction;
                        while (temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp = (Node *) malloc(sizeof(Node));
                        temp->data = malloc(sizeof(Transaction));
                        ((Transaction *) temp->data)->fromAccount = sender;
                        ((Transaction *) temp->data)->toAccount = receiver;
                        ((Transaction *) temp->data)->amount = value;
                        temp->next = NULL;
                    }
                    // Add the new transaction node to dummyListTran
                    if (dummyListHeadTran == NULL) {
                        dummyListHeadTran = dummyNewTransaction;
                    } else {
                        while (dummyListHeadTran->next != NULL) {
                            dummyListHeadTran = dummyListHeadTran->next;
                        }
                        dummyListHeadTran->next = dummyNewTransaction;
                    }
                // Check if the receiver account is present and split the cases to balance 0 or over 0
                } else if (((Account *) dummyListHead->data)->accountNumber == receiver) {
                    if (((Account *) dummyListHead->data)->balance == 0) {
                        ((Account *) dummyListHead->data)->balance = value;
                    } else {
                        ((Account *) dummyListHead->data)->balance += value;
                    }
                // Else the user account number isn't in the database, invalid
                } else {
                    printf("Invalid instructions\n");
                    free(str);
                    free(strCopy);
                    freeDummyMemory(dummyList, dummyListTran);
                    return;
                }
                // Go to the next element in the list unless its NULL
                if (dummyListHead->next != NULL) {
                    dummyListHead = dummyListHead->next;
                }
            }
        }
        // Free memory of dummyList and dummyListTran
        freeDummyMemory(dummyList, dummyListTran);
        // Reset senderChar, head, and headTran for the next iteration
        senderChar = "-5\0";
        head = bank->accounts;
        headTran = bank->transactions;
        // Process transactions with new accounts
        while (conditionCleared == 1) {
            // Extract sender account number
            if (strcmp(senderChar, "-5\0") == 0) {
                senderChar = strtok(str, "-");
            } else {
                senderChar = strtok(NULL, "-");
            }
            // Check if all instructions have been processed
            if (senderChar == NULL) {
                conditionCleared++;
                printf("Instructions executed successfully\n");
                continue;
            }
            // Convert sender account number to an integer
            sender = stringToInt(senderChar);
            // Extract receiver account number
            receiverChar = strtok(NULL, ":");
            // Convert receiver account number to an integer
            receiver = stringToInt(receiverChar);
            // Extract value
            valueChar = strtok(NULL, ",");
            // Convert value to an integer
            value = stringToInt(valueChar);
            // Reset head for account traversal
            head = bank->accounts;
            // Find the sender account and process the transaction
            while (head != NULL) {
                if (((Account *) head->data)->accountNumber == sender) {
                    (((Account *) head->data)->balance -= value);
                    // Create a new transaction node
                    newTransaction = (Node *) malloc(sizeof(Node));
                    newTransaction->data = malloc(sizeof(Transaction));
                    ((Transaction *) newTransaction->data)->fromAccount = sender;
                    ((Transaction *) newTransaction->data)->toAccount = receiver;
                    ((Transaction *) newTransaction->data)->amount = value;
                    newTransaction->next = NULL;
                    // Add the new transaction node to the transaction list
                    if (bank->transactions == NULL) {
                        bank->transactions = newTransaction;
                    } else {
                        // Using temp again setting it to the transactions database head
                        temp = bank->transactions;
                        while (temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = newTransaction;
                    }
                // Find the receiver account and process the transaction
                } else if (((Account *) head->data)->accountNumber == receiver) {
                    if (((Account *) head->data)->balance == 0) {
                        ((Account *) head->data)->balance = value;
                    } else {
                        ((Account *) head->data)->balance += value;
                    }
                }
                // Move to the next account
                head = head->next;
            }
        }
    }
    // Free memory of str and strCopy
    free(str);
    free(strCopy);
}


/**
 * @brief Converts a string to an integer.
 *
 * @param turnToNumber The string to convert.
 * @return The converted integer if the string is a valid number, -1 otherwise.
 */
int stringToInt(char *turnToNumber) {
    // Declare variables
    char *endptr;
    long number;
    // Convert the string to a long integer
    number = strtol(turnToNumber, &endptr, DECIMAL_BASE);
    // Check if conversion was successful
    if (*endptr == '\0') {
        // Return the converted integer
        return number;
    } else {
        // Return 0 to indicate an error in conversion
        return 0;
    }
}


/**
 * @brief Reads a string from the user.
 *
 * @return The dynamically allocated string.
 */
char *makeString() {
    // Declare variables
    char *string;
    char character;
    int length = 0, count = 1;
    // Read the first character
    scanf("%c", &character);
    // Allocate memory for the string
    string = (char *) malloc(sizeof(char) * count + 1);
    // Read characters until a newline is encountered
    while (character != '\n') {
        // Store the character in the string
        string[length] = character;
        // Increment the length counter
        length++;
        // Check if the allocated memory is sufficient
        if (length >= SIZE_OF_CHAR * count) {
            // Increase the memory size
            count++;
            string = (char *) realloc(string, sizeof(char) * count + 1);
            // Check if memory reallocation was successful
            if (string == NULL) {
                free(string);
                exit(1);
            }
        }
        // Read the next character
        scanf("%c", &character);
    }
    // Add null terminator to mark the end of the string
    string[length] = '\0';
    // Return the dynamically allocated string
    return string;
}


/**
 * @brief Reads a transaction string from the user.
 *
 * @return The dynamically allocated transaction string.
 */
char *makeStringTransactions() {
    // Declare a pointer to char to store the string
    char *string;
    // Declare a variable to store each character
    char character;
    // Declare and initialize some counters
    int length = 0, count = 1, countHyphens = 0, countColons = 0, countComas = 0, counter = 0;
    // Assuming there's a function to clean the input buffer
    cleanBuffer(0);
    // Read the first character
    scanf("%c", &character);
    if (character < '0' || character > '9') {
        // If the first character is not a digit, return "-1"
        return "-1\0";
    }
    // Allocate memory for the string
    string = (char *) malloc(sizeof(char) * count + 1);
    // Continue reading characters until a newline is encountered
    while (character != '\n') {
        if (character == '-') {
            // Count the number of hyphens encountered
            countHyphens++;
            if (countHyphens > 1) {
                free(string);
                // If more than one hyphen is encountered, return "-1"
                return "-1\0";
            }
        } else if (character == ':') {
            // Count the number of colons encountered
            countColons++;
            if (countColons > 1) {
                free(string);
                // If more than one colon is encountered, return "-1"
                return "-1\0";
            }
        } else if (character == ',') {
            countHyphens = 0;
            countColons = 0;
            // Count the number of commas encountered
            countComas++;
            if (countComas >= 1) {
                while (character == ',') {
                    // Skip consecutive commas
                    scanf("%c", &character);
                }
                // Increment the counter to add a comma after skipping
                counter++;
                countComas = 0;
            }
        } else if (character < '0' || character > '9') {
            if ((character != ',') && (character != '-') && (character != ':') & (character != ' ')) {
                // If a non-digit, non-space, non-comma, non-hyphen, non-colon character is encountered, return "-1"
                return "-1\0";
            }
        }
        if (counter >= 1) {
            // Add a comma if the counter is at least 1
            string[length] = ',';
            length++;
            counter = 0;
        }
        // Add the character to the string
        string[length] = character;
        length++;
        // Check if the allocated memory is not enough
        if (length >= SIZE_OF_CHAR * count) {
            // Increase the size counter
            count++;
            // Reallocate memory
            string = (char *) realloc(string, sizeof(char) * count + 1);
            if (string == NULL) {
                free(string);
                // If memory allocation fails, exit the program
                exit(1);
            }
        }
        // Read the next character
        scanf("%c", &character);
    }
    // Add the null-terminating character
    string[length] = '\0';
    // Return the final string
    return string;
}


/**
 * @brief Displays account information for a given account number.
 *
 * @param bank The bank structure.
 */
void viewAccount(Bank *bank) {
    // Declare variables to store the account number and count
    unsigned int insertNum, count = 0;
    // Declare pointers to nodes
    Node *head, *headTran;
    printf("Enter account number:\n");
    // Read the account number from the user
    scanf("%d", &insertNum);
    // Get the head node of the accounts linked list
    head = bank->accounts;
    // Get the head node of the transactions linked list
    headTran = bank->transactions;
    // Traverse the accounts linked list
    while (head != NULL) {
        // Check if the current account number matches the input
        if (((Account *) head->data)->accountNumber == insertNum) {
            // Increment the count if a match is found
            count++;
            // Print the account details
            printf("Account #%u (%s)\n", insertNum, ((Account *) head->data)->accountHolder);
            printf("Balance: %d\n", ((Account *) head->data)->balance);
            // Check if the balance is zero
            if (((Account *) head->data)->balance == 0) {
                // Traverse the transactions linked list
                while (headTran != NULL) {
                    if (((Transaction *) headTran->data)->toAccount == insertNum ||
                        ((Transaction *) headTran->data)->fromAccount == insertNum) {
                        // Break the loop if a transaction involving the account is found
                        break;
                    }
                    headTran = headTran->next;
                }
                // Print a message indicating no transactions
                printf("No transactions\n");
                // Return from the function
                return;
            }
        }
        // Move to the next node in the accounts linked list
        head = head->next;
    }
    if (count == 0) {
        // Print a message indicating the account was not found
        printf("Account not found\n");
        // Return from the function
        return;
    }
    // Print a header for the transactions
    printf("Transactions:\n");
    // Traverse the transactions linked list
    while (headTran != NULL) {
        // Check if the transaction is a deposit to the account
        if (((Transaction *) headTran->data)->toAccount == insertNum) {
            if (((Transaction *) headTran->data)->fromAccount == 0) {
                // Print the deposit amount
                printf("Deposited %d\n", ((Transaction *) headTran->data)->amount);
            } else {
                // Print the transaction amount and the source account
                printf("%d from %u\n", ((Transaction *) headTran->data)->amount,
                       ((Transaction *) headTran->data)->fromAccount);
            }
        // Check if the transaction is a withdrawal from the account
        } else if (((Transaction *) headTran->data)->fromAccount == insertNum) {
            if (((Transaction *) headTran->data)->toAccount == 0) {
                // Print the withdrawal amount
                printf("Withdrew %d\n", ((Transaction *) headTran->data)->amount);
            } else {
                // Print the transaction amount and the destination account
                printf("%d to %u\n", ((Transaction *) headTran->data)->amount,
                       ((Transaction *) headTran->data)->toAccount);
            }
        }
        // Move to the next node in the transactions linked list
        headTran = headTran->next;
    }
}


void freeDummyMemory(Node *dummyList, Node *dummyListTran) {
    // Declare a temporary node pointer
    Node *temp;
    // Check if dummyList and dummyListTran are different
    if (dummyList != dummyListTran) {
        // Traverse dummyList
        while (dummyList != NULL) {
            // Store the current node in temp
            temp = dummyList;
            // Move to the next node
            dummyList = dummyList->next;
            // Free the memory allocated for the data of the current node
            free(temp->data);
            // Free the memory of the current node
            free(temp);
        }
        // Same as first while loop but for the transactions
        while (dummyListTran != NULL) {
            temp = dummyListTran;
            dummyListTran = dummyListTran->next;
            free(temp->data);
            free(temp);
        }
    } else {
        // If the lists address is the same address free only once, same as before
        while (dummyList != NULL) {
            temp = dummyList;
            dummyList = dummyList->next;
            free(temp->data);
            free(temp);
        }
    }
}
