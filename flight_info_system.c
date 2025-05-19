#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure definitions
struct Flight {
    char flightID[10];
    char source[20];
    char arrivalTime[10];
    char destination[20];
    char departureTime[10];
    float flightTime;
    float fare;
} flights[100];

struct City {
    char cities[20];
} city_list[100];

struct UserDetails {
    char username[100];
    char email[100];
    char password[100];
} user[50];

struct CheapestFlight {
    float fare;
    char source[20];
    char stop[20];
    char destination[20];
    char flightID1[10];
    char flightID2[10];
} cheapflight[10];

// Global counters
int countuser = 0;
int countflight = 0;
int countplaces = 0;

// Function prototypes
void load_files();
void load_users();
void user_login();
void create_account();
void authenticate_user();
void display_all_flights();
void display_flights_from_source();
void display_flights_source_to_destination();
int menu_choice();
int validate_username(const char *username);
int validate_email(const char *email);
int validate_password(const char *password);

// Main function
int main() {
    load_files();
    load_users();
    user_login();
    menu_choice();
    return 0;
}

// Menu selection
int menu_choice() {
    int choice;
    do {
        printf("\nSelect an option:\n");
        printf("1. Check all flights available\n");
        printf("2. Check flights from one place\n");
        printf("3. Check flights from one place to another\n");
        printf("4. Logout\n");
        printf("Choice: ");

        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Error: Please enter a valid number.\nChoice: ");
        }
        getchar(); // Clear newline

        switch (choice) {
            case 1: display_all_flights(); break;
            case 2: display_flights_from_source(); break;
            case 3: display_flights_source_to_destination(); break;
            case 4: printf("Successfully logged out... :)\n"); return 0;
            default: printf("Invalid choice\n"); break;
        }
    } while (choice != 4);
    return 0;
}

// Load flight and city data from CSV
void load_files() {
    FILE *fp = fopen("FLIGHTDETAILS.csv", "r");
    if (!fp) {
        printf("Error: Could not open FLIGHTDETAILS.csv. Creating new file.\n");
        fp = fopen("FLIGHTDETAILS.csv", "w");
        if (!fp) {
            printf("Error: Could not create FLIGHTDETAILS.csv.\n");
            exit(1);
        }
        fclose(fp);
        return;
    }

    char line[100]; // Increased buffer size
    int i = 0;
    while (fgets(line, sizeof(line), fp) && i < 100) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%f,%f",
                   flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                   flights[i].destination, flights[i].departureTime, &flights[i].flightTime,
                   &flights[i].fare) == 7) {
            i++;
            countflight++;
        }
    }
    fclose(fp);

    FILE *fp2 = fopen("PLACES.csv", "r");
    if (!fp2) {
        printf("Error: Could not open PLACES.csv. Creating new file.\n");
        fp2 = fopen("PLACES.csv", "w");
        if (!fp2) {
            printf("Error: Could not create PLACES.csv.\n");
            exit(1);
        }
        fclose(fp2);
        return;
    }

    i = 0;
    while (fscanf(fp2, "%19s", city_list[i].cities) == 1 && i < 100) {
        i++;
        countplaces++;
    }
    fclose(fp2);
}

// Load user data from CSV
void load_users() {
    FILE *fp = fopen("Userdetails.csv", "r");
    if (!fp) {
        printf("Error: Could not open Userdetails.csv. Creating new file.\n");
        fp = fopen("Userdetails.csv", "w");
        if (!fp) {
            printf("Error: Could not create Userdetails.csv.\n");
            exit(1);
        }
        fclose(fp);
        return;
    }

    char line[300]; // Increased buffer size
    int i = 0;
    while (fgets(line, sizeof(line), fp) && i < 50) {
        line[strcspn(line, "\n")] = '\0';
        if (sscanf(line, "%[^,],%[^,],%[^,]", user[i].username, user[i].email, user[i].password) == 3) {
            i++;
            countuser++;
        }
    }
    fclose(fp);
}

