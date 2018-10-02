# Graphics Assn #1

##### <span style="float:right">20160785 양준하, 20160463 성해빈 </span>

## Introduction

이번 과제는 Opengl, 더 구체적으로는 glew와 freeglut를 이용해서 둠을 2D 시점으로 옮겨놓은 게임을 구현하는 과제이다.

## Background
### OpenGL, glew, freeglut
Opengl은 대표적인 크로스 플랫폼 라이브러리이다. opengl은 각 플랫폼이나 언어, 드라이버마다 구현이 다 다르므로 이것을 쉽게 사용할 수 있게 해주기 위해, 또 추가적인 기능을 더 쓸 수 있게 하기 위해 glew라는 extension loading library를 사용한다. freeglut는 순수 그래픽인 opengl에서 키보드 입력, 타이머,  마우스 입력 등등의 유틸리티 기능을 추가한 toolkit이다.
### 2D Rendering
우리가 작성하는 opengl 프로그램은 각 프레임마다 새로 화면을 계속 그려내는 식이다. double buffer로 애니메이션을 부드럽게 구현할 수 있으며, glViewport로 화면을 얼마만큼 렌더링할 것인지를 정하고, gluOrtho2D로 virtual world의 얼마만큼을 clipping할 것인지를 정한다. 이 clipping할 구역을 바꾸면서 세계 렌더링을 똑같이 하면 카메라 움직임이 되는 것이다. UI는 사이즈와 위치가 고정되는 것을 원하는데, 그 때는 사용자의 화면 비율과 같은 좌표계를 선언해서 고정 사이즈의 UI를 구현했다.

### default reshapefunc

```
If a reshape callback is not registered for a window or NULL is passed to glutReshapeFunc (to deregister a previously registered callback), the default reshape callback is used. This default callback will simply call glViewport(0,0,width,height) on the normal plane (and on the overlay if one exists).
```

reshape func를 지정하지 않았는데도 reshaping이 되는 것을 볼 수 있다. 그 이유는 default reshape callback이 있기 때문이다. `glViewport(0,0,width,height)`

### reshapefunc, displayfunc

reshape이 실행되고 나서, display가 실행된다.

첫 시작때도 reshape이 한 번 실행되고 display가 한 번 실행된다.

display는 이외에도 키보드 인풋이나 클릭에 반응해서 실행되기도 한다.

결국 여기서의 포인트는 display가 기본값으로는 지속적으로 실행되지는 않는다는 점이다.

### glclear, glclearcolor

glclearcolor는 glclear에 쓰일 초기화값을 설정해준다.

glclearcolor() -> glclear() 의 순서로 써야 한다는 뜻이다.

한 번 세팅해놓은 glclearcolor()는 glclear() 여러 번에 계속 적용된다.

### glutPostRedisplay()

glutDisplayFunc에 등록된 함수를 호출시켜준다. 다시 말해서 창을 다시 그려준다. 애니메이션을 구현하려면 지속적으로 display를 불러야하므로 필수다. 

### glLoadIdentity

새로 display를 그릴 때 반드시 필요한 작업으로, 현재 MatrixMode에 따른 matrix를 identity matrix로 초기화해주는 작업이다. 

### glMatrixMode

MatrixMode에는 4가지가 있는데, 우리는 원시적인 2D 구현이므로 다른 matrix로의 전환을 쓸 일이 아직 없다.

GL_MODELVIEW: 기본값

GL_PROJECTION

GL_TEXTURE

GL_COLOR

### glGet

opengl은 state machine을 표방하고 있어, 각각의 설정들이 ON/OFF 로 되어 있는지의 확인이 필요하다.

`glGet`으로 현재 MatrixMode나, 컬러나, 그런 잡다한 모든 설정 변수들을 확인할 수 있다.

### key, specialkey

ASCII code에 있는 건 key, 그 외는 specialkey이다.

x와 y는 그 키를 눌렀을 때의 mouse location

special key ref : <https://www.opengl.org/resources/libraries/glut/spec3/node54.html>

### glShadeModel

`GL_FLAT`과 `GL_SMOOTH`존재, flat shading과 smooth shading을 관리한다. 2D는 별 차이가 없는듯하다. 

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

OpenGL 사용법에 대해서는 레퍼런스를 참고했으나 순수 게임 Logic 파트는 창작이다.

[The OpenGL Utility Toolkit (GLUT) Programming Interface API Version 3](https://www.opengl.org/resources/libraries/glut/spec3/spec3.html)

[OpenGL® 4.5 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/)

[Lighthouse3d.com](http://www.lighthouse3d.com/tutorials/glut-tutorial/)

[opengl-tutorial](http://www.opengl-tutorial.org/)



```c++
glm::mat4 transform(glm::vec2 const& Orientation, glm::vec3 const& Translate, glm::vec3 const& Up)
{
	glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
	glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
	glm::mat4 Model = glm::mat4(1.0f);
	return Proj * View * Model;
}
```

