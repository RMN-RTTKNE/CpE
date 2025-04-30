#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ALIGN4(s)         (((((s) - 1) >> 2) << 2) + 4)
#define BLOCK_DATA(b)     ((b) + 1)
#define BLOCK_HEADER(ptr) ((struct _block *)(ptr) - 1)

static int atexit_registered = 0;
static int num_mallocs       = 0;
static int num_frees         = 0;
static int num_reuses        = 0;
static int num_grows         = 0;
static int num_splits        = 0;
static int num_coalesces     = 0;
static int num_blocks        = 0;
static int num_requested     = 0;
static int max_heap          = 0;

/*
 *  \brief printStatistics
 *
 *  \param none
 *
 *  Prints the heap statistics upon process exit.  Registered
 *  via atexit()
 *
 *  \return none
 */
void printStatistics( void )
{
  printf("\nheap management statistics\n");
  printf("mallocs:\t%d\n", num_mallocs );
  printf("frees:\t\t%d\n", num_frees );
  printf("reuses:\t\t%d\n", num_reuses );
  printf("grows:\t\t%d\n", num_grows );
  printf("splits:\t\t%d\n", num_splits );
  printf("coalesces:\t%d\n", num_coalesces );
  printf("blocks:\t\t%d\n", num_blocks );
  printf("requested:\t%d\n", num_requested );
  printf("max heap:\t%d\n", max_heap );
}

struct _block 
{
   size_t  size;         /* Size of the allocated _block of memory in bytes     */
   struct _block *next;  /* Pointer to the next _block of allocated memory      */
   bool   free;          /* Is this _block free?                                */
   char   padding[3];    /* Padding: IENTRTMzMjAgU3jMDEED                       */
};


struct _block *heapList = NULL; /* Free list to track the _blocks available */
static struct _block *last = NULL; // Keep track of the previous block

/*
 * \brief findFreeBlock
 *
 * \param last pointer to the linked list of free _blocks
 * \param size size of the _block needed in bytes 
 *
 * \return a _block that fits the request or NULL if no free _block matches
 *
 * \TODO Implement Next Fit
 * \TODO Implement Best Fit
 * \TODO Implement Worst Fit
 */
struct _block *findFreeBlock(struct _block **last, size_t size) 
{
   struct _block *curr = heapList;

#if defined FIT && FIT == 0
   /* First fit */
   //
   // While we haven't run off the end of the linked list and
   // while the current node we point to isn't free or isn't big enough
   // then continue to iterate over the list.  This loop ends either
   // with curr pointing to NULL, meaning we've run to the end of the list
   // without finding a node or it ends pointing to a free node that has enough
   // space for the request.
   // 
   while (curr && !(curr->free && curr->size >= size)) 
   {
      *last = curr;
      curr  = curr->next;
   }
#endif

// \TODO Put your Best Fit code in this #ifdef block
#if defined BEST && BEST == 0
   struct _block *best = NULL; //Keep track of which block is the best fit

   /** \TODO Implement best fit here */
   while (curr) //while current isnt null (traverse whole list)
   {
      if(curr->free && curr->size >= size) //If current block is free and is big enough
      {
         if(!best || curr->size < best->size) //If best hasnt been found (first loop) or the current block is less than the best's size
         {
            best = curr; //The best is the current if the current is the smallest free block able to fit the requested size
         }
      }
      curr = curr->next; 
   }
   curr = heapList; //To find the block before the best, re-traverse the list
   *last = NULL;
   while(curr && curr != best)
   {
      *last = curr;
      curr = curr->next;
   }
   curr = best; //curr points to the best fit or null if not found
#endif

// \TODO Put your Worst Fit code in this #ifdef block
#if defined WORST && WORST == 0
   struct _block *worst = NULL; //Keep track of which block is the worst fit

