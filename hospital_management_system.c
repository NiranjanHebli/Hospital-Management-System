#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>

// Username: DefaultUser Password:0 Works

struct today
{

	char date[11];
} T;
struct UserDetails
{
	char password[50];
	char UserName[50];
	char Name[50];
};
struct DoctorDetails
{
	char Name[50];
	int IDnumber;
	int Age;
	char contactNo[11];
	int experience;
	char Date[11];
	char gender[2];
	char Address[500];
	char designation[40];
};
struct StaffDetails
{
	char Name[50];
	int Age;
	int experience;
	char Date[11];
	char gender[2];
	char Address[500];
	int IDnumber;
	double salary;
	char designation[40];
};
struct PatientDetails
{

	char diagnosis[250];
	int ID;
	char BloodGroup[4];
	char gender[2];
	int age;
	char history[250];
	char address[500];
	char Date[11];
	char DOB[11];
	char Name[150];
};
struct OrganBank
{
	char Name[50];
	char NameOfDonor[100];
	char BloodGroup[4];
	char Date[11];
};
struct BloodBank
{
	char Date[11];
	char NameOfDonor[100];
	char BloodGroup[4];
	int quantity;
};

void CreateUser();
void DeleteUser();
void AddPatient();
void FindPatient();
void UpdatePatient();
void DeletePatient();
void SortByNameP();
void AddStaff();
void FindStaff();
void UpdateStaff();
void DeleteStaff();
void AddDoctor();
void UpdateDoctor();
void FindDoctor();
void DeleteDoctor();
void UpdateAll();
void AddDonor();
void FindDonor();
void AddODonor();
void FindODonor();

int checkIDStaff(int ID)
{
	struct StaffDetails Mem;
	FILE *fp;
	fp = fopen("StaffDetails.dat", "rb");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again\n");
	else
	{
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
		{
			if (Mem.IDnumber == ID)
			{
				return 1;
			}
		}
		return 0;
	}
}
int checkID(int ID)
{
	struct PatientDetails pat;
	FILE *fp;
	fp = fopen("PatientDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again\n");
	else
	{
		while ((fread((char *)&pat, sizeof(pat), 1, fp)) == 1)
		{
			if (pat.ID == ID)
			{
				return 1;
			}
		}
		return 0;
	}
}
int isLeapYear(int yyyy)
{
	if (yyyy % 400 == 0)
		return 1;
	else if (yyyy % 100 == 0)
		return 0;
	else if (yyyy % 4 == 0)
		return 1;
	else
		return 0;
}
int checkDate(char Date[])
{
	if (Date[10] != '\0')
		return 0;
	if (Date[2] != '/' || Date[5] != '/')
		return 0;
	int dd = (Date[0] - '0') * 10 + (Date[1] - '0');
	int mm = (Date[3] - '0') * 10 + Date[4] - '0';
	int yyyy = (Date[6] - '0') * 1000 + (Date[7] - '0') * 100 + (Date[8] - '0') * 10 + (Date[9] - '0');
	// printf("%d/%d/%d",dd,mm,yyyy);
	if (dd > 31 || dd < 1)
		return 0;
	if (mm > 12 || mm < 0)
		return 0;
	if (yyyy > 2022 || yyyy < 1850)
		return 0;
	if (mm == 4 || mm == 6 || mm == 9 || mm == 11)
	{
		if (dd > 30)
			return 0;
	}
	if (isLeapYear(yyyy) && mm == 2 && dd == 29)
		return 1;
	if (!isLeapYear(yyyy) && mm == 2 && dd > 28)
		return 0;
	// Indexing
	// dd / mm / yyyy
	// 01 2 34 5 6789
	return 1;
}
int checkDOB(char DOB[])
{
	if (DOB[10] != '\0')
		return 0;
	if (DOB[2] != '/' || DOB[5] != '/')
		return 0;
	int dd = (DOB[0] - '0') * 10 + (DOB[1] - '0');
	int mm = (DOB[3] - '0') * 10 + DOB[4] - '0';
	int yyyy = (DOB[6] - '0') * 1000 + (DOB[7] - '0') * 100 + (DOB[8] - '0') * 10 + (DOB[9] - '0');
	// printf("%d/%d/%d",dd,mm,yyyy);
	int d = (T.date[0] - '0') * 10 + (T.date[1] - '0');
	int m = (T.date[3] - '0') * 10 + (T.date[4] - '0');
	int y = (T.date[6] - '0') * 1000 + (T.date[7] - '0') * 100 + (T.date[8] - '0') * 10 + (T.date[9] - '0');
	if (d < dd && m < mm && y < yyyy)
		return 0;
	if (dd > 31 || dd < 1)
		return 0;
	if (mm > 12 || mm < 0)
		return 0;
	if (yyyy > 2022 || yyyy < 1850)
		return 0;
	if (mm == 4 || mm == 6 || mm == 9 || mm == 11)
	{
		if (dd > 30)
			return 0;
	}
	if (isLeapYear(yyyy) && mm == 2 && dd == 29)
		return 1;
	if (!isLeapYear(yyyy) && mm == 2 && dd > 28)
		return 0;
	// Indexing
	// dd / mm / yyyy
	// 01 2 34 5 6789
	return 1;
}
int getAge(char DOB[])
{
	// converting from string to integer
	int dd = (DOB[0] - '0') * 10 + (DOB[1] - '0');
	int mm = (DOB[3] - '0') * 10 + DOB[4] - '0';
	int yyyy = (DOB[6] - '0') * 1000 + (DOB[7] - '0') * 100 + (DOB[8] - '0') * 10 + (DOB[9] - '0');
	// t for today
	int tday = (T.date[0] - '0') * 10 + (T.date[1] - '0');
	int tmonth = (T.date[3] - '0') * 10 + T.date[4] - '0';
	int tyear = (T.date[6] - '0') * 1000 + (T.date[7] - '0') * 100 + (T.date[8] - '0') * 10 + (T.date[9] - '0');

	int age = tyear - yyyy;
	if (mm > tmonth)
		age--;
	else if (tmonth == mm)
	{
		if (tday < dd)
			age--;
	}
	// printf("This is executed\n\n");

	return age;
}
int checkBloodGroup(char s[])
{
	if (strcmp(s, "NA") == 0 || strcmp(s, "A+") == 0 || strcmp(s, "A-") == 0 || strcmp(s, "B+") == 0 || strcmp(s, "B-") == 0 || strcmp(s, "AB+") == 0 || strcmp(s, "AB-") == 0 || strcmp(s, "O+") == 0 || strcmp(s, "O-") == 0)
		return 1;
	else
		return 0;
}
int checkPassword(char Password[])
{
	int sym = 0, num = 0, lalpha = 0, ualpha = 0;
	for (int i = 0; Password[i] != '\0'; i++)
	{
		if (Password[i] >= 'A' && Password[i] <= 'Z')
			ualpha++;
		else if (Password[i] >= 'a' && Password[i] <= 'z')
			lalpha++;
		else if (Password[i] >= '0' && Password[i] <= '9')
			num++;
		else if ((Password[i] >= '!' && Password[i] <= '/') || (Password[i] >= ':' && Password[i] <= '@') || (Password[i] >= '[' && Password[i] <= '`') || (Password[i] >= '{' && Password[i] <= '~'))
		{
			sym++;
		}
		else if (Password[i] == ' ')
			return 2;
	}
	if (num > 0 && ualpha > 0 && lalpha > 0 && sym > 0)
		return 1;
	else
		return 0;
}
int checkChoice(int C)
{
	if (C < 1 || C > 8)
		return 0;
	return 1;
}
int checkGender(char G[]){
	// printf("%s\n",G);
	if(G[0]!='M'&&G[0]!='F'&&G[0]!='O') return 0;
	if(G[1]!='\0') return 0;
	return 1;
}
int checkChoiceS(int C){
		if (C < 1 || C > 6)
		return 0;
	return 1;
}
int checkChoiceD(int C){
			if (C < 1 || C > 4)
		return 0;
	return 1;
}

