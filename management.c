#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>  // For _getch() on Windows
#include <dirent.h> // For directory handling
#include <sys/stat.h>

#define MAX_PASSWD_LEN 50
#define MAX_USERNAME_LEN 50
#define MAX_MOBILE_LEN 12
#define MAX_EMAIL_LEN 50

// GLOBAL VARIABLES
char regionName[50];
char hotelName[100];
char hotelAddress[100];
char hotelCoordinates[100];
int MenuChoice;

// ADMIN
void adminLogin();
int validateAdmin(const char *username, const char *passwd);
void getPassword(char *passwd);
void addHotel(const char *regionName);
void deleteHotelFromCSV(const char *regionName, const char *hotelName);
void addMenuItem(const char *regionName, const char *hotelName, const char *itemName, const char *type, int price, int time);
void deleteMenuItem(const char *regionName, const char *hotelName, const char *itemName);
bool isItemInMenu(const char *regionName, const char *hotelName, const char *itemName);
bool isRegionValid(const char *regionName);

// SHARED
void listRegions();
void displayRegionDetails(const char *regionName);
void displayHotelMenu(const char *regionName, const char *hotelName);
bool validateHotelExistence(const char *regionName, const char *hotelName);

// CUSTOMER
void CustomerLogin();
void cart(const char *regionName, const char *hotelName);
int getItemPrice(const char *regionName, const char *hotelName, const char *itemName);
int getItemTime(const char *regionName, const char *hotelName, const char *itemName);
bool validateEmail(const char *email);
bool isMobileNumberExist(const char *mobileNumber);
bool isValidMobileNumber(const char *mobileNumber);
bool isEmailExist(const char *email);
bool loginUser(const char *checkMobileNumber, const char *checkPasswd);

// MAIN CODE:
int main()
{
    while (1)
    {
        printf("\n");
        printf("*********************************************\n");
        printf("*           HOTEL MANAGEMENT SYSTEM         *\n");
        printf("*********************************************\n");
        printf("* %-10s %s \t\t\t    *\n", "OPTION", "\tACTION");
        printf("*-------------------------------------------*\n");
        printf("*   %-10d %s \t\t    *\n", 1, "USER LOGIN");
        printf("*   %-10d %s  \t    *\n", 2, "HOTEL ADMIN LOGIN");
        printf("*   %-10d %s \t\t\t    *\n", 3, "EXIT");
        printf("*********************************************\n");
        printf("SELECT CHOICE   :");
        int input;
        scanf(" %d", &input);
        system("cls");
        switch (input)
        {
        case 1:
            CustomerLogin();
            break;
        case 2:
            adminLogin();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("\nInvalid option");
            break;
        }
    }
    return 0;
}

