#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <regex.h>

#define MAX 1000

// accounts number aka size of array
int SIZE = 1;

// Date struct
typedef struct
{
    int month;
    int year;
} date;

// account struct
typedef struct
{
    char account_number[11];
    char name[30];
    char email_address[30];
    float balance;
    char phone_number[12];
    date account_oppened;
} account;


// our main array of accounts
account* accounts;

// print account "index" of account (done)
void print_acc(int idx)
{
    if (idx == -1)
    {
        printf("Account not found\n");
        return;
    }
    char *month_str;
    switch (accounts[idx].account_oppened.month)
    {
        case 1:
            month_str = "January";
            break;
        case 2:
            month_str = "February";
            break;
        case 3:
            month_str = "March";
            break;
        case 4:
            month_str = "April";
            break;
        case 5:
            month_str = "May";
            break;
        case 6:
            month_str = "June";
            break;
        case 7:
            month_str = "July";
            break;
        case 8:
            month_str = "August";
            break;
        case 9:
            month_str = "September";
            break;
        case 10:
            month_str = "October";
            break;
        case 11:
            month_str = "November";
            break;
        case 12:
            month_str = "December";
            break;
        default:
            printf("Invalid month number\n");
            return;
    }
    printf("Account Number: %s\nName: %s\nE-mail: %s\nBalance: %.2f $\nMobile: %s\nDate Opened: %s %d\n",
           accounts[idx].account_number, accounts[idx].name, accounts[idx].email_address, accounts[idx].balance, accounts[idx].phone_number, month_str, accounts[idx].account_oppened.year);
}

// return 1 if the first date is grater (2004)
// return -1 if the first date is smaller (2003)
// return 0 if same date    (done)
int datecmp(date date1,date date2)
{
    if(date1.year > date2.year)
    {
        return 1;
    }
    if(date1.year < date2.year)
    {
        return -1;
    }
    if(date1.year == date2.year)
    {
        if(date1.month > date2.month)
        {
            return 1;
        }
        if(date1.month < date2.month)
        {
            return -1;
        }
    }
    return 0;
}

//(done)
void sortByName()
{
    // merge sort
    int i,j=1,flag=0;
    account temp;
    while(!flag)
    {
        flag = 1;
        for (i = 0; i < SIZE-j; i++)
        {
            if(strcmp(accounts[i].name,accounts[i+1].name)>0)
            {
                flag = 0;
                temp = accounts[i];
                accounts[i] = accounts[i + 1];
                accounts[i + 1] = temp;
            }
        }
        j++; // to skip the sorted elements
    }
}

//(done)
void SortByDate()
{
    // merge sort
    int i,j=1,flag=0;
    account temp;
    while(!flag)
    {
        flag = 1;
        for (i = 0; i < SIZE-j; i++)
        {
            if(datecmp(accounts[i].account_oppened,accounts[i+1].account_oppened)<0)
            {
                flag = 0;
                temp = accounts[i];
                accounts[i] = accounts[i + 1];
                accounts[i + 1] = temp;
            }
        }
        j++; // to skip the sorted elements
    }
}

// (done)
void SortByBalance()
{
    // merge sort
    int i,j=1,flag=0;
    account temp;
    while(!flag)
    {
        flag = 1;
        for (i = 0; i < SIZE-j; i++)
        {
            if(accounts[i].balance > accounts[i+1].balance)
            {
                flag = 0;
                temp = accounts[i];
                accounts[i] = accounts[i + 1];
                accounts[i + 1] = temp;
            }
        }
        j++; // to skip the sorted elements
    }
}

/* search by account number as a "string"
return the index of required account
if not exist returns -1 (done) */
int QSearch(char *acc_num)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        if (!strcmp(accounts[i].account_number, acc_num))
        {
            return i;
        }
    }
    return -1;
}

