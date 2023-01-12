#ifndef _fdefs
#define _fdefs 

/*****************************************************************************helping functions***********************************************************************************/

// strP() will return one string for 2 arguements of string type. the outcome is same everytime the 2 strings are given.
// used to name the files
int strP(char* s1, char*s2)
{
    // the first priority is length
    int tmp1 = strlen(s1);
    int tmp2 = strlen(s2);

    if(tmp1>tmp2)
    return 1 ;

    else if(tmp2>tmp1)
    return 0 ;

    else
    {
        // if not length, the next criteria will be 
        for(int i = 0 ; i <tmp1; i++)
        {
            if(s1[i]> s2[i])
            return 1 ;

            else if(s2[i]>s1[i])
            return 0 ;

            else 
            continue ;
        }
    }
}


// the delay() will make the control flow pause for time mentioned in milliseconds
void delay(unsigned int ms)
{
    clock_t later = ms + clock();
    // the loop will run untill the condition is met
    while( later> clock() );
}

// design - animation purpose 
void load_animation()
{
    system("cls");
	fflush(stdin);
	char loading[]="**************************************************";
	printf(" Elpmis        x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://mail.elpmis.com\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	int i=0;
	
	printf("\n\n");
	printf("\t\t\t\t\t     Loading  home page....");
	printf("\n\t\t\t\t   ___________________________________________________");
	printf("\n\t\t\t\t   ");
	while (loading[i]!='\0')
	{
		printf("%c",loading[i]);
		delay(30);
        if(i%5==0)delay(20);
        if(i%10==0)delay(30);
        if(i%15==0)delay(70);
		i++;
	}
	
	delay(300);

}

// the file mentioned as param- username will be opened and iterated to 3rd line to get the name
char* getname(char * username)
{
    // creating the required directory
    char dir[50] = "" ;
    strcat(dir,USERDB);
    strcat(dir,username);
    strcat(dir,".txt");
    FILE* ptr = fopen(dir,"r");
    char tmp ; int i=0 ;

    // iterating 2 lines
    while(fgetc(ptr) != '\n');
    while(fgetc(ptr) != '\n');

    char* pass = (char*)malloc(sizeof(char)*50);
    tmp = fgetc(ptr);
    while(tmp != '\n')
    {
        pass[i++] = tmp ;
        tmp = fgetc(ptr);
    }
    pass[i] = '\0' ;   
    fclose(ptr);
    return pass;
}

// deletes the extra lines below the file
void trim(char* user1, char* dir)
{
    //file will be the directory
    char file[]= ""; 
    strcat(file, dir);
    strcat(file, user1); 
    strcat(file,".txt");

    FILE* f = fopen(file,"a");
    fputc('\n',f);
    fputc('\n',f);
    fclose(f);
    char fil[]= ""; 
    strcat(fil, dir);
    strcat(fil, user1); 
    strcat(fil,".txt");
    f = fopen(fil,"r");

    int count = 0 ; 
    char x  = fgetc(f); count++ ; 
    char y; 

    while( !feof(f) )
    {
        y = fgetc(f) ;count++;
        if(x == '\n' && y == '\n')
        {
            fseek(f, -3, SEEK_CUR);
            count-=2; 
            count++;
            break;
        }
       
        if(!feof(f))
        {
            x = fgetc(f);
            count++;
        }
       
        else
        break;

        if(x == '\n' && y == '\n')
        {
            fseek(f, -3, SEEK_CUR);
            count-=2; 
            count++;
            break;
        }
       
    }

    fclose(f);
    char file2[]= ""; 
    strcat(file2, dir);
    strcat(file2, user1); 
    strcat(file2,".txt");
    f = fopen(file2,"r");

    FILE* ptr = fopen("tmp.txt","w");
    int i = 1 ;

    while(i < count)
    {
        fputc(fgetc(f), ptr);
        i++;
    }

    fclose(ptr);
    fclose(f);

    char file3[]= ""; 
    strcat(file3, dir);
    strcat(file3, user1); 
    strcat(file3,".txt");
    ptr = fopen(file3,"w");
    f = fopen("tmp.txt","r");

    i= 1;
    while( i< count )
    {
        fputc(fgetc(f),ptr);i++;
    }
    fclose(f);
    fclose(ptr);
    remove("tmp.txt");
    return ; 
    
}

char* getTime(char* new)
{
    // needing only month day and year
    time_t t;          
    time(&t);
    char* curr= ctime(&t);
    int j =0 ;
    for(int i = 4; i<= 10; i++)
    new[j++] = curr[i] ;
    for(int i = 20; i<= 23; i++)
    new[j++] = curr[i] ;
    new[24] = '\0';
    return new;
}

/***************************************************************************login-signup-functions*********************************************************************************/


// the initial display when the main.c is run, the search bar
// the user has to enter elpmis irrespective of case insensitive and stripping spacebars
void search_engine_display()
{
    // many of these type of functions will include a lot of design intended lines of code
    // many non functional printf statements to look good for the user on terminal
    system("cls");
	system("color FC");//FC white bg red font
	printf(" zenyuzien     x\\ +\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<--  -->    http://www.zenyuzien.com\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\tZ E N Y U Z I E N\n\t\t\t\t\t\t\t   \n");
	printf("\t\t\t       ________________________________________________\n");
	printf("\t\t\t       |Search: ");
    // the validate search will validate the user's input
    validate_search_(); 
}

void validate_search_()
{
    // the valid final texts after stripping spacebars and case sensitivity

    char tmp1[] = "elpmis.com" ;
    char tmp2[] = "elpmis" ;
    char tmp3[] = "www.elpmis.com" ;
    char tmp4[] = "https://www.elpmis.com" ;
    char tmp5[] = "https://elpmis.com" ;

    // for taking input 
    char user_input[50] = "\n" ;// maade initially \n to handle empty input
    fflush(stdin);
	scanf("%[^\n]",user_input);

    // if the user input is ntg and simply enters
	if(strcmp(user_input,"\n")==0)
	{
        //call search engine again if there is no input
		search_engine_display();
		return ;
	}

    //lowercase shift
    for(int i = 0 ; i < strlen(user_input) ; i++)
    user_input[i] = tolower(user_input[i]);

    //stripping spaces 
    int start = 0 ; 

    for(int i = 0 ;  user_input[i] == ' '; i++)
    if(user_input[i] == ' ')start++;
    
  
    int end = strlen(user_input)  -1 ;
    for(int i = end ;  user_input[i] == ' '; i--)
    if(user_input[i] == ' ')end--;

    char ret[ end - start + 1 ] ;
    ret[end-start+1] = '\0' ;
    
    for(int i = start ,j =0 ; i <= end ; i++)
    ret[j++]  = user_input[i] ; 


    //  final evaluation spaces
    if( strcmp(ret, tmp1)==0 || strcmp(ret, tmp2)==0 || 
    strcmp(ret, tmp3)==0 || strcmp(ret, tmp4)==0  || strcmp(ret, tmp5)==0 )
    elpmis_home(1);
    else
    bad_search(ret);
    

}

// if it is a valid choice, home to , the flag is only used to handle errors and unexpected user inputs
void elpmis_home(int flag)
{
 
    // the load animation is for design purpose only , for user xp
	load_animation();
	system("cls");

	printf(" Elpmis        x\\ +\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->      http://www.elpmis.com/home\t\t\t\t\t\t\t\t\t\tT  | | |\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\n\n\n\n");


	if(flag==1)
	{
        // delay function delays for millisseconds
		delay(100);
		printf("\t\t\t\t\t\t 'a zenyuzien subsidiary'\n\n");
		int i=0;

        // to print character by character with delay
		char design[]="\t\t\t\t\t\t      E L P M I S\n";
		while (design[i]!='\0')
		{
			printf("%c",design[i]);
 		    delay(100);
			i++;
		}
	}
    // if error occured, no design, directly printing

	else
	{
		printf("\t\t\t\t\t\t 'a zenyuzien subsidiary'\n\n");
		printf("\t\t\t\t\t\t      E L P M I S\n");
	}

	
	
	printf("\n\n\n\t\t\t\t\tEnter 'login' if you already have account\n\t\t\t\t\tEnter 'signup' to create new Elpmis account\n\n\t\t\t\t\tEnter 'close' to close the window\n\t\t\t\t\t");

	if(flag==0)printf("invalid option, try again\n\t\t\t\t\t");
	else printf("\n\t\t\t\t\t");
	char option[10]= "\n";
	fflush(stdin);
	scanf("%[^\n]s",option);
	// cse sensitivity removal
    for(int i = 0 ; i < strlen(option); i++)option[i]= tolower(option[i]);

    // this is where user either logins or creates a new account
	if(strcmp(option,"login")==0){
		login_page(1);
		//delay(300);
		//elpmis_home(1);
	}
	else if(strcmp(option,"signup")==0){
		signup_page();
		delay(300);
		elpmis_home(1);
	}

    // the point where user terminate the program
	else if(strcmp(option,"close")==0)
	{
		system("cls");return; 
	}
	else 
    // the page will reappear without the animation delay, hence the flag
	elpmis_home(0);
		
}

// the bad search is only for design, user xp purpose it has no functionality. 
// when user enters anything out of the valid elpmis links, this message will be shown
void bad_search(char* ret){
	system("cls");
	printf(" %s   x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n",ret);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->      http://%s\n",ret);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\n\n\n\n\n\n\n\n");
	delay(250);
	printf("\t\t\t(-_-)\n\n");
	printf("\t\t\tThis site can\'t be reached.\n\n");
	printf("\t\t\t%s\'s server DNS address could not be found.\n",ret);
	printf("\t\t\tERR_NAME_NOT_RESOLVED");
	
	printf("\n\n\n\n\n\n");
    printf("\t\t\tThis problem may arised because the site might not be a subsidiary of zenyuzien\n");
	printf("\t\t\tTo go back to previous page: (Press b)\n");
	printf("\t\t\tTo close the Window: (Press x)\n");
	printf("\t\t\tEnter your option: ");
	
    // user will howver be given the chocie to decide either to close the window or to try a different url
	char choice='\n';
    fflush(stdin);
	scanf("%c", &choice);

    // the empty enter case
	if(choice=='\n')
	{
		bad_search(ret);
		return;
	}
    if(choice == 'B' || choice == 'b')
    search_engine_display() ;
    else if (choice == 'x' || choice == 'X'){system("cls");
    return ;}
    else
    bad_search(ret);
	
}


// when user  enters the login page
void login_page(int f)
{

    // the basic design 
    system("cls");
	fflush(stdin);
	printf("  Login        x\\ +\t\t\t\t\t\t\t\t\t\t\t\t      | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://accounts.elpmis.com/login\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\n\n");
	
    // the same thing, the flag will decide if animation to happen or not, wouldnt happen in case of exceptions , the first time, yes.
    if(f == 1)
    {
        int i=0;
	    char p[]="\t\t\t\t\t              ELPMIS LOGIN         \n\n\n";
	    while (p[i]!='\0')
	    {
		    printf("%c",p[i]);
            delay(100);
		    i++;
	    }
        printf("\n\t\t\t\t    Enter your username:");
    }
    else if(f == 2)
    {
        printf("\t\t\t\t\t              ELPMIS LOGIN         \n\n\n");
        printf("\n\t\t\t\t    Enter your username:");
    }
    
    
    // the username shall enter his username
    fflush(stdin);
    char use[50]="\n"; 
    scanf("%[^\n]s",use);
    if(strcmp(use,"\n")==0)
    login_page(2);

    // the username checker will follow a standard convention, you can see it in the definition of this function
    if(username_checker(use)==1);
    else goto z;

    // isUsername will check if the i/p is already in the user database file
    if( isUsername(use) ==1 );
    //if the username exists, alright, now check for password
    else
    {   z:;
        printf("\n\t\t\t\t    username doesnt exist, enter 'retry' to try again or enter 'signup' to sign in");
        q:;
        fflush(stdin);
        printf("\n\t\t\t\t    ");
        scanf("%[^\n]s",use);
        char tmp[strlen(use)+1] ; 
        int i ; 
        for(i = 0 ; i < strlen(use); i++)
        tmp[i] = tolower(use[i]);  tmp[i] = '\0' ;

        if( strcmp(tmp, "retry")==0 || strcmp(tmp, "'retry'")==0 )
        {
                login_page(2);
        }
        else if (strcmp(tmp, "signup")==0 || strcmp(tmp, "'signup'")==0)
        {
            printf("\t\t\t\t   redirecting to signup page in 3...");
            delay(200);
            printf(" 2...");
            delay(200);
            printf("1...");
            delay(200);
            signup_page();
            return ;
        }
        else
        {
            printf("\n\t\t\t\t    invalid input, try again\n\t\t\t\t    ");
        
            goto q;
        }

    }
    

    // for the password, we expect stars rather than characters so, we use putch() and getch() to take control of the console
    // using conio.hfunction putch() here now 
    printf("\n\t\t\t\t    Enter your password: ");
    x:;
    fflush(stdin);

    char pass[50];
    char c ;
    int index = 0;
  
    
    /* 13 is ASCII value of Enter key */
   
    while((c = getch()) != 13)
    {
       //for dealing with backspaces at beginning itself
       if(index < 0)
           index = 0;
       /* 8 is ASCII value of BACKSPACE character */
       if(c == 3)
       {
        exit(1);
       }
       else if(c==8 && index==0)continue ;
       else if(c == 8 )
       {
           putch('\b');
           putch(' ');
           putch('\b');
           index--;
           continue;
       }
       pass[index++] = c;
       putch('*');
    }
    pass[index] = '\0';
    
    // isPassword checks if the password is right ot not from the user file from the user database
    if(isPassword(use,pass))
    {
        // well the username is now assigned to the global vairable which revolves around everywhere now
        global = use; 

        // if the accpunt is deactivated, it will be reactivated without the knowledge of the user
        if(isDeactivated(use))
        deletionUtility("deactivated_db.txt",global,REQ,0);

        // the real menu of elpmis
        display_options(1);
    }
    else{
        printf("\n\t\t\t\t    incorrect password, try again: or enter 'forgot-password' ");
        goto x; 
    }

}

// the process to check if it is the right passwsord
int isPassword(char* username ,char* password) 
{
    // creating a string of the required directory
    char dir[50] = "" ;
    strcat(dir,USERDB);
    strcat(dir,username);
    strcat(dir,".txt");

    // the buffer to store the right password
    char pas[50];  int i;
    FILE* ptr = fopen(dir, "r");
    char tmp; 
    do
    {
        tmp = fgetc(ptr);
    }
    while(tmp != '\n') ;
    tmp = fgetc(ptr); i = 0 ; 
    while(tmp != '\n')
    {
        pas[i] = tmp ;
        i++;
        tmp = fgetc(ptr);
    }
    pas[i] = '\0' ; 
    // pas[] now contains the right password 
    fclose(ptr);
    if(strcmp(pas,password)==0)return 1 ;
    else return 0 ;

    
}

// the signup page where user creates his account of elpmis

void signup_page()
{
    system("cls");
	printf("     Signup    x\\ +\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->      http://www.elpmis.com/signup\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\n\n");
	delay(100);
	printf("\t\t\t\t  ___________________________________\n");
	printf("\t\t\t\t \n");
    printf("\t\t\t\t *************************************\n\t\t\t\t");

    // some animation as usual
	char title[]="      Create your elpmis account     ";
	for (int i = 0 ; title[i]!='\0';){
		printf("%c",title[i]);
 	   	delay(100);
		i++;
	}
	delay(100);
	printf("\n\t\t\t\t   _________________________________  \n");
	printf("\t\t\t\t *************************************\n");
	
	printf("\t\t\t\t\t________________________\n");
	printf("\t\t\t\t\t|    Enter your Name   |\n");
	printf("\t\t\t\t\t|______________________|");
	qa:;

	printf("\n\t\t\t\t    First Name: ");

    fflush(stdin);
    char fname[20]="";
	scanf("%[^\n]s",fname);
    fflush(stdin);
    // for almost any data, length conventions are followed
        if(strlen(fname)<2 ||strlen(fname)>16  )
        {
                printf("\n\t\t\t\t    Name length not in range [2,16] ");
                goto qa;
        }
    qb:;
	fflush(stdin);
    char lname[20]="" ;
	printf("\n\t\t\t\t    Last Name: ");
	scanf("%[^\n]s",lname);
    fflush(stdin);
    
        if(strlen(lname)<2 ||strlen(lname)>16  )
        {
                printf("\t\t\t\t    Name length not in range [2,16] ");
                goto qb;
        }

	
	printf("\n\t\t\t\t -------------------------------------\n\n");
	
	printf("\t\t\t\t\t________________________\n");
	printf("\t\t\t\t\t|  Creating a Username |\n");
	printf("\t\t\t\t\t|______________________|");
    y:;
    printf("\n\t\t\t\t    Enter a catchy username:");
	

    fflush(stdin);
    char uname[20]="";
	scanf("%[^\n]s",uname);
    
    // should check if the username already exists
    if( username_checker(uname) && isUsername(uname) ==0 )
    {
        // well the username doesnt exist in database, but dooesnt follow conventions
        int tmp = username_checker(uname) ; 
        // to let the user know what convention was violated in his/her username
        if(tmp == -1 ){printf("\n\t\t\t\t    username should not start with digit, try again");goto y;}
        else if(tmp == (-2) ){printf("\n\t\t\t\t    unsatisifed username length (<4, >16)");goto y;}
        else if(tmp == -3 ){printf("\n\t\t\t\t    username is a reserved keyword, try input a unique name or add numbers");goto y;}
        else if(tmp == 0){printf("\n\t\t\t\t    username should not special characters except '-' / '_' / '.' ");goto y;}

        // now the conventions are also followed. uname is a valid username
        else;
    }
    else
    {
        // the username already exists, so aknowledging the user
        char choice[25];
        printf("\n\t\t\t\t    username already exists. enter 'login' to sign in or enter 'retry' to try different username\n\t\t\t\t    ");
        z:;
        fflush(stdin);
        scanf("%[^\n]s",choice);

        char tmp[strlen(choice)+1] ; 
        int i ; 
        for(i = 0 ; i < strlen(choice); i++)
        tmp[i] = tolower(choice[i]);  tmp[i] = '\0' ;

        // if user has the same username , he can login
        if( strcmp(tmp, "login")==0 || strcmp(tmp,"'login'")==0 )
        {
            login_page(1);
            return ;
        }

        // if user wishes to retry another username
        else if( strcmp(tmp, "retry")==0 || strcmp(tmp,"'retry'")==0 )
        {
            goto y; 
        }
        
        // all other inputs
        else {
            printf("\t\t\t\t    invalid input, try again\n\t\t\t\t    ");
            goto z;
        }
    }
	printf("\n\t\t\t\t -------------------------------------\n\n");
	
	printf("\t\t\t\t\t|  Creating a Password |\n");
	printf("\t\t\t\t\t|______________________|\n");
    x:;
	printf("\n\t\t\t\t    Enter your Passowrd:");

    fflush(stdin);
	char pass[50] ;
    char  c ;
    int index = 0;
  
   
    /* 13 is ASCII value of Enter key */
   
    while((c = getch()) != 13)
    {
        //for dealing with backspaces at beginning itself
       if(index < 0)
           index = 0;
       /* 8 is ASCII value of BACKSPACE character */
       if(c == 3)
       {
        exit(1);
       }
       else if(c==8 && index==0)continue ;
       else if(c == 8 )
       {
           putch('\b');
           putch(' ');
           putch('\b');
           index--;
           continue;
       }
       pass[index++] = c;
       putch('*');
    }
    pass[index] = '\0';
    
   // the password checker function will return integers based on the contraints
    if( password_checker(pass) == -8)
    {
        printf("\n\t\t\t\t    password should be atleast 8 characters long\n");
        goto x;
    }
    else if( password_checker(pass) == -16 )
    {
        printf("\n\t\t\t\t    password should be at max 16 characters long\n");
        goto x;
    }
    else if( password_checker(pass) == 0 )
    {
        printf("\n\t\t\t\t    password should contain atleast one of each:\n\t\t\t\t    lowercase, uppercase, numeric and special characters\n");
        goto x;
    }
    else;

	printf("\n\t\t\t\t    Re-Enter your password: ");
    fflush(stdin);
    char passcheck[50];
    index = 0;
  
   
    /* 13 is ASCII value of Enter key */

    while((c = getch()) != 13)
    {
        //for dealing with backspaces at beginning itself
       if(index < 0)
           index = 0;
       /* 8 is ASCII value of BACKSPACE character */
       if(c == 3)
       {
        exit(1);
       }
       else if(c==8 && index==0)continue ;
       else if(c == 8 )
       {
           // the putch() will put the character mentioned in the console
           putch('\b');
           putch(' ');
           putch('\b');
           index--;
           continue;
       }
       passcheck[index++] = c;
       putch('*');
    }
    passcheck[index] = '\0';

    
    // password match -> ignore
    if( strcmp(passcheck, pass) == 0  );
    else
    {
        printf("\n\t\t\t\t    password mismatch!\n");
        goto x;
    }
    
    sec:;
    printf("\n\t\t\t\t    choose a security question to answer by entering the number coresspondingly");
    printf("\n\t\t\t\t    1) what is your nickname ? \t 2) what is your pet's name ? \t 3) what is your mother's name ?\n\t\t\t\t");
    char cv[25] = "\n" ; int cb ;
    qad:;
    fflush(stdin);
    scanf("%[^\n]s",cv);
    if(strcmp(cv,"\n")==0 || strlen(cv)!=1)
    {
        printf("\n\t\t\t\t invalid input, try again\t\t\t\t");
        goto qad;
    }
    cb = atoi(cv);
    if(cb != 1 && cb!= 2 && cb!= 3)
    {
        printf("\n\t\t\t\t invalid input, try again\t\t\t\t");
        goto qad;
    }
    printf("\n\t\t\t\t    enter your answer or enter 'back' to try different question (answer should not exceed 20 characters) :");
    fflush(stdin);
    scanf("%[^\n]s",cv);
    for(int i = 0 ; i < strlen(cv); i++)cv[i]=tolower(cv[i]);
    if(!strcmp(cv,"back"))
    goto sec;
    
    printf("\t\t\t\tyour answer for ");

    if(cb==1)
    printf("what is your nickname ?");
    
    else if(cb==2)
    printf("what is your pet's name ?");

    else 
    printf("what is your mother's name ?");

    printf(" is %s , enter 'yes' to confirm or 'no' to try again \n\t\t\t\t ",cv);
    yesno:;
    char ccv[10]="\n";
    fflush(stdin);
    scanf("%[^\n]s",ccv);

    if(!strcmp(ccv,"yes"))
    ;
    else if(!strcmp(ccv,"no"))
    {
        goto sec;
    }
    else
    {
        if(strcmp(ccv,"\n")==0);
        else 
        printf("\n\t\t\t\t invalid input, try again\t\t\t\t");
        goto yesno;   
    }

    char question[50] = "" ;
    if(cb==1)
    strcat(question,"what is your nickname ?");
    else if(cb==2)
    strcat(question,"what is your pet's name ?");
    else if(cb ==3 )
    strcat(question,"what is your mother's name ?");

    strcat(question,cv);

    // to create a file, just open the file in write mode
    char directory[50] = "" ;
    strcat(directory, USERDB);
    strcat(directory, uname);
    strcat(directory, ".txt");
    FILE* ptr = fopen(directory, "w");

    // now to add the user details into the file
    char tmp[100] =""; 
    
    strcat(tmp,uname);
    strcat(tmp,"\n");
    strcat(tmp,pass);
    strcat(tmp,"\n");
    strcat(tmp,fname);
    strcat(tmp,"\n");
    strcat(tmp,lname);
    strcat(tmp,"\n");
    strcat(tmp,question);
    strcat(tmp,"\n");
    fputs( tmp,ptr);

    // getTime will give the time and date at the moment called
    char new[24]; char* x =getTime(new);

    // this loop will slice off the time part.
    for(int i = 0 ; i < 11; i++)
    fprintf(ptr,"%c",x[i]);   
    
    fclose(ptr);
    // done with the file writing
    global = uname ;

    // to create a blocklist file for the user and ntg to write
    char dir[30] ="block_db\\";
    strcat(dir,uname);
    strcat(dir,".txt");
    FILE* f = fopen(dir,"w");
    fclose(f);

    //  to create a game score file for the user
    char ff[50]="" ;
        strcat(ff,GAME);
        strcat(ff,global);/////
        strcat(ff,".txt");
    f  =  fopen(ff,"w");
    // initially there are 2 games available, top 5 scores of each are initially zero
    fprintf(f, "2048 0 0 0 0 0\nsnake 0 0 0 0 0\n");
    fclose(f);   

    
    // aknowledging the account creation to be success
	printf("\n\t\t\t\t    Account created succesfully !\n\n");
    printf("\t\t\t\t   directing to home page in 3...");
            delay(400);
            printf(" 2...");
            delay(400);
            printf("1...");
            delay(400);

            // back to the previous page where asked to login or signup
            elpmis_home(1);
            return ;	
}


// the password checker will check if the password will meet the standar conventions
int password_checker(char* password)
{
    // the lenth criteria
    if(strlen(password)<8 )
    return -8 ;
    else if(strlen(password)>16)
    return -16 ; 
    else; 

    // the character criteria
    char lwr,hgr,spl,num ;
    lwr=hgr=spl=num = 'n' ;

    for(int i = 0 ; password[i] != '\0'; i++ )
    {
        if( islower(password[i]) )
        lwr = 'y' ;
        else if( isupper(password[i]) )
        hgr = 'y' ;
        else if (isdigit(password[i]))
        num = 'y' ;
        else 
        spl = 'y' ;
    }

    if( lwr=='n' || spl == 'n' || num == 'n' || hgr == 'n' )
    return 0 ; 
    else return 1 ;

}

// username checker checks the criteria for the username
int username_checker(char* user)
{
    // removing case sensitivity for condition checking.
    //  it doesnt effect the user db checking by isUsername()
        
    // should satisfy length citeria
    if(strlen(user)<4 || strlen(user)>16 )
    return -2; 

    // RESERVED KEYWORDS used in menu for the program 
    else if( strcmp(user,"gamezone")==0 ||strcmp(user,"view")==0 || strcmp(user,"login")==0 ||strcmp(user,"signup")==0 ||
    strcmp(user,"view")==0 || strcmp(user,"delete")==0 || strcmp(user,"add")==0 ||strcmp(user,"chat")==0 ||
     strcmp(user,"block")==0 || strcmp(user,"mine")==0 || strcmp(user,"new")==0 ||  strcmp(user,"confirm")==0 || 
    strcmp(user,"unfriend")==0 || strcmp(user,"other")==0 || strcmp(user,"unsend")==0 || strcmp(user,"tmpp")==0 ||
    strcmp(user,"accept")==0 || strcmp(user,"search")==0 || strcmp(user,"profile")==0 ||  strcmp(user,"ttmp")==0 ||
    strcmp(user,"request")==0 || strcmp(user,"retry")==0 || strcmp(user,"exit")==0 || strcmp(user,"full")==0 || strcmp(user,"back")==0 ||
    strcmp(user,"score")==0 || strcmp(user,"play")==0 || strcmp(user,"manage")==0 ||strcmp(user,"close")==0|| 
    strcmp(user,"logout")==0 || strcmp(user,"remove")==0 ||  strcmp(user,"clear")==0 ||strcmp(user,"scores")==0|| strcmp(user,"message")==0  )
     return -3 ;
    if(isdigit(user[0]) )
    return -1 ;

    // should not contain special characters except _ - .
    for(int i = 0 ; user[i] != '\0'; i++ )
    {
        if( islower(user[i]) || isdigit(user[i]) || user[i] == '_' || user[i] == '-' || user[i] == '.'  );        
        else 
        return 0;
    }

    // if all contraints pass
    return 1; 

}


// isusername will return if the username exists in the userdatabase
int isUsername(char* target)
{
    // using the acess() to check if the file exists
    char tmr[strlen(target)+1]; 
    for(int i = 0 ; i < strlen(target); i++)
    tmr[i] = target[i] ; 
    tmr[strlen(target)] = '\0' ;
    char dir[50] = "" ;
    strcat(dir,USERDB);
    strcat(dir,tmr); //;
    strcat(dir,".txt");
    if (access(dir, 0) == 0) 
    return 1 ;
    else 
    return 0;
}

/*****************************************************************************functionalities functions***********************************************************************************/

void display_options(int flag)
{
    system("cls");
	//scanf("%d",&opt);

	printf(" Home          x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://mail.elpmis.com/%s/menu \n",global);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	
	printf("\n   Elpmis +\t|\t\t\t\t\t\t\t\t\t\t\t\t  | | |");
	printf("\n            \t|\t");
	printf("\n            \t|\t");
	printf("\n            \t|\t  Greetings %s!", getname(global) );
	printf("\n            \t|\t");
	printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*message     |      enter 'message' to open message-box of any friend ");
	printf("\n            \t|\t  -------------");
    printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*gamezone    |      enter 'gamezone' to enter games page ");
	printf("\n            \t|\t  -------------");
    printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*manage     |      enter 'manage' to manage friends list");
	printf("\n            \t|\t  -------------");
	printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*Logout     |      enter 'logout' to sign out from elpmis");
	printf("\n            \t|\t  -------------");
	printf("\n            \t|");
    if(flag==1)
	printf("\n            \t|\t  Enter Your choice: ");
    else
    printf("\n            \t|\t  invalid input, try again: ");
    fflush(stdin);
    char choice[20]="\n" ;;
    fflush(stdin);
    scanf("%[^\n]s",choice);
    if(strcmp(choice,"\n")==0)display_options(1);
    for(int i = 0 ; i < strlen(choice); i++)choice[i]= tolower(choice[i]);

    if(strcmp(choice,"message")==0 || strcmp(choice,"'message'")==0)
    {
        send();
    }
    else if(strcmp(choice,"gamezone")==0 || strcmp(choice,"'gamezone'")==0)
    {
        gameZone(1);
    }
    else if(strcmp(choice,"manage")==0 || strcmp(choice,"'manage'")==0)
    {
        manage(1);
    }
    else if(strcmp(choice,"logout")==0 || strcmp(choice,"'logout'")==0)
    {
        elpmis_home(1);
    }
    
    else
    {
        display_options(0);
    }

}

int delete_file() //not now
{  
    printf("\n delete_file() ");
    int flag =0;
    FILE* ptr; 
    char file2[]= ""; 
    strcat(file2, USERDB);
    strcat(file2, global); 
    strcat(file2,".txt");
    
    printf("opening %s in r \n",file2);
    ptr = fopen(file2, "r");
    //printf("opening %s in r \n",file2); // file 2 corrupted. period.
    while(fgetc(ptr) != '\n');
    while(fgetc(ptr) != '\n');
    while(fgetc(ptr) != '\n');
    while(fgetc(ptr) != '\n');
    while(fgetc(ptr) != '\n');
    while(fgetc(ptr) != '\n')
    if(feof(ptr))
    {
        printf("no friends to delete ");
        fclose(ptr);
        return 1;
    }
    
    
    int err = 0 ; 
    while(!feof(ptr))
    {   
        //if(err==1000)
        //break;
        char f[50] ="";
        int i =0 ;
        char tmp ;

        tmp = fgetc(ptr);
        while(tmp != '\n' && !feof(ptr) )
        {   
            f[i++] = tmp;
            tmp = fgetc(ptr);
        } f[i] = '\0';
        if(strlen(f)==0)continue; 
        char fil[50] = "" ;

            deletionUtility(f,global,USERDB,3);
            strcat(fil,CHAT);
            if(strP(global,f))
            {
                strcat(fil,global);
                strcat(fil," ");
                strcat(fil,f);
                strcat(fil,".txt");
            }   
            else 
            {
                strcat(fil,f);
                strcat(fil," ");
                strcat(fil,global);
                strcat(fil,".txt");
            }
            
        int st = remove(fil);
        printf("attempting deletion of %s, status: %d ",fil,st);
        if (st != 0 )
        flag = 1; 
                  
    }
    fclose(ptr);
    return flag ;
}

void send()
{
    char f = 'n' ;
    system("cls");

	printf("     inbox       x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->  G | http://mail.elpmis.com/messages   \t\t\t\t\t\tT | | |\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	
    
    if(numFriends(global,0)==0)
    {
        fflush(stdin);
        printf("\n            \t|\t  You don't have any friends, press any key to redirect back ");
        getch();
        fflush(stdin);
        display_options(1);
        
    }

	printf("\n            \t|\t");
	printf("\n            \t|\t"); use:;
    printf("\n            \t|\t  enter friend's username to open corresponding chat or enter 'back'(lowercase) to redirect back \n\t\t\t  ");
    fflush(stdin);
    char uip[30];
    scanf("%[^\n]s",uip);
    if(strcmp(uip,"back")==0 || strcmp(uip,"'back'")==0 )
    {
        display_options(1);
    }
    else if(strcmp(uip,global)==0 )
    {
        printf("\n            \t|\t  it is your username\n");
        goto use;
    }
    else if(checkRSB(uip,0,BLOCK)||checkRSB(uip,1,BLOCK))
    {
        // in global , check for uip 0 
        goto none; 
    } 
    else if(isDeactivated(uip))
    {
        f = 'd' ; 
    }
    if( username_checker(global)&& isUsername(global)) 
    if( isFriend(global,uip) )
    {
        aga:;
        printf("\n");
        if(strP(uip,global) )
        displayChat(uip,global,1);
        else
        displayChat(global,uip,1);
        ggg:;
        if(f == 'n')
        printf("\n\n            \t|\t  enter 'new' to write new message or enter 'back' to redirect back");
        else if(f == 'd')
        printf("\n\n            \t|\t  %s has deactivated their account, you cannot send new messages");

        printf("\n\n            \t|\t  Enter 'full' to display full chat or enter 'clear' to delete chat\n\t\t\t  ");
        fflush(stdin);
        char choice[25];
        scanf("%[^\n]s",choice);
        for(int i = 0 ; i < strlen(choice); i++)choice[i]= tolower(choice[i]);
        if((strcmp(choice,"new")==0 || strcmp(choice,"'new'")==0 )&& f=='n')
        {
                printf("\n            \t|\t  enter message (min chars: 1 , max chars: 100) \n\t\t\t  ");
                fflush(stdin);
                char message[100];
                scanf("%[^\n]s",message);
                if(strlen(message)==0 || strlen(message)>100)
                {
                    printf("\n            \t|\t  message length criteria not met \n\t\t\t  ");
                    delay(2000);
                    goto ggg;
                }
                char dir4[50] = "" ;
                strcat(dir4, CHAT);
                if(strP(uip,global) )
                {
                        strcat(dir4,uip);
                        strcat(dir4," ");
                        strcat(dir4,global);
                }
                else
                {
                        strcat(dir4,global);
                        strcat(dir4," ");
                        strcat(dir4,uip);        
                }   
                strcat(dir4,".txt");
                FILE* f = fopen(dir4, "a");
                fputc('\n', f);
                fprintf(f,"%s ",global);
                fprintf(f,"%s",message);
                fclose(f);
                goto aga;
        }
        else if(strcmp(choice,"back")==0 || strcmp(choice,"'back'")==0)
        {
            display_options(1);
        }
        else if(strcmp(choice,"full")==0 || strcmp(choice,"'full'")==0)
        {
            if(strP(uip,global) )
            displayChat(uip,global,2);
            else
            displayChat(global,uip,2);
            goto ggg;
        }
        else if(strcmp(choice,"clear")==0 || strcmp(choice,"'clear'")==0)
        {
                printf("\n            \t|\t  Confirm action by entering 'Confirm' with case sensitivity again: ");
                fflush(stdin);
                scanf("%[^\n]s",choice);
                if(strcmp(choice,"Confirm")==0 || strcmp(choice, "'Confirm'")==0 )
                    {
                                char dir5[50] = "" ;
                            strcat(dir5, CHAT);
                            if(strP(uip,global) )
                            {
                        strcat(dir5,uip);
                        strcat(dir5," ");
                        strcat(dir5,global);
                        strcat(dir5,".txt");
                            }
                            else
                            {
                        strcat(dir5,global);
                        strcat(dir5," ");
                        strcat(dir5,uip);
                        strcat(dir5,".txt");
                            }   
                
                            FILE* f4 = fopen(dir5, "r");
                            char store[12]="";int k ;
                            for( k = 0 ; k < 12 ; k++)
                            store[k] = fgetc(f4);
                            store[k] = '\0' ; 
                            fclose(f4);
                            f4 = fopen(dir5, "w");
                            fprintf(f4,"%s",store);
                            fclose(f4);
                            goto ggg;
                    }
                    

        }
        else
        {
            printf("\n            \t|\t  invalid input, try again: ");
            goto use;
        }

    }
    
    else 
    {
        none:;
        printf("\n\t\t|\t  elpmis doesnt recognise %s as your friend, enter 'retry' to try again or\nenter 'back' to redirect to main menu\n\t\t\t  ",uip);
        fflush(stdin);
        char choice[25];
        scanf("%[^\n]s",choice);
        for(int i = 0 ; i < strlen(choice); i++)choice[i]= tolower(choice[i]);
        if(strcmp(choice,"retry")==0 || strcmp(choice,"'retry'")==0)
        {
            goto use;
        }
        else if(strcmp(choice,"back")==0 || strcmp(choice,"'back'")==0)
        {   
            
            display_options(1);
        }
        
    }
}

void displayChat(char* u1, char* u2, int p)
{
    system("cls");
    printf("  Chat       x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://mail.elpmis.com/chats   \n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	
	printf("\n   Elpmis +\t|\t\t\t\t\t\t\t\t\t\t\t\t  | | |");
	printf("\n\n");
    
    char dir4[50] = "" ;
    strcat(dir4, CHAT);
    strcat(dir4,u1);
    strcat(dir4," ");
    strcat(dir4,u2);
    strcat(dir4,".txt");
    //printf("%s",dir4);
    FILE* f = fopen(dir4,"r");//
    int count=0;
    while(fgetc(f)!='\n' && !feof(f));//date
    
    while(!feof(f))
    {
        while(fgetc(f)!='\n' && !feof(f));//
        count++;
    }
    fclose(f);
    f = fopen(dir4,"r");
    
    while(fgetc(f)!='\n' && !feof(f));// date
    if(p == 1)
    {
        while(count>=20)
        {
        while(fgetc(f)!='\n' && !feof(f));
        count--;
        }
    }
    
        
        printf("\n\t");    
    
        while(!feof(f))
        {
        char tmp = fgetc(f);

        while(tmp!= ' ' && !feof(f))
        {
            if(tmp != '\n')
            printf("%c",tmp);
            tmp = fgetc(f);
        }
        if(feof(f))break;
        if(tmp == ' ')
        {
            printf("\t|\t  ");
        }
        tmp = fgetc(f);
        while(tmp!= '\n' && !feof(f))
        {
            printf("%c",tmp);
            tmp = fgetc(f);
        }
        if(feof(f))break;
        if(tmp=='\n') printf("\n\t");

        }
    fclose(f);


}

void delUtility(char* dir)
{
    printf("delutility called for %s \n",dir);
    char dir1[30]="";
    strcat(dir1,dir);
    strcat(dir1,global);
    strcat(dir1,".txt");
    FILE* f;
    if(access(dir1,F_OK)==0)
    {
        f = fopen(dir1, "r");
        printf("opening %s in r ",dir1);
    }
    else
    {
        printf("%s doesnt exist ",dir1);
        return ;
    }
    if(!feof(f))
    fgetc(f);
    if(feof(f))
    {
        fclose(f);
        printf("it is empty, deleting it, status : %d \n",remove(dir1));
        return ;
    }
    printf("%s is not empty, iterating next line ",dir1);
    while(!feof(f))
    {
        char tmp[30]="";
        char x ; int i = 0; 
        x = fgetc(f);
        while(x!=' ' && !feof(f))
        {
            tmp[i++]=x;
            if(!feof(f))//why
            x=fgetc(f);//asdefghtfrdewsdfghgfredfghn7
        }
        tmp[i]='\0';
        if(strlen(tmp)==0)continue;
        if(strcmp(dir,REQ)==0)
        {
            deletionUtility(tmp,global,REQ,0);
            //deletionUtility(global,tmp,REQ,0);
        }
        

        else{
            deletionUtility(tmp,global,BLOCK,1);
            deletionUtility(tmp,global,BLOCK,0);
        }
        
        fgetc(f);// spacebar recieved, 1/0
        if(!feof(f))fgetc(f); // '\n or eof
        
    }
    fclose(f);
    printf("okay, did some deleting, now deletin %d ", remove(dir1));
}

void deleteUser()
{   
    char d1[50] = "casual\\"; 
    strcat(d1,"sos\\");
    strcat(d1,global);
    strcat(d1,".txt");
    char d2[50] ="casual\\"; 
    strcat(d2,"dot\\");
    strcat(d2,global);
    strcat(d2,".txt");
    remove(d1);
    remove(d2);
    char d3[50]="";
    strcat(d3,GAME);
    strcat(d3,global);
    strcat(d3,".txt");
    remove(d3);

    deletionUtility("deactivated_db.txt",global,REQ,0);
    delUtility(REQ);
    delUtility(BLOCK);
    delete_file();
    delay(200);
    getch();
}


void gameZone(int flag)
{
    system("cls");
	
	printf(" Game Zone      x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://mail.elpmis.com/%s/gameZone \n",global);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*select     |      enter 'select' to select a game ");
	printf("\n            \t|\t  -------------");
    printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*scores     |      enter 'scores' to view your scores of all games ");
	printf("\n            \t|\t  -------------");
    printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*back       |      enter 'back' to direct back");
	printf("\n            \t|\t  -------------");
	printf("\n            \t|");
    if(flag==1)
	printf("\n            \t|\t  Enter Your choice: ");
    else
    printf("\n            \t|\t  invalid input, try again: ");
    fflush(stdin);
    char choice[20]="\n" ;;
    scanf("%[^\n]s",choice);
    if(strcmp(choice,"\n")==0)display_options(1);
    for(int i = 0 ; i < strlen(choice); i++)choice[i]= tolower(choice[i]);

    if(strcmp(choice,"select")==0 || strcmp(choice,"'select'")==0)
    {
        flw:;
        printf("\n            \t|\t  Enter the game name from the following or enter 'back' to go back ");
        printf("\n            \t|\t  Competitive games: ");
        printf("\n            \t|\t  2048 ");
        printf("\n            \t|\t  snake ");
        printf("\n            \t|\t  Local Multiplayer games: ");
        printf("\n            \t|\t  SOS ");
        printf("\n            \t|\t  DOTS-AND-BOXES ");
        flaf:;
        printf("\n            \t|\t  ");
        fflush(stdin);
        scanf("%[^\n]s",choice);
        if(strcmp(choice,"\n")==0)display_options(1);
        for(int i = 0 ; i < strlen(choice); i++)choice[i]= tolower(choice[i]);
        if(strcmp(choice,"2048")==0 || strcmp(choice,"'2048'")==0 || strcmp(choice,"snake")==0 || strcmp(choice,"'snake'")==0)
        {
            if(strcmp(choice,"snake")==0)
            {
                printf("\n            \t|\t  Currently snake is unavailable, please try again later. Press any key to direct back");
                getch();
                goto flw; 
            }
            qas:;
            printf("\n            \t|\t  Enter 'score' to view yours or your friends' scores of this game");
            printf("\n            \t|\t  Enter 'play' to play %s or enter 'back' to go back",choice);flaq:;
            char cho[50];
            fflush(stdin);printf("\n            \t|\t  ");
            scanf("%[^\n]s",cho);
            for(int i = 0 ; i < strlen(cho); i++)cho[i]= tolower(cho[i]);
            if(strcmp(cho,"score")==0 || strcmp(cho,"'score'")==0)
            {
                
                printf("\n            \t|\t  Enter 'mine' or your friend's username or enter 'back' to go back\n            \t|\t  ");
                fflush(stdin);
                scanf("%[^\n]s",cho);
                for(int i = 0 ; i < strlen(cho); i++)cho[i]= tolower(cho[i]);
                if(strcmp(cho,"back")==0 || strcmp(cho,"'back'")==0)
                goto qas;
                else if((username_checker(cho) && isFriend(global,cho) && !checkRSB(cho,1,BLOCK) && !checkRSB(cho,0,BLOCK) && !isDeactivated(cho)) || strcmp(cho,"mine")==0)
                {
                   // printf("gmae: %s use: %s global: %s \n",choice,cho,global);
                    
                    if(strcmp(cho,"mine")==0)
                    getOrUpdateScore(choice,global,-1);
                    else
                    getOrUpdateScore(choice,cho,-1);
                    printf("\n            \t|\t  Press amy key to go back\n");
                    getch();
                    goto qas;
                }
                else if(username_checker(cho) && isUsername(cho) )
                {
                    printf("\n            \t|\t  Invalid username. Press any key to redirect back");
                    getch();
                    goto flw;

                }
                else
                {
                    printf("\n            \t|\t  Invalid input. Press amy key to go back\n");
                    getch();
                    goto flw;
                }

            }
            else if(strcmp(cho,"back")==0 || strcmp(cho,"'back'")==0)
            {
                goto flw;
            }
            else if(strcmp(cho,"play")==0 || strcmp(cho,"'play'")==0)
            {
                system("cls");
                int score = game_2048();
                getOrUpdateScore(choice,global,score);
                printf("\n            \t|\t  Your score has been saved. Press amy key to go back\n");
                getch();
                gameZone(1);

                
            }
            else
            {
                printf("\n            \t|\t  Invalid choice, try again");
                goto flaq;
            }

        }
        else if(strcmp(choice,"dots-and-boxes")==0 || strcmp(choice,"'dots-and-boxes'")==0 || strcmp(choice,"sos")==0 || strcmp(choice,"'sos'")==0)
            {   gtr:;
                printf("\n            \t|\t  Enter 'play' to play %s ",choice);
                printf("\n            \t|\t  Enter 'history' to view game history, or 'back' to go back \n            \t|\t  ");
                char ch[50] = "\n" ;
                gtl:;
                fflush(stdin);
                scanf("%[^\n]s",ch);
                for(int i = 0 ; i < strlen(ch); i++)ch[i]= tolower(ch[i]);

                if(strcmp(ch,"play")==0 )
                {
 
                    printf("\n            \t|\t  enter player 1 name \n          \t|\t  ");
                    char pl1[50]="\n", 
                    pl2[50]="\n" ;
                    gt1:;
                    fflush(stdin); 
                    scanf("%[^\n]s",pl1);
                    if(strcmp(pl1,"\n")==0)
                    {
                        printf("\n            \t|\t  please enter a name to continue\n          \t|\t  ");
                        goto gt1;
                    }
                    if(strlen(pl1)>50)
                    {
                        printf("\n            \t|\t  please enter a name of length not more than 50");
                        goto gt1;
                    }
                    printf("\n            \t|\t  enter player 2 name \n          \t|\t  ");
                    gt2:;
                    fflush(stdin); 
                    scanf("%[^\n]s",pl2);
                if(strcmp(pl2,"\n")==0)
                {
                    printf("\n            \t|\t  please enter a name to continue\n          \t|\t  ");
                    goto gt2;
                }
                if(strlen(pl2)>50)
                {
                    printf("\n            \t|\t  please enter a name of length not more than 50\n          \t|\t  ");
                    goto gt2;
                }
                int arr[2];
                int sts ;
                fflush(stdin);
                if(strcmp(choice,"dots-and-boxes")==0 || strcmp(choice,"'dots-and-boxes'")==0 )
                game_dot(pl1,pl2,arr);
                else
                sts = game_sosUtility(pl1, pl2,arr);
                if(sts==-1)
                goto flw;
                char* win; 
                if(arr[0]>arr[1])
                win = pl1; 
                else if(arr[1]>arr[0])
                win = pl2;
                else
                win = "draw" ;
                char dir[60] = "";
                strcat(dir,"casual\\");
                
                if(strcmp(choice,"dots-and-boxes")==0)
                strcat(dir,"dot");
                else
                strcat(dir,choice);
                strcat(dir,"\\");
                strcat(dir,global);
                strcat(dir,".txt");
                
                FILE* f = fopen(dir,"a");
                char tmp[50];
                fprintf(f,"            \t|\t  %s vs %s result: %s:%d %s:%d  winner:%s\n",pl1,pl2,pl1,arr[0],pl2,arr[1],win);
                fclose(f);
                printf("\n            \t|\t  Press any key to go back");
                getch();
                goto flw; 
                    
                }
                else if(strcmp(ch,"history")==0)
                {
                    int n  = history(choice,0);
                    if(n==-1)
                    {
                        printf("\n            \t|\t  No history of playing. Enter any key to go back");
                        getch();
                        goto gtr;
                    }
                    

                    if(n>20)
                    printf("\n            \t|\t  Enter 'full' to generate full history or enter 'clear' to clear history");
                    else
                    printf("\n            \t|\t  Enter 'clear' to clear history");
                    printf("\n            \t|\t  Enter 'back' to go back            \t|\t  ");
                    fcd:;
                    fflush(stdin);
                    scanf("%[^\n]s",ch);
                    if(strcmp(ch,"full")==0)
                    {
                        history(choice,1);
                        printf("\n            \t|\t  Press anhy key to go back");
                        getch();
                    }
                    else if(strcmp(ch,"clear")==0)
                    {
                        char dir[50] = "";
                        strcat(dir,choice);
                        strcat(dir,"\\");
                        strcat(dir,global);
                        strcat(dir,".txt");
                        FILE* f = fopen(dir,"w");
                        fclose(f);
                        printf("\n            \t|\t  History cleared. Press any key to continue");
                        goto qas;
                    }
                    else if(strcmp(ch,"back")==0)
                    {
                        goto gtr;
                    }
                    else
                    {
                        printf("\n            \t|\t  invalid choice, try again");
                        goto fcd;
                    }
                }
                else if(strcmp(ch,"back")==0)
                {
                    goto flw;
                }
                else
                {
                    printf("\n          \t|\t  invalid choice, try again");
                    goto gtl;
                }
                

            }
        else if(strcmp(choice,"back")==0 || strcmp(choice,"'back'")==0)
        {
            gameZone(1);
        }
        else
        {
            printf("\n            \t|\t  Invalid choice, try again");
            goto flaf;
        }
        
    }
    else if(strcmp(choice,"scores")==0 || strcmp(choice,"'scores'")==0)
    {
        char d[50] ="";
        strcat(d,GAME);
        strcat(d,global);
        strcat(d,".txt");
        FILE* f = fopen(d,"r");
        char c = fgetc(f);
        
            printf("\n            \t|\t  ");
            while (c != EOF)
            {
            printf ("%c", c);
            c = fgetc(f);
            if(c=='\n')
            {
                c=fgetc(f);printf("\n            \t|\t  ");
            }
            
            }
            printf("\n            \t|\t  Press any key to redirect back");
            getch();
            fclose(f);
            gameZone(1);
        

    }
    else if(strcmp(choice,"back")==0 || strcmp(choice,"'back'")==0)
    {
        display_options(1);
    }
    else
    {
        gameZone(0);
    }
}
        
void getOrUpdateScore(char* game, char* user, int score ) // even used to update score (when score is -1, it means getScore, else update)
{
    char d[50]="";
    strcat(d,GAME);strcat(d,user);strcat(d,".txt");
    //printf("%s\n",d);
    FILE* f = fopen(d,"r");
    char st[50], x = fgetc(f);
    int p=0;
    if(feof(f) && strcmp(user,global)==0)
    printf("\n            \t|\t  You have not played any game so far. press any key to redirect back");
    else if(feof(f))
    printf("\n            \t|\t  %s has not played any game so far. press any key to redirect back",user);
    else
    {
        while(!feof(f))
        {
            // we know space exists 0 0 0 0 
            while(x!=' ')
            {
            st[p++]=x ;
            x = fgetc(f);

            }st[p]='\0';

            if(strcmp(st,game)==0)
            {
            //print the scores now in appropriate way 
            // or update 
                if(score == -1 )
                {printf("\n            \t|\t  ");
                //getscore here
              //  printf("getscore");
                while(1)
                {   x = fgetc(f);
                if(x=='\n' || feof(f)) break;
                printf("%c",x);
                if(x==' ')printf("\n            \t|\t  ");

                }
                printf("\n");
                fclose(f);
                return ;

                }
                else
                {
                //update score here
                //printf("update");
                int arr[5], ii=0;
                
                //x= fgetc(f);
                //printf("got x = %c ",x);
                int flagg=0;
                while(1)
                {
                   // printf("iteration \n");
                    //x= fgetc(f);
                    //printf("got x = %c ",x);
                    if(feof(f)) break;
                    
                    char tmp[5]="";
                    int it = 0 ; 
                    while( 1)
                    {
                        x = fgetc(f);
                      //  printf("got x = %c ",x);
                        if(x=='\n'){
                            flagg=1;break;}
                        else if(x==' ' ||feof(f) )break;

                        //    printf("tm[%d]=%c \n",it,x);
                            tmp[it++]=x;

                            
                    }tmp[it]='\0';
                 //   printf("ended..");
                 //   printf("arr[%d]=%d",ii,atoi(tmp));
                    arr[ii++]=atoi(tmp);
                    //if(feof(f)) break;
                    if(flagg==1)break;
                }
                
                
              //  printf("array \n");
                for(int i = 0 ; i < ii; i++)
               // printf("%d ",arr[i]);
                
                if(score<= arr[ii-1])
                {
                    fclose(f);return ;
                }
                //int t ;
                for(int i = 0 ;  i < ii ;i++)
                {
                    
                    if(arr[i]<=score)
                    {
                        for(int j = ii-1; j>i;j--)
                        {
                            arr[j]=arr[j-1];
                        }
                        arr[i]=score;
                        break;

                    }
                }

           //     printf("array \n");
          //      for(int i = 0 ; i < ii; i++)
             //   printf("%d ",arr[i]);
                
                fclose(f);
            //    printf("calling the rewe %s  \n",d);
                rewrite(d,game,arr);
                return;
                }
            }
         //   printf("wsedfg");
            p=0;
            while(fgetc(f)!='\n' && !feof(f));
            if(!feof(f))
            {
                x =fgetc(f);
            }
            else{
               // printf("cvbhj");
                fclose(f);
            }
            
        }
        
    }    
}

void rewrite(char* dir, char* game, int* arr)
{
    
    FILE* f = fopen(dir,"r");
    FILE* w = fopen("ttmp.txt","w");

    char st[50];
        char x = fgetc(f);
        while(!feof(f))
        {
            // we know space exists 0 0 0 0 
            int p = 0 ; 
            while(x!=' ')
            {
            st[p++]=x ;
            x = fgetc(f);

            }st[p]='\0';

            fprintf(w,"%s ",st);
            if(strcmp(st,game)==0)
            {
                char buff[10];
                for(int i = 0 ; i < 5 ; i++)
                {
                    if(i!=4)
                    fprintf(w,"%s ",itoa(arr[i],buff,10));
                    else
                    fprintf(w,"%s",itoa(arr[i],buff,10));
                }
                fputc('\n',w);
                //copy the array and \n
                //skip the line 
                while(fgetc(f)!='\n');

               
            }
            else
            {
                //copy till the end of line and  \n  
                x = fgetc(f);
                while(x!='\n')//eof doesnt occur in same line
                {
                    fputc(x,w);
                    x=fgetc(f);
                }
                fputc('\n',w);
            }
                
             x=fgetc(f); // the character of next line
             // it oculd either be EOF or the 1st character of a game
                
            
        }
    fclose(f);
    fclose(w);
    f = fopen("ttmp.txt","r");
    w = fopen(dir,"w");

    x = fgetc(f);
    while(1)
    {
        if(x!=EOF)
        fputc(x,w);
        else
        break;
        x = fgetc(f);
    }
    fclose(f);
    fclose(w);
    remove("ttmp.txt");
}


int history(char* game, int full)
{
    
    
    char dir[50] = "casual\\";
    strcat(dir,game);
    strcat(dir,"\\");
    strcat(dir,global);
    strcat(dir,".txt");
    FILE* f;
    if(access(dir,0)==0)
    f = fopen(dir,"r");
    else
    return -1 ;

    char x;
    if(full==1)
    goto ff;

    // to count the no.of lines 
    int n = 0 ; 
    
    while(!feof(f))
    {
         x = fgetc(f); 
        while(x!='\n' && x!= EOF)
        {
            x = fgetc(f);
        }
        n++;
    }
    
    
    int m=0 ;
    if(n > 20)
    {
        m = n - 21 ;
    }
    fclose(f);



    f = fopen(dir,"r");
    //FILE* w = fopen(dir,"w");

    while(m!=0)
    {
        x = fgetc(f); 
        while(x!='\n' && x!= EOF)
        {
            x = fgetc(f);
        }
        m--;
        //printf("n++");
    }
    printf("\n");
    ff:
    while(1)
    {
        x = fgetc(f) ;
        if(x==EOF)break ;
        printf("%c",x);
    }


   // fclose(w);
    fclose(f);
    return n ;// no.of lines

}

/*******************************************************************friends-management-functions************************************************************************************/


void manage(int flag)
{   
    
    fla:;
    system("cls");
	printf(" Manage        x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://elpmis.com/%s/manage \n",global);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n   ELPMIS +\t|\t\t\t\t\t\t\t\t\t\t\t\t  | | |");
	printf("\n            \t|\t");
	printf("\n            \t|\t");
	printf("\n            \t|\t  Greetings %s!", getname(global) );
	printf("\n            \t|\t");
	printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*profile     |      enter 'profile' to view your profile ");
	printf("\n            \t|\t  -------------");
	printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*search      |      enter 'search' to search for a profile ");
	printf("\n            \t|\t  -------------");
    printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*requests    |      enter 'requests' to view pending requests");
	printf("\n            \t|\t  -------------");
    printf("\n            \t|\t  _____________");
	printf("\n            \t|\t  |*back        |      enter 'back' to redirect back");
	printf("\n            \t|\t  -------------");
	printf("\n            \t|") ;
    if(flag==1)
	printf("\n            \t|\t  Enter Your choice: ");
    else
    printf("\n            \t|\t  invalid input, try again: ");
    fflush(stdin);
    char choice[20]="\n" ;
    fflush(stdin);
    scanf("%[^\n]s",choice);
    if(strcmp(choice,"\n")==0)manage(1);
    for(int i = 0 ; i < strlen(choice); i++)choice[i]= tolower(choice[i]);
    if(strcmp(choice,"profile")==0 || strcmp(choice,"'profile'")==0)
    { 
       profile(global,1)       ;
    }
    else if(strcmp(choice,"search")==0 || strcmp(choice,"'search'")==0)
    {
        searchPage();
    }
    else if(strcmp(choice,"requests")==0 || strcmp(choice,"'requests'")==0)
    {
    
        requestsPage();
        
    }
    else if(strcmp(choice,"back")==0 || strcmp(choice,"'back'")==0)
    {
        printf("\n            \t|\t  redirecting back.... \n");
        delay(1500);
        display_options(1);
    }
    else
    {       
       manage(0);
    }
}

int isFriend(char* user1, char* user2 )
{
    if(strP(user1,user2))
    {
        char dr[50] = "" ;
        strcat(dr,CHAT);
        strcat(dr,user1);
        strcat(dr," ");
        strcat(dr,user2);
        strcat(dr,".txt");
        if (access(dr, F_OK) == 0) 
        return 1 ;
        else 
        return 0;
    }else
    return isFriend(user2, user1);
}

int addFriend(char*user1)
{
    char filee[] = "" ;
    strcat(filee,USERDB);
    strcat(filee, user1);
    strcat(filee,".txt");
    FILE* f = fopen(filee, "a");
    fprintf(f , "\n%s",global);
    fclose(f);

    char fileee[] = "" ;
    strcat(fileee,USERDB);
    strcat(fileee, global);
    strcat(fileee,".txt");
    f = fopen(fileee, "a");
    fprintf(f , "\n%s",user1);
    fclose(f);

    char file[] = "" ;
    strcat(file,CHAT); 
    if(strP(user1,global))
    {
        strcat(file,user1);
        strcat(file," ");
        strcat(file,global);
    }
    else{
        strcat(file,global);
        strcat(file," ");
        strcat(file,user1);
    }
    strcat(file,".txt");
    
    FILE* ptr = fopen(file,"w"); 
    fclose(ptr); 
    return 1;     
}

void sendRequest(char* ok)
{
    // global is sending request to ok 
    char dir1[50] ="";
    strcat(dir1,REQ);
    strcat(dir1,global);
    strcat(dir1,".txt");
    FILE* f = fopen(dir1,"a");
    fprintf(f, "\n%s 1",ok);
    fclose(f);

    char dir2[50]="";
    strcat(dir2,REQ);
    strcat(dir2,ok);
    strcat(dir2,".txt");
    f = fopen(dir2,"a");
    fprintf(f, "\n%s 0",global);
    fclose(f);

}

int checkRSB(char* ok,  int s, char* dir)
{
    // already we know that ok exists, and is not equal to global
    char dir1[50] ="";
    strcat(dir1,dir);
    strcat(dir1,global);
    strcat(dir1,".txt");
    FILE* f = fopen(dir1,"r");
    if(f== NULL)
    return 0;
    fgetc(f); // newline, now pointing to target area
     
    while(!feof(f))
    {
        char tmp[30] = "" ;
        int i = 0 ;

        char x = fgetc(f);
        while( x!='\n' && !feof(f) )
        {
            tmp[i++] = x; 
            x = fgetc(f);
        }
        tmp[i]='\0';
        
        char cmp[30] = "" ;
        strcat(cmp,ok);

        if(s == 1)
        strcat(cmp," 1");
        else
        strcat(cmp," 0");
        strcat(cmp,"\0");
        
        if(strcmp(tmp,cmp)==0)
        {
            return 1 ;
        }
        
    }
    fclose(f);
    return 0 ;
}

void deletionUtility(char* u1, char* u2, char* dir, int blocknum)
{
    //printf("\ndeletionUtility called %s %s %s %d \n",u1,u2,dir,blocknum);
    if(strlen(u2)==0)
    return ;
    FILE* f ;
    char dir1[30]= "";
    if(strcmp(u1,"deactivated_db.txt")==0)
    {
        f = fopen(u1,"r");
    }
    else
    {
    //delete the request from friends
    //addfriend on userdb 
        strcat(dir1,dir);
        strcat(dir1,u1);
        strcat(dir1,".txt");
       // printf("opening %s in r ",dir1);
        f = fopen(dir1,"r");
        //printf("%s \n",dir1);
    }
    FILE* w = fopen("requests_db\\tmmp.txt","w");
    char x;

    //we know both files have atleast one line
   fputc(fgetc(f),w); // '\n' starting
    if(feof(f))
    {
        fclose(w);
        remove("requests_db\\tmmp.txt");
        return ;
    }
    
    if(strcmp(dir,BLOCK)==0  ) 
    {
        while(!feof(f))
        {
        char buf[30]= ""; 
        int i =0 ; 

        x = fgetc(f);
        if(feof(f))break;

        while(x!='\n' && !feof(f))
        {
            buf[i++] = x; //why?.
            x = fgetc(f);
        }
        buf[i] = '\0';
        char cm[30] ="";
        strcat(cm,u2);
        if(blocknum==1)
        strcat(cm," 1");
        else
        strcat(cm," 0");
        if(strcmp(buf,cm)==0)
        {
            // \n already caught
            ;
        }
        else
        {
            fprintf(w,"%s\n",buf);
            
        }
        
        }
    }
    else
    {
        while(!feof(f))
        {
        char buf[30]= ""; 
        int i =0 ; 

        x = fgetc(f);
        if(feof(f))break;
        if(strcmp(u1,"deactivated_db.txt")==0 || blocknum ==3)
        //block num = 3 => userdb deletion utility
        {
            while(x!='\n' && !feof(f))
            {
            buf[i++] = x; ////
            x = fgetc(f);
            }
            buf[i] = '\0';
            if(strcmp(buf,u2)==0)
            {
            ;
            }
            else
            {
            fprintf(w,"%s\n",buf);
            }
        }
        else
        {
            while(x!=' ')
            {
            buf[i++] = x; 
            x = fgetc(f);
            }
        buf[i] = '\0';
        if(strcmp(buf,u2)==0)
        {
            // space already caught
            fgetc(f); // '1'/'0'
            if(feof(f))break;
            fgetc(f); // '\n' 
            if(feof(f))break;
        }
        else
        {
            fprintf(w,"%s ",buf);
            fputc(fgetc(f),w); // 1/0
            if(feof(f))break;
            char x = fgetc(f); // '\n' or eof
            if(feof(f))break;
            fputc(x,w);
        }
        }
        
        }
    }
    
    //fputs("\n\n", w);
    //trim("tmmp",REQ);
    fclose(f);
    fclose(w);
    trim("tmmp",REQ);
    //printf("...");
    if(strcmp(u1,"deactivated_db.txt")==0)
    w = fopen("deactivated_db.txt","w");
    else
    w = fopen(dir1,"w");
    f = fopen("requests_db\\tmmp.txt","r"); 
    while(1)
    {
        char t= fgetc(f);
        if(feof(f))break;
        fputc(t,w);
    }
    fclose(w);
    fclose(f);
    remove("requests_db\\tmmp.txt");
   // printf(",,,");
}

void acceptRequest(char* u2)
{

    char dii[30] = "" ; 
    strcat(dii,USERDB);
    strcat(dii,global);
    strcat(dii,".txt");

    char dij[30] = "" ; 
    strcat(dij,USERDB);
    strcat(dij,u2);
    strcat(dij,".txt");

    FILE* w = fopen(dii,"a");
    fprintf(w,"\n%s",u2);
    fclose(w);
    w = fopen(dij,"a");
    fprintf(w,"\n%s",global);
    fclose(w);

    deletionUtility(global,u2,REQ,0);
    
    deletionUtility(u2,global,REQ,0);
   

    char dir[50]= "" ;
    strcat(dir,CHAT);
    if(strP(global,u2))
    {
        strcat(dir,global);
        strcat(dir," ");
        strcat(dir,u2);
        strcat(dir,".txt");
    }
    
    else
    {
        strcat(dir,u2);
        strcat(dir," ");
        strcat(dir,global);
        strcat(dir,".txt");
    }
    FILE* ww = fopen(dir,"w");
    char new[24]; char* x =getTime(new);
    for(int i = 0 ; i < 11; i++)
    fprintf(ww,"%c",x[i]); 
    fclose(ww);
    
}

int displayProfile(char* ok)
{
    system("cls");
    int z = 0 ; 
    if(strcmp(ok,global)==0)
    z=1;

    printf(" Elpmis        x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://mail.elpmis.com/%s/profile\n",ok);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
    

    // fine till here

    char dir[30]="";
    strcat(dir,USERDB);
    strcat(dir,ok);
    strcat(dir,".txt");

    FILE* f = fopen(dir,"r");

    if(z==0)
	printf("\n            \t|\t  %s's profile:",ok);
    else
    printf("\n            \t|\t  Your profile:");

    while(fgetc(f)!='\n'); //username
    while(fgetc(f)!='\n'); //password
    printf("\n            \t|\t  FULL NAME: ");
    char x = fgetc(f);
    while(x!='\n')  //fname
    {
        printf("%c",x);
        x=fgetc(f);
    }printf(" ");

    x=fgetc(f);
    while(x!='\n')  //lname
    {
        printf("%c",x);x=fgetc(f);
    }

    // to avoid showing security question and answer
    while(fgetc(f)!='\n');

    printf("\n            \t|\t  ELPMIS MEMBER SINCE: ");
    while(1)    //date
    {
        x = fgetc(f);
        if(feof(f) || x=='\n')break;
        
        printf("%c",x);
    }
    printf("\n            \t|\t  Number of Friends: %d",numFriends(ok,0));
    if(z==1)
    {

        fclose(f);
        
     return 2 ;
     //fine
    }

    if(isFriend(global,ok))
    {
        printf("\n            \t|\t  Friend since: ");
        
        char dir2[50]="";
        strcat(dir2,CHAT);
        if(strP(global,ok))
        {
        strcat(dir2,global);
        strcat(dir2," ");
        strcat(dir2,ok);
        strcat(dir2,".txt");
        }
    
        else
        {
        strcat(dir2,ok);
        strcat(dir2," ");
        strcat(dir2,global);
        strcat(dir2,".txt");
        }

        FILE* f2 = fopen(dir2,"r");
        char c = fgetc(f2);
        
        while(c != '\n' && !feof(f2))
        {
            
            if(feof(f2))break;
            printf("%c",c);
            c =fgetc(f2);
            //printf("here?");
        }
        fclose(f2);
        fclose(f);
        /*char del[40]="user_db\\"; strcat(del,global);strcat(del,".txt");
    printf("%s -> %d",del,unlink(del));
    delay(3000);
    //return 0;*/
        return 1; 
    }
    else
    {
        printf("\n            \t|\t  %s is not your friend ",ok); 
        fclose(f);

        /*char del[40]="user_db\\"; strcat(del,global);strcat(del,".txt");
    printf("%s -> %d",del,unlink(del));
    delay(3000);*/
    
        return 0;
    }
    
	
}

void block(char* ok)
{
    // ok != global
    // ok should be a friend

    // global blocks ok 

        /// ok will be deleted from global
        /// global will be deleted from ok
        // ok.txt will append global 0
        // global.txt will append ok 1
        ///deleteFriend(global,ok);
        ///deleteFriend(ok,global);

        char d1[30]= "";
        strcat(d1,BLOCK);
        strcat(d1,global);
        strcat(d1,".txt");

        char d2[30]="";
        strcat(d2,BLOCK);
        strcat(d2,ok);
        strcat(d2,".txt");

        printf("%s %s \n",d1,d2);

        FILE* f = fopen(d1,"a");
        fprintf(f,"\n%s 1",ok);
        fclose(f);
        f = fopen(d2,"a");
        fprintf(f,"\n%s 0",global);
        fclose(f);

 }

void unBlock(char* ok)
{
    //global unblocks ok
    //deleting ok 1 from global.txt
    // deleteing global 0 from ok.txt
    // ignoring ok 0 in global.txt and global 1 in ok.txt
    deletionUtility(global,ok,BLOCK,1);
    deletionUtility(ok,global,BLOCK,0);
}

void searchPage( )
{
        system("cls");
        printf(" search       x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	    printf("----------------------------------------------------------------------------------------------------------------------\n");
	    printf("<-  ->    | http://elpmis.com/%s/search \n",global);
	    printf("----------------------------------------------------------------------------------------------------------------------\n");
	    printf("\n   ELPMIS  +\t|\t\t\t\t\t\t\t\t\t\t\t\t  | | |\n");
	    printf("\n            \t|\t  enter username (case-sensitive) of anyone to view their profile or enter 'back' to go back \n            \t|\t  ");
        fflush(stdin);
        char choice[30]="\n";
        scanf("%[^\n]s",choice);   
        if(strcmp(choice,"\n")==0)
        searchPage();
        f3:;
        if(strcmp(choice,"back")==0 || strcmp(choice,"Back")==0 || strcmp(choice,"BACK")==0 ||strcmp(choice,"'back'")==0 )
        {
            printf("\n            \t|\t  redirecting back.... \n");
            delay(1500);
            manage(1);
        }else 
        if(username_checker(choice)&& isUsername(choice))     
        {
            if(checkRSB(choice,0,BLOCK) || (isDeactivated(choice)))
            {
                printf("u r blocked / acc deactivated");
                delay(2000);
                goto g4; //shouldnt recognise
            }
            else if(checkRSB(choice,1,BLOCK) )
            {
                printf("\n            \t|\t  %s is in your blocked list, enter 'unblock' to view profile ",choice);
                printf("\n            \t|\t  or enter 'retry' to search different username or enter 'back' to redirect back ");
                fflush(stdin);
                char ch[30];
                scanf("%[^\n]s",ch); 
                for(int i = 0 ; i < strlen(ch); i++)ch[i]= tolower(ch[i]);
                if((strcmp(ch,"unblock")==0 || strcmp(ch,"'unblock'")==0) )
                {
                    unBlock(choice);
                    printf("\n            \t|\t  %s is now unblocked, press any key to view his profile",choice);
                    getch();
                    goto f3; 
                }

            }
            else if(displayProfile(choice) == 0) // not a friend
            {
                int a = 0 ; 
                if(checkRSB(choice,1,REQ)==0 && checkRSB(choice,0,REQ)==1 ) // didnt send request but recieved request //accept?
                a= 1 ;
                if(checkRSB(choice,0,REQ)==0 && checkRSB(choice,1,REQ)==1 ) // sent request but no response //unsend?
                a= 2;
                else if(checkRSB(choice,0,REQ)==0 && checkRSB(choice,1,REQ)==0 )
                a= 3 ; // no one requested none //request?
                else ;

                if(a==3)
                printf("\n            \t|\t  enter 'request' to send Request to %s",choice);
                else if(a==2)
                printf("\n            \t|\t  Sent request is pending. enter 'unsend' to unsend the sent request ");
                else if(a==1)
                printf("\n            \t|\t  Recieved request already, enter 'accept' to accept");

                printf("\n            \t|\t  or enter 'block' to blcok %s, or enter 'back' to go back\n            \t|\t  ",choice);
                f2:;
                fflush(stdin);
                char ch[30];
                scanf("%[^\n]s",ch); 
                for(int i = 0 ; i < strlen(ch); i++)ch[i]= tolower(ch[i]);
                if((strcmp(ch,"request")==0 || strcmp(ch,"'request'")==0) && a==3)
                {
                    sendRequest(choice);
                    printf("\n            \t|\t  sent request successfully, press any key to redirect back");
                    getch();
                    manage(1);

                }
                else if((strcmp(ch,"unsend")==0 || strcmp(ch,"'unsend'")==0) && a==2)
                {
                    deletionUtility(global,choice,REQ,0);
                    deletionUtility(choice,global,REQ,0);
                    printf("\n            \t|\t  undone request to %s, press any key to redirect back",choice);
                    getch();
                    searchPage();
                }
                else if((strcmp(ch,"accept")==0 || strcmp(ch,"'accept'")==0) && a==1)
                {
                    acceptRequest(choice);
                    printf("\n            \t|\t  %s is now your friend, press any key to redirect back",choice);
                    getch();
                    searchPage();
                }
                else if(strcmp(ch,"block")==0 || strcmp(ch,"'block'")==0)
                {
                    printf("\n            \t|\t  untill you unblock %s, %s cannot acess your profile, chats or game scores",choice,choice);
                    block(choice);
                    printf("\n            \t|\t  %s is blocked. press any key to continue",choice);
                    getch();
                    searchPage();
                    
                }
                else if(strcmp(ch,"back")==0 || strcmp(ch,"'black'")==0)
                {
                    manage(1);
                }
                else
                {
                    printf("\n            \t|\t  invalid input, try again: ");
                    goto f2;
                }

            }
            else
            {
                int a=0;
                if(strcmp(choice,global)==0)
                a = 1; 
                else
                a =2 ;
                profile(choice,a);
            }
            
        }
        else
        {
            g4:;
            printf("\n            \t|\t  username %s is not in elpmis database ",choice);
            printf("\n            \t|\t  enter 'retry' to try other username or  ",choice);
            printf("\n            \t|\t  enter 'back' to redirect back");
            printf("\n            \t|\t  ");
            g1:;
            fflush(stdin);
            scanf("%[^\n]s",choice);
            for(int i = 0 ; i < strlen(choice); i++)choice[i]= tolower(choice[i]);

            if(strcmp(choice,"retry")==0 || strcmp(choice,"'retry'")==0)
            {
                searchPage();
            }
            else if(strcmp(choice,"back")==0 || strcmp(choice,"'back'")==0)
            {
                manage(1);
            }
            else
            {
                printf("\n            \t|\t  invalid input, try again: ");
                goto g1;
            }

        }
        
}

void requestsPage()
{
    system("cls");
	printf(" Manage        x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("<-  ->    | http://elpmis.com/%s/manage/requests \n",global);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n   ELPMIS +\t|\t\t\t\t\t\t\t\t\t\t\t\t  | | |");
	printf("\n            \t|\t");
    // print all friendi 1 from requests_db\\global.txt
    char dir[50]="";
    strcat(dir,REQ);
    strcat(dir,global);
    strcat(dir,".txt");
    if(access(dir,0))
    {
        printf("\n            \t|\t\t NO SENT REQUESTS CURRENTLY\n\n");
        printf("\n            \t|\t\t NO RECIEVED REQUESTS CURRENTLY\n\n");
        printf("\n            \t|\t  press any key to redirect back");
        getch();
        manage(1);
        
    }
    FILE* f = fopen(dir,"r");
    fgetc(f);// \n 
    int c1 = 0 ;
    printf("\n            \t|\t\t SENT REQUESTS\n\n");
    while(!feof(f))
    {
        char tmp[30]="";
        char x; int i = 0 ; 
        x = fgetc(f);
        while(x != ' ' && x!='\n' && !feof(f))
        {
            tmp[i++]= x ; 
            x = fgetc(f); ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }   tmp[i] = '\0';
        
        if(!checkRSB(tmp,1,BLOCK) && !checkRSB(tmp,0,BLOCK) && !isDeactivated(tmp))
        if(!feof(f) && fgetc(f)=='1')
        {
            printf("\n            \t|\t %s",tmp);
            c1 ++ ;
        }
    }
    if(c1 == 0 )
    printf("\n            \t|\t\t NO SENT REQUESTS CURRENTLY\n\n");
    fseek(f,0,SEEK_SET);
    fgetc(f);// \n
    int c2= 0 ; 
    printf("\n\n            \t|\t\t RECIEVED REQUESTS\n\n");
    while(!feof(f))
    {
        char tmp[30]="";
        char x; int i = 0 ; 
        x = fgetc(f);
        while(x != ' ' && x!='\n' && !feof(f))
        {
            tmp[i++]= x ; 
            x = fgetc(f);
        }   tmp[i] = '\0';

        if(!checkRSB(tmp,1,BLOCK) && !checkRSB(tmp,0,BLOCK) && !isDeactivated(tmp))
        {
        if(!feof(f) && fgetc(f)=='0')
        {
            printf("\n            \t|\t %s",tmp);
            c2 ++ ;
        }
        }
        else if(strlen(tmp)!=0){fgetc(f);fgetc(f);}//number and \n
    }
    fclose(f);
    if(c2 == 0 )
    printf("\n            \t|\t\t NO RECIEVED REQUESTS CURRENTLY\n\n");
    z:;
    if(c1 ==0 && c2 ==0 )
    {
        printf("\n            \t|\t  press any key to redirect back");
        getch();
        manage(1);
    }
    printf("\n\n            \t|\t\t enter username to accept or unsend request or enter 'back'\n            \t|\t\t ");
    fflush(stdin);
    char ch[30] ="";
    scanf("%[^\n]s",ch);
    if(strcmp(ch,"back")==0 || strcmp(ch,"Back")==0 || strcmp(ch,"BACK")==0 ||strcmp(ch,"'back'")==0 )
        {
            printf("\n            \t|\t  redirecting back.... \n");
            delay(1500);
            manage(1);
        }else
    if( (strcmp(ch,global)!= 0) && (username_checker(ch) )&& (isUsername(ch)))
    {
        if(checkRSB(ch,0,REQ))
        {
            acceptRequest(ch);
            printf("\n            \t|\t  %s is now your friend. Press any key to continue",ch);
        }
        
        else if(checkRSB(ch,1,REQ))
        {
            deletionUtility(global,ch,REQ,0);
            deletionUtility(ch,global,REQ,0);
            printf("\n            \t|\t  %s request undone. press any key to continue",ch);
        }
        
                    getch();
                    requestsPage();

    }
    else
    {
        printf("\n            \t|\t  invalid username, try again\n");
        goto z;
    }
}

int numFriends(char* ok, int j) //includes deactivated, blocked accounts.
{
    int k = 0 ; 
    char dir[30]="";
    strcat(dir,USERDB);
    strcat(dir,ok);
    strcat(dir,".txt");
    FILE* f = fopen(dir,"r");

    int n = 0 ; 
    for(int i = 0 ; i < 5; i++)
    while(fgetc(f)!='\n');
    while(fgetc(f)!='\n')
    {
        if(feof(f))
        {
            fclose(f);
            return 0;
        }
    }
    
    while(1)
    {
        n++;
        char tmp[30];
        char x = fgetc(f);
        int i = 0 ;
        while(x!='\n' && !feof(f))
        {
            tmp[i++]= x ; 
            x= fgetc(f);
            if(feof(f))
            {
                break;
            }
            
        }
        tmp[i]='\0';
        char* tempp ;
        tempp = global ;
        global = ok ;
        if(isDeactivated(tmp) || checkRSB(tmp,0,BLOCK))n--;
        else if(j==1)
        {
            if(k%2==0)
            printf("\n\t %s\t|",tmp);
            else
            printf("\t  %s \n",tmp);
            k++;
        }
        else;
        global = tempp;
        if(feof(f))
            {
                fclose(f);
                return n ; 
            }
        
    }
    
}

void deactivate()
{
    FILE* f = fopen("deactivated_db.txt","a");
    fprintf(f,"\n%s",global);
    fclose(f);
    // mention that logging in again will re-activate automatically
}

int isDeactivated(char* ok)
{
    FILE* f = fopen("deactivated_db.txt","r");
    while(!feof(f))
    {
        char tmp[30];
        int i = 0 ;
        while(1)
        {
            char c = fgetc(f) ;

            if(c == '\n' || feof(f))break;
            tmp[i++]=c;

        }tmp[i]='\0';
        if(strcmp(tmp,ok)==0)
        return 1;
       
       
    }
    return 0 ;
    fclose(f);
}

void unSend(char* ok)
{
    // delete ok 1 from global.txt
    // delete global 0 from ok.txt
    deletionUtility(global,ok,REQ,0);
    deletionUtility(ok,global,REQ,0);
}

void profile(char* choice, int a)
{                  
    displayProfile(choice);
    //fine

                if(a==1)
                {
                    printf("\n            \t|\t  Enter 'view' to display your friends");
                    printf("\n            \t|\t  Enter 'back' to go back or enter 'other' to view other account options: \n            \t|\t  ");
                }
                else
                {
                    printf("\n            \t|\t  Enter 'unfriend' to remove %s from your friends' list ",choice);
                    printf("\n            \t|\t  Enter 'block' to block %s or Enter 'back' to go back: \n            \t|\t  ",choice);
                }
                f5:;
                fflush(stdin);
                char ch[30] ;
                scanf("%[^\n]s",ch); 
                for(int i = 0 ; i < strlen(ch); i++)
                ch[i]= tolower(ch[i]);

                if((strcmp(ch,"view")==0 || strcmp(ch,"'view'")==0) && a==1 )
                {
                    if(numFriends(choice,1)==0)
                    printf("\n            \t|\t  No friends to display, press any key to redirect back");
                    else
                    printf("\n            \t|\t  press any key to redirect back");
                    getch();
                    profile(global,1);

                }
                else if((strcmp(ch,"back")==0 || strcmp(ch,"'back'")==0) )
                {
                    manage(1);
                }
                else if((strcmp(ch,"other")==0 || strcmp(ch,"'other'")==0) && a==1 )
                {
                    system("cls");
                    printf(" search       x\\ +\t\t\t\t\t\t\t\t\t\t\t\t   | X\n");
	                printf("----------------------------------------------------------------------------------------------------------------------\n");
	                printf("<-  ->    | http://elpmis.com/%s/search/profile/other \n",global);
	                printf("----------------------------------------------------------------------------------------------------------------------\n");
	                printf("\n   ELPMIS  +\t|\t\t\t\t\t\t\t\t\t\t\t\t  | | |\n");
                    printf("\n            \t|\t  Enter 'deactivate' to deactivate your account, enter 'change' to change password");
                    printf("\n            \t|\t  Enter 'delete' to delete your elpmis account or enter 'back' to go back \n            \t|\t  ");
                    f6:;
                    fflush(stdin);
                    
                    char ci[30] ;
                    scanf("%[^\n]s",ci); 
                    for(int i = 0 ; i < strlen(ci); i++)ci[i]= tolower(ci[i]);
                    if( (strcmp(ci,"change")==0 || strcmp(ci,"'change'")==0) && a==1)
                    {
                        changeCred();
                        printf("\n            \t|\t  Done! Press any key to continue");
                        getch();
                        profile(choice,a);

                    }
                    else if( (strcmp(ci,"deactivate")==0 || strcmp(ci,"'deactivate'")==0) && a==1)
                    {
                        printf("\n            \t|\t  when you login to your elpmis account, yoour account is reactivated back automatically");
                        printf("\n            \t|\t  while this period, nobody can message you, however existing chat is preserved and visible");
                        printf("\n            \t|\t  your leaderboard position of any game, wont change. you are not visible in users database");
                        printf("\n            \t|\t  enter 'confirm' to continue or press 'back' to redirect back");
                        fflush(stdin);
                        char chh[30] ;
                        scanf("%[^\n]s",chh); 
                        for(int i = 0 ; i < strlen(chh); i++)chh[i]= tolower(chh[i]);
                        if(strcmp(chh,"confirm")==0 || strcmp(chh,"'confirm'")==0)
                        {
                            deactivate();
                            elpmis_home(1);
                        }
                        else if(strcmp(chh,"back")==0 || strcmp(chh,"'back'")==0)
                        {
                            searchPage();
                        }
                        else
                        {
                            printf("\n            \t|\t  invalid input, try again: ");
                            goto f6;
                        }

                    }
                    else if(strcmp(ci,"delete")==0 || strcmp(ci,"'delete'")==0)
                    {
                        
                        printf("\n            \t|\t  all your chats, game scores and posts will be deleted permanantly");
                        printf("\n            \t|\t  enter 'confirm' to continue or press 'back' to redirect back");
                        fflush(stdin);
                        char chh[30] ;
                        scanf("%[^\n]s",chh); 
                        for(int i = 0 ; i < strlen(chh); i++)chh[i]= tolower(chh[i]);
                        if(strcmp(chh,"confirm")==0 || strcmp(chh,"'confirm'")==0)
                        {
                            delay(1000);
                           printf("\n            \t|\t  unable to complete the action, please try again later");/**********temporary message************/
                           printf("\n            \t|\t  Redirecting you back...");
                            //deleteUser();
                            
                              // char del[40]="user_db\\"; strcat(del,global);strcat(del,".txt");
                               global= "";
                              //  printf("%s -> %d",del,unlink(del));
                            delay(3000);
                            elpmis_home(1);
                        }
                        else if(strcmp(chh,"back")==0 || strcmp(chh,"'back'")==0)
                        {
                            searchPage();
                        }
                        else
                        {
                            printf("\n            \t|\t  invalid input, try again: ");
                            goto f6;
                        }
                    }
                    else if(strcmp(ci,"back")==0 || strcmp(ci,"'back'")==0)
                    {
                        searchPage();
                    }
                    else
                    {
                        printf("\n            \t|\t  invalid input, try again: ");
                        goto f6;
                    }
                }
                else if((strcmp(ch,"unfriend")==0 || strcmp(ch,"'unfriend'")==0) && a==2 )
                {
                    //delete each other in block 
                    //delete chat 
                    // delete each other in friends
                    deletionUtility(global,ch,USERDB,3);
                    deletionUtility(ch,global,USERDB,3);
                    char fil[50] = "" ;
                    strcat(fil,CHAT);
                    if(strP(global,choice))
                    {
                    strcat(fil,global);
                    strcat(fil," ");
                    strcat(fil,choice);
                    strcat(fil,".txt");
                    }   
                    else 
                    {
                    strcat(fil,choice);
                    strcat(fil," ");
                    strcat(fil,global);
                    strcat(fil,".txt");
                    }
                    remove(fil);
                    printf("\n            \t|\t Successfully removed %s from friends list. press any key to redirect back",choice);
                    getch();
                    searchPage();
            

                }
                else if((strcmp(ch,"block")==0 || strcmp(ch,"'block'")==0) && a==2)
                {
                    printf("\n            \t|\t  untill you unblock %s, %s cannot acess your profile, chats or game scores",choice,choice);
                    block(choice);
                    printf("\n            \t|\t  %s is blocked. press any key to continue",choice);
                    getch();
                    searchPage();
                }
                else
                {
                    printf("\n            \t|\t  invalid input, try again: ");
                    goto f5;
                }
                
}

void changeCred()
{
    printf("\n            \t|\t  You must answer the security question you selected inorder to change password. Press any key to display the question");
    getch();

    char dir[50] = "" ;
    strcat(dir, USERDB);
    strcat(dir,global);
    strcat(dir,".txt");

    FILE* f = fopen(dir,"r");
    while(fgetc(f)!='\n');
    while(fgetc(f)!='\n');
    while(fgetc(f)!='\n');
    while(fgetc(f)!='\n');
    char x = fgetc(f) ; 
    char question[50] ; 
    int i = 0 ; 
    while(x!='?')
    {
        question[i++] = x ; 
        x = fgetc(f);
    }
    question[i] ='\0';

    // now f points to the answer 

    char ans[21] ; i =0 ;
    x= fgetc(f) ; 
    while(x!='\n')
    {
        ans[i++]=x;
        x= fgetc(f);
    }
    ans[i] = '\0';
    fclose(f);
    printf("\n            \t|\t  %s :",question);
    char tmp[25] = ""; 
    ent:;
    fflush(stdin);
    scanf("%[^\n]s",tmp);
    for(int i = 0 ;i < strlen(tmp); i++)
    tmp[i]= tolower(tmp[i]);
    if(!strcmp(tmp,"\n"))
    {
        printf("\n            \t|\t  Enter something! ");
        goto ent; 
    }
    if(!strcmp(tmp,ans))
    {
        char pass[50], passs[50] ; 
        char  c ;
        int index ;  

        ret:;
        index = 0;  

        printf("\n            \t|\t  Enter new password: ");
        fflush(stdin);
	     
        while((c = getch()) != 13)
        {
        
            if(index < 0)
            index = 0;
      
            if(c == 3)
            {
                exit(1);
            }
            else if(c==8 && index==0)continue ;
            else if(c == 8 )
            {
                putch('\b');
                putch(' ');
                putch('\b');
                index--;
                continue;
            }
            pass[index++] = c;
            putch('*');
        }

        pass[index] = '\0';
        //printf("*%s*",pass);
        
        if( password_checker(pass) == -8)
        {
            printf("\n\t\t\t\t    password should be atleast 8 characters long\n");
            goto ret;
        }
        else if( password_checker(pass) == -16 )
        {
            printf("\n\t\t\t\t    password should be at max 16 characters long\n");
            goto ret;
        }
        else if( password_checker(pass) == 0 )
        {
            printf("\n\t\t\t\t    password should contain atleast one of each:\n\t\t\t\t    lowercase, uppercase, numeric and special characters\n");
            goto ret;
        }


        printf("\n            \t|\t  Confirm password again: ");
        
        fflush(stdin);
        index = 0;   
   
        while((c = getch()) != 13)
        {
        
            if(index < 0)
            index = 0;
      
            if(c == 3)
            {
                exit(1);
            }
            else if(c==8 && index==0)continue ;
            else if(c == 8 )
            {
                putch('\b');
                putch(' ');
                putch('\b');
                index--;
                continue;
            }
            passs[index++] = c;
            putch('*');
        }

        passs[index] = '\0';

        if(strcmp(pass,passs)==0)
        {
            FILE* w = fopen("tmp.txt","w");
            char di[50] ="" ;
            strcat(di,USERDB);
            strcat(di,global);
            strcat(di,".txt");
            FILE* f = fopen(di, "r");

            char x = fgetc(f);
            while(x != '\n')
            {
                fputc(x,w);
                x= fgetc(f);
            }
            fputc('\n',w);
            fprintf(w,"%s\n",pass);
            while(fgetc(f)!='\n');
            
            x = fgetc(f);
            while(x != EOF)
            {
                fputc(x,w);
                x = fgetc(f);
            }

            fclose(f);
            fclose(w);

            w = fopen(di,"w");
            f= fopen("tmp.txt","r");

            x = fgetc(f);
            while(x!=EOF)
            {
                fputc(x,w);
                x=fgetc(f);
            }

            fclose(f);
            fclose(w);
            remove("tmp.txt");

        }
        else 
        {
            printf("\n            \t|\t  Password mismatch, enter 'retry' to try again or 'back' to go back");
            char er[15]="\n";
            qaz:;
            fflush(stdin);
            scanf("%[^\n]s",er);
            for(int i = 0 ; i < strlen(er); i++)
            er[i]= tolower(er[i]);

            if(strcmp(er,"retry")==0)
            {
                goto ret ;
            }
            else if(strcmp(er,"back")==0)
            {
                profile(global,1);
            }
            else
            {
                printf("\n            \t|\t  invalid input, try again ");
                goto qaz; 
            }
        }
    
    }
    else 
    {
        printf("\n            \t|\t  wrong answer, enter 'retry' to try again or enter 'back' to go back ");
        tg:;
        fflush(stdin);
        scanf("%[^\n]s",tmp);
        for(int i = 0 ;i < strlen(tmp); i++)
        tmp[i]= tolower(tmp[i]);
        if(strcmp(tmp,"back")==0)
        {
            profile(global,1);
        }
        else if(strcmp(tmp,"retry")==0)
        {
            changeCred();
        }
        else
        {
            printf("\n            \t|\t  invalid input, try again ");
            goto tg; 
        }
    }

}


/****************************************************************************games-functions*******************************************************************************************************/


// a matrix which holds the values in the grid
int* *mat_2048;

// the score counter
int score_2048 = 0 ;


// whenever this function is called, the grid will be displayed on terminal
void display_matrix_2048()
{
    // each value of matrix is independantly mentioned rather than loop
    printf(" ___________________________\n");
    printf("|      |      |      |      |\n");
    printf("| %4d | %4d | %4d | %4d |\n",mat_2048[0][0],mat_2048[0][1],mat_2048[0][2],mat_2048[0][3]);
    printf("|______|______|______|______|\n");
    printf("|      |      |      |      |\n");
    printf("| %4d | %4d | %4d | %4d |\n",mat_2048[1][0],mat_2048[1][1],mat_2048[1][2],mat_2048[1][3]);
    printf("|______|______|______|______|\n");
    printf("|      |      |      |      |\n");
    printf("| %4d | %4d | %4d | %4d |\n",mat_2048[2][0],mat_2048[2][1],mat_2048[2][2],mat_2048[2][3]);
    printf("|______|______|______|______|\n");
    printf("|      |      |      |      |\n");
    printf("| %4d | %4d | %4d | %4d |\n",mat_2048[3][0],mat_2048[3][1],mat_2048[3][2],mat_2048[3][3]);
    printf("|______|______|______|______|\n");
    printf("current score_2048 : %d \n",score_2048);
}

// this function will make the addition changes according to the direction specified in the parameter
void sum_2048(int* *mat_2048,char* dir )
{

    // d means right , so from right to left, all equal boxes will be added and stored in the right-adjacent block
    if(strcmp(dir,"d")==0)
    {
    for(int i = 0 ; i < 4 ; i ++)
    for(int j = 3 ; j > 0 ; j --)
    {
        // if equal blocks, then sum and store in right-adjacent block
        if(mat_2048[i][j] == mat_2048[i][j-1])
        {
            mat_2048[i][j]+=mat_2048[i][j-1]; // could just have multiplied by 2 but okay
            score_2048+=mat_2048[i][j]; // score gets incremented 
            mat_2048[i][j-1]= 0; // the u block will be zero once merged 
        }
    }
    }
    // similar logic works for all directions 
    else if(strcmp(dir,"a")==0)
    {
    for(int i = 0 ; i < 4 ; i ++)
    for(int j = 0 ; j <= 2 ; j ++)
    {
        if(mat_2048[i][j] == mat_2048[i][j+1])
        {
            mat_2048[i][j]+=mat_2048[i][j+1];
            score_2048+=mat_2048[i][j] ;
            mat_2048[i][j+1]= 0;
        }
    }
    }
    else if(strcmp(dir,"w")==0)
    {
    for(int i = 0 ; i < 4 ; i ++)
    for(int j = 0 ; j <= 2 ; j ++)
    {
        if(mat_2048[j][i] == mat_2048[j+1][i])
        {
            mat_2048[j][i]+=mat_2048[j+1][i];
            score_2048+=mat_2048[j][i] ;
            mat_2048[j+1][i]= 0;
        }
    }
    }
    else if(strcmp(dir,"s")==0)
    {
    for(int i = 0 ; i < 4 ; i ++)
    for(int j = 3 ; j > 0 ; j --)
    {
        if(mat_2048[j][i] == mat_2048[j-1][i])
        {
            mat_2048[j][i]+=mat_2048[j-1][i];
            score_2048+= mat_2048[j][i] ; 
            mat_2048[j-1][i]= 0;
        }
    }
    }
}

// the sliding function for the board, works depending on parameter - direction, just like the sum_2048()
void slide_2048(int* *mat_2048 ,char* dir )
{
    // the arr[4] will take the non ero values in chronological order in one iteration
    // then again from the stored values, during 2nd iteration, will put all the non zero values adjacent to each other
    // hence sliding is working like this way. but after sliding addition is possible, so thats why slide is called before and after the sum function because after sum, sliding can occur
    int arr[4] ;int k=0; // the k is used to iterate through matrix for the array

    // case 'd' which means right as per wasd convention
    if(strcmp(dir,"d")==0)
    {printf("pressed d\n");
        for(int i = 0 ; i < 4 ; i ++)
        {k=0;
        for(int j = 3 ; j >= 0 ; j --)
        {
            // ignores the zero values coz it takes the non zero values chronologically
            if(mat_2048[i][j] == 0)continue;
            else
            // when non zero, storing in array
            arr[k++] = mat_2048[i][j];
        }
        // the 2nd iteration, to assign the values stored all adjacent to each other from the direction specified
        int tmp = 0 ;// used to iterate for assigning
        for(int j = 3 ; j >=0  ; j --)
        {
            // its non zeroes while until reached k , which was the no.of non zeroe values in above case
            if(tmp<k)
            mat_2048[i][j] = arr[tmp++];
            else
            mat_2048[i][j]=0;
        }
        }
    }

    // the same logic applies for all other directions
    else if(strcmp(dir,"a")==0)
    {
        printf("pressed a\n");
            for(int i = 0 ; i < 4 ; i ++)
    {k=0;
        for(int j = 0 ; j <=3  ; j ++)
        {
            if(mat_2048[i][j] == 0)continue; //.
            else
            arr[k++] = mat_2048[i][j];
        }
        int tmp = 0 ;
        for(int j = 0 ; j <=3  ; j ++)
        {
            if(tmp<k)
            mat_2048[i][j] = arr[tmp++];
            else
            mat_2048[i][j]=0;
        }
    }
    }
    else if(strcmp(dir,"w")==0)
    {printf("pressed w\n");
            for(int i = 0 ; i < 4 ; i ++)
    {
        k=0;
        for(int j = 0 ; j <=3 ; j ++)
        {
            if(mat_2048[j][i] == 0)continue; ////
            else
            arr[k++] = mat_2048[j][i];
        }
        int tmp = 0 ;
        for(int j = 0; j <=3  ; j ++)
        {
            if(tmp<k)
            mat_2048[j][i] = arr[tmp++];
            else
            mat_2048[j][i]=0;
        }
    }
    }
    else if(strcmp(dir,"s")==0)
    {printf("pressed s\n");
            for(int i = 0 ; i < 4 ; i ++)
    {
        k=0;
        for(int j = 3 ; j >= 0 ; j --)
        {
            if(mat_2048[j][i] == 0)continue;
            else
            arr[k++] = mat_2048[j][i];
        }
        int tmp = 0 ;
        for(int j = 3 ; j >=0  ; j --)
        {
            if(tmp<k)
            mat_2048[j][i] = arr[tmp++];
            else
            mat_2048[j][i]=0;

        }
    }
    }

}

// this function returns 1 if the board changed its state when performed slide and sum and slide cycle using a clone of the 
// the current board. this is crucial to check wethear the user's move is a valid one
// if it returs 0, the user has to move other direction.
int isSlide_2048( char* dir ) //returns if changed or not
{
    // the clone generation
    int* *temp;
    temp =(int**) malloc(sizeof(int)*16);
    for(int i = 0 ; i < 4; i++)
    temp[i]=(int*) malloc(sizeof(int)*4);
    
    for(int i = 0 ;  i < 4 ;i++)
    for(int j = 0 ; j < 4 ; j++)
    temp[i][j] = mat_2048[i][j] ;

    // the slide functionality
    // cannot explicity call the slide function itself because the orginal slide uses the global vairable
    slide_2048(temp,dir);
    sum_2048(temp,dir);
    slide_2048(temp,dir);

    for(int i = 0 ;  i < 4 ;i++)
    for(int j = 0 ; j < 4 ; j++)
    {
        if(temp[i][j] != mat_2048[i][j] )return 1;
    }

    free(temp);
    return 0 ;
}

// to check if game can still be played by any move. 
int isFull_2048()
{
    for(int i = 0 ; i < 4 ; i ++)
    for(int j = 3 ; j > 0 ; j --)
    {
        if(mat_2048[i][j]==0)return 0;
    }
    if(isSlide_2048("w") || isSlide_2048("d") || isSlide_2048("a") || isSlide_2048("s") )
    return 0;
    return 1; 
}

void randomPlace_2048()
{
    srand(time(NULL));
    int r1,r2,r3 ;
    do
    {
        r1 = rand() % 4 ;
        r2 = rand() % 4 ;
        //printf("got mat_2048[%d][%d] = %d \n",r1,r2,mat_2048[r1][r2]);
    }while(mat_2048[r1][r2]!= 0);

    r3 = rand() % 2 ;
    if(r3==0) r3 = 2;
    else r3 = 4 ;
    mat_2048[r1][r2]=r3;   
}

int game_2048()
{
    //int* *mat_2048 ; 
    mat_2048= (int**)malloc(sizeof(int)*16);
    for(int i = 0 ; i < 4; i++)
    mat_2048[i] = (int*)malloc(sizeof(int)*4);
    for(int i = 0 ;  i < 4 ;i++)
    for(int j = 0 ; j < 4 ; j++)
    mat_2048[i][j] = 0 ;

    score_2048 = 0;
   
   char x[50] ;
   printf("welcome to 2048 ! enter 'W' 'A' 'S' 'D' keys for up left down right keys respectively and\n");
   printf("enter 'exit' to stop the game while in between\nenter 'highscore' to view leaderboard\nenter 'back' to go back now or enter 'start' to play the game\n");
   goto1:;
   fflush(stdin);
   scanf("%[^\n]s",x);
   for(int i = 0 ; i < strlen(x); i++)x[i]= tolower(x[i]);
    if(strcmp(x,"start")==0);
    else if(strcmp(x,"back")==0);
    else
    {
        printf("invalid input, try again\n");
        goto goto1;
    }

    int flag =1 ; // valid move flag
   while(!isFull_2048())
   {
     randomPlace_2048();
     if(isFull_2048())break;
     display_matrix_2048();
     goto2:;
     fflush(stdin);
     scanf("%[^\n]s",x);
     for(int i = 0 ; i < strlen(x); i++)x[i]= tolower(x[i]);
     if(strcmp(x,"exit")==0)
     {
        break;
     }
     if(isSlide_2048(x)==0)
     {
        system("cls");
        display_matrix_2048();
        goto goto2;
     }
     system("cls");
     
     if(strcmp(x,"w")==0 || strcmp(x,"a")==0  || strcmp(x,"s")==0  ||strcmp(x,"d")==0 )
     {
        slide_2048(mat_2048,x);
        sum_2048(mat_2048,x);
        slide_2048(mat_2048,x);
     }
     
     else
     {
        printf("invalid input, try again \n");
        goto goto2;
     }        
   }
   printf("Game over! your score_2048 is %d ",score_2048);
   getch();
   display_matrix_2048();
    free(mat_2048);
    return score_2048 ;
}

/* ******SOS********************************************************************************* */

void board_sos( char str[] )
{

system("cls");
printf("\n            \t|\t   ____ ____ ____ ____ ____           ");
printf(" ____ ____ ____ ____ ____ \n");
printf("            \t|\t  |    |    |    |    |    |          ");
printf("|    |    |    |    |    | \n");
printf("            \t|\t  | %c  | %c  | %c  | %c  | %c  |          ",str[0],str[1],str[2],str[3],str[4]);
printf("| 1  | 2  | 3  | 4  | 5  | \n");
printf("            \t|\t  |____|____|____|____|____|          ");
printf("|____|____|____|____|____| \n");
printf("            \t|\t  |    |    |    |    |    |          ");
printf("|    |    |    |    |    | \n");
printf("            \t|\t  | %c  | %c  | %c  | %c  | %c  |          ",str[5],str[6],str[7],str[8],str[9]);
printf("| 6  | 7  | 8  | 9  | 10 | \n");
printf("            \t|\t  |____|____|____|____|____|          ");
printf("|____|____|____|____|____| \n");
printf("            \t|\t  |    |    |    |    |    |          ");
printf("|    |    |    |    |    | \n");
printf("            \t|\t  | %c  | %c  | %c  | %c  | %c  |          ",str[10],str[11],str[12],str[13],str[14]);
printf("| 11 | 12 | 13 | 14 | 15 | \n");
printf("            \t|\t  |____|____|____|____|____|          ");
printf("|____|____|____|____|____| \n");
printf("            \t|\t  |    |    |    |    |    |          ");
printf("|    |    |    |    |    | \n");
printf("            \t|\t  | %c  | %c  | %c  | %c  | %c  |          ",str[15],str[16],str[17],str[18],str[19]);
printf("| 16 | 17 | 18 | 19 | 20 | \n");
printf("            \t|\t  |____|____|____|____|____|          ");
printf("|____|____|____|____|____| \n");
printf("            \t|\t  |    |    |    |    |    |          ");
printf("|    |    |    |    |    | \n");
printf("            \t|\t  | %c  | %c  | %c  | %c  | %c  |          ",str[20],str[21],str[22],str[23],str[24]);
printf("| 21 | 22 | 23 | 24 | 25 | \n");
printf("            \t|\t  |____|____|____|____|____|          ");
printf("|____|____|____|____|____| \n");

return ;

}

int game_sos(char str[])
{
    for(int i=0 ; i<= 24 ; i++)
    {
        if(str[i] == ' ')
        return 1;
        else
        continue ;
    }
    

    return 0 ;
}


int game_sosUtility(char* pl1, char* pl2, int* arr)
{
    int tpp[3] = {0,0,0} ;
    char f[49] ; 
    for(int i = 1; i<= 48; i++)f[i] ='0' ;
    
    char str[25] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '} ;
    
    char bbox[10];
    char bbos[10];
    printf("\n          \t|\t  WELCOME TO SOS MULTIPLAYER ");
    printf("\n          \t|\t  When it is a player's turn, refering to the labelled board, enter the box number to select that box ");
    printf("\n          \t|\t  then enter S or O as per your choice. Both players shall do the same, the points will be updated each turn.");
    printf("\n          \t|\t  enter 'exit' anytime to stop. Press any key to continue");
    getch();

    for(int i=1; game_sos(str) == 1 ; i++)
    { k:

        
            if(i%2==1)
            tpp[0] = 1; 
            else
            tpp[0] = 0; 
            
            if(game_sos(str)==0)
            break;
            
            printf("\n          \t|\t  %s, enter box number from guide which is unfilled\n          \t|\t  ",pl1);
            board_sos(str);
            printf("\n\n          \t|\t  ");
            fflush(stdin);
            scanf("%[^\n]s",bbox);
            if(strcmp(bbox,"exit")==0)
            {
                printf("\n          \t|\t  are you sure? enter 'yes' to quit now, or enter 'no' to continue playing          \t|\t  ");
                char cx[30];
                aqs:;
                fflush(stdin);
                scanf("%[^\n]s",cx);
                if(strcmp(cx,"yes")==0)
                return -1 ; 
                else if(strcmp(cx,"no")==0);
                else 
                {
                    printf("\n          \t|\t  invalid input, enter 'yes' to quit now, or enter 'no' to continue playing          \t|\t  ");
                    goto aqs;
                }

            }
            int box = atoi(bbox);
            
            if( (box>=26) || (box<1) || str[box-1]!=' ' )     {
            printf("\n          \t|\t  Invalid input, try again, ");
            
            goto k ;                }
            l:
            
            printf("\n          \t|\t  enter S or enter O \n          \t|\t  ");
            fflush(stdin);
            scanf("%[^\n]s",bbos);
            for(int i = 0 ; i < strlen(bbos); i++)bbos[i]=tolower(bbos[i]);
            
            if( strcmp(bbos,"s")!=0 && strcmp(bbos,"o")!=0)   {
            printf("\n          \t|\t  only S or O applicable, try agian, ");
            goto l ;                }
            
            if(!strcmp(bbos,"s"))                  
            str[box-1] = 'S' ;    
            else if(!strcmp(bbos,"o"))
            str[box-1] = 'O' ;
            
            int ok;
            if(i%2==1)
            ok = tpp[1];
            else
            ok = tpp[2];

            
            mark_sos( str, f , tpp );
            

            if((tpp[0]==1 && ok != tpp[1]) || (tpp[0]==0 && ok!=tpp[2])) {
            printf("\n          \t|\t  extra chance for match, ");
            printf("\n          \t|\t  the present scores are, PLAYER 1 --> %d    PLAYER 2 --> %d ",tpp[1],tpp[2]);
            goto k ;    }
            printf("\n          \t|\t  the present scores are, PLAYER 1 --> %d    PLAYER 2 --> %d ",tpp[1],tpp[2]);
        
    }
    board_sos(str);
    printf("\n          \t|\t  the final scores are \nPLAYER 1 --> %d      PLAYER 2 --> %d ",tpp[1],tpp[2]);
    if(tpp[1]>tpp[2])
    printf("\n          \t|\t  %s WINS ",pl1);
    else if(tpp[2]>tpp[1])
    printf("\n          \t|\t  %s WINS ",pl2);
    else
    printf("\n          \t|\t  DRAW game ");
    
    
    arr[0] = tpp[1];
    arr[1] = tpp[2] ; 
    return 1;
    
}

void mark_sos(char* str, char* f , int*tpp )
{
    if( (str[0] == 'S')  && (str[6] == 'O')  && (str[12] == 'S') )    if(f[1]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[1 ]= '1';       }    else;
    if( (str[5] == 'S')  && (str[11] == 'O') && (str[17] == 'S') )    if(f[2]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[2 ]= '1';       }    else;
    if( (str[10] == 'S') && (str[16] == 'O') && (str[22] == 'S') )    if(f[3]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[3 ]= '1';       }    else;
    if( (str[1] == 'S')  && (str[7] == 'O')  && (str[13] == 'S') )    if(f[4]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[4 ]= '1';       }    else;
    if( (str[6] == 'S')  && (str[12] == 'O') && (str[18] == 'S') )    if(f[5]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[5 ]= '1';       }    else;
    if( (str[11] == 'S') && (str[17] == 'O') && (str[23] == 'S') )    if(f[6]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[6 ]= '1';       }    else;
    if( (str[2] == 'S')  && (str[8] == 'O')  && (str[14] == 'S') )    if(f[7]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[7 ]= '1';       }    else;
    if( (str[7] == 'S')  && (str[13] == 'O') && (str[19] == 'S') )    if(f[8]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[8 ]= '1';       }    else;
    if( (str[12] == 'S') && (str[18] == 'O') && (str[24] == 'S') )    if(f[9]== '0') {     if(tpp[0])tpp[1]++;else tpp[2]++;    f[9 ]= '1';       }    else;
    if( (str[2] == 'S')  && (str[6] == 'O')  && (str[10] == 'S') )    if(f[10]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[10 ]= '1';       }    else;
    if( (str[7] == 'S')  && (str[11] == 'O') && (str[15] == 'S') )    if(f[11]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[11 ]= '1';       }    else;
    if( (str[12] == 'S') && (str[16] == 'O') && (str[20] == 'S') )    if(f[12]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[12 ]= '1';       }    else;
    if( (str[3] == 'S')  && (str[7] == 'O')  && (str[11] == 'S') )    if(f[13]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[13 ]= '1';       }    else;
    if( (str[8] == 'S')  && (str[12] == 'O') && (str[16] == 'S') )    if(f[14]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[14 ]= '1';       }    else;
    if( (str[13] == 'S') && (str[17] == 'O') && (str[21] == 'S') )    if(f[15]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[15 ]= '1';       }    else;
    if( (str[4] == 'S')  && (str[8] == 'O')  && (str[12] == 'S') )    if(f[16]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[16 ]= '1';       }    else;
    if( (str[9] == 'S')  && (str[13] == 'O') && (str[17] == 'S') )    if(f[17]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[17 ]= '1';       }    else;
    if( (str[14] == 'S') && (str[18] == 'O') && (str[22] == 'S') )    if(f[18]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[18 ]= '1';       }    else;
    if( (str[0] == 'S')  && (str[5] == 'O')  && (str[10] == 'S') )    if(f[19]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[19 ]= '1';       }    else;
    if( (str[5] == 'S')  && (str[10] == 'O') && (str[15] == 'S') )    if(f[20]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[20 ]= '1';       }    else;
    if( (str[10] == 'S') && (str[15] == 'O') && (str[20] == 'S') )    if(f[21]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[21 ]= '1';       }    else;
    if( (str[1] == 'S')  && (str[6] == 'O')  && (str[11] == 'S') )    if(f[22]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[22 ]= '1';       }    else;
    if( (str[6] == 'S')  && (str[11] == 'O') && (str[16] == 'S') )    if(f[23]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[23 ]= '1';       }    else;
    if( (str[11] == 'S') && (str[16] == 'O') && (str[21] == 'S') )    if(f[24]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[24 ]= '1';       }    else;
    if( (str[2] == 'S')  && (str[7] == 'O')  && (str[12] == 'S') )    if(f[25]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[25 ]= '1';       }    else;
    if( (str[7] == 'S')  && (str[12] == 'O') && (str[17] == 'S') )    if(f[26]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[26 ]= '1';       }    else;
    if( (str[12] == 'S') && (str[17] == 'O') && (str[22] == 'S') )    if(f[27]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[27 ]= '1';       }    else;
    if( (str[3] == 'S')  && (str[8] == 'O')  && (str[13] == 'S') )    if(f[28]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[28 ]= '1';       }    else;
    if( (str[8] == 'S')  && (str[13] == 'O') && (str[18] == 'S') )    if(f[29]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[29 ]= '1';       }    else;
    if( (str[13] == 'S') && (str[18] == 'O') && (str[23] == 'S') )    if(f[30]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[30 ]= '1';       }    else;
    if( (str[4] == 'S')  && (str[9] == 'O')  && (str[14] == 'S') )    if(f[31]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[31 ]= '1';       }    else;
    if( (str[9] == 'S')  && (str[14] == 'O') && (str[19] == 'S') )    if(f[32]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[32 ]= '1';       }    else;
    if( (str[14] == 'S') && (str[19] == 'O') && (str[24] == 'S') )    if(f[33]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[33 ]= '1';       }    else;
    if( (str[0] == 'S')  && (str[1] == 'O')  && (str[2]  == 'S') )    if(f[34]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[34 ]= '1';       }    else;
    if( (str[1] == 'S')  && (str[2] == 'O')  && (str[3]  == 'S') )    if(f[35]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[35 ]= '1';       }    else;
    if( (str[2] == 'S')  && (str[3] == 'O')  && (str[4]  == 'S') )    if(f[36]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[36 ]= '1';       }    else;
    if( (str[5] == 'S')  && (str[6] == 'O')  && (str[7]  == 'S') )    if(f[37]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[37 ]= '1';       }    else;
    if( (str[6] == 'S')  && (str[7] == 'O')  && (str[8]  == 'S') )    if(f[38]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[38 ]= '1';       }    else;
    if( (str[7] == 'S')  && (str[8] == 'O')  && (str[9]  == 'S') )    if(f[39]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[39 ]= '1';       }    else;
    if( (str[10] == 'S') && (str[11] == 'O') && (str[12] == 'S') )    if(f[40]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[40 ]= '1';       }    else;
    if( (str[11] == 'S') && (str[12] == 'O') && (str[13] == 'S') )    if(f[41]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[41 ]= '1';       }    else;
    if( (str[12] == 'S') && (str[13] == 'O') && (str[14] == 'S') )    if(f[42]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[42 ]= '1';       }    else;
    if( (str[15] == 'S') && (str[16] == 'O') && (str[17] == 'S') )    if(f[43]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[43 ]= '1';       }    else;
    if( (str[16] == 'S') && (str[17] == 'O') && (str[18] == 'S') )    if(f[44]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[44 ]= '1';       }    else;
    if( (str[17] == 'S') && (str[18] == 'O') && (str[19] == 'S') )    if(f[45]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[45 ]= '1';       }    else;
    if( (str[20] == 'S') && (str[21] == 'O') && (str[22] == 'S') )    if(f[46]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[46 ]= '1';       }    else;
    if( (str[21] == 'S') && (str[22] == 'O') && (str[23] == 'S') )    if(f[47]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[47 ]= '1';       }    else;
    if( (str[22] == 'S') && (str[23] == 'O') && (str[24] == 'S') )    if(f[48]== '0') {    if(tpp[0])tpp[1]++;else tpp[2]++;   f[48 ]= '1';       }    else;
}

/*****DOT************************************************************************************ */

void board_dot(char* a , char* b, char* c, char* d)
{
    system("cls");
    printf("\n\n\n            \t|\t      1   2   3   4   5 \n\n");
    printf("            \t|\t  1   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \n",d[0],b[0],b[1],b[2],    d[1],b[3],b[4],b[5],    d[2],b[6],b[7],b[8],    d[3],b[9],b[10],b[11],d[4]);
    printf("            \t|\t      %c   %c   %c   %c   %c \n",a[0],a[3],a[6],a[9],a[12] );
    printf("            \t|\t      %c %c %c %c %c %c %c %c %c \n",a[1],c[0],a[4],c[1],a[7],c[2],a[10],c[3],a[13] );
    printf("            \t|\t  2   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \n",a[2],b[12],b[13],b[14],  a[5],b[15],b[16],b[17],   a[8],b[18],b[19],b[20],   a[11],b[21],b[22],b[23],a[14] );
    printf("            \t|\t      %c   %c   %c   %c   %c \n",a[15],a[18],a[21],a[24],a[27] );
    printf("            \t|\t      %c %c %c %c %c %c %c %c %c \n",a[16],c[4],a[19],c[5],a[22],c[6],a[25],c[7],a[28] );
    printf("            \t|\t  3   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \n",a[17],b[24],b[25],b[26],  a[20],b[27],b[28],b[29],   a[23],b[30],b[31],b[32],   a[26],b[33],b[34],b[35],a[29] );
    printf("            \t|\t      %c   %c   %c   %c   %c \n",a[30],a[33],a[36],a[39],a[42] );
    printf("            \t|\t      %c %c %c %c %c %c %c %c %c \n",a[31],c[8],a[34],c[9],a[37],c[10],a[40],c[11],a[43] );
    printf("            \t|\t  4   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \n",a[32],b[36],b[37],b[38],  a[35],b[39],b[40],b[41],   a[38],b[42],b[43],b[44],   a[41],b[45],b[46],b[47],a[44] );
    printf("            \t|\t      %c   %c   %c   %c   %c \n",a[45],a[48],a[51],a[54],a[57] );
    printf("            \t|\t      %c %c %c %c %c %c %c %c %c \n",a[46],c[12],a[49],c[13],a[52],c[14],a[55],c[15],a[58] );
    printf("            \t|\t  5   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \n",a[47],b[48],b[49],b[50],  a[50],b[51],b[52],b[53],   a[53],b[54],b[55],b[56],   a[56],b[57],b[58],b[59],a[59] );
    return ;
}

int mark_dot(int* rc,  char* a, char* b, char * d, char* z, int check)
{
    if( ( rc[0] == 1 && rc[1] == 1 && rc[2] == 1 && rc[3] == 2 ) || ( rc[0] == 1 && rc[1] == 2 && rc[2] == 1 && rc[3] == 1 ) )    { if( z[0]=='0' && check) { z[0]='1' ; return 1 ; }b[0] = b[1] = b[2] = '_' ;        d[0] = d[1] = ' ' ;    }
    if( ( rc[0] == 1 && rc[1] == 2 && rc[2] == 1 && rc[3] == 3 ) || ( rc[0] == 1 && rc[1] == 3 && rc[2] == 1 && rc[3] == 2 ) )    { if( z[1]=='0' && check) { z[1]='1' ; return 1 ; }b[3] = b[4] = b[5] = '_' ;        d[2] = d[1] = ' ' ;    }   
    if( ( rc[0] == 1 && rc[1] == 3 && rc[2] == 1 && rc[3] == 4 ) || ( rc[0] == 1 && rc[1] == 4 && rc[2] == 1 && rc[3] == 3 ) )    { if( z[2]=='0' && check) { z[2]='1' ; return 1 ; }b[6] = b[7] = b[8] = '_' ;       d[2] = d[3] = ' ' ;    }
    if( ( rc[0] == 1 && rc[1] == 4 && rc[2] == 1 && rc[3] == 5 ) || ( rc[0] == 1 && rc[1] == 5 && rc[2] == 1 && rc[3] == 4 ) )    { if( z[3]=='0' && check) { z[3]='1' ; return 1 ; }b[9] = b[10] = b[11] = '_' ;       d[4] = d[3] = ' ' ;    }
    
    if( ( rc[0] == 2 && rc[1] == 1 && rc[2] == 2 && rc[3] == 2 ) || ( rc[0] == 2 && rc[1] == 2 && rc[2] == 2 && rc[3] == 1 ) ) { if( z[4]=='0' && check) { z[4]='1' ; return 1 ; }b[12] = b[13] = b[14] = '_' ; }
    if( ( rc[0] == 2 && rc[1] == 2 && rc[2] == 2 && rc[3] == 3 ) || ( rc[0] == 2 && rc[1] == 3 && rc[2] == 2 && rc[3] == 2 ) ) { if( z[5]=='0' && check) { z[5]='1' ; return 1 ; }b[15] = b[16] = b[17] = '_' ; }
    if( ( rc[0] == 2 && rc[1] == 3 && rc[2] == 2 && rc[3] == 4 ) || ( rc[0] == 2 && rc[1] == 4 && rc[2] == 2 && rc[3] == 3 ) ) { if( z[6]=='0' && check) { z[6]='1' ; return 1 ; }b[18] = b[19] = b[20] = '_' ; }
    if( ( rc[0] == 2 && rc[1] == 4 && rc[2] == 2 && rc[3] == 5 ) || ( rc[0] == 2 && rc[1] == 5 && rc[2] == 2 && rc[3] == 4 ) ) { if( z[7]=='0' && check) { z[7]='1' ; return 1 ; }b[21] = b[22] = b[23] = '_' ; }
    
    if( ( rc[0] == 3 && rc[1] == 1 && rc[2] == 3 && rc[3] == 2 ) || ( rc[0] == 3 && rc[1] == 2 && rc[2] == 3 && rc[3] == 1 ) ) { if( z[8]=='0' && check) { z[8]='1' ; return 1 ; }b[24] = b[25] = b[26] = '_' ; }
    if( ( rc[0] == 3 && rc[1] == 2 && rc[2] == 3 && rc[3] == 3 ) || ( rc[0] == 3 && rc[1] == 3 && rc[2] == 3 && rc[3] == 2 ) ) { if( z[9]=='0' && check) { z[9]='1' ; return 1 ; }b[27] = b[28] = b[29] = '_' ; }
    if( ( rc[0] == 3 && rc[1] == 3 && rc[2] == 3 && rc[3] == 4 ) || ( rc[0] == 3 && rc[1] == 4 && rc[2] == 3 && rc[3] == 3 ) ) { if( z[10]=='0' && check) { z[10]='1' ; return 1 ; }b[30] = b[31] = b[32] = '_' ; }
    if( ( rc[0] == 3 && rc[1] == 4 && rc[2] == 3 && rc[3] == 5 ) || ( rc[0] == 3 && rc[1] == 5 && rc[2] == 3 && rc[3] == 4 ) ) { if( z[11]=='0' && check) { z[11]='1' ; return 1 ; }b[33] = b[34] = b[35] = '_' ; }
    
    if( ( rc[0] == 4 && rc[1] == 1 && rc[2] == 4 && rc[3] == 2 ) || ( rc[0] == 4 && rc[1] == 2 && rc[2] == 4 && rc[3] == 1 ) ) { if( z[12]=='0' && check) { z[12]='1' ; return 1 ; }b[36] = b[37] = b[38] = '_' ; }
    if( ( rc[0] == 4 && rc[1] == 2 && rc[2] == 4 && rc[3] == 3 ) || ( rc[0] == 4 && rc[1] == 3 && rc[2] == 4 && rc[3] == 2 ) ) { if( z[13]=='0' && check) { z[13]='1' ; return 1 ; }b[39] = b[40] = b[41] = '_' ; }
    if( ( rc[0] == 4 && rc[1] == 3 && rc[2] == 4 && rc[3] == 4 ) || ( rc[0] == 4 && rc[1] == 4 && rc[2] == 4 && rc[3] == 3 ) ) { if( z[14]=='0' && check) { z[14]='1' ; return 1 ; }b[42] = b[43] = b[44] = '_' ; }
    if( ( rc[0] == 4 && rc[1] == 4 && rc[2] == 4 && rc[3] == 5 ) || ( rc[0] == 4 && rc[1] == 5 && rc[2] == 4 && rc[3] == 4 ) ) { if( z[15]=='0' && check) { z[15]='1' ; return 1 ; }b[45] = b[46] = b[47] = '_' ; }
    
    if( ( rc[0] == 5 && rc[1] == 1 && rc[2] == 5 && rc[3] == 2 ) || ( rc[0] == 5 && rc[1] == 2 && rc[2] == 5 && rc[3] == 1 ) ) { if( z[16]=='0' && check) { z[16]='1' ; return 1 ; }b[48] = b[49] = b[50] = '_' ; }
    if( ( rc[0] == 5 && rc[1] == 2 && rc[2] == 5 && rc[3] == 3 ) || ( rc[0] == 5 && rc[1] == 3 && rc[2] == 5 && rc[3] == 2 ) ) { if( z[17]=='0' && check) { z[17]='1' ; return 1 ; }b[51] = b[52] = b[53] = '_' ; }
    if( ( rc[0] == 5 && rc[1] == 3 && rc[2] == 5 && rc[3] == 4 ) || ( rc[0] == 5 && rc[1] == 4 && rc[2] == 5 && rc[3] == 3 ) ) { if( z[18]=='0' && check) { z[18]='1' ; return 1 ; }b[54] = b[55] = b[56] = '_' ; }
    if( ( rc[0] == 5 && rc[1] == 4 && rc[2] == 5 && rc[3] == 5 ) || ( rc[0] == 5 && rc[1] == 5 && rc[2] == 5 && rc[3] == 4 ) ) { if( z[19]=='0' && check) { z[19]='1' ; return 1 ; }b[57] = b[58] = b[59] = '_' ; }
    
    if( ( rc[0] == 1 && rc[1] == 1 && rc[2] == 2 && rc[3] == 1 ) || ( rc[0] == 2 && rc[1] == 1 && rc[2] == 1 && rc[3] == 1 ) ) { if( z[20]=='0' && check) { z[20]='1' ; return 1 ; } a[0] = a[1] = '|' ; a[2] = '|' ;    }
    if( ( rc[0] == 1 && rc[1] == 2 && rc[2] == 2 && rc[3] == 2 ) || ( rc[0] == 2 && rc[1] == 2 && rc[2] == 1 && rc[3] == 2 ) ) { if( z[21]=='0' && check) { z[21]='1' ; return 1 ; } a[3] = a[4] = '|' ; a[5] = '|' ;    }
    if( ( rc[0] == 1 && rc[1] == 3 && rc[2] == 2 && rc[3] == 3 ) || ( rc[0] == 2 && rc[1] == 3 && rc[2] == 1 && rc[3] == 3 ) ) { if( z[22]=='0' && check) { z[22]='1' ; return 1 ; } a[6] = a[7] = '|' ; a[8] = '|' ;    }
    if( ( rc[0] == 1 && rc[1] == 4 && rc[2] == 2 && rc[3] == 4 ) || ( rc[0] == 2 && rc[1] == 4 && rc[2] == 1 && rc[3] == 4 ) ) { if( z[23]=='0' && check) { z[23]='1' ; return 1 ; } a[9] = a[10] = '|' ; a[11] = '|' ;   }
    if( ( rc[0] == 1 && rc[1] == 5 && rc[2] == 2 && rc[3] == 5 ) || ( rc[0] == 2 && rc[1] == 5 && rc[2] == 1 && rc[3] == 5 ) ) { if( z[24]=='0' && check) { z[24]='1' ; return 1 ; } a[12] = a[13] = '|' ; a[14] = '|' ;    }
    
    if( ( rc[0] == 2 && rc[1] == 1 && rc[2] == 3 && rc[3] == 1 ) || ( rc[0] == 3 && rc[1] == 1 && rc[2] == 2 && rc[3] == 1 ) ) { if( z[25]=='0' && check) { z[25]='1' ; return 1 ; } a[15] = a[16] = '|' ; a[17] = '|' ;    }
    if( ( rc[0] == 2 && rc[1] == 2 && rc[2] == 3 && rc[3] == 2 ) || ( rc[0] == 3 && rc[1] == 2 && rc[2] == 2 && rc[3] == 2 ) ) { if( z[26]=='0' && check) { z[26]='1' ; return 1 ; } a[18] = a[19] = '|' ; a[20] = '|' ;    }
    if( ( rc[0] == 2 && rc[1] == 3 && rc[2] == 3 && rc[3] == 3 ) || ( rc[0] == 3 && rc[1] == 3 && rc[2] == 2 && rc[3] == 3 ) ) { if( z[27]=='0' && check) { z[27]='1' ; return 1 ; } a[21] = a[22] = '|' ; a[23] = '|' ;    }
    if( ( rc[0] == 2 && rc[1] == 4 && rc[2] == 3 && rc[3] == 4 ) || ( rc[0] == 3 && rc[1] == 4 && rc[2] == 2 && rc[3] == 4 ) ) { if( z[28]=='0' && check) { z[28]='1' ; return 1 ; } a[24] = a[25] = '|' ; a[26] = '|' ;    }
    if( ( rc[0] == 2 && rc[1] == 5 && rc[2] == 3 && rc[3] == 5 ) || ( rc[0] == 3 && rc[1] == 5 && rc[2] == 2 && rc[3] == 5 ) ) { if( z[29]=='0' && check) { z[29]='1' ; return 1 ; } a[27] = a[28] = '|' ; a[29] = '|' ;    }
    
    if( ( rc[0] == 3 && rc[1] == 1 && rc[2] == 4 && rc[3] == 1 ) || ( rc[0] == 4 && rc[1] == 1 && rc[2] == 3 && rc[3] == 1 ) ) { if( z[30]=='0' && check) { z[30]='1' ; return 1 ; } a[30] = a[31] = '|' ; a[32] = '|' ;    }
    if( ( rc[0] == 3 && rc[1] == 2 && rc[2] == 4 && rc[3] == 2 ) || ( rc[0] == 4 && rc[1] == 2 && rc[2] == 3 && rc[3] == 2 ) ) { if( z[31]=='0' && check) { z[31]='1' ; return 1 ; } a[33] = a[34] = '|' ; a[35] = '|' ;    }
    if( ( rc[0] == 3 && rc[1] == 3 && rc[2] == 4 && rc[3] == 3 ) || ( rc[0] == 4 && rc[1] == 3 && rc[2] == 3 && rc[3] == 3 ) ) { if( z[32]=='0' && check) { z[32]='1' ; return 1 ; } a[36] = a[37] = '|' ; a[38] = '|' ;    }
    if( ( rc[0] == 3 && rc[1] == 4 && rc[2] == 4 && rc[3] == 4 ) || ( rc[0] == 4 && rc[1] == 4 && rc[2] == 3 && rc[3] == 4 ) ) { if( z[33]=='0' && check) { z[33]='1' ; return 1 ; } a[39] = a[40] = '|' ; a[41] = '|' ;    }
    if( ( rc[0] == 3 && rc[1] == 5 && rc[2] == 4 && rc[3] == 5 ) || ( rc[0] == 4 && rc[1] == 5 && rc[2] == 3 && rc[3] == 5 ) ) { if( z[34]=='0' && check) { z[34]='1' ; return 1 ; } a[42] = a[43] = '|' ; a[44] = '|' ;    }
    
    if( ( rc[0] == 4 && rc[1] == 1 && rc[2] == 5 && rc[3] == 1 ) || ( rc[0] == 5 && rc[1] == 1 && rc[2] == 4 && rc[3] == 1 ) ) { if( z[35]=='0' && check) { z[35]='1' ; return 1 ; } a[45] = a[46] = '|' ; a[47] = '|' ;    }
    if( ( rc[0] == 4 && rc[1] == 2 && rc[2] == 5 && rc[3] == 2 ) || ( rc[0] == 5 && rc[1] == 2 && rc[2] == 4 && rc[3] == 2 ) ) { if( z[36]=='0' && check) { z[36]='1' ; return 1 ; } a[48] = a[49] = '|' ; a[50] = '|' ;    }
    if( ( rc[0] == 4 && rc[1] == 3 && rc[2] == 5 && rc[3] == 3 ) || ( rc[0] == 5 && rc[1] == 3 && rc[2] == 4 && rc[3] == 3 ) ) { if( z[37]=='0' && check) { z[37]='1' ; return 1 ; } a[51] = a[52] = '|' ; a[53] = '|' ;    }
    if( ( rc[0] == 4 && rc[1] == 4 && rc[2] == 5 && rc[3] == 4 ) || ( rc[0] == 5 && rc[1] == 4 && rc[2] == 4 && rc[3] == 4 ) ) { if( z[38]=='0' && check) { z[38]='1' ; return 1 ; } a[54] = a[55] = '|' ; a[56] = '|' ;    }
    if( ( rc[0] == 4 && rc[1] == 5 && rc[2] == 5 && rc[3] == 5 ) || ( rc[0] == 5 && rc[1] == 5 && rc[2] == 4 && rc[3] == 5 ) ) { if( z[39]=='0' && check) { z[39]='1' ; return 1 ; } a[57] = a[58] = '|' ; a[59] = '|' ;    }
    
    return 0 ;
}

void pointer_dot(char* f, char* a ,char* b, char* c, int* pc )
{
    if( ( a[0] == a[3] && a[3] == '|') && ( b[0] == b[12] && b[12] == '_' ) )         if(f[0] == '0')    {           if(pc[0]) c[0] = '1'  ;else c[0]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[0] ='1';         }     
    if( ( a[6] == a[3] && a[3] == '|') && ( b[3] == b[15] && b[15] == '_' ) )        if(f[1] == '0')     {           if(pc[0]) c[1] = '1'  ;else c[1]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[1] ='1';         }        
    if( ( a[6] == a[9] && a[9] == '|') && ( b[6] == b[18] && b[18] == '_' ) )        if(f[2] == '0')     {           if(pc[0]) c[2] = '1'  ;else c[2]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[2] ='1';         }    
    if( ( a[9] == a[12] && a[12] == '|') && ( b[9] == b[21] && b[21] == '_' ) )      if(f[3] == '0')     {           if(pc[0]) c[3] = '1'  ;else c[3]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[3] ='1';         }    
    if( ( a[15] == a[18] && a[18] == '|') && ( b[24] == b[12]  && b[12]== '_' ) )    if(f[4] == '0')     {           if(pc[0]) c[4] = '1'  ;else c[4]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[4] ='1';         }    
    if( ( a[18] == a[21] && a[21] == '|') && ( b[15] == b[27] && b[27] == '_' ) )    if(f[5] == '0')     {           if(pc[0]) c[5] = '1'  ;else c[5]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[5] ='1';         }    
    if( ( a[21] == a[24] && a[24] == '|') && ( b[18] == b[30] && b[30] == '_' ) )    if(f[6] == '0')     {           if(pc[0]) c[6] = '1'  ;else c[6]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[6] ='1';         }    
    if( ( a[24] == a[27] && a[27] == '|') && ( b[21] == b[33] && b[33] == '_' ) )    if(f[7] == '0')     {           if(pc[0]) c[7] = '1'  ;else c[7]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[7] ='1';         }    
    if( ( a[30] == a[33] && a[33] == '|') && ( b[24] == b[36] && b[36] == '_' ) )    if(f[8] == '0')     {           if(pc[0]) c[8] = '1'  ;else c[8]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[8] ='1';         }    
    if( ( a[33] == a[36] && a[36] == '|') && ( b[27] == b[39] && b[39] == '_' ) )    if(f[9] == '0')     {           if(pc[0]) c[9] = '1'  ;else c[9]  = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[9] ='1';         }    
    if( ( a[36] == a[39] && a[39]== '|') && ( b[30] == b[42] && b[42] == '_' ) )    if(f[10] == '0')     {           if(pc[0]) c[10] = '1' ;else c[10] = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[10] ='1';        }    
    if( ( a[39] == a[42] && a[42]== '|') && ( b[33] == b[45] && b[45] == '_' ) )    if(f[11] == '0')     {           if(pc[0]) c[11] = '1' ;else c[11] = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[11] ='1';        }    
    if( ( a[45] == a[48] && a[48] == '|') && ( b[36] == b[48] && b[48] == '_' ) )   if(f[12] == '0')     {           if(pc[0]) c[12] = '1' ;else c[12] = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[12] ='1';        }    
    if( ( a[51] == a[48] && a[48] == '|') && ( b[39] == b[51] && b[51] == '_' ) )   if(f[13] == '0')     {           if(pc[0]) c[13] = '1' ;else c[13] = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[13] ='1';        }    
    if( ( a[54] == a[51] && a[51] == '|') && ( b[42] == b[54] && b[54] == '_' ) )   if(f[14] == '0')     {           if(pc[0]) c[14] = '1' ;else c[14] = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[14] ='1';        }    
    if( ( a[57] == a[54] && a[55] == '|') && ( b[45] == b[57] && b[57] == '_' ) )   if(f[15] == '0')     {           if(pc[0]) c[15] = '1' ;else c[15] = '2';  ;if(pc[0])pc[1]++;else pc[2]++;    f[15] ='1';        }
    return ;
}

int check_dot(char c[])
{
    for(int i =0;i<16;i++)
    if(c[i]==' ')
    return 1;
    
    return 0;
}

void  game_dot( char* p1, char* p2, int* p)
{
    // pc[0]gle , player1 , player2 
    int pc[3] = {0,0,0};

    // rc[0] column1 rc[2] column2
    int rc[4] = {0,0,0,0};  

    // flag for each pointer symbol
    char f[16]="0000000000000000";

    // for the checking for valid move 
    char z[40] ; 
    for(int j = 0 ; j < 40 ; j++)z[j] = '0';

    // a b c d arrays 
    int i ;
    char a[60] ;
    for(i=1;i<=60;i++)   {
    if(i%3==0)
    a[i-1] = '.' ;
    else
    a[i-1] = ' ' ;    }
    char b[60] ;
    for(i=0;i<60;i++)
    b[i] = ' ';
    char c[16] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' };
    char d[5] = { '.', '.', '.','.','.' };

    int tmp;
    printf("\n\n          \t|\t  WELCOME TO DOT GAME MULTIPLAYER! \n");
    printf("\n          \t|\t  to connect 2 dots, first enter the row, and then enter the column number for the first dot.\n");
    printf("\n          \t|\t  repeat for 2nd dot again. Press any key to continue \n");
    getch();

    char ch[50] = "\n" ; 

    for(i=1;check_dot(c)==1;i++)
    {
        invalid:        
            if(i%2==1)
            pc[0]= 1; 
            else 
            pc[0] = 0 ;
            board_dot(a,b,c,d);
            flag1: ;
            if(i%2==1)
            printf("\n          \t|\t  %s, enter row number for 1st dot ",p1);
            else 
            printf("\n          \t|\t  %s, enter row number for 1st dot ",p2);

            fflush(stdin);
            scanf("%[^\n]s",ch);
            rc[0] = atoi(ch); 
            if(( rc[0] > 5 || rc[0]< 1))
            {
                printf("\n          \t|\t  enter valid number {1,2,3,4,5} ");
                goto flag1 ;
            }
            flag2:;
            printf("\n          \t|\t  enter column number for first dot\n         \t|\t  ");

            fflush(stdin);
            scanf("%[^\n]s",ch);
            rc[1] = atoi(ch);
            if(( rc[1] > 5 || rc[1]< 1))
            {
                printf("\n          \t|\t  enter valid number {1,2,3,4,5} ");
                goto flag2 ;
            }
            flag3:;
            printf("\n          \t|\t  enter row number for 2nd dot");

            fflush(stdin);
            scanf("%[^\n]s",ch);
            rc[2] = atoi(ch);
            if(( rc[2] > 5 || rc[2]< 1))
            {
                printf("\n          \t|\t  enter valid number {1,2,3,4,5} ");
                goto flag3 ;
            }
            flag4:;
            printf("\n          \t|\t  enter column number for 2nd dot");
            fflush(stdin);
            scanf("%[^\n]s",ch);
            rc[3] = atoi(ch);
            if(( rc[3] > 5 || rc[3]< 1))
            {
                printf("\n          \t|\t  enter valid number {1,2,3,4,5} ");
                goto flag4 ;
            }
            
            if(mark_dot(rc,a,b,d,z,1)==1);
            else
            {
                printf("\n          \t|\t  inavlid input, try again ");
                goto invalid ;
            }
            if(i%2==1)
            tmp = pc[1] ;
            else 
            tmp = pc[2] ;

            mark_dot(rc,a,b,d,z,0);
            pointer_dot(f,a,b,c,pc) ;

            if( (i%2==1 && pc[1]>tmp) || (i%2==0 && pc[2]>tmp) )
            {
                if(check_dot(c)==0)break;
                printf("\n          \t|\t  extra chance for filling box ");
                goto invalid ;
            }

            printf("\n          \t|\t  scoreboard- PLAYER 1 --> %d , PLAYER 2 --> %d ",pc[1],pc[2]);
            if(check_dot(c)==0)
            break;
       
    }
    board_dot(a,b,c,d);
    printf("\n          \t|\t  the final scoreboard is\n          \t|\t  %s --> %d \n          \t|\t  %s --> %d ",p1,pc[1],p2,pc[2]);
    if(pc[1]>pc[2])
    printf("\n          \t|\t  %s wins ",p1);
    else if(pc[2]>pc[1])
    printf("\n          \t|\t  %s wins ",p2);
    else
    printf("\n          \t|\t  DRAW GAME \n");
    p[0] = pc[1] ; 
    p[1] = pc[2] ;
}


#endif