// ADMIN CODE
void adminLogin()
{
    char username[MAX_USERNAME_LEN];
    char passwd[MAX_PASSWD_LEN];
admin_login:
    printf("*********************************************\n");
    printf("*                 ADMIN LOGIN               *\n");
    printf("*********************************************\n");
    printf("Enter Admin Username    :");
    scanf("%s", username);
    printf("Enter Admin Password    :");
    getPassword(passwd);
    printf("\n");
    if (validateAdmin(username, passwd))
    {
        printf("Admin login successful!\n");
        printf("Please tap the (ENTER) key to initiate the operation.");
        getch();
        system("cls");
        int adminChoice;
        do
        {
            // Display admin menu options
            printf("\n");
            printf("*********************************************\n");
            printf("*                 MAIN MENU                 *\n");
            printf("*********************************************\n");
            printf("* %-10s %s \t\t\t    *\n", "OPTION", "\tACTION");
            printf("*-------------------------------------------*\n");
            printf("*   %-10d %s \t\t    *\n", 1, "ADD HOTEL");
            printf("*   %-10d %s \t\t\t    *\n", 2, "DELETE");
            printf("*   %-10d %s \t    *\n", 3, "UPDATE HOTEL DETAILS");
            printf("*   %-10d %s \t\t\t    *\n", 4, "LOGOUT");
            printf("*********************************************\n");
            printf("SELECT CHOICE   :");
            scanf("%d", &adminChoice);
            switch (adminChoice)
            {
            case 1:
                listRegions();
                printf("Enter region name to display details    :");
                scanf("%s", regionName);
                for (int i = 0; regionName[i] != '\0'; i++)
                {
                    regionName[i] = toupper(regionName[i]);
                }
                if (!isRegionValid(regionName))
                {
                    printf("Entered Region is invalid %s....!\n", regionName);
                    exit(0);
                }
                system("cls");
                addHotel(regionName);
                displayRegionDetails(regionName);
                break;
            case 2:
                listRegions();
                printf("Enter region name to display details    :");
                scanf("%s", regionName);
                for (int i = 0; regionName[i] != '\0'; i++)
                {
                    regionName[i] = toupper(regionName[i]);
                }
                if (!isRegionValid(regionName))
                {
                    printf("Entered Region is invalid %s....!\n", regionName);
                    exit(0);
                }
                system("cls");
                displayRegionDetails(regionName);
                // Convert regionName to uppercase
                printf("Enter Hotel to delete   :");
                scanf("%s", hotelName);
                for (int i = 0; hotelName[i] != '\0'; i++)
                {
                    hotelName[i] = toupper(hotelName[i]);
                }
                if (!(validateHotelExistence(regionName, hotelName)))
                {
                    printf("Entered Hotel Name is invalid %s....!\n", hotelName);
                    exit(0);
                }
                deleteHotelFromCSV(regionName, hotelName);
                displayRegionDetails(regionName);
                break;
            case 3:
                listRegions();
                printf("Enter region name to display details    :");
                scanf("%s", regionName);
                for (int i = 0; regionName[i] != '\0'; i++)
                {
                    regionName[i] = toupper(regionName[i]);
                }
                if (!isRegionValid(regionName))
                {
                    printf("Entered Region is invalid %s....!\n", regionName);
                    exit(0);
                }
                system("cls");
                displayRegionDetails(regionName);
                // Convert regionName to uppercase
                printf("Enter Hotel to update   :");
                scanf("%s", hotelName);
                for (int i = 0; hotelName[i] != '\0'; i++)
                {
                    hotelName[i] = toupper(hotelName[i]);
                }
                displayHotelMenu(regionName, hotelName);
                printf("\n");
                printf("*********************************************\n");
                printf("*               MENU OPERATION              *\n");
                printf("*********************************************\n");
                printf("* %-10s %s \t\t\t    *\n", "OPTION", "\tACTION");
                printf("*-------------------------------------------*\n");
                printf("*   %-10d %s \t\t    *\n", 1, "ADD MENU ITEMS");
                printf("*   %-10d %s \t\t\t    *\n", 2, "DELETE MENU ITEMS");
                printf("*   %-10d %s \t\t\t    *\n", 3, "LOGOUT");
                printf("*********************************************\n");
                printf("SELECT CHOICE   :");
                scanf("%d", &MenuChoice);
                char itemName[50];
                char itemType[10];
                int price;
                int time;
                switch (MenuChoice)
                {
                case 1:
                    printf("Enter Item Name: ");
                    scanf("%s", itemName);

                    // Convert item name to upper case
                    for (int i = 0; itemName[i] != '\0'; ++i)
                    {
                        itemName[i] = toupper(itemName[i]);
                    }

                    printf("Enter Item Type (Non-Veg/Veg): ");
                    scanf("%s", itemType);

                    // Convert item type to upper case
                    for (int i = 0; itemType[i] != '\0'; ++i)
                    {
                        itemType[i] = toupper(itemType[i]);
                    }

                    // Check if the item type is valid
                    if (strcmp(itemType, "NON-VEG") != 0 && strcmp(itemType, "VEG") != 0)
                    {
                        printf("Invalid item type! Please enter either 'Non-Veg' or 'Veg'.\n");
                        // Handle the error (e.g., ask the user to re-enter the item type)
                    }
                    else
                    {
                        printf("Enter Item Price: ");
                        scanf("%d", &price);

                        printf("Enter Item Time: ");
                        scanf("%d", &time);

                        // Now you have itemName, itemType, price, and time to pass to the addMenuItem function
                        addMenuItem(regionName, hotelName, itemName, itemType, price, time);
                        displayHotelMenu(regionName, hotelName);
                    }
                    void addMenuItem(const char *regionName, const char *hotelName, const char *itemName, const char *type, int price, int time);
                    break;
                case 2:
                    printf("Enter Item Name to Delete: ");
                    scanf("%s", itemName);

                    // Convert item name to upper case
                    for (int i = 0; itemName[i] != '\0'; ++i)
                    {
                        itemName[i] = toupper(itemName[i]);
                    }
                    // Now you have the itemName to pass to the deleteMenuItem function
                    deleteMenuItem(regionName, hotelName, itemName);
                    displayHotelMenu(regionName, hotelName);
                    break;
                case 3:
                    printf("Logging out...!");
                    system("cls");
                    break;
                default:
                    printf("Invalid Choice");
                    break;
                }
                break;
            case 4:
                printf("Logging out...\n");
                system("cls");
                break;

            default:
                system("cls");
                printf("Invalid option! Please select a valid option.\n");
                break;
            }
        } while (adminChoice != 4);
    }
    else
    {
        int choice2 = 0;
        printf("Invalid username or password. Access denied!\n");
        printf("Press 1 to try again | Press 2 for Home page    :");
        scanf("%d", &choice2);
        system("cls");
        switch (choice2)
        {
        case 1:
            goto admin_login;
            break;
        case 2:
            break;
        default:
            printf("Invalid Choice! Code Exited..\n");
            exit(0);
            break;
        }
    }
}

