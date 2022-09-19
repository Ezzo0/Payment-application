#pragma warning(disable : 4996)
#include "terminal.h" 
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void set_date(int day, int mon, int year , ST_terminalData_t *termData)
{
	// transectiondate array indcies : 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10

	int i = 1;
	if (day < 10) termData->transactionDate[0] = 0 + '0';
	while (day)
	{
		//eg : 12
		termData->transactionDate[i] = day % 10 + '0';
		day /= 10;
		i--;
	}
	termData->transactionDate[2] = '/';
	i = 4;
	if (mon < 10) termData->transactionDate[3] = 0 + '0';
	while (mon)
	{
		//eg : 12
		termData->transactionDate[i] = mon % 10 + '0';
		mon /= 10;
		i--;
	}
	termData->transactionDate[5] = '/';
	i = 9;
	while (year)
	{
		//eg : 2001
		termData->transactionDate[i] = year % 10 + '0';
		year /= 10;
		i--;
	}
}
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	time_t ti = time(0); // integer type which stores the seconds passed since 12 a.m at 1 jan 1970
	struct tm *today_date = localtime(&ti); // structure to hold day, month, and year using localtime function
	
	//date format should be like this 05 / 08 / 2002

	int day = today_date->tm_mday;
	int mon = today_date->tm_mon + 1;
	int year = today_date->tm_year + 1900;

	set_date(day, mon, year, termData);

	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	int cardMonth, cardYear, terminalMonth, terminalYear;

	// transectiondate array indcies : 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10
	// cardexpirationdate array indcies : 0 | 1 | 2 | 3 | 4 | 5
	cardMonth = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	cardYear = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');

	terminalMonth = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
	terminalYear = (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');

	if (cardYear < terminalYear)
		return EXPIRED_CARD;

	else if (cardYear == terminalYear)
	{
		if (cardMonth >= terminalMonth)
			return TERMINAL_OK;
		else
			return EXPIRED_CARD;
	}

	return TERMINAL_OK;
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	printf("Enter the transaction amount: ");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;

	return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;

	return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	printf("Enter the maximum allowed transaction amount: ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
		return INVALID_AMOUNT;
	//termData->maxTransAmount = 8000.0;	// If you want to set it manually (not from user)

	return TERMINAL_OK;
}