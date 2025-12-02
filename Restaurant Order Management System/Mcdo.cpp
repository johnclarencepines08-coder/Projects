#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <iomanip>  
#include <chrono>
#include <thread>// For setw

using namespace std;

// Structure to represent an order
struct Order {
    vector<string> foodItems;  // List of food items ordered
    int type;                  // 1 = dine-in, 2 = takeout, 3 = delivery
    int preparationTime;       // in minutes
    string status;             // "active" or "cancelled"
    string customerName;       // Name of the customer
};

// Predefined food choices
vector<string> foodChoices = {
   "Yumburger", "Jolly Spaghetti", "Chicken Joy (2 pieces)", "Halo-Halo", "French Fries",
    "Jolly Crispy Fries", "Soft Drink (Regular)", "Iced Tea", "Jolly Chicken Sausage", "Palabok Fiesta",
	 "Peach Mango Pie", "Ube Pie", "Chocolate Sundae Twirl", "Pineapple Quencher", "Burger Steak", "Chicken Tenders",
};

void loading() {
    auto one_seconds = 1s;
    for (int i = 1; i <= 3; i++) {
        cout << " .";
        this_thread::sleep_for(one_seconds);
    }
}
// Display menu to the user
void displayMenu() {
    cout << "\n============================================\n";
    cout << "          === Jollibee Menu ===             \n";
    cout << "============================================\n";
    for (int i = 0; i < foodChoices.size(); i++) {
        cout << "   [" << i + 1 << "] | " << foodChoices[i] << endl;
    }
    cout << "   [17] | Done (Finish Adding Items)\n";
    cout << "============================================\n";
}

// Input validation function for positive integers
int getPositiveIntegerInput(const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input <= 0) {
            cin.clear(); // clear error flag
            cout << "   Invalid input. Please enter a positive integer.\n";
         
        } else {
            return input;
        }
    }
}

// Function to get non-empty customer name with error handling
string getCustomerName() {
    string name;
    while (true) {
        cout << "Enter the customer's name: ";
        getline(cin, name);  // Use getline to allow spaces in the name
        if (name.empty()) {
            cout << "   Name cannot be empty. Please enter a valid name.\n";
        } else {
            return name;
        }
    }
}

// Function to select items from the menu
vector<string> selectItems() {
    vector<string> items;
    bool addingItems = true;

    while (addingItems) {
        displayMenu();
        Ask:
        int choice = getPositiveIntegerInput("Enter your choice (1-17): ");
        
        switch (choice) {
            case 1: 
                items.push_back("Yumburger");
                cout << "Yumburger added to your order.\n";
                goto Ask;
                break;
            case 2: 
                items.push_back("Jolly Spaghetti");
                cout << "Jolly Spaghetti added to your order.\n";
                goto Ask;
                break;
            case 3: 
                items.push_back("Chicken Joy (2 pieces)");
                cout << "Chicken Joy (2 pieces) added to your order.\n";
                goto Ask;
                break;
            case 4: 
                items.push_back("Halo-Halo");
                cout << "Halo-Halo added to your order.\n";
                goto Ask;
                break;
            case 5: 
                items.push_back("French Fries");
                cout << "French Fries added to your order.\n";
                goto Ask;
                break;
            case 6: 
                items.push_back("Jolly Crispy Fries");
                cout << "Jolly Crispy Fries added to your order.\n";
                goto Ask;
                break;
            case 7: 
                items.push_back("Soft Drink (Regular)");
                cout << "Soft Drink (Regular) added to your order.\n";
                goto Ask;
                break;
            case 8: 
                items.push_back("Iced Tea");
                cout << "Iced Tea added to your order.\n";
                goto Ask;
                break;
            case 9: 
                items.push_back("Jolly Chicken Sausage");
                cout << "Jolly Chicken Sausage added to your order.\n";
                goto Ask;
                break;
            case 10: 
                items.push_back("Palabok Fiesta");
                cout << "Palabok Fiesta added to your order.\n";
                goto Ask;
                break;
            case 11: 
                items.push_back("Peach Mango Pie");
                cout << "Peach Mango Pie added to your order.\n";
                goto Ask;
                break;
            case 12: 
                items.push_back("Ube Pie");
                cout << "Ube Pie added to your order.\n";
                goto Ask;
                break;
            case 13: 
                items.push_back("Chocolate Sundae Twirl");
                cout << "Chocolate Sundae Twirl added to your order.\n";
                goto Ask;
                break;
            case 14: 
                items.push_back("Pineapple Quencher");
                cout << "Pineapple Quencher added to your order.\n";
                goto Ask;
                break;
            case 15: 
                items.push_back("Burger Steak");
                cout << "Burger Steak added to your order.\n";
                goto Ask;
                break;
            case 16: 
                items.push_back("Chicken Tenders");
                cout << "Chicken Tenders added to your order.\n";
                goto Ask;
                break;
            case 17: 
                addingItems = false; 
                cout << "Finished adding items.\n";
                break;
            default: 
                cout << "Invalid choice. Please select a valid item (1-17).\n";
                goto Ask;
                break;
        }
    }
    return items;
}

