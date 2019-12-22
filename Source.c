#include <signal.h>
#include <stdio.h>
#define	MAX	100

char	arithmetic_operation[10];
int	right[MAX];
int	left[MAX];
int	rights;
int	wrongs;
long	stvec;
long	etvec;
long	dtvec;

main(argc, argv)
char	*argv[];
{
	int range_of_numbers, k, count_of_aritmetic_operation, index_of_aritmetic_operation;
	char line[100];
	int answer, users_answer, first_number, second_number, summ;
	extern	delete();

	signal(SIGINT, delete);

	range_of_numbers = 11;
	count_of_aritmetic_operation = 0;
	while (argc > 1) {
		switch (*argv[1]) {
		case '+':
		case '-':
		case 'x':
		case '/':
			while (arithmetic_operation[count_of_aritmetic_operation] = argv[1][count_of_aritmetic_operation])
				count_of_aritmetic_operation++;
			break;

		default:
			range_of_numbers = getnum(argv[1]) + 1;
		}
		argv++;
		argc--;
	}
	if (range_of_numbers > MAX) {
		printf("Range is too large.\n");
		exit(0);
	}

	if (count_of_aritmetic_operation == 0) {
		arithmetic_operation[0] = '+';
		arithmetic_operation[1] = '-';
		count_of_aritmetic_operation = 2;
	}

	for (first_number = 0; first_number < range_of_numbers; first_number++) {
		left[first_number] = right[first_number] = first_number;
	}

	time(&stvec);
	k = stvec;
	srand(k);
	k = 0;
	index_of_aritmetic_operation = 0;
	goto start;

loop:
	if (++k % 2 == 0)
		score();

start:
	first_number = skrand(range_of_numbers);
	second_number = skrand(range_of_numbers);
	if (count_of_aritmetic_operation > 1)
		index_of_aritmetic_operation = random(count_of_aritmetic_operation);

	switch (arithmetic_operation[index_of_aritmetic_operation]) {
	case '+':
	default:
		answer = first_number + second_number;//left[first_number] + right[second_number];
		printf("%d + %d =   ", first_number, second_number);
		break;

	case '-':
		summ = first_number + second_number;
		answer = first_number;
		printf("%d - %d =   ", summ, second_number);
		break;

	case 'x':
		answer = first_number * second_number;
		printf("%d x %d =   ", first_number, second_number);
		break;

	case '/':
		while (right[second_number] == 0)
			second_number = random(range_of_numbers);
		summ = left[first_number] * right[second_number] + random(right[second_number]);
		answer = left[first_number];
		printf("%d / %d =   ", summ, right[second_number]);
		break;
	}


loop1:
	getline(line);
	dtvec += etvec - stvec;
	if (line[0] == '\n') goto loop1;
	users_answer = getnum(line);
	if (users_answer == answer) {
		printf("Right!\n");
		rights++;
		goto loop;
	}
	else {
		printf("What?\n");
		wrongs++;
		if (range_of_numbers >= MAX)	goto loop1;
		left[range_of_numbers] = left[first_number];
		right[range_of_numbers++] = right[second_number];
		goto loop1;
	}
}

getline(s)
char *s;
{
	register char	*rs;

	rs = s;

	while ((*rs = getchar()) == ' ');
	while (*rs != '\n')
		if (*rs == 0)
			exit(0);
		else if (rs >= &s[99]) {
			while ((*rs = getchar()) != '\n')
				if (*rs == '\0')	exit(0);
		}
		else
			*++rs = getchar();
	while (*--rs == ' ')
		*rs = '\n';
}

getnum(s)
char *s;
{
	int	a;
	char	c;

	a = 0;
	while ((c = *s++) >= '0' && c <= '9') {
		a = a * 10 + c - '0';
	}
	return(a);
}


random(range)
{
	return(rand() % range);
}

skrand(range) {
	int temp;
	temp = random(range) + random(range);
	if (temp > range - 1) temp = 2 * range - 1 - temp;
	return(temp);
}

score()
{
	time(&etvec);

	printf("\n\nRights %d; Wrongs %d; Score %d%%\n", rights, wrongs,
		(rights * 100) / (rights + wrongs));

	if (rights == 0)	return;
	printf("Total time %ld seconds; %.1f seconds per problem\n\n\n",
		etvec - stvec,
		(etvec - stvec) / (rights + 0.));

	//sleep(3);
	time(&dtvec);
	stvec += dtvec - etvec;
}

delete()
{
	if (rights + wrongs == 0.) {
		printf("\n");
		exit(0);
	}
	score();
	for (int i = 0; i < 1000000000; i++) {}
	exit(0);
}