void ASearch()
{
    char keyword[20];
    printf("Enter keyword: ");
    scanf("%s", keyword);

    int i = 0, flag = 0;
    char name[50];
    printf("\nSearch results: \n");
    for (; i < SIZE; i++)
    {
        strcpy(name, accounts[i].name);
        char *result = strstr(name, keyword);
        if (result)
        {
            flag = 1;
            print_acc(i);
            printf("\n");
        }

    }
    if (!flag)
    {
        printf("no matches are found\n");
    }
}

// delete a struct by account number as a "string" scanned in the function (done)
void DELETE()
{
    char acc_num[11];
    printf("Please enter the account number: ");
    scanf("%s", acc_num);
    char confirm;
    int idx = QSearch(acc_num);
    // Check for valid index
    if (idx == -1)
    {
        printf("account not found");
        return;
    }
    if (accounts[idx].balance < 0.01)
    {
        printf("confirm deleting your account(Y/N):");
        scanf(" %c", &confirm);
        confirm = toupper(confirm);
        if (confirm == 'Y')
        {
            // Shift all elements after the deleted one to the left
            for (int i = idx; i < SIZE - 1; i++)
            {
                accounts[i] = accounts[i + 1];
            }
            // Reduce the array size
            SIZE--;
            accounts = realloc(accounts, SIZE);
            printf("Account is deleted successfully\n");
        }
        else
        {
            printf("Account deletion is declined \n");
        }
    }
    else
    {
        printf("you can't delete your account because your balance is %.2f \n", accounts[idx].balance);
    }
}

// load from file to array of struct "accounts" (done)
// return 1 if file correctly opend
// return -1 if false
int LOAD()
{
    FILE *f = fopen("accounts.txt", "r");
    if (!f)
    {
        return -1; // did not open
    }
    int i = 0;
    char c;
    while (!feof(f))
    {
        c = getc(f);
        if (c == '\n')
            SIZE ++;
    }
    char line[100];
    char *dilem = ",-";
    accounts = malloc(SIZE * sizeof(account));
    fseek(f, 0, SEEK_SET);
    while (!feof(f))
    {
        // get the line
        fgets(line, 100, f);

        // account number
        char *tok = strtok(line, dilem);
        strcpy(accounts[i].account_number, tok);

        // name
        tok = strtok(NULL, dilem);
        strcpy(accounts[i].name, tok);

        // E-mail
        tok = strtok(NULL, dilem);
        strcpy(accounts[i].email_address, tok);

        // balance
        tok = strtok(NULL, dilem);
        accounts[i].balance = atof(tok);

        // phone number
        tok = strtok(NULL, dilem);
        strcpy(accounts[i].phone_number, tok);

        // date
        // month
        tok = strtok(NULL, dilem);
        accounts[i].account_oppened.month = atoi(tok);
        //      year
        tok = strtok(NULL, dilem);
        accounts[i].account_oppened.year = atoi(tok);

        i++;
    }

    fclose(f);
    return i;
}

// login from users file (done)
int LOGIN()
{
    char username[100];
    char username_cpy[100];
    char password[50];
    char password_ds[100]; // username and password form Data Set
    printf("Enter the username: ");
    getchar();
    fgets(username, MAX, stdin);
    username[strcspn(username, "\n")] = '\0'; // to remove the new line character
    strcpy(username_cpy, username);
    printf("Enter the password: ");
    fgets(password, MAX, stdin);
    password[strcspn(password, "\n")] = '\0'; // to remove the new line character
    strcat(username, " ");
    strcat(username, password);
    strcat(username, "\r\n");

    FILE *f = fopen("users.txt", "r");
    if (f==NULL)
    {
        printf("File not found");
        return -1;
    }
    while (fgets(password_ds, MAX, f))
    {
        if (!strcmp(username, password_ds))
        {
            printf("Login successful.\n");
            printf("-----------\n");
            printf("\nWelcome: %s\n", username_cpy);
            fclose(f);
            return 1;
        }
    }
    printf("Invalid login credentials, please try again\n");
    fclose(f);
    return 0;
}

