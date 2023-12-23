#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>


void tampilanAwal() {
	system("cls");
	Sleep(750);
	puts("==================================");
	puts("PERMAINAN ANGKA BOMB");
	puts("==================================\n");
	Sleep(500);
	puts("1. CARA BERMAIN");
	Sleep(500);
	puts("2. MULAI PERMAINAN");
	Sleep(500);
	puts("3. CREATOR");
	Sleep(500);
	printf("SILAKAN PILIH ANGKA: ");
}

void caraMain() {
	puts("\n1. Permainan disarankan dimainkan secara multiplayer");
	Sleep(1000);
	puts("2. Silakan masukkan jumlah dan nama pemain dulu supaya dapat giliran masing-masing");
	Sleep(2500);
	puts("3. Angka bomb akan dibangkitkan secara random dan tidak boleh disebutkan oleh pemain");
	Sleep(2500);
	puts("4. Sesuai gilirannya, pemain memasukkan angka dari rentang 1-100 (atau angka yang ditentukan).");
	Sleep(2500);
	puts("Jika itu adalah angka bomb, pemain tersebut kalah. Jika tidak,");
	Sleep(2500);
	puts("rentang akan dipersempit dan begitu seterusnya");
	Sleep(500);
}

void aboutMe() {
	puts("\n========================================================================");
	Sleep(1000);
	puts("STEPANUS IMANUEL - 2702355574 - COMPUTER SCIENCE - BINUS@BANDUNG");
	Sleep(1500);
	puts("Kalau ada saran atau kritik, line aja @stepanusimnl");
	Sleep(1500);
	puts("Terima kasih buat yang udah mau main :)");
	Sleep(1000);
	puts("========================================================================");
	Sleep(500);
}

void acakPlayer(int *player, char (*nama)[32]) {
	int i;
	for(i = 0; i < *player; i++) {
		int random = rand() % *player;
		char temp[32];
		strcpy(temp,nama[i]);
		strcpy(nama[i], nama[random]);
		strcpy(nama[random], temp);
	}
}

void mulaiGame(int *player, char (*nama)[32], int *max, FILE *write) {
	srand(time(0));
	acakPlayer(player, nama);
	
	int bomb = rand() % *max + 1;
	int input = 0;
	int first = 0;
	int last = *max + 1;
	int i = 0;
	while(1) {
		if (i == *player - 1) {
			i = 0;
		} else {
			i++;
		}
		printf("Giliran %s: ", nama[i]);
		scanf("%d", &input);
		
		while(input <= first || input >= last) {
			printf("%s tolong masukkin angkanya %d - %d aja yaa\n", nama[i], first+1, last-1);
			printf("Giliran %s: ", nama[i]);
			scanf("%d", &input);
			getchar();
		}
		
		if(input == bomb) {
			printf("%s KALAH\n", nama[i]);
			
			time_t t;
			t = time(NULL);
			char *date = ctime(&t); // has new line in it
			
			fprintf(write, "===========================\n");
			fprintf(write, "%s\n", date);
			fprintf(write, "Kalah: %s\n", nama[i]);
			fprintf(write, "===========================\n");
			
			break;
		} else {
			if(input > bomb) {
				last = input;
				printf("%d - %d\n", first+1, last-1);
			} else {
				first = input;
				printf("%d - %d\n", first+1, last-1);					
			}
		}
	}	
}

void checkDatabaseExist(FILE *database) {
	if(database == NULL) {
		database = fopen("database.bin", "ab");
	}
	
	fseek(database, 0, SEEK_END);
	if(ftell(database) == 0) fprintf(database, "HISTORY PERMAINAN\n");
}


int main() {

	FILE *database;
	
	bool mainLagi = true;
	
	while(mainLagi) {
		int angka;
	
		tampilanAwal();
		
		scanf("%d", &angka);
		getchar();
		
		if(angka == 1) caraMain();
		else if(angka == 2) {
			int player, max;
			
			printf("\nKetikkan angka maksimal yang diinginkan: ");
			scanf("%d", &max);
			getchar();
			printf("Range permainan angka bomb: 1 - %d\n", max);
			
			printf("Jumlah pemain: ");
			scanf("%d", &player);
			getchar();
			
			int i;
			char nama[player][32];
			for(i = 0; i < player; i++) {
				printf("Nama pemain ke-%d: ", i+1);
				scanf("%s", nama[i]);
				getchar();
			}
			
			database = fopen("database.bin", "ab+");
			
			checkDatabaseExist(database);
			
			mulaiGame(&player, nama, &max, database);
			fclose(database);
			
		} else if(angka == 3) aboutMe();
		else puts("Pilih 1 - 3 yaa");
		
		printf("\ningin kembali ke menu? 1 jika ya, lainnya jika tidak\n");
		scanf("%d", &mainLagi);
		getchar();
	}
	
	return 0;
}
