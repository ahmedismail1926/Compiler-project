int main() {
    int x;
    float y;
    char c;
    bool flag;
    int a;
    int b;
    int result;
    int i;
    int p;
    int q;
    int r;
    bool t;
    bool f;
    bool res;
    const int MAX = 100;
    
    x = 10;
    y = 3.14;
    c = 'A';
    flag = true;
    
    a = 20;
    b = 7;
    result = a + b;
    result = a - b;
    result = a * b;
    result = a / b;
    result = a % b;
    
    x = 5;
    x += 3;
    x -= 2;
    x *= 4;
    x /= 2;
    x %= 3;
    
    i = 0;
    ++i;
    i++;
    --i;
    i--;
    
    p = 5;
    q = 3;
    r = p & q;
    r = p | q;
    r = p ^ q;
    r = ~p;
    
    t = true;
    f = false;
    res = t && f;
    res = t || f;
    res = !t;
    
    if (x > 0) {
        x = x + 1;
    } else {
        x = x - 1;
    }
    
    x = 5;
    while (x > 0) {
        x = x - 1;
    }
    
    for (i = 0; i < 10; i = i + 1) {
        a = a + 1;
    }
    
    x = 5;
    do {
        x = x - 1;
    } while (x > 0);
    
    x = 1;
    switch (x) {
        case 0:
            a = 0;
        case 1:
            a = 1;
        default:
            a = 2;
    }
    
    for (i = 0; i < 10; i = i + 1) {
        if (i == 5) {
            break;
        }
        if (i == 3) {
            continue;
        }
        a = i;
    }
    
    return 0;
}

int add(int a, int b) {
    return a + b;
}

void doNothing() {
    return;
}
