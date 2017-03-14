Caltech CS2 Assignment 9: Othello

See [assignment9_part1.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part1.html) and [assignment9_part2.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part2.html)

Kelly worked on getting the original basic ai working from the first week. Helped with minimax
Commented throughout the functions
Anant worked on first ai, beat constant time player and better time player.
Also implemented negamax and alpha beta pruning. 


Put certain weights on the advantageous squares on the board, and negative weight on squares that are
bad to get. 

Alpha Beta Pruning:

If at any point we discover that making a move would set alpha greater than beta, we need not trace further
into that subtree, since that represents a "mistake" made by some side; either we have made a bad move that
allowed the opponent to drive the minimum score too low, or the opponent has made a bad move that allowed us
to drive the maximum score too high. In any case, the entire subtree resulting from that decision need not
be explored further.

This allows for deeper look ahead within the time limit because it no longer wastes time looking suboptimal
subtrees.

10 steps before the end, we look to maximize the number of pieces on the board rather than board score,
since number of pieces is what matters in the end. 


