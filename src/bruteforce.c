#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char dictionary[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                             'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                             'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                             'y', 'z' };

const int dict_len = sizeof(dictionary) / sizeof(char);


bool recursion(char* password, char* brute_buf, int max_depth, int depth) {

    /** as long as the password length is shorter than the maximum length */
    if (depth < max_depth) {

        /** if our password is only 1 character long... */
        if (sizeof(brute_buf) == 1) {
            for(int i = 0; i < dict_len; i++) {
                if (password[0] == (char) dictionary[i]) {
                    printf("The password was: %c", dictionary[i]);
                    return true;
                }
            }
        } else {
            /**
             * add an iterator with every iteration
             * the recursion starts with 'a'
             * goes directly to the second level and tries 'aa'
             * when 'a' * max_depth is reached, go back and try with
             * 'aaa..aab'
             */
            for(int i = 0; i < dict_len; i++) {
                if (strcat(brute_buf, &dictionary[i]) == password) {
                    printf("the password is %s", strcat(brute_buf, &dictionary[i]));
                    return true;
                } else {
                    char* new_brute_buf = strcat(brute_buf, &dictionary[i]);
                    recursion(password, brute_buf, max_depth, ++depth);
                }
            }
        }
    }

    /**
     * when the max depth was reached and the password couldn't be found
     * then return fail state
     */
    return false;
}

/** is given a password and tries to guess it by bruteforcing it */
bool bruteforce(char* password, int depth) {

    char* brute_buf = malloc(1);
    if (!brute_buf) {
        printf("system ran out of memory.");
        return true;
    }
    brute_buf[0] = dictionary[0];

    /**
     * hand over the password,
     * start guessing with a length of 1,
     * password still has to be found so hand over "true"
     */
    if (recursion(password, brute_buf, depth, 1) == true) {
        free(brute_buf);
        return true;
    }

    /**
     * when the max depth was reached and the password couldn't be found
     * then return fail state
     */
    return false;
}

int main(int argc, char** argv) {

    char* filename;
    int depth;
    if (argc == 2) {
        filename = argv[0];
        depth = (int) argv[1];
    }

    /** open file specified by the command line parameter */
    FILE* password_fd = fopen(filename, "r");

    // TODO: fix segfault caused by fseek, learn about errno
    int errno = 0;
    /** obtain file size: */
    fseek(password_fd, 0 , SEEK_END);
    size_t lSize = ftell(password_fd);
    rewind(password_fd);

    /** allocate memory to contain the whole file: */
    char* password = (char*) malloc (sizeof(char)*lSize);
    if (password == NULL) {
        printf("System ran out of memory.");
        exit(1);
    }

    if (bruteforce(password, depth) == true) {
        free(password);
        fclose(password_fd);
        exit(0);
    } else {
        printf("Password couldn't be found.");
        exit(2);
    }
}
