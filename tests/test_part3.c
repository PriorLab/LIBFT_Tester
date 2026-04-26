#include "../utils/tester.h"
#include "libft.h"

static void	del_free(void *c)  { free(c); }
static void	del_noop(void *c)  { (void)c; }

static void	*map_upper(void *c)
{
	char	*s = ft_strdup((char *)c);
	int		i = 0;
	if (!s) return NULL;
	while (s[i]) { if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 32; i++; }
	return s;
}
static void	*map_identity(void *c) { return ft_strdup((char *)c); }
static void	*map_add_x(void *c)    { return ft_strjoin((char *)c, "x"); }

static int	g_iter_count = 0;
static char	g_iter_buf[64];
static int	g_iter_buf_pos = 0;
static void	iter_counter(void *c) { (void)c; g_iter_count++; }
static void	iter_collect(void *c) { g_iter_buf[g_iter_buf_pos++] = ((char *)c)[0]; }

void	test_lstnew(void)
{
	t_list	*n;
	int		*p;
	print_header("lstnew");

	n = ft_lstnew("hello");
	CHECK("node not NULL",               n != NULL);
	if (n) {
		CHECK("content is \"hello\"",    strcmp((char*)n->content, "hello") == 0);
		CHECK("next is NULL",            n->next == NULL);
		free(n);
	}
	n = ft_lstnew(NULL);
	CHECK("NULL content: node not NULL", n != NULL);
	if (n) {
		CHECK("NULL content: is NULL",   n->content == NULL);
		CHECK("NULL content: next NULL", n->next == NULL);
		free(n);
	}
	p = malloc(sizeof(int)); *p = 42;
	n = ft_lstnew(p);
	CHECK("int*: node not NULL",         n != NULL);
	if (n) {
		CHECK("int*: value = 42",        *(int*)n->content == 42);
		CHECK("int*: next is NULL",      n->next == NULL);
		free(n);
	}
	free(p);
	t_list *n1 = ft_lstnew("a");
	t_list *n2 = ft_lstnew("b");
	CHECK("two nodes are different",     n1 != n2);
	CHECK("n1->next != n2",              n1->next != n2);
	free(n1); free(n2);
	double d = 3.14;
	n = ft_lstnew(&d);
	CHECK("double*: node not NULL",      n != NULL);
	if (n) { CHECK("double*: next NULL", n->next == NULL); free(n); }
	n = ft_lstnew("test");
	CHECK("next always NULL on create",  n && n->next == NULL);
	if (n) free(n);
}

void	test_lstadd_front(void)
{
	t_list	*lst = NULL;
	t_list	*n1 = ft_lstnew("a");
	t_list	*n2 = ft_lstnew("b");
	t_list	*n3 = ft_lstnew("c");
	t_list	*n4 = ft_lstnew("d");
	print_header("lstadd_front");

	ft_lstadd_front(&lst, n1);
	CHECK("1st add: lst == n1",          lst == n1);
	CHECK("1st add: n1->next == NULL",   n1->next == NULL);

	ft_lstadd_front(&lst, n2);
	CHECK("2nd add: lst == n2",          lst == n2);
	CHECK("2nd add: n2->next == n1",     n2->next == n1);
	CHECK("2nd add: n1->next == NULL",   n1->next == NULL);

	ft_lstadd_front(&lst, n3);
	CHECK("3rd add: lst == n3",          lst == n3);
	CHECK("3rd add: n3->next == n2",     n3->next == n2);
	CHECK("3rd add: n2->next == n1",     n2->next == n1);

	ft_lstadd_front(&lst, n4);
	CHECK("4th add: lst == n4",          lst == n4);
	CHECK("4th add: n4->next == n3",     n4->next == n3);
	CHECK("size = 4",                    ft_lstsize(lst) == 4);
	CHECK("head content = \"d\"",        strcmp((char*)lst->content, "d") == 0);
	CHECK("tail content = \"a\"",        strcmp((char*)ft_lstlast(lst)->content, "a") == 0);

	free(n1); free(n2); free(n3); free(n4);
}

