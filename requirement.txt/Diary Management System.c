#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int choice;
    char date[15],location[50],subject[100],description[10000],search[50],line[15000],input_pass[70];
    FILE *fp;

  for(int i=1;i<=3;i++){
      system("cls || clear");// NEW PAGE
      if(i!=1){
        printf("\nWrong PIN! Try Again.\n");
      }
    printf("\nEnter PIN To Access: ");
    fgets(input_pass, sizeof(input_pass), stdin); // TAKING PIN AND CLEARING NEW LINE TO ENTER
    input_pass[strcspn(input_pass, "\n")] = '\0';
    if(strcmp(input_pass,"CSE115")==0){
    while (1) {
        system("cls || clear");
        printf("\n======= MY Diary =======\n");
        printf("\n1.Write a Note");
        printf("\n2.Search and Read Notes");
        printf("\n3.Exit");
        printf("\n\nChoose One Number:");

        choice = 0;
        scanf("%d", &choice);// TAKING USER CHOICE AND CLEARING THE EXTRA 'ENTER' FROM BUFFER
        while (getchar()!='\n');

        switch (choice) {

        case 1:
            system("cls || clear");
            fp = fopen("diary.txt", "a");// OPEN FILE IN 'APPEND' MODE TO ADD DATA WITHOUT DELETING OLD NOTES

            printf("\nDate [DD/MM/YYYY]:");
            fgets(date, sizeof(date), stdin);// fgets() CAPTURES THE WHOLE LINE INCLUDING SPACES
            date[strcspn(date, "\n")] = '\0';

            printf("\nLocation:");
            fgets(location, sizeof(location), stdin);
            location[strcspn(location, "\n")] = '\0';

            printf("\nTopic:");
            fgets(subject, sizeof(subject), stdin);
            subject[strcspn(subject, "\n")] = '\0';

            printf("\nEnter Note:");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = '\0';

            fprintf(fp, "%s | %s | %s | %s\n", date, location, subject, description);// WRITING DATA TO FILE WITH '|' SEPARATOR TO DISTINGUISH FIELDS LATER
            fclose(fp); // ALWAYS CLOSE THE FILE TO SAVE PROGRESS
            printf("\nPress Enter to Continue.....");
            getchar();
            break;

        case 2:
            system("cls || clear");
            fp = fopen("diary.txt", "r");// OPEN FILE IN 'READ' MODE

            if (fp == NULL) {
                printf("\nDiary is empty.\n");
                printf("\nPress Enter to Continue.....");
                getchar();
                break;
            }

            printf("\nPress Enter to View All....");
            printf("\n\nOr Enter Search Term: ");
            fgets(search, sizeof(search), stdin);// GETTING THE DATE FROM USER TO SEARCH
            search[strcspn(search, "\n")] = '\0';

            int found = 0; // READING EVERY LINE FROM FILE UNTILL THE END (EOF)
            while (fgets(line, sizeof(line), fp)) {// IF LINE CONTAINS THE SEARCHED STRING
                if (strlen(search)==0 || strstr(line, search) != NULL) {// strstr() CHECKS IF THE SEARCH STRING EXISTS INSIDE THE CURRENT LINE
                    printf("\n%s", line);// DISPLAYING THE MATCHING LINE
                    found = 1;
                }
            }
            if (found == 0)
            printf("\nNot found!\n");
            fclose(fp);// CLOSING FILE AFTER READING
            printf("\nPress Enter to Continue.....");
            getchar();
            break;

        case 3:// TERMINATING THE INFINITE WHILE LOOP
            system("cls || clear");
            printf("\nGoodbye!\n");
            return 0;

        default://WRONG NUMBER
            system("cls || clear");
            printf("\nWrong Choice, Try Again\n");
            printf("\nPress Enter to Continue.....");
            getchar();
        }
    }
    return 0;
   }
  }
  if(strcmp(input_pass,"CSE115")!=0) {
    system("cls || clear");
    printf("\nWrong PIN! Closing program...\n");// WRONG PASSWORD
    return 0;
}
}
