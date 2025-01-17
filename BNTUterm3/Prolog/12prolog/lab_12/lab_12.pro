domains
  		db_selector = vdb
  		name,surname,pol = string
  		day,month,year = integer
  		d = date(day,month,year)
  		st = student(name,surname,d,pol)
predicates
  		nondeterm repeat         
  		nondeterm menu
  		nondeterm process(integer)
  		nondeterm error
  		nondeterm start         
 
clauses

  start:-existfile("my.db"),
    	db_open(vdb,"my.db",in_file),
    	write("�� �������"),nl;
    	db_create(vdb,"my.db",in_file),
    	write("�� �������"),nl.
    	   
  repeat.
  repeat:-repeat. 
  
  menu:-repeat,
    write("*************����*************"),nl,
    write("  1 - ������� � ��� ���������, ���������� ���� (gr210)"),nl,
    write("  2 - ������� � ��� ���������, ���������� � ������������ ����� (gr210 � gr310)"),nl,
    write("  3 - �������� ���������� (gr210 ��� gr310)"),nl,
    write("  4 - ���������� ����������"),nl,
    write("  5 - �������� ����������"),nl,
    write("  6 - ������� �� ���� �� ������� � �����, ��� ����� ������� ������ ����� �����"),nl,
    write("  7 - �����"),nl,
    write("*********************************"),nl,
    write("������� ���� � ����(1-7)"),nl,
    readint(X),%������ ����� ������ ����
    process(X),X=7,!.    
  
  
  process(1):-write("������� ��� �������� (�/�) -  "),
    	readln(Pol),%������ ��� ��������
    	upper_lower(Pol,Pol1),
    	chain_terms(vdb, "gr210", st, student(Name, Surname, _, Pol1), _),
          write(Name, ' ', Surname, ' '),nl.
    
  process(2):-write("������� ����� �������� - "),
  		     readint(Month),
    	     db_chains(vdb, Chain), 		         chain_terms(vdb,Chain,st,student(Name,Surname,date(_,Month,_),_),_),
    	     write(Surname,' ',Name), nl.       
    
  process(3):-write("������� ��� ������� - "),
  		     readln(Name_chain),
  		     write("--------------------------------------------------\n"),
     		     chain_terms(vdb,Name_chain,st,student(Name,Surname,date(Day,Month,Year),Pol),_),
    	     write(Name,' ',Surname,"  ",Day,'.',Month,'.',Year,"   ",Pol),nl.
     
  process(4):-write("������� ��� ������� - "),
  		     readln(Name_chain),
   		     write("��� - "),     
   		     readln(Name),
   		     write("������� - "), 
   		     readln(Surname),  
   		     write("���� ��������:"), nl,    
   		     write("���� - "), 
   		     readint(Day),    
   		     write("����� - "),
   		     readint(Month),    
    	     write("��� - "),
    	     readint(Year),    
   		     write("��� (�/�) - "),
   		     readln(Pol),
   		     upper_lower(Pol,Pol1), 
   		     chain_insertz(vdb,Name_chain,st,student(Name, Surname,date(Day, Month, Year), Pol1),_).
   	
  process(5):-write("������� ��� ������� - "),
 		     readln(Name_chain),
    	     write("������� ������� - "),
    	     readln(Surname),
                 chain_terms(vdb,Name_chain, st, student(_,Surname,_,_),Ref),
    	     term_delete(vdb,Name_Chain,Ref),
    	     write(Surname," - ������"),nl.
   		    
 process(6):-db_chains(vdb,Chain),
   	  	   chain_terms(vdb,Chain,st,student(Name,Surname,_,_),_),
   	         str_len(Name,N),
   		   str_len(Surname,S), N>S,
   		   write(Name," ", Surname), nl.
   	
 process(7):-write("������ ���������? (�/�)"),nl,
    	    readln(R),
    	    upper_lower(R,R),
    	    frontchar(R,'�',_),!. 
        
 process(X):-X<1,error;X>7,error.
     
 error:-write("��������� ����� ������ ���� � ��������� 1-7"),nl,
    	write("������� ����� ������!"),nl,nl,
    	readchar(_). %�������� ������� ����� �������   

goal
  	  start,
  	  menu,
  	  db_close(vdb).










































