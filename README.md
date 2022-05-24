- About the project: Support Assist is a useful application in which users will be looked after very carefully. 
Our application has three main functions:
1.	With the training function, you need to insert your information so that the app may suggest suitable exercises for you like cycling, jogging,....etc. 
2.	The app also has timer functions that users can set their time and focus on their tasks. 
3.	Finally, when it comes to making a list of a day, the app provides these interesting functions.  
When users start the app, they must sign in or sign up if they haven't had an account for use yet. After that, the menu will appear and users can choose one of the three options mentioned before. 
In case, users click on the timer button, 4 options for you to set the time are 15, 30, 45, and 60 minutes respectively. Moreover, users must insert their weight and height with the training function. Hence, the app would suggest to you how long you should spend doing exercises and show the result of BMI on the screen. Meanwhile, making a list is much easier with the timer function cause, only two buttons comprising of add button will replenish more textboxes and the save button for saving data. 
This project is named “Support Assist”

How to run this project:
    git init
    git clone https://github.com/jeikai/BT-ln-INT-221522.git
    
    //Build MyTexture
    g++ -Isrc/include -Lsrc/lib -c MyTexture.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    
    //Build Button
    g++ -Isrc/include -Lsrc/lib -c Button.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    
    //Build textbox
    g++ -Isrc/include -Lsrc/lib -c Textbox.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    
    //Build timer
    g++ -Isrc/include -Lsrc/lib -c Timer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    
    //Build Account
    g++ -Isrc/include -Lsrc/lib -c Account.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    
    //Build Demo app
    g++ -Isrc/include -Lsrc/lib -o demo demo.cpp MyTexture.o Button.o Textbox.o Timer.o Account.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_Contributors:
+Nguyen Minh Kien: textbox, timer functions, training functions, i/o files, password, sign in, sign up.
+Tran Quang Phuc: app graphics and design buttons, background….etc, list functions, making menu.
