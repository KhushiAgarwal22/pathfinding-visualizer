#include <SFML/Graphics.hpp>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>

//Global Variables for the entire program
RenderWindow window(VideoMode(1000,600),"Grid");
bool ranBFS = false;
string BFSpath = "For BFS Press : 1 ";
#define num 60      //number of cells in a row



//Djikstra Algorithm
//--------Dijkstra--------
vector<pair<int,int> > pathD;        //Shortest pathD
bool sptSet[num][num];      //explored cells
void findmin(float dist[num][num],int& min_x,int& min_y){
    float mini=FLT_MAX;
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            if(sptSet[i][j]==false && dist[i][j]<mini){
                mini=dist[i][j];
                min_x=i;
                min_y=j;
            }
}
void findpath(pair<int,int> previous[num][num],float dist[num][num],int dest_x,int dest_y,int source_x,int source_y){
    cout<<"\nLength of Dijkstra path is: "<<dist[dest_x][dest_y]<<endl;
    while(previous[dest_x][dest_y].first!=source_x || previous[dest_x][dest_y].second!=source_y){        // both simultaneously equal to source coordinates
        sf::sleep(milliseconds(10));        //delay shortest pathD
        int x = previous[dest_x][dest_y].first;
        int y = previous[dest_x][dest_y].second;    
        cout << "Visiting x = " << previous[dest_x][dest_y].first << "  " << "and y = " << previous[dest_x][dest_y].second << endl;
        RectangleShape yellowRectangle(Vector2f(10,10));
        yellowRectangle.setFillColor(Color::Magenta);
        yellowRectangle.setOutlineThickness(1);
        yellowRectangle.setOutlineColor(Color::Red);
        yellowRectangle.setPosition(y*10,x*10);
        window.draw(yellowRectangle);
        window.display();
        pathD.push_back(make_pair(previous[dest_x][dest_y].first,previous[dest_x][dest_y].second));
        int save_x=dest_x,save_y=dest_y;
        dest_x=previous[save_x][save_y].first;
        dest_y=previous[save_x][save_y].second;
    }
    sleep(seconds(5));
}
void dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[num][num]){
    pair<int,int> previous[num][num];
    float dist[num][num];
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            dist[i][j]=FLT_MAX;
    dist[source_x][source_y]=0.0;
    int found=0;
    for(int i=0;i<num && found==0;i++) {
        for(int j=0;j<num && found==0;j++){
            int min_x=0,min_y=0;
            findmin(dist,min_x,min_y);
            sptSet[min_x][min_y]=true;
            if(sptSet[dest_x][dest_y]==true){
                found=1;
                break;
            }
            sf::sleep(milliseconds(1));        //delay exploration
            int possibleX[] = {0, 0, 1, -1, 1, -1, -1, 1};
            int possibleY[] = {1, -1, 0, 0, 1, 1, -1, -1};

            for(int i = 0; i < 8; ++i) {
                int newRow = min_x + possibleX[i];
                int newCol = min_y + possibleY[i];
                RectangleShape yellowRectangle(Vector2f(10,10));
                yellowRectangle.setFillColor(Color::Yellow);
                yellowRectangle.setOutlineThickness(1);
                yellowRectangle.setOutlineColor(Color::Red);
                yellowRectangle.setPosition(min_y*10,min_x*10);
                window.draw(yellowRectangle);
                window.display();
                if(grid[newRow][newCol]==1 && sptSet[newRow][newCol]==false && dist[newRow][newCol]>dist[min_x][min_y]+1.0){
                dist[newRow][newCol]=dist[min_x][min_y]+1.0;
                previous[newRow][newCol]=make_pair(min_x,min_y);
                }
            }
        }
    }
        
    findpath(previous,dist,dest_x,dest_y,source_x,source_y);
}


//Breadth First Algorithm

// Direction vectors
int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, 1, 0, -1 };




bool isValid(bool vis[][60],int grid[][60],
             int row, int col)
{
    // If cell lies out of bounds
    if (row < 0 || col < 0
        || row >= 59 || col >= 59)
        return false;
 
    // If cell is already visited
    if (vis[row][col])
        return false;

    //if wall is encountered;
    if(grid[row][col] == 0)
        return false;

    // Otherwise
    return true;
}
 
