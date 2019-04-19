#include <stdio.h>

/*
int main()
{
	printf("%Lf", 123.123L);
}
*/
/*
void	ft_putnumber(long long n)
{
	if (n > 9)
		ft_putnumber(n / 10);
	printf("%d", n % 10);
}

int main()
{
	float big = 681684351981656;

	printf("%f\n", big);

	ft_putnumber((long long)big);
}
*/
int main()
{
	char digit;
	long double pi = 0.924;

	printf("%Lf\n", pi);

	while (pi != (long long)pi)
	{
		digit = (long long)pi % 10;
		printf("%d", digit);
		pi -= digit;
		pi *= 10;
	}
	printf("%d", (int)pi % 10);
}