void CreateUser()
{
	struct UserDetails User;
	FILE *fp;
	fp = fopen("UserDetails.dat", "a");
	if (fp == NULL)
	{
		printf("File Creation Failed!\n");
	}
	printf("Enter the Name : ");
	getchar();
	gets(User.Name);
	printf("Enter Username: ");

	gets(User.UserName);
PASS:
	printf("Enter Password: ");
	gets(User.password);
	printf("%s\n%s\n%s\n", User.password, User.Name, User.UserName);
	if (!checkPassword(User.password))
	{
		printf("Error! The PassWord is too weak ,should contain atleast 1 integer,1 Uppercase,1 Lowercase and 1 Special character\n");
		goto PASS;
	}
	else if (checkPassword(User.password) == 2)
	{
		printf("Error!Password cannot contain any blankspaces and tabs\n");
		goto PASS;
	}

	fwrite((char *)&User, sizeof(User), 1, fp);
	// printf("%s\n%s\n%s\n", User.password, User.Name, User.UserName);

	printf("User Added!\n");
	printf("Press any other key to continue...");
	getchar();
	fclose(fp);
}
void DeleteUser()
{
	char Password[50], Username[50];
	int ch = 0;
	struct UserDetails user;
	FILE *fp, *ft;
	fp = fopen("UserDetails.dat", "rb");
	ft = fopen("Temp.dat", "wb");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		getchar();
		// ViewAllPatients();
		printf("\nEnter the UserName : ");
		gets(Username);
		// getchar();
		while ((fread((char *)&user, sizeof(user), 1, fp)) == 1)
		{
			if (strcmp(Username, user.UserName) == 0)
			{
				ch = 1;
			}
		}

		if (ch == 1)
		{
			rewind(fp);
			printf("\nEnter the Password : ");
			gets(Password);
			while ((fread((char *)&user, sizeof(user), 1, fp)) == 1)
			{
				if (strcmp(Password, user.password) == 0)
				{
					ch = 1;
				}
			}
			rewind(fp);
			if (ch == 1)
			{
				while ((fread((char *)&user, sizeof(user), 1, fp)) == 1)
				{
					if (strcmp(Username, user.UserName) != 0)
					{
						fwrite((char *)&user, sizeof(user), 1, ft);
					}
				}
				printf("\nUser Removed\n");
				printf("Press any other key to continue...\n");
				getchar();
				fclose(fp);
				fclose(ft);
				remove("UserDetails.dat");
				rename("Temp.dat", "UserDetails.dat");
				system("clear");
			}
			else
			{
				printf("Error!Wrong password!\n");
				printf("Press any other key to continue...\n");
				getchar();
				fclose(fp);
				fclose(ft);
				remove("Temp.dat");
				system("clear");
			}
		}
		else
		{
			printf("UserName was not found!\n");

			printf("Press any other key to continue...\n");
			getchar();
			fclose(fp);
			fclose(ft);
			remove("Temp.dat");
			system("clear");
		}
	}
}

void DisplayDoctors(FILE *fp)
{

	getchar();
	int nofrec = 0;
	struct DoctorDetails Doc;
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Doc, sizeof(Doc), 1, fp)) == 1)
		{
			nofrec++;
			printf("\nDate Of Joining: %s", Doc.Date);
			printf("\nID Number : %d", Doc.IDnumber);
			printf("\nDesignation:%s", Doc.designation);
			printf("\nName : %s", Doc.Name);
			printf("\nExperience:%d", Doc.experience);
			printf("\nAge : %d", Doc.Age);
			printf("\nGender : %s", Doc.gender);
			printf("\nAddress:%s", Doc.Address);
			printf("\n");
			printf("\n\n");
		}
		printf("Total number of records present are : %d\n", nofrec);
		printf("Please any key to continue...\n");
		getchar();
		system("clear");
	}
}
void AddDoctor()
{
	int N;
	struct DoctorDetails Doc;
	FILE *fp;
	fp = fopen("DoctorDetails.dat", "a");
	if (fp == NULL)
	{
		printf("File Creation Failed!\n");
	}
	printf("Enter the No of Members : ");
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		printf("Enter ID No:");
		scanf("%d",&Doc.IDnumber);
		printf("Enter Name: ");
		char ch;
		if (ch = getchar() == '\n')
			;
		gets(Doc.Name);
		printf("Enter Designation:");

		gets(Doc.designation);
		printf("Enter Gender :");
		scanf("%s", &Doc.gender);

	DATE:
		printf("Enter Date Of Joining(Enter in the format of dd/mm/yyyy):");
		scanf("%s", &Doc.Date);
		if (!checkDate(Doc.Date))
		{
			printf("Error!Please Enter in the format of dd/mm/yyyy or try again!\n");
			goto DATE;
		}
		printf("Enter Age:");
		scanf("%d", &Doc.Age);
		getchar();
		printf("Enter the Staff members Home address:");
		gets(Doc.Address);
		Doc.experience = getAge(Doc.Date); /// works perfectly
		// getchar();
		fwrite((char *)&Doc, sizeof(Doc), 1, fp);
		printf("record saved successfully!\n");
		printf("Press any other key to continue...");
	}

	getchar();
	system("clear");

	fclose(fp);
}
void FindDoctor()
{
	int c = 1, X;
	char sname[150];
	struct DoctorDetails Doc;
	FILE *fp;
	fp = fopen("DoctorDetails.dat", "rb");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again\n");
	else
	{
		// printf("\n1.Search by Name\n2.Search by IDNO.\n Enter choice : ");
		// scanf("%d", &c);
		// getchar();

		switch (c)
		{
		case 1:
			printf("Enter the Doctor's Name to Search : ");
			// scanf("%s",sname);
			gets(sname);
			int flag1 = 1;
			while ((fread((char *)&Doc, sizeof(Doc), 1, fp)) == 1)
			{
				if (strcmp(sname, Doc.Name) == 0)
				{
					flag1 = 0;
					printf("\nDate Of Joining: %s", Doc.Date);
					printf("\nDesignation:%s", Doc.designation);
					printf("\nName : %s", Doc.Name);
					printf("\nExperience:%d", Doc.experience);
					printf("\nAge : %d", Doc.Age);
					printf("\nGender : %s", Doc.gender);
					printf("\nAddress:%s", Doc.Address);
					printf("\n");
					printf("Press any other key to continue...\n");
					getchar();
					system("clear");
				}
			}
			if (flag1)
			{
				printf("Doctor with such name doesnt exist!\n");
				printf("Press any other key to continue...\n");
				getchar();
				system("clear");
			}
			break;
		}
	}
}
void DeleteDoctor()
{
	getchar();
	int recno;
	int ch;
	struct DoctorDetails Mem;
	FILE *fp, *ft;
	fp = fopen("DoctorDetails.dat", "rb");
	ft = fopen("TempD.dat", "wb");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		// ViewAllPatients();
		printf("\nEnter the Staff Members's ID Number to delete : ");
		scanf("%d", &recno);
		getchar();
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
		{
			if (Mem.IDnumber == recno)
			{
				printf("\nDate Of Joining: %s", Mem.Date);
				printf("\nDesignation:%s", Mem.designation);
				printf("\nName : %s", Mem.Name);
				printf("\nExperience:%d", Mem.experience);
				printf("\nAge : %d", Mem.Age);
				printf("\nGender : %s", Mem.gender);
				printf("\nAddress:%s", Mem.Address);
				printf("\n");
				printf("Do you want to delete this record : ? (1.Y/2.N)\n");
				scanf("%d", &ch);
				getchar();
			}
		}
		if (ch == 1)
		{
			rewind(fp);
			while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
			{
				if (recno != Mem.IDnumber)
				{
					fwrite((char *)&Mem, sizeof(Mem), 1, ft);
				}
			}
			printf("\nRecord Deleted\n");
			printf("Press any other key to continue...\n");
			getchar();
			fclose(fp);
			fclose(ft);
			remove("DocterDetails.dat");
			rename("TempD.dat", "DocterDetails.dat");
			system("clear");
		}
		else
		{
			printf("No Record was deleted\n");

			printf("Press any other key to continue...\n");
			getchar();
			fclose(fp);
			fclose(ft);
			remove("TempD.dat");
			system("clear");
		}
	}
}
void UpdateDoctor()
{
	getchar();
	int recno, nofrec = 0;
	int ch;
	struct DoctorDetails Doc;
	FILE *fp;
	fp = fopen("DoctorDetails.dat", "rb+");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		printf("\nEnter the Docter's id Number to modify : ");
		scanf("%d", &recno);
		getchar();
		while ((fread((char *)&Doc, sizeof(Doc), 1, fp)) == 1)
		{
			nofrec++;
			if (Doc.IDnumber == recno)
			{
				printf("\nDate Of Joining: %s", Doc.Date);
				printf("\nDesignation:%s", Doc.designation);
				printf("\nName : %s", Doc.Name);
				printf("\nExperience:%d", Doc.experience);
				printf("\nAge : %d", Doc.Age);
				printf("\nGender : %s", Doc.gender);
				printf("\nAddress:%s", Doc.Address);
				printf("\n");
				printf("Do you want to modify this record : ? (1.Y/2.N)\n");
				scanf("%d", &ch);
				getchar();
				fseek(fp, ((nofrec - 1) * sizeof(Doc)), 0);
				if (ch == 1)
				{
				ID:
					printf("Enter the Doctor's Id NUmber: ");
					scanf("%d", &Doc.IDnumber);
					if (checkID(Doc.IDnumber))
					{
						printf("Error!Report with such ID number exist!\n");
						getchar();
						goto ID;
					}
					printf("Enter Name: ");
					char ch;
					getchar();
					gets(Doc.Name);
					printf("Enter Gender :");
					scanf("%s", &Doc.gender);

				DATE:
					printf("Enter Date Of Joining(Enter in the format of dd/mm/yyyy):\n");
					scanf("%s", &Doc.Date);
					if (!checkDate(Doc.Date))
					{
						printf("Error!Please Enter in the format of dd/mm/yyyy or try again!\n");
						goto DATE;
					}
					printf("Enter Age:");
					scanf("%d", &Doc.Age);
					getchar();
					printf("Enter the Docter's Home address:\n");
					gets(Doc.Address);
					Doc.experience = getAge(Doc.Date);
					getchar();
					printf("Enter Designation:\n");
					gets(Doc.designation);
					fwrite((char *)&Doc, sizeof(Doc), 1, fp);
					printf("Record Modified\n");
					printf("Please any key to continue...\n");
					getchar();
				}
				else
				{
					printf("No modifications were made\n");
					printf("Please any key to continue...\n");
					getchar();
				}
				fclose(fp);
			}
		}
	}
}
void ViewSortedDoctor()
{
	getchar();
	FILE *fp;
	fp = fopen("DoctorDetailsSorted.dat", "r");
	DisplayDoctors(fp);
	fclose(fp);
}
void ViewAllDoctors()
{

	getchar();
	FILE *fp;
	fp = fopen("DoctorDetails.dat", "r");
	DisplayDoctors(fp);
	fclose(fp);
}

