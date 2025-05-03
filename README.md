# mirrory
Небольшая игра, основанная на механике отражения и преломления световых лучей.

### build
Так как проект основан на библиотеке Raylib установить все необходимые зависимости для её сбоки. [Подробнее в документации  необходимо Raylib](https://github.com/raysan5/raylib/wiki)

x86_64:
```sh
cmake . -B build
cd build
make
```

web:
```sh
emcmake cmake . -B webbuild -DPLATFORM=Web
cd webbuild
make
```
