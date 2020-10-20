#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE_ARRAY 100

void BubbleSort(long long [], int);

struct interval_t {
    long long point_from;
    long long point_to;
    int amount_from;
    int amount_to;
};


int review_entering_args(int argc, char* argv[], struct interval_t* interval1) {
    if (argc < 2) {
        return -1;
    }
    if (argc > 3) {
        return -2;
    }
    interval1->amount_from = 0;
    interval1->amount_to = 0;
    for (int i = 1; i < argc; i++){
        if (strncmp(argv[i],"--from=",7) == 0){
            interval1->amount_from++;
        }
        if (strncmp(argv[i],"--to=",5) == 0){
            interval1->amount_to++;
        }
    }
    if (interval1->amount_from > 1 || interval1->amount_to > 1) {
        return -3;
    }
    if (interval1->amount_from != 1 && interval1->amount_to != 1) {
        return -4;
    }

    for (int j = 1; j < argc; j++) {
      long long possible_from, possible_to;
        char *pEnd;
        if (strncmp(argv[j], "--from=", 7) == 0 && interval1->amount_from == 1) {
            possible_from = strtoll(strchr(argv[j], '=') + 1, &pEnd, 10);
            if (*pEnd != '\0') {
              possible_from = 0;
            }
            interval1->point_from = possible_from;
            interval1->amount_from = -1;
        }
        if (strncmp(argv[j], "--to=", 5) == 0 && interval1->amount_to == 1) {
            possible_to = strtoll(strchr(argv[j], '=') + 1, &pEnd, 10);
            if (*pEnd != '\0') {
              possible_to = 0;
            }
            interval1->point_to = possible_to;
            interval1->amount_to = -1;
        }
    }
    return 0;
}

int reading_array (long long need_clear_array[], struct interval_t interval) {
    char space;
    long long stdout_array[MAX_SIZE_ARRAY], error_array[MAX_SIZE_ARRAY], number;
    int clear_array_size = 0, stdout_array_size = 0, error_array_size = 0;
    while (space != '\n' && clear_array_size < MAX_SIZE_ARRAY && stdout_array_size < MAX_SIZE_ARRAY && error_array_size < MAX_SIZE_ARRAY) {
        if (scanf("%lld%c",&number ,&space) != 2) {
          return -1;
        };
        if ((number > interval.point_from || interval.amount_from == 0) && (number < interval.point_to || interval.amount_to == 0)) {
            need_clear_array[clear_array_size] = number;
            ++clear_array_size;
        }
        if (number >= interval.point_to && interval.amount_to == -1) {
            stdout_array[stdout_array_size] = number;
            ++stdout_array_size;
        }
        if (number <= interval.point_from && interval.amount_from == -1) {
            error_array[error_array_size] = number;
           ++error_array_size;
        }

    }

    for (int i = 0; i < stdout_array_size; i++) {
        fprintf (stdout, "%lld ", stdout_array[i]);
    }
    for (int i = 0; i < error_array_size; i++ ) {
        fprintf(stderr, "%lld ", error_array[i]);
    }
    return clear_array_size;
}

int counting_shifts_in_array (const long long array_before[], const long long array_after[], int array_size) {
    int amount_shifts = 0;
    for (int i = 0; i < array_size; i++) {
        if (array_before[i] != array_after[i]) {
            amount_shifts++;
        }
    }
    return amount_shifts;
}

int main(int argc, char* argv[]) {
    struct interval_t interval = {0, 0, 0, 0};
    int review_args = review_entering_args(argc,argv, &interval);
    if(review_args < 0) {
        return 1;
    }
    long long clear_array[MAX_SIZE_ARRAY];
    int clear_array_size = reading_array(clear_array,interval);
    long long new_clear_array[clear_array_size];
    memcpy(new_clear_array, clear_array, clear_array_size * sizeof(long long));


   BubbleSort(new_clear_array, clear_array_size);
    int counting_shifts = counting_shifts_in_array(clear_array, new_clear_array, clear_array_size);
    return counting_shifts;
}