void	test_lstsize(void)
{
	t_list	*lst = NULL;
	print_header("lstsize");

	CHECK("NULL -> 0",                   ft_lstsize(NULL) == 0);

	t_list *n1 = ft_lstnew("a");
	ft_lstadd_back(&lst, n1);
	CHECK("1 node -> 1",                 ft_lstsize(lst) == 1);

	t_list *n2 = ft_lstnew("b");
	ft_lstadd_back(&lst, n2);
	CHECK("2 nodes -> 2",                ft_lstsize(lst) == 2);

	t_list *n3 = ft_lstnew("c");
	ft_lstadd_back(&lst, n3);
	CHECK("3 nodes -> 3",                ft_lstsize(lst) == 3);

	t_list *n4 = ft_lstnew("d");
	t_list *n5 = ft_lstnew("e");
	ft_lstadd_back(&lst, n4);
	ft_lstadd_back(&lst, n5);
	CHECK("5 nodes -> 5",                ft_lstsize(lst) == 5);
	CHECK("idempotent: still 5",         ft_lstsize(lst) == 5);
	CHECK("list intact: head=n1",        lst == n1);
	CHECK("list intact: last=n5",        ft_lstlast(lst) == n5);

	t_list *single = ft_lstnew("x");
	CHECK("single node -> 1",            ft_lstsize(single) == 1);
	free(single);
	free(n1); free(n2); free(n3); free(n4); free(n5);
}

void	test_lstlast(void)
{
	t_list	*n1 = ft_lstnew("a");
	t_list	*n2 = ft_lstnew("b");
	t_list	*n3 = ft_lstnew("c");
	t_list	*n4 = ft_lstnew("d");
	print_header("lstlast");

	CHECK("NULL -> NULL",                ft_lstlast(NULL) == NULL);
	CHECK("1 node -> itself",            ft_lstlast(n1) == n1);

	n1->next = n2;
	CHECK("2 nodes: last = n2",          ft_lstlast(n1) == n2);
	CHECK("2 nodes: n2->next NULL",      ft_lstlast(n1)->next == NULL);

	n2->next = n3;
	CHECK("3 nodes: last = n3",          ft_lstlast(n1) == n3);

	n3->next = n4;
	CHECK("4 nodes: last = n4",          ft_lstlast(n1) == n4);
	CHECK("4 nodes: last->next NULL",    ft_lstlast(n1)->next == NULL);
	CHECK("content of last = \"d\"",     strcmp((char*)ft_lstlast(n1)->content, "d") == 0);
	CHECK("head unchanged",              n1->next == n2);

	t_list *single = ft_lstnew("z");
	CHECK("single: last = itself",       ft_lstlast(single) == single);
	CHECK("single: last->next NULL",     ft_lstlast(single)->next == NULL);
	free(single);
	free(n1); free(n2); free(n3); free(n4);
}

void	test_lstadd_back(void)
{
	t_list	*lst = NULL;
	t_list	*n1 = ft_lstnew("a");
	t_list	*n2 = ft_lstnew("b");
	t_list	*n3 = ft_lstnew("c");
	t_list	*n4 = ft_lstnew("d");
	print_header("lstadd_back");

	ft_lstadd_back(&lst, n1);
	CHECK("1st add: lst == n1",          lst == n1);
	CHECK("1st add: n1->next == NULL",   n1->next == NULL);

	ft_lstadd_back(&lst, n2);
	CHECK("2nd add: head still n1",      lst == n1);
	CHECK("2nd add: n1->next == n2",     n1->next == n2);
	CHECK("2nd add: n2->next == NULL",   n2->next == NULL);

	ft_lstadd_back(&lst, n3);
	CHECK("3rd add: head still n1",      lst == n1);
	CHECK("3rd add: n2->next == n3",     n2->next == n3);
	CHECK("3rd add: n3->next == NULL",   n3->next == NULL);

	ft_lstadd_back(&lst, n4);
	CHECK("4th add: n3->next == n4",     n3->next == n4);
	CHECK("4th add: n4->next == NULL",   n4->next == NULL);
	CHECK("4th add: size = 4",           ft_lstsize(lst) == 4);
	CHECK("4th add: last = n4",          ft_lstlast(lst) == n4);
	CHECK("head content = \"a\"",        strcmp((char*)lst->content, "a") == 0);
	CHECK("tail content = \"d\"",        strcmp((char*)ft_lstlast(lst)->content, "d") == 0);

	free(n1); free(n2); free(n3); free(n4);
}

