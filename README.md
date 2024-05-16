# Fdf
 ’fil de fer’ in French which means wireframe model.
 
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf_main.jpg">
  
 ## Introduction
  * This project is about creating a simple wireframe model representation of a 3D landscape by linking various points (x, y, z) thanks to line segments (edges).
  * The fdf represent the model in isometric projection.
  * The coordinates of the landscape are stored in a `.fdf` file passed as a parameter to your program. Here is an example:
    
    ```shall
    $>cat 42.fdf
    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
    0  0  10 10 0  0  10 10 0  0  0  10 10 10 10 10 0  0  0
    0  0  10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
    0  0  10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
    0  0  10 10 10 10 10 10 0  0  0  0  10 10 10 10 0  0  0
    0  0  0  10 10 10 10 10 0  0  0  10 10 0  0  0  0  0  0
    0  0  0  0  0  0  10 10 0  0  0  10 10 0  0  0  0  0  0
    0  0  0  0  0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
    $>
    ```
    Each number represents a point in space:   
    ◦ The horizontal position corresponds to its axis.   
    ◦ The vertical position corresponds to its ordinate.   
    ◦ The value corresponds to its altitude.

## Process
* When the program runs, it initially validates the argument.   
  ◦ Validation follows three rules.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf1.jpg">   
  ◦ Verify that the contents of the file fit the rules and format.
  ◦ And parse the file into a instruction structure while reading it.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf2.jpg">
* Create and fill a map that is a double array of coordinates.    
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf3.jpg">   
  ◦ The size of the map is calculated by the number of rows and columns in the instruction.   
  ◦ Multiply the size by the length to find the size to display on the window.   
  ◦ If know the size of the map, can also get the size of the window.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf4.jpg">    
* Visualize calculating the size   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf5.jpg">
* If the window becomes too big, apply the scale.
  ◦ When the scale exceeds 50, the program ends.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf6.jpg">
* Create the window and image to print.   
  ◦ Using the graphics library [`minilibx`](https://github.com/42Paris/minilibx-linux).   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf7.jpg">
* Draw a wire frame to display in the generated image.
  ◦ The method of drawing a wire frame uses two coordinates to create a line and fills that line.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf8.jpg">   
  ◦ And the beginning of the pixel is the top left of the image.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf9.jpg">   
  ◦ Visualize how to calculate coordinates.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf10.jpg">   
  ◦ Visualize how to draw a line using two calculated coordinates.   
  <img alt="image" src="https://github.com/leebo155/Fdf/blob/main/img/fdf11.jpg">

## Makefile
| Rules | Description |
| ----- | ----------- |
| all | Compile a program fdf. |
| clean | Remove all the temporary generated files. |
| fclean | Remove all the generated files. |
| re | Remove all the generated files and compile a fdf. |

## Usage
```shall
$> ./fdf [fdf file]
```
