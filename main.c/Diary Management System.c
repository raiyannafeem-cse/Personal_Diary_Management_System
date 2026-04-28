#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int choice;
    char date[15],location[50],subject[100],description[10000],search[50],line[15000],input_pass[70],pass[70];
    FILE *fp ,*password;


   password=fopen("pass.txt","r");
   if(password==NULL){
        password=fopen("pass.txt","a");
        printf("\n  =================================== WELCOME TO PERSONAL DIARY MANAGEMENT SYSTEM ===================================\n\n");
        printf("\n  Set a Password To Sign Up: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = '\0';
        fprintf(password, "%s\n", pass);
        fclose(password);
    }
   else {
        fgets(pass, sizeof(pass), password);
        pass[strcspn(pass, "\n")] = '\0';
        fclose(password);
    }

  for(int i=1;i<=3;i++){
      system("cls || clear");// NEW PAGE
      printf("\n  =================================== WELCOME TO PERSONAL DIARY MANAGEMENT SYSTEM ===================================\n\n");
      if(i!=1){
        printf("\n  Wrong PIN! Try Again.\n");
      }
    printf("\n  Enter Your Password To Sign In: ");
    fgets(input_pass, sizeof(input_pass), stdin); // TAKING PIN AND CLEARING NEW LINE TO ENTER
    input_pass[strcspn(input_pass, "\n")] = '\0';
    if(strcmp(input_pass,pass)==0){
    while (1) {
        system("cls || clear");
        printf("\n  ====================== MY Diary ======================\n");
        printf("\n  1.Write a Note");
        printf("\n  2.Search and Read Notes");
        printf("\n  3.Exit");
        printf("\n\n  Choose One Number:");

        choice = 0;
        scanf("%d", &choice);// TAKING USER CHOICE AND CLEARING THE EXTRA 'ENTER' FROM BUFFER
        while (getchar()!='\n');

        switch (choice) {

        case 1:
            system("cls || clear");
            printf("\n  ====================== Write Notes ======================\n");
            fp = fopen("diary.txt", "a");// OPEN FILE IN 'APPEND' MODE TO ADD DATA WITHOUT DELETING OLD NOTES

            printf("\n  Date [DD/MM/YYYY]:");
            fgets(date, sizeof(date), stdin);// fgets() CAPTURES THE WHOLE LINE INCLUDING SPACES
            date[strcspn(date, "\n")] = '\0';

            printf("\n  Location:");
            fgets(location, sizeof(location), stdin);
            location[strcspn(location, "\n")] = '\0';

            printf("\n  Topic:");
            fgets(subject, sizeof(subject), stdin);
            subject[strcspn(subject, "\n")] = '\0';

            printf("\n  Enter Note:");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = '\0';

            fprintf(fp, "%s | %s | %s | %s\n", date, location, subject, description);// WRITING DATA TO FILE WITH '|' SEPARATOR TO DISTINGUISH FIELDS LATER
            fclose(fp); // ALWAYS CLOSE THE FILE TO SAVE PROGRESS
            printf("\n  Press Enter to Continue.....");
            getchar();
            break;

        case 2:
            system("cls || clear");
            printf("\n  ====================== Search And Read ======================\n");
            fp = fopen("diary.txt", "r");// OPEN FILE IN 'READ' MODE

            if (fp == NULL) {
                printf("\n  Diary is empty.\n");
                printf("\n  Press Enter to Continue.....");
                getchar();
                break;
            }

            printf("\n  Press Enter to View All....");
            printf("\n\n  Or Enter Search Term: ");
            fgets(search, sizeof(search), stdin);// GETTING THE DATE FROM USER TO SEARCH
            search[strcspn(search, "\n")] = '\0';

            int found = 0; // READING EVERY LINE FROM FILE UNTILL THE END (EOF)
            while (fgets(line, sizeof(line), fp)) {// IF LINE CONTAINS THE SEARCHED STRING
                if (strlen(search)==0 || strstr(line, search) != NULL) {// strstr() CHECKS IF THE SEARCH STRING EXISTS INSIDE THE CURRENT LINE
                    printf("\n  %s", line);// DISPLAYING THE MATCHING LINE
                    found = 1;
                }
            }
            if (found == 0)
            printf("\n  Not found!\n");
            fclose(fp);// CLOSING FILE AFTER READING
            printf("\n  Press Enter to Continue.....");
            getchar();
            break;

        case 3:// TERMINATING THE INFINITE WHILE LOOP
            system("cls || clear");
            printf("\n  ====================== Exit ======================\n");
            printf("\n  Goodbye!\n");
            return 0;

        default://WRONG NUMBER
            system("cls || clear");
            printf("\n  Wrong Choice, Try Again\n");
            printf("\n  Press Enter to Continue.....");
            getchar();
        }
    }
    return 0;
   }
  }
  if(strcmp(input_pass,"CSE115")!=0) {
    system("cls || clear");
    printf("\n  ====================== MY Diary ======================\n");
    printf("\n  Wrong PIN! Closing program...\n");// WRONG PASSWORD
    return 0;
}
}
