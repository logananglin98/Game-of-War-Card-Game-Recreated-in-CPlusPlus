# L4: Game of War
## Code designed to learn to use stacks, queues, and deques correctly

## Author(s) of primary logic and code: Logan Anglin

## Author of deck and sort: Jan Pearce, Berea College

### Authors:

- Logan Anglin

### Starter files have been provided for you in C++

1. **HIGH LEVEL DESIGN**
*Complete the high-level design components in the Google Doc.*

2. **CRC Cards**
*Complete the CRC Card in the linked Google Doc. Turn on sharing and paste link to completed Google Doc here.*

https://docs.google.com/document/d/1sk8zBnHIohvz6NtB9HghK0vDp9tsYtg14oTWjSNh-gY/edit?usp=sharing

3. **Big O Analysis**
*Please analyze the Big O of all of the methods of the War class, including constructors. Hint: Your game uses 5 sets of cards, so for most, but possibly not all, of your methods, the input size (n) is the number of possible cards in the pile, but be sure you understand that this number should not be thought of as a constant! Anyone at anytime could possibly change either the number of decks used or even the number of cards in the deck for a game of War. (This is not far-fetched, the number of cards in a standard deck is 52 if you exclude Jokers or 54 if you include Jokers. A standard Tarot deck of cards has 78 cards. The normal Uno deck of cards has 108 cards. And, there are other decks...)*

War(): O(n) = n

add_dealingPile(): O(n) = n

deal(): O(n) = n

declare_war(): O(n) = n

check_piles: O(n) = n

display_winner: O(n) = 1

check_sizez(): O(n) = 1

game_run_method: O(n) = 1

draw_cards(): O(n) = 1

run_game(): O(n) = 1

4. **PROCESS SUMMARY**
*Briefly summarize your design and implementation process,
including how much your initial design plan evolved,
the final results you achieved, and the amount of time you spent
as a programmer or programmers in accomplishing these results.
This should be one or at most two paragraphs.*

My design plan changed heavily, primarily because I decided to design the infrastructure and methods of the program myself instead of using the suggested methods. Once I decided to implement
my own ideas for logic, I kind of came up with ideas as I went. My first working version of the code printed information to the terminal very similar to what is printed now, but I had very
few methods in the War class doing a lot of work, and most of the latter part of creating this program consisted of breaking the larger, multi-purpose methods into smaller methods. I don't
know that I have broken this program into as granular of a design as it could be, but it is certainly much easier to follow.
My final result is a program that is a little janky, but serves the purpose it should and (as far as I know) does what it should do. This lab took me much more time than any previous lab,
and a lot of this was due to debugging and constantly thinking of a new way to break down big methods into smaller methods.

5. **DESIGN CHALLENGES**
*Describe the primary conceptual challenges that you encountered
in trying to complete this lab and what might have made the
lab easier for you.*

The biggest challenge for the logic working right was making sure exactly the right amount of cards were moving where they should be moved. Getting empty dequeue errors became really
frustrating, and a significant amount of time was spent making sure the program didn't try to work with empty stacks or queues. Once I finally had the program working without those
empty dequeue errors, I almost missed that I was losing cards as the game progressed. Specifically, two cards were being lost every time the declare_war method was being called. I found
out the cards in the myCurrent and otherCurrent variables weren't being added into the storage stacks of the winner of the war. Once this problem was ironed out, the program ran as it 
should.

6. **ERRORS**
*List in bulleted form of all known errors
and deficiencies with a very brief explanation.*

- With the program as it is right now, I am unaware of any bugs other than any possibly caused by a wrong input when prompted. I still worry an empty dequeue error may pop up simply 
because of how common they were while testing the program, but I have tested the final version many times and haven't got that error since.

8. **OPTIONAL ENHANCMENT**
*If you chose to make an optional enhancement to deal with cycles,
discuss what rule you added, and why you added it. Also, discuss
how well your rule worked.*

I simply added a round counter that ends the game after 500 rounds. I also edited the logic to declare a winner so it would check which player has the most cards instead of only checking
if both stacks for the player or the opponent are empty. I added this because I occasionally get what seems to be an infinite loop. Considering that this game can theoretically never end
if I understand it correctly, the infinite loop made more sense (it may have not been infinite, but the program ran for 10 minutes once and the game never ended). 

9. **LEARNING AND REACTION**
*A paragraph or so of your own comments
on what you learned and your reactions to this lab.*

I learned how to implement stacks and queues into a program, the positives and negatives of using one structure over another, and how annoying it is to deal with the errors that come from
trying to manipulate empty data structures in C++.

10. **INTEGRITY STATEMENT**
*Please briefly describe ALL help you received and
all help you gave to others in completing this lab.
Also list all other references below.*

I was once again helped a lot by Dr. Pearce's starter code. The websites below came in handy too!

11. **Pairwork statement**
If you worked in a pair of programmers, you are required to use good pair programming practices, always working together and not using a divide and conquer technique in which only one of you does the work and learns. Also, the two programmers roles should be switched frequently--around every 20 minutes or so. If you worked alone, please say so. If you worked in a pair, please describe how you worked together.

I worked alone.

## References:
- This repo contains original deck and sort code by Jan Pearce
- https://cplusplus.com/reference/vector/vector/size/
- https://runestone.academy/assignment/student/doAssignment?assignment_id=171059
- https://cplusplus.com/doc/tutorial/operators/
- https://www.geeksforgeeks.org/cin-get-in-c-with-examples/
- https://www.youtube.com/watch?v=ZPTSRHIKuU0&ab_channel=GhostTogether