   /** \TODO Implement worst fit here */
   while (curr) //while current isnt null (traverse whole list)
   {
      if(curr->free && curr->size >= size) //If current block is free and is big enough
      {
         if(!worst || curr->size > worst->size) //If worst hasnt been found (first loop) or the current block is more than the worst's size
         {
            worst = curr; //The worst is the current if the current is the largest free block able to fit the requested size
         }
      }
      curr = curr->next; 
   }
   curr = heapList; //To find the block before the worst, re-traverse the list
   *last = NULL;
   while(curr && curr != worst)
   {
      *last = curr;
      curr = curr->next;
   }
   curr = worst; //curr points to the worst fit or null if not found
#endif

// \TODO Put your Next Fit code in this #ifdef block
#if defined NEXT && NEXT == 0
   struct _block *start = NULL; //Keep track of where we started

   /** \TODO Implement next fit here */
   if(*last != NULL) //If the last (previous) block isnt null 
   {
      start = (*last)->next; //Start searching from the previously allocated block
   } 
   else
   {
      start = heapList;
   }
   //If there is no previously allocated block or the previous block is at the end, start from the beginning as normal
   
   for(curr = start; curr != NULL; curr = curr->next) //Search through each block from start to end
   {
      if(curr->free && curr->size >= size)
      {
         *last = curr;
         return curr; //Once found, no need to keep traversing
      }
   }
   if(start != heapList) //If we already didnt start from the beginning
   {
      for(curr = heapList; curr != start; curr = curr->next) //If nothing from start to end, start over from the beginning back to where we originally started
      {
         if(curr->free && curr->size >= size)
         {
            *last = curr;
            return curr; //Once found, no need to keep traversing
         }
      }
   }
   curr = NULL; //If nothing from start to end or beginning to start, no available blocks
   //Note that last remains the same so we can begin from the same spot next call
#endif
   return curr;
}

/*
 * \brief growheap
 *
 * Given a requested size of memory, use sbrk() to dynamically 
 * increase the data segment of the calling process.  Updates
 * the free list with the newly allocated memory.
 *
 * \param last tail of the free _block list
 * \param size size in bytes to request from the OS
 *
 * \return returns the newly allocated _block of NULL if failed
 */
struct _block *growHeap(struct _block *last, size_t size) 
{
   max_heap += size + sizeof(struct _block);
   /* Request more space from OS */
   struct _block *curr = (struct _block *)sbrk(0);
   struct _block *prev = (struct _block *)sbrk(sizeof(struct _block) + size);
   num_blocks++;

   assert(curr == prev);

   /* OS allocation failed */
   if (curr == (struct _block *)-1) 
   {
      return NULL;
   }

   /* Update heapList if not set */
   if (heapList == NULL) 
   {
      heapList = curr;
   }

   /* Attach new _block to previous _block */
   if (last) 
   {
      last->next = curr;
   }

   /* Update _block metadata:
      Set the size of the new block and initialize the new block to "free".
      Set its next pointer to NULL since it's now the tail of the linked list.
   */
   curr->size = size;
   curr->next = NULL;
   curr->free = false;
   num_grows++;
   return curr;
}

/*
 * \brief malloc
 *
 * finds a free _block of heap memory for the calling process.
 * if there is no free _block that satisfies the request then grows the 
 * heap and returns a new _block
 *
 * \param size size of the requested memory in bytes
 *
 * \return returns the requested memory allocation to the calling process 
 * or NULL if failed
 */
