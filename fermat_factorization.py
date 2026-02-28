import math

def fermat_factor(n):
    if n <= 1:
        return None

    if n % 2 == 0:
        return (2, n // 2)

    a = math.isqrt(n)
    if a * a < n:
        a += 1

    while True:
        b2 = a * a - n
        b = math.isqrt(b2)

        if b * b == b2:
            return a - b, a + b

        a += 1


n = int(input("Enter an odd number to factor: "))

result = fermat_factor(n)

if result:
    print(f"Factors of {n} are: {result[0]} and {result[1]}")
else:
    print("Invalid input")
