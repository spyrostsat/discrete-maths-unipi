#include <stdio.h>
#include <stdlib.h>

void get_user_input(int *a, int *b);
void clean_stdin(void);
void print_division_arrays(int* array_dividends, int* array_divisors, int* array_quotients, int* array_remainders, int N);

int main(int argc, char *argv[])
{
    int i, j; // indeces to perform 'for' loops

    int a, b; /* dividend and divisor respectively */

    /* the 4 arrays that will hold all necessary intermidiate values for all needed divisions
    until we successfully locate the Greatest Common Divisor (i.e., gcd) of a and b */
    int array_dividends[100];
    int array_divisors[100];
    int array_quotients[100];
    int array_remainders[100];

    switch (argc)
    {
    case 1: /* if the user doesn't provide command line arguments, then we prompt him to enter the dividend and divisor explicitly */
        get_user_input(&a, &b);
        break;
    case 3: /* the user can provide the dividend and divisor from the command line */
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        break;
    default:
        printf("Expected 2 command line arguments. Exiting program...\n");
        exit(1);
    }

    if (a == 0 || b == 0) /* neither a nor b can be 0 for this program to have meaning */
    {
        printf("Wrong input. Exiting program...\n");
        exit(1);
    }

    if (abs(a) < abs(b)) /* dividend should be larger than its divisor, at least in absolute terms */
    {
        printf("Wrong input. Exiting program...\n");
        exit(1);
    }

    printf("\nDividend: %d\nDivisor: %d\n", a, b);

    i = -1; /* we keep track of how many values populate the 4 arrays holding all the necessary gcd-finding data */
    
    /* =====================
       Code to find gcd(a,b)
       ===================== */

    do
    {
        i++;
        array_dividends[i] = a;
        array_divisors[i] = b;
        array_quotients[i] = a / b;
        array_remainders[i] = a % b;
        a = b;
        b = array_remainders[i];
    } while (array_remainders[i] != 0);

    int N = i + 1; // variable N holds the final size of the arrays

    print_division_arrays(array_dividends, array_divisors, array_quotients, array_remainders, N);

    printf("\ngcd(%d, %d) = %d\n", array_dividends[0], array_divisors[0], array_divisors[N-1]);    
    
    /* =======================================================
       Code to find integers s, t so that a*s + b*t = gcd(a,b)
       ======================================================= */

    if (N == 1) { // in the special case where gcd(a,b) = b, we observe that 0*a + 1*b = b = gcd(a,b)
        int s = 0;
        int t = 1;

        printf("s=%d, t=%d\n\n", s, t);
        printf("(%d * %d) + (%d * %d) = %d\n\n", array_dividends[0], s, array_divisors[0], t, array_divisors[N-1]);
    }
    else {
        int help_array[N-1][2]; 
        int final_array[N-1][2];

        for ( i = 0; i < N-1; i++)
        {
            for (j = 0; j < 2; j++)
            {
                if (j == 0)
                    help_array[i][j] = 1;
                else
                    help_array[i][j] = -array_quotients[N-i-2];
            }
        }

        // Code to populate the final array that will contain the requested values s, t

        for (i = 0; i < N-1; i++)
        {
            for (j = 0; j < 2; j++)
            {
                if (i == 0)
                    final_array[i][j] = help_array[i][j];
                else
                {
                    if (j == 0)
                        final_array[i][j] = final_array[i-1][1] * help_array[i][j];
                    else
                        final_array[i][j] = final_array[i-1][1] * help_array[i][j] + final_array[i-1][0];
                }
            }
        }

        // final prints showing the requested values s, t
        printf("s=%d, t=%d\n\n", final_array[N-2][0], final_array[N-2][1]);
        printf("(%d * %d) + (%d * %d) = %d\n\n", array_dividends[0], final_array[N-2][0], array_divisors[0], final_array[N-2][1], array_divisors[N-1]);
    }
}

void clean_stdin(void)
{
    /* routine to clean the stdin stream, handling the case of the user providing complex input instead of the expected integers */
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void get_user_input(int *a, int *b)
{
    /* routine to prompt the user to provide input, if he hasn't given it already as command line arguments */

    printf("Give dividend: ");
    scanf("%d", a);
    clean_stdin();

    printf("Give divisor: ");
    scanf("%d", b);
    clean_stdin();
}

void print_division_arrays(int* array_dividends, int* array_divisors, int* array_quotients, int* array_remainders, int N)
{
    /* a routine to print all the arrays participating in the gcd finding */

    printf("\nDIVIDENDS ARRAY:\t");

    for (int i = 0; i < N; i++)
    {
        printf("%d\t", array_dividends[i]);
    }

    printf("\nDIVISORS ARRAY:\t\t");
    for (int i = 0; i < N; i++)
    {
        printf("%d\t", array_divisors[i]);
    }

    printf("\nQUOTIENTS ARRAY:\t");
    for (int i = 0; i < N; i++)
    {
        printf("%d\t", array_quotients[i]);
    }

    printf("\nREMAINDERS ARRAY:\t");
    for (int i = 0; i < N; i++)
    {
        printf("%d\t", array_remainders[i]);
    }
    printf("\n");
}
