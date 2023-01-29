schedule(canakkale, erzincan, 6).
schedule(erzincan, antalya, 3).
schedule(antalya, izmir, 2).
schedule(antalya, diyarbakir, 4).
schedule(izmir, istanbul, 2).
schedule(izmir, ankara, 6).
schedule(diyarbakir, ankara, 8).
schedule(istanbul, ankara, 1).
schedule(istanbul, rize, 4).
schedule(ankara, rize, 5).
schedule(ankara, van, 4).
schedule(van, gaziantep, 3).
schedule(gaziantep, mugla, 7).
schedule(antalya, bursa, 2).

/* Check whether is there a connection between A and B. */
connection(A, B, C) :- connection(A, B, [], C).

/* Check schedules from A to B, without same path is not visited again. */
connection(A, B, Visited, C) :- schedule(A, B, K), C is K; /* If there is a direct schedule from A to B, C is K. */
                                schedule(B, A, K), C is K; /* If there is a direct schedule from B to A, C is K. */
                                schedule(A, X, K), /* If there is a schedule from A to X with cost K. */
                                \+contains([A, X], Visited), /* If the A-X path is not visited, continue. */
                                \+contains([X, A], Visited), /* If the X-A path is not visited, continue. */
                                connection(X, B, [[A, X] | Visited], L), /* If there is a connection between X to B with cost L, add A-X path to Visited list. */
                                B \= A,
                                C is K + L; /* C is sumation of the costs of the A-X path and X-A path. */
                                schedule(X, A, K), /* If there is a schedule from A to X with cost K. */
                                \+contains([A, X], Visited), /* If the A-X path is not visited, continue. */
                                \+contains([X, A], Visited), /* If the X-A path is not visited, continue. */
                                connection(X, B, [[A, X] | Visited], L), /* If there is a connection between X to B with cost L, add A-X path to Visited list. */
                                B \= A,
                                C is K + L. /* C is sumation of the costs of the A-X path and X-A path. */
                                
/* Check whether list contains another list. */
contains(A,[A|_]).
contains(A,[_|Tail]) :- contains(A,Tail).