void DisplayStaff(FILE *fp)
{

	int nofrec = 0;
	struct StaffDetails Mem;
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
		{
			nofrec++;
			printf("\nDate Of Joining: %s", Mem.Date);
			printf("\nID Number : %d", Mem.IDnumber);
			printf("\nDesignation:%s", Mem.designation);
			printf("\nName : %s", Mem.Name);
			printf("\nExperience:%d", Mem.experience);
			printf("\nAge : %d", Mem.Age);
			printf("\nGender : %s", Mem.gender);
			printf("\nSalary:%lf", Mem.salary);
			printf("\nAddress:%s", Mem.Address);
			printf("\n");
			printf("\n\n");
		}
		printf("Total number of records present are : %d\n", nofrec);
		printf("Please any key to continue...\n");
		getchar();
		system("clear");
	}
}
void ViewAllStaff()
{

	getchar();
	FILE *fp;
	fp = fopen("StaffDetails.dat", "r");
	DisplayStaff(fp);
	fclose(fp);
}
void AddStaff()
{
	int N;
	struct StaffDetails newStaff;
	FILE *fp;
	fp = fopen("StaffDetails.dat", "a");
	if (fp == NULL)
	{
		printf("File Creation Failed!\n");
	}
	printf("Enter the No of Members : ");
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
	ID:
		printf("Enter the Staff Id NUmber: ");
		scanf("%d", &newStaff.IDnumber);
		printf("Enter the Salary:");
		scanf("%lf", &newStaff.salary);
		if (checkIDStaff(newStaff.IDnumber))
		{
			printf("Error!Report with such ID number exist!\n");
			printf("Press any other key to continue...\n");
			getchar();
			goto ID;
		}
		printf("Enter Name: ");
		char ch;
		if (ch = getchar() == '\n')
			;
		gets(newStaff.Name);
		printf("Enter Designation:");

		gets(newStaff.designation);
		printf("Enter Gender :");
		scanf("%s", &newStaff.gender);

	DATE:
		printf("Enter Date Of Joining(Enter in the format of dd/mm/yyyy):");
		scanf("%s", &newStaff.Date);
		if (!checkDate(newStaff.Date))
		{
			printf("Error!Please Enter in the format of dd/mm/yyyy or try again!\n");
			goto DATE;
		}
		printf("Enter Age:");
		scanf("%d", &newStaff.Age);
		getchar();
		// getchar();
		printf("Enter the Staff members Home address:");
		gets(newStaff.Address);
		newStaff.experience = getAge(newStaff.Date); /// works perfectly
		// getchar();
		fwrite((char *)&newStaff, sizeof(newStaff), 1, fp);
		printf("record saved successfully!\n");
		printf("Press any other key to continue...");
	}

	getchar();
	system("clear");

	fclose(fp);
}
void FindStaff()
{
	int c, X;
	char sname[150];
	struct StaffDetails Mem;
	FILE *fp;
	fp = fopen("StaffDetails.dat", "rb");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again\n");
	else
	{
		printf("\n1.Search by Name\n2.Search by IDNO.\n Enter choice : ");
		scanf("%d", &c);
		getchar();
		switch (c)
		{
		case 1:
			printf("Enter the patient Name to Search : ");
			// scanf("%s",sname);
			gets(sname);
			int flag1 = 1;
			while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
			{
				if (strcmp(sname, Mem.Name) == 0)
				{
					flag1 = 0;
					printf("\nDate Of Joining: %s", Mem.Date);
					printf("\nID Number : %d", Mem.IDnumber);
					printf("\nDesignation:%s", Mem.designation);
					printf("\nName : %s", Mem.Name);
					printf("\nExperience:%d", Mem.experience);
					printf("\nAge : %d", Mem.Age);
					printf("\nGender : %s", Mem.gender);
					printf("\nSalary:%lf", Mem.salary);
					printf("\nAddress:%s", Mem.Address);
					printf("\n");
					printf("Press any other key to continue...\n");
					getchar();
					system("clear");
				}
			}
			if (flag1)
			{
				printf("Staff Member with such name doesnt exist!\n");
				printf("Press any other key to continue...\n");
				getchar();
				system("clear");
			}
			break;
		case 2:
			printf("Enter the Staff Members's ID Number to Search : ");
			scanf("%d", &X);
			// getchar();
			int flag2 = 1;
			while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
			{
				if (Mem.IDnumber == X)
				{
					flag2 = 0;
					printf("\nDate Of Joining: %s", Mem.Date);
					printf("\nID Number : %d", Mem.IDnumber);
					printf("\nDesignation:%s", Mem.designation);
					printf("\nName : %s", Mem.Name);
					printf("\nExperience:%d", Mem.experience);
					printf("\nAge : %d", Mem.Age);
					printf("\nGender : %s", Mem.gender);
					printf("\nSalary:%lf", Mem.salary);
					printf("\nAddress:%s", Mem.Address);
					printf("\n");
					printf("Press any other key to continue...\n");
					getchar();
					system("clear");
				}
			}
			if (flag2)
			{
				printf("Staff Member with such ID Number doesn't exist!\n");
				printf("Press any other key to continue...\n");
				getchar();
				getchar();
				system("clear");
			}
			break;
		}
	}
}
void UpdateStaff()
{
	getchar();
	int recno, nofrec = 0;
	int ch;
	struct StaffDetails Mem;
	FILE *fp;
	fp = fopen("StaffDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		// ViewAllPatients();
		printf("\nEnter the patient id Number to modify : ");
		scanf("%d", &recno);
		getchar();
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
		{
			printf("%d\n",Mem.IDnumber);
			nofrec++;
			if (Mem.IDnumber == recno)
			{
				printf("\nDate Of Joining: %s", Mem.Date);
				printf("\nID Number : %d", Mem.IDnumber);
				printf("\nDesignation:%s", Mem.designation);
				printf("\nName : %s", Mem.Name);
				printf("\nExperience:%d", Mem.experience);
				printf("\nAge : %d", Mem.Age);
				printf("\nGender : %s", Mem.gender);
				printf("\nSalary:%lf", Mem.salary);
				printf("\nAddress:%s", Mem.Address);
				printf("\n");
				printf("Do you want to modify this record : ? (1.Y/2.N)\n");
				scanf("%d", &ch);
				getchar();
				fseek(fp, ((nofrec - 1) * sizeof(Mem)), 0);
				if (ch == 1)
				{
				ID:
					printf("Enter the Staff Id NUmber: ");
					scanf("%d", &Mem.IDnumber);
					if (checkID(Mem.IDnumber))
					{
						printf("Error!Report with such ID number exist!\n");
						getchar();
						goto ID;
					}
					printf("Enter Name: ");
					char ch;
					getchar();
					gets(Mem.Name);
					printf("Enter Gender :");
					scanf("%s", &Mem.gender);

				DATE:
					printf("Enter Date Of Joining(Enter in the format of dd/mm/yyyy):\n");
					scanf("%s", &Mem.Date);
					if (!checkDate(Mem.Date))
					{
						printf("Error!Please Enter in the format of dd/mm/yyyy or try again!\n");
						goto DATE;
					}
					printf("Enter Age:");
					scanf("%d", &Mem.Age);
					getchar();
					printf("Enter the Staff members Home address:\n");
					gets(Mem.Address);
					Mem.experience = getAge(Mem.Date);
					getchar();
					printf("Enter Designation:\n");
					gets(Mem.designation);
					printf("Enter the Salary:\n");
					scanf("%lf", Mem.salary);

					fwrite((char *)&Mem, sizeof(Mem), 1, fp);
					printf("Record Modified\n");
					printf("Please any key to continue...\n");
					getchar();
				}
				else
				{
					printf("No modifications were made\n");
					printf("Please any key to continue...\n");
					getchar();
				}
				fclose(fp);
			}
		}
	}
}
void DeleteStaff()
{

	getchar();
	int recno;
	int ch;
	struct StaffDetails Mem;
	FILE *fp, *ft;
	fp = fopen("StaffDetails.dat", "r");
	ft = fopen("TempS.dat", "w");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		// ViewAllPatients();
		printf("\nEnter the Staff Members's ID Number to delete : ");
		scanf("%d",&recno);
		getchar();
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
		{
			// printf("%d\n",Mem.IDnumber);
			if (Mem.IDnumber == recno)
			{
				printf("\nDate Of Joining: %s", Mem.Date);
				printf("\nID Number : %d", Mem.IDnumber);
				printf("\nDesignation:%s", Mem.designation);
				printf("\nName : %s", Mem.Name);
				printf("\nExperience:%d", Mem.experience);
				printf("\nAge : %d", Mem.Age);
				printf("\nGender : %s", Mem.gender);
				printf("\nSalary:%lf", Mem.salary);
				printf("\nAddress:%s", Mem.Address);
				printf("\n");
				printf("Do you want to delete this record : ? (1.Y/2.N)\n");
				scanf("%d", &ch);
				getchar();
			}
		}
		if (ch == 1)
		{
			rewind(fp);
			while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
			{
				if (recno != Mem.IDnumber)
				{
					fwrite((char *)&Mem, sizeof(Mem), 1, ft);
				}
			}
			printf("\nRecord Deleted\n");
			printf("Press any other key to continue...\n");
			getchar();
			fclose(fp);
			fclose(ft);
			remove("StaffDetails.dat");
			rename("TempS.dat", "StaffDetails.dat");
			system("clear");
		}
		else
		{
			printf("No Record was deleted\n");

			printf("Press any other key to continue...\n");
			getchar();
			fclose(fp);
			fclose(ft);
			remove("TempS.dat");
			system("clear");
		}
	}
}
void ViewSortedStaff()
{
	getchar();
	FILE *fp;
	fp = fopen("StaffDetailsSorted.dat", "r");
	DisplayStaff(fp);
	fclose(fp);
}

