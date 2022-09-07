#include <iostream>
using std::cout, std::endl;

int fibonacci_exp(int n){
    if(n <= 1)
        return n;
    return fibonacci_exp(n - 1) + fibonacci_exp(n - 2);
}

int fibonacci_lineal(int n){
    int *F = new int[n + 2];
    F[0] = 0; F[1] = 1;
    for(int i = 2; i <= n; i++)
        F[i] = F[i - 1] + F[i - 2];
    return F[n];
}

class fibonacci_log{
public:

    void mat_mult(int F[2][2], int F_prime[2][2]);
    void pow(int F[2][2], int n);
    int fib_log(int n);
};

void fibonacci_log::mat_mult(int (*F)[2], int (*F_prime)[2]) {
    int i, j, k, z;
    i = (F[0][0] * F_prime[0][0]) + (F[0][1] * F_prime[1][0]);
    j = (F[0][0] * F_prime[0][1]) + (F[0][1] * F_prime[1][1]);
    k = (F[1][0] * F_prime[0][0]) + (F[1][1] * F_prime[1][0]);
    z = (F[1][0] * F_prime[0][1]) + (F[1][1] * F_prime[1][1]);
    F[0][0] = i;
    F[0][1] = j;
    F[1][0] = k;
    F[1][1] = z;
}

void fibonacci_log::pow(int (*F)[2], int n) {
    if (n == 0 || n == 1)
        return;
    int FF[2][2] = {{0, 1},{1, 1}};
    pow(F, n/2);
    mat_mult(F, F);
    if(n % 2 != 0)
        mat_mult(F, FF);
}

int fibonacci_log::fib_log(int n) {
    int i, j;
    int F[2][2] = {
            {0, 1},
            {1, 1}
    };
    int FF[2][1] = {
            {0}, {1}
    };
    if (n == 0)
        return 0;
    pow(F, n - 1);

    j = F[1][0] * FF[0][0] + F[1][1] * FF[1][0];
    FF[1][0] = j;

    return FF[1][0];
}

void test(){
    int vec[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    fibonacci_log A;
    for(auto i : vec){
        cout << i + 1 << " - " << fibonacci_exp(i) << " " << fibonacci_lineal(i) << " " << A.fib_log(i) << endl;
    }
}

int main() {
    test();
    return 0;
}
