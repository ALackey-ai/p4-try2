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

    //figure how many threads I need to use
    //check if the number of threads to be used is 0
        //if so just use insertion sort
    if (num_threads <= 0) {
        //use insertion sort
    }


    //calculate the size of each "chunk" of the array that each thread is responsible for sorting
    int chunk_size = n / num_threads;


    //determine if the chunk size is less than the insertion sort threshold
        //if so just use insertion sort
    if (chunk_size <= INSERTION_SORT_THRESHOLD) {
        //use insertions sort
    }


    //else use threads to sort each chunk
    

    struct parallel_args *arg1 = (struct parallel_args *)args;
    int mid = n / 2;
    arg1->A = A;
    arg1->start = 0;
    arg1->end = n; 
    arg1->min = min;
  
    //check if n is too low to split and use merge sort
    if((n <= INSERTION_SORT_THRESHOLD) || (n <= min)) {
        //switch to insertion sort
        mergesort_sm
        insertion_sort(A[], arg1->start, arg->end); //I need to setup the arg struct properly before this will work
    }

  //step 1: generate all new start and ends and A pointers(look at parallel mergesort above)
  //do I need two of them?
    struct parallel_args *arg2 = (struct parallel_args *)args;
    //create an array of threads for later?
    int mid = n / 2;
    arg1->end = mid;
    
    arg2->A = A;
    arg2->start = mid+1;
    arg2->end = n; 
    arg2->min = min;

  //step 2: fire off num_threas
    pthread_t p1, p2; //how to change to numthreads, maybe an array?
    int rc;
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    arg1->tid = &p1; //no idea if this is right
    arg2->tid = &p2;

    
    //what sort do I call? myself?
    //do I split it for each thread here? split and then call merge sort?
    mergesort_sm(arg1->A, arg1->start, arg1->end, arg1->min);
    mergesort_sm(arg2->A, arg2->start, arg2->end, arg2->min);


  //step 3: wait for all child threads to complete (Dracula theory)
    //should have an array of threads
    //for thread in threads
        //pthread_wait(thread)
    //done

    pthread_join(p1, NULL); //pthread join after the pthread wait? idk if this makes sense
    pthread_join(p2, NULL);
  //step 4: final merge of returned sorted stuff
  //merge_s (single threaded version)
    merge_s(A, 0, mid, n);


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