/*predicates
nondeterm result
nondeterm status(integer,string)
%status(x,r)(integer,string):(i,o)
nondeterm substr(integer,integer)
%substr(x,y)(integer,integer):(i,o)
clauses
substr(X,Y):-Y=2019-X.
status(X,"Centenar"):-X>100.
status(X,"Elderler"):-X>70, X<=100.
status(X,"Male"):-X>25, X<=70.
status(X,"Youth"):-X>16,X<=25.
status(X,"Teenager"):-X>12,X<=16.
status(X,"Child"):-X>2,X<=12.
status(_,"Baby").
result:-
write("Shove a date of berth :"),nl,
write("X="),readint(X),
substr(X,Y),
status(Y,R),
write("It is a ",R),nl.
goal
result.*/


predicates
nondeterm result
nondeterm status(integer,string)
%status(x,r)(integer,string):(i,o)
nondeterm substr(integer,integer)
%substr(x,y)(integer,integer):(i,o)
clauses
substr(X,Y):-Y=2019-X.

status(X,"Centenar"):-X>100,!.
status(X,"Elderler"):-X>70,!.
status(X,"Male"):-X>25,!.
status(X,"Youth"):-X>16,!.
status(X,"Teenager"):-X>12,!.
status(X,"Child"):-X>2,!.
status(_,"Baby").
result:-
write("Shove a date of berth :"),nl,
write("X="),readint(X),
substr(X,Y),
status(Y,R),
write("It is a ",R),nl.
goal
result.