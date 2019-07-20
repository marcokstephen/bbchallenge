## game

```
g++ *.cpp
./a.out <movefile>
```

### Basic Test
```
GAME-START
R:S
R:S
R:E
R:E
R:E
R:E
R:E
R:E
R:E
R:N
R:N
R:N
GAME-END
```

### Output
```
g++ *.cpp
./a.out movefile.txt
```
```
B: [[7,0],"LIVE",null,1,1]
G: [[7,7],"LIVE",null,1,1]
R: [null,"DROWNED",null,0,0]
Y: [[0,7],"DEAD",null,0,0]
A: [[0,7],false]
D: [[2,5],false]
H: [[5,5],false]
M: [[5,2],false]
```

