#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>
class Node{
    private:
        Node();
    public:
        Node(int value);
        Node(int value1, int value2);
        ~Node();
    private:
    public:
        Node *getSmallNode();
        void setSmallNode(int value);
        void setNextNode(Node *node);
    private:
        int value;
        Node * nextNode;
};

#endif