#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROUTES 8
#define MAX_DAYS 3
#define MAX_TIMES 10
#define MAX_SEATS 40

typedef struct
{
    int isBooked;
    char name[50];
    char id[20];
    char phone[15];
} Seat;

typedef struct
{
    char routeName[50];
    char days[MAX_DAYS][3];
    char times[MAX_DAYS][MAX_TIMES][10];
    Seat seats[MAX_DAYS][MAX_TIMES][MAX_SEATS];
} BusRoute;

void clearBuffer()
{
    while (getchar() != '\n');
}

void initializeRoutes(BusRoute *routes)
{

    char *routeName[] = {
        "Uttara to NSU", "NSU to Uttara", "Dhanmondi to NSU", "NSU to Dhanmondi",
        "Mirpur to NSU", "NSU to Mirpur", "Banani to NSU", "NSU to Banani"};

    char *days[] = {"ST", "MW", "RA"};

    char *times[] = {
        "08:00", "09:00", "10:00", "11:00", "12:00",
        "13:00", "14:00", "15:00", "16:00", "17:00"};

    for (int i = 0; i < MAX_ROUTES; i++)
    {
        strcpy(routes[i].routeName, routeName[i]);

        for (int j = 0; j < MAX_DAYS; j++)
        {
            strcpy(routes[i].days[j], days[j]);

            for (int k = 0; k < MAX_TIMES; k++)
            {
                strcpy(routes[i].times[j][k], times[k]);

                for (int s = 0; s < MAX_SEATS; s++)
                {
                    routes[i].seats[j][k][s].isBooked = 0;
                    strcpy(routes[i].seats[j][k][s].name, "");
                    strcpy(routes[i].seats[j][k][s].id, "");
                    strcpy(routes[i].seats[j][k][s].phone, "");
                }
            }
        }
    }
}

void viewSeats(BusRoute *route, int dayIndex, int timeIndex)
{
    printf("\nSeat Status for Route %s at %s on %s:\n", route->routeName, route->times[dayIndex][timeIndex], route->days[dayIndex]);
    for (int i = 0; i < MAX_SEATS; i++)
    {
        if (i % 4 == 0)
            printf("\n"); 
        if (i % 4 == 2)
            printf("   "); 

        if (route->seats[dayIndex][timeIndex][i].isBooked)
        {
            printf("\033[1;31m%2d\033[0m ", i + 1); 
        }
        else
        {
            printf("\033[1;32m%2d\033[0m ", i + 1); 
        }
    }
    printf("\n");
}

void OPviewSeats(BusRoute *routes)
{
    int routeIndex, dayIndex, timeIndex;
    printf("\nAvailable Routes:\n");
    for (int i = 0; i < MAX_ROUTES; i++)
    {
        printf("%d. %s\n", i + 1, routes[i].routeName);
    }
    printf("Select a route (1-%d): ", MAX_ROUTES);
    scanf("%d", &routeIndex);
    clearBuffer(); 
    routeIndex--;

    if (routeIndex < 0 || routeIndex >= MAX_ROUTES)
    {
        printf("Invalid route selection.\n");
        return;
    }

    BusRoute *route = &routes[routeIndex];

    printf("\nSelect a day for Route %s:\n", route->routeName);
    for (int i = 0; i < MAX_DAYS; i++)
    {
        printf("%d. %s\n", i + 1, route->days[i]);
    }
    printf("Select a day (1-%d): ", MAX_DAYS);
    scanf("%d", &dayIndex);
    clearBuffer(); 
    dayIndex--;

    if (dayIndex < 0 || dayIndex >= MAX_DAYS)
    {
        printf("Invalid day selection.\n");
        return;
    }

    printf("\nAvailable Times for Route %s on %s:\n", route->routeName, route->days[dayIndex]);
    for (int i = 0; i < MAX_TIMES; i++)
    {
        printf("%d. %s\n", i + 1, route->times[dayIndex][i]);
    }
    printf("Select a time (1-%d): ", MAX_TIMES);
    scanf("%d", &timeIndex);
    clearBuffer();
    timeIndex--;

    if (timeIndex < 0 || timeIndex >= MAX_TIMES)
    {
        printf("Invalid time selection.\n");
        return;
    }

    viewSeats(route, dayIndex, timeIndex);
}