// Validate username
int validate_username(const char *username) {
    if (strlen(username) < 3 || strlen(username) >= 100) {
        printf("Username must be 3-99 characters long.\n");
        return 0;
    }
    if (strchr(username, ',') || strchr(username, ' ')) {
        printf("Username cannot contain commas or spaces.\n");
        return 0;
    }
    for (int i = 0; i < countuser; i++) {
        if (strcmp(username, user[i].username) == 0) {
            printf("Username already exists.\n");
            return 0;
        }
    }
    return 1;
}

// Validate email
int validate_email(const char *email) {
    if (strlen(email) >= 100 || !strchr(email, '@')) {
        printf("Invalid email address.\n");
        return 0;
    }
    if (strchr(email, ',')) {
        printf("Email cannot contain commas.\n");
        return 0;
    }
    for (int i = 0; i < countuser; i++) {
        if (strcmp(email, user[i].email) == 0) {
            printf("Email already exists.\n");
            return 0;
        }
    }
    return 1;
}

// Validate password
int validate_password(const char *password) {
    if (strlen(password) < 8 || strlen(password) >= 100) {
        printf("Password must be 8-99 characters long.\n");
        return 0;
    }
    if (strchr(password, ',')) {
        printf("Password cannot contain commas.\n");
        return 0;
    }
    return 1;
}

// User login or account creation
void user_login() {
    char option;
    printf("\n%60s\n", "------------------------------------------------------------");
    printf("%40s", "Welcome to Flight Finder\n");
    printf("%5s", "Do you have a travel account with us? [Y/N] ");

    while (1) {
        scanf(" %c", &option);
        getchar(); // Clear newline
        if (option == 'y' || option == 'Y') {
            authenticate_user();
            break;
        } else if (option == 'n' || option == 'N') {
            create_account();
            break;
        } else {
            printf("ERROR: Please type [y/Y] or [n/N]: ");
        }
    }
    printf("%60s\n", "------------------------------------------------------------");
}

// Create new user account
void create_account() {
    if (countuser >= 50) {
        printf("Error: Maximum number of users reached.\n");
        return;
    }

    char username[100], email[100], password[100];
    printf("\n%60s\n", "------------------------------------------------------------");
    printf("%10s", "Let's create your new account :)\n");

    // Username input
    while (1) {
        printf("Enter Your Username: ");
        if (scanf(" %99[^\n]", username) != 1) {
            while (getchar() != '\n');
            printf("Error: Invalid input.\n");
            continue;
        }
        getchar();
        if (validate_username(username)) break;
    }

    // Email input
    while (1) {
        printf("Enter your Email Address: ");
        if (scanf(" %99s", email) != 1) {
            while (getchar() != '\n');
            printf("Error: Invalid input.\n");
            continue;
        }
        getchar();
        if (validate_email(email)) break;
    }

    // Password input
    while (1) {
        printf("Enter your Password: ");
        if (scanf(" %99[^\n]", password) != 1) {
            while (getchar() != '\n');
            printf("Error: Invalid input.\n");
            continue;
        }
        getchar();
        if (validate_password(password)) break;
    }

    // Save user
    strcpy(user[countuser].username, username);
    strcpy(user[countuser].email, email);
    strcpy(user[countuser].password, password);
    countuser++;

    FILE *fp = fopen("Userdetails.csv", "a");
    if (!fp) {
        printf("Error: Could not open Userdetails.csv for writing.\n");
        return;
    }
    fprintf(fp, "%s,%s,%s\n", username, email, password);
    fclose(fp);

    printf("\nAccount created successfully!\n");
    printf("%60s\n", "------------------------------------------------------------");
    printf("%10s%s\n", "Welcome!! ", username);
    printf("%10s", "How may I help you\n");
}

