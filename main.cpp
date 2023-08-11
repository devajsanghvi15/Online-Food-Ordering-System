#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<stdexcept>
#include<exception>
#include<typeinfo>
#include<cstdlib>

using namespace std;

int assign_order;

class Person;
class Customer;
class DeliverPerson;
class Order;
class Payment;
class FoodItem;
class Menu;
class Restaurant;

class Person
{
public:
    string name;
    string phoneNo;
    char gender;
    string address;

    Person(string name, string phoneNo, char gender, string address)
    {
        this->name = name;
        this->phoneNo = phoneNo;
        this->gender = gender;
        this->address = address;
    }

    virtual void details() = 0;

};

class DeliveryPerson:public Person
{
public:
    int deliveryPersonId;

    DeliveryPerson(string name, string phoneNo, char gender, string address,int deliveryPersonId):Person(name,phoneNo,gender,address)
    {
        this->deliveryPersonId = deliveryPersonId;
    }

    void details()
    {
        cout<<endl<<"Name: "<<name;
        cout<<endl<<"Phone No: "<<phoneNo;
        cout<<endl<<"Gender: "<<gender;
        cout<<endl<<"Address: "<<address;
        cout<<endl<<"Delivery person ID: "<<deliveryPersonId;
    }
};

class FoodItem
{
public:
    int FoodId;
    string FoodName;
    int FoodPrice;
    string FoodType;

    FoodItem(int FoodId, string FoodName, int FoodPrice, string FoodType)
    {
        this->FoodId = FoodId;
        this->FoodName = FoodName;
        this->FoodPrice = FoodPrice;
        this->FoodType = FoodType;
    }

    void getFoodDetails()
    {
        cout<<left<<setw(20)<<FoodName<<left<<setw(20)<<FoodPrice<<left<<setw(20)<<FoodType<<endl;
    }

    void updateFoodDetails()
    {
        cout<<"\nEnter the new price of "<<FoodName<<": ";
        cin>>FoodPrice;
    }
};

class Menu
{
public:
    vector<FoodItem> food;             //list of food items;

    Menu(vector<FoodItem> food)
    {
        this->food = food;
    }

    void showMenu()
    {
        int i;
        cout<<endl<<left<<setw(8)<<"S.No"<<left<<setw(25)<<"Name"<<left<<setw(15)<<"Type"<<left<<setw(5)<<"Price"<<endl;
        for(i=0; i<food.size(); i++)
        {
            cout<<left<<setw(8)<<food[i].FoodId<<left<<setw(25)<<food[i].FoodName<<left<<setw(15)<<food[i].FoodType<<left<<setw(5)<<food[i].FoodPrice<<endl;
        }
    }
};

class Restaurant
{
public:
    int restaurantId;
    string restaurantName;
    string restaurantAddress;
    Menu restaurantMenu;

    Restaurant(int restaurantId, string restaurantName, string restaurantAddress, Menu restaurantMenu):restaurantMenu(restaurantMenu)
    {
        this->restaurantId = restaurantId;
        this->restaurantName = restaurantName;
        this->restaurantAddress = restaurantAddress;
    }

    void updateRestaurantDetails()
    {
        cout<<"\nEnter new name for the restaurant: ";
        getline(cin,restaurantName);
        cout<<"\nEnter new address for the restaurant: ";
        getline(cin,restaurantAddress);
    }
};

class Customer:public Person
{
public:
    int customerId;
    int walletBalance;
    vector<Order> orders;

    Customer(string name, string phoneNo, char gender, string address,int customerId, int walletBalance):Person(name,phoneNo,gender,address)
    {
        this->customerId = customerId;
        this->walletBalance = walletBalance;
    }

    void details()
    {
        cout<<endl<<"Name: "<<name;
        cout<<endl<<"Phone No: "<<phoneNo;
        cout<<endl<<"Gender: "<<gender;
        cout<<endl<<"Address: "<<address;
        cout<<endl<<"Customer ID: "<<customerId;
        cout<<endl<<"Wallet Balance: "<<walletBalance<<endl;
    }

    friend void recentlyPlacedOrders();
    friend void clearRecentlyPlacedOrders();
};

Customer c1("Devaj", "9384999999", 'M', "Vijayawada Vatturi Vari Street", 12344, 2000);

class Payment
{
public:
    int orderId;
    string paymentMethod;

    Payment(int orderId, string paymentMethod = "Wallet Balance")
    {
        this->orderId = orderId;
        this->paymentMethod = paymentMethod;
    }

