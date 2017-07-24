#include<iostream>
#include<conio.h>
using namespace std;

int toIt=0; 
FILE *fp;

class product
{
	friend class admin;
	public:
		char name[100];
		int price, quantity, Id;
}pr[100];

class admin
{
	friend class customer;
	int ch, temp, ch1;
	public:
	void addItem()
	{
		cout<<"Enter number of items you want to add..."<<endl;
		cin>>temp;
		int i = toIt;
		toIt += temp;
		while(i != toIt)
		{
			system("cls");
			cout<<"For item "<<(i+1)<<endl;
			pr[i].Id = i;
			addAttributes(pr[i]);
			i++;			
		}
	}
	void addAttributes(product &p)
	{
		cout<<"Enter the name"<<endl;
		cin>>p.name;
		cout<<"Enter the price"<<endl;
		cin>>p.price;
		cout<<"Enter the quantity"<<endl;
		cin>>p.quantity;
	}
	void subMenu()
	{
		cout<<"1. Add item"<<endl<<"2. Edit Item"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:
				addItem();
				break;
			case 2:
				try
				{
					if(toIt == 0)
					{
						throw toIt;
					}
					else
					{
						editForm();			
					}
				}
				catch(int a)
				{
					cout<<"No items to edit"<<endl;
					getch();
				}
				break;	
		}
	}
	void editForm()
	{
		cout<<"Enter the item you want to edit..."<<endl;
		cout<<"S no Name Price Quantity"<<endl;
		for(int i=0; i<toIt; i++)
		{				
			printf("%4d ",i);
			cout<<pr[i].name;
			printf("%4d %3d \n", pr[i].price, pr[i].quantity);
		}
		cout<<"enter your choice..."<<endl;
		cin>>ch1;
		editItem(ch1);
	}
	void editItem(int ch)
	{
		int cho;
		cout<<"What do you want to edit..."<<endl<<"press..."<<endl;
		cout<<"1. Name"<<endl;
		cout<<"2. Quantity"<<endl;
		cout<<"3. Price"<<endl;
		cin>>cho;
		switch(cho)
		{
			case 1:
				cout<<"Enter new name"<<endl;
				cin>>pr[ch].name;
				break;
			case 2:
				cout<<"Enter new quantity"<<endl;
				cin>>pr[ch].quantity;
				break;	
			case 3:
				cout<<"Enter new price"<<endl;
				cin>>pr[ch].price;
				break;	
			default :
				cout<<"ERROR";
				break;	
		}		
	}
};

class customer
{
	public:
		int total, toSel;
		int qty;
		int ch, ch1;
		
		void displayChoice()
		{
			do
			{
				system("cls");
				cout<<"1. Display Menu"<<endl<<"2. You are done"<<endl<<"Total = "<<total<<endl;
				cin>>ch;
				switch(ch)
				{
					case 1:
						displayMenu();
						break;
					case 2:
						char c;
						FILE *fp1;
						fp1 = fopen("bill.txt","r");
						fscanf(fp1,"%c",&c);
						while(!feof(fp1))
						{
							cout<<c;
							fscanf(fp1,"%c",&c);
						}
						cout<<"TOTAL = "<<total<<endl;
						break;
					default :
						break;	
				}
			}while(ch!=2);
		}
		void displayMenu()
		{	
			system("cls");		
			cout<<"S no Name Price Quantity"<<endl;
			for(int i=0; i<toIt; i++)
			{				
				printf("%4d ",i);
				cout<<pr[i].name;
				printf("%4d %3d \n", pr[i].price, pr[i].quantity);
			}
			cout<<"enter your choice..."<<endl;
			cin>>ch1;
			getOrder(ch1);
		}
		void getOrder(int ch)
		{
			try
			{
				if(pr[ch].quantity == 0)
				{
					throw pr[ch].quantity;
				}
				else
				{
					do
					{	
						try
						{
							cout<<"enter the quantity..."<<endl;
							cin>>qty;
							if((qty>pr[ch].quantity))
							{
								throw qty;
							}
							else
							{
								toSel++;
								total = total + (pr[ch].price * qty);
								pr[ch].quantity -= qty; 
								fp=fopen("bill.txt","a");
								fprintf(fp,"%3d %s %5d %4d %3d\n",toSel,pr[ch].name,pr[ch].price, qty, (pr[ch].price * qty));	
								fclose(fp);
								break;
							}
						}
						catch(int q)
						{
							cout<<"Requested Quantity not avaliable"<<endl;
							getch();
						}
					}while(1);
				}
			}
			catch(int qa)
			{
				cout<<"we are out of stock"<<endl;
				getch();
			}
		}
};

class menu
{
	public:
		int choice;
		void getChoice()
		{
			do
			{
				system("cls");
				cout<<"enter your role"<<endl<<"1. Admin"<<endl<<"2. Customer"<<endl<<"3. End"<<endl;
				cin>>choice;
				switch(choice)
				{
					case 1:
						admin ad;
						ad.subMenu();
						break;
					case 2:
						customer c;
						fp = fopen("bill.txt","w");
						fprintf(fp,"Sno Name price quantity Total\n");
						fclose(fp);
						c.total = 0;
						c.toSel = 0;
						system("cls");
						c.displayChoice();
						getch();
						break;
					case 3:
						cout<<"Thank you!!"<<endl;
						break;	
					default:
						cout<<"Error"  ;							
				}
			}while(choice!=3); 
		}
};

main()
{
	menu m1;
	m1.getChoice();
}