// Queue for order processing
class OrderQueue {
private:
    queue<Order> orders;
public:
    void addOrder(const Order& order) {
        orders.push(order);
    }

    Order removeOrder() {
        Order frontOrder = orders.front();
        orders.pop();
        return frontOrder;
    }

    bool isEmpty() {
        return orders.empty();
    }

    void displayOrders() {
        queue<Order> tempQueue = orders;
        int orderNumber = 1;  // To display the order number

        // Displaying the table header
        cout << "\n=============================================================================================================\n";
        cout << "   Order # | Customer Name           | Order Type  | Food Items                                      | Prep Time (mins)\n";
        cout << "=============================================================================================================\n";

        while (!tempQueue.empty()) {
            Order order = tempQueue.front();
            tempQueue.pop();

            // Display the basic order details in a row
            cout << "   " << setw(6) << orderNumber++ << " | ";

            // Truncate customer name if too long
            string customerName = order.customerName;
            if (customerName.length() > 20) {
                customerName = customerName.substr(0, 17) + "..."; // Truncate to 20 characters, including "..."
            }
            cout << setw(25) << left << customerName << " | ";

            // Display order type
            switch (order.type) {
                case 1: cout << setw(11) << "Dine-in"; break;
                case 2: cout << setw(11) << "Takeout"; break;
                case 3: cout << setw(11) << "Delivery"; break;
                default: cout << setw(11) << "Unknown"; break;
            }

            // Display food items on new lines under the "Food Items" column
            cout << " | \n";
            if (!order.foodItems.empty()) {
                for (size_t i = 0; i < order.foodItems.size(); i++) {
                    // Output food items directly using the indices
                    cout << "               |                          |             | " << order.foodItems[i] << "\n";
                }
            } else {
                cout << "               |                          |             | None\n"; // No food items
            }

            // Display preparation time
            cout << "               |                          |             | " << setw(4) << order.preparationTime << " mins\n";
        }

        cout << "=============================================================================================================\n";
    }
};
class UndoCancelStack {
private:
    stack<Order> undoCancelStack;
public:
    void addToUndoStack(const Order& order) {
        undoCancelStack.push(order);
    }

    void undoRecentCancellation(OrderQueue& orderQueue) {
        if (!undoCancelStack.empty()) {
            Order lastCancelledOrder = undoCancelStack.top();
            undoCancelStack.pop();

            // Update the status of the undone cancellation to 'active'
            lastCancelledOrder.status = "active";
            orderQueue.addOrder(lastCancelledOrder);

            cout << "   Undo Successful: Order for " << lastCancelledOrder.customerName 
                 << " has been reinstated.\n";
        } else {
            cout << "   No cancellations to undo.\n";
        }
    }

    bool isEmpty() {
        return undoCancelStack.empty();
    }
};
// Stack for managing order cancellations
class OrderStack {
public:
    stack<Order> cancelStack;
public:
    void addToCancelStack(const Order& order) {
        cancelStack.push(order);
    }

