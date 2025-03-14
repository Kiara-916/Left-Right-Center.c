#include "game.h"
#include "randi.h"
#include "strings.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
* Here is an array of player names.  Given a player number i, use the
* player names like this:
*
*   player_name[i]
*
* Following this array declaration is the definition of MAX_PLAYERS.  The
* player number i can be anything from 0 to MAX_PLAYERS - 1.
*/


const char *player_name[] = {

    "Ada Lovelace",
    /*
    * 1815-1852.  Wrote the first algorithm for a computer.
    */

    "Margaret Hamilton",
    /*
    * 1936-.  While in her 20s, lead the team that wrote and tested the
    * Apollo moon program's on-board flight software. Invented the term
    * "software engineering".
    */

    "Katherine Johnson",
    /*
    * 1918-2020.  Mathematician who hand-calculated trajectories for crewed
    * spaceflights.
    */

    "Joy Buolamwini",
    /*
    * ~1989-.  MIT computer scientist who works to challenge racial and
    * gender bias in AI-based decision software.
    */

    "Grace Hopper",
    /*
    * 1906-1992.  Mathematician and computer scientist who made the first
    * machine-independent computer language.
    */

    "Adele Goldberg",
    /*
    * 1945-.  Managed the team at Xerox that developed object-oriented
    * programming and graphical user interfaces.
    */

    "Annie Easley",
    /*
    * 1933-2011.  NASA computer scientist and mathematician who developed
    * algorithms that analyze various power technologies.
    */

    "Jeannette Wing",
    /*
    * 1956-.  Led many research projects as a university professor and as a
    * vice president at Microsoft Research.
    */

    "Mary Kenneth Keller",
    /*
    * 1913-1985.  First person to earn a Ph.D. in computer science in the
    * United States.
    */

    "Megan Smith",
    /*
    * 1964-.  Vice president at Google and 3rd Chief Technology Officer of
    * the United States.
    */

    "Radia Perlman",
    /*
    * 1958-.  Computer programmer and network engineer who invented many
    * network protocols include the Spanning Tree Protocol used by network
    * bridges.
    */
};

/*
* Faces of the die are numbered 0 through 5, and each face has a symbol.
* Create an array of six Symbols that is indexed by the face number.  Then
* you can convert the roll of a die (0-5) into a Symbol by accessing the
* array like this:
*
*    Symbol sym = symbol_of_roll[roll];
*/
const Symbol symbol_of_roll[6] = {
    DOT,
    DOT,
    DOT,
    LEFT,
    CENTER,
    RIGHT,
};

int score[MAX_PLAYERS];


/*
* Return the letter of the Symbol according to this table:
*
*    sym    return
*   ------  ------
*   DOT      '.'
*   LEFT     'L'
*   CENTER   'C'
*   RIGHT    'R'
*/
char letter_of_symbol(Symbol sym) {
    switch (sym) {
        case DOT: return '.';
        case LEFT: return 'L';
        case CENTER: return 'C';
        case RIGHT: return 'R';
        default: return '?'; //for unexpected cases

    }
    return 0;
}

/*
* Return a or b, whichever is smallest.
*/
int min(int a, int b) {
    if (a < b) {return a;}
    else {
        return b;
    }
    // Replace this comment with your source code.
    //return 0;
}

/*
* Return the next roll of a CSE 13S die.  That is, call randi(), and then
* convert the result into a number between 0 and 5.
*/
int rand_roll(void) {
    return randi() % 6;// Replace this comment with your source code.

    return 0;
}

/*
* Return the number of the player that is to the LEFT of the player with
* the number given in parameter "player".  (See Section 2 of the assignment
* PDF.)
*/
int left_of(int player, int num_players) {
    return (player == num_players - 1) ? 0 : player + 1;// Replace this comment with your source code.
    return 0;
}

/*
* Return the number of the player that is to the RIGHT of the player with
* the number given in parameter "player".  (See Section 2 of the assignment
* PDF.)
*/
int right_of(int player, int num_players) {
    if (player == 0) {
    return num_players -1;
    }
    // Replace this comment with your source code.
    return player - 1;
}

/*
* Print all of the players' scores followed by the number of chips in the
* pot.  The scores are in the array score[], which is delcared near the top
* of this file.  You can compute the number of chips in the pot (the game
* has a total of 3 * num_players chips), or you can maintain the pot's
* score in a new variable that you declare up where the score[] array is.
*
* Here is an example of the output:

Current scores:
    3 -- Ada Lovelace
    3 -- Margaret Hamilton
    3 -- Katherine Johnson
    0 -- pot

* If you want, you can use two format strings in the file string.h:
* CURRENT_SCORES and SCORE_ds.  Look in strings.h to see what they
* represent.
*/
int pot = 0;

void print_scores(int num_players) {
    printf(CURRENT_SCORES);

    for (int i = 0; i < num_players; i++) {
        printf(SCORE_ds, score[i], player_name[i]);
    }// Replace this comment with your source code.
   
    printf(SCORE_ds, pot, "pot");   // pot = (3 * num_players) - pot;  use for later
   /// printf(SCORE_ds, pot, "pot");
}

/*
* Play the game.  See Section 2 of the assignment PDF for details.
*/
void play_game(int seed, int num_players) {
    randi_seed(seed);

    for (int i = 0; i < num_players; i++) {
        score[i] = 3;
        
    }// Replace this comment with your source code.
    int current_player = 0;
    ///int total_chips = 3 * num_players;
    print_scores(num_players);
    while(1){
        int active_players = 0;

        for (int i = 0; i < num_players; i++) {
            if (score[i] > 0) {
                active_players++;
            }
        }
        if (current_player == num_players){current_player = 0;}
        if (active_players == 1) {
            for (int i = 0; i < num_players; i++) {
                if (score[i] > 0){
                    printf(ONE_PLAYER_HAS_CHIPS);
                    printf(WON_s, player_name[i]);
                    exit(1);
                }
           } 
          // break; ///game ends if only one player has chips
        }
        if (score[current_player] <= 0) {
            printf(HAS_NO_CHIPS_s, player_name[current_player] );

            current_player++;
            continue;
        }

        int rolls = min(score[current_player], 3);
        printf(TURN_s, player_name[current_player]);///max of 3 rolls
       
        for (int i = 0; i < rolls; i++) {
            int dice_r = rand_roll();
            Symbol sym = symbol_of_roll[dice_r];
            printf(ROLLS_c, letter_of_symbol(sym));
            switch (sym) {
                case LEFT:
                    score[current_player]--;
                    score[left_of(current_player, num_players)]++;
                    printf(GIVES_A_CHIP_TO_s,player_name[left_of(current_player, num_players)]);
                    break;
                case RIGHT:
                    score[current_player]--;
                    score[right_of(current_player, num_players)]++;
                    printf(GIVES_A_CHIP_TO_s,player_name[right_of(current_player,num_players)]);
                    break;
                case CENTER:
                    score[current_player]--;
                    pot++;
                    printf(PUTS_A_CHIP);
                    break;
                default://dot
                    break;
            }
        
        }
        //if (score[current_player] <= 0) {
         //   printf(HAS_NO_CHIPS_s, player_name[current_player]);
        //} ///move
        //current_player = right_of(current_player, num_players) ;       
        //the next
        current_player++; 
        print_scores(num_players); 
    }

   // print_scores(num_players); //print final scores
}   

