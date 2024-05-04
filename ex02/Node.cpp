#include "Node.hpp"

Node::Node(int value): value(value){
    smallNode = NULL;
}
Node::Node(int value1, int value2){
    if(value1 < value2){
        value = value2;
        setSmallNode(value1);
        return ;
    }
    value = value1;
    setSmallNode(value2);
}

Node::~Node(){
    if(smallNode != NULL)
        delete smallNode;
}

void Node::setSmallNode(int value){
    if(smallNode != NULL){
        std::cerr << "Debug: smallValue already set" << std::endl;;
        return;
    }
    smallNode = new Node(value);
}

void Node::setNextNode(Node *node){
    nextNode = node;
}

Node *Node::getSmallNode(){
    return smallNode;
}