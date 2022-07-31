

// Grocer app 2.o (DSA_Sem_Project).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <ctime>
#include <queue>
#include<cctype>
using namespace std;
string filename_employees = "employees.csv";
string filename_products = "Products.csv";
string filename_Sales = "Sales.csv";


void tokenize(string& str, char delim, vector<string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}




class node
{
public:
	node* next;
	string name, SerialNo;
	float Avail_Quantity_inKg = 0;string Buyer_Quantity;
	string price_perKg;

	node(string SerialNo, string name, float Avail_Quantity_inKg, string price_perKg)
	{
		next = NULL;
		this->name = name;
		this->SerialNo = SerialNo;
		this->Avail_Quantity_inKg = Avail_Quantity_inKg;
		this->price_perKg = price_perKg;
	}

	
	node(string seri, string name, string bq, string price)
	{
		next = NULL;
		this->name = name;
		this->SerialNo = seri;
		this->Buyer_Quantity = bq;
		this->price_perKg = price;
	}
};




class linkedlist
{
public:
	node* head;
	node* tail;
	
	linkedlist()
	{
		head = NULL;
		tail = NULL;
	}

	void insert(string SerialNo, string name, float Avail_Quantity_inKg,string price_perKg)
	{
		node* ne = new node(SerialNo,name, Avail_Quantity_inKg, price_perKg);

		if (head == NULL)
		{
			head = tail = ne;
		}
		else
		{
			tail->next = ne;
			tail = ne;
		}
	}


	void insert(string serial, string name,string bq,string pri)
	{
		node* ne = new node(serial, name, bq, pri);

		if (head == NULL)
		{
			head = tail = ne;
		}
		else
		{
			tail->next = ne;
			tail = ne;
		}
	}


	string search(string s,string quan)
	{
		node* temp = head;
		while (temp != NULL)
		{
			string ser = temp->SerialNo;

			transform(ser.begin(), ser.end(), ser.begin(),[](unsigned char c) { return std::tolower(c); });
			transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
			
			if (temp->next == NULL)
			{
				if (ser==s)
					if (temp->Avail_Quantity_inKg >= stof(quan))
					{
						float price	=Calculate_Price(stof(temp->price_perKg),stof(quan));
						temp->Buyer_Quantity = quan;
						temp->Avail_Quantity_inKg -= stof(quan);
						return (temp->SerialNo + "," + temp->name + "," + temp->Buyer_Quantity + "," + to_string(price));
					}
					else
						return "Empty";
			}
			else
			{
				if (ser == s)
					if (temp->Avail_Quantity_inKg >= stof(quan))
					{
						float price = Calculate_Price(stof(temp->price_perKg), stof(quan));
						temp->Buyer_Quantity = quan;
						temp->Avail_Quantity_inKg -= stof(quan);
						vector<string> a;                    // Splitting up the comma separated string
						// tokenize(temp->price_perKg, '/', a);
						// string array[2]; int i = 0;
						// for (auto it : a)
						// {
						// 	array[i] = it;
						// 	i++;
						// }
						return (temp->SerialNo + "," + temp->name + "," + temp->Buyer_Quantity+"," + to_string(price));
					}
					else
						return "Empty";

			}
			temp = temp->next;
		}
	}

	float Calculate_Price(float price_perKg, float qu)
	{
		return (price_perKg * qu);
		
	}
	
	void print()
	{
		cout << "=====================================================          Catalog          ==============================================\n\n";
		cout << "\t\t\t\t\t\tSerial No\tName\t\t\tPrice\n\n";

		node* temp = head;
		while (temp != NULL)
		{
			if (temp->next == NULL)
			{
				if(temp->name.length()<=7)
					cout <<"\t\t\t\t\t\t"<<temp->SerialNo<<"\t\t"<< temp->name << "\t\t\t"<< temp->price_perKg << "\n";
				else if(temp->name.length()<=14)
					cout <<"\t\t\t\t\t\t"<< temp->SerialNo << "\t\t" << temp->name << "\t\t" <<temp->price_perKg << "\n";
				else if (temp->name.length() > 14)
					cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t" << temp->price_perKg << "\n";
			}
			else
			{
				if (temp->name.length() <= 7)
					cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t\t" << temp->price_perKg << "\n";
				else if (temp->name.length() <= 14)
					cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t" << temp->price_perKg << "\n";
				else if (temp->name.length() > 14)
					cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t" << temp->price_perKg << "\n";
			}
			temp = temp->next;
		}
		cout << "\n==============================================================================================================================\n\n";
	}




