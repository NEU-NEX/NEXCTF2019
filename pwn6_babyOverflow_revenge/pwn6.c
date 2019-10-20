#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct WIFE{
    int size;
    char* ctx;
} WIFE;

WIFE wife[10];

int get_num()
{
    int result;
    char input[48];
    char *end_ptr;    
    read(0, input, 48);
    result = strtol(input, &end_ptr, 0);
    return result;
}

void print_menu()
{
    puts("Welcome to baby Overflow Revenge!");
    puts("1 add wife");
    puts("2 delete wife");
    puts("3 show wife");
    puts("4 edit wife");
    puts("5 exit");
    printf("your choice:");
}

void show_wife()
{
    int index;
    printf("Input the index:");
    index = get_num();
    if (index < 0 || index > 9)
        exit(1);
    if(wife[index].ctx == NULL)
        exit(1);
    printf("your wife:");
    puts(wife[index].ctx);
}

void add_wife()
{
    int index;
    int length;
    printf("Input the index:");
    index = get_num();
    if (index < 0 || index > 9)
        exit(1);
    printf("How long you will enter:");
    length = get_num();
    wife[index].ctx = malloc(length);
    wife[index].size = length;
    printf("please enter your wife:");
    read(0, wife[index].ctx, wife[index].size);
    printf("you have a new wife!\n");
}

void delete_wife()
{
    int index;
    printf("enter index:");
    index = get_num();
    if (index < 0 || index > 9)
        exit(1);
    free(wife[index].ctx);
    wife[index].size = 0;
    wife[index].ctx = 0;
    puts("say byebye to your wife!");
}

void edit_wife()
{
    int idx;
    printf("enter index:");
    idx = get_num();
    if (idx < 0 || idx > 9)
        exit(1);
    printf("enter content:");
    read(0, wife[idx].ctx, wife[idx].size + 1); // bug
}


char *logo = ".....,, ......,,...,,,,,,,.,,.......,,..........DM8 ...,,,,,,,,,..,,,,,,, ......\n....MMMM.... MM...MMMMMMM...MM... MM.........MMMDMMMM.MMMMMMMMMM. MMMMMMM.......\n....MMMM.... MM ..MM........MM .NMM........+MM ... MM... 8MM.....MM .. ..... ...\n...MM NMM...MM ..MM,. ...  ..MMNM  .... . .MM. ..........MM .... MM.............\n...MN. MM .:MO.. MMMMMM .....MMM..........MM ...........NMM... .MMMMMMM.........\n..MM...MMD.MM ..MM.........MM?MM ........~MM............MM......MM.... .........\n.,MO....MM=MI...MM....... MM .+MM........MMM.....MD ...MMZ.....MM.....~~ Z.+ M .\n MM ....MMMM...MM77777..MM: ...MM.........MMM.~MMM ... MM.....,MM.....  M. M.M8.\n8M...... MM ..,MMMMMMM=MM......7MM........ MMMM.......MM,.....MM .......  ..   .\n.......................... ..... ... ...........................................";
int main()
{
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    puts(logo);
    int choice;
    while (1){
        print_menu();
        choice = get_num();
        switch (choice){
            case 1:
                add_wife();
                break;
            case 2:
                delete_wife();
                break;
            case 3:
                show_wife();
                break;
            case 4:
                edit_wife();
                break;
            case 5:
                exit(0);
            default:
                puts("invoid!");
        }
    }
    return 0;
}
