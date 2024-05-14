#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Room {
    int roomID;
    int status;
    char customerName[20];
} Room;

typedef struct Rooms {
    Room values[5];
    size_t length;
} Rooms;


int compare_room(const void *a, const void *b) {
    return ((Room*) a)->roomID - ((Room*) b)->roomID;
}

void sort(Rooms *const rooms) {
    qsort(rooms->values, rooms->length, sizeof(Room), compare_room);
}


void read(char *const in) {
    fgets(in, 20, stdin);
    in[strcspn(in, "\r\n")] = 0;
}

void to_lower(const char in[20], char out[20]) {
    strcpy(out, in);
    size_t i = 0;
    for(; out[i] != '\0'; i++) {
        out[i] = tolower(in[i]);
    }
}

void print_room(const Room *const room) {
    printf("roomID: %d\n", room->roomID);
    printf("customer name: %s\n", room->customerName);
}


void listOccupiedRooms(const Rooms *const rooms) {
    printf("listOccupiedRooms():\n");

    if (rooms->length == 0) {
        printf("The hotel is empty\n");
        return;
    }

    size_t i = 0;
    for (; i < rooms->length; i++) {
        print_room(&rooms->values[i]);
    }
}

void assignRoom(Rooms *const rooms) {
    printf("assignRoom():\n");
    Room room = {};
    while(1){
    if (rooms->length == 5) {
        printf("The hotel is full\n");
        return;}

    int buffer;

    while (1){
            ask:
                printf("Enter a roomID between 1 and 5: \n");
                scanf("%d", &buffer);
        if (buffer >= 1 && buffer <= 5){
                room.roomID = buffer;
                size_t i = 0;
                for (; i < rooms->length; i++) {
                    if (room.roomID == rooms->values[i].roomID) {
                        printf("Occupied! Enter another roomID\n");
                        goto ask;
                    }
                }
    break;
    }
    else {
        continue;
    }
    }

    printf("Enter customer name:\n");
    scanf("\n");
    read(room.customerName);
    rooms->values[rooms->length] = room;
    rooms->length++;
    sort(rooms);
    printf("The room has been assigned successfully\n");
    break;
}
}

void removeRoom(Rooms *const rooms) {
    printf("removeRoom():\n");
    while(1){
    int target;
    if (rooms->length == 0) {
        printf("All the rooms are empty\n");
        return;
    }
    while (1){
    printf("Enter a roomID between 1 and 5: \n");
    scanf("%d", &target);
        if (target >= 1 && target <= 5){
            break;
        }
        else{
            continue;
        }
    }
    size_t i = 0;
    for (; i < rooms->length; i++) {
        Room room = rooms->values[i];
        if (room.roomID == target) {
            size_t current = i;
            size_t next = i + 1;
            for (; next < rooms->length; current++, next++) {
                rooms->values[current] = rooms->values[next];
            }
            rooms->length--;

            printf("Removal is successful\n");

            return;
        }
    }

    printf("Empty! Enter another roomID for removal\n");
    continue;

break;
}
}

void findCustomer(Rooms *const rooms) {
    printf("findCustomer():\n");
    printf("Enter customer name:\n");
    char target[20];
    scanf("\n");
    read(target);
    to_lower(target, target);

    size_t i = 0;
    for (; i < rooms->length; i++) {
        Room room = rooms->values[i];
        char customerName[20];
        to_lower(room.customerName, customerName);
        if (strcmp(target, customerName) == 0) {
            printf( "The target customer name is found\n");
            print_room(&room);
            return;
        }
    }

    printf("The target customer name is not found\n");
}


int main() {
    Rooms rooms = { .length = 0 };

    printf("NTU HOTEL ROOM RESERVATION PROGRAM: \n"
           "1: listOccupiedRooms() \n"
           "2: assignRoom() \n"
           "3: removeRoom() \n"
           "4: findCustomer() \n"
           "5: quit\n"
    );

    while (true) {
        printf("Enter your choice: \n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listOccupiedRooms(&rooms);
                break;
            case 2:
                assignRoom(&rooms);
                break;
            case 3:
                removeRoom(&rooms);
                break;
            case 4:
                findCustomer(&rooms);
                break;
            default:
                return 0;
        }
    }
}