	void print2()
	{
		cout << "=====================================================          Catalog          ==============================================\n\n";
		cout << "\t\t\t\t\t\tSerial No\tName\t\t\tPrice\t\tAvailable Quantity\n\n";

		node* temp = head;
		while (temp != NULL)
		{
			if (temp->next == NULL)
			{
				if (temp->name.length() <= 7)
				{
					if (temp->price_perKg.length() <= 7)
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t\t" << temp->price_perKg << "\t\t" << temp->Avail_Quantity_inKg << "\n";
					else
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t\t" << temp->price_perKg << "\t" << temp->Avail_Quantity_inKg << "\n";
				}
				else if (temp->name.length() <=14)
				{
					if (temp->price_perKg.length() <= 7)
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t" << temp->price_perKg << "\t\t" << temp->Avail_Quantity_inKg << "\n";
					else
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t" << temp->price_perKg << "\t" << temp->Avail_Quantity_inKg << "\n";
				}
				
				else if (temp->name.length() > 14)
				{
					if (temp->price_perKg.length() <= 7)
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t" << temp->price_perKg << "\t\t" << temp->Avail_Quantity_inKg << "\n";
					else
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t" << temp->price_perKg << "\t" << temp->Avail_Quantity_inKg << "\n";
				}
			}

			else
			{
				if (temp->name.length() <= 7)
				{
					if (temp->price_perKg.length() <= 7)
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t\t" << temp->price_perKg << "\t\t" << temp->Avail_Quantity_inKg << "\n";
					else
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t\t" << temp->price_perKg << "\t" << temp->Avail_Quantity_inKg << "\n";
				}
				else if (temp->name.length() <= 14)
				{
					if (temp->price_perKg.length() <= 7)
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t" << temp->price_perKg << "\t\t" << temp->Avail_Quantity_inKg << "\n";
					else
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t\t" << temp->price_perKg << "\t" << temp->Avail_Quantity_inKg << "\n";
				}

				else if (temp->name.length() > 14)
				{
					if (temp->price_perKg.length() <= 7)
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t" << temp->price_perKg << "\t\t" << temp->Avail_Quantity_inKg << "\n";
					else
						cout << "\t\t\t\t\t\t" << temp->SerialNo << "\t\t" << temp->name << "\t" << temp->price_perKg << "\t" << temp->Avail_Quantity_inKg << "\n";
				}
			}
			temp = temp->next;
		}
		cout << "\n==============================================================================================================================\n\n";
	}



	void DEL()
	{
		string n;
		cin.ignore();
		cout << "Enter Serial number of product to be removed: ";
		getline(cin, n);
		bool b = false;
		node* nex;
		node* temp = head;
		while (temp != NULL)
		{
			if (b == false)
			{
				if (temp->next->SerialNo == n)
				{
					nex = temp->next->next;
					temp->next = nex;
					b = true;
				}
			}
			if (temp == NULL)
				break;
			temp = temp->next;
		}
		if (b == true)
			cout << "Product Deleted\n";
		else
			cout << "No data found!\n";
	}

	void FileWrite()
	{
		fstream f;
		f.open(filename_products,ios::out);
		node* temp = head;
		while (temp != NULL)
		{
			if (temp->next == NULL)
			{
				f << temp->SerialNo << "," << temp->name << "," << temp->Avail_Quantity_inKg << "," << temp->price_perKg <<"\n";
			}

			else
			{
				f << temp->SerialNo << "," << temp->name << "," << temp->Avail_Quantity_inKg << "," << temp->price_perKg << "\n";
			}
			temp = temp->next;
		}		
	}


