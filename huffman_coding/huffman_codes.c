#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

/**
 * free_huffman_tree - Frees the Huffman tree
 *
 * @node: Pointer to the root node of the tree
 */
static void free_huffman_tree(binary_tree_node_t *node)
{
    if (node)
    {
        free_huffman_tree(node->left);
        free_huffman_tree(node->right);
        if (node->data)
            free(node->data); /* Free symbol_t */
        free(node);
    }
}

/**
 * print_huffman_codes - Recursively prints Huffman codes
 *
 * @node: Current node
 * @buff: Buffer to store the code
 * @depth: Current depth (length of code)
 */
static void print_huffman_codes(binary_tree_node_t *node, char *buff, int depth)
{
    symbol_t *symbol;

    if (!node)
        return;

    symbol = (symbol_t *)node->data;

    if (!node->left && !node->right)
    {
        buff[depth] = '\0';
        printf("%c: %s\n", symbol->data, buff);
        return;
    }

    if (node->left)
    {
        buff[depth] = '0';
        print_huffman_codes(node->left, buff, depth + 1);
    }

    if (node->right)
    {
        buff[depth] = '1';
        print_huffman_codes(node->right, buff, depth + 1);
    }
}

/**
 * huffman_codes - Build the Huffman tree and print the resulting Huffman codes
 *
 * @data: Array of characters of size size
 * @freq: Array containing the associated frequencies
 * @size: Size of the arrays
 *
 * Return: 1 if it succeed, 0 if it fails
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
    binary_tree_node_t *root;
    char *buff;

    if (!data || !freq || size == 0)
        return (0);

    root = huffman_tree(data, freq, size);
    if (!root)
        return (0);

    buff = malloc(sizeof(char) * (size + 1)); /* Max depth generally < size */
    /* Actually max depth could theoretically be size-1 in worst case degenerate tree */
    /* Wait, for safety let's allocate enough. A degenerate tree of N nodes has depth N-1. */
    /* So size + 1 is barely enough for null terminator possibly? */
    /* Let's be safe and use a reasonable buffer or exact size. */
    /* Actually worst case depth is 'size', so size + 1 is fine. */
    
    if (!buff)
    {
        free_huffman_tree(root);
        return (0);
    }

    print_huffman_codes(root, buff, 0);

    free(buff);
    free_huffman_tree(root);
    return (1);
}