/*
domains

db_selector = database1.
student = s(string, string, string, integer, integer, integer, string).

predicates

nondeterm res.
nondeterm menu.				
nondeterm process(integer).
nondeterm control_open_file(string).
nondeterm view_database.
nondeterm view_database2(ref).
nondeterm view_database3.
nondeterm add(integer).
nondeterm delete(integer).
nondeterm show(integer).
nondeterm show2(string).
nondeterm show3(integer).
nondeterm letter.
nondeterm check(string,string,char).

nondeterm rav(string,char,char).

clauses

res:- menu.

%���� ���������
menu:- nl, write ("*******************"), nl,
write ("0. �����"), nl, 
write ("1. C������ ���� ������"), nl,
write ("2. ����������� ���� ������"), nl, 
write ("3. ���������� ��������� � ���� ������"), nl,  
write ("4. �������� ���� ������"), nl, 
write ("5. �������� �������� �� ���� ������"), nl, 
write ("6. �������� �������"), nl, 
write ("7. �������������� ������� - ����� ��������, ������� �������� �������� �����"), nl,
write ("8. �������� �������"), nl,nl,
write ("*******************"), nl, 
write ("������� ����� ����"), nl, readint (X), process(X), !.

process(0).
process(1):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), db_create(database1, FileAddress, in_file),  
db_close(database1), menu.

process(2):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), control_open_file(FileAddress), 
db_open(database1, FileAddress, in_file), view_database, db_close(database1), menu.

process(3):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), control_open_file(FileAddress), 
db_open(database1, FileAddress, in_file), add(1), db_close(database1), menu.

process(4):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), control_open_file(FileAddress), 
db_delete(FileAddress, in_file), nl, write("���� ������ �������"), nl, menu.

process(5):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), control_open_file(FileAddress), db_open(database1, FileAddress, in_file),
db_statistics(database1, CountTerms, _, _, _), delete(CountTerms), db_close(database1), menu.

process(6):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), control_open_file(FileAddress), 
db_open(database1, FileAddress, in_file), nl, write("������ � ����� ��������(����� 1) / ������ � ����� ���������(����� 2)"), nl, readint(Chain), nl,  show(Chain).

process(7):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), control_open_file(FileAddress), 
db_open(database1, FileAddress, in_file), nl, letter, db_close(database1), menu.

process(8):- nl, write("������� ��� ���� ������"), nl, readln(FileAddress), control_open_file(FileAddress), 
db_open(database1, FileAddress, in_file), view_database3, db_close(database1), menu.

% ������ � ��������� ������
show(0):- db_close(database1), menu.
show(1):- write("�������� ��� �/�"), nl, readln(S), nl, show2(S),
write("������ � ����� ��������(����� 1) / ������ � ����� ���������(����� 2) ��� 0 ��� ������"), nl, readint(Chain), show(Chain).
show(2):- write("�������� �����"), nl, readint(Month), nl, show3(Month),
write("������ � ����� ��������(����� 1) / ������ � ����� ���������(����� 2)  ��� 0 ��� ������"), nl, readint(Chain), show(Chain).
show(_):- write("������"), nl, nl, write("������ � ����� ��������(����� 1) / ������ � ����� ���������(����� 2) ��� 0 ��� ������"), nl, 
readint(Chain), nl, show(Chain).

show2(S):- chain_terms(database1, "gr215", student, s(F, I, O, Day, Month, Year, S), _), 
write("�������: ", F), nl, write("���: ", I), nl, write("��������: ", O), nl, 
write("���� ��������: ", Day,".", Month, ".", Year), nl, fail.
show2(_).

show3(Month):- db_chains(database1, Chain), chain_terms(database1, Chain, student, s(F, I, O, Day, Month, Year, _), _), 
write("�������: ", F), nl, write("���: ", I), nl, write("��������: ", O), nl, 
write("���� ��������: ", Day,".", Month, ".", Year), nl, nl, fail.
show3(_).

% �������� ������������� �����
control_open_file(FileAddress):- existfile(FileAddress).
control_open_file(FileAddress):- not(existfile(FileAddress)), nl, write("������. ���� ������ �� �������"), nl, menu.

% �������� ���� ������
view_database:- db_statistics(database1, CountTerms, _, _, _), nl, write("���������� ��������� ���� ������ - ", CountTerms), 
nl, nl, db_chains(database1, Chain), write(Chain), nl, chain_first(database1, Chain, Ref), view_database2(Ref).
view_database.

view_database2(Ref):- ref_term(database1, student, Ref, s(F, I, O, Day, Month, Year, _)), nl, 
write("�������: ", F), nl, write("���: ", I), nl, write("��������: ", O), nl, 
write("���� ��������: ", Day,".", Month, ".", Year), nl, nl, fail.
view_database2(Ref):- chain_next(database1, Ref, Next), view_database2(Next).

view_database3:- write("������� �������� �������"),readln(Chain), nl, chain_first(database1, Chain, Ref), view_database2(Ref).
view_database3.

add(0).
add(1):- nl, write("�������: "), readln(F), write("���: "), readln(I), write("��������: "), readln(O),  
write("���� ��������"), nl, write("����: "), readint(Day), write("�����: "), readint(Month), write("���: "), readint(Year), write("���: �/� "), readln(S), nl, nl,

write("������� "), readln(Chain), nl, chain_insertz(database1, Chain, student, s(F, I, O, Day, Month, Year, S), _), 
write("������ ������ 0 - ��� 1- ��"), nl, readint(Ask), add(Ask).

delete(0):-  write("���� ������ ������"), nl, menu.
delete(_):-  db_chains(database1, Chain), nl, write("�������: "), readln(F), nl, 
chain_terms(database1, Chain, student, s(F, _, _, _, _, _, _), Ref), term_delete(database1, Chain, Ref), fail.
delete(_).

letter:- write("������� ����� - "),readchar(Letter1),write(Letter1),nl,upper_lower(Letter1,Letter),db_chains(database1, Chain),
		     chain_terms(database1,Chain,student,s(F,_,_,_,_,_,_),_),NF = F,check(F,NF,Letter).
		     
		     
letter.  
rav(F,Ch,Let):- Ch=Let, write(F), nl, fail, menu.
rav(_,C,L):-C<>L.
check(_,NF,_):-str_len(NF,N),N<0, write("����� �� ����������� �� � ����� �� �������"),!, nl, fail, menu.	
check(F,NF,Letter):-str_len(NF,N),N>0,frontchar(NF,Char1,F1), upper_lower(Char1,Char),rav(F,Char,Letter), Char<>Letter, check(F,F1,Letter).



goal
res.
*/