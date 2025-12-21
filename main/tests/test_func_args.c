int add(int a, int b) {
    return a + b;
}

int multiply(int x, int y) {
    int result;
    result = x * y;
    return result;
}

int main() {
    int x;
    int y;
    int sum;
    int product;
    
    x = 5;
    y = 3;
    
    sum = add(x, y);
    product = multiply(10, 20);
    
    return 0;
}
