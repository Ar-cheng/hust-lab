#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
typedef struct
{
    int valid;      //有效位
    int tag;        //标识位
    int lru_number; //LRU算法需要位
} Line;

typedef struct
{
    Line *lines; //一组中所有的行
} Set;

typedef struct
{
    int set_num;  //组数
    int line_num; //行数
    Set *sets;    //cache
} Cache;

void init_Cache(int s, int E, int b, Cache *cache);
int Cache_fresh(Cache *cache, int set_num, int tag_num);
void read_cache(Cache *cache, int addr, int size, int set_num, int tag_num, int cflag);
void print_usage(); //打印菜单

int miss_count, hit_count, evict_count;

int main(int argc, char **argv)
{
    int s, E, b, cflag;
    char trace_file[100], opt;

    int addr, size, set_num, tag_num;
    cflag = miss_count = hit_count = evict_count = 0;

    //read args
    const char *optstring = "hvs:E:b:t:";
    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_usage();
            break;
        case 'v':
            cflag = 1;
            break;
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            strcpy(trace_file, optarg);
            break;
        default:
            print_usage();
            exit(0);
        }
    }

    Cache cache;
    init_Cache(s, E, b, &cache);

    FILE *tracefile = fopen(trace_file, "r");
    while (fscanf(tracefile, "%c %x,%d", &opt, &addr, &size) != EOF)
    {
        if (opt == 'I') //ignore
            continue;

        set_num = addr >> b & ((1 << s) - 1);
        tag_num = addr >> (s + b);

        if (cflag == 1)
            printf("%c %x,%d ", opt, addr, size);
        if (opt == 'S')
            read_cache(&cache, addr, size, set_num, tag_num, cflag);
        if (opt == 'M')
        {
            read_cache(&cache, addr, size, set_num, tag_num, cflag);
            read_cache(&cache, addr, size, set_num, tag_num, cflag);
        }
        if (opt == 'L')
            read_cache(&cache, addr, size, set_num, tag_num, cflag);
        if (cflag == 1)
            printf("\n");
    }
    printSummary(hit_count, miss_count, evict_count);
    return 0;
}

void init_Cache(int s, int E, int b, Cache *cache)
{ //初始化cache
    int i, j;
    cache->set_num = 2 << s; //2^s sets
    cache->line_num = E;     //E lines per set
    cache->sets = (Set *)malloc(cache->set_num * sizeof(Set));
    for (i = 0; i < cache->set_num; i++)
    {
        cache->sets[i].lines = (Line *)malloc(E * sizeof(Line));
        for (j = 0; j < E; j++)
        {
            cache->sets[i].lines[j].valid = 0;
            cache->sets[i].lines[j].lru_number = 0;
        }
    }
    return;
}

int Cache_fresh(Cache *cache, int set_num, int tag_num)
{ //fresh cache : add or evict
    int i;
    int isfull = 1;
    for (i = 0; i < cache->line_num; i++)
    {
        if (cache->sets[set_num].lines[i].valid == 0)
        {
            isfull = 0;
            break;
        }
    }
    if (isfull == 0)
    { //set未满
        cache->sets[set_num].lines[i].valid = 1;
        cache->sets[set_num].lines[i].tag = tag_num;
        //update lru_num
        int j = 0;
        cache->sets[set_num].lines[i].lru_number = 0;
        for (j = 0; j < cache->line_num; j++)
        { //更新其他行的lru_number
            if (j != i)
                cache->sets[set_num].lines[j].lru_number++;
        }
    }
    else
    { //set已满,找替换行
        int evict_Index = 0;
        int maxLru = 0;
        for (i = 0; i < cache->line_num; i++)
        { //find max lru_num
            if (cache->sets[set_num].lines[i].lru_number > maxLru)
            {
                maxLru = cache->sets[set_num].lines[i].lru_number;
                evict_Index = i;
            }
        }
        cache->sets[set_num].lines[evict_Index].valid = 1;
        cache->sets[set_num].lines[evict_Index].tag = tag_num;
        //update lru_num
        int j = 0;
        cache->sets[set_num].lines[evict_Index].lru_number = 0;
        for (j = 0; j < cache->line_num; j++)
        { //更新其他行的lru_number
            if (j != evict_Index)
                cache->sets[set_num].lines[j].lru_number++;
        }
    }
    return isfull;
}

void read_cache(Cache *cache, int addr, int size, int set_num, int tag_num, int cflag)
{
    int i = 0;
    int ismiss = 1;
    while (i < cache->line_num) //judge miss or no
    {
        if (cache->sets[set_num].lines[i].valid == 1 && cache->sets[set_num].lines[i].tag == tag_num)
        { //命中了
            ismiss = 0;
            //update lru_num
            int j = 0;
            cache->sets[set_num].lines[i].lru_number = 0;
            for (j = 0; j < cache->line_num; j++)
            { //更新其他行的lru_number
                if (j != i)
                    cache->sets[set_num].lines[j].lru_number++;
            }
        }
        i++;
    }

    if (ismiss == 1)
    { //miss
        miss_count++;
        if (cflag == 1)
            printf("miss ");
        if (Cache_fresh(cache, set_num, tag_num) == 1)
        { //set已满
            evict_count++;
            if (cflag == 1)
                printf("eviction ");
        }
    }
    else
    { //hit
        hit_count++;
        if (cflag == 1)
            printf("hit ");
    }
}

void print_usage()
{ //打印帮助文档
    printf("Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
    printf("Options:\n");
    printf("-h       Print help message.\n");
    printf("-v       Display trace information.\n");
    printf("-s <s>   Number of set index bits.\n");
    printf("-E <E>   Number of lines per set.\n");
    printf("-b <b>   Number of address bits.\n");
    printf("-t <tracefile> \n\n\n");
}