// modify account by account number as a "string" scanned in the function (done)
void MODIFY()
{
    char acc_num[11];
    printf("Enter Account Number: ");
    scanf("%s", acc_num);
    int index = QSearch(acc_num);
    if (index == -1)
    {
        printf("Account not found!");
        return;
    }
    printf("Account details:\n");
    printf("Name: %s\n", accounts[index].name);
    printf("Mobile: %s\n", accounts[index].phone_number);
    printf("Email: %s\n", accounts[index].email_address);
    printf("---------------------\n");

    printf("Enter new name: ");
    getchar();
    fgets(accounts[index].name, MAX, stdin);
    accounts[index].name[strcspn(accounts[index].name, "\n")] = '\0';

    printf("Enter new mobile number: ");
    fgets(accounts[index].phone_number, 12, stdin);
    accounts[index].phone_number[strcspn(accounts[index].phone_number, "\n")] = '\0';

    printf("Enter new email address: ");
    getchar();
    fgets(accounts[index].email_address, MAX, stdin);
    accounts[index].email_address[strcspn(accounts[index].email_address, "\n")] = '\0';

    printf("Account details updated successfully.\n");

    return;
}

// saves transactions in the account file by account number as a "string"
// indentifies each transaction by index [ 1 - d / 2- w / 3- t / 4- r ]
// takes the amount from the function
// ! naming !
void save_transaction(char *acc_num, float amount, int idx)
{
    char acc_num_copy[15];
    strcpy(acc_num_copy, acc_num);
    strcat(acc_num_copy, ".txt");

    FILE *f1 = fopen(acc_num_copy, "a");
    if (f1 == NULL)
    {
        printf("Error opening file"); // for us to understand , will be edited for the user later.
        return;
    }

    if (idx == 1)
    {
        fprintf(f1, "deposited - %.2f\n", amount);
    }
    else if (idx == 2)
    {
        fprintf(f1, "withdrawn - %.2f\n", amount);
    }
    else if (idx == 3)
    {
        fprintf(f1, "transferred - %.2f\n", amount);
    }
    else if (idx == 4)
    {
        fprintf(f1, "received - %.2f\n", amount);
    }

    fclose(f1);
}

// deposit by account number as a "string" scanned in the function (done)
void DEPOSIT()
{
    char acc_num[11];
    printf("Please enter the account number: ");
    int x = scanf("%s", acc_num);
    if (!x)
        printf("Invalid account number.");
    float amount;
    int idx = QSearch(acc_num); // find the account index
    if (idx == -1)
    {
        printf("Account not found.\n");
        return;
    }
    do
    {
        printf("Enter amount to deposit: ");
        scanf("%f", &amount);
        if (!x)
            printf("Invalid amount.");

        if (amount > 10000)
        {
            printf("Deposit not successful because the amount exceeds maximum limit of $10,000$, please enter another amount\n");
        }
        else
        {
            accounts[idx].balance += amount; // update the account balance
            printf("Deposit successful. New balance: %.2f$\n", accounts[idx].balance);
            save_transaction(acc_num, amount, 1);
            printf("--------------------\n");
            return;
        }
    }
    while (1);
}

// withdraw by account number as a "string" scanned in the function (done)
void WITHDRAW()
{
    char acc_num[11];
    printf("Please enter the account number: ");
    scanf("%s", acc_num);

    float amount;
    int idx = QSearch(acc_num); // find the account index
    if (idx == -1)
    {
        printf("Account not found.\n");
        return;
    }

    do
    {
        printf("Enter amount to withdraw: ");
        int x = scanf("%f", &amount);
        if (!x)
            printf("Invalid amount");

        if (amount > 10000)
        {
            printf("Withdrawal not successful because the amount exceeds maximum limit of 10,000$, please enter another amount\n");
        }
        else if (amount > accounts[idx].balance)
        {
            printf("Withdrawal not successful because the amount exceeds your account balance, please enter another amount\n");
        }
        else
        {
            accounts[idx].balance -= amount; // update the account balance
            printf("Withdraw successful. New balance: %.2f$\n", accounts[idx].balance);

            save_transaction(acc_num, amount, 2);
            printf("--------------------\n");
            return;
        }
    }
    while (1);
}

