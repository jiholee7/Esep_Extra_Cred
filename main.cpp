#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>

class InMemoryDB {
private:
    std::unordered_map<std::string, int> data;
    std::unordered_map<std::string, int> uncommittedData;
    bool inTransaction;

public:
    InMemoryDB() : inTransaction(false) {}

    void begin_transaction() {
        if (inTransaction) {
            std::cout << "Error: Transaction already in progress" << std::endl;
            return;
        }
        inTransaction = true;
        std::cout << "Transaction in progress" << std::endl;
        uncommittedData.clear();
    }

    void put(const std::string& key, int value) {
        if (!inTransaction) {
            std::cout << "Error: No transaction in progress" << std::endl;
            return;
        }
        uncommittedData[key] = value;
    }

    int get(const std::string& key) {
        if (data.find(key) != data.end()) {
            return data[key];
        } else {
            return NULL; //if key not found
        }
    }

    void commit() {
        if (!inTransaction) {
            std::cout << "Error: No transaction in progress" << std::endl;
            return;
        }
        data.insert(uncommittedData.begin(), uncommittedData.end());
        uncommittedData.clear();
        std::cout << "Transaction Committed" << std::endl;
        inTransaction = false;
    }

    void rollback() {
        if (!inTransaction) {
            std::cout << "Error: No transaction in progress" << std::endl;
            return;
        }
        uncommittedData.clear();
        std::cout << "Transaction Rolled Back" << std::endl;
        inTransaction = false;
    }
};

int main() {
    //The following are tests for the In Memory DB as displayed in the instruction document with additional tests
    //created by myself to ensure comprehensive testing of all features and potential error conditions.

    //For the get method, in the case that NULL is returned because the key doesn't exist
    //in the DB, it will show as 0 being returned, due to C++ limitations. In the actual code for get(),
    //NULL is returned, but when it is outputted to the console, C++ writes it as 0.

    //As the instructions didn't mention requiring user input or menu system, the tests have
    //been hard coded.

    //The following should be the output in the console if the tests are working correctly:
    //Test 1: 0
    //Test 2: Error: No transaction in progress
    //Transaction in progress
    //Test 3: 0
    //Transaction Committed
    //Test 4: 6
    //Test 5: Error: No transaction in progress
    //Test 6: Error: No transaction in progress
    //Test 7: 0
    //Transaction in progress
    //Transaction Rolled Back
    //Test 8: 0
    //Transaction in progress
    //Test 9: Error: Transaction already in progress

    //initialize the in memory DB
    InMemoryDB inmemoryDB;

    // should return null, because A doesn’t exist in the DB yet
    std::cout << "Test 1: ";
    std::cout << inmemoryDB.get("A") << std::endl;

    // should throw an error because a transaction is not in progress
    std::cout << "Test 2: ";
    inmemoryDB.put("A", 5);

    // starts a new transaction
    inmemoryDB.begin_transaction();

    // set’s value of A to 5, but its not committed yet
    inmemoryDB.put("A", 5);

    // should return null, because updates to A are not committed yet
    std::cout << "Test 3: ";
    std::cout << inmemoryDB.get("A") << std::endl;

    // update A’s value to 6 within the transaction
    inmemoryDB.put("A", 6);

    // commits the open transaction
    inmemoryDB.commit();

    // should return 6, that was the last value of A to be committed
    std::cout << "Test 4: ";
    std::cout << inmemoryDB.get("A") << std::endl;

    // throws an error, because there is no open transaction
    std::cout << "Test 5: ";
    inmemoryDB.commit();

    // throws an error because there is no ongoing transaction
    std::cout << "Test 6: ";
    inmemoryDB.rollback();

    // should return null because B does not exist in the database
    std::cout << "Test 7: ";
    std::cout << inmemoryDB.get("B") << std::endl;

    // starts a new transaction
    inmemoryDB.begin_transaction();

    // Set key B’s value to 10 within the transaction
    inmemoryDB.put("B", 10);

    // Rollback the transaction - revert any changes made to B
    inmemoryDB.rollback();

    // Should return null because changes to B were rolled back
    std::cout << "Test 8: ";
    std::cout << inmemoryDB.get("B") << std::endl;

    // starts a new transaction
    inmemoryDB.begin_transaction();

    // Should throw error since transaction already in progress
    std::cout << "Test 9: ";
    inmemoryDB.begin_transaction();

    return 0;
}
