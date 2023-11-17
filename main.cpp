#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>


int main()
{
    RenderWindow window(VideoMode(1000,600),"Grid");

    RectangleShape rectangle(Vector2f(10,10));   //White grid box
    rectangle.setFillColor(Color::White);
    RectangleShape brectangle(Vector2f(10,10));     //Black box for border
    brectangle.setFillColor(Color::Black);

    int grid[60][60];



    for(int i = 0;i<60;i++){
        for(int j = 0;j<60;j++){
            if(i == 0||i == 59||j ==0 || j == 59) grid[i][j] = 0; //adding the walls at the border
            else grid[i][j] = 1;
        }
    }

    for(int i = 0 ; i < 60;i++){
        for(int j = 0;j<60;j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    while(window.isOpen()){
        sf::Event evnt;

        

        while(window.pollEvent(evnt)){
            if(evnt.type == evnt.Closed){
                window.close();
            }   
        }

        for(int i = 0;i<=590;i+=10){
            for(int j = 0;j<=590;j+=10){
                //adding the default white cells
                if(grid[i/10][j/10] == 1){
                    rectangle.setOutlineThickness(2);
                    rectangle.setOutlineColor(Color::Blue);
                    rectangle.setPosition(j,i);
                    window.draw(rectangle);   

                }
                
                else if(grid[i/10][j/10] == 0){
                    brectangle.setOutlineThickness(2);
                    brectangle.setOutlineColor(Color::Red);
                    brectangle.setPosition(j,i);
                    window.draw(brectangle);
                }
                
            }
        }

        window.display();

    }
    return 0;
}