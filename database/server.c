#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <dirent.h>

#define PORT 4442

int main(){

    int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    char buffer[1024]={0};
    char login[1024]={0};
    char *kred;
    char use_kred[1024]={0};
    char temp[1000]={0};
    char database[1024]={0};
    char makedb[1024]={0};
    char *fin;
    FILE * fp;
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
    printf("[-]Error in connection.\n");
    exit(1);
    }
    printf("[+]Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
    printf("[-]Error in binding.\n");
    exit(1);
    }
    printf("[+]Bind to port %d\n", 4444);

    if(listen(sockfd, 10) == 0){
    printf("[+]Listening....\n");
    }else{
    printf("[-]Error in binding.\n");
    }


    while(1){
    newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
    if(newSocket < 0){
        exit(1);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

    if((childpid = fork()) == 0){
    close(sockfd);

    while(1){
        recv(newSocket, buffer, 1024, 0);
        if(strcmp(buffer, ":exit") == 0){
            printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            break;
        }
        else if (strstr(buffer,"login;")){
            strcpy(login,buffer);
            strtok(login,";");
            kred = strtok(NULL,";");
            printf("kred : %s\n",kred);
            bzero(buffer, sizeof(buffer));
            char * buff = 0;
            char *ret2={0};
            long length;
            FILE * f = fopen ("databases/user.txt", "rb");

            if (f)
            {
                fseek (f, 0, SEEK_END);
                length = ftell (f);
                fseek (f, 0, SEEK_SET);
                buff = malloc (length);
            if (buff)
            {
                fread (buff, 1, length, f);
            }
            fclose (f);
            }
            ret2 = strstr(buff,kred);
            if (ret2){
                send(newSocket, "bener", strlen("bener"), 0);
            }
            else {
                send(newSocket, "salah", strlen("salah"), 0);
            }
        }
        else if(strcmp(buffer,"kosong")==0){
            printf("Sudo kan? masuk aja\n");
            send(newSocket, "bener", strlen("bener"), 0);
            bzero(buffer, sizeof(buffer));
        }
        else{
            strcpy(temp,buffer);
            fin = strtok(temp," ");
            //create user
            if (strcmp(fin,"1")==0){
                fp = fopen("databases/user.txt", "a+");
                fin = strtok(NULL," ");
                strcat(fin,"\n");
                fputs(fin,fp);
                fclose(fp);
                printf("%s\n",fin);
                strcpy(buffer,fin);
            }
            //end create user
            //use
            else if (strcmp(fin,"2")==0){
                fin = strtok(NULL," ");
                if (strcmp(fin,"sudo")==0){
                    printf("use sudo\n");
                    send(newSocket, "use_bener", strlen("use_bener"), 0);
                    fin = strtok(NULL," ");
                    strcpy(database,fin);
                    printf("database : %s\n",database);
                }
                else {
                    strcpy (use_kred,fin);
                    printf("use not sudo : %s\n",use_kred);
                    
                    //CHECK grant
                    char * buff3 = 0;
                    char *ret3={0};
                    long length;
                    FILE * f = fopen ("databases/grant.txt", "rb");

                    if (f)
                    {
                        fseek (f, 0, SEEK_END);
                        length = ftell (f);
                        fseek (f, 0, SEEK_SET);
                        buff3 = malloc (length);
                    if (buff3)
                    {
                        fread (buff3, 1, length, f);
                    }
                    fclose (f);
                    }
                    ret3 = strstr(buff3,use_kred);
                    if (ret3){
                        send(newSocket, "use_bener", strlen("use_bener"), 0);
                        printf("use database\n");
                        fin = strtok(NULL," ");
                        strcpy(database,fin);
                        printf("database : %s\n",database);
                    }
                    else {
                        send(newSocket, "use_salah", strlen("use_salah"), 0);
                        printf("grant gaada\n");
                    }
                    //END check grant
                }
                // printf("%s\n",fin);
                // strcpy(buffer,fin);
            }
            //end use
            //grant
            else if (strcmp(fin,"3")==0){
                fp = fopen("databases/grant.txt", "a+");
                fin = strtok(NULL," ");
                strcat(fin,"\n");
                fputs(fin,fp);
                fclose(fp);
                printf("%s\n",fin);
                strcpy(buffer,fin);
            }
            //end grant
            //create database
            else if (strcmp(fin,"4")==0){
                fin = strtok(NULL," ");
                strcpy(makedb,"databases/");
                strcat(makedb,fin);
                mkdir(makedb,0700);
                fin = strtok(NULL," ");
                fp = fopen("databases/grant.txt", "a+");
                //fin = strtok(NULL," ");
                strcat(fin,"\n");
                fputs(fin,fp);
                fclose(fp);
                printf("Create Database %s\n",fin);
            }
            //end create database
            //create table
            else if (strcmp(fin,"5")==0){
                fin = strtok(NULL," ");
                char table_name[100];
                strcpy(table_name,fin);
                printf("Create TABLE (nama) : %s\n",fin);
                fin = strtok(NULL," ");
                fin = strtok(NULL,"(");

                char string[2000];
                strcpy(string,fin);
                const char s[2] = " ";
                char *token;
                char final[1000]={0};
                int i=0;
            
                /* get the first token */
                token = strtok(string, s);
                
                /* walk through other tokens */
                while( token != NULL ) {
                    if (strcmp(token,")")==0)
                        break;
                    if (i%2==0){
                        strcat(final,token);
                        strcat(final,", ");
                    }
                    
                    token = strtok(NULL, s);
                    i++;
                }
                printf("final column : %s\n",final);
                FILE *fpt;
                char fpath[1000]={0};
                strcpy(fpath,"databases/");
                strcat(fpath,database);
                strcat(fpath,"/");
                strcat(fpath,table_name);
                strcat(fpath,".csv");
                fpt = fopen(fpath, "a+");
                strcat(final,"\n");
                fprintf(fpt,final);
                fclose(fpt);
            }
            //end create table

            //drop database
            else if (strcmp(fin,"6")==0){
                char drop_db[1000]={0};
                char cmd[1000]={0};
                fin = strtok(NULL, " ");
                strcpy(drop_db,"databases/");
                strcat(drop_db,fin);
                printf("database drop : %s\n",drop_db);
                strcpy(cmd,"rm -r ");
                strcat(cmd,drop_db);
                system(cmd);
                // char *argv[] = {"rm", "-r",drop_db,NULL};
                // execv("/bin/rm", argv);
            }
            //end drop database
            //drop table
            else if (strcmp(fin,"7")==0){
                char drop_db[1000]={0};
                char cmd[1000]={0};
                fin = strtok(NULL, " ");
                strcpy(drop_db,"databases/");
                strcat(drop_db,database);
                strcat(drop_db,"/");
                strcat(drop_db,fin);
                strcat(drop_db,".csv");
                printf("table drop ini : %s\n",drop_db);
                strcpy(cmd,"rm ");
                strcat(cmd,drop_db);
                system(cmd);
                // char *argv[] = {"rm",drop_db,NULL};
                // execv("/bin/rm", argv);
                // continue;
            }
            //end drop table
            //drop collumn
            else if (strcmp(fin,"8")==0){
                char drop_db[1000]={0};
                char cmd[1000]={0};
                char col[1000]={0};
                char tab[1000]={0};
                char snum[5]={0};
                char oldname[100];
                char newname[100];
                char jalur[100];
                fin = strtok(NULL, " ");
                strcpy(col,fin);
                fin = strtok(NULL, " ");
                strcpy(tab,"databases/");
                strcat(tab,database);
                strcat(tab,"/");
                strcat(tab,fin);
                strcat(tab,".csv");
                printf("Drop table (database): %s\n",database);
                printf("Drop table (table): %s\n",tab);
                printf("Drop table (column): %s\n",col);

                FILE* stream = fopen(tab, "r");

                char line[1024];
                fgets(line, 1024, stream);
                puts(line);
                const char s[3] = ", ";
                char *token;
                char pembanding[100];
                strcpy(pembanding,col);
                int i =1;
                
                /* get the first token */
                token = strtok(line, s);
                
                /* walk through other tokens */
                while( token != NULL ) {
                    //printf( " %s\n", token );
                    if(strcmp(pembanding,token)==0){
                        printf("field ke : %d\n",i);
                        break;
                    }
                    
                    token = strtok(NULL, s);
                    i++;
                }
                //cut -d, -f4 --complement MyFile.csv > Out.csv
                sprintf(snum, "%d", i);
                strcpy (cmd,"cut -d, -f");
                strcat (cmd,snum);
                strcat (cmd," --complement ");
                strcat (cmd,tab);
                strcat (cmd," > databases/");
                strcat (cmd,database);
                strcat (cmd,"/out.csv");
                system(cmd);
                strcpy(cmd,"rm ");
                strcpy(cmd,tab);
                system(cmd);
                strcpy(jalur,"databases/");
                strcat(jalur,database);
                strcat(jalur,"/");
                strcpy(oldname,jalur);
                strcat(oldname,"out.csv");
                strcpy(newname,tab);
                rename(oldname, newname);
            }
            //end drop collumn
            //insert into
            else if (strcmp(fin,"9")==0){
                //printf("Insert Into : %s\n",buffer);
                fin = strtok(NULL," ");
                char table_name[100];
                strcpy(table_name,fin);
                printf("INSERT nih : %s\n",fin);
                fin = strtok(NULL," ");
                fin = strtok(NULL,"(");

                char string[2000];
                strcpy(string,fin);
                const char s[2] = " ";
                char *token;
                char final[1000]={0};
                int i=0;
            
                /* get the first token */
                token = strtok(string, s);
                
                /* walk through other tokens */
                while( token != NULL ) {
                    if (strcmp(token,")")==0)
                        break;

                    strcat(final,token);
                    //strcat(final,", ");
                    
                    token = strtok(NULL, s);
                    i++;
                }
                printf("final column : %s\n",final);
                FILE *fpt;
                char fpath[1000]={0};
                strcpy(fpath,"databases/");
                strcat(fpath,database);
                strcat(fpath,"/");
                strcat(fpath,table_name);
                strcat(fpath,".csv");
                fpt = fopen(fpath, "a+");
                strcat(final,"\n");
                fprintf(fpt,final);
                fclose(fpt);

            }
            //end insert into
            
            //delete
            else if (strcmp(fin,"10")==0){
                char tbl[100]={0};
                fin = strtok(NULL," ");
                strcpy(tbl,"databases/");
                strcat(tbl,database);
                strcat(tbl,"/");
                strcat(tbl,fin);
                strcat(tbl,".csv");
                printf ("Delete ini : %s\n",tbl);
                FILE* stream = fopen(tbl, "r");

                char line[1024];
                fgets(line, 1024, stream);
                puts(line);
                fclose(stream);

                FILE *fpt2;
                // strcat(line,"\n");
                fpt2 = fopen(tbl, "w+");
                fprintf(fpt2,line);
                fclose(fpt2);
            }
            //end delete
            //select *
            else if (strcmp(fin,"11")==0){
                char tbl[100]={0};
                char isicsv[100]={0};
                fin = strtok(NULL," ");
                strcpy(tbl,"databases/");
                strcat(tbl,database);
                strcat(tbl,"/");
                strcat(tbl,fin);
                strcat(tbl,".csv");
                printf ("Select ini : %s\n",tbl);
                FILE* stream = fopen(tbl, "r");

                char line[1024];
                while (fgets(line, 1024, stream))
                {
                    // char* tmp = strdup(line);
                    // printf("ISI : %s\n",tmp);
                    // // NOTE strtok clobbers tmp
                    // free(tmp);
                    strcat(isicsv,line);
                }
                fclose(stream);
                printf("Isi : %s\n",isicsv);
                send(newSocket, isicsv, strlen(isicsv), 0);
            }
            //end select *
            //show databases
            else if (strcmp(fin,"12")==0){
                char database[1000]={0};
                printf("Show db : %s\n",buffer);
                struct dirent *de;
                DIR *dr = opendir("databases/");

                if (dr == NULL)
                {
                    printf("Could not open current directory" );
                    return 0;
                }

                while ((de = readdir(dr)) != NULL){
                        if (strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0||strcmp(de->d_name,"user.txt")==0||strcmp(de->d_name,"grant.txt")==0);
                        else{
                            strcat(database,de->d_name);
                            strcat(database,"\n");
                        }
                }
                closedir(dr);	
                send(newSocket, database, strlen(database), 0);
            }
            //show databases end
            //show tables
            else if (strcmp(fin,"13")==0){
                char database2[1000]={0};
                char direct[100]={0};
                printf("Show tables : %s\n",buffer);
                struct dirent *de;
                strcpy(direct,"databases/");
                strcat(direct,database);
                strcat(direct,"/");
                printf("directory : %s\n",direct);
                DIR *dr = opendir(direct);

                if (dr == NULL)
                {
                    printf("Could not open current directory" );
                    return 0;
                }

                while ((de = readdir(dr)) != NULL){
                        if (strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0||strcmp(de->d_name,"user.txt")==0||strcmp(de->d_name,"grant.txt")==0);
                        else{
                            strcat(database2,de->d_name);
                            strcat(database2,"\n");
                        }
                }
                closedir(dr);	
                send(newSocket, database2, strlen(database2), 0);
            }
            //show tables end

            //describe table
            else if (strcmp(fin,"14")==0){
                char tbl[100]={0};
                char isicsv[100]={0};
                fin = strtok(NULL," ");
                strcpy(tbl,"databases/");
                strcat(tbl,database);
                strcat(tbl,"/");
                strcat(tbl,fin);
                strcat(tbl,".csv");
                printf ("Describe ini : %s\n",tbl);
                FILE* stream = fopen(tbl, "r");

                char line[1024];
                fgets(line, 1024, stream);
                fclose(stream);
                send(newSocket, line, strlen(line), 0);
            }
            //describe table end
            
            printf("Client: %s\n", buffer);
            //send(newSocket, buffer, strlen(buffer), 0);
            bzero(buffer, sizeof(buffer));
        }
    }
    }

    }

    close(newSocket);


    return 0;
}
