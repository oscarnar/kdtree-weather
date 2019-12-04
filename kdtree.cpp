#include "kdtree.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

    //Funcion para ordenar los puntos de acuerdo al axis
    void Kdtree::ordenar(vector<vector<int>> &points, int axi){
        vector<pair<int,vector<int>>> temp;
        for(int i=0; i<points.size(); i++){
            int x = points[i][axi];
            temp.push_back(pair<int,vector<int>> (x,points[i]));
        }
        sort(temp.begin(),temp.end());
        points.clear();
        for(int i=0; i<temp.size(); i++){
            points.push_back(temp[i].second);
        }
    }
    //Constructor del kdtree
    Node* Kdtree::build_kdtree(vector<vector<int>> points,int depth){
        int tam = points.size();
        int axis = depth % k;

        if(tam <= 0)
            return 0;
        if(tam == 1)
            return new Node(points[0],axis);
        int med = tam/2;
        vector<vector<int>> lef,rig;
        ordenar(points,axis);
        for(int i=0; i<tam; i++){
            if(i<med)
                lef.push_back(points[i]);
            if(i>med)
                rig.push_back(points[i]);
        }
        Node* temp = new Node(points[med],axis);
        temp->left = build_kdtree(lef,depth + 1);
        temp->right = build_kdtree(rig,depth + 1);
        if(temp->left != NULL)
            temp->left->parent=temp;
        if(temp->right != NULL)
            temp->right->parent=temp;

        return temp;
    }
    void Kdtree::build(){
        vector<vector<int>> result;
        vector<string> clima;
        vector<int> anio;
        llenar(result);
        //for(int i=0; i<15; i++)
        //    cout<<result[i][2]<<endl;
        this->root=build_kdtree(result,0);
    }
    void Kdtree::weather(vector<string> clima){
        vector<string> allclimas{clima[0]};
        cout<<allclimas[0]<<endl;
        for(int i=1; i<clima.size(); i++){
            vector<string>::iterator it;
            it=find(allclimas.begin(),allclimas.end(),clima[i]);
            if(it != allclimas.end()){
                //allclimas.push_back(*it);
            }
            else{
                allclimas.push_back(clima[i]);
                cout<<"\""<<clima[i]<<"\",";
            }
        }
        cout<<endl;
    }
    void Kdtree::llenar(vector<vector<int>> &result){
        ifstream file;
        file.open("../data.csv");
        string line;
        while(getline(file,line)){
            stringstream str(line);
            string tmp;
            vector<int> word;
            char delim = ',';
            for(int i=0; i<7; i++){
                getline(str,tmp,delim);
                if(i == 0){
                    stringstream sdate(tmp);
                    int tmpdate,ani,mes,dia;
                    for(int j=0; j<3; j++){
                        string stmp;
                        getline(sdate,stmp,'.');
                        if(j==0)
                            dia=stoi(stmp);
                        if(j==1)
                            mes=stoi(stmp);
                        else
                            ani=stoi(stmp);
                    }
                    tmpdate=(mes*100)+dia;
                    word.push_back(tmpdate);
                    word.push_back(ani);
                }
                if(i == 1){
                    vector<string>::iterator it;
                    it = find(climas.begin(),climas.end(),tmp);
                    int pos=it - climas.begin();
                    word.push_back(pos);
                }
                if(i == 2){
                    float lluvia=stof(tmp);
                    word.push_back(lluvia*10);
                }
                if(i > 2){
                    int dat=stoi(tmp);
                    word.push_back(dat);
                }
            }
            result.push_back(word);
        }
    }
    double Kdtree::distance(vector<int> p1,vector<int> p2){
        double dis=0.0;
        dis=pow((p1[0]-p2[0])*1.0, 2) + pow((p1[1]-p2[1])*1.0, 2);
        dis=sqrt(dis);
        return dis;
    }
    //nn: busca los n puntos mas cercanos
    void Kdtree::nn(Node* node,vector<int> point,double &dist,vector<pair<double,vector<int>>> &result,int k){
        if(node == NULL)
            return;
        double nodeDist=distance(point,node->point);
        if(result.size() < k){
            result.push_back(make_pair(nodeDist,node->point));
            sort(result.begin(),result.end());
            dist=result[result.size()-1].first;
        }
        else{
            if(nodeDist < dist){
                result[k-1] = make_pair(nodeDist,node->point);
                sort(result.begin(),result.end());
                dist=result[k-1].first;
            }
        }
        int split=node->point[node->axis];

        if(point[node->axis] >= split - dist){
            nn(node->right,point,dist,result,k);
        }
        if(point[node->axis] <= split + dist){
            nn(node->left,point,dist,result,k);
        }
    }
    vector<vector<int>> Kdtree::nn(vector<int> point,int k){
        vector<pair<double,vector<int>>> result;
        double dist=99999;
        nn(this->root,point,dist,result,k);
        vector<vector<int>> rpta;
        for(int i=0; i<result.size();i++ )
            rpta.push_back(result[i].second);
        return rpta;
    }
    //k es el numero de puntos a consultar
    string Kdtree::consulta(vector<int> point, int k){
        vector<vector<int>> npoints;
        npoints = nn(point,k);
        int posClima = 0;
        for(int i=0; i<k; i++){
            posClima+=npoints[i][2];
        }
        posClima=posClima/k;
        point[2]=posClima;
        return climas[posClima];
    }


