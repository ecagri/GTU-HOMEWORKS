:- dynamic student/3.
:- dynamic instructor/3.
:- dynamic course/6.
:- dynamic room/5.

/* Courses */
course(cse341, yakup, 120, 14, 16, [cagri, ali]).
course(cse101, mehmet, 60, 9, 11, [murat, merve, fatih]).
course(cse102, alp, 100, 10, 12, [ayse, dogukan, yusuf, melih]).

/* Students */

student(cagri, [cse341], no).
student(ali, [cse341], no).
student(murat, [cse101], no).
student(merve, [cse101], yes).
student(fatih, [cse101], no).
student(ayse, [cse102], no).
student(dogukan, [cse102], no).
student(yusuf, [cse102], no).
student(melih, [cse102], no).
student(begum, [], no).
student(mustafa, [], yes).
student(burak, [], no).

/* Instructors */

instructor(yakup, [cse341], projector).
instructor(mehmet, [cse101], no-need).
instructor(alp, [cse102], smartboard).
instructor(didem, [], smartboard).
instructor(oya, [], no-need).

/* Rooms */

room(z23, 150, [], projector, no).
room(z10, 80, [], smartboard, yes).
room(z06, 100, [], projector, yes).
room(z11, 110, [], smartboard, no).

/* Adds new fact for Student. */
createStudent :- askID(ID), askHandicapped(Handicapped), assert(student(ID, [], Handicapped)).

/* Adds new fact for Instructor. */
createInstructor :- askID(ID), askNeeds(SpecialNeeds), assert(instructor(ID, [], SpecialNeeds)).

/* Adds new fact for Room. */
createRoom :- askID(ID), askCapacity(Capacity), askNeeds(SpecialNeeds), askHandicapped(Handicapped), assert(room(ID, Capacity, [], SpecialNeeds, Handicapped)).

/* Adds new fact for Course. */
createCourse :- askID(ID), askInstructor(Instructor), askCapacity(Capacity), askStart(Start), askEnd(End), instructor(Instructor, _, _) ->
             (assert(course(ID, Instructor, Capacity, Start, End, [])), retract(instructor(Instructor, Courses, SpecialNeeds)), assert(instructor(Instructor, [ID | Courses], SpecialNeeds))); writeln("The instructor could not found in the system!"), menu.

/* Ask ID. */
askID(ID) :- write("Enter The Id: "),
             read(UID),
             not((student(UID, _, _); instructor(UID, _, _); course(UID, _, _, _, _, _); room(UID, _, _, _, _))) -> ID = UID; /* If there is no instance of same id, assign it.  */
             /* If there is any instance of same id, print an error, and ask it again. */
             writeln("The ID Must Be Unique!"),
             askID(ID).

/* Ask whether the student is handicapped or room is proper access for handicapped students */
askHandicapped(Handicapped) :- writeln("1) Handicapped"),
                               writeln("2) No Speciality"),
                               write("Your Prefer: "),
                               read(Prefer),
                               (
                               (Prefer =:= 1 -> Handicapped = yes); /* If the prefer is 1, handicapped is yes. */
                               (Prefer =:= 2 -> Handicapped = no); /* If the prefer is 2, handicapped is no. */
                               (writeln("Unknown Prefer!"), askHandicapped(Handicapped))). /* If the prefer is neither 1 nor 2, print an error, and ask it again. */
                               
/* Ask instructor preferences(projector, smartboard, no-need), or room equipments. */
askNeeds(SpecialNeeds) :- writeln("1) Projector"),
                          writeln("2) Smart Board"),
                          writeln("3) No Speciality"),
                          write("Your Prefer: "),
                          read(Prefer),
                          (
                          (Prefer =:= 1 -> SpecialNeeds = projector); /* If the prefer is 1, SpecialNeeds is projector. */
                          (Prefer =:= 2 -> SpecialNeeds = smartboard); /* If the prefer is 2, SpecialNeeds is smartboard. */
                          (Prefer =:= 3 -> SpecialNeeds = no-need); /* If the prefer is 3, SpecialNeeds is no-need. */
                          (writeln("Unknown Prefer!"), askNeeds(SpecialNeeds))).  /* If the prefer is neither 1,2 nor 3, print an error, and ask it again. */
                          
