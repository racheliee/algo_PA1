//pseudocode

//structure
typedef struct MinMaxHeap{
    int arr[MAX_SIZE/2+2];
    int size;
    int min_max; //min-max heap = 1 and max-min heap = 0
} Heap;

typedef struct PriorityQueue{
    Heap LH; //min-max heap stores the lesser half of values
    Heap GH; //min-max heap stores the greater half of values and the median 
} PQ;

PQ pq;


//helper functions
void swap(int* a, int* b){
	//swap a and b
}

int get_tree_level(int index){
	int level = 0;
    int node_index = index;

    while(node_index != 0){
        if(node_index % 2 ==0){
            node_index--;
        }
        node_index /= 2;
        level++;
    }

    return level;
}

int smallest_descent_index(heap, index){
	smallest_index = left child of index;
	minimum = left child of index;

	check if there is a right child and compare the minimum with it;

	check if tehre are grandchild and compare the minimum with it;

	return smallest_index
}

int largest_descent_index(heap, index){
	largest_index = left child of index;
	maximum = left child of index;

	check if there is a right child and compare the maximum with it;

	check if tehre are grandchild and compare the maximum with it;

	return largest_index
}

int is_a_grandchild(heap, g_index, c_index){
	if(4*g_index+3 >= c_index && c_index <= 4*g_index+6){
		return 1
	}
	return 0
}

//heap functions

int find_heap_max_index(Heap* heap){
	if heap.size = 1 or heap.min_max = 0 //max_min heap or heap size = 1
		return 0;

	if heap.min_max = 1: //finding max of min_max heap
		if heap.size = 2
			return 1
		else if heap.arr[1] > heap.arr[2]
			return 1
		else 
			return 2
}

int find_heap_min_index(Heap* heap){
	if heap.size = 1 or heap.min_max = 1
		return 0;

	if heap.min_max = 0:
		if heap.size = 2
			return 1
		else if heap.arr[1] < heap.arr[2]
			return 1
		else 
			return 2

}

int push_down_min_max(heap, index){
	while(2*index+1 < size) // while index node has children
		i := m
        if i is on a min level then: //tree_level(index)%2 == 0
            m := index of the smallest child or grandchild of i
            if h[m] < h[i] then:
                swap h[m] and h[i]
                if m is a grandchild of i then:
                    if h[m] > h[parent(m)] then:
                        swap h[m] and h[parent(m)]
                    endif
                else
                    break
                endif
            else
                break 
            endif
        else:
            m := index of the largest child or grandchild of i
            if h[m] > h[i] then:
                swap h[m] and h[i]
                if m is a grandchild of i then:
                    if h[m] < h[parent(m)] then:
                        swap h[m] and h[parent(m)]
                    endif
                else
                    break
                endif
            else
                break 
            endif
        endif
    endwhile
	
}

int push_down_max_min(heap, index){
	while(2*index+1 < size) // while index node has children
		i := m
        if i is on a min level then: //tree_level(index)%2 == 1
            m := index of the smallest child or grandchild of i
            if h[m] < h[i] then:
                swap h[m] and h[i]
                if m is a grandchild of i then:
                    if h[m] > h[parent(m)] then:
                        swap h[m] and h[parent(m)]
                    endif
                else
                    break
                endif
            else
                break 
            endif
        else:
            m := index of the largest child or grandchild of i
            if h[m] > h[i] then:
                swap h[m] and h[i]
                if m is a grandchild of i then:
                    if h[m] < h[parent(m)] then:
                        swap h[m] and h[parent(m)]
                    endif
                else
                    break
                endif
            else
                break 
            endif
        endif
    endwhile
	
}

int pop_min(Heap* heap){
	int min_index = find_heap_min_index(heap)
	int min = heap[min_index]

	heap.size--;
	heap.arr[min_index] = heap.arr[heap.size]

	if heap.min_max = 1
		push_down_min_max(heap, min_index);
	else
		push_down_max_min(heap, min_index);

	return min
}

int pop_max(Heap* heap){
	int max_index = find_heap_max_index(heap)
	int max = heap[max_index]

	decrease heap size
	heap.arr[max_index] = heap.arr[heap.size]

	if heap.min_max = 1
		push_down_min_max(heap, min_index);
	else
		push_down_max_min(heap, min_index);

	return max
}

//wikipedia
void push_up_max(heap, index){
	while i has a grandparent and heap(grandpa) < heap(i): //grandparent exists if index >= 3
		swap(heap(grandpa), heap(i))
		i = grandpa_index
	end while
}

void push_up_min(heap, index){
	while i has a grandparent and heap(i) < heap(grandpa) :
		swap(heap(grandpa), heap (i))
		i = grandpa_index
	end while
}

void push_up_min_max(Heap* heap, int index){
	if i is not the root then:
        if i is on a min level then: //tree_level(index)%2 == 0
            if h[i] > h[parent(i)] then:
                swap h[i] and h[parent(i)]
                PUSH-UP-MAX(h, parent(i))
            else:
                PUSH-UP-MIN(h, i)
            endif
        else:
            if h[i] < h[parent(i)] then:
                swap h[i] and h[parent(i)]
                PUSH-UP-MIN(h, parent(i))
            else:
                PUSH-UP-MAX(h, i)
            endif
        endif
}

void push_up_max_min(Heap* heap, int index){
	if i is not the root then:
        if i is on a min level then: //tree_level(index)%2 == 1
            if h[i] > h[parent(i)] then:
                swap h[i] and h[parent(i)]
                PUSH-UP-MAX(h, parent(i))
            else:
                PUSH-UP-MIN(h, i)
            endif
        else:
            if h[i] < h[parent(i)] then:
                swap h[i] and h[parent(i)]
                PUSH-UP-MIN(h, parent(i))
            else:
                PUSH-UP-MAX(h, i)
            endif
        endif
}


void heap_insert(Heap* heap, int element){
	heap.arr[size] = element

	if heap.min_max = 1
		push_up_min_max(heap, size)
	else
		push_up_max_min(heap, size)

	heap size ++;
}

//priority queue functions
//instances where pq is empty will be handled in the main function
void initPriorityQueue(){
	heap size of pq set to 0

	LH.min_max = 0
	GH.min_max = 1
}

void insert(int element){
	if element is greater than root of GH
		if LH.size < GH.size:
			heap_insert(LH, pop_min(GH))
		heap_insert(GH, element)
		
	if element is smaller than root of LH
		if LH.size == GH.size:
			heap_insert(GH, pop_max(LH))
		heap_insert(LH, element)
}

int find_min(){
	if LH.size = 0
		return root node of GH

	return LH.arr[find_heap_min_index(LH)];
}

int find_median(){
	if LH.size = GH.size:
		return root of LH
	if LH is smaller than GH:
		return root of GH
}

int find_max(){
	return GH.arr[find_heap_max_index(GH)];
}

int delete_min(){

	if GH.size = LH.size:
		pop_min(LH)
	if LH.size < GH.size:
		pop_min(LH)
		heap_insert(LH, pop_min(GH))
}

int delete_median(){
	if LH.size = GH.size:
		return root of LH and delete it
	if LH is smaller than GH:
		return root of GH and delete it

}

int delete_max(){
	if GH.size = LH.size: //avoinding GH getting smaller than LH
		heap_insert(GH, pop_max(LH)) 
		
	return pop_max(GH) //max is going to be in gh anyways so pop max here

}
