#pragma once
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/////////////////////////////////////////
#define ushort unsigned short
#define uint unsigned int
#define TRUE 1
#define FALSE 0
 
#define STOR_BUSY 1
#define STOR_FREE 0

#define ITEM_COUNT 5
#define BUYERS_COUNT 3
///////////////////////////////////////
extern _Bool exit_status;
extern ushort my_crutch;
/////////////////////////////////////////
///////////_FUNCS_PROTOTYPE_/////////////

//START_ Погрузчик.
void loader(uint* storage, _Bool* storage_stat, ushort count);

// Структура-обертка для параметров функции loader.
struct loader_thr_params {
	uint* storage;
	_Bool* storage_stat;
	ushort count;
};

// Функция-обертка для функции loader.
void *loader_thr_wrapper(void *in_parms);

//END_ Погрузчик.

//START_ Покупатель.
// Функция покупателя. v02
void buyer2(uint* storage, _Bool* storage_stat, ushort count, ushort buy_id);

// Структура-обертка для параметров функции buyer2.
struct buyer2_thr_params {
	uint* storage;
	_Bool* storage_stat;
	ushort count;
	ushort buy_id;
};

// Функция-обертка для функции buyer2.
void *buyer2_thr_wrapper(void *in_parms);
//END_ Покупатель.

// Выдает число в диапазоне от start до end.
ushort my_rand(ushort start, ushort end);

/////////////////////////////////////////
/////////////////////////////////////////