    Order cancelMostRecentOrder(OrderQueue& orderQueue) {
    if (!cancelStack.empty()) {
        Order cancelledOrder = cancelStack.top();
        cancelStack.pop();

        // Update the status of the cancelled order to 'cancelled'
        cancelledOrder.status = "cancelled";

        // Output the cancelled order details
        	cout<<"Canceling Order ";
        	loading();
        cout << "   Cancelled Most Recent Order: " << cancelledOrder.customerName << " (" << cancelledOrder.foodItems.size() << " items)\n";

        // Update the queue by removing the cancelled order
        queue<Order> tempQueue;
        while (!orderQueue.isEmpty()) {
            Order order = orderQueue.removeOrder();
            if (order.customerName != cancelledOrder.customerName || order.status == "cancelled") {
                tempQueue.push(order);
            }
        }
        // Transfer remaining orders back to the queue
        while (!tempQueue.empty()) {
            orderQueue.addOrder(tempQueue.front());
            tempQueue.pop();
        }

        return cancelledOrder; // Return the cancelled order
    } else {
        cout << "   No orders to cancel.\n";
        return Order{}; // Return an empty Order if no order was canceled
    }
}


    bool isEmpty() {
        return cancelStack.empty();
    }
};

// Bubble sort for orders based on preparation time
void bubbleSort(vector<Order>& orders) {
    int n = orders.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (orders[j].preparationTime > orders[j + 1].preparationTime) {
                swap(orders[j], orders[j + 1]);
            }
        }
    }
}

