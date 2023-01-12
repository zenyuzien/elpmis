#ifndef prototypes_
#define prototypes_

char CHAT[] = "friends_db\\" ;
char USERDB[] = "user_db\\" ; 
char REQ[] = "requests_db\\" ;
char BLOCK[] = "block_db\\" ;
char GAME[] = "game_db\\" ;

char* global; // this will traverse across the project


// starting_page_functions

// zenyuzien search engine, type url of elpmis with optional www. or .com or https
void search_engine_display() ;           

// will check if give nurl is elpmis valid or not 
void validate_search_();        

// if it is a valid input then user is directed to the elpmis home page 
void elpmis_home(int);                     

// when user enters elpmis invalid url then user is directed to a error page design. 
void bad_search(char*);                   


    // user will enter details and appropriate files will be created, i.e. userdb file, block file, game files
    void signup_page();   
    
    // when user has an account, user shall enter credentials here
    void login_page(int) ;                        
    
    // verifies the password for corresponding username
    int isPassword(char*,char*);                
    
    // checks if the password entered matches the standard password protection protocol
    int password_checker(char*);                
    
    // checks if username is a standard one, i.e. not having special characters except -/_/. and avoiding keywords(refer readme)
    int username_checker(char*); 
    
    // checks if username exists in elpmis file database
    int isUsername(char*);                      

//after logging in
//functionalities

// display various functionalities in a menu driven system
void display_options(int);                     

// deletes the files associated with friends 
int delete_file();        

// the main delete function, attempts to delete all files, but sometimes partially fails, hence this option is currently unavailable
void deleteUser();

// a part of deletion functionality
void delUtility(char*);

// the message page
void send(); 

// displays the chat, allows user to enter new message or delete chat, clear chat based on param
void displayChat(char*, char*,int);            
     
    //friends_management

    // menu driven page to manage friends and profile
    void manage(int) ; 

        // redirects to search page                     
        void searchPage();

        // prints the pending sent and recieved requests and allows to take action 
        void requestsPage();

        // displays profile of a username
        int displayProfile(char*);       

        // checks if one is friend of other    
        int isFriend(char*, char*); 

        // creats the friend file of username to initiate conversation
        int addFriend(char*);                          

        // the user sends friend request to mentioned username
        void sendRequest(char*);                   

        // check if user is blocked or sent request or recieved request by mentioned username
        int checkRSB(char*, int, char*);        

        // returns the no.of friends according to param or prints the friends' list    
        int numFriends(char*,int); 

        // accepts the friend request- removes the data from requests database
        void acceptRequest(char*);

        // user blocks the username mentioned 
        void block(char*);

        // user unblocks the give nusername                           
        void unBlock(char*);             
        
        // the user account will deactivated and logged out
        void deactivate();  
        
        // returns 1 if user is deactivated or returns 0 when not
        int isDeactivated(char*);

        // prints the profile details of mentioned username          
        void profile(char* ,int);

        // deletes data from block file, deactivate file, requests file, friends file accoring to parameter 
        void deletionUtility(char*,char*,char*,int);                

        // change credentials of the user via security question
        void changeCred();
//helping_functions

// a delay for mentioned milliseconds
void delay(unsigned int) ;                  

// loading animation for a short while
void load_animation();           

// get firstname from username
char* getname(char*);         

// removes exess new lines from a file
void trim(char*,char*);      

// returns the smaller string, criteria for filename
int strP(char*, char*);                    

// return current date , not time
char* getTime(char*);                       

// menu will be printed to access games and gaming history
void gameZone(int);

// get the score or first part of the update the new score into the game file 
void getOrUpdateScore(char* , char*, int);

// the later part updation of score into the game file 
void rewrite(char*,char*,int*);

// prints the gaming history of casual games , returns the no.of games played from the file
int history(char* , int);
    //2048

    // the function where entire game runs. will return the score of the user
    int game_2048();

    // the board which is a matrix will be printed
    void display_matrix_2048() ;

    // either a 4 or 2 will be printed on the board at a random location unfilled 
    void randomPlace_2048();

    // checks if the game is still playabble or not
    int isFull_2048();

    // returns 1 if it is possible to slide along given direction
    int isSlide_2048(char*);

    // the sliding functionality updates the matrix elements accordingly 
    void slide_2048(int**,char*);

    // the summation of adacent equal terms will be done in the board.
    void sum_2048(int**,char*);//

    //dots and boxes

    // prints the current board of the dots and boxes game
    void board_dot(char*,char*,char*,char*);

    // the functionality which marks the dots. returns 1 is markable or 0 when unmarkable
    // returns 1 only when last param is 1, else it just marks
    int mark_dot(int* ,char*,char*,char*,char*,int);

    // the functionality which adds the point when found complete box formation
    void pointer_dot(char*,char*,char*,char*,int*);

    // returns 1 if there are boxes available to complete, else returns 0 when full
    int check_dot(char*);

    // the function where entire game runs, updates the array with the players' scores
    void game_dot(char*,char*,int*);

    //S.O.S

    // board_sos will print the current board of game 
    // 2 grids of 5x5 where the left board is the game board with s and o's while 
    // the right board will show reference of what number to press for easy selection
    void board_sos(char*);

    // checks if the game is still playable by the players returns 1 if still playable
    int game_sos(char*);

    //the function where the game works, returns the updated array with the players' scores. returns -1 when user wants to quit in between
    int game_sosUtility(char*,char*,int*);

    // the marking of s or o on the board is done by this function
    void mark_sos(char*,char*,int*);



#endif 