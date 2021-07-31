#include "../includes/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	char			*temp;
	unsigned int	i;

	if (!s2)
		return (NULL);
	temp = (char *)s1;
	i = 0;
	result = malloc(sizeof(int) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (*s1)
		result[i++] = (char)*s1++;
	while (*s2)
		result[i++] = (char)*s2++;
	result[i] = '\0';
	free(temp);
	return (result);
}

char	*get_number(unsigned long timestamp)
{
	char			*timeline;
	unsigned long 	temp;
	size_t 			length;

	temp = timestamp;
	length = 0;
	if (temp == 0)
		length++;
	while (temp != 0 && ++length)
		temp /= 10;
	timeline = malloc(sizeof(char) * length + 2);
	if (!timeline)
		return (NULL);
	timeline[length + 1] = '\0';
	timeline[length] = ' ';
	if (timestamp == 0)
		timeline[0] = '0';
	while (timestamp > 0)
	{
		timeline[--length] = (char)(timestamp % 10 + '0');
		timestamp /= 10;
	}
	return (&timeline[0]);
}

void	put_message(unsigned int id, char *message, t_process	*table, char *color)
{
	char			*status;
	char			*number;
	unsigned int	length;
	unsigned int	i;

	pthread_mutex_lock(&table->message);
	i = -1;
	length = 0;
	usleep(10);
	status = get_number(current_time() - table->start_time);
//	if (!status)
//		return (NULL);
	status = ft_strjoin(status, get_number(id));
	status = ft_strjoin(status, message);
	write(1, status, ft_strlen(status));
	free(status);
//	printf("%s%lu  %u  %s\033[0m\n", color, current_time() - table->start_time, id, message);
//	printf("%lu %u %s\n", current_time() - table->start_time, id, message);
	if (!table->is_somebody_dead)
		pthread_mutex_unlock(&table->message);
}