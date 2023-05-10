
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "grades.h"
#include "linked-list.h"

typedef int(*element_compare)(void *element, void *param);

/* the grades struct here*/
struct grades{
	struct list *students_list;
};

/*student struct here*/
/*the grades list will have these as elements*/
struct student_node {
		int student_id;
		char *student_name;
		struct list *courses;
};

/*course struct here*/
/*the courses list in the student struct have these as elements*/
struct course_node {
	char *course_name;
	int course_grade;
};

enum { MAX_GRADE = 100 };


/*declare about functions*/
static int student_clone_func(void *element, void **output);
static void student_destroy_func(void *element);
static int course_clone_func(void *element, void **output);
static void course_destroy(void *element);


/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, or NULL in case of an error
 */
struct grades* grades_init(){
	/*initialize grades struct*/
	struct grades *grades_ptr;

	grades_ptr = (struct grades*)malloc(sizeof(struct grades));

	if(!grades_ptr){
		return NULL;
	}

	/*initialize students_list field*/
	struct list* students_ptr = list_init(student_clone_func,
										  student_destroy_func);

	if(!students_ptr){
		return NULL;
	}

	grades_ptr->students_list = students_ptr;
	return grades_ptr;
}

/**
 * @brief Creates new student with "id", "name" and pointer to courses list
 * @return pointer to new student on success else NULL
 * @note Fails if out of memory
 */
static struct student_node* create_new_student(const char *name, int id){

	struct student_node *student;

	student = (struct student_node*)malloc(sizeof(struct student_node));

	if(!student){
		return NULL;
	}

	student->student_name = (char*)malloc((strlen(name)+1)*sizeof(char));

	if(!(student->student_name)){
		/*out of memory - must free what was allocated*/
		free(student);
		return NULL;
	}

	student->student_id=id;
	strcpy(student->student_name, name);

	/*add pointer to list*/
	struct list* courses_ptr = list_init(course_clone_func,course_destroy);

	if(!courses_ptr){
		return NULL;
	}

	student->courses=courses_ptr;

	return student;
}

/**
 * @brief finds node with the same parameter as requested in list
 * @return cursor to node with a match on success else NULL
 */
static struct iterator* find_node(struct list *list,
								  void *param,
								  element_compare compare_func){

	struct iterator *cursor = list_begin(list);

	/*check if student already exists*/
	while(cursor){

		int is_equal = compare_func(list_get(cursor), param);
		if(is_equal){
			break;
		}
		cursor = list_next(cursor);
	}

	return cursor;

}

/**
 * @brief clones “course_element” to “*output”.
 * @returns 0 on success.
 */
static int course_clone_func(void *element, void **output){
	/*create a clone*/
	struct course_node *element_clone;
	element_clone = (struct course_node*)malloc(sizeof(struct course_node));

	if(!element_clone){
			return 1;
		}

	element_clone->course_name = (char*)malloc((strlen(
			((struct course_node*)element)->course_name)+1)*sizeof(char));

	if(!(element_clone->course_name)){
		/*out of memory - must free what was allocated*/
		free(element_clone);
		return 1;
	}

	/*copy fields to clone*/
	element_clone->course_grade = ((struct course_node*)element)->course_grade;
	strcpy(element_clone->course_name,
			((struct course_node*)element)->course_name);

	*output = element_clone;
	return 0;
}

/**
 * @brief clones “student_element” to “*output”. Returns 0 on success.
 */
