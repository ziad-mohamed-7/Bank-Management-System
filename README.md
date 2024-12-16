# Bank Management System

A comprehensive **Bank Management System** developed in C language to manage customer accounts, transactions, and provide essential banking functionalities efficiently.

## Features

### Account Management
- **Add Accounts:** Create a new account with details like name, email, phone number, balance, and date of account opening.
- **Delete Accounts:** Remove an account using its account number.
- **Modify Accounts:** Update account details based on the account number.

### Transactions
- **Deposit:** Add money to a specific account.
- **Withdraw:** Deduct money from an account, ensuring sufficient balance.
- **Transfer:** Transfer funds between two accounts securely.
- **Transaction Reports:** View the last 5 transactions for any account.

### Sorting and Searching
- **Sort Accounts:**
  - By Name (Alphabetical Order)
  - By Date of Account Opening
  - By Balance
- **Search Accounts:**
  - Query Search: Locate an account by account number.
  - Advanced Search: Perform custom searches.

### Validation
- **Phone Number Validation:** Ensure valid phone numbers (11 digits, starting with '01').
- **Email Validation:** Check the format of email addresses.
- **Name Validation:** Verify proper formatting of names (First Last, each capitalized).

### File Operations
- Load accounts data from a file upon login.
- Save account details and transactions to a file for persistence.

### User Authentication
- Login system to ensure authorized access to banking features.

## File Structure

- **accounts.txt**: Stores account details.
- **transactions.txt**: Records all transactions.
- **users.txt**: Stores login credentials.

## Dependencies

- **C Standard Library**: Used for file handling, string manipulation, and memory management.
- **POSIX Regex Library**: Validates email and name formats.