// Authenticate existing user
void authenticate_user() {
    if (countuser == 0) {
        printf("No user data available. Please create a new account.\n");
        create_account();
        return;
    }

    char name[100], password[100];
    int attempts = 3;

    while (attempts > 0) {
        printf("Enter your username or email address: ");
        if (scanf(" %99s", name) != 1) {
            while (getchar() != '\n');
            printf("Error: Invalid input.\n");
            continue;
        }
        getchar();

        for (int i = 0; i < countuser; i++) {
            if (strcmp(name, user[i].username) == 0 || strcmp(name, user[i].email) == 0) {
                int pwd_attempts = 3;
                while (pwd_attempts > 0) {
                    printf("Enter your password: ");
                    if (scanf(" %99[^\n]", password) != 1) {
                        while (getchar() != '\n');
                        printf("Error: Invalid input.\n");
                        continue;
                    }
                    getchar();

                    if (strcmp(password, user[i].password) == 0) {
                        printf("Welcome Back!! %s\n", user[i].username);
                        return;
                    } else {
                        pwd_attempts--;
                        printf("Wrong password! %d attempts left.\n", pwd_attempts);
                    }
                }
                printf("Maximum password attempts reached.\n");
                create_account();
                return;
            }
        }
        attempts--;
        printf("Invalid username/email. %d attempts left.\n", attempts);
    }

    printf("Maximum login attempts reached. Exiting.\n");
    exit(0);
}

// Display all flights
void display_all_flights() {
    if (countflight == 0) {
        printf("No flights available.\n");
        return;
    }

    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    printf("%75s\n", "---------------------------------------------------------------------------");
    for (int i = 0; i < countflight; i++) {
        printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f\n",
               flights[i].flightID, flights[i].source, flights[i].arrivalTime,
               flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
    }
    printf("%75s\n", "---------------------------------------------------------------------------");
}

// Display flights from a source
void display_flights_from_source() {
    if (countplaces == 0) {
        printf("No cities available.\n");
        return;
    }

    int option;
    while (1) {
        printf("Select the source:\n");
        for (int i = 0; i < countplaces; i++) {
            printf("%d. %s\n", i + 1, city_list[i].cities);
        }
        printf("Choice: ");
        if (scanf("%d", &option) != 1 || option < 1 || option > countplaces) {
            while (getchar() != '\n');
            printf("Error: Please select a valid option.\n");
            continue;
        }
        getchar();
        break;
    }

    printf("%s\n", city_list[option - 1].cities);
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    printf("%75s\n", "---------------------------------------------------------------------------");

    int found = 0;
    for (int i = 0; i < countflight; i++) {
        if (strcmp(city_list[option - 1].cities, flights[i].source) == 0) {
            found = 1;
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f\n",
                   flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                   flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
        }
    }
    if (!found) {
        printf("\t\t\tNO FLIGHTS FROM THIS SOURCE\n");
    }
    printf("%75s\n", "---------------------------------------------------------------------------");
}

