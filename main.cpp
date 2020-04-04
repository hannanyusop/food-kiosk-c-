// Music Store Manangement System in C++ Design and Developed by CodeWithC.com

#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
#include "TextTable.h"

using namespace std;


int qstate, user_id;
bool is_manager = false;
string auth_name;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            //getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "", "kiosk", 3306, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            //getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};

void newOrder();
void headerLogo();
void printReceipt(string);
void viewOrder();
void printReceipt(string);
void insertItem();
void updateItem();
void endMenu();
void newOrderList();
void viewMonthlySale();
void menuCustomer();
void menuStaff();
void endMenuStaff();
void addStaff();
void viewStaff();
void setting();
void checkManager();
void logout();

int main()
{
    system("cls");
    system("SELF ORDERING SYSTEM");
    system("color 0f");
    int role;

    db_response::ConnectionFunction();

    

    headerLogo();

    cout << "Please choose:" << endl;
    cout << "1.Guest (For Customer)" << endl;
    cout << "2. Login (For Staff)" << endl << "Selection :";
    cin >> role;


    if (role == 1) {
        menuCustomer();
    } else {

        int attempt = 1;
        bool auth = false;
        string username, password;

        headerLogo();

        cout << "Notes : Maximum attempt 3" << endl;

        do {
            cout << "Please enter username:";
            cin >> username;

            cout << "Password:";
            cin >> password;

            string findbyid_query = "SELECT id,username,password,is_manager,name FROM  staff WHERE username = '"+username+"' AND password='"+password+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);
            
            if (!qstate) {
                res = mysql_store_result(conn);
                int ttlRow = mysql_num_rows(res);
                row = mysql_fetch_row(res);

                if (ttlRow > 0) {
                    auth = true;

                    auth_name = row[4];
                  
                    is_manager == false;
                    //check if manager
                    if (stoi(row[3]) == 1) {
                        is_manager = true;
                    }

                    menuStaff();

                }
                else {
                    attempt++;
                    cout << endl << "Invalid username/password (" << attempt << " attempt(s))" << endl;
                }
            }
            else {
                cout << endl << "Error MYSQL";
            }
        } while (auth == false && attempt <= 3);

        main();
    }

}

void menuCustomer() {

    int chooseOneFromMenu = 0;
    char exitSurity;

    headerLogo();

    mysql_query(conn, "SELECT * FROM settings");
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    string happy_hour_active = row[0], discount_rate = row[1], new_hha, new_dr;

    if (happy_hour_active == "1") {
        cout << endl << "--- Enjoy Happy Hour With Discount " + discount_rate + "% ---" << endl << endl;
    }

    cout << "Please Select Menu" << endl;
    cout << "1. New Order" << endl;
    cout << "2. View Order" << endl;
    cout << "3. Back" << endl;

    cout << endl;
    cout << "Selection :";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {

    case 1:
        newOrder();
        break;
    case 2:
        viewOrder();
        break;

    case 3 :
        main();
        break;
    case 9:
    ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {
  
        }
        else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            menuCustomer();
        }
        else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 2. Press Enter To Continue...";
        _getch();
        system("cls");
        menuCustomer();
        break;
    }

}

void menuStaff() {

    int chooseOneFromMenu = 0;
    char exitSurity;

    headerLogo();

    cout << "Hye!" << auth_name << "," << endl << endl;
    cout << "-------------------------------" << endl;
    cout << "            ADMIN PANEL        " << endl;
    cout << "-------------------------------" << endl;
    cout << "1. View New Order" << endl;

    if (is_manager) {
        cout << "2. Update Menu" << endl;
        cout << "3. Insert New Menu" << endl;
        cout << "4. View Monthly Sale" << endl;
        cout << "5. View All Staff" << endl;
        cout << "6. Add Staff" << endl;
        cout << "7. System Setting" << endl;
    }

    cout << "8. Logout" << endl;



    cout << endl;
    cout << "Selection :";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {

    case 1:
        newOrderList();
        break;
    case 2:
        updateItem();
        break;
    case 3:
        insertItem();
        break;
    case 4:
        viewMonthlySale();
        break;
    case 5 :
        viewStaff();
        break;
    case 6 : 
        addStaff();
        break;
    case 7 :
        setting();
        break;

    case 8 :
        logout();
        break;
    case 9:
    ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {

        }
        else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            menuStaff();
        }
        else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 6. Press Enter To Continue...";
        _getch();
        system("cls");
        menuStaff();
        break;
    }
}