// transfer money by account numbers as "strings" scanned in the function (done)
void TRANSFER()
{
    char acc_num1[11];
    printf("Please enter the account number of the sender: ");
    scanf("%s", acc_num1);
    char acc_num2[11];
    printf("Please enter the account number of the receiver: ");
    scanf("%s", acc_num2);
    float amount;
    int idx1 = QSearch(acc_num1), idx2 = QSearch(acc_num2);
    if (idx1 == -1)
    {
        printf("Account of the sender not found\n");
        return;
    }
    else if (idx2 == -1)
    {
        printf("Account of the receiver not found\n");
        return;
    }

    printf("Enter amount to be transferred: ");
    int x = scanf("%f", &amount);
    if (!x)
    {
        printf("Invalid amount.");
        return ;
    }

    if (accounts[idx1].balance >= amount)
    {
        accounts[idx1].balance -= amount; // update the account balance of sender
        accounts[idx2].balance += amount; // update the account balance of receiver
        printf("Transfer successful. New balance for sender: %.2f\t New balance for receiver: %.2f\n", accounts[idx1].balance, accounts[idx2].balance);
        printf("--------------------\n");
        save_transaction(acc_num1, amount, 3);
        save_transaction(acc_num2, amount, 4);
    }
    else
    {
        printf("Transfer not successful because the amount exceeds the account balance of the sender %s\n", acc_num1);
    }
}

// Function report asks for account number and prints the last 5 transactions
void REPORT()
{
    char acc_num[20];
    int length = 0, idx = 0;
    char buffer[200];
    printf("Enter the account number:");
    getchar();
    fgets(acc_num, sizeof(acc_num), stdin);
    acc_num[strcspn(acc_num, "\n")] = '\0';
    strcat(acc_num, ".txt");


    FILE *f = fopen(acc_num, "r");
    if (f == NULL)
    {
        printf("File Not Found");
        return;
    }

    while (fgets(buffer, sizeof(buffer), f))   // To get the length of the file
    {
        length++;
    }

    rewind(f); // rewinds the pointer to the first line

    if (length <= 5)   // If the account has exactly 5 transactions or fewer
    {
        while (fgets(buffer, sizeof(buffer), f))
            printf("%s", buffer);
    }
    else
    {
        while (fgets(buffer, sizeof(buffer), f))
        {
            idx++;
            if (idx > (length - 5))
                printf("%s", buffer);
        }
    }
    fclose(f);
}


// (done)
int isAccountNumber(char* account_number)
{
    int i;
    if (strlen(account_number) != 10)
    {
        printf("Invalid account number.\n");
        return 0;
    }
    for (i = 0; i < SIZE-1; i++)
    {
        if (!strcmp(accounts[i].account_number, account_number))
        {
            printf("Account number already exist.");
            return 0;
        }
    }
    for (i=0; i<10; i++)
    {
        if (account_number[i] < '0' || account_number[i] > '9')
        {
            printf("Invalid account number.\n");
            return 0;
        }
    }
    return 1;
}

