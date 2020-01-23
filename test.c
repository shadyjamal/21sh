/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 07:34:55 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/20 07:49:20 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void empty(int sig)
{
    (void)sig;
    write(0, "ko\n",3);
}

int main()
{
    char str[100] = {0};
    signal(2, empty);
    read(0,str,99);
    printf("%s\n",str);
    write(1,"ok\n",3);
}