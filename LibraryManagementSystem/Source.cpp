#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int MAX_BOOKS = 10;
const int MAX_USERS = 10;
int TotalBooks = 0, TotalUsers = 0, TotalNumberOfBooksThatBorrowed = 0, TotalQuantity = 0;
struct Books
{
	int ID = 0;
	string Name;
	int Quantity = 0;
	int TotalBorrowed = 0;
};
struct Users
{
	int ID = 0;
	string Name;
	Books BorrowedBook[MAX_BOOKS];
	int NumberOfBorrowedBook = 0;
};
Books Book[MAX_BOOKS];
Users User[MAX_USERS];
void AddNewBook()
{
	if (TotalBooks == 10)
	{
		cout << "-------------------------------\n";
		cout << "You Can't Add More Books\n";
		cout << "-------------------------------\n";
		return;
	}
	cout << "	ID       : ";
	cin >> Book[TotalBooks].ID;
	cout << "	Name     : ";
	cin >> Book[TotalBooks].Name;
	int QuantityOfBook = 0;
	do
	{
		cout << "	Quantity : ";
		cin >> QuantityOfBook;
		if (QuantityOfBook < 0)
		{
			cout << "------------------------------------------\n";
			cout << "You Should Enter Positive Number. \n";
			cout << "------------------------------------------\n";
		}
	} while (QuantityOfBook < 0);
	Book[TotalBooks].Quantity = QuantityOfBook;
	TotalBooks++;
	TotalQuantity += QuantityOfBook;
	cout << "=============================================================\n";
}
void SearchBookByPrefix()
{
	if (TotalBooks == 0)
	{
		cout << "------------------------------------------------------\n";
		cout << "There Is No Books Available , Add Books And Come Back \n";
		cout << "------------------------------------------------------\n";
		return;
	}
	string Prefix = "";
	cout << "Enter The Name Of Prefix : ";
	cin >> Prefix;
	int LengthOfPrefix = size(Prefix), count = 0;
	bool TheSame = false;
	for (int Booki = 0; Booki < TotalBooks; Booki++)
	{
		TheSame = true;
		int LengthOfBook = size(Book[Booki].Name);
		if (LengthOfBook < LengthOfPrefix)
			continue;
		for (int pre = 0; pre < LengthOfPrefix; pre++)
		{
			if (Prefix[pre] != Book[Booki].Name[pre])
			{
				TheSame = false;
				break;
			}
		}
		if (TheSame == true)
		{
			count++;
			cout << Book[Booki].Name << "  -  ";
		}
	}
	if (count == 0)
	{
		cout << "-------------------------------------\n";
		cout << "There Is No Book With This Name.\n";
		cout << "-------------------------------------";
	}
	cout << "\n=============================================================\n";
}
void AddUser()
{
	if (TotalUsers == 10)
	{
		cout << "-------------------------------\n";
		cout << "You Can't Add More Users\n";
		cout << "-------------------------------\n";
		return;
	}
	cout << "	ID   : ";
	cin >> User[TotalUsers].ID;
	cout << "	Name : ";
	cin >> User[TotalUsers].Name;
	TotalUsers++;
	cout << "=============================================================\n";
}
int CheckIfUserIsFoundToBorrow(string UserName)
{
	for (int user = 0; user < TotalUsers; user++)
	{
		if (User[user].Name == UserName)
		{
			if (User[user].NumberOfBorrowedBook < 5) // Each User Can Borrow Only 5 Books
				return user;
			else
			{
				cout << "This User Borrowed [ 5 ] Books He Can't Borrow More Now. \n";
				cout << "---------------------------------------------------------\n";
				return -5;
			}
		}
	}
	return -1;
}
int CheckIfBookIsFoundToBorrow(string BookName)
{
	for (int book = 0; book < TotalBooks; book++)
	{
		if (Book[book].Name == BookName)
		{
			if (Book[book].Quantity > Book[book].TotalBorrowed)
				return book;
			else
			{
				cout << "The Quantity Of This Book Is [ Zero ]. \n";
				cout << "---------------------------------------\n";
				return -5;
			}
		}
	}
	return -1;
}
void BorrowThisBookToUser(int UserIndex, int BookIndex)
{
	User[UserIndex].BorrowedBook[User[UserIndex].NumberOfBorrowedBook] = Book[BookIndex];
	User[UserIndex].NumberOfBorrowedBook++;
	TotalNumberOfBooksThatBorrowed++;
	Book[BookIndex].TotalBorrowed++;
	//Book[BookIndex].Quantity--;
}
void UserBorrowBook()
{
	if (TotalUsers == 0)
	{
		cout << "------------------------------------------------------\n";
		cout << "There Is No Users Available , Add Users And Come Back \n";
		cout << "------------------------------------------------------\n";
		return;
	}
	if (TotalNumberOfBooksThatBorrowed == TotalQuantity)
	{
		cout << "------------------------------------------------------\n";
		cout << "There Is No Books Available , Add Books And Come Back \n";
		cout << "------------------------------------------------------\n";
		return;
	}
	string UserName, BookName;
	int UserIndex, BookIndex;
	do
	{
		cout << "Enter User Name : ";
		cin >> UserName;
		UserIndex = CheckIfUserIsFoundToBorrow(UserName);
		if (UserIndex == -5)
			return;
		cout << "Enter Book Name : ";
		cin >> BookName;
		BookIndex = CheckIfBookIsFoundToBorrow(BookName);
		if (BookIndex == -5)
			return;
		if (UserIndex != -1 && BookIndex != -1)
		{
			BorrowThisBookToUser(UserIndex, BookIndex);
		}
		else
		{
			cout << "---------------------------------------------------------------\n";
			cout << "This User Or Book Not Available Now , Enter The Correct Name.  \n";
			cout << "---------------------------------------------------------------\n";
		}
	} while (UserIndex == -1 || BookIndex == -1);
	cout << "Borrow Is Completed. \n";
	cout << "=============================================================\n";
}
int CheckIfUserIsFoundToReturn(string UserName)
{
	for (int user = 0; user < TotalUsers; user++)
	{
		if (User[user].Name == UserName)
		{
			return user;
		}
	}
	return -1;
}
int CheckIfBookIsFoundInBorrowedBookToReturn(int UserIndex, string BookName)
{
	for (int book = 0; book < User[UserIndex].NumberOfBorrowedBook; book++)
	{
		if (User[UserIndex].BorrowedBook[book].Name == BookName)
		{
			return book;
		}
	}
	return -1;
}
void ReturnThisBookToLibrary(int UserIndex, int BorrowedBookIndex)
{
	for (int BorrowedBook = BorrowedBookIndex; BorrowedBook < User[UserIndex].NumberOfBorrowedBook; BorrowedBook++)
	{
		User[UserIndex].BorrowedBook[BorrowedBook] = User[UserIndex].BorrowedBook[BorrowedBook + 1];
	}
	User[UserIndex].NumberOfBorrowedBook--;
	TotalNumberOfBooksThatBorrowed--;
}
void UserReturnBook()
{
	string UserName, BookName;
	int UserIndex, BorrowedBookIndex;
	do
	{
		cout << "Enter User Name : ";
		cin >> UserName;
		UserIndex = CheckIfUserIsFoundToReturn(UserName);
		cout << "Enter Book Name : ";
		cin >> BookName;
		BorrowedBookIndex = CheckIfBookIsFoundInBorrowedBookToReturn(UserIndex, BookName);
		if (UserIndex != -1 && BorrowedBookIndex != -1)
		{
			ReturnThisBookToLibrary(UserIndex, BorrowedBookIndex);
			for (int book = 0; book < TotalBooks; book++)
			{
				if (Book[book].Name == BookName)
				{
					//Book[book].Quantity++;
					Book[book].TotalBorrowed--;
				}
			}
		}
		else
		{
			cout << "---------------------------------------------------------------\n";
			cout << "The Name Of User Or Book Is Wrong , Enter It Again Correct \n";
			cout << "---------------------------------------------------------------\n";
		}
	} while (UserIndex == -1 || BorrowedBookIndex == -1);
	cout << "Return Book Is Completed\n";
	cout << "=============================================================\n";
}
void PrintUsers()
{
	if (TotalUsers == 0)
	{
		cout << "------------------------------------------------------\n";
		cout << "There Is No Users Available , Add Users And Come Back \n";
		cout << "------------------------------------------------------\n";
		return;
	}
	for (int user = 0; user < TotalUsers; user++)
	{
		cout << "User " << User[user].Name << " ID " << User[user].ID << " Borrowed Books IDS : ";
		for (int borrowedbook = 0; borrowedbook < User[user].NumberOfBorrowedBook; borrowedbook++)
		{
			cout << User[user].BorrowedBook[borrowedbook].ID << "  ";
		}
		cout << "\n";
	}
	cout << "=============================================================\n";
}
int CheckIfBookIsFound(string BookName)
{
	for (int book = 0; book < TotalBooks; book++)
	{
		if (Book[book].Name == BookName)
		{
			return book;
		}
	}
	return -1;
}
void GetUsersWhoBorrowedThisBook(int BookIndex)
{
	int Count = 0;
	for (int user = 0; user < TotalUsers; user++)
	{
		for (int borrowedbook = 0; borrowedbook < User[user].NumberOfBorrowedBook; borrowedbook++)
		{
			if (User[user].BorrowedBook[borrowedbook].Name == Book[BookIndex].Name)
			{
				Count++;
				cout << User[user].Name << "\n";
			}
		}
	}
	if (Count == 0)
	{
		cout << "----------------------------------\n";
		cout << "No One Borrowed This Book Before .\n";
		cout << "----------------------------------\n";
	}
}
void PrintWhoBorrowedBookByName()
{
	if (TotalUsers == 0)
	{
		cout << "------------------------------------------------------\n";
		cout << "There Is No Users Available , Add Users And Come Back \n";
		cout << "------------------------------------------------------\n";
		return;
	}
	string BookName;
	int BookIndex;
	do
	{
		cout << "Enter Book Name : ";
		cin >> BookName;
		BookIndex = CheckIfBookIsFound(BookName);
		if (BookIndex != -1)
		{
			GetUsersWhoBorrowedThisBook(BookIndex);
		}
		else
		{
			cout << "-------------------------------------------------\n";
			cout << "This Book Not Available , Enter The Correct Name \n";
			cout << "-------------------------------------------------\n";
		}
	} while (BookIndex == -1);
	cout << "========================================\n";
}
bool ComBookByID(Books& a, Books& b)
{
	return a.ID < b.ID;
}
bool ComBookByName(Books& a, Books& b)
{
	return a.Name < b.Name;
}
void PrintLibraryByID()
{
	cout << "\n";
	sort(Book, Book + TotalBooks, ComBookByID);
	for (int book = 0; book < TotalBooks; book++)
	{
		cout << "ID = " << Book[book].ID << "  " << "Name = " << Book[book].Name << "  ";
		cout << "TotalQuantity = " << Book[book].Quantity << "  " << "TotalBorrowed = " << Book[book].TotalBorrowed << "\n";
	}
	cout << "\n=================================================================================\n";
}
void PrintLibraryByName()
{
	cout << "\n";
	sort(Book, Book + TotalBooks, ComBookByName);
	for (int book = 0; book < TotalBooks; book++)
	{
		cout << "ID = " << Book[book].ID << "  " << "Name = " << Book[book].Name << "  ";
		cout << "TotalQuantity = " << Book[book].Quantity << "  " << "TotalBorrowed = " << Book[book].TotalBorrowed << "\n";
	}
	cout << "\n=================================================================================\n";
}
void MoveToYourFunction(int Choice)
{
	switch (Choice)
	{
	case 1: AddNewBook();break;
	case 2: SearchBookByPrefix();break;
	case 3: PrintWhoBorrowedBookByName();break;
	case 4: PrintLibraryByID();break;
	case 5: PrintLibraryByName();break;
	case 6: AddUser();break;
	case 7: UserBorrowBook();break;
	case 8: UserReturnBook();break;
	case 9: PrintUsers();break;
	default:
		return;
	}
}
void Menu()
{
	int Choice = 0;
	cout << "[1] Add Book                        \n";
	cout << "[2] Search Book By Prefix           \n";
	cout << "[3] Print Who Borrowed Book By Name \n";
	cout << "[4] Print Library By ID             \n";
	cout << "[5] Print Library By Name           \n";
	cout << "[6] Add User                        \n";
	cout << "[7] User Borrow Book                \n";
	cout << "[8] User Return Book                \n";
	cout << "[9] Print Users                     \n";
	cout << "[10] Exit                           \n";
	cout << "=================================== \n";
}
void Library()
{
	int Choice = 0;
	Menu();
	while (true)
	{
		do
		{
			cout << "Enter Your Choice [1 : 10] :   ";
			cin >> Choice;
			cout << "================================\n";
			if (Choice > 10 || Choice < 1)
			{
				cout << "----------------------------------------------- \n";
				cout << "Invalid Range , Please Enter The Correct Number \n";
				cout << "----------------------------------------------- \n";
			}
		} while (Choice > 10 || Choice < 1);
		if (Choice == 10)
		{
			cout << "-------------------------\n";
			cout << "This Program Is Finished.\n";
			cout << "-------------------------\n";
			return;
		}
		MoveToYourFunction(Choice);
	}
}
int main()
{
	Library();
	return 0;
}