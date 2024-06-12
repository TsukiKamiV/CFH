#include <stdio.h>

int main() {
    // 定义一些变量
    int a = 10;
    char b = 'A';
    double c = 3.14;
    int array[3] = {1, 2, 3};
    
    // 定义一些指针并指向上述变量
    int *pInt = &a;
    char *pChar = &b;
    double *pDouble = &c;
    int *pArray = array;
    
    // 打印这些指针的值
    printf("Pointer to int: %p\n", (void *)pInt);
    printf("Pointer to char: %p\n", (void *)pChar);
    printf("Pointer to double: %p\n", (void *)pDouble);
    printf("Pointer to array: %p\n", (void *)pArray);
    
    // 传递空指针
    int *pNull = NULL;
    printf("Null pointer: %p\n", (void *)pNull);
    
    return 0;
}