void newOrder() {

    system("cls");

    mysql_query(conn, "SELECT * FROM settings");
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    string happy_hour_active = row[0], discount_rate = row[1];

    int x = 1, orderItemId[20] = { NULL };
    string code = "", orderItemPrice[20];
    char again;
    float ttl_price = 0.00;

    do {

        headerLogo();
        cout << " >>    ORDER     <<" << endl << endl;

        qstate = mysql_query(conn, "SELECT id,code,name,price FROM items WHERE is_deleted = 0");
        res = mysql_store_result(conn);
        cout << "--------------------------------" << endl;
        cout << "NO |\tCODE |\tPRICE |\tNAME" << endl;
        cout << "--------------------------------" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << " |\t" << row[1] << " |\tRM" << row[3] << " |\t" << row[2] << endl;
        }

        cout << "--------------------------------" << endl << endl;


        cout << "Insert Food/Drink Code (Item No. " << x << ')' << endl;
        cout << "CODE :";
        cin >> code;

        string findbyid_query = "SELECT * FROM items WHERE code = '" + code + "'";
        const char* qi = findbyid_query.c_str();
        qstate = mysql_query(conn, qi);

        if (!qstate){
            res = mysql_store_result(conn);

            int ttlRow = mysql_num_rows(res);

            if (ttlRow > 0){

                row = mysql_fetch_row(res);
                cout << "MENU :" << row[1] << "-" << row[2] << endl;
                cout << "RM :" << row[4] << endl << endl;

                ttl_price += stof(row[4]);
                orderItemPrice[x] = row[4];

                //store data to array
                string item_id = row[0];
                orderItemId[x] = atoi(item_id.c_str()); //convert string to int

                x++;
      
            } else {
                cout << "Item not found!" << endl;
            }

        } else {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        

        cout << "Add other item?(Y/y) or (N/n) or 'x' to cancel'" << endl;
        cin >> again;

        if (again == 'x') {
            menuCustomer();
        }


    } while ((again == 'Y') || (again == 'y'));

    //check at least 1 order


    //list out all order list

    system("cls");

    //discount

    int discount = 0;
    double after_discount;

    if (happy_hour_active == "1") {
        discount = stof(discount_rate);
        after_discount = (double)ttl_price - (discount/(double)100 * (double)ttl_price);
    }
    else {
        after_discount = ttl_price;
    }

    //insert into order
    string order_q = "INSERT INTO orders(price, status, discount_rate, after_discount) values ('" + to_string(ttl_price) + "', 1, '"+to_string(discount)+"', '"+to_string(after_discount)+"')";
    const char* order_str = order_q.c_str();
    qstate = mysql_query(conn, order_str);

    //get last row id
    string last_id_q = "SELECT id FROM orders ORDER by id DESC LIMIT 1";
    const char* lid_str = last_id_q.c_str();
    qstate = mysql_query(conn, lid_str);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    string order_id = row[0];

    for (int i = 1; i <= 11; i++) {

        if (orderItemId[i] != NULL) {

            string order_id = row[0];

            string order_q = "INSERT INTO order_items (order_id, item_id, price, notes) VALUES ('"+ order_id +"', '"+to_string(orderItemId[i])+"','"+ orderItemPrice[i] +"','EX NOTES')";
            const char* order_str = order_q.c_str();
            qstate = mysql_query(conn, order_str);
            
        } else {
            break; // exit from loop;
        }
    }

    printReceipt(order_id);

    cout << endl << "Your order No is : #" << order_id << endl << "Enter any key to continue =>";
    cin >> order_id;

    menuCustomer();
}

void viewOrder() {
    
    string order_id;
    bool res_found = false;
    do {

        //list out all order list

        headerLogo();
        cout << " >>    VIEW ORDER     <<" << endl << endl;

        cout << "Order No :";
        cin >> order_id;

        string findbyid_query = "SELECT * FROM orders WHERE id='"+ order_id +"'";
        const char* qi = findbyid_query.c_str();
        qstate = mysql_query(conn, qi);

        if (!qstate) {
            res = mysql_store_result(conn);

            int ttlRow = mysql_num_rows(res);

            if (ttlRow > 0) {

                row = mysql_fetch_row(res);
                res_found = true;
                printReceipt(row[0]);
            } else {
                cout << "Invalid Order No!" << endl;
            }
        } else {
            cout << "MySQL Error" << endl;
        }

    } while (!res_found);

    endMenu();

}