void bookSeat(BusRoute *routes)
{
    int routeIndex, dayIndex, timeIndex, seatNumber;

    printf("\nAvailable Routes:\n");
    for (int i = 0; i < MAX_ROUTES; i++)
    {
        printf("%d. %s\n", i + 1, routes[i].routeName);
    }
    printf("Select a route (1-%d): ", MAX_ROUTES);
    scanf("%d", &routeIndex);
    clearBuffer();
    routeIndex--;

    if (routeIndex < 0 || routeIndex >= MAX_ROUTES)
    {
        printf("Invalid route selection.\n");
        return;
    }

    BusRoute *route = &routes[routeIndex];

    printf("\nSelect a day for Route %s:\n", route->routeName);
    for (int i = 0; i < MAX_DAYS; i++)
    {
        printf("%d. %s\n", i + 1, route->days[i]);
    }
    printf("Select a day (1-%d): ", MAX_DAYS);
    scanf("%d", &dayIndex);
    clearBuffer();
    dayIndex--;

    if (dayIndex < 0 || dayIndex >= MAX_DAYS)
    {
        printf("Invalid day selection.\n");
        return;
    }

    printf("\nAvailable Times for Route %s on %s:\n", route->routeName, route->days[dayIndex]);
    for (int i = 0; i < MAX_TIMES; i++)
    {
        printf("%d. %s\n", i + 1, route->times[dayIndex][i]);
    }

    printf("Select a time (1-%d): ", MAX_TIMES);
    scanf("%d", &timeIndex);
    clearBuffer();
    timeIndex--;

    if (timeIndex < 0 || timeIndex >= MAX_TIMES)
    {
        printf("Invalid time selection.\n");
        return;
    }

    viewSeats(route, dayIndex, timeIndex);

    printf("\nEnter seat number to book: ");
    scanf("%d", &seatNumber);
    clearBuffer();

    if (seatNumber < 1 || seatNumber > MAX_SEATS)
    {
        printf("Invalid seat number.\n");
        return;
    }

    Seat *seat = &route->seats[dayIndex][timeIndex][seatNumber - 1];
    if (seat->isBooked)
    {
        printf("Seat %d is already booked by %s.\n", seatNumber, seat->name);
    }
    else
    {
        printf("Enter your name: ");
        fgets(seat->name, sizeof(seat->name), stdin);
        seat->name[strcspn(seat->name, "\n")] = 0;

        printf("Enter your ID: ");
        fgets(seat->id, sizeof(seat->id), stdin);
        seat->id[strcspn(seat->id, "\n")] = 0;

        printf("Enter your phone number: ");
        fgets(seat->phone, sizeof(seat->phone), stdin);
        seat->phone[strcspn(seat->phone, "\n")] = 0;

        seat->isBooked = 1;
        printf("Seat %d booked successfully on route %s at %s on %s!\n", seatNumber, route->routeName, route->times[dayIndex][timeIndex], route->days[dayIndex]);
    }
}

void cancelBooking(BusRoute *routes)
{
    int routeIndex, dayIndex, timeIndex, seatNumber;

    printf("\nAvailable Routes:\n");
    for (int i = 0; i < MAX_ROUTES; i++)
    {
        printf("%d. %s\n", i + 1, routes[i].routeName);
    }
    printf("Select a route (1-%d): ", MAX_ROUTES);
    scanf("%d", &routeIndex);
    clearBuffer();
    routeIndex--;

    if (routeIndex < 0 || routeIndex >= MAX_ROUTES)
    {
        printf("Invalid route selection.\n");
        return;
    }

    BusRoute *route = &routes[routeIndex];

    printf("\nSelect a day for Route %s:\n", route->routeName);
    for (int i = 0; i < MAX_DAYS; i++)
    {
        printf("%d. %s\n", i + 1, route->days[i]);
    }
    printf("Select a day (1-%d): ", MAX_DAYS);
    scanf("%d", &dayIndex);
    clearBuffer();
    dayIndex--;

    if (dayIndex < 0 || dayIndex >= MAX_DAYS)
    {
        printf("Invalid day selection.\n");
        return;
    }

    printf("\nAvailable Times for Route %s on %s:\n", route->routeName, route->days[dayIndex]);
    for (int i = 0; i < MAX_TIMES; i++)
    {
        printf("%d. %s\n", i + 1, route->times[dayIndex][i]);
    }
    printf("Select a time (1-%d): ", MAX_TIMES);
    scanf("%d", &timeIndex);
    clearBuffer();
    timeIndex--;

    if (timeIndex < 0 || timeIndex >= MAX_TIMES)
    {
        printf("Invalid time selection.\n");
        return;
    }

    viewSeats(route, dayIndex, timeIndex);

    printf("\nEnter seat number to cancel booking: ");
    scanf("%d", &seatNumber);
    clearBuffer();

    if (seatNumber < 1 || seatNumber > MAX_SEATS)
    {
        printf("Invalid seat number.\n");
        return;
    }

    Seat *seat = &route->seats[dayIndex][timeIndex][seatNumber - 1];
    if (!seat->isBooked)
    {
        printf("Seat %d is not booked.\n", seatNumber);
    }
    else
    {
        seat->isBooked = 0;
        printf("Booking for seat %d on route %s at %s on %s has been canceled.\n", seatNumber, route->routeName, route->times[dayIndex][timeIndex], route->days[dayIndex]);
    }
}

void saveToFile(BusRoute *routes)
{
    FILE *file = fopen("bus_booking_details.txt", "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file for saving data.\n");
        return;
    }

    // Iterate over all routes
    for (int i = 0; i < MAX_ROUTES; i++)
    {
        fprintf(file, "Route: %s\n", routes[i].routeName);

        for (int j = 0; j < MAX_DAYS; j++)
        {
            fprintf(file, "  Day: %s\n", routes[i].days[j]);

            for (int k = 0; k < MAX_TIMES; k++)
            {
                fprintf(file, "    Time: %s\n", routes[i].times[j][k]);
                fprintf(file, "      Bookings:\n");

                for (int s = 0; s < MAX_SEATS; s++)
                {
                    if (routes[i].seats[j][k][s].isBooked)
                    {
                        Seat *seat = &routes[i].seats[j][k][s];
                        fprintf(file, "        Seat %d: Name: %s, ID: %s, Phone: %s\n",
                                s + 1, seat->name, seat->id, seat->phone);
                    }
                }
            }
        }
    }

    fclose(file);
    printf("Booking details successfully saved to 'bus_booking_details.txt'.\n");
}

int main()
{
    BusRoute routes[MAX_ROUTES];

    initializeRoutes(routes);

    int choice;
    do
    {
        printf("\n1. View Seats\n2. Book Seat\n3. Cancel Booking\n4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        clearBuffer(); 

        switch (choice)
        {
        case 1:
        {
            OPviewSeats(routes);
            break;
        }
        case 2:
            bookSeat(routes);
            break;
        case 3:
            cancelBooking(routes);
            break;
        case 4:
            printf("Exiting Program...\nHappy Wheelz :)\n");
            saveToFile(routes);
           
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
