#ELPMIS

(the term 'elpmis' comes from the reverse chronological character order of the word 'simple' )
ELPMIS is a simple social-media-like program which slightly mimics a website ,written purely in (Vannila) C using file handling to store data.

The main purpose of this project is to get experience on file handling, exception handling and explore the C programming language.

the usage of putch() under the conio header file makes this program run only in windows OS.
there is no specific things to download, it can be run on any IDE by running the main.c file.
One needs to search elpmis in the search bar when run the main.c files
the valid inputs : the spaces are stripped both sides 
elpmis.com
elpmis
www.elpmis.com
https://www.elpmis.com
https://elpmis.com

Build status:
The option to delete the elpmis account is currently not available. (all files except in the user_db are removed)
The snake game is unavailable yet.

functionalities :
-> signup
-> login
    --> username
    --> password
-> manage friend
    --> add friends
    --> delete friends
    --> view friends
    --> block friends
-> message friend
    --> send messages
    --> delete chats
    --> view chats
-> delete account
-> deactivate account
    --> auto reactivate when logged in again
-> change password
    --> via protective question about user, asked when created account
-> play games
    --> competitive games
        ---> 2048
        ---> snake
    --> local multiplayer games
        ---> S.O.S 
        ---> dots and boxes
-> view scores of all games
-> view friends' scores for competitive games 
-> view multiplayer games' history 

About file database:

user_db :
file will be created when done signing up. 
the files will be saved as <username>.txt format and the contents of the file would be username, password, first and last name, security question and answer,
date of joining and friends'list.

requests_db:
the file (named <username>.txt under this folder) will be created when user requests or recieves friend request. 
the 0 will represent recieval and 1 will represent sent 
eg. in requests_db\\abhi.txt 'rushi 1' indicates abhi has sent request to rushi hence in rushi,txt in the same directory, will have 'abhi 0' 
when request is accepted or deleted or account is deleted , both entries will be deleted from the file 

block_db:
file named <username>.txt will be created at the time of creating account, this is similar to requests_db, 
in block_db\\A.txt 'B 0' will imply 'A' has been blocked by 'B' and in block_db\\B.txt will have 'A 1' implies that B has blocked 'A'
when unblocked or deleted, the data will be removed from either account file

friends_db:
when a friend request is accepted by a user from other user, a file will be created the file name will be the 2 usernames (smaller fisrt) seperated by a space.
the messages exchanged shall be stored here. when unfriended or deleted, the data will be removed 

game_db:
the file name will be <username>.txt under this folder, created at the time of account creation
competitive games. i.e. snake and 2048 scores will be stored here 

casual:
the file name will be <username>.txt under this folder, created at the time of account creation
the causal games / local multiplayer games i.e sos and dots-and-boxes gaming history will be stored here 

deactivated_db.txt: 
the deactivated accounts' username will be stored in this file. when user logins back, automatically deletes the entry

Notes:
-> username cant use special characters except ./-/_ and some commands used as choices to input:
    {login, signup, close, view, delete, add, manage, close, chat, tmpp, ttmp, back, logout, remove, message , gamezone, select, exit,
    scores, score, play, mine, new, full, confirm , clear, retry, requests, profile, search, unsend, accept, block, unfriend, other}
-> in chat, recent 20 messages will be shown unless command 'full' which will anyway be shown in menu
-> each message is limited to 100 characters
-> only top 5 scores will be saved per competitive game 

refer headers.h to look at the built-in header files used 
refer prototypes.h to for the overview of all the user defined functions used in this project


Limitation:
-> this is a local project, multiple users can't use at same time, hence one user should logout before another user logins.

initial database status/details:

accounts: usernames:
abhi
akshay
rushi
tate

akshay and rushi are friends. 
they exchanged some messages

REQUESTS:
abhi sent friend request to rushi 
rushi has a pending request from abhi
akshay has a pending request from tate 
tate sent a friend request to akshay 

BLOCK:
rushi has blocked akshay 

DEACTIVATED:
abhi has deactivated 

GAMES:
rushi played 2048 once and scored 568
sos has been played in abhis' account and tate's account
dots-and-boxes has been played in rushi's account
