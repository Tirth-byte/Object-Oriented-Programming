LOOPS
Set of instructions given to the compiler to execute set of statements until condition becomes false
Types of loops
1. Entery controlled loops
2. Exit controlled loops
# Advantages of loops
1.Reduce length of code
2. take less memory space
1. entry controlled loops
In entry controlled loops, the condition is checked first before executing the loop body.
If the condition is true, the loop body is executed; if false, the loop terminates
Types of entry controlled loops
1. for loop
2. while loop
2. Exit controlled loops
In exit controlled loops, the loop body is executed first, and then the condition is checked.
If the condition is true, the loop continues; if false, the loop terminates.
Types of exit controlled loops
1. do-while loop
# for loop
The for loop is used when the number of iterations is known beforehand.
Syntax:
for(initialization; condition; increment/decrement)
{
    // loop body
}
Example:
// User choise print even numebers using for long
#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Even numbers up to " << n << " are: ";
    for(int i = 2; i <= n; i += 2)
    {
        cout << i << " ";
    }
    return 0;
}
// prime numbes using for loop
#include <iostream>
using namespace std;
int main()
{
    int n, isPrime = 1;
    cout << "Enter a number: ";
    cin >> n;
    for(int i = 2; i <= n / 2; i++)
    {
        if(n % i == 0)
        {
            isPrime = 0;
            break;
        }
    }
    if(isPrime && n > 1)
        cout << n << " is a prime number.";
    else
        cout << n << " is not a prime number.";
    return 0;
}
# while loop
The while loop is used when the number of iterations is not known beforehand and depends on a condition
Syntax:
while(condition)
{
    // loop body
}
Example:
// cheack even numbers using while loop
#include <iostream>
using namespace std;
int main()
{
    int n, i = 2;   
    cout << "Enter a number: ";
    cin >> n;
    cout << "Even numbers up to " << n << " are: ";
    while(i <= n)
    {
        cout << i << " ";
        i += 2;
    }
    return 0;
}
# do-while loop
The do-while loop is similar to the while loop, but it guarantees that the loop body is executed at least once before checking the condition.
Syntax:
do
{
    // loop body
} while(condition);
Note: The semicolon after the while(condition) is mandatory.
Example:
// print "hello world" n times using do-while loop
#include <iostream>
using namespace std;
int main()
{
    int n, count = 0;
    cout << "Enter a number: ";
    cin >> n;
    do
    {
        cout << "Hello, World!" << endl;
        count++;
    } while(count < n);
    return 0;
}