    string makePayment(Customer &c, int total)
    {
        if(c.walletBalance >= total)
        {
            assign_order = 1;
            c.walletBalance -= total;
            return "Order placed";
        }
        else
        {
            assign_order = 0;
            return "cannot place order, insufficient wallet balance";
        }
    }
};

class Order
{
public:
    int orderId;
    DeliveryPerson d;
    vector<FoodItem> foodItems;

    Order(int orderId, DeliveryPerson d):d(d)
    {
        this->orderId = orderId;
    }


    void placeOrder(Menu menu, Customer &c, Order &o)
    {
        int x,flag=0,flag1=0,total=0;
        menu.showMenu();
        cout<<endl<<"Enter the S.No of the item you want to add to your cart: "<<endl<<endl;
        cout<<"6. Move to billing page";
        cout<<endl<<"7. View Cart";
        cout<<endl<<"8. Clear cart"<<endl;
        cout<<"9. Go to previous page"<<endl;
        while(1)
        {
            try
            {
                cin>>x;
                if(!cin.good())
                {
                    cin.clear();
                    cin.ignore(100,'\n');
                    throw 1;
                }
                if(x<1 || x>9)
                {
                    throw 2;
                }
                switch(x)
                {
                case 1 ... 5:
                    foodItems.push_back(menu.food.at(x-1));
                    cout<<endl<<menu.food[x-1].FoodName<<" added to cart\n";
                    break;

                case 6:
                    if(foodItems.size() == 0)
                    {
                        cout<<"\nNo items added to the cart"<<endl;
                    }
                    else
                    {
                        int i;
                        cout<<"***************************************************************************************"<<endl;
                        cout<<setw(50)<<"BILL";
                        cout<<endl<<left<<setw(25)<<"Name"<<left<<setw(5)<<"Price"<<endl;
                        for(i=0; i<foodItems.size(); i++)
                        {
                            cout<<left<<setw(25)<<foodItems[i].FoodName<<left<<setw(5)<<foodItems[i].FoodPrice<<endl;
                            total += foodItems[i].FoodPrice;
                        }
                        cout<<endl<<left<<setw(25)<<"Total"<<left<<setw(5)<<total<<endl;
                        cout<<"***************************************************************************************"<<endl;
                        flag=1;
                    }
                    break;

                case 7:
                    if(foodItems.size()==0)
                    {
                        cout<<endl<<"Cart is empty"<<endl;
                    }
                    else
                    {
                        int i;
                        for(i=0; i!=foodItems.size(); i++)
                        {
                            cout<<endl<<foodItems[i].FoodName;
                        }
                        cout<<endl;
                    }
                    break;

                case 8:
                    if(foodItems.size()==0)
                    {
                        cout<<endl<<"Cart is empty"<<endl;
                    }
                    else
                    {
                        foodItems.clear();
                        cout<<endl<<"Cart cleared"<<endl;
                    }
                    break;

                case 9:
                    flag1=1;
                    break;

                }
                if(flag1==1)
                {
                    cout<<endl<<"Loading the restaurant page...";
                    return;
                }
                if(flag==1)
                {
                    break;
                }
            }
            catch(int a)
            {
                cout<<endl<<"Enter an appropriate choice"<<endl;
            }

        }
        int choice,flag2=0;
        while(flag2==0)
        {
            cout<<endl<<"1. Place Order"<<endl;
            cout<<"2. Cancel Order"<<endl;
            try
            {
                cin>>choice;
                if(!cin.good())
                {
                    cin.clear();
                    cin.ignore(100,'\n');
                    throw 1;
                }
                if(choice<1 || choice>2)
                {
                    throw 2;
                }
                switch(choice)
                {
                case 1:
                    if(flag==1)
                    {
                        Payment p(orderId, "Wallet Balance");
                        cout<<p.makePayment(c,total);
                        if(assign_order)
                        {
                            cout<<endl<<d.name<<" is assigned with your order"<<endl;
                            c.orders.push_back(o);
                        }
                        cout<<endl<<"Wallet Balance: "<<c.walletBalance;
                        foodItems.clear();
                    }
                    else
                    {
                        cout<<endl<<"No items added to the cart"<<endl;
                    }
                    flag2=1;
                    break;

                case 2:
                    if(flag==1)
                    {
                        foodItems.clear();
                        cout<<endl<<"Order canceled"<<endl;
                    }
                    else
                    {
                        cout<<endl<<"No items added to the cart"<<endl;
                    }
                    flag2=1;
                    break;
                }
            }
            catch(int a)
            {
                cout<<endl<<"Enter an appropriate choice";
            }
        }
    }

};

