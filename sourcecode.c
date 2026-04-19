
#include <stdio.h>
#include <string.h>

/* -------- TRANSACTION STRUCTURE -------- */
struct transaction
{
    char type[20];
    float amount;
    float balance_after;
};

/* -------- BANK ACCOUNT STRUCTURE -------- */
struct bank_acc
{
    char owner_name[20];
    char acc_no[10];
    int pin;                      
    float balance;

    struct transaction history[50];
    int t_count;
};

/* -------- PIN AUTHENTICATION FUNCTION -------- */
int authenticate(struct bank_acc B[], int index)
{
    int entered_pin, attempts = 3;

    while (attempts > 0)
    {
        printf("Enter PIN: ");
        scanf("%d", &entered_pin);

        if (entered_pin == B[index].pin)
            return 1;

        attempts--;
        printf("Wrong PIN! Attempts left: %d\n", attempts);
    }

    printf("Authentication failed.\n");
    return 0;
}

int main()
{
    struct bank_acc B[10];
    int count, i, j, choice;
    char acc[10], sender[10], receiver[10];
    float amount;

    printf("Enter number of bank accounts (max 10): ");
    scanf("%d", &count);

    if (count > 10)
    {
        printf("Maximum 10 accounts allowed.\n");
        return 0;
    }

    /* -------- INITIAL ACCOUNT INPUT -------- */
    for (i = 0; i < count; i++)
    {
        printf("\nEnter details for account %d\n", i + 1);

        printf("Owner name: ");
        scanf("%19s", B[i].owner_name);

        printf("Account number: ");
        scanf("%9s", B[i].acc_no);

        printf("Set 4-digit PIN: ");
        scanf("%d", &B[i].pin);

        printf("Balance: ");
        scanf("%f", &B[i].balance);

        B[i].t_count = 0;
    }

    do
    {
        printf("\n----- MENU -----\n");
        printf("1. Create new account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check balance\n");
        printf("5. View account details\n");
        printf("6. Check loan eligibility\n");
        printf("7. Delete account\n");
        printf("8. Transfer money\n");
        printf("9. View transaction history\n");
        printf("10. Add compound Interest\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        /* -------- CREATE ACCOUNT -------- */
        case 1:
            if (count >= 10)
            {
                printf("Account limit reached.\n");
                break;
            }

            printf("Owner name: ");
            scanf("%19s", B[count].owner_name);

            printf("Account number: ");
            scanf("%9s", B[count].acc_no);

            printf("Set 4-digit PIN: ");
            scanf("%d", &B[count].pin);

            printf("Balance: ");
            scanf("%f", &B[count].balance);

            B[count].t_count = 0;
            count++;

            printf("Account created successfully.\n");
            break;

        /* -------- DEPOSIT -------- */
        case 2:
            printf("Enter account number: ");
            scanf("%9s", acc);

            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            for (j = 0; j < count; j++)
            {
                if (strcmp(B[j].acc_no, acc) == 0)
                {
                    if (!authenticate(B, j)) break;

                    B[j].balance += amount;

                    strcpy(B[j].history[B[j].t_count].type, "Deposit");
                    B[j].history[B[j].t_count].amount = amount;
                    B[j].history[B[j].t_count].balance_after = B[j].balance;
                    B[j].t_count++;

                    printf("Deposit successful.\n");
                    break;
                }
            }
            if (j == count) printf("Account not found.\n");
            break;

        /* -------- WITHDRAW -------- */
        case 3:
            printf("Enter account number: ");
            scanf("%9s", acc);

            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            for (j = 0; j < count; j++)
            {
                if (strcmp(B[j].acc_no, acc) == 0)
                {
                    if (!authenticate(B, j)) break;

                    if (B[j].balance >= amount)
                    {
                        B[j].balance -= amount;

                        strcpy(B[j].history[B[j].t_count].type, "Withdraw");
                        B[j].history[B[j].t_count].amount = amount;
                        B[j].history[B[j].t_count].balance_after = B[j].balance;
                        B[j].t_count++;

                        printf("Withdrawal successful.\n");
                    }
                    else
                        printf("Insufficient balance.\n");

                    break;
                }
            }
            if (j == count) printf("Account not found.\n");
            break;

        /* -------- CHECK BALANCE -------- */
        case 4:
            printf("Enter account number: ");
            scanf("%9s", acc);

            for (j = 0; j < count; j++)
            {
                if (strcmp(B[j].acc_no, acc) == 0)
                {
                    if (!authenticate(B, j)) break;
                    printf("Balance: %.2f\n", B[j].balance);
                    break;
                }
            }
            if (j == count) printf("Account not found.\n");
            break;

        /* -------- VIEW ALL ACCOUNTS -------- */
        case 5:
                printf("Enter Account Number\n");
                scanf("%9s",&acc);
                for(i=0;i<count;i++)
                {
                    if (strcmp(acc, B[i].acc_no) == 0)
                    {
                        if (!authenticate(B, i)) break;

                        printf("\nName: %s", B[i].owner_name);
                        printf("\nAccount No: %s", B[i].acc_no);
                        printf("\nBalance: %.2f\n", B[i].balance);
                        break;
                    }
                }
                if(i==count)
                {
                    printf("Account number entered is invalid\n");
                }
            
            break;

        /* -------- LOAN ELIGIBILITY -------- */
        case 6:
            printf("Enter account number: ");
            scanf("%9s", acc);

            for (j = 0; j < count; j++)
            {
                if (strcmp(B[j].acc_no, acc) == 0)
                {
                    if (!authenticate(B, j)) break;

                    if (B[j].balance >= 50000)
                        printf("Eligible for loan.\n");
                    else
                        printf("Not eligible for loan.\n");
                    break;
                }
            }
            if (j == count) printf("Account not found.\n");
            break;

        /* -------- DELETE ACCOUNT -------- */
        case 7:
            printf("Enter account number to delete: ");
            scanf("%9s", acc);

            for (j = 0; j < count; j++)
            {
                if (strcmp(B[j].acc_no, acc) == 0)
                {
                    if (!authenticate(B, j)) break;

                    for (i = j; i < count - 1; i++)
                        B[i] = B[i + 1];

                    count--;
                    printf("Account deleted.\n");
                    break;
                }
            }
            if (j == count) printf("Account not found.\n");
            break;

        /* -------- TRANSFER -------- */
        case 8:
        {
            int s = -1, r = -1;

            printf("Sender account: ");
            scanf("%9s", sender);
            printf("Receiver account: ");
            scanf("%9s", receiver);
            printf("Amount: ");
            scanf("%f", &amount);

            for (j = 0; j < count; j++)
            {
                if (strcmp(B[j].acc_no, sender) == 0) s = j;
                if (strcmp(B[j].acc_no, receiver) == 0) r = j;
            }

            if (s == -1 || r == -1)
                printf("Account not found.\n");
            else if (!authenticate(B, s))
                break;
            else if (B[s].balance < amount)
                printf("Insufficient balance.\n");
            else
            {
                B[s].balance -= amount;
                B[r].balance += amount;

                strcpy(B[s].history[B[s].t_count].type, "Transfer Out");
                B[s].history[B[s].t_count].amount = amount;
                B[s].history[B[s].t_count].balance_after = B[s].balance;
                B[s].t_count++;

                strcpy(B[r].history[B[r].t_count].type, "Transfer In");
                B[r].history[B[r].t_count].amount = amount;
                B[r].history[B[r].t_count].balance_after = B[r].balance;
                B[r].t_count++;

                printf("Transfer successful.\n");
            }
            break;
        }

        /* -------- VIEW TRANSACTION HISTORY -------- */
        case 9:
        {
            printf("Enter account number: ");
            scanf("%9s", acc);

            for (j = 0; j < count; j++)
            {
                if (strcmp(B[j].acc_no, acc) == 0)
                {
                    if (!authenticate(B, j)) break;

                    if (B[j].t_count == 0)
                    {
                        printf("No transactions.\n");
                        break;
                    }

                    for (i = 0; i < B[j].t_count; i++)
                    {
                        printf("%d. %s | %.2f | Balance: %.2f\n",
                               i + 1,
                               B[j].history[i].type,
                               B[j].history[i].amount,
                               B[j].history[i].balance_after);
                    }
                    break;
                }
            }
            if (j == count) printf("Account not found.\n");
            break;
        }
    case 10:/* -------- COMPOUND INTEREST -------- */
    {
    float rate;
    int years;

    printf("Enter account number: ");
    scanf("%9s", acc);

    for (j = 0; j < count; j++)
    {
        if (strcmp(B[j].acc_no, acc) == 0)
        {
            printf("Enter annual interest rate (in %%): ");
            scanf("%f", &rate);

            printf("Enter number of years: ");
            scanf("%d", &years);

            float principal = B[j].balance;
            float compoundAmount = principal;

            for (i = 0; i < years; i++)
            {
                compoundAmount = compoundAmount * (1 + rate / 100);
            }

            float interestEarned = compoundAmount - principal;

            B[j].balance = compoundAmount;

            /* Store transaction */
            strcpy(B[j].history[B[j].t_count].type, "Compound Interest");
            B[j].history[B[j].t_count].amount = interestEarned;
            B[j].history[B[j].t_count].balance_after = B[j].balance;
            B[j].t_count++;

            printf("Compound Interest added successfully.\n");
            printf("Interest Earned: %.2f\n", interestEarned);
            printf("New Balance: %.2f\n", B[j].balance);
            break;
        }
    }

    if (j == count)
    printf("Account not found.\n");

    break;
}

    case 11:
    {
        printf("Exiting...\n");
        break;
    }
    default:
        printf("Invalid choice.\n");
        }

    } while (choice != 10);

    return 0;
}
