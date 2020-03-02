#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//some definitions
#define FALSE 0
#define TRUE 1
#define ADDR unsigned long
#define DATA unsigned long
#define BOOL char

typedef struct _MEMREQUEST{
    ADDR addr;
    BOOL is_write;
    DATA data;
} MEMREQUEST;

//misc. function
BOOL read_new_memrequest(FILE*, MEMREQUEST*);  //read new memory request from the memory trace file (already implemented)

//TODO: implement this function
//configure a cache
void init_cache();

//TODO: implement this function
//check if the memory request hits on the cache
BOOL isHit(MEMREQUEST *mem_request);

//TODO: implement this function
//write data to the cache. Data size is 4B
void write_data(MEMREQUEST *mem_request);

//TODO: implement this function
//insert a new block into the cache
//the initial values of the block are all zeros
void insert_to_cache(MEMREQUEST *mem_request);

//TODO: implement this function
//print the contents stored in the data storage of the cache
void print_contents();

//TODO: update this function so that some simulation statistics are calculated in it
//print the simulation statistics
void print_stats();


////global variables///
int cache_size=32768;               //cache size
int block_size=32;                  //block size

long long hit_cnt=0;               //total number of cache hits
long long miss_cnt=0;              //total number of cache misses
float miss_rate=0;                 //miss rate
long long dirty_block_num=0;       //total number of dirty blocks in cache at the end of simulation
float average_mem_access_time=0; //average memory access time
long miss_penalty=200;             //miss penalty
long cache_hit_time=1;             //cache hit time


/*
 * main
 *
 */
int main(int argc, char*argv[])  
{
    char trace_file[100];
	
    //Read through command-line arguments for options.
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') 
        {
            if (argv[i][1] == 's') 
                cache_size=atoi(argv[i+1]);
            
            if (argv[i][1] == 'b')
                block_size=atoi(argv[i+1]);
            
            if (argv[i][1] == 'f')
                strcpy(trace_file,argv[i+1]);
        }
    }
 
    //open the mem trace file
    FILE* fp = 0;
    fp=fopen(trace_file,"r");
    if(fp==NULL)
    {
        printf("[error] error opening file");
        fflush(stdout);
        exit(-1);   
    }

    ///main body of cache simulator /////////////////
    init_cache();   //configure a cache with the cache parameters specified in the input arguments
    
    while(1)
	{
        MEMREQUEST new_request;
        BOOL success=read_new_memrequest(fp, &new_request);  //read a new memory request from the memory trace file
        
        if(success!=TRUE)   //check the end of the trace file
            break;
        
        //check if the new memory request hits on the cache
        //if miss on the cache, insert a new block to the cache
        if(isHit(&new_request)==FALSE) 
            insert_to_cache(&new_request);  

        //if the request type is a write, write data to the cache
        if(new_request.is_write)
            write_data(&new_request);
    }
    print_contents();  //print the contentns (blocks) stored in the data storage of the cache
    print_stats();     //print simulation statistics
    
    fclose(fp);
    return 0;
}

/*
 * Function: read_new_memrequest
 * ____________________________
 * read a new memory request from the memory trace file
 *
 */
BOOL read_new_memrequest(FILE* fp, MEMREQUEST* mem_request)
{
    ADDR request_addr;
    DATA data;
    char request_type[5];
    char str_read[100];
    
    if(mem_request==NULL)
    {
        fprintf(stderr,"MEMREQUEST pointer is null!");
        exit(2);
    }

    if(fgets(str_read,100,fp))
    {
        str_read[strlen(str_read) - 1] = '\0';
        char *token = strtok(str_read," ");
        if(token)
        {
            mem_request->addr=strtol(token,NULL,16);

            token=strtok(NULL," ");
            if(strcmp(token,"R")==0)
                mem_request->is_write=FALSE;
            else if(strcmp(token,"W")==0){
                mem_request->is_write=TRUE;
                token= strtok(NULL, " ");
                if(token)
                    mem_request->data=atoi(token);
                else
                { 
                    fprintf(stderr,"[error] write request with no data!!\n");
                    exit(-1);
                }
            }
            else
            {
                printf("[error] unsupported request type!:%s\n",token);
                fflush(stdout);
                exit(-1);
            }
            return TRUE;
            
        }
    }       
    
    return FALSE;
}


/*
 * Function: print_contents
 * --------------------------
 * print the contents (blocks) stored in the cache
 *
 */
void print_contents(){
    printf("\n1.Cache contents");
    printf("\nindex     contents ");
    printf("\n----------------------------------------------\n");
    
    //TODO: print contents (blocks) stored in the data storage of the cache
    //for all blocks
    //   printf("%d: ", index)
    //   for all words in each block
    //      printf("%lu ", word)
    //   print("\n");
    //

}


/*
 * Function: print_stat
 * --------------------------
 * print the simulation statistics
 *
 */
void print_stats()
{
    //TODO: Calculate some simulation statistics


    //print the simualtion statistics
    printf("\n2.Simulation statistics\n");
    printf("total number of hits: %lld\n", hit_cnt);
    printf("total number of misses: %lld\n", miss_cnt);
    printf("miss rate: %f\n",miss_rate);
    printf("total number of dirty blocks: %lld\n",dirty_block_num);
    printf("average memory access time: %f\n",average_mem_access_time);
}