// Sort Patient Details wrt IDNUMBER
void mergeP(struct PatientDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct PatientDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].ID <= R[j].ID)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortP(struct PatientDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortP(arr, l, m);
		mergeSortP(arr, m + 1, r);

		mergeP(arr, l, m, r);
	}
}

// Sort Staff wrt ID
void mergeS(struct StaffDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct StaffDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].IDnumber <= R[j].IDnumber)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortS(struct StaffDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortS(arr, l, m);
		mergeSortS(arr, m + 1, r);

		mergeS(arr, l, m, r);
	}
}

// Sort Doctor wrt experience
void mergeD(struct DoctorDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct DoctorDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].experience <= R[j].experience)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortD(struct DoctorDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortD(arr, l, m);
		mergeSortD(arr, m + 1, r);

		mergeD(arr, l, m, r);
	}
}

// Sort Patient details wrt Age simeple and reversed
void mergePAge(struct PatientDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct PatientDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].age <= R[j].age)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortPAge(struct PatientDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortPAge(arr, l, m);
		mergeSortPAge(arr, m + 1, r);

		mergePAge(arr, l, m, r);
	}
}
void mergePAgeR(struct PatientDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct PatientDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].age >= R[j].age)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortPAgeR(struct PatientDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortPAgeR(arr, l, m);
		mergeSortPAgeR(arr, m + 1, r);

		mergePAgeR(arr, l, m, r);
	}
}

// Sort Staff details wrt Age simple and reversed
void mergeSAge(struct StaffDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct StaffDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].Age <= R[j].Age)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortSAge(struct StaffDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortSAge(arr, l, m);
		mergeSortSAge(arr, m + 1, r);

		mergeSAge(arr, l, m, r);
	}
}
void mergeSAgeR(struct StaffDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct StaffDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].Age >= R[j].Age)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortSAgeR(struct StaffDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortSAgeR(arr, l, m);
		mergeSortSAgeR(arr, m + 1, r);

		mergeSAgeR(arr, l, m, r);
	}
}

// Reverse Sort Patient(wrt ID)
void mergePR(struct PatientDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct PatientDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].ID >= R[j].ID)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortPR(struct PatientDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortPR(arr, l, m);
		mergeSortPR(arr, m + 1, r);

		mergePR(arr, l, m, r);
	}
}

// Reverse Sort Staff(wrt ID)
void mergeSR(struct StaffDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct StaffDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].IDnumber >= R[j].IDnumber)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortSR(struct StaffDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortSR(arr, l, m);
		mergeSortSR(arr, m + 1, r);

		mergeSR(arr, l, m, r);
	}
}

// Reverse Sort Doctors(wrt Experience)
void mergeDR(struct DoctorDetails arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	struct DoctorDetails L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].experience >= R[j].experience)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortDR(struct DoctorDetails arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		mergeSortDR(arr, l, m);
		mergeSortDR(arr, m + 1, r);

		mergeDR(arr, l, m, r);
	}
}

// Sort Patient,Doctor and Staff Details wrt Name
void SortByNameP(struct PatientDetails arr[], int nofrec)
{
	struct PatientDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].Name, arr[j].Name) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}
void SortByNameD(struct DoctorDetails arr[], int nofrec)
{
	struct DoctorDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].Name, arr[j].Name) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}
void SortByNameS(struct StaffDetails arr[], int nofrec)
{
	struct StaffDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].Name, arr[j].Name) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}

// Sort Patients wrt BloodGroup simple and reversed
void SortByNamePB(struct PatientDetails arr[], int nofrec)
{
	struct PatientDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].BloodGroup, arr[j].BloodGroup) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}
void SortByNamePBR(struct PatientDetails arr[],int nofrec){
	struct PatientDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].BloodGroup, arr[j].BloodGroup) < 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}

// Sort Patient,Doctor and Staff Details wrt Name (reversed)
void SortByNamePR(struct PatientDetails arr[], int nofrec)
{
	struct PatientDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].Name, arr[j].Name) < 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}
void SortByNameDR(struct DoctorDetails arr[], int nofrec)
{
	struct DoctorDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].Name, arr[j].Name) < 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}