	void Edit(string serial,float quantity)
	{
		node* temp = head;
		while (temp != NULL)
		{
			string ser = temp->SerialNo;
			if (temp->next == NULL)
			{
				cout << temp->Avail_Quantity_inKg << "\n";
				if (ser == serial)
				{
					temp->Avail_Quantity_inKg = quantity;
					break;
				}
			}
			
			else
			{
				cout << temp->Avail_Quantity_inKg << "\n";
				if (ser == serial)
				{
					temp->Avail_Quantity_inKg = quantity;
					break;
				}
			}
			temp = temp->next;
		}

	}
	
	
};




class products :public linkedlist
{
public:
	string Serial;
	string Buyer_Quantity,name,price;
	products() {};
	
	products(string s,string n,string bq,string pr)
	{
		Serial = s;
		Buyer_Quantity = bq;
		name = n;
		price = pr;
	}


	void AProducts()
	{
		fstream f;
		f.open(filename_products, ios::in);
		string name, SerialNo, Avail_Quantity_inKg, price_perKg;


		while (f)
		{
			getline(f, SerialNo, ',');
			getline(f, name, ',');
			getline(f, Avail_Quantity_inKg, ',');
			getline(f, price_perKg, '\n');
			if(SerialNo!="")
				insert(SerialNo, name, stof(Avail_Quantity_inKg), price_perKg);
		}
		cout << "\n\n";

		print();
	}



	void AllProducts()
	{
		fstream f;
		f.open(filename_products, ios::in);
		string name, SerialNo, Avail_Quantity_inKg, price_perKg;


		while (f)
		{
			getline(f, SerialNo, ',');
			getline(f, name, ',');
			getline(f, Avail_Quantity_inKg, ',');
			getline(f, price_perKg, '\n');
			if (SerialNo != "")
				insert(SerialNo, name, stof(Avail_Quantity_inKg), price_perKg);
		}
		cout << "\n\n";

		print2();
	}
	

	
	string check(string ser,string q)
	{
		return search(ser, q);
	}

};




class HashTable
{
private:
	int key;
public:
	int SIZE = 110;
	string* HashArray = new string[SIZE];
	int BloomArray[50];

	int hash3(string word)
	{
		transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
		int seed = 131;
		unsigned long hash = 0;
		for (int i = 0; i < word.length(); i++)
		{
			hash = (hash * seed) + word[i];
		}
		return hash % SIZE;
	}

	void insert(string serial, string na,float Avl_Q, string pri, int key)
	{
		if (HashArray[key] == "")
		{
			HashArray[key] = serial+","+na+","+to_string(Avl_Q)+","+pri;
		}
		else
		{
			if (key + 1 != SIZE)
			{
				insert(serial,na,Avl_Q, pri,key+1);
			}
		}
	}

	
	
	string search(int key, string q, string se)
	{
		vector<string> a;
		tokenize(HashArray[key], ',', a);
		string array1[4]; int i = 0;
		for (auto it : a)
		{
			array1[i] = it;
			i++;
		}
		
		string s = array1[0];
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
		transform(se.begin(), se.end(), se.begin(), [](unsigned char c) { return std::tolower(c); });
		if (s == se)
		{
			if (stof(array1[2]) > stof(q))
			{
				array1[2] = to_string(stof(array1[2]) - stof(q));
				insert(se, array1[1], stof(array1[2]),array1[3],key);
				return array1[0] +","+ array1[1] + "," + q+ ","+to_string(stof(array1[3])* stof(q));
			}
			else
			{
				return "Empty";
			}
		}
		else
		{
			if (key != SIZE)
			{
				search(key+1, q, se);
			}
			else
				return "Empty";
		}
	}



	bool BloomFilter(string ser)
	{
		int k = hash3(ser)%50;
		if (BloomArray[k] == 1)
			return true;
		
		else
		return false;
	}
};






class customer
{
public:
	string name, cnic, contactno, address, Date_and_time;
	int nextproduct;
	float TotalBill;         //Link list and will use bloom filter as well.
	stack<products*>cstack;
	