// Function to perform the BFS traversal
void BFS(int grid[][60], bool vis[60][60],int filled[][60],
         int row, int col,int dest_x,int dest_y)
{   
    int shortestLength = 0;
    // Stores indices of the matrix cells
    queue<pair<int, int> > q;
 
    // Mark the starting cell as visited
    // and push it into the queue
    q.push({ row, col });
    vis[row][col] = true;
    map<pair<int,int>,pair<int,int>> prev_cell;
    // Iterate while the queue
    // is not empty
    while (!q.empty()) {
        sf::sleep(milliseconds(1));
        pair<int, int> cell = q.front();
        int x = cell.first;
        int y = cell.second;

        //cout << grid[x][y] << " ";
        
        filled[x][y] = 1;

        if(x != row || y != col){
            RectangleShape yellowRectangle(Vector2f(10,10));
            sf::Clock clock;

            if (clock.getElapsedTime().asMilliseconds() >= 10) {
                // Update visualization code here
                clock.restart();
            }

            yellowRectangle.setFillColor(Color::Yellow);
            yellowRectangle.setOutlineThickness(1);
            yellowRectangle.setOutlineColor(Color::Red);
            yellowRectangle.setPosition(y*10,x*10);
            window.draw(yellowRectangle);
            window.display();
        }
        

 
        q.pop();

        if(x == dest_x && y == dest_y){
            while(prev_cell[{x,y}].first != row || prev_cell[{x,y}].second != col ){
                x = prev_cell[{x,y}].first;
                y = prev_cell[{x,y}].second;

                RectangleShape magentaRectangle(Vector2f(10,10));
                magentaRectangle.setFillColor(Color::Magenta);
                magentaRectangle.setOutlineThickness(1);
                magentaRectangle.setOutlineColor(Color::Red);
                magentaRectangle.setPosition(y*10,x*10);
                sf::sleep(milliseconds(50));
                shortestLength++;
                window.draw(magentaRectangle);
                window.display();
            }
            shortestLength--;
            cout << "BFS Shortest length : " << shortestLength << endl;
            ranBFS = true;
            sleep(milliseconds(10));
            for(int i = 0;i<5000;i++){
                sleep(milliseconds(1));
            }
            return;
        }
        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {
 
            int adjx = x + dRow[i];
            int adjy = y + dCol[i];

            if (isValid(vis,grid, adjx, adjy)) {
                prev_cell[{adjx,adjy}] = {x,y};
                q.push({ adjx, adjy });
                vis[adjx][adjy] = true;
               
            }
        }
    }
}

