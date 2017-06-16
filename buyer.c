#include "funcs.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Функция поиска следующего (случайного)
// свободного склада, с достаточным кол-вом товара.
inline static uint free_stor(uint* storage, _Bool* storage_stat, ushort count, uint buy_demand);

// Функция покупателя. v02
void buyer2(uint* storage, _Bool* storage_stat, ushort count, ushort buy_id)
{
	// Общая потребность.
	uint demand = my_rand(2500, 3000);
	// Переменная хранящая номер склада.
	uint stor_n;
	// Разовая потребность.
	uint buy_count;


	while(TRUE) {
		printf("Покупатель: %d . Потребность осталось: %d\n", buy_id, demand);
		// Проверяем что, остаточная общая потребность
		// больше разовой, чтобы не купить лишнего.
		// Если, остаточная меньше минимально возможной разовой,
		// присваеваем её значение разовой.
		if (demand <= (buy_count = my_rand(400, 500)))
			buy_count = demand;

		stor_n = free_stor(storage, storage_stat, count, buy_count);
		printf("Покупатель: %d . Вошел на склад: %d\n", buy_id, stor_n+1);
		// Покупаем на найденном складе.
		storage[stor_n] -= buy_count;
		printf("Покупатель: %d . Купил: %d\n", buy_id, buy_count);
		// Уменьшаем свою общую потребность на кол-во купленного.
		demand -= buy_count;
		// Освобождаем склад.
		storage_stat[stor_n] = STOR_FREE;
		printf("Покупатель: %d . Вышел со склада: %d\n", buy_id, stor_n+1);
		sleep(1);
		// printf("%d\n", pthread_self();
		// Проверяем удовлетворена-ли потребность, если да, то выходим.
		if (demand == 0) {
			printf("Покупатель: %d . Закончил закупку.\n\n", buy_id);
			// Говорим что мы тоже закупились.
			my_crutch++;
			return;
		}

	}

}

// Функция поиска следующего (случайного)
// свободного склада, с достаточным кол-вом товара.
inline static uint free_stor(uint* storage, _Bool* storage_stat, ushort count, uint buy_demand)
{
	// Переменная хранящая случайный номер склада.
	uint tmpr;

	while(TRUE) {
		tmpr = my_rand(0, count);

		if (storage_stat[tmpr] == STOR_BUSY) {
			// Чуть притормозим, пожалеем проц.
			sleep(1);
			continue;
		}

		sleep(1);

		if (storage[tmpr] >= buy_demand) {
			// Если нашли подходящий склад сразу его занимаем.
			storage_stat[tmpr] = STOR_BUSY;
			// Возвращаем номер занятого склада.
			return tmpr;
		}
	}
}


//struct buyer2_thr_params {
//	uint* storage;
//	_Bool* storage_stat;
//	ushort count;
//	ushort buy_id;
//};

void *buyer2_thr_wrapper(void *in_parms)
{
	struct buyer2_thr_params *parms = in_parms;
	buyer2(parms->storage, parms->storage_stat, parms->count, parms->buy_id);
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////