// Main menu and logic
int main() {
    OrderQueue orderQueue;
    OrderStack cancelStack;
    UndoCancelStack undoCancelStack; // New stack for undo cancellations
    vector<Order> allOrders;

    while (true) {
        cout << "\n==============================================\n";
        cout << "    Restaurant Order Management System        \n";
        cout << "==============================================\n";
        cout << "   [1] | Add Order\n";
        cout << "   [2] | Cancel Most Recent Order\n";
        cout << "   [3] | Undo Recent Cancellation\n"; // New menu option
        cout << "   [4] | Sort Orders by Preparation Time\n";
        cout << "   [5] | Display Orders\n";
        cout << "   [6] | Process Next Order\n";
        cout << "   [7] | Exit\n";
        cout << "----------------------------------------------\n";
        Ask:
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
           loading();
        	system("cls");
            vector<string> selectedItems = selectItems();
            Order newOrder;

           cout << "\n============================================\n";
            cin.ignore(); // Clear the buffer
            newOrder.customerName = getCustomerName();

            // Get selected food items
            newOrder.foodItems = selectedItems;

            // Get preparation time (ensure it's a positive integer)
            newOrder.preparationTime = getPositiveIntegerInput("Enter preparation time (in minutes): ");

            // Get order type (ensure it's valid: 1, 2, or 3)
            while (true) {
                newOrder.type = getPositiveIntegerInput("Enter order type (1 = Dine-in, 2 = Takeout, 3 = Delivery): ");
                if (newOrder.type >= 1 && newOrder.type <= 3) break;
                cout << "Invalid input. Please enter 1, 2, or 3.\n";
            }

            // Set the status to active
            newOrder.status = "active";

            // Add order to the queue
            orderQueue.addOrder(newOrder);

            // Add to vector for sorting later
            allOrders.push_back(newOrder);
            cancelStack.addToCancelStack(newOrder); 

            cout << "Order added successfully!\n";
			cout << "\n============================================\n";
			  cout << "\nPress Enter to return to the main menu:\n";
    cin.ignore();

    cin.get();	loading();
    system("cls");
        } else if (choice == 2) {
    // Cancel most recent order
    if (!orderQueue.isEmpty()) {
    	system("cls");
        Order canceledOrder = cancelStack.cancelMostRecentOrder(orderQueue);
        if (!canceledOrder.customerName.empty()) { // Ensure a valid order was canceled
        
            undoCancelStack.addToUndoStack(canceledOrder);
            			  cout << "\nPress Enter to return to the main menu:\n";
    cin.ignore();

    cin.get();	loading();
    system("cls");
        }
    } else {
    	system("cls");
        cout << "   No orders to cancel.\n";
        			  cout << "\nPress Enter to return to the main menu:\n";
    cin.ignore();

    cin.get();	loading();
    system("cls");
    }
} else if (choice == 3) {
    system("cls");
    if (!undoCancelStack.isEmpty()) {
    	cout<<"Undoing";
    	loading();
        undoCancelStack.undoRecentCancellation(orderQueue);
        system("cls");
    } else {
        cout << "   No recent cancellations to undo.\n";
    }
}

 else if (choice == 4) {
        	loading();
    system("cls");  // Clear the screen (for Windows)
    
    if (orderQueue.isEmpty()) {
        cout << "No orders to sort.\n";
    } else {
        vector<Order> orders;
        while (!orderQueue.isEmpty()) {
            orders.push_back(orderQueue.removeOrder());
        }
        bubbleSort(orders);

        // Displaying sorted orders like the displayOrders function
        	system("cls");
        cout << "\n					==============================================\n";
        cout << "					|                JOLLIBEE  ORDERS            |  \n";
        cout << "					==============================================\n\n";
        cout << "\n=============================================================================================================\n";
        cout << "   Order # | Customer Name           | Order Type  | Food Items                                      | Prep Time (mins)\n";
        cout << "=============================================================================================================\n";

        int orderNumber = 1;  // To display the order number
        for (const Order& order : orders) {
            // Display the basic order details in a row
            cout << "   " << setw(6) << orderNumber++ << " | ";

            // Truncate customer name if too long
            string customerName = order.customerName;
            if (customerName.length() > 20) {
                customerName = customerName.substr(0, 17) + "..."; // Truncate to 20 characters, including "..."
            }
            cout << setw(25) << left << customerName << " | ";

            // Display order type
            switch (order.type) {
                case 1: cout << setw(11) << "Dine-in"; break;
                case 2: cout << setw(11) << "Takeout"; break;
                case 3: cout << setw(11) << "Delivery"; break;
                default: cout << setw(11) << "Unknown"; break;
            }

            // Display food items under the "Food Items" column
            cout << " | \n";
            if (!order.foodItems.empty()) {
                for (size_t i = 0; i < order.foodItems.size(); i++) {
                    cout << "               |                          |             | " << order.foodItems[i] << "\n";
                }
            } else {
                cout << "               |                          |             | None\n"; // No food items
            }

            // Display preparation time
            cout << "               |                          |             | " << setw(4) << order.preparationTime << " mins\n";
        }

        cout << "=============================================================================================================\n";

        // Refill the queue with sorted orders
        for (const Order& order : orders) {
            orderQueue.addOrder(order);
        }
    }

    // Prompt the user to press Enter to return to the main menu
    cout << "\nPress Enter to return to the main menu:\n";
    cin.ignore();  // Ignore any leftover newline character from previous input
    cin.get();  // Wait for the user to press Enter
    loading();   // Call loading function if defined, if not remove this line
    system("cls");  // Clear the screen after returning to the main menu
}
else if (choice == 5) {
	loading();
	system("cls");
        cout << "\n					==============================================\n";
        cout << "					|                JOLLIBEE  ORDERS            |  \n";
        cout << "					==============================================\n\n";
    if (orderQueue.isEmpty()) {
        cout << "No orders to display.\n";
        
    } else {
        orderQueue.displayOrders();
    }
     cout << "\nPress Enter to return to the main menu:\n";
    cin.ignore();

    cin.get();	
	loading();
	system("cls");
}


 else if (choice == 6) {
            if (!orderQueue.isEmpty()) {
            	loading();
                // Remove the order from the queue and process it
                Order orderToProcess = orderQueue.removeOrder();
                cout << "\nProcessing Order for " << orderToProcess.customerName; 
                loading();

                // After processing, add it to the cancel stack for possible cancellation
                cancelStack.addToCancelStack(orderToProcess);
                cout << "\nOrder processed.\n";
                cout << "\nPress Enter to return to the main menu:\n";
    cin.ignore();

    cin.get();	
	loading();
	system("cls");
            } else {
                cout << "No orders to process.\n";
                goto Ask;
            }

        } else if (choice == 7) {
        	
            cout << "Exiting system";
            loading();
            system("cls");
               // Decorative border
    string border = "****************************************************";
    string spaces = "               ";
    
    // Print the top border
    cout << endl << border << endl;

    // Aesthetic thank you message
    cout << "*                                                  *" << endl;
    cout << "*                THANK YOU FOR VISITING!           *" << endl;
    cout << "*                                                  *" << endl;
    cout << "*   We hope to see you again soon. Stay safe!      *" << endl;
    cout << "*                                                  *" << endl;

    // Print the bottom border
    cout << border << endl;

    // Add a decorative newline for spacing
    cout << endl;
            break;

        } else {
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