// (done)
int isPhoneNumber(char* phone_number)
{
    // checking the number length
    if(strlen(phone_number)!=11)
    {
        printf("\tInvalid phone number.\n");
        return 0;
    }
    if (phone_number[0] != '0' || phone_number[1] != '1')
    {
        printf("\tInvalid phone number.\n");
        return 0;
    }
    if (!(phone_number[2] == '0' || phone_number[2] == '1' || phone_number[2] == '2'|| phone_number[2] == '5' ))
    {
        printf("\tInvalid phone number.\n");
        getchar();
        return 0;
    }
    int i;
    for (i=3; i<11; i++)
    {
        if (phone_number[i]<'0' || phone_number[i]>'9')
        {
            printf("\tInvalid phone number.\n");
            return 0;
        }
    }
        return 1;
}

// (done)

int isName(char name[])
{
    int re;
    regex_t rgx;
    re = regcomp(&rgx, "^[[:upper:]][[:lower:]]* [[:upper:]][[:lower:]]*$", 0);
    re = regexec(&rgx, name, 0, NULL, 0);
    if ((!re)==0)
        printf("\tInvalid name. Please enter client's first and last name separated by a single space and each begins with a capital letter.\n ");
    return !re;
}


int isEmailAddress (char* email_address)
{
    int re, size;
    regex_t rgx;
    size = strlen(email_address);
    if (size > 0 && email_address[size-1] == '\n')
        email_address[size-1] = '\0';
    re = regcomp(&rgx, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$", REG_EXTENDED);
    re = regexec(&rgx, email_address, 0, NULL, 0);
    if(re == REG_NOMATCH)
        printf("\tInvalid email\n");
    return !re;
}

// (done)
int isBalance(int flag)
{
    if (flag == 0)
        printf("\tInvalid Balance.\n");
    return flag;
}

void ADD()
{
    FILE* fptr = fopen("accounts.txt", "a");
    time_t t =time(NULL);
    struct tm dt = *localtime(&t);
    int flag;
    SIZE ++;
    accounts = realloc(accounts, SIZE * sizeof(account));
    printf("Enter account data:-\n");
    do
    {
        printf("\tEnter account number:\t");
        scanf("%s", accounts[SIZE - 1].account_number);
        while (getchar() != '\n');
    }
    while(!isAccountNumber(accounts[SIZE - 1].account_number));
    do{
        printf("\tEnter name:\t");
        fgets(accounts[SIZE - 1].name, sizeof(accounts[SIZE - 1].name), stdin);
        accounts[SIZE - 1].name[strcspn(accounts[SIZE - 1].name, "\n")] = '\0';
    } while (!isName(accounts[SIZE - 1].name));
    do{
        printf("\tEnter email address:\t");
        fgets(accounts[SIZE - 1].email_address, sizeof(accounts[SIZE - 1].email_address), stdin);
        accounts[SIZE - 1].email_address[strcspn(accounts[SIZE - 1].email_address, "\n")] = '\0';
    } while(!isEmailAddress(accounts[SIZE - 1].email_address));
    do
    {
        printf("\tEnter mobile number:\t");
        fgets(accounts[SIZE - 1].phone_number, sizeof(accounts[SIZE - 1].phone_number), stdin);
        accounts[SIZE - 1].phone_number[strcspn(accounts[SIZE - 1].phone_number, "\n")] = '\0';
    }
    while (!isPhoneNumber(accounts[SIZE - 1].phone_number));
    do
    {
        printf("\tEnter balance:\t");
        flag = scanf("%f", &accounts[SIZE - 1].balance);
        getchar();
    }
    while (!isBalance(flag));
    accounts[SIZE - 1].account_oppened.month = dt.tm_mon +1;
    accounts[SIZE - 1].account_oppened.year = dt.tm_year +1900;
    fclose(fptr);
}

void QUIT()
{
    printf("Thank you for banking with us.");
    free(accounts);
    exit(1);
}
// propmts the user for choice and loops till the user quits the program

void SAVE()
{
    int idx;
    FILE *f = fopen("accounts.txt","w");
    if (f==NULL) {
        printf("File not found");
        return;
    }
    for (idx=0 ; idx < SIZE ; idx++) {
        fprintf(f, "%s,%s,%s,%.2f,%s,%d-%d",accounts[idx].account_number, accounts[idx].name, accounts[idx].email_address, accounts[idx].balance, accounts[idx].phone_number, accounts[idx].account_oppened.month, accounts[idx].account_oppened.year);
        if(idx < (SIZE-1)){
            fprintf(f, "\n");
        }
    }
    
    fclose(f);
}

void MENU()
{
    int choice, answer, flag, logged_in = 0;

    while (1)
    {
        if (!logged_in)
        {
            printf("\nWelcome:\n");
            printf("1. LOGIN\n");
            printf("2. QUIT\n");
        }
        else
        {
            printf("----------");
            printf("\nMenu:\n");
            printf("1. ADD\n");
            printf("2. DELETE\n");
            printf("3. MODIFY\n");
            printf("4. SEARCH\n");
            printf("5. ADVANCED SEARCH\n");
            printf("6. WITHDRAW\n");
            printf("7. DEPOSIT\n");
            printf("8. TRANSFER\n");
            printf("9. REPORT\n");
            printf("10. PRINT\n");
            printf("11. QUIT\n");
        }
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (!logged_in) // if not logged in and the user chooses to quit
        {
            if (choice == 2)
            {
                choice = 11; // easier to make one switch case for quitting
            }
        }

        switch (choice)
        {
            case 1:// if logged in -> Add     if not logged in -> Login then Load accounts
                if ((!logged_in))
                {
                    // Perform login logic here
                    if (LOGIN())
                    {
                        LOAD(); // Load data if login is successful
                        logged_in = 1;
                    }
                }
                else
                {
                    ADD();
                }
                break;
            case 2: // Delete
                if (logged_in)
                {
                    DELETE();
                }
                break;
            case 3: // Modify
                if (logged_in)
                {
                    MODIFY();
                }
                break;
            case 4: // Query Search
                if (logged_in)
                {
                    char acc_num[11];
                    printf("Please enter the account number: ");
                    scanf("%s", acc_num);
                    print_acc(QSearch(acc_num));
                }
                break;
            case 5: // Advanced Search
                if (logged_in)
                {
                    ASearch();
                }
                break;

            case 6: // Withdraw
                if (logged_in)
                {
                    WITHDRAW();
                }
                break;
            case 7: // Deposit
                if (logged_in)
                {
                    DEPOSIT();
                }
                break;
            case 8: // Transfer
                if (logged_in)
                {
                    TRANSFER();
                }
                break;

            case 9: // Report
                if (logged_in)
                {
                    REPORT();
                }
                break;
            case 10: // Print
                if (logged_in)
                {
                    flag = 0;
                    while (!flag)
                    {
                        printf("Choose how would you like the data to be printed:\n");
                        printf("1. Sorted by name\n");
                        printf("2. Sorted by date\n");
                        printf("3. Sorted by balance\n");
                        printf("Enter your choice: ");
                        scanf("%d", &answer);
                        switch (answer)
                        {
                            case 1:
                                sortByName();
                                int i;
                                for (i = 0; i < SIZE; i++)
                                {
                                    print_acc(i);
                                    printf("-----------------\n");
                                }
                                flag = 1;
                                break;
                            case 2:
                                SortByDate();
                                int j;
                                for (j = 0; j < SIZE; j++)
                                {
                                    print_acc(j);
                                    printf("-----------------\n");
                                }
                                flag = 1;
                                break;
                            case 3:
                                SortByBalance();
                                int k;
                                for (k = 0; k < SIZE; k++)
                                {
                                    print_acc(k);
                                    printf("-----------------\n");
                                }
                                flag = 1;
                                break;
                            default:
                                printf("Invalid choice, please try again.\n");
                                break;
                        }
                    }
                }
                break;
            case 11: // Quit
                SAVE();
                QUIT();
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
}


int main()
{
    MENU();
    //LOAD();
    //SAVE();
}
