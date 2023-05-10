

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_GRADE = 100, PASS_GRADE = 55 };


int find_median(int arr[], int n);
int find_extreme(int arr[], int op);
double find_pass_rate(int arr[], int n);

/**
 * @brief Application's main entry point
 * @param argc Number of arguments
 * @param argv Pointer to arguments
 * @return Non-zero value in case of an error
 */
int main(int argc, char *argv[]) {

	if(argc < 1) {
		 fprintf(stderr, "Error\n");
		 return 1;
 		}


	FILE *fd, *fp;

	/*cursor of new file*/
	fd = fopen(argv[1], "w");
	/*cursor of grades file*/
	fp = fopen(argv[2], "r");
	/* if did not open file successfully */
	if ((fd == NULL) || (fp == NULL)) {
		return -1;
	}

	char cur_char;
	int students_num = 0;


	/* count number of students_num */
	for(cur_char = getc(fp); cur_char != EOF; cur_char = getc(fp)) {
		if(cur_char == '\n') {
			students_num++;
		}
	}

	fprintf(fd, "num of students = %d\n", students_num);

	int histogram[MAX_GRADE] = {0};

	int sum;
	int num;
	/* return cursor to beginning of file */
	fseek(fp, 0, SEEK_SET);

	/* calculate sum of grades */
	/* create array of grade for later use  */
	/* create histogram */
	for (int i = 0; i < students_num; i++) {

		/* if did not scan successfully */
		if(!fscanf(fp, "%d", &num)){
				return -1;
		}
		//printf("%d", num);
		histogram[num-1]++;
		sum += num;
	}

	fprintf(fd, "avg = %.3f\n", ((double)sum/students_num));



	int median = find_median(histogram, students_num);
	int mini = find_extreme(histogram, 0);
	int maxi = find_extreme(histogram, 1);
	double passing_rate = find_pass_rate(histogram, students_num);

	fprintf(fd, "the median is - %d\n", median);
	fprintf(fd, "max grade = %d, min grade = %d\n", maxi, mini);
	fprintf(fd, "pass rate = %.2f%%\n", passing_rate);

	for(int i = 0; i < MAX_GRADE; i++){

		if((i != 0) && ((i+1)%10 == 0)){
			fprintf(fd, "%d\n",histogram[i]);
		}
		else {
			fprintf(fd, "%d ",histogram[i]);
		}
	}

	fclose(fd);
	fclose(fp);

	return 0;
}


/**
 * @brief find median of grades
 * @param arr[] is histogram of grades
 * @param n is number of students
 * @return index that is the median grade
 */
int find_median(int arr[], int n){
	int med = (n+1)/2;
	int count = 0;
	int i;

	for(i = 0; count <= med; i++) {
		count += arr[i];
	}
	return i;
}

/**
 * @brief Find min/max grade
 * @param arr[] is the histogram of grades
 * @param op is the type of extreme needed: 0=min, 1=max
 * @return value of extreme grade
 */
int find_extreme(int arr[], int op){

	/*find minimum*/
	if (!op) {
		for(int i = 0; ((i < MAX_GRADE)); i++) {
			if (arr[i] != 0) {
				return i+1;
			}
		}
	}

	/*find maximum*/
	for(int i = (MAX_GRADE - 1); (i >= 0); i--){
		if (arr[i] != 0){
			return i+1;
		}
	}
	/*return -1 if the list of grades is empty*/
	return -1;
}

/**
 * @brief Finds pass rate of students
 * @param arr[] is the histogram of grade
 * @param n is the number of students
 * @return pass rate value
 */
double find_pass_rate(int arr[], int n) {

	int pass_num = 0;

	for(int i = PASS_GRADE - 1; i < MAX_GRADE; i++) {
		pass_num += arr[i];
	}

	return (((double)pass_num / n)*MAX_GRADE);

}
