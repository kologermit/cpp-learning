# Длинная арифметика

Постановка задачи: реализовать класс **BigInteger**, который умеет производить любые операции с числами любой длины.

## Необходимые операции

Реализуем следующие операции:

### Конструкторы

Конструктор по умолчанию, число 0:

    BigInteger bi;

Конструктор от числа:

    BigInteger bi(123456789);

Конструктор от строки:

    BigInteger bi("3784523790845703e4895723047895");
    BigInteger bi("-2378490723089567340589743057640139587340285");
    BigInteger bi("0");
    BigInteger bi("");

Оператор присваивания:

    BigInteger bi(123456);
    BigInteger bi2(123);
    bi = 100;
    bi = bi2;

### Чтение из строки и вывод в строку

    BigInteger bi;
    std::cin >> bi;
    std::cout << bi << std::endl;

### Операторы +, -, *. /, %

    BigInteger bi(123456789);
    std::cout << bi += 10 << std::endl;         // 123456799
    std::cout << bi + 10 << std::endl;          // 123456809
    std::cout << 10 + bi << std::endl;          // 123456809

    std::cout << bi *= 1234556 << std::endl;    // 152414331946244
    std::cout << bi * 1234556 << std::endl;     // 188164027990227207664

    BigInteger bi2("123456789123456789");
    std::cout << bi *= bi2 << std::endl;        // 18816584038479988870179404850516
    std::cout << bi2 * bi << std::endl;         // 2323035047662426912007479043443817529899730353124

### Инкременты

    BigInteger bi(100500);
    std::cout << ++bi;  // 100501
    std::cout << --bi;  // 100500
    std::cout << bi++;  // 100500
    std::cout << bi--;  // 100501

### Операторы свавнения

    BigInteger bi(1234);
    std::cout << (bi == 1234);      // true
    std::cout << (1234 == bi);      // true
    std::cout << (1234 != bi);      // false

    std::cout << (bi != 123566);    // true
    std::cout << (bi != 123);       // true
    std::cout << (bi != 1234);      // false

    std::cout << (bi < 12345);      // true
    std::cout << (bi < 1230);       // false
    std::cout << (123 < bi);        // true

### Унарный минус

    BigInteger bi("2323035047662426912007");
    std::cout << -bi;   // -2323035047662426912007

### Приведение в bool

    BigInteger bi(12312435);
    if (bi) {
        std::cout << "Right";
    }

    if (!BigInteger()) {
        std::cout << "Right;
    }

### Вывод в строку

    BigInteger bi(7654321);
    std::cout << bi.toString();
