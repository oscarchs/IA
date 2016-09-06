#ifndef GRAPH_H
#define GRAPH_H
#include "GNode.h"
#include "GEdge.h"
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
template <class N,class E>
class Graph{
public:
  typedef N NodeType;
  typedef E EdgeType;
  typedef Graph<NodeType,EdgeType> self;
  typedef GNode<self> Node;
  typedef GEdge<self> Edge;

  vector<Node*> nodes_;
  bool dir_;
  bool insert_node(N x);
  bool find_node(N x,Node** &p);
  void insert_edge(N a,N b,E data);
  void remove_edge(N x,N y);
  void remove_edge(E x,E y);

  void insert_edge_by_nodes(Node* a,Node* b,E data,bool dir);
  Edge * find_edge_by_nodes(Node* a,Node* b);

  void finding_node(N i);
  Node * find_in_vector(N a);
 
  void breadth_first_search(N a,N b);
  void gen_dot_();
  void delete_double_edge(string tmp,string &tmp1);
};
template <class N,class E>
void Graph<N,E>::finding_node(N i){
  Node** p;

  cout << find_node(i,p);
  return;
}

template <class N,class E>
bool Graph<N,E>::insert_node(N x){
  Node* n = new Node(x);
  nodes_.push_back(n);
  return 1;
}

template <class N,class E>
bool Graph<N,E>::find_node(N x,Node** &p){
  for(int i=0; i < this->nodes_.size() ; i++){
    p = &(this->nodes_[i]);
    if((*p)->data_ == x){
      return 1;
    }
    if(!(*p)->edges_.empty()){
      for (int j=0; j < (*p)->edges_.size(); j++){
          while(!(*p)->visited_){
              //cout << (*p)->data_;
              if((*p)->data_ == x){
                return 1;
              }
              (*p)->visited_ = 1;
              if((*p)->edges_.empty()){
                  break;
              }
              (*p) = (*p)->edges_[j]->nodes_[1];
          }
      }
    }
  }
  return 0;
}



template <class N,class E>
void Graph<N,E>::insert_edge(N a,N b,E data){ // insert edge 
  insert_edge_by_nodes(find_in_vector(a),find_in_vector(b),data,this->dir_);
  if(!this->dir_)
    insert_edge_by_nodes(find_in_vector(b),find_in_vector(a),data,this->dir_);
  return;
}


template <class N,class E>
typename Graph<N,E>::Node* Graph<N,E>::find_in_vector(N a){
  for(int i =0;i < this->nodes_.size(); i++){
      if (this->nodes_[i]->data_== a ){
        return this->nodes_[i];
      }
    }
}

template <class N,class E>
void Graph<N,E>::insert_edge_by_nodes(Node* a,Node* b,E data,bool dir){
  Edge* n = new Edge(b,data);
  n->dir_ = dir;
  a->edges_.push_back(n);
  return;
}

/*****************/
template <class N,class E>
typename Graph<N,E>::Edge * Graph<N,E>::find_edge_by_nodes(Node* a,Node* b){
  Edge * ret;
  Node * p = find_in_vector(a->data_);
  for(int i=0;i<p->edges_.size();i++){
      if(p->edges_[i]->nodes_[1]->data_ == b->data_)
        ret = p->edges_[i];
    }
  return ret;
}
template <class N,class E>
void Graph<N,E>::delete_double_edge(string tmp,string &tmp1){
  for(int i=0;i<tmp1.size();i=i+4){
    cout << tmp.find(tmp1.substr(i,4));
  }
}
template <class N,class E>
void Graph<N,E>::remove_edge(N x,N y){
  Node * a = find_in_vector(x);

  for(int i = 0;i < a->edges_.size(); i++){
      if(a->edges_[i]->nodes_[1]->data_ == y)
        a->edges_.erase();
    }
  Node * b = find_in_vector(y);
  for(int i = 0;i < b->edges_.size(); i++){
      if(b->edges_[i]->nodes_[1]->data_ == a)
        b->edges_.erase(i);
    }
}

/** bfs ********************/

template< typename N, typename E>
void Graph<N,E>::breadth_first_search(N a,N b) {
    Node* x = find_in_vector(a);
    Node* y = find_in_vector(b);

    for (int i=0; i<nodes_.size(); i++) {
        nodes_[i]->color = 0; // WHITE
        nodes_[i]->d = numeric_limits<int>::max();
        nodes_[i]->pi = '-';
    }
    x->color = 1; //gray
    x->d = 0;
    x->pi = '-';
    deque<Node*> q;
    q.push_back(x);
    while ( !q.empty() ) {
        Node* u = q.front();
        q.pop_front();
        cout<<"root: "<<u->data_<<endl;
        for (int i=0; i < u->edges_.size(); i++) {
            if (u->edges_[i]->nodes_[1]->color == 0){ //white
                cout<<u->edges_[i]->nodes_[1]->data_<<'\t';
                if(u->edges_[i]->nodes_[1]->data_ == y->data_ ) {
                    cout<<endl;
                    cout<<"node founded"<<" d: "<<u->d + 2<<endl;
                    return;
                }
                u->edges_[i]->nodes_[1]->color = 1; // gray
                u->edges_[i]->nodes_[1]->d = (u->d)+1;

                u->edges_[i]->nodes_[1]->pi = u->data_;
                q.push_back(u->edges_[i]->nodes_[1]);
            }
        }
        cout<<endl;
        cout << q.size()<<endl;
        u->color = 2; // black
    }
}


/** GraphViz **/

template <class N,class E>
void Graph<N,E>::gen_dot_(){
  string tmp;
  if(this->nodes_[0]->edges_[0]->dir_)
    tmp += "di";
  tmp += "graph{\n\n";
  for(int i=0;i<this->nodes_.size();i++){
    this->nodes_[i]->get_node_and_edges(tmp);
    tmp += "\n";
  }
  tmp += "}\n";
  //cout << tmp;
  ofstream graph("graph.dot");
  graph<<tmp;
  return ;
}







#endif // GRAPH_H