void SortByNameSR(struct StaffDetails arr[], int nofrec)
{
	struct StaffDetails temp;
	for (int i = 0; i <= nofrec; i++)
		for (int j = i + 1; j <= nofrec; j++)
		{
			if (strcmp(arr[i].Name, arr[j].Name) < 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
}


void SortPatients(int C)
{
	getchar();
	struct PatientDetails Patient;
	FILE *fp;
	int i = 0;
	int nofrec = 0;
	struct PatientDetails *arr = (struct PatientDetails *)malloc(sizeof(struct PatientDetails) * 1000);
	fp = fopen("PatientDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Patient, sizeof(Patient), 1, fp)) == 1)
		{
			nofrec++;
			arr[i] = Patient;
			i++;
		}
		// printf("Total number of records present are : %d\n", nofrec);
		if (C == 1)
			mergeSortP(arr, 0, nofrec - 1);
		else if (C == 2)
			mergeSortPR(arr, 0, nofrec - 1);
		else if(C==3)
			SortByNameP(arr, nofrec - 1);
		else if(C==4)
		SortByNamePR(arr,nofrec-1);
	    else if(C==5) 
		SortByNamePB(arr,nofrec-1);
		else if(C==6)
		SortByNamePBR(arr,nofrec-1);
		else if(C==7)
		mergeSortPAge(arr,0,nofrec-1);
		else 
		mergeSortPAgeR(arr,0,nofrec-1);

		remove("PatientDetailsSorted.dat");
		FILE *sf = NULL;
		sf = fopen("PatientDetailsSorted.dat", "a");
		if (sf == NULL)
		{
			printf("File Creation Failed!\n");
		}
		i = 0;
		while (nofrec--)
		{
			fwrite((char *)(arr + i), sizeof(arr[i]), 1, sf);
			i++;
		}
		fclose(sf);
	}
}
void SortDoctors(int C)
{

	getchar();
	struct DoctorDetails Mem;
	FILE *fp;
	int i = 0, nofrec = 0;
	struct DoctorDetails *arr = (struct DoctorDetails *)malloc(sizeof(struct DoctorDetails) * 1000);
	fp = fopen("DoctorDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
		{
			nofrec++;
			arr[i] = Mem;
			i++;
		}
		printf("Total number of records present are : %d\n", nofrec);
		if (C == 1)
			mergeSortD(arr, 0, nofrec - 1);
		else if (C == 2)
			mergeSortDR(arr, 0, nofrec - 1);
		else if(C==3)
			SortByNameD(arr, nofrec - 1);
	    else 
		    SortByNameDR(arr,nofrec-1);
	
		remove("DoctorDetailsSorted.dat");
		FILE *sf = NULL;
		sf = fopen("DoctorDetailsSorted.dat", "a");
		if (sf == NULL)
		{
			printf("File Creation Failed!\n");
		}
		i = 0;
		while (nofrec--)
		{
			fwrite((char *)(arr + i), sizeof(arr[i]), 1, sf);
			i++;
		}
		fclose(sf);
	}
}

void SortStaff(int C)
{

	getchar();
	struct StaffDetails Mem;
	FILE *fp;
	int i = 0, nofrec = 0;
	struct StaffDetails *arr = (struct StaffDetails *)malloc(sizeof(struct StaffDetails) * 1000);
	fp = fopen("StaffDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp)) == 1)
		{
			nofrec++;
			arr[i] = Mem;
			i++;
		}
		printf("Total number of records present are : %d\n", nofrec);
		if (C == 1)
			mergeSortS(arr, 0, nofrec - 1);
		else if (C == 2)
			mergeSortSR(arr, 0, nofrec - 1);
		else if(C==3)
			SortByNameS(arr, nofrec - 1);
		else if(C==4)
		SortByNameSR(arr,nofrec-1);
		else if(C==5)
		mergeSortSAge(arr,0,nofrec-1);
        else 
		mergeSortSAgeR(arr,0,nofrec-1);

		remove("StaffDetailsSorted.dat");
		FILE *sf = NULL;
		sf = fopen("StaffDetailsSorted.dat", "a");
		if (sf == NULL)
		{
			printf("File Creation Failed!\n");
		}
		i = 0;
		while (nofrec--)
		{
			fwrite((char *)(arr + i), sizeof(arr[i]), 1, sf);
			i++;
		}
		fclose(sf);
	}
}
void AddPatient()
{
	int N;
	struct PatientDetails newPat;
	FILE *fp;
	fp = fopen("PatientDetails.dat", "a");
	if (fp == NULL)
	{
		printf("File Creation Failed!\n");
	}
	printf("Enter the nos. of Patients : ");
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
	ID:
		printf("Enter the Patient id  Number : ");
		scanf("%d", &newPat.ID);
		if (checkID(newPat.ID))
		{
			printf("Error!Report with such ID number exist!\n");
			getchar();
			goto ID;
		}
		printf("Enter the patient Name : ");
		char ch;
		if (ch = getchar() == '\n')
			;
		gets(newPat.Name);

		printf("Enter the Address:");
		// getchar();
		gets(newPat.address);

	BG:
		printf("Enter Blood Group(Enter in the format X+(Ex.A+)):");
		scanf("%s", newPat.BloodGroup);

		if (!checkBloodGroup(newPat.BloodGroup))
		{
			printf("Error!Please enter in the format of X+(NA if no idea) or try again!\n");
			printf("Press any other key to continue...\n");
			getchar();
			goto BG;
		}
		printf("Enter the history:");
		getchar();
		gets(newPat.history);

		printf("Enter diagnosis :");
		// getchar();
		gets(newPat.diagnosis);
		// scanf("%s", &newPat.diagnosis);
		do{
		printf("Enter Gender(M:Male,F:Female,O:Other):");
		scanf("%s", &newPat.gender);
		if(!checkGender(newPat.gender)) printf("Error!Pleae enter the format mentioned or try again!\n");
	}while(!checkGender(newPat.gender));
	// newPat.gender=getchar();
	DOB:
		printf("Enter DOB(Enter in the format of dd/mm/yyyy):");
		scanf("%s", newPat.DOB);
		if (!checkDOB(newPat.DOB))
		{
			printf("%s", newPat.DOB);
			printf("Error!Please Enter in the form of dd/mm/yyyy or try again!\n");
			printf("Press any other key to continue...");
			getchar();
			goto DOB;
		}
		// printf("Enter Age :");
		// scanf("%d", &newPat.age);
		strcpy(newPat.Date, T.date);
		newPat.age = getAge(newPat.DOB);
		fwrite((char *)&newPat, sizeof(newPat), 1, fp);
		printf("Record saved successfully...\n");
		printf("Press any other key to continue...\n");

	}
	getchar();
	fclose(fp);
}
void DisplayPatients(FILE *fp)
{
	int nofrec = 0;
	struct PatientDetails Patient;
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Patient, sizeof(Patient), 1, fp)) == 1)
		{
			nofrec++;
			printf("\nDate Of Report:%s", Patient.Date);
			printf("\nID Number : %d", Patient.ID);
			printf("\nName : %s", Patient.Name);
			printf("\nBlood Group:%s", Patient.BloodGroup);
			printf("\nGender : %s", Patient.gender);
			printf("\nDOB:%s", Patient.DOB);
			printf("\nAge : %d", Patient.age);
			printf("\nAddress: %s", Patient.address);
			printf("\nDiagnosis : %s", Patient.diagnosis);
			printf("\nHistory: %s", Patient.history);
			printf("\n");
			printf("\n\n");
		}
		printf("Total number of records present are : %d\n", nofrec);
		printf("Please any key to continue...\n");
		getchar();
		system("clear");
	}
}
void ViewAllPatients()
{
	getchar();
	FILE *fp;
	fp = fopen("PatientDetails.dat", "r");
	DisplayPatients(fp);
	fclose(fp);
}
void ViewSortedPatients()
{
	getchar();
	FILE *fp;
	fp = fopen("PatientDetailsSorted.dat", "r");
	DisplayPatients(fp);
	fclose(fp);
}
void UpdatePatient()
{
	getchar();
	int recno, nofrec = 0;
	int ch;
	struct PatientDetails pat;
	FILE *fp;
	fp = fopen("PatientDetails.dat", "rb+");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		// ViewAllPatients();
		printf("\nEnter the patient id Number to modify : ");
		scanf("%d", &recno);
		getchar();
		getchar();
		printf("%d\n", recno);
		while ((fread((char *)&pat, sizeof(pat), 1, fp)) == 1)
		{
			printf("%d\n", pat.ID);
			nofrec++;
			if (pat.ID == recno)
			{
				printf("\nDate Of Report:%s", pat.Date);
				printf("\nID Number : %d", pat.ID);
				printf("\nName : %s", pat.Name);
				printf("\nHistory: %s", pat.history);
				printf("\nDiagnosis : %s", pat.diagnosis);
				printf("\nBlood Group:%s", pat.BloodGroup);
				printf("\nGender : %s", pat.gender);
				printf("\nDOB:%s", pat.DOB);
				printf("\nAge : %d", pat.age);
				printf("\n");

				printf("Do you want to modify this record : ? (1.Y/2.N)\n");
				scanf("%d", &ch);
				getchar();
				fseek(fp, ((nofrec - 1) * sizeof(pat)), 0);
				if (ch == 1)
				{
					strcpy(pat.Date, T.date);
				ID:
					// printf("\nDate Of Report:%s",Patient.Date);
					printf("Enter the patient id No : ");
					scanf("%d", &pat.ID);
					if (checkID(pat.ID))
					{
						printf("Error!File with such ID number exist!\n");
						getchar();
						goto ID;
					}
					getchar();
					printf("Enter the patient Name : ");
					// scanf("%s", pat.Name);
					gets(pat.Name);
					getchar();
					printf("Enter diagnosis :");
					// scanf("%s", pat.diagnosis);

					gets(pat.diagnosis);

				BG:
					printf("Enter Blood Group(Enter in the format X+(Ex.A+)):");
					scanf("%s", pat.BloodGroup);
					if (!checkBloodGroup(pat.BloodGroup))
					{
						printf("Error!Please enter in the format of X+(NA if no idea) or try again!\n");
						printf("Press any other key to continue...\n");
						getchar();
						goto BG;
					}
					printf("Enter Gender :");
					scanf("%s", pat.gender);
				DOB:
					printf("Enter DOB(Enter in the format of dd/mm/yyyy):");
					scanf("%s", pat.DOB);
					if (!checkDOB(pat.DOB))
					{
						printf("Error!Please Enter in the form of dd/mm/yyyy or try again!\n");
						goto DOB;
					}
					// printf("Enter Age :");
					// scanf("%d", &pat.age);
					pat.age = getAge(pat.DOB);
					fwrite((char *)&pat, sizeof(pat), 1, fp);
					printf("Record Modified\n");
					printf("Please any key to continue...\n");
					getchar();
					getchar();
				}
				else
				{
					printf("No modifications were made\n");
					printf("Please any key to continue...\n");
					getchar();
				}
				fclose(fp);
			}
		}
	}
}
void DeletePatient()
{
	getchar();
	int recno;
	int ch;
	struct PatientDetails pat;
	FILE *fp, *ft;
	fp = fopen("PatientDetails.dat", "r");
	ft = fopen("Temp.dat", "w");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		// ViewAllPatients();
		printf("\nEnter the patient id Number to delete : ");
		scanf("%d", &recno);
		getchar();
		while ((fread((char *)&pat, sizeof(pat), 1, fp)) == 1)
		{
			if (pat.ID == recno)
			{
				// printf("\nDate Of Report: %d", pat.Date);
				printf("\nID Number : %d", pat.ID);
				printf("\nName : %s", pat.Name);
				printf("\nDiagnosis : %s", pat.diagnosis);
				printf("\nBlood Group:%s", pat.BloodGroup);
				printf("\nGender : %s", pat.gender);
				printf("\nDOB:%s", pat.DOB);
				printf("\nAge : %d", pat.age);
				printf("\n");
				printf("Do you want to delete this record : ? (1.Y/2.N)\n");
				scanf("%d", &ch);
				getchar();
			}
		}
		if (ch == 1)
		{
			rewind(fp);
			while ((fread((char *)&pat, sizeof(pat), 1, fp)) == 1)
			{
				if (recno != pat.ID)
				{
					fwrite((char *)&pat, sizeof(pat), 1, ft);
				}
			}
			printf("\nRecord Deleted\n");
			printf("Press any other key to continue...\n");
			getchar();
			fclose(fp);
			fclose(ft);
			remove("PatientDetails.dat");
			rename("Temp.dat", "PatientDetails.dat");
			system("clear");
		}
		else
		{
			printf("No Record was deleted\n");

			printf("Press any other key to continue...\n");
			getchar();
			fclose(fp);
			fclose(ft);
			remove("Temp.dat");
			system("clear");
		}
	}
}
void FindPatient()
{
	int s, recno;
	char sname[150];
	struct PatientDetails pat;
	FILE *fp;
	fp = fopen("PatientDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again\n");
	else
	{
		printf("\n1.Search by Name\n2.Search by patient No.\n Enter choice : ");
		scanf("%d", &s);
		getchar();
		switch (s)
		{
		case 1:
			printf("Enter the patient Name to Search : ");
			scanf("%s", sname);
			// gets(sname);
			// printf("%s\n",sname);
			int flag1 = 1;
			while ((fread((char *)&pat, sizeof(pat), 1, fp)) == 1)
			{
				printf("%s\n", pat.Name);
				if (strcmp(sname, pat.Name) == 0)
				{
					flag1 = 0;
					printf("\nDate Of Report: %s", pat.Date);
					printf("\nID Number : %d", pat.ID);
					printf("\nName : %s", pat.Name);
					printf("\ndiagnosis : %s", pat.diagnosis);
					printf("\nBlood Group:%s", pat.BloodGroup);
					printf("\nGender : %s", pat.gender);
					printf("\nDOB:%s", pat.DOB);
					printf("\nAge : %d", pat.age);
					printf("\n");
					printf("Press any other key to continue...\n");
					getchar();
					getchar();
					system("clear");
				}
			}
			if (flag1)
			{
				printf("Patient with such name doesnt exist!\n");
				printf("Press any other key to continue...\n");
				getchar();
				getchar();
				system("clear");
			}
			break;
		case 2:
			printf("Enter the patient Number to Search : ");
			scanf("%d", &recno);
			// getchar();
			int flag2 = 1;
			while ((fread((char *)&pat, sizeof(pat), 1, fp)) == 1)
			{
				if (pat.ID == recno)
				{
					flag2 = 0;
					printf("\nDate Of Report: %s", pat.Date);
					printf("\nID Number : %d", pat.ID);
					printf("\nName : %s", pat.Name);
					printf("\nDiagnosis : %s", pat.diagnosis);
					printf("\nBlood Group:%s", pat.BloodGroup);
					printf("\nGender : %s", pat.gender);
					printf("\nDOB:%s", pat.DOB);
					printf("\nAge : %d", pat.age);
					printf("\n");
					printf("Press any other key to continue...\n");
					getchar();
					getchar();
					system("clear");
				}
			}
			if (flag2)
			{
				printf("Patient with this Record ID doesnt exit!\n");
				printf("Press any other key to continue...\n");
				getchar();
				getchar();
				system("clear");
			}
			break;
		}
	}
}

