![](https://github.com/Sur1ive/42tokyo_piscine/blob/master/42.png)
# minishell
**Final grade: 105%**:white_check_mark:</br>

This project is a 3D renderer created in collaboration with [@ARATA](https://github.com/N-Art157). It utilizes the ray-casting algorithm, famously used in early 3D games like Wolfenstein 3D, to render a 2D map file into a first-person 3D perspective. The engine supports custom wall textures and ceiling/floor colors.

![](./demo.gif)

## Usage:
1. **Compile the project:**
```bash
make
```
2. **Run the renderer**
```bash
./cub3D <map file>

# example
./cub3D maps/map.cub
```

### Example Map File
- `NO`, `SO`, `WE`, `EA`: Path to the texture for North/South/West/East-facing walls.
- `F`, `C`: RGB color for the Floor and Ceiling.
- `1`: a solid wall.
- `0`: empty space.
- `N`, `S` ,`W` ,`E`: the player's starting position and initial viewing direction
```
NO ./textures/Textures-1.xpm
SO ./textures/Textures-2.xpm
WE ./textures/Textures-3.xpm
EA ./textures/Textures-4.xpm

F 99,62,0
C 102,170,255

111111111111111111111111
10000000000000000000001
 1000000000000000000001
  10000000S00000000001
   100000000100000001
    1000000000000001
     10000000000001
      100000000001
       1000000001
        10000001
         101101
          1001
           11
```
