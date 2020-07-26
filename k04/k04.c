#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int gender;
    double height;
} sample;

typedef struct {
    sample *data; /* actual data for this vector. */
    size_t cap;   /* capacity of the data array. */
    size_t size;  /* count of items inserted. */
} vector;

static vector *vector_new(void) {
    vector *vec = malloc(sizeof(vector));
    if (vec == NULL) return NULL;

    memset(vec, 0, sizeof(vector));

    return vec;
}

static void vector_delete(vector *vec) {
    free(vec->data);
    free(vec);
}

static _Bool vector_push_back(vector *vec, sample *s) {
    if (vec->cap <= vec->size) {
        if (vec->cap == 0) {
            size_t tmp_cap = 8;
            vec->data = malloc(sizeof(sample) * tmp_cap);
            if (vec->data == NULL) {
                return 0;
            }
            vec->cap = tmp_cap;
        } else {
            size_t tmp_cap = vec->cap << 1;
            sample *tmp_data = realloc(vec->data, sizeof(sample) * tmp_cap);
            if (tmp_data == NULL) {
                return 0;
            }
            vec->data = tmp_data;
            vec->cap = tmp_cap;
        }
    }

    vec->data[vec->size] = *s;
    ++(vec->size);
    return 1;
}

static sample *vector_at(vector *vec, size_t i) {
    if (i >= vec->size) {
        return NULL;
    }
    return &vec->data[i];
}

static size_t vector_size(vector *vec) {
    return vec->size;
}

/* TODO: O(n) */
static sample *vector_find(vector *vec, int id) {
    for (size_t i = 0; i < vec->size; ++i) {
        if (vec->data[i].id == id) {
            return &vec->data[i];
        }
    }
    return NULL;
}

int main(void) {
    char fname[FILENAME_MAX];
    char buf[256];
    FILE *fp;

    printf("input the filename of sample heights: ");
    fgets(fname, sizeof(fname), stdin);
    fname[strlen(fname) - 1] = '\0';

    fp = fopen(fname, "r");
    if (fp == NULL) {
        fputs("File open error\n", stderr);
        exit(EXIT_FAILURE);
    }

    /* skip 1 line for header. */
    if (fgets(buf, sizeof(buf), fp) == NULL) {
        fclose(fp);
        return 1;
    }

    vector *samples = vector_new();
    if (samples == NULL) {
        perror(NULL);
        fclose(fp);
        return 1;
    }

    sample tmp;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        sscanf(buf, "%d, %lf", &tmp.gender, &tmp.height);

        if (!vector_push_back(samples, &tmp)) {
            perror(NULL);
            vector_delete(samples);
            fclose(fp);
            return 1;
        }
    }

    if (fclose(fp) == EOF) {
        fputs("file close error\n", stderr);
        exit(EXIT_FAILURE);
    }

    printf("input the filename of sample ID: ");
    fgets(fname, sizeof(fname), stdin);
    fname[strlen(fname) - 1] = '\0';

    fp = fopen(fname, "r");
    if (fp == NULL) {
        fputs("File open error\n", stderr);
        exit(EXIT_FAILURE);
    }

    size_t index = 0;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        int val;
        sscanf(buf, "%d", &val);

        sample *cur = vector_at(samples, index);
        if (cur == NULL) {
            fputs("Corrupted data (heights length != ID length)\n", stderr);

            vector_delete(samples);
            fclose(fp);
            return 1;
        }
        cur->id = val;

        ++index;
    }

    if (index != vector_size(samples)) {
        fputs("Corrupted data (heights length != ID length)\n", stderr);

        vector_delete(samples);
        fclose(fp);
        return 1;
    }

    printf("which id's data do you want? ");
    fgets(buf, sizeof(buf), stdin);

    int id;
    if (sscanf(buf, "%d", &id) != 1) {
        vector_delete(samples);
        fclose(fp);
    }

    puts("---");

    sample *data = vector_find(samples, id);
    if (data == NULL) {
        puts("No data");
    } else {
        printf("ID: %d\n", data->id);
        printf("gender: %s\n", data->gender == 1 ? "Male" : "Female");
        printf("height: %.2lf\n", data->height);
    }

    vector_delete(samples);

    if (fclose(fp) == EOF) {
        fputs("file close error\n", stderr);
        exit(EXIT_FAILURE);
    }

    return 0;
}