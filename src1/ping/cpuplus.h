/*
 *  Библиотека функций для процессорной платы
 *  Copyrigth (c) 2002 Fomin D.A. V1.00
 */
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <i86.h>

/*
 * com_bios_data - функция определяет номер COM-порта по результатам POST
 */
int com_bios_data(unsigned int base) {
 	unsigned char __far *cp;
	unsigned int  number;

	/* Быстрое завершение */
	if(base == 0)
		return(0);
	/* Получение указателя на область данных BIOS */
	cp = (unsigned char __far *) MK_FP(0x40, 0);
	/* Поиск COM-порта */
	number = 0;
	if (base == *(unsigned short __far *) (cp + 0))
		number = 1;
	if (base == *(unsigned short __far *) (cp + 2))
		number = 2;
	if (base == *(unsigned short __far *) (cp + 4))
		number = 3;
	if (base == *(unsigned short __far *) (cp + 6))
		number = 4;
	/* Завершение с найденным номером COM-порта */
	return(number);
} /* com_bios_data() */

/*
 * lpt_bios_data - функция определяет номер LPT-порта по результатам POST
 */
int lpt_bios_data(unsigned int base) {
 	unsigned char __far *cp;
	unsigned int  number;

	/* Быстрое завершение */
	if(base == 0)
		return(0);
	/* Получение указателя на область данных BIOS */
	cp = (unsigned char __far *) MK_FP(0x40, 8);
	/* Поиск LPT-порта */
	number = 0;
	if (base == *(unsigned short __far *) (cp + 0))
		number = 1;
	if (base == *(unsigned short __far *) (cp + 2))
		number = 2;
	if (base == *(unsigned short __far *) (cp + 4))
		number = 3;
	/* Завершение с найденным номером LPT-порта */
	return(number);
} /* lpt_bios_data() */

/*
 * rtc_cmos - функция проверяет работу RTC-часов
 */
int rtc_cmos(unsigned int time) {
	unsigned int time_start;
	unsigned int time_end;

	/* Быстрое завершение */
	if (time == 0)
		return(0);
	/* Определение текущего значения секунд показаний RTC-часов */
	do {
		delay(0);
		outp(0x70, 0xA);
	} while (inp(0x71) & 0x80);
	delay(0);
	outp(0x70, 0x0);
	time_start = inp(0x71);
	/* Пауза */
	sleep(time);
	/* Определение нового текущего значения секунд показаний RTC-часов */
	do {
		delay(0);
		outp(0x70, 0xA);
	} while (inp(0x71) & 0x80);
	delay(0);
	outp(0x70, 0x0);
	time_end = inp(0x71);
	/* Завершение с разностью в показаниях RTC-часов */
	return(time_end - time_start);
} /* rtc_cmos() */

/*
 * batt_cmos - функция читает информацию о заряде батареи
 */
int batt_cmos(void) {
	unsigned int batt;

	/* Чтение регистра D CMOS */
	delay(0);
	outp(0x70, 0xD);
	batt = inp(0x71);
	/* Выделение информации о батарее */
	batt &= 0x80;
	/* Завершение с информацией о батарее */
	return(batt);
} /* batt_cmos() */

/*
 * chip_cmos - функция читает результаты POST чипсета
 */
int chip_cmos(void) {
	unsigned int status;

	/* Чтение значения диагностического байта */
	delay(0);
	outp(0x70, 0xE);
	status = inp(0x71);
	/* Выделение полезной информации */
	status &= 0xFC;
	/* Завершение со зачением диагностического байта */
	return(status);
} /* chip_cmos() */

/*
 * basemem_cmos - функция определяет размер базового ОЗУ
 */
int basemem_cmos(void) {
	int unsigned memory;

	/* Чтение размера обнаруженного базового ОЗУ */
	delay(0);
	outp(0x70, 0x15);
	memory = inp(0x71);
	delay(0);
	outp(0x70, 0x16);
	memory += inp(0x71) * 256;
	/* Завершение с размером базового ОЗУ */
	return(memory);
} /* basemem_cmos() */

/*
 * extmem_cmos - функция определяет размер расширенного ОЗУ
 */
int extmem_cmos(void) {
	int unsigned memory;

	/* Чтение размера обнаруженного расширенного ОЗУ */
	delay(0);
	outp(0x70, 0x17);
	memory = inp(0x71);
	delay(0);
	outp(0x70, 0x18);
	memory += inp(0x71) * 256;
	/* Завершение с размером расширенного ОЗУ */
	return(memory);
} /* extmem_cmos() */