int main()
{   
    int filled[60][60];
    bool visited[60][60];
    int grid[60][60];

    for(int i = 0;i<60;i++){
        for(int j = 0;j<60;j++){
            visited[i][j] = false;
            filled[i][j] = 0;
        }
    }

    RectangleShape rectangle(Vector2f(10,10));   //White grid box
    rectangle.setFillColor(Color::White);
    RectangleShape blackRectangle(Vector2f(10,10));     //Black box for border
    blackRectangle.setFillColor(Color::Black);
    RectangleShape redRectangle(Vector2f(10,10));   //destination grid box
    redRectangle.setFillColor(Color::Red);
    //redRectangle.setOutlineThickness(2);
    redRectangle.setOutlineColor(Color::Blue);
    RectangleShape GreenRectangle(Vector2f(10,10)); // source grid box
    GreenRectangle.setFillColor(Color::Green);
    //blueRectangle.setOutlineThickness(2);
    GreenRectangle.setOutlineColor(Color::Black);
    RectangleShape yellowRectangle(Vector2f(10,10));
    yellowRectangle.setFillColor(Color::Yellow);

    int source_x=2,source_y=2,dest_x=50,dest_y=56;      //original start and destination : Origin(2,3) -> Goal(50,56)

    //text
    sf::Font font;
    font.loadFromFile("Pixeled.ttf");
    sf::Text text1("Pathfinding Visualizer",font,20);
    Text text2(BFSpath,font, 18);
    
    


    for(int i = 0;i<60;i++){
        for(int j = 0;j<60;j++){
            if(i == 0||i == 59||j ==0 || j == 59) grid[i][j] = 0; //adding the walls at the border
            else grid[i][j] = 1;
        }
    }

    /*
    for(int i = 0 ; i < 60;i++){
        for(int j = 0;j<60;j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    */

    //BFS(grid,visited,filled,0,0);

    while(window.isOpen()){
        sf::Event evnt;

        

        while(window.pollEvent(evnt)){
            if(evnt.type == evnt.Closed){
                window.close();
            } 
            if(Mouse::isButtonPressed(Mouse::Left)){
                int x = Mouse::getPosition(window).x;
                int y = Mouse::getPosition(window).y;
                int row=y/10;
                int col = x/10;
                if(grid[row][col] == 1 && (row < 60 && col < 60)){
                    grid[row][col] = 0;
                }
            }
            if(Mouse::isButtonPressed(Mouse::Right)){
                int x = Mouse::getPosition(window).x;
                int y = Mouse::getPosition(window).y;
                int row=y/10;
                int col = x/10;
                if(grid[row][col] == 0 && (row < 60 && col < 60)){
                    grid[row][col] = 1;
                }

            }

            //adding source grid box
            if(evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::S){
                int mouse_x = Mouse::getPosition(window).x;
                int mouse_y = Mouse::getPosition(window).y;
                cout << mouse_x << " " <<mouse_y << endl;
                source_x=mouse_y/10;
                source_y = mouse_x/10;
                //cout << "You tried to enter source grid box.";
                
            }
            //adding destination grid box
            if(evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::D){
               int mouse_x = Mouse::getPosition(window).x;
                int mouse_y = Mouse::getPosition(window).y;
                cout << mouse_x << " " <<mouse_y << endl;
                dest_x=mouse_y/10;
                dest_y = mouse_x/10;
                //cout << "You tried to enter dest grid box.";
            }

            //BFS keybind
            if(evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Num1){
                for(int i = 0;i<60;i++){
                    for(int j = 0;j<60;j++){
                        visited[i][j] = false;
                        filled[i][j] = 0;
                    }
                }
                BFS(grid,visited,filled,source_x,source_y,dest_x,dest_y);
                cout << "Function call has ended";
            }
            if(evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Num2){
                for(int i = 0;i<60;i++){
                    for(int j = 0;j<60;j++){
                        visited[i][j] = false;
                        filled[i][j] = 0;
                    }
                }
                dijkstra(source_x,source_y,dest_x,dest_y,grid);
                cout << "Function call has ended";
            }

        }

        

        for(int i = 0;i<=590;i+=10){
            for(int j = 0;j<=590;j+=10){
                //adding the default white cells
                if(grid[i/10][j/10] == 1){
                    rectangle.setOutlineThickness(1);
                    rectangle.setOutlineColor(Color::Black);
                    rectangle.setPosition(j,i);
                    window.draw(rectangle);   
                }
                //adding black border cells
                else if(grid[i/10][j/10] == 0){
                    blackRectangle.setOutlineThickness(1);
                    blackRectangle.setOutlineColor(Color::Red);
                    blackRectangle.setPosition(j,i);
                    window.draw(blackRectangle);
                }
                //cells explored by bfs
                /*
                if(filled[i/10][j/10] == 1){
                    yellowRectangle.setOutlineThickness(1);
                    yellowRectangle.setOutlineColor(Color::Red);
                    yellowRectangle.setPosition(j,i);
                    window.draw(yellowRectangle);
                }
                */
                
            }
        }
        text2.setPosition(620,50);
        text1.setPosition(620,10);       //Pathfinder Text Header
        window.draw(text1);
        window.draw(text2);
        GreenRectangle.setPosition(source_y*10,source_x*10);
        window.draw(GreenRectangle);     //source
        //filled[source_x][source_y]=1;
        redRectangle.setPosition(dest_y*10,dest_x*10);  
        window.draw(redRectangle);        //destination
        //filled[dest_x][dest_y]=1;

        window.display();

    }
    return 0;
}