void	test_lstdelone(void)
{
	t_list	*n1, *n2, *n3;
	print_header("lstdelone");

	n1 = ft_lstnew(ft_strdup("hello"));
	ft_lstdelone(n1, del_free);
	CHECK("del_free: no crash",          1);

	n1 = ft_lstnew("static");
	ft_lstdelone(n1, del_noop);
	CHECK("del_noop: no crash",          1);

	n1 = ft_lstnew(NULL);
	ft_lstdelone(n1, del_noop);
	CHECK("NULL content: no crash",      1);

	/* must not touch next */
	n1 = ft_lstnew(ft_strdup("a"));
	n2 = ft_lstnew(ft_strdup("b"));
	n3 = ft_lstnew(ft_strdup("c"));
	n1->next = n2;
	n2->next = n3;
	ft_lstdelone(n1, del_free);
	CHECK("does not touch n2",           strcmp((char*)n2->content, "b") == 0);
	CHECK("does not touch n3",           strcmp((char*)n3->content, "c") == 0);
	CHECK("n2->next still n3",           n2->next == n3);
	ft_lstdelone(n2, del_free);
	ft_lstdelone(n3, del_free);

	for (int i = 0; i < 5; i++) {
		n1 = ft_lstnew(ft_strdup("x"));
		ft_lstdelone(n1, del_free);
	}
	CHECK("5 consecutive deletes: no crash", 1);
}

void	test_lstclear(void)
{
	t_list	*lst = NULL;
	print_header("lstclear");

	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("a")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("b")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("c")));
	ft_lstclear(&lst, del_free);
	CHECK("3 nodes: list is NULL",       lst == NULL);

	ft_lstclear(&lst, del_free);
	CHECK("double clear: still NULL",    lst == NULL);

	lst = ft_lstnew(ft_strdup("x"));
	ft_lstclear(&lst, del_free);
	CHECK("1 node: list is NULL",        lst == NULL);

	for (int i = 0; i < 10; i++)
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup("x")));
	ft_lstclear(&lst, del_free);
	CHECK("10 nodes: list is NULL",      lst == NULL);

	for (int i = 0; i < 50; i++)
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup("x")));
	ft_lstclear(&lst, del_free);
	CHECK("50 nodes: list is NULL",      lst == NULL);

	lst = ft_lstnew(NULL);
	ft_lstclear(&lst, del_noop);
	CHECK("NULL content: list is NULL",  lst == NULL);
}

void	test_lstiter(void)
{
	t_list	*lst = NULL;
	t_list	*tmp;
	print_header("lstiter");

	g_iter_count = 0;
	ft_lstiter(NULL, iter_counter);
	CHECK("NULL: 0 calls",               g_iter_count == 0);

	ft_lstadd_back(&lst, ft_lstnew("a"));
	g_iter_count = 0;
	ft_lstiter(lst, iter_counter);
	CHECK("1 node: 1 call",              g_iter_count == 1);

	ft_lstadd_back(&lst, ft_lstnew("b"));
	ft_lstadd_back(&lst, ft_lstnew("c"));
	g_iter_count = 0;
	ft_lstiter(lst, iter_counter);
	CHECK("3 nodes: 3 calls",            g_iter_count == 3);

	/* iteration order */
	g_iter_buf_pos = 0;
	memset(g_iter_buf, 0, sizeof(g_iter_buf));
	ft_lstiter(lst, iter_collect);
	CHECK("order: buf[0]='a'",           g_iter_buf[0] == 'a');
	CHECK("order: buf[1]='b'",           g_iter_buf[1] == 'b');
	CHECK("order: buf[2]='c'",           g_iter_buf[2] == 'c');

	CHECK("list intact: size=3",         ft_lstsize(lst) == 3);

	ft_lstadd_back(&lst, ft_lstnew("d"));
	ft_lstadd_back(&lst, ft_lstnew("e"));
	g_iter_count = 0;
	ft_lstiter(lst, iter_counter);
	CHECK("5 nodes: 5 calls",            g_iter_count == 5);

	while (lst) { tmp = lst->next; free(lst); lst = tmp; }
}