static int student_clone_func(void *element, void **output){
	/*create a clone*/
	struct student_node *element_clone;
	element_clone = (struct student_node*)malloc(sizeof(struct student_node));

	if(!element_clone){
		/*out of memory - must free what was allocated*/
		return 1;
	}
	element_clone->student_name = (char*)malloc((strlen((
			(struct student_node*)element)->student_name)+1)*sizeof(char));

	if(!(element_clone->student_name)){
		/*out of memory - must free what was allocated*/
		free(element_clone);
		return 1;
	}
	/*copy fields to clone*/
	strcpy(element_clone->student_name,
		   ((struct student_node*)element)->student_name);
	element_clone->student_id = ((struct student_node*)element)->student_id;

	/*clone courses_list*/
	/*add pointer to list*/
	struct list* courses_ptr = list_init(course_clone_func,course_destroy);

	if(!courses_ptr){
		/*out of memory - must free what was allocated*/
		return 1;
	}

	struct list *original_list = ((struct student_node*)element)->courses;

	int list_length = list_size(original_list);
	struct iterator *cursor = list_begin(original_list);
	struct iterator *new_cursor = list_begin(courses_ptr);


	for(int i=0; i<list_length; i++,list_next(cursor),list_next(new_cursor)){
		struct course_node* clone_course;

		course_clone_func(list_get(cursor), (void**)(&clone_course));
		list_insert(courses_ptr, new_cursor, clone_course);
	}

	element_clone->courses = courses_ptr;

	*output = element_clone;
	return 0;
}
/**
 * @brief Destroys "course_node", de-allocate all memory!
 */
static void course_destroy(void *element){
	if(!element){
			return;
	}

	free(((struct course_node*) element)->course_name);
	free(((struct course_node*) element));
	return;
}

/**
 * @brief Destroys "student_node", de-allocate all memory!
 */
static void student_destroy_func(void* element){
	if(!element){
		return;
	}

	/*destroy list of courses and fields*/
	list_destroy(((struct student_node*) element)->courses);
	free(((struct student_node*) element)->student_name);
	free((struct student_node*) element);
}

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
	if(!grades){
		return;
	}

	/*destroy list of students*/
	list_destroy(grades->students_list);
	free(grades);
}
/**
 * @brief compare student's ID with wanted id
 * @return 1 if a match else 0
 */
static int student_compare(void* curr_student, void *id){

	if(((struct student_node*)curr_student)->student_id == *(int*)id){
		return 1;
	}
	return 0;
}

/**
 * @brief compare course's name with wanted name
 * @return 1 if a match else 0
 */
static int course_compare(void *curr_course, void *name){

	if(!strcmp((((struct course_node*)curr_course)->course_name),(char*)name)){
		return 1;
	}
	return 0;
}

/**
 * @brief Creates new course with "grade", "name"
 * @return pointer to new course on success else NULL
 * @note Fails if out of memory
 */
static struct course_node* create_new_course(const char *name, int grade){
	struct course_node *course;

	course = (struct course_node*)malloc(sizeof(struct course_node));

	if(!course){
		/*out of memory - must free what was allocated*/
		return NULL;
	}

	course->course_name = (char*)malloc((strlen(name)+1)*sizeof(char));

	if(!(course->course_name)){
		/*out of memory - must free what was allocated*/
		free(course);
		return NULL;
	}

	course->course_grade=grade;
	strcpy(course->course_name, name);

	return course;
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
	/*check if grades is valid*/
	if(grades==NULL){
		return 1;
	}

	/*check if student already exists*/
	if(find_node(grades->students_list, &id, student_compare)){
		return 1;
	}

	/*create new student*/
	struct student_node *new_student = create_new_student(name,id);

	if(!new_student){
		/*out of memory - must free what was allocated*/
		return 1;
	}