	customer()
	{
		//system("COLOR 4F");
		cout << "\n\t\tWhat is your name: ";
		getline(cin, this->name);
		cin.clear();
		cout << "\t\tHi, " << this->name << " you are required to mention these details to proceed forward.\n\n\t\tEnter your contact no: ";
		getline(cin, this->contactno);
		cin.clear();
		cout << "\t\tEnter your CNIC no: ";
		getline(cin, this->cnic);
		cin.clear();
		cout << "\t\tEnter deliver-to location: ";
		getline(cin, this->address);
		cin.clear();
		cout << "\n=============================================================================================================================\n";
		cout << "\n\t\tPlease select one of the following:\n";
		cout << "\t\tPress 1) to see all products:\n";
		cout << "\t\tPress 2) to fill up your cart:\n";
		cout << "\t\tPress 3) to exit:\n";
		cout << "\t\tNow press:	";
		products p;
		int proceed;
		cin >> proceed;

		switch (proceed)
		{
		case 1:
			p.AProducts();
			cout << "\n\t\tDo you wanna buy? enter(Y/N) ";
			char buy;
			cin >> buy;
			if (buy == 'Y' || buy == 'y')
				addtocart_By_Serial(p);
			break;

		case 2:
			addtocart_By_Search();
			break;

		case 3:
			break;

		}

	};

	customer(string name, string cnic, string contactno, string address)
	{
		this->name = name;
		this->cnic = cnic;
		this->contactno = contactno;
		this->address = address;
	}


	void addtocart_By_Serial(products p)
	{
		//using stack.
		//products are to be added accordingly.
		//and can be edit or delete from the cart using pop and then push the edited product.
		
		products* n;

		string input,quan;
		bool b = false;

		while (true)
		{
			cin.clear();
			cin.ignore();

			cout << "\t\tPlease enter the serial no very carefully: ";
			getline(cin, input);
			cin.clear();
			
			cout << "\t\tEnter the quantity: ";
			getline(cin,quan);
			
			string data=p.check(input, quan);
			
			if (data != "Empty")
			{
				vector<string> a;                    // Splitting up the comma separated string
				tokenize(data, ',', a);
				string array[4]; int i = 0;
				for (auto it : a)
				{
					array[i]=it;
					i++;
				}
				
				cstack.push(new products(array[0], array[1], array[2],array[3]));
				TotalBill += stof(array[3]);
			}

			cout << "\t\tPress 1): to ad more items into the cart\n\t\tPress 2): ro edit your cart\n\t\tPress 3 to wrap up your cart\n\t\tNow please enter:	";
			cin >> nextproduct;
			if(nextproduct==2)
			{
				string ser, quant;
				cout << "Enter the Serial No to be edited: ";
				cin.clear();
				cin.ignore();
				getline(cin, ser);
				cin.clear();
				cout << "Enter the new quantity:	";
				getline(cin, quant);
				EditCart(cstack, ser, quant);
				Print_Cart(cstack);
			}
			if (nextproduct == 3)
			{
				Print_Cart(cstack);
				break;
			}
		}
		CDetails(cstack, to_string(TotalBill));

	}


