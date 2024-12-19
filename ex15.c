#include <stdio.h>

int main(void)
{
	// Crate two arrays we care about
	int ages[] = { 23, 43, 12, 89, 2 };
	char *names[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};

	// Safely get the sizeof ages 
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	// First way using indexing
	for (i = 0; i < count; i ++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}

	printf("---\n");

	// Set up the pointers to the start of the arrays
	int *cur_age = ages;
	char **cur_name = names;

	// Second way using pointers
	for (i = 0; i < count; i++) {
		printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
	}

	printf("---\n");

	// Third way pointers are just arrays
	for (i = 0; i < count; i++) {
		printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
	}

	return 0;
}

