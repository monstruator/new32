/*
 *  ������⥪� �㭪権 ��� �����୮� �����
 *  Copyrigth (c) 2002 Fomin D.A. V1.00
 */
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <i86.h>

/*
 * com_bios_data - �㭪�� ��।���� ����� COM-���� �� १���⠬ POST
 */
int com_bios_data(unsigned int base) {
 	unsigned char __far *cp;
	unsigned int  number;

	/* ����஥ �����襭�� */
	if(base == 0)
		return(0);
	/* ����祭�� 㪠��⥫� �� ������� ������ BIOS */
	cp = (unsigned char __far *) MK_FP(0x40, 0);
	/* ���� COM-���� */
	number = 0;
	if (base == *(unsigned short __far *) (cp + 0))
		number = 1;
	if (base == *(unsigned short __far *) (cp + 2))
		number = 2;
	if (base == *(unsigned short __far *) (cp + 4))
		number = 3;
	if (base == *(unsigned short __far *) (cp + 6))
		number = 4;
	/* �����襭�� � �������� ����஬ COM-���� */
	return(number);
} /* com_bios_data() */

/*
 * lpt_bios_data - �㭪�� ��।���� ����� LPT-���� �� १���⠬ POST
 */
int lpt_bios_data(unsigned int base) {
 	unsigned char __far *cp;
	unsigned int  number;

	/* ����஥ �����襭�� */
	if(base == 0)
		return(0);
	/* ����祭�� 㪠��⥫� �� ������� ������ BIOS */
	cp = (unsigned char __far *) MK_FP(0x40, 8);
	/* ���� LPT-���� */
	number = 0;
	if (base == *(unsigned short __far *) (cp + 0))
		number = 1;
	if (base == *(unsigned short __far *) (cp + 2))
		number = 2;
	if (base == *(unsigned short __far *) (cp + 4))
		number = 3;
	/* �����襭�� � �������� ����஬ LPT-���� */
	return(number);
} /* lpt_bios_data() */

/*
 * rtc_cmos - �㭪�� �஢���� ࠡ��� RTC-�ᮢ
 */
int rtc_cmos(unsigned int time) {
	unsigned int time_start;
	unsigned int time_end;

	/* ����஥ �����襭�� */
	if (time == 0)
		return(0);
	/* ��।������ ⥪�饣� ���祭�� ᥪ㭤 ��������� RTC-�ᮢ */
	do {
		delay(0);
		outp(0x70, 0xA);
	} while (inp(0x71) & 0x80);
	delay(0);
	outp(0x70, 0x0);
	time_start = inp(0x71);
	/* ��㧠 */
	sleep(time);
	/* ��।������ ������ ⥪�饣� ���祭�� ᥪ㭤 ��������� RTC-�ᮢ */
	do {
		delay(0);
		outp(0x70, 0xA);
	} while (inp(0x71) & 0x80);
	delay(0);
	outp(0x70, 0x0);
	time_end = inp(0x71);
	/* �����襭�� � ࠧ������ � ���������� RTC-�ᮢ */
	return(time_end - time_start);
} /* rtc_cmos() */

/*
 * batt_cmos - �㭪�� �⠥� ���ଠ�� � ���拉 ���२
 */
int batt_cmos(void) {
	unsigned int batt;

	/* �⥭�� ॣ���� D CMOS */
	delay(0);
	outp(0x70, 0xD);
	batt = inp(0x71);
	/* �뤥����� ���ଠ樨 � ���॥ */
	batt &= 0x80;
	/* �����襭�� � ���ଠ樥� � ���॥ */
	return(batt);
} /* batt_cmos() */

/*
 * chip_cmos - �㭪�� �⠥� १����� POST 稯��
 */
int chip_cmos(void) {
	unsigned int status;

	/* �⥭�� ���祭�� ���������᪮�� ���� */
	delay(0);
	outp(0x70, 0xE);
	status = inp(0x71);
	/* �뤥����� �������� ���ଠ樨 */
	status &= 0xFC;
	/* �����襭�� � ��祭��� ���������᪮�� ���� */
	return(status);
} /* chip_cmos() */

/*
 * basemem_cmos - �㭪�� ��।���� ࠧ��� �������� ���
 */
int basemem_cmos(void) {
	int unsigned memory;

	/* �⥭�� ࠧ��� �����㦥����� �������� ��� */
	delay(0);
	outp(0x70, 0x15);
	memory = inp(0x71);
	delay(0);
	outp(0x70, 0x16);
	memory += inp(0x71) * 256;
	/* �����襭�� � ࠧ��஬ �������� ��� */
	return(memory);
} /* basemem_cmos() */

/*
 * extmem_cmos - �㭪�� ��।���� ࠧ��� ���७���� ���
 */
int extmem_cmos(void) {
	int unsigned memory;

	/* �⥭�� ࠧ��� �����㦥����� ���७���� ��� */
	delay(0);
	outp(0x70, 0x17);
	memory = inp(0x71);
	delay(0);
	outp(0x70, 0x18);
	memory += inp(0x71) * 256;
	/* �����襭�� � ࠧ��஬ ���७���� ��� */
	return(memory);
} /* extmem_cmos() */
