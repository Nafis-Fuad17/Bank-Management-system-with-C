#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct
{
    char customerName[100];
    int accountNumber;
    double balance;
} BankInfo;

int ReadAccountsNumber(BankInfo accounts[])
{
    int numAccounts = 0;
    FILE *file;
    file = fopen("Bankfile.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
    }

    while (fscanf(file, "%d,%[^,],%lf\n", &accounts[numAccounts].accountNumber, &accounts[numAccounts].customerName,
                  &accounts[numAccounts].balance) == 3)
    {
        numAccounts++;
    }

    fclose(file);
    return numAccounts;
}

void SaveAccounts(BankInfo accounts[], int numAccounts)
{
    FILE *file;
    file = fopen("Bankfile.txt", "w");

    for (int i = 0; i < numAccounts; i++)
    {
        fprintf(file, "%d,%s,%.2f\n", accounts[i].accountNumber, accounts[i].customerName, accounts[i].balance);
    }

    fclose(file);
}

void AccountCreate(BankInfo accounts[], int *numAccounts);
void DepositMoney(BankInfo accounts[], int numAccounts);
void WithdrawMoney(BankInfo accounts[], int numAccounts);
void CheckBalance(BankInfo accounts[], int numAccounts);
void TransferMoney(BankInfo accounts[], int numAccounts);
void PrintStatement(BankInfo accounts[], int numAccounts);
void ChangeAccountName(BankInfo accounts[], int numAccounts);
void DeleteAccount(BankInfo accounts[], int *numAccounts);
void ViewAllAccounts(BankInfo accounts[], int numAccounts);

