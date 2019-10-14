#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
// gcc pwn1.c -o pwn  -fno-stack-protector
char *logo = ".....,, ......,,...,,,,,,,.,,.......,,..........DM8 ...,,,,,,,,,..,,,,,,, ......\n....MMMM.... MM...MMMMMMM...MM... MM.........MMMDMMMM.MMMMMMMMMM. MMMMMMM.......\n....MMMM.... MM ..MM........MM .NMM........+MM ... MM... 8MM.....MM .. ..... ...\n...MM NMM...MM ..MM,. ...  ..MMNM  .... . .MM. ..........MM .... MM.............\n...MN. MM .:MO.. MMMMMM .....MMM..........MM ...........NMM... .MMMMMMM.........\n..MM...MMD.MM ..MM.........MM?MM ........~MM............MM......MM.... .........\n.,MO....MM=MI...MM....... MM .+MM........MMM.....MD ...MMZ.....MM.....~~ Z.+ M .\n MM ....MMMM...MM77777..MM: ...MM.........MMM.~MMM ... MM.....,MM.....  M. M.M8.\n8M...... MM ..,MMMMMMM=MM......7MM........ MMMM.......MM,.....MM .......  ..   .\n.......................... ..... ... ...........................................";
void vuln(){
    uint8_t buf[32];
    read(0, buf, 0x100);
    return;
}

void init(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

int main(){
    init();
    puts(logo);
    printf("input your payload:\n");
    vuln();
    printf("Byebyebye~\n");
    return 0;
}