void AddDonor()
{
	int N;
	struct BloodBank Donor;
	FILE *fp;
	fp = fopen("DonorDetails.dat", "a");
	if (fp == NULL)
	{
		printf("File Creation Failed!\n");
	}
	printf("Enter the nos. of Donors : ");
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{

		printf("Enter the Donor's Name : ");
		char ch;
		if (ch = getchar() == '\n')
			;
		gets(Donor.NameOfDonor);
	BG:
		printf("Enter Blood Group(Enter in the format X+(Ex.A+)):");
		scanf("%s", &Donor.BloodGroup);

		if (!checkBloodGroup(Donor.BloodGroup))
		{
			printf("Error!Please enter in the format of X+(NA if no idea) or try again!\n");
			printf("Press any other key to continue...\n");
			getchar();
			goto BG;
		}
		printf("Enter quantity of blood donated(in ml):");
		getchar();
		scanf("%d", &Donor.quantity);
		strcpy(Donor.Date, T.date);
		printf("Record saved successfully,press any other key to continue...\n");
		getchar();
		fwrite((char *)&Donor, sizeof(Donor), 1, fp);
	}
	getchar();
	fclose(fp);
}
void FindDonor() {
int s, recno;
	char sname[100];
	struct BloodBank donor;
	FILE *fp;
	fp = fopen("DonorDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again\n");
	else
	{
        s=1;
		getchar();

			printf("Enter the donors Name to Search : ");
			scanf("%s", sname);

			int flag1 = 1;
			while ((fread((char *)&donor, sizeof(donor), 1, fp)) == 1)
			{
				printf("%s\n", donor.NameOfDonor);
				if (strcmp(sname, donor.NameOfDonor) == 0)
				{
					flag1 = 0;
					printf("\nDate Of Report: %s", donor.Date);
					printf("\nName : %s", donor.NameOfDonor);
					printf("\nBlood Group:%s", donor.BloodGroup);
					printf("\nQuantity: %s",donor.quantity);
					printf("\nPress any other key to continue...\n");
					getchar();
					getchar();
					system("clear");
				}
			}
			if (flag1)
			{
				printf("Patient with such name doesnt exist!\n");
				printf("Press any other key to continue...\n");
				getchar();
				getchar();
				system("clear");
			}
	
}
}
void ViewAllDonors()
{
	int nofrec = 0;
	struct BloodBank Donor;
	FILE *fp;
	fp = fopen("DonorDetails.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Donor, sizeof(Donor), 1, fp)) == 1)
		{
			nofrec++;
			printf("\nDate Of Donation:%s", Donor.Date);
			printf("\nName of Donor : %s", Donor.NameOfDonor);
			printf("\nBlood Group:%s", Donor.BloodGroup);
			printf("\nQuantity : %d", Donor.quantity);
			printf("\n");
			printf("\n\n");
		}
		printf("Total number of records present are : %d\n", nofrec);
		printf("Please any key to continue...\n");
		getchar();
		system("clear");
	}
}

