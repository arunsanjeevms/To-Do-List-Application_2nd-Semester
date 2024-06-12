#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 101

typedef struct Task {
    char description[MAX_STRING_LENGTH];
    struct Task *next;
} Task;

void viewTasks(Task *head) {
    Task *current = head;
    int index = 1;
    while (current != NULL) {
        printf("\n %2d  ➠  %s\n", index++, current->description);
        current = current->next;
    }
}

void addTask(Task **head, int position, const char *description) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    strncpy(newTask->description, description, MAX_STRING_LENGTH);
    newTask->description[MAX_STRING_LENGTH - 1] = '\0';
    newTask->next = NULL;

    if (position == 1) {
        newTask->next = *head;
        *head = newTask;
        return;
    }

    Task *current = *head;
    for (int i = 1; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid position!\n");
        free(newTask);
    } else {
        newTask->next = current->next;
        current->next = newTask;
    }
}

void deleteTask(Task **head, int position) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Task *temp = *head;

    if (position == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    Task *prev = NULL;
    for (int i = 1; i < position && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
    } else {
        prev->next = temp->next;
        free(temp);
    }
}

void saveTasks(Task *head) {
    FILE *f = fopen("list.bin", "w");
    Task *current = head;
    while (current != NULL) {
        fwrite(current->description, sizeof(char), MAX_STRING_LENGTH, f);
        current = current->next;
    }
    fclose(f);
}

void loadTasks(Task **head) {
    FILE *f = fopen("list.bin", "r");
    if (f == NULL) return;

    char description[MAX_STRING_LENGTH];
    while (fread(description, sizeof(char), MAX_STRING_LENGTH, f) == MAX_STRING_LENGTH) {
        addTask(head, 1, description);
    }
    fclose(f);
}

int main() {
    int input;
    Task *head = NULL;

    loadTasks(&head);

    while (1) {
        printf("\n﹌﹌﹌﹌﹌﹌﹌﹌﹌ 𝐓𝐎 - 𝐃𝐎 𝐋𝐈𝐒𝐓 𝐀𝐏𝐏𝐋𝐈𝐂𝐀𝐓𝐈𝐎𝐍 ﹌﹌﹌﹌﹌﹌﹌﹌﹌\n\n");
        printf("  - Please Select a Option Below  - \n");
        printf("1. View To-Do List \n");
        printf("2. Add Task \n");
        printf("3. Delete Task \n");
        printf("4. Exit\n\n");

        scanf("%d", &input);

        if (input == 4) {
            saveTasks(head);
            while (head != NULL) {
                Task *temp = head;
                head = head->next;
                free(temp);
            }
            return EXIT_SUCCESS;
        } else if (input == 1 || input == 2 || input == 3) {
            switch (input) {
                case 1:
                    viewTasks(head);
                    break;
                case 2: {
                    printf("Please Enter the position you would like to add the task at: ");
                    int position;
                    scanf("%d", &position);
                    printf("Task Description: ");
                    getchar();
                    char description[MAX_STRING_LENGTH];
                    fgets(description, MAX_STRING_LENGTH, stdin);
                    description[strcspn(description, "\n")] = '\0'; // Remove newline character
                    addTask(&head, position, description);
                    break;
                }
                case 3: {
                    printf("Please Enter the position you would like to remove: ");
                    int position;
                    scanf("%d", &position);
                    deleteTask(&head, position);
                    break;
                }
            }
        } else {
            printf("Please enter 1, 2, 3, or 4...\n");
        }
    }

    return EXIT_SUCCESS;
}
