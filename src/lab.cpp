#include <stdlib.h>
#include <stdio.h>
#include <lab.h>
#include <sys/time.h>  /* for gettimeofday system call */
#include <iostream>
#include <pthread.h>

/**
 * @brief Standard insertion sort that is faster than merge sort for small array's
 *
 * @param A The array to sort
 * @param p The starting index
 * @param r The ending index
 */
static void insertion_sort(int A[], int p, int r)
{
    int j;

    for (j = p + 1; j <= r; j++)
    {
        int key = A[j];
        int i = j - 1;
        while ((i > p - 1) && (A[i] > key))
        {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}

void mergesort_sm(int A[], int p, int r, int min)
{
    if (r - p + 1 <= min)
    {
        insertion_sort(A, p, r);
    }
    else
    {
        int q = (p + r) / 2;
        mergesort_s(A, p, q);
        mergesort_s(A, q + 1, r);
        //make sure threads are done before moving on //pthread join //but dont change this
        merge_s(A, p, q, r);
    }
}

void mergesort_s(int A[], int p, int r) //int array of A is a pointer, its not going to be a copy of what was passed to this class
{
    mergesort_sm(A, p, r, INSERTION_SORT_THRESHOLD);
}

void merge_s(int A[], int p, int q, int r)
{
    int *B = (int *)malloc(sizeof(int) * (r - p + 1));

    int i = p;
    int j = q + 1;
    int k = 0;
    int l;

    /* as long as both lists have unexamined elements */
    /*  this loop keeps executing. */
    while ((i <= q) && (j <= r))
    {
        if (A[i] < A[j])
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    /* now only at most one list has unprocessed elements. */
    if (i <= q)
    {
        /* copy remaining elements from the first list */
        for (l = i; l <= q; l++)
        {
            B[k] = A[l];
            k++;
        }
    }
    else
    {
        /* copy remaining elements from the second list */
        for (l = j; l <= r; l++)
        {
            B[k] = A[l];
            k++;
        }
    }

    /* copy merged output from array B back to array A */
    k = 0;
    for (l = p; l <= r; l++)
    {
        A[l] = B[k];
        k++;
    }

    free(B);
}

double getMilliSeconds()
{
    struct timeval now;
    gettimeofday(&now, (struct timezone *)0);
    return (double)now.tv_sec * 1000.0 + now.tv_usec / 1000.0;
}

static void *parallel_mergesort(void *args)
{
    struct parallel_args *arg = (struct parallel_args *)args;
    mergesort_sm(arg->A, arg->start, arg->end, arg->min);
    return NULL;
}

void mergesort_mt(int *A, int n, int num_threads, int min)
{
    //check if the number of threads to be used is 0
        //if so just use insertion sort
    if (num_threads <= 0) {
        //use insertion sort
        mergesort_sm(A, 0, n, min);
        return;
    }


    //calculate the size of each "chunk" of the array that each thread is responsible for sorting
    int chunk_size = n / num_threads;
    int extra = n - ( chunk_size * num_threads );


    //determine if the chunk size is less than the insertion sort threshold
        //if so just use insertion sort
    if (chunk_size <= INSERTION_SORT_THRESHOLD) {
        //use insertions sort
        mergesort_sm(A, 0, n, min);
        return;
    }


    //else use threads to sort each chunk
    //create thread/chunk array and fill with structs of chunks
    struct parallel_args chunk1;
    chunk1.A = A;
    chunk1.min = min;
    chunk1.start = 0;
    chunk1.end = (chunk_size + extra - 1);
    struct parallel_args chunks[MAX_THREADS];
    chunks[0] = chunk1;
    for (int i = 1; i < num_threads; i++){
        struct parallel_args arg;
        arg.A = A;
        arg.min = min;
        arg.start = (chunk_size * i) + extra;
        arg.end = arg.start + chunk_size - 1;
        chunks[i] = arg;
    }

    //step 2: fire off num_threads
    for (int i = 0; i < num_threads; i++){
        pthread_t p;
        pthread_create(&p, NULL, parallel_mergesort, &chunks[i]);
        chunks[i].tid = p; //should this line be before or after pthread_create?
    }

    //step 3: wait for all child threads to complete (Dracula theory)
    //should have an array of threads
    //for thread in threads
        //pthread_wait(thread)
    //done
    
    for (int i = 0; i< num_threads; i++){
        pthread_join(chunks[i].tid, NULL); 
    }
    //q is the middle, aka the last element(end) of the first of the two
    //do this "combine" for the first two thread's arrays, then use that resulting "combined" 
    //to combine with the next, and so on.
    //make sure to update the "ends" so that that I can continue to use them correctly
    merge_s(A, 0, );
    
    //step 4: final merge of returned sorted stuff
    //merge_s (single threaded version)
    mergesort_sm(A, 0, n, 0);
    return;

}

using namespace std;

int myMain(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "usage: " << argv[0] << " <array_size> <num_threads>" << endl;
        return 1;
    }
    int size = atoi(argv[1]);
    int t = atoi(argv[2]);

    int *A_ = new int[size];
    srandom(1);
    for (int i = 0; i < size; i++)
        A_[i] = random() % 100000;

    double end = 0;
    double start = getMilliSeconds();
    mergesort_mt(A_, size, t, 0);
    end = getMilliSeconds();
    cout << end - start << " " << t << endl;

    return 0;
}