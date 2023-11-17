#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>


int main()
{   
    int filled[60][60];
    int grid[60][60];


    RenderWindow window(VideoMode(1000,600),"Grid");

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

    int source_x=2,source_y=2,dest_x=50,dest_y=56;      //Origin(2,3)->Goal(50,56)


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
                cout << "You tried to enter source grid box.";
                
            }
            //adding destination grid box
            if(evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::D){
               int mouse_x = Mouse::getPosition(window).x;
                int mouse_y = Mouse::getPosition(window).y;
                cout << mouse_x << " " <<mouse_y << endl;
                dest_x=mouse_y/10;
                dest_y = mouse_x/10;
                cout << "You tried to enter source grid box.";
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
                
            }
        }

        GreenRectangle.setPosition(source_y*10,source_x*10);
        window.draw(GreenRectangle);     //source
        filled[source_x][source_y]=1;
        redRectangle.setPosition(dest_y*10,dest_x*10);
        window.draw(redRectangle);        //destination
        filled[dest_x][dest_y]=1;

        window.display();

    }
    return 0;
}