 #include <stdio.h>
int main(int argc, char *argv[])
{
    printf("%d xxx\n", argc);
    if(argc >2)
        main(argc-1, NULL);
    return 0;
}
