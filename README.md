# Payment Application Simulation
This is a simulation for sale transaction.

## Flowchart
![payment-flowchart](https://user-images.githubusercontent.com/62207434/183305187-4d1241fb-fa97-4daf-8a6b-a1f41a540ac7.jpg)

## Functions
- `appStart()` : this would be called in `Main.c` to start the application.
- `getTransactionDate()` : retrieve `System Date` automatically in the form `DD/MM/YYYY`.
- `getCardPAN()` : this functions asks to enter manually card PAN.
- `saveTransaction()` : saves all types of transactions with all details into the transactions database.
- `getTransaction()` : check if the transactions is saved or not.
- `isValidAccount()` : check if the account is found in databas or not.
- `isBlockedAccount` : check if the account is blocked or not.
- `isAmountAvailable` : check if the balance in the account is morethan or equal to the transaction amount or not.

