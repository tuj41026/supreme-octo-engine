#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse(char * points);
int add(char * token);

/*Bowling Game code by Olivia Chaves
 * Test Cases:
 * X-X-X-X-X-X-X-X-X-X-X-X = 300
 * 45-54-36-27-09-63-81-18-90-72 = 90
 * 5/-5/-5/-5/-5/-5/-5/-5/-5/-5/-5 = 150
 * 13-X-X-X-7/-5/-43-8/-50-X-X-X = 167
 * */

int main(int argc, const char * argv[]) {
    printf("Please enter each frame with a \"-\" in between\nFor example, instead of \"X-X-X-X-X-X-X-X-X-XXX\" please type \"X-X-X-X-X-X-X-X-X-X-X-X\"\n");
    //create an array that can hold the maximum number of characters
    // necessary to represent a 10 frame game
    char * string = malloc(sizeof(char)*34);

    //Obtain input from user
    printf("Enter Throws: ");
    scanf("%s", string);

    //Parse the input
    parse(string);

    //Free memory
    free(string);
}

void parse(char * points){
    int pin = 0; //Value of first pin in a frame
    int current = 0;//Current type: 2 = strike, 1 = spare, 0 = regular frame
    int last = 0; //Last type
    int fort = 0; //Type from 2 throws ago
    int score = 0; //Current score
    int frame = 0; //Value of frame
    int count = 0; //Counter for calculating final throw

    //Tokenize the input using "-" as the delimeter
    char * token = strtok(points, "-");

    //Calculate scores for first 9 throws
    for(int i = 0; i < 9; i++) {
        //strike
        if(strcmp(token, "X")==0){
            current = 2;
            pin = 10;
            frame = 10;
        }
            //spare
        else if(strstr(token, "/")!= NULL){
            current = 1;
            pin = atoi(token);
            frame = 10;
        }
            //regular frame
        else{
            //split the numbers and add together
            current = 0;
            pin = atoi(token)/10;
            frame = add(token);
        }

        //Calculate bonus scores from last throws
        if(fort == 2 && last == 2){
            score += pin;
        }
        if(last == 2){
            score += frame;
        }
        if(last == 1){
            score += pin;
        }
        //Add the score from this throw
        score += frame;

        //Get the next token
        token = strtok(NULL, "-");

        //Increment fort and last
        fort = last;
        last = current;

    }
    //Tenth Frame
    while(token != NULL) {
        //strike
        if(strcmp(token, "X")==0){
            current = 2;
            pin = 10;
            frame = 10;
        }
            //spare
        else if(strstr(token, "/")!= NULL){
            current = 1;
            pin = atoi(token);
            frame = 10;
        }
            //regular frame
        else{
            //split the numbers and add together
            current = 0;
            pin = atoi(token);
            frame = add(token);
        }
        if(fort == 2 && last == 2 && count < 2){
            //Don't add this if it is the third in a series of strikes
            score += pin;
        }
        if(last == 2){
            score += frame;
        }
        if(last == 1){
            score += pin;
        }
        if(count == 0){
            score += frame;
        }

        //get next token
        token = strtok(NULL, "-");

        //Increment fort and last
        fort = last;
        last = current;

        //Increment count to see whether this is 10th, 11th, or 12th throw
        count += 1;
    }
    //Print the final score
    printf("Final Score: %d\n", score);
}

int add(char * token) {
    int a = atoi(token);
    int b = a % 10;
    int c = a / 10;
    return (c + b);
}