void printReceipt(string id) {

    int indexForId = 0;
    string items[5000];

    string order_q = "SELECT price,status,discount_rate,after_discount,created_at FROM orders WHERE id='"+id+"'";
    const char* order_str = order_q.c_str();
    qstate = mysql_query(conn, order_str);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    string o_status = row[1],
        o_price = row[0],
        discount_rate = row[2],
        after_discount = row[3],
        dt = row[4],
        status[2] = { "On Going", "Ready" };

    headerLogo();
    cout << "===================================" << endl;
    cout << "       RECEIPT #"+ id + "      " << endl << endl;

    cout << "Order Status :" + status[stoi(row[2])] << endl;
    cout << "Time / Date : " << dt << endl;

    string items_q = "SELECT oi.id,i.code,i.name,oi.price FROM order_items AS oi LEFT JOIN items AS i ON i.id=oi.item_id WHERE order_id='" + id + "'";

    const char* qu = items_q.c_str();
    qstate = mysql_query(conn, qu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        cout << "CODE\tPRICE\tNAME\n" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << row[1] << "\tRM" << row[3] << "\t" << row[2] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }
        cout << endl << endl << "\t TOTAL :RM " << o_price;
        cout << endl << "\t DISCOUNT : " << discount_rate << "%";
        cout << endl << "\t ================" << endl;
        cout << "\t  :RM " << after_discount;
        cout << endl << "\t ================" << endl << endl;

        cout << "===================================" << endl;
        cout << "   THANK YOU, PLEASE COME AGAIN    " << endl;
        cout << "===================================" << endl;
    }
    
}

//STAFF FUNCTION

void newOrderList() {

    string
        items[500];

    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    headerLogo();

    cout << " >>    NEW ORDER LIST     <<" << endl << endl;

    qstate = mysql_query(conn, "SELECT id,price,status FROM orders WHERE status = 1");
    if (!qstate) {
        res = mysql_store_result(conn);

        cout << "*NOTE : Select order that you want to mark as complete." << endl << endl;

        cout << "--------------------------------" << endl;
        cout << "ORDER NO |\tSTATUS |TOTAL" << endl;
        cout << "--------------------------------" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << "   " << row[0] << " \t | " << row[2] << " |\tRM" << row[1] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }

        cout << "--------------------------------" << endl << endl;

    }
    else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try {
        cout << "Enter Item No: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e) {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
    }

    if (HaveException == false) {

        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i]) {
                NotInDatabase = true;
            }
            else {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false) {

            string findbyid_query = "SELECT id,status,price FROM orders WHERE status=1 AND id='" + strid + "'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate) {

                MYSQL_ROW order, order_items;
                MYSQL_RES* order_res;

                order_res = mysql_store_result(conn);
                order = mysql_fetch_row(order_res);

                string order_id = order[0];

                string order_item_str = "SELECT oi.id,i.code,i.name,oi.price FROM order_items AS oi LEFT JOIN items AS i ON i.id=oi.item_id WHERE order_id='" + order_id + "'";
                const char* order_item_q = order_item_str.c_str();
                mysql_query(conn, order_item_q);
                res = mysql_store_result(conn);

                headerLogo();
                printReceipt(order_id);
                
                string selection;

                do {

                    //mark as complete
                    cout << "Press (Y/y) to mark order as complete or Press (N/n) to exit. :";
                    cin >> selection;
                    cout << endl;
                    cout << selection;

                } while ((selection != "Y") && (selection != "y") && (selection != "N") && (selection != "n"));

                if ((selection == "Y") || (selection == "y")) {

                    string update_str = "UPDATE orders SET status=2 WHERE id='" + order_id + "'";
                    const char* update_q = update_str.c_str();
                    mysql_query(conn, update_q);
                    
                    cout << "Order No :#" + order_id + " has been set to complete. (Please wait 5 seconds .. .)" << endl;
                    Sleep(5);

                }
            }
            else {
                cout << "Order Not Found in database." << endl;
            }
        } else {
            cout << "Data not found!" << endl;
        }
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'v' to view another order and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        main();
    }
    else if (choose == 'v' || choose == 'V') {
        newOrderList();
    }
    else {
        exit(0);
    }

}

