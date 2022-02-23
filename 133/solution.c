#include <stdlib.h>
#include <stdio.h>

struct Node
{
    int val;
    int numNeighbors;
    struct Node **neighbors;
};

void init_node(struct Node **node, int val, int numNeighbors)
{
    struct Node *working;
    *node = malloc(sizeof(struct Node));
    working = *node;

    working->val = val;
    working->numNeighbors = numNeighbors;
    working->neighbors = malloc(sizeof(struct Node) * numNeighbors);
}

struct Node *cloneGraph(struct Node *s)
{
    struct Node *new_head = NULL;
    struct Node *orig_pt = NULL;
    struct Node *curr_pt = NULL;
    struct Node *walk_pt = NULL;
    size_t i, j, end_val = 0;
    int breaking = 0, exists = 0;

    if (s == NULL)
    {
        return NULL;
    }
    else if (s->numNeighbors == 0)
    {
        init_node(&new_head, 1, 0);
        return new_head;
    }
    else if (s->val == 0)
    {
        return NULL;
    }

    init_node(&new_head, 1, s->numNeighbors);

    orig_pt = s;
    curr_pt = new_head;

    for (i = 0; i < new_head->numNeighbors; i++)
    {
        // The largest node connected to the first node is the last node
        if (s->neighbors[i]->val > end_val)
        {
            end_val = s->neighbors[i]->val;
        }
    }

    while (!breaking)
    {
        //printf("Looking at %d's neighbors:\n", orig_pt->val);

        if (curr_pt->val == end_val)
        {
            //printf("Reached the end of the graph. Checking to see that everything is connected...\n");
            // If we have reached the last node and all of its neighbors have been linked we can break
            for (j = 0; j < curr_pt->numNeighbors; j++)
            {
                breaking = curr_pt->neighbors[j] != NULL && curr_pt->neighbors[j]->val != 0;
                if (!breaking)
                {
                    //printf("Unconnected neighbor on node %d index %lu\n", curr_pt->val, j);
                    break;
                }
            }
        }

        for (i = 0; i < orig_pt->numNeighbors && !breaking; i++)
        {
            //printf("Looking at %d\n", orig_pt->neighbors[i]->val);
            if (orig_pt->neighbors[i]->val == curr_pt->val + 1)
            {
                // Make a new node on the graph
                orig_pt = orig_pt->neighbors[i];
                //printf("Making a new node with value %d and connecting it to %d\n", orig_pt->val, curr_pt->val);
                init_node(&curr_pt->neighbors[i], orig_pt->val, orig_pt->numNeighbors);
                curr_pt = curr_pt->neighbors[i];
                break;
            }
            else if (orig_pt->neighbors[i]->val < curr_pt->val && (curr_pt->neighbors[i] == NULL || curr_pt->neighbors[i]->val != orig_pt->neighbors[i]->val))
            {
                // Find the node that has already been created and link it with this node
                //printf("Need to find %d in previous nodes...\n", orig_pt->neighbors[i]->val);
                walk_pt = new_head;
                while (walk_pt->val != orig_pt->neighbors[i]->val)
                {
                    for (j = 0; j < walk_pt->numNeighbors; j++)
                    {
                        if (walk_pt->neighbors[j]->val == walk_pt->val + 1)
                        {
                            walk_pt = walk_pt->neighbors[j];
                            break;
                        }
                    }
                }
                //printf("Found %d!\n", walk_pt->val);
                if (walk_pt->val != orig_pt->neighbors[i]->val)
                {
                    //printf("Something terrible has happened! The found node does not equal the original's value! (%d != %d)\n", walk_pt->val, orig_pt->neighbors[i]->val);
                    return NULL;
                }

                //printf("Connected %d to %d! (used index %lu)\n", curr_pt->val, walk_pt->val, i);
                curr_pt->neighbors[i] = walk_pt;
                for (j = 0; j < walk_pt->numNeighbors; j++)
                {
                    if (walk_pt->neighbors[j] == NULL || walk_pt->neighbors[j]->val == 0)
                    {
                        break;
                    } else if (walk_pt->neighbors[j]->val == curr_pt->val) {
                        //printf("Node %d already has node %d linked! (index %lu)\n", walk_pt->val, curr_pt->val, j);
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    if (walk_pt->neighbors[j] != NULL && walk_pt->neighbors[j]->val != 0) {
                        //printf("Something terrible has happened! I was unable to find an empty neighbor to link %d to %d!\n", walk_pt->val, curr_pt->val);
                        return NULL;
                    }
                    //printf("Connecting %d to %d! (used index %lu)\n", walk_pt->val, curr_pt->val, j);
                    walk_pt->neighbors[j] = curr_pt;
                }
                exists = 0;
            }
        }
    }

    //printf("Made new graph! Returning...\n");
    return new_head;
}

void print_graph(struct Node *head)
{
    struct Node *curr, *next;
    int end_val = 0;
    size_t i = 0;

    for (i = 0; i < head->numNeighbors; i++)
    {
        if (head->neighbors[i]->val > end_val)
        {
            end_val = head->neighbors[i]->val;
        }
    }

    curr = head;

    putchar('[');
    while (1)
    {

        putchar('[');
        for (i = 0; i < curr->numNeighbors; i++)
        {
            if (curr->neighbors[i]->val == curr->val + 1)
            {
                next = curr->neighbors[i];
            }

            printf("%d", curr->neighbors[i]->val);
            if (i + 1 != curr->numNeighbors)
            {
                putchar(',');
            }
        }
        putchar(']');

        if (curr->val == end_val)
        {
            break;
        }
        curr = next;
        putchar(',');
    }
    printf("]\n");
}

void free_graph(struct Node *head)
{

    struct Node *curr, *next;
    int end_val = 0;
    size_t i;

    if (head == NULL)
    {
        return;
    }
    else if (head->numNeighbors == 0)
    {
        free(head);
        return;
    }

    for (i = 0; i < head->numNeighbors; i++)
    {
        if (head->neighbors[i]->val > end_val)
        {
            curr = head->neighbors[i];
            end_val = curr->val;
        }
    }

    while (curr->val != 1)
    {
        for (i = 0; i < curr->numNeighbors; i++)
        {
            if (curr->neighbors[i]->val == curr->val - 1)
            {
                next = curr->neighbors[i];
                free(curr->neighbors);
                free(curr);
                curr = next;
                break;
            }
        }
    }
    free(curr->neighbors);
    free(curr);
}

int main(void)
{
    struct Node *first, *second, *third, *fourth, *fifth, *out;

    init_node(&first, 1, 3);
    init_node(&second, 2, 3);
    init_node(&third, 3, 3);
    init_node(&fourth, 4, 3);
    init_node(&fifth, 5, 4);
    

    first->neighbors[0] = second;
    first->neighbors[1] = fourth;
    first->neighbors[2] = fifth;

    second->neighbors[0] = first;
    second->neighbors[1] = third;
    second->neighbors[2] = fifth;

    third->neighbors[0] = second;
    third->neighbors[1] = fourth;
    third->neighbors[2] = fifth;

    fourth->neighbors[0] = first;
    fourth->neighbors[1] = third;
    fourth->neighbors[2] = fifth;

    fifth->neighbors[0] = first;
    fifth->neighbors[1] = second;
    fifth->neighbors[2] = third;
    fifth->neighbors[3] = fourth;

    printf("Original graph:\n");
    print_graph(first);

    printf("Cloning graph...\n");
    out = cloneGraph(first);

    printf("New graph:\n");
    print_graph(out);

    free_graph(first);
    free_graph(out);
}