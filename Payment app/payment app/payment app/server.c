#include "server.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


// Global array that represent the server-side accounts' database
ST_accountsDB_t accounts[255] = { 
								  {1000.0, RUNNING, "8989374615436851"} , 
								  {2000.0, BLOCKED, "5807007076043875"} ,
								  {3000.5, RUNNING, "1989674625446851"} , 
								  {4000.0, RUNNING, "3007027083043845"} ,
								  {5000.0, RUNNING, "3260927085443645"}
								};

// Global array that represent the server-side transactions' database
ST_transaction_t transactions[255] = { 0 };

ST_accountsDB_t *idx = NULL;	// For pointing to the account in the data base
int transactionNumber = -1;	// Counter for the transaction number

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{

	if (isValidAccount(&transData->cardHolderData, &idx) == ACCOUNT_NOT_FOUND)
	{
		transData->transState = FRAUD_CARD;
		if (saveTransaction(transData) == SAVING_FAILED)
			return INTERNAL_SERVER_ERROR;
		saveTransaction(transData);

		if (getTransaction(transactionNumber, transData) == SERVER_OK)
			return FRAUD_CARD;
		else
			return INTERNAL_SERVER_ERROR;
	}

	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		if (saveTransaction(transData) == SAVING_FAILED)
			return INTERNAL_SERVER_ERROR;
		saveTransaction(transData);

		if (getTransaction(transactionNumber, transData) == SERVER_OK)
			return DECLINED_INSUFFECIENT_FUND;		
		else
			return INTERNAL_SERVER_ERROR;
	}

	if (isBlockedAccount(idx) == BLOCKED_ACCOUNT)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		if (saveTransaction(transData) == SAVING_FAILED)
			return INTERNAL_SERVER_ERROR;
		saveTransaction(transData);

		if (getTransaction(transactionNumber, transData) == SERVER_OK)
			return DECLINED_STOLEN_CARD;
		else
			return INTERNAL_SERVER_ERROR;
	}

	if (saveTransaction(transData) == SAVING_FAILED)
		return INTERNAL_SERVER_ERROR;
	
	transData->transState = APPROVED;
	idx->balance -= transData->terminalData.transAmount;
	saveTransaction(transData);

	if(getTransaction(transactionNumber, transData) == SERVER_OK)
		return APPROVED;
	else
		return INTERNAL_SERVER_ERROR;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountRefrence)
{
	uint8_t *PAN = cardData->primaryAccountNumber;
	bool found = false;	// To indicate that PAN was found
	bool different;		// To indicate if the charcter in PAN variable is different from the charcter in PAN of the account in the data base
	for (int i = 0; i < 255; ++i)
	{
		different = false;		
		if (accounts[i].primaryAccountNumber != '\0')
		{
			if (strlen(PAN) != strlen(accounts[i].primaryAccountNumber))
				continue;
			for (int j = 0; j < strlen(PAN); ++j)
			{
				if (accounts[i].primaryAccountNumber[j] != PAN[j])
				{
					different = true;
					break;
				}
			}
			if (!different)
			{
				*accountRefrence = &accounts[i];
				found = true;
				break;
			}
		}
		else
			break;
	}
	if (found)
		return SERVER_OK;
	else
		return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	if (accountRefrence->state == BLOCKED)
		return BLOCKED_ACCOUNT;
	else
		return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
	//printf("%f , %f\n", idx->balance, termData->transAmount);
	if (idx->balance >= termData->transAmount)
		return SERVER_OK;
	else
		return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	if (transactionNumber < 254)
	{
		transactionNumber++;
		transactions[transactionNumber].cardHolderData = transData->cardHolderData;
		transactions[transactionNumber].terminalData = transData->terminalData;
		transactions[transactionNumber].transactionSequenceNumber = transactionNumber;
		return SERVER_OK;
	}
	return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
	bool found = false;
	for (int i = 0; i < 255; ++i)
	{
		if (transactions[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			found = true;
			break;
		}
	}
	if (found)
		return SERVER_OK;
	return TRANSACTION_NOT_FOUND;
}