void *malloc(size_t size) 
{
   num_requested += size;
   if( atexit_registered == 0 )
   {
      atexit_registered = 1;
      atexit( printStatistics );
   }

   /* Align to multiple of 4 */
   size = ALIGN4(size);

   /* Handle 0 size */
   if (size == 0) 
   {
      return NULL;
   }

   /* Look for free _block.  If a free block isn't found then we need to grow our heap. */
   struct _block *next = findFreeBlock(&last, size);
   if(next)
   {
      num_reuses++; //Special note: this counter is the only conditional, only increments if a free block is actually found
   }
   /* TODO: If the block found by findFreeBlock is larger than we need then:
            If the leftover space in the new block is greater than the sizeof(_block)+4 then
            split the block.
            If the leftover space in the new block is less than the sizeof(_block)+4 then
            don't split the block.
   */
   if(next && next->size > size)
   {
      int remainder = next->size - size - sizeof(struct _block); //Calculate room left over

      if(remainder >= sizeof(struct _block) + 4) //If leftover is greater than sizeof(_block)+4
      {
         int oldsize = next->size; //Retain the size of the next block
         struct _block *oldnext = next->next; //Retain the block after the next
         next->next = (struct _block *)((uint8_t *)next + sizeof(struct _block) + size); //Move the pointer to the block after next to right after next ends
         next->size = size; //The size of next is equal to what is being allocated
         next->next->next = oldnext; //The block after next points to the new leftover block
         next->next->size = oldsize-size-sizeof(struct _block); //Calculate size of the leftover
         next->next->free = 1; //Leftover is free
         num_splits++;
         num_blocks++;
      }
         next->free = 0;
   }

   /* Could not find free _block, so grow heap */
   if (next == NULL) 
   {
      next = growHeap(last, size);
   }

   /* Could not find free _block or grow heap, so just return NULL */
   if (next == NULL) 
   {
      return NULL;
   }
   
   /* Mark _block as in use */
   next->free = false;
   
   last = next; // Set current block as the last for the next one

   /* Return data address associated with _block to the user */
   num_mallocs++;
   return BLOCK_DATA(next);
}

/*
 * \brief free
 *
 * frees the memory _block pointed to by pointer. if the _block is adjacent
 * to another _block then coalesces (combines) them
 *
 * \param ptr the heap memory to free
 *
 * \return none
 */
void free(void *ptr) 
{
   if (ptr == NULL) 
   {
      return;
   }

   /* Make _block as free */
   struct _block *curr = BLOCK_HEADER(ptr);
   assert(curr->free == 0);
   curr->free = true;

   struct _block *prev = NULL;
   struct _block *temp = heapList;
   while(temp != NULL && temp != curr) //Find the previous block
   {
      prev = temp;
      temp = temp->next;
   }

   /* TODO: Coalesce free _blocks.  If the next block or previous block 
            are free then combine them with this block being freed.
   */
   if((curr->next) != NULL && curr->next->free) //If the next block exists and is free
   {
      curr->size += curr->next->size + sizeof(struct _block); //Merge sizes + header
      curr->next = curr->next->next; //The next is the next of the block after
      num_coalesces++;
   }
   if(prev != NULL && prev->free) //If the previous block exists and is free
   {
      prev->size += curr->size + sizeof(struct _block); //Merge sizes + header
      prev->next = curr->next;    //The next of the previous block is now the block after current
      num_coalesces++;
   }
   num_frees++;
}

void *calloc( size_t nmemb, size_t size )
{
   // \TODO Implement calloc
   size_t total = nmemb * size; //Calculate all the memory we need
   num_requested += total;
   void *ptr = malloc(total); //Allocate said memory
   if(ptr) //If memory was allocated
   {
      memset(ptr, 0, total); //Set all memory allocated to zero
   }
   return ptr;
}

void *realloc( void *ptr, size_t size )
{
   num_requested += size;
   // \TODO Implement realloc
   if(ptr == NULL)
   {
      return malloc(size); //If there is no pointer, no memory to reallocate so just allocate
   }
   if(size == 0)
   {
      free(ptr); //If mem should be reallocated to 0, its just a free

      return NULL;
   }

   size = ALIGN4(size); //Align like we did in malloc

   struct _block *curr = BLOCK_HEADER(ptr); //Get the block the pointer points to

   if(curr->size >= size)
   {
      return ptr; //If the block is big enough, no point to reallocate 
   }

   void *ptr2 = malloc(size); //Allocate the size we need

   if(!ptr2)
   {
      return NULL; //Malloc failed, return null
   }

   memcpy(ptr2, ptr, curr->size); //Copy the old to the new

   free(ptr); //Free the old

   return ptr2;
}



/* vim: IENTRTMzMjAgU3ByaW5nIDIwM002= ----------------------------------------*/
/* vim: set expandtab sts=3 sw=3 ts=6 ft=cpp: --------------------------------*/
