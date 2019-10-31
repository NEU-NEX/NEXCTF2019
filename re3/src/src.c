#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include "aes.h"

// flag{i_th1nk_reverse_1n_CTFisok}
uint8_t key[0x10] = {49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49};
uint8_t vdata[0x20] = {231, 91, 138, 202, 66, 39, 70, 65, 232, 10, 217, 90, 154, 127, 46, 17, 83, 187, 203, 218,  
233, 152, 160, 195, 162, 20, 46, 59, 38, 94, 51, 151};

int judge(char* ttt);

int main(){
	char in[40];
	scanf("%39s", in);
	int len = strlen(in);
	if(len != 32){
		printf("Wrong!\n");
		exit(0);
	}

	int (*p)(char* s);
	p = judge;
	mprotect(0x400000, 0xF000, PROT_READ|PROT_WRITE|PROT_EXEC);
	uint8_t* pt = (uint8_t*)p;
	/*decrypt here*/
	for(int i=0;i<154;i++){
		uint8_t tmp = pt[i];
		pt[i] = tmp^0x99;
	}

	if(judge(in)){
        printf("Correct!\n");
    }
	else{
		printf("Wrong!\n");
	}
	exit(0);
}

int judge(char* ttt){
	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);
	AES_ECB_decrypt(&ctx, vdata);
	AES_ECB_decrypt(&ctx, vdata+0x10);
	if(0 == strcmp(ttt, vdata)){
		return 1;
	}
	return 0;
}