#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STRING_LENGTH 101
#define MAX_TODO 5


int main() {
    int input;
    int loop;
    FILE *f;

    char list[MAX_TODO][MAX_STRING_LENGTH] = {};
   
    
    while(1){
    
    printf("\n﹌﹌﹌﹌﹌﹌﹌﹌﹌ 𝐓𝐎  - 𝐃𝐎  𝐋𝐈𝐒𝐓 𝐀𝐏𝐏𝐋𝐈𝐂𝐀𝐓𝐈𝐎𝐍 ﹌﹌﹌﹌﹌﹌﹌﹌﹌\n\n");
   // printf("You will lose all your todos!\n\n");
    printf("  - Please Select a Option Below  - \n");
    printf("1. View To-Do List \n");
    printf("2. Add Task \n");
    printf("3. Delete Task \n");
    printf("4. Exit\n\n");

    scanf("%d", &input);
    

    if(input == 4){
        f = fopen("list.bin", "w");
        fwrite(list, sizeof(char), sizeof(list), f);
        fclose(f);
        return EXIT_SUCCESS;
    }else if (input == 1 || input == 2 || input == 3){
        switch(input){
            case 1:
                for (int loop = 0; loop < MAX_TODO; loop++)
                {
                    printf("\n %2d  ➠  %s\n", loop + 1, list[loop]);
                }  
                break;
            case 2:
                printf("Please Enter the number you would like to Add : ");
                int j;
                
                scanf("%d", &j);
                printf("Task Description : ");
                getchar();
                scanf("%[^\n]", list[j - 1]);
                break;
            case 3:
                printf("Please Enter the number you would like to remove: ");
                int k;
                scanf("%d", &k);
                
                strncpy(list[k-1], " ", 101);
                
                printf("[%d] ---> DELETED!!!", k);
                break;           
        }
    }else {
        printf("Please enter 1, 2, 3, or 4...\n");
    }

    }

return EXIT_SUCCESS;
}