void AddODonor()
{
	int N;
	struct OrganBank Donor;
	FILE *fp;
	fp = fopen("DonorDetails1.dat", "a");
	if (fp == NULL)
	{
		printf("File Creation Failed!\n");
	}
	printf("Enter the nos. of Donors : ");
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{

		printf("Enter the Donor's Name : ");
		char ch;
		if (ch = getchar() == '\n')
			;
		gets(Donor.NameOfDonor);
		printf("Enter the Donoting organ: ");
		// if (ch = getchar() == '\n')
		// 	;
		gets(Donor.Name);
	BG:
		printf("Enter Blood Group(Enter in the format X+(Ex.A+)):");
		scanf("%s", Donor.BloodGroup);

		if (!checkBloodGroup(Donor.BloodGroup))
		{
			printf("Error!Please enter in the format of X+(NA if no idea) or try again!\n");
			printf("Press any other key to continue...\n");
			getchar();
			goto BG;
		}
		strcpy(Donor.Date, T.date);
		// printf("This is executed\n\n");
		fwrite((char *)&Donor, sizeof(Donor), 1, fp);
	}
	getchar();
	fclose(fp);
}
void FindODonor() {
	int s, recno;
	char sname[100];
	struct OrganBank donor;
	FILE *fp;
	fp = fopen("DonorDetails1.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again\n");
	else
	{
        s=1;
		getchar();

			printf("Enter the donors Name to Search : ");
			scanf("%s", sname);

			int flag1 = 1;
			while ((fread((char *)&donor, sizeof(donor), 1, fp)) == 1)
			{
				printf("%s\n", donor.NameOfDonor);
				if (strcmp(sname, donor.NameOfDonor) == 0)
				{
					flag1 = 0;
					printf("\nDate Of Report: %s", donor.Date);
					printf("\nNameOfDonor : %s", donor.NameOfDonor);
					printf("\nBlood Group:%s", donor.BloodGroup);
					printf("\nName: %s",donor.Name);
					printf("\nPress any other key to continue...\n");
					getchar();
					getchar();
					system("clear");
				}
			}
			if (flag1)
			{
				printf("Patient with such name doesnt exist!\n");
				printf("Press any other key to continue...\n");
				getchar();
				getchar();
				system("clear");
			}
	
}
}
void ViewAllODonors()
{
	int nofrec = 0;
	struct OrganBank Donor;
	FILE *fp;
	fp = fopen("DonorDetails1.dat", "r");
	if (fp == NULL)
		printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Donor, sizeof(Donor), 1, fp)) == 1)
		{
			nofrec++;
			printf("\nDate Of Donation:%s", Donor.Date);
			printf("\nName of Donor : %s", Donor.NameOfDonor);
			printf("\nOrgan: %s", Donor.Name);
			printf("\nBlood Group:%s", Donor.BloodGroup);
			printf("\n");
			printf("\n\n");
		}
		printf("Total number of records present are : %d\n", nofrec);
		printf("Please any key to continue...\n");
		getchar();
		getchar();
		system("clear");
	}
}

void OrganBank()
{
	int loop = 1;
	do
	{
		int takeChoice;
		// printf("Enter what you wish to do:\n");
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-OrganBank\n");
		printf("##########################################################################################\n");
		printf("1:AddDonor\n2:FindRecord\n3:ViewAllRecords\nPress any other key to exit...");
		printf("\n##########################################################################################\n");
		printf("Enter the number corresponding to the Option:");
		scanf("%d", &takeChoice);
		// getchar();
		switch (takeChoice)
		{
		case 1:
			AddODonor();
			break;
		case 2:
			FindODonor();
			break;
		case 3:
			ViewAllODonors();
			break;

		default:
			system("clear");
			loop = 0;
			// break;
		}

	} while (loop);
}
void BloodBank()
{
	int loop = 1;
	do
	{
		int takeChoice;
		// printf("Enter what you wish to do:\n");
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-BloodBank\n");
		printf("##########################################################################################\n");
		printf("1:AddDonor\n2:FindRecord\n3:ViewAllRecords\nPress any other key to exit...");
		printf("\n##########################################################################################\n");
		printf("Enter the number corresponding to the Option:");
		scanf("%d", &takeChoice);
		// getchar();
		switch (takeChoice)
		{
		case 1:
			AddDonor();
			break;
		case 2:
			FindDonor();
			break;
		case 3:
			ViewAllDonors();
			break;
		default:
			system("clear");
			loop = 0;
			// break;
		}

	} while (loop);
}
void ResourceMenu()
{
	int loop = 1;
	do
	{
		int takeChoice;
		// printf("Enter what you wish to do:\n");
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-Resource Menu\n");
		printf("##########################################################################################\n");
		printf("1:OrganBank\n2:BloodBank\nPress any other key to exit...");
		printf("\n##########################################################################################\n");
		printf("Enter the number corresponding to the Option:");
		scanf("%d", &takeChoice);
		// getchar();
		switch (takeChoice)
		{
		case 1:
			OrganBank();
			break;
		case 2:
			BloodBank();
			break;
		default:
			system("clear");
			loop = 0;
			// break;
		}

	} while (loop);
}
void UserMenu()
{
	int loop = 1;
	do
	{
		int takeChoice;
		// printf("Enter what you wish to do:\n");
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-User's Menu\n");
		printf("##########################################################################################\n");
		printf("1:Create User\n2:Delete User\nPress any other key to exit...");
		printf("\n##########################################################################################\n");
		printf("Enter the number corresponding to the Option:");
		scanf("%d", &takeChoice);
		// getchar();
		switch (takeChoice)
		{
		case 1:
			CreateUser();
			break;
		case 2:
			DeleteUser();
			break;
		default:
			system("clear");
			loop = 0;
			// break;
		}

	} while (loop);
}
void DoctorMenu()
{
	int loop = 1,C;
	do
	{
		int takeChoice;
		// printf("Enter what you wish to do:\n");
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-Doctors Menu\n");
		printf("##########################################################################################\n");
		printf("1:Add Doctor's information\n2:Find Doctor's information\n3:Update Doctor's information\n4:Delete Doctor's information\n5:View All Doctors\nPress any other key to exit");
		printf("\n##########################################################################################\n");
		printf("Enter the number corresponding to the Operation you wish to perform:");
		scanf("%d", &takeChoice);
		// getchar();
		switch (takeChoice)
		{
		case 1:
			AddDoctor();
			break;
		case 2:
			FindDoctor();
			break;
		case 3:
			UpdateDoctor();
			break;
		case 4:
			DeleteDoctor();
			break;
		case 5:
			ViewAllDoctors();
			break;
        case 6:
         RETRY:
			printf("Enter the Order in which you wish to view Sorted:\n");
			printf("Press 1:Simple Sort wrt to IDNo(Acending)\nPress 2:Reverse Sort wrt to IDNo(Decending)\nPress 3: Sort by Name\nPress 4:Sort by Name(reversed)\nPress 5:Sort by Age\nPress 6:Sort by Age(reversed)\nEnter the choice:");
			scanf("%d", &C);
			if (!checkChoiceS(C))
			{
				printf("Error!Wrong input value\n");
				goto RETRY;
			}
			printf("Press any other key to continue..\n");
			SortDoctors(C);
			ViewSortedDoctor();
		break;
		default:
			system("clear");
			loop = 0;
			// break;
		}

	} while (loop);
}
void StaffMenu()
{
	int loop = 1;
	do
	{
		int takeChoice,C;
		// printf("Enter what you wish to do:\n");
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-Staff Menu\n");
		printf("##########################################################################################\n");
		printf("1:Add Staff Member's information\n2:Find Staff Member's information\n3:Update Staff Member's information\n4:Delete Staff Member's information\n5:View All Staff Members\n6:View All Staff members Sorted\nPress any other key to exit");
		printf("\n##########################################################################################\n");
		printf("Enter the number corresponding to the Operation you wish to perform:");
		scanf("%d", &takeChoice);
		// getchar();
		switch (takeChoice)
		{
		case 1:
			AddStaff();
			break;
		case 2:
			FindStaff();
			break;
		case 3:
			UpdateStaff();
			break;
		case 4:
			DeleteStaff();
			break;
		case 5:
			ViewAllStaff();
			break;
         case 6:
				RETRY:
			printf("Enter the Order in which you wish to view Sorted:\n");
			printf("Press 1:Simple Sort wrt to IDNo(Acending)\nPress 2:Reverse Sort wrt to IDNo(Decending)\nPress 3: Sort by Name\nPress 4:Sort by Name(reversed)\nPress 5:Sort by Age\nPress 6:Sort by Age(reversed)\nEnter the choice:");
			scanf("%d", &C);
			if (!checkChoiceS(C))
			{
				printf("Error!Wrong input value\n");
				goto RETRY;
			}
			printf("Press any other key to continue..\n");
			SortStaff(C);
			ViewSortedStaff();
			break;

		default:
			system("clear");
			loop = 0;
			// break;
		}

	} while (loop);
}
void patientMenu()
{

	int loop = 1;
	do
	{
		int takeChoice;
		int C;

		// printf("Enter what you wish to do:\n");
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-Patient Menu\n");
		printf("##########################################################################################\n");
		printf("1:Add patient information\n2:Find patient information\n3:Update patient information\n4:Delete patient information\n5:View All Patients\n6:View All Patients Sorted \nPress any other key to exit");
		printf("\n##########################################################################################\n");
		printf("Enter the number corresponding to the Operation you wish to perform:");
		scanf("%d", &takeChoice);
		// getchar();
		switch (takeChoice)
		{
		case 1:
			AddPatient();
			break;
		case 2:
			FindPatient();
			break;
		case 3:
			UpdatePatient();
			break;
		case 4:
			DeletePatient();
			break;
		case 5:
			ViewAllPatients();
			break;
		case 6:
		RETRY:
			printf("Enter the Order in which you wish to view Sorted:\n");
			printf("Press 1:Simple Sort wrt to IDNo(Acending)\nPress 2:Reverse Sort wrt to IDNo(Decending)\nPress 3: Sort by Name\nPress 4:Sort by Name(reversed)\nPress 5:Sort by BloodGroup\nPress 6:Sort by BloodGroup(reversed)\nPress 7:Sort by Age\nPress 8:Sort by Age(reversed)\nEnter the choice:");
			scanf("%d", &C);
			if (!checkChoice(C))
			{
				printf("Error!Wrong input value\n");
				goto RETRY;
			}
			printf("Press any other key to continue..\n");
			SortPatients(C);
			ViewSortedPatients();
			break;

		default:
			system("clear");
			loop = 0;
			// break;
		}

	} while (loop);
}