// ADMIN FUCNCTION IMPLEMENTATION
int validateAdmin(const char *username, const char *passwd)
{
    // Replace with your admin credentials
    const char *adminUsername = "admin";
    const char *adminPasswd = "admin123";

    if (strcmp(username, adminUsername) == 0 && strcmp(passwd, adminPasswd) == 0)
    {
        return 1; // Admin credentials are valid
    }
    else
    {
        return 0; // Admin credentials are invalid
    }
}
void getPassword(char *passwd)
{
    int i = 0;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        // Read characters until Enter (Return) key is pressed
        if (ch == '\b' && i > 0)
        {
            // Handle backspace
            printf("\b \b"); // Move cursor back, print space, move cursor back again
            i--;
            passwd[i] = '\0';
        }
        else if (ch != '\b')
        {
            // Skip backspace character
            passwd[i++] = ch; // Store character in password buffer
            printf("*");      // Print asterisk (*) to the console
        }
    }
    passwd[i] = '\0'; // Null-terminate the password string
}
void listRegions()
{
    system("cls");
    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error opening directory.\n");
        return;
    }
    printf("\n");
    printf("****************************************************\n");
    printf("*                SELECT REGIONS                    *\n");
    printf("****************************************************\n");
    // Loop through each entry in the directory
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if entry is a directory and not '.' or '..'
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            printf("Region    : %s\n", entry->d_name);

            // Open the region directory
            DIR *regionDir = opendir(entry->d_name);
            if (regionDir == NULL)
            {
                printf("Error opening region directory.\n");
                return;
            }
            // Close the region directory
            closedir(regionDir);
        }
    }
    printf("----------------------------------------------------\n");
    // Close the current directory
    closedir(dir);
}
bool isRegionValid(const char *regionName)
{
    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error opening current directory.\n");
        return false;
    }

    // Iterate through the directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if the entry is a directory and matches the region name
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, regionName) == 0)
        {
            closedir(dir);
            return true; // Region directory found
        }
    }
    // Close the directory
    closedir(dir);

    // Region directory not found
    return false;
}
void addHotel(const char *regionName)
{
    system("cls");
    printf("****************************************************\n");
    printf("*                   ADDING HOTEL                   *\n");
    printf("****************************************************\n");
    printf("Enter Hotel Name            :");
    scanf("%s", hotelName);
    for (int i = 0; hotelName[i] != '\0'; i++)
    {
        hotelName[i] = toupper(hotelName[i]);
    }
    printf("Enter Hotel Address (use '-' instead of ',') :");
    scanf("%s", hotelAddress);
    printf("Enter Hotel Coordinates     :");
    scanf("%s", hotelCoordinates);

    // Check if the hotel name already exists in the details.csv file
    char detailsFilePath[100];
    snprintf(detailsFilePath, sizeof(detailsFilePath), "%s/details.csv", regionName);
    FILE *detailsFile = fopen(detailsFilePath, "r");
    if (detailsFile == NULL)
    {
        printf("Error opening details file for region %s.\n", regionName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), detailsFile) != NULL)
    {
        char *token = strtok(line, ",");
        if (strcmp(token, hotelName) == 0)
        {
            printf("Hotel with name '%s' already exists in this region.\n", hotelName);
            fclose(detailsFile);
            return;
        }
    }
    fclose(detailsFile);

    // Append new hotel details to the details.csv file
    detailsFile = fopen(detailsFilePath, "a");
    if (detailsFile == NULL)
    {
        printf("Error opening details file for writing.\n");
        return;
    }
    fprintf(detailsFile, "%s,%s,%s\n", hotelName, hotelAddress, hotelCoordinates);
    fclose(detailsFile);

    // Create a new CSV file for the hotel in the region directory
    char hotelFilePath[100];
    snprintf(hotelFilePath, sizeof(hotelFilePath), "%s/%s.csv", regionName, hotelName);
    FILE *hotelFile = fopen(hotelFilePath, "w");
    if (hotelFile == NULL)
    {
        printf("Error creating hotel file for writing.\n");
        return;
    }
    fclose(hotelFile);

    printf("Hotel '%s' has been added successfully to the '%s' region.\n", hotelName, regionName);
    printf("Kindly press (ENTER) to display Hotel...!.");
    getch();
    system("cls");
}
void addMenuItem(const char *regionName, const char *hotelName, const char *itemName, const char *type, int price, int time)
{
    // Construct the file path for the hotel's menu file
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.csv", regionName, hotelName);

    // Open the hotel's menu file for appending
    FILE *file = fopen(filePath, "a");
    if (file == NULL)
    {
        printf("Error opening menu file for hotel '%s' in region '%s'.\n", hotelName, regionName);
        return;
    }

    // Write the new menu item to the file
    fprintf(file, "%s,%s,%d,%d\n", itemName, type, price, time);

    // Close the file
    fclose(file);

    printf("Menu item added successfully to hotel '%s' in region '%s'.\n", hotelName, regionName);
}
void deleteMenuItem(const char *regionName, const char *hotelName, const char *itemName)
{
    // Construct the file path for the hotel's menu file
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.csv", regionName, hotelName);

    // Open the hotel's menu file for reading
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error opening menu file for hotel '%s' in region '%s'.\n", hotelName, regionName);
        return;
    }

    // Create a temporary file to write the updated menu without the deleted item
    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Check if the line contains the item to be deleted
        if (strstr(line, itemName) == NULL)
        {
            // If not, write the line to the temporary file
            fputs(line, tempFile);
        }
        else
        {
            // Set found to true if the item is found
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        // Replace the original menu file with the temporary file
        remove(filePath);
        rename("temp.csv", filePath);
        printf("Item '%s' has been deleted from the menu of hotel '%s' in region '%s'.\n", itemName, hotelName, regionName);
    }
    else
    {
        remove("temp.csv");
        printf("Item '%s' not found in the menu of hotel '%s' in region '%s'.\n", itemName, hotelName, regionName);
    }
}
void displayRegionDetails(const char *regionName)
{
    // Create the file path for the details.csv file in the selected region directory
    char filePath[100];
    snprintf(filePath, sizeof(filePath), "%s/details.csv", regionName);

    // Open the details.csv file for reading
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Entered Region is invalid %s....!\n", regionName);
        exit(0);
        return;
    }
    system("cls");
    printf("\n");
    printf("*******************************************************************\n");
    printf("                 DETAILS OF %s REGION                    \n", regionName);
    printf("*******************************************************************\n");
    char line[256];
    int hotelCount = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        hotelCount++;
        // Extract hotel details from the CSV line
        char *token = strtok(line, ",");
        char *hotelName = token;
        token = strtok(NULL, ",");
        char *hotelAddress = token;
        token = strtok(NULL, ",");
        char *hotelCoordinates = token;

        // Print hotel details
        printf("=================================HOTEL %d==================================\n", hotelCount);
        printf("HOTEL NAME              : %s\n", hotelName);
        printf("HOTEL ADDRESS           : %s\n", hotelAddress);
        printf("GOOGLE MAP CO_ORDINATES : %s\n", hotelCoordinates);
    }

    // Close the file
    fclose(file);
}
void displayHotelMenu(const char *regionName, const char *hotelName)
{
    // Construct the file path for the hotel's menu file
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.csv", regionName, hotelName);

    // Open the hotel's menu file for reading
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Invaild Hotel Name '%s'..! Exiting Code.\n", hotelName);
        exit(0);
        return;
    }
    system("cls");
    // Display hotel menu header
    printf("\n");
    printf("********************************************************************************\n");
    printf("                           MENU FOR HOTEL %s                   \n", hotelName);
    printf("********************************************************************************\n");
    printf("--------------------------------------------------------------------------------\n");
    // Print headers for each menu item
    printf("%-30s | %-20s | %-10s | %-20s\n", "ITEM", "TYPE", "PRICE(INR)", "TIME(MIN)");
    printf("---------------------------------------------------------------------------------\n");

    // Read and print each line of the hotel's menu file
    char line[256];
    char *token;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Tokenize the line by comma
        token = strtok(line, ",");
        printf("%-30s | ", token); // Print ITEM

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            printf("%-20s | ", token); // Print TYPE
        }
        else
        {
            printf("%-20s | ", "(null)");
        }

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            printf("%-10s | ", token); // Print PRICE
        }
        else
        {
            printf("%-10s | ", "(null)");
        }

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            printf("%-20s\n", token); // Print TIME
        }
        else
        {
            printf("%-20s\n", "(null)");
        }
    }

    // Close the file
    fclose(file);
}
void deleteHotelFromCSV(const char *regionName, const char *hotelName)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/details.csv", regionName);
    char hotelFilePath[256];
    snprintf(hotelFilePath, sizeof(hotelFilePath), "%s/%s.csv", regionName, hotelName);
    FILE *inputFile = fopen(filePath, "r");
    if (inputFile == NULL)
    {
        printf("Error: Unable to open the input CSV file %s.\n", filePath);
        return;
    }

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        printf("Error: Unable to create a temporary file.\n");
        fclose(inputFile);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        if (strstr(line, hotelName) != NULL)
        {
            // Skip the current line (hotel row)
            found = 1;
        }
        else
        {
            fputs(line, tempFile);
        }
    }

    fclose(inputFile);
    fclose(tempFile);

    if (found)
    {
        remove(filePath);
        rename("temp.csv", filePath);
        printf("Hotel '%s' has been deleted from the CSV file %s.\n", hotelName, filePath);
        remove(hotelFilePath);
        printf("Hotel-specific CSV file '%s' has been deleted.\n", hotelFilePath);
    }
    else
    {
        remove("temp.csv");
        printf("Hotel '%s' not found in the CSV file %s.\n", hotelName, filePath);
    }
}

