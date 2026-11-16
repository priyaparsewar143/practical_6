#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node
{
    int seat;
    Node *prev;
    Node *next;
};

Node *head[10] = {NULL};

// Insert available seat
void insertSeat(int row, int seat)
{
    Node *newNode = new Node;
    newNode->seat = seat;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head[row] == NULL)
    {
        head[row] = newNode;
        return;
    }

    Node *temp = head[row];

    while (temp != NULL && temp->seat < seat)
    {
        temp = temp->next;
    }

    if (temp == head[row])
    {
        newNode->next = head[row];
        head[row]->prev = newNode;
        head[row] = newNode;
    }
    else if (temp == NULL)
    {
        Node *last = head[row];

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = newNode;
        newNode->prev = last;
    }
    else
    {
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
    }
}

// Book a seat
bool bookSeat(int row, int seat)
{
    Node *temp = head[row];

    while (temp != NULL && temp->seat != seat)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return false;
    }

    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        head[row] = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    delete temp;
    return true;
}

// Display available seats
void displaySeats()
{
    cout << "\nAvailable Seats:\n";

    for (int i = 0; i < 10; i++)
    {
        cout << "Row " << i + 1 << ": ";

        Node *temp = head[i];

        if (temp == NULL)
        {
            cout << "No seats available";
        }

        while (temp != NULL)
        {
            cout << temp->seat << " ";
            temp = temp->next;
        }

        cout << endl;
    }
}

// Book a seat
void booking()
{
    int row, seat;

    cout << "Enter row number (1-10): ";
    cin >> row;

    cout << "Enter seat number (1-7): ";
    cin >> seat;

    if (row < 1 || row > 10 || seat < 1 || seat > 7)
    {
        cout << "Invalid seat or row number!\n";
        return;
    }

    if (bookSeat(row - 1, seat))
    {
        cout << "Seat booked successfully!\n";
    }
    else
    {
        cout << "Seat is already booked!\n";
    }
}

// Cancel booking
void cancelBooking()
{
    int row, seat;

    cout << "Enter row number (1-10): ";
    cin >> row;

    cout << "Enter seat number (1-7): ";
    cin >> seat;

    if (row < 1 || row > 10 || seat < 1 || seat > 7)
    {
        cout << "Invalid seat or row number!\n";
        return;
    }

    Node *temp = head[row - 1];

    while (temp != NULL && temp->seat != seat)
    {
        temp = temp->next;
    }

    if (temp != NULL)
    {
        cout << "Seat is not booked!\n";
    }
    else
    {
        insertSeat(row - 1, seat);
        cout << "Booking cancelled successfully!\n";
    }
}

// Initialize seats
void initialize()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            insertSeat(i, j);
        }
    }

    srand(time(0));

    int count = 0;

    while (count < 10)
    {
        int row = rand() % 10;
        int seat = rand() % 7 + 1;

        if (bookSeat(row, seat))
        {
            count++;
        }
    }
}

// Main function
int main()
{
    int choice;

    initialize();

    do
    {
        cout << "\n===== CINEMAX THEATRE BOOKING SYSTEM =====\n";
        cout << "1. Display Available Seats\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displaySeats();
                break;

            case 2:
                booking();
                break;

            case 3:
                cancelBooking();
                break;

            case 4:
                cout << "Thank you for using Cinemax!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    // Free memory
    for (int i = 0; i < 10; i++)
    {
        Node *temp = head[i];

        while (temp != NULL)
        {
            Node *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        head[i] = NULL;
    }

    return 0;
}
