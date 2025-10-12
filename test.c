#include <stdio.h>
int func(int* a) {
    return sizeof(*a);
}
int main()
{
    int a[] = {1,2,3,4,5};
    printf("%i ", sizeof(a));
    printf("%i ", func(a));

}