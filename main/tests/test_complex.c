int factorial(int n) {
    int result;
    result = 1;
    
    while (n > 1) {
        result = result * n;
        n = n - 1;
    }
    
    return result;
}

float calculate(float x, float y) {
    if (x > y) {
        return x + y;
    } else {
        return x - y;
    }
}

int main() {
    int num;
    float a;
    float b;
    
    num = 5;
    a = 10.5;
    b = 3.2;
    
    repeat {
        num = num - 1;
    } until (num == 0);
    
    for (num = 0; num < 10; num = num + 1) {
        a = a + 1.0;
    }
    
    switch (num) {
        case 0:
            a = 0.0;
        case 1:
            b = 1.0;
    }
    
    return 0;
}
