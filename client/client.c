#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4442

int main(int argc, char *argv[]){

    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[1024]={0};
    char kred[1024]={0};
    char command[1024]={0};
    int permission = geteuid();
    char tipe[50]={0};
    char uname[50]={0};
    char kred_uname[100]={0};
    char dump1[50]={0};
    char dump2[50]={0};
    char database[120]={0};
    char user[120]={0};
    char password[100]={0};
    char table_cnt[1000]={0};
    char *potong={0};

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
    printf("[-]Error in connection.\n");
    exit(1);
    }
    printf("[+]Client Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
    printf("[-]Error in connection.\n");
    exit(1);
    }
    printf("[+]Connected to Server.\n");

    if (permission!=0){
        if( argc == 5 ) {
            printf("The argument supplied is %s and %s\n", argv[2],argv[4]);
            strcpy (kred,"login;");
            strcat(kred,argv[2]);
            strcpy(kred_uname,argv[2]);
            strcat (kred,":");
            strcat (kred,argv[4]);
            send(clientSocket, kred, strlen(kred), 0);
        }
        else if( argc > 5 ) {
            printf("Too many arguments supplied.\n");
            send(clientSocket, ":exit", strlen(":exit"), 0);
            close(clientSocket);
            printf("[-]Disconnected from server.\n");
            exit(1);
        }
        else {
            printf("Argument terlalu sedikit.\n");
            send(clientSocket, ":exit", strlen(":exit"), 0);
            close(clientSocket);
            printf("[-]Disconnected from server.\n");
            exit(1);
        }
    }
    else {
        send(clientSocket,"kosong", strlen("kosong"), 0);
    }

    recv(clientSocket, buffer, 1024, 0);

    if (strcmp(buffer,"bener")==0){
        while(1){
            printf("Client: \t");
            scanf("%s", command);
            bzero(buffer, sizeof(buffer));
            // if (permission==0 && strcmp(command,":exit")!=0){
            //     printf ("Sudo nih!\n");
            //     send(clientSocket, command, strlen(command), 0);
            // }

            // else if (permission!=0 && strcmp(command,":exit")!=0){
            //     printf ("Bukan sudo nih!\n");
            //     send(clientSocket, command, strlen(command), 0);
            // }

            //create start
            if (strcmp(command, "CREATE")==0){
                scanf("%s",tipe);
                //create user
                if(strcmp(tipe,"USER")==0){
                        scanf("%s",uname);
                        scanf("%s %s",dump1,dump2);
                        scanf("%s",password);
                        strcpy(buffer,"1 ");
                        strcat(buffer,uname);
                        strcat(buffer,":");
                        strcat(buffer,password);
                        potong = strtok(buffer,";");
                        strcpy(buffer,potong);
                        //check root
                        if (permission==0)
                            send(clientSocket, buffer, strlen(buffer), 0);
                        else
                            printf("Unauthorized\n");
                            continue;
                }
                //create user end
                //create database
                else if (strcmp(tipe,"DATABASE")==0){
                    scanf("%s",database);
                    potong = strtok(database,";");
                    strcpy(buffer,"4 ");
                    strcat(buffer,database);
                    strcat(buffer," ");
                    strcat(buffer,database);
                    if (permission==0){
                        strcat(buffer,":");
                        strcat(buffer,"sudo");
                    }
                    else{
                        strcat(buffer,":");
                        strcat(buffer,kred_uname);
                    }
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
                //create database end
                //create table
                else if (strcmp(tipe,"TABLE")==0){
                    scanf("%s",database);
                    gets(table_cnt);
                    potong = strtok(table_cnt,";");
                    strcpy(buffer,"5 ");
                    strcat(buffer,database);
                    strcat(buffer," ");
                    strcat(buffer, table_cnt);
                    // strcat(buffer," ; ");
                    // strcat(buffer,database);
                    // if (permission==0){
                    //     strcat(buffer,":");
                    //     strcat(buffer,"sudo");
                    // }
                    // else{
                    //     strcat(buffer,":");
                    //     strcat(buffer,kred_uname);
                    // }
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
                //create table end
            }
            //END CREATE
            //USE
            else if (strcmp(command, "USE")==0){
                scanf("%s",database);
                //sudo
                if (permission==0){
                    potong = strtok(database,";");
                    strcpy(buffer,"2 ");
                    strcat(buffer,"sudo ");
                    strcat(buffer,database);
                    send(clientSocket, buffer, strlen(buffer), 0);
                }
                //not sudo
                else{
                    strcpy(buffer,"2 ");
                    potong = strtok(database,";");
                    strcat(buffer,database);
                    strcat(buffer,":");
                    strcat(buffer,kred_uname);
                    strcat(buffer," ");
                    strcat(buffer,database);
                    send(clientSocket, buffer, strlen(buffer), 0);
                }
                bzero(buffer, sizeof(buffer));
                recv(clientSocket, buffer, 1024, 0);
                //printf ("\nbuffer_use : %s\n",buffer);
                if(strcmp(buffer,"use_bener")==0){
                    printf("use database : %s\n",database);
                }
                else if (strcmp(buffer,"use_salah")==0){
                    printf("unauthorized to use this database\n");
                }
                continue;
            }
            //END USE
            //GRANT permission
            else if (strcmp(command, "GRANT")==0){
                scanf("%s",dump1);
                scanf("%s",database);
                scanf("%s",dump2);
                scanf("%s",user);
                strcpy(buffer,"3 ");
                strcat(buffer,database);
                strcat(buffer,":");
                strcat(buffer,user);
                potong = strtok(buffer,";");
                strcpy(buffer,potong);
                if (permission==0)
                    send(clientSocket, buffer, strlen(buffer), 0);
                else
                    printf("Unauthorized\n");
                    continue;
            }
            //END GRANT
            //DROP
            else if (strcmp(command, "DROP")==0){
                scanf("%s",tipe);
                //drop database
                if (strcmp(tipe,"DATABASE")==0){
                    scanf("%s",database);
                    strcpy(buffer,"6 ");
                    strcat(buffer,database);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
                //end drop database
                //drop table
                else if (strcmp(tipe,"TABLE")==0){
                    scanf("%s",database);
                    strcpy(buffer,"7 ");
                    strcat(buffer,database);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
                //end drop table
                //drop table
                else if (strcmp(tipe,"COLUMN")==0){
                    char collumn[100];
                    scanf("%s",collumn);
                    scanf("%s",dump1);
                    scanf("%s",database);
                    strcpy(buffer,"8 ");
                    strcat(buffer,collumn);
                    strcat(buffer," ");
                    strcat(buffer,database);
                    //printf("%s\n",buffer);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    //printf("%s\n", collumn);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
                //end drop table
            }
            //END DROP
            //INSERT
            else if (strcmp(command, "INSERT")==0){
                scanf("%s",dump1);
                scanf("%s",database);
                gets(table_cnt);
                potong = strtok(table_cnt,";");
                strcpy(buffer,"9 ");
                strcat(buffer,database);
                strcat(buffer," ");
                strcat(buffer, table_cnt);
                send(clientSocket, buffer, strlen(buffer), 0);
                continue;
            }   
            //END INSERT
            //DELETE
            else if (strcmp(command, "DELETE")==0){
                scanf("%s",dump1);
                scanf("%s",database);
                strcpy(buffer,"10 ");
                strcat(buffer,database);
                potong = strtok(buffer,";");
                strcpy(buffer,potong);
                send(clientSocket, buffer, strlen(buffer), 0);
                continue;
            }
            //END DELETE
            //SELECT
            else if (strcmp(command, "SELECT")==0){
                char isicsv[100]={0};
                scanf("%s",tipe);
                //SELECT *
                if (strcmp(tipe,"*")==0){
                    scanf("%s",dump1);
                    scanf("%s",database);
                    strcpy(buffer,"11 ");
                    strcat(buffer,database);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                    recv(clientSocket, buffer, 1024, 0);
                    strcpy(isicsv,buffer);
                    printf("isi database :\n%s\n",isicsv);
                    continue;
                }
                //END SELECT *
            }
            //END SELECT

            //SHOW
            else if (strcmp(command, "SHOW")==0){
                scanf("%s",tipe);
                char isicsv[100]={0};
                //show databases
                potong = strtok(tipe,";");
                strcpy(tipe,potong);
                printf("tipe : %s\n",tipe);
                if (strcmp(tipe,"DATABASES")==0){
                    strcpy(buffer,"12 ");
                    send(clientSocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                    recv(clientSocket, buffer, 1024, 0);
                    strcpy(isicsv,buffer);
                    printf("database tersedia :\n%s\n",isicsv);
                    continue;
                }
                //show tables
                else if (strcmp(tipe,"TABLES")==0){
                    strcpy(buffer,"13 ");
                    send(clientSocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                    recv(clientSocket, buffer, 1024, 0);
                    strcpy(isicsv,buffer);
                    printf("table tersedia :\n%s\n",isicsv);
                    continue;
                }
            }
            //END SHOW

            //DESCRIBE
            else if (strcmp(command, "DESCRIBE")==0){
                char isicsv[100]={0};
                scanf("%s",database);
                strcpy(buffer,"14 ");
                strcat(buffer,database);
                potong = strtok(buffer,";");
                strcpy(buffer,potong);
                send(clientSocket, buffer, strlen(buffer), 0);
                bzero(buffer, sizeof(buffer));
                recv(clientSocket, buffer, 1024, 0);
                strcpy(isicsv,buffer);
                printf("table tersedia :\n%s\n",isicsv);
                continue;
            }
            //END DESCRIBE

            else if(strcmp(command, ":exit") == 0){
                send(clientSocket, ":exit", strlen(":exit"), 0);
                close(clientSocket);
                printf("[-]Disconnected from server.\n");
                exit(1);
            }

            if(recv(clientSocket, buffer, 1024, 0) < 0){
                printf("[-]Error in receiving data.\n");
            }else{
                printf("Server: \t%s\n", buffer);
            }
        }
    }
    else if (strcmp(buffer,"salah")==0){
        send(clientSocket, ":exit", strlen(":exit"), 0);
        close(clientSocket);
        printf("Unauthorized\n");
        exit(1);
    }
    return 0;
}