	void addtocart_By_Search()
	{
		// add products from the file into hash table using bloom filter and hash function.
		// search/ delete and edit product using bloom filter from the hash table.
		HashTable h;
		fstream f;
		int key = 0;
		f.open(filename_products, ios::in);
		string data;
		string name, SerialNo, Avail_Quantity_inKg, price_perKg;
		bool b = false;
		
		while (f)
		{
			getline(f, SerialNo, ',');
			getline(f, name, ',');
			getline(f, Avail_Quantity_inKg, ',');
			getline(f, price_perKg, '\n');
			if (SerialNo != "")
			{
				key = h.hash3(SerialNo);
				h.insert(SerialNo, name, stof(Avail_Quantity_inKg), price_perKg, key);
				h.BloomArray[h.hash3(SerialNo) % 50]=1;
			}
		}
		
		while (true)
		{
			int check;
			cout << "\n\t\tpress 1 to add: or Press 0 to pack up your cart and proceed to pay: ";
			cin >> check;
			if (check == 0)
			{
				break;
			}
			cin.clear();
			cin.ignore();
			cout << "\t\tPlease enter the serial no very carefully: ";
			getline(cin, SerialNo);
			cin.clear();
			cout << "\t\tEnter the quantity in Kg,Lt or number of items: ";
			getline(cin, data);
			
			int k = h.hash3(SerialNo);
			if(h.BloomArray[k%50]!=1)
			{
				cout << "\n\t\tThis product is not available! \n";
				break;
			}
			
			string search = h.search(k, data, SerialNo);
			if (search == "Empty")
			{
				cout << "\t\tData not found! Please enter again:	\n";
				return addtocart_By_Search();
			}
			
			vector<string> a;
			tokenize(search, ',', a);
			string array[4]; int i = 0;
			for (auto it : a)
			{
				array[i] = it;
				i++;
			}

				cstack.push(new products(array[0], array[1], array[2], array[3]));
				TotalBill += stof(array[3]);
				cout << "\t\tPress 1): to ad more items into the cart\n\t\tPress 2): ro edit your cart\n\t\tPress 3 to wrap up your cart\n\t\tNow please enter:	";
				cin >> nextproduct;
				if (nextproduct == 2)
				{
					string ser, quant;
					cout << "Enter the Serial No to be edited: ";
					cin.clear();
					cin.ignore();
					getline(cin, ser);
					cin.clear();
					cout << "Enter the new quantity:	";
					getline(cin, quant);
					EditCart(cstack,ser,quant);
					Print_Cart(cstack);
				}
				if (nextproduct == 3)
				{
					Print_Cart(cstack);
					break;
				}
		}
			CDetails(cstack, to_string(TotalBill));
	}

	
	void Print_Cart(stack<products*> p)
	{
	if(p.empty())
	{
		return;
	}

	cout << "\n\n=====================================================\tYour Cart\t=====================================================\n\n";

	cout << "\t\t\t\t\tSerial no\tName\t\tQuantity\tPrice\n";
		
	while (!p.empty())
	{
		if (p.top()->Serial.length() > 6)
		{
			cout << "\t\t\t\t\t" << p.top()->Serial << "\t";
		}

		else
		{
			cout << "\t\t\t\t\t" << p.top()->Serial << "\t\t";
		}

		if (p.top()->name.length() > 7)
		{
			cout << p.top()->name << "\t";
			cout << p.top()->Buyer_Quantity << "\t\t";
			cout << p.top()->price << "\n";
		}
		else
		{
			cout << p.top()->name << "\t\t";
			cout << p.top()->Buyer_Quantity << "\t\t";
			cout << p.top()->price << "\n";
		}
		p.pop();
	}
		cout<<"\n";
	}



	void EditCart(stack<products*> p,string serial,string quant)
	{
		products* newp=p.top();
		if (p.empty())
		{
			cout << "The Cart is empty!\n";
			return;
		}
		else
		{
			if (p.top()->Serial == serial)
			{
				
				float ppkg = stof(p.top()->price)/stof(p.top()->Buyer_Quantity);
				float price = ppkg* stof(quant);
				p.top()->Buyer_Quantity = quant;
				p.top()->price = to_string(price);
				newp= p.top();
				p.pop();
				p.push(newp);
				return;

				// float pri = stof(p.top()->price);
				// float bq = stof(p.top()->Buyer_Quantity);
				// float ppkg = pri / bq;
				// float price = ppkg * stof(quant);
				// p.top()->Buyer_Quantity = quant;
				// p.top()->price = to_string(price);
				// newp = p.top();
				// p.pop();
				// p.push(newp);
			}
			else
			{
				p.pop();
				EditCart(p, serial, quant);
				p.push(newp);
			}
		}
		
	}

	
	void CDetails(stack<products*> p, string bill)
	{
		cout << "\n\n\n=================================================\tCustomer Details\t================================================\n";
		cout << "\n\t\t\t\t\t\t\tName:		" << name;
		cout << "\n\t\t\t\t\t\t\tContact no:	" << contactno;
		cout << "\n\t\t\t\t\t\t\tCNIC:		" << cnic;
		cout << "\n\t\t\t\t\t\t\tTotal bill:	" << bill;
		cout << "\n\t\t\t\t\t\t\tAddress:	"<< address << "\n\n";
	}


};


