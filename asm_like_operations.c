/*
Build a program that:
Reads a command as text
Chooses the correct function
Executes it
All using function pointers.
Example: 
Input: add 3 4
Output: 7
*/
#include <stdio.h>
#include <string.h>

/*addition, subtraction, multiplication, and division*/
float add(float a, float b){return a + b;}
float sub(float a, float b){return a - b;}
float mul(float a, float b){return a * b;}
float div(float a, float b){return a / b;}

// struct to check the commands
typedef struct{
	char *cmd;
	float (*fp)(float, float); // function pointer variable.
}command;

// convert string to float
float str_to_fl(char *s){
	float sign = 1.0;
	int i = 0;
	int cnt = 0; // variable to find the index of the dot.
	float sum = 0.0; // variable to turn the string to float.
	if(s[0] == '-') sign *= (-1);
	// find the dot position.
	while(s[i++] != '.') ++cnt;
	
	// process the right hand side of the dot.
	float a = 1;
	for(int k = cnt - 1; k >= 0; k--){
		if(s[k] >= '0' && s[k] <= '9'){
			float left = s[k] - 48;
			sum += (left*a);
			a *= 10;
		}
	}

	// process the left hand side of the dot.
	float b = 0.1;
	for(int h = cnt + 1; h < strlen(s); h++){
		float right = s[h] - 48;
		sum += (right*b);
		b *= 0.1;
	}
	
	// return the float number associated with its sign.
	return sign*sum;
}

// convert string to integer
int str_to_int(char *s){
	int sign = 1;
	if(s[0] == '-') sign *= (-1);
	int sum = 0;
	int m = 1;
	for(int i = strlen(s) - 1; i >= 0; i--){
		int cv = s[i] - 48;
		sum += (cv*m);
		m *= 10;
	}
	return sign*sum;
}

// the user may enter integers, check if they are integers are floats.
int check_char(char *s){
	int check_dot = 0;
	for(int i = 0; i < strlen(s); i++){
		if(s[i] == '.'){
			check_dot = 1; // detect float numbers.
			break;
		}
	}
	return check_dot;
}

int main(){
	command cd[] = {{"add", add}, {"sub", sub}, {"mul", mul}, {"div", div}};
	// user command input.
	fprintf(stdout, "Enter your command: ");
	// the user may enter float or integer numbers.
	char input[25];
	char comm[4]; // parse the command.
	char operand1[25]; // parse the 1st operand.
	char operand2[25]; // parse the 2nd operand.
	fgets(input, sizeof(input), stdin); // after this there is a newline \n and \0 at the end of the text.
	// parse the input, space doesn't matter.
	// parse the command, bypass the space.
	int index = 0;
	while(input[index] == ' '){index++;}
	int l = 0;
	while(input[index] != ' '){
		comm[l++] = input[index];
		index++;
	}
	comm[l] = '\0';

	// operand 1:
	// count the space after the command.
	while(input[index] == ' '){index++;}
	int k = 0;
	while(input[index] != ' '){
		operand1[k++] = input[index];
		index++;
	}
	// find the null-terminated index.
	operand1[k] = '\0';

	// operand 2 is the same process as operand 1
	while(input[index] == ' '){index++;}
	int h = 0;
	// note there is a newline signal at the end of the input string.
	while(input[index] != ' ' && input[index] != '\n'){
		operand2[h++] = input[index];
		index++;
	}
	operand2[h] = '\0';

	int check_num1 = check_char(operand1);
	int check_num2 = check_char(operand2);
	
	// 2 float numbers.
	if(check_num1 && check_num2){
		// when the user enters float numbers.
		float fl_op1 = str_to_fl(operand1);
		float fl_op2 = str_to_fl(operand2);
		float (*ptr)(float, float);
		for(int i = 0; i <= 3; i++){
			if(strstr(cd[i].cmd, comm)){
				ptr = cd[i].fp;
				fprintf(stdout, "The result is %.3f\n", ptr(fl_op1, fl_op2));
				break;
			}
		}
	}

	// 2 integer numbers.
	else if(!check_num1 && !check_num2){
		// when the user enters integer numbers.
		int int_op1 = str_to_int(operand1);
		int int_op2 = str_to_int(operand2);
		float (*ptr)(float, float);
		for(int i = 0; i <= 3; i++){
			if(strstr(cd[i].cmd, comm)){
				ptr = cd[i].fp;
				fprintf(stdout, "The result is %.3f\n", ptr(int_op1, int_op2));
				break;
			}
		}
	}

	// 1st num is float, the other one is integer
	else if(check_num1 && !check_num2){
		float fl_op1 = str_to_fl(operand1);
		int int_op2 = str_to_int(operand2);
		float (*ptr)(float, float);
		for(int i = 0; i <= 3; i++){
			if(strstr(cd[i].cmd, comm)){
				ptr = cd[i].fp;
				fprintf(stdout, "The result is %.3f\n", ptr(fl_op1, (float)int_op2));
				break;
			}
		}
	}

	// 1st num is integer, the other one is float
	else if(!check_num1 && check_num2){
		int int_op1 = str_to_int(operand1);
		float fl_op2 = str_to_fl(operand2);
		float (*ptr)(float, float);
		for(int i = 0; i <= 3; i++){
			if(strstr(cd[i].cmd, comm)){
				ptr = cd[i].fp;
				fprintf(stdout, "The result is %.3f\n", ptr((float)int_op1, fl_op2));
				break;
			}
		}
	}

	return 0;
}