// MANAGET FUNCTION

void insertItem() {


    checkManager();

    headerLogo();
    cout << " >>    ADD MENU     <<" << endl << endl;

    string code;
    char name[100] = { 0 };
    float price;
    int type;
    bool proceed = false;


    //select type
    do {

        cout << "Select type :" << endl;
        cout << "1. Food" << endl;
        cout << "2. Drink" << endl;
        cout << endl << "Selection : ";
        cin >> type;

        if (type == 1 || type == 2) {

            proceed = true;

            //generate code
            if (type == 1) {

                //count total food
                qstate = mysql_query(conn, "SELECT count(id) as total FROM items WHERE type=1");

                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);

                string total = row[0];
                code = "F" + total;

            }
            else if (type == 2) {

                //count total drink
                qstate = mysql_query(conn, "SELECT count(id) as total FROM items WHERE type=2");

                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);

                string total = row[0];
                code = "D" + total;
            }
        }

    } while (!proceed);

    cout << "Name :";
    cin.getline(name, 100);

    price = NULL;
    cout << "Insert Price: RM ";
    cin >> price;


    string item_q = "INSERT INTO items (code, name, is_available, price, is_deleted, type) VALUES ('" + code + "', '" + name + "',1, '" + to_string(price) + "', 0,'" + to_string(type) + "')";
    const char* item_str = item_q.c_str();
    qstate = mysql_query(conn, item_str);

    if (!qstate) {
        cout << "New menu inserted!" << endl;

        char choose;
    ExitMenu:
        cout << "Press any key to back main menu?=>";
        cin >> choose;
        menuStaff();

    }
    else {
        cout << "Mysql error!" << endl;
    }

}

void updateItem() {


    checkManager();

    system("cls");

    // Variables
    string code = "",
        name = "",
        price = "",
        is_deleted = "",
        type = "",
        items[500],
        new_name, new_price, new_type;

    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    headerLogo();
    cout << ">>        EDIT MENU      <<" << endl;

    qstate = mysql_query(conn, "SELECT id,code,name,price FROM items WHERE is_deleted = 0");
    if (!qstate) {
        res = mysql_store_result(conn);

        cout << "--------------------------------" << endl;
        cout << "NO |\tCODE |\tPRICE |\tNAME" << endl;
        cout << "--------------------------------" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << " |\t" << row[1] << " |\tRM" << row[3] << " |\t" << row[2] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }

        cout << "--------------------------------" << endl << endl;

    }
    else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try {
        cout << "Enter Item No: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e) {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i]) {
                NotInDatabase = true;
            }
            else {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false) {

            string findbyid_query = "SELECT id,code,name,price,type FROM items WHERE id='" + strid + "' AND is_deleted=0";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate) {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res))) {
                    code = row[1];
                    name = row[2];
                    price = row[3];
                    type = row[4];
                }
            }
            else {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');

            cout << "Enter Name (Enter 'xn' to not change): ";
            getline(cin, new_name);
            if (new_name == "xn") {
                new_name = name;
            }

            cout << "Enter Price (Enter 'xn' to not change): ";
            getline(cin, new_price);
            if (type == "xn") {
                new_price = price;
            }

            cout << "Enter Type:" << endl;
            cout << "1 => FOOD" << endl;
            cout << "2 => DRINK" << endl;
            cout << "xn => Not change" << endl;
            cout << "Type :";

            getline(cin, new_type);
            if (type == "xn") {
                new_type = type;
            }

            string update_query = "UPDATE items SET name='" + new_name + "', price='" + new_price + "',type='" + new_type + "' WHERE id='" + strid + "'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate) {
                cout << endl << "Successfully Saved In Database." << endl;
            }
            else {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else {
            cout << "Item Not Found in database." << endl;
        }
    }

    endMenuStaff();


}