// CUSTOMER CODE
struct User
{
    char emailID[MAX_EMAIL_LEN];
    char username[MAX_USERNAME_LEN];
    char mobileNumber[MAX_MOBILE_LEN];
    char passwd[MAX_PASSWD_LEN];
};
//
void CustomerLogin()
{
    int choice;
    struct User user;
    do
    {
        printf("\n");
        printf("****************************************************\n");
        printf("*                 SIGNIN || SIGNUP                 *\n");
        printf("****************************************************\n");
        printf("\n");
        printf("****************************************************\n");
        printf("* %-10s %s \t\t\t   *\n", "OPTION", "\t\tACTION");
        printf("----------------------------------------------------\n");
        printf("*   %-10d %s \t\t   *\n", 1, "\t\tREGISTER");
        printf("*   %-10d %s  \t\t\t   *\n", 2, "\t\tLOGIN");
        printf("****************************************************\n");
        printf("SELECT CHOICE   :");
        scanf("%d", &choice);
        if (choice > 2)
        {
            system("cls");
            printf("Please enter the vaild option\n");
        }
    } while (choice > 2);
    switch (choice)
    {
    case 1:
    registertion_page:
        system("cls");
        printf("****************************************************\n");
        printf("*            CUSTOMER REGISTERTION                 *\n");
        printf("****************************************************\n");
        do
        {
            printf("\nEnter Customer Email      :");
            scanf("%s", user.emailID);
            if (!(validateEmail(user.emailID)))
            {
                printf("Email is not valid! Kindly Enter valid Email...!");
            }
            else if (isEmailExist(user.emailID))
            {
                printf("Email already exists! Please enter a different email...!");
            }
        } while (!(validateEmail(user.emailID)) || isEmailExist(user.emailID));

        printf("Enter Customer Name       :");
        scanf("%s", user.username);
        // Check if the mobile number is valid and does not already exist in the CSV file
        do
        {
            printf("Enter Mobile Number       :");
            scanf("%s", user.mobileNumber);
            if (!isValidMobileNumber(user.mobileNumber))
            {
                printf("Invalid mobile number! Please enter a 10-digit mobile number.\n");
            }
            else if (isMobileNumberExist(user.mobileNumber))
            {
                printf("Mobile number already exists! Please enter a different mobile number.\n");
            }
        } while (!isValidMobileNumber(user.mobileNumber) || isMobileNumberExist(user.mobileNumber));

        printf("Enter Password              :");
        scanf("%s", user.passwd);

        FILE *file = fopen("CustomerData.csv", "a");
        if (file == NULL)
        {
            printf("Error opening file for writing!\n");
        }
        else
        {
            // Trim leading and trailing whitespace characters from the password
            char trimmedPasswd[MAX_PASSWD_LEN];
            sscanf(user.passwd, "%s", trimmedPasswd);
            char trimmedMobilenumber[MAX_MOBILE_LEN];
            sscanf(user.mobileNumber, "%s", trimmedMobilenumber);
            // Write the trimmed details to the CSV file
            fprintf(file, "%s,%s,%s,%s\n", user.mobileNumber, user.passwd, user.username, user.emailID);

            // Close the file
            fclose(file);

            // Print registration success message
            printf("\t\tRegistration successful.....!\n");
            printf("Please! Press (ENTER) for moving to Login Page.....");
            getch();
        }

    case 2:
    login_page:
        system("cls");
        printf("****************************************************\n");
        printf("*                CUSTOMER LOGIN                    *\n");
        printf("****************************************************\n");
        char checkMobileNumber[11];
        char checkPasswd[50];
        printf("Enter Mobile Number  :");
        scanf("%s", checkMobileNumber);
        printf("Enter Password       :");
        getPassword(checkPasswd);
        if (loginUser(checkMobileNumber, checkPasswd))
        {
            printf("Login successful!\n");
            goto Ordering_phase;
        }
        else
        {
            printf("\nInvalid mobile number or password!");
            exit(0);
        }
        break;
    default:
        break;
    }
Ordering_phase:
    listRegions();
    printf("Enter region name to display details    :");
    scanf("%s", regionName);
    // Convert regionName to uppercase
    for (int i = 0; regionName[i] != '\0'; i++)
    {
        regionName[i] = toupper(regionName[i]);
    }
    displayRegionDetails(regionName);
    printf("Enter Hotel Name to Display Menu    :");
    scanf("%s", hotelName);
    for (int i = 0; hotelName[i] != '\0'; i++)
    {
        hotelName[i] = toupper(hotelName[i]);
    }
    displayHotelMenu(regionName, hotelName);
    cart(regionName, hotelName);
    printf("Kindly press (ENTER) to EXIT...!.");
    getch();
    exit(0);
    system("cls");
}
// ADMIN FUCNCTION IMPLEMENTATION
// Function to validate email address
bool validateEmail(const char *email)
{
    // Find the position of '@' character
    char *atSymbol = strchr(email, '@');

    // If '@' is not found or it's the first character, return false
    if (atSymbol == NULL || atSymbol == email)
    {
        return false;
    }

    // Get the substring after '@' to validate the domain
    char *domain = atSymbol + 1;

    // Check if the domain ends with allowed suffixes
    if (strcmp(domain, "gmail.com") == 0 ||
        strcmp(domain, "hotmail.com") == 0 ||
        strcmp(domain, "yahoo.com") == 0)
    {
        return true;
    }

    // If not found, return false
    return false;
}
bool isMobileNumberExist(const char *mobileNumber)
{
    FILE *file = fopen("CustomerData.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading!\n");
        exit(1);
    }
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *token;
        token = strtok(line, ",");
        // Assuming the mobile number is the third field
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        if (strcmp(token, mobileNumber) == 0)
        {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}
