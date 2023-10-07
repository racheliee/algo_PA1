//Checking run time
//at beginning of main
    int TIME = 0;
    clock_t start = clock();

//at end of main
    TIME += ((int)clock() - start) / (CLOCKS_PER_SEC / 1000);
    printf("TIME : %d ms\n", TIME);


//opening from input.txt and saving it
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);



//printing heaps
void print_heap(*Heap heap){
    for(int i = 0; i < heap->size; i++){
        printf("%d ", i);
    }
    printf("\n");
}

printf("lesser heap: ");
print_heap(&pq.lesser);
printf("greater heap: ");
print_heap(&pq.greater);
printf("lesser heap size: %d\n", pq.lesser.size);
printf("greater heap size: %d\n", pq.greater.size);