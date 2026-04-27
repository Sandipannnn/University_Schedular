#include <stdio.h>
#include <string.h>

#define MAX_COURSES 20
#define MAX_ROOMS 10
#define DAYS 5
#define SLOTS 6

struct Course {
    int id;
    char name[50];
    char faculty[50];
    int hours;
};

struct Room {
    int id;
    char name[30];
};

struct Assignment {
    int day;
    int slot;
    int room;
};

struct Course courses[MAX_COURSES];
struct Room rooms[MAX_ROOMS];
struct Assignment timetable[MAX_COURSES][10];

int facultyAvailable[MAX_COURSES][DAYS][SLOTS];
int facultyBusy[DAYS][SLOTS][MAX_COURSES];
int roomBusy[DAYS][SLOTS][MAX_ROOMS];

int numCourses = 0;
int numRooms = 0;

/* ---------- SYSTEM INITIALIZATION ---------- */
void initializeBackend() {
    for(int c=0; c<MAX_COURSES; c++) {
        for(int d=0; d<DAYS; d++) {
            for(int s=0; s<SLOTS; s++) {
                facultyAvailable[c][d][s] = 1;
            }
        }
    }
    memset(facultyBusy, 0, sizeof(facultyBusy));
    memset(roomBusy, 0, sizeof(roomBusy));
}

/* ---------- FILE STORAGE ---------- */
void loadCourses() {
    FILE *fp = fopen("courses.txt","r");
    if(fp==NULL) return;

    numCourses = 0;
    while(fscanf(fp,"%d %s %s %d",
        &courses[numCourses].id,
        courses[numCourses].name,
        courses[numCourses].faculty,
        &courses[numCourses].hours) != EOF) {

        numCourses++;
    }
    fclose(fp);
}

void loadRooms() {
    FILE *fp = fopen("rooms.txt","r");
    if(fp==NULL) return;

    numRooms = 0;
    while(fscanf(fp,"%d %s",
        &rooms[numRooms].id,
        rooms[numRooms].name) != EOF) {

        numRooms++;
    }
    fclose(fp);
}

/* ---------- CONSTRAINT CHECK ---------- */
int isSafe(int course, int day, int slot, int room) {

    if(roomBusy[day][slot][room])
        return 0;

    if(facultyAvailable[course][day][slot] == 0)
        return 0;

    for(int i=0; i<numCourses; i++) {
        if(facultyBusy[day][slot][i] &&
           strcmp(courses[i].faculty, courses[course].faculty)==0) {
            return 0;
        }
    }

    return 1;
}

/* ---------- BACKTRACKING ENGINE ---------- */
int generateTimetable(int course, int hour) {

    if(course == numCourses)
        return 1;

    if(hour == courses[course].hours)
        return generateTimetable(course+1, 0);

    for(int d=0; d<DAYS; d++) {
        for(int s=0; s<SLOTS; s++) {
            for(int r=0; r<numRooms; r++) {

                if(isSafe(course, d, s, r)) {

                    timetable[course][hour].day = d;
                    timetable[course][hour].slot = s;
                    timetable[course][hour].room = r;

                    roomBusy[d][s][r] = 1;
                    facultyBusy[d][s][course] = 1;

                    if(generateTimetable(course, hour+1))
                        return 1;

                    // Backtrack
                    roomBusy[d][s][r] = 0;
                    facultyBusy[d][s][course] = 0;
                }
            }
        }
    }
    return 0;
}

/* ---------- SAVE TIMETABLE ---------- */
void saveTimetable() {
    FILE *fp = fopen("timetable.txt","w");
    if (fp == NULL) return;

    char *days[]={"Mon","Tue","Wed","Thu","Fri"};

    for(int d=0; d<DAYS; d++) {
        fprintf(fp,"\n%s\n",days[d]);

        for(int s=0; s<SLOTS; s++) {
            fprintf(fp,"Slot %d: ",s+1);

            for(int c=0; c<numCourses; c++) {
                for(int h=0; h<courses[c].hours; h++) {
                    if(timetable[c][h].day==d &&
                       timetable[c][h].slot==s) {

                        fprintf(fp,"%s(%s) Room:%s  ",
                            courses[c].name,
                            courses[c].faculty,
                            rooms[timetable[c][h].room].name);
                    }
                }
            }
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
}