// Function to validate mobile number format
bool isValidMobileNumber(const char *mobileNumber)
{
    int length = strlen(mobileNumber);
    if (length != 10)
    {
        return false;
    }
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(mobileNumber[i]))
        {
            return false;
        }
    }
    return true;
}
// Function to check if email already exists in the CSV file
bool isEmailExist(const char *email)
{
    FILE *file = fopen("CustomerData.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading!\n");
        exit(1);
    }
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *token;
        token = strtok(line, ",");
        for (int i = 0; i < 2; i++)
        { // Skip first two tokens
            token = strtok(NULL, ",");
            if (token == NULL)
            { // Check if token is NULL (invalid CSV format)
                fclose(file);
                return false;
            }
        }
        if (strcmp(token, email) == 0)
        {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}
bool loginUser(const char *checkMobileNumber, const char *checkPasswd)
{
    FILE *file = fopen("CustomerData.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading!\n");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        if (strcmp(token, checkMobileNumber) == 0)
        {
            char *passwordToken = strtok(NULL, ",");
            if (passwordToken != NULL)
            {
                // Null-terminate the password token
                char password[MAX_PASSWD_LEN + 1];
                strncpy(password, passwordToken, MAX_PASSWD_LEN);
                password[MAX_PASSWD_LEN] = '\0';

                // Check if the password matches
                if (strcmp(password, checkPasswd) == 0)
                {
                    fclose(file);
                    return true; // Mobile number and password match
                }
            }
        }
    }

    fclose(file);
    return false; // Mobile number or password doesn't match
}
bool isItemInMenu(const char *regionName, const char *hotelName, const char *itemName)
{
    // Construct the file path for the hotel's menu file
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.csv", regionName, hotelName);

    // Open the hotel's menu file for reading
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error opening menu file for hotel '%s' in region '%s'.\n", hotelName, regionName);
        return false;
    }

    // Search for the item name in the menu file
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Tokenize the line to extract the item name
        char *token = strtok(line, ",");
        if (token != NULL && strcmp(token, itemName) == 0)
        {
            fclose(file);
            return true; // Item found in the menu
        }
    }

    // Close the file
    fclose(file);

    // Item not found in the menu
    return false;
}
bool validateHotelExistence(const char *regionName, const char *hotelName)
{
    // Construct the path for the hotel CSV file
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.csv", regionName, hotelName);
    // Check if the hotel CSV file exists
    struct stat st;
    if (stat(filePath, &st) == 0 && S_ISREG(st.st_mode))
    {
        return true; // Hotel CSV file exists
    }
}
int getItemPrice(const char *regionName, const char *hotelName, const char *itemName)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.csv", regionName, hotelName);

    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open the menu file for hotel '%s' in region '%s'.\n", hotelName, regionName);
        return -1; // Return -1 indicating error
    }

    char line[256];
    int price = -1; // Default price if not found

    // Loop through each line in the menu file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Tokenize the line using commas as delimiters
        char *token = strtok(line, ",");
        if (strcmp(token, itemName) == 0) // Compare the item name
        {
            // Extract price (second field after two commas)
            token = strtok(NULL, ","); // Skip first field
            token = strtok(NULL, ","); // Skip second field
            if (token != NULL)
            {
                price = atoi(token); // Convert string to integer
                break;               // Item found, break the loop
            }
        }
    }

    fclose(file);
    return price;
}
int getItemTime(const char *regionName, const char *hotelName, const char *itemName)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.csv", regionName, hotelName);

    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open the menu file for hotel '%s' in region '%s'.\n", hotelName, regionName);
        return -1; // Return -1 indicating error
    }

    char line[256];
    int time = -1; // Default time if not found

    // Loop through each line in the menu file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Tokenize the line using commas as delimiters
        char *token = strtok(line, ",");
        if (strcmp(token, itemName) == 0) // Compare the item name
        {
            // Extract time (third field after three commas)
            token = strtok(NULL, ","); // Skip first field
            token = strtok(NULL, ","); // Skip second field
            token = strtok(NULL, ","); // Skip third field
            if (token != NULL)
            {
                time = atoi(token); // Convert string to integer
                break;              // Item found, break the loop
            }
        }
    }

    fclose(file);
    return time;
}
void cart(const char *regionName, const char *hotelName)
{
    char itemName[50];
    int quantity;
    int totalPrice = 0;
    int totalTime = 0;
    char choice;
    printf("===========================================================================\n");
    printf("                              ADDING ITEMS TO CART                 \n");
    printf("===========================================================================\n");
    // Display hotel menu here (you can reuse the displayHotelMenu function)
    do
    {
        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    Invalid_item:
    {
        // Prompt for item name
        printf("Enter Item Name        :");
        fgets(itemName, sizeof(itemName), stdin);

        // Remove trailing newline character from itemName
        if (strlen(itemName) > 0 && itemName[strlen(itemName) - 1] == '\n')
        {
            itemName[strlen(itemName) - 1] = '\0';
        }

        // Convert item name to upper case
        for (int i = 0; itemName[i] != '\0'; ++i)
        {
            itemName[i] = toupper(itemName[i]);
        }
        if (!isItemInMenu(regionName, hotelName, itemName))
        {
            printf("Item '%s' is not available in the menu.\n", itemName);
            goto Invalid_item;
        }
    }
        // Prompt for quantity
        printf("Enter Quantity         :");
        scanf("%d", &quantity);

        // Calculate total price and time for the item
        // You need to fetch the price and time for the item from the menu file
        // Then multiply by the quantity to get the total
        int itemPrice = getItemPrice(regionName, hotelName, itemName);
        int itemTime = getItemTime(regionName, hotelName, itemName);
        int totalItemPrice = itemPrice * quantity;
        int totalItemTime = itemTime * quantity;

        // Update total price and time for the order
        totalPrice += totalItemPrice;
        totalTime += totalItemTime;

        // Ask if user wants to add more items
        printf("Add another item? (y/n): ");
        scanf(" %c", &choice);
    } while (tolower(choice) == 'y');

    // Display total price and time for the order
    printf("\n=========================================\n");
    printf("        ORDER SUMMARY\n");
    printf("-----------------------------------------\n");
    printf("Total Price: INR %d\n", totalPrice);
    printf("Total Time: %d mins\n", totalTime);
}