class sales
{
public:
	sales(string cname, string ccont, string ccnic, string caddress, float ctotalbill, string emname, string emcontact, string emcnic, string emdetails)
	{
		fstream f;
		string alldata, data;
		f.open(filename_Sales,ios::app);
		alldata = cname + "," + ccont + "," + ccnic + "," + caddress + "," + to_string(ctotalbill) + "," + emname + "," + emcontact + emcnic + "," + emdetails + "\n";
		f << alldata;
		f.close();
	};

};



class employee
{
public:
	string name, contactno, details, cnic;
	queue<employee*> riders;
	employee() {};

	//I will be using a queue to maintaining the order of employees/riders.
	//So I will implement the cube in such a way that if one rider is on the ride then the next customer will be assigned the second rider,
	//the rider that is on the first position in the queue as the first one was on the ride then the second one will become on the first position
	//and will be assigned to the new customer and when one rider came back he will be added at the end of the queue.

	employee(string name, string contactno, string details, string cnic)
	{
		this->name = name;
		this->contactno = contactno;
		this->details = details;
		this->cnic = cnic;
	}

	void Employees()
	{
		fstream f;
		f.open(filename_employees, ios::in);
		while (f.good())
		{
			employee* e = new employee;
			getline(f, e->name, ',');
			getline(f, e->contactno, ',');
			getline(f, e->details, ',');
			getline(f, e->cnic, '\n');
			if (e->name != "" || e->contactno != "" || e->details != "" || e->cnic != "")
			{
				riders.push(e);
			}
		}
	}

	void Go_and_Deliver(customer c, stack<products*> p)
	{
		if (!p.empty())
		{
			string time = __TIME__;
			string hours = "", minute = "";
			int counter = 0;
			employee* e1 = riders.front();

			for (auto x : time)
			{
				if (x != ':')
				{
					if (counter <= 2)
						hours += x;
					else
						if (counter > 2 && counter <= 4)
							minute += x;
				}
				counter++;
			}



			
			if(riders.empty())
			{
				cout << "It's a busy day! Your order will be delivered on the specified address by today.\n";

				cout << "\n\n=====================================================\tHappy Shopping\t=====================================================\n";
				if ((stoi(hours) % 12 + 3) < 12)
				{
					cout << "\n\t\t\t\tDear " << c.name << " your order will be delivered to you by " << (stoi(hours) + 3) % 12 << ":" << minute << " pm";
				}
				else
				{
					cout << "\n\t\t\t\tDear " << c.name << " your order will be delivered to you by " << (stoi(hours) + 3) % 12 << ":" << minute << " am\n";
				}

				cout << "\n\t\t\t\tYou have to pay: Rs." << c.TotalBill << " to the rider after receiving your order.";
				cout << "\nThank you very much " << c.name << ". Take care!\n\n";
				
			}
			
			cout << "\n\n\n\n=====================================================\tRider details\t=====================================================\n\n";
			employee* em = riders.front();
			cout << "\t\t\t\t\t\t\tName:        " << (riders.front())->name << "\n";
			cout << "\t\t\t\t\t\t\tContact:     " << (riders.front())->contactno << "\n";
			cout << "\t\t\t\t\t\t\tDetails:     " << (riders.front())->details << "\n";
			cout << "\t\t\t\t\t\t\tTotal Bill:  " << (c.TotalBill) << "\n\n";
			riders.pop();
			riders.push(e1);

			cout << "\n\n=====================================================\tHappy Shopping\t=====================================================\n";
			if ((stoi(hours) % 12 + 3) < 12)
			{
				cout << "\n\t\t\t\tDear " << c.name << " your order will be delivered to you by " << (stoi(hours) + 3) % 12 << ":" << minute << " pm";
			}
			else
			{
				cout << "\n\t\t\t\tDear " << c.name << " your order will be delivered to you by " << (stoi(hours) + 3) % 12 << ":" << minute << " am\n";
			}
			
			cout << "\n\t\t\t\tYou have to pay: Rs." << c.TotalBill << " to the rider after receiving your order.";
			cout << "\nThanks you very much " << c.name << ". Take care!\n\n";
			sales s(c.name,c.contactno,c.cnic,c.address,c.TotalBill,em->name,em->contactno,em->cnic,em->details);
		}
		else
		{
			cout << "~~~~\tWe are sorry, No data found\t~~~~\n\n";
		}
	}

};

