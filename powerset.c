#include <stdio.h>
#include <stdlib.h>

int target;
int size;
int *nums;

void print_subset(int subsize, int *subset)
{
	for (int i = 0; i < subsize; i++)
	{
		printf("%d", subset[i]);
		if (i < subsize - 1)
			printf(" ");
	}
	printf("\n");
}

int calc_subset_sum(int subsize, int *subset)
{
	int sum = 0;
	for (int i = 0; i < subsize; i++)
		sum += subset[i];
	return sum;
}

void solve(int subsize, int current_index, int *subset)
{
	if (current_index == size)
	{
		if (calc_subset_sum(subsize, subset) == target && subsize != 0)
			print_subset(subsize, subset);
		return ;
	}

	solve(subsize, current_index + 1, subset);

	subset[subsize] = nums[current_index];

	solve(subsize + 1, current_index + 1, subset);
}

int main(int ac, char **av)
{
	if (ac <= 2)
	{
		printf("\n");
		return (0);
	}
	target = atoi(av[1]);
	size = ac - 2;
	nums = malloc(sizeof(int) * size);
	if (!nums)
		return (1);
	int *subset = calloc(size, sizeof(int));
	if (!subset)
	{
		free(nums);
		return (1);
	}
	for (int i = 0; i < size; i++)
		nums[i] = atoi(av[i + 2]);
	int subsize = 0;
	int current_index = 0;
	solve(subsize, current_index, subset);
	free(nums);
	free(subset);
}
