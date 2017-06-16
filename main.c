#include "funcs.h"


_Bool exit_status = FALSE;
ushort my_crutch = 0;


/*
 ****************************************
 **************************************** 
 ****************************************
 ****************************************
*/

int main(int argc, char** argv)
{
	
	// Склады.
	uint storage[ITEM_COUNT];
	// Семафоры для складов.
	_Bool storage_status[ITEM_COUNT] = { STOR_FREE };

	// Параметры для передачи потоку-погрузчику.
	struct loader_thr_params lpr = {.storage = storage, .storage_stat = storage_status, .count = ITEM_COUNT};

	// Тут параметры для передачи потокам-покупателям.
	struct buyer2_thr_params buy_parms1 = {.storage = storage, .storage_stat = storage_status, .count = ITEM_COUNT, .buy_id = 1};
	struct buyer2_thr_params buy_parms2 = {.storage = storage, .storage_stat = storage_status, .count = ITEM_COUNT, .buy_id = 2};
	struct buyer2_thr_params buy_parms3 = {.storage = storage, .storage_stat = storage_status, .count = ITEM_COUNT, .buy_id = 3};

	// ID потоков.
	pthread_t loader_id, buyer1, buyer2, buyer3;
	// Статусы потоков.
	int thr_status, thr_status_addr;

	printf("Инициализироуем склады...\n");
	for(int i = 0; i < 5; i++) {
		ushort tmp = my_rand(1000, 1500);
		storage[i] = tmp;
		printf("Склад %d = %d.\n", i+1, tmp);
	}


	printf("Стартует погрузчик...\n");
	thr_status = pthread_create(&loader_id, NULL, loader_thr_wrapper, &lpr);
	if (thr_status != 0)
		printf("D_Error: %d\n", thr_status);

	printf("Стартует покупатель 1...\n");
	thr_status = pthread_create(&buyer1, NULL, buyer2_thr_wrapper, &buy_parms1);
	if (thr_status != 0)
		printf("D_Error: %d\n", thr_status);

	printf("Стартует покупатель 2...\n");
	thr_status = pthread_create(&buyer2, NULL, buyer2_thr_wrapper, &buy_parms2);
	if (thr_status != 0)
		printf("D_Error: %d\n", thr_status);


	printf("Стартует покупатель 3...\n");
	thr_status = pthread_create(&buyer3, NULL, buyer2_thr_wrapper, &buy_parms3);
	if (thr_status != 0)
		printf("D_Error: %d\n", thr_status);


	//pthread_detach(buyer1);

	//pthread_detach(buyer2);

	//pthread_detach(buyer3);
	
	// Проверяем количество закупившихся.
	while (my_crutch < BUYERS_COUNT)
		sleep(2);
	exit_status = TRUE;

	pthread_join(loader_id, (void**)&thr_status_addr);

	printf("Done!\n");

	return 0;
}