// Display flights from source to destination
void display_flights_source_to_destination() {
    if (countplaces == 0 || countflight == 0) {
        printf("No cities or flights available.\n");
        return;
    }

    int src_option, dst_option;
    while (1) {
        printf("Select the source:\n");
        for (int i = 0; i < countplaces; i++) {
            printf("%d. %s\n", i + 1, city_list[i].cities);
        }
        printf("Choice: ");
        if (scanf("%d", &src_option) != 1 || src_option < 1 || src_option > countplaces) {
            while (getchar() != '\n');
            printf("Error: Please select a valid option.\n");
            continue;
        }
        getchar();
        break;
    }
    printf("%s\n", city_list[src_option - 1].cities);

    while (1) {
        printf("Select the destination:\n");
        int j = 1;
        for (int i = 0; i < countplaces; i++) {
            if (strcmp(city_list[src_option - 1].cities, city_list[i].cities) != 0) {
                printf("%d. %s\n", j++, city_list[i].cities);
            }
        }
        printf("Choice: ");
        if (scanf("%d", &dst_option) != 1 || dst_option < 1 || dst_option >= countplaces) {
            while (getchar() != '\n');
            printf("Error: Please select a valid option.\n");
            continue;
        }
        getchar();

        // Map dst_option to actual city index
        int actual_dst = 0, current = 1;
        for (int i = 0; i < countplaces; i++) {
            if (strcmp(city_list[src_option - 1].cities, city_list[i].cities) != 0) {
                if (current == dst_option) {
                    actual_dst = i;
                    break;
                }
                current++;
            }
        }
        if (actual_dst == src_option - 1) {
            printf("Source and destination cannot be the same.\n");
            continue;
        }
        dst_option = actual_dst + 1;
        break;
    }
    printf("%s\n", city_list[dst_option - 1].cities);

    // Direct flights
    printf("\n%40s\n", "DIRECT FLIGHTS");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    printf("%75s\n", "---------------------------------------------------------------------------");

    int direct_found = 0;
    for (int i = 0; i < countflight; i++) {
        if (strcmp(city_list[src_option - 1].cities, flights[i].source) == 0 &&
            strcmp(city_list[dst_option - 1].cities, flights[i].destination) == 0) {
            direct_found = 1;
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f\n",
                   flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                   flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
        }
    }
    if (!direct_found) {
        printf("\t\t\tNO DIRECT FLIGHTS ):\n");
    }
    printf("%75s\n", "---------------------------------------------------------------------------");

    // Indirect flights
    printf("\n%40s\n", "INDIRECT FLIGHTS");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    printf("%75s\n", "---------------------------------------------------------------------------");

    int indirect_found = 0, cheap_count = 0;
    float min_fare = 1e9;
    int min_index = 0;
    for (int i = 0; i < countflight && cheap_count < 10; i++) {
        for (int j = 0; j < countflight; j++) {
            if (strcmp(city_list[src_option - 1].cities, flights[i].source) == 0 &&
                strcmp(flights[j].source, flights[i].destination) == 0 &&
                strcmp(city_list[dst_option - 1].cities, flights[j].destination) == 0) {
                indirect_found = 1;
                float total_fare = flights[i].fare + flights[j].fare;
                float total_time = flights[i].flightTime + flights[j].flightTime;

                printf("**FLIGHT 1**\n\n");
                printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f\n",
                       flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                       flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
                printf("\n**FLIGHT 2**\n\n");
                printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f\n",
                       flights[j].flightID, flights[j].source, flights[j].arrivalTime,
                       flights[j].destination, flights[j].departureTime, flights[j].flightTime, flights[j].fare);
                printf("\nTOTAL TIME = %.2f hours\n", total_time);
                printf("TOTAL FARE = Rs. %.2f\n", total_fare);
                printf("%75s\n", "---------------------------------------------------------------------------");

                // Store in cheapflight array
                cheapflight[cheap_count].fare = total_fare;
                strcpy(cheapflight[cheap_count].source, flights[i].source);
                strcpy(cheapflight[cheap_count].stop, flights[i].destination);
                strcpy(cheapflight[cheap_count].destination, flights[j].destination);
                strcpy(cheapflight[cheap_count].flightID1, flights[i].flightID);
                strcpy(cheapflight[cheap_count].flightID2, flights[j].flightID);
                if (total_fare < min_fare) {
                    min_fare = total_fare;
                    min_index = cheap_count;
                }
                cheap_count++;
            }
        }
    }

    if (!indirect_found) {
        printf("\t\t\tNO INDIRECT FLIGHTS ):\n");
    } else if (cheap_count > 0) {
        printf("\n%40s\n", "CHEAPEST INDIRECT FLIGHT");
        printf("%75s\n", "---------------------------------------------------------------------------");
        printf("\nFLIGHT IDs: %s, %s\n", cheapflight[min_index].flightID1, cheapflight[min_index].flightID2);
        printf("CHECKPOINTS: %s -> %s -> %s\n", cheapflight[min_index].source,
               cheapflight[min_index].stop, cheapflight[min_index].destination);
        printf("FARE = Rs. %.2f\n", cheapflight[min_index].fare);
    }
    printf("%75s\n", "---------------------------------------------------------------------------");
}
