void scanf_is_valid(int *a) {
    if (scanf("%d", a) != 1) {
        printf("n/a");
        exit(1);
    }
}

void last_symbol_check() {
    char ch = getchar();
    if (ch != '\n') {
        printf("n/a");
        exit(1);
    }
}
