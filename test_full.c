const int MAX = 100;

int global;
float pi;

void testFunction() {
    return;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    int x;
    float y;
    
    x = 10;
    y = 3.14;
    
    if (x > 5) {
        x = x + 1;
    }
    
    if (x < 20) {
        x = x - 1;
    } else {
        x = 0;
    }
    
    while (x > 0) {
        x = x - 1;
    }
    
    for (x = 0; x < 10; x = x + 1) {
        y = y + 1.0;
    }
    
    repeat {
        x = x + 1;
    } until (x >= 5);
    
    x = add(5, 10);
    
    return 0;
}