/* Ask the instructor of the course. */
askInstructor(Instructor) :- write("Enter The Instructor ID: "),
                             read(Instructor).
                             
/* Ask capacity of the course or room. */
askCapacity(Capacity) :- write("Enter The Capacity: "),
                         read(Capacity).
                         
/* Ask start hour of the course. */
askStart(Start) :- write("Enter The Start Hour(Without Any Minute Info, Example; 5, 13): "),
                   read(Start).
                   
/* Ask end hour of the course. */
askEnd(End) :- write("Enter The End Hour(Without Any Minute Info, Example; 5, 13): "),
                   read(End).

menu :- writeln("0) Create Student"),
        writeln("1) Create Instructor"),
        writeln("2) Create Course"),
        writeln("3) Create Room"),
        writeln("4) Student Menu"),
        writeln("5) Course Menu"),
        writeln("6) Print Proper Class-Room Pairs"),
        writeln("7) Print Proper Rooms For Specific Class"),
        writeln("8) Check Student-Class Pair Proper"),
        writeln("9) Print Proper Classes For Specific Student"),
        writeln("-1) Quit"),
        write("Enter Your Option: "),
        read(Option),
        (
        (Option =:= 0, createStudent);
        (Option =:= 1, createInstructor);
        (Option =:= 2, createCourse);
        (Option =:= 3, createRoom);
        (Option =:= 4, studentMenu);
        (Option =:= 5, courseMenu);
        (Option =:= 6, classRoomPairs);
        (Option =:= 7, properRooms);
        (Option =:= 8, studentCoursePair);
        (Option =:= 9, properCourses)),
        (Option =\= -1, menu). /* If the option is not quit, print menu again. */

/* Assign a student with a course. */
studentMenu :-     write("Enter Student ID: "), read(ID), /* Get id of the student. */
                   write("Enter Course ID: "),read(CourseID), /* Get id of the course. */
                   (student(ID, Courses, Handicapped), course(CourseID, InstructorID, Capacity, Start, End, Students)) -> /* If there is such student and class with these IDs, check properness. */
                   (courseProper(ID, CourseID) ->  /* If student and course proper, update student and course facts with new informations. */
                   (retract(student(ID, Courses, Handicapped)),
                   retract(course(CourseID, InstructorID, Capacity, Start, End, Students)),
                   assert(student(ID, [CourseID | Courses], Handicapped)),
                   assert(course(CourseID, InstructorID, Capacity, Start, End, [ID | Students])),
                   writeln("Student Is Registered To The Course Succesfully."));
                   writeln("Course Is Not Proper For Student.")); /* If course is not proper for student, print an error. */
                   writeln("Student Or Course Could Not Found").  /* If student or course couldnt found, print an error. */

/* Assign a course with a room. */
courseMenu :-  write("Enter Course ID: "), read(ID), /* Get id of the course. */
               write("Enter Room ID: "), read(RoomID), /* Get id of the room. */
               (course(ID, _, _, _, _, _), room(RoomID, RCapacity, RCourses, RSpecialNeeds, RHandicapped)) -> /* If there is such course and room with these IDs, check properness. */
               (roomProper(ID, RoomID) -> /* If course and room proper, update room fact with new informations. */
               (retract(room(RoomID, RCapacity, RCourses, RSpecialNeeds, RHandicapped)),
               assert(room(RoomID, RCapacity, [ID | RCourses], RSpecialNeeds, RHandicapped)),
               writeln("Course Is Registered To The Room Succesfully."));
               writeln("Room Is Not Proper For Course.")); /* If room is not proper for course, print an error. */
               writeln("Room or Course Could Not Found").  /* If course or room couldnt found, print an error. */
               
