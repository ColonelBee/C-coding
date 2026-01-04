#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*BMI check for lil bro!
compile this program first with gcc
then run this program with options -w followed by ur weight and -h followed by ur height.*/

int main(int argc, char *argv[]){
	fprintf(stdout, "BMI check for bro!!!\n");
	char *weight = "";
	char *height = "";
	float w, h;
	char check;
	while((check = getopt(argc, argv, "w:h:")) != EOF){
		switch(check){
			case 'w':
				weight = optarg;
				break;
			case 'h':
				height = optarg;
				break;
			default:
				fprintf(stderr, "No such option '%s'\n", optarg);
				return 1;
		}
	}
	// function calculating the exponential
	float expo(float a, float b){
		float tmp = a;
		for(int i = 1;i < b;i++) a *= tmp;
 		return a;
	}
	// the optarg we receive from the user is in the char type.
	// we need a function that converts this char to float (or double) numbers.
	float stof(const char *str){
    		float result = 0.0;
    		float fraction = 0.1;
    		int sign = 1;
    		int i = 0;
    		if (str[i] == '-') {
        		sign = -1;
        		i++;
    		}

    		// integer part
    		while (str[i] >= '0' && str[i] <= '9') {
        		result = result * 10.0 + (str[i] - '0');
        		i++;
    		}
    		// fractional part
    		if (str[i] == '.') {
        		i++;
        		while (str[i] >= '0' && str[i] <= '9') {
            			result += (str[i] - '0') * fraction;
            			fraction *= 0.1;
            			i++;
        		}
    		}
    		return sign * result;
	}
	// change the char optarg to float numbers.
	w = stof(weight);
	h = stof(height);
	float BMI = w/(h*h);
	if(BMI < 18.5) fprintf(stdout, "Ur skinny, eat more hamburgers!!!\nUr BMI = %f\n", BMI);
	else if((BMI >= 18.5) && (BMI <= 24.9)) fprintf(stdout, "Ur healthy, keep it up bro!\nUr BMI = %f\n", BMI);
	else if((BMI >= 25) && (BMI <= 29.9)) fprintf(stdout, "I think bro is overweight :(\nUr BMI = %f\n", BMI);
	else fprintf(stdout, "Lil bro is obese :D\nUr BMI = %f\n", BMI);
	return 0;
}
