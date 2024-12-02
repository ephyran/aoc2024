#include <stdio.h>
#include <stdlib.h>

struct buffer {
    int size;
    int counter;
    int *data;
};

void update_buffer (struct buffer *buffer) {
    if (buffer->counter + 1 >= buffer->size) {
        buffer->size = buffer->size * 2;
        buffer->data = realloc(buffer->data, sizeof(int) * buffer->size);
    }
}

void swap (int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void insertion_sort (struct buffer *buffer) {
    for (int i = 0; i < buffer->counter; i++) {
        int j = i;

        while (j > 0 && buffer->data[j - 1] > buffer->data[j]) {
            swap(&buffer->data[j - 1], &buffer->data[j]);
            j--;
        }
    }
}

int binary_search (struct buffer *buffer, int target) {
    int bot = 0;
    int top = buffer->counter;

    while (bot <= top) {
        int pivot = bot + (top - bot) / 2;

        if (buffer->data[pivot] == target) {
            while (buffer->data[pivot - 1] == target) {
                pivot--;
            }

            return pivot;
        }

        if (buffer->data[pivot] < target) {
            bot = pivot + 1;
        } else {
            top = pivot - 1;
        }
    }

    return -1;
}

int part_one (struct buffer *first, struct buffer *second) {
    int result = 0;

    for (int i = 0; i < first->counter; i++) {
        result += abs(first->data[i] - second->data[i]);
    }

    return result;
}

int part_two(struct buffer *first, struct buffer *second) {
    int result = 0;

    for (int i = 0; i < first->counter; i++) {
        int target = first->data[i];
        int location = binary_search(second, target);
        int total = 0;

        if (location != -1) {
            int grabbed = second->data[location + total];

            while (grabbed == target) {
                total++;
                grabbed = second->data[location + total];
            }
        }

        result += target * total;
    }

    return result;
}

int main (void) {
    FILE *fp = fopen("input_one.txt", "r");
    if (fp == NULL) {
        printf("Input not available.");
        return -1;
    }

    int first, second;
    struct buffer first_buffer, second_buffer;

    first_buffer.data = malloc(sizeof(int) * 100);
    first_buffer.size = 100;
    first_buffer.counter = 0;

    second_buffer.data = malloc(sizeof(int) * 100);
    second_buffer.size = 100;
    second_buffer.counter = 0;

    while (fscanf(fp, "%d %d", &first, &second) == 2) {
        update_buffer(&first_buffer);
        update_buffer(&second_buffer);

        first_buffer.data[first_buffer.counter] = first;
        second_buffer.data[second_buffer.counter] = second;

        first_buffer.counter++;
        second_buffer.counter++;
    }

    insertion_sort(&first_buffer);
    insertion_sort(&second_buffer);

    printf("First: %d\n", part_one(&first_buffer, &second_buffer));
    printf("Second: %d\n", part_two(&first_buffer, &second_buffer));

    free(first_buffer.data);
    free(second_buffer.data);

    return 0;
}