void ForCustomer()
{
	cin.clear();
	cin.ignore();
	customer c;
	employee e;
	e.Employees();
	e.Go_and_Deliver(c, c.cstack);
}

void ForEmployee()
{
	int i;
	products p;
	p.AllProducts();
	
	while (true)
	{
		cout << "Press 1): To add product.\n";
		cout << "Press 2): To delete product.\n";
		cout << "Press 3): To edit product details.\n";
		cout << "Press 4): To Exit.\n";
		cout << "Now enter your choice: "; cin >> i;
		float avl;
		switch (i)
		{
		case 1:
			cin.clear();
			cin.ignore();
			cout << "Enter Serial no of product: ";
			getline(cin, p.Serial);
			cin.clear();
			cout << "\t\tWhat is name of product: ";
			getline(cin, p.name);
			cin.clear();
			cout << "\t\tWhat is price of product: ";
			getline(cin, p.price);
			cin.clear();
			cout << "\t\tWhat is Available Quantity of product: ";
			cin >> avl;
			cin.clear();
			p.insert(p.Serial, p.name,avl, p.price);
			p.print2();
			break;

		case 2:
			cout << "In singly link list we can only delete items/nodes just like a queue\n";
			p.DEL();
			p.print2();
			break;

		case 3:
			cin.clear();
			cin.ignore();
			float q;
			cout << "Enter Serial no of product: ";
			getline(cin, p.Serial);
			cin.clear();
			cout << "What is Available Quantity of product: ";
			cin >> q;
			cin.clear();
			p.Edit(p.Serial,q);
			p.print2();
			break;

		case 4:
			cout << "Closing the App!............\n";
			p.FileWrite();
			break;
			
		default:
			break;
		}
		
		if(i==4)
		{
			break;
		}
	}

	
}
int main()
{
	int J;
	while (true)
	{
		system("COLOR F2");


		cout << char(178);
		for (int i = 0; i < 122; i++)
		{
			cout << char(178);
		}
		cout << char(178) << endl;
		cout << char(178);
		for (int i = 0; i < 51; i++) { cout << char(176); }
		cout << "   Grocer App 2.o   ";
		for (int i = 0; i < 51; i++) { cout << char(176); }cout << char(178) << endl;
		for (int i = 0; i < 122; i++)
			cout << char(178);
		cout << char(178);
		cout << char(178) << endl;





		//    I have to implement add employee, delete employee and add product, delete product.





		//cout << "\n*****************************************************\tGrocer App 2.o\t*****************************************************\n\n";
		cout << "\t\t\t\t\t\tProgrammed By:	RAFAY AAMIR GULL\n\n";
		cout << "\t\t\t\t\t\tList of data structures used: \n";
		cout << "\t\t\t\t\t\t(1)	Link List\n";
		cout << "\t\t\t\t\t\t(2)	Hash Table\n";
		cout << "\t\t\t\t\t\t(3)	Bloom Filter\n";
		cout << "\t\t\t\t\t\t(4)	Stack\n";
		cout << "\t\t\t\t\t\t(5)	Queue\n";
		cout << "\t\t\t\t\t\tNote:\tIt is a Front end application.\n";
		cout << "\n=============================================================================================================================\n";

		cout << "Press 1): If you are an employee of RAFAY!\n";
		cout << "Press 2): If you are a Customer of GrocerApp 2.o!\n";
		cout << "Press 3): To close the program/App!\n";
		cout << "Now enter your choice: "; cin >> J;
		switch (J)
		{
		case 1:
			ForEmployee();
			system("PAUSE");
			system("CLS");
			break;
		case 2:
			ForCustomer();
			system("PAUSE");
			system("CLS");
			break;
		case 3:
			cout << "Closing the App...................";
			system("PAUSE");
			system("CLS");
			break;

		default:
			break;
		}

		if (J == 3)
			break;

	}
	return 0;
}
