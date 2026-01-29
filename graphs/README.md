# Graphs

## Description
This project implements a Graph data structure in C using an adjacency linked list representation. It covers creation, manipulation, and traversal of graphs.

## Data Structures
The graph is represented using the following structures:
- `edge_type_t`: Enumeration for Unidirectional and Bidirectional edges.
- `edge_t`: Linked list node representing an edge.
- `vertex_t`: Linked list node representing a vertex, containing a list of edges.
- `graph_t`: Structure holding the number of vertices and the head of the vertex list.

## Requirements
- OS: Ubuntu 14.04 LTS
- Compiler: gcc 4.8.4
- Flags: -Wall -Werror -Wextra -pedantic
- Style: Betty style
