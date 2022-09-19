#include "application.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void appStart(void)
{
	//mostafa ahmed mousa ezz
	// first test name 
	// second test wrong exp format
	// third test wrong pan format 
	// fourth test ==> be expired card
	// test the amount
	// account not found  ==> 8989374615436852
	// low balance 
	// blocked account

	printf("-------------------------------------------- WELCOME TO PAYMENT APPLICATION --------------------------------------------\n\n");

	ST_cardData_t cardData;
	ST_terminalData_t terminaData;
	ST_transaction_t transactionData;
	EN_cardError_t ce;
	EN_terminalError_t te;
	EN_serverError_t se;

	// getting Card Data
	do
	{
		ce = getCardHolderName(&cardData);
		if (ce == WRONG_NAME)
			printf("WRONG NAME FORMAT\n");
	} while (ce == WRONG_NAME);
	do
	{
		ce = getCardExpiryDate(&cardData);
		if (ce == WRONG_EXP_DATE)
			printf("WRONG EXP DATE FORMAT\n");
	} while (ce == WRONG_EXP_DATE);
	do
	{
		ce = getCardPAN(&cardData);
		if (ce == WRONG_PAN)
			printf("WRONG PAN FORMAT\n");
	} while (ce == WRONG_PAN);

	printf("Getting Transaction Date....\n");
	getTransactionDate(&terminaData);

	if (isCardExpired(&cardData, &terminaData) == EXPIRED_CARD)
	{
		printf("Expired Card");
		return;
	}


	// Getting Transaction Data
	do
	{
		te = setMaxAmount(&terminaData);
		if (te == INVALID_AMOUNT)
			printf("INVALID AMOUNT\n");
	} while (te == INVALID_AMOUNT);

	do
	{
		te = getTransactionAmount(&terminaData);
		if (te == INVALID_AMOUNT)
			printf("INVALID AMOUNT\n");
	} while (te == INVALID_AMOUNT);

	if (isBelowMaxAmount(&terminaData) == EXCEED_MAX_AMOUNT)
	{
		printf("Amount Limit Exceed\n");
		return;
	}

	transactionData.cardHolderData = cardData;
	transactionData.terminalData = terminaData;

	// Checking input data with server 
	se = recieveTransactionData(&transactionData);

	if(se == FRAUD_CARD)
		printf("Account Not Found\n");
	
	else if (se == DECLINED_INSUFFECIENT_FUND)
		printf("Low Balance\n");

	else if (se == DECLINED_STOLEN_CARD)
		printf("Blocked Account\n");

	else if (se == INTERNAL_SERVER_ERROR)
		printf("Saving Error\n");

	else 
		printf("Transaction completed\n");

	return;
}