void	test_lstmap(void)
{
	t_list	*original = NULL;
	t_list	*mapped;
	print_header("lstmap");

	mapped = ft_lstmap(NULL, map_upper, del_free);
	CHECK("NULL -> NULL",                mapped == NULL);

	ft_lstadd_back(&original, ft_lstnew(ft_strdup("hello")));
	mapped = ft_lstmap(original, map_upper, del_free);
	CHECK("1 node: not NULL",            mapped != NULL);
	if (mapped) {
		CHECK("1 node: size=1",          ft_lstsize(mapped) == 1);
		CHECK("1 node: \"HELLO\"",       strcmp((char*)mapped->content, "HELLO") == 0);
		CHECK("1 node: next==NULL",      mapped->next == NULL);
		ft_lstclear(&mapped, del_free);
	}
	ft_lstclear(&original, del_free);

	ft_lstadd_back(&original, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&original, ft_lstnew(ft_strdup("world")));
	ft_lstadd_back(&original, ft_lstnew(ft_strdup("42")));
	mapped = ft_lstmap(original, map_upper, del_free);
	CHECK("3 nodes: not NULL",           mapped != NULL);
	if (mapped) {
		CHECK("3 nodes: size=3",         ft_lstsize(mapped) == 3);
		CHECK("node 0: \"HELLO\"",       strcmp((char*)mapped->content, "HELLO") == 0);
		CHECK("node 1: \"WORLD\"",       strcmp((char*)mapped->next->content, "WORLD") == 0);
		CHECK("node 2: \"42\"",          strcmp((char*)mapped->next->next->content, "42") == 0);
		CHECK("last->next == NULL",      mapped->next->next->next == NULL);
		CHECK("new list is independent", mapped != original);
		ft_lstclear(&mapped, del_free);
	}
	CHECK("original intact: size=3",     ft_lstsize(original) == 3);
	CHECK("original node 0 = \"hello\"", strcmp((char*)original->content, "hello") == 0);
	ft_lstclear(&original, del_free);

	ft_lstadd_back(&original, ft_lstnew(ft_strdup("abc")));
	ft_lstadd_back(&original, ft_lstnew(ft_strdup("def")));
	mapped = ft_lstmap(original, map_identity, del_free);
	CHECK("identity: size=2",            mapped && ft_lstsize(mapped) == 2);
	if (mapped) {
		CHECK("identity: node0=\"abc\"", strcmp((char*)mapped->content, "abc") == 0);
		CHECK("identity: node1=\"def\"", strcmp((char*)mapped->next->content, "def") == 0);
		ft_lstclear(&mapped, del_free);
	}
	ft_lstclear(&original, del_free);

	ft_lstadd_back(&original, ft_lstnew(ft_strdup("a")));
	ft_lstadd_back(&original, ft_lstnew(ft_strdup("b")));
	mapped = ft_lstmap(original, map_add_x, del_free);
	CHECK("add_x: size=2",               mapped && ft_lstsize(mapped) == 2);
	if (mapped) {
		CHECK("add_x: node0=\"ax\"",     strcmp((char*)mapped->content, "ax") == 0);
		CHECK("add_x: node1=\"bx\"",     strcmp((char*)mapped->next->content, "bx") == 0);
		ft_lstclear(&mapped, del_free);
	}
	ft_lstclear(&original, del_free);

	for (int i = 0; i < 5; i++)
		ft_lstadd_back(&original, ft_lstnew(ft_strdup("x")));
	mapped = ft_lstmap(original, map_identity, del_free);
	CHECK("5 nodes: size=5",             mapped && ft_lstsize(mapped) == 5);
	if (mapped) ft_lstclear(&mapped, del_free);
	ft_lstclear(&original, del_free);
}
