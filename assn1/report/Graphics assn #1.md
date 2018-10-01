# Graphics Assn #1

##### <span style="float:right">20160785 양준하, 20160463 성해빈 </span>

## Introduction

## Background
### OpenGL
opengl, glut, glew, opengl frame, fuck, shit bullshit
### 2D Rendering
ortho2d...

### default reshapefunc

```
If a reshape callback is not registered for a window or NULL is passed to glutReshapeFunc (to deregister a previously registered callback), the default reshape callback is used. This default callback will simply call glViewport(0,0,width,height) on the normal plane (and on the overlay if one exists).
```

default callback calls `glViewport(0,0,width,height)` : why my glViewport() was being overridden

### reshapefunc, displayfunc

순서 : reshape -> display 한 번씩

처음 실행(resizing 없어도) 때도 동일하게 reshape -> display

resizing이 일어나고 있지 않으면 계속 불리지 않는다

클릭하면 display가 불림

### glclear, glclearcolor

glclearcolor는 glclear에 쓰일 초기화값을 설정해줌

glclearcolor() -> glclear() 의 순서로 써야 한다는 뜻

한 번 세팅해놓은 glclearcolor()는 glclear() 여러 번에 계속 적용됨

### glutPostRedisplay()

glutDisplayFunc에 등록된 함수를 호출시켜준다. 다시 말해서 창을 다시 그려준다.

### glLoadIdentity

새로 display 그릴 때 현재 MatrixMode에 따른 matrix를 identity matrix로 초기화해주는 작업, 필수

위치에 민감함 , 분석 필요

`glGet`으로 현재 MatrixMode알아낼 수 있음

### glMatrixMode

GL_MODELVIEW: 기본값

GL_PROJECTION

GL_TEXTURE

GL_COLOR

`glGet`으로 현재 MatrixMode알아낼 수 있음

### key, specialkey

ASCII code에 있는 건 key, 그 외는 specialkey

x와 y는 그 키를 눌렀을 때의 mouse location

special key ref : <https://www.opengl.org/resources/libraries/glut/spec3/node54.html>

### glShadeModel

`GL_FLAT`과 `GL_SMOOTH`존재, flat shading과 smooth shading

### clippling

`gluOrtho2D`로 카메라 위치 바꾸기 가능,

컴퓨터가 렌더링하는 가상좌표는 무한이고 `gluOrtho2D`로 우리가 보는 세계를 자른다고 생각하면 됨

### multiple viewport 에 관한 고찰

viewport여러개를 관리하려면

```
glViewport(0, 0, width / 2, height / 2);
glLoadIdentity();
gluOrtho2D(0.0, 100.0, 0.0, 100.0);
glColor3ub(0, 0, 255);
glRectd(0, 0, 33.3, 100);

glViewport(width / 2, 0, width / 2, height / 2);
glLoadIdentity();
gluOrtho2D(0.0, 100.0, 0.0, 100.0);
glColor3ub(255, 204, 0);
glRectd(0, 0, 100, 33.3);
```

이런 식의 코딩이 필요한데, 필연적으로 reshape과 display의 구조 개혁이 필요함(예시에서 나온 대로는 안 됨)

`glutCreateSubWindow`를 이용한 코딩도 가능한듯, 추후 조사

### glewinit의 필요성

??? 아직 모르겠다

## Gameplay
게임은 맵의 왼쪽 아래 모서리에서 시작한다. 
### Player

플레이어는 빨간색 세모로 표시된다. 방향키를 이용해 플레이어가 가는 방향을 조작할 수 있으며, 스페이스를 누르면 플레이어가 바라보는 방향으로 총알을 1개 쏘고, 그 옆에 미사일도 2개를 쏜다. 

### Enemy

적은 초록색 오각형으로 표시된다. 적은 평소에 랜덤하게 상하좌우로 움직이다가, 플레이어와 일정 거리가 되면 dijkstra 알고리즘을 이용해 플레이어를 추적한다. 이 일정 거리는 게임 진행에 따라 늘어나, 게임이 후반으로 갈 수록 어려워진다. 적은 랜덤으로 생성되지만, 적의 개수는 맵 파일에서 받아온다. 

### Item

아이템은 게임 시작때마다 랜덤으로 생성되고, 아이템의 개수는 맵 파일에서 받아온다.

#### 메가파이어

전방향으로 총알을 쏜다.

#### 슈퍼파이어

상하좌우 방향으로 총알을 쏜다.

#### 카메라

잠시동안 시야를 넓혀준다.

#### 신발

잠시동안 이동속도가 빨라진다.

#### 별

잠시동안 무적이 된다. 

## Implementation
### Develope Environment
### OpenGL
### Game Logic
## Example
## Discussion and Conclusion

## Reference

OpenGL 사용법에 대해서는 레퍼런스를 참고했으나 순수 게임 Logic 파트는 원본이다.

[The OpenGL Utility Toolkit (GLUT) Programming Interface API Version 3](https://www.opengl.org/resources/libraries/glut/spec3/spec3.html)

[OpenGL® 4.5 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/)

[Lighthouse3d.com](http://www.lighthouse3d.com/tutorials/glut-tutorial/)

[opengl-tutorial](http://www.opengl-tutorial.org/)