/* For all course and room pairs, check properness of it, if it is proper, print it. */
classRoomPairs :-
                  forall(course(CourseID, _, _, _, _, _),forall(room(RoomID, _, _, _, _), (roomProper(CourseID, RoomID)  -> (write(CourseID), write(-), writeln(RoomID)); true))).
                  
/* Gets an course id and check properness of it with all rooms, if there is any proper room, print it. */
properRooms :- write("Course ID: "),
               read(CourseID), /* Gets id of the course. */
               course(CourseID, _, _, _, _, _) -> forall(room(RoomID, _, _, _, _), (roomProper(CourseID, RoomID) -> (write(CourseID), write(-), writeln(RoomID)); true));
               writeln("The Course Could Not Found!"). /* If the course couldnt found, print an error. */

/* Gets an student and course id and check properness of it, if it is proper, print it. */
studentCoursePair :-
                 write("Student ID: "),
                 read(StudentID), /* Gets id of the student. */
                 write("Course ID: "),
                 read(CourseID), /* Gets id of the course. */
                 (student(StudentID, _, _), course(CourseID, _, _, _, _, _)) -> (courseProper(StudentID, CourseID) -> writeln("Course Is Proper For Student."); writeln("Couse Is Not Proper For Student."));
                 writeln("Student Or Course Could Not Found"). /* If the student or course couldnt found, print an error. */

/* Check properness of course and room. */
roomProper(CourseID, RoomID) :-
              course(CourseID, InstructorID, CourseCapacity, CourseStart, CourseEnd, CourseStudents),
              room(RoomID, RoomCapacity, Courses, SpecialEquipment, Handicapped),
              \+member(CourseID, Courses), /* If course is not in the course list of the room, continue. */
              CourseCapacity =< RoomCapacity,/* If the capacity of the room is bigger than or equal to capacity of the course, continue. */
              instructor(InstructorID, _, SpecialNeeds),
              (SpecialNeeds \== no-need -> SpecialEquipment == SpecialNeeds; /* If the special needs of instructor matches with special equipment of the class, continue. */
              true),
              (student(StudentID, _, yes), member(StudentID, CourseStudents) -> Handicapped == yes; /* If any student of the course is handicapped, class must be available for handicapped students. */
              true),
              forall(member(Course, Courses), not((course(Course, _, _, Start, End, _), ((Start =< CourseStart, CourseStart < End); (Start < CourseEnd, CourseEnd =< End))))). /* There must be no time crash with courses. */

/* Gets an student id and check properness of it with all courses, if there is any proper course, print it. */
properCourses :- write("Student ID: "),
                 read(StudentID), /* Gets id of the student. */
                 student(StudentID, _, _) -> forall(course(CourseID, _, _, _, _, _), (courseProper(StudentID, CourseID) -> (write(StudentID), write(-), writeln(CourseID)); true));
                 writeln("The Student Could Not Found!"). /* If the course couldnt found, print an error. */

/* Check properness of course and room. */
courseProper(StudentID, CourseID) :-
                        student(StudentID, Courses, Handicapped),
                        \+member(CourseID, Courses), /* If student is not registered to the course before, continue. */
                        course(CourseID, _, CourseCapacity, _, _, CourseStudents),
                        len(CourseStudents, Length), /* Gets the how many students gets the course. */
                        Length < CourseCapacity, /* If the number of students who gets the course is less than course capacity, continue. */
                        forall(room(_, _, RCourses, _, no), (member(CourseID, RCourses) -> (Handicapped == no); true)). /* If the course will be in room which does not have special access for handicapped students, student shouldn't be handicapped to take the course. */
len([],0).
len([_|Tail],N) :- len(Tail,N2), N is N2 + 1.
