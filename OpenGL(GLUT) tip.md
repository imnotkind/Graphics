# OpenGL(glew + GLUT) tip



## default reshapefunc

```
If a reshape callback is not registered for a window or NULL is passed to glutReshapeFunc (to deregister a previously registered callback), the default reshape callback is used. This default callback will simply call glViewport(0,0,width,height) on the normal plane (and on the overlay if one exists).
```

default callback calls `glViewport(0,0,width,height)` : why my glViewport() was being overridden



## reshapefunc, displayfunc

순서 : reshape -> display 한 번씩

처음 실행(resizing 없어도) 때도 동일하게 reshape -> display

resizing이 일어나고 있지 않으면 계속 불리지 않는다

클릭하면 display가 불림



## glclear, glclearcolor

glclearcolor는 glclear에 쓰일 초기화값을 설정해줌

glclearcolor() -> glclear() 의 순서로 써야 한다는 뜻

한 번 세팅해놓은 glclearcolor()는 glclear() 여러 번에 계속 적용됨



## glutPostRedisplay()

glutDisplayFunc에 등록된 함수를 호출시켜준다. 다시 말해서 창을 다시 그려준다.



## glLoadIdentity

새로 display 그릴 때 현재 MatrixMode에 따른 matrix를 identity matrix로 초기화해주는 작업, 필수

위치에 민감함 , 분석 필요

`glGet`으로 현재 MatrixMode알아낼 수 있음



## glMatrixMode

GL_MODELVIEW: 기본값

GL_PROJECTION

GL_TEXTURE

GL_COLOR

`glGet`으로 현재 MatrixMode알아낼 수 있음

## key, specialkey

ASCII code에 있는 건 key, 그 외는 specialkey

x와 y는 그 키를 눌렀을 때의 mouse location

special key ref : https://www.opengl.org/resources/libraries/glut/spec3/node54.html



## glShadeModel

`GL_FLAT`과 `GL_SMOOTH`존재, flat shading과 smooth shading



## multiple viewport 에 관한 고찰

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



## glewinit의 필요성

??? 아직 모르겠다