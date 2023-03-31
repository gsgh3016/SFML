# 1. Environment

OS: Window 10<br>
Editor: VScode<br>
Compiler: MinGW 64 SEH<br>
<br>

## 1-1. tasks.json 설정

"args"에

"-I", "SFML-2.5.1\include 경로",<br>
"-L", "SFML-2.5.1\lib 경로",<br>
"-lsfml-window",<br>
"-lsfml-system",<br>
"-lsfml-graphics"<br>

추가.<br>
<br>

## 1-2. c_cpp_properties.json 설정

"includePath"에

"SFML-2.5.1\include 경로",<br>
"SFML-2.5.1\lib 경로",<br>

추가.<br>
<br>

## 1-3. 시스템 환경 변수

환경 변수 편집 - 환경 변수 - Path 선택 후 편집 - "SFML-2.5.1\bin" 추가.(.dll 파일들 포함하기 위함.) - VScode 재실행<br>
<br>

## 1-4. 실행

Run C/C++ File 선택 시 실행<br>
<br>
<hr>

# 2. clone하기

```linux
git clone https://github.com/gsgh3016/SFML [your dir]
```