# Инструкция по установке SDL2 в Visual Studio 2022 comunity #

- скачать Simple-SDL-Project.zip и vclib.zip
- создать проэкт консольное приложение
- заменить файлы проэкта на файлы из архива Simple-SDL-Project.zip
- распаковать содержимое архива vclib.zip в C:\
- следуя инструкции https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php#8 добавить в Path :
- - C:\vclib\SDL2-LIB\lib\x64
- - C:\vclib\SDL2_ttf-LIB\lib\x64
- - C:\vclib\SDL2_mixer-LIB\lib\x64
- - C:\vclib\SDL2_mixer-LIB\lib\x64\optional
- - C:\vclib\SDL2_image-LIB\lib\x64
- - C:\vclib\SDL2_image-LIB\lib\x64\optional
- Готово ! Можно пользоваться !
