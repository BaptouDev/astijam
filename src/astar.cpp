/*#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "include/vector2.h"

#define ROW 9
#define COL 10 

using namespace std;

struct cell {
    int parent_i, parent_j;
    double h;
};

struct shit {
    Vector2f pos;
    int distance;
};

double calculateHValue(Vector2f pos, Vector2f dest){
    // Return using the distance formula
    return ((double)sqrt(
        (pos.x - dest.x) * (pos.x - dest.x)
        + (pos.y - dest.y) * (pos.y - dest.y)));
}

bool is_dest(Vector2f des, Vector2f pos ){
    if ( des.x == pos.x && des.y == pos.y){
        return true;
    }

    return false;
}

bool is_valid(Vector2f pos){
    if(pos.x < COL && pos.x >= 0){
        if(pos.y >= 0&& pos.y < ROW){
            return true;
        }
    }

    return false;
}

vector<Vector2f> build_chemin(Cells[][],Vector2f dest, Vector2f pos){
    int i = dest.x;
    int j = dest.y;
    vector<Vector2f>res;
    while(!(i==pos.x && j == pos.y)){
        Vector2f nouveau;
        nouveau.x = i;
        nouveau.y = j;
        res.push_back(nouveau);
        Vector2f cur = Cells[i][j];
        i = cur.parent_i;
        j = cur.parent_j;
    }

    vector<Vector2f>trueres(res.size(),0);

    for(int i = 0; i<res.size(); i++){
        trueres[res.size()-i-1] = res[i];
    }
    return trueres;
}



vector<Vector2f> astar(int grid, Vector2f posennemi, Vector2f posjoueur){

    cell cellDetails[ROW][COL];


    for(int i = 0 ; i< COL; i++){
        for(int j = 0; j< ROW; j++){
            cellDetails[i][j].h = __FLT128_MAX__ ;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;

        }
    }

    int i = posennemi.x;
    int j = posennemi.y;

    cellDetails[i][j].h = 0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    bool Found_Dest = false;

    map<Vector2f,int>distances;

    set<shit> myqueue;



    while(!myqueue.empty()){
        shit cur = *myqueue.begin();
        myqueue.erase(myqueue.begin());

        int i = cur.pos.x;
        int j  =cur.pos.y;


        double hnew;


        if(distances.find(cur.pos)==distances.end()){ //si pas dans le dico
            distances[cur.pos] = cur.distance;
            //         distances.insert(cur.pos,cur.distance);
 // ou ce shit là à voir ce qui est mieux 67



            
            //W E S N SE SW NE NW

            //pour chaque neighbour 

            //North (i, j-1)
            Vector2f newpos;
            newpos.x = i;
            newpos.y = j-1;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i][j - 1].parent_i = i;
                        cellDetails[i][j - 1].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur, posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }

            // South (i,j+1)
            Vector2f newpos;
            newpos.x = i;
            newpos.y = j+1;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i][j + 1].parent_i = i;
                        cellDetails[i][j + 1].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur,posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }

            // East (i+1,j)
            Vector2f newpos;
            newpos.x = i+1;
            newpos.y = j;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i+1][j].parent_i = i;
                        cellDetails[i+1][j].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur, posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }

            //West (i-1, j)
            Vector2f newpos;
            newpos.x = i-1;
            newpos.y = j;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i-1][j].parent_i = i;
                        cellDetails[i-1][j].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur, posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }           

            // NW (i-1, j-1)
            Vector2f newpos;
            newpos.x = i-1;
            newpos.y = j-1;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i-1][j - 1].parent_i = i;
                        cellDetails[i-1][j - 1].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur, posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }
            // NE (i+1, j-1)
            Vector2f newpos;
            newpos.x = i+1;
            newpos.y = j-1;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i+1][j - 1].parent_i = i;
                        cellDetails[i+1][j - 1].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur, posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }

            //SW (i-1, j+1)
            Vector2f newpos;
            newpos.x = i-1;
            newpos.y = j+1;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i-1][j + 1].parent_i = i;
                        cellDetails[i-1][j + 1].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur, posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }

            // SE (i+1, j+1)
            Vector2f newpos;
            newpos.x = i+1;
            newpos.y = j+1;
            if(is_valid(newpos)){ //si on est sur une case valide
                if(!grid[newpos.x][newpos.y]){ // si y'a pas de obstacle

                    if(is_dest(posjoueur, newpos)){ //si on a trouvé la destination
                        // return gg

                        cellDetails[i+1][j + 1].parent_i = i;
                        cellDetails[i+1][j + 1].parent_j = j;
                          
                        Found_Dest = true;
                        return build_chemin(cellDetails, posjoueur, posennemi);


                    }else if (distances.find(newpos)==distances.end()){  //pas dans le dico
                        

                        hnew = calculateHValue(newpos,posjoueur );

                        distance[newpos]= hnew;


                        if(cellDetails[newpos.x][newpos.y].h == __FLT128_MAX__ || cellDetails[newpos.x][newpos.y].h > hnew){
                            shit nouveau;
                            nouveau.pos = newpos;
                            nouveau.distance = hnew;
                            myqueue.insert(nouveau); //tu insert ton nouveau shit

                            //tu update la celldetails

                            cellDetails[newpos.x][newpos.y].h = hnew;
                            cellDetails[newpos.x][newpos.y].parent_i = i;
                            cellDetails[newpos.x][newpos.y].parent_j = j;
                        }


                    }
                }
                    


                
            }

       
        }





    }
}

*/
