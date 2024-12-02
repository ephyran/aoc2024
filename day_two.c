#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum direction_state {
    ASCENDING = 0,
    DESCENDING = 1,
    UNSET
};

bool is_safe (long first, long second, enum direction_state state) {
    if (state == UNSET) {
        return false;
    }

    long temp = labs(first - second);
    if (temp > 0 && temp < 4) {
        if (first > second) {
            return state;
        } else if (first < second) {
            return !state;
        }
        
        return false;
    }
    
    return false;
}

int main (void) {
    FILE *fp = fopen("input_two.txt", "r");
    if (fp == NULL) {
        printf("Input not available.");
        return -1;
    }

    int safe_lines = 0;

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        bool line_safe = true;
        long previous = -1;
        enum direction_state state = UNSET;

        char *source = line;
        char *next;

        while (true) {
            long current = strtol(source, &next, 10);

            if (previous > 0 && current > 0) {
                if (state == UNSET) {
                    state = (previous - current) > 0;
                }

                if (!is_safe(previous, current, state)) {
                    line_safe = false;
                    break;
                }
            }

            previous = current;

            if (next != source) {
                source = next;
            } else {
                break;
            }
        }

        if (line_safe) {
            safe_lines++;
        }
    }

    printf("Safe report count: %d\n", safe_lines);
    fclose(fp);

    return 0;
}