int main()
{
    BankInfo accounts[MAX_ACCOUNTS];
    int numAccounts = ReadAccountsNumber(accounts);
    int choice;
    int k=0;
    char username[99];
    char password[99];

    char definedUsername[99] = "admin";
    char definedPassword[99] = "password";

    printf("Welcome to the Login Panel of NSN Bank Ltd.\n");
    do
    {

        printf("Enter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        if (strcmp(username, definedUsername) == 0 && strcmp(password, definedPassword) == 0)
        {
            printf("Login successful!\n");
            do
            {
                printf("\n***************************\n");
                printf("\n     NSN BANK LTD.                \n");
                printf("\n");
                printf("\n   MANAGEMENT SYSTEM         \n");
                printf("\n***************************\n");
                printf("1. Let's Create an Account\n");
                printf("2. Deposit Money\n");
                printf("3. Withdraw Money\n");
                printf("4. Check Balance\n");
                printf("5. Transfer Balance\n");
                printf("6. Print Bank Statement\n");
                printf("7. Change Account Holder's name\n");
                printf("8. Delete Account\n");
                printf("9. View All Accounts\n");
                printf("0. Exit\n");
                printf("Enter your choice to proceed: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    AccountCreate(accounts, &numAccounts);
                    SaveAccounts(accounts, numAccounts);
                    break;
                case 2:
                    DepositMoney(accounts, numAccounts);
                    SaveAccounts(accounts, numAccounts);
                    break;
                case 3:
                    WithdrawMoney(accounts, numAccounts);
                    SaveAccounts(accounts, numAccounts);
                    break;
                case 4:
                    CheckBalance(accounts, numAccounts);
                    break;
                case 5:
                    TransferMoney(accounts, numAccounts);
                    SaveAccounts(accounts, numAccounts);
                    break;
                case 6:
                    PrintStatement(accounts, numAccounts);
                    break;
                case 7:
                    ChangeAccountName(accounts, numAccounts);
                    SaveAccounts(accounts, numAccounts);
                    break;
                case 8:
                    DeleteAccount(accounts, &numAccounts);
                    SaveAccounts(accounts, numAccounts);
                    break;
                case 9:
                    ViewAllAccounts(accounts, numAccounts);
                    break;
                case 0:
                    printf("Exiting the program. Thank you!\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                }
            }
            while (choice != 0);

        }
        else
        {
            printf("Login failed because of invalid username or password.\a\n");
            printf("\t\tTry again if you want...\n");
            k++;
        }
    }
    while(k!=0);


    getch();
    return 0;
}

void AccountCreate(BankInfo accounts[], int *numAccounts)
{
    if (*numAccounts >= MAX_ACCOUNTS)
    {
        printf("Maximum number of accounts reached.\n");
        return;
     }

    BankInfo newAccount;

    printf("Enter new account number: ");
    scanf("%d", &newAccount.accountNumber);

    for (int i = 0; i < *numAccounts; i++)
    {
        if (accounts[i].accountNumber == newAccount.accountNumber)
        {
            printf("Account number already exists.\n");
            return;
        }
    }


    printf("Enter new customer name: ");
    fflush(stdin);
    gets(newAccount.customerName);

    printf("Enter first deposit amount: ");
    scanf("%lf", &newAccount.balance);

    accounts[*numAccounts] = newAccount;
    (*numAccounts)++;

    printf("Account of %s created successfully.\n",newAccount.customerName);

}

void DepositMoney(BankInfo accounts[], int numAccounts)
{
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int accountIndex = -1;
    for (int i = 0; i < numAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Account not found.\n");
        return;

    }

    printf("Enter deposit amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid deposit amount.\n");
        return;

    }

    accounts[accountIndex].balance += amount;
    printf("Amount has been deposited successfully to %s's account.\n",accounts[accountIndex].customerName);
    printf("New balance: %.2f\n",accounts[accountIndex].balance);
}

void WithdrawMoney(BankInfo accounts[], int numAccounts)
{
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int accountIndex = -1;
    for (int i = 0; i < numAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Enter request of withdrawal amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid withdrawal amount.\n");
        return;
    }

    if (amount > accounts[accountIndex].balance)
    {
        printf("Insufficient balance.\n");
        return;
    }

    accounts[accountIndex].balance -= amount;
    printf("Amount has been withdrawn successfully from %s's account.\n",accounts[accountIndex].customerName);
    printf("New balance: %.2f\n", accounts[accountIndex].balance);
}

void CheckBalance(BankInfo accounts[], int numAccounts)
{
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int accountIndex = -1;
    for (int i = 0; i < numAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Account not found.\n");
        return;
    }
    else
        printf("Account balance: %.2f\n", accounts[accountIndex].balance);
}

void TransferMoney(BankInfo accounts[], int numAccounts)
{
    int senderAccountNumber, receiverAccountNumber;
    double amount;

    printf("Enter sender's account number: ");
    scanf("%d", &senderAccountNumber);

    int senderAccountIndex = -1;
    for (int i = 0; i < numAccounts; i++)
    {
        if (accounts[i].accountNumber == senderAccountNumber)
        {
            senderAccountIndex = i;
            break;
        }
    }

    if (senderAccountIndex == -1)
    {
        printf("Sender's account not found.\n");
        return;
    }

    printf("Enter receiver's account number: ");
    scanf("%d", &receiverAccountNumber);

    int receiverAccountIndex = -1;
    for (int i = 0; i < numAccounts; i++)
    {
        if (accounts[i].accountNumber == receiverAccountNumber)
        {
            receiverAccountIndex = i;
            break;
        }
    }

    if (receiverAccountIndex == -1)
    {
        printf("Receiver's account not found.\n");
        return;
    }

    printf("Enter transfer amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid transfer amount.\n");
        return;
    }

    if (amount > accounts[senderAccountIndex].balance)
    {
        printf("Insufficient balance.\n");
        return;
    }

    accounts[senderAccountIndex].balance -= amount;
    accounts[receiverAccountIndex].balance += amount;
    printf("Your request of transferring balance is successful..\n");
    printf("%s's (Sender) new balance: %.2f\n",accounts[senderAccountIndex].customerName, accounts[senderAccountIndex].balance);
}

void PrintStatement(BankInfo accounts[], int numAccounts)
{
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int accountIndex = -1;
    for (int i = 0; i < numAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Account Number: %d\n", accounts[accountIndex].accountNumber);
    printf("Customer Name: %s\n", accounts[accountIndex].customerName);
    printf("Current Balance: %.2f\n", accounts[accountIndex].balance);
}

void ChangeAccountName(BankInfo accounts[], int numAccounts)
{
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int accountIndex = -1;
    for (int i = 0; i < numAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Enter new customer name: ");
    fflush(stdin);
    gets( accounts[accountIndex].customerName);

    printf("Account holder's name changed successfully.\n");
}

void DeleteAccount(BankInfo accounts[], int *numAccounts)
{
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int accountIndex = -1;
    for (int i = 0; i < *numAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Account not found.\n");
        return;
    }

    for (int i = accountIndex; i < *numAccounts - 1; i++)
    {
        accounts[i] = accounts[i + 1];
    }

    (*numAccounts)--;
    printf("Account deleted successfully.\n");
}

void ViewAllAccounts(BankInfo accounts[], int numAccounts)
{
    printf("All Accounts:\n");
    for (int i = 0; i < numAccounts; i++)
    {
        printf("Account Number: %d, Customer Name: %s\n", accounts[i].accountNumber, accounts[i].customerName);
    }
}



