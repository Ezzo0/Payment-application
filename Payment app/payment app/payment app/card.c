#include "card.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	printf("Enter your name (Not less than 20 char and Not more than 24): ");
	gets(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) > 24 || strlen(cardData->cardHolderName) < 20)
		return WRONG_NAME;
	
	for (int i = 0; i < strlen(cardData->cardHolderName); ++i)
	{
		if (!isalpha(cardData->cardHolderName[i]) && cardData->cardHolderName[i] != ' ')
			return WRONG_NAME;
	}
	return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	printf("Enter your card expiry date (In the format MM / YY, e.g 05 / 25): ");
	gets(cardData->cardExpirationDate);
	if (strlen(cardData->cardExpirationDate) > 5 || strlen(cardData->cardExpirationDate) < 5)
		return WRONG_EXP_DATE;
	for (int i = 0; i < 5; ++i)
	{
		if (i == 2)
		{
			if (cardData->cardExpirationDate[i] != '/')
				return WRONG_EXP_DATE;
			continue;
		}
		if(!isdigit(cardData->cardExpirationDate[i]))
			return WRONG_EXP_DATE;
	}
	int month_check = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';
	if(month_check > 12)
		return WRONG_EXP_DATE;
	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	printf("Enter your card's Primary Account Number (19 character max and 16 character min): ");
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16)
		return WRONG_PAN;
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); ++i)
	{
		if (!isdigit(cardData->primaryAccountNumber[i]))
			return WRONG_PAN;
	}
	return CARD_OK;
}