# Payment Application Simulation
This is a Payment Application Simulation project for the EgFWD Embedded Systems Professional NanoDegree Scholarship. This project was written in C. It includes a Luhn card PAN generation and validation.

## Flowchart
![payment-flowchart](https://user-images.githubusercontent.com/62207434/183305187-4d1241fb-fa97-4daf-8a6b-a1f41a540ac7.jpg)

## Functions
- `appStart()` : this would be called in `Main.c` to start the application
- `getTransactionDate()` : retrieve `System Date` automatically
- `getCardPAN()` : this functions asks to enter manually card PAN
- `saveTransaction()` : saves all types of transactions with all details into the transactions database
- - `getTransaction()` : check if the transactions is saved or not