int CheckUser()
{     system("clear");
	char Password[50], Username[50];
	int ch = 0;
	struct UserDetails user;
	FILE *fp;
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		fp = fopen("UserDetails.dat", "rb");
		while ((fread((char *)&user, sizeof(user), 1, fp)) == 1)
		{
			// printf("%s %s %s",user.Name,user.UserName,user.password);
		}
		printf("\nUserName: ");

		rewind(fp);
		gets(Username);
		// printf("\nUserName:%s",Username);

		printf("Password : ");
		gets(Password);
		// printf("Password :%s ",Password);

		while ((fread((char *)&user, sizeof(user), 1, fp)) == 1)
		{
			// printf("%s %s %s",user.Name,user.UserName,user.password);

			if (strcmp(Username, user.UserName) == 0 && strcmp(Password, user.password) == 0)
			{
				ch = 1;
				system("clear");
				printf("Welcome  %s!\n\n\n", user.Name);
			}
		}
		if (strcmp(Username, "DefaultUser") == 0 && strcmp(Password, "0") == 0)
		{
			ch = 1;
			system("clear");
			printf("Welcome User!\n\n\n");
		}
		if (ch == 0)
		{
			printf("Wrong Username or Password!\n");
			printf("Press any other key to continue...\n");
			getchar();
			system("clear");
		}
	}
	fclose(fp);
	return ch;
}
void UpdateAll()
{

	int nofrec = 0;
	struct DoctorDetails Doc;
	FILE *fp;
	fp = fopen("DoctorDetails.dat", "r");
	if (fp == NULL)
	{
		printf("This was executed\n");
	}

	else
	{

		while ((fread((char *)&Doc, sizeof(Doc), 1, fp)) == 1)
		{
			printf("%d", nofrec);
			nofrec++;
			Doc.experience = getAge(Doc.Date);
			fwrite((char *)&Doc, sizeof(Doc), 1, fp);
		}

		fclose(fp);
	}

	nofrec = 0;

	struct PatientDetails pat;
	FILE *fp1;
	fp1 = fopen("PatientDetails.dat", "r");
	if (fp1 == NULL)
	{
	}
	// printf("\n\tFile doesn't exist!! try again");
	else
	{
		// ViewAllPatients();
		while ((fread((char *)&pat, sizeof(pat), 1, fp1)) == 1)
		{
			nofrec++;
			printf("%d\n", nofrec);
			printf("This is executed\n\n");
			printf("Name: %s\n", pat.Name);
			printf("Age: %d\n", pat.age);
			pat.age = getAge(pat.DOB);
			printf("Age :%d\n", pat.age);

			fwrite((char *)&pat, sizeof(pat), 1, fp1);
		}
		fclose(fp1);
	}

	nofrec = 0;
	struct StaffDetails Mem;
	FILE *fp2;
	fp2 = fopen("StaffDetails.dat", "rb+");
	if (fp2 == NULL)
	{
	}
	// printf("\n\tFile doesn't exist!! try again");
	else
	{
		while ((fread((char *)&Mem, sizeof(Mem), 1, fp2)) == 1)
		{
			nofrec++;

			Mem.experience = getAge(Mem.Date);

			fwrite((char *)&Mem, sizeof(Mem), 1, fp2);
		}

		fclose(fp2);
	}
}

int main()
{
check:
	if (!CheckUser())
	{
		goto check;
	}
	int newChoice, mainLoop = 1;
date:
	printf("Enter Todays Date(Enter in the format of dd/mm/yyyy):\n");
	scanf("%s", T.date);
	if (!checkDate(T.date))
	{
		printf("Error!Please enter in the format of dd/mm/yyyy or enter the date correctly:\n");
		printf("Press any key to continue...");
		getchar();
		getchar();
		system("clear");
		goto date;
	}
	// UpdateAll();
	do
	{
		printf("\n##########################################################################################\n");
		printf("\t\tHospital Management System-Main Menu\n");
		printf("##########################################################################################\n");
		printf("Enter 1: To Open the Patients records\n");
		printf("Enter 2:To Open the Staffs records\n");
		printf("Enter 3:To Open the Doctors Menu\n");
		printf("Enter 4:To Open the Resources record\n");
		printf("Enter 5: To Open the Users Menu\n");
		printf("Press any other key to exit...\n");
		printf("Enter the number to open the corresponding menu:\n");

		scanf("%d", &newChoice);
		system("clear");
		switch (newChoice)
		{
			
		case 1:
			patientMenu();
			// getchar();
			break;
		case 2:
			StaffMenu();
			// getchar();
			break;
		case 3:
			DoctorMenu();
			// getchar();
			break;
		case 4:
			ResourceMenu();
			break;
		case 5:
			UserMenu();
			break;
		default:
			system("clear");
			printf("\n--------------------Thank you!--------------------\n");
			getchar();
			mainLoop = 0;
		}
	} while (mainLoop);
	return 0;
}

