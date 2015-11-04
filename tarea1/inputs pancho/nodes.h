#ifndef NODES_H
#define NODES_H

struct l_node;

struct t_node
{
    struct l_node *children;
    char *word;
    void (*callback)(const char *);
};

struct l_node
{
    struct t_node *data;
    struct l_node *next;
};

#endif // NODES_H
