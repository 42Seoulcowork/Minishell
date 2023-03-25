## 1. echo

`echo` 명령어는 후에 주어진 문자열을 출력하는 명령어이다. 

```shell
$minishell echo hello
>hello
$minishell echo -n hello
>hello$minishell 
```

위 예시처럼 -n이 옵션으로 주어지면 개행을 제거하고 출력되어야 한다.
이때 -n옵션이 -nnnnnnnnnnnnn 식으로 들어와도 작동이 되어야 한다.

## 2. cd

`cd` 는 현재 위치를 이동할 때, 사용하는 명령어이다. 
`chdir` 함수를 이용하여 구현하면 될 듯 하다.

```c
#include <unistd.h>

int chdir(const char *path);
```

`chdir` 함수는 변경할 디렉토리의 경로명을 받으며 시작점은 현재 디렉토리이다.

이때 환경변수 `PWD` 와 `OLDPWD` 를 각각 현재 위치와 이전 위치로 변경해야 한다.

## 3. export

`export` 는 환경변수 목록을 출력하는데 아래와 같은 형식으로 출력해야 한다. 

```shell
declare -x {KEY}={VALUE}
```

또한 {KEY}값을 기준으로 오름차순 정렬이 되어있어야 한다.
환경변수 {KEY} 값의 첫번째 글자에는 '_' 나 영어만 올 수 있다.
이미 선언되어 있는 환경변수를 {KEY}로 하는 경우 해당 환경변수의 {VALUE}를 변경한다.

## 4. unset


## 5. env


## 6. exit

`exit` 은 exit이란 문자열을 출력하고 주어진 값을 unsigned char 형식으로 exit한다.
이때, 주어진 값은 종료 상태에 저장된다.
만약 인자가 없다면 0으로 간주한다.

```shell
> bash
> delphinus@Delphinus-Laptop:~$ exit 25
exit
> echo $?
25
```

```shell
> bash
> delphinus@Delphinus-Laptop:~$ exit 256
exit
> echo $?
0
```

### 문자나 long long을 벗어날 때

종료상태는 imac에서 확인해봐야 한다.

```shell
> bash
> delphinus@Delphinus-Laptop:~$ exit a
exit
bash: exit: a: numeric argument required
> echo $?
2
``` 

```shell
> bash
> delphinus@Delphinus-Laptop:~$ exit 55555555555555555555555
exit
bash: exit: 55555555555555555555555: numeric argument required
> echo $?
2
```

### 두 개 이상의 인자가 들어올 경우

```shell
> bash
> delphinus@Delphinus-Laptop:~$ exit 5 2
exit
bash: exit: too many arguments
> delphinus@Delphinus-Laptop:~$ echo $?
1
```

## 7. pwd

`pwd` 는 현재 위치를 절대 경로로 나타내는 명령어다.
`getcwd` 함수를 이용하여 구현하면 될 것 같다.

```c
#include <unistd.h>

char    *getcwd(char *buf, size_t size);
```

buf를 할당해서 맞는 size를 줘도 된다.
하지만 할당과 맞는 size를 찾기 너무 귀찮고 어려울 수 있다.
또한 buf의 크기를 MAXPATHLEN(4096, <sys/param.h>에 정의되어 있음)보다 더 크게 줘야 한다.
그렇기에 buf에 NULL을 입력하여 `getcwd` 함수가 size와 관계없이 경로를 반환하도록 만드는게 좋을 듯하다.