	/*add new student to list*/
	if(list_push_back(grades->students_list, new_student)){
		/*list_push puts a clone in list - free original*/
		student_destroy_func(new_student);
		return 1;
	}
	/*list_push puts a clone in list - free original*/
	student_destroy_func(new_student);
	return 0;

}

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

	/*check if grades is valid*/
	if(grades == NULL) {
		return 1;
	}

	/*check if grade is valid*/
	if(!((grade >= 0) && (grade <= MAX_GRADE))) {
		return 1;
	}

	struct iterator *cursor = find_node(grades->students_list,
										&id,
										student_compare);

	/*check if student exists*/
	struct student_node *current_student =
			(struct student_node*)list_get(cursor);

	/*if cursor didn't find student*/
	if(!current_student){
		return 1;
	}

	/*check if course already exist for current student*/
	if(find_node(current_student->courses,(void*)name,course_compare)){
		return 1;
	}

	/*if not add course and grade*/
	/*create new course*/
	struct course_node *new_course = create_new_course(name,grade);

	/*add new course to course list*/
	if(list_push_back(current_student->courses, new_course)){
		/*list_push puts a clone in list - free original*/
		course_destroy(new_course);
		return 1;
	}
	/*list_push puts a clone in list - free original*/
	course_destroy(new_course);
	return 0;
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
	/*check if grades is valid*/
	if(grades == NULL) {
		return 1;
	}

	struct iterator *students_cursor = list_begin(grades->students_list);

	/*check if grades is valid*/
	if(students_cursor == NULL) {
		return 1;
	}

	/*check if student exists*/
	students_cursor = find_node(grades->students_list, &id, student_compare);

	/*if cursor didn't find student*/
	if(!students_cursor){
		return 1;
	}

	/*go through all the courses and print grades*/
	struct student_node *current_student =
			(struct student_node*)list_get(students_cursor);
	struct course_node *current_course;
	struct iterator *courses_cursor = list_begin(current_student->courses);

	printf("%s %d:",current_student->student_name, current_student->student_id);
	int is_first_grade = 1;
	while(courses_cursor){
		current_course = (struct course_node*)list_get(courses_cursor);
		/*print current course*/
		if(!is_first_grade){
			printf(",");
		}
		printf(" %s %d",current_course->course_name,
				current_course->course_grade);
		is_first_grade = 0;
		courses_cursor = list_next(courses_cursor);
	}
	printf("\n");

	/*return success*/
	return 0;
}


/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){
	/*check if grades is valid*/
	if(grades == NULL) {
		return 1;
	}

	struct iterator *students_cursor = list_begin(grades->students_list);

	/*check if grades is valid*/
	if(students_cursor == NULL) {
		return 1;
	}

	struct student_node  *current_student; 

	/*go through all the students*/
	while(students_cursor){
		current_student = ((struct student_node*) list_get(students_cursor));
		grades_print_student(grades,current_student->student_id);
		students_cursor = list_next(students_cursor);
	}

	/*return success*/
	return 0;
}


/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average i/s 0.
 * @note On error, sets "*out" to NULL.
 * @note "out" is a pointer to char*. Meaning, your function should
 * allocate memory on the heap and set "*out" to point on that memory.
 * This methodology (of returning values via pointers) is very common in C.
 * An example of C method that returns a value via pointer:
 * void foo(int *out) {
 *   *out = 1;  
 * }
 */
float grades_calc_avg(struct grades *grades, int id, char **out){

	/*check if grades is valid*/
	if(grades == NULL) {
		*out = NULL;
		return -1;
	}

	/*check if student exists*/
	struct iterator *current_students_cursor = find_node(grades->students_list,
														 &id,
														 student_compare);

	/*if cursor didn't find student*/
	if(current_students_cursor == NULL) {
		*out = NULL;
		return -1;
	}

	struct student_node *current_student =
			((struct student_node*) list_get(current_students_cursor));

	/*allocating *out */
	*out = (char*)malloc((strlen(current_student->student_name)+1)
			*sizeof(char));

	strcpy(*out, current_student->student_name);

	float grades_sum=0;
	struct course_node  *current_course;

	/*go through all the courses and add grades*/
	struct iterator *courses_cursor = list_begin(current_student->courses);
	if(!courses_cursor){
		return 0;
	}

	while(courses_cursor){
		current_course = ((struct course_node*) list_get(courses_cursor));
		grades_sum += (current_course->course_grade);
		courses_cursor = list_next(courses_cursor);
	}
	
	/*calculate average*/
	float average = grades_sum/(list_size(current_student->courses));
	return average;
}


