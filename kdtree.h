#include <iostream>
#include <vector>
using namespace std;

class Node{
public:
    vector<int> point;
    Node* left;
    Node* right;
    int axis;
    Node* parent;
public:
    Node(){
        this->left=0;
        this->right=0;
        this->parent=0;
        this->axis=0;
        this->point.assign(9,0);
    }
    Node(vector<int> poi,int axi){
        this->left=0;
        this->right=0;
        this->point=poi;
        this->axis=axi;
        this->parent=0;
    }
};
class Kdtree{
private:
    Node* root;
    int k;
    vector<string> climas{"Sunny","Partly cloudy","Cloudy","Overcast","Fog","Mist","Patchy light drizzle","Light drizzle","Patchy rain possible","Light rain","Light rain shower","Patchy light rain with thunder","Moderate rain at times","Moderate rain","Moderate or heavy rain shower","Moderate or heavy rain with thunder","Heavy rain at times","Heavy rain","Torrential rain shower","Thundery outbreaks possible","Light sleet","Light sleet showers","Moderate or heavy sleet","Moderate snow","Moderate or heavy snow showers","Blizzard"};
public:
    Kdtree(){
        this->root=NULL;
        this->k=9;
    }
    ~Kdtree(){
        destroi(this->root);
    }
    void destroi(Node* node){
        if(node == NULL)
            return;
        destroi(node->left);
        destroi(node->right);
        delete node;
    }
    void ordenar(vector<vector<int>> &points,int axi);
    Node* build_kdtree(vector<vector<int>> points,int depth=0);
    void build();
    void weather(vector<string> clima);
    void llenar(vector<vector<int>> &result);
    double distance(vector<int> p1,vector<int> p2);
    void nn(Node* node,vector<int> point,double &dist,vector<pair<double,vector<int>>> &result,int k);
    vector<vector<int>> nn(vector<int> point, int k);
    string consulta(vector<int> point,int k);
}; 