void viewMonthlySale() {

    checkManager();
    //max day in a year
    int year,
        month = 1;

    headerLogo();

    cout << ">>  Monthly Sale Report <<" << endl << endl;

    
    do {
        cout << "Please Enter Years(EX:2020). Year > :";
        cin >> year;

    } while (year < 1990 || year > 2020);

    string date_str[31];
    float monthly_sale[12] = {0.00};

    while (month <= 12){

        string dt = to_string(year) + "-" + to_string(month);


        string daily_sale_str = "select created_at,sum(after_discount) from orders where YEAR(created_at) = '"+to_string(year)+"' AND MONTH(created_at) = '"+to_string(month)+"' group by month(created_at);";
        const char* daily_sale_q = daily_sale_str.c_str();
        mysql_query(conn, daily_sale_q);
        res = mysql_store_result(conn);

        int ttlRow = mysql_num_rows(res);

        if (ttlRow > 0) {
            row = mysql_fetch_row(res);
            monthly_sale[month] = stof(row[1]);
        } else {
            monthly_sale[month] = stof("0");
        }

        date_str[month] = dt;
        month++;

    }

    //reuse var
    month = 1;

    headerLogo();
    cout << "MONTHLY SALE REPORT FOR " + to_string(year) << endl << endl;

    TextTable t('-', '|', '+');

    t.add("DATE");
    t.add("TOTAL SALE");
    t.endOfRow();

    while (month <= 12){
       
        t.add(date_str[month]);
        t.add("RM "+to_string(monthly_sale[month]));
        t.endOfRow();
        month++;
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;

    endMenuStaff();
}

void addStaff() {

    checkManager();

    string username, password,is_admin = "0";
    char selection;
    bool unique = false;

    headerLogo();

    cout << ">>    ADD STAFF   <<" << endl << endl;

    do {

        cout << "Username:";
        cin >> username;

        string user_str = "SELECT * FROM staff WHERE username='" + username + "'";
        const char* user_q = user_str.c_str();
        mysql_query(conn, user_q);
        res = mysql_store_result(conn);
        int ttl_row = mysql_num_rows(res);

        if (ttl_row == 0) {
            unique = true;
        } else {
            cout << "Username already exist! Please enter another username." << endl;
        } 

    } while (!unique);

    cout << "Password :";
    cin >> password;

    char name[100] = { 0 };

    cout << "Name :";
    cin.getline(name, 100);

    cout << "Set as admin? (Y/y) :";
    cin >> selection;

    if (selection == 'y' || selection == 'Y') {
        is_admin = 1;
    }
    
    string insert_str = "INSERT INTO staff (username,password,name,is_admin) VALUES ('" + username + "','" + password + "', '" + name + "', '" + is_admin + "')";
    const char* insert_q = insert_str.c_str();
    qstate = mysql_query(conn, insert_q);

    if (!qstate) {
        cout << "Data inserted!";
    } else {
        cout << "MySQL error!";
    }

    endMenuStaff();
    
}

void viewStaff() {


    checkManager();

    system("cls");

    // Variables
    string username = "",
        password = "",
        name = "",
        is_admin = "",
        items[500],
        new_username, new_password, new_name, new_is_admin;

    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    headerLogo();
    cout << ">>        Staff List      <<" << endl;

    qstate = mysql_query(conn, "SELECT id,username,name,is_admin FROM staff");
    if (!qstate) {
        res = mysql_store_result(conn);

        TextTable t('-', '|', '+');

        t.add("STAFF NO");
        t.add("USERNAME");
        t.add("NAME");
        t.add("ADMIN");
        t.endOfRow();

        while ((row = mysql_fetch_row(res))) {

            t.add(row[0]);
            t.add(row[1]);
            t.add(row[2]);

            if (row[3] == "1") {
                t.add("YES");
            }
            else {
                t.add("NO");
            }
            t.endOfRow();

            items[indexForId] = row[0];
            indexForId++;
        }

        t.setAlignment(3, TextTable::Alignment::RIGHT);
        cout << t;

        cout << "--------------------------------" << endl << endl;

    }
    else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try {
        cout << "Enter Staff No: (Enter 0 to exit) : =>";
        cin >> itemId;
        cout << endl;

        if (itemId == 0) {
            menuStaff();
        }
    }
    catch (exception e) {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i]) {
                NotInDatabase = true;
            }
            else {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false) {

            string findbyid_query = "SELECT id,username,password,name,is_admin FROM staff WHERE id='"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate) {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res))) {
                    username = row[1];
                    password = row[2];
                    name = row[3];
                    is_admin = row[4];
                }
            }

            else {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');

            cout << endl << "Enter Username (Enter 'xn' to not change): ";
            cin >> new_username;
            if (new_username == "xn") {
                new_username = username;
            }

            cout << endl << "Enter Password (Enter 'xn' to not change): ";
            cin >> new_password;
            if (new_password == "xn") {
                new_password = password;
            }

            cout << endl << "Enter Name (Enter 'xn' to not change): ";
            getline(cin, new_name);
            if (new_name == "xn") {
                new_name = name;
            }

            if (is_admin == "1") {
                cout << "Staff is admin.";
            }
            else {
                cout << "Staff is not admin";
            }


            string acc_selection;
            cout << endl << "Enter (Y/y) to switch account type or 'xn' to not change";
            cin >> acc_selection;

            if (acc_selection == "Y" || acc_selection == "y") {
                
                if (is_admin == "1") {
                    new_is_admin == "0";
                }
                else {
                    new_is_admin = "1";
                }
            }
            else {
                new_is_admin = is_admin;
            }

            string update_query = "UPDATE items SET username='"+new_username+"',password='"+new_password+"',name='"+new_name+"',is_admin='"+new_is_admin+"' WHERE id='" + strid + "'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate) {
                cout << endl << "Successfully Saved In Database." << endl;
            }
            else {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else {
            cout << "Item Not Found in database." << endl;
        }
    }

    endMenuStaff();


}

void setting() {

    checkManager();
    headerLogo();

    mysql_query(conn, "SELECT * FROM settings");
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    string happy_hour_active = row[0], discount_rate = row[1], new_hha, new_dr;

    TextTable t('-', '|', '+');

    t.add("HAPPY HOUR");
    if (happy_hour_active == "1") {
        t.add("ACTIVE");
    } else {
        t.add("INACTIVE");
    }
    t.endOfRow();

    t.add("DISCOUNT RATE(&)");
    t.add(discount_rate);
    t.endOfRow();
    t.setAlignment(3, TextTable::Alignment::RIGHT);
    cout << t;

    string selection,new_hho,new_rate;
    cout << "Enter (Y/y) to update or other to back Menu. : =>";
    cin >> selection;

    if (selection == "y" || selection == "Y") {

        new_hho = happy_hour_active;

        if (happy_hour_active == "1") {

            cout << "Deactivate Happy Hour Status? Enter (Y/y) or (N/n). =>";
            cin >> selection;
            
            if (selection == "y" || selection == "Y") {
                new_hho = "0";
            }
        } else {
            cout << "Activate Happy Hour Status? Enter (Y/y) or (N/n). =>";
            cin >> selection;

            if (selection == "y" || selection == "Y") {
                
                new_hho = "1";
            }
        }

        cout << "Current rate :" << discount_rate << "%, Enter new value to update or 'xn' to skip. =>";
        cin >> new_rate;

        if (new_rate == "xn" || new_rate == "XN") {

        }
        else {


            
            try {
                int x = stoi(new_rate);

                if (x < 0 || x > 100) {
                    cout << "Invalid input. Discount rate not changed." << endl;
                    new_rate = discount_rate;
                }
            }
            catch (exception e) {
                cout << "Invalid rate input";
                new_rate = discount_rate;
            }
        }

        string update_str = "UPDATE settings SET happy_hour_active='"+ new_hho +"', discount_rate='"+new_rate+"'";
        const char* update_q = update_str.c_str();
        qstate = mysql_query(conn, update_q);

        if (!qstate) {
            cout << "Setting updated!";
        }
        else {
            cout << "Setting failed to update!";
            cout << "Enter any key to continue. =>";
            cin >> selection;
        }
        setting();
    } else {

        menuStaff();
    }
}

void endMenu() {

    char choose;
    ExitMenu:
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        menuCustomer();
    } else {
        main();
    }
}

void endMenuStaff() {

    char choose;
ExitMenu:
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        menuStaff();
    }else {
        main();
    }
}

void headerLogo() {

    system("cls");
    cout << endl << "===================================" << endl;
    cout << "|| QAYYUM MAMAK STYLE RESTAURANT ||" << endl;
    cout << "===================================" << endl << endl;
}

void checkManager() {

    string x; 

    if (!is_manager) {
        cout << "Ops! Not allowed!. Enter any key to continue.";
        cin >> x;
        main();
    }
}

void logout() {

    string selection;
    cout << "Are you sure want to logout? (Y/y) or (N/n). =>";
    cin >> selection;

    if (selection == "y" || selection == "Y") {
        is_manager = false;
        main();
    }
    else {
        menuStaff();
    }
}
