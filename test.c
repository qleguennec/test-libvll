/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:27:50 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/28 13:35:57 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvll/libvll.h"
#include "libprintf/libprintf.h"
#include <string.h>
#include <stdio.h>

#define IMPORT(s) 		strcpy(a, s); b = a; l = vll_import(&b, "[],'", 0);
#define EXPORT(l, v)	vll_export(l, &v, VLL_DEF_DELIM, VLL_EXPORT_DELIM | VLL_EXPORT_STR);
#define PRINT(l)		printf("%lu\t", l->size); fflush(stdout); vll_print(1, l, VLL_PRINT_NL);
#define TEST_START(s)	vect_init(&v); ok = 0; tests = 0; printf("\ntest_%s\n", s);
#define TEST_RESULT		printf("OK: %d/%d\n", ok, tests);

#define TEST_IMP_EXP(s) tests++; \
	IMPORT(s); \
	EXPORT(l, v); \
	if (!strcmp(v.data, s)) \
		{ok++; vll_free(l);} \
	else \
		{printf("fail on %s\n", s); PRINT(l); l1 = vll_fmap(l, &_vllsize); PRINT(l1);} \
	v.used = 0;

#define TEST_SIZE(s, k) tests++; \
	IMPORT(s); \
	if (l->size == k) \
		{ok++; vll_free(l);} \
	else \
		{printf("fail on %s\n", s); PRINT(l); l1 = vll_fmap(l, &_vllsize); PRINT(l1);} \

t_vll		*_vllsize(t_vll *l)
{
	t_vll	*new;
	t_vect	*v;
	size_t	size;

	new = vll_new();
	size = vll_size(l);
	v = vect_new(NULL, 0);
	vect_fmt(v, "size = %lu", size);
	vll_data_add(new, v);
	return (new);
}

void		test_imp_exp(void)
{
	t_vll	*l;
	t_vll	*l1;
	t_vect	v;
	char	a[1024];
	char	*b;
	int		ok;
	int		tests;

	vect_init(&v);
	TEST_START("imp_exp");

	TEST_IMP_EXP("['vamos' 'a' 'la' 'playa']");
	TEST_IMP_EXP("[['vamos' 'a'] ['la'] ['playa']]");
	TEST_IMP_EXP("[[''] ['hot' 'hot'] ['cold'] ['']]");
	TEST_IMP_EXP("[['chat'] ['bll'] ['chien' 'dog']]");

	free(v.data);
	TEST_RESULT;
}

void		test_size(void)
{
	t_vll	*l;
	t_vll	*l1;
	t_vect	v;
	char	a[1024];
	char	*b;
	int		ok;
	int		tests;

	TEST_START("size");

	TEST_SIZE("['']", 1);
	TEST_SIZE("[[''] ['']]", 2);
	TEST_SIZE("[]", 0);
	TEST_SIZE("[[''] [''] [''] ['']   ['']]", 5);

	TEST_RESULT;
}

int			main(void)
{
	test_imp_exp();
	test_size();
}