void recentlyPlacedOrders()
{

    if(c1.orders.size()==0)
    {
        cout<<endl<<"No orders have been placed";
    }
    else
    {
        cout<<endl<<"Recently placed orders: "<<endl;
        for(int i=c1.orders.size()-1; i>=0; i--)
        {
            cout<<"***************************************************************************************";
            cout<<endl<<left<<setw(20)<<"Name"<<left<<setw(20)<<"Price"<<left<<setw(20)<<"Type"<<endl;
            for(int j=0; j<c1.orders[i].foodItems.size(); j++)
            {
                c1.orders[i].foodItems[j].getFoodDetails();
            }
        }
        cout<<"***************************************************************************************";
    }
}

void clearRecentlyPlacedOrders()
{
    if(c1.orders.size()==0)
    {
        cout<<endl<<"No orders have been placed";
    }
    else
    {
        c1.orders.clear();
        cout<<endl<<"Recently placed order histoey has been cleared";
    }
}

int main()
{

    DeliveryPerson d1("Raju", "7364538209", 'M', "Gokul Road", 1);
    DeliveryPerson d2("Diya", "9384726400", 'F', "Navnagar", 2);
    DeliveryPerson d3("Shyaam", "9748294393", 'M', "Naveen Park",3);

    FoodItem f1(1,"Vada Pav",20,"Veg");
    FoodItem f2(2,"Bhel Puri",30,"Veg");
    FoodItem f3(3,"Chicken Biryani",130,"Non-Veg");
    FoodItem f4(4,"Bread Omlette",150,"Non-Veg");
    FoodItem f5(5,"Mango Lassi",60,"Veg");
    vector<FoodItem> x1 = {f1,f2,f3,f4,f5};
    Menu menu1(x1);
    Restaurant r1(1,"Spirit of India","Keshwapur",menu1);

    FoodItem f6(1,"Veg Cheese Pizza",150,"Veg");
    FoodItem f7(2,"Bruschetta",180,"Veg");
    FoodItem f8(3,"Lasagna",200,"Non-Veg");
    FoodItem f9(4,"Bombardino",120,"Non-Veg");
    FoodItem f10(5,"Limoncello",110,"Veg");
    vector<FoodItem> x2 = {f6,f7,f8,f9,f10};
    Menu menu2(x2);
    Restaurant r2(2,"The Sunday Sauce","Gokul Road",menu2);

    FoodItem f11(1,"Veg Manchurian",80,"Veg");
    FoodItem f12(2,"Chicken Noodles",150,"Non-Veg");
    FoodItem f13(3,"Mutton Dumplings",170,"Non-Veg");
    FoodItem f14(4,"Kung Pao Chicken",250,"Non-Veg");
    FoodItem f15(5,"Bubble Tea",160,"Veg");
    vector<FoodItem> x3 = {f11,f12,f13,f14,f15};
    Menu menu3(x3);
    Restaurant r3(3,"Dragon Palace","Vidyanagar",menu3);

    vector<Restaurant> restaurantList = {r1,r2,r3};

    Order o1(1,d1);
    Order o2(2,d2);
    Order o3(3,d3);

    cout<<setw(75)<<"Welcome";
    int choice,i;
    while(1)
    {
        cout<<endl<<"Select a restaurant"<<endl;
        for(i=0; i!=restaurantList.size(); i++)
        {
            cout<<restaurantList[i].restaurantId<<". "<<restaurantList[i].restaurantName<<endl;
        }
        cout<<endl<<endl<<"4. View your details"<<endl;
        cout<<"5. View recent orders"<<endl;
        cout<<"6. Clear recently placed orders history"<<endl;
        cout<<"7. Exit app"<<endl;
        cout<<"Enter a number: ";
        try
        {
            cin>>choice;
            if(!cin.good())
            {
                cin.clear();
                cin.ignore(100,'\n');
                throw 1;
            }
            if(choice<1 || choice>7)
            {
                throw 2;
            }
            switch(choice)
            {
            case 1:
                o1.placeOrder(r1.restaurantMenu,c1,o1);
                break;

            case 2:
                o2.placeOrder(r2.restaurantMenu,c1,o2);
                break;

            case 3:
                o3.placeOrder(r3.restaurantMenu,c1,o3);
                break;

            case 4:
                c1.details();
                break;

            case 5:
                recentlyPlacedOrders();
                break;

            case 6:
                clearRecentlyPlacedOrders();
                break;

            case 7:
                cout<<endl<<"Thank You";
                exit(0);
            }

        }
        catch(int x)
        {
            cout<<endl<<"Enter an appropriate choice";
        }